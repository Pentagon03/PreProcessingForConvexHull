Point P0;
//a에서 바라 봤을 때 b->c가 counter clock wise인지 체크
int ccw(Point a, Point b, Point c)
{ 
    ll res = (b.x - a.x) * 1LL * (c.y - a.y) - (b.y - a.y) * 1LL * (c.x - a.x);
    if (res != 0) res = (res > 0 ? 1 : -1);
    return res;
}
//P0,P1,P2가 ccw인지 체크
//P0,P1,P2가 일직선 상에 있다면 작은 것을 앞에 있을 경우 참을 리턴
bool cmp(Point P1, Point P2)
{
    int res = ccw(P0, P1, P2);
    if (res == 0) return (P1 - P0).sq() < (P2 - P0).sq();
    return res > 0;
}
//Stack의 top 전에 있는 원소를 리턴
Point nextToTop(stack<Point> &st)
{
    Point p = st.top();
    st.pop();
    Point res = st.top();
    st.push(p);
    return res;
}

//좌하 점에 대해 반시계 방향으로 점들을 정렬
void recoordinate(vector<Point> &P)
{
    if(P.size()<2) return;
    P0 = P[0];
    int n = P.size(), id = 0;
    for (int i = 1; i < n; i++)
        if (P[i] < P0)
            P0 = P[i], id = i;
    P[id] = P[0];
    P[0] = P0;
    sort(P.begin() + 1, P.end(), cmp);
    int m = 1;
    for (int i = 1; i < n; i++)
    {
        while (i < n - 1 && ccw(P0, P[i], P[i + 1]) == 0) i++;
        P[m++] = P[i];
    }
    P.resize(m);   
}

//점집합을 리스트로 받아 Convex Hull 점집합의 리스트를 리턴
vector<Point> GrahamScan(vector<Point> P)
{
    recoordinate(P);
    if(P.size()<3) return P;
    stack<Point> st;
    st.push(P[0]); st.push(P[1]); st.push(P[2]);
    for (int i = 3; i < P.size(); i++)
    {
        while (ccw(nextToTop(st), st.top(), P[i]) <= 0) st.pop();
        st.push(P[i]);
    }
    vector<Point> ans;
    while (!st.empty())
        ans.push_back(st.top()), st.pop();
    reverse(all(ans));
    return ans;
}
