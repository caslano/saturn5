/* Boost interval/detail/interval_prototype.hpp file
 *
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_INTERVAL_PROTOTYPE_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_INTERVAL_PROTOTYPE_HPP

namespace boost {
namespace numeric {

namespace interval_lib {

template<class T> struct rounded_math;
template<class T> struct checking_strict;
class comparison_error;
template<class Rounding, class Checking> struct policies;

/*
 * default policies class
 */

template<class T>
struct default_policies
{
  typedef policies<rounded_math<T>, checking_strict<T> > type;
};
    
} // namespace interval_lib

template<class T, class Policies = typename interval_lib::default_policies<T>::type >
class interval;  

} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_DETAIL_INTERVAL_PROTOTYPE_HPP

/* interval_prototype.hpp
bQZAuScsYdJRdwurgkrsCHrd1cEOzycEL1iKWdTcXyH4qTv6MBx3XWj3rdXFBKv0Om/Ut33OAqeeAruPZcU8WVA1InOOnUJrzyLqJXlqHnwrPC9xo8aCa0RRRb6/IIgPtraqLZYJemIfS+FoCcwg0WQhd94NzVNH/9DBYkT1MPeUgurRRENZrNaS8TJoCNlPC5hp90tExmieMPU47oxK7LvFTjFOWxOOITcm1hBXrQtsQRFBcicIl2UqolYj7SMyG8JjdWTYh5+qU2vaCJQlapaxi+gjob5ud4RxYmkVi9jqc5xbdM2KOVYt9kVvTvUWtW2i8ZEsxtAds/V5xKdeZApBKZKT/vBDp086/YK9Jpv6uc0lrmLe0CvKF/iprdqYZvgtqfMGI3M1pi5UvcCsaEJgCtvwk86SZXyQZrjjwMHWS7PMhbUNsbfh4/CCc0LyMzYbbRqsKZRJOGz4V8ma21gc0z72+l1CXLzr9wb6TrkxxH6yZHTB4HgSUWfXhmP2jsc2dp3YbN+FNwsMsMT3phzx5UkJMeW5dOxTY9cpEoJYaeJbaANOdJu0DjDPzaZCRkNVNgPEqzCwfRhjft+/N6ken5Dj4aBbCdqElNK+J70dXEP7+6UMmlOQ1HB7ppVUSGQ05re0ILANt/Si
*/