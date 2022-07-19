--------------------------------------------------------------------
																		
	@file 		Convert Sensor Value to Distance

	@brief		Convert Sensor Value to Distance Header File

				초기 특정 위치에서의 거리와 센서 기준값을 설정한 후,
				센서값에 따라 위치를 계산하여 결과를 구한다.

	@author		박선응

	@date		2007/07/26

----------------------------------------------------------------------*/

#ifndef	__STOD_H
#define	__STOD_H


#include "DSP280x_Device.h"



//-- Define -----------------------------------------------------------

#define	STOD_SEP_N		5


//-- Structure --------------------------------------------------------
/**	
	struct	Sensor Value to Distance Info
	brief	거리대 광량 테이블을 만들기 위한 정보를 저장
*/
typedef struct
{
	// 거리
	Uint16	Dis[STOD_SEP_N];	///< 거리값 배열

	// 센서
	Uint16	Sen[STOD_SEP_N];	///< 센서값 배열

	// 기울기
	_iq		iqSlope[STOD_SEP_N-1];///< 기울기값 배열
}STOD;



//-- Function Prototype -----------------------------------------------
void	StoD_SetBaseDistance( const Uint16 senN, const Uint16 *pDisArray );
void	StoD_SetBaseSensor( const Uint16 senN, const Uint16 *pSenArray );

void	StoD_CalSlope( const Uint16 senN );

Uint16	StoD_GetDistance( const Uint16 senN, const Uint16 senValue );

// Write/Read ROM
void	StoD_WriteROM( void );
void	StoD_ReadROM( void );


#endif
