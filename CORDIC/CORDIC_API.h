/*
 * CORDIC_API.h
 *
 *  Created on: Jan 16, 2022
 *      Author: batuhan
 */

#ifndef INC_CORDIC_API_H_
#define INC_CORDIC_API_H_

#include "stm32g4xx_hal.h"
#include "math.h"

#define _PI	3.1415926535897932384626433f
#define	_2_POW_31	2147483648.0f
#define q31_to_f32(x)	( (float)(x)/(_2_POW_31) )

extern CORDIC_HandleTypeDef hcordic;

int f32_to_q31(double input);
HAL_StatusTypeDef API_CORDIC_COMPUTE(float theta, float *c, float *s);
HAL_StatusTypeDef	API_CORDIC_Init(void);



#endif /* INC_CORDIC_API_H_ */
