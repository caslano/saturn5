/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_END_IMPL_05052005_0332)
#define BOOST_FUSION_SINGLE_VIEW_END_IMPL_05052005_0332

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    struct single_view_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<single_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef single_view_iterator<Sequence, mpl::int_<1> > type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
JrZKd2jQfaNWdH8/3qT/cpfnDh7q8YmWqJRJaJItxf5u0Sg7SPS+K87HH10v8o3yxhtlrMegM8Kn7CabNUvzg/9r5DP06TNPfE6bLFqb9mHQiXX+FDt0C2dFQYZ08raraA5rfcrXpPMLorbQ/SVTfo+/uvfvn8rv0klMdFIofzDLF6V+bnyxva8+7R15+kEaZnqNfOWz5SulcYl2vAtbTMefrP84f9QSl7Qb1FC3tGdPy1c9W75FZwX/mAp5G53OX6cYDJmMOW7C/dnu7nnd+2ufLd+UPnmPVXECWDDjn4md8A9mxUe1vH5wB8QWuX9A5Eit9OQXOPXf98ovsEiDL9JSdAOP+tN6ZP2INIkQq2TfjS/K6+dEimvQUUJ+cpVvds1Plod++W75ySXo8cTvAD/ZHfFWrfhtDGPK96BzulDEMgQdpnk+Ar+wltUdwih0+knQz6uyb0YSUlehF7TP/FMqQIvyP/2hQewfkKmkj2II48fnmORR06dXXOSjdjOEES5dnL2veX63eYP3R1UfRCe5+v3IjdBPPB36Gf+qDrg3iDLhuKhfI9/4bPnopoCNwliX/chfbWH8UBWTfDhu8px2l56RvH45p89e5R32soid1uuVlRxjk3cD68cgL5fYv7zYX9Aus3wSEEdrGJ/jrqNZOtG9cvSej4r350y+RU9THE/5HH4VuitAK4EaB4ffyv9rD/1MJDdHEUYY
*/