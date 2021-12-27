#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

template<typename T>
class matrix {
        int n;      
        T *elements;
        int m;
    public:
        matrix(int h = 1, int w = 1);
        matrix (const matrix & source);
        ~matrix(){ delete [] elements; }
        void operator = (const matrix & source);
        matrix operator + (matrix & b);
        void set_element(int str, int col, T &elem);
        T get_element(int str, int col);
        void read_matrix(ifstream &in);         
        void print();
        void fprint(ofstream &out);
        void rand_val();
        
        template<typename Tip>
        friend void ijk(const matrix<Tip> &a, const matrix<Tip> &b, matrix<Tip> &c);

};

template<typename T>
matrix<T>::matrix(int h , int w ): m(h), n(w){
    int size_of_matrix = m * n;
    elements = new T[size_of_matrix];
    memset(elements, 0, size_of_matrix * sizeof(T));
}

template<typename T>
matrix<T>::matrix (const matrix & source){
    m = source.m; n = source.n;
    int size_of_matrix = m * n;
    elements = new T[size_of_matrix];
    for(int i = 0; i < size_of_matrix; ++i){
        elements[i] = source.elements[i];
    }
}

template<typename T>
void matrix<T>::operator = (const matrix & source){
    delete [] elements;
    m = source.m; n = source.n;
    int size_of_matrix = m * n;
    elements = new T[size_of_matrix];
    for(int i = 0; i < size_of_matrix; ++i){
        elements[i] = source.elements[i];
    }
}
template<typename T>    
matrix<T> matrix<T>::operator + (matrix & b){
    try{ //могу заменить на if
        if((n != b.n) | (m != b.m)){
            throw 100;
        }
    }
    catch(int i){
        
                cout << "+matrix!"<<endl;
        throw;
    }
    matrix ret(m, n);
    for(int i = 0; i < m * n; ++i){
        ret.elements[i] = elements[i] + b.elements[i];
    }
    return ret;
}
template<typename T>
void matrix<T>::set_element(int str, int col, T &elem){
    try{
        if((str > m) | (col > n)){
            throw 200;
        }
    }
    catch(int i){
                cout << "set!"<<endl;
        throw;
    }
    elements[ (str - 1) * n + col - 1 ] = elem;
}
template<typename T>
T matrix<T>::get_element(int str, int col){
    try{
        if((str > m) | (col > n)){
            throw 300;
        }
    }
    catch(int i){
                cout << "get!"<<endl;
        throw;
    }
    return elements[ (str - 1) * n + col - 1 ];
}
template<typename T>
void matrix<T>::print(){
    int i, k;
    for(i = 1; i <= m; ++i){
        for(k = 1; k <= n; k++){
            cout << get_element(i,k)<<' ';
        }
        cout << endl;
    }
}

template<typename T>
void matrix<T>::read_matrix(ifstream &in) {
    T tmp;
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            in.read((char*)&tmp, sizeof tmp);
            elements[i * n + j] = tmp;
        }
    }
}       
template<typename T>
void matrix<T>::fprint(ofstream &out){
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            out.write((char*)&elements[i * n + j], sizeof(T));
        }
    }
}
template<typename T>
void matrix<T>::rand_val() {
    for(int i = 0; i < m*n; ++i) {
        elements[i] = rand();
    }
}

template<typename T>
void ijk(const matrix<T> &a, const matrix<T> &b, matrix<T> &c) {
    int i, j, k, m, n, h;
    m = a.m;
    h = a.n;
    n = b.n;
    for ( i = 0; i < m; ++i) {
        for ( j = 0; j < n; ++j) {
            for (int k = 0; k < h; ++k) {
                c.elements[i * n + j] += a.elements[i * h + k] * b.elements[k * n + j];
            }
        }
    }
}


int main(int argc, char * argv[]) {   
    ofstream out_a;
    out_a.open("./a.bin", ios::binary | ios::trunc | ios::out);
    ofstream out_b;
    out_b.open("./b.bin", ios::binary | ios::trunc | ios::out);
    ofstream out_cntrl;
    out_cntrl.open("./cntrl.bin", ios::binary | ios::trunc | ios::out);
    
    char c;
    int a_m, a_n, b_m, b_n;
    if (argc == 3) {
        a_m = a_n = b_m = b_n = atoi(argv[1]);
        c = *argv[2];
    }
    else {
        a_m = a_n = b_m = b_n = 400;
        c = 'T';
    }
    srand(time(0));

    out_a.write(&c, sizeof c);
    out_a.write((char*)&a_m, sizeof a_m);

    out_b.write(&c, sizeof c);
    out_b.write((char*)&b_m, sizeof b_m);

    out_cntrl.write(&c, sizeof c);
    out_cntrl.write((char*)&a_m, sizeof a_m);

    if(c == 'T') {
        matrix<int> A(a_m, a_n);
        matrix<int> B(b_m, b_n);
        matrix<int> C(a_m, b_n);
        A.rand_val();
        B.rand_val();
        ijk(A, B, C);
        A.fprint(out_a);    
        B.fprint(out_b);
        C.fprint(out_cntrl);
    }
    else {
        matrix<long> A(a_m, a_n);
        matrix<long> B(b_m, b_n);
        matrix<long> C(a_m, b_n);
        A.rand_val();
        B.rand_val();
        ijk(A, B, C);
        A.fprint(out_a);
        B.fprint(out_b);
        C.fprint(out_cntrl);    
    }
    
    out_b.close();
    out_a.close();
    out_cntrl.close();
    
    out_b.open("./out.bin");
    out_b.close();
    out_b.open("./tmp.bin");
    out_b.close();
    out_b.open("./tim.bin");
    out_b.close();
    
    return 0;
}
