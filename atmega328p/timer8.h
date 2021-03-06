#ifndef TIMER8_H_
#define TIMER8_H_
#include <stdint.h>

#include "common.h"
#include "timer-common.h"



enum Timer8Opmode { TOM8_NORMAL = 0,
					TOM8_CTC = 2,
					TOM8_PWM_FAST = 3, 
					TOM8_PWM_PHASE_CORRECT  = 1 };

enum Timer8Matchmode { MM_NONE,
					   MM_TOGGLE,
					   MM_CLEAR,
					   MM_SET };



static enum TimerClkSrc saved_clk_src = TCS_NONE;

inline int t0_clk_src_set(enum TimerClkSrc clk_src)
{
	TCCR0B = (TCCR0B & ~(7 << CS00)) | clk_src;
	return ERR_SUCCESS;
}

inline enum TimerClkSrc t0_clk_src_get(void)
{
	return TCCR0B & (7 << CS00);
}

inline void t0_enable(void)
{
	t0_clk_src_set(saved_clk_src);	
}

inline void t0_disable(void)
{	
	saved_clk_src = t0_clk_src_get();
	t0_clk_src_set(TCS_NONE);	
}




inline int t0_opmode_set(enum Timer8Opmode opmode)
{
	TCCR0A = (TCCR0A & ~(3 << WGM00)) | opmode;
	TCCR0B = TCCR0B & ~(1 << WGM02);
	return ERR_SUCCESS;
}


inline int t2_opmode_set(enum Timer8Opmode opmode)
{
	TCCR2A = (TCCR2A & ~(3 << WGM00)) | opmode;
	TCCR2B = TCCR2B & ~(1 << WGM02);
	return ERR_SUCCESS;
}

inline int t0_cha_matchmode_set(enum Timer8Matchmode match_mode)
{
	TCCR0A = (TCCR0A & ~(3 << COM0A0)) | match_mode  << COM0A0;
	return ERR_SUCCESS;
}

inline enum Timer8Matchmode t0_cha_matchmode_get(void)
{
	return (TCCR0A & (3 << COM0A0)) >> COM0A0;
}
#endif