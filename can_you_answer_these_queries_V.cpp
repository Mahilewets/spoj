#include <vector>
#include <cstdio>
#include <algorithm>
using std::vector;
struct node{
    long long global=0, pref=0, suff=0, sum=0;
    void combine(const node &l, const node &r){
        sum=l.sum+r.sum;
        pref=std::max(l.pref, l.sum+r.pref);
        suff=std::max(r.suff, r.sum+l.suff);
        global=std::max({l.global, r.global, l.suff+r.pref});
    }
};
void build(vector<node> &tree, const vector<int> &arr, int n, int l, int r, int i=1){
    if(l==r){
        tree[i].sum=tree[i].global=tree[i].pref=tree[i].suff=arr[l];
        return;
    }
    int m=(l+r)>>1, j=i<<1, k=j|1;
    build(tree, arr, n, l, m, j);
    build(tree, arr, n, m+1, r, k);
    tree[i].combine(tree[j], tree[k]);
}
node query(const vector<node> &tree, int l, int r, int tl, int tr, int i=1){
    if(l>r){
        return node();
    }
    if(l==tl && r==tr){
        return tree[i];
    }
    int tm=(tl+tr)>>1, j=i<<1, k=j|1;
    if(r<=tm){
        return query(tree, l, r, tl, tm, j);
    }
    if(l>=tm+1){
        return query(tree, l, r, tm+1, tr, k);
    }
    node res, left, right;
    left=query(tree, l, tm, tl, tm, j);
    right=query(tree, tm+1, r, tm+1, tr, k);
    res.combine(left, right);
    return res;
}
int main(){
    int q=0;
    scanf("%d", &q);
    for(int i=q; i>0; --i){
        int n=0, m=0;
        scanf("%d", &n);
        vector<int> arr(n);
        vector<node> tree(n<<2);
        for(auto &it: arr){
            scanf("%d", &it);
        }
        build(tree, arr, n, 0, n-1);
        scanf("%d", &m);
        for(int j=m; j>0; --j){
            int x1=0, y1=0, x2=0, y2=0;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            --x1; --y1; --x2; --y2;
            long long result=0;
            x1=std::max(x1,0);
            y1=std::min(y1, n-1);
            x2=std::max(x2, 0);
            y2=std::min(y2, n-1);
            if(x1<=x2 && x2<=y2 && y2<=y1){
                node mid=query(tree, x2, y2, 0, n-1),
                     left=query(tree, x1, x2-1, 0, n-1);
                result=std::max({mid.global, left.suff+mid.pref});
                goto answer;
            }
            if(x2<=x1 && x1<=y1 && y1<=y2){
                node mid=query(tree, x1, y1, 0, n-1),
                     right=query(tree, y1+1, y2, 0, n-1);
                result=std::max({mid.global, mid.suff+right.pref});
                goto answer;
            }
            if(x1<=x2 && x2<=y1 && y1<=y2){
                node mid=query(tree, x2, y1, 0, n-1),
                     left=query(tree, x1, x2-1, 0, n-1),
                     right=query(tree, y1+1, y2, 0, n-1);
                result=std::max({mid.global, left.suff+mid.pref, mid.suff+right.pref, left.suff+mid.sum+right.pref});
                goto answer;
            }
            if(x1<=y1 && y1<=x2 && x2<=y2){
                node mid=query(tree, y1, x2, 0, n-1),
                     left=query(tree, x1, y1-1, 0, n-1),
                     right=query(tree, x2+1, y2, 0, n-1);
                result=std::max({mid.sum, left.suff+mid.sum, mid.sum+right.pref, left.suff+mid.sum+right.pref});
                goto answer;
            }
            answer:
            printf("%lld\n", result);
        }
    }

    return 0;
}
