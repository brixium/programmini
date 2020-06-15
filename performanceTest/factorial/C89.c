#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>

int main(int argc, char * argv [] )
{
	mpz_t val;
	clock_t begin, end;
	double exec_time;
	
	mpz_init (val);
	
	begin = clock();
	mpz_fac_ui (val, 19);
	gmp_printf("%Zd\n", val);
	end = clock();
	exec_time = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("Time elapsed: %f s\n", exec_time);
	return 0;
}

