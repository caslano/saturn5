/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_TUPLE_TIE_14122014_0115
#define FUSION_TUPLE_TIE_14122014_0115

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/tuple/tuple_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
# include <boost/fusion/tuple/detail/tuple_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/tuple/tuple.hpp>

namespace boost { namespace fusion
{
    template <typename ...T>
    BOOST_FUSION_GPU_ENABLED
    inline tuple<T&...>
    tie(T&... arg)
    {
        return tuple<T&...>(arg...);
    }
}}

#endif
#endif


/* tuple_tie.hpp
wsu7dqd7NOi1u38A/91tnx2/VxtjnSBeEwJthtOmaBFKYs1fwKt0EthKEFv7youzVgFnIz+8ZUpu9pVuRuOG3ZAxNFA+ohgcFk6jAjXkpKmW0ek200nqqJA6rqI04UWSiW5lEJDezJXZC8bzlt4Aiegc3W0IX+UTC6PncTLEGIogTSY3HBsHDNwkBFKNCvb+4Zm9pYheyAYxnQPqAh6ZIQitjrQj/eOeiW0pXY+jVHTpQa93vI3vooE7vwo/4fBmSzGCJJya6+EhY2NVcTRdHuNjGHTBoi6wG/blm7NfhhfaYhevPCQU8QKNLCCPnnatzXuHIg3sxieU0q6jDcC989kkDYX5zGfRMB7HKI4DEqB9Q9PDZVToUEV1VYkUz7I4zZQFBoSWeTiR/rYcBQxKyr2oOKdHPWgp+yByJE57Czbe+Jzpw5aRe6eD3snRq/PXOohGqziU4ocfoMbw+iol7VgQF64aKBldzMfQZWOxcc5Rwcxnxv2aJ725y3+I/6s+xW8lsQ4NXqP0OsEN2PeVU+UxvE7rVUklGEAHP+KTGA70NDd3mxp2So1ms60Z6pmTywHyNIq+EOX+MkMSKVhJczxM9CmcgmcswHbG+1eFV3+0aQPFu2r5T6B84zOya/mccR/qcmHl0yncYIJs
*/