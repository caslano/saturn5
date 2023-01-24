/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_05042005_1037)
#define FUSION_DEREF_IMPL_05042005_1037

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef typename value_at_impl<vector_tag>::template apply<vector, index>::type element;

                typedef typename
                    mpl::if_<
                        is_const<vector>
                      , typename fusion::detail::cref_result<element>::type
                      , typename fusion::detail::ref_result<element>::type
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.vec.at_impl(index());
                }
            };
        };
    }
}}

#endif

/* deref_impl.hpp
7C7NG8J7e7TmRIIBmtHXeOO2KB6g+W3tr5e2oZ/xjR8Bo20iJ8zYTkbPjeMYWlYRGWEWvNDEBLFBKje9HgHK4wz8ccngCMybXVIotKxEpgvY8dumx/i3EdoIO79AI1zQxAirtRGuLmqcPgbk6q04nFp61GyNMuS6ac/GlWiMl05ZuCxzOmphRCkzFlO0AjCWEsinDHowY0U5vs0S4L7/YXhAPxc9bzWxWcljY4mHBFKglWZCCi09A1akyGJLNhQqba9oHW1InIwZE1jTdSh2P4C/VUe/562NktpiWmQ/QQhVjldZ3otniyvgwfIPcyG+QFlRUk8Jbqni/autmBLLZqZw9gUuShtPaZDZ2kiil26e3A6vJ7OeUEIss0iLbCg5kpfEpA48gdfGJKBUB+9okpuUYVFtCir5FNTwKajEnvZdzafA1HgKKpuYgnWRPM2eIV8AxZJ1iSmgiveuoilowL2JF8KiRVZmRM98MbDFUTSgevwSLbIzY/JP8NMS5W6LoinCGsp3e/rwrHrF2fKLBFH+lWcAhr9/E6X2PaojbxXsncN4m7MHgw9epDr6G95dCu82AaJFs7fB2SDYzMbbBb2eZhpmA1bSlf3powSs/ousUNgJg5MVrOJbMBVHqigsHgSD9I1Mg8uUqbxTrWJ6943+uN5wNpEMuh1U/sRz4Eb5TTZjXSU8lf0NU1eCqs8T3DEGWigt/gfV/UuZ
*/