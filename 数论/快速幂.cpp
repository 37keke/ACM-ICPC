int quick_mod(int a,int b)
{
    int sum=1;
    while(b>0)
    {
        if(b&1) sum=sum*a;//把b分解为二进制数，然后进行b的位运算，
        b=b>>1;//每一次位运算，a进行一次相乘，遇到b分解的1，此刻a相乘sum
        a=a*a;
    }
    return sum;
}
