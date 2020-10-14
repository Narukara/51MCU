#include "NRF24L01.h"

#include <REG51.H>

#include "time.h"

sbit CE = P1 ^ 0;    // if running
sbit SCLK = P1 ^ 1;  // SPI Clock
sbit MISO = P1 ^ 2;  // SPI master in slave out
sbit CSN = P1 ^ 3;   // SPI Chip Select
sbit MOSI = P1 ^ 4;  // SPI master out slave in
sbit IRQ = P1 ^ 5;   // TX/RX interrupt

static u8 bdata status;
sbit RX_DR = status ^ 6;   // receive interrupt
sbit TX_DS = status ^ 5;   // transmit interrupt
sbit MAX_RT = status ^ 4;  // retry overflow interrupt

// Don't forget to call this function!!
void NRF24L01_init() {
    delay_10ms();
    CE = 0;
    CSN = 1;
    SCLK = 0;
    IRQ = 1;
}

/*
 * Don't forget to set CSN when calling this function
 * It seems that NRF24L01 can only accept one command during one Chip Select
 */
u8 SPI_RW(u8 c) {
    u8 i = 0;
    // CSN = 0;
    for (; i < 8; i++) {
        MOSI = c & 0x80;
        c <<= 1;
        SCLK = 1;
        c |= (MISO & 0x01);
        SCLK = 0;
    }
    // CSN = 1;
    return c;
}

// R_REGISTER : 000A AAAA
u8 SPI_read_reg(u8 reg_addr) {
    u8 reg_data;
    CSN = 0;
    SPI_RW(reg_addr);
    reg_data = SPI_RW(NOP);
    CSN = 1;
    return reg_data;
}

/*
 * W_REGISTER : 001A AAAA
 * only call this function when NRF24L01 is not running
 */
void SPI_write_reg(u8 reg_addr, u8 reg_data) {
    CSN = 0;
    SPI_RW(reg_addr | 0x20);
    SPI_RW(reg_data);
    CSN = 1;
}

void SPI_read_multi(u8 reg_addr, u8 *reg_data, u8 len) {
    CSN = 0;
    SPI_RW(reg_addr);
    for (; len > 0; len--) {
        *reg_data = SPI_RW(NOP);
        reg_data++;
    }
    CSN = 1;
}

// only call this function when NRF24L01 is not running
void SPI_write_multi(u8 reg_addr, u8 *reg_data, u8 len) {
    CSN = 0;
    SPI_RW(reg_addr | 0x20);
    for (; len > 0; len--) {
        SPI_RW(*reg_data);
        reg_data++;
    }
    CSN = 1;
}

// the only function that will change CE, except for init
void NRF24L01_running(bit ce) {
    CE = ce;
    delay_1ms();
}

/*
 * only call this function when NRF24L01 is not running
 *
 * using channel 0, addr length = 5, auto retry,
 * radio frequency channel = 0x40, 1Mbps, 0dBm
 */
void NRF24L01_SetTxMode(u8 *TX_addr) {
    SPI_write_reg(CONFIG, 0x0e);  // CRC 16
    SPI_write_reg(EN_RXADDR, 0x01);
    SPI_write_reg(SETUP_RETR, 0x3a);
    SPI_write_reg(RF_CH, 0x40);
    SPI_write_reg(RF_SETUP, 0x07);
    SPI_write_multi(RX_ADDR_P0, TX_addr, 5);
    SPI_write_multi(TX_ADDR, TX_addr, 5);
}

// call NRF24L01_running(1) after this to start transmission
void NRF24L01_transmit(u8 *TX_data, u8 TX_data_len) {
    SPI_write_multi(W_TX_PAYLOAD, TX_data, TX_data_len);
}

/*
 * only call this function when NRF24L01 is not running
 *
 * using channel 0, addr length = 5,
 * radio frequency channel = 0x40
 *
 * call NRF24L01_running(1) after this to start reception
 */
void NRF24L01_SetRxMode(u8 *RX_addr, u8 TX_data_len) {
    SPI_write_reg(CONFIG, 0x0f);  // CRC 16
    SPI_write_reg(EN_AA, 0x01);
    SPI_write_reg(EN_RXADDR, 0x01);
    SPI_write_reg(RF_CH, 0x40);
    SPI_write_reg(RF_SETUP, 0x07);
    SPI_write_multi(RX_ADDR_P0, RX_addr, 5);
    SPI_write_reg(RX_PW_P0, TX_data_len);
}

/*
 * Blocking method
 * this function won't change CE
 */
void NRF24L01_receive(u8 *RX_data, u8 RX_data_len) {
retry:
    status = SPI_read_reg(STATUS);
    if (RX_DR) {
        bit temp = CE;
        CE = 0;
        SPI_read_multi(R_RX_PAYLOAD, RX_data, RX_data_len);
        SPI_write_reg(STATUS, 0x40);
        CE = temp;
        return;
    } else {
        goto retry;
    }
}

/**
 * if transmit successful, return 1
 * if all attempt failed, return 2
 * else return 0
 */
u8 NRF24L01_checkACK() {
    status = SPI_read_reg(STATUS);
    if (MAX_RT) {
        bit temp = CE;
        CE = 0;
        SPI_write_reg(STATUS, 0x10);
        CSN = 0;
        SPI_RW(FLUSH_TX);
        CSN = 1;
        CE = temp;
        return 2;
    }
    if (TX_DS) {
        bit temp = CE;
        CE = 0;
        SPI_write_reg(STATUS, 0x20);
        CSN = 0;
        SPI_RW(FLUSH_TX);
        CSN = 1;
        CE = temp;
        return 1;
    }
    return 0;
}