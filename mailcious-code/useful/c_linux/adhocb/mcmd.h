/*
 *	By using this file, you agree to the terms and conditions set
 *	forth in the COPYING file which can be found at the top level
 *	of this distribution.
 */
#ifndef MCMD_H
#define MCMD_H

#define	C_NOP		0
#define	C_RET		1
#define	C_PUSHA		2
#define	C_POPA		3
#define	C_INC_R		4
#define	C_JCC		5
#define	C_XOR_MR_C8	6
#define	C_SUB_MR_C8	7
#define	C_ADD_MR_C8	8
#define	C_PUSH_C	9
#define	C_CALL_C	10
#define	C_MOV_R_C	11
#define	C_CMP_R_C	12

#define	JCC_JO		0
#define	JCC_JNO		1
#define	JCC_JB		2
#define	JCC_JNB		3
#define	JCC_JE		4
#define	JCC_JNE		5
#define	JCC_JBE		6
#define	JCC_JA		7
#define	JCC_JS		8
#define	JCC_JNS		9
#define	JCC_JP		10
#define	JCC_JNP		11
#define	JCC_JL		12
#define	JCC_JNL		13
#define	JCC_JLE		14
#define	JCC_JG		15

#endif	/* MCMD_H */
