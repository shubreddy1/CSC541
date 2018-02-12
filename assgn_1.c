#include<stdio.h>
#include<string.h>
#include<sys/time.h>

//######################Disk based binary###########################
int main()
{
struct timeval t1,t2;
FILE *fp1,*fp2;
fp1=fopen("seek.db","rb");
fp2=fopen("key.db","rb");

int size1;

fseek(fp1,0L,SEEK_END);
size1=ftell(fp1)/sizeof(int);
int seek_array[size1];
rewind(fp1);
int i=0;
for(i=0;i<size1;i++)
{
fread(&seek_array[i],sizeof(int),1,fp1);
}
fseek(fp2,0L,SEEK_END);
int cntr=ftell(fp1)/sizeof(int);
rewind(fp2);

int j=0;
int hit[size1];
int flag=0;
int to_search=0;
FILE *fp=fopen("out1.txt","wb");
gettimeofday( &t1, NULL ); 
char vdtr=getc(fp2);
int val=0;
int tmp=0,mid=0,hi,lo;
gettimeofday( &t1, NULL ); 
for(i=0;i<size1;i++) //size1
{	
	//vdtr=getc(fp2);
	hi=cntr-1;
	lo=0;
	flag=0;val=0;
	to_search=seek_array[i];
	fseek(fp2,0L,SEEK_SET);
	while(hi-lo>1)
	{
		mid=(hi+lo)/2;
		fseek(fp2,(mid-1)*sizeof(int),SEEK_SET);
		fread(&tmp,sizeof(int),1,fp2);
		//printf("%d	%d	\n",lo,hi);
		if(to_search==tmp)
		{
		flag=1;
		break;
		}
		else
		if(to_search<tmp)
		{
		hi=mid-1;
		}
		else
		{
		lo=mid+1;
		}	
	}
	//printf("%d	%d	\n",lo,hi);
	fseek(fp2,(lo-1)*sizeof(int),SEEK_SET);
	fread(&tmp,sizeof(int),1,fp2);
	fread(&val,sizeof(int),1,fp2);
	//printf("%d	%d	\n",lo,hi);
	if(tmp==to_search||val==to_search)
	{
	flag=1;
	}
	if(flag)
	{
		fprintf(fp,"%12d: Yes\n",seek_array[i]);
		hit[i]=1;
	}
	else
	{
		fprintf(fp,"%12d: No\n",seek_array[i]);
		hit[i]=0;
	}
}
gettimeofday( &t2, NULL ); 							//###############################
fprintf(fp,"Time: %ld.%06ld\n",t2.tv_sec-t1.tv_sec,t2.tv_usec-t1.tv_usec);	//conversion required
fclose(fp);
}

//###################Disk based sequential#####################
/*
int main()
{
struct timeval t1,t2;
FILE *fp1,*fp2;
fp1=fopen("seek.db","rb");
fp2=fopen("key.db","rb");

int size1;

fseek(fp1,0L,SEEK_END);
size1=ftell(fp1)/sizeof(int);
int seek_array[size1];
rewind(fp1);
int i=0;
for(i=0;i<size1;i++)
{
fread(&seek_array[i],sizeof(int),1,fp1);
}
fseek(fp2,0L,SEEK_END);
int cntr=ftell(fp1)/sizeof(int);
rewind(fp2);

int j=0;
int hit[size1];
int flag=0;
int to_search=0;
FILE *fp=fopen("out1.txt","wb");
gettimeofday( &t1, NULL ); 
char vdtr=getc(fp2);
int val=0;
int tmp=0;
gettimeofday( &t1, NULL ); 
for(i=0;i<size1;i++) //size1
{	
	//vdtr=getc(fp2);
	flag=0;val=0;
	to_search=seek_array[i];
	fseek(fp2,0L,SEEK_SET);
	while(val<cntr)
	{	val+=1;
		fread(&tmp,sizeof(int),1,fp2);
		if(tmp==to_search)
		{
			flag=1;
			break;
		}
	}	
	if(flag)
	{
		fprintf(fp,"%12d: Yes\n",seek_array[i]);
		hit[i]=1;
	}
	else
	{
		fprintf(fp,"%12d: No\n",seek_array[i]);
		hit[i]=0;
	}
}
gettimeofday( &t2, NULL ); 							//###############################
fprintf(fp,"Time: %ld.%06ld\n",t2.tv_sec-t1.tv_sec,t2.tv_usec-t1.tv_usec);	//conversion required
fclose(fp);
}
*/




//###############in-memory binary#################
/*
int main()
{
struct timeval t1,t2;
FILE *fp1,*fp2,*fp3;
fp1=fopen("seek.db","rb");
fp2=fopen("key.db","rb");

int size1;

fseek(fp1,0L,SEEK_END);
size1=ftell(fp1)/sizeof(int);
int seek_array[size1];
rewind(fp1);
int i=0;
for(i=0;i<size1;i++)
{
fread(&seek_array[i],sizeof(int),1,fp1);
}

int size2;
fseek(fp2,0L,SEEK_END);
size2=ftell(fp2)/sizeof(int);
int key_array[size2];
rewind(fp2);
int k=0;
for(i=0;i<size2;i++)
{
fread(&k,sizeof(int),1,fp2);
key_array[i]=k;
}
int j=0;
int hit[size1];
int flag=0,mid,lo,hi;
int to_search=0;
FILE *fp=fopen("out1.txt","wb");
gettimeofday( &t1, NULL ); 
for(i=0;i<size1;i++) //size1
{
	flag=0;
	to_search=seek_array[i];
	hi=size2-1;
	lo=0;
	
	while(hi-lo>1)
	{	//printf("%d	%d	\n",lo,hi);
		mid=(hi+lo)/2;
		if(to_search==key_array[mid])
		{
		flag=1;
		break;
		}
		else
		if(to_search<key_array[mid])
		{
		hi=mid-1;
		}
		else
		{
		lo=mid+1;
		}	
	}
	//printf("%d	%d	\n",lo,hi);
	if(key_array[lo]==to_search || key_array[hi]==to_search)
	{
	flag=1;
	}
	if(flag)
	{
		fprintf(fp,"%12d: Yes\n",seek_array[i]);
		hit[i]=1;
	}
	else
	{
		fprintf(fp,"%12d: No\n",seek_array[i]);
		hit[i]=0;
		flag=0;
	}
}
gettimeofday( &t2, NULL ); 
fprintf(fp,"Time: %ld.%06ld\n",t2.tv_sec-t1.tv_sec,t2.tv_usec-t1.tv_usec);
fclose(fp);
}

*/










//##################### in memory search ###########################
/*
int main()
{
struct timeval t1,t2;
//printf("hello world");
FILE *fp1,*fp2,*fp3;
// in memory read or part 1
fp1=fopen("seek.db","rb");
fp2=fopen("key.db","rb");

int size1;

//finding length and creating array for keys
fseek(fp1,0L,SEEK_END);
size1=ftell(fp1)/sizeof(int);
int seek_array[size1];
rewind(fp1);
int i=0;
for(i=0;i<size1;i++)
{
fread(&seek_array[i],sizeof(int),1,fp1);
//fseek(fp1,sizeof(int),SEEK_CUR);
}

//for(i=0;i<100;i++)
//{
//printf("%d\n",key_array[i]);
//}

//printf("%d",size1);

//finding length and creating array for seek
int size2;
fseek(fp2,0L,SEEK_END);
size2=ftell(fp2)/sizeof(int);
//printf("%d seek   %d keys",size1,size2);
int key_array[size2];
rewind(fp2);
int k=0;
for(i=0;i<size2;i++)
{
fread(&k,sizeof(int),1,fp2);
key_array[i]=k;
//fseek(fp2,sizeof(int),SEEK_CUR);
//printf("%d\n",key_array[i]);
}
int j=0;

//FILE *ftemp1,*ftemp2;
//ftemp1=fopen("seek.txt","wb");
//ftemp2=fopen("keys.txt","wb");
//for(j=0;j<size1;j++)
//	{
//		fprintf(ftemp1,"%12d\n",seek_array[j]);
//	}
//for(j=0;j<size2;j++)
//	{
//		fprintf(ftemp2,"%12d\n",key_array[j]);
//	}
//fclose(ftemp1);
//fclose(ftemp2);
int hit[size1];
int flag=0;
int to_search=0;
FILE *fp=fopen("out1.txt","wb");
gettimeofday( &t1, NULL ); 
//printf( "Seconds: %d\n", t1.tv_sec ); 
//printf( "Microseconds: %d\n", t1.tv_usec );
for(i=0;i<size1;i++)
{
	//flag=0;
	to_search=seek_array[i];
	//printf("%12d\n",to_search);
	for(j=0;j<size2;j++)
	{
		if(to_search==key_array[j])
		{//printf("cert %d    \n",to_search);
		flag=1;
		break;}
	}
	if(flag)
	{
		fprintf(fp,"%12d: Yes\n",seek_array[i]);
		flag=0;
		hit[i]=1;
	}
	else
	{
		fprintf(fp,"%12d: No\n",seek_array[i]);
		hit[i]=0;
		flag=0;
	}
}
gettimeofday( &t2, NULL ); 
//printf( "Seconds: %d\n", t2.tv_sec ); 
//printf( "Microseconds: %d\n", t2.tv_usec );
fprintf(fp,"Time: %ld.%06ld\n",t2.tv_sec-t1.tv_sec,t2.tv_usec-t1.tv_usec);
fclose(fp);
//printf("%d seek   %d keys",size1,size2);
}
*/
