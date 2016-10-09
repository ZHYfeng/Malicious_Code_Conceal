#define FILENAME	"csmall"
#define	ENTRY		77
#define MAX_SIZE	512
#define	TASK_SIZE	0xc0000000

#define WARNING(M,F,E)fprintf(stderr,"%s:%d: "#M": %d "	\
"(%s), %s return %d expected %d\n", __FILE__, __LINE__,	\
errno, strerror(errno), #F, r, E);
#define CHECK(F,E,...)({int r;do r=F(__VA_ARGS__);while	\
(r==-1 && errno==EINTR); if(r==-1) {WARNING(Error,F,E);	\
_exit(2); } if (r != E ) WARNING (Warning, F, E); r; })

#define _pread(a,b,c,d)		CHECK(pread,c,a,b,c,d)
#define _pwrite(a,b,c,d)	CHECK(pwrite,c,a,b,c,d)
#define _close(a)		CHECK(close,0,a)
#define _truncate(a,b)		CHECK(truncate,0,a,b)

void error(char *msg);
void sighnd(int sig);
