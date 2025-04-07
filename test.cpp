#include <iostream>
using namespace std;
int main() {
    string n;
    string a;
    bool p[10] ={1,1,1,1,1,1,1,1,1,1};
    cin >> n >> a;
    int k=0;
    for (int i=0; n[i]!=0; i++){
        k++;
        cout << "k" << endl;
        cout << k << endl;
    }


    cout << "dafdsa" << endl;
    int l =k;
    int m=0;
    for(int i=0;i<k;i++){
        m=m+n[i]*pow(10,l);
        l--;
    }
    cout << "dafdsa" << endl;
    for (int i=0; i<10; i++){
        p[a[i]-'0']=0;
    }
    cout << "dafdsa" << endl;
    for (int i[8]={0,0,0,0,0,0,0,1}; i[8-k]<=n[0]; i[7]++){
        for(int f=0;f<10;f++){
            if (i[7] ==10){
                i[6]++;
                i[7]=0;
            }
            else if (i[6] ==10){
                i[5]++;
                i[6]=0;
            }
            else if (i[5] ==10){
                i[4]++;
                i[5]=0;
            }
            else if (i[4] ==10){
                i[3]++;
                i[4]=0;
            }
            else if (i[3] ==10){
                i[2]++;
                i[3]=0;
            }
            else if (i[2] ==10){
                i[1]++;
                i[2]=0;
            }
            else if (i[1] ==10){
                i[0]++;
                i[1]=0;
            }
            if (p[i[f]]==0){
                m--;
            }
        }
    }
    cout << m;
    return 0;
}