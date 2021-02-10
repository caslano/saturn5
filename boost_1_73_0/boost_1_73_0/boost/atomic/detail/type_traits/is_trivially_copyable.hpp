/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_trivially_copyable.hpp
 *
 * This header defines \c is_trivially_copyable type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#else
// For std::is_trivially_copyable we require a genuine support from the compiler.
// Fallback to is_pod or a false negative result in Boost.TypeTraits is not acceptable
// as this trait will be used in a static assert and may deny valid uses of boost::atomic/atomic_ref.
#define BOOST_ATOMIC_DETAIL_NO_CXX11_IS_TRIVIALLY_COPYABLE
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_IS_TRIVIALLY_COPYABLE)

namespace boost {
namespace atomics {
namespace detail {

using std::is_trivially_copyable;

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_IS_TRIVIALLY_COPYABLE)

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED_

/* is_trivially_copyable.hpp
Cm9t6agN3fihNDY9IJqMpmfeyePu1lKy5zLaICi6eynjIoEAHXwroYMF0WmSfY7dZO5AnhSCFiFRiTNTxSiIn9zzmNucZeiK04yGBj93RtAPQdFX6/3AGfxsfcIA4geNfEQwFbvUOqVuJo2Mxu3Oz07/rEZTdchm4tJwh7yZIyJ9O7H7YhehO0oQV2kAIhGljvMRrX6Yzp3BCVsSTkoodyaDmOKClm2LRZBHYmbEd1+oM67WHvUOHbv9grIp5EI0U6+QRBRgNo9522ntGWbEn38K+t18E8jwKpshHcAPqr5FErJyCRZLxGvRH1g9pBTOHHqIJjVjkdgTh3UCnMv5JL6tAb4heJ4Cjv6o8Wt8vxhjvwH5AY3rbZnCO2a+Tcq6kaHPSXcCiyb7gUFcyYx8VYmS2s0sEi2RNdXPbx2AO7CrmlIjqbChzYDET6poVMRjPwQKJDgOoQJao8RKw/6KRbQ7SKpHDrWbh7bKkqkhy7T64ZQNofwG7tm8ciId78ivKRJXdmuwPtS/EKPWYXrtbG7nhIt5rdyhvlWriLs1n0UvfPFKPAkRQPf26uxfQmyCE5ceUG7HdeMGC2lgg2GwOTAj/ZOfHCRAR6Hv1Vyv+UZF3zqybFZPvifD0jxMkGNd8w2HRoChJnBgCCVk
*/