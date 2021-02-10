/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/integral_constant.hpp
 *
 * This header defines \c integral_constant wrapper
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <boost/type_traits/integral_constant.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
using std::integral_constant;
using std::true_type;
using std::false_type;
#else
using boost::integral_constant;
using boost::true_type;
using boost::false_type;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP_INCLUDED_

/* integral_constant.hpp
d0kUCw3eJ656rVahUVMIRfKPYBrWO7ZViRZsWcrQ2WTopZdr5df7NOxf5FqsFz5cjoIheIVG89du60sLQAldKglLQ+Xs8X6NqGR7ra8v6KcoWPXhiqv/o56YmmlPpFGdqyxWoiis+oNQLbjyW99LpCgrFykerA942FGqM81TOrAGmKjCyGzbEFFa/kYWlcRLYUEdkCt0dOm0TyIsMXw4JzGcnLj3su2TGWh95L3vdk+7He32jC1x9MhsYhZMSC2Ug3EDytfnYBVCsw1PS+FczT+zm+nkajqczRyMmXtE+B+6VPCNsHTVgXUPj8TmHh6KlX/ORXvGF7fTADxKa8xhAFNKH8zABC92LJGJtuTJ0qFlF76YeMU2q6w80vXMapjJQoPdWiapkHwtcL+tRaFPCd62cjbZslKTEAoss1xIp0b40N4u2q6xCA6MwQhluTZm+Mbyyc2c4eADGdZrIn03Hc2Hg/6870Ol/Qdwl7fji/loMvaP67sZw3TYHxwR7Au0GX48qVPCh27QDFMjjvQeVeeP8djAYcP79mxyobBpr22OVLvLMM0K4RwHGguIp1u+KyDE1JVlXlfrM1e1UXMBfG09Z/f4NghMgptmwxPp0ISrOPSrxPPwZWPT+6D33OHdkm198C6VSTE7nvWs
*/