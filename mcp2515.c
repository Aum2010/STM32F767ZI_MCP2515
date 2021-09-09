/*
 * mcp2515.c
 *
 *  Created on: 8 ก.ย. 2564
 *      Author: PC
 */

#include "mcp2515.h"
#include "stdint.h"

extern SPI_HandleTypeDef 		hspi1;
#define SPI_CAN                 &hspi1
#define SPI_TIMEOUT             10

#define SPI_SELECT()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)

#define SPI_UNSELECT() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)

uint8_t mcp2515_initialize ( void )
{
	uint8_t count = 10;
	SPI_SELECT();

	do
	{
		if( HAL_SPI_GetState(SPI_CAN) == HAL_SPI_STATE_READY )
			return 1;

		count--;
	}while ( count > 0 );
			return 0;
}

uint8_t mcp2515_setmode_normalmode ( void )
{
	uint8_t count = 10;
	mcp2515_write(MCP2515_CANSTAT, 0x00) ;

	do
	{
		if( (mcp2515_read(MCP2515_CANSTAT) & 0xe0) == 0x00 )
		{
			return 1 ;
		}

		count--;
	}while( count > 0 ) ;
		return 0;
}

uint8_t mcp2515_setmode_configmode ( void )
{
	uint8_t count = 10;
	mcp2515_write(MCP2515_CANSTAT, 0x80) ;

	do{
		if( (mcp2515_read(MCP2515_CANSTAT) & 0xe0 ) == 0x80 ){
			return 1;
		}

		count--;
	}while( count > 0 );
			return 0;
}

void mcp2515_reset ( void )
{
	SPI_SELECT();
	HAL_SPI_Transmit(SPI_CAN, (uint8_t)MCP2515_RESET , 1, SPI_TIMEOUT);
	SPI_UNSELECT();
}

void mcp2515_write ( uint8_t address , uint8_t data)
{
//	uint8_t inst = 0x02;
	SPI_SELECT();

	HAL_SPI_Transmit(SPI_CAN, (uint8_t)(MCP2515_WRITE) , 1, SPI_TIMEOUT);
	HAL_SPI_Transmit(SPI_CAN, &address, 1, SPI_TIMEOUT);
	HAL_SPI_Transmit(SPI_CAN, &data, 1, SPI_TIMEOUT);

	SPI_UNSELECT();

}

void mcp2515_write_sequence ( uint8_t address , uint8_t data , uint8_t length)
{
	  SPI_SELECT();

	  HAL_SPI_Transmit(SPI_CAN, (uint8_t)MCP2515_WRITE , 1, SPI_TIMEOUT);
	  HAL_SPI_Transmit(SPI_CAN, &address, 1, SPI_TIMEOUT);
	  HAL_SPI_Transmit(SPI_CAN, &data, 1, SPI_TIMEOUT);

	  SPI_UNSELECT();

}


uint8_t mcp2515_read ( uint8_t address )
{
	  uint8_t res ;
	  uint8_t inst = 0x03;

	  SPI_SELECT();
	  HAL_SPI_Transmit(SPI_CAN, &inst , 1, SPI_TIMEOUT);
	  HAL_SPI_Transmit(SPI_CAN, &address, 1, SPI_TIMEOUT);
	  HAL_SPI_Receive(SPI_CAN, &res, 1, SPI_TIMEOUT);

	  SPI_UNSELECT();

	  return res ;
}

uint8_t mcp2515_read_sequence ( uint8_t address , uint8_t length )
{
	  uint8_t res ;

	  SPI_SELECT();
	  HAL_SPI_Transmit(SPI_CAN,(uint8_t *)MCP2515_READ , 1, SPI_TIMEOUT);
	  HAL_SPI_Transmit(SPI_CAN, &address, 1, SPI_TIMEOUT);
	  HAL_SPI_Receive(SPI_CAN, &res, length , SPI_TIMEOUT);

	  SPI_UNSELECT();

	  return res ;
}

uint8_t mcp2515_read_status( void )
{
	uint8_t res ;

	SPI_SELECT();
	HAL_SPI_Transmit(SPI_CAN,(uint8_t)MCP2515_READ_STATUS , 1, SPI_TIMEOUT);
	HAL_SPI_Receive(SPI_CAN, &res, 1 , SPI_TIMEOUT);
	SPI_UNSELECT();

	return res ;
}

uint8_t mcp2515_getRx_status ( void )
{
	uint8_t res ;
	SPI_SELECT();

	HAL_SPI_Transmit(SPI_CAN,(uint8_t)MCP2515_RX_STATUS , 1, SPI_TIMEOUT);
	HAL_SPI_Receive(SPI_CAN, &res, 1 , SPI_TIMEOUT);

	SPI_UNSELECT();

	return res ;
}

void mcp2515_bit_modify( uint8_t address , uint8_t mask ,uint8_t data )
{
	SPI_SELECT();
	HAL_SPI_Transmit(SPI_CAN,(uint8_t)MCP2515_BIT_MOD , 1, SPI_TIMEOUT);
	HAL_SPI_Transmit(SPI_CAN, &address , 1, SPI_TIMEOUT);
	HAL_SPI_Transmit(SPI_CAN, &mask , 1, SPI_TIMEOUT);
	HAL_SPI_Transmit(SPI_CAN, &data , 1, SPI_TIMEOUT);
	SPI_UNSELECT();
}

void mcp2515_request_to_send( uint8_t instruction )
{
	SPI_SELECT();

	HAL_SPI_Transmit(SPI_CAN, &instruction , 1, SPI_TIMEOUT);

	SPI_UNSELECT();
}

void mcp2515_loadTx_Sequence( uint8_t instruction, uint8_t *idReg, uint8_t dlc, uint8_t *data )
{
	SPI_SELECT();

	HAL_SPI_Transmit(SPI_CAN, &instruction , 1, SPI_TIMEOUT);
	HAL_SPI_Transmit(SPI_CAN, idReg , 4, SPI_TIMEOUT);
	HAL_SPI_Transmit(SPI_CAN, &dlc , 1, SPI_TIMEOUT);
	HAL_SPI_Transmit(SPI_CAN, data , dlc, SPI_TIMEOUT);

	SPI_UNSELECT();
}



