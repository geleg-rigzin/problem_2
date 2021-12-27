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
        int comparison(const matrix &B);
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
    try{ 
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
int matrix<T>::comparison(const matrix &B) {
    int ret = 0;
    for(int i = 0; i < m*n; ++i) {
        ret = !(elements[i] == B.elements[i]);
        if(ret) {
            return ret;
        }
    }
    return ret;
}
int main(int argc, char *argv[])
{
    try {   
        ifstream ain, bin;
        ain.open(argv[1], ios::binary | ios::in);
        bin.open(argv[2], ios::binary | ios::in);
    
        char c_1, c_2;      
        int m, k;
        ain.read(&c_1, sizeof c_1);
        bin.read(&c_2, sizeof c_2);
   
        ain.read((char*)&m, sizeof m);
        bin.read((char*)&k, sizeof k);

        if( c_1 != c_2 || m != k ) {
            throw "Несоответсвие типа или размера матриц";
        }
        int ret;
        if( c_1 == 'T' ) {
            matrix<int> A(m, m), B(k, k);
            A.read_matrix(ain); B.read_matrix(bin);
            ret = A.comparison(B);
        }
        else{
            matrix<long> A(m, m), B(k, k);
            A.read_matrix(ain); B.read_matrix(bin);
            ret = A.comparison(B);
        }
        ain.close();
        bin.close();
        if(ret) {
            cout << "Результат вычислений программы не совпадает с контрольным"<<endl;
        }
        else {
            cout << "Результат вычислений программы совпадает с контрольным" <<endl;
        }
        return ret;
    }
    catch (const char *error) {
        cout << error << endl;
        return 100;
    }   
}
