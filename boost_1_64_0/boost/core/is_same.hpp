#ifndef BOOST_CORE_IS_SAME_HPP_INCLUDED
#define BOOST_CORE_IS_SAME_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// is_same<T1,T2>::value is true when T1 == T2
//
// Copyright 2014 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/config.hpp>

namespace boost
{

namespace core
{

template< class T1, class T2 > struct is_same
{
    BOOST_STATIC_CONSTANT( bool, value = false );
};

template< class T > struct is_same< T, T >
{
    BOOST_STATIC_CONSTANT( bool, value = true );
};

} // namespace core

} // namespace boost

#endif // #ifndef BOOST_CORE_IS_SAME_HPP_INCLUDED

/* is_same.hpp
rjVIsp0yse+Zi7TaaWP9DX8ayrWRQ33epvXn40b2O2x/Hpuh23nzGHNtqcHgLi/laej6C6GnOXkxjcawd9G/R2gMu7+aA3hcu45pXYrW2LhGYWGk9faQOKe+fxmMOcUq2QzSj1iA5LnYHGBW3vU8vuh6zzXhd76ocM53sG5k+2Le+tZ9qo56ZhTG7oNiHT8a61snwnogXduSHfc+jhhZlOpQda8VVRnJvMsVqR0eKa45Pun2XxyE7DeHUnnIa16nn1yXTbpHN7qq5j06ypzv0dV1hq/zouIGeeVdHUD9KAFfSVYJk3GnkbpN5seD/CbEOf0zWp87+7ZnD27NdmXAjiFGne6nSRlvjsvIc1ARPqsHdiV8x8eMCZ+n9NFksRx304bajAwwqNeMaO9f0PVid6AdH6/QdHXzaJbMB+ZYCYvjsel1LfBg4kTus7nd4sdHZIplSHNMY+btxmkuncg05gANJ7DG2l16Szjn6Mcbf9UQb/L+qqbp57X87ibBvqYxtXrhe/J2XfZNwFSRE/q3gV6+dMLYzxeYHryMA7v8juEhZeojSIN912D88SJI9z2zDrUyzT0iwvSZDuZNPRrS/xh5FAbt+FOes/x6/hzoWM9bmL5QPX9lebCe2B74PUaD/ZoxSQe/NViY3+81Vi1ELNS1U8I4imlD863KRhrnny32zdt0PioRbSPsmvCPQPff/vzJYhysr1yO1QXj9J8tD9xKtTL+4uLYWQ3PXz0e7Ovm3ZPHwx3blOPvPs56bpXTuwtWjAuVwgfztCiv6H378w7A8Rtv/wJ6lKLT/7g8Hb5OF61FXNbpCciTotMTkUfQ6cmIo07F9Ok6PQX5RJ3K8qg4Zg9+T8KetUTH//lJQ/2knLLffr04N59K+eSjUVoXmmKateQSVb7hHqc9lzI/Lx50lSgl9qPTU3gy0D/PYNnmfhd8A1ZtyqhAOuoQ9N1bEaNNJqa7BTA/tuJdl1mM93q2zT1MLbww7SLAOXy5HecgTw57bmzgCogt5++IIX+UAbqE9/F2Hsq0d23Jqgs7qVimS8I62jNd2Y7udnPPbyXpvnCkHG9+dWcZy1bJoRlNubHNzuQ2ovFTTVINrBGk+6TXi+ve1Wt9Xwy9K2/I3ivjuc0dHeGbpA9DfrpPnU153ch+rZ8z7QFMWw+0BzHtbEWrtyzRqPphb5dflo+Lfe/BlA/5migZ7OtxH02AWjwh/SHcJv6+eob5XQcS+GYY902xxc0vdM5g/A3mQecM2mo3v9Wi8vFIZ8t3DNMKa/kRfocBaQ0WYVpWFfpxCLOOHBivt5Guhnb2Dp+XHR7YQd8rogAC2/dAGF7095AMdPiATwcwLrYpF2DgR8T2MI4Z9MswPfAtTQLm+48ii3FWrFtoO8epwjjaDOKo32cm6YsTLNvaW/9a06ZKi6YeA0RnWqxRbMudgPl3dHet0P4luGyan2X9oI+HyhPMDU8ATG0WhX5h6Gizpal81m/f1aHNDmkfG31oA+0W0qMNEI52i+nr99vzmMGeJG++vsUdL9EnhHmBzwjx2DfHMPigTLsUwVZ3QXvhXfJBoKu1G+p7iDHVjEjfS3SlD05n8h4m+l66zkWCnL3uumSOKWlRCX0/0/l+uKlfm+FnCOz4Io3B4UGgF8eXZn1mPDaO1XnWxe3Gniev3f4q+lwOcrkFp5KZl7cAT+h4aqxs8pvwO1bVfBNOBUicT3X74ThPKreQ578hTzFuKi1bGqubfO626Eypv2wGncJaHXFcq/I6rrHyyPE2T4TyQHw0Lg86QBLsUYyBA8RgY4hxHRIsjxg5B3AtXmAsdIRw/wcedmTZuYrp4CAx2ITFWB6cgzMGDpKa/pE=
*/