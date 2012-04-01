#define nume "inversiuni"

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
template<class T> inline void Swap(T& a,T& b){a^=b,b^=a,a^=b;}

int n,x;
pair<vector<int>,long long> merge(vector<int> b, vector<int> c)
{
    long long count=0;
    vector<int> d;
    reverse(b.begin(),b.end());
    reverse(c.begin(),c.end());
    while(!b.empty() && !c.empty()){
        if(b.back()>c.back()){
            count+=b.size();
            d.push_back(c.back());
            c.pop_back();
        }
        else{
            d.push_back(b.back());
            b.pop_back();
        }
    }
    while(!b.empty())
        d.push_back(b.back()),
        b.pop_back();
    while(!c.empty())
        d.push_back(c.back()),
        c.pop_back();
    return make_pair(d,count);
}
pair<vector<int>,long long> mergesort(vector<int> v)
{
    if(v.size()<=1)
        return make_pair(v,0);
    pair<vector<int>,long long> a=mergesort(vector<int>(v.begin(),v.begin()+v.size()/2));
    pair<vector<int>,long long> b=mergesort(vector<int>(v.begin()+v.size()/2,v.end()));
    pair<vector<int>,long long> c=merge(a.first,b.first);
    return make_pair(c.first,a.second+b.second+c.second);
    
}
int main()
{
    #ifdef _PARSARE_
    freopen(nume ".in","r",stdin);
    cit(n);
    #endif
    
    vector<int> v;
    while(!fin.eof())
    {
        fin>>n;
        if(fin.eof())
            break;
        v.clear();
        for(int i=0;i<n;++i)
            fin>>x,v.push_back(x);
        fout<<mergesort(v).second<<'\n';
    }

    fout.close();
    return 0;
}
