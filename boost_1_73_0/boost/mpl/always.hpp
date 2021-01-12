
#ifndef BOOST_MPL_ALWAYS_HPP_INCLUDED
#define BOOST_MPL_ALWAYS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/preprocessor/default_params.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/arity_spec.hpp>

namespace boost { namespace mpl {

template< typename Value > struct always
{
    template<
        BOOST_MPL_PP_DEFAULT_PARAMS(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, typename T, na)
        >
    struct apply
    {
        typedef Value type;
    };
};

BOOST_MPL_AUX_ARITY_SPEC(0, always)

}}

#endif // BOOST_MPL_ALWAYS_HPP_INCLUDED

/* always.hpp
bClm9zgvgV6M81Kpq26MuS6e6fOSNhpvp67HGHPWtESbOV471tw53ThwVxpf7QKvhfs5l2tOtjNmhufz5dvJ9QSrtLGSCKUOQrq664D1ej+eoDfj5OnzqW3XV5J2/UryVQ/n4scBqOZH6kHGMbrKPCnrt9kT7Tk29Xnz4YSVRxjwarZZM7aLci6nrNj1/ote1L22THukTEpbrh7Wl/0svLtaJtk+11QmtZ7VfI4McuY92Tif
*/