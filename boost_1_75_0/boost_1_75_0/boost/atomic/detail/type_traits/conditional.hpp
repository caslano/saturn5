/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/conditional.hpp
 *
 * This header defines \c conditional type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_CONDITIONAL_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_CONDITIONAL_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <boost/type_traits/conditional.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
using std::conditional;
#else
using boost::conditional;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_CONDITIONAL_HPP_INCLUDED_

/* conditional.hpp
VNMqLuCl8+xldOd48In+JKRfw7FiVYjjR6mexXPNINw0oSsXquUlzHsyYJTeBd0RHln/1DKFW51U5VpqiG5f0iy85w+1o9r3vlYPn/2ePzEnO5F1SricmLpIeN6WuuwAOClcE24GcuZMzG+M76HL2a+X9bTkC4CDCKcltPIwQNMgDaJ7/aQDDN3fggp2s4qHUcU195Rv5O98shjuaYtZt+OmX/qXl/r8ZOckBQNIUL6lCMsQomtFBX8shtyhP3KLyhPl91BOVf9RKKRk2+Hzz5TmfZ46H8Sz5HENloSslKKUnAPcgbJIfh/N84HiuNkn34SmCxxMxvWL4hb9Gs8zhu86ruFaOChJUrbn6y2J52H8mGHwHwwR7NdPAv5oWc0zdeh6KnQlgAMHA8dC0DR/w64QHkxlf89g/9ZocQlctHfgs485d17uNXMWdniHx/iNLpvgD+lS+VJfIaNZTp5LABvzjife5xGmx0Cl2aZpMCoiR1IFjLrXU9yDdgq8Xrjm+wFmTsRBREqqhSib5fPMwKZhRaUJCNSiP3Kd/VFPoIvB5pG4S8kMC1R1TQqXhwPgdnByuB70r50YBLoVH1cSNq5QioPjETTtwXiS7yw6MpV3W0VOlR+577m3+Qbl+FNlCEGPjWw5c8xYe36DrkuPn/8AtdEW5OZLhN6k7foWDFBpWBu9xGka1r1+2WKtFFJqkWOF3TQp+FZqInMr
*/