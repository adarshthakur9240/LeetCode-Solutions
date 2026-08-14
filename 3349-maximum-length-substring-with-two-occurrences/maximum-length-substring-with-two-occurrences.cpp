class Solution {
public:
    int maximumLengthSubstring(string& s) {
        int freq[26]={0};
        int l=0, n=s.size(), len=0;
        for(int r=0; r<n; r++){
            int x=s[r]-'a';
            freq[x]++;
            while(l<r && freq[x]>2){
                freq[s[l]-'a']--;
                l++;
            }
            len=max(len, r-l+1);
        }
        return len;
    }
};

auto init = []() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 'c';
}();