/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_END_IMPL_02042013_0857)
#define BOOST_FUSION_MAP_END_IMPL_02042013_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map_iterator.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template<typename T>
        struct end_impl;

        template<>
        struct end_impl<map_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef map_iterator<Sequence, Sequence::size::value> type;

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

/* end_impl.hpp
ZlNuUsVtsS/V+qvdwxeMfSaZZ2Jz8TfLJ3YTLnywZ47I+UvkXONvhYSzcQ/KvcyRNMVjz5LzqymzA8TNNnGXkZoePvHndmMuyMGeT6+Ln46U4Rbm+dRS3Lr4tuP6nrNW3G7ofj6Zd/ly8dfIlJsVYn/dZvyPtWBfmzHArpL+VP0+iubvYM+zfS4/sfW5qV4rR87/aE/lWtOsmyipTep8rj0haTihzuearoc315YxJspVQNuD
*/