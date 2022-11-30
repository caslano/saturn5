// Boost.Polygon library detail/voronoi_robust_fpt.hpp header file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_DETAIL_VORONOI_ROBUST_FPT
#define BOOST_POLYGON_DETAIL_VORONOI_ROBUST_FPT

#include <algorithm>
#include <cmath>

// Geometry predicates with floating-point variables usually require
// high-precision predicates to retrieve the correct result.
// Epsilon robust predicates give the result within some epsilon relative
// error, but are a lot faster than high-precision predicates.
// To make algorithm robust and efficient epsilon robust predicates are
// used at the first step. In case of the undefined result high-precision
// arithmetic is used to produce required robustness. This approach
// requires exact computation of epsilon intervals within which epsilon
// robust predicates have undefined value.
// There are two ways to measure an error of floating-point calculations:
// relative error and ULPs (units in the last place).
// Let EPS be machine epsilon, then next inequalities have place:
// 1 EPS <= 1 ULP <= 2 EPS (1), 0.5 ULP <= 1 EPS <= 1 ULP (2).
// ULPs are good for measuring rounding errors and comparing values.
// Relative errors are good for computation of general relative
// error of formulas or expressions. So to calculate epsilon
// interval within which epsilon robust predicates have undefined result
// next schema is used:
//     1) Compute rounding errors of initial variables using ULPs;
//     2) Transform ULPs to epsilons using upper bound of the (1);
//     3) Compute relative error of the formula using epsilon arithmetic;
//     4) Transform epsilon to ULPs using upper bound of the (2);
// In case two values are inside undefined ULP range use high-precision
// arithmetic to produce the correct result, else output the result.
// Look at almost_equal function to see how two floating-point variables
// are checked to fit in the ULP range.
// If A has relative error of r(A) and B has relative error of r(B) then:
//     1) r(A + B) <= max(r(A), r(B)), for A * B >= 0;
//     2) r(A - B) <= B*r(A)+A*r(B)/(A-B), for A * B >= 0;
//     2) r(A * B) <= r(A) + r(B);
//     3) r(A / B) <= r(A) + r(B);
// In addition rounding error should be added, that is always equal to
// 0.5 ULP or at most 1 epsilon. As you might see from the above formulas
// subtraction relative error may be extremely large, that's why
// epsilon robust comparator class is used to store floating point values
// and compute subtraction as the final step of the evaluation.
// For further information about relative errors and ULPs try this link:
// http://docs.sun.com/source/806-3568/ncg_goldberg.html

namespace boost {
namespace polygon {
namespace detail {

template <typename T>
T get_sqrt(const T& that) {
  return (std::sqrt)(that);
}

template <typename T>
bool is_pos(const T& that) {
  return that > 0;
}

template <typename T>
bool is_neg(const T& that) {
  return that < 0;
}

template <typename T>
bool is_zero(const T& that) {
  return that == 0;
}

template <typename _fpt>
class robust_fpt {
 public:
  typedef _fpt floating_point_type;
  typedef _fpt relative_error_type;

  // Rounding error is at most 1 EPS.
  enum {
    ROUNDING_ERROR = 1
  };

  robust_fpt() : fpv_(0.0), re_(0.0) {}
  explicit robust_fpt(floating_point_type fpv) :
      fpv_(fpv), re_(0.0) {}
  robust_fpt(floating_point_type fpv, relative_error_type error) :
      fpv_(fpv), re_(error) {}

  floating_point_type fpv() const { return fpv_; }
  relative_error_type re() const { return re_; }
  relative_error_type ulp() const { return re_; }

  bool has_pos_value() const {
    return is_pos(fpv_);
  }

  bool has_neg_value() const {
    return is_neg(fpv_);
  }

  bool has_zero_value() const {
    return is_zero(fpv_);
  }

  robust_fpt operator-() const {
    return robust_fpt(-fpv_, re_);
  }

  robust_fpt& operator+=(const robust_fpt& that) {
    floating_point_type fpv = this->fpv_ + that.fpv_;
    if ((!is_neg(this->fpv_) && !is_neg(that.fpv_)) ||
        (!is_pos(this->fpv_) && !is_pos(that.fpv_))) {
      this->re_ = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
    } else {
      floating_point_type temp =
        (this->fpv_ * this->re_ - that.fpv_ * that.re_) / fpv;
      if (is_neg(temp))
        temp = -temp;
      this->re_ = temp + ROUNDING_ERROR;
    }
    this->fpv_ = fpv;
    return *this;
  }

  robust_fpt& operator-=(const robust_fpt& that) {
    floating_point_type fpv = this->fpv_ - that.fpv_;
    if ((!is_neg(this->fpv_) && !is_pos(that.fpv_)) ||
        (!is_pos(this->fpv_) && !is_neg(that.fpv_))) {
       this->re_ = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
    } else {
      floating_point_type temp =
        (this->fpv_ * this->re_ + that.fpv_ * that.re_) / fpv;
      if (is_neg(temp))
         temp = -temp;
      this->re_ = temp + ROUNDING_ERROR;
    }
    this->fpv_ = fpv;
    return *this;
  }

  robust_fpt& operator*=(const robust_fpt& that) {
    this->re_ += that.re_ + ROUNDING_ERROR;
    this->fpv_ *= that.fpv_;
    return *this;
  }

  robust_fpt& operator/=(const robust_fpt& that) {
    this->re_ += that.re_ + ROUNDING_ERROR;
    this->fpv_ /= that.fpv_;
    return *this;
  }

  robust_fpt operator+(const robust_fpt& that) const {
    floating_point_type fpv = this->fpv_ + that.fpv_;
    relative_error_type re;
    if ((!is_neg(this->fpv_) && !is_neg(that.fpv_)) ||
        (!is_pos(this->fpv_) && !is_pos(that.fpv_))) {
      re = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
    } else {
      floating_point_type temp =
        (this->fpv_ * this->re_ - that.fpv_ * that.re_) / fpv;
      if (is_neg(temp))
        temp = -temp;
      re = temp + ROUNDING_ERROR;
    }
    return robust_fpt(fpv, re);
  }

  robust_fpt operator-(const robust_fpt& that) const {
    floating_point_type fpv = this->fpv_ - that.fpv_;
    relative_error_type re;
    if ((!is_neg(this->fpv_) && !is_pos(that.fpv_)) ||
        (!is_pos(this->fpv_) && !is_neg(that.fpv_))) {
      re = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
    } else {
      floating_point_type temp =
        (this->fpv_ * this->re_ + that.fpv_ * that.re_) / fpv;
      if (is_neg(temp))
        temp = -temp;
      re = temp + ROUNDING_ERROR;
    }
    return robust_fpt(fpv, re);
  }

  robust_fpt operator*(const robust_fpt& that) const {
    floating_point_type fpv = this->fpv_ * that.fpv_;
    relative_error_type re = this->re_ + that.re_ + ROUNDING_ERROR;
    return robust_fpt(fpv, re);
  }

  robust_fpt operator/(const robust_fpt& that) const {
    floating_point_type fpv = this->fpv_ / that.fpv_;
    relative_error_type re = this->re_ + that.re_ + ROUNDING_ERROR;
    return robust_fpt(fpv, re);
  }

  robust_fpt sqrt() const {
    return robust_fpt(get_sqrt(fpv_),
                      re_ * static_cast<relative_error_type>(0.5) +
                      ROUNDING_ERROR);
  }

 private:
  floating_point_type fpv_;
  relative_error_type re_;
};

template <typename T>
robust_fpt<T> get_sqrt(const robust_fpt<T>& that) {
  return that.sqrt();
}

template <typename T>
bool is_pos(const robust_fpt<T>& that) {
  return that.has_pos_value();
}

template <typename T>
bool is_neg(const robust_fpt<T>& that) {
  return that.has_neg_value();
}

template <typename T>
bool is_zero(const robust_fpt<T>& that) {
  return that.has_zero_value();
}

// robust_dif consists of two not negative values: value1 and value2.
// The resulting expression is equal to the value1 - value2.
// Subtraction of a positive value is equivalent to the addition to value2
// and subtraction of a negative value is equivalent to the addition to
// value1. The structure implicitly avoids difference computation.
template <typename T>
class robust_dif {
 public:
  robust_dif() :
      positive_sum_(0),
      negative_sum_(0) {}

  explicit robust_dif(const T& value) :
      positive_sum_((value > 0)?value:0),
      negative_sum_((value < 0)?-value:0) {}

  robust_dif(const T& pos, const T& neg) :
      positive_sum_(pos),
      negative_sum_(neg) {}

  T dif() const {
    return positive_sum_ - negative_sum_;
  }

  T pos() const {
    return positive_sum_;
  }

  T neg() const {
    return negative_sum_;
  }

  robust_dif<T> operator-() const {
    return robust_dif(negative_sum_, positive_sum_);
  }

  robust_dif<T>& operator+=(const T& val) {
    if (!is_neg(val))
      positive_sum_ += val;
    else
      negative_sum_ -= val;
    return *this;
  }

  robust_dif<T>& operator+=(const robust_dif<T>& that) {
    positive_sum_ += that.positive_sum_;
    negative_sum_ += that.negative_sum_;
    return *this;
  }

  robust_dif<T>& operator-=(const T& val) {
    if (!is_neg(val))
      negative_sum_ += val;
    else
      positive_sum_ -= val;
    return *this;
  }

  robust_dif<T>& operator-=(const robust_dif<T>& that) {
    positive_sum_ += that.negative_sum_;
    negative_sum_ += that.positive_sum_;
    return *this;
  }

  robust_dif<T>& operator*=(const T& val) {
    if (!is_neg(val)) {
      positive_sum_ *= val;
      negative_sum_ *= val;
    } else {
      positive_sum_ *= -val;
      negative_sum_ *= -val;
      swap();
    }
    return *this;
  }

  robust_dif<T>& operator*=(const robust_dif<T>& that) {
    T positive_sum = this->positive_sum_ * that.positive_sum_ +
                     this->negative_sum_ * that.negative_sum_;
    T negative_sum = this->positive_sum_ * that.negative_sum_ +
                     this->negative_sum_ * that.positive_sum_;
    positive_sum_ = positive_sum;
    negative_sum_ = negative_sum;
    return *this;
  }

  robust_dif<T>& operator/=(const T& val) {
    if (!is_neg(val)) {
      positive_sum_ /= val;
      negative_sum_ /= val;
    } else {
      positive_sum_ /= -val;
      negative_sum_ /= -val;
      swap();
    }
    return *this;
  }

 private:
  void swap() {
    (std::swap)(positive_sum_, negative_sum_);
  }

  T positive_sum_;
  T negative_sum_;
};

template<typename T>
robust_dif<T> operator+(const robust_dif<T>& lhs,
                        const robust_dif<T>& rhs) {
  return robust_dif<T>(lhs.pos() + rhs.pos(), lhs.neg() + rhs.neg());
}

template<typename T>
robust_dif<T> operator+(const robust_dif<T>& lhs, const T& rhs) {
  if (!is_neg(rhs)) {
    return robust_dif<T>(lhs.pos() + rhs, lhs.neg());
  } else {
    return robust_dif<T>(lhs.pos(), lhs.neg() - rhs);
  }
}

template<typename T>
robust_dif<T> operator+(const T& lhs, const robust_dif<T>& rhs) {
  if (!is_neg(lhs)) {
    return robust_dif<T>(lhs + rhs.pos(), rhs.neg());
  } else {
    return robust_dif<T>(rhs.pos(), rhs.neg() - lhs);
  }
}

template<typename T>
robust_dif<T> operator-(const robust_dif<T>& lhs,
                        const robust_dif<T>& rhs) {
  return robust_dif<T>(lhs.pos() + rhs.neg(), lhs.neg() + rhs.pos());
}

template<typename T>
robust_dif<T> operator-(const robust_dif<T>& lhs, const T& rhs) {
  if (!is_neg(rhs)) {
    return robust_dif<T>(lhs.pos(), lhs.neg() + rhs);
  } else {
    return robust_dif<T>(lhs.pos() - rhs, lhs.neg());
  }
}

template<typename T>
robust_dif<T> operator-(const T& lhs, const robust_dif<T>& rhs) {
  if (!is_neg(lhs)) {
    return robust_dif<T>(lhs + rhs.neg(), rhs.pos());
  } else {
    return robust_dif<T>(rhs.neg(), rhs.pos() - lhs);
  }
}

template<typename T>
robust_dif<T> operator*(const robust_dif<T>& lhs,
                        const robust_dif<T>& rhs) {
  T res_pos = lhs.pos() * rhs.pos() + lhs.neg() * rhs.neg();
  T res_neg = lhs.pos() * rhs.neg() + lhs.neg() * rhs.pos();
  return robust_dif<T>(res_pos, res_neg);
}

template<typename T>
robust_dif<T> operator*(const robust_dif<T>& lhs, const T& val) {
  if (!is_neg(val)) {
    return robust_dif<T>(lhs.pos() * val, lhs.neg() * val);
  } else {
    return robust_dif<T>(-lhs.neg() * val, -lhs.pos() * val);
  }
}

template<typename T>
robust_dif<T> operator*(const T& val, const robust_dif<T>& rhs) {
  if (!is_neg(val)) {
    return robust_dif<T>(val * rhs.pos(), val * rhs.neg());
  } else {
    return robust_dif<T>(-val * rhs.neg(), -val * rhs.pos());
  }
}

template<typename T>
robust_dif<T> operator/(const robust_dif<T>& lhs, const T& val) {
  if (!is_neg(val)) {
    return robust_dif<T>(lhs.pos() / val, lhs.neg() / val);
  } else {
    return robust_dif<T>(-lhs.neg() / val, -lhs.pos() / val);
  }
}

// Used to compute expressions that operate with sqrts with predefined
// relative error. Evaluates expressions of the next type:
// sum(i = 1 .. n)(A[i] * sqrt(B[i])), 1 <= n <= 4.
template <typename _int, typename _fpt, typename _converter>
class robust_sqrt_expr {
 public:
  enum MAX_RELATIVE_ERROR {
    MAX_RELATIVE_ERROR_EVAL1 = 4,
    MAX_RELATIVE_ERROR_EVAL2 = 7,
    MAX_RELATIVE_ERROR_EVAL3 = 16,
    MAX_RELATIVE_ERROR_EVAL4 = 25
  };

  // Evaluates expression (re = 4 EPS):
  // A[0] * sqrt(B[0]).
  _fpt eval1(_int* A, _int* B) {
    _fpt a = convert(A[0]);
    _fpt b = convert(B[0]);
    return a * get_sqrt(b);
  }

  // Evaluates expression (re = 7 EPS):
  // A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]).
  _fpt eval2(_int* A, _int* B) {
    _fpt a = eval1(A, B);
    _fpt b = eval1(A + 1, B + 1);
    if ((!is_neg(a) && !is_neg(b)) ||
        (!is_pos(a) && !is_pos(b)))
      return a + b;
    return convert(A[0] * A[0] * B[0] - A[1] * A[1] * B[1]) / (a - b);
  }

  // Evaluates expression (re = 16 EPS):
  // A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]) + A[2] * sqrt(B[2]).
  _fpt eval3(_int* A, _int* B) {
    _fpt a = eval2(A, B);
    _fpt b = eval1(A + 2, B + 2);
    if ((!is_neg(a) && !is_neg(b)) ||
        (!is_pos(a) && !is_pos(b)))
      return a + b;
    tA[3] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1] - A[2] * A[2] * B[2];
    tB[3] = 1;
    tA[4] = A[0] * A[1] * 2;
    tB[4] = B[0] * B[1];
    return eval2(tA + 3, tB + 3) / (a - b);
  }


  // Evaluates expression (re = 25 EPS):
  // A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]) +
  // A[2] * sqrt(B[2]) + A[3] * sqrt(B[3]).
  _fpt eval4(_int* A, _int* B) {
    _fpt a = eval2(A, B);
    _fpt b = eval2(A + 2, B + 2);
    if ((!is_neg(a) && !is_neg(b)) ||
        (!is_pos(a) && !is_pos(b)))
      return a + b;
    tA[0] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1] -
            A[2] * A[2] * B[2] - A[3] * A[3] * B[3];
    tB[0] = 1;
    tA[1] = A[0] * A[1] * 2;
    tB[1] = B[0] * B[1];
    tA[2] = A[2] * A[3] * -2;
    tB[2] = B[2] * B[3];
    return eval3(tA, tB) / (a - b);
  }

 private:
  _int tA[5];
  _int tB[5];
  _converter convert;
};
}  // detail
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_DETAIL_VORONOI_ROBUST_FPT

/* voronoi_robust_fpt.hpp
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
*/