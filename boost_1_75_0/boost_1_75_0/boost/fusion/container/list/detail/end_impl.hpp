/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07172005_0828)
#define FUSION_END_IMPL_07172005_0828

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    struct cons_tag;

    template <typename Car, typename Cdr>
    struct cons;

    template <typename Cons>
    struct cons_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef cons_iterator<
                    typename mpl::if_<is_const<Sequence>, nil_ const, nil_>::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence&)
                {
                    return type();
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
PsMfHCQPzpAHR/mDzeQB+SajXMEfrCQPiC8hl/EH88kD8pVAuZg/eJk8KCYPCvmDoeQB+dadvJ4/6EkekI9My2v5g07kwVryYKXyAN3CaUVQy4QHy8QHBcKDAv7AnJASGz0tPMs/dsG0cDSePO6vyp8RYnf8OPlGEFmaEaZPCAB8Rn5LXaq5YUTAx2y63o8ht9iGvDsDyvB0Vx1eWouEjzeNxdN5TXdHa2CKbcUnQfClpvX4B8UWlu2RahWNMq5Gga3DdyuC0V2YIYOYToLB7cEn/FVxcFZ7Fl7Pk+LkGn1hGI6r3wnD3DYvDAM7YPHupUYtPfzcmQA0rH+F77Fn4bGoXjMRi/xOGLDLsjLFF+4Vi/cWknsE2PReDtyTfSY9QjoXrS804apR0Gnp+TLOT0QFNxJI5liaOVJfOJdmjrRoSOb1NHOk5X7SGgYT8g+7a1SWAHKrmuX572hfyjFtKzUKgfbBvMAqmFJLy9/aB37QZRxYlq398P9G/D8EbMh8XtXMjgtLgTlI9JeB/P3ez5DVzyQc7lrCm6tVcg3EvykxWWHJGlMhlhpWeQOJVtAYvRNWCGCBoAYFCI/Ju6uC9DGxIa+20EfEhiTKsWo8a5YAo3qlXGaQY1FM1LIMztlfgojHlcMXAYpxtkdQthgp5NXmERLCXqwae1CtoaxVgpKyd1maKfoxTd46RIk+JiPk1ab6iAylmey/cSVX
*/