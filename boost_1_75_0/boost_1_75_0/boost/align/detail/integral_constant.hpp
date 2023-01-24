/*
Copyright 2014-2016 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_INTEGRAL_CONSTANT_HPP
#define BOOST_ALIGN_DETAIL_INTEGRAL_CONSTANT_HPP

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#endif

namespace boost {
namespace alignment {
namespace detail {

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
using std::integral_constant;
using std::true_type;
using std::false_type;
#else
template<class T, T Value>
struct integral_constant {
    typedef T value_type;
    typedef integral_constant type;

    BOOST_CONSTEXPR operator value_type() const BOOST_NOEXCEPT {
        return Value;
    }

    BOOST_CONSTEXPR value_type operator()() const BOOST_NOEXCEPT {
        return Value;
    }

    BOOST_STATIC_CONSTEXPR T value = Value;
};

template<class T, T Value>
BOOST_CONSTEXPR_OR_CONST T integral_constant<T, Value>::value;

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;
#endif

} /* detail */
} /* alignment */
} /* boost */

#endif

/* integral_constant.hpp
w6Cb7wX5nHBGXYFqy8SK94GCZXKLW4Dj8rb7FcaXagKdSO7PoUW39YjS0fN2BmocyJ/QIVYby0WzXQTFDwuGeLHP5x+5T+KLGiQ6Mnu4dQspRfOuQWocnL7qNK7TK5GFro1tHqhjvyM8gCAXC6ioMsvavorjtX6uixg9OZOVr+7DFxRmq3QELs/0vR7IoBXPy27szLgcQAUVkm2R/PAnKhWsKsjPF9c5IUgqhdqaKI9yogu8uD49hA7wgjYae77XNhyvu7vreafaQnj8kx/IvTYVJmLvxqqLS7377QUCk+U3Fecf9N/GHf7V4nHCTqoMJX2hLi93GGrdgXWz3Duixg6GI+LUEInlpeJwkku94b8ZhvUCDAnjqdLPmN9DlDFvAvVOLBui2qF6lLy5d9DNEilU0VR5as0Q981y5/pWIZl/hHqJxso6PEIY1pBscWwi94VkbsOP8Lo9Jtw54jswpHDIpOvsEbjBjUp5syJw/U2ChXgWzIU0yY3hj6q33pE8pWEB1DZLjyVLMwUVaRHOaDYhD6uOtiSMCBIcnoUmUKqQDXCHKQ7HhxLOeiVS7JinoP9+OlSV9SQP9yi0Uqq09BqsZTf1KWtPkxPORYTAn8o/HD1ILnxQwg9mOBjXeBEoVwzmHX7TTx01H/5uMpA/ui9+3z/35QaHBZdmgzHHRg4YaWO/ZR+O/5XEKG4M31Bsm33l+Qohdjiqax1p
*/