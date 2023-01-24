// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_WEIGHT_HPP
#define BOOST_HISTOGRAM_WEIGHT_HPP

#include <utility>

namespace boost {
namespace histogram {

/** Weight holder and type envelope.

  You should not construct these directly, use the weight() helper function.

  @tparam Underlying arithmetic type.
*/
template <class T>
struct weight_type {
  /// Access underlying value.
  T value;

  /// Allow implicit conversions of types when the underlying value type allows them.
  template <class U>
  operator weight_type<U>() const {
    return weight_type<U>{static_cast<U>(value)};
  }
};

/** Helper function to mark argument as weight.

  @param t argument to be forward to the histogram.
*/
template <class T>
auto weight(T&& t) noexcept {
  return weight_type<T>{std::forward<T>(t)};
}

} // namespace histogram
} // namespace boost

#endif

/* weight.hpp
+CbgNxKxFpnd1Xi3MLJvt8Kot8jYF5hOeFKU6t9UFDQn0piaM7TimRQ+UzHGfOo/EIHm2tWfiGhFp0gaG7TCC3nhuh+LNt2TNR32KZwGkFkFY5eIoDU+d8LoQm404z4o7bSa6QdD7GpKPxSVpdvkJL9dGQYNOvqsRNJloXvx/cCF8u1jv/2SuL5rPdbvstcI0gXx7WxLZJyzbI+d/ixD8F9pL6r5JnxIzhkBqQw3Bw7wpMlAJh+KODQjKwZqsEfeGqeYmwYeps5rccFGBA1TQKa9598ITZ+7miO/UQQuxDkYq0gJktIDZ6INZKdHI+3pDfnXeyfTqdcU8zQgJjVhDB+pP3/IcstSUvFbdT8btGzHUHwYDHQpiM1VWoRqoRirvLYI8KnhLWHAB+hvccJj6gD62dkkYkMsPhYfe2L00Md4vCsgCTp2TVVjZKDiok50JrUrZOIZ+hCggz9dBrp3p0dUbSI7okhH/0iBFxxgEK4WpoVJh38oPmK4pFyGCgn22iIVkImx2cp86VIBNPJ28K4Q1bD9ugS2fGMSwMQBJeqXiNOJnHY/LZxZtWDtYcAfyeFIJFAX8gvmNkfApF4T7bcMeI6CD2FlBFOvPTiUy2oh1skWYamG5CoaZ6vRxz/z+1QZkRL8wD2RJ7LTghpNahCghiHAL57GeOmZeGik8+pSJBG/v0nNFKum8cscpdd7lZIbtvoJdcbtDRWH
*/