#ifndef BOOST_MP11_INTEGRAL_HPP_INCLUDED
#define BOOST_MP11_INTEGRAL_HPP_INCLUDED

//  Copyright 2015 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/version.hpp>
#include <type_traits>
#include <cstddef>

namespace boost
{
namespace mp11
{

// mp_bool
template<bool B> using mp_bool = std::integral_constant<bool, B>;

using mp_true = mp_bool<true>;
using mp_false = mp_bool<false>;

// mp_to_bool
template<class T> using mp_to_bool = mp_bool<static_cast<bool>( T::value )>;

// mp_not<T>
template<class T> using mp_not = mp_bool< !T::value >;

// mp_int
template<int I> using mp_int = std::integral_constant<int, I>;

// mp_size_t
template<std::size_t N> using mp_size_t = std::integral_constant<std::size_t, N>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_INTEGRAL_HPP_INCLUDED

/* integral.hpp
pc27wK2n3MiL6WHum/T1tnhHMuKdqudpOWKPwxhbY+X1yO7G1uZ4bmsPQzgIE2n3L1o9PItRDUqOo+qDjA1HbXeqD1uaVB3vnLxKa7attDbIWWaKsy5iZXhKZHH4sojh4aPokW7HYOtUyQgUUI5tuHWUPgid5oV2Z4STPjhAXSc9Axqmrgf9wj3criGc/ioIVw8x7r9aHzwriHoLHdnz1hfoJu54uidXH0yRoJH0TTpFDHRNFAOTJ4iBprFH6cYWBPkR9c3bIfQbasw9AptGU8D9yibzUaV0b+cF+oDH3dnzhCs0rVyP51uYm9BpxIhC2w75/PuE8AUR1ZEFUTdFLg+Pd8bTzcyRyXQ7szY4YnCkk29pNi6g/Kvn9Vcg6fJ5/Vsh7B5q7+Z5/at++Xl93tQ4+nn9Of7n9Vf9e8/ry3V2v6O+t5h4Fo/J50GYdpaxFgj+5vhALawdsnwd1SPo77xW3rsLD9q7qz+L9+6uh9AM88xZduNZhPX83seAoV4+i7DuLP/y7DV0ABWWyHa92ppsy7NnWrF2pB29zv082a/S91oHoV+NPqpfPXIW71OHYnLsglkBM8hm3/yINeBrifyd+YA3IPNF/hT7FnhsTTryPMbmUvm78xNN/SdLoyTorFsselhEZC2iEDGxSxM6e9bJ59mMHLWVQv6+b9pAaJz1bvSyNziywwqdvc0RczTboehnYjbEbo2O6Jdi
*/