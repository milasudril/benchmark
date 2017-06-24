//@	{
//@	 "targets":[{"name":"benchmark.so","type":"lib_dynamic"
//@	,"dependencies":[{"ref":"rt","rel":"external"}]}]
//@	}

#include <time.h>
#include <unistd.h>
#include <sys/resource.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static timespec s_time_start;

inline double secs(const timespec& t)
	{return static_cast<double>( t.tv_sec + 1e-9*t.tv_nsec );}

inline double secs(const timeval& t)
	{return static_cast<double>( t.tv_sec + 1e-6*t.tv_usec );}

static void end()
	{
	timespec real;
	clock_gettime(CLOCK_MONOTONIC_RAW,&real);
	
	rusage self;
	getrusage(RUSAGE_SELF,&self);
	
	rusage children;
	getrusage(RUSAGE_CHILDREN,&children);
 
	fprintf(stderr,"\n# Processing time in seconds for %d\n\n",getpid());
	fprintf(stderr,"Self (user / kernel):     %.3f / %.3f\n",secs(self.ru_utime),secs(self.ru_stime));
	fprintf(stderr,"Children (user / kernel): %.3f / %.3f\n",secs(children.ru_utime),secs(children.ru_stime));
	fprintf(stderr,"Wallclock (total):        %.3f\n",secs(real) - secs(s_time_start));
	}

__attribute__((constructor)) void init()
	{
	atexit(end);
	for(int i=0;environ[i];i++ )
		{
		if(strstr(environ[i],"LD_PRELOAD="))
			{environ[i][0] = 'D';}
		}
	clock_gettime(CLOCK_MONOTONIC_RAW,&s_time_start);
	}
