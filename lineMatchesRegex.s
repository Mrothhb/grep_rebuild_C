/*
 * Filename: lineMatchesRegex.s
 * Author: Matt Roth 
 * UserId: cs30xgs
 * Date: May 29th, 2019
 * Sources of Help: Textbook, lecture notes, and discussion section notes.
 *
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Version of our Pis
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4		@ Offset from sp to set fp
	.equ	PARAM_SPACE, 8		@ allocate space for the parameters

	.global	lineMatchesRegex	@ Specify lineMatchesRegex as a global 
					@ symbol

	.text				@ Switch to Text segment 
	.align 2			@ Align on evenly divisible by 4 byte 
					@ address;
					@.align n where 2^n determines alignment
/*
 * Function Name: lineMatchesRegex()
 * Function Prototype: int lineMatchesRegex( const regex_t * pattern,
 *		       const char * line );
 * Description: Checks if a line matches the regex pattern by calling regexec.
 * Parameters: pattern - the regex pattern to check for matching pattern.
 *	       line    - the line to search for a match in regex.	
 * Side Effects: The patterns matches. 
 * Error Conditions: None.
 * Return Value: 1 if the lines matches and 0 otherwise. 
 *
 * Registers used:
 *	r0 - arg 1 -- the pattern, and the argument to regexc().
 *	r1 - arg 2 -- the line and the argument to regexc.
 *	r2 - local var -- the third argument to regexec.
 *	r3 - local var -- the fourth argument to regexec.
 *
 * Stack variables:
 *	arg 5	-- store argument 5 to regexec() on stack, at [sp]
 */
lineMatchesRegex:
@ Standard prologue
 	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
					@ Uses 4, from (#_of_regs_saved - 1)*4.
	sub	sp, sp, PARAM_SPACE	@ allocate space for the formal params 
	mov	r3, 0			@ get ready to store 0 as 5th arg
	str	r3, [sp]		@ store the 5th arg on the stack
	mov	r2, 0			@ move 0 into the third argument

	bl	regexec			@ regexec( pattern, line, 0 , 0 ,0 );
	add	sp, sp, PARAM_SPACE	@ deallocate the 5th argument 

@ if( regexec == 0 ) { return 1;} 
@ else { return 0; }
	cmp	r0, 0			@ compare the retrun value to 0
	bne	else			@ if( regexec != 0 )
	mov	r0, 1			@ move 1 into the return value 
	b	end			@ return the value 

@ the line did not match
else:
	mov	r0, 0			@ move 1 into the return value
	
end:
@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@ return 
