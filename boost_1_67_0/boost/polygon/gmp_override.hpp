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