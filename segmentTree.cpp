#include<iostream>
using namespace std;

int a[100005],seg[4*100005];
int lazy[4*100005];
void build(int ind,int low,int high){
    if(low == high){
        seg[ind] = a[low];
        return;
    }
    int mid = (low+high)/2;
    int left = 2*ind+1;
    int right = 2*ind+2;

    build(left,low,mid);
    build(right,mid+1,high);
    seg[ind] = max(seg[left],seg[right]);
}

void pointUpdate(int ind,int low,int high,int node,int val){
    if(low==high){
        seg[ind]+=val;
    }
    else{
        int mid = (low+high)/2;
        if(node<=mid&&node>=low){
            //lefthalf
            pointUpdate(2*ind+1,low,mid,node,val);
        }
        else{
            //rightHalf
            pointUpdate(2*ind+2,mid+1,high,node,val);
        }

        //backtrack
        seg[ind] = seg[2*ind+1]+seg[2*ind+2];
    }
}

//lazy update -- means lazy range update l to r
void rangeUpdate(int ind,int low,int high,int l,int r,int val){
    if(lazy[ind]!=0){
        //agar koi phele ka lazy hai tho update kr do
        seg[ind] += (high-low+1)*lazy[ind];
        if(low!=high){
            //means no leaf node -- propogate to children
            lazy[2*ind+1] +=lazy[ind];
            lazy[2*ind+2] += lazy[ind];
        } 
        //now set current ind lazy to 0
        lazy[ind] = 0;
    }

    //yaha se curr val k li

    //means not in current range than go
    if(r<low || l>high || low>high) return;

    if(low>=l && high<=r){
        //complete overlap
        //step1 --> current val lazy update
        seg[ind]+=(high-low+1)*val;
        if(low!=high){
            //means no leaf node -- propogate to children
            lazy[2*ind+1] +=lazy[ind];
            lazy[2*ind+2] += lazy[ind];
        }
        return;
    }

    //if partial overlap means go to both dirn
    int mid = (low+high)/2;
    rangeUpdate(2*ind+1,low,mid,l,r,val);
    rangeUpdate(2*ind+2,mid+1,high,l,r,val);
    seg[ind] = seg[2*ind+1] + seg[2*ind+2];
}

int querySumLazy(int ind,int low,int high,int l,int r){
   if(lazy[ind]!=0){
        //agar koi phele ka lazy hai tho update kr do
        seg[ind] += (high-low+1)*lazy[ind];
        if(low!=high){
            //means no leaf node -- propogate to children
            lazy[2*ind+1] +=lazy[ind];
            lazy[2*ind+2] += lazy[ind];
        } 
        //now set current ind lazy to 0
        lazy[ind] = 0;
    }
   
    //now yaha se ab ka kaam
    if(r<low || l>high || low>high) return 0;

    if(low>=l && high<=r){
        //complete overlap
        return seg[ind];
    }

    //partial overlap
    int mid = (low+high)/2;
    return querySumLazy(2*ind+1,low,mid,l,r) +  querySumLazy(2*ind+2,mid+1,high,l,r);

}


int query(int ind,int low,int high,int l,int r){
   
    if(low>=l && high<=r){
        //completely lies inside
        return seg[ind];
    }
    if(high<l||low>r){
        return -1e9;
    }
    //mtlb ab overlap hai
    //go both dirn
    int mid = (low+high)/2;
    int left = query(2*ind+1,low,mid,l,r);
    int right = query(2*ind+2,mid+1,high,l,r);
    
    return max(left,right);
}


int main(){
   int n;
   cin>>n;
   for(int i = 0;i<n;i++){
    cin>>a[i];
   }
   int low = 0;
   int high = n-1;

   build(0,low,high);

   int q;
   cin>>q;
   while(q--){
    int l,r;
    cin>>l>>r;
    cout<<query(0,0,n-1,l,r)<<"\n";
   }


}