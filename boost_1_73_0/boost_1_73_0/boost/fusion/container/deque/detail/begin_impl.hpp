/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_BEGIN_IMPL_09122006_2034)
#define BOOST_FUSION_DEQUE_BEGIN_IMPL_09122006_2034

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque_iterator.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template<>
        struct begin_impl<deque_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef
                    deque_iterator<Sequence, (Sequence::next_down::value + 1)>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
1/J94ZDNgKuDcvn/9tZsVcNEBlwdlcu1IsJEBlyPKNcVbjUNExlwdVIu1+oZJjLg6qxcF7g1MkxkwNVFuVxrRpjIgKurcl3k1vIwkQFXrnK51p4wkQHXo8p1iVvnwkQGXN2Uy7UCw0UGXN2V6xy36oSLDLh6KJdrpYSLDLgeU66z3GofLjLg6qlcrjU0XGTA1Uu5rnHrjXCRAVdv5XKt98JFBlyPK9ctbq0JFxlw9VEu19obLjLgekK5rnLrp3A=
*/