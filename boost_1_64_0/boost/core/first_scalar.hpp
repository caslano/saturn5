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
L2wqLn24OmN1OOjo6d7J2sCLkqN4Dpxkus1eaYDVftbMuraoTRQnnAbOkeF6GRhbqy+1TzcrRUyF7gTYjmdH7dLP1FNqRexuUocmXPG4c3PSqzavfYb7WIgS5LOaElTus9WPEARBrAssT80nFNo0TAE9gasSgeNDmzqxHGNHTRyDIPyNtWXovNpDtLKLtzA0bh16OzDsz2+EvrWmj8tgGkxYOp/k68xdgtTD0tv9Q9j6UBAdx9iX85c8zwRNCP9oYqD6flcx4WDUqJpTNt7sPvplVatQ8cfN7BSx3gTd/tDq2pnIAmpifoNBgptvzKgxTTTYEK5HC14SkpboVDeizfEZYrGdsDQ+AXpM7DyPmnzsyBLgBcRb3ahGiYLw2BB/VpGjlzzldLQcRs3SOQQ8t6LYrI/pvYPUrS582nQ7kUqNofL0jLCKIIgBTMpvygAk1UtFdJnJLPJ0fKSz9TlQ+fz09/dXg+PBp/USLlrirZPL3moPUoF2HAWM8s8J/AafyGPMTyfQz8PfXvj3zXbZeYG/PlAmZLHEV553vKGESY87ZbaW5eSXkBrDgA==
*/