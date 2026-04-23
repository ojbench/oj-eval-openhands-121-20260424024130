#ifndef SJTU_COMPLEX_HPP
#define SJTU_COMPLEX_HPP

#include <iostream> // 输入输出
#include <iomanip>  // 控制输出格式
#include <cmath>    // 数学函数
#include <stdexcept> // 异常处理
// 你不可以使用任何其他的头文件!


namespace sjtu {

// 异常类，你需要要添加一个函数 what() 来返回异常信息。
class divided_by_zero final : public std::exception {
  public:
    divided_by_zero()   = default;
    ~divided_by_zero()  = default;
    const char* what() const noexcept override {
        return "complex divided by zero!";
    }
};

// 用于判断浮点数的符号.
inline int sign(double x) {
    const double eps = 1e-6;
    return (x > eps) - (x < -eps);
}

// 请保留所有的接口声明，即使你没有实现它们。
// 否则可能出现编译错误，无法通过部分测试点。
// TODO 补全类的实现
class complex {
  private:
    double a, b; // a + bi
  public:
    
    complex();                    // 默认构造函数 0+0i
    complex(double a);            // 构造函数 a+0i
    complex(double a, double b);  // 构造函数 a+bi

    double &real(); // 返回实部
    double &imag(); // 返回虚部

    complex operator - () const; // 返回负数
    complex operator ~ () const; // 返回共轭复数

    complex operator + (const complex &rhs) const; // 加法
    complex operator - (const complex &rhs) const; // 减法
    complex operator * (const complex &rhs) const; // 乘法
    complex operator / (const complex &rhs) const; // 除法

    complex &operator += (const complex &rhs);
    complex &operator -= (const complex &rhs);
    complex &operator *= (const complex &rhs);
    complex &operator /= (const complex &rhs);

    bool operator == (const complex &rhs) const; // 判断相等
    
    explicit operator bool() const; // 转换为 bool

    friend std::ostream &operator << (std::ostream &os, const complex &x); // 输出
};

// 构造函数实现
complex::complex() : a(0.0), b(0.0) {}

complex::complex(double a) : a(a), b(0.0) {}

complex::complex(double a, double b) : a(a), b(b) {}

// 访问器实现
double &complex::real() {
    return a;
}

double &complex::imag() {
    return b;
}

// 单目运算符实现
complex complex::operator - () const {
    return complex(-a, -b);
}

complex complex::operator ~ () const {
    return complex(a, -b);
}

// 双目运算符实现
complex complex::operator + (const complex &rhs) const {
    return complex(a + rhs.a, b + rhs.b);
}

complex complex::operator - (const complex &rhs) const {
    return complex(a - rhs.a, b - rhs.b);
}

complex complex::operator * (const complex &rhs) const {
    return complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a);
}

complex complex::operator / (const complex &rhs) const {
    // 检查除数是否为0
    if (sign(rhs.a) == 0 && sign(rhs.b) == 0) {
        throw divided_by_zero();
    }
    
    double denominator = rhs.a * rhs.a + rhs.b * rhs.b;
    return complex((a * rhs.a + b * rhs.b) / denominator, 
                   (b * rhs.a - a * rhs.b) / denominator);
}

// 复合赋值运算符实现
complex &complex::operator += (const complex &rhs) {
    a += rhs.a;
    b += rhs.b;
    return *this;
}

complex &complex::operator -= (const complex &rhs) {
    a -= rhs.a;
    b -= rhs.b;
    return *this;
}

complex &complex::operator *= (const complex &rhs) {
    double new_a = a * rhs.a - b * rhs.b;
    double new_b = a * rhs.b + b * rhs.a;
    a = new_a;
    b = new_b;
    return *this;
}

complex &complex::operator /= (const complex &rhs) {
    // 检查除数是否为0
    if (sign(rhs.a) == 0 && sign(rhs.b) == 0) {
        throw divided_by_zero();
    }
    
    double denominator = rhs.a * rhs.a + rhs.b * rhs.b;
    double new_a = (a * rhs.a + b * rhs.b) / denominator;
    double new_b = (b * rhs.a - a * rhs.b) / denominator;
    a = new_a;
    b = new_b;
    return *this;
}

// 相等运算符实现
bool complex::operator == (const complex &rhs) const {
    return sign(a - rhs.a) == 0 && sign(b - rhs.b) == 0;
}

// bool转换运算符实现
complex::operator bool() const {
    return !(sign(a) == 0 && sign(b) == 0);
}

// 输出运算符实现
std::ostream &operator << (std::ostream &os, const complex &x) {
    os << std::fixed << std::setprecision(6);
    
    // 输出实部（负数需要符号，非负数不需要）
    if (sign(x.a) < 0) {
        os << x.a;
    } else {
        os << (sign(x.a) == 0 ? 0.0 : x.a);
    }
    
    // 输出虚部符号
    if (sign(x.b) < 0) {
        os << x.b;
    } else {
        os << "+" << (sign(x.b) == 0 ? 0.0 : x.b);
    }
    
    os << "i";
    return os;
}

}

#endif