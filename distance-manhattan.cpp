#include <cstdio>
#include <vector>
#include <cmath>
#include <utility>
int get_l_inf(std::vector<int> &pt, unsigned mask)
{
    int d=pt.size(), res=0;
    for(int i=0; i<d; ++i)
    {
        int bit=(mask>>i)&1, proj_sign=1-2*bit;
        res+=pt[i]*proj_sign;
    }
    return res;
}
std::pair<int,int> get_min_max_id(std::vector<std::vector<int>> &point_l_1, unsigned mask)
{
    int min=get_l_inf(point_l_1[0], mask), max=min, min_id=0, max_id=0, n=point_l_1.size();
    for(int i=1; i<n; ++i)
    {
        int curr=get_l_inf(point_l_1[i], mask);
        if(curr<min)
        {
            min=curr;
            min_id=i;
        }
        else if(curr>max)
        {
            max=curr;
            max_id=i;
        }
    }
    return std::pair<int,int>(min_id, max_id);
}
int get_max_distance(std::vector<std::vector<int>> &point_l_1, unsigned mask)
{
    std::pair<int,int> best=get_min_max_id(point_l_1, mask);
    std::vector<int> left=point_l_1[best.first], right=point_l_1[best.second];
    int res=0, d=point_l_1[0].size();
    for(int i=0; i<d; ++i)
    {
        res+=std::abs(left[i]-right[i]);
    }
    return res;
}
int get_max_distance(std::vector<std::vector<int>> &point_l_1)
{
    int n=point_l_1.size(), d=point_l_1[0].size(), k=1<<d, res=0;
    for(unsigned mask=0; mask<k; ++mask)
    {
        int curr=get_max_distance(point_l_1, mask);
        if(curr>res)
        {
            res=curr;
        }
    }
    return res;
}
int main()
{
    int n=0, d=0;
    scanf("%d %d", &n, &d);
    std::vector<std::vector<int>> point_l_1(n, std::vector<int>(d));
    for(auto &pt: point_l_1)
    {
        for(auto &coord: pt)
        {
            scanf("%d", &coord);
        }
    }
    int res=get_max_distance(point_l_1);
    printf("%d\n", res);
    return 0;
}
