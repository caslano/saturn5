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
+lm9HoV75A4lGY+dKKZ3yuQD1kFhet182zZK3rmi5Q5SHYZQccPrimUOvJgN0ey6EI2XHp6LBtRWIuYtw1BlNwhTYdUjqHCYWH9txJlCNEuCzU1J89eUOBI3dgnYquYTNcOG3MsQZHrXRhmjmPZqj5WhQX7PKrHDojWDIhmNbq9WWos1tZ+SBYk76G8UjkXNm3sswprl1UMAy8N87ZUBFR4X6KAO1hPjQsuZYU90Ue4JIuFix0R9Si3KDQVCnpEebL8+YxZ62OldzFaxd6Q4/RguYmTZnTMd09i2wgA17SWebfOrwy6fjNFjStdsgh+O+xwv4yDGtQd5iFzQRDY6sIrG09FTTVaB0LolabpxzBJWdB7NXz/rxCJMFoc66OoTHd9KDFRsBke93kPJ0Tpe/0SXrAuq8awHmdpsyJ0t6/KPLtFWYmiT4DQDqMZkYU1IMrgAcTuFXP0IUgGMtKdbbMq/4YN+seypebvHVhR45wM6QEqY9ogdXaWiaL7Ppy6n8fSwsMRWE8sfHxdXq8Ok0t2vJXWGELATkbkuroSkWHWN64hd0B7jthvz/pghBqBm+6OVGdGHRwSxn4fpaDxJFxfzZJ8ae6KWEP4+nz1OARjb1dH7uzR2DEXbo9UgLHXxg1l6NAM9ygN3ebSo
*/