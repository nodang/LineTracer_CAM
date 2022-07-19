--------------------------------------------------------------------
																		
	@file 		Convert Sensor Value to Distance

	@brief		Convert Sensor Value to Distance Header File

				�ʱ� Ư�� ��ġ������ �Ÿ��� ���� ���ذ��� ������ ��,
				�������� ���� ��ġ�� ����Ͽ� ����� ���Ѵ�.

	@author		�ڼ���

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
	brief	�Ÿ��� ���� ���̺��� ����� ���� ������ ����
*/
typedef struct
{
	// �Ÿ�
	Uint16	Dis[STOD_SEP_N];	///< �Ÿ��� �迭

	// ����
	Uint16	Sen[STOD_SEP_N];	///< ������ �迭

	// ����
	_iq		iqSlope[STOD_SEP_N-1];///< ���Ⱚ �迭
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
