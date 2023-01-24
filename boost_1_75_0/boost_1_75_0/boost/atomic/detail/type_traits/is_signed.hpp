/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_signed.hpp
 *
 * This header defines \c is_signed type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_SIGNED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_SIGNED_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
// Some versions of libstdc++ don't consider __int128 an integral type. Use Boost.TypeTraits because of that.
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
#include <type_traits>
#else
#include <boost/type_traits/is_signed.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
using std::is_signed;
#else
using boost::is_signed;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_SIGNED_HPP_INCLUDED_

/* is_signed.hpp
3rAyrBcTib8OJWGuI1diNj7o6VwlD310GmB3k9igrDetJuEoGBX9K6urbGkE6OGwjytXmY9/Z7VvxB/+xuqMf2V1l150+Ax5q/uAWRJHbrMmwyRACKR5OYMPD2BUnpFXVT0+MRVO9bt5FCLSDTr+jAM0RMbUCeZP2pW3gs/Qg5Pncntlik9RaFm8vp2LaN7hwBi8ytQZ50ykG9V9sOkLTokIcbzIPTvU7/CHvrab+b5nhe9FtINa38zl9hdJryl3smgfm96cf6mEBm2xbXLVzXSu7srCiwBWLyIshSejgN/mutBhHJ5i9V9JBTt+xwQDHLGON109v8qoa+UGT9R2fwgY1rwPNCuoEuE7bLaEsBU1iWf83BIDoauCqRLkQEMTieVi1DqvvjnbPax+J4VY6cY3BcNvxHyQ0rS0Z5OYRjfUn395/NCB/lG3S2hRtOZ66na8kcNR6rlpw+1evDOWJbhskw8WhFGA1Qh1VzWw7QHeivFIF5Y7gN39gfy81rejfR0O9Bjxmc8ZBwrNBjw9r9cKB82fWwQF38GiW/SI5H4UnFmSpmAUwCJGw/c9w/VZKuVqFkNJG15BnM1zefKGPfahQQUc72t9wlZ5yyDIvnDCrxqpf+LsroLiCqwADBcvIZAQLHiCO8HdLUjw4O5OcPfg7hZcluDuriE4Cyy+aHBfbGF3m3o705l2+nrnzn3/5pz7H1Bd8WGW7b7F
*/