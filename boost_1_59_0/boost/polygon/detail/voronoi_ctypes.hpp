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
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
*/