class Solution {
public:
    string ans;
    bool solve(int i,string s,vector<int> &count, string target,char mid,bool flag){

        if(s.size()==target.size()/2){
            string p = s;
            reverse(s.begin(),s.end());
            
            if(target.size()%2==1){
                p+=mid;
            }
            p+=s;

            if(p>target){
                ans = p;
                return true;
            }

            return false;
        }

        for(int j=0;j<26;j++){
            if(count[j]==0){
                continue;
            }

            if(!flag && ('a'+j)<target[i]){
                continue;
            }

            //Include this 
            count[j]--;
            s+='a'+j;
            bool newFlag = flag;
            if(target[i]<'a'+j){
                newFlag =true;
            }

            if(solve(i+1,s,count,target,mid,newFlag)){
                return true;
            }

            s.pop_back();
            count[j]++;

        }
        return false;
    }
    string lexPalindromicPermutation(string s, string target) {

        vector<int> count(26, 0);
        ans="";
        for (char c : s) {
            count[c - 'a']++;
        }
        int odd = 0;
        char mid =' ';
        for (int i = 0; i < 26; i++) {

            if (count[i] % 2 == 1) {
                mid = 'a'+i;
                odd++;
            }

            if (odd > 1) {
                return "";
            }
            count[i] = count[i] / 2;
        }

        solve(0,"",count,target,mid,false);
        return ans;


    }
};