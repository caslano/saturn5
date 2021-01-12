/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_09242011_1744)
#define BOOST_FUSION_IS_VIEW_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<std_tuple_tag>
        {
            template<typename T>
            struct apply : mpl::false_ {};
        };
    }
}}

#endif

/* is_view_impl.hpp
LqwHr4H14T2wEfwzvAg+C1vCQ3AhPAnbwrake0/YAQ6EA+EoOAmOgzPgeHgjzIAr4ST4BJwMn4FT4HaYDb+DOfAsnAFjvIQfJsEFsBZcCOvDAthM9S9RfSd+mnl0rz2/czV+uiNp2j4ejaE/D4/BCvAErARPwlrwNEyDv8Ju0NZ20wvHQR+cCPPhdBgLF8I4uBzGwz/DAHwEloPbYXltZyvA/TABfg4TobMuXBHWhZVhc1gF
*/