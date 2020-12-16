// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ACCUMULATORS_WEIGHTED_SUM_HPP
#define BOOST_HISTOGRAM_ACCUMULATORS_WEIGHTED_SUM_HPP

#include <boost/core/nvp.hpp>
#include <boost/histogram/fwd.hpp> // for weighted_sum<>
#include <type_traits>

namespace boost {
namespace histogram {
namespace accumulators {

/// Holds sum of weights and its variance estimate
template <class ValueType>
class weighted_sum {
public:
  using value_type = ValueType;
  using const_reference = const value_type&;

  weighted_sum() = default;

  /// Initialize sum to value and allow implicit conversion
  weighted_sum(const_reference value) noexcept : weighted_sum(value, value) {}

  /// Allow implicit conversion from sum<T>
  template <class T>
  weighted_sum(const weighted_sum<T>& s) noexcept
      : weighted_sum(s.value(), s.variance()) {}

  /// Initialize sum to value and variance
  weighted_sum(const_reference value, const_reference variance) noexcept
      : sum_of_weights_(value), sum_of_weights_squared_(variance) {}

  /// Increment by one.
  weighted_sum& operator++() {
    ++sum_of_weights_;
    ++sum_of_weights_squared_;
    return *this;
  }

  /// Increment by weight.
  template <class T>
  weighted_sum& operator+=(const weight_type<T>& w) {
    sum_of_weights_ += w.value;
    sum_of_weights_squared_ += w.value * w.value;
    return *this;
  }

  /// Added another weighted sum.
  weighted_sum& operator+=(const weighted_sum& rhs) {
    sum_of_weights_ += rhs.sum_of_weights_;
    sum_of_weights_squared_ += rhs.sum_of_weights_squared_;
    return *this;
  }

  /// Scale by value.
  weighted_sum& operator*=(const_reference x) {
    sum_of_weights_ *= x;
    sum_of_weights_squared_ *= x * x;
    return *this;
  }

  bool operator==(const weighted_sum& rhs) const noexcept {
    return sum_of_weights_ == rhs.sum_of_weights_ &&
           sum_of_weights_squared_ == rhs.sum_of_weights_squared_;
  }

  bool operator!=(const weighted_sum& rhs) const noexcept { return !operator==(rhs); }

  /// Return value of the sum.
  const_reference value() const noexcept { return sum_of_weights_; }

  /// Return estimated variance of the sum.
  const_reference variance() const noexcept { return sum_of_weights_squared_; }

  // lossy conversion must be explicit
  explicit operator const_reference() const { return sum_of_weights_; }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    ar& make_nvp("sum_of_weights", sum_of_weights_);
    ar& make_nvp("sum_of_weights_squared", sum_of_weights_squared_);
  }

private:
  value_type sum_of_weights_{};
  value_type sum_of_weights_squared_{};
};

} // namespace accumulators
} // namespace histogram
} // namespace boost

#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED
namespace std {
template <class T, class U>
struct common_type<boost::histogram::accumulators::weighted_sum<T>,
                   boost::histogram::accumulators::weighted_sum<U>> {
  using type = boost::histogram::accumulators::weighted_sum<common_type_t<T, U>>;
};

template <class T, class U>
struct common_type<boost::histogram::accumulators::weighted_sum<T>, U> {
  using type = boost::histogram::accumulators::weighted_sum<common_type_t<T, U>>;
};

template <class T, class U>
struct common_type<T, boost::histogram::accumulators::weighted_sum<U>> {
  using type = boost::histogram::accumulators::weighted_sum<common_type_t<T, U>>;
};
} // namespace std
#endif

#endif

/* weighted_sum.hpp
kBf5Oq/2lp+Ivu/IjBh9HxnRSFOeNKnB55Hat9DEsQaQ72zIke4fZIx0rEuf2qEQAFF+RFNN6LAV5MwUlHu0oSN7YpaEuj4j3qHI61QzAwSK1y/lNCDYNholjW/TrM+k7lKXA9D6DLxeZmBfYxdeNTT0YwN1w6hlekz8ey6IYhRn/fUHOW3119J+wJRlru8o7GSqDhsDiuNPbHkbpzsxvVkFit+K2c0qOJ/9gU2vtUDJmkL5C2xZUzrI35SP8UWHLXHhytI4/mdObDg8LjZ8R25seIIrVn+8+NY+jIRGeFl1bDgzLvxUVWx4b1y6iKtPqYkNV90WGx4RF66Kza8eRThM9mT3FcVbF3D+o+3kF6ULmWi2A2IV45H1TW+vPk7H2u+4PPovy3dttzyni5cWdFi+JKiXf66w3fFQen1cfrGx4/qWGeNZ2259nC6mdFx+r1F+fLvlOV2YOy6fdqte/tS0dsdD6fVx+cWj8zusb7FR3y/arY/TxU0dl68y8OXadstzuri04/LCaH9Yu+U5XXzw1Q7LP2SUb5raLjwovT4uv9jScX1YHzr+t1cfp4Nb77j8ZgPfrmy/P5ReH5sf+N9xfVj/Ov633x+kA/+v7LC8UmPgf0G75ZEOs4oOyxv0IPInDhZFb6RYv3HpDUa6sT7j0n9qpBvrLS791tj0ZfH1L41N3xufXmSkG/gfl35xbPri+HRrXP/bjL8wJl3El28w0g18ix+/kW7gU/z4jXQDP+LHb6Qb8x8//th0pSZ+/Hp67PzaefueOS92++b5jUof0Tad59dIt7dN5/k10t/3tElfFl3/C23T90an/7ptOs+vkb65bfri6PRlnrb9jxl/23QRXX5EXDrPb/T449J5fqPH745Px/xGjz8unec3evxt05Wa6PHHp0v+KcKzRe7/TCF5GzGUT5sR9sD+4vtkrAGlR5l4frZxeumu5pEc9WwIx59vNPPzBvdZwJAbdtI958J0oyyIb2GSuxmdGtX8SKFKXNYdKmZdpht1kX8hMMJTiGe9L2s7H5fAxfffpjPVdmhM/jhNr2htP3VGpKL1XFEXoyJyrkIqrhrWDPXjDivcYXekyM3N46jDHbflETOi2pofKXgLt3XfGL2tMo9o6Nua7+uRfOs4301Gvgqt4dObe3/qj1vcgdFqR0khGR4rbh4jLxZg+HwYpcPkIDcZh14z0phFR9DqFg9nUVC/9dzxeVLKD8iW0G8T44bhnFJEwgxDoMCGpThpZQcq7Sa/XWybTjnsZGzmgQ2y+HCE0ai8Z+QRf8zkdis6e471iL42KajwDSCUDhXjxfh7yo1qu3nENy6gAN+vZsFLYyKpLEgy+jWZEqxUZGuduTFNOm+NzOmE9yIurQlxbyJ6AP0cQ7lfaJZSXiouiHRhsFu09OCs4ZVO0aeAfzZO5bORbkHeaOUurVTEizJnED+bhgJWU0mm0EhHRFR9BbSzhaVGvX28yyVe3YD/hoq+oxmvmr9HGkxtqtNdhlklIaOGFl1iBp8AWRPqh8RNmvrNxK3x2aaIInYBEmil5JyAcds0fY1UDkWrPwEvgbU2hPM6KW828nqKxB6ZLe/our9/+rc0OvPR7YkUum8dXu4UV8sGjTYi9+e7sE9b9m203kkXVUMlUKN5HNM/EKONPt7Cj5xhOHsAknB2mdhSrI/H1wtjSYqM5TUsTK4OK/QTkEK+zximndIthg/RNeRrGfvlKmi2szzsKslO0exE/7nE70YZlqgp8p5jx6gfbV9FPBoBJCmaTTP0ARlG0NAf6NpDO+zrg3w6lh5npIQSSnVOtRmp9ujU83u8ke3Z62PD6TFht7ZcIf8T6n0mgxYu894InL0=
*/