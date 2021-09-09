/*
 * define_mcp2515.h
 *
 *  Created on: Sep 8, 2021
 *      Author: wasurat.l
 */

#ifndef INC_DEFINE_MCP2515_H_
#define INC_DEFINE_MCP2515_H_

#define CANINTF_RX0IF 0x01
#define CANINTF_RX1IF 0x02
#define CANINTF_TX0IF 0x04
#define CANINTF_TX1IF 0x08
#define CANINTF_TX2IF 0x10
#define CANINTF_ERRIF 0x20
#define CANINTF_WAKIF 0x40
#define CANINTF_MERRF 0x80

static const uint8_t CANSTAT_OPMOD = 0xE0;
static const uint8_t CANSTAT_ICOD = 0x0E;

static const uint8_t CNF3_SOF = 0x80;

static const uint8_t TXB_EXIDE_MASK = 0x08;
static const uint8_t DLC_MASK       = 0x0F;
static const uint8_t RTR_MASK       = 0x40;

static const uint8_t RXBnCTRL_RXM_STD    = 0x20;
static const uint8_t RXBnCTRL_RXM_EXT    = 0x40;
static const uint8_t RXBnCTRL_RXM_STDEXT = 0x00;
static const uint8_t RXBnCTRL_RXM_MASK   = 0x60;
static const uint8_t RXBnCTRL_RTR        = 0x08;
static const uint8_t RXB0CTRL_BUKT       = 0x04;
static const uint8_t RXB0CTRL_FILHIT_MASK = 0x03;
static const uint8_t RXB1CTRL_FILHIT_MASK = 0x07;
static const uint8_t RXB0CTRL_FILHIT = 0x00;
static const uint8_t RXB1CTRL_FILHIT = 0x01;

static const uint8_t MCP_SIDH = 0;
static const uint8_t MCP_SIDL = 1;
static const uint8_t MCP_EID8 = 2;
static const uint8_t MCP_EID0 = 3;
static const uint8_t MCP_DLC  = 4;
static const uint8_t MCP_DATA = 5;


#endif /* INC_DEFINE_MCP2515_H_ */
