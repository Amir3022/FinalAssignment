#include<string>
#include<iostream>
#include<cmath>
using namespace std;
typedef int QueueElemType;
const int maxarraysize=1000;
class Queue
{
    public:
    Queue(int size);
    bool enqueue(const QueueElemType &e, int p);
    QueueElemType dequeue();
    QueueElemType frontElem();
    QueueElemType rearElem();
    int frontPri();
    bool IsEmpty();
    bool IsFull();
    int nextposition(int x);
    int previousposition(int x);
    bool search(int x,int y);
    void printelements();
    private:
    struct node
    {
        QueueElemType item;
        int priority;
    };
    node Elements[maxarraysize];
    int front;
    int rear;
    int maxqueuesize;
};

Queue::Queue(int size)
{
    front=0;
    rear=0;
    maxqueuesize=size;
}

bool Queue::enqueue(const QueueElemType &e, int p)
{
    if(!IsFull())
    {
        if(IsEmpty())
        {
            rear=nextposition(rear);
            Elements[rear].item=e;
            Elements[rear].priority=p;
            return true;
        }
        else
        {
            int i=nextposition(front);
            /*while(i!=nextposition(rear)&&(e>Elements[i].item||p>Elements[i].priority))
            {
                i=nextposition(i);
            }*/

            if (p<Elements[i].priority)
            {
                goto L;
            }            
            while(i!=nextposition(rear))
            {
                if(p>Elements[i].priority)
                {
                    i=nextposition(i);
                }
                else
                {
                    if(e>Elements[i].item)
                    {
                        i=nextposition(i);
                    }
                    else
                    {
                        break;
                    }
                    
                }
                
            }
            L:if(previousposition(i)==rear)
            {
                Elements[i].item=e;
                Elements[i].priority=p;
                rear=nextposition(rear);
                return true;
            }
            else
            {
                int j=rear;
                while(j!=previousposition(i))
                {
                    Elements[nextposition(j)]=Elements[j];
                    j=previousposition(j);
                }
                rear=nextposition(rear);
                Elements[i].item=e;
                Elements[i].priority=p;
                return true;

            }
            
        }
        
    }
    else
    {
        return false;
    }
    
}

QueueElemType Queue::dequeue()
{
    if(!IsEmpty())
    {
        front=nextposition(front);
        return Elements[front].item;
    }
    else return -1;
}

QueueElemType Queue::frontElem()
{
    if(!IsEmpty())
    {
        return Elements[nextposition(front)].item;
    }
    else return -1;
}

int Queue::frontPri()
{
    if(!IsEmpty())
    {
        return Elements[nextposition(front)].priority;
    }
    else return -1;
}

QueueElemType Queue::rearElem()
{
    if(!IsEmpty())
    {
        return Elements[rear].item;
    }
    else return -1;
}

int Queue::nextposition(int x)
{
    if(x==maxqueuesize-1)
    {
        return 0;
    }
    else
    {
        return x+1;
    }
}

int Queue::previousposition(int x)
{
    if(x==0)
    {
        return maxqueuesize-1;
    }
    else
    {
        return x-1;
    }
    
}

bool Queue::IsEmpty()
{
    return front==rear;
}

bool Queue::IsFull()
{
    return nextposition(rear)==front;
}

bool Queue::search(int x,int y)
{
    if(IsEmpty())
    {
        return false;
    }
    else
    {
        int i=nextposition(front);
        while(i!=nextposition(rear))
        {
            if(x==Elements[i].item&&y==Elements[i].priority)
            {
                return true;
            }
            i=nextposition(i);
        }
        return false;
    }
    
}

void Queue::printelements()
{
    if(!IsEmpty())
    {
        int i=nextposition(front);
        while(i!=nextposition(rear))
        {
            cout<<Elements[i].item<<'\t'<<Elements[i].priority<<endl;
            i=nextposition(i);
        }
    }
}

int maxseq;
int seqNumBits;
int winSize;
int initSeq;
int packets[1000];
int numofpackets=0;
void generatequeues();
void generatewindow(int *x,int *k,int y,int z);
void addtorecieved(Queue &x,int y,int z);
void addtowaiting(Queue &x,int y,int z);
void addtodropped(Queue &x,int y,int z);


int main(int argc,char *argv[])
{
    string temp;
    bool error=false;
    if(argc<5)
    {
        cout<<"Invalid number of arguments"<<endl;
        return 0;
    }
    temp=argv[1];
    if(temp.find_first_not_of("123456789")!=string::npos)
    {
        cout<<"Invalid seqNumBits"<<' ';
        error=true;
        maxseq=1000000;
    }
    else
    {
        seqNumBits=stoi(temp);
        maxseq=pow(2,seqNumBits)-1;
    }
    temp=argv[2];
    if(temp.find_first_not_of("0123456789")!=string::npos||stoi(temp)<=0||stoi(temp)>maxseq)
    {
        cout<<"Invalid winSize"<<' ';
        error=true;
    }
    else
    {
        winSize=stoi(temp);
    }
    temp=argv[3];
    if(temp.find_first_not_of("0123456789")!=string::npos||stoi(temp)<0||stoi(temp)>maxseq)
    {
        cout<<"Invalid initSeq"<<' ';
        error=true;
    }
    else
    {
        initSeq=stoi(temp);
    }
    for(int i=4;i<argc;i++)
    {
        temp=argv[i];
        if(temp.find_first_not_of("0123456789")!=string::npos||stoi(temp)<0||stoi(temp)>maxseq)
        {
            cout<<"Invalid packet ID"<<endl;
            return 0;
        }
        else
        {
            packets[i-4]=stoi(temp);
            numofpackets++;
        }
    }
    if(error)
    {
        return 0;
    }
    generatequeues();
}


void generatequeues()
{
    int expected=initSeq;
    int window[1000];
    int windowpri[1000];
    Queue R(1000);
    Queue W(1000);
    Queue D(1000);
    int Rp=1;
    int wp=1;
    int Dp=1;
    generatewindow(window,windowpri,expected,Rp);
    for(int i=0;i<numofpackets;i++)
    {
        for(int k=0;k<winSize;k++)
        {
            if(packets[i]==window[k])
            {
                wp=windowpri[k];
                break;
            }
        }
        if(packets[i]==expected)
        {   
            int temp=packets[i];
            addtorecieved(R,temp,Rp);
            expected++;
            if(expected>maxseq)
            {
                expected=expected-maxseq-1;
                Rp++;
            }
            generatewindow(window,windowpri,expected,Rp);
        }
        else if(R.search(packets[i],wp))
        {   
            addtodropped(D,packets[i],Dp);
            Dp++;
        }
        else if(W.search(packets[i],wp))
        {
            addtodropped(D,packets[i],Dp);
            Dp++;
        }
        else
        {
            bool found=false;
            for(int j=0;j<winSize;j++)
            {
                if(packets[i]==window[j])
                {
                    found=true;
                    wp=windowpri[j];
                    break;
                }     
            }
            if(found)
            {
                int temp=packets[i];
                addtowaiting(W,temp,wp);
            }
            else
            {
                int temp=packets[i];
                addtodropped(D,temp,Dp);
                Dp++;
            }
        }
        while(expected==W.frontElem())
        {
            int temp=W.dequeue();
            addtorecieved(R,temp,Rp);
            expected++;
            if(expected>maxseq)
            {
                expected=expected-maxseq-1;
                Rp++;
            }
            generatewindow(window,windowpri,expected,Rp);
        }
        
    }
    cout<<"R ";
    while(!R.IsEmpty())
    {
        cout<<R.dequeue()<<' ';
    }
    cout<<"E "<<expected<<' ';
    cout<<"W ";
    while(!W.IsEmpty())
    {   
        cout<<W.dequeue()<<' ';
    }
    cout<<"D ";
    while(!D.IsEmpty())
    {
        cout<<D.dequeue()<<' ';
    }
    cout<<endl;

}

void generatewindow(int *x,int *k,int y,int z)
{
    int temp;
    int pri=z;
    for(int i=0;i<winSize;i++)
    {
        temp=y+i;
        if(temp>maxseq)
        {
            temp=temp-maxseq-1;
            pri=z+1;
        }
        x[i]=temp;
        k[i]=pri;
    }
}

void addtorecieved(Queue &x,int y,int z)
{
    int pri=z;
    bool temp=x.enqueue(y,pri);
}

void addtowaiting(Queue &x,int y,int z)
{
    int pri=z;
    x.enqueue(y,pri);
}

void addtodropped(Queue &x,int y,int z)
{
    int pri=z;
    x.enqueue(y,z);
}