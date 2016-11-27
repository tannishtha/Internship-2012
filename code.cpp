#include <iostream>
using namespace std;
#define MAX 4
#define CONST 100
class fuzzy_graph
{
  public:
    class arr   //class to store all the possible paths between source and     
    {         //destination 
	    public:
		    int num;
        arr *left;
        arr(){left=NULL;}
		    arr(int x)
          {num=x;left=NULL;}
		    ~arr(){}
     };
     
     struct flength  //structure to store the fuzzy length of an edge
     { 
        float grade; 
        int length;
     };
     
     class e_node    //class for the adjacent vertices of a vertex           
	   {
	      public:
		      int data;
          flength arr[MAX];
          e_node *next;
          e_node(){next=NULL;}
		      e_node(int x)
          { 
             data =x;
             for(int i=0;i<MAX;i++)
              {arr[i].length=0;}
	           next=NULL;
          }
         ~e_node(){}
	    };
      
      class v_node   //class for storing all vertices of the graph
	    {
	      public:
		      int vertex;
          e_node *edge; 
          v_node(){edge=NULL;}
		      ~v_node(){}
	    };
	    
      class node   //class to store Lmin
	    {
	      public:
		      int data;
          float y;
          node *next;
          node(){next=NULL;}
       }; 
	
      class len_node  //class for storing the discrete fuzzy lengths of the possible paths
	    {                  
	      public:
		      int num;
          node *next;
          len_node(){next=NULL;}
	    };
	
      class pd        //class to store the predecessors of a vertex which occur twice in the predecessor matrix
	    {               
	      public:
		      int number;
          int pred;
          pd *next;
          pd(){next=NULL;}
		      pd(int x){number=x; next=NULL;}
		      ~pd(){}
	    };
      
      int size; 
      v_node *adjlist; 
      int queue[CONST];
      int front,rear;
	    int source,destination; 
      int **pred; 
      int *p;
      arr *head;
      arr *path;
      int count; 
      len_node *len;
      int m;
      pd *head;
      node *min_len;
      float *result;
	    
      fuzzy_graph(int t)
	    {
        size=t;
        count=0;
        front=rear=-1;
        adjlist=new v_node[t];
	      for(int i=0;i<t;i++) 
        {
            adjlist[i].vertex=(i+1);
            adjlist[i].edge=NULL;
        }
        p=new int[t];
        for(int i=0;i<size;i++)
          {p[i]=0;}
	      head=NULL; 
        min_len=NULL; 
        path=NULL; 
        head1=NULL;
	    }
      
      ~fuzzy_graph()
       {
        delete []adjlist;
        delete []p;
       }
    
      void make_list()  //function to store the adjacency list for storing the graph
	    {
        int ver,arc;
        float member;   
	      cout << "\nEnter the vertices adjacent to each vertex.\nFor no     adjacent vertices or no more adjacent vertices type 0 .";
	      cout << "\nFor each adjacent vertex type the fuzzy arc length.\nFor stop giving the entries to the fuzzy arc length type -1";
	      for(int i=0;i<size;i++)
	      {
          e_node *temp1=adjlist[i].edge;int j=i+1;
	        cout << "\nenter the adjacent vertices of vertex " << j<<" " ;
	        cin >> ver;
	        while(ver!= 0)
	        {
            count++; 
            e_node *ptr=new e_node(ver);
	          cout << "\nNow enter its fuzzy arc lengths:";
	          int k=0; 
            cin >> arc;
	          while(arc!=-1)
	          {
              cin >> member; 
              ptr->arr[k].length=arc;
              ptr->arr[k].grade=member;
              k++;
              cin >> arc;
            }
           if(adjlist[i].edge==NULL)
           {
              adjlist[i].edge=ptr;
              temp1=ptr;
            }
	          else
            {
              temp1->next=ptr;
              temp1=ptr;
            }
	          cout << "\nEnter the next adjacent vertex:";
            cin >> ver;
         }
       }
       
       pred=new int*[size];
       
       for(int i=0;i<size;i++)
          {pred[i]=new int[count];}
	     
       for(int i=0;i<size;i++)
       {
        for(int j=0;j<count;j++)
          {pred[i][j]=-1;}
       }
       
       cout << "\nThe adjacency list is as follows.."<<endl;
       
       for(int i=0;i<size;i++)
	     {
          cout << adjlist[i].vertex << "-->";
          e_node *temp=adjlist[i].edge;
	        while(temp!=NULL)
          {
            cout << temp->data <<"-->";
            temp=temp->next;
          }
	        cout << "\n";
       }
       
       cout << "\nEnter the source:";cin >> source;
	     cout << "\nEnter the destination:"; cin >> destination;
      }
      
    //function to check if queue is empty or not
    bool isempty() 
    {
      if(front==-1) return(true);
      else return(false);
     }
    
    //function to enter the data in the queue
    void enqueue(int data) 
	  {
      if(rear==CONST-1) 
        {cout<<"Queue is full\n";}
      else
      {
        if(rear==-1)
        {
            rear=0;
            front=0;
            queue[rear]=data;
         }
         else
         {
            rear++;
            queue[rear]=data;
          }  
        }
     }

    //function to take out values from the queue
    int dequeue()  
    {
      if(!isempty())
      {
          if(rear==front)
          {
             int k=queue[front];
             rear=front=-1;
             return k;
           }
           else
           {
              int k=queue[front];
              front++;
              return k;
            }
       }	
     }
   
   //function to find the predecessors of each vertex and store it in the predecessor matrix 
   void search()                  
   {
      int x;
      enqueue(source);  
      while(!isempty())
      {
        x=dequeue();
        if(adjlist[x-1].edge!=NULL)
        {
            e_node *temp=adjlist[x-1].edge;
            while(temp!=NULL)
		        {
               int y=temp->data;
               pred[y-1][p[y-1]]=x;
		           if((y)!=destination){enqueue(y);}
		           p[y-1]=p[y-1]+1;
		           temp=temp->next;}}}
            }
            node *add1(flength *pt1, flength *pt2) //function to add two fuzzy sets 
            {
              node *hd=NULL;                      
              for(int i=0; i<MAX && pt1[i].length !=0;i++)
              {
                  for(int j=0; j<MAX && pt2[j].length!=0;j++)
	                {
                      node *pt=new node;pt->data=pt1[i].length + pt2[j].length;
	                    pt->y= min(pt1[i].grade , pt2[j].grade);
                      pt->next=NULL;hd=insertsort(hd,pt);
                   }
               }
	             hd=del(hd);
               return(hd);	
            }

            float min(float x,float y){return(x <= y ? x : y);}
            node *insertsort(node *hd,node *pt)  //function to sort the elements in ascending order after addition of two fuzzy sets
            {
                if(hd==NULL){hd=pt;return hd;}     
	              else
                {
                  node *temp1=NULL;node *temp=hd; 
	                while((pt->data > temp->data) && temp->next!=NULL)
	                {
                      temp1=temp;temp=temp->next;
                  }
	                if(pt->data > temp->data){temp->next=pt;}
	                else{temp1->next=pt;pt->next=temp;}
                  return(hd);
                }
            }
            
            node *add2(node *head,flength *pt2) //function to add the third fuzzy set to the result of addition of two fuzzy sets    
	          {
                node *temp=head;
                node *head1=NULL; 
	              while(temp!=NULL)                
	              {
                    for(int i=0;i<3 && pt2[i].length!=0;i++)
	                  {
                        node *ptr=new node;
                        ptr->data=temp->data + pt2[i].length;
	                      ptr->y=min (temp->y , pt2[i].grade);
                        ptr->next=NULL;
                        head1=insert(head1,ptr);
                    }
	                  temp=temp->next;
                    delete(head);
                    head=temp;
                }
	              head1=del(head1);
                return(head1);
	          }
            float max(float x,float y){return(x >= y ? x : y);}
	
            node *insert(node *head1,node *bc)  //function to sort the elements in ascending order after addition of two fuzzy sets
            {
                if(head1==NULL){head1=bc;return head1;} 
                else
                {
                    node *temp1=NULL;
                    node *temp=head1; 
	                  while((bc->data > temp->data) && temp->next!=NULL)
	                  {
                      temp1=temp;
                      temp=temp->next;
                    }
	                  if(bc->data > temp->data){temp->next=bc;}
	                  else{temp1->next=bc;bc->next=temp;}
                    return head1;
                 }
             }
            
            node *del(node *head1) //function to calculate the maximum of membership grades of the same element after addition of two fuzzy sets 
            {
              node *temp1=head1;
              node *temp=head1->next;
              node *temp2=NULL;
              while(temp !=NULL)                             
              {
                  if(temp1->data != temp->data)                   
                  {
                      temp2=temp1;
                      temp1=temp;
                      temp=temp->next;
                   }    
                  else
                  {
                      if(temp1==head1)
	                    {
                          float t=max(temp1->y,temp->y);
		                      if(t==temp1->y)
                          {
                              temp1->next=temp->next;delete (temp);
                              temp=temp1->next;
                          }
		                      else
                          {
                              delete(temp1);
                              temp1=temp;
                              head1=temp1;
                              temp=temp->next;
                          }
	                     }
                       else
                       {
                          float t=max(temp1->y,temp->y);
                          if(t==temp1->y)
			                    {
                              temp1->next=temp->next;
                              delete (temp);
                              temp=temp1->next;
                          }
			                    else
                          {
                              delete(temp1);
                              temp2->next=temp;
                              temp1=temp;
	                            temp=temp->next;
                           }
                         }
                     } 
                 }
                return(head1);
           }
   
   //function to display the paths and their fuzzy lengths
   void display() 
   {
      cout << "\nThe number of paths from "<<source << " to " <<destination << " are "<< p[destination-1];
      m=p[destination-1];
      len=new len_node[m];
      result=new float[m];
      path=new arr[m];
      for(int i=0;i<m;i++)
      {
          len[i].num=(i+1);
          len[i].next=NULL;
          result[i]=0.0;
          path[i].num=(i+1);
          path[i].left=NULL;
       }
       for(int i=0;i<size;i++){p[i]=0;}
       if(pred[destination-1][0]==-1) return;
       cout << "\nThe paths from "<<source << " to " << destination << " are :"<<endl;int t;pd *uv=NULL,*uv1=NULL;
       for(int i=0;i<size ;i++)
       {
          if(pred[i][1] != -1)
          {
            while(pred[i][p[i]]!=-1)
            {
                if(pred[i][p[i]]==pred[i][p[i]+1] && pred[i][p[i]]!=pred[i][p[i]+2])
	              {
                    uv=new pd(i+1);
                    uv->pred=pred[i][p[i]];
	                  if(head1==NULL){ head1=uv;}
	                  else
                    {
                        uv1=head1;
                        while(uv->pred > uv1->pred && uv1->next!=NULL)
		                    {uv1=uv1->next;}
		                    if(uv->pred==uv1->pred)
                            {uv->next=uv1->next;uv1->next=uv;}
		                    else {uv1->next=uv;}
                     }
                 }
	               p[i]=p[i]+1;
              }
            }
        }
        for(int i=0;i<size;i++){p[i]=0;}
        arr *temp1=NULL,*temp2=NULL,*temp3=NULL,*temp4=NULL;
        while(pred[destination-1][p[destination-1]]!=-1)
        {
            temp1=new arr(destination);
            if(head==NULL){head=temp1;}
            else{temp1->left=head;head=temp1;}
            int k=pred[destination-1][p[destination-1]];
            temp2=new arr(k);
            temp2->left=head;
            head=temp2;
            t=head->num;
            while(pred[t-1][p[t-1]]!=-1)
            {
                if(pred[t-1][p[t-1]]==source && pred[t-1][p[t-1]+1]==-1)
                {
                    temp3=new arr(source);
                    temp3->left=head;
                    head=temp3;
                    break;
                 }
                else if(pred[t-1][p[t-1]]==source && pred[t-1][p[t-1]+1]!=-1)
                {
                    temp3=new arr(source);
                    temp3->left=head;
                    head=temp3;
                    if(head1!=NULL)
                    {
                        if(t==head1->pred && pred[destination-1][p[destination-1]]!=t)
                        {
                            pd *gh=head1->next;
	                          while(gh->number !=pred[destination-1][p[destination-1]+1]  && gh->pred==t && gh!=NULL){gh=gh->next;}
                            if(gh!=NULL && gh->pred==t){p[t-1]=p[t-1];}
                            else {p[t-1]=p[t-1]+1;}
                            break;
                         }
                     }
                     p[t-1]=p[t-1]+1;
                     break;
                 }
                else if(pred[t-1][1]==-1)
                {
                    int ab=pred[t-1][p[t-1]];
                    temp4=new arr(ab);
                    temp4->left=head;
                    head=temp4;
                    t=head->num;
                 }
                else if(pred[t-1][p[t-1]+1]==-1 )
                {
                    int ab=pred[t-1][p[t-1]];
                    temp4=new arr(ab);
                    temp4->left=head;
	                  head=temp4;
                    p[t-1]=0;
                    t=head->num;
                }
                else
	              {
                    int ab=pred[t-1][p[t-1]];
                    temp4=new arr(ab);
                    temp4->left=head;
	                  head=temp4;
                    if(head1!=NULL)
	                  {
                        pd *find=head1;
	                      while(find->pred!=t || head->left->left->num!=find->number)
	                      {
                            if(find->next!=NULL){find=find->next;}
                            else{find=NULL;break;}
                        }
	                      if(find!=NULL && find->number!=destination)
	                      {
                            if(find->next->pred==t && find->next->number==destination)
		                              {p[t-1]=p[t-1]+1;}
	                          else if(find->next->pred==t && find->next->number!=destination)
	                                {p[t-1]=p[t-1];}
	                          else if(find->next->pred!=t && find->next->number==destination)
		                              {p[t-1]=p[t-1]+1;}
		                        else{p[t-1]=p[t-1]+1;}
                        }
		                    else if(find==NULL){p[t-1]=p[t-1]+1;}
		                    else if(find!=NULL && find->number==destination)
		                            {p[t-1]=p[t-1]+1;}
		                    t=head->num;
                    }
		                else{p[t-1]=p[t-1]+1;t=head->num;}
                }
            }
	          p[destination-1]=p[destination-1]+1;
       }
        arr *tempr=head;
        arr *tempr1=NULL;
        arr *pntr=NULL;
        while(tempr!=NULL)
        {
              for(int i=0;i<m;i++)
              {
                  tempr1=&path[i];
	                while(tempr->num != destination)
	                {
                      int x=tempr->num;
                      if(path[i].left==NULL)
	                    {
                          pntr=new arr(x);
                          path[i].left=pntr;
                          tempr1=pntr;
                      }
	                    else{pntr=new arr(x);tempr1->left=pntr;tempr1=pntr;}
                      tempr=tempr->left;
                   }
	                 pntr=new arr(destination);
                   tempr1->left=pntr;
                   tempr=tempr->left;
               }
        }

        arr *temp=head;
        int i=0,y;
        v_node *ptr=NULL;
        e_node *ptr1=NULL,*ptr2=NULL;
        while(temp!=NULL)
        {
          cout << temp->num<<"-->";
          int x=temp->num;
          ptr=&adjlist[x-1];
	        temp=temp->left;
          if(temp->num == destination)
	        {
              cout << temp->num << "\n";
              ptr1=ptr->edge;
	            while(ptr1->data != destination){ptr1=ptr1->next;}
	            node *h=NULL;
              for(int k=0;k<MAX && ptr1->arr[k].length != 0;k++)
	            {
                  node *w=new node;
                  w->data=ptr1->arr[k].length;
	                w->y=ptr1->arr[k].grade;
                  w->next=NULL;
                  if(h==NULL){h=w;}
	                else
                  {
                      node *tr=h;
                      while(tr->next !=NULL){tr=tr->next;}
	                    tr->next=w;
                   }
               }
	             len[i].next=h;
	             cout << "The fuzzy arc length is L["<<len[i].num<<"]=";
	             node *ht=len[i].next;
               while(ht!=NULL)
	             {
                  cout << ht->y << "/" << ht->data << "    ";
                  ht=ht->next;
                }
	              cout << "\n";i++;temp=temp->left;
            }
	          else
            {
                cout<< temp->num<<"-->";
                y=temp->num;
                ptr1=ptr->edge;
		            while(ptr1->data != y){ptr1=ptr1->next;}
		            ptr=&adjlist[y-1];
                temp=temp->left;
                y=temp->num;
                ptr2=ptr->edge;
		            while(ptr2->data!=y){ptr2=ptr2->next;}
		            node *h=add1(ptr1->arr , ptr2->arr );
		            if(y==destination)
                {
                    cout << y << "\n";len[i].next=h;
		                cout << "The fuzzy arc length is L["<<len[i].num<<"]=";
		                node *ht=len[i].next;
		                while(ht!=NULL)
		                {cout << ht->y << "/" << ht->data << "    ";ht=ht->next;}
	                  cout <<"\n";i++;
                    temp=temp->left;
                }
                else
                {
                    cout << y << "-->";
                    temp=temp->left;
                    int az=temp->num;
		                node *hf=h;
		                while(az != destination)
		                {
                        cout << az << "-->";
                        ptr=&adjlist[y-1];
                        ptr2=ptr->edge;
		                    y=temp->num;
                        while(ptr2->data !=az){ptr2=ptr2->next;}
			                  hf=add2(hf,ptr2->arr);
                        temp=temp->left;
                        az=temp->num;
                    }
			              cout << destination << "\n";
                    ptr=&adjlist[y-1];
			              ptr2=ptr->edge;
                    y=temp->num;
			              while(ptr2->data !=destination){ptr2=ptr2->next;}
			              hf=add2(hf,ptr2->arr);
                    temp=temp->left;
                    len[i].next=hf;
			              cout << "The fuzzy arc length is L["<<len[i].num<<"]=";
		                node *ht=len[i].next;
		                while(ht!=NULL)
		                {cout << ht->y << "/" << ht->data << "    ";ht=ht->next;}
                    cout << "\n\n";i++;
                 }
             }
        }
    }
    
   //function to calculate Lmin 
   void min_length()           
   {
      node *potr=NULL;
      node *tn=NULL;
      node *tn1=NULL;
      node *h=NULL;
      node*tp=NULL;
      float q,maximum;
      node *hp=len[0].next;
      while(hp!=NULL)
      {
              q=hp->y;
              for(int j=1 ; j<m  ;j++)
		          {
                  h=len[j].next;
                  maximum=0.0;
		              while(h!=NULL && h->data < hp->data)
		              {
                      maximum=max(maximum,h->y);
                      h=h->next;
                  }
		              q=min(q,(1.0-maximum));
               }
               potr=new node;
               potr->y=q;
               potr->data=hp->data;
               potr->next=NULL;
               if(min_len==NULL){min_len=potr;}
		           else
               {
                  tp=min_len;
                  while(tp->next!=NULL){tp=tp->next;}
                  tp->next=potr;
                }
                hp=hp->next;
      }
      for(int i=1;i<m;i++)
      {
            hp=len[i].next;
            while (hp!=NULL)
            {
                q=hp->y;
                int k=0;
	              while(k<m)
                {
                    if(k!=i)
                    {
                        h=len[k].next;
                        maximum=0.0;
			                  while(h!=NULL && h->data < hp->data)
			                  {
                            maximum=max(maximum,h->y);
                            h=h->next;
                        }
				                q=min(q,(1.0-maximum));
                     }
		                k++;
                }
                tn=min_len;
                tn1=NULL;
                if(hp->data < tn->data)
	              {
                    potr=new node;
                    potr->data=hp->data;
                    potr->y=q;
                    potr->next=min_len;
	                  min_len=potr;
                }
	              else
                {
                    while(hp->data > tn->data  && tn->next!=NULL)
	                    {tn1=tn;tn=tn->next;}
		                if(tn->data == hp->data){tn->y=max(tn->y, q);}
		                else if(tn->next==NULL)
		                      {potr=new node;potr->data=hp->data;potr->y=q;potr->next=NULL;tn->next=potr;}
		                else{ 
                        potr=new node;potr->data=hp->data;potr->y=q;
                        potr->next=tn;tn1->next=potr;
                    }
                }
                hp=hp->next;
            }
      }
      cout << "\nThe fuzzy shortest length is.."<<endl;node *gh=min_len;
	    while(gh !=NULL)
      {
            if(gh->y !=0) {cout << gh->y << "/" << gh->data << "\t";}
		        gh=gh->next;
       }
   }
   
   //function to return absolute value of two floating point numbers
   float abso(float x1,float x2)  
   { 
       if(x1 >= x2){return(x1-x2);} 
        else {return (x2 - x1);}
   }
  
  //function to calculate hamming distance
  void hamming_distance()  
  {
      node *q2=NULL;
      node *q3=NULL;
      int d;
      for(int i=0;i<m;i++)
      {
          float sum=0.0;
          q2=min_len;
          while(q2!=NULL)
	        {
              q3=len[i].next;
              d=q2->data;
              if(d < q3->data ){sum=sum+q2->y;}
	            else{while(q3->data != d && q3->next!=NULL){q3=q3->next;}
		          if(q3->data==d && q3->next!=NULL)
                    {sum=sum + abso(q2->y,q3->y);}
		          else if(q3->data==d && q3->next==NULL)
		                {sum=sum+abso(q2->y,q3->y);}
		          else if(q3->data!=d && q3->next==NULL)
                    {sum=sum+q2->y;}
           }
		      q2=q2->next;
       }
		   float w = sum; 
       result[i] = w;
       int y=i+1;
		   cout << "H(Lmin,L["<<y<<"])= " << result[i]<<endl;
    }
    
    float min=result[0];
    for(int i=1;i<m;i++)
    {
        if(result[i] < min){min=result[i];}
    }
	  int y1;
    for(int i=0;i<m;i++)
    {
        if(min==result[i])
            {y1=i;break;}
     }
     cout << "The lowest Hamming Distance to the fuzzy shortest length is "<<min << " and this corresponds to the path "<<endl;
	   arr *y2=path[y1].left;
	   while(y2 !=NULL)
        {cout << y2->num <<"\t";y2=y2->left;}
   }
};	


void main()
{ 
    int z;
    cout << "\nEnter the number of vertices in the graph:";
    cin >>z;
    fuzzy_graph B(z);
    B.make_list();
    B.search();
    B.display();
    B.min_length();
    cout << "\nThe Hamming Distances are as follows.."<<endl;
    B.hamming_distance();
}
