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
uPeQ0qy4GtLPBdUjl4NQQLgECQTyI1t+ZsWHPQxw9GcT+AmbekO41fAPjgL/TKJRQ7rrNZjrnwZyOZFD3REv3hn0j7FjSHYbqc6t+AE+6yRrfAMnVZlMHP85mc6N4jzu89t1oWqqpOZETGuamtIEYD1lxcazHIZp28GaFCdFXyN5z5qqEJgCjZoe39CVnx+HYOtwZ01OIgIVhm6OFgKpvWk2d/NvKBggX6OimouLxH99/lgCV1CzNsatfudh0Ej2Dmtkub7WULwY4Bg5EVAmv1aUrpSPAj+N1ixgo1KCje/yeGYBIbXpwsWRBIjKO6gbvYLlnb6358Z8TuZQHauiDyOB4cpIHgn5NIhTO8i1HXy7A/B3aLXIRVVLZVJ2EEylpymC0JG9YX/bUvHERQOMHGKspsqq7J5GVyYjQeARWz1fpeM840IntKBrNHaHMfupe/rhv2E8sUNKXSomGYdM8RCd/snazX0zv72RidLR1FjpIMnLTG2mDNaH+FwcgkJ2rNVBLm0z41uN1DVbm/pIczXzHxvINS+2m68vc1SlkVGgaROtnG8z2MS82ILBcpTpwdlvOuKV2Rw/NZtj7k31MTEmPkzisMlDz4pibfGIB/CFFFgiezQbQpJTVT312EVAuv2SvcGG22/ZBf77
*/