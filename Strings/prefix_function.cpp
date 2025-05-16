template<typename T>
vector<int> prefix_function(T s){
    int n = (int) s.size();
    vector<int> p(n + 1, 0);
    for(int i = 0; i < n; i++){
        if(i == 0)
            p[i + 1] = 0;
        else {
            int cur = p[i];
            while(cur && s[cur] != s[i]){
                cur = p[cur];
            }
            if(s[cur] == s[i])
                p[i + 1] = cur + 1;
            else
                p[i + 1] = 0;
        }
    }
    return p;
}
