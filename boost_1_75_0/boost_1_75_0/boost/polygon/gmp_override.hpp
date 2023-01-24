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
rsP5leRgyQ1GcxVdrg7kvXfe73+w3xaWTyWmdEdqe0iqOKN4koYkohMUc0JCZewnx6Hfwl6F/LorlPnua1Fd2s3bve5zilRuj95d5PYhHZh35zWd1yNnCjVylS2646DnntPb+8cL81aoXYA8LV/63yI73V70FuGUQuZo94Cav9WCvc6aposqqybP6oJHPQErHRNheaCcANfJhNoTm7/L8ZydAH4Sf47vOz5MJ1TdOVewn1+M12zXmvUT+xJFbprqko7RIaLAd30dR0z8oeSuK9aM/GYr9LpgHrNbbbgDciS7X941E0pTGkHqfNp8U/+R0SsjVCO0c9EBURndbd3O0f2fO9fZHOfvM0X1U3NRcVFWRSdcHx6vpwyUoB2vvRkBE7alDqTIizItZtr4eKFzEfRlydtrouU08Sg6uX7UNw8uM9b2uaXflwaM9umap4fZuZr9uHqcN3cyeR0fkq3Z9JXxkNvyE7G6aVRR454DoHd7m1Hp9b3MNiV++Vd5iYslrnqsr6XKdhSreuuNIysnD7GWwKpdpjLibmEUCh8/l1s94qsi/0rcoQMmUhCUlzkuyGiN8K7kRvAdPuK6T29DWcTZbAJpLmCMA/Qiyzon/T9uTc03cTi8i/fCBQlLlHuaYJRzhItSXyK9bL8+2ur19prs7TysNCK28GlXuNouP6tyovkaVrCLu4ot6FNX4PanDTaiZn30E9fsc7R7
*/