/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_GMP_OVERRIDE_HPP
#define BOOST_POLYGON_GMP_OVERRIDE_HPP
#include <gmpxx.h>
namespace boost { namespace polygon {

  class gmp_int {
  private:
    inline gmp_int(const mpq_class& input) : v_(input) {}
  public:
    inline gmp_int() {}
    explicit inline gmp_int(long input) : v_(input) {}
    inline gmp_int(const gmp_int& input) : v_(input.v_) {}
    inline gmp_int& operator=(const gmp_int& that) {
      v_ = that.v_;
      return (*this);
    }
    inline gmp_int& operator=(long that) {
      v_ = that;
      return (*this);
    }
    inline operator int() const {
      std::cout << "cast\n";
      mpz_class num = v_.get_num();
      mpz_class den = v_.get_den();
      num /= den;
      return num.get_si();
    }
    inline double get_d() const {
      return v_.get_d();
    }
    inline int get_num() const {
      return v_.get_num().get_si();
    }
    inline int get_den() const {
      return v_.get_den().get_si();
    }
    inline bool operator==(const gmp_int& that) const {
      return v_ == that.v_;
    }
    inline bool operator!=(const gmp_int& that) const {
      return v_ != that.v_;
    }
    inline bool operator<(const gmp_int& that) const {
      bool retval = v_ < that.v_;
      return retval;
    }
    inline bool operator<=(const gmp_int& that) const {
      return v_ <= that.v_;
    }
    inline bool operator>(const gmp_int& that) const {
      return v_ > that.v_;
    }
    inline bool operator>=(const gmp_int& that) const {
      return v_ >= that.v_;
    }
    inline gmp_int operator+(const gmp_int& b) {
      return gmp_int((*this).v_ + b.v_);
    }
    inline gmp_int operator-(const gmp_int& b) {
      return gmp_int((*this).v_ - b.v_);
    }
    inline gmp_int operator*(const gmp_int& b) {
      return gmp_int((*this).v_ * b.v_);
    }
    inline gmp_int operator/(const gmp_int& b) {
      return gmp_int((*this).v_ / b.v_);
    }
    inline gmp_int& operator+=(const gmp_int& b) {
      (*this).v_ += b.v_;
      return (*this);
    }
    inline gmp_int& operator-=(const gmp_int& b) {
      (*this).v_ -= b.v_;
      return (*this);
    }
    inline gmp_int& operator*=(const gmp_int& b) {
      (*this).v_ *= b.v_;
      return (*this);
    }
    inline gmp_int& operator/=(const gmp_int& b) {
      (*this).v_ /= b.v_;
      return (*this);
    }
    inline gmp_int& operator++() {
      ++v_;
      return (*this);
    }
    inline gmp_int& operator--() {
      --v_;
      return (*this);
    }
    inline gmp_int operator++(int) {
      gmp_int retval(*this);
      ++(*this);
      return retval;
    }
    inline gmp_int operator--(int) {
      gmp_int retval(*this);
      --(*this);
      return retval;
    }
  private:
    mpq_class v_;
  };

  template <>
  struct high_precision_type<int> {
    typedef mpq_class type;
  };

  template <>
  int convert_high_precision_type<int>(const mpq_class& v) {
    mpz_class num = v.get_num();
    mpz_class den = v.get_den();
    num /= den;
    return num.get_si();
  };

}
}
#endif

/* gmp_override.hpp
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
*/