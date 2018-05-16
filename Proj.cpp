#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<cmath>

using namespace std;

ifstream file;


class heap
{
public:
	int math;
	int eng;
	int gpa;
	int ID;
	double finalscr;
	void setfinalscr(){ finalscr=0.25*eng+0.30*math+0.45*gpa;}

};

int INSERT(heap *scores,int heap_size,int insNo,int IDcounter)
{
	int dbltemp;
	heap tempheap;
	int a=0;
	while(!file.eof() &&a<insNo)
	{
		a++;	
		file>>dbltemp;
		tempheap.eng = dbltemp;
		file>>dbltemp;
		tempheap.math = dbltemp;
		file>>dbltemp;
		tempheap.gpa = dbltemp;
		tempheap.setfinalscr();
		tempheap.ID=IDcounter;

		scores[heap_size] = tempheap;
		cout<<"ID of new applicant = "<<tempheap.ID<<endl;
		heap_size++;
	}
	return heap_size;
}

int UPDATE(heap *A, int heap_size)
{
	if (heap_size>0)
	{
	int changedID = rand() % heap_size+1;
	A[changedID].finalscr+rand()%20-10;
	if(A[changedID].finalscr>100) A[changedID].finalscr = 100;
	else if(A[changedID].finalscr<0) A[changedID].finalscr = 0;
	cout<<"changed ID = "<< changedID<<endl;
	return changedID;
	}
}

void MAX_HEAPIFY(heap *A, int i, int d,int heap_size )
{
		int *children= new int[d];
		int largest = i;

		for(int j=d-1;j>=0;j--)
		{
			children[d-j-1]=(d*i+1)-(j)+(d-1);
		}
		for(int j=0;j<d;j++)
		{
			if(children[j]<=heap_size && A[children[j]].finalscr>A[largest].finalscr) largest = children[j];
		}

		if(largest != i)
		{
			heap temp = A[i];
			A[i]=A[largest];
			A[largest]=temp;
			MAX_HEAPIFY(A,largest,d,heap_size);
		}
}
void BUILD_MAX_HEAP(heap *A,int d, int heap_size)
{
	
	for(int i = floor(heap_size/d)-1;i>=0;i--) MAX_HEAPIFY(A,i,d,heap_size);

}
int REMOVE(heap *A,int heap_size,int d)
{
	int removedID;
	if(heap_size<1)
	{
		cout<<"there aren't any applicant that can be removed!"<<endl;
		return heap_size;
	}
	else
	{
		if(heap_size==1) removedID=1;
		else
		{
			removedID = rand() % (heap_size-1) + 1;
		}
	
		cout<<"Removed ID = "<<removedID<<endl;
		A[removedID-1].finalscr = 0;
		MAX_HEAPIFY(A,removedID-1,d,heap_size);
		return heap_size-1;
	}
	
}
void HEAP_SORT(heap *A,int d, int heap_size,heap *queue)
{
	BUILD_MAX_HEAP(A,d,heap_size);
	int j=0;
	for(int i=heap_size;i>0;i--)
	{
		heap temp = A[0];
		A[0]=A[i];
		A[i]=temp;
		queue[j]=temp;
		j++;
		heap_size--;
		MAX_HEAPIFY(A,0,d,heap_size);
	}
}

int main(int argc, char *argv[])
{
	int d = atoi(argv[1]);
	int M = atoi(argv[2]);
	int N = atoi(argv[3]);
	double p = atof(argv[4]);
	clock_t basl,son;
	file.open("scores.txt");
	string temp;
	file>>temp;
	int heap_size=0;
	int IDcounter=0;
	heap *newHeap = new heap;
	int N;
	basl = clock();
	heap *scores = new heap[M];

	int a ;
	heap *queue=new heap[N];
	srand(time(NULL));
	p=p*10;
	for(int i=0;i<M;i++)
	{
		int pro=rand()%10;
		if(pro<p)	UPDATE(scores,heap_size);		//update yapsýn
		else	// add one more applicant
		{
			IDcounter++;
			heap_size=INSERT(scores,heap_size,1,IDcounter);	
			
		} 
		pro=rand()%10;
		if(pro<2) heap_size = REMOVE(scores,heap_size,d);

	}
	HEAP_SORT(scores,d,heap_size,queue);
	cout<<"Order\t"<<"ID\t"<<"final score"<<endl;
	for(int i=0;i<N&&i<heap_size;i++)
	{
		cout<<i+1<<"\t"<<queue[i].ID<<"\t"<< queue[i].finalscr<<endl;
	}
	son=clock();
	double zaman=static_cast<double>(son-basl)/1000;
	cout<< "Operations is done in " << zaman<<" seconds.";
	return 0;
}