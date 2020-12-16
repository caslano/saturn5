//  (C) Copyright John Maddock 2018.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_IS_CONST_ITERABLE_HPP
#define BOOST_MATH_TOOLS_IS_CONST_ITERABLE_HPP

#include <boost/config.hpp>
#include <boost/math/tools/cxx03_warn.hpp>

#if !defined(BOOST_NO_CXX14_VARIABLE_TEMPLATES) && !defined(BOOST_NO_CXX11_DECLTYPE) && !defined(BOOST_NO_CXX11_SFINAE_EXPR)

#define BOOST_MATH_HAS_IS_CONST_ITERABLE

#include <boost/type_traits/is_detected.hpp>
#include <utility>

namespace boost {
   namespace math {
      namespace tools {
         namespace detail {

            template<class T>
            using begin_t = decltype(std::declval<const T&>().begin());
            template<class T>
            using end_t = decltype(std::declval<const T&>().end());
            template<class T>
            using const_iterator_t = typename T::const_iterator;

            template <class T>
            struct is_const_iterable
               : public boost::integral_constant<bool,
               boost::is_detected<begin_t, T>::value
               && boost::is_detected<end_t, T>::value
               && boost::is_detected<const_iterator_t, T>::value
               > {};

} } } }

#endif

#endif // BOOST_MATH_TOOLS_IS_CONST_ITERABLE_HPP

/* is_const_iterable.hpp
3T17f+KMn57D+fbbczbe3bPn/HC4Y/OBJ451PWXb3Txd7vrbXl0fAVailLQO0duGPdxsruY+O84PXxnaWDOsAqMQP21bUznLXrXx94a6O2csVTw0fInH8YaDbPKFG9WcWwO35AYrIhr04mzv+Hxvfxprt2FbP/FHsK1zUxnGfOpsNl0whBZy6VJdFwFWohKfPASqGvbsIGf2LY4RMxzajAG8QMpFiqnpKp69aba8qarvsQCeo6CdN6IzWc0tnWIachp/YMDa4h7Ag+zsfTCAq96fGOpNfGRYh85mR2d7GfXmw4vjvByscvB+vscnJD1LxrLY4PlLZd7BwbvLH8FxoaWOxEDYG9zw3THWNXJsTNANtXnm2LYdsK4/hXVNVEdtA23wthCBsXjpx9C+5WWWz4p2wHmT0tAL9pkD1lhnnNaqYXNdzz6YcsdcPuiar8qPh7EgHQ1WNuOWicMdHr/nDXvHt0/W31kO4CXiXJtcbbLCg8Zt69/djIcxgqRiJtZOWTcapYHxFO1urw2N1j8/DsphSEuHGRVuPtnP1ciR8ct77XbmsVfzwg9YgpnxOol6cl/mkoP4LnJ4dnF3wH55sH3QQjCSTMOeHu3tNzDI19JjI5pePCfBGvQOuKu8XNdYwOlRSfItAyYNOEX4OPtgvgHMgQY/lOeDu4encO/yyJ/APTYxPmhJzZYy8u44z8XN6LWMlw9lRMEZzlNSvZloe59x31L7nwJlyLLfKAdouitjSnaj59VgnBNvA7xGmilhiFUNv383H2Xkfg9LuLLsv3p8QComKqNMDX4nHxWcQswneoxHgkRstDYNk49Bxrn/M6CeCpU+7ojS9aZlOmB/Pb35wRxkKV9Cvu9VkPPLPd4hylRyPvHlMiX/qBuhi6V/faPHJCQCTUma2DDJ6u497G6NGwbqyhAr102JKgCE30yXF84/AixGiZCsqOIoOwrWk8M6C7W16bE/Hb43S8K8KC3CbM60sHMTQlsMhBf22FcbSo2xgmfk28sRAjz7fsUga73xiaKS/b8/Qzhd9LkO6kWRFVh4IQSa4sMUH3hoiEWfBHAcxcB54tEhUnBjOpLhPr3H7kQTyw5aoX5PkJZ+cdrLOhRoYNwIN6dN6SGXjquvEig/RB4i8RzREpdzXEM/1st65KizBjs+l1+Wz50FdLzo/qlBd0ES00pbNEUrnZIftFwew5zyBYC1yFjrguMa4Yodjbe60/w2aGNPbf6lTA6fRkvUJjgHf6+XjUiJiJ2hstov6ziD4NnpTyFOaM5SOaKY3THpFGd12EP9dbCLwSJhYshMNn+ZZcYGbvExfgbGsiuh3ZyiaE6Y6dob7tYHX/6z4Ruca4vZzHZzAmY2AK18DPJxyYMmgaJ8/FkWpdstSELbS7xl4POJM2dZRs+gpeUmcNvnvWz59nzPg7p+qUqoRYu6KGnVv2K/k7vmQu7wZorkWF2JL8XqC9jXaTfLJqydR1P4uTecnNQ94yL/kV7eIR1IihLdKuK5xy2ANj4+0csHZBQOREmKsjvG8Ml3aa/G0YC2DV5jS4lEOYTSK/eW6Eezeczi+9FjKM4dLmpieMyBKPNHQ26/nG5r7gslg8zujZ2xpJYn43t9WVd98J47w1F8g4S+Ot+HcpgpXfx/Ts7uQLkfADma10OblEAsMij3Qyino5hyPdw+Gdr3p73ctbwS4MCwRxqH6v+6s8j+FsgS7C0j5aRg73ivylZ/cNAXuHNBsOSbBWfA++odwM+BfCwJ6zxiUDzLL3V5ai9/LeX11mAq0L0795Zu1u5RntvLOsQDNjowgnyu+J3pngeO/1f08gFFk21XnKvz3X+Ol1rk9+YDsXYe9lqIEZY=
*/