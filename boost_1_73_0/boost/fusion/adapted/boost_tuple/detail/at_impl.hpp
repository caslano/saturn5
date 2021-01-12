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
0OmHST0hvn2WP6uohD1qaka+6SisXuDZriXfVRHOnuK+fSi6Z0wHMR8Zaupr6dWu43rxe73IJUx9oO1J4p+pD8wW8x12K3qKe9LfNcNuKNeewrUHiV/NQ3WN1/aR83uC23iWfmVPCET7YO4bi56Jlb2tgHlGt46p6a0YbaWZ78HvHufo5rPPUUCuWc41x4qfaaFsE37nm92VchPuuuqfxb8jnX4is7dkN3F7RGicvc7O8T9r
*/