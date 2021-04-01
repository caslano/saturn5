/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_09242011_1744)
#define BOOST_FUSION_SIZE_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <tuple>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template <>
        struct size_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply :
                mpl::int_<std::tuple_size<
                    typename remove_const<Sequence>::type>::value
                >
            {};
        };
    }
}}

#endif

/* size_impl.hpp
xIpnvBlXtcfH5QA1cINHT9SR9AGE0oya8BWN4cxiU19XjSl8skjPwxILLStIq7UHGGvGTfuTPkQOH/vETNBj+gyuB6TY8mwBP+13ftPI3xI++dG+oMniLVD5ld0I3F4XRAKxVA6/Xsb90lFItaio0xnam/4CNMYcWjc09mhWTkQTQUVWIrgm1w7IBLJwp0chys7iwXofalMgpq1AA7GCXZLIGP+FC0jlGryMWJa+QYbaGSWi1ITXHRjv725KtbLeGyksBNTMHnlsL59QCvKo/D8Nx8PU7G2FQa+X8tWFeD8CfGRqGkpFYU0e576Qg90ECFanJY4UddIEpxebAR7nM9YxuY8Ro++5JqMwiapPgSO0AgoSnXMUOs9zscpy8eFKdMdZz585NHNGyPr6lBYkT6fm6kWZ/uW75GH9LKpgiP7yM6x/G9l5HX3Am/o6TO5A0nLMH+TKf90G+++6EgWvp7VRiuSQkMJL2uymGdm+hExYe12HIdjhmkmIQtmoZS3bWf6ztl/jD9obl2ovrX8FsfnK9Ey6xNUXu3SryGvGPDPRJ/SGHkZeXPRtBg==
*/