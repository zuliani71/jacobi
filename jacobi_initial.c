#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
  size_t i,j,it;
  double *m,*m1,*mTmp;
  size_t dim=0,iters=0;
size_t dimByte=0;
  if(argc!=3) {
  fprintf(stderr,"\nwrong number of arguments. Usage: ./a.out dim iterations \n");
  return 1;
  }
  dim=atoi(argv[1]);
  iters=atoi(argv[2]);
  printf("m size = %zu\n", dim);
  printf("number of iter = %zu\n", iters);
  dimByte=sizeof(double)*(dim+2)*(dim+2);
  m=(double*)malloc(dimByte);
  m1=(double*)malloc(dimByte);
  for(i=1;i<(dim+2)*(dim+2);++i)
  m[i]=0;
  double incr=100.0/(dim+1);
  for(i=1;i<=dim+1;++i){
  m[i*(dim+2)]=i*incr;
  m[((dim+1)*(dim+2))+(dim+1-i)]=i*incr;
  m1[i*(dim+2)]=i*incr;
  m1[((dim+1)*(dim+2))+(dim+1-i)]=i*incr;
  }
  for(it=0;it<iters;++it){
  for(i=1;i<=dim;++i)
  for(j=1;j<=dim;++j)
  m1[(i*(dim+2))+j]=(0.25)*(m[((i-1)*(dim+2))+j]+m[(i*(dim+2))+(j+1)]+m[((i+1)*(dim+2))+j]+m[(i*(dim+2))+(j-1)]);
  mTmp=m;
  m=m1;
  m1=mTmp;
  }
  FILE *f;
  f=fopen( "solution.dat", "w+" );
  for(i=0;i<dim+2;++i){
  for(j=0;j<dim+2;++j){
  fprintf(f,"%f ",m[(i*(dim+2))+j]);
  }
  fprintf(f,"\n");
  }
  fclose(f);
  free(m);
  free(m1);
  return 0;
}
