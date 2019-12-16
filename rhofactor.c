#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TESTREP 5
#define BUFINC 4

void _rho(mpz_t n)
{
  mpz_t seed;
  mpz_t x,y,d;
  mpz_t tmp;

  mpz_init(tmp);
  mpz_init_set_si(seed,2);
  mpz_init_set_si(d,1);
  mpz_init_set_si(x,2);
  mpz_init_set_si(y,2);

  if(mpz_probab_prime_p(n,TESTREP)) {
    mpz_out_str(stdout,10,n);
    fputc(' ',stdout);
    mpz_clear(seed); mpz_clear(x); mpz_clear(y); mpz_clear(d); mpz_clear(tmp);
    return;
  }
  while(mpz_cmp_si(d,1)==0) {
    // x = (x*x + 1)%n 
    mpz_mul(tmp,x,x);
    mpz_add_ui(tmp,tmp,1);
    mpz_tdiv_r(x,tmp,n);
    // y = ((y*y + 1) * (y*y + 1) + 1) % n
    mpz_mul(tmp,y,y);
    mpz_add_ui(tmp,tmp,1);
    mpz_mul(tmp,tmp,tmp);
    mpz_add_ui(tmp,tmp,1);
    mpz_tdiv_r(y,tmp,n);

    mpz_sub(tmp,x,y);
    if(mpz_cmp_si(tmp,0)==0) {
      mpz_add_ui(seed,seed,1);
      mpz_set(x,seed);
      mpz_set(y,seed);
      continue;
    }
    // d = gcd(x-y,n);
    mpz_gcd(d,tmp,n);
    // if(d < 0)
    // d = -d;
    mpz_abs(d,d);
    if(mpz_cmp_si(d,1)!=0 && mpz_cmp(d,n)<0) break;
  }
  mpz_tdiv_q(y,n,d);
  _rho(d);
  _rho(y);
  mpz_clear(seed); mpz_clear(x); mpz_clear(y); mpz_clear(d); mpz_clear(tmp);
}
void rho(mpz_t n)
{
  mpz_t r;
  int ret;

  mpz_init(r);
  mpz_set(r,n);
  while(mpz_even_p(r)) {
    fputc('2',stdout);
    fputc(' ',stdout);
    mpz_tdiv_q_ui(r,r,2);
  }
  if(mpz_cmp_ui(r,1) == 0) return;
  _rho(r);
  mpz_clear(r);
  fputc('\n',stdout);
  fflush(stdout);
}
int main(int argc,char *argv[])
{
  mpz_t n;
  int i;
  int c;
  char *buf;
  int size;
  int p;
  int eof;
  
  size = BUFINC;
  buf = malloc(sizeof(char)*size);

  for(eof=0;!eof;) {
    p = 0;

    for(c = fgetc(stdin);c != '\n';c = fgetc(stdin)) {
      if(c == EOF) { eof = 1; p = 0; break; }
      if(c == '\r') continue;
      buf[p++] = c;
      if(p >= size) {
	size += BUFINC;
	buf = realloc(buf,size);
      }
    }
    buf[p] = '\0';

    if(p == 0) continue;
    mpz_init(n);
    if(mpz_set_str(n,buf,10) < 0) {
      fprintf(stdout,"'%s' is not a valid positive integer",buf);
      continue;
    }
    if(mpz_sgn(n) <= 0) {
      fprintf(stdout,"'%s' is not a valid positive integer",buf);
      continue;
    }
    fprintf(stdout,"%s: ",buf);
    rho(n);
    mpz_clear(n);
  }
  return 0;
}

