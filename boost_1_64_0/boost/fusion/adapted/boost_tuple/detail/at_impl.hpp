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
Qw5KITAMiOn7jNnkNQmQuQkGs4g08gr6NwDqmL6lb5MYf8cqyYyrGOSDsei68jz42I97L0usCKkvk0IfeDqgCkCXdTgH7mVBFodAQ5Alo5bI+w1vTpG2BkgN7NbTv2dfijBDafSubaANyUQQIglGi7LwttWg2lhlOL41uhf5x9N6TPbUOAW12fa0p1J+Jx2ahzqyBGi3T/dVMy5DXcm2ySkbuDhHG66BW/efAnpnqTNYHVsfWy7kdhD3pqhVCVcmhrKrtE5PNjLroD5+OHA9c9D6fCz5Sl0p9BLtAmP8sI+Y32TlSI7FOHykcj0RLcb27gZKrwfM+B0kTWaCDEyXUQ50w/4z+BTRk99jjraYAXGHM/bv7vKMZqVSTi5Ieqzt6vEotHpu3sUFkjjxjKT0nlo17NXIdlBjiNFRfms2Ke2sf+Gb7Gx6awnUYdH+Qnwnl7HX92IEQQJbOM2jcQiYn/alYW42tKI3DH/JHTGdYjT4FkfBTYXGtcmhWiv1nSTQrEcxbBIesV8xdHDSkLJ2eH9Dhor00i4YtgVrWxm/UfCy9CLMlav1bfHjQw==
*/