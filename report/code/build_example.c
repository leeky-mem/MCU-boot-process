#include <stdio.h>

int global_var = 1;
extern volatile int extern_var;
static int local_var_bss;
static int local_var_data = 5;

static int local_sum(int sum1, int sum2)
{
	return sum1 + sum2;
}

int main(void)
{
	local_var_bss = local_sum(extern_var, local_var_data);
	printf("The sum is: %d", local_var_bss);
}