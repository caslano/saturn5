/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ADD_REFERENCE_HPP
#define BOOST_ALIGN_DETAIL_ADD_REFERENCE_HPP

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#endif

namespace boost {
namespace alignment {
namespace detail {

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
using std::add_lvalue_reference;
#else
template<class T>
struct add_lvalue_reference {
    typedef T& type;
};

template<>
struct add_lvalue_reference<void> {
    typedef void type;
};

template<>
struct add_lvalue_reference<const void> {
    typedef const void type;
};
#endif

} /* detail */
} /* alignment */
} /* boost */

#endif

/* add_reference.hpp
zODiCqzNMHRfEVXo326fKxQuJgB9u9vGvKrm7lPwsLeyUFch0k1z7asGOHfnGzAaKqSDRa6un00nZbo4TuGx+hA7kTxEum09n37V+Sm4E3hntCvwNWStjkCCtOrouPwwmCWrm6Z8fMXUvkbP+miGNETqnRolFJ6swYpcn5RZSlgQIPU7PXjJU+FAltf38i85rdkf7H7l3eWwTN/qDTuTHprKfWDcR1Gjl1qaEKVaFfL06lkB1NrOoi4Hs5q2ocktxxUOmDV3KAfYkLaf+Xl1IIIcJVosKtI41k/pnIV9miylOx5QAWV3j9Jx1io0oUgWBsNLouxdYw4ih657pEL4PI+Jehlk+RC3vot+Cp9GCjq/xfEA8UUMb9r9eyWSc0RGX2rFTrb/qmvIftJq6zMNCQVncrV2/8gsKpoucoQlfjCB3Wo7g1LDGlxxqgqXHilT6MFGYCcIDyJ/33foctXEvq7XiOCvzcZpk23JNh6lZGRiCH8uj6nZrFgIOsIrdBLSczYFbiuwgf2CUZpnOv2DC964ZDRTGAFL9IOFwKZNhgMgC90qHp1HPXQeIiO39Wa/cts9U4B4Fb8y+Ty6O9n6WA/DpOG7lOB6nupm590AT6a7/IPPFtsOpg2uwATuBmBNOwRx9tliENakRnVQ8VKcphQzydzAgPXxG6o0lkHPP/5k4ntmqnTw+F3YICgOPxdbSY40FazFIIUad2r/
*/