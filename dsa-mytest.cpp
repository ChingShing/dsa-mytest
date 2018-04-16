#include<iostream>
using namespace std;

typedef int Rank; //秩
#define DEFAULT_CAPACITY  3 //默认的初始容量（实际应用中可设置为更大）

template <typename T> class Vector { //向量模板类
protected:
    Rank _size; int _capacity;  T* _elem; //规模、容量、数据区
public:
    // 构造函数
    Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 ) //容量为c、规模为s、所有元素初始为v
    { _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); } //s<=c
    // 析构函数
    ~Vector() { delete [] _elem; } //释放内部空间
    // 可写访问接口
    T& operator[] ( Rank r ) const; //重载下标操作符，可以类似于数组形式引用各元素
    T remove ( Rank r ); //删除秩为r的元素
    int remove ( Rank lo, Rank hi ); //删除秩在区间[lo, hi)之内的元素
    Rank insert ( Rank r, T const& e ); //插入元素
    Rank insert ( T const& e ) { return insert ( _size, e ); } //默认作为末元素插入
    // 遍历
    void traverse ( void (* ) ( T& ) ); //遍历（使用函数指针，只读或局部性修改）
    template <typename VST> void traverse ( VST& ); //遍历（使用函数对象，可全局性修改）
}; //Vector

template <typename T> //将e作为秩为r元素插入
Rank Vector<T>::insert ( Rank r, T const& e ) { //assert: 0 <= r <= size
    //expand(); //若有必要，扩容
    for ( int i = _size; i > r; i-- ) _elem[i] = _elem[i-1]; //自后向前，后继元素顺次后移一个单元
    _elem[r] = e; _size++; //置入新元素并更新容量
    return r; //返回秩
}


template <typename T>
struct VST { virtual void operator()(T & e) { e = 42;cout<< e <<"\t"; } };//打印当前元素

template <typename T> template <typename VST> //元素类型、操作器
void Vector<T>::traverse ( VST& visit ) //借助函数对象机制
{ for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); } //遍历向量

template <typename T> void visit2 ( T& e ){ e = 42 ;cout<< e <<"\t";}

template <typename T> void Vector<T>::traverse ( void ( *visit2 ) ( T& ) ) //借助函数指针机制
{ for ( int i = 0; i < _size; i++ ) visit2 ( _elem[i] ); } //遍历向量


int main () {
    cout << "Hi, let's Traverse!" << endl;
    Vector<int> my_vector;
    for ( int i = 0; i < 3; i++ ) my_vector.insert (i);
    
    cout << "1.函数对象" << endl;
    VST<int> visit;
    my_vector.traverse(visit);
    cout << endl;
    
    cout << "2.函数指针" << endl;
    my_vector.traverse(visit2);
    cout << endl;
    
    return 0;
}
