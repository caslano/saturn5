
#ifndef BOOST_MPL_VECTOR_AUX_CLEAR_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_CLEAR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/vector/aux_/vector0.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct clear_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct clear_impl< aux::vector_tag<N> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_CLEAR_HPP_INCLUDED

/* clear.hpp
3vGRMOoqIdrWIqVuiRoWD/aizYAxJKFDpZVHqcLV/cfvBWZYHCYS4x5gdRy/2zJv8xfdnrl1Uk2Yp4/75hpE9y1P7mg2Re1U1LjKIzp/wVskAtwI4z4umFbUqOQVeAs8fZhupZLo6MfC1VmzDxnen6TMQejQp5LQPORfM3xivY9oP4jGvBLdyQSuIg91oeyjQsoOLpTk6EQptndTIb8CUeAn/AIm3PaaV03IJCfd8gcgGp3QBOwG0As2MnaM9lTV+ZO93IWgWvTeTbg6HqXWsdVHL0J0qEg4YwPKu90nBnFxPqXyxN/5UdWJhLBoOL+JUPjICgGG2UpkfxMkwCmo68YE4ZisrC+b4J6tXh5RGAoNErm8q03oo6QeEud06YXdiE1Opn2vaOYwUiaSyRfvqXWD4pnubb+BaCQ0LiEcM37Q8qF+hHzzxNsw0rCdMNHTCgSI6pFYgDjeDkDcjIEsZ7B8Aw5bvn3TSZpLt/ReXVJ+gslZ1ebTDN61/usGukSCizQi5EQjQphmiZ1i5U1t5rvFLE8QUwigQbygsNhDJMV471f0iL7IjZB+XJAssb6lUPVFOIwwpV2Q7xK00Z+6sJGKF3Yj5qSjfH25rD+ewl29DZVAhXW4TDj8CAGJeR5DacP+DGToOf6Uorv0A99jZNFO62G/VZTHwOOJb2rxx/wKKePZx/dqNlvoQ9GvkZIcmQhlD+v+C0fDaTTZ
*/