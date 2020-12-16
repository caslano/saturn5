// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/symmetrical_base.hpp
/// \brief Base class for symmetrical types

#ifndef BOOST_BIMAP_RELATION_SYMMETRICAL_BASE_HPP
#define BOOST_BIMAP_RELATION_SYMMETRICAL_BASE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_const.hpp>

// Boost.Bimap
#include <boost/bimap/tags/tagged.hpp>
#include <boost/bimap/tags/support/default_tagged.hpp>

#include <boost/bimap/relation/member_at.hpp>


namespace boost {
namespace bimaps {
namespace relation {

/// \brief Base of symetrical tagged types.
/**

                                                           **/

template< class TA, class TB, bool force_mutable = false >
class symmetrical_base
{

    public:

    typedef BOOST_DEDUCED_TYPENAME tags::support::default_tagged
    <
        TA,
        member_at::left

    >::type tagged_left_type;

    typedef BOOST_DEDUCED_TYPENAME tags::support::default_tagged
    <
        TB,
        member_at::right

    >::type tagged_right_type;

    public:

    //@{
        /// The type stored in the relation

        typedef BOOST_DEDUCED_TYPENAME ::boost::mpl::if_c< force_mutable,

            BOOST_DEDUCED_TYPENAME ::boost::remove_const<
                BOOST_DEDUCED_TYPENAME tagged_left_type::value_type >::type,
            BOOST_DEDUCED_TYPENAME tagged_left_type::value_type

        >::type left_value_type;

        typedef BOOST_DEDUCED_TYPENAME ::boost::mpl::if_c< force_mutable,

            BOOST_DEDUCED_TYPENAME ::boost::remove_const<
                BOOST_DEDUCED_TYPENAME tagged_right_type::value_type >::type,
            BOOST_DEDUCED_TYPENAME tagged_right_type::value_type

        >::type right_value_type;
    //@}

    //@{
        /// The tag of the member. By default it is \c member_at::{side}
        typedef BOOST_DEDUCED_TYPENAME tagged_left_type ::tag  left_tag;
        typedef BOOST_DEDUCED_TYPENAME tagged_right_type::tag right_tag;
    //@}
};



} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_RELATION_SYMMETRICAL_BASE_HPP


/* symmetrical_base.hpp
FN9rSWKJJVEkWJPF69ZE0c+WJN6ztRT32ZOw/C1cbHQkiR4BQWJfQJK4LbC+uBiYJBYGwX9wktgenCh6hySJL0MSxfQqySI6NFGsD00SHcMSxYdhSWIevpwDIxKN3/eyr/A41YcwWR+WUB6vhBeIvVipul+8ru4XX2n7Rax1v+hs2yvusu8VqxwbxPaAveLLwP3Y9Wu/6BiyX5RW2S9+H7pfHAzbL/sFb9Dzmyt68HdiJ4q7V2RnrF0tUUaLVWqBOKQVCMVaIJraCsRA+2jxgGO0WB4wWpQHjhZXsM9YckiBGFSlQMwLLRBbwgrEceSsYt+gId9LOaV3t9DwW1UVv31p+PZvj/e3OzgYLDD0ic6QX5tpP6MplUsrvP8O7mfYRV2wkaHPcrfdY58u+p0RV+lTOHz0KcJ8zGGONrZNFdqhFDwo+tVFJkLBSSC1Q8GOCu1Qmnc7xN8v75HfnhGyXSJ3PbN97Ph6nGyHDpK7boRpO0TXOwS0Fj87DO2QrGdrQpzXJ+Bp7hYPKDvQe9gtDuBb9bxlt6hu2yHa2F8VHRw7xR0BO8TCwN1iU9BucSR4t/ghZLeoFbobdbtM9OB6tpPSGhhxQqBuoCfUBHWqP/Yfm4p965ZjD7LXUK8+dXQWX2EfsnDUqWzsVHdbSL64t0o+2rB88Sbq1enwIp/tzLcUt4Z2Jld8j6c/UuknvlSGiyfU9iJW6yd2or3pi7bmhCVHTEFbE2jLFU/CNrHninX2XqKVo5/43lFFdAroJz4I6CXGBvYTV2BXBh0Rb6KtGYx25quQHDGzSq4IR1vzB9hMamtyxMDwNrKd+TDamY8RPtuZA3RtiGxnvqE8B0bcgd7lEdEVp9An4kT1RLEJtr0GGWyhJRFfr43EArQ1tWyJYgNsW3ui+MIeIUY5EsVlR5CYGIDeKdqaRwITRb2gROymt1V8hLZmAtqZKyGNxMNVEkUi2pqtsJ3R1nwdFiHGhScY2xn5vGPoeQ8Pz0df8z4879V43vvxvM/geUfadovm9h1isGONGIXn/WDgDrEez/sdPO+LeN4xeN6tw3bLduRtur+0iO5oW8cpBWKJij0JsefcR3jmCp53oj0fdadA9MTzLsW+c4/hmZfhmR/HM3fgeSeH5Yue4fm/2vtaVs1T/1SX9U8H6xre16von+DXQ/90Bm5T/ZP0v8l0HsmPdP0nqW+Cf9/6Jv5OCU6gto7Pl3D7z/Gpf5oKv0b9U3Qi3Ab90ypcN+qfTiMuM/3TBPitqH96DjKj/ukcwlemf7qA6y79U7ip/qlOguOa9E9rEhxX1T+dJz9xIgjyyP8g/ZN7PtTzNYTrzqzYA4PZDn5nJcr6ON6gezI7B4X9Z0hdwmZyf2/xOgeF69xG53W88VxHOXyqua5J+mkidU3rya1qs8UVJZ5k0GolOWVzLKOhsylRuuLKbPExerArtDmGM1Pz3Qc4yjpdi8IdoefWS6bV07Ic+pmF0EnFkBz9X/JXpiWizr2A9rSFkqRKfZSJrietPu1/AV2PQ3Xrtl6j+ItVg36K08T+FKyf4jK1ToJuwHyeFvtjfc88Q7gkbZfowPoeoz6H99zwqcPZibBGHU4zyvuL0IG9InU4X9dzyraquWKc1OFsIH8COpxFSgTn41mSVVFrV6LDmQc/Rh1OJ3J3RNzmOpwMegYFSkuxXDQw6HBepbC/U/4oasMvZDJfF5QQ8UfxPnQ4Zjqa8Ab6Wj3SPcBt1NH8lcolDV/oFrHPoKPp25DW7JnqaEKRV6OOpirF21LqaN6heGdbWsHPy/hF2KHUED3VbayjkfGbnsfyNoUfBp3XEam3aU33fJs6UBzk+o0TZyieanDDj3SHyTM=
*/