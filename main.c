//
//  proj_new.c
//  proj
//
//  Created by Sughosh Divanji on 11/19/13.
//  Copyright (c) 2013 Sughosh Divanji. All rights reserved.
//

#include <stdio.h>


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define infinity 999




//Global vars and function declaration

int cost [100][100];
int check_valid_char(char *);

void my_atoi (char []) ;
int path [10];

int i,j,k;//variables to hold length of array and dimension of cost matrix respectively

//Function to read the input file and store the contents as a matrix.
int read_file (char fname[100])
{
    
    FILE* fd = NULL;
    
    int x,y;
    char buff[65535];
    //char nbytes;
    memset(buff,0,sizeof(buff));
    fd= fopen(fname, "rw+");//read the input file
    if(NULL==fd)
    {
        printf("\nError in reading file\n");
        return 0;
    }
    
    printf("\n File opened succesfully\n" );
    /*
    nbytes= fread(buff, sizeof (char),sizeof(buff),fd);
    if (nbytes==0) {
        printf("\n fread() failed\n");
        return 0;
    }
     */
    
    //Read the input file line by line
    
    while (!feof(fd)) {
     
        fgets(buff, sizeof (buff), fd);
        //printf("Line is %s\n", buff);
        //printf("\n Line read succesfully\n");
        
       // if(strcmp(buff, "")) {
        //    continue;
        //}
    
    
    //Check for a valid number
    if (!(check_valid_char(&buff[i] ))) {
        printf("\n Input contains invalid data\n");
        return 0;
    }
    
    //Convert the string in input file to an integer number to be stored in the matrix
    my_atoi(buff);
    
        j++;
    
    }
    
    
    if(j!=k) {
        j--;
        k=j;
    }
    
    
    printf("Original routing table is \n");
    for (x=0;x<j;x++){
        
        for(y=0;y<k;y++){
            
            if (cost[x][x]!=0){
             printf("\n Invalid data format\n");
             return 0;
             }
            printf("%d\t", cost[x][y]);
        }
        printf("\n");
    }
    return 1;
}

//Function to convert the string in input file to an integer number
void my_atoi (char str[4096]) {
    
    char *pch;
    int res=0,x,nflag=0,tmp;
    unsigned long size;
    //char mybuff[1024];
    
    //split the line when there is a space
    pch=strtok(str," ");
    k=0;
    while (pch){
        
        size=strlen(pch);
        
        
        //Remove the newline character at the end of the line
        if(pch[size-1] == '\n') {
            pch[size-1]='\0';
        }
        
        //extract individual digits
        for(x=0;x<size;x++) {
            if((int)pch[x] == 0x2d) {
                //printf("Negative number\n");
                nflag =1;
                continue;
                
            }
            
            //ignore the null character at the end of string
            if(pch[x]=='\0') {
                size=size-1;
                break;
            }
           
           //get the integer number from individual string elements
            //printf("pch[x] is %d\n", pch[x]);
            tmp=res;
           res=(res*10)+(pch[x]-'0');
            //printf("res is %d\n",res);
            
            //take care of -ve numbers
            if(nflag==1) {
                res*=-1;
                //printf("Neg res is %d\n",res);
            }
        }
        
        
        
        
        //stor the number in a matrix
        
        cost[j][k]=res;
        //printf("j is %d, k is %d and cost[j][k] is %d\n", j,k,cost[j][k]);
        k++;
        ++pch;
        
        //reset the temp var and  the flags
        res=0;
        nflag=0;
        
        //keep splitting the line at spaces till you encounter null character
        pch=strtok(0," ");
        
    }
    
}

//Function to check if the contents of the input file are valid numbers
int check_valid_char(char *str){
    
    // Handle negative numbers.
    //
    if (*str == '-')
    {
        ++str;
        if(isdigit(*str)) {
            //printf("Negative number\n");
            ++str;}
        else {
            printf("\n Invalid data format\n");
            return 0;
        }
    }
    
    
    // Handle empty string or just "-".
    //
    if (!*str)
        return 0;
    // Check for non-digit chars in the rest of the stirng.
    //
    while (*str)
    {
        if (!isdigit(*str) && !isspace(*str) && !(*str=='-')) {
            //printf("*str is %c and is inavlid\n", *str);
            return 0;
            
        }
        else {
            ++str;
        }
    }
    
    return 1;
}

//Function to insert the intermediate nodes in shortest path

void insert_path( int path[10], int u, int pos){
    //shift the array element by one place to right
    path[pos+1]=path[pos];
    //insert the intermediate node at the previous position
    path[pos]=u;
}

//function to find position of the last node in the shortest path array
int find_pos(int w, int size) {
    
    int i,pos;
    for( i=0;i<size; i++) {
        //search the array for the last node
        if(path[i]==w){
            pos=i;
        }
    }
    //return its position
    return pos;
}


//Dijkstra's algorithm to build the routing table
void dij(int n,int v,int cost[100][100],int dist[])
{
    int i,u,count,w,flag[10],min;
    
    //Initialization
    for(i=0;i<n;i++){
        flag[i]=0,dist[i]=cost[v][i];
        if(dist[i]==-1){
            dist[i]=infinity;
        }
    }
    count=1;
    
    //FInd the node having min cost to the source node. Assuming the max cost to be 99.
    while(count<n)
    {
        min=99;
        for(w=0;w<n;w++){
            if(dist[w]<min && !flag[w] && dist[w]>0){
                min=dist[w],u=w;
            }
        }
        
        flag[u]=1;
        count++;
        
        //Relaxation of neighbors
        for(w=0;w<n;w++) {
            if(((dist[u]>0) && (dist[w]>0) && (cost[u][w]>0)) &&(dist[u]+cost[u][w]<dist[w]) && !flag[w]) {
                dist[w]=dist[u]+cost[u][w];
            }
        }
    }
}


//Find shortest path from source to destination
void shortest_path(int n,int v,int cost[100][100],int dist[],int dst)
{
    
    //Initialization
    int i,u,count,w,flag[100],min,size,pos;
    for(i=0;i<n;i++){
        flag[i]=0,dist[i]=cost[v][i];
        if(dist[i]==-1){
            dist[i]=infinity;
        }
    }
    count=1;
    
    //Find the node with min cost from source to destination
    while(count<n)
    {
        min=99;
        for(w=0;w<n;w++){
            if(dist[w]<min && !flag[w] && dist[w]>0){
                min=dist[w],u=w;
            }
        }
        
        flag[u]=1;
        count++;
        
        //Relaxation
        for(w=0;w<n;w++) {
            if(((dist[u]>0) && (dist[w]>0) && (cost[u][w]>0)) &&(dist[u]+cost[u][w]<dist[w]) && !flag[w]) {
                dist[w]=dist[u]+cost[u][w];
                
                //If the relaxed node is the destination, insert the current min node into the shortest path array and exit the loop. Else keep looping.
                if (w==dst) {
                    size=sizeof(path);
                    pos=find_pos(w,size);
                    insert_path(path,u,pos);
                    break;
                }
            }
        }
    }
}


int main(void) {
    
    int choice,status,n,v,dist[100],i,dst,pos,size,tmp,zflag=0;
    char fname[100];
	
    
    
    printf("\nMenu\n");
    printf("\n1-Load File\n"
           "\n2-Build Routing Table for Each Router\n"
           "\n3-Out Optimal Path and Minimum Cost\n");
    
    while (1) {
        printf("\nEnter the option between 1 & 3  to execute the program. Enter any other value to exit.\n");
        scanf ("%d", &choice);
        
        
        switch (choice) {
            //Enter the input file name. If its not in the same path as the source file, provide full path.
            case 1:
                i=0,j=0,k=0;
                memset(cost, 0, 10000);
                printf("\n Enter the file name with full path\n");
                scanf ("%s", fname);
                status = read_file (fname);
                break;
            
             //Enter the router for which thre routing table has to be built (0 for R0, 1 for R1 etc.) after the file has been succesfully read.
            case 2:
                if(!status)
                {
                    printf("File not read succesfully yet\n");
                    break;
                }
                n=j;// no. of nodes is equal to either dimension of matrix.
                printf ("\n Please select a router\n");
                scanf("%d", &v);
                dij(n,v,cost,dist);
                printf("\nRouting table for router %d is\n", v );
                for(i=0;i<n;i++) {
                    if(i!=v) {
                        printf("\n %d->%d cost =%d\n", v,i,dist[i]);
                    }
                }
                break;
                
            //Once the routing table is built for all routers, find the shortest distance between the source and the destination.
            case 3:
                printf("Please enter the source and destination router number\n");
                scanf("%d %d", &v, &dst);
                printf("Source is %d and destination is %d\n",v,dst);
                path[0]=v;
                path[1]=dst;
                zflag=0;
                if(dst==0) {
                    tmp=v;
                    v=dst;
                    dst=tmp;
                    zflag=1;
                }
                
                shortest_path(n,v,cost,dist,dst);
                //printf("ALgo complete\n");
                //printf("Shortest path from %d to %d is \n ", v, dst);
                
                size=sizeof(path);
                pos=find_pos(dst,size);
                if(!zflag) {
                for(i=0;i<=pos;i++){
                    printf("%d->",path[i]);
                    
                }
                }
                else {
                    for(i=pos;i>=0;i--) {
                        printf("%d->",path[i]);
                    }
                    printf("%d->",v);
                }
                printf("and the cost is %d\n", dist[dst]);
                memset(path, 0, sizeof(path));//flush the array after use.
                break;
            
                // Enter any value outside of 1-3 to exit the program
            default:
            
                exit(0);
                
                
                
        }
        
    }
    
}
