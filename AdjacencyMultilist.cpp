/**************************************"AM head file"******************************************/
#ifndef AM_H
#define AM_H
//ÁÚ½Ó¶àÖØ±í 
#define MAX_NODE_NUM  10
#define error         0 
#define success       1

#include <iostream>
#include <vector>
using namespace std;

class AM
{
	struct edge{
		int mark;
		int inode;
		struct edge *ilink;
		int jnode;
		struct edge *jlink;
	};
	
	typedef struct{
		int data;
		struct edge *firstedge;
	}Node;
	
	typedef struct{
		Node head[MAX_NODE_NUM];
		int vexnum,edgenum;
	}AMLGraph;
	AMLGraph G;
	vector<int> visited,queue;
	public:
		int create(int vexnum,vector<vector<int>> &edgelist);
		void print();
		void DFStraver();
		int DFS(int i);
		void BFStraver();
		int BFS(int i); 
};
#endif

/*************************************"AM cpp file"*******************************************/
#include "AM.h"
#include <iostream>
using namespace std;

//创建邻接表
int AM::create(int vexnum,vector<vector<int>> &edgelist){
	int i,j;
	edge *p;
	if(vexnum > MAX_NODE_NUM)
		return error;
	G.vexnum = vexnum;
	G.edgenum = edgelist.size();
	for(i=0;i<vexnum;i++)
		G.head[i].firstedge = NULL;
	for(i=0;i<edgelist.size();i++){
		p = (edge*)malloc(sizeof(edge));
		if(!p)
			return error;
		p->mark = 1;
		p->inode = edgelist[i][0];
		p->jnode = edgelist[i][1];
		p->ilink = G.head[p->inode].firstedge;
		p->jlink = G.head[p->jnode].firstedge;
		G.head[p->inode].firstedge = p;
		G.head[p->jnode].firstedge = p;
	}
	return success;
}

//深度遍历
void AM::DFStraver(){
	int i;
	for(i=0;i<G.vexnum;i++)
		visited.push_back(false); 
	for(i=0;i<G.vexnum;i++){
		if(!visited[i])
			DFS(i);
	}
}
int AM::DFS(int i){
	edge *p;
	p = G.head[i].firstedge;
	if(visited[i])
		return 0;
	cout << i << endl; //´òÓ¡½ÚµãºÅ 
	visited[i] = true;
	while(p){
		if(p->jnode == i){
			DFS(p->inode);
			p = p->ilink;
		}
		else{
			DFS(p->jnode);
			p = p->jlink;
		}
	}
}

//广度遍历
void AM::BFStraver(){
	int i,cur,next;
	edge *p;
	for(i=0;i<G.vexnum;i++) //Êý×é±êÖ¾ 
		visited.push_back(false); 
	for(i=0;i<G.vexnum;i++){
		if(!visited[i]){
			visited[i] = true;
			queue.push_back(i);
			while(!queue.empty()){
				cur = queue[0];
				cout << cur << endl;
				queue.erase(queue.begin());
				p = G.head[cur].firstedge; 
				while(p){
					next = p->inode == i ? p->jnode : p->inode;
					if(!visited[next]){
						queue.push_back(next);
						visited[next] = true;	
					}
					p = p->inode == i ? p->ilink : p->jlink;
				}
			}
		}
	}
}