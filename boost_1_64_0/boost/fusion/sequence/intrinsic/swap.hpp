/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SWAP_20070501_1956)
#define BOOST_FUSION_SWAP_20070501_1956

#include <boost/fusion/support/config.hpp>
#include <algorithm>

#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/view/zip_view.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/sequence/intrinsic/front.hpp>
#include <boost/fusion/sequence/intrinsic/back.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace fusion {

    namespace result_of
    {
        template<typename Seq1, typename Seq2>
        struct swap
            : enable_if<mpl::and_<
                  traits::is_sequence<Seq1>,
                  traits::is_sequence<Seq2>
              > > {};
    }

    namespace detail
    {
        struct swap
        {
            template<typename Elem>
            struct result
            {
                typedef void type;
            };

            template<typename Elem>
            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            void operator()(Elem const& e) const
            {
                using std::swap;
                swap(front(e), back(e));
            }
        };
    }

    template<typename Seq1, typename Seq2>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::swap<Seq1, Seq2>::type
    swap(Seq1& lhs, Seq2& rhs)
    {
        typedef vector<Seq1&, Seq2&> references;
        for_each(zip_view<references>(references(lhs, rhs)), detail::swap());
    }
}}

#endif

/* swap.hpp
lgxiVIWH+w9p3JiAc0o8WF5oglft367/JX6nWuaQksmJzJyFSVmkhd8h9Jg6hAqpsgQqE2PJfK0VU8R3SjerHHhD+mdaxkRr9glQSC3Jw1zVRI7HvDANwwJevHnDfl2JLV2hfve7oo7nwsqQeZ5P3NzPvDhjjYSydwr23ad7gpnehYx/3ajH/Qs3cPOgiJkowQsPHOzLygiWvYrn0a8wyjrEq9Cpqqpp1f0H62rOq/rtRR3l1+n7pnGWZjm3203G7bjOEIP6qJaM3IHJxw9LS8ZDxLUmhKkzvh/GaSAyUlYFeRo5hRRh/ynFRVrjFSw6Cra76mOLRF7GAhh2cVlk0IL/VmTtjAz/0jKNWEtfbd1L8zyN88K3+1izY5KNhWMK54Sv0ji1RRwmSRnGA+VMcXnZlIl7o2T15NqR65iOR3KxPZ7CsgqCxGOyrxBuB69j8BXRx47I4Swqy6qI80zJOWZchYljI62X7vsY/+vrNG5tUHqJFxeRHOeyR8EgX4JoH/Bevq5Sz1Xjh8iIWZ5nLvezVMrAFuoSgrqUVv/085i7bpFLoxsjrBraLVyn2uQK4S1YHqYRTOD/5luJCCZSN6I7EVN5/Pc9whijkzC3ZHmUhnKMHq/ROE+Of6MVOxPgRZhWHX2Ym1estAZ0XvFXzDkiD1KPF3lhzhHYBhxjJn2DjqXYF8qoIGX47spDtrN7zWFcUSInZHES5FWYOnXp8JP1Z2Tozqlj/V5frEdIkZW6DsdiS1YYJm6RZqWWJQI6UXmTuo86qk7niJyIlb4XVFmkxRwVMUGvrU4XW7J4GFe5W3i0TlKgXSkHbdu+QW2MeMXzLNZSHOFSqdbcPvIfwthcJn/BYD7PChg0WkAzjSwY/dPBuEEm76Gy8mIeZ80b9M1OCtAp0y92d7O3n9vankU/TkUHgYq+Nt9fX1poIHgfc3hU0ZEXae9HGhokoFy+U9KIYYfm3XM9Sgei9slGmuHfvbC1sm76ao7bGFlD3FOevz5g/kOcmF03sDFtn97LX6Fxt4rcy/Oi+K/9sVUfGvoq7YthHiVpWvk0ZtZRGWcJd34HVR/6E+F3WBbnge+kat514PSwdGILgntqXgdtI79G4zRlLvTgIlbLyNz+I9ft32+MRTU37jH5JkPYAHhFmiq2Go4x8/ceNuaxA16eART6qerQe0M1336Nro2xH/IyKyqi12kskKbm1Evpuh1UcmIiJ2NpzlPPT2LZHrIhxagOcDHBpgE56h2fTN+xSHkSBGHzjoead8T+fRF+bj2CBjLWuNo/TOjW+Ng9ZtJxDGC//JSgd+cwwPPV4R2dmM7c6p/vxlpnoj1fpn0d1hMvSz33v+3rGGeXyAuYiFcXhkHa6uvo2gbBKEEd0ezA4YJYiHoA7s2+THWYbuqlVVRV9Gzyn487St4FIi9jSZb5MK7jtrytf3/SwXF92ZTHWVny2PeKjGyp7KVhyMO1gdTHZXGcJVkaSv58TrRLEx9erw5oO0t4PVblQSUircN+pGEve9sd7J7q+xPmHDcJq6yfl17ORNABVc9ttI0zsZzB2u5ngQxHSvdrVAe9H/joOTD3wwri38pI6VPYJ8jc5bmSnxP+jMW5CC0ZRnV8yG4huIIrGetERsDiLIfvlAas+wxKzhrYD4mMnPm543oBT6y9H+3YPml5Yz24QOSFjAelUxZOJhtUmK92tatvzkW3Qp2KPRddHCZ0a645PgL0/5C36vMEQ/NWYf//UmsP6bqFJ+LJ5/WBpLbhnYKyha3D3PwiKoFvq/Z7OsaIuAYTmrRCtfmPTdnQMVMvy13u/td3NbW+eQr2GC8W+mTxtFbbSffQJi/7PvDBXe+tgCqt338=
*/