/*                       ____     ____                   
			 / _____)  (__  )   |__   )
			( (____    |  )__)  |  |__)
			 \____ \   | |      | |\ \
			 _____) )  | |      | | \ \ 
			(______/   | |      | |  \ \

*/
#include<stdio.h>
#include<conio.h>
#include<math.h>
int Nhap_size();
int Nhap_filter_length();
void vao_sl(float *Magnetic_normal, int size);
void Medium_Filter(float *Magnetic_normal, float *Magnetic_field_after_filtering, int N, int k);
void ra_sl(float *Magnetic_field_after_filtering, int size);
float Find_Sample_Variance(float *Magnetic_field_after_filtering, int N);
main()
{
    int N=Nhap_size();
    float Medium;
    int filter_length=Nhap_filter_length();
	float Magnetic_normal[N];
	float Magnetic_field_after_filtering[N];
	vao_sl(Magnetic_normal,N);
	Medium_Filter(Magnetic_normal, Magnetic_field_after_filtering, N, filter_length);
	ra_sl(Magnetic_field_after_filtering, N);
	Medium=Find_Sample_Variance(Magnetic_field_after_filtering, N);
	printf("\nPhuong sai mau:%f",Medium);
}
int Nhap_size()
{	
    int size;
	tt:printf("\nNhap so phan tu cua mang Size: ");
    scanf("%d",&size);
    if(size<=2) goto tt;
    return size;
}
int Nhap_filter_length()
{	
    int filter_length;
	tt:printf("\nNhap so bac cua bo loc filter_length nho hon size: ");
    scanf("%d",&filter_length);
    if(filter_length<=2) goto tt;
    return filter_length;
}
void vao_sl(float *Magnetic_normal, int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		printf("\nMagnetic_normal[%d]= ", i+1);
		scanf("%f",Magnetic_normal+i);
	}		
}
void ra_sl(float *Magnetic_field_after_filtering, int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		printf("\nMagnetic_field_after_filtering[%d]=%f", i+1,*(Magnetic_field_after_filtering+i));

	}		
}
void Medium_Filter(float *Magnetic_normal, float *Magnetic_field_after_filtering, int N, int k)
{
	// N chieu dai cua cua so
	// k so bac cua bo loc k le
	// n so phan tu ngoai nhom
	// phan tu canh ben p
	// n=k-1
	// p=n/2
	
	int i, j, m, n=k-1,p=n/2;	 
	for(i=0;i<=N-1;i++)
	{
		if((0<=i)&&(i<=p-1))
		{			
		    int sum1=0;		    
			for(m=0;m<=i+p;m++)
			{
				sum1+=(*(Magnetic_normal+m));
			}
			*(Magnetic_field_after_filtering+i)=((p-i)*(*(Magnetic_normal+0))+sum1)/k;
			sum1=0;						 				
		}
		if((p<=i)&&(i<=N-p-1))
		{
			int sum2=0;
			for(m=i-p;m<=i+p;m++)
			{
				sum2+=(*(Magnetic_normal+m));	
			}
			*(Magnetic_field_after_filtering+i)=sum2/k;
			sum2=0;
		}
		if((N-p<=i)&&(i<=N-1))
		{
			int sum3=0;
			for(m=i-p;m<=N-1;m++)
			{
				sum3+=(*(Magnetic_normal+m));
			}
			*(Magnetic_field_after_filtering+i)=((p+i-N+1)*(*(Magnetic_normal+(N-1)))+sum3)/k;
			sum3=0;
		}
	}
}
float Find_Sample_Variance(float *Magnetic_field_after_filtering, int N)
{
	int i;
	float Medium=0;
	float Variance=0;
	for(i=0;i<N;i++)
	{
		Medium+=(*(Magnetic_field_after_filtering+i))/N;
	}
	for(i=0;i<N;i++)
	{
		Variance=pow((*(Magnetic_field_after_filtering+i)-Medium),2)/(N-1);	
	}
	return Variance;
}
