/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_FIRST_SCALAR_HPP
#define BOOST_CORE_FIRST_SCALAR_HPP

#include <boost/config.hpp>
#include <cstddef>

namespace boost {
namespace detail {

template<class T>
struct make_scalar {
    typedef T type;
};

template<class T, std::size_t N>
struct make_scalar<T[N]> {
    typedef typename make_scalar<T>::type type;
};

} /* detail */

template<class T>
BOOST_CONSTEXPR inline T*
first_scalar(T* p) BOOST_NOEXCEPT
{
    return p;
}

template<class T, std::size_t N>
BOOST_CONSTEXPR inline typename detail::make_scalar<T>::type*
first_scalar(T (*p)[N]) BOOST_NOEXCEPT
{
    return boost::first_scalar(&(*p)[0]);
}

} /* boost */

#endif

/* first_scalar.hpp
cBj8DTwVToK71V2QeHNhKsyHLeAU2BmeDvvCYjga4l7SXcfW79n6zX8ZbIbZo+meaRMunAPrwrlwKpwH58Fz4Z/h+fB+eAH8Gi6A2QR6ERwAF8ICeDE8E/4J3gkvhY/AK+HH8Bro5ON6mApvgY3g7bAJXA8PgS/BY+E9cBy8D86D98ML4QNwIXwELoePwfvhE/Az+AwMkLF1sB58KToe2vqtS7+nLYPtKsdvOV7FXUv4GmwD
*/