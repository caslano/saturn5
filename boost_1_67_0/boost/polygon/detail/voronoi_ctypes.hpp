// Boost.Polygon library detail/voronoi_ctypes.hpp header file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_DETAIL_VORONOI_CTYPES
#define BOOST_POLYGON_DETAIL_VORONOI_CTYPES

#include <boost/cstdint.hpp>

#include <algorithm>
#include <cmath>
#include <cstring>
#include <utility>
#include <vector>

namespace boost {
namespace polygon {
namespace detail {

typedef boost::int32_t int32;
typedef boost::int64_t int64;
typedef boost::uint32_t uint32;
typedef boost::uint64_t uint64;
typedef double fpt64;

// If two floating-point numbers in the same format are ordered (x < y),
// then they are ordered the same way when their bits are reinterpreted as
// sign-magnitude integers. Values are considered to be almost equal if
// their integer bits reinterpretations differ in not more than maxUlps units.
template <typename _fpt>
struct ulp_comparison;

template <>
struct ulp_comparison<fpt64> {
  enum Result {
    LESS = -1,
    EQUAL = 0,
    MORE = 1
  };

  Result operator()(fpt64 a, fpt64 b, unsigned int maxUlps) const {
    uint64 ll_a, ll_b;

    // Reinterpret double bits as 64-bit signed integer.
    std::memcpy(&ll_a, &a, sizeof(fpt64));
    std::memcpy(&ll_b, &b, sizeof(fpt64));

    // Positive 0.0 is integer zero. Negative 0.0 is 0x8000000000000000.
    // Map negative zero to an integer zero representation - making it
    // identical to positive zero - the smallest negative number is
    // represented by negative one, and downwards from there.
    if (ll_a < 0x8000000000000000ULL)
      ll_a = 0x8000000000000000ULL - ll_a;
    if (ll_b < 0x8000000000000000ULL)
      ll_b = 0x8000000000000000ULL - ll_b;

    // Compare 64-bit signed integer representations of input values.
    // Difference in 1 Ulp is equivalent to a relative error of between
    // 1/4,000,000,000,000,000 and 1/8,000,000,000,000,000.
    if (ll_a > ll_b)
      return (ll_a - ll_b <= maxUlps) ? EQUAL : LESS;
    return (ll_b - ll_a <= maxUlps) ? EQUAL : MORE;
  }
};

template <typename _fpt>
struct extened_exponent_fpt_traits;

template <>
struct extened_exponent_fpt_traits<fpt64> {
 public:
  typedef int exp_type;
  enum {
    MAX_SIGNIFICANT_EXP_DIF = 54
  };
};

// Floating point type wrapper. Allows to extend exponent boundaries to the
// integer type range. This class does not handle division by zero, subnormal
// numbers or NaNs.
template <typename _fpt, typename _traits = extened_exponent_fpt_traits<_fpt> >
class extended_exponent_fpt {
 public:
  typedef _fpt fpt_type;
  typedef typename _traits::exp_type exp_type;

  explicit extended_exponent_fpt(fpt_type val) {
    val_ = std::frexp(val, &exp_);
  }

  extended_exponent_fpt(fpt_type val, exp_type exp) {
    val_ = std::frexp(val, &exp_);
    exp_ += exp;
  }

  bool is_pos() const {
    return val_ > 0;
  }

  bool is_neg() const {
    return val_ < 0;
  }

  bool is_zero() const {
    return val_ == 0;
  }

  extended_exponent_fpt operator-() const {
    return extended_exponent_fpt(-val_, exp_);
  }

  extended_exponent_fpt operator+(const extended_exponent_fpt& that) const {
    if (this->val_ == 0.0 ||
        that.exp_ > this->exp_ + _traits::MAX_SIGNIFICANT_EXP_DIF) {
      return that;
    }
    if (that.val_ == 0.0 ||
        this->exp_ > that.exp_ + _traits::MAX_SIGNIFICANT_EXP_DIF) {
      return *this;
    }
    if (this->exp_ >= that.exp_) {
      exp_type exp_dif = this->exp_ - that.exp_;
      fpt_type val = std::ldexp(this->val_, exp_dif) + that.val_;
      return extended_exponent_fpt(val, that.exp_);
    } else {
      exp_type exp_dif = that.exp_ - this->exp_;
      fpt_type val = std::ldexp(that.val_, exp_dif) + this->val_;
      return extended_exponent_fpt(val, this->exp_);
    }
  }

  extended_exponent_fpt operator-(const extended_exponent_fpt& that) const {
    if (this->val_ == 0.0 ||
        that.exp_ > this->exp_ + _traits::MAX_SIGNIFICANT_EXP_DIF) {
      return extended_exponent_fpt(-that.val_, that.exp_);
    }
    if (that.val_ == 0.0 ||
        this->exp_ > that.exp_ + _traits::MAX_SIGNIFICANT_EXP_DIF) {
      return *this;
    }
    if (this->exp_ >= that.exp_) {
      exp_type exp_dif = this->exp_ - that.exp_;
      fpt_type val = std::ldexp(this->val_, exp_dif) - that.val_;
      return extended_exponent_fpt(val, that.exp_);
    } else {
      exp_type exp_dif = that.exp_ - this->exp_;
      fpt_type val = std::ldexp(-that.val_, exp_dif) + this->val_;
      return extended_exponent_fpt(val, this->exp_);
    }
  }

  extended_exponent_fpt operator*(const extended_exponent_fpt& that) const {
    fpt_type val = this->val_ * that.val_;
    exp_type exp = this->exp_ + that.exp_;
    return extended_exponent_fpt(val, exp);
  }

  extended_exponent_fpt operator/(const extended_exponent_fpt& that) const {
    fpt_type val = this->val_ / that.val_;
    exp_type exp = this->exp_ - that.exp_;
    return extended_exponent_fpt(val, exp);
  }

  extended_exponent_fpt& operator+=(const extended_exponent_fpt& that) {
    return *this = *this + that;
  }

  extended_exponent_fpt& operator-=(const extended_exponent_fpt& that) {
    return *this = *this - that;
  }

  extended_exponent_fpt& operator*=(const extended_exponent_fpt& that) {
    return *this = *this * that;
  }

  extended_exponent_fpt& operator/=(const extended_exponent_fpt& that) {
    return *this = *this / that;
  }

  extended_exponent_fpt sqrt() const {
    fpt_type val = val_;
    exp_type exp = exp_;
    if (exp & 1) {
      val *= 2.0;
      --exp;
    }
    return extended_exponent_fpt(std::sqrt(val), exp >> 1);
  }

  fpt_type d() const {
    return std::ldexp(val_, exp_);
  }

 private:
  fpt_type val_;
  exp_type exp_;
};
typedef extended_exponent_fpt<double> efpt64;

template <typename _fpt>
extended_exponent_fpt<_fpt> get_sqrt(const extended_exponent_fpt<_fpt>& that) {
  return that.sqrt();
}

template <typename _fpt>
bool is_pos(const extended_exponent_fpt<_fpt>& that) {
  return that.is_pos();
}

template <typename _fpt>
bool is_neg(const extended_exponent_fpt<_fpt>& that) {
  return that.is_neg();
}

template <typename _fpt>
bool is_zero(const extended_exponent_fpt<_fpt>& that) {
  return that.is_zero();
}

// Very efficient stack allocated big integer class.
// Supports next set of arithmetic operations: +, -, *.
template<std::size_t N>
class extended_int {
 public:
  extended_int() {}

  extended_int(int32 that) {
    if (that > 0) {
      this->chunks_[0] = that;
      this->count_ = 1;
    } else if (that < 0) {
      this->chunks_[0] = -that;
      this->count_ = -1;
    } else {
      this->count_ = 0;
    }
  }

  extended_int(int64 that) {
    if (that > 0) {
      this->chunks_[0] = static_cast<uint32>(that);
      this->chunks_[1] = that >> 32;
      this->count_ = this->chunks_[1] ? 2 : 1;
    } else if (that < 0) {
      that = -that;
      this->chunks_[0] = static_cast<uint32>(that);
      this->chunks_[1] = that >> 32;
      this->count_ = this->chunks_[1] ? -2 : -1;
    } else {
      this->count_ = 0;
    }
  }

  extended_int(const std::vector<uint32>& chunks, bool plus = true) {
    this->count_ = static_cast<int32>((std::min)(N, chunks.size()));
    for (int i = 0; i < this->count_; ++i)
      this->chunks_[i] = chunks[chunks.size() - i - 1];
    if (!plus)
      this->count_ = -this->count_;
  }

  template<std::size_t M>
  extended_int(const extended_int<M>& that) {
    this->count_ = that.count();
    std::memcpy(this->chunks_, that.chunks(), that.size() * sizeof(uint32));
  }

  extended_int& operator=(int32 that) {
    if (that > 0) {
      this->chunks_[0] = that;
      this->count_ = 1;
    } else if (that < 0) {
      this->chunks_[0] = -that;
      this->count_ = -1;
    } else {
      this->count_ = 0;
    }
    return *this;
  }

  extended_int& operator=(int64 that) {
    if (that > 0) {
      this->chunks_[0] = static_cast<uint32>(that);
      this->chunks_[1] = that >> 32;
      this->count_ = this->chunks_[1] ? 2 : 1;
    } else if (that < 0) {
      that = -that;
      this->chunks_[0] = static_cast<uint32>(that);
      this->chunks_[1] = that >> 32;
      this->count_ = this->chunks_[1] ? -2 : -1;
    } else {
      this->count_ = 0;
    }
    return *this;
  }

  template<std::size_t M>
  extended_int& operator=(const extended_int<M>& that) {
    this->count_ = that.count();
    std::memcpy(this->chunks_, that.chunks(), that.size() * sizeof(uint32));
    return *this;
  }

  bool is_pos() const {
    return this->count_ > 0;
  }

  bool is_neg() const {
    return this->count_ < 0;
  }

  bool is_zero() const {
    return this->count_ == 0;
  }

  bool operator==(const extended_int& that) const {
    if (this->count_ != that.count())
      return false;
    for (std::size_t i = 0; i < this->size(); ++i)
      if (this->chunks_[i] != that.chunks()[i])
        return false;
    return true;
  }

  bool operator!=(const extended_int& that) const {
    return !(*this == that);
  }

  bool operator<(const extended_int& that) const {
    if (this->count_ != that.count())
      return this->count_ < that.count();
    std::size_t i = this->size();
    if (!i)
      return false;
    do {
      --i;
      if (this->chunks_[i] != that.chunks()[i])
        return (this->chunks_[i] < that.chunks()[i]) ^ (this->count_ < 0);
    } while (i);
    return false;
  }

  bool operator>(const extended_int& that) const {
    return that < *this;
  }

  bool operator<=(const extended_int& that) const {
    return !(that < *this);
  }

  bool operator>=(const extended_int& that) const {
    return !(*this < that);
  }

  extended_int operator-() const {
    extended_int ret_val = *this;
    ret_val.neg();
    return ret_val;
  }

  void neg() {
    this->count_ = -this->count_;
  }

  extended_int operator+(const extended_int& that) const {
    extended_int ret_val;
    ret_val.add(*this, that);
    return ret_val;
  }

  void add(const extended_int& e1, const extended_int& e2) {
    if (!e1.count()) {
      *this = e2;
      return;
    }
    if (!e2.count()) {
      *this = e1;
      return;
    }
    if ((e1.count() > 0) ^ (e2.count() > 0)) {
      dif(e1.chunks(), e1.size(), e2.chunks(), e2.size());
    } else {
      add(e1.chunks(), e1.size(), e2.chunks(), e2.size());
    }
    if (e1.count() < 0)
      this->count_ = -this->count_;
  }

  extended_int operator-(const extended_int& that) const {
    extended_int ret_val;
    ret_val.dif(*this, that);
    return ret_val;
  }

  void dif(const extended_int& e1, const extended_int& e2) {
    if (!e1.count()) {
      *this = e2;
      this->count_ = -this->count_;
      return;
    }
    if (!e2.count()) {
      *this = e1;
      return;
    }
    if ((e1.count() > 0) ^ (e2.count() > 0)) {
      add(e1.chunks(), e1.size(), e2.chunks(), e2.size());
    } else {
      dif(e1.chunks(), e1.size(), e2.chunks(), e2.size());
    }
    if (e1.count() < 0)
      this->count_ = -this->count_;
  }

  extended_int operator*(int32 that) const {
    extended_int temp(that);
    return (*this) * temp;
  }

  extended_int operator*(int64 that) const {
    extended_int temp(that);
    return (*this) * temp;
  }

  extended_int operator*(const extended_int& that) const {
    extended_int ret_val;
    ret_val.mul(*this, that);
    return ret_val;
  }

  void mul(const extended_int& e1, const extended_int& e2) {
    if (!e1.count() || !e2.count()) {
      this->count_ = 0;
      return;
    }
    mul(e1.chunks(), e1.size(), e2.chunks(), e2.size());
    if ((e1.count() > 0) ^ (e2.count() > 0))
      this->count_ = -this->count_;
  }

  const uint32* chunks() const {
    return chunks_;
  }

  int32 count() const {
    return count_;
  }

  std::size_t size() const {
    return (std::abs)(count_);
  }

  std::pair<fpt64, int> p() const {
    std::pair<fpt64, int> ret_val(0, 0);
    std::size_t sz = this->size();
    if (!sz) {
      return ret_val;
    } else {
      if (sz == 1) {
        ret_val.first = static_cast<fpt64>(this->chunks_[0]);
      } else if (sz == 2) {
        ret_val.first = static_cast<fpt64>(this->chunks_[1]) *
                        static_cast<fpt64>(0x100000000LL) +
                        static_cast<fpt64>(this->chunks_[0]);
      } else {
        for (std::size_t i = 1; i <= 3; ++i) {
          ret_val.first *= static_cast<fpt64>(0x100000000LL);
          ret_val.first += static_cast<fpt64>(this->chunks_[sz - i]);
        }
        ret_val.second = static_cast<int>((sz - 3) << 5);
      }
    }
    if (this->count_ < 0)
      ret_val.first = -ret_val.first;
    return ret_val;
  }

  fpt64 d() const {
    std::pair<fpt64, int> p = this->p();
    return std::ldexp(p.first, p.second);
  }

 private:
  void add(const uint32* c1, std::size_t sz1,
           const uint32* c2, std::size_t sz2) {
    if (sz1 < sz2) {
      add(c2, sz2, c1, sz1);
      return;
    }
    this->count_ = static_cast<int32>(sz1);
    uint64 temp = 0;
    for (std::size_t i = 0; i < sz2; ++i) {
      temp += static_cast<uint64>(c1[i]) + static_cast<uint64>(c2[i]);
      this->chunks_[i] = static_cast<uint32>(temp);
      temp >>= 32;
    }
    for (std::size_t i = sz2; i < sz1; ++i) {
      temp += static_cast<uint64>(c1[i]);
      this->chunks_[i] = static_cast<uint32>(temp);
      temp >>= 32;
    }
    if (temp && (this->count_ != N)) {
      this->chunks_[this->count_] = static_cast<uint32>(temp);
      ++this->count_;
    }
  }

  void dif(const uint32* c1, std::size_t sz1,
           const uint32* c2, std::size_t sz2,
           bool rec = false) {
    if (sz1 < sz2) {
      dif(c2, sz2, c1, sz1, true);
      this->count_ = -this->count_;
      return;
    } else if ((sz1 == sz2) && !rec) {
      do {
        --sz1;
        if (c1[sz1] < c2[sz1]) {
          ++sz1;
          dif(c2, sz1, c1, sz1, true);
          this->count_ = -this->count_;
          return;
        } else if (c1[sz1] > c2[sz1]) {
          ++sz1;
          break;
        }
      } while (sz1);
      if (!sz1) {
        this->count_ = 0;
        return;
      }
      sz2 = sz1;
    }
    this->count_ = static_cast<int32>(sz1-1);
    bool flag = false;
    for (std::size_t i = 0; i < sz2; ++i) {
      this->chunks_[i] = c1[i] - c2[i] - (flag?1:0);
      flag = (c1[i] < c2[i]) || ((c1[i] == c2[i]) && flag);
    }
    for (std::size_t i = sz2; i < sz1; ++i) {
      this->chunks_[i] = c1[i] - (flag?1:0);
      flag = !c1[i] && flag;
    }
    if (this->chunks_[this->count_])
      ++this->count_;
  }

  void mul(const uint32* c1, std::size_t sz1,
           const uint32* c2, std::size_t sz2) {
    uint64 cur = 0, nxt, tmp;
    this->count_ = static_cast<int32>((std::min)(N, sz1 + sz2 - 1));
    for (std::size_t shift = 0; shift < static_cast<std::size_t>(this->count_);
         ++shift) {
      nxt = 0;
      for (std::size_t first = 0; first <= shift; ++first) {
        if (first >= sz1)
          break;
        std::size_t second = shift - first;
        if (second >= sz2)
          continue;
        tmp = static_cast<uint64>(c1[first]) * static_cast<uint64>(c2[second]);
        cur += static_cast<uint32>(tmp);
        nxt += tmp >> 32;
      }
      this->chunks_[shift] = static_cast<uint32>(cur);
      cur = nxt + (cur >> 32);
    }
    if (cur && (this->count_ != N)) {
      this->chunks_[this->count_] = static_cast<uint32>(cur);
      ++this->count_;
    }
  }

  uint32 chunks_[N];
  int32 count_;
};

template <std::size_t N>
bool is_pos(const extended_int<N>& that) {
  return that.count() > 0;
}

template <std::size_t N>
bool is_neg(const extended_int<N>& that) {
  return that.count() < 0;
}

template <std::size_t N>
bool is_zero(const extended_int<N>& that) {
  return !that.count();
}

struct type_converter_fpt {
  template <typename T>
  fpt64 operator()(const T& that) const {
    return static_cast<fpt64>(that);
  }

  template <std::size_t N>
  fpt64 operator()(const extended_int<N>& that) const {
    return that.d();
  }

  fpt64 operator()(const extended_exponent_fpt<fpt64>& that) const {
    return that.d();
  }
};

struct type_converter_efpt {
  template <std::size_t N>
  extended_exponent_fpt<fpt64> operator()(const extended_int<N>& that) const {
    std::pair<fpt64, int> p = that.p();
    return extended_exponent_fpt<fpt64>(p.first, p.second);
  }
};

// Voronoi coordinate type traits make it possible to extend algorithm
// input coordinate range to any user provided integer type and algorithm
// output coordinate range to any ieee-754 like floating point type.
template <typename T>
struct voronoi_ctype_traits;

template <>
struct voronoi_ctype_traits<int32> {
  typedef int32 int_type;
  typedef int64 int_x2_type;
  typedef uint64 uint_x2_type;
  typedef extended_int<64> big_int_type;
  typedef fpt64 fpt_type;
  typedef extended_exponent_fpt<fpt_type> efpt_type;
  typedef ulp_comparison<fpt_type> ulp_cmp_type;
  typedef type_converter_fpt to_fpt_converter_type;
  typedef type_converter_efpt to_efpt_converter_type;
};
}  // detail
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_DETAIL_VORONOI_CTYPES

/* voronoi_ctypes.hpp
zfURqnBqk8a9/oDkOWQtNSUJZpDG1K1kss/pAc7tNeMJiApM+mWkoaYTLuPJ4wrSyz4GgU8JTXZCekpoG9P8riRFlUhTTx2rmW0+8uPfaVKF7b7SEZidtoJofC+iL/XXnoY6fyjb4QqC8JAF4n9ube9teAJbof/J5zfYtnsH5tGFEP5aqsbCHU/CEO6/XYogzv6S/tcbrbyDhyM9C6IP3duMZ7AR+t9c2bf6vI07BMnNaIXtYJSp03AxEC3HhsJBsc7oco6hfFyBjrg/QYJmaGg8l/zrTFwm0VmBJT/37EOEPNEOeQ7bP6Mjrdv4B1lJDjf+Nnq5HpeU5NWF5MZI3JYcMZ+1I/uGYerj7IQk8D0BOT2mxxllbdrTbMDgiZzjhQGEqgN2pI9g7g9ek3pDZhKGuPuJDhVQSQMvhTNH7rFa8+LTlKr/CA7v/BsCfLEgV/41qZcOINNxaRZlqbQAjCMR7tTVIRUtqsZdbFqqerycbMee4Lt0XWBY/Gj71Jm2TAJGb762HNqRKGgltKvelHu2+4aHpZvfjmdX2p28TLUit7XzwA1txnrpU5g/Pz8Y3YGwrRrf0mGR0pk8l16fTiLaIQIrXZVOjJFgr5Q1UKNJtgq6Kdqs2gx2W/y3NgyLWQW1ueMmIrMo4TyLnCu5b0aqdB6ADYlNDdhWM0L/38ewSG9dssysLFzivQ+NYSetI3T6arekYJSkNALm0idkvH/LkPWoFWMAC+xcxujV7EHL+Swi/lX3OulextAz9aDe/oDQfy2fd+JnNMyrGoZwkKIO7B1OUXQ9T65SAdrSNGmbQLhby9X079+d5FqCaqyzh1uE7z+OvvaFAtvOedpVHSRCZHAuGnK2mnD/Fb8Kt2h5dw/8ggIA/P4OdcO4I4u00HP/WiRKePoTg0Cjk+Bjzp/5I4ITo5OCkHAa6Cf+g7ipiXVYQsnHsifxe4kuWYztqLlJqWzzTOm+0lk1UXt3QssyoOe7sAyvIRVc2xOtzicSjRgHEfzgKvU0TfS/6d593br12R93Xi5XKpXNruA8VXZRcYHV8M0tYLZaYMGEeV8HFCnngmevJMekVXj4RgEawLmchaCRfLsUjhnh1Mfa5zV+lUVwQxJHdHtd2B18ciP74d2E6bXdJKt6Vel7PZt4FjoI+A8gVcypLs4OsO63xLYVnmJzqsELrt7rogG1WDPYVnVFAxix2MVOH6hzNDMTzh4OiThUcj5MXwvpslsGMJYQ4sponF9s/OVYul69CrB/F+488swL1uPuuqAX5+kV/Ttmbpf1DcZNbs48TzvA2EEEaN7p0TGj7SoL/z9IhJVWcEWyK9GnO91/kL7QmAO9cWHN+7v8bTmhl/zG+6X04DGhPvDOUGY1e07E3fCM4ZteB9FvQFVnuCTsbTgB+yoACeYf3QHCrredP8XSmZF4M0JHOOo0Mu620TdVDs6fhc5K5DqUAXWxild8cYQjg3oMlsNEk+2IBIrDx1AJn23QBA3pz92zQxVFAfJvAEHHND1xuWV4kYE0AD80SIe7iD+v7uxUXyAkWfjCNYelHSGa29y+iXPW4aYgGCG3YkfhKjLdqjLbAeWSNHcuWDLdSc+oC308VW4IMNx9nqfzALOeTub6UJfdyWAT6rfK0Fd9toDP3+i4VN9NYSyLqiuGZjUYqskP9nqCTRtuDXK6hUF1rzY4C/YNcqZAmGpU8SRZoJx913ejRyAauxBERXgTliXdEBTl3ZoFhKpU2bd89NBxPpj4JLhnhdMBRv2rE5FyAFXpkVvB34fswuAW4FMiHO+aLIWJXHkYmSNkwvsLgJqJBXcjrQricyfAyFRSNp4W03VtOFAm3UJgMSNuyXKe644+HSJPBPJr81LFDVhEvCE+hoRLpfNHMHU7IP/ev+0MZ3gCEMETcgEgUj6Bslrq5PNRxrj8e7U2B0b96/j5534BfgQod8wS7BL7PD/FkEGHn1IBQaNwFjjl0Q/t2CT5VgT0QvRuSsD0oLi/ealXCObFkmpRNJRdu8GEv5m391/zhXGMBwflZwyi6O7gqW5GEqjJ2kQySgzLUpRV5N449wym0vwztvBRMLyrs1RQqFzNXmxizka5t4psOMJEP8XetHhc81k5h3oC79AxOMdsYbnksAqEVxrlfPOHcx7ZaERvDfH4xPfdGuW8XWCf53m2ZkPGZtutr5p6fv2ZVbBdDmyv2LfkCo0AiSk6D6YEqRLBfQGnwWEaj6MLhEXG0rcT4bwatJYmozGRn6eVyxVawGHqYZN3r4Q+Iu51gwtjnm2Bmb8dyvEJOcIG/cL+8UE0jW57l29QJYR7R1UXhyqgBC0p8j1B9lnWvP6WAyHqHDW2Akh+erefbZZPLDOq3igKyypHGIhK0E3XfjwKR8EDRcoZOPbXnXmZNs2nbLMnrgWFJW9/398AzulGBnJI4kx4T2c5Rz1ELJDajFb8C2O6/I2ATM2kndvP21cqPJJMeT8ht/Vo12L3j96ZNuujRw/qH2K4QJ09JhPVAqholcapLd4vJ1LP9q1g0g3aBUmWauFnbdgJC7NAe+0BIF+i9s4bZohR/8/ioLpSEo+ZaMybSt/TcTKvtCcOKK9MMA/kAE8/5ts8dKDYH9mGHKoCKDou1oZWCeao8mFf+moTdLAhYFuLvksmB1EGeN7xw0afclOlijytc2xVl8uksh9tjd2hTsh8FdqXVfPQPEFOQCo7gdM9WyVCsmmDu0RMGqlMEreIkyZuwEp6HhdR0vJE5j95rb/B/IKtGp+B1WsZaCkT3j+dUsbfUu2czDnOlZT3H5jT8HUcUQDseTR9sprRwqcCPQxF6wT4Fy9x8qIyugkcS7ncM9mZfnWw7H/4LMs0Y8dZkDi9iNcBFTmWC0cTUOUHUjFwmiw+zv6TSLZOUFDMWRJ4TxRf59gZ3sQFqYTYfYCgMXVKUahIGmvps8dfsKAjGNxOx8nZmu4nYyXZnLTLSSo3qN+3Sg+jBUfFwOZlTmUDUxz839AbKG4Z79YeoZbJ3BoVKh0x3p88qREGxVlMb8kbhxO2U0Q47oB+rX7SowOfFaTCzInzSFa6JV1ZnZowmG/riDQiOSfjKhZS+ZtjtTOlP+32/pSsP7oWXCzSYla+hPOxfLIIo8x3lc7QO4I9p+UPKD5xi6HV46quvZIkUuuFwwmTedTfgMLkrzjV2yR6JG8W/Q/ULsKVLIrmVCMXIky0n2SaWCky06pWTYJbKPOQOvgNQd+nUdLs/hvigzKqZa0SpGoF7YV1jhEd6Yg4KHsx6uDCuRdRrAJsllB8bzwfeWd09uMDgN6kdbzXr3xnNxWSapS4umoW35uYip2KCppCP8cZQhSokwSNwwtwfq0kWtSzg7t+A7urd6vAFreHfKWVypopNgmppqWSVA1MqrXOycnKLkGZnmRl7G+vjrdVzlHPdW3Mme1KWSHw/NMpE+h9PQucKpp2qKKi7FhzaWRZGPvQLbesOse5reO9LzBRycSo6SFhMJg/35Q0rptAoVXatfNXpdsIhG6Cwjsup0mixFTYM+pq7aQgxjBBUtBnUVdC3DOQxwyKCEY2BFySyCbNyin5VWxUlzQTH8qORB+rYdMoyOAVBBcvARyLwarAGKId2h70Sh70Qh72sBJRhLiM5qqdktkLElZ9nksbtjh1A+hajTUNhMTZyT0pgbg074fA9E59S6riasl0alLd+MRxpibLhRioUhDrrXKFgLJUefGfDekpJJD/ZUu6xgmfM2FCuF+5SLmCkcK0XxHBaD7JErFZG691AwYcqQa/aCEDrAdWyUNYfN7Sl9eL0Z/QSThvwtpIA2xl4ee9DCP+N4TE9uXE13GCnMEE+Z35eyKDzGqC3MIHthg34Dqkv2t+UKc3oi92SP+SEMZv/Ll9Yi7Rz0BxKf+fqNOXLbT3Ovob3WhfrahkLLKkxeAgw9kS+0topxE9EavSXAB9qf2YgMFuoPnrqdbSVpRhmhjCBo9IiC5qUE/QNPyUyJrxvnyNtbcVZgoL8TcaaTP53NwaL8knsvRYI1NXP6Y5zLWQSOR8DKprbXZCIpOAXKMXjNTRue9n3WDh8ybGm8oC9B7HG1DXD+InPf6AXr2HaR3LkWkvRDJ7Mb40NEGzKiexty4WMcTW849aY71b57omzRdN/Z4c6s/RgRzvD/vdKeyXxi3afBj5wab39dbzAkGatGNVVVh99Pv3JI3Il/8dx6SJZFiVWBCZCzaR7DMd29aUWLAtj5llWkdROF9jCTWxCzQuimBqVlxVQMqC2MBpWomOI5MfKbkRbp5xW0jcFq4uzEHOJ2U0+o0iYGQGYbzxjPbQeXXAHC/wm02+T9JZbUD/bgR6KrI8uo8ztxaKn4FpeVDybjX5CkBnqwhkJAsYAnYzptNdMAnFWW39189r766em0cH6AgY/qn3HauptfQyq/qD3SH4d5xs2JkATAgDQGcKnrZaeYu8j10JQ4nvDsL14Izi3KTZHMKmsfwCunloKwNeR+EgJnY9jO4hfZNDT7WHkF/h7RLG0yZC/DGMffvP9W5Wv4UwVKeYndV6Vg7SlNtbrsSIs9yK5IMVG05PDKgmQdEj2JscN6ZJEga3+xjIMUeetXAI7t58vBYrv4NYNgD4GUeTcP2R4tgRcRxJIasWpgg6bpR8iC+wyAeFyIRoO4/tqCFYoCZtsW2IRUfxvQNRYgoZLIiLNmZgAzxIMCYuW37fUXAomjnA5UdLlyKKUWMt+NgXGHpLi67s4ELj2+VriX5Dz7SfV6q968XJUAcKxSLNTyI1hwY7k0sjRqHGT+INWFSV3YJ56hrv1lzwCIhNhAvoBmJcO+WdYEbI0jdI9JqSXZ7Q94OUWrGW9+RKUKeWV25oJqFNzQPMXTRZVJcS4IucJeEsoONYkvQUGQHtFksVIHLCbf30Lgfb9oDOKdZeSXtyU7Xd3P7QSpw+3T6i9lEy1J2eKLGDRopwPQFWHqP/hrUYAyUITehX8NArP+A1CGOZj+hZM3u+ydewT3AAKkrprAdCx87YP77C9XABZnLJDNCPmcBIgxlaFLHg3Co+Mjpk0Zn7pJGCNEARXspo6MckYq/cZDt0mWQ4ox2Qcdz8llYLGauqqyqGbJUK+k7iHAoSN0pyWvrb5WibYLkEwaNqA2za/f8C0JWnMMc2W6EuxjwVjChfcAniO8vgArF6KtTGOJxXOPqq1AaYtUOQOrunYUloUigJVy4Fl23J5l7P8vjnngEKiJb04s8d47//+n3TLvCHhtcani3jURXpRQGbyWW51P9IrKz83Q5Tqau6qhWiFNwL0qCoKVShOY6gcd/szPgJIN1Ly0mkZ/O31H+D1VHWKB8VbP34KgfLoIA2aKwD61I3SNi03IZTfpG2UYQ1O7kCI19Cza0w1C4oVOlqWxCJSNkNy38gtG4JuosFjd6Z5Aj3qVLaMGBdT/8+yg4of3N7gcWWQe3fRbD/jemP1jnzO3IpuZ2gXZlWfq7tWCsoGwz+O6ZzotN8E/LUGl9ginHa1/FXvLI+PtL8OQ19lKzoShRWetmMosryYFnF0e9UZtz11Idq+QrhjbJOfRZs8FKFLfa/zPkEqhvV8DooLbUqXlHOPJViF5W5kyMB9K6C7HoUdHU7ClYRVGhPxlsWbDScnsKqVvhpX2BOgczKosZSt39MLLKgjD0esDyy8zswMWeDYIlvRhMlFW/k6eQoqjSKoxFBzBwOPVoax8mo+2PyvDjk2rVGPmQOA2ZD8+UmPjrwAQiEvhhYgaChaqj8333vniYEPhl642GlLPiCo1HolTS2FiIBwzQZ12pA7HqkzCYIroEXRyMoGOkwMHTH+oLqMvww2jCQVMAs0kKDM1QM11IhsRvsm0nn5rFMOdIYubH0pQ8W1sKX9ubHQI0fdPbsk43B4QNmy7kqThzjpXvLqUmGatbXaqz/3Fys8koTKgX2g4NFuv0kW83fJHKchkBBJjNj/s0pTubBypdKZcQlUobEqld4E/K0SAWdBC1y0TfYWR9N1yf0mQ/1zsxbm82xVfuxP1COpWXinxdaDAwOnqWgoRvex4tQmLrj3zHsYSUQ85cfiq8LsHpDXqLgA2oIGXzrGVU6xix11RDSkuUk4H5TRd6Yl9MM8dSZw7ILaac8kTeA+U90Qf+4ns/7WFpDDpFyjbnsZVF50aO1Y3CfPTiez7ONEhTFEIL4xv6bwC0Sm+E4uLvFZgcoEgO2HCmOZ9DzfKIfOjmQd40n8sfn+eAN3hUVoyhdF4BVlNdibolCHPwyDgO26RDxRKbqMCeLPC7oOo0nOyoZB95whSNNqG5S9pPRDm+ugCeThOgTRqQH7G5BTnhYgXFKKjIJVbDnDQwxpVw0RWsHKzzcWLtS0nc1NuP/etRWrLGJz1SipMXHxb7QB6YDCgqzcmSznJj/p+moQtSG0Fm3pB1Bh5Gn0wdg1RK0ozBhUFSXJ17EuwyAVgM+Ww0GbU8a8YXbd3kbpbk/TLsMKdeBU12Xzv3hoQxK/giRTMC8fUp4HFlh6zkS0x/kr+MF5PTIwzCZuu9M0bWuJz2Wy/8ogQLtsm49ylaTGBlRh0d2vJGh3CSIW530BaPGAei7Rk0m9UxjrvCCORFsSzPmn3KxW0o6Eo/gG5KR5wuDuchrKS20jyZ/uR5RJ1fsEaPeD1KJASYRBG9G0YT25STljOOuWJh9f4Z5NQiDcppxRZThyBGjXY+oMoSy5qWFRRmaeXXKLOVP+HZzCfOzjBDnaxLR6942BLooViTJ+byEINT5DuCjVWjyuka0BeIqdy9flykBKapBfSOkl89oe4NG44OAEgu69oDWTQMts82t8M9YQMtCPiWsDnCSSvDWiM6eo9hQSpFKLRq4cqPLbRyr9XYcqLTHwdVQzgjITcPQP5OC2SLE9BpGz4Z++252mnP7PzZmIXKQ/BKsjndigqrjOHUtu7MT0itw0hSYjn5ZirYSRx2rs+/7X232JDnIOyd9sOhGz8ZmnzutcmCysburJMEgN6AuEcuB0p/wLugBK8AGys1odrEBsVhcDo8iovKUWzxummdAVUp96ukWaN9yvgaCYTD3zHSYKhh7Npk2FnBEWs2UbEseSAIwwZP+WTCu4Fnmhc4FMUWyVCWPsQLZCIHqog8wy8R8Ko3wX1XOhU9irxI6+aQj+TfoB/iQfKN/Mpmx+MIhseBAKgsPAnwT5wvgHDRd84VUSUlVgHpUnTR7ehXzqqKjmcZyMYqN8diSMvtMAbFG0NnQ9omUBzcHZZOk1TMAu/Mqlp9lJ4Z5RN2d3gJgo0ebO0EUapWEOBMQqOuwKlaPIl6h6gjjlWMnSXnnJDDsYQU8Whm/pHfgM9rD2GRrD9Av6/4DpR8wt+blgceNAiZBuXNmXJNk/o+tiH0soDm2Vl7re3nw8zZtO73ODI3iwERmj8YP2kTQDYN5xoyZLLeD9glknOL9NPI4ADLmK84BGmhA0ea34GwlBXy1Bble1cr7n/nq5EicnKmh3+1Y4IveVXWL5YTyFN6EG0Qt8JfDFN++1Atq1vu0/11p/Bty+M8srk6up4Axh4PV6A2iSB2nPru63QL6cZXgsWXvxNlRG2QmzMasveIE5Ejb3PTIAvbhbPqUiU6Ev5nCv019n0heeDdNMe+ZzoXzkbLBPWiRIrMPJq8ancLFcHrhJSAvH6z4KKb0U4Dg4fuoFx/gx739twZ3rnuvUeNXFFczGlarKj3/2EHRHlMFl2/U7lZIUqGDnLnZHPwdyOV+/6rjwoDz6Pwpz0UZCgiTsn91ohzxCc28HLgpHfSbcHkYOXvqN2+hI5JLzkIEkzI048qM34KkoCSSeT3sIIMSJSXFZ03hoFUM2zeYY2yUT0gkBRQ2xSSgm6+GuRqQA0WN0HRj+pB5GVOFhV2BwNhfcAwgJD4SmKMGfuruS1xXEIXf0hlh7gsYEj+I0n+pDajOH0gcAFR/p6h7eQOWyFvGOjyoaH4kDxjQlTy769+imJxncZrUix14AkvItL4h97oKOQJaexGyvivTGkT8hBhiEFF5G1wHS5tv87lW+ke+d9+aOWkxA+ODXoj4wMrQRu1lGG9W95FaZq99qiezissKkqYYRDqIar+e8lntqEi9jZ8HpB5J1jNfkfsNciWRIQOwi+1Oi638PblK74BbIM6cSQtE7uVzWCBCtl/5T6aN4lDvEc15ow0VzlArBn0G3cdY4buUToTqIcgcGIDEss/H2NDyN5B4R4t7ZX+ptTaY8UVmAriBS6+oZTkfIFgx7NdvWPRkyMo+iXfD6YzNcZBQjysvimfQfQ/Ini3fMayB1JMZQ643DWWS+Yn6zJBfOhPgFKuORMhN8GOYbz19c3JagFQcIaqpbWWFl48wYM/uRhG5QkkYix1ojUTr3Ujrxz4Biqmm1n9H28ZlsqmcqUcmrLY8QlSd2l3LiUbmT+ZDgkxNcUgfBYlSOwCMOSAE+uS7rOwgSVeUUpDu8t5+5WcT+L07RakT1pUXn6r9iv8BDUlEPVMLUzcgABjm7+/0DWSFux9y1jNOYqorrWMqbe3h31sc/WQeenHheuFidUMruzhS0lMNOFcbcjv+kD9cF45h8EVzeyB73JA3kMR2wUFBXE/m9aJ+fCL+eNZUTQiuTkLlZD+Xqc8TqnpTqz6Fo4wORcLWF2wm8decDUHIDNN7oLG5rHV+v+CCl6uUTRj52B0+bfhOCZCO4vvlxcPKQzCMPY6tFHUyY87/9LB346HR8CoPidgRukW5DtipuJpWhDADgq1JJ/BZc007QJnaX+rFAtCSr0hh0z6M2SmDDno6VLOnAvFeQLmK2yeU9pNMucWvthBtUFkyXsoMqpXRDhT2/pu58g5O+u2CUYnBWHTAvBjyO1q2iUQszLjCD3HljBHiV5mPYt+eBBEysjLtDiu7bRaWHonsiraYO9sz7Xgs4QNEoBWR9AIMuIZ6DlO+O/2X8+KYK+ldoO5NPfomSK0XZq1YfN3aypGVM0x/quQoVanaFf4o9uNjMc/L+S1yylhbECMX7CyxKN+iLisvhGH0UM3Wd+ZHkZF0Uq+fQzw0xaZPSoo5Zd7iJy2m5gJ3PgzxDQRh+p4rLIRTlB1qmOPEoTkdGaexa8Z+uNLJ/a7o0urIc18TcwOr7+PlIJIvoed2qJ1j0dKKfy2Idg5UrOsrBzCKGF4w30QfZoR6YiujlabGVS8=
*/