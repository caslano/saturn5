/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_09242011_1744)
#define BOOST_FUSION_BEGIN_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/std_tuple/std_tuple_iterator.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef std_tuple_iterator<Sequence, 0> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
+ahD0a8C+8J6cABsDi+HHeFgeBkcCofDYTADXgmnwxFwLkyH18OxcCUcD++BE+BDcCJ8EmbCF2AWfAtOgh/CyfCfcAo8BrPhL3AqjCXv5sA6cDpsAmfAdjAX9oR5cDCcCcfAfJgNr4ZF8Bq4AF4Hn4aL4R54EwxE03+BF8O1sA+8Dw6CD8HR8BGYB/8C58PH4DL4BPwYboWfwR3wGHwJnoEvQzuG8TiMg6/CRPgGrAzfhY3g
*/