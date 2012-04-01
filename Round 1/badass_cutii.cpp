#define nume "cutii"

#include<cstdio>
#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
#include<string>
#include<sstream>
#include<cstdlib>
#include<queue>
#include<set>
#include<map>
#include<ctime>
#include<list>
#include<algorithm>

using namespace std;

//#define _PARSARE_
#ifdef _PARSARE_
#define DIM 8192
char ax[DIM+16];
int _idx;
template<class T>
inline void cit(T& x)
{
    x=0;
    while((ax[_idx]<'0' || ax[_idx]>'9') && (ax[_idx]!='-'))
        if(++_idx==DIM)fread(ax, 1, DIM, stdin), _idx=0;

    int neg=0;
    if(ax[_idx]=='-') {
        neg=1;
        if(++_idx==DIM)fread(ax, 1, DIM, stdin),_idx=0;
    }

    while(ax[_idx]>='0' && ax[_idx]<='9') {
        x=x*10+ax[_idx]-'0';
        if(++_idx==DIM)fread(ax,1, DIM, stdin),_idx=0;
    }
    if(neg) x=-x;
}
#else
ifstream fin (nume ".in");
#endif //_PARSARE_
ofstream fout(nume ".out");

#define foreach(it, v) for (typeof((v).begin()) it = (v).begin(),stop=(v).end(); it != stop; ++it)
#define foreach_r(it, v) for (typeof((v).rbegin()) it = (v).rbegin(),stop=(v).rend(); it != stop; ++it)
template<class T> inline void Swap(T& a,T& b)
{
    a^=b,b^=a,a^=b;
}

int n,dim;
#define EGAL 0
#define MAI_MIC 1
#define MAI_MARE 2
#define NEDEFINIT -1

vector<int> G[21];
vector<int> v[21];

int cmp(vector<int> a, vector<int> b)
{
    if(a.empty() || b.empty())
        return NEDEFINIT;
    if(a[0]<b[0]){
        for(int i=1;i<a.size();++i)
            if(a[i]>b[i])
                return NEDEFINIT;
        return MAI_MIC;
    }
    else if(a[0]>b[0]){
        for(int i=1;i<a.size();++i)
            if(a[i]<b[i])
                return NEDEFINIT;
        return MAI_MARE;
    }
    else { //egal
        for(int i=1;i<a.size();++i)
            if(a[i]<b[i])
                return NEDEFINIT;
        return EGAL;
    }
        
}
bool viz[21];
vector<int> tmp;
vector<int> rez;
void dfs(int nod)
{
//    cout<<">>"<<nod+1<<'\n';
    viz[nod]=true;
    foreach(it,G[nod]){
        if(!viz[*it])
            dfs(*it);
    }
    tmp.push_back(nod);
}
int prev[21];
int a[21];
vector<int> Q;
vector<int> sol;
inline void afis(int poz)
{
    if(poz == 0) {
        return;
    }
    afis(prev[poz]);
    fout<<a[poz]+1<<' ';
}
inline int bin_search (int val)
{
    int st=-1,dr=Q.size()-1,m;
    while(dr-st>1) {
        m = ((unsigned int)st + (unsigned int)dr) >> 1;
        if(cmp(v[a[Q[m]]], v[val])==MAI_MIC)
            st=m;
        else
            dr=m;
    }
    return dr;
}
inline void scmax()
{
    for(int i=0;i<rez.size();++i)
        a[i+1]=rez[i];
    Q.push_back(1);
    for(int i=2; i<=rez.size(); ++i) {
        if (cmp(v[a[i]], v[a[Q.back()]])==MAI_MARE) {   
            prev[i] = Q.back(); 
            Q.push_back(i);
            continue;
        }
        int p = bin_search(a[i]);
//        assert(p>=0);
        if (cmp(v[a[i]], v[a[Q[p]]])==MAI_MIC) {
            if (p > 0)
                prev[i] = Q[p-1];
            Q[p] = i;
        }
    }
    fout<<Q.size()<<'\n';
    afis(Q.back());
    fout<<'\n';
}
int main()
{
#ifdef _PARSARE_
    freopen(nume ".in","r",stdin);
    cit(n);
#endif

    fin>>n>>dim;

    for(int i=0; i<n; ++i) {
        for(int j=0; j<dim; ++j) {
            int x;
            fin>>x;
            v[i].push_back(x);
        }
        sort(v[i].begin(),v[i].end());
    }

    for(int i=0;i<n;++i)
        for(int j=i+1;j<n;++j){
            int x=cmp(v[i],v[j]);
            if(x==MAI_MARE)
                G[j].push_back(i);
            else if(x==EGAL)
                G[i].push_back(j),
                G[j].push_back(i);
            else if(x==MAI_MIC)
                G[i].push_back(j);
        }
    int Max=0;
    for(int i=0;i<n;++i)
        if(!viz[i])
            dfs(i);
    reverse(tmp.begin(),tmp.end());
    for(int i=0;i<tmp.size();++i)
    {
        int j;
        for(j=i+1;j<tmp.size();++j)
        {
            int x=cmp(v[tmp[i]],v[tmp[j]]);
            if(x!=MAI_MIC && x!=EGAL)
                break;
//                rez.push_back(tmp[i]);
//            else
//            {
//                if(Max<rez.size())
//                {
//                    sol=rez;
//                    sol.push_back(tmp[i]);
//                    Max=sol.size();
//                }
//            }
        }
        if(j>=tmp.size())
            rez.push_back(tmp[i]);
    }
    scmax();

    
    fout.close();
    return 0;
}
