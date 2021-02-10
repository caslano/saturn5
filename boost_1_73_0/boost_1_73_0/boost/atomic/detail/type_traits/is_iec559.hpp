/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_iec559.hpp
 *
 * This header defines \c is_iec559 type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_IEC559_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_IEC559_HPP_INCLUDED_

#include <limits>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename T >
struct is_iec559
{
    static BOOST_CONSTEXPR_OR_CONST bool value = !!std::numeric_limits< T >::is_iec559;
};

#if defined(BOOST_HAS_FLOAT128)
// libstdc++ does not specialize numeric_limits for __float128
template< >
struct is_iec559< boost::float128_type >
{
    static BOOST_CONSTEXPR_OR_CONST bool value = true;
};
#endif // defined(BOOST_HAS_FLOAT128)

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_IEC559_HPP_INCLUDED_

/* is_iec559.hpp
utgCQk/FpQSeXLpHmyyAVEOcOQsQkreYyO/BxVczAVL1WlrnRZMFGbmb28k+TCDCTCLmsO4EHpyWumYbYV9iBKYIctn82GK7dL0bcjb21BIR7QRY9m3pZgtyDOynPYhkoDGn0TRbsuGQILFPHICRVVnAv8JoGUjvitCmL/XSKkcuJfkMzE6ChYdtCoyevIEYYnBzqTCSxOSad2lcU02cNsQVPxxHUXDtww9rsyyLX+7vL5fLVmTgakXJ1X69qlF9DVWkx0cJIiBNiyIlNWhBUHsKGZPkNs4ovMczf1IStUzI10MiyUow8SlahFcaUQ2W9XdeR+AtROx661EuDYRjf64xvVt4KWyvlv0+W0dY1Ub11xbHwdCdA1t1mxqqbPDVbZGyqowIngYH0HtChh6dEjL0cCSS+xDV84gPBqY+hUoSHyFVnULsnyUfZYzET5z4FDc1bxwi+RhpibOt4w0RBxInHR8XbqFb03aakyiRf1+3ptzHXrSIt0epnMNlFNd8IMk1+VSLEJQw6OokHazSTbSl+YkWvuZ8ledcDgWHypvvObg0E/+19RxwQx1BlzhW0ghekWycB0UIyGPgNwwE69Q+PRA8Egf+Pwz8+2Fg/M4eiVH/bPyhPbQEPg+G/ff2qXUqTj5h0lrT4LD/
*/