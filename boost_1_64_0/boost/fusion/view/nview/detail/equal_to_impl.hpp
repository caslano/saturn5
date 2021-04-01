/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_ITERATOR_SEP_24_2009_0329PM)
#define BOOST_FUSION_NVIEW_ITERATOR_SEP_24_2009_0329PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion 
{
    struct nview_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<nview_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
              : result_of::equal_to<typename It1::first_type, typename It2::first_type>
            {};
        };
    }
}}

#endif

/* equal_to_impl.hpp
2y0ymH35wbKnfM/kbx5hdekx9CFJ8/iXvywl+z5zSSXzDV/gbTbKVTiLzZkbV9iErH3A/stTdi9h7ZGRR4RZ2m/Zsb4jMTc8k17Vq5h7y2D9VpAqk+FxqUjvgLcuKYUmKA7BbkcAZNYirmi43MkPLiWtH+iSK7kKEETFuTmO8gYBkyzv9DWh9MOGothJBVbFMksB1dRPvupBrWgreX/uT9pc4AlLjZNiTyJnHg1bLgVm27GGgx7ADIkNlTITmCT81aAX5SexH+e6KTvk8niV6kGK5n4+r22aNIW4rEVm0Q679etPm6cyR0mv44Vcb3gKXiJOIUUqXvJDtlEsetkQiUyZdhRrelkUB08IloVubcqgKZsPiU6yvKLLeJLwOHaaSOYd6ngUO5sW5ohhmfywqstd9gWdlfNiukbJSpB0xgblZ+miabW3rtl3kZqIMnOB2kXEAo6keS8zNRyugOPNzaBy/zZz3f+CkZv1S0AC08u+9gb9vsQPQCs2jGUzFwKNkimtT7mW1POHj5qIZA3c3ZXsbsJuywH1eQSmtnCFcxlOkbLzM2irusiHMA==
*/