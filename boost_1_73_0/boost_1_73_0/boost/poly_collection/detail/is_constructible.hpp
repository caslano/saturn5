/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_CONSTRUCIBLE_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_CONSTRUCIBLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC_FULL_VER,<190023918)
/* https://connect.microsoft.com/VisualStudio/Feedback/Details/2118677,
 * fixed in VS2015U2 according to
 * https://blogs.msdn.microsoft.com/vcblog/2016/03/31/
 * visual-c-2015-update-2-bug-fixes/, via github.com/dodheim
 */

#include <boost/type_traits/is_constructible.hpp>

namespace boost{

namespace poly_collection{

namespace detail{

template<typename T,typename... Args>
struct is_constructible:std::integral_constant<
  bool,
  boost::is_constructible<T,Args...>::value
>{};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#else
#include <type_traits>

namespace boost{

namespace poly_collection{

namespace detail{

template<typename T,typename... Args>
using is_constructible=std::is_constructible<T,Args...>;

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif
#endif

/* is_constructible.hpp
lfTWL/m0LUHwA5/pHytnyW+9N0H4KRlypZ+ki9L0nU/SKerbVTGP+uiXVgKDcJ9z5iDwk1D/zBqoHzF9N/n1VFcfJfTNKvT/VOxX9CdufmmUg4Kvm3V18H/cTT34DkcNqhz1tRKtWlBr18afHNvlCfeDyE5s7lkIb7rkU0FjIlAzLgT3PwLRmBBZOs+v7dnSXLdkZ6m5nP9KG50Fs/PL+vJVXRVj377VZdvsc2WznY+jhQC5wjJaj1lnPZdqakP6ZTcJnDSJL4+eEsaO2hNKPfIZ6z/MqixMEFZJ+T6/4x2dNBpPZMmBYV/+KZ/CvWJ3nGZ6NVWiKTlT/t8MLCFiDCiyingXNKEq3+WTxr8BUEsDBAoAAAAIAC1nSlIgsygidhYAAFZnAAAhAAkAY3VybC1tYXN0ZXIvdGVzdHMvdW5pdC91bml0MTY1MS5jVVQFAAG2SCRgtV3/b9tGsv/df8W+FLhnt75apChSfG0fHkVJvaBFUtQuiuL1YMgSHfOqSIYotUmv/d+P3M9Q+1ktKdFOmqIMQ+3OzM73naVGV59+vD9n6lN18s+t/v+2/FP+rWd8t1n/K5tvm0ff3v6h8F856+fy71NIrpSZ8sfthTo95Q91rqfcCpYvq/vb21OIfq5oqy5X1cyfb6vb
*/