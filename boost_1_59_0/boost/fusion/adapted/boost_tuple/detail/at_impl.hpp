/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_09262006_1920)
#define BOOST_FUSION_AT_IMPL_09262006_1920

#include <boost/fusion/support/config.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template <>
        struct at_impl<boost_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply 
            {
                typedef typename
                    tuples::element<N::value, Sequence>::type 
                element;
    
                typedef typename 
                    mpl::if_<
                        is_const<Sequence>
                      , typename tuples::access_traits<element>::const_type
                      , typename tuples::access_traits<element>::non_const_type
                    >::type 
                type;
    
                BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return tuples::get<N::value>(seq);
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
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
*/