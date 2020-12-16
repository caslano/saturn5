/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_REP_TYPE_OF_HPP_JOFA_110329
#define BOOST_ICL_TYPE_TRAITS_REP_TYPE_OF_HPP_JOFA_110329

#include <boost/config.hpp> // For macro BOOST_STATIC_CONSTANT
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/icl/type_traits/no_type.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(rep)
    }

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_rep_type
      : mpl::bool_<detail::has_rep<Type>::value>
    {};

    template <class Rep, class Type>
    struct represents // Rep represents Type;  Type is_wrapper_of Rep
      : mpl::bool_<detail::has_rep<Type>::value>
    {
        typedef represents type;
        BOOST_STATIC_CONSTANT(bool,
            value = (mpl::and_< has_rep_type<Type>
                              , boost::is_same<typename Type::rep, Rep> >::value)
            );
    };

    //--------------------------------------------------------------------------
    template <class Type, bool has_rep>
    struct get_rep_type;

    template <class Type>
    struct get_rep_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_rep_type<Type, true>
    {
        typedef typename Type::rep type;
    };

    //--------------------------------------------------------------------------
    template<class Type>
    struct rep_type_of
    {
        typedef typename
            get_rep_type<Type, has_rep_type<Type>::value>::type type;
    };

}} // namespace boost icl

#endif

/* rep_type_of.hpp
JQ7NC48yTVm1Cgif9S+jcIl81ovPpZf7qvW1czL1RC9R+oqSn20Xqudl8AAnn41xXKis18Itrxt/Areqi9B0TqJdO8eMw6vE0WFOXH5V8sBlJuq9IG/K1CJjdVX3U0JVYdSEWRHS2VijdKWwtAqsC1HlCA7mXyJD/XvWzRub3wU/vGflCXl8v3OO1PZ5nUjguBwCcMvlYJtbdzmI48C8thnLjdCF8xczLgen78Uum7n+XHujscCIz8EROqQYsyi+GMohYmyIfA3XaqeF3P+fdfT2NvqAKFelTFdC939wmrVM1wpcTP93rrVMu1xUd5nmx+aGRfmugqy8dIFXbb2yaVdemP68seCTU+vOS/gj7C9/UHc/1v3i2mOREQIXm/9dpMz/QJfHIuVwZ0wzxyL7RF5Nev36AWMhydAkEWwgn3NRCcxTOc78fCzF2eLg3A3hlQpPWFPseENNjNeK6h9PJCjFgrAjMIXSwOF0qH0U46gu3ZKuGu81K2d52Uk0to/FtJgz1xfVSjxhn0PxFNRkX7x3bbXlolX4K3yEMem+IOWJB4DsR2DJrRqEwcpbbA/dGaxx5Es2ejzBGpth99cXCIt0hEq0sOkUdye76Q5oa9qilDRCi9ipit1C93Ky2HclrxeJMwrd8IPMRJ9KYylqHzTGO5ZxWRg5sI5NCzj8iNptzYe19NVN2h2Vx+v3ba2WzusybpdH28do0c4+unn8dHRfULs/TAJO7lOj85UzC6Db4pwLk/dRR8PPTGnPeYMSR/qC+rV9ei4IGaZAeW3ePQVWacWCgd+rGW69/cSxiT7F0MKh5dhpiAcULQkrsSQsG1j+1UGfVX/gsBgYr25Tdx0nt25n34dfXWuJQxeK8hcy8julXECPGzfMjxSNdTkLJxa44OI7j4vYcl4cXFFVaoPyGw1o0HtoOJ9WRgMimDhb5bOJNllDEKs2pZ6ARshc+uVhXzLYt68uE1L9Rer6j66yL2ze+IpIQ6lIv7k1aGyL1qEXKVSxLvCZfo6ssWXRtS0SCszslo2rekOw/CuUoIUbI1W2uMxufSJQSu4y8qoV0X0SRaQ2YoYE76ZqRbommit3Yg5yXehKt+KznIMwKhJ9mMBLmmsGrqoo/pxb3sunT0v2k7C1X4RtenPsKtHN+3tppE5FX8kJjqB+6PwgwrCb/Bi8hnclzQpepFnG5aUVugqLYt6ZRpKO1zw1H5nJBvfqm0BFoviEDKADHfAINdUSFSd/rxatkm3VMb4MX1HjAU7xW4W0Kfq1Ai/yMyaLc8P4OuuG6eoZAsbH079jGu1o8Xu8fQSmKWulcfHgVsYjt+HYu3qeCjjRDEg53Ywr3hyaafHG9kxTx2OMF2M6+kgMp8o6CBn9enOcLY+ZKZPP3U/ST/qkUKNUcMzOjKPiY7vFKq6Ij4GqNESr4ri9M46Yx2xTCp4vMlfxlDbjHncrLUzDRCwJsVjnc/QF+XluF6VUxbHVZbKf7A87PLzkzjjZ5nZxkIyGphYL40qMi4Yc0CpPcZCsLfNFBFE8QgAKpLlHaxpfRgLYb2U4YOw6Uy/uiBke08M6UGoYhJKiuE620hCVTqlVx2xsU6VA/8e4ucHjEGVvGmNmrxQIydWsOEt2FP+QoGzQSsZTHvXkqYbm1PBUrdbI/QFsrpOxxYpwVDXdR4b+IthwYYt9whCcI+opU+0CoobYJLOME2cKJJy4bt/BjCfT+OsyVaYL5W66G9+KDwu2UvxX0GnHcMDniHiDKo0rg92kEsVIFW8Um4pnTS7GMS9LBjiVuEJiwiLhRMnWHUZfjxG+uJrVcmF7ozJO85T6JTczoexHsuvH89raNrSDPvCwrFzn8AStuTc=
*/