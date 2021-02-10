/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_IMPL_07172005_0952)
#define FUSION_VALUE_AT_IMPL_07172005_0952

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct cons_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<cons_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename
                    mpl::eval_if<
                        mpl::bool_<N::value == 0>
                      , mpl::identity<typename Sequence::car_type>
                      , apply<typename Sequence::cdr_type, mpl::int_<N::value-1> >
                    >::type
                type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
9wsg+L91ylQRU1hQW3fobfVsmTQcHDMMyb1xJeqvsbK4Ud8ntamp+puSIoUVfrHSEUZ5rQMm3yg5UptCMNpN04jrZBjfHOf9wjy1VviXQ04V4phop7oWnEKInW8YbZYsFrY0LtKyRfsxUJNqI9zg1T49oBlKRrbeqX5UHFlTP9I1EWl0d+i4EnJBgq53nrC7JZVFZJ2no+oURc9x3K2vS1SI2QZvWUVobub+bWYBtK7H7jjVRohdmkw7calvBb+Rh4uWVEKO4RGBFCVVEVu58Q05blWWxus4dLYn69PGX2swrna10p5o42srm3nchzhUrvJVhGKw6y3VTekTdpRJGC1m1faUwRh0Nof6FIJjrAjwkBAozuEbFYEIidfIZyww18PI2V1A2zwFxk05iO5d4CyEnBo6zVWK0krbyodldHSi2IHl7+kCjz0h+Lq6SvnVePTD1xyx1LWG/BgTJCPBCb8o+8GPhx9mmNzhTWxaUutHgQ4YvEcf9uQuSlJU6bnvnI6uL86GU0elM5IWOy3IfW7N5Niw29yfR5NpDh+0bdLr753SRcAwSo1L/FPyFv7faxfXy73NJloXzzB1YVIJ3ijRSx6m8cNLpg4aqRhqkmVQQpI6oIscz33btZrtVCaJRUTlZX+1d2VFRwU+
*/