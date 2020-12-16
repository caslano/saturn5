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
0pTfvbjeA5U8hkt7RSgxmA+BX6t5TDNkGvmx6WJ+WWn0uc3CnjfUplXWV9qB5DytDSr7iChJS370qa40Ja0uDaUldcp+3uB+HiD7+WqWr4B0r+LzRiUdTR1/Wl3v9nyq45cy/m1K3r9xfR/TQpZC+66PAbJckXKhyq5effY/WinDM+pyZfhyL8b1fr3re2s2SBpdJY3Osp5i6tOwZKc2Lh1ZRy59C+r3Gee9D0H9Puy89/Gn37ed974L9fsQ9N6nnn4fed77ntPv67Dxffzp943ovW8+/b4OG983n37fiN771NPvM9FbX3ve+/4bHawM//nSV/o2WRbc7Z65WZUXrxv9grc+Jb33vTgvUBn+wKPbn33z5RtqVwQdDu7r//1U730I6vd92fg+HL31WWnvQ62p/OZYfoPcmzQtyjYo7xr7vrn0dYcd8BcMx19xMLI55Y+AJhiDF+EUbIozsDnOw4vRiC0wA/1xCbbC9RiA72Fb/BDb4cfYHj/HIKzGYPwWO+IZ7IR1GIq/YDg2Z2E6Ywvsim3xEgzECOyE3TAMe2AERmJ3vAz7YC/si31wEPbDeTgAF+AVaMSBuBgHYQZGow2H4BIchjficLwJR+I6vBLX41W4CUfjZozBrTgGt+M4vB/H406ciHtxCn7KupqKX+A0/Abj8Qe8Fn/BmdicdTkLW+FsbI9zMASvw644F7tjIvbB+dgXk3AQJmM0LsArMQWvQhOOw1ScgGk4Fc04HRfjbEzHBMzEJMxCA96AaZiNi9CGN2AOWnEpLsdczMPleDOuwLV4I27AlXg7rsK7cDXeg2vwPlyLRXgLPoi3Yetm7LMwCG/HYCzAzrgZu+KdGIlb8DK8G/vjPXgFbsOhuB2H4714Nd6HY7AIY/F+nIzFeC3uwpn4IM7FfXgbPoy34wGUPnfkN8LUdaK3a587VHL6zMBV2BFXo9oH0QtMB6NlOm2fQQ8wXhvciZfhLuyHuzEKH8SRuAedfe3Ey/yulPlp+9o5Sn7b4EsYjK9gOFZgBL6KffE1jMZKHIZvoMxffmNL3nXmv1byewt2wPXYCW+V/P4Rh+Jtku8NOA43asvjRe/lUSDz3yzlcaeUxxaZ/10y37vRuV7iZX6tddbLMZarKb6NLfEddOYjuYF8bJN8bJd8FEo+7pV83Cf52IHOPqtKZH6hMj9tn1Vlko9nJR/PYXs8giFYjmqfhsp8ZNrebn3+PCrzOSjzeQwD8XHsgk9gD3wSB2GpWn/lN6V4hU457ZPl3Y998WFZrloiWabb08QxnZJOtUzXUaYLxR4Yhv2xB16NkTgfL8OF2AdvwMtxPfbF27EfbsX++BgOwKdwID6Pg/A1HIxvYbTkbwj6k6+hGITDMApH4DC88t/s3Qd8FFUewPHQFCFAAiGE0AJEegk9IL13AkQINW3TSCXZQBCQ0BQQJFQRAXMKCIIYkSrgRUFEDyUgIFIUFBQRMYcoKJzeb3b/Ozu7O0s2qFc+n+zd88tOZua9efOm7My8/+AI7IgJ2AknYWdcgl3QtJ/Hl7A7rscemvaV+aHz9hUk2/0wfARHoCXma5ZMV0Gm08Z8vSvr8R6Wxn9hOfwN1RhfMn0ZnXxHSb5jsDSGasqbK9O11Jmuj6yvftgMB6ntV57PhEd12m9xma4EVsaSWBNLYW18SOajHNsDZD5PSnuppYwvoRzOlGQ++BlWw7PYBs9hZzyPIXgBQ/FzjMUvcBZexGfwEm7AL3ErXsHt+DUexG/wBF7Fk/gtfonf4VW8jjfxB1QKm4818SbWwZ+wF97GAXgHR+CvGIr3MBx/wwn4OyZgMc7H0rEkPoGPoHm9yLOUWE1nvTwi67MMVsWyqMY=
*/