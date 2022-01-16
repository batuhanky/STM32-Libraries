/*
 * CORDIC_API.c
 *
 *  Created on: Jan 16, 2022
 *      Author: batuhan
 */


#include "CORDIC_API.h"

int f32_to_q31(double input) {
	const float Q31_MAX_F = 0x0.FFFFFFp0F;
	const float Q31_MIN_F = -1.0f;
	return (int)roundf(scalbnf(fmaxf(fminf(input, Q31_MAX_F), Q31_MIN_F), 31));
}

HAL_StatusTypeDef API_CORDIC_Init(void) {
	CORDIC_ConfigTypeDef config = {
			CORDIC_FUNCTION_COSINE,
			CORDIC_SCALE_0,
			CORDIC_INSIZE_32BITS,
			CORDIC_OUTSIZE_32BITS,
			CORDIC_NBWRITE_1,
			CORDIC_NBREAD_2,
			CORDIC_PRECISION_6CYCLES
	};
	return HAL_CORDIC_Configure(&hcordic, &config);
}

HAL_StatusTypeDef API_CORDIC_COMPUTE(float theta, float *c, float *s) {
	int32_t input_buff[1] = {0};
	input_buff[0] = f32_to_q31(fmodf(theta, 2.0f * _PI) / (2.0f * _PI)) << 1;
	int32_t output_buff[2] = {0, 0};
	HAL_StatusTypeDef state = HAL_CORDIC_Calculate(&hcordic, input_buff, output_buff, 1, 10);
	if(state == HAL_OK) {
		if(c!=0) {
			*c = q31_to_f32(output_buff[0]);
		}
		if(s!=0) {
			*s = q31_to_f32(output_buff[1]);
		}
	}
	return state;
}
