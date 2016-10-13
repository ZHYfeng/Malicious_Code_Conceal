	.file	"ghttpd"
	.section	.debug_info,"",@progbits
.Lsection_info:
	.section	.debug_abbrev,"",@progbits
.Lsection_abbrev:
	.section	.debug_aranges,"",@progbits
	.section	.debug_macinfo,"",@progbits
	.section	.debug_line,"",@progbits
.Lsection_line:
	.section	.debug_loc,"",@progbits
	.section	.debug_pubnames,"",@progbits
	.section	.debug_pubtypes,"",@progbits
	.section	.debug_str,"MS",@progbits,1
.Linfo_string:
	.section	.debug_ranges,"",@progbits
.Ldebug_range:
	.section	.debug_loc,"",@progbits
.Lsection_debug_loc:
	.text
.Ltext_begin:
	.data
	.file	1 "main.c"
	.file	2 "./ghttpd.h"
	.file	3 "/usr/include/x86_64-linux-gnu/bits/socket_type.h"
	.file	4 "protocol.c"
	.file	5 "util.c"
	.text
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
.Lfunc_begin0:
	.loc	1 50 0                  # main.c:50:0
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp3:
	.cfi_def_cfa_offset 16
.Ltmp4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp5:
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%rbx
	subq	$376, %rsp              # imm = 0x178
.Ltmp6:
	.cfi_offset %rbx, -40
.Ltmp7:
	.cfi_offset %r14, -32
.Ltmp8:
	.cfi_offset %r15, -24
	movl	$0, -28(%rbp)
	.loc	1 51 0 prologue_end     # main.c:51:0
.Ltmp9:
	movl	$0, -32(%rbp)
	movl	$0, -44(%rbp)
	movl	$defaulthost+255, %edi
	.loc	1 63 0                  # main.c:63:0
	movl	$.L.str, %esi
	callq	strcpy
	movl	$defaulthost+510, %edi
	.loc	1 64 0                  # main.c:64:0
	movl	$.L.str1, %esi
	callq	strcpy
	movl	$defaulthost+765, %edi
	.loc	1 65 0                  # main.c:65:0
	movl	$.L.str2, %esi
	callq	strcpy
	movl	$defaulthost+1020, %edi
	.loc	1 66 0                  # main.c:66:0
	movl	$.L.str3, %esi
	callq	strcpy
	xorl	%eax, %eax
	.loc	1 72 0                  # main.c:72:0
	callq	count_vhosts
	cltq
	movq	%rax, no_vhosts(%rip)
	.loc	1 73 0                  # main.c:73:0
	imulq	$1275, %rax, %rdi       # imm = 0x4FB
	addq	$1275, %rdi             # imm = 0x4FB
	callq	malloc
	movq	%rax, vhosts(%rip)
	xorl	%eax, %eax
	.loc	1 79 0                  # main.c:79:0
	callq	readinconfig
	.loc	1 81 0                  # main.c:81:0
.Ltmp10:
	movl	$SERVERTYPE, %edi
	movl	$.L.str4, %esi
	callq	strcmp
	testl	%eax, %eax
	je	.LBB0_22
.Ltmp11:
# BB#1:                                 # %if.end
	.loc	1 88 0                  # main.c:88:0
	movl	$.L.str5, %edi
	xorl	%esi, %esi
	movl	$24, %edx
	callq	openlog
	movl	$2, %edi
	movl	$1, %esi
	xorl	%edx, %edx
	.loc	1 90 0                  # main.c:90:0
.Ltmp12:
	callq	socket
	movl	%eax, -36(%rbp)
	cmpl	$-1, %eax
	je	.LBB0_2
.Ltmp13:
# BB#4:                                 # %if.end11
	.loc	1 100 0                 # main.c:100:0
	movl	$1, -88(%rbp)
	.loc	1 101 0                 # main.c:101:0
	movl	-36(%rbp), %edi
	leaq	-88(%rbp), %rcx
	movl	$1, %esi
	movl	$2, %edx
	movl	$1, %r8d
	callq	setsockopt
	.loc	1 104 0                 # main.c:104:0
	movw	$2, -64(%rbp)
	.loc	1 105 0                 # main.c:105:0
	movzwl	SERVERPORT(%rip), %edi
	callq	htons
	movw	%ax, -62(%rbp)
	.loc	1 106 0                 # main.c:106:0
	movl	$0, -60(%rbp)
	.loc	1 107 0                 # main.c:107:0
	leaq	-56(%rbp), %rdi
	movl	$8, %esi
	callq	bzero
	.loc	1 109 0                 # main.c:109:0
.Ltmp14:
	movl	-36(%rbp), %edi
	leaq	-64(%rbp), %rsi
	movq	%rsi, -376(%rbp)
	movl	$16, %edx
	callq	bind
	cmpl	$-1, %eax
	je	.LBB0_5
.Ltmp15:
# BB#6:                                 # %if.end19
	.loc	1 117 0                 # main.c:117:0
	movl	-36(%rbp), %edi
	movl	$150, %esi
	callq	listen
	cmpl	$-1, %eax
	je	.LBB0_7
.Ltmp16:
# BB#8:                                 # %if.end24
	movl	$15, %edi
	.loc	1 125 0                 # main.c:125:0
	movl	$signal_handler, %esi
	callq	signal
	movl	$1, %edi
	movl	$signal_handler, %esi
	.loc	1 126 0                 # main.c:126:0
	callq	signal
	movl	$2, %edi
	.loc	1 125 0                 # main.c:125:0
	movl	$signal_handler, %esi
	.loc	1 127 0                 # main.c:127:0
	callq	signal
	movl	$17, %edi
	.loc	1 125 0                 # main.c:125:0
	movl	$signal_handler, %esi
	.loc	1 128 0                 # main.c:128:0
	callq	signal
	.loc	1 130 0                 # main.c:130:0
	callq	fork
	movl	%eax, -32(%rbp)
	cmpl	$-1, %eax
	je	.LBB0_9
# BB#10:                                # %if.end34
	.loc	1 138 0                 # main.c:138:0
.Ltmp17:
	cmpl	$0, -32(%rbp)
	jne	.LBB0_23
.Ltmp18:
# BB#11:                                # %if.end38
	.loc	1 141 0                 # main.c:141:0
	callq	getpid
	movl	%eax, %ecx
	movl	$.L.str14, %edi
	xorl	%eax, %eax
	movl	%ecx, %esi
	callq	printf
	.loc	1 143 0                 # main.c:143:0
	callq	closelog
	.loc	1 146 0                 # main.c:146:0
.Ltmp19:
	movl	$.L.str15, %edi
	callq	getpwnam
	movq	%rax, -368(%rbp)
	testq	%rax, %rax
	je	.LBB0_13
# BB#12:                                # %if.then44
	.loc	1 147 0                 # main.c:147:0
.Ltmp20:
	movq	-368(%rbp), %rax
	movl	20(%rax), %edi
	callq	setgid
	.loc	1 148 0                 # main.c:148:0
	movq	-368(%rbp), %rax
	movl	16(%rax), %edi
	callq	setuid
	jmp	.LBB0_13
.Ltmp21:
	.align	16, 0x90
.LBB0_20:                               # %if.end117
                                        #   in Loop: Header=BB0_13 Depth=1
	.loc	1 185 0                 # main.c:185:0
	movl	-40(%rbp), %edi
	callq	close
	.align	16, 0x90
.LBB0_21:                               # %while.cond119
                                        #   Parent Loop BB0_13 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	$-1, %edi
	xorl	%esi, %esi
	movl	$1, %edx
	.loc	1 187 0                 # main.c:187:0
	callq	waitpid
	testl	%eax, %eax
	jg	.LBB0_21
.LBB0_13:                               # %while.body
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_21 Depth 2
	.loc	1 152 0                 # main.c:152:0
	movl	$16, -84(%rbp)
	.loc	1 154 0                 # main.c:154:0
.Ltmp22:
	movl	-36(%rbp), %edi
	leaq	-80(%rbp), %rsi
	movq	%rsi, -384(%rbp)
	leaq	-84(%rbp), %rdx
	callq	accept
	movl	%eax, -40(%rbp)
	cmpl	$-1, %eax
	je	.LBB0_13
.Ltmp23:
# BB#14:                                # %if.end55
                                        #   in Loop: Header=BB0_13 Depth=1
	.loc	1 157 0                 # main.c:157:0
	callq	fork
	testl	%eax, %eax
	jne	.LBB0_20
# BB#15:
	leaq	-232(%rbp), %r14
	leaq	-360(%rbp), %rbx
	leaq	-104(%rbp), %r15
	.align	16, 0x90
.LBB0_16:                               # %do.end72
                                        # =>This Inner Loop Header: Depth=1
	.loc	1 160 0                 # main.c:160:0
.Ltmp24:
	movl	-36(%rbp), %edi
	callq	close
.Ltmp25:
	#DEBUG_VALUE: __d1 <- [RBP+-392]
	#DEBUG_VALUE: __d0 <- [RBP+-388]
	xorl	%eax, %eax
	movl	$16, %ecx
	.loc	1 161 0                 # main.c:161:0
.Ltmp26:
	movq	%r14, %rdi
	#APP
	cld; rep; stosq
	#NO_APP
	movl	%ecx, -388(%rbp)
	movl	%edi, -392(%rbp)
.Ltmp27:
	.loc	1 162 0                 # main.c:162:0
	movl	-40(%rbp), %ecx
	movl	%ecx, %eax
	sarl	$31, %eax
	shrl	$26, %eax
	addl	%ecx, %eax
	movl	%eax, %edx
	andl	$192, %edx
	subl	%edx, %ecx
	movl	$1, %edx
                                        # kill: CL<def> CL<kill> ECX<kill>
	shlq	%cl, %rdx
	sarl	$6, %eax
	cltq
	orq	%rdx, -232(%rbp,%rax,8)
.Ltmp28:
	#DEBUG_VALUE: __d1 <- [RBP+-400]
	#DEBUG_VALUE: __d0 <- [RBP+-396]
	xorl	%eax, %eax
	movl	$16, %ecx
	.loc	1 163 0                 # main.c:163:0
.Ltmp29:
	movq	%rbx, %rdi
	#APP
	cld; rep; stosq
	#NO_APP
	movl	%ecx, -396(%rbp)
	movl	%edi, -400(%rbp)
.Ltmp30:
	.loc	1 164 0                 # main.c:164:0
	movl	-40(%rbp), %ecx
	movl	%ecx, %eax
	sarl	$31, %eax
	shrl	$26, %eax
	addl	%ecx, %eax
	movl	%eax, %edx
	andl	$192, %edx
	subl	%edx, %ecx
	movl	$1, %edx
                                        # kill: CL<def> CL<kill> ECX<kill>
	shlq	%cl, %rdx
	sarl	$6, %eax
	cltq
	orq	%rdx, -360(%rbp,%rax,8)
	.loc	1 165 0                 # main.c:165:0
	movq	$5, -104(%rbp)
	.loc	1 166 0                 # main.c:166:0
	movq	$0, -96(%rbp)
	.loc	1 167 0                 # main.c:167:0
	movl	-40(%rbp), %edi
	incl	%edi
	xorl	%edx, %edx
	movq	%r14, %rsi
	movq	%rbx, %rcx
	movq	%r15, %r8
	callq	select
	.loc	1 169 0                 # main.c:169:0
.Ltmp31:
	movl	-40(%rbp), %eax
	movl	%eax, %ecx
	sarl	$31, %ecx
	shrl	$26, %ecx
	addl	%eax, %ecx
	sarl	$6, %ecx
	movslq	%ecx, %rcx
	movq	-360(%rbp,%rcx,8), %rcx
	btq	%rax, %rcx
	jb	.LBB0_19
.Ltmp32:
# BB#17:                                # %if.end93
                                        #   in Loop: Header=BB0_16 Depth=1
	.loc	1 172 0                 # main.c:172:0
	movl	-40(%rbp), %eax
	movl	%eax, %ecx
	sarl	$31, %ecx
	shrl	$26, %ecx
	addl	%eax, %ecx
	sarl	$6, %ecx
	movslq	%ecx, %rcx
	movq	-232(%rbp,%rcx,8), %rcx
	btq	%rax, %rcx
	jae	.LBB0_19
# BB#18:                                # %if.then104
                                        #   in Loop: Header=BB0_16 Depth=1
	.loc	1 174 0                 # main.c:174:0
.Ltmp33:
	movl	-76(%rbp), %edi
	xorl	%eax, %eax
	callq	inet_ntoa
	movslq	%eax, %rsi
	movl	$.L.str16, %edi
	movl	$1, %edx
	callq	setenv
	.loc	1 175 0                 # main.c:175:0
.Ltmp34:
	movl	-40(%rbp), %edi
	callq	serveconnection
	cmpl	$-1, %eax
	jne	.LBB0_16
.Ltmp35:
.LBB0_19:                               # %while.end
	.loc	1 182 0                 # main.c:182:0
	movl	-40(%rbp), %edi
	callq	close
	xorl	%edi, %edi
	.loc	1 183 0                 # main.c:183:0
	callq	exit
.Ltmp36:
.LBB0_22:                               # %if.then
	.loc	1 82 0                  # main.c:82:0
	callq	inetd_server
	addq	$376, %rsp              # imm = 0x178
	popq	%rbx
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
.Ltmp37:
.LBB0_2:                                # %if.then10
	.loc	1 91 0                  # main.c:91:0
	movl	$.L.str6, %edi
	callq	perror
	movl	$2, %edi
	.loc	1 92 0                  # main.c:92:0
	movl	$.L.str7, %esi
	jmp	.LBB0_3
.Ltmp38:
.LBB0_5:                                # %if.then18
	.loc	1 111 0                 # main.c:111:0
	movl	$.L.str8, %edi
	callq	perror
	movl	$2, %edi
	.loc	1 112 0                 # main.c:112:0
	movl	$.L.str9, %esi
	jmp	.LBB0_3
.Ltmp39:
.LBB0_7:                                # %if.then23
	.loc	1 118 0                 # main.c:118:0
	movl	$.L.str10, %edi
	callq	perror
	movl	$2, %edi
	.loc	1 119 0                 # main.c:119:0
	movl	$.L.str11, %esi
	jmp	.LBB0_3
.Ltmp40:
.LBB0_9:                                # %if.then32
	.loc	1 133 0                 # main.c:133:0
	movl	$.L.str12, %edi
	xorl	%eax, %eax
	callq	printf
	movl	$2, %edi
	.loc	1 134 0                 # main.c:134:0
	movl	$.L.str13, %esi
.Ltmp41:
.LBB0_3:                                # %if.then10
	xorl	%eax, %eax
	.loc	1 92 0                  # main.c:92:0
.Ltmp42:
	callq	syslog
	.loc	1 93 0                  # main.c:93:0
	callq	closelog
	movl	$1, %edi
	.loc	1 94 0                  # main.c:94:0
	callq	exit
.Ltmp43:
.LBB0_23:                               # %if.then37
	xorl	%edi, %edi
	.loc	1 139 0                 # main.c:139:0
.Ltmp44:
	callq	exit
.Ltmp45:
.Ltmp46:
	.size	main, .Ltmp46-main
.Lfunc_end0:
	.file	6 "/usr/include/netinet/in.h"
	.file	7 "/usr/include/x86_64-linux-gnu/bits/time.h"
	.file	8 "/usr/include/x86_64-linux-gnu/sys/select.h"
	.file	9 "/usr/include/pwd.h"
	.cfi_endproc

	.globl	signal_handler
	.align	16, 0x90
	.type	signal_handler,@function
signal_handler:                         # @signal_handler
	.cfi_startproc
.Lfunc_begin1:
	.loc	1 223 0                 # main.c:223:0
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp49:
	.cfi_def_cfa_offset 16
.Ltmp50:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp51:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	cmpl	$17, %edi
	jne	.LBB1_2
	.align	16, 0x90
.LBB1_1:                                # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	$-1, %edi
	xorl	%esi, %esi
	movl	$1, %edx
	.loc	1 226 0 prologue_end    # main.c:226:0
.Ltmp52:
	callq	waitpid
	testl	%eax, %eax
	jg	.LBB1_1
	jmp	.LBB1_4
.Ltmp53:
.LBB1_2:                                # %if.else
	.loc	1 228 0                 # main.c:228:0
	cmpl	$1, -4(%rbp)
	jne	.LBB1_5
# BB#3:                                 # %if.then3
	xorl	%eax, %eax
	.loc	1 229 0                 # main.c:229:0
	callq	readinconfig
.Ltmp54:
.LBB1_4:                                # %if.end10
	.loc	1 235 0                 # main.c:235:0
	addq	$16, %rsp
	popq	%rbp
	ret
	.align	16, 0x90
.LBB1_5:                                # %while.cond5
                                        # =>This Inner Loop Header: Depth=1
	movl	$-1, %edi
	xorl	%esi, %esi
	movl	$1, %edx
	.loc	1 232 0                 # main.c:232:0
.Ltmp55:
	callq	waitpid
	testl	%eax, %eax
	jg	.LBB1_5
# BB#6:                                 # %while.end9
	xorl	%edi, %edi
	.loc	1 233 0                 # main.c:233:0
	callq	exit
.Ltmp56:
.Ltmp57:
	.size	signal_handler, .Ltmp57-signal_handler
.Lfunc_end1:
	.cfi_endproc

	.globl	inetd_server
	.align	16, 0x90
	.type	inetd_server,@function
inetd_server:                           # @inetd_server
	.cfi_startproc
.Lfunc_begin2:
	.loc	1 198 0                 # main.c:198:0
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp60:
	.cfi_def_cfa_offset 16
.Ltmp61:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp62:
	.cfi_def_cfa_register %rbp
	.loc	1 200 0 prologue_end    # main.c:200:0
.Ltmp63:
	subq	$48, %rsp
	movq	$16, -24(%rbp)
	leaq	-16(%rbp), %rsi
	.loc	1 204 0                 # main.c:204:0
.Ltmp64:
	movq	%rsi, -40(%rbp)
	leaq	-24(%rbp), %rdx
	xorl	%edi, %edi
	callq	getpeername
	testl	%eax, %eax
	js	.LBB2_4
.Ltmp65:
# BB#1:                                 # %if.end
	.loc	1 209 0                 # main.c:209:0
	movl	$.L.str15, %edi
	callq	getpwnam
	movq	%rax, -32(%rbp)
	testq	%rax, %rax
	je	.LBB2_3
# BB#2:                                 # %if.then3
	.loc	1 210 0                 # main.c:210:0
.Ltmp66:
	movq	-32(%rbp), %rax
	movl	20(%rax), %edi
	callq	setgid
	.loc	1 211 0                 # main.c:211:0
	movq	-32(%rbp), %rax
	movl	16(%rax), %edi
	callq	setuid
.Ltmp67:
.LBB2_3:                                # %if.end6
	.loc	1 214 0                 # main.c:214:0
	movl	-12(%rbp), %edi
	xorl	%eax, %eax
	callq	inet_ntoa
	movl	%eax, %ecx
	movl	$.L.str17, %edi
	xorl	%eax, %eax
	movl	%ecx, %esi
	callq	Log
	.loc	1 215 0                 # main.c:215:0
	movl	-12(%rbp), %edi
	xorl	%eax, %eax
	callq	inet_ntoa
	movslq	%eax, %rsi
	movl	$.L.str16, %edi
	movl	$1, %edx
	callq	setenv
	xorl	%edi, %edi
	.loc	1 217 0                 # main.c:217:0
	callq	serveconnection
	xorl	%eax, %eax
	.loc	1 219 0                 # main.c:219:0
	addq	$48, %rsp
	popq	%rbp
	ret
.LBB2_4:                                # %if.then
	movl	$1, %edi
	.loc	1 205 0                 # main.c:205:0
.Ltmp68:
	callq	exit
.Ltmp69:
.Ltmp70:
	.size	inetd_server, .Ltmp70-inetd_server
.Lfunc_end2:
	.cfi_endproc

	.globl	serveconnection
	.align	16, 0x90
	.type	serveconnection,@function
serveconnection:                        # @serveconnection
	.cfi_startproc
.Lfunc_begin3:
	.loc	4 38 0                  # protocol.c:38:0
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp74:
	.cfi_def_cfa_offset 16
.Ltmp75:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp76:
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%rbx
	subq	$16824, %rsp            # imm = 0x41B8
.Ltmp77:
	.cfi_offset %rbx, -40
.Ltmp78:
	.cfi_offset %r14, -32
.Ltmp79:
	.cfi_offset %r15, -24
	movl	%edi, -32(%rbp)
	.loc	4 43 0 prologue_end     # protocol.c:43:0
.Ltmp80:
	movl	$0, -16788(%rbp)
	movl	$0, -16792(%rbp)
	.loc	4 44 0                  # protocol.c:44:0
	movl	$0, -16796(%rbp)
	.loc	4 47 0                  # protocol.c:47:0
	movl	$16, -16820(%rbp)
	.loc	4 49 0                  # protocol.c:49:0
	movq	$0, -16840(%rbp)
	.loc	4 51 0                  # protocol.c:51:0
	movq	$defaulthost, -16832(%rbp)
	leaq	-8240(%rbp), %rbx
	.align	16, 0x90
.LBB3_1:                                # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	.loc	4 55 0                  # protocol.c:55:0
	movl	$.L.str18, %esi
	movq	%rbx, %rdi
	callq	strstr
	testq	%rax, %rax
	je	.LBB3_3
# BB#2:                                 #   in Loop: Header=BB3_1 Depth=1
	xorl	%eax, %eax
	jmp	.LBB3_4
	.align	16, 0x90
.LBB3_3:                                # %land.rhs
                                        #   in Loop: Header=BB3_1 Depth=1
	movl	$.L.str119, %esi
	movq	%rbx, %rdi
	callq	strstr
	testq	%rax, %rax
	sete	%al
.LBB3_4:                                # %land.end
                                        #   in Loop: Header=BB3_1 Depth=1
	testb	%al, %al
	je	.LBB3_7
# BB#5:                                 # %while.body
                                        #   in Loop: Header=BB3_1 Depth=1
	.loc	4 57 0                  # protocol.c:57:0
.Ltmp81:
	movl	-32(%rbp), %edi
	movslq	-16796(%rbp), %rax
	leaq	-8240(%rbp,%rax), %rsi
	movl	$4096, %ecx             # imm = 0x1000
	subl	%eax, %ecx
	movslq	%ecx, %rdx
	xorl	%ecx, %ecx
	callq	recv
	movl	%eax, -16796(%rbp)
	cmpl	$-1, %eax
	jne	.LBB3_1
# BB#6:                                 # %if.then
	.loc	4 58 0                  # protocol.c:58:0
	movl	$-1, -28(%rbp)
	jmp	.LBB3_66
.Ltmp82:
.LBB3_7:                                # %while.end
	.loc	4 60 0                  # protocol.c:60:0
	movl	$0, -16788(%rbp)
	jmp	.LBB3_8
	.align	16, 0x90
.LBB3_11:                               # %for.inc
                                        #   in Loop: Header=BB3_8 Depth=1
	.loc	4 61 0                  # protocol.c:61:0
	movl	-16788(%rbp), %eax
	movb	-8240(%rbp,%rax), %cl
	movb	%cl, -16464(%rbp,%rax)
	.loc	4 60 0                  # protocol.c:60:0
	incl	-16788(%rbp)
.LBB3_8:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$4095, -16788(%rbp)     # imm = 0xFFF
	ja	.LBB3_12
# BB#9:                                 # %land.lhs.true
                                        #   in Loop: Header=BB3_8 Depth=1
	movl	-16788(%rbp), %eax
	movsbl	-8240(%rbp,%rax), %eax
	cmpl	$10, %eax
	je	.LBB3_12
# BB#10:                                # %land.lhs.true13
                                        #   in Loop: Header=BB3_8 Depth=1
	movl	-16788(%rbp), %eax
	movsbl	-8240(%rbp,%rax), %eax
	cmpl	$13, %eax
	jne	.LBB3_11
.Ltmp83:
.LBB3_12:                               # %for.end
	.loc	4 63 0                  # protocol.c:63:0
	movl	-16788(%rbp), %eax
	movb	$0, -16464(%rbp,%rax)
	leaq	-16464(%rbp), %rdi
	.loc	4 64 0                  # protocol.c:64:0
	movl	$.L.str220, %esi
	callq	strtok
	movq	%rax, -8248(%rbp)
	testq	%rax, %rax
	je	.LBB3_13
# BB#14:                                # %if.end30
	.loc	4 67 0                  # protocol.c:67:0
.Ltmp84:
	movq	-8248(%rbp), %rdi
	movl	$.L.str321, %esi
	callq	strcmp
	testl	%eax, %eax
	je	.LBB3_16
# BB#15:                                # %if.then33
	.loc	4 69 0                  # protocol.c:69:0
.Ltmp85:
	movl	-16812(%rbp), %edi
	xorl	%eax, %eax
	callq	inet_ntoa
	movl	%eax, %ecx
	movq	-8248(%rbp), %rdx
	movl	$.L.str422, %edi
	xorl	%eax, %eax
	movl	%ecx, %esi
	callq	Log
	jmp	.LBB3_18
.Ltmp86:
.LBB3_13:                               # %if.then29
	.loc	4 66 0                  # protocol.c:66:0
	movl	$-1, -28(%rbp)
	jmp	.LBB3_66
.Ltmp87:
.LBB3_16:                               # %if.end39
	xorl	%edi, %edi
	.loc	4 74 0                  # protocol.c:74:0
	movl	$.L.str220, %esi
	callq	strtok
	movq	%rax, -8248(%rbp)
	testq	%rax, %rax
	je	.LBB3_17
# BB#19:                                # %if.end51
	leaq	-8240(%rbp), %rdi
	.loc	4 83 0                  # protocol.c:83:0
	movl	$.L.str725, %esi
	callq	strstr
	movq	%rax, -8264(%rbp)
	testq	%rax, %rax
	.loc	4 84 0                  # protocol.c:84:0
.Ltmp88:
	je	.LBB3_25
# BB#20:                                # %if.then55
	.loc	4 86 0                  # protocol.c:86:0
.Ltmp89:
	movq	-8264(%rbp), %rdi
	addq	$6, %rdi
	movl	$.L.str826, %esi
	callq	strtok
	movq	%rax, -8272(%rbp)
	.loc	4 88 0                  # protocol.c:88:0
.Ltmp90:
	movl	$0, -16788(%rbp)
	jmp	.LBB3_21
	.align	16, 0x90
.LBB3_24:                               # %for.inc72
                                        #   in Loop: Header=BB3_21 Depth=1
	incl	-16788(%rbp)
.LBB3_21:                               # %for.cond58
                                        # =>This Inner Loop Header: Depth=1
	movl	-16788(%rbp), %eax
	cmpq	no_vhosts(%rip), %rax
	jae	.LBB3_26
# BB#22:                                # %for.body62
                                        #   in Loop: Header=BB3_21 Depth=1
	.loc	4 89 0                  # protocol.c:89:0
.Ltmp91:
	movl	-16788(%rbp), %eax
	imulq	$1275, %rax, %rdi       # imm = 0x4FB
	addq	vhosts(%rip), %rdi
	movq	-8272(%rbp), %rsi
	xorl	%eax, %eax
	callq	gstricmp
	testl	%eax, %eax
	jne	.LBB3_24
# BB#23:                                # %if.then68
                                        #   in Loop: Header=BB3_21 Depth=1
	.loc	4 90 0                  # protocol.c:90:0
	movl	-16788(%rbp), %eax
	imulq	$1275, %rax, %rax       # imm = 0x4FB
	addq	vhosts(%rip), %rax
	movq	%rax, -16832(%rbp)
	jmp	.LBB3_24
.Ltmp92:
.LBB3_17:                               # %if.then43
	.loc	4 77 0                  # protocol.c:77:0
	movl	-16812(%rbp), %edi
	xorl	%eax, %eax
	callq	inet_ntoa
	movl	%eax, %ecx
	movl	$.L.str624, %edi
	xorl	%eax, %eax
	movl	%ecx, %esi
	callq	Log
.LBB3_18:                               # %sendpage
	leaq	-16784(%rbp), %rbx
	.loc	4 78 0                  # protocol.c:78:0
	movl	$SERVERROOT, %esi
	movq	%rbx, %rdi
	callq	strcpy
	.loc	4 79 0                  # protocol.c:79:0
	movl	$.L.str523, %esi
.Ltmp93:
.LBB3_29:                               # %sendpage
	.loc	4 179 0                 # protocol.c:179:0
	movq	%rbx, %rdi
	callq	strcat
.Ltmp94:
.LBB3_30:                               # %sendpage
	leaq	-16784(%rbp), %rdi
	.loc	4 184 0                 # protocol.c:184:0
.Ltmp95:
	movl	$.L.str21, %esi
	callq	fopen
	movq	%rax, -40(%rbp)
	testq	%rax, %rax
	je	.LBB3_31
.Ltmp96:
# BB#57:                                # %if.end246
	.loc	4 187 0                 # protocol.c:187:0
	movq	-40(%rbp), %rdi
	xorl	%esi, %esi
	movl	$2, %edx
	callq	fseek
	.loc	4 189 0                 # protocol.c:189:0
.Ltmp97:
	movl	-32(%rbp), %edi
	movl	$.L.str1533, %esi
	movl	$16, %edx
	xorl	%ecx, %ecx
	callq	send
	cmpq	$-1, %rax
	je	.LBB3_41
.Ltmp98:
# BB#58:                                # %if.end253
	.loc	4 194 0                 # protocol.c:194:0
	movl	-32(%rbp), %edi
	movl	$.L.str1634, %esi
	movl	$34, %edx
	xorl	%ecx, %ecx
	callq	send
	cmpq	$-1, %rax
	je	.LBB3_41
.Ltmp99:
# BB#59:                                # %if.end259
	.loc	4 199 0                 # protocol.c:199:0
	movq	-40(%rbp), %rdi
	callq	ftell
	movq	%rax, %rcx
	leaq	-16464(%rbp), %r14
	movl	$.L.str22, %esi
	xorl	%eax, %eax
	movq	%r14, %rdi
	movq	%rcx, %rdx
	callq	sprintf
	.loc	4 200 0                 # protocol.c:200:0
.Ltmp100:
	movl	-32(%rbp), %ebx
	movq	%r14, %rdi
	callq	strlen
	xorl	%ecx, %ecx
	movl	%ebx, %edi
	movq	%r14, %rsi
	movq	%rax, %rdx
	callq	send
	cmpq	$-1, %rax
	je	.LBB3_41
.Ltmp101:
# BB#60:                                # %if.end271
	leaq	-16784(%rbp), %rdi
	leaq	-16528(%rbp), %r14
	.loc	4 206 0                 # protocol.c:206:0
	movq	%r14, %rsi
	callq	getmimetype
	leaq	-16464(%rbp), %r15
	.loc	4 207 0                 # protocol.c:207:0
	movl	$.L.str23, %esi
	xorl	%eax, %eax
	movq	%r15, %rdi
	movq	%r14, %rdx
	callq	sprintf
	.loc	4 208 0                 # protocol.c:208:0
.Ltmp102:
	movl	-32(%rbp), %ebx
	movq	%r15, %rdi
	callq	strlen
	xorl	%ecx, %ecx
	movl	%ebx, %edi
	movq	%r15, %rsi
	movq	%rax, %rdx
	callq	send
	cmpq	$-1, %rax
	je	.LBB3_41
.Ltmp103:
# BB#61:                                # %if.end285
	.loc	4 214 0                 # protocol.c:214:0
	movq	-40(%rbp), %rdi
	xorl	%esi, %esi
	xorl	%edx, %edx
	callq	fseek
	leaq	-8240(%rbp), %rbx
	.align	16, 0x90
.LBB3_62:                               # %while.cond287
                                        # =>This Inner Loop Header: Depth=1
	.loc	4 216 0                 # protocol.c:216:0
	movq	-40(%rbp), %rdi
	callq	feof
	testl	%eax, %eax
	jne	.LBB3_64
# BB#63:                                # %while.body291
                                        #   in Loop: Header=BB3_62 Depth=1
	.loc	4 218 0                 # protocol.c:218:0
.Ltmp104:
	movq	-40(%rbp), %rcx
	movl	$1, %esi
	movl	$1024, %edx             # imm = 0x400
	movq	%rbx, %rdi
	callq	fread
	movl	%eax, -16796(%rbp)
	.loc	4 219 0                 # protocol.c:219:0
.Ltmp105:
	movl	-32(%rbp), %edi
	movslq	-16796(%rbp), %rdx
	xorl	%ecx, %ecx
	movq	%rbx, %rsi
	callq	send
	cmpq	$-1, %rax
	jne	.LBB3_62
	jmp	.LBB3_41
.Ltmp106:
.LBB3_31:                               # %if.then245
	.loc	4 185 0                 # protocol.c:185:0
	movl	$-1, -28(%rbp)
	jmp	.LBB3_66
.Ltmp107:
.LBB3_25:                               # %if.else
	.loc	4 93 0                  # protocol.c:93:0
	movq	$defaulthost, -16832(%rbp)
.Ltmp108:
.LBB3_26:                               # %if.end75
	.loc	4 94 0                  # protocol.c:94:0
	movq	-8248(%rbp), %rdi
	movl	$.L.str927, %esi
	callq	strstr
	testq	%rax, %rax
	je	.LBB3_32
# BB#27:                                # %if.then78
	.loc	4 96 0                  # protocol.c:96:0
.Ltmp109:
	movl	-16812(%rbp), %edi
	xorl	%eax, %eax
	callq	inet_ntoa
	movl	%eax, %ecx
	movq	-8248(%rbp), %rdx
	movl	$.L.str1028, %edi
	xorl	%eax, %eax
	movl	%ecx, %esi
	callq	Log
.Ltmp110:
.LBB3_28:                               # %if.end234
	leaq	-16784(%rbp), %rbx
	.loc	4 178 0                 # protocol.c:178:0
.Ltmp111:
	movl	$SERVERROOT, %esi
	movq	%rbx, %rdi
	callq	strcpy
	.loc	4 179 0                 # protocol.c:179:0
	movl	$.L.str1129, %esi
	jmp	.LBB3_29
.Ltmp112:
.LBB3_32:                               # %if.end86
	.loc	4 102 0                 # protocol.c:102:0
	movl	-32(%rbp), %edi
	leaq	-16816(%rbp), %rsi
	movq	%rsi, -16848(%rbp)
	leaq	-16820(%rbp), %rdx
	callq	getpeername
	.loc	4 103 0                 # protocol.c:103:0
	movl	-16812(%rbp), %edi
	xorl	%eax, %eax
	callq	inet_ntoa
	movl	%eax, %ecx
	movq	-8248(%rbp), %rdx
	movl	$.L.str1230, %edi
	xorl	%eax, %eax
	movl	%ecx, %esi
	callq	Log
	jmp	.LBB3_33
	.align	16, 0x90
.LBB3_34:                               # %while.body96
                                        #   in Loop: Header=BB3_33 Depth=1
	.loc	4 108 0                 # protocol.c:108:0
.Ltmp113:
	movq	-8248(%rbp), %rdi
.Ltmp114:
	.loc	4 107 0                 # protocol.c:107:0
	movl	$.L.str1331, %esi
	.loc	4 108 0                 # protocol.c:108:0
.Ltmp115:
	callq	strstr
	movq	%rax, -16840(%rbp)
	.loc	4 109 0                 # protocol.c:109:0
	movb	$32, (%rax)
	.loc	4 110 0                 # protocol.c:110:0
	movq	-16840(%rbp), %rsi
	leaq	1(%rsi), %rdi
	addq	$3, %rsi
	callq	strcpy
.Ltmp116:
.LBB3_33:                               # %while.cond92
                                        # =>This Inner Loop Header: Depth=1
	.loc	4 107 0                 # protocol.c:107:0
	movq	-8248(%rbp), %rdi
	movl	$.L.str1331, %esi
	callq	strstr
	testq	%rax, %rax
	jne	.LBB3_34
# BB#35:                                # %while.end101
	.loc	4 114 0                 # protocol.c:114:0
.Ltmp117:
	movq	-8248(%rbp), %r14
	movl	$765, %ebx              # imm = 0x2FD
	addq	-16832(%rbp), %rbx
	movq	%rbx, %rdi
	callq	strlen
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movq	%rax, %rdx
	callq	strncmp
	testl	%eax, %eax
	je	.LBB3_36
.Ltmp118:
# BB#50:                                # %if.end180
	.loc	4 159 0                 # protocol.c:159:0
	movq	-16832(%rbp), %rsi
	addq	$255, %rsi
	leaq	-16784(%rbp), %rbx
	movq	%rbx, %rdi
	callq	strcpy
	.loc	4 160 0                 # protocol.c:160:0
	movq	%rbx, %rdi
	callq	strlen
	movl	%eax, -16800(%rbp)
	.loc	4 161 0                 # protocol.c:161:0
	movq	-8248(%rbp), %rsi
	movslq	-16800(%rbp), %rax
	movl	$255, %edx
	subq	%rax, %rdx
	movq	%rbx, %rdi
	callq	strncat
	.loc	4 163 0                 # protocol.c:163:0
.Ltmp119:
	movq	%rbx, %rdi
	callq	does_file_exist
	testl	%eax, %eax
	jne	.LBB3_30
# BB#51:                                # %if.then195
	.loc	4 165 0                 # protocol.c:165:0
.Ltmp120:
	movq	%rbx, %rdi
	callq	strlen
	movsbl	-1(%rax,%rbx), %eax
	cmpl	$47, %eax
	jne	.LBB3_53
# BB#52:                                # %if.then203
	.loc	4 166 0                 # protocol.c:166:0
	movq	-16832(%rbp), %rsi
	addq	$510, %rsi              # imm = 0x1FE
	leaq	-16784(%rbp), %rdi
	jmp	.LBB3_54
.Ltmp121:
.LBB3_64:                               # %while.end303
	.loc	4 225 0                 # protocol.c:225:0
	movq	-40(%rbp), %rdi
	callq	fclose
	.loc	4 227 0                 # protocol.c:227:0
	movl	-32(%rbp), %edi
	callq	close
.LBB3_65:                               # %return
	.loc	4 228 0                 # protocol.c:228:0
	movl	$0, -28(%rbp)
	jmp	.LBB3_66
.LBB3_36:                               # %if.then108
	.loc	4 116 0                 # protocol.c:116:0
.Ltmp122:
	movq	-8248(%rbp), %rdi
	movl	$.L.str1432, %esi
	callq	strstr
	movq	%rax, -8256(%rbp)
	testq	%rax, %rax
	je	.LBB3_38
# BB#37:                                # %if.then112
	.loc	4 117 0                 # protocol.c:117:0
.Ltmp123:
	movq	-8256(%rbp), %rax
	movb	$0, (%rax)
	movl	$1, -16792(%rbp)
.Ltmp124:
.LBB3_38:                               # %if.end114
	.loc	4 119 0                 # protocol.c:119:0
	movq	-16832(%rbp), %rsi
	addq	$1020, %rsi             # imm = 0x3FC
	leaq	-16784(%rbp), %rbx
	movq	%rbx, %rdi
	callq	strcpy
	.loc	4 120 0                 # protocol.c:120:0
	movq	-16832(%rbp), %rdi
	addq	$765, %rdi              # imm = 0x2FD
	callq	strlen
	addq	%rax, -8248(%rbp)
	.loc	4 121 0                 # protocol.c:121:0
	movq	%rbx, %rdi
	callq	strlen
	movl	%eax, -16800(%rbp)
	.loc	4 122 0                 # protocol.c:122:0
	movq	-8248(%rbp), %rsi
	movslq	-16800(%rbp), %rax
	movl	$255, %edx
	subq	%rax, %rdx
	movq	%rbx, %rdi
	callq	strncat
	.loc	4 127 0                 # protocol.c:127:0
.Ltmp125:
	movq	%rbx, %rdi
	callq	does_file_exist
	cmpl	$1, %eax
	jne	.LBB3_49
# BB#39:                                # %land.lhs.true133
	leaq	-16784(%rbp), %rdi
	callq	isDirectory
	testl	%eax, %eax
	je	.LBB3_40
.Ltmp126:
.LBB3_49:                               # %if.end170
	.loc	4 153 0                 # protocol.c:153:0
	movl	-16812(%rbp), %edi
	xorl	%eax, %eax
	callq	inet_ntoa
	movl	%eax, %edx
	movq	-8256(%rbp), %rcx
	incq	%rcx
	leaq	-16784(%rbp), %rbx
	movl	$.L.str1836, %edi
	xorl	%eax, %eax
	movl	%edx, %esi
	movq	%rbx, %rdx
	callq	Log
	.loc	4 154 0                 # protocol.c:154:0
	movl	$SERVERROOT, %esi
	movq	%rbx, %rdi
	callq	strcpy
	.loc	4 155 0                 # protocol.c:155:0
	movl	$.L.str19, %esi
	jmp	.LBB3_29
.Ltmp127:
.LBB3_53:                               # %if.else207
	leaq	-16784(%rbp), %rbx
	.loc	4 169 0                 # protocol.c:169:0
.Ltmp128:
	movl	$.L.str20, %esi
	movq	%rbx, %rdi
	callq	strcat
	.loc	4 170 0                 # protocol.c:170:0
	movq	-16832(%rbp), %rsi
	addq	$510, %rsi              # imm = 0x1FE
	movq	%rbx, %rdi
.LBB3_54:                               # %if.end214
	callq	strcat
	leaq	-16784(%rbp), %r14
.Ltmp129:
	.loc	4 172 0                 # protocol.c:172:0
	movq	%r14, %rdi
	callq	does_file_exist
	testl	%eax, %eax
	jne	.LBB3_30
# BB#55:                                # %if.then219
	.loc	4 174 0                 # protocol.c:174:0
.Ltmp130:
	movq	%r14, %rdi
	callq	strlen
	movq	%rax, %rbx
	movq	-16832(%rbp), %rdi
	addq	$510, %rdi              # imm = 0x1FE
	callq	strlen
	subq	%rax, %rbx
	movb	$0, -1(%rbx,%r14)
	.loc	4 175 0                 # protocol.c:175:0
.Ltmp131:
	movq	%r14, %rdi
	callq	isDirectory
	cmpl	$1, %eax
	jne	.LBB3_28
# BB#56:                                # %if.then232
	.loc	4 175 0                 # protocol.c:175:0
.Ltmp132:
	movl	-32(%rbp), %esi
	movq	-16832(%rbp), %rdx
	leaq	-16784(%rbp), %rdi
	callq	showdir
	jmp	.LBB3_65
.Ltmp133:
.LBB3_40:                               # %if.then138
	.loc	4 129 0                 # protocol.c:129:0
	movl	-32(%rbp), %edi
	movl	$.L.str1533, %esi
	movl	$16, %edx
	xorl	%ecx, %ecx
	callq	send
	cmpq	$-1, %rax
	je	.LBB3_41
.Ltmp134:
# BB#42:                                # %if.end144
	.loc	4 134 0                 # protocol.c:134:0
	movl	-32(%rbp), %edi
	movl	$.L.str1634, %esi
	movl	$34, %edx
	xorl	%ecx, %ecx
	callq	send
	cmpq	$-1, %rax
	je	.LBB3_41
.Ltmp135:
# BB#43:                                # %if.end150
	.loc	4 141 0                 # protocol.c:141:0
	movl	-32(%rbp), %edi
	xorl	%esi, %esi
	callq	dup2
	testl	%eax, %eax
	jne	.LBB3_45
# BB#44:                                # %lor.lhs.false
	movl	-32(%rbp), %edi
	movl	$1, %esi
	callq	dup2
	cmpl	$1, %eax
	je	.LBB3_46
.LBB3_45:                               # %if.then157
	.loc	4 142 0                 # protocol.c:142:0
	movl	$-1, -28(%rbp)
	jmp	.LBB3_66
.Ltmp136:
.LBB3_41:                               # %if.then142
	.loc	4 131 0                 # protocol.c:131:0
	movq	-40(%rbp), %rdi
	callq	fclose
	.loc	4 132 0                 # protocol.c:132:0
	movl	$-1, -28(%rbp)
.Ltmp137:
.LBB3_66:                               # %return
	.loc	4 229 0                 # protocol.c:229:0
	movl	-28(%rbp), %eax
	addq	$16824, %rsp            # imm = 0x41B8
	popq	%rbx
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
.LBB3_46:                               # %if.end158
	.loc	4 144 0                 # protocol.c:144:0
.Ltmp138:
	movq	stdin(%rip), %rdi
	xorl	%esi, %esi
	callq	setbuf
	.loc	4 145 0                 # protocol.c:145:0
	movq	stdout(%rip), %rdi
	xorl	%esi, %esi
	callq	setbuf
	.loc	4 146 0                 # protocol.c:146:0
.Ltmp139:
	cmpl	$1, -16792(%rbp)
	jne	.LBB3_48
# BB#47:                                # %if.then161
	movq	-8256(%rbp), %rsi
	incq	%rsi
	movl	$.L.str1735, %edi
	movl	$1, %edx
	callq	setenv
.Ltmp140:
.LBB3_48:                               # %if.end164
	.loc	4 148 0                 # protocol.c:148:0
	movq	-16832(%rbp), %rdi
	addq	$1020, %rdi             # imm = 0x3FC
	callq	chdir
	leaq	-16784(%rbp), %rdi
	xorl	%esi, %esi
	xorl	%eax, %eax
	.loc	4 150 0                 # protocol.c:150:0
	callq	execlp
	jmp	.LBB3_65
.Ltmp141:
.Ltmp142:
	.size	serveconnection, .Ltmp142-serveconnection
.Lfunc_end3:
	.file	10 "/usr/include/libio.h"
	.cfi_endproc

	.globl	showdir
	.align	16, 0x90
	.type	showdir,@function
showdir:                                # @showdir
	.cfi_startproc
.Lfunc_begin4:
	.loc	4 259 0                 # protocol.c:259:0
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp146:
	.cfi_def_cfa_offset 16
.Ltmp147:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp148:
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%rbx
	subq	$2360, %rsp             # imm = 0x938
.Ltmp149:
	.cfi_offset %rbx, -40
.Ltmp150:
	.cfi_offset %r14, -32
.Ltmp151:
	.cfi_offset %r15, -24
	movq	%rdi, -32(%rbp)
	movl	%esi, -36(%rbp)
	movq	%rdx, -48(%rbp)
	.loc	4 262 0 prologue_end    # protocol.c:262:0
.Ltmp152:
	movq	$0, -72(%rbp)
	leaq	-2384(%rbp), %r14
	xorl	%esi, %esi
	movl	$2048, %edx             # imm = 0x800
	.loc	4 268 0                 # protocol.c:268:0
	movq	%r14, %rdi
	callq	memset
	.loc	4 270 0                 # protocol.c:270:0
	movq	-32(%rbp), %rbx
	movl	$255, %edi
	addq	-48(%rbp), %rdi
	callq	strlen
	addq	%rax, %rbx
	movl	$.L.str26, %esi
	xorl	%eax, %eax
	movq	%r14, %rdi
	movq	%rbx, %rdx
	callq	sprintf
	.loc	4 272 0                 # protocol.c:272:0
.Ltmp153:
	movl	-36(%rbp), %edi
	movl	$2048, %edx             # imm = 0x800
	xorl	%ecx, %ecx
	movq	%r14, %rsi
	callq	send
	cmpq	$-1, %rax
	je	.LBB4_4
.Ltmp154:
# BB#1:                                 # %if.end
	.loc	4 275 0                 # protocol.c:275:0
	movq	-32(%rbp), %rdi
	leaq	-56(%rbp), %rsi
	xorl	%edx, %edx
	movl	$alphasort, %ecx
	callq	scandir
	movl	%eax, -60(%rbp)
	.loc	4 277 0                 # protocol.c:277:0
	movq	-48(%rbp), %rdi
	addq	$255, %rdi
	callq	strlen
	addq	%rax, -32(%rbp)
	.loc	4 279 0                 # protocol.c:279:0
.Ltmp155:
	cmpl	$0, -60(%rbp)
	js	.LBB4_2
# BB#5:                                 # %if.else
	.loc	4 282 0                 # protocol.c:282:0
.Ltmp156:
	movl	$0, -64(%rbp)
	movl	$255, %r15d
	leaq	-336(%rbp), %r14
	jmp	.LBB4_6
	.align	16, 0x90
.LBB4_10:                               # %for.inc
                                        #   in Loop: Header=BB4_6 Depth=1
	incl	-64(%rbp)
.LBB4_6:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	-64(%rbp), %eax
	cmpl	-60(%rbp), %eax
	jge	.LBB4_3
# BB#7:                                 # %for.body
                                        #   in Loop: Header=BB4_6 Depth=1
	movq	-48(%rbp), %rdx
	.loc	4 284 0                 # protocol.c:284:0
.Ltmp157:
	addq	%r15, %rdx
	movq	-32(%rbp), %rcx
	movslq	-64(%rbp), %rax
	movq	-56(%rbp), %rsi
	movq	(%rsi,%rax,8), %r8
	addq	$19, %r8
	movl	$.L.str28, %esi
	xorl	%eax, %eax
	movq	%r14, %rdi
	callq	sprintf
	.loc	4 285 0                 # protocol.c:285:0
	movq	%r14, %rdi
	callq	get_file_size
	movq	%rax, -72(%rbp)
	.loc	4 286 0                 # protocol.c:286:0
.Ltmp158:
	movq	%r14, %rdi
	callq	isDirectory
	testl	%eax, %eax
	je	.LBB4_9
# BB#8:                                 # %if.then22
                                        #   in Loop: Header=BB4_6 Depth=1
	movq	$0, -72(%rbp)
.Ltmp159:
.LBB4_9:                                # %if.end23
                                        #   in Loop: Header=BB4_6 Depth=1
	.loc	4 287 0                 # protocol.c:287:0
	movq	-32(%rbp), %rdx
	movslq	-64(%rbp), %rax
	movq	-56(%rbp), %rcx
	movq	(%rcx,%rax,8), %rcx
	addq	$19, %rcx
	movq	-72(%rbp), %r9
	movl	$.L.str29, %esi
	xorl	%eax, %eax
	movq	%r14, %rdi
	movq	%rcx, %r8
	callq	sprintf
	.loc	4 288 0                 # protocol.c:288:0
.Ltmp160:
	movl	-36(%rbp), %ebx
	movq	%r14, %rdi
	callq	strlen
	xorl	%ecx, %ecx
	movl	%ebx, %edi
	movq	%r14, %rsi
	movq	%rax, %rdx
	callq	send
	cmpq	$-1, %rax
	jne	.LBB4_10
	jmp	.LBB4_4
.Ltmp161:
.LBB4_2:                                # %if.then11
	.loc	4 280 0                 # protocol.c:280:0
	movl	$.L.str27, %edi
	callq	perror
.Ltmp162:
.LBB4_3:                                # %if.end41
	.loc	4 292 0                 # protocol.c:292:0
	movl	-36(%rbp), %edi
	movl	$showdir.dirfooter, %esi
	movl	$191, %edx
	xorl	%ecx, %ecx
	callq	send
.LBB4_4:                                # %return
	.loc	4 293 0                 # protocol.c:293:0
	addq	$2360, %rsp             # imm = 0x938
	popq	%rbx
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
.Ltmp163:
.Ltmp164:
	.size	showdir, .Ltmp164-showdir
.Lfunc_end4:
	.file	11 "/usr/include/x86_64-linux-gnu/bits/dirent.h"
	.cfi_endproc

	.globl	getmimetype
	.align	16, 0x90
	.type	getmimetype,@function
getmimetype:                            # @getmimetype
	.cfi_startproc
.Lfunc_begin5:
	.loc	4 232 0                 # protocol.c:232:0
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp168:
	.cfi_def_cfa_offset 16
.Ltmp169:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp170:
	.cfi_def_cfa_register %rbp
	pushq	%r14
	pushq	%rbx
	andq	$-32, %rsp
	subq	$192, %rsp
.Ltmp171:
	.cfi_offset %rbx, -32
.Ltmp172:
	.cfi_offset %r14, -24
	movq	%rdi, 184(%rsp)
	movq	%rsi, 176(%rsp)
	.loc	4 235 0 prologue_end    # protocol.c:235:0
.Ltmp173:
	movl	$0, 28(%rsp)
	.loc	4 237 0                 # protocol.c:237:0
	vxorps	%xmm0, %xmm0, %xmm0
	vmovups	%xmm0, 130(%rsp)
	vmovups	%xmm0, 114(%rsp)
	vxorps	%ymm0, %ymm0, %ymm0
	vmovaps	%ymm0, 96(%rsp)
	.loc	4 240 0                 # protocol.c:240:0
.Ltmp174:
	movl	$1, 28(%rsp)
	jmp	.LBB5_1
	.align	16, 0x90
.LBB5_3:                                # %for.inc
                                        #   in Loop: Header=BB5_1 Depth=1
	.loc	4 241 0                 # protocol.c:241:0
	movq	184(%rsp), %rdi
	callq	strlen
	movl	28(%rsp), %ecx
	subq	%rcx, %rax
	movq	184(%rsp), %rdx
	movb	(%rdx,%rax), %al
	leal	-1(%rcx), %ecx
	movb	%al, 96(%rsp,%rcx)
	.loc	4 240 0                 # protocol.c:240:0
	incl	28(%rsp)
.LBB5_1:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movl	28(%rsp), %ebx
	movq	184(%rsp), %rdi
	vzeroupper
	callq	strlen
	cmpq	%rax, %rbx
	jae	.LBB5_4
# BB#2:                                 # %land.lhs.true
                                        #   in Loop: Header=BB5_1 Depth=1
	movq	184(%rsp), %rdi
	callq	strlen
	movl	28(%rsp), %ecx
	subq	%rcx, %rax
	movq	184(%rsp), %rcx
	movsbl	(%rcx,%rax), %eax
	cmpl	$46, %eax
	jne	.LBB5_3
.Ltmp175:
.LBB5_4:                                # %for.end
	.loc	4 244 0                 # protocol.c:244:0
	movl	$0, 28(%rsp)
	leaq	96(%rsp), %r14
	jmp	.LBB5_5
	.align	16, 0x90
.LBB5_6:                                # %for.inc27
                                        #   in Loop: Header=BB5_5 Depth=1
	.loc	4 245 0                 # protocol.c:245:0
	movq	%r14, %rdi
	callq	strlen
	movl	28(%rsp), %ecx
	subq	%rcx, %rax
	movb	-1(%rax,%r14), %al
	movb	%al, 32(%rsp,%rcx)
	.loc	4 244 0                 # protocol.c:244:0
	incl	28(%rsp)
.LBB5_5:                                # %for.cond13
                                        # =>This Inner Loop Header: Depth=1
	movl	28(%rsp), %ebx
	movq	%r14, %rdi
	callq	strlen
	cmpq	%rax, %rbx
	jb	.LBB5_6
.Ltmp176:
# BB#7:                                 # %for.end29
	.loc	4 247 0                 # protocol.c:247:0
	movl	28(%rsp), %eax
	movb	$0, 32(%rsp,%rax)
	.loc	4 252 0                 # protocol.c:252:0
.Ltmp177:
	movl	$0, 28(%rsp)
	leaq	32(%rsp), %rbx
	jmp	.LBB5_8
	.align	16, 0x90
.LBB5_10:                               # %for.inc47
                                        #   in Loop: Header=BB5_8 Depth=1
	incl	28(%rsp)
.LBB5_8:                                # %for.cond32
                                        # =>This Inner Loop Header: Depth=1
	movl	28(%rsp), %eax
	imulq	$200, %rax, %rax
	leaq	assocNames(%rax), %rdi
	movl	$.L.str24, %esi
	callq	strcmp
	testl	%eax, %eax
	je	.LBB5_11
# BB#9:                                 # %land.lhs.true38
                                        #   in Loop: Header=BB5_8 Depth=1
	movl	28(%rsp), %eax
	imulq	$200, %rax, %rax
	leaq	assocNames(%rax), %rdi
	movq	%rbx, %rsi
	callq	strcmp
	testl	%eax, %eax
	jne	.LBB5_10
.Ltmp178:
.LBB5_11:                               # %for.end49
	.loc	4 254 0                 # protocol.c:254:0
	movq	176(%rsp), %rdi
	movl	28(%rsp), %eax
	imulq	$200, %rax, %rax
	leaq	assocNames+100(%rax), %rsi
	callq	strcpy
	.loc	4 255 0                 # protocol.c:255:0
.Ltmp179:
	movq	176(%rsp), %rdi
	movl	$.L.str24, %esi
	callq	strcmp
	testl	%eax, %eax
	jne	.LBB5_13
# BB#12:                                # %if.then
	movq	176(%rsp), %rdi
	movl	$.L.str25, %esi
	callq	strcpy
.Ltmp180:
.LBB5_13:                               # %if.end
	.loc	4 256 0                 # protocol.c:256:0
	leaq	-16(%rbp), %rsp
	popq	%rbx
	popq	%r14
	popq	%rbp
	ret
.Ltmp181:
.Ltmp182:
	.size	getmimetype, .Ltmp182-getmimetype
.Lfunc_end5:
	.cfi_endproc

	.globl	getfileline
	.align	16, 0x90
	.type	getfileline,@function
getfileline:                            # @getfileline
	.cfi_startproc
.Lfunc_begin6:
	.loc	5 41 0                  # util.c:41:0
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp185:
	.cfi_def_cfa_offset 16
.Ltmp186:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp187:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	.loc	5 42 0 prologue_end     # util.c:42:0
.Ltmp188:
	movl	$0, -20(%rbp)
	.loc	5 43 0                  # util.c:43:0
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rdx
	movl	$255, %esi
	callq	fgets
	.loc	5 44 0                  # util.c:44:0
.Ltmp189:
	movl	$0, -20(%rbp)
	jmp	.LBB6_1
	.align	16, 0x90
.LBB6_6:                                # %for.inc
                                        #   in Loop: Header=BB6_1 Depth=1
	incl	-20(%rbp)
.LBB6_1:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$254, -20(%rbp)
	ja	.LBB6_7
# BB#2:                                 # %land.lhs.true
                                        #   in Loop: Header=BB6_1 Depth=1
	movl	-20(%rbp), %eax
	movq	-8(%rbp), %rcx
	movsbl	(%rcx,%rax), %eax
	testl	%eax, %eax
	je	.LBB6_7
# BB#3:                                 # %for.body
                                        #   in Loop: Header=BB6_1 Depth=1
	.loc	5 44 0                  # util.c:44:0
.Ltmp190:
	movl	-20(%rbp), %eax
	movq	-8(%rbp), %rcx
	movsbl	(%rcx,%rax), %eax
	cmpl	$13, %eax
	je	.LBB6_5
# BB#4:                                 # %lor.lhs.false
                                        #   in Loop: Header=BB6_1 Depth=1
	movl	-20(%rbp), %eax
	movq	-8(%rbp), %rcx
	movsbl	(%rcx,%rax), %eax
	cmpl	$10, %eax
	jne	.LBB6_6
.LBB6_5:                                # %if.then
                                        #   in Loop: Header=BB6_1 Depth=1
	movl	-20(%rbp), %eax
	movq	-8(%rbp), %rcx
	movb	$0, (%rcx,%rax)
	jmp	.LBB6_6
.Ltmp191:
.LBB6_7:                                # %for.end
	.loc	5 45 0                  # util.c:45:0
	addq	$32, %rsp
	popq	%rbp
	ret
.Ltmp192:
.Ltmp193:
	.size	getfileline, .Ltmp193-getfileline
.Lfunc_end6:
	.cfi_endproc

	.globl	does_file_exist
	.align	16, 0x90
	.type	does_file_exist,@function
does_file_exist:                        # @does_file_exist
	.cfi_startproc
.Lfunc_begin7:
	.loc	5 48 0                  # util.c:48:0
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp196:
	.cfi_def_cfa_offset 16
.Ltmp197:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp198:
	.cfi_def_cfa_register %rbp
	subq	$160, %rsp
	movq	%rdi, -16(%rbp)
	leaq	-160(%rbp), %rsi
	.loc	5 50 0 prologue_end     # util.c:50:0
.Ltmp199:
	callq	stat
	testl	%eax, %eax
	jne	.LBB7_2
# BB#1:                                 # %lor.lhs.false
	movq	-16(%rbp), %rdi
	callq	isDirectory
	testl	%eax, %eax
	je	.LBB7_3
.LBB7_2:                                # %if.then
	movl	$0, -4(%rbp)
.Ltmp200:
.LBB7_4:                                # %return
	.loc	5 52 0                  # util.c:52:0
	movl	-4(%rbp), %eax
	addq	$160, %rsp
	popq	%rbp
	ret
.LBB7_3:                                # %if.end
	.loc	5 51 0                  # util.c:51:0
	movl	$1, -4(%rbp)
	jmp	.LBB7_4
.Ltmp201:
.Ltmp202:
	.size	does_file_exist, .Ltmp202-does_file_exist
.Lfunc_end7:
	.file	12 "/usr/include/x86_64-linux-gnu/bits/stat.h"
	.file	13 "/usr/include/time.h"
	.cfi_endproc

	.globl	isDirectory
	.align	16, 0x90
	.type	isDirectory,@function
isDirectory:                            # @isDirectory
	.cfi_startproc
.Lfunc_begin8:
	.loc	5 62 0                  # util.c:62:0
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp205:
	.cfi_def_cfa_offset 16
.Ltmp206:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp207:
	.cfi_def_cfa_register %rbp
	subq	$160, %rsp
	movq	%rdi, -16(%rbp)
	leaq	-160(%rbp), %rsi
	.loc	5 65 0 prologue_end     # util.c:65:0
.Ltmp208:
	callq	stat
	testl	%eax, %eax
	je	.LBB8_2
# BB#1:                                 # %if.then
	movl	$0, -4(%rbp)
	jmp	.LBB8_5
.Ltmp209:
.LBB8_2:                                # %if.end
	movl	$61440, %eax            # imm = 0xF000
	.loc	5 66 0                  # util.c:66:0
.Ltmp210:
	andl	-136(%rbp), %eax
	cmpl	$16384, %eax            # imm = 0x4000
	jne	.LBB8_3
.Ltmp211:
# BB#4:                                 # %if.end2
	.loc	5 68 0                  # util.c:68:0
	movl	$1, -4(%rbp)
	jmp	.LBB8_5
.LBB8_3:                                # %if.then1
	.loc	5 66 0                  # util.c:66:0
.Ltmp212:
	movl	$0, -4(%rbp)
.Ltmp213:
.LBB8_5:                                # %return
	.loc	5 69 0                  # util.c:69:0
	movl	-4(%rbp), %eax
	addq	$160, %rsp
	popq	%rbp
	ret
.Ltmp214:
.Ltmp215:
	.size	isDirectory, .Ltmp215-isDirectory
.Lfunc_end8:
	.cfi_endproc

	.globl	get_file_size
	.align	16, 0x90
	.type	get_file_size,@function
get_file_size:                          # @get_file_size
	.cfi_startproc
.Lfunc_begin9:
	.loc	5 55 0                  # util.c:55:0
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp218:
	.cfi_def_cfa_offset 16
.Ltmp219:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp220:
	.cfi_def_cfa_register %rbp
	subq	$160, %rsp
	movq	%rdi, -16(%rbp)
	leaq	-160(%rbp), %rsi
	.loc	5 57 0 prologue_end     # util.c:57:0
.Ltmp221:
	callq	stat
	testl	%eax, %eax
	je	.LBB9_1
.Ltmp222:
# BB#2:                                 # %if.end
	.loc	5 58 0                  # util.c:58:0
	movq	$0, -8(%rbp)
	jmp	.LBB9_3
.LBB9_1:                                # %if.then
	.loc	5 57 0                  # util.c:57:0
.Ltmp223:
	movq	-112(%rbp), %rax
	movq	%rax, -8(%rbp)
.Ltmp224:
.LBB9_3:                                # %return
	.loc	5 59 0                  # util.c:59:0
	movq	-8(%rbp), %rax
	addq	$160, %rsp
	popq	%rbp
	ret
.Ltmp225:
.Ltmp226:
	.size	get_file_size, .Ltmp226-get_file_size
.Lfunc_end9:
	.cfi_endproc

	.globl	count_vhosts
	.align	16, 0x90
	.type	count_vhosts,@function
count_vhosts:                           # @count_vhosts
	.cfi_startproc
.Lfunc_begin10:
	.loc	5 72 0                  # util.c:72:0
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp230:
	.cfi_def_cfa_offset 16
.Ltmp231:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp232:
	.cfi_def_cfa_register %rbp
	.loc	5 74 0 prologue_end     # util.c:74:0
.Ltmp233:
	pushq	%rbx
	andq	$-32, %rsp
	subq	$352, %rsp              # imm = 0x160
.Ltmp234:
	.cfi_offset %rbx, -24
	movq	$0, 304(%rsp)
	.loc	5 75 0                  # util.c:75:0
	movq	$0, 24(%rsp)
	.loc	5 77 0                  # util.c:77:0
.Ltmp235:
	movl	$.L.str39, %edi
	movl	$.L.str140, %esi
	callq	fopen
	movq	%rax, 312(%rsp)
	testq	%rax, %rax
	je	.LBB10_9
.Ltmp236:
# BB#1:
	leaq	32(%rsp), %rbx
	jmp	.LBB10_2
	.align	16, 0x90
.LBB10_6:                               # %if.then11
                                        #   in Loop: Header=BB10_2 Depth=1
	.loc	5 88 0                  # util.c:88:0
.Ltmp237:
	incq	304(%rsp)
.Ltmp238:
.LBB10_2:                               # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	.loc	5 80 0                  # util.c:80:0
	movq	312(%rsp), %rdi
	callq	feof
	testl	%eax, %eax
	jne	.LBB10_7
# BB#3:                                 # %while.body
                                        #   in Loop: Header=BB10_2 Depth=1
	.loc	5 82 0                  # util.c:82:0
.Ltmp239:
	vxorps	%xmm0, %xmm0, %xmm0
	vmovups	%xmm0, 271(%rsp)
	vmovups	%xmm0, 255(%rsp)
	vxorps	%ymm0, %ymm0, %ymm0
	vmovaps	%ymm0, 224(%rsp)
	vmovaps	%ymm0, 192(%rsp)
	vmovaps	%ymm0, 160(%rsp)
	vmovaps	%ymm0, 128(%rsp)
	vmovaps	%ymm0, 96(%rsp)
	vmovaps	%ymm0, 64(%rsp)
	vmovaps	%ymm0, 32(%rsp)
	.loc	5 83 0                  # util.c:83:0
	movq	312(%rsp), %rsi
	movq	%rbx, %rdi
	vzeroupper
	callq	getfileline
	.loc	5 84 0                  # util.c:84:0
.Ltmp240:
	movq	312(%rsp), %rdi
	callq	feof
	testl	%eax, %eax
	jne	.LBB10_7
.Ltmp241:
# BB#4:                                 # %if.end5
                                        #   in Loop: Header=BB10_2 Depth=1
	.loc	5 86 0                  # util.c:86:0
	movl	$.L.str241, %esi
	movq	%rbx, %rdi
	callq	strtok
	movq	%rax, 24(%rsp)
	testq	%rax, %rax
	je	.LBB10_2
# BB#5:                                 # %land.lhs.true
                                        #   in Loop: Header=BB10_2 Depth=1
	.loc	5 87 0                  # util.c:87:0
.Ltmp242:
	movq	24(%rsp), %rdi
	movl	$.L.str342, %esi
	callq	gstricmp
	testl	%eax, %eax
	jne	.LBB10_2
	jmp	.LBB10_6
.Ltmp243:
.LBB10_7:                               # %while.end
	.loc	5 91 0                  # util.c:91:0
	movq	312(%rsp), %rdi
	callq	fclose
	.loc	5 92 0                  # util.c:92:0
	movq	304(%rsp), %rax
	movq	%rax, 320(%rsp)
	jmp	.LBB10_8
.LBB10_9:                               # %if.then
	.loc	5 78 0                  # util.c:78:0
.Ltmp244:
	movq	$0, 320(%rsp)
.Ltmp245:
.LBB10_8:                               # %return
	.loc	5 93 0                  # util.c:93:0
	movq	320(%rsp), %rax
	leaq	-8(%rbp), %rsp
	popq	%rbx
	popq	%rbp
	ret
.Ltmp246:
.Ltmp247:
	.size	count_vhosts, .Ltmp247-count_vhosts
.Lfunc_end10:
	.cfi_endproc

	.globl	gstricmp
	.align	16, 0x90
	.type	gstricmp,@function
gstricmp:                               # @gstricmp
	.cfi_startproc
.Lfunc_begin11:
	.loc	5 195 0                 # util.c:195:0
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp251:
	.cfi_def_cfa_offset 16
.Ltmp252:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp253:
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	subq	$40, %rsp
.Ltmp254:
	.cfi_offset %rbx, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	.loc	5 196 0 prologue_end    # util.c:196:0
.Ltmp255:
	movl	$0, -36(%rbp)
	.loc	5 198 0                 # util.c:198:0
.Ltmp256:
	cmpq	$0, -24(%rbp)
	je	.LBB11_2
# BB#1:                                 # %lor.lhs.false
	cmpq	$0, -32(%rbp)
	je	.LBB11_2
.Ltmp257:
	.align	16, 0x90
.LBB11_3:                               # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	.loc	5 200 0                 # util.c:200:0
	movq	-24(%rbp), %rax
	movsbl	(%rax), %eax
	testl	%eax, %eax
	je	.LBB11_4
# BB#5:                                 # %land.rhs
                                        #   in Loop: Header=BB11_3 Depth=1
	movq	-32(%rbp), %rax
	movsbl	(%rax), %eax
	testl	%eax, %eax
	setne	%al
	jmp	.LBB11_6
	.align	16, 0x90
.LBB11_4:                               #   in Loop: Header=BB11_3 Depth=1
	xorl	%eax, %eax
.LBB11_6:                               # %land.end
                                        #   in Loop: Header=BB11_3 Depth=1
	testb	%al, %al
	je	.LBB11_9
# BB#7:                                 # %while.body
                                        #   in Loop: Header=BB11_3 Depth=1
	.loc	5 201 0                 # util.c:201:0
.Ltmp258:
	movq	-24(%rbp), %rax
	leaq	1(%rax), %rcx
	movq	%rcx, -24(%rbp)
	movsbl	(%rax), %edi
	callq	tolower
	movl	%eax, %ebx
	movq	-32(%rbp), %rax
	leaq	1(%rax), %rcx
	movq	%rcx, -32(%rbp)
	movsbl	(%rax), %edi
	callq	tolower
	cmpl	%eax, %ebx
	je	.LBB11_3
# BB#8:                                 # %if.then10
	movl	$1, -12(%rbp)
	jmp	.LBB11_12
.Ltmp259:
.LBB11_2:                               # %if.then
	.loc	5 198 0                 # util.c:198:0
	movl	$1, -12(%rbp)
.Ltmp260:
.LBB11_12:                              # %return
	.loc	5 206 0                 # util.c:206:0
	movl	-12(%rbp), %eax
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	ret
.LBB11_9:                               # %while.end
	.loc	5 203 0                 # util.c:203:0
.Ltmp261:
	movq	-24(%rbp), %rax
	leaq	1(%rax), %rcx
	movq	%rcx, -24(%rbp)
	movsbl	(%rax), %edi
	callq	tolower
	movl	%eax, %ebx
	movq	-32(%rbp), %rax
	leaq	1(%rax), %rcx
	movq	%rcx, -32(%rbp)
	movsbl	(%rax), %edi
	callq	tolower
	cmpl	%eax, %ebx
	je	.LBB11_11
# BB#10:                                # %if.then20
	movl	$1, -12(%rbp)
	jmp	.LBB11_12
.Ltmp262:
.LBB11_11:                              # %if.end21
	.loc	5 205 0                 # util.c:205:0
	movl	$0, -12(%rbp)
	jmp	.LBB11_12
.Ltmp263:
.Ltmp264:
	.size	gstricmp, .Ltmp264-gstricmp
.Lfunc_end11:
	.cfi_endproc

	.globl	VirtualHostDefinition
	.align	16, 0x90
	.type	VirtualHostDefinition,@function
VirtualHostDefinition:                  # @VirtualHostDefinition
	.cfi_startproc
.Lfunc_begin12:
	.loc	5 96 0                  # util.c:96:0
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp268:
	.cfi_def_cfa_offset 16
.Ltmp269:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp270:
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$296, %rsp              # imm = 0x128
.Ltmp271:
	.cfi_offset %rbx, -56
.Ltmp272:
	.cfi_offset %r12, -48
.Ltmp273:
	.cfi_offset %r13, -40
.Ltmp274:
	.cfi_offset %r14, -32
.Ltmp275:
	.cfi_offset %r15, -24
	movq	%rdi, -48(%rbp)
	.loc	5 97 0 prologue_end     # util.c:97:0
.Ltmp276:
	movq	$0, -312(%rbp)
	movq	$0, -320(%rbp)
	.loc	5 98 0                  # util.c:98:0
	movq	$0, -328(%rbp)
	.loc	5 100 0                 # util.c:100:0
	imulq	$1275, no_vhosts(%rip), %rdi # imm = 0x4FB
	addq	vhosts(%rip), %rdi
	movq	%rdi, -328(%rbp)
	.loc	5 102 0                 # util.c:102:0
	movl	$.L.str443, %esi
	callq	strcpy
	.loc	5 103 0                 # util.c:103:0
	movq	-328(%rbp), %rdi
	addq	$255, %rdi
	movl	$defaulthost+255, %esi
	callq	strcpy
	.loc	5 104 0                 # util.c:104:0
	movq	-328(%rbp), %rdi
	addq	$510, %rdi              # imm = 0x1FE
	movl	$defaulthost+510, %esi
	callq	strcpy
	.loc	5 105 0                 # util.c:105:0
	movq	-328(%rbp), %rdi
	addq	$765, %rdi              # imm = 0x2FD
	movl	$defaulthost+765, %esi
	callq	strcpy
	.loc	5 106 0                 # util.c:106:0
	movq	-328(%rbp), %rdi
	addq	$1020, %rdi             # imm = 0x3FC
	movl	$defaulthost+1020, %esi
	callq	strcpy
	leaq	-304(%rbp), %rbx
	movl	$1020, %r14d            # imm = 0x3FC
	movl	$765, %r15d             # imm = 0x2FD
	movl	$510, %r12d             # imm = 0x1FE
	movl	$255, %r13d
	jmp	.LBB12_1
.LBB12_10:                              # %while.cond
                                        #   in Loop: Header=BB12_1 Depth=1
	.loc	5 123 0                 # util.c:123:0
.Ltmp277:
	movq	-320(%rbp), %rsi
	callq	strcpy
.Ltmp278:
	.align	16, 0x90
.LBB12_1:                               # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	.loc	5 108 0                 # util.c:108:0
	movq	-48(%rbp), %rdi
	callq	feof
	testl	%eax, %eax
	jne	.LBB12_19
# BB#2:                                 # %while.body
                                        #   in Loop: Header=BB12_1 Depth=1
	.loc	5 110 0                 # util.c:110:0
.Ltmp279:
	movq	-48(%rbp), %rsi
	movq	%rbx, %rdi
	callq	getfileline
	.loc	5 112 0                 # util.c:112:0
.Ltmp280:
	movq	-48(%rbp), %rdi
	callq	feof
	testl	%eax, %eax
	jne	.LBB12_19
.Ltmp281:
# BB#3:                                 # %if.end
                                        #   in Loop: Header=BB12_1 Depth=1
	.loc	5 113 0                 # util.c:113:0
	movl	$.L.str544, %esi
	movq	%rbx, %rdi
	callq	strtok
	movq	%rax, -312(%rbp)
	xorl	%edi, %edi
	movl	$.L.str544, %esi
	.loc	5 114 0                 # util.c:114:0
	callq	strtok
	movq	%rax, -320(%rbp)
	.loc	5 116 0                 # util.c:116:0
.Ltmp282:
	cmpq	$0, -312(%rbp)
	je	.LBB12_1
.Ltmp283:
# BB#4:                                 # %if.end18
                                        #   in Loop: Header=BB12_1 Depth=1
	.loc	5 117 0                 # util.c:117:0
	movq	-312(%rbp), %rax
	movsbl	(%rax), %eax
	cmpl	$60, %eax
	je	.LBB12_6
# BB#5:                                 # %land.lhs.true
                                        #   in Loop: Header=BB12_1 Depth=1
	cmpq	$0, -320(%rbp)
	je	.LBB12_1
.Ltmp284:
.LBB12_6:                               # %if.end23
                                        #   in Loop: Header=BB12_1 Depth=1
	.loc	5 118 0                 # util.c:118:0
	movq	-312(%rbp), %rax
	movsbl	(%rax), %eax
	cmpl	$35, %eax
	je	.LBB12_1
.Ltmp285:
# BB#7:                                 # %if.end29
                                        #   in Loop: Header=BB12_1 Depth=1
	.loc	5 120 0                 # util.c:120:0
	movq	-312(%rbp), %rdi
	movl	$.L.str645, %esi
	callq	gstricmp
	testl	%eax, %eax
	je	.LBB12_19
# BB#8:                                 # %if.else
                                        #   in Loop: Header=BB12_1 Depth=1
	.loc	5 122 0                 # util.c:122:0
.Ltmp286:
	movq	-312(%rbp), %rdi
	movl	$.L.str746, %esi
	callq	gstricmp
	testl	%eax, %eax
	je	.LBB12_9
# BB#11:                                # %if.else39
                                        #   in Loop: Header=BB12_1 Depth=1
	.loc	5 124 0                 # util.c:124:0
.Ltmp287:
	movq	-312(%rbp), %rdi
	movl	$.L.str847, %esi
	callq	gstricmp
	testl	%eax, %eax
	je	.LBB12_12
# BB#13:                                # %if.else46
                                        #   in Loop: Header=BB12_1 Depth=1
	.loc	5 126 0                 # util.c:126:0
.Ltmp288:
	movq	-312(%rbp), %rdi
	movl	$.L.str948, %esi
	callq	gstricmp
	testl	%eax, %eax
	je	.LBB12_14
# BB#15:                                # %if.else53
                                        #   in Loop: Header=BB12_1 Depth=1
	.loc	5 128 0                 # util.c:128:0
.Ltmp289:
	movq	-312(%rbp), %rdi
	movl	$.L.str1049, %esi
	callq	gstricmp
	testl	%eax, %eax
	je	.LBB12_16
# BB#17:                                # %if.else60
                                        #   in Loop: Header=BB12_1 Depth=1
	.loc	5 130 0                 # util.c:130:0
.Ltmp290:
	movq	-312(%rbp), %rdi
	movl	$.L.str1150, %esi
	callq	gstricmp
	testl	%eax, %eax
	jne	.LBB12_1
# BB#18:                                # %if.then63
                                        #   in Loop: Header=BB12_1 Depth=1
	movq	-328(%rbp), %rdi
	.loc	5 131 0                 # util.c:131:0
	addq	%r14, %rdi
	jmp	.LBB12_10
.Ltmp291:
.LBB12_9:                               # %if.then35
                                        #   in Loop: Header=BB12_1 Depth=1
	.loc	5 123 0                 # util.c:123:0
	movq	-328(%rbp), %rdi
	jmp	.LBB12_10
.LBB12_12:                              # %if.then42
                                        #   in Loop: Header=BB12_1 Depth=1
	movq	-328(%rbp), %rdi
	.loc	5 125 0                 # util.c:125:0
.Ltmp292:
	addq	%r13, %rdi
	jmp	.LBB12_10
.LBB12_14:                              # %if.then49
                                        #   in Loop: Header=BB12_1 Depth=1
	movq	-328(%rbp), %rdi
	.loc	5 127 0                 # util.c:127:0
.Ltmp293:
	addq	%r12, %rdi
	jmp	.LBB12_10
.LBB12_16:                              # %if.then56
                                        #   in Loop: Header=BB12_1 Depth=1
	movq	-328(%rbp), %rdi
	.loc	5 129 0                 # util.c:129:0
.Ltmp294:
	addq	%r15, %rdi
	jmp	.LBB12_10
.Ltmp295:
.LBB12_19:                              # %while.end
	.loc	5 134 0                 # util.c:134:0
	incq	no_vhosts(%rip)
	.loc	5 135 0                 # util.c:135:0
	addq	$296, %rsp              # imm = 0x128
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
.Ltmp296:
.Ltmp297:
	.size	VirtualHostDefinition, .Ltmp297-VirtualHostDefinition
.Lfunc_end12:
	.cfi_endproc

	.globl	gstrlwr
	.align	16, 0x90
	.type	gstrlwr,@function
gstrlwr:                                # @gstrlwr
	.cfi_startproc
.Lfunc_begin13:
	.loc	5 138 0                 # util.c:138:0
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp300:
	.cfi_def_cfa_offset 16
.Ltmp301:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp302:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	.loc	5 139 0 prologue_end    # util.c:139:0
.Ltmp303:
	movl	$0, -12(%rbp)
	.loc	5 141 0                 # util.c:141:0
.Ltmp304:
	cmpq	$0, -8(%rbp)
	je	.LBB13_5
.Ltmp305:
# BB#1:                                 # %if.end
	.loc	5 142 0                 # util.c:142:0
	movl	$0, -12(%rbp)
	jmp	.LBB13_2
	.align	16, 0x90
.LBB13_4:                               # %for.inc
                                        #   in Loop: Header=BB13_2 Depth=1
	.loc	5 143 0                 # util.c:143:0
	movl	-12(%rbp), %eax
	movq	-8(%rbp), %rcx
	movsbl	(%rcx,%rax), %edi
	callq	tolower
	movl	-12(%rbp), %ecx
	movq	-8(%rbp), %rdx
	movb	%al, (%rdx,%rcx)
	.loc	5 142 0                 # util.c:142:0
	incl	-12(%rbp)
.LBB13_2:                               # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$254, -12(%rbp)
	ja	.LBB13_5
# BB#3:                                 # %land.lhs.true
                                        #   in Loop: Header=BB13_2 Depth=1
	movl	-12(%rbp), %eax
	movq	-8(%rbp), %rcx
	movsbl	(%rcx,%rax), %eax
	testl	%eax, %eax
	jne	.LBB13_4
.Ltmp306:
.LBB13_5:                               # %for.end
	.loc	5 144 0                 # util.c:144:0
	addq	$16, %rsp
	popq	%rbp
	ret
.Ltmp307:
.Ltmp308:
	.size	gstrlwr, .Ltmp308-gstrlwr
.Lfunc_end13:
	.cfi_endproc

	.globl	readinconfig
	.align	16, 0x90
	.type	readinconfig,@function
readinconfig:                           # @readinconfig
	.cfi_startproc
.Lfunc_begin14:
	.loc	5 147 0                 # util.c:147:0
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp312:
	.cfi_def_cfa_offset 16
.Ltmp313:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp314:
	.cfi_def_cfa_register %rbp
	.loc	5 149 0 prologue_end    # util.c:149:0
.Ltmp315:
	pushq	%rbx
	subq	$296, %rsp              # imm = 0x128
.Ltmp316:
	.cfi_offset %rbx, -24
	movq	$0, -24(%rbp)
	movq	$0, -32(%rbp)
	.loc	5 151 0                 # util.c:151:0
	movl	$0, -292(%rbp)
	.loc	5 154 0                 # util.c:154:0
.Ltmp317:
	movl	$.L.str39, %edi
	movl	$.L.str140, %esi
	callq	fopen
	movq	%rax, -16(%rbp)
	testq	%rax, %rax
	je	.LBB14_26
.Ltmp318:
# BB#1:                                 # %if.end
	.loc	5 157 0                 # util.c:157:0
	movq	$0, no_vhosts(%rip)
	leaq	-288(%rbp), %rbx
	jmp	.LBB14_2
.LBB14_9:                               # %if.then25
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 172 0                 # util.c:172:0
.Ltmp319:
	movq	-32(%rbp), %rsi
	movl	$SERVERROOT, %edi
	callq	strcpy
.Ltmp320:
	.align	16, 0x90
.LBB14_2:                               # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	.loc	5 159 0                 # util.c:159:0
	movq	-16(%rbp), %rdi
	callq	feof
	testl	%eax, %eax
	jne	.LBB14_25
# BB#3:                                 # %while.body
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 161 0                 # util.c:161:0
.Ltmp321:
	movq	-16(%rbp), %rsi
	movq	%rbx, %rdi
	callq	getfileline
	.loc	5 163 0                 # util.c:163:0
.Ltmp322:
	movq	-16(%rbp), %rdi
	callq	feof
	testl	%eax, %eax
	jne	.LBB14_25
.Ltmp323:
# BB#4:                                 # %if.end5
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 164 0                 # util.c:164:0
	movl	$.L.str1251, %esi
	movq	%rbx, %rdi
	callq	strtok
	movq	%rax, -24(%rbp)
	xorl	%edi, %edi
	movl	$.L.str1251, %esi
	.loc	5 165 0                 # util.c:165:0
	callq	strtok
	movq	%rax, -32(%rbp)
	.loc	5 167 0                 # util.c:167:0
.Ltmp324:
	cmpq	$0, -24(%rbp)
	je	.LBB14_2
.Ltmp325:
# BB#5:                                 # %if.end11
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 168 0                 # util.c:168:0
	movq	-24(%rbp), %rax
	movsbl	(%rax), %eax
	cmpl	$60, %eax
	je	.LBB14_7
# BB#6:                                 # %land.lhs.true
                                        #   in Loop: Header=BB14_2 Depth=1
	cmpq	$0, -32(%rbp)
	je	.LBB14_2
.Ltmp326:
.LBB14_7:                               # %if.end16
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 169 0                 # util.c:169:0
	movq	-24(%rbp), %rax
	movsbl	(%rax), %eax
	cmpl	$35, %eax
	je	.LBB14_2
.Ltmp327:
# BB#8:                                 # %if.end22
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 171 0                 # util.c:171:0
	movq	-24(%rbp), %rdi
	movl	$.L.str1352, %esi
	callq	gstricmp
	testl	%eax, %eax
	je	.LBB14_9
# BB#10:                                # %if.else
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 173 0                 # util.c:173:0
.Ltmp328:
	movq	-24(%rbp), %rdi
	movl	$.L.str847, %esi
	callq	gstricmp
	testl	%eax, %eax
	je	.LBB14_11
# BB#12:                                # %if.else31
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 175 0                 # util.c:175:0
.Ltmp329:
	movq	-24(%rbp), %rdi
	movl	$.L.str948, %esi
	callq	gstricmp
	testl	%eax, %eax
	je	.LBB14_13
# BB#14:                                # %if.else36
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 177 0                 # util.c:177:0
.Ltmp330:
	movq	-24(%rbp), %rdi
	movl	$.L.str1049, %esi
	callq	gstricmp
	testl	%eax, %eax
	je	.LBB14_15
# BB#16:                                # %if.else41
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 179 0                 # util.c:179:0
.Ltmp331:
	movq	-24(%rbp), %rdi
	movl	$.L.str1150, %esi
	callq	gstricmp
	testl	%eax, %eax
	je	.LBB14_17
# BB#18:                                # %if.else46
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 181 0                 # util.c:181:0
.Ltmp332:
	movq	-24(%rbp), %rdi
	movl	$.L.str1453, %esi
	callq	gstricmp
	testl	%eax, %eax
	je	.LBB14_19
# BB#20:                                # %if.else51
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 183 0                 # util.c:183:0
.Ltmp333:
	movq	-24(%rbp), %rdi
	movl	$.L.str1554, %esi
	callq	gstricmp
	testl	%eax, %eax
	je	.LBB14_21
# BB#22:                                # %if.else56
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 185 0                 # util.c:185:0
.Ltmp334:
	movq	-24(%rbp), %rdi
	movl	$.L.str1655, %esi
	callq	gstricmp
	testl	%eax, %eax
	je	.LBB14_23
# BB#24:                                # %if.else60
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 188 0                 # util.c:188:0
	movq	-24(%rbp), %rsi
	movl	$.L.str1756, %edi
	xorl	%eax, %eax
	callq	printf
	jmp	.LBB14_2
.Ltmp335:
.LBB14_11:                              # %if.then29
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 174 0                 # util.c:174:0
	movq	-32(%rbp), %rsi
	movl	$defaulthost+255, %edi
	callq	strcpy
	jmp	.LBB14_2
.LBB14_13:                              # %if.then34
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 176 0                 # util.c:176:0
.Ltmp336:
	movq	-32(%rbp), %rsi
	movl	$defaulthost+510, %edi
	callq	strcpy
	jmp	.LBB14_2
.LBB14_15:                              # %if.then39
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 178 0                 # util.c:178:0
.Ltmp337:
	movq	-32(%rbp), %rsi
	movl	$defaulthost+765, %edi
	callq	strcpy
	jmp	.LBB14_2
.LBB14_17:                              # %if.then44
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 180 0                 # util.c:180:0
.Ltmp338:
	movq	-32(%rbp), %rsi
	movl	$defaulthost+1020, %edi
	callq	strcpy
	jmp	.LBB14_2
.LBB14_19:                              # %if.then49
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 182 0                 # util.c:182:0
.Ltmp339:
	movq	-32(%rbp), %rdi
	callq	atoi
	movl	%eax, SERVERPORT(%rip)
	jmp	.LBB14_2
.LBB14_21:                              # %if.then54
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 184 0                 # util.c:184:0
.Ltmp340:
	movq	-32(%rbp), %rsi
	movl	$SERVERTYPE, %edi
	callq	strcpy
	jmp	.LBB14_2
.LBB14_23:                              # %if.then59
                                        #   in Loop: Header=BB14_2 Depth=1
	.loc	5 186 0                 # util.c:186:0
.Ltmp341:
	movq	-16(%rbp), %rdi
	callq	VirtualHostDefinition
	jmp	.LBB14_2
.Ltmp342:
.LBB14_25:                              # %while.end
	.loc	5 191 0                 # util.c:191:0
	movq	-16(%rbp), %rdi
	callq	fclose
.LBB14_26:                              # %return
	.loc	5 192 0                 # util.c:192:0
	addq	$296, %rsp              # imm = 0x128
	popq	%rbx
	popq	%rbp
	ret
.Ltmp343:
.Ltmp344:
	.size	readinconfig, .Ltmp344-readinconfig
.Lfunc_end14:
	.cfi_endproc

	.globl	Log
	.align	16, 0x90
	.type	Log,@function
Log:                                    # @Log
	.cfi_startproc
.Lfunc_begin15:
	.loc	5 209 0                 # util.c:209:0
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp348:
	.cfi_def_cfa_offset 16
.Ltmp349:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp350:
	.cfi_def_cfa_register %rbp
	pushq	%r14
	pushq	%rbx
	andq	$-32, %rsp
	subq	$704, %rsp              # imm = 0x2C0
.Ltmp351:
	.cfi_offset %rbx, -32
.Ltmp352:
	.cfi_offset %r14, -24
	testb	%al, %al
	je	.LBB15_2
# BB#1:                                 # %entry
	vmovaps	%xmm0, 64(%rsp)
	vmovaps	%xmm1, 80(%rsp)
	vmovaps	%xmm2, 96(%rsp)
	vmovaps	%xmm3, 112(%rsp)
	vmovaps	%xmm4, 128(%rsp)
	vmovaps	%xmm5, 144(%rsp)
	vmovaps	%xmm6, 160(%rsp)
	vmovaps	%xmm7, 176(%rsp)
.LBB15_2:                               # %entry
	movq	%r9, 56(%rsp)
	movq	%r8, 48(%rsp)
	movq	%rcx, 40(%rsp)
	movq	%rdx, 32(%rsp)
	movq	%rsi, 24(%rsp)
	movq	%rdi, 696(%rsp)
	movabsq	$26268591989794106, %rax # imm = 0x5D53252E4D253A
	.loc	5 215 0 prologue_end    # util.c:215:0
.Ltmp353:
	movq	%rax, 382(%rsp)
	vmovaps	.LLog.datetime(%rip), %xmm0
	vmovaps	%xmm0, 368(%rsp)
	leaq	16(%rsp), %rax
	.loc	5 219 0                 # util.c:219:0
	movq	%rax, 208(%rsp)
	leaq	16(%rbp), %rax
	movq	%rax, 200(%rsp)
	movl	$48, 196(%rsp)
	movl	$8, 192(%rsp)
	.loc	5 221 0                 # util.c:221:0
	movq	696(%rsp), %rdi
	callq	strlen
	movq	%rax, %rdi
	callq	malloc
	movq	%rax, 664(%rsp)
	movq	696(%rsp), %rsi
	leaq	192(%rsp), %rdx
	movq	%rax, %rdi
	callq	vsprintf
	leaq	680(%rsp), %rbx
	xorl	%eax, %eax
	.loc	5 224 0                 # util.c:224:0
	movq	%rbx, %rdi
	callq	time
	xorl	%eax, %eax
	.loc	5 225 0                 # util.c:225:0
	movq	%rbx, %rdi
	callq	localtime
	cltq
	movq	%rax, 672(%rsp)
	vxorps	%ymm0, %ymm0, %ymm0
	.loc	5 226 0                 # util.c:226:0
	vmovaps	%ymm0, 320(%rsp)
	vmovaps	%ymm0, 288(%rsp)
	vmovaps	%ymm0, 256(%rsp)
	vmovaps	%ymm0, 224(%rsp)
	.loc	5 227 0                 # util.c:227:0
	movq	672(%rsp), %rcx
	leaq	224(%rsp), %r14
	leaq	368(%rsp), %rdx
	movl	$127, %esi
	xorl	%eax, %eax
	movq	%r14, %rdi
	vzeroupper
	callq	strftime
	.loc	5 231 0                 # util.c:231:0
	movq	664(%rsp), %rdi
	callq	strlen
	movq	%rax, %rbx
	movq	%r14, %rdi
	callq	strlen
	leaq	5(%rbx,%rax), %rdi
	callq	malloc
	movq	%rax, %rdx
	movq	%rdx, 656(%rsp)
	.loc	5 232 0                 # util.c:232:0
	movq	664(%rsp), %rcx
	movl	$.L.str1857, %esi
	xorl	%eax, %eax
	movq	%rdx, %rdi
	movq	%r14, %rdx
	callq	sprintf
	leaq	400(%rsp), %rbx
	.loc	5 233 0                 # util.c:233:0
	movl	$.L.str1958, %esi
	movl	$SERVERROOT, %edx
	xorl	%eax, %eax
	movq	%rbx, %rdi
	callq	sprintf
	.loc	5 235 0                 # util.c:235:0
.Ltmp354:
	movl	$.L.str2059, %esi
	movq	%rbx, %rdi
	callq	fopen
	movq	%rax, 688(%rsp)
	testq	%rax, %rax
	je	.LBB15_4
.Ltmp355:
# BB#3:                                 # %if.end
	.loc	5 238 0                 # util.c:238:0
	movq	656(%rsp), %rdi
	movq	688(%rsp), %rsi
	callq	fputs
	.loc	5 240 0                 # util.c:240:0
	movq	688(%rsp), %rdi
	callq	fclose
.LBB15_4:                               # %return
	.loc	5 241 0                 # util.c:241:0
	leaq	-16(%rbp), %rsp
	popq	%rbx
	popq	%r14
	popq	%rbp
	ret
.Ltmp356:
.Ltmp357:
	.size	Log, .Ltmp357-Log
.Lfunc_end15:
	.cfi_endproc

	.type	no_vhosts,@object       # @no_vhosts
	.bss
	.globl	no_vhosts
	.align	8
no_vhosts:
	.quad	0                       # 0x0
	.size	no_vhosts, 8

	.type	vhosts,@object          # @vhosts
	.globl	vhosts
	.align	8
vhosts:
	.quad	0
	.size	vhosts, 8

	.type	SERVERPORT,@object      # @SERVERPORT
	.data
	.globl	SERVERPORT
	.align	4
SERVERPORT:
	.long	80                      # 0x50
	.size	SERVERPORT, 4

	.type	SERVERTYPE,@object      # @SERVERTYPE
	.globl	SERVERTYPE
	.align	16
SERVERTYPE:
	.asciz	"Standalone\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.size	SERVERTYPE, 255

	.type	SERVERROOT,@object      # @SERVERROOT
	.globl	SERVERROOT
	.align	16
SERVERROOT:
	.asciz	"/usr/local/ghttpd\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.size	SERVERROOT, 255

	.type	defaulthost,@object     # @defaulthost
	.comm	defaulthost,1275,1
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"/usr/local/ghttpd/htdocs"
	.size	.L.str, 25

	.type	.L.str1,@object         # @.str1
.L.str1:
	.asciz	"index.html"
	.size	.L.str1, 11

	.type	.L.str2,@object         # @.str2
.L.str2:
	.asciz	"/cgi-bin"
	.size	.L.str2, 9

	.type	.L.str3,@object         # @.str3
.L.str3:
	.asciz	"/usr/local/ghttpd/cgi-bin"
	.size	.L.str3, 26

	.type	.L.str4,@object         # @.str4
.L.str4:
	.asciz	"inetd"
	.size	.L.str4, 6

	.type	.L.str5,@object         # @.str5
.L.str5:
	.asciz	"ghttpd"
	.size	.L.str5, 7

	.type	.L.str6,@object         # @.str6
.L.str6:
	.asciz	"socket"
	.size	.L.str6, 7

	.type	.L.str7,@object         # @.str7
.L.str7:
	.asciz	"Could create a socket, exiting\n"
	.size	.L.str7, 32

	.type	.L.str8,@object         # @.str8
.L.str8:
	.asciz	"bind"
	.size	.L.str8, 5

	.type	.L.str9,@object         # @.str9
.L.str9:
	.asciz	"Could not bind to port, exiting\n"
	.size	.L.str9, 33

	.type	.L.str10,@object        # @.str10
.L.str10:
	.asciz	"listen"
	.size	.L.str10, 7

	.type	.L.str11,@object        # @.str11
.L.str11:
	.asciz	"Unable to do a listen()\n"
	.size	.L.str11, 25

	.type	.L.str12,@object        # @.str12
.L.str12:
	.asciz	"FATAL ERROR, Could not fork() ghttpd into background\n"
	.size	.L.str12, 54

	.type	.L.str13,@object        # @.str13
.L.str13:
	.asciz	"Could not fork() ghttpd into background\n"
	.size	.L.str13, 41

	.type	.L.str14,@object        # @.str14
.L.str14:
	.asciz	"ghttpd launched into background, PID = %d\n"
	.size	.L.str14, 43

	.type	.L.str15,@object        # @.str15
.L.str15:
	.asciz	"nobody"
	.size	.L.str15, 7

	.type	.L.str16,@object        # @.str16
.L.str16:
	.asciz	"REMOTE_ADDR"
	.size	.L.str16, 12

	.type	.L.str17,@object        # @.str17
.L.str17:
	.asciz	"Connection from %s"
	.size	.L.str17, 19

	.type	.L.str18,@object        # @.str18
.L.str18:
	.asciz	"\r\n\r\n"
	.size	.L.str18, 5

	.type	.L.str119,@object       # @.str119
.L.str119:
	.asciz	"\n\n"
	.size	.L.str119, 3

	.type	.L.str220,@object       # @.str220
.L.str220:
	.asciz	" "
	.size	.L.str220, 2

	.type	.L.str321,@object       # @.str321
.L.str321:
	.asciz	"GET"
	.size	.L.str321, 4

	.type	.L.str422,@object       # @.str422
.L.str422:
	.asciz	"Connection from %s, cmderror = \"GET %s\""
	.size	.L.str422, 40

	.type	.L.str523,@object       # @.str523
.L.str523:
	.asciz	"/cmderror.html"
	.size	.L.str523, 15

	.type	.L.str624,@object       # @.str624
.L.str624:
	.asciz	"Connection from %s, cmderror = \"GET\""
	.size	.L.str624, 37

	.type	.L.str725,@object       # @.str725
.L.str725:
	.asciz	"Host:"
	.size	.L.str725, 6

	.type	.L.str826,@object       # @.str826
.L.str826:
	.asciz	" \r\n\t"
	.size	.L.str826, 5

	.type	.L.str927,@object       # @.str927
.L.str927:
	.asciz	"/.."
	.size	.L.str927, 4

	.type	.L.str1028,@object      # @.str1028
.L.str1028:
	.asciz	"Connection from %s, 404 = \"GET %s\""
	.size	.L.str1028, 35

	.type	.L.str1129,@object      # @.str1129
.L.str1129:
	.asciz	"/404.html"
	.size	.L.str1129, 10

	.type	.L.str1230,@object      # @.str1230
.L.str1230:
	.asciz	"Connection from %s, request = \"GET %s\""
	.size	.L.str1230, 39

	.type	.L.str1331,@object      # @.str1331
.L.str1331:
	.asciz	"%20"
	.size	.L.str1331, 4

	.type	.L.str1432,@object      # @.str1432
.L.str1432:
	.asciz	"?"
	.size	.L.str1432, 2

	.type	.L.str1533,@object      # @.str1533
.L.str1533:
	.asciz	"HTTP/1.1 200 OK\n"
	.size	.L.str1533, 17

	.type	.L.str1634,@object      # @.str1634
.L.str1634:
	.asciz	"Server: GazTek HTTP Daemon v1.4-4\n"
	.size	.L.str1634, 35

	.type	.L.str1735,@object      # @.str1735
.L.str1735:
	.asciz	"QUERY_STRING"
	.size	.L.str1735, 13

	.type	.L.str1836,@object      # @.str1836
.L.str1836:
	.asciz	"Connection from %s, cgierror = \"EXEC %s %s\""
	.size	.L.str1836, 44

	.type	.L.str19,@object        # @.str19
.L.str19:
	.asciz	"/cgierror.html"
	.size	.L.str19, 15

	.type	.L.str20,@object        # @.str20
.L.str20:
	.asciz	"/"
	.size	.L.str20, 2

	.type	.L.str21,@object        # @.str21
.L.str21:
	.asciz	"rb"
	.size	.L.str21, 3

	.type	.L.str22,@object        # @.str22
.L.str22:
	.asciz	"Content-Length: %d\n"
	.size	.L.str22, 20

	.type	.L.str23,@object        # @.str23
.L.str23:
	.asciz	"Content-Type: %s\n\n"
	.size	.L.str23, 19

	.type	.L.str24,@object        # @.str24
.L.str24:
	.zero	1
	.size	.L.str24, 1

	.type	.L.str25,@object        # @.str25
.L.str25:
	.asciz	"application/octet-stream"
	.size	.L.str25, 25

	.type	showdir.dirfooter,@object # @showdir.dirfooter
	.section	.rodata,"a",@progbits
	.align	16
showdir.dirfooter:
	.asciz	"</TABLE><hr><center><font size=-1>This page is being provided to you by ghttpd<br><A HREF=\"http://members.xoom.com/gaztek\">http://members.xoom.com/gaztek</a></TD></TR></TABLE></BODY></HTML>\n"
	.size	showdir.dirfooter, 191

	.type	.L.str26,@object        # @.str26
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str26:
	.asciz	"HTTP/1.1 200 OK\nServer: GazTek HTTP Daemon v1.4-4\nContent-Type: text/html\n\n<HTML><BODY bgcolor=\"#33CCFF\"><center><TABLE BORDER=3 COLS=1 WIDTH=\"75%\" BGCOLOR=\"#66FFFF\"><tr><td><center><h2><u>Directory listing for %s</u></h2></center><TABLE BORDER=3 COLS=2 WIDTH=100% BGCOLOR=\"#FFFFFF\"><tr><td><b><center>Filename</center></b></td><td><b><center>Size (bytes)</center></b></td></tr>"
	.size	.L.str26, 379

	.type	.L.str27,@object        # @.str27
.L.str27:
	.asciz	"scandir"
	.size	.L.str27, 8

	.type	.L.str28,@object        # @.str28
.L.str28:
	.asciz	"%s%s/%s"
	.size	.L.str28, 8

	.type	.L.str29,@object        # @.str29
.L.str29:
	.asciz	"<tr><td><center><A HREF=\"%s/%s\">%s</a></center></td><td><center>%d</center></td></tr>\n"
	.size	.L.str29, 87

	.type	assocNames,@object      # @assocNames
	.data
	.globl	assocNames
	.align	16
assocNames:
	.asciz	"mp2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"audio/x-mpeg\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"mpa\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"audio/x-mpeg\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"abs\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"audio/x-mpeg\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"mpega\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"audio/x-mpeg\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"mpeg\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"video/mpeg\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"mpg\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"video/mpeg\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"mpe\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"video/mpeg\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"mpv\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"video/mpeg\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"vbs\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"video/mpeg\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"mpegv\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"video/mpeg\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"bin\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"application/octet-stream\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"com\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"application/octet-stream\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"dll\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"application/octet-stream\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"bmp\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"image/x-MS-bmp\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"exe\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"application/octet-stream\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"mid\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"audio/x-midi\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"midi\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"audio/x-midi\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"htm\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"text/html\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"html\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"text/html\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"txt\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"text/plain\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"gif\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"image/gif\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"tar\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"application/x-tar\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"jpg\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"image/jpeg\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"jpeg\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"image/jpeg\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"png\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"image/png\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"ra\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"audio/x-pn-realaudio\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"ram\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"audio/x-pn-realaudio\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"sys\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"application/octet-stream\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"wav\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"audio/x-wav\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"xbm\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"image/x-xbitmap\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"zip\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.asciz	"application/x-zip\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
	.zero	200
	.size	assocNames, 6400

	.type	.L.str39,@object        # @.str39
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str39:
	.asciz	"/etc/ghttpd.conf"
	.size	.L.str39, 17

	.type	.L.str140,@object       # @.str140
.L.str140:
	.asciz	"rt"
	.size	.L.str140, 3

	.type	.L.str241,@object       # @.str241
.L.str241:
	.asciz	" \t\n\r"
	.size	.L.str241, 5

	.type	.L.str342,@object       # @.str342
.L.str342:
	.asciz	"<virtualhost>"
	.size	.L.str342, 14

	.type	.L.str443,@object       # @.str443
.L.str443:
	.zero	1
	.size	.L.str443, 1

	.type	.L.str544,@object       # @.str544
.L.str544:
	.asciz	"\" \t"
	.size	.L.str544, 4

	.type	.L.str645,@object       # @.str645
.L.str645:
	.asciz	"</virtualhost>"
	.size	.L.str645, 15

	.type	.L.str746,@object       # @.str746
.L.str746:
	.asciz	"Host"
	.size	.L.str746, 5

	.type	.L.str847,@object       # @.str847
.L.str847:
	.asciz	"DocumentRoot"
	.size	.L.str847, 13

	.type	.L.str948,@object       # @.str948
.L.str948:
	.asciz	"DefaultPage"
	.size	.L.str948, 12

	.type	.L.str1049,@object      # @.str1049
.L.str1049:
	.asciz	"CgiBinDir"
	.size	.L.str1049, 10

	.type	.L.str1150,@object      # @.str1150
.L.str1150:
	.asciz	"CgiBinRoot"
	.size	.L.str1150, 11

	.type	.L.str1251,@object      # @.str1251
.L.str1251:
	.asciz	"\"\t "
	.size	.L.str1251, 4

	.type	.L.str1352,@object      # @.str1352
.L.str1352:
	.asciz	"ServerRoot"
	.size	.L.str1352, 11

	.type	.L.str1453,@object      # @.str1453
.L.str1453:
	.asciz	"ServerPort"
	.size	.L.str1453, 11

	.type	.L.str1554,@object      # @.str1554
.L.str1554:
	.asciz	"ServerType"
	.size	.L.str1554, 11

	.type	.L.str1655,@object      # @.str1655
.L.str1655:
	.asciz	"<VirtualHost>"
	.size	.L.str1655, 14

	.type	.L.str1756,@object      # @.str1756
.L.str1756:
	.asciz	"Warning: unknown variable in config file \"%s\"\n"
	.size	.L.str1756, 47

	.type	.LLog.datetime,@object  # @Log.datetime
	.section	.rodata.str1.16,"aMS",@progbits,1
	.align	16
.LLog.datetime:
	.asciz	"[%d.%m.%Y] [%H:%M.%S]"
	.size	.LLog.datetime, 22

	.type	.L.str1857,@object      # @.str1857
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str1857:
	.asciz	"%s - %s\n"
	.size	.L.str1857, 9

	.type	.L.str1958,@object      # @.str1958
.L.str1958:
	.asciz	"%s/ghttpd.log"
	.size	.L.str1958, 14

	.type	.L.str2059,@object      # @.str2059
.L.str2059:
	.asciz	"at"
	.size	.L.str2059, 3

	.bss
.Ldebug_end1:
	.data
.Ldebug_end2:
	.section	.rodata,"a",@progbits
.Ldebug_end3:
	.text
.Ldebug_end4:
	.section	.debug_str,"MS",@progbits,1
.Linfo_string0:
	.asciz	"clang version 3.4 (tags/RELEASE_34/final)"
.Linfo_string1:
	.asciz	"main.c"
.Linfo_string2:
	.asciz	"/home/zhy/work/test/new/ghttpd/ghttpd-1.4-4"
.Linfo_string3:
	.asciz	"no_vhosts"
.Linfo_string4:
	.asciz	"long unsigned int"
.Linfo_string5:
	.asciz	"vhosts"
.Linfo_string6:
	.asciz	"host"
.Linfo_string7:
	.asciz	"char"
.Linfo_string8:
	.asciz	"int"
.Linfo_string9:
	.asciz	"DOCUMENTROOT"
.Linfo_string10:
	.asciz	"DEFAULTPAGE"
.Linfo_string11:
	.asciz	"CGIBINDIR"
.Linfo_string12:
	.asciz	"CGIBINROOT"
.Linfo_string13:
	.asciz	"t_vhost"
.Linfo_string14:
	.asciz	"SERVERPORT"
.Linfo_string15:
	.asciz	"unsigned int"
.Linfo_string16:
	.asciz	"SERVERTYPE"
.Linfo_string17:
	.asciz	"SERVERROOT"
.Linfo_string18:
	.asciz	"defaulthost"
.Linfo_string19:
	.asciz	"main"
.Linfo_string20:
	.asciz	"inetd_server"
.Linfo_string21:
	.asciz	"signal_handler"
.Linfo_string22:
	.asciz	"SOCK_STREAM"
.Linfo_string23:
	.asciz	"SOCK_DGRAM"
.Linfo_string24:
	.asciz	"SOCK_RAW"
.Linfo_string25:
	.asciz	"SOCK_RDM"
.Linfo_string26:
	.asciz	"SOCK_SEQPACKET"
.Linfo_string27:
	.asciz	"SOCK_DCCP"
.Linfo_string28:
	.asciz	"SOCK_PACKET"
.Linfo_string29:
	.asciz	"SOCK_CLOEXEC"
.Linfo_string30:
	.asciz	"SOCK_NONBLOCK"
.Linfo_string31:
	.asciz	"__socket_type"
.Linfo_string32:
	.asciz	"protocol.c"
.Linfo_string33:
	.asciz	"showdir"
.Linfo_string34:
	.asciz	"dirfooter"
.Linfo_string35:
	.asciz	"assocNames"
.Linfo_string36:
	.asciz	"serveconnection"
.Linfo_string37:
	.asciz	"getmimetype"
.Linfo_string38:
	.asciz	"util.c"
.Linfo_string39:
	.asciz	"getfileline"
.Linfo_string40:
	.asciz	"does_file_exist"
.Linfo_string41:
	.asciz	"get_file_size"
.Linfo_string42:
	.asciz	"isDirectory"
.Linfo_string43:
	.asciz	"count_vhosts"
.Linfo_string44:
	.asciz	"VirtualHostDefinition"
.Linfo_string45:
	.asciz	"gstrlwr"
.Linfo_string46:
	.asciz	"readinconfig"
.Linfo_string47:
	.asciz	"gstricmp"
.Linfo_string48:
	.asciz	"Log"
.Linfo_string49:
	.asciz	"xx"
.Linfo_string50:
	.asciz	"sockfd"
.Linfo_string51:
	.asciz	"new_fd"
.Linfo_string52:
	.asciz	"numbytes"
.Linfo_string53:
	.asciz	"my_addr"
.Linfo_string54:
	.asciz	"sin_family"
.Linfo_string55:
	.asciz	"unsigned short"
.Linfo_string56:
	.asciz	"sa_family_t"
.Linfo_string57:
	.asciz	"sin_port"
.Linfo_string58:
	.asciz	"uint16_t"
.Linfo_string59:
	.asciz	"in_port_t"
.Linfo_string60:
	.asciz	"sin_addr"
.Linfo_string61:
	.asciz	"s_addr"
.Linfo_string62:
	.asciz	"uint32_t"
.Linfo_string63:
	.asciz	"in_addr_t"
.Linfo_string64:
	.asciz	"in_addr"
.Linfo_string65:
	.asciz	"sin_zero"
.Linfo_string66:
	.asciz	"unsigned char"
.Linfo_string67:
	.asciz	"sockaddr_in"
.Linfo_string68:
	.asciz	"their_addr"
.Linfo_string69:
	.asciz	"sin_size"
.Linfo_string70:
	.asciz	"i"
.Linfo_string71:
	.asciz	"tv"
.Linfo_string72:
	.asciz	"tv_sec"
.Linfo_string73:
	.asciz	"long int"
.Linfo_string74:
	.asciz	"__time_t"
.Linfo_string75:
	.asciz	"tv_usec"
.Linfo_string76:
	.asciz	"__suseconds_t"
.Linfo_string77:
	.asciz	"timeval"
.Linfo_string78:
	.asciz	"readfds"
.Linfo_string79:
	.asciz	"fds_bits"
.Linfo_string80:
	.asciz	"__fd_mask"
.Linfo_string81:
	.asciz	"fd_set"
.Linfo_string82:
	.asciz	"exceptfds"
.Linfo_string83:
	.asciz	"pw"
.Linfo_string84:
	.asciz	"pw_name"
.Linfo_string85:
	.asciz	"pw_passwd"
.Linfo_string86:
	.asciz	"pw_uid"
.Linfo_string87:
	.asciz	"__uid_t"
.Linfo_string88:
	.asciz	"pw_gid"
.Linfo_string89:
	.asciz	"__gid_t"
.Linfo_string90:
	.asciz	"pw_gecos"
.Linfo_string91:
	.asciz	"pw_dir"
.Linfo_string92:
	.asciz	"pw_shell"
.Linfo_string93:
	.asciz	"passwd"
.Linfo_string94:
	.asciz	"__d0"
.Linfo_string95:
	.asciz	"__d1"
.Linfo_string96:
	.asciz	"signum"
.Linfo_string97:
	.asciz	"sval"
.Linfo_string98:
	.asciz	"size_t"
.Linfo_string99:
	.asciz	"in"
.Linfo_string100:
	.asciz	"_flags"
.Linfo_string101:
	.asciz	"_IO_read_ptr"
.Linfo_string102:
	.asciz	"_IO_read_end"
.Linfo_string103:
	.asciz	"_IO_read_base"
.Linfo_string104:
	.asciz	"_IO_write_base"
.Linfo_string105:
	.asciz	"_IO_write_ptr"
.Linfo_string106:
	.asciz	"_IO_write_end"
.Linfo_string107:
	.asciz	"_IO_buf_base"
.Linfo_string108:
	.asciz	"_IO_buf_end"
.Linfo_string109:
	.asciz	"_IO_save_base"
.Linfo_string110:
	.asciz	"_IO_backup_base"
.Linfo_string111:
	.asciz	"_IO_save_end"
.Linfo_string112:
	.asciz	"_markers"
.Linfo_string113:
	.asciz	"_next"
.Linfo_string114:
	.asciz	"_sbuf"
.Linfo_string115:
	.asciz	"_pos"
.Linfo_string116:
	.asciz	"_IO_marker"
.Linfo_string117:
	.asciz	"_chain"
.Linfo_string118:
	.asciz	"_fileno"
.Linfo_string119:
	.asciz	"_flags2"
.Linfo_string120:
	.asciz	"_old_offset"
.Linfo_string121:
	.asciz	"__off_t"
.Linfo_string122:
	.asciz	"_cur_column"
.Linfo_string123:
	.asciz	"_vtable_offset"
.Linfo_string124:
	.asciz	"signed char"
.Linfo_string125:
	.asciz	"_shortbuf"
.Linfo_string126:
	.asciz	"_lock"
.Linfo_string127:
	.asciz	"_offset"
.Linfo_string128:
	.asciz	"__off64_t"
.Linfo_string129:
	.asciz	"__pad1"
.Linfo_string130:
	.asciz	"__pad2"
.Linfo_string131:
	.asciz	"__pad3"
.Linfo_string132:
	.asciz	"__pad4"
.Linfo_string133:
	.asciz	"__pad5"
.Linfo_string134:
	.asciz	"_mode"
.Linfo_string135:
	.asciz	"_unused2"
.Linfo_string136:
	.asciz	"_IO_FILE"
.Linfo_string137:
	.asciz	"FILE"
.Linfo_string138:
	.asciz	"tempdata"
.Linfo_string139:
	.asciz	"ptr"
.Linfo_string140:
	.asciz	"ptr2"
.Linfo_string141:
	.asciz	"host_ptr1"
.Linfo_string142:
	.asciz	"host_ptr2"
.Linfo_string143:
	.asciz	"tempstring"
.Linfo_string144:
	.asciz	"mimetype"
.Linfo_string145:
	.asciz	"filename"
.Linfo_string146:
	.asciz	"loop"
.Linfo_string147:
	.asciz	"flag"
.Linfo_string148:
	.asciz	"tno"
.Linfo_string149:
	.asciz	"sa"
.Linfo_string150:
	.asciz	"addrlen"
.Linfo_string151:
	.asciz	"thehost"
.Linfo_string152:
	.asciz	"stringpos"
.Linfo_string153:
	.asciz	"directory"
.Linfo_string154:
	.asciz	"namelist"
.Linfo_string155:
	.asciz	"d_ino"
.Linfo_string156:
	.asciz	"__ino_t"
.Linfo_string157:
	.asciz	"d_off"
.Linfo_string158:
	.asciz	"d_reclen"
.Linfo_string159:
	.asciz	"d_type"
.Linfo_string160:
	.asciz	"d_name"
.Linfo_string161:
	.asciz	"dirent"
.Linfo_string162:
	.asciz	"n"
.Linfo_string163:
	.asciz	"size"
.Linfo_string164:
	.asciz	"dirheader"
.Linfo_string165:
	.asciz	"tempstring2"
.Linfo_string166:
	.asciz	"line"
.Linfo_string167:
	.asciz	"st"
.Linfo_string168:
	.asciz	"st_dev"
.Linfo_string169:
	.asciz	"__dev_t"
.Linfo_string170:
	.asciz	"st_ino"
.Linfo_string171:
	.asciz	"st_nlink"
.Linfo_string172:
	.asciz	"__nlink_t"
.Linfo_string173:
	.asciz	"st_mode"
.Linfo_string174:
	.asciz	"__mode_t"
.Linfo_string175:
	.asciz	"st_uid"
.Linfo_string176:
	.asciz	"st_gid"
.Linfo_string177:
	.asciz	"__pad0"
.Linfo_string178:
	.asciz	"st_rdev"
.Linfo_string179:
	.asciz	"st_size"
.Linfo_string180:
	.asciz	"st_blksize"
.Linfo_string181:
	.asciz	"__blksize_t"
.Linfo_string182:
	.asciz	"st_blocks"
.Linfo_string183:
	.asciz	"__blkcnt_t"
.Linfo_string184:
	.asciz	"st_atim"
.Linfo_string185:
	.asciz	"tv_nsec"
.Linfo_string186:
	.asciz	"__syscall_slong_t"
.Linfo_string187:
	.asciz	"timespec"
.Linfo_string188:
	.asciz	"st_mtim"
.Linfo_string189:
	.asciz	"st_ctim"
.Linfo_string190:
	.asciz	"__glibc_reserved"
.Linfo_string191:
	.asciz	"stat"
.Linfo_string192:
	.asciz	"count"
.Linfo_string193:
	.asciz	"ptr1"
.Linfo_string194:
	.asciz	"string1"
.Linfo_string195:
	.asciz	"string2"
.Linfo_string196:
	.asciz	"thevhost"
.Linfo_string197:
	.asciz	"string"
.Linfo_string198:
	.asciz	"format"
.Linfo_string199:
	.asciz	"logfile"
.Linfo_string200:
	.asciz	"t"
.Linfo_string201:
	.asciz	"time_t"
.Linfo_string202:
	.asciz	"tm"
.Linfo_string203:
	.asciz	"temp"
.Linfo_string204:
	.asciz	"temp2"
.Linfo_string205:
	.asciz	"logfilename"
.Linfo_string206:
	.asciz	"datetime"
.Linfo_string207:
	.asciz	"datetime_final"
.Linfo_string208:
	.asciz	"ap"
.Linfo_string209:
	.asciz	"gp_offset"
.Linfo_string210:
	.asciz	"fp_offset"
.Linfo_string211:
	.asciz	"overflow_arg_area"
.Linfo_string212:
	.asciz	"reg_save_area"
.Linfo_string213:
	.asciz	"__va_list_tag"
.Linfo_string214:
	.asciz	"__builtin_va_list"
.Linfo_string215:
	.asciz	"__gnuc_va_list"
.Linfo_string216:
	.asciz	"va_list"
	.section	.debug_info,"",@progbits
.L.debug_info_begin0:
	.long	1272                    # Length of Unit
	.short	4                       # DWARF version number
	.long	.L.debug_abbrev_begin   # Offset Into Abbrev. Section
	.byte	8                       # Address Size (in bytes)
	.byte	1                       # Abbrev [1] 0xb:0x4f1 DW_TAG_compile_unit
	.long	.Linfo_string0          # DW_AT_producer
	.short	12                      # DW_AT_language
	.long	.Linfo_string1          # DW_AT_name
	.quad	0                       # DW_AT_low_pc
	.long	.Lsection_line          # DW_AT_stmt_list
	.long	.Linfo_string2          # DW_AT_comp_dir
	.byte	2                       # Abbrev [2] 0x26:0x15 DW_TAG_variable
	.long	.Linfo_string3          # DW_AT_name
	.long	59                      # DW_AT_type
                                        # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	40                      # DW_AT_decl_line
	.byte	9                       # DW_AT_location
	.byte	3
	.quad	no_vhosts
	.byte	3                       # Abbrev [3] 0x3b:0x7 DW_TAG_base_type
	.long	.Linfo_string4          # DW_AT_name
	.byte	7                       # DW_AT_encoding
	.byte	8                       # DW_AT_byte_size
	.byte	2                       # Abbrev [2] 0x42:0x15 DW_TAG_variable
	.long	.Linfo_string5          # DW_AT_name
	.long	87                      # DW_AT_type
                                        # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	41                      # DW_AT_decl_line
	.byte	9                       # DW_AT_location
	.byte	3
	.quad	vhosts
	.byte	4                       # Abbrev [4] 0x57:0x5 DW_TAG_pointer_type
	.long	92                      # DW_AT_type
	.byte	5                       # Abbrev [5] 0x5c:0xb DW_TAG_typedef
	.long	103                     # DW_AT_type
	.long	.Linfo_string13         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	30                      # DW_AT_decl_line
	.byte	6                       # Abbrev [6] 0x67:0x4a DW_TAG_structure_type
	.short	1275                    # DW_AT_byte_size
	.byte	2                       # DW_AT_decl_file
	.byte	23                      # DW_AT_decl_line
	.byte	7                       # Abbrev [7] 0x6c:0xd DW_TAG_member
	.long	.Linfo_string6          # DW_AT_name
	.long	177                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	25                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x79:0xd DW_TAG_member
	.long	.Linfo_string9          # DW_AT_name
	.long	177                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	26                      # DW_AT_decl_line
	.byte	255                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	8                       # Abbrev [8] 0x86:0xe DW_TAG_member
	.long	.Linfo_string10         # DW_AT_name
	.long	177                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	27                      # DW_AT_decl_line
	.short	510                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	8                       # Abbrev [8] 0x94:0xe DW_TAG_member
	.long	.Linfo_string11         # DW_AT_name
	.long	177                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	28                      # DW_AT_decl_line
	.short	765                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	8                       # Abbrev [8] 0xa2:0xe DW_TAG_member
	.long	.Linfo_string12         # DW_AT_name
	.long	177                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	29                      # DW_AT_decl_line
	.short	1020                    # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	9                       # Abbrev [9] 0xb1:0xc DW_TAG_array_type
	.long	189                     # DW_AT_type
	.byte	10                      # Abbrev [10] 0xb6:0x6 DW_TAG_subrange_type
	.long	196                     # DW_AT_type
	.byte	254                     # DW_AT_upper_bound
	.byte	0                       # End Of Children Mark
	.byte	3                       # Abbrev [3] 0xbd:0x7 DW_TAG_base_type
	.long	.Linfo_string7          # DW_AT_name
	.byte	6                       # DW_AT_encoding
	.byte	1                       # DW_AT_byte_size
	.byte	11                      # Abbrev [11] 0xc4:0x7 DW_TAG_base_type
	.long	.Linfo_string8          # DW_AT_name
	.byte	4                       # DW_AT_byte_size
	.byte	5                       # DW_AT_encoding
	.byte	2                       # Abbrev [2] 0xcb:0x15 DW_TAG_variable
	.long	.Linfo_string14         # DW_AT_name
	.long	224                     # DW_AT_type
                                        # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	43                      # DW_AT_decl_line
	.byte	9                       # DW_AT_location
	.byte	3
	.quad	SERVERPORT
	.byte	3                       # Abbrev [3] 0xe0:0x7 DW_TAG_base_type
	.long	.Linfo_string15         # DW_AT_name
	.byte	7                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	2                       # Abbrev [2] 0xe7:0x15 DW_TAG_variable
	.long	.Linfo_string16         # DW_AT_name
	.long	177                     # DW_AT_type
                                        # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	44                      # DW_AT_decl_line
	.byte	9                       # DW_AT_location
	.byte	3
	.quad	SERVERTYPE
	.byte	2                       # Abbrev [2] 0xfc:0x15 DW_TAG_variable
	.long	.Linfo_string17         # DW_AT_name
	.long	177                     # DW_AT_type
                                        # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	45                      # DW_AT_decl_line
	.byte	9                       # DW_AT_location
	.byte	3
	.quad	SERVERROOT
	.byte	2                       # Abbrev [2] 0x111:0x15 DW_TAG_variable
	.long	.Linfo_string18         # DW_AT_name
	.long	92                      # DW_AT_type
                                        # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	47                      # DW_AT_decl_line
	.byte	9                       # DW_AT_location
	.byte	3
	.quad	defaulthost
	.byte	12                      # Abbrev [12] 0x126:0x175 DW_TAG_subprogram
	.long	.Linfo_string19         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	49                      # DW_AT_decl_line
	.long	667                     # DW_AT_type
                                        # DW_AT_external
	.quad	.Lfunc_begin0           # DW_AT_low_pc
	.quad	.Lfunc_end0             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.byte	13                      # Abbrev [13] 0x143:0xe DW_TAG_variable
	.long	.Linfo_string49         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	51                      # DW_AT_decl_line
	.long	667                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	96
	.byte	13                      # Abbrev [13] 0x151:0xe DW_TAG_variable
	.long	.Linfo_string50         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	51                      # DW_AT_decl_line
	.long	667                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	92
	.byte	13                      # Abbrev [13] 0x15f:0xe DW_TAG_variable
	.long	.Linfo_string51         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	51                      # DW_AT_decl_line
	.long	667                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	88
	.byte	13                      # Abbrev [13] 0x16d:0xe DW_TAG_variable
	.long	.Linfo_string52         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	51                      # DW_AT_decl_line
	.long	667                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	84
	.byte	13                      # Abbrev [13] 0x17b:0xe DW_TAG_variable
	.long	.Linfo_string53         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	52                      # DW_AT_decl_line
	.long	852                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	64
	.byte	13                      # Abbrev [13] 0x189:0xf DW_TAG_variable
	.long	.Linfo_string68         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	53                      # DW_AT_decl_line
	.long	852                     # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\260\177"
	.byte	13                      # Abbrev [13] 0x198:0xf DW_TAG_variable
	.long	.Linfo_string69         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	54                      # DW_AT_decl_line
	.long	667                     # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\254\177"
	.byte	13                      # Abbrev [13] 0x1a7:0xf DW_TAG_variable
	.long	.Linfo_string70         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	54                      # DW_AT_decl_line
	.long	667                     # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\250\177"
	.byte	13                      # Abbrev [13] 0x1b6:0xf DW_TAG_variable
	.long	.Linfo_string71         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	55                      # DW_AT_decl_line
	.long	1016                    # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\230\177"
	.byte	13                      # Abbrev [13] 0x1c5:0xf DW_TAG_variable
	.long	.Linfo_string78         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	56                      # DW_AT_decl_line
	.long	1080                    # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\230~"
	.byte	13                      # Abbrev [13] 0x1d4:0xf DW_TAG_variable
	.long	.Linfo_string82         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	56                      # DW_AT_decl_line
	.long	1080                    # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\230}"
	.byte	13                      # Abbrev [13] 0x1e3:0xf DW_TAG_variable
	.long	.Linfo_string83         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	57                      # DW_AT_decl_line
	.long	1132                    # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\220}"
	.byte	14                      # Abbrev [14] 0x1f2:0xa8 DW_TAG_lexical_block
	.quad	.Ltmp21                 # DW_AT_low_pc
	.quad	.Ltmp36                 # DW_AT_high_pc
	.byte	14                      # Abbrev [14] 0x203:0x96 DW_TAG_lexical_block
	.quad	.Ltmp23                 # DW_AT_low_pc
	.quad	.Ltmp36                 # DW_AT_high_pc
	.byte	14                      # Abbrev [14] 0x214:0x84 DW_TAG_lexical_block
	.quad	.Ltmp24                 # DW_AT_low_pc
	.quad	.Ltmp36                 # DW_AT_high_pc
	.byte	14                      # Abbrev [14] 0x225:0x72 DW_TAG_lexical_block
	.quad	.Ltmp24                 # DW_AT_low_pc
	.quad	.Ltmp35                 # DW_AT_high_pc
	.byte	14                      # Abbrev [14] 0x236:0x30 DW_TAG_lexical_block
	.quad	.Ltmp26                 # DW_AT_low_pc
	.quad	.Ltmp27                 # DW_AT_high_pc
	.byte	13                      # Abbrev [13] 0x247:0xf DW_TAG_variable
	.long	.Linfo_string94         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	161                     # DW_AT_decl_line
	.long	667                     # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\374|"
	.byte	13                      # Abbrev [13] 0x256:0xf DW_TAG_variable
	.long	.Linfo_string95         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	161                     # DW_AT_decl_line
	.long	667                     # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\370|"
	.byte	0                       # End Of Children Mark
	.byte	14                      # Abbrev [14] 0x266:0x30 DW_TAG_lexical_block
	.quad	.Ltmp29                 # DW_AT_low_pc
	.quad	.Ltmp30                 # DW_AT_high_pc
	.byte	13                      # Abbrev [13] 0x277:0xf DW_TAG_variable
	.long	.Linfo_string94         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	163                     # DW_AT_decl_line
	.long	667                     # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\364|"
	.byte	13                      # Abbrev [13] 0x286:0xf DW_TAG_variable
	.long	.Linfo_string95         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	163                     # DW_AT_decl_line
	.long	667                     # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\360|"
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	3                       # Abbrev [3] 0x29b:0x7 DW_TAG_base_type
	.long	.Linfo_string8          # DW_AT_name
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	12                      # Abbrev [12] 0x2a2:0x48 DW_TAG_subprogram
	.long	.Linfo_string20         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	197                     # DW_AT_decl_line
	.long	667                     # DW_AT_type
                                        # DW_AT_external
	.quad	.Lfunc_begin2           # DW_AT_low_pc
	.quad	.Lfunc_end2             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.byte	13                      # Abbrev [13] 0x2bf:0xe DW_TAG_variable
	.long	.Linfo_string68         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	199                     # DW_AT_decl_line
	.long	852                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	112
	.byte	13                      # Abbrev [13] 0x2cd:0xe DW_TAG_variable
	.long	.Linfo_string97         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	200                     # DW_AT_decl_line
	.long	1264                    # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	104
	.byte	13                      # Abbrev [13] 0x2db:0xe DW_TAG_variable
	.long	.Linfo_string83         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	201                     # DW_AT_decl_line
	.long	1132                    # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	96
	.byte	0                       # End Of Children Mark
	.byte	15                      # Abbrev [15] 0x2ea:0x28 DW_TAG_subprogram
	.long	.Linfo_string21         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	222                     # DW_AT_decl_line
                                        # DW_AT_prototyped
                                        # DW_AT_external
	.quad	.Lfunc_begin1           # DW_AT_low_pc
	.quad	.Lfunc_end1             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.byte	16                      # Abbrev [16] 0x303:0xe DW_TAG_formal_parameter
	.long	.Linfo_string96         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	222                     # DW_AT_decl_line
	.long	667                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	124
	.byte	0                       # End Of Children Mark
	.byte	17                      # Abbrev [17] 0x312:0x42 DW_TAG_enumeration_type
	.long	.Linfo_string31         # DW_AT_name
	.byte	4                       # DW_AT_byte_size
	.byte	3                       # DW_AT_decl_file
	.byte	24                      # DW_AT_decl_line
	.byte	18                      # Abbrev [18] 0x31a:0x6 DW_TAG_enumerator
	.long	.Linfo_string22         # DW_AT_name
	.byte	1                       # DW_AT_const_value
	.byte	18                      # Abbrev [18] 0x320:0x6 DW_TAG_enumerator
	.long	.Linfo_string23         # DW_AT_name
	.byte	2                       # DW_AT_const_value
	.byte	18                      # Abbrev [18] 0x326:0x6 DW_TAG_enumerator
	.long	.Linfo_string24         # DW_AT_name
	.byte	3                       # DW_AT_const_value
	.byte	18                      # Abbrev [18] 0x32c:0x6 DW_TAG_enumerator
	.long	.Linfo_string25         # DW_AT_name
	.byte	4                       # DW_AT_const_value
	.byte	18                      # Abbrev [18] 0x332:0x6 DW_TAG_enumerator
	.long	.Linfo_string26         # DW_AT_name
	.byte	5                       # DW_AT_const_value
	.byte	18                      # Abbrev [18] 0x338:0x6 DW_TAG_enumerator
	.long	.Linfo_string27         # DW_AT_name
	.byte	6                       # DW_AT_const_value
	.byte	18                      # Abbrev [18] 0x33e:0x6 DW_TAG_enumerator
	.long	.Linfo_string28         # DW_AT_name
	.byte	10                      # DW_AT_const_value
	.byte	18                      # Abbrev [18] 0x344:0x8 DW_TAG_enumerator
	.long	.Linfo_string29         # DW_AT_name
	.ascii	"\200\200 "             # DW_AT_const_value
	.byte	18                      # Abbrev [18] 0x34c:0x7 DW_TAG_enumerator
	.long	.Linfo_string30         # DW_AT_name
	.ascii	"\200\020"              # DW_AT_const_value
	.byte	0                       # End Of Children Mark
	.byte	19                      # Abbrev [19] 0x354:0x3d DW_TAG_structure_type
	.long	.Linfo_string67         # DW_AT_name
	.byte	16                      # DW_AT_byte_size
	.byte	6                       # DW_AT_decl_file
	.byte	237                     # DW_AT_decl_line
	.byte	7                       # Abbrev [7] 0x35c:0xd DW_TAG_member
	.long	.Linfo_string54         # DW_AT_name
	.long	913                     # DW_AT_type
	.byte	6                       # DW_AT_decl_file
	.byte	239                     # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x369:0xd DW_TAG_member
	.long	.Linfo_string57         # DW_AT_name
	.long	931                     # DW_AT_type
	.byte	6                       # DW_AT_decl_file
	.byte	240                     # DW_AT_decl_line
	.byte	2                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x376:0xd DW_TAG_member
	.long	.Linfo_string60         # DW_AT_name
	.long	953                     # DW_AT_type
	.byte	6                       # DW_AT_decl_file
	.byte	241                     # DW_AT_decl_line
	.byte	4                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x383:0xd DW_TAG_member
	.long	.Linfo_string65         # DW_AT_name
	.long	997                     # DW_AT_type
	.byte	6                       # DW_AT_decl_file
	.byte	244                     # DW_AT_decl_line
	.byte	8                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x391:0xb DW_TAG_typedef
	.long	924                     # DW_AT_type
	.long	.Linfo_string56         # DW_AT_name
	.byte	6                       # DW_AT_decl_file
	.byte	28                      # DW_AT_decl_line
	.byte	3                       # Abbrev [3] 0x39c:0x7 DW_TAG_base_type
	.long	.Linfo_string55         # DW_AT_name
	.byte	7                       # DW_AT_encoding
	.byte	2                       # DW_AT_byte_size
	.byte	5                       # Abbrev [5] 0x3a3:0xb DW_TAG_typedef
	.long	942                     # DW_AT_type
	.long	.Linfo_string59         # DW_AT_name
	.byte	6                       # DW_AT_decl_file
	.byte	117                     # DW_AT_decl_line
	.byte	5                       # Abbrev [5] 0x3ae:0xb DW_TAG_typedef
	.long	924                     # DW_AT_type
	.long	.Linfo_string58         # DW_AT_name
	.byte	6                       # DW_AT_decl_file
	.byte	49                      # DW_AT_decl_line
	.byte	19                      # Abbrev [19] 0x3b9:0x16 DW_TAG_structure_type
	.long	.Linfo_string64         # DW_AT_name
	.byte	4                       # DW_AT_byte_size
	.byte	6                       # DW_AT_decl_file
	.byte	31                      # DW_AT_decl_line
	.byte	7                       # Abbrev [7] 0x3c1:0xd DW_TAG_member
	.long	.Linfo_string61         # DW_AT_name
	.long	975                     # DW_AT_type
	.byte	6                       # DW_AT_decl_file
	.byte	33                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x3cf:0xb DW_TAG_typedef
	.long	986                     # DW_AT_type
	.long	.Linfo_string63         # DW_AT_name
	.byte	6                       # DW_AT_decl_file
	.byte	30                      # DW_AT_decl_line
	.byte	5                       # Abbrev [5] 0x3da:0xb DW_TAG_typedef
	.long	224                     # DW_AT_type
	.long	.Linfo_string62         # DW_AT_name
	.byte	6                       # DW_AT_decl_file
	.byte	51                      # DW_AT_decl_line
	.byte	9                       # Abbrev [9] 0x3e5:0xc DW_TAG_array_type
	.long	1009                    # DW_AT_type
	.byte	10                      # Abbrev [10] 0x3ea:0x6 DW_TAG_subrange_type
	.long	196                     # DW_AT_type
	.byte	7                       # DW_AT_upper_bound
	.byte	0                       # End Of Children Mark
	.byte	3                       # Abbrev [3] 0x3f1:0x7 DW_TAG_base_type
	.long	.Linfo_string66         # DW_AT_name
	.byte	8                       # DW_AT_encoding
	.byte	1                       # DW_AT_byte_size
	.byte	19                      # Abbrev [19] 0x3f8:0x23 DW_TAG_structure_type
	.long	.Linfo_string77         # DW_AT_name
	.byte	16                      # DW_AT_byte_size
	.byte	7                       # DW_AT_decl_file
	.byte	30                      # DW_AT_decl_line
	.byte	7                       # Abbrev [7] 0x400:0xd DW_TAG_member
	.long	.Linfo_string72         # DW_AT_name
	.long	1051                    # DW_AT_type
	.byte	7                       # DW_AT_decl_file
	.byte	32                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x40d:0xd DW_TAG_member
	.long	.Linfo_string75         # DW_AT_name
	.long	1069                    # DW_AT_type
	.byte	7                       # DW_AT_decl_file
	.byte	33                      # DW_AT_decl_line
	.byte	8                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x41b:0xb DW_TAG_typedef
	.long	1062                    # DW_AT_type
	.long	.Linfo_string74         # DW_AT_name
	.byte	7                       # DW_AT_decl_file
	.byte	139                     # DW_AT_decl_line
	.byte	3                       # Abbrev [3] 0x426:0x7 DW_TAG_base_type
	.long	.Linfo_string73         # DW_AT_name
	.byte	5                       # DW_AT_encoding
	.byte	8                       # DW_AT_byte_size
	.byte	5                       # Abbrev [5] 0x42d:0xb DW_TAG_typedef
	.long	1062                    # DW_AT_type
	.long	.Linfo_string76         # DW_AT_name
	.byte	7                       # DW_AT_decl_file
	.byte	141                     # DW_AT_decl_line
	.byte	5                       # Abbrev [5] 0x438:0xb DW_TAG_typedef
	.long	1091                    # DW_AT_type
	.long	.Linfo_string81         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	75                      # DW_AT_decl_line
	.byte	20                      # Abbrev [20] 0x443:0x12 DW_TAG_structure_type
	.byte	128                     # DW_AT_byte_size
	.byte	8                       # DW_AT_decl_file
	.byte	64                      # DW_AT_decl_line
	.byte	7                       # Abbrev [7] 0x447:0xd DW_TAG_member
	.long	.Linfo_string79         # DW_AT_name
	.long	1109                    # DW_AT_type
	.byte	8                       # DW_AT_decl_file
	.byte	69                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	9                       # Abbrev [9] 0x455:0xc DW_TAG_array_type
	.long	1121                    # DW_AT_type
	.byte	10                      # Abbrev [10] 0x45a:0x6 DW_TAG_subrange_type
	.long	196                     # DW_AT_type
	.byte	15                      # DW_AT_upper_bound
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x461:0xb DW_TAG_typedef
	.long	1062                    # DW_AT_type
	.long	.Linfo_string80         # DW_AT_name
	.byte	8                       # DW_AT_decl_file
	.byte	54                      # DW_AT_decl_line
	.byte	4                       # Abbrev [4] 0x46c:0x5 DW_TAG_pointer_type
	.long	1137                    # DW_AT_type
	.byte	19                      # Abbrev [19] 0x471:0x64 DW_TAG_structure_type
	.long	.Linfo_string93         # DW_AT_name
	.byte	48                      # DW_AT_byte_size
	.byte	9                       # DW_AT_decl_file
	.byte	49                      # DW_AT_decl_line
	.byte	7                       # Abbrev [7] 0x479:0xd DW_TAG_member
	.long	.Linfo_string84         # DW_AT_name
	.long	1237                    # DW_AT_type
	.byte	9                       # DW_AT_decl_file
	.byte	51                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x486:0xd DW_TAG_member
	.long	.Linfo_string85         # DW_AT_name
	.long	1237                    # DW_AT_type
	.byte	9                       # DW_AT_decl_file
	.byte	52                      # DW_AT_decl_line
	.byte	8                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x493:0xd DW_TAG_member
	.long	.Linfo_string86         # DW_AT_name
	.long	1242                    # DW_AT_type
	.byte	9                       # DW_AT_decl_file
	.byte	53                      # DW_AT_decl_line
	.byte	16                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x4a0:0xd DW_TAG_member
	.long	.Linfo_string88         # DW_AT_name
	.long	1253                    # DW_AT_type
	.byte	9                       # DW_AT_decl_file
	.byte	54                      # DW_AT_decl_line
	.byte	20                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x4ad:0xd DW_TAG_member
	.long	.Linfo_string90         # DW_AT_name
	.long	1237                    # DW_AT_type
	.byte	9                       # DW_AT_decl_file
	.byte	55                      # DW_AT_decl_line
	.byte	24                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x4ba:0xd DW_TAG_member
	.long	.Linfo_string91         # DW_AT_name
	.long	1237                    # DW_AT_type
	.byte	9                       # DW_AT_decl_file
	.byte	56                      # DW_AT_decl_line
	.byte	32                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x4c7:0xd DW_TAG_member
	.long	.Linfo_string92         # DW_AT_name
	.long	1237                    # DW_AT_type
	.byte	9                       # DW_AT_decl_file
	.byte	57                      # DW_AT_decl_line
	.byte	40                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0x4d5:0x5 DW_TAG_pointer_type
	.long	189                     # DW_AT_type
	.byte	5                       # Abbrev [5] 0x4da:0xb DW_TAG_typedef
	.long	224                     # DW_AT_type
	.long	.Linfo_string87         # DW_AT_name
	.byte	9                       # DW_AT_decl_file
	.byte	125                     # DW_AT_decl_line
	.byte	5                       # Abbrev [5] 0x4e5:0xb DW_TAG_typedef
	.long	224                     # DW_AT_type
	.long	.Linfo_string89         # DW_AT_name
	.byte	9                       # DW_AT_decl_file
	.byte	126                     # DW_AT_decl_line
	.byte	5                       # Abbrev [5] 0x4f0:0xb DW_TAG_typedef
	.long	59                      # DW_AT_type
	.long	.Linfo_string98         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	42                      # DW_AT_decl_line
	.byte	0                       # End Of Children Mark
.L.debug_info_end0:
.L.debug_info_begin1:
	.long	1588                    # Length of Unit
	.short	4                       # DWARF version number
	.long	.L.debug_abbrev_begin   # Offset Into Abbrev. Section
	.byte	8                       # Address Size (in bytes)
	.byte	1                       # Abbrev [1] 0xb:0x62d DW_TAG_compile_unit
	.long	.Linfo_string0          # DW_AT_producer
	.short	12                      # DW_AT_language
	.long	.Linfo_string32         # DW_AT_name
	.quad	0                       # DW_AT_low_pc
	.long	.Lsection_line          # DW_AT_stmt_list
	.long	.Linfo_string2          # DW_AT_comp_dir
	.byte	21                      # Abbrev [21] 0x26:0xcb DW_TAG_subprogram
	.long	.Linfo_string33         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.short	258                     # DW_AT_decl_line
                                        # DW_AT_prototyped
                                        # DW_AT_external
	.quad	.Lfunc_begin4           # DW_AT_low_pc
	.quad	.Lfunc_end4             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.byte	22                      # Abbrev [22] 0x40:0x16 DW_TAG_variable
	.long	.Linfo_string34         # DW_AT_name
	.long	241                     # DW_AT_type
	.byte	4                       # DW_AT_decl_file
	.short	266                     # DW_AT_decl_line
	.byte	9                       # DW_AT_location
	.byte	3
	.quad	showdir.dirfooter
	.byte	23                      # Abbrev [23] 0x56:0xf DW_TAG_formal_parameter
	.long	.Linfo_string153        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.short	258                     # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	96
	.byte	23                      # Abbrev [23] 0x65:0xf DW_TAG_formal_parameter
	.long	.Linfo_string50         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.short	258                     # DW_AT_decl_line
	.long	.Lsection_info+667      # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	92
	.byte	24                      # Abbrev [24] 0x74:0xf DW_TAG_formal_parameter
	.long	.Linfo_string151        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.short	258                     # DW_AT_decl_line
	.long	1380                    # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	80
	.byte	25                      # Abbrev [25] 0x83:0xf DW_TAG_variable
	.long	.Linfo_string154        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.short	260                     # DW_AT_decl_line
	.long	1470                    # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	72
	.byte	26                      # Abbrev [26] 0x92:0xf DW_TAG_variable
	.long	.Linfo_string162        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.short	261                     # DW_AT_decl_line
	.long	.Lsection_info+667      # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	68
	.byte	26                      # Abbrev [26] 0xa1:0xf DW_TAG_variable
	.long	.Linfo_string146        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.short	261                     # DW_AT_decl_line
	.long	.Lsection_info+667      # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	64
	.byte	26                      # Abbrev [26] 0xb0:0x10 DW_TAG_variable
	.long	.Linfo_string163        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.short	262                     # DW_AT_decl_line
	.long	.Lsection_info+59       # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\270\177"
	.byte	25                      # Abbrev [25] 0xc0:0x10 DW_TAG_variable
	.long	.Linfo_string99         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.short	263                     # DW_AT_decl_line
	.long	724                     # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\260\177"
	.byte	26                      # Abbrev [26] 0xd0:0x10 DW_TAG_variable
	.long	.Linfo_string143        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.short	264                     # DW_AT_decl_line
	.long	.Lsection_info+177      # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\260}"
	.byte	25                      # Abbrev [25] 0xe0:0x10 DW_TAG_variable
	.long	.Linfo_string164        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.short	265                     # DW_AT_decl_line
	.long	1578                    # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\260m"
	.byte	0                       # End Of Children Mark
	.byte	9                       # Abbrev [9] 0xf1:0xc DW_TAG_array_type
	.long	253                     # DW_AT_type
	.byte	10                      # Abbrev [10] 0xf6:0x6 DW_TAG_subrange_type
	.long	258                     # DW_AT_type
	.byte	190                     # DW_AT_upper_bound
	.byte	0                       # End Of Children Mark
	.byte	27                      # Abbrev [27] 0xfd:0x5 DW_TAG_const_type
	.long	.Lsection_info+189      # DW_AT_type
	.byte	11                      # Abbrev [11] 0x102:0x7 DW_TAG_base_type
	.long	.Linfo_string8          # DW_AT_name
	.byte	4                       # DW_AT_byte_size
	.byte	5                       # DW_AT_encoding
	.byte	28                      # Abbrev [28] 0x109:0x16 DW_TAG_variable
	.long	.Linfo_string35         # DW_AT_name
	.long	287                     # DW_AT_type
                                        # DW_AT_external
	.byte	4                       # DW_AT_decl_file
	.short	295                     # DW_AT_decl_line
	.byte	9                       # DW_AT_location
	.byte	3
	.quad	assocNames
	.byte	29                      # Abbrev [29] 0x11f:0x18 DW_TAG_array_type
	.long	.Lsection_info+189      # DW_AT_type
	.byte	10                      # Abbrev [10] 0x124:0x6 DW_TAG_subrange_type
	.long	258                     # DW_AT_type
	.byte	31                      # DW_AT_upper_bound
	.byte	10                      # Abbrev [10] 0x12a:0x6 DW_TAG_subrange_type
	.long	258                     # DW_AT_type
	.byte	1                       # DW_AT_upper_bound
	.byte	10                      # Abbrev [10] 0x130:0x6 DW_TAG_subrange_type
	.long	258                     # DW_AT_type
	.byte	99                      # DW_AT_upper_bound
	.byte	0                       # End Of Children Mark
	.byte	30                      # Abbrev [30] 0x137:0x13a DW_TAG_subprogram
	.long	.Linfo_string36         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	37                      # DW_AT_decl_line
                                        # DW_AT_prototyped
	.long	.Lsection_info+667      # DW_AT_type
                                        # DW_AT_external
	.quad	.Lfunc_begin3           # DW_AT_low_pc
	.quad	.Lfunc_end3             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.byte	31                      # Abbrev [31] 0x154:0xe DW_TAG_formal_parameter
	.long	.Linfo_string50         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	37                      # DW_AT_decl_line
	.long	.Lsection_info+667      # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	96
	.byte	13                      # Abbrev [13] 0x162:0xe DW_TAG_variable
	.long	.Linfo_string99         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	39                      # DW_AT_decl_line
	.long	724                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	88
	.byte	13                      # Abbrev [13] 0x170:0x10 DW_TAG_variable
	.long	.Linfo_string138        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	40                      # DW_AT_decl_line
	.long	1272                    # DW_AT_type
	.byte	4                       # DW_AT_location
	.byte	145
	.ascii	"\320\277\177"
	.byte	32                      # Abbrev [32] 0x180:0x10 DW_TAG_variable
	.long	.Linfo_string139        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	40                      # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	4                       # DW_AT_location
	.byte	145
	.ascii	"\310\277\177"
	.byte	32                      # Abbrev [32] 0x190:0x10 DW_TAG_variable
	.long	.Linfo_string140        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	40                      # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	4                       # DW_AT_location
	.byte	145
	.ascii	"\300\277\177"
	.byte	32                      # Abbrev [32] 0x1a0:0x10 DW_TAG_variable
	.long	.Linfo_string141        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	40                      # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	4                       # DW_AT_location
	.byte	145
	.ascii	"\270\277\177"
	.byte	32                      # Abbrev [32] 0x1b0:0x10 DW_TAG_variable
	.long	.Linfo_string142        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	40                      # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	4                       # DW_AT_location
	.byte	145
	.ascii	"\260\277\177"
	.byte	13                      # Abbrev [13] 0x1c0:0x10 DW_TAG_variable
	.long	.Linfo_string143        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	41                      # DW_AT_decl_line
	.long	1272                    # DW_AT_type
	.byte	4                       # DW_AT_location
	.byte	145
	.ascii	"\260\377~"
	.byte	13                      # Abbrev [13] 0x1d0:0x10 DW_TAG_variable
	.long	.Linfo_string144        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	41                      # DW_AT_decl_line
	.long	1285                    # DW_AT_type
	.byte	4                       # DW_AT_location
	.byte	145
	.ascii	"\360\376~"
	.byte	32                      # Abbrev [32] 0x1e0:0x10 DW_TAG_variable
	.long	.Linfo_string145        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	42                      # DW_AT_decl_line
	.long	.Lsection_info+177      # DW_AT_type
	.byte	4                       # DW_AT_location
	.byte	145
	.ascii	"\360\374~"
	.byte	32                      # Abbrev [32] 0x1f0:0x10 DW_TAG_variable
	.long	.Linfo_string146        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	43                      # DW_AT_decl_line
	.long	.Lsection_info+224      # DW_AT_type
	.byte	4                       # DW_AT_location
	.byte	145
	.ascii	"\354\374~"
	.byte	32                      # Abbrev [32] 0x200:0x10 DW_TAG_variable
	.long	.Linfo_string147        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	43                      # DW_AT_decl_line
	.long	.Lsection_info+224      # DW_AT_type
	.byte	4                       # DW_AT_location
	.byte	145
	.ascii	"\350\374~"
	.byte	32                      # Abbrev [32] 0x210:0x10 DW_TAG_variable
	.long	.Linfo_string52         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	44                      # DW_AT_decl_line
	.long	.Lsection_info+667      # DW_AT_type
	.byte	4                       # DW_AT_location
	.byte	145
	.ascii	"\344\374~"
	.byte	32                      # Abbrev [32] 0x220:0x10 DW_TAG_variable
	.long	.Linfo_string148        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	45                      # DW_AT_decl_line
	.long	.Lsection_info+667      # DW_AT_type
	.byte	4                       # DW_AT_location
	.byte	145
	.ascii	"\340\374~"
	.byte	13                      # Abbrev [13] 0x230:0x10 DW_TAG_variable
	.long	.Linfo_string149        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	46                      # DW_AT_decl_line
	.long	1297                    # DW_AT_type
	.byte	4                       # DW_AT_location
	.byte	145
	.ascii	"\320\374~"
	.byte	32                      # Abbrev [32] 0x240:0x10 DW_TAG_variable
	.long	.Linfo_string150        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	47                      # DW_AT_decl_line
	.long	.Lsection_info+667      # DW_AT_type
	.byte	4                       # DW_AT_location
	.byte	145
	.ascii	"\314\374~"
	.byte	13                      # Abbrev [13] 0x250:0x10 DW_TAG_variable
	.long	.Linfo_string151        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	48                      # DW_AT_decl_line
	.long	1380                    # DW_AT_type
	.byte	4                       # DW_AT_location
	.byte	145
	.ascii	"\300\374~"
	.byte	32                      # Abbrev [32] 0x260:0x10 DW_TAG_variable
	.long	.Linfo_string152        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	49                      # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	4                       # DW_AT_location
	.byte	145
	.ascii	"\270\374~"
	.byte	0                       # End Of Children Mark
	.byte	15                      # Abbrev [15] 0x271:0x63 DW_TAG_subprogram
	.long	.Linfo_string37         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	231                     # DW_AT_decl_line
                                        # DW_AT_prototyped
                                        # DW_AT_external
	.quad	.Lfunc_begin5           # DW_AT_low_pc
	.quad	.Lfunc_end5             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.byte	31                      # Abbrev [31] 0x28a:0xf DW_TAG_formal_parameter
	.long	.Linfo_string145        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	231                     # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	119
	.ascii	"\270\001"
	.byte	31                      # Abbrev [31] 0x299:0xf DW_TAG_formal_parameter
	.long	.Linfo_string144        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	231                     # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	119
	.ascii	"\260\001"
	.byte	13                      # Abbrev [13] 0x2a8:0xf DW_TAG_variable
	.long	.Linfo_string143        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	233                     # DW_AT_decl_line
	.long	1285                    # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	119
	.asciz	"\340"
	.byte	13                      # Abbrev [13] 0x2b7:0xe DW_TAG_variable
	.long	.Linfo_string165        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	234                     # DW_AT_decl_line
	.long	1285                    # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	119
	.byte	32
	.byte	32                      # Abbrev [32] 0x2c5:0xe DW_TAG_variable
	.long	.Linfo_string146        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	235                     # DW_AT_decl_line
	.long	.Lsection_info+224      # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	119
	.byte	28
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0x2d4:0x5 DW_TAG_pointer_type
	.long	729                     # DW_AT_type
	.byte	5                       # Abbrev [5] 0x2d9:0xb DW_TAG_typedef
	.long	740                     # DW_AT_type
	.long	.Linfo_string137        # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	48                      # DW_AT_decl_line
	.byte	19                      # Abbrev [19] 0x2e4:0x199 DW_TAG_structure_type
	.long	.Linfo_string136        # DW_AT_name
	.byte	216                     # DW_AT_byte_size
	.byte	10                      # DW_AT_decl_file
	.byte	245                     # DW_AT_decl_line
	.byte	33                      # Abbrev [33] 0x2ec:0xd DW_TAG_member
	.long	.Linfo_string100        # DW_AT_name
	.long	.Lsection_info+667      # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.byte	246                     # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x2f9:0xd DW_TAG_member
	.long	.Linfo_string101        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.byte	251                     # DW_AT_decl_line
	.byte	8                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x306:0xd DW_TAG_member
	.long	.Linfo_string102        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.byte	252                     # DW_AT_decl_line
	.byte	16                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x313:0xd DW_TAG_member
	.long	.Linfo_string103        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.byte	253                     # DW_AT_decl_line
	.byte	24                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x320:0xd DW_TAG_member
	.long	.Linfo_string104        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.byte	254                     # DW_AT_decl_line
	.byte	32                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x32d:0xd DW_TAG_member
	.long	.Linfo_string105        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.byte	255                     # DW_AT_decl_line
	.byte	40                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x33a:0xe DW_TAG_member
	.long	.Linfo_string106        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	256                     # DW_AT_decl_line
	.byte	48                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x348:0xe DW_TAG_member
	.long	.Linfo_string107        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	257                     # DW_AT_decl_line
	.byte	56                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x356:0xe DW_TAG_member
	.long	.Linfo_string108        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	258                     # DW_AT_decl_line
	.byte	64                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x364:0xe DW_TAG_member
	.long	.Linfo_string109        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	260                     # DW_AT_decl_line
	.byte	72                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x372:0xe DW_TAG_member
	.long	.Linfo_string110        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	261                     # DW_AT_decl_line
	.byte	80                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x380:0xe DW_TAG_member
	.long	.Linfo_string111        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	262                     # DW_AT_decl_line
	.byte	88                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	35                      # Abbrev [35] 0x38e:0xe DW_TAG_member
	.long	.Linfo_string112        # DW_AT_name
	.long	1149                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	264                     # DW_AT_decl_line
	.byte	96                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	35                      # Abbrev [35] 0x39c:0xe DW_TAG_member
	.long	.Linfo_string117        # DW_AT_name
	.long	1202                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	266                     # DW_AT_decl_line
	.byte	104                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x3aa:0xe DW_TAG_member
	.long	.Linfo_string118        # DW_AT_name
	.long	.Lsection_info+667      # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	268                     # DW_AT_decl_line
	.byte	112                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x3b8:0xe DW_TAG_member
	.long	.Linfo_string119        # DW_AT_name
	.long	.Lsection_info+667      # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	272                     # DW_AT_decl_line
	.byte	116                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	35                      # Abbrev [35] 0x3c6:0xe DW_TAG_member
	.long	.Linfo_string120        # DW_AT_name
	.long	1207                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	274                     # DW_AT_decl_line
	.byte	120                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x3d4:0xe DW_TAG_member
	.long	.Linfo_string122        # DW_AT_name
	.long	.Lsection_info+924      # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	278                     # DW_AT_decl_line
	.byte	128                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	35                      # Abbrev [35] 0x3e2:0xe DW_TAG_member
	.long	.Linfo_string123        # DW_AT_name
	.long	1218                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	279                     # DW_AT_decl_line
	.byte	130                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	35                      # Abbrev [35] 0x3f0:0xe DW_TAG_member
	.long	.Linfo_string125        # DW_AT_name
	.long	1225                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	280                     # DW_AT_decl_line
	.byte	131                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	35                      # Abbrev [35] 0x3fe:0xe DW_TAG_member
	.long	.Linfo_string126        # DW_AT_name
	.long	1237                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	284                     # DW_AT_decl_line
	.byte	136                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	35                      # Abbrev [35] 0x40c:0xe DW_TAG_member
	.long	.Linfo_string127        # DW_AT_name
	.long	1238                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	293                     # DW_AT_decl_line
	.byte	144                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	35                      # Abbrev [35] 0x41a:0xe DW_TAG_member
	.long	.Linfo_string129        # DW_AT_name
	.long	1237                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	302                     # DW_AT_decl_line
	.byte	152                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	35                      # Abbrev [35] 0x428:0xe DW_TAG_member
	.long	.Linfo_string130        # DW_AT_name
	.long	1237                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	303                     # DW_AT_decl_line
	.byte	160                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	35                      # Abbrev [35] 0x436:0xe DW_TAG_member
	.long	.Linfo_string131        # DW_AT_name
	.long	1237                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	304                     # DW_AT_decl_line
	.byte	168                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	35                      # Abbrev [35] 0x444:0xe DW_TAG_member
	.long	.Linfo_string132        # DW_AT_name
	.long	1237                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	305                     # DW_AT_decl_line
	.byte	176                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	35                      # Abbrev [35] 0x452:0xe DW_TAG_member
	.long	.Linfo_string133        # DW_AT_name
	.long	1249                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	306                     # DW_AT_decl_line
	.byte	184                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x460:0xe DW_TAG_member
	.long	.Linfo_string134        # DW_AT_name
	.long	.Lsection_info+667      # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	308                     # DW_AT_decl_line
	.byte	192                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	35                      # Abbrev [35] 0x46e:0xe DW_TAG_member
	.long	.Linfo_string135        # DW_AT_name
	.long	1260                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	310                     # DW_AT_decl_line
	.byte	196                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0x47d:0x5 DW_TAG_pointer_type
	.long	1154                    # DW_AT_type
	.byte	19                      # Abbrev [19] 0x482:0x30 DW_TAG_structure_type
	.long	.Linfo_string116        # DW_AT_name
	.byte	24                      # DW_AT_byte_size
	.byte	10                      # DW_AT_decl_file
	.byte	160                     # DW_AT_decl_line
	.byte	7                       # Abbrev [7] 0x48a:0xd DW_TAG_member
	.long	.Linfo_string113        # DW_AT_name
	.long	1149                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.byte	161                     # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x497:0xd DW_TAG_member
	.long	.Linfo_string114        # DW_AT_name
	.long	1202                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.byte	162                     # DW_AT_decl_line
	.byte	8                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x4a4:0xd DW_TAG_member
	.long	.Linfo_string115        # DW_AT_name
	.long	.Lsection_info+667      # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.byte	166                     # DW_AT_decl_line
	.byte	16                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0x4b2:0x5 DW_TAG_pointer_type
	.long	740                     # DW_AT_type
	.byte	36                      # Abbrev [36] 0x4b7:0xb DW_TAG_typedef
	.long	.Lsection_info+1062     # DW_AT_type
	.long	.Linfo_string121        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	131                     # DW_AT_decl_line
	.byte	3                       # Abbrev [3] 0x4c2:0x7 DW_TAG_base_type
	.long	.Linfo_string124        # DW_AT_name
	.byte	6                       # DW_AT_encoding
	.byte	1                       # DW_AT_byte_size
	.byte	29                      # Abbrev [29] 0x4c9:0xc DW_TAG_array_type
	.long	.Lsection_info+189      # DW_AT_type
	.byte	10                      # Abbrev [10] 0x4ce:0x6 DW_TAG_subrange_type
	.long	258                     # DW_AT_type
	.byte	0                       # DW_AT_upper_bound
	.byte	0                       # End Of Children Mark
	.byte	37                      # Abbrev [37] 0x4d5:0x1 DW_TAG_pointer_type
	.byte	36                      # Abbrev [36] 0x4d6:0xb DW_TAG_typedef
	.long	.Lsection_info+1062     # DW_AT_type
	.long	.Linfo_string128        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	132                     # DW_AT_decl_line
	.byte	36                      # Abbrev [36] 0x4e1:0xb DW_TAG_typedef
	.long	.Lsection_info+59       # DW_AT_type
	.long	.Linfo_string98         # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	42                      # DW_AT_decl_line
	.byte	29                      # Abbrev [29] 0x4ec:0xc DW_TAG_array_type
	.long	.Lsection_info+189      # DW_AT_type
	.byte	10                      # Abbrev [10] 0x4f1:0x6 DW_TAG_subrange_type
	.long	258                     # DW_AT_type
	.byte	19                      # DW_AT_upper_bound
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x4f8:0xd DW_TAG_array_type
	.long	.Lsection_info+189      # DW_AT_type
	.byte	38                      # Abbrev [38] 0x4fd:0x7 DW_TAG_subrange_type
	.long	258                     # DW_AT_type
	.short	8191                    # DW_AT_upper_bound
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x505:0xc DW_TAG_array_type
	.long	.Lsection_info+189      # DW_AT_type
	.byte	10                      # Abbrev [10] 0x50a:0x6 DW_TAG_subrange_type
	.long	258                     # DW_AT_type
	.byte	49                      # DW_AT_upper_bound
	.byte	0                       # End Of Children Mark
	.byte	19                      # Abbrev [19] 0x511:0x3d DW_TAG_structure_type
	.long	.Linfo_string67         # DW_AT_name
	.byte	16                      # DW_AT_byte_size
	.byte	6                       # DW_AT_decl_file
	.byte	237                     # DW_AT_decl_line
	.byte	33                      # Abbrev [33] 0x519:0xd DW_TAG_member
	.long	.Linfo_string54         # DW_AT_name
	.long	.Lsection_info+913      # DW_AT_type
	.byte	6                       # DW_AT_decl_file
	.byte	239                     # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x526:0xd DW_TAG_member
	.long	.Linfo_string57         # DW_AT_name
	.long	.Lsection_info+931      # DW_AT_type
	.byte	6                       # DW_AT_decl_file
	.byte	240                     # DW_AT_decl_line
	.byte	2                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x533:0xd DW_TAG_member
	.long	.Linfo_string60         # DW_AT_name
	.long	1358                    # DW_AT_type
	.byte	6                       # DW_AT_decl_file
	.byte	241                     # DW_AT_decl_line
	.byte	4                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x540:0xd DW_TAG_member
	.long	.Linfo_string65         # DW_AT_name
	.long	.Lsection_info+997      # DW_AT_type
	.byte	6                       # DW_AT_decl_file
	.byte	244                     # DW_AT_decl_line
	.byte	8                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	19                      # Abbrev [19] 0x54e:0x16 DW_TAG_structure_type
	.long	.Linfo_string64         # DW_AT_name
	.byte	4                       # DW_AT_byte_size
	.byte	6                       # DW_AT_decl_file
	.byte	31                      # DW_AT_decl_line
	.byte	33                      # Abbrev [33] 0x556:0xd DW_TAG_member
	.long	.Linfo_string61         # DW_AT_name
	.long	.Lsection_info+975      # DW_AT_type
	.byte	6                       # DW_AT_decl_file
	.byte	33                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0x564:0x5 DW_TAG_pointer_type
	.long	1385                    # DW_AT_type
	.byte	5                       # Abbrev [5] 0x569:0xb DW_TAG_typedef
	.long	1396                    # DW_AT_type
	.long	.Linfo_string13         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	30                      # DW_AT_decl_line
	.byte	6                       # Abbrev [6] 0x574:0x4a DW_TAG_structure_type
	.short	1275                    # DW_AT_byte_size
	.byte	2                       # DW_AT_decl_file
	.byte	23                      # DW_AT_decl_line
	.byte	33                      # Abbrev [33] 0x579:0xd DW_TAG_member
	.long	.Linfo_string6          # DW_AT_name
	.long	.Lsection_info+177      # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	25                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x586:0xd DW_TAG_member
	.long	.Linfo_string9          # DW_AT_name
	.long	.Lsection_info+177      # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	26                      # DW_AT_decl_line
	.byte	255                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	39                      # Abbrev [39] 0x593:0xe DW_TAG_member
	.long	.Linfo_string10         # DW_AT_name
	.long	.Lsection_info+177      # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	27                      # DW_AT_decl_line
	.short	510                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	39                      # Abbrev [39] 0x5a1:0xe DW_TAG_member
	.long	.Linfo_string11         # DW_AT_name
	.long	.Lsection_info+177      # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	28                      # DW_AT_decl_line
	.short	765                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	39                      # Abbrev [39] 0x5af:0xe DW_TAG_member
	.long	.Linfo_string12         # DW_AT_name
	.long	.Lsection_info+177      # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	29                      # DW_AT_decl_line
	.short	1020                    # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0x5be:0x5 DW_TAG_pointer_type
	.long	1475                    # DW_AT_type
	.byte	4                       # Abbrev [4] 0x5c3:0x5 DW_TAG_pointer_type
	.long	1480                    # DW_AT_type
	.byte	40                      # Abbrev [40] 0x5c8:0x4b DW_TAG_structure_type
	.long	.Linfo_string161        # DW_AT_name
	.short	280                     # DW_AT_byte_size
	.byte	11                      # DW_AT_decl_file
	.byte	22                      # DW_AT_decl_line
	.byte	7                       # Abbrev [7] 0x5d1:0xd DW_TAG_member
	.long	.Linfo_string155        # DW_AT_name
	.long	1555                    # DW_AT_type
	.byte	11                      # DW_AT_decl_file
	.byte	25                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x5de:0xd DW_TAG_member
	.long	.Linfo_string157        # DW_AT_name
	.long	1207                    # DW_AT_type
	.byte	11                      # DW_AT_decl_file
	.byte	26                      # DW_AT_decl_line
	.byte	8                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x5eb:0xd DW_TAG_member
	.long	.Linfo_string158        # DW_AT_name
	.long	.Lsection_info+924      # DW_AT_type
	.byte	11                      # DW_AT_decl_file
	.byte	31                      # DW_AT_decl_line
	.byte	16                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x5f8:0xd DW_TAG_member
	.long	.Linfo_string159        # DW_AT_name
	.long	.Lsection_info+1009     # DW_AT_type
	.byte	11                      # DW_AT_decl_file
	.byte	32                      # DW_AT_decl_line
	.byte	18                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x605:0xd DW_TAG_member
	.long	.Linfo_string160        # DW_AT_name
	.long	1566                    # DW_AT_type
	.byte	11                      # DW_AT_decl_file
	.byte	33                      # DW_AT_decl_line
	.byte	19                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	36                      # Abbrev [36] 0x613:0xb DW_TAG_typedef
	.long	.Lsection_info+59       # DW_AT_type
	.long	.Linfo_string156        # DW_AT_name
	.byte	11                      # DW_AT_decl_file
	.byte	127                     # DW_AT_decl_line
	.byte	29                      # Abbrev [29] 0x61e:0xc DW_TAG_array_type
	.long	.Lsection_info+189      # DW_AT_type
	.byte	10                      # Abbrev [10] 0x623:0x6 DW_TAG_subrange_type
	.long	258                     # DW_AT_type
	.byte	255                     # DW_AT_upper_bound
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x62a:0xd DW_TAG_array_type
	.long	.Lsection_info+189      # DW_AT_type
	.byte	38                      # Abbrev [38] 0x62f:0x7 DW_TAG_subrange_type
	.long	258                     # DW_AT_type
	.short	2047                    # DW_AT_upper_bound
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
.L.debug_info_end1:
.L.debug_info_begin2:
	.long	1971                    # Length of Unit
	.short	4                       # DWARF version number
	.long	.L.debug_abbrev_begin   # Offset Into Abbrev. Section
	.byte	8                       # Address Size (in bytes)
	.byte	1                       # Abbrev [1] 0xb:0x7ac DW_TAG_compile_unit
	.long	.Linfo_string0          # DW_AT_producer
	.short	12                      # DW_AT_language
	.long	.Linfo_string38         # DW_AT_name
	.quad	0                       # DW_AT_low_pc
	.long	.Lsection_line          # DW_AT_stmt_list
	.long	.Linfo_string2          # DW_AT_comp_dir
	.byte	15                      # Abbrev [15] 0x26:0x44 DW_TAG_subprogram
	.long	.Linfo_string39         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	40                      # DW_AT_decl_line
                                        # DW_AT_prototyped
                                        # DW_AT_external
	.quad	.Lfunc_begin6           # DW_AT_low_pc
	.quad	.Lfunc_end6             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.byte	31                      # Abbrev [31] 0x3f:0xe DW_TAG_formal_parameter
	.long	.Linfo_string166        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	40                      # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	120
	.byte	16                      # Abbrev [16] 0x4d:0xe DW_TAG_formal_parameter
	.long	.Linfo_string99         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	40                      # DW_AT_decl_line
	.long	876                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	112
	.byte	32                      # Abbrev [32] 0x5b:0xe DW_TAG_variable
	.long	.Linfo_string146        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	42                      # DW_AT_decl_line
	.long	.Lsection_info+224      # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	108
	.byte	0                       # End Of Children Mark
	.byte	30                      # Abbrev [30] 0x6a:0x3b DW_TAG_subprogram
	.long	.Linfo_string40         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	47                      # DW_AT_decl_line
                                        # DW_AT_prototyped
	.long	.Lsection_info+667      # DW_AT_type
                                        # DW_AT_external
	.quad	.Lfunc_begin7           # DW_AT_low_pc
	.quad	.Lfunc_end7             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.byte	31                      # Abbrev [31] 0x87:0xe DW_TAG_formal_parameter
	.long	.Linfo_string145        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	47                      # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	112
	.byte	13                      # Abbrev [13] 0x95:0xf DW_TAG_variable
	.long	.Linfo_string167        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	49                      # DW_AT_decl_line
	.long	1359                    # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\340~"
	.byte	0                       # End Of Children Mark
	.byte	30                      # Abbrev [30] 0xa5:0x3b DW_TAG_subprogram
	.long	.Linfo_string41         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	54                      # DW_AT_decl_line
                                        # DW_AT_prototyped
	.long	.Lsection_info+59       # DW_AT_type
                                        # DW_AT_external
	.quad	.Lfunc_begin9           # DW_AT_low_pc
	.quad	.Lfunc_end9             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.byte	31                      # Abbrev [31] 0xc2:0xe DW_TAG_formal_parameter
	.long	.Linfo_string145        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	54                      # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	112
	.byte	13                      # Abbrev [13] 0xd0:0xf DW_TAG_variable
	.long	.Linfo_string167        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	56                      # DW_AT_decl_line
	.long	1359                    # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\340~"
	.byte	0                       # End Of Children Mark
	.byte	30                      # Abbrev [30] 0xe0:0x3b DW_TAG_subprogram
	.long	.Linfo_string42         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	61                      # DW_AT_decl_line
                                        # DW_AT_prototyped
	.long	.Lsection_info+667      # DW_AT_type
                                        # DW_AT_external
	.quad	.Lfunc_begin8           # DW_AT_low_pc
	.quad	.Lfunc_end8             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.byte	31                      # Abbrev [31] 0xfd:0xe DW_TAG_formal_parameter
	.long	.Linfo_string145        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	61                      # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	112
	.byte	13                      # Abbrev [13] 0x10b:0xf DW_TAG_variable
	.long	.Linfo_string167        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	63                      # DW_AT_decl_line
	.long	1359                    # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\340~"
	.byte	0                       # End Of Children Mark
	.byte	41                      # Abbrev [41] 0x11b:0x58 DW_TAG_subprogram
	.long	.Linfo_string43         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	71                      # DW_AT_decl_line
	.long	.Lsection_info+59       # DW_AT_type
                                        # DW_AT_external
	.quad	.Lfunc_begin10          # DW_AT_low_pc
	.quad	.Lfunc_end10            # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.byte	13                      # Abbrev [13] 0x138:0xf DW_TAG_variable
	.long	.Linfo_string99         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	73                      # DW_AT_decl_line
	.long	876                     # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	119
	.ascii	"\270\002"
	.byte	32                      # Abbrev [32] 0x147:0xf DW_TAG_variable
	.long	.Linfo_string192        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	74                      # DW_AT_decl_line
	.long	.Lsection_info+59       # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	119
	.ascii	"\260\002"
	.byte	32                      # Abbrev [32] 0x156:0xe DW_TAG_variable
	.long	.Linfo_string143        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	75                      # DW_AT_decl_line
	.long	.Lsection_info+177      # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	119
	.byte	32
	.byte	32                      # Abbrev [32] 0x164:0xe DW_TAG_variable
	.long	.Linfo_string193        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	75                      # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	119
	.byte	24
	.byte	0                       # End Of Children Mark
	.byte	15                      # Abbrev [15] 0x173:0x64 DW_TAG_subprogram
	.long	.Linfo_string44         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	95                      # DW_AT_decl_line
                                        # DW_AT_prototyped
                                        # DW_AT_external
	.quad	.Lfunc_begin12          # DW_AT_low_pc
	.quad	.Lfunc_end12            # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.byte	16                      # Abbrev [16] 0x18c:0xe DW_TAG_formal_parameter
	.long	.Linfo_string99         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	95                      # DW_AT_decl_line
	.long	876                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	80
	.byte	32                      # Abbrev [32] 0x19a:0xf DW_TAG_variable
	.long	.Linfo_string143        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	97                      # DW_AT_decl_line
	.long	.Lsection_info+177      # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\320}"
	.byte	32                      # Abbrev [32] 0x1a9:0xf DW_TAG_variable
	.long	.Linfo_string193        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	97                      # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\310}"
	.byte	32                      # Abbrev [32] 0x1b8:0xf DW_TAG_variable
	.long	.Linfo_string140        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	97                      # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\300}"
	.byte	13                      # Abbrev [13] 0x1c7:0xf DW_TAG_variable
	.long	.Linfo_string196        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	98                      # DW_AT_decl_line
	.long	1727                    # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\270}"
	.byte	0                       # End Of Children Mark
	.byte	15                      # Abbrev [15] 0x1d7:0x36 DW_TAG_subprogram
	.long	.Linfo_string45         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	137                     # DW_AT_decl_line
                                        # DW_AT_prototyped
                                        # DW_AT_external
	.quad	.Lfunc_begin13          # DW_AT_low_pc
	.quad	.Lfunc_end13            # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.byte	31                      # Abbrev [31] 0x1f0:0xe DW_TAG_formal_parameter
	.long	.Linfo_string197        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	137                     # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	120
	.byte	32                      # Abbrev [32] 0x1fe:0xe DW_TAG_variable
	.long	.Linfo_string146        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	139                     # DW_AT_decl_line
	.long	.Lsection_info+224      # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	116
	.byte	0                       # End Of Children Mark
	.byte	42                      # Abbrev [42] 0x20d:0x62 DW_TAG_subprogram
	.long	.Linfo_string46         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	146                     # DW_AT_decl_line
                                        # DW_AT_external
	.quad	.Lfunc_begin14          # DW_AT_low_pc
	.quad	.Lfunc_end14            # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.byte	13                      # Abbrev [13] 0x226:0xe DW_TAG_variable
	.long	.Linfo_string99         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	148                     # DW_AT_decl_line
	.long	876                     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	112
	.byte	32                      # Abbrev [32] 0x234:0xe DW_TAG_variable
	.long	.Linfo_string193        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	149                     # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	104
	.byte	32                      # Abbrev [32] 0x242:0xe DW_TAG_variable
	.long	.Linfo_string140        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	149                     # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	96
	.byte	32                      # Abbrev [32] 0x250:0xf DW_TAG_variable
	.long	.Linfo_string143        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	150                     # DW_AT_decl_line
	.long	.Lsection_info+177      # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\340}"
	.byte	32                      # Abbrev [32] 0x25f:0xf DW_TAG_variable
	.long	.Linfo_string146        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	151                     # DW_AT_decl_line
	.long	.Lsection_info+667      # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	145
	.ascii	"\334}"
	.byte	0                       # End Of Children Mark
	.byte	30                      # Abbrev [30] 0x26f:0x48 DW_TAG_subprogram
	.long	.Linfo_string47         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	194                     # DW_AT_decl_line
                                        # DW_AT_prototyped
	.long	.Lsection_info+667      # DW_AT_type
                                        # DW_AT_external
	.quad	.Lfunc_begin11          # DW_AT_low_pc
	.quad	.Lfunc_end11            # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.byte	31                      # Abbrev [31] 0x28c:0xe DW_TAG_formal_parameter
	.long	.Linfo_string194        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	194                     # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	104
	.byte	31                      # Abbrev [31] 0x29a:0xe DW_TAG_formal_parameter
	.long	.Linfo_string195        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	194                     # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	96
	.byte	32                      # Abbrev [32] 0x2a8:0xe DW_TAG_variable
	.long	.Linfo_string146        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	196                     # DW_AT_decl_line
	.long	.Lsection_info+667      # DW_AT_type
	.byte	2                       # DW_AT_location
	.byte	145
	.byte	92
	.byte	0                       # End Of Children Mark
	.byte	15                      # Abbrev [15] 0x2b7:0xb5 DW_TAG_subprogram
	.long	.Linfo_string48         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	208                     # DW_AT_decl_line
                                        # DW_AT_prototyped
                                        # DW_AT_external
	.quad	.Lfunc_begin15          # DW_AT_low_pc
	.quad	.Lfunc_end15            # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	86
	.byte	43                      # Abbrev [43] 0x2d0:0x5 DW_TAG_structure_type
	.long	.Linfo_string202        # DW_AT_name
                                        # DW_AT_declaration
	.byte	31                      # Abbrev [31] 0x2d5:0xf DW_TAG_formal_parameter
	.long	.Linfo_string198        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	208                     # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	119
	.ascii	"\270\005"
	.byte	13                      # Abbrev [13] 0x2e4:0xf DW_TAG_variable
	.long	.Linfo_string199        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	210                     # DW_AT_decl_line
	.long	876                     # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	119
	.ascii	"\260\005"
	.byte	13                      # Abbrev [13] 0x2f3:0xf DW_TAG_variable
	.long	.Linfo_string200        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	211                     # DW_AT_decl_line
	.long	1817                    # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	119
	.ascii	"\250\005"
	.byte	13                      # Abbrev [13] 0x302:0xf DW_TAG_variable
	.long	.Linfo_string202        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	212                     # DW_AT_decl_line
	.long	1828                    # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	119
	.ascii	"\240\005"
	.byte	32                      # Abbrev [32] 0x311:0xf DW_TAG_variable
	.long	.Linfo_string203        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	213                     # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	119
	.ascii	"\230\005"
	.byte	32                      # Abbrev [32] 0x320:0xf DW_TAG_variable
	.long	.Linfo_string204        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	213                     # DW_AT_decl_line
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	119
	.ascii	"\220\005"
	.byte	32                      # Abbrev [32] 0x32f:0xf DW_TAG_variable
	.long	.Linfo_string205        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	214                     # DW_AT_decl_line
	.long	.Lsection_info+177      # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	119
	.ascii	"\220\003"
	.byte	13                      # Abbrev [13] 0x33e:0xf DW_TAG_variable
	.long	.Linfo_string206        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	215                     # DW_AT_decl_line
	.long	1833                    # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	119
	.ascii	"\360\002"
	.byte	13                      # Abbrev [13] 0x34d:0xf DW_TAG_variable
	.long	.Linfo_string207        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	216                     # DW_AT_decl_line
	.long	1845                    # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	119
	.ascii	"\340\001"
	.byte	13                      # Abbrev [13] 0x35c:0xf DW_TAG_variable
	.long	.Linfo_string208        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	217                     # DW_AT_decl_line
	.long	1857                    # DW_AT_type
	.byte	3                       # DW_AT_location
	.byte	119
	.ascii	"\300\001"
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0x36c:0x5 DW_TAG_pointer_type
	.long	881                     # DW_AT_type
	.byte	5                       # Abbrev [5] 0x371:0xb DW_TAG_typedef
	.long	892                     # DW_AT_type
	.long	.Linfo_string137        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	48                      # DW_AT_decl_line
	.byte	19                      # Abbrev [19] 0x37c:0x199 DW_TAG_structure_type
	.long	.Linfo_string136        # DW_AT_name
	.byte	216                     # DW_AT_byte_size
	.byte	10                      # DW_AT_decl_file
	.byte	245                     # DW_AT_decl_line
	.byte	33                      # Abbrev [33] 0x384:0xd DW_TAG_member
	.long	.Linfo_string100        # DW_AT_name
	.long	.Lsection_info+667      # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.byte	246                     # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x391:0xd DW_TAG_member
	.long	.Linfo_string101        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.byte	251                     # DW_AT_decl_line
	.byte	8                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x39e:0xd DW_TAG_member
	.long	.Linfo_string102        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.byte	252                     # DW_AT_decl_line
	.byte	16                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x3ab:0xd DW_TAG_member
	.long	.Linfo_string103        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.byte	253                     # DW_AT_decl_line
	.byte	24                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x3b8:0xd DW_TAG_member
	.long	.Linfo_string104        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.byte	254                     # DW_AT_decl_line
	.byte	32                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x3c5:0xd DW_TAG_member
	.long	.Linfo_string105        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.byte	255                     # DW_AT_decl_line
	.byte	40                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x3d2:0xe DW_TAG_member
	.long	.Linfo_string106        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	256                     # DW_AT_decl_line
	.byte	48                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x3e0:0xe DW_TAG_member
	.long	.Linfo_string107        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	257                     # DW_AT_decl_line
	.byte	56                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x3ee:0xe DW_TAG_member
	.long	.Linfo_string108        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	258                     # DW_AT_decl_line
	.byte	64                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x3fc:0xe DW_TAG_member
	.long	.Linfo_string109        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	260                     # DW_AT_decl_line
	.byte	72                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x40a:0xe DW_TAG_member
	.long	.Linfo_string110        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	261                     # DW_AT_decl_line
	.byte	80                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x418:0xe DW_TAG_member
	.long	.Linfo_string111        # DW_AT_name
	.long	.Lsection_info+1237     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	262                     # DW_AT_decl_line
	.byte	88                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	35                      # Abbrev [35] 0x426:0xe DW_TAG_member
	.long	.Linfo_string112        # DW_AT_name
	.long	1301                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	264                     # DW_AT_decl_line
	.byte	96                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	35                      # Abbrev [35] 0x434:0xe DW_TAG_member
	.long	.Linfo_string117        # DW_AT_name
	.long	1354                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	266                     # DW_AT_decl_line
	.byte	104                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x442:0xe DW_TAG_member
	.long	.Linfo_string118        # DW_AT_name
	.long	.Lsection_info+667      # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	268                     # DW_AT_decl_line
	.byte	112                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x450:0xe DW_TAG_member
	.long	.Linfo_string119        # DW_AT_name
	.long	.Lsection_info+667      # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	272                     # DW_AT_decl_line
	.byte	116                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x45e:0xe DW_TAG_member
	.long	.Linfo_string120        # DW_AT_name
	.long	.Lsection_info+2483     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	274                     # DW_AT_decl_line
	.byte	120                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x46c:0xe DW_TAG_member
	.long	.Linfo_string122        # DW_AT_name
	.long	.Lsection_info+924      # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	278                     # DW_AT_decl_line
	.byte	128                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x47a:0xe DW_TAG_member
	.long	.Linfo_string123        # DW_AT_name
	.long	.Lsection_info+2494     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	279                     # DW_AT_decl_line
	.byte	130                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x488:0xe DW_TAG_member
	.long	.Linfo_string125        # DW_AT_name
	.long	.Lsection_info+2501     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	280                     # DW_AT_decl_line
	.byte	131                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x496:0xe DW_TAG_member
	.long	.Linfo_string126        # DW_AT_name
	.long	.Lsection_info+2513     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	284                     # DW_AT_decl_line
	.byte	136                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x4a4:0xe DW_TAG_member
	.long	.Linfo_string127        # DW_AT_name
	.long	.Lsection_info+2514     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	293                     # DW_AT_decl_line
	.byte	144                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x4b2:0xe DW_TAG_member
	.long	.Linfo_string129        # DW_AT_name
	.long	.Lsection_info+2513     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	302                     # DW_AT_decl_line
	.byte	152                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x4c0:0xe DW_TAG_member
	.long	.Linfo_string130        # DW_AT_name
	.long	.Lsection_info+2513     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	303                     # DW_AT_decl_line
	.byte	160                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x4ce:0xe DW_TAG_member
	.long	.Linfo_string131        # DW_AT_name
	.long	.Lsection_info+2513     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	304                     # DW_AT_decl_line
	.byte	168                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x4dc:0xe DW_TAG_member
	.long	.Linfo_string132        # DW_AT_name
	.long	.Lsection_info+2513     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	305                     # DW_AT_decl_line
	.byte	176                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x4ea:0xe DW_TAG_member
	.long	.Linfo_string133        # DW_AT_name
	.long	.Lsection_info+2525     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	306                     # DW_AT_decl_line
	.byte	184                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x4f8:0xe DW_TAG_member
	.long	.Linfo_string134        # DW_AT_name
	.long	.Lsection_info+667      # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	308                     # DW_AT_decl_line
	.byte	192                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	34                      # Abbrev [34] 0x506:0xe DW_TAG_member
	.long	.Linfo_string135        # DW_AT_name
	.long	.Lsection_info+2536     # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.short	310                     # DW_AT_decl_line
	.byte	196                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0x515:0x5 DW_TAG_pointer_type
	.long	1306                    # DW_AT_type
	.byte	19                      # Abbrev [19] 0x51a:0x30 DW_TAG_structure_type
	.long	.Linfo_string116        # DW_AT_name
	.byte	24                      # DW_AT_byte_size
	.byte	10                      # DW_AT_decl_file
	.byte	160                     # DW_AT_decl_line
	.byte	7                       # Abbrev [7] 0x522:0xd DW_TAG_member
	.long	.Linfo_string113        # DW_AT_name
	.long	1301                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.byte	161                     # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x52f:0xd DW_TAG_member
	.long	.Linfo_string114        # DW_AT_name
	.long	1354                    # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.byte	162                     # DW_AT_decl_line
	.byte	8                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x53c:0xd DW_TAG_member
	.long	.Linfo_string115        # DW_AT_name
	.long	.Lsection_info+667      # DW_AT_type
	.byte	10                      # DW_AT_decl_file
	.byte	166                     # DW_AT_decl_line
	.byte	16                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	4                       # Abbrev [4] 0x54a:0x5 DW_TAG_pointer_type
	.long	892                     # DW_AT_type
	.byte	19                      # Abbrev [19] 0x54f:0xcc DW_TAG_structure_type
	.long	.Linfo_string191        # DW_AT_name
	.byte	144                     # DW_AT_byte_size
	.byte	12                      # DW_AT_decl_file
	.byte	46                      # DW_AT_decl_line
	.byte	7                       # Abbrev [7] 0x557:0xd DW_TAG_member
	.long	.Linfo_string168        # DW_AT_name
	.long	1563                    # DW_AT_type
	.byte	12                      # DW_AT_decl_file
	.byte	48                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x564:0xd DW_TAG_member
	.long	.Linfo_string170        # DW_AT_name
	.long	1574                    # DW_AT_type
	.byte	12                      # DW_AT_decl_file
	.byte	53                      # DW_AT_decl_line
	.byte	8                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x571:0xd DW_TAG_member
	.long	.Linfo_string171        # DW_AT_name
	.long	1585                    # DW_AT_type
	.byte	12                      # DW_AT_decl_file
	.byte	61                      # DW_AT_decl_line
	.byte	16                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x57e:0xd DW_TAG_member
	.long	.Linfo_string173        # DW_AT_name
	.long	1596                    # DW_AT_type
	.byte	12                      # DW_AT_decl_file
	.byte	62                      # DW_AT_decl_line
	.byte	24                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x58b:0xd DW_TAG_member
	.long	.Linfo_string175        # DW_AT_name
	.long	1607                    # DW_AT_type
	.byte	12                      # DW_AT_decl_file
	.byte	64                      # DW_AT_decl_line
	.byte	28                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x598:0xd DW_TAG_member
	.long	.Linfo_string176        # DW_AT_name
	.long	1618                    # DW_AT_type
	.byte	12                      # DW_AT_decl_file
	.byte	65                      # DW_AT_decl_line
	.byte	32                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x5a5:0xd DW_TAG_member
	.long	.Linfo_string177        # DW_AT_name
	.long	.Lsection_info+667      # DW_AT_type
	.byte	12                      # DW_AT_decl_file
	.byte	67                      # DW_AT_decl_line
	.byte	36                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x5b2:0xd DW_TAG_member
	.long	.Linfo_string178        # DW_AT_name
	.long	1563                    # DW_AT_type
	.byte	12                      # DW_AT_decl_file
	.byte	69                      # DW_AT_decl_line
	.byte	40                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x5bf:0xd DW_TAG_member
	.long	.Linfo_string179        # DW_AT_name
	.long	.Lsection_info+2483     # DW_AT_type
	.byte	12                      # DW_AT_decl_file
	.byte	74                      # DW_AT_decl_line
	.byte	48                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x5cc:0xd DW_TAG_member
	.long	.Linfo_string180        # DW_AT_name
	.long	1629                    # DW_AT_type
	.byte	12                      # DW_AT_decl_file
	.byte	78                      # DW_AT_decl_line
	.byte	56                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x5d9:0xd DW_TAG_member
	.long	.Linfo_string182        # DW_AT_name
	.long	1640                    # DW_AT_type
	.byte	12                      # DW_AT_decl_file
	.byte	80                      # DW_AT_decl_line
	.byte	64                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x5e6:0xd DW_TAG_member
	.long	.Linfo_string184        # DW_AT_name
	.long	1651                    # DW_AT_type
	.byte	12                      # DW_AT_decl_file
	.byte	91                      # DW_AT_decl_line
	.byte	72                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x5f3:0xd DW_TAG_member
	.long	.Linfo_string188        # DW_AT_name
	.long	1651                    # DW_AT_type
	.byte	12                      # DW_AT_decl_file
	.byte	92                      # DW_AT_decl_line
	.byte	88                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x600:0xd DW_TAG_member
	.long	.Linfo_string189        # DW_AT_name
	.long	1651                    # DW_AT_type
	.byte	12                      # DW_AT_decl_file
	.byte	93                      # DW_AT_decl_line
	.byte	104                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x60d:0xd DW_TAG_member
	.long	.Linfo_string190        # DW_AT_name
	.long	1708                    # DW_AT_type
	.byte	12                      # DW_AT_decl_file
	.byte	106                     # DW_AT_decl_line
	.byte	120                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	36                      # Abbrev [36] 0x61b:0xb DW_TAG_typedef
	.long	.Lsection_info+59       # DW_AT_type
	.long	.Linfo_string169        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	124                     # DW_AT_decl_line
	.byte	36                      # Abbrev [36] 0x626:0xb DW_TAG_typedef
	.long	.Lsection_info+59       # DW_AT_type
	.long	.Linfo_string156        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	127                     # DW_AT_decl_line
	.byte	36                      # Abbrev [36] 0x631:0xb DW_TAG_typedef
	.long	.Lsection_info+59       # DW_AT_type
	.long	.Linfo_string172        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	130                     # DW_AT_decl_line
	.byte	36                      # Abbrev [36] 0x63c:0xb DW_TAG_typedef
	.long	.Lsection_info+224      # DW_AT_type
	.long	.Linfo_string174        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	129                     # DW_AT_decl_line
	.byte	36                      # Abbrev [36] 0x647:0xb DW_TAG_typedef
	.long	.Lsection_info+224      # DW_AT_type
	.long	.Linfo_string87         # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	125                     # DW_AT_decl_line
	.byte	36                      # Abbrev [36] 0x652:0xb DW_TAG_typedef
	.long	.Lsection_info+224      # DW_AT_type
	.long	.Linfo_string89         # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	126                     # DW_AT_decl_line
	.byte	36                      # Abbrev [36] 0x65d:0xb DW_TAG_typedef
	.long	.Lsection_info+1062     # DW_AT_type
	.long	.Linfo_string181        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	153                     # DW_AT_decl_line
	.byte	36                      # Abbrev [36] 0x668:0xb DW_TAG_typedef
	.long	.Lsection_info+1062     # DW_AT_type
	.long	.Linfo_string183        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	158                     # DW_AT_decl_line
	.byte	19                      # Abbrev [19] 0x673:0x23 DW_TAG_structure_type
	.long	.Linfo_string187        # DW_AT_name
	.byte	16                      # DW_AT_byte_size
	.byte	13                      # DW_AT_decl_file
	.byte	120                     # DW_AT_decl_line
	.byte	7                       # Abbrev [7] 0x67b:0xd DW_TAG_member
	.long	.Linfo_string72         # DW_AT_name
	.long	1686                    # DW_AT_type
	.byte	13                      # DW_AT_decl_file
	.byte	122                     # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	7                       # Abbrev [7] 0x688:0xd DW_TAG_member
	.long	.Linfo_string185        # DW_AT_name
	.long	1697                    # DW_AT_type
	.byte	13                      # DW_AT_decl_file
	.byte	123                     # DW_AT_decl_line
	.byte	8                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	36                      # Abbrev [36] 0x696:0xb DW_TAG_typedef
	.long	.Lsection_info+1062     # DW_AT_type
	.long	.Linfo_string74         # DW_AT_name
	.byte	13                      # DW_AT_decl_file
	.byte	139                     # DW_AT_decl_line
	.byte	36                      # Abbrev [36] 0x6a1:0xb DW_TAG_typedef
	.long	.Lsection_info+1062     # DW_AT_type
	.long	.Linfo_string186        # DW_AT_name
	.byte	13                      # DW_AT_decl_file
	.byte	175                     # DW_AT_decl_line
	.byte	9                       # Abbrev [9] 0x6ac:0xc DW_TAG_array_type
	.long	1697                    # DW_AT_type
	.byte	10                      # Abbrev [10] 0x6b1:0x6 DW_TAG_subrange_type
	.long	1720                    # DW_AT_type
	.byte	2                       # DW_AT_upper_bound
	.byte	0                       # End Of Children Mark
	.byte	11                      # Abbrev [11] 0x6b8:0x7 DW_TAG_base_type
	.long	.Linfo_string8          # DW_AT_name
	.byte	4                       # DW_AT_byte_size
	.byte	5                       # DW_AT_encoding
	.byte	4                       # Abbrev [4] 0x6bf:0x5 DW_TAG_pointer_type
	.long	1732                    # DW_AT_type
	.byte	5                       # Abbrev [5] 0x6c4:0xb DW_TAG_typedef
	.long	1743                    # DW_AT_type
	.long	.Linfo_string13         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	30                      # DW_AT_decl_line
	.byte	6                       # Abbrev [6] 0x6cf:0x4a DW_TAG_structure_type
	.short	1275                    # DW_AT_byte_size
	.byte	2                       # DW_AT_decl_file
	.byte	23                      # DW_AT_decl_line
	.byte	33                      # Abbrev [33] 0x6d4:0xd DW_TAG_member
	.long	.Linfo_string6          # DW_AT_name
	.long	.Lsection_info+177      # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	25                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x6e1:0xd DW_TAG_member
	.long	.Linfo_string9          # DW_AT_name
	.long	.Lsection_info+177      # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	26                      # DW_AT_decl_line
	.byte	255                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	39                      # Abbrev [39] 0x6ee:0xe DW_TAG_member
	.long	.Linfo_string10         # DW_AT_name
	.long	.Lsection_info+177      # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	27                      # DW_AT_decl_line
	.short	510                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	39                      # Abbrev [39] 0x6fc:0xe DW_TAG_member
	.long	.Linfo_string11         # DW_AT_name
	.long	.Lsection_info+177      # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	28                      # DW_AT_decl_line
	.short	765                     # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	39                      # Abbrev [39] 0x70a:0xe DW_TAG_member
	.long	.Linfo_string12         # DW_AT_name
	.long	.Lsection_info+177      # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	29                      # DW_AT_decl_line
	.short	1020                    # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x719:0xb DW_TAG_typedef
	.long	1686                    # DW_AT_type
	.long	.Linfo_string201        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	75                      # DW_AT_decl_line
	.byte	4                       # Abbrev [4] 0x724:0x5 DW_TAG_pointer_type
	.long	720                     # DW_AT_type
	.byte	29                      # Abbrev [29] 0x729:0xc DW_TAG_array_type
	.long	.Lsection_info+189      # DW_AT_type
	.byte	10                      # Abbrev [10] 0x72e:0x6 DW_TAG_subrange_type
	.long	1720                    # DW_AT_type
	.byte	21                      # DW_AT_upper_bound
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x735:0xc DW_TAG_array_type
	.long	.Lsection_info+189      # DW_AT_type
	.byte	10                      # Abbrev [10] 0x73a:0x6 DW_TAG_subrange_type
	.long	1720                    # DW_AT_type
	.byte	127                     # DW_AT_upper_bound
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x741:0xb DW_TAG_typedef
	.long	1868                    # DW_AT_type
	.long	.Linfo_string216        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	79                      # DW_AT_decl_line
	.byte	5                       # Abbrev [5] 0x74c:0xb DW_TAG_typedef
	.long	1879                    # DW_AT_type
	.long	.Linfo_string215        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	48                      # DW_AT_decl_line
	.byte	5                       # Abbrev [5] 0x757:0xb DW_TAG_typedef
	.long	1890                    # DW_AT_type
	.long	.Linfo_string214        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	217                     # DW_AT_decl_line
	.byte	9                       # Abbrev [9] 0x762:0xc DW_TAG_array_type
	.long	1902                    # DW_AT_type
	.byte	10                      # Abbrev [10] 0x767:0x6 DW_TAG_subrange_type
	.long	1720                    # DW_AT_type
	.byte	0                       # DW_AT_upper_bound
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x76e:0xb DW_TAG_typedef
	.long	1913                    # DW_AT_type
	.long	.Linfo_string213        # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	217                     # DW_AT_decl_line
	.byte	19                      # Abbrev [19] 0x779:0x3d DW_TAG_structure_type
	.long	.Linfo_string213        # DW_AT_name
	.byte	24                      # DW_AT_byte_size
	.byte	5                       # DW_AT_decl_file
	.byte	217                     # DW_AT_decl_line
	.byte	33                      # Abbrev [33] 0x781:0xd DW_TAG_member
	.long	.Linfo_string209        # DW_AT_name
	.long	.Lsection_info+224      # DW_AT_type
	.byte	5                       # DW_AT_decl_file
	.byte	217                     # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x78e:0xd DW_TAG_member
	.long	.Linfo_string210        # DW_AT_name
	.long	.Lsection_info+224      # DW_AT_type
	.byte	5                       # DW_AT_decl_file
	.byte	217                     # DW_AT_decl_line
	.byte	4                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x79b:0xd DW_TAG_member
	.long	.Linfo_string211        # DW_AT_name
	.long	.Lsection_info+2513     # DW_AT_type
	.byte	5                       # DW_AT_decl_file
	.byte	217                     # DW_AT_decl_line
	.byte	8                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	33                      # Abbrev [33] 0x7a8:0xd DW_TAG_member
	.long	.Linfo_string212        # DW_AT_name
	.long	.Lsection_info+2513     # DW_AT_type
	.byte	5                       # DW_AT_decl_file
	.byte	217                     # DW_AT_decl_line
	.byte	16                      # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
.L.debug_info_end2:
	.section	.debug_abbrev,"",@progbits
.L.debug_abbrev_begin:
	.byte	1                       # Abbreviation Code
	.byte	17                      # DW_TAG_compile_unit
	.byte	1                       # DW_CHILDREN_yes
	.byte	37                      # DW_AT_producer
	.byte	14                      # DW_FORM_strp
	.byte	19                      # DW_AT_language
	.byte	5                       # DW_FORM_data2
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	16                      # DW_AT_stmt_list
	.byte	23                      # DW_FORM_sec_offset
	.byte	27                      # DW_AT_comp_dir
	.byte	14                      # DW_FORM_strp
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	2                       # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	2                       # DW_AT_location
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	3                       # Abbreviation Code
	.byte	36                      # DW_TAG_base_type
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	62                      # DW_AT_encoding
	.byte	11                      # DW_FORM_data1
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	4                       # Abbreviation Code
	.byte	15                      # DW_TAG_pointer_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	5                       # Abbreviation Code
	.byte	22                      # DW_TAG_typedef
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	6                       # Abbreviation Code
	.byte	19                      # DW_TAG_structure_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	11                      # DW_AT_byte_size
	.byte	5                       # DW_FORM_data2
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	7                       # Abbreviation Code
	.byte	13                      # DW_TAG_member
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	56                      # DW_AT_data_member_location
	.byte	11                      # DW_FORM_data1
	.byte	50                      # DW_AT_accessibility
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	8                       # Abbreviation Code
	.byte	13                      # DW_TAG_member
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	56                      # DW_AT_data_member_location
	.byte	5                       # DW_FORM_data2
	.byte	50                      # DW_AT_accessibility
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	9                       # Abbreviation Code
	.byte	1                       # DW_TAG_array_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	10                      # Abbreviation Code
	.byte	33                      # DW_TAG_subrange_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	47                      # DW_AT_upper_bound
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	11                      # Abbreviation Code
	.byte	36                      # DW_TAG_base_type
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	62                      # DW_AT_encoding
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	12                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	64                      # DW_AT_frame_base
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	13                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	2                       # DW_AT_location
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	14                      # Abbreviation Code
	.byte	11                      # DW_TAG_lexical_block
	.byte	1                       # DW_CHILDREN_yes
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	15                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	39                      # DW_AT_prototyped
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	64                      # DW_AT_frame_base
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	16                      # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	2                       # DW_AT_location
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	17                      # Abbreviation Code
	.byte	4                       # DW_TAG_enumeration_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	18                      # Abbreviation Code
	.byte	40                      # DW_TAG_enumerator
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	28                      # DW_AT_const_value
	.byte	13                      # DW_FORM_sdata
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	19                      # Abbreviation Code
	.byte	19                      # DW_TAG_structure_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	20                      # Abbreviation Code
	.byte	19                      # DW_TAG_structure_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	21                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	5                       # DW_FORM_data2
	.byte	39                      # DW_AT_prototyped
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	64                      # DW_AT_frame_base
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	22                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	5                       # DW_FORM_data2
	.byte	2                       # DW_AT_location
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	23                      # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	5                       # DW_FORM_data2
	.byte	73                      # DW_AT_type
	.byte	16                      # DW_FORM_ref_addr
	.byte	2                       # DW_AT_location
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	24                      # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	5                       # DW_FORM_data2
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	2                       # DW_AT_location
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	25                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	5                       # DW_FORM_data2
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	2                       # DW_AT_location
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	26                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	5                       # DW_FORM_data2
	.byte	73                      # DW_AT_type
	.byte	16                      # DW_FORM_ref_addr
	.byte	2                       # DW_AT_location
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	27                      # Abbreviation Code
	.byte	38                      # DW_TAG_const_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	16                      # DW_FORM_ref_addr
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	28                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	5                       # DW_FORM_data2
	.byte	2                       # DW_AT_location
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	29                      # Abbreviation Code
	.byte	1                       # DW_TAG_array_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	73                      # DW_AT_type
	.byte	16                      # DW_FORM_ref_addr
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	30                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	39                      # DW_AT_prototyped
	.byte	25                      # DW_FORM_flag_present
	.byte	73                      # DW_AT_type
	.byte	16                      # DW_FORM_ref_addr
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	64                      # DW_AT_frame_base
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	31                      # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	16                      # DW_FORM_ref_addr
	.byte	2                       # DW_AT_location
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	32                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	16                      # DW_FORM_ref_addr
	.byte	2                       # DW_AT_location
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	33                      # Abbreviation Code
	.byte	13                      # DW_TAG_member
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	73                      # DW_AT_type
	.byte	16                      # DW_FORM_ref_addr
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	56                      # DW_AT_data_member_location
	.byte	11                      # DW_FORM_data1
	.byte	50                      # DW_AT_accessibility
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	34                      # Abbreviation Code
	.byte	13                      # DW_TAG_member
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	73                      # DW_AT_type
	.byte	16                      # DW_FORM_ref_addr
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	5                       # DW_FORM_data2
	.byte	56                      # DW_AT_data_member_location
	.byte	11                      # DW_FORM_data1
	.byte	50                      # DW_AT_accessibility
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	35                      # Abbreviation Code
	.byte	13                      # DW_TAG_member
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	5                       # DW_FORM_data2
	.byte	56                      # DW_AT_data_member_location
	.byte	11                      # DW_FORM_data1
	.byte	50                      # DW_AT_accessibility
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	36                      # Abbreviation Code
	.byte	22                      # DW_TAG_typedef
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	16                      # DW_FORM_ref_addr
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	37                      # Abbreviation Code
	.byte	15                      # DW_TAG_pointer_type
	.byte	0                       # DW_CHILDREN_no
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	38                      # Abbreviation Code
	.byte	33                      # DW_TAG_subrange_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	47                      # DW_AT_upper_bound
	.byte	5                       # DW_FORM_data2
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	39                      # Abbreviation Code
	.byte	13                      # DW_TAG_member
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	73                      # DW_AT_type
	.byte	16                      # DW_FORM_ref_addr
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	56                      # DW_AT_data_member_location
	.byte	5                       # DW_FORM_data2
	.byte	50                      # DW_AT_accessibility
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	40                      # Abbreviation Code
	.byte	19                      # DW_TAG_structure_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	11                      # DW_AT_byte_size
	.byte	5                       # DW_FORM_data2
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	41                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	16                      # DW_FORM_ref_addr
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	64                      # DW_AT_frame_base
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	42                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	64                      # DW_AT_frame_base
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	43                      # Abbreviation Code
	.byte	19                      # DW_TAG_structure_type
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	0                       # EOM(3)
.L.debug_abbrev_end:
	.section	.debug_aranges,"",@progbits
	.long	92                      # Length of ARange Set
	.short	2                       # DWARF Arange version number
	.long	.L.debug_info_begin0    # Offset Into Debug Info Section
	.byte	8                       # Address Size (in bytes)
	.byte	0                       # Segment Size (in bytes)
	.byte	255
	.byte	255
	.byte	255
	.byte	255
	.quad	defaulthost
	.quad	1275
	.quad	no_vhosts
.Lset0 = .Ldebug_end1-no_vhosts
	.quad	.Lset0
	.quad	SERVERPORT
.Lset1 = assocNames-SERVERPORT
	.quad	.Lset1
	.quad	.Lfunc_begin0
.Lset2 = .Lfunc_begin3-.Lfunc_begin0
	.quad	.Lset2
	.quad	0                       # ARange terminator
	.quad	0
	.long	76                      # Length of ARange Set
	.short	2                       # DWARF Arange version number
	.long	.L.debug_info_begin1    # Offset Into Debug Info Section
	.byte	8                       # Address Size (in bytes)
	.byte	0                       # Segment Size (in bytes)
	.byte	255
	.byte	255
	.byte	255
	.byte	255
	.quad	assocNames
.Lset3 = .Ldebug_end2-assocNames
	.quad	.Lset3
	.quad	showdir.dirfooter
.Lset4 = .Ldebug_end3-showdir.dirfooter
	.quad	.Lset4
	.quad	.Lfunc_begin3
.Lset5 = .Lfunc_begin6-.Lfunc_begin3
	.quad	.Lset5
	.quad	0                       # ARange terminator
	.quad	0
	.long	44                      # Length of ARange Set
	.short	2                       # DWARF Arange version number
	.long	.L.debug_info_begin2    # Offset Into Debug Info Section
	.byte	8                       # Address Size (in bytes)
	.byte	0                       # Segment Size (in bytes)
	.byte	255
	.byte	255
	.byte	255
	.byte	255
	.quad	.Lfunc_begin6
.Lset6 = .Ldebug_end4-.Lfunc_begin6
	.quad	.Lset6
	.quad	0                       # ARange terminator
	.quad	0
	.section	.debug_ranges,"",@progbits
	.section	.debug_macinfo,"",@progbits
	.section	.debug_pubnames,"",@progbits
.Lset7 = .Lpubnames_end1-.Lpubnames_begin1 # Length of Public Names Info
	.long	.Lset7
.Lpubnames_begin1:
	.short	2                       # DWARF Version
	.long	.L.debug_info_begin1    # Offset of Compilation Unit Info
.Lset8 = .L.debug_info_end1-.L.debug_info_begin1 # Compilation Unit Length
	.long	.Lset8
	.long	38                      # DIE offset
	.asciz	"showdir"               # External Name
	.long	311                     # DIE offset
	.asciz	"serveconnection"       # External Name
	.long	625                     # DIE offset
	.asciz	"getmimetype"           # External Name
	.long	265                     # DIE offset
	.asciz	"assocNames"            # External Name
	.long	0                       # End Mark
.Lpubnames_end1:
.Lset9 = .Lpubnames_end0-.Lpubnames_begin0 # Length of Public Names Info
	.long	.Lset9
.Lpubnames_begin0:
	.short	2                       # DWARF Version
	.long	.L.debug_info_begin0    # Offset of Compilation Unit Info
.Lset10 = .L.debug_info_end0-.L.debug_info_begin0 # Compilation Unit Length
	.long	.Lset10
	.long	38                      # DIE offset
	.asciz	"no_vhosts"             # External Name
	.long	273                     # DIE offset
	.asciz	"defaulthost"           # External Name
	.long	294                     # DIE offset
	.asciz	"main"                  # External Name
	.long	66                      # DIE offset
	.asciz	"vhosts"                # External Name
	.long	231                     # DIE offset
	.asciz	"SERVERTYPE"            # External Name
	.long	674                     # DIE offset
	.asciz	"inetd_server"          # External Name
	.long	252                     # DIE offset
	.asciz	"SERVERROOT"            # External Name
	.long	203                     # DIE offset
	.asciz	"SERVERPORT"            # External Name
	.long	746                     # DIE offset
	.asciz	"signal_handler"        # External Name
	.long	0                       # End Mark
.Lpubnames_end0:
.Lset11 = .Lpubnames_end2-.Lpubnames_begin2 # Length of Public Names Info
	.long	.Lset11
.Lpubnames_begin2:
	.short	2                       # DWARF Version
	.long	.L.debug_info_begin2    # Offset of Compilation Unit Info
.Lset12 = .L.debug_info_end2-.L.debug_info_begin2 # Compilation Unit Length
	.long	.Lset12
	.long	224                     # DIE offset
	.asciz	"isDirectory"           # External Name
	.long	695                     # DIE offset
	.asciz	"Log"                   # External Name
	.long	471                     # DIE offset
	.asciz	"gstrlwr"               # External Name
	.long	106                     # DIE offset
	.asciz	"does_file_exist"       # External Name
	.long	38                      # DIE offset
	.asciz	"getfileline"           # External Name
	.long	165                     # DIE offset
	.asciz	"get_file_size"         # External Name
	.long	525                     # DIE offset
	.asciz	"readinconfig"          # External Name
	.long	623                     # DIE offset
	.asciz	"gstricmp"              # External Name
	.long	371                     # DIE offset
	.asciz	"VirtualHostDefinition" # External Name
	.long	283                     # DIE offset
	.asciz	"count_vhosts"          # External Name
	.long	0                       # End Mark
.Lpubnames_end2:
	.section	.debug_pubtypes,"",@progbits
.Lset13 = .Lpubtypes_end1-.Lpubtypes_begin1 # Length of Public Types Info
	.long	.Lset13
.Lpubtypes_begin1:
	.short	2                       # DWARF Version
	.long	.L.debug_info_begin1    # Offset of Compilation Unit Info
.Lset14 = .L.debug_info_end1-.L.debug_info_begin1 # Compilation Unit Length
	.long	.Lset14
	.long	729                     # DIE offset
	.asciz	"FILE"                  # External Name
	.long	1297                    # DIE offset
	.asciz	"sockaddr_in"           # External Name
	.long	975                     # DIE offset
	.asciz	"in_addr_t"             # External Name
	.long	1009                    # DIE offset
	.asciz	"unsigned char"         # External Name
	.long	1480                    # DIE offset
	.asciz	"dirent"                # External Name
	.long	1385                    # DIE offset
	.asciz	"t_vhost"               # External Name
	.long	224                     # DIE offset
	.asciz	"unsigned int"          # External Name
	.long	913                     # DIE offset
	.asciz	"sa_family_t"           # External Name
	.long	667                     # DIE offset
	.asciz	"int"                   # External Name
	.long	1207                    # DIE offset
	.asciz	"__off_t"               # External Name
	.long	924                     # DIE offset
	.asciz	"unsigned short"        # External Name
	.long	1249                    # DIE offset
	.asciz	"size_t"                # External Name
	.long	931                     # DIE offset
	.asciz	"in_port_t"             # External Name
	.long	1358                    # DIE offset
	.asciz	"in_addr"               # External Name
	.long	740                     # DIE offset
	.asciz	"_IO_FILE"              # External Name
	.long	1238                    # DIE offset
	.asciz	"__off64_t"             # External Name
	.long	59                      # DIE offset
	.asciz	"long unsigned int"     # External Name
	.long	1154                    # DIE offset
	.asciz	"_IO_marker"            # External Name
	.long	1555                    # DIE offset
	.asciz	"__ino_t"               # External Name
	.long	1218                    # DIE offset
	.asciz	"signed char"           # External Name
	.long	1062                    # DIE offset
	.asciz	"long int"              # External Name
	.long	189                     # DIE offset
	.asciz	"char"                  # External Name
	.long	0                       # End Mark
.Lpubtypes_end1:
.Lset15 = .Lpubtypes_end0-.Lpubtypes_begin0 # Length of Public Types Info
	.long	.Lset15
.Lpubtypes_begin0:
	.short	2                       # DWARF Version
	.long	.L.debug_info_begin0    # Offset of Compilation Unit Info
.Lset16 = .L.debug_info_end0-.L.debug_info_begin0 # Compilation Unit Length
	.long	.Lset16
	.long	1051                    # DIE offset
	.asciz	"__time_t"              # External Name
	.long	852                     # DIE offset
	.asciz	"sockaddr_in"           # External Name
	.long	975                     # DIE offset
	.asciz	"in_addr_t"             # External Name
	.long	1253                    # DIE offset
	.asciz	"__gid_t"               # External Name
	.long	92                      # DIE offset
	.asciz	"t_vhost"               # External Name
	.long	913                     # DIE offset
	.asciz	"sa_family_t"           # External Name
	.long	224                     # DIE offset
	.asciz	"unsigned int"          # External Name
	.long	667                     # DIE offset
	.asciz	"int"                   # External Name
	.long	924                     # DIE offset
	.asciz	"unsigned short"        # External Name
	.long	931                     # DIE offset
	.asciz	"in_port_t"             # External Name
	.long	1264                    # DIE offset
	.asciz	"size_t"                # External Name
	.long	953                     # DIE offset
	.asciz	"in_addr"               # External Name
	.long	1069                    # DIE offset
	.asciz	"__suseconds_t"         # External Name
	.long	1016                    # DIE offset
	.asciz	"timeval"               # External Name
	.long	1121                    # DIE offset
	.asciz	"__fd_mask"             # External Name
	.long	1080                    # DIE offset
	.asciz	"fd_set"                # External Name
	.long	1242                    # DIE offset
	.asciz	"__uid_t"               # External Name
	.long	986                     # DIE offset
	.asciz	"uint32_t"              # External Name
	.long	59                      # DIE offset
	.asciz	"long unsigned int"     # External Name
	.long	942                     # DIE offset
	.asciz	"uint16_t"              # External Name
	.long	1009                    # DIE offset
	.asciz	"unsigned char"         # External Name
	.long	1062                    # DIE offset
	.asciz	"long int"              # External Name
	.long	189                     # DIE offset
	.asciz	"char"                  # External Name
	.long	1137                    # DIE offset
	.asciz	"passwd"                # External Name
	.long	0                       # End Mark
.Lpubtypes_end0:
.Lset17 = .Lpubtypes_end2-.Lpubtypes_begin2 # Length of Public Types Info
	.long	.Lset17
.Lpubtypes_begin2:
	.short	2                       # DWARF Version
	.long	.L.debug_info_begin2    # Offset of Compilation Unit Info
.Lset18 = .L.debug_info_end2-.L.debug_info_begin2 # Compilation Unit Length
	.long	.Lset18
	.long	1817                    # DIE offset
	.asciz	"time_t"                # External Name
	.long	1879                    # DIE offset
	.asciz	"__builtin_va_list"     # External Name
	.long	1732                    # DIE offset
	.asciz	"t_vhost"               # External Name
	.long	224                     # DIE offset
	.asciz	"unsigned int"          # External Name
	.long	667                     # DIE offset
	.asciz	"int"                   # External Name
	.long	1207                    # DIE offset
	.asciz	"__off_t"               # External Name
	.long	1249                    # DIE offset
	.asciz	"size_t"                # External Name
	.long	1596                    # DIE offset
	.asciz	"__mode_t"              # External Name
	.long	1574                    # DIE offset
	.asciz	"__ino_t"               # External Name
	.long	59                      # DIE offset
	.asciz	"long unsigned int"     # External Name
	.long	1306                    # DIE offset
	.asciz	"_IO_marker"            # External Name
	.long	1218                    # DIE offset
	.asciz	"signed char"           # External Name
	.long	1062                    # DIE offset
	.asciz	"long int"              # External Name
	.long	189                     # DIE offset
	.asciz	"char"                  # External Name
	.long	881                     # DIE offset
	.asciz	"FILE"                  # External Name
	.long	1686                    # DIE offset
	.asciz	"__time_t"              # External Name
	.long	1618                    # DIE offset
	.asciz	"__gid_t"               # External Name
	.long	1629                    # DIE offset
	.asciz	"__blksize_t"           # External Name
	.long	1902                    # DIE offset
	.asciz	"__va_list_tag"         # External Name
	.long	924                     # DIE offset
	.asciz	"unsigned short"        # External Name
	.long	1697                    # DIE offset
	.asciz	"__syscall_slong_t"     # External Name
	.long	1640                    # DIE offset
	.asciz	"__blkcnt_t"            # External Name
	.long	1563                    # DIE offset
	.asciz	"__dev_t"               # External Name
	.long	1857                    # DIE offset
	.asciz	"va_list"               # External Name
	.long	1585                    # DIE offset
	.asciz	"__nlink_t"             # External Name
	.long	1607                    # DIE offset
	.asciz	"__uid_t"               # External Name
	.long	892                     # DIE offset
	.asciz	"_IO_FILE"              # External Name
	.long	1238                    # DIE offset
	.asciz	"__off64_t"             # External Name
	.long	1651                    # DIE offset
	.asciz	"timespec"              # External Name
	.long	1359                    # DIE offset
	.asciz	"stat"                  # External Name
	.long	1868                    # DIE offset
	.asciz	"__gnuc_va_list"        # External Name
	.long	0                       # End Mark
.Lpubtypes_end2:

	.ident	"clang version 3.4 (tags/RELEASE_34/final)"
	.ident	"clang version 3.4 (tags/RELEASE_34/final)"
	.ident	"clang version 3.4 (tags/RELEASE_34/final)"
	.section	".note.GNU-stack","",@progbits
