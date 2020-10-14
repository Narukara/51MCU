#ifndef _NARUKARA_NRF24L01_H_
#define _NARUKARA_NRF24L01_H_

#include "type.h"

/*******************************
 * Don't forget to check CE, SCLK, MISO, CSN, MOSI, IRQ
 *******************************/

// SPI command
#define R_REGISTER 0x00    // read register
#define W_REGISTER 0x20    // write register
#define R_RX_PAYLOAD 0x61  // read RX data
#define W_TX_PAYLOAD 0xa0  // write TX data
#define FLUSH_TX 0xe1      // clean TX FIFO
#define FLUSH_RX 0xe2      // clean RX FIFO
#define REUSE_TX_PL 0xe3   // cyclically transmit
#define NOP 0xff           // nope

// register address
#define CONFIG 0x00       // config
#define EN_AA 0x01        // enable auto answer (channel)
#define EN_RXADDR 0x02    // enable receive channel
#define SETUP_AW 0x03     // addr length
#define SETUP_RETR 0x04   // retry setup
#define RF_CH 0x05        // radio frequency channel
#define RF_SETUP 0x06     // radio frequency setup
#define STATUS 0x07       // status
#define OBSERVE_TX 0x08   // retry status
#define CD 0x09           // carrier detect
#define RX_ADDR_P0 0x0a   // channel 0 receive addr
#define RX_ADDR_P1 0x0b   // channel 1 receive addr
#define RX_ADDR_P2 0x0c   // channel 2 receive addr
#define RX_ADDR_P3 0x0d   // channel 3 receive addr
#define RX_ADDR_P4 0x0e   // channel 4 receive addr
#define RX_ADDR_P5 0x0f   // channel 5 receive addr
#define TX_ADDR 0x10      // transmit addr
#define RX_PW_P0 0x11     // channel 0 receive data length
#define RX_PW_P1 0x12     // channel 1 receive data length
#define RX_PW_P2 0x13     // channel 2 receive data length
#define RX_PW_P3 0x14     // channel 3 receive data length
#define RX_PW_P4 0x15     // channel 4 receive data length
#define RX_PW_P5 0x16     // channel 5 receive data length
#define FIFO_STATUS 0x17  // FIFO status

void NRF24L01_init();
u8 SPI_RW(u8 c);
u8 SPI_read_reg(u8 reg_addr);
void SPI_write_reg(u8 reg_addr, u8 reg_data);
void SPI_read_multi(u8 reg_addr, u8 *reg_data, u8 len);
void SPI_write_multi(u8 reg_addr, u8 *reg_data, u8 len);
void NRF24L01_running(bit ce);
void NRF24L01_SetTxMode(u8 *TX_addr);
void NRF24L01_transmit(u8 *TX_data, u8 TX_data_len);
void NRF24L01_SetRxMode(u8 *RX_addr, u8 TX_data_len);
void NRF24L01_receive(u8 *RX_data, u8 RX_data_len);
u8 NRF24L01_checkACK();

/************* EXAMPLE ****************
#include "NRF24L01.h"
#include "time.h"
#include "type.h"
#include "uart.h"

u8 addr[] = {0x20, 0x20, 0x20, 0x30, 0x30};
u8 dt[6];

void main() {
    set_UART_mode(0, 1, 0, 1);
    set_UART_19200();
    NRF24L01_init();
    delay_1s();

    NRF24L01_SetRxMode(addr, 5);
    NRF24L01_running(1);
    while (1) {
        NRF24L01_receive(dt, 5);
        UART_send_string(dt);
    }

    // NRF24L01_SetTxMode(addr);
    // while (1) {
    //     NRF24L01_transmit(addr, 5);
    //     NRF24L01_running(1);
    //     delay_100ms();
    //     UART_send(NRF24L01_checkACK());
    //     NRF24L01_running(0);
    // }
}
 *
 */

#endif