class Solution {
public:
    bool checkDivisibility(int n) {
        int a=0,b=1,c=n;
        while(n){
            a+=n%10;
            b*=n%10;
            n/=10;
        }
        return c%(a+b)==0;
    }
};