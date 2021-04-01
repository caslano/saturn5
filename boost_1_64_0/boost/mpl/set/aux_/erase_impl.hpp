
#ifndef BOOST_MPL_SET_AUX_ERASE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_ERASE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/erase_fwd.hpp>
#include <boost/mpl/set/aux_/erase_key_impl.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct erase_impl< aux::set_tag >
{
    template< 
          typename Set
        , typename Pos
        , typename unused_
        > 
    struct apply
        : erase_key_impl<aux::set_tag>
            ::apply<Set,typename Pos::type>
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_ERASE_IMPL_HPP_INCLUDED

/* erase_impl.hpp
ASZylQESHbYJ7YpoQNyCdAn4SJvWQ2Fwn1znUDYQRfGzKt1VRqX5RPdj8iIUy/ln6h7zmCvEXZJ2UhhSXjLKxzTsN45HblOxmNVxA2m5F6MNxI2Awe3z6jbF69FiLr6IpPjemNR3zlAME2vtmg/ajcfcdYPM9epbaX+CdfI4HrzoMTlVO/60lVAeoZUGu1A5hqPDVeoyV4+pc7SeAgQLLrtr2RkwJfCRGw+DtmdOc/Y26RSRB3CiT1w4mD51PnJ00FI0n2H2zv0m0xlNit1frJnhFS+Z90f/nqAvC0JKbc3L/jYOlR3HyJdXYpz/yW0X2tvMQUDMTXriKrvqyGHFl6NBO5Wsn+g5de1TAoD0N6df441KyFk9muKz5zHg/4hn9BCFh50xVs95W2pZF0wPJAADBskOhuN5OVwhAEIxPbxICYNzPXH9SDiqu53pMixwm0PiVV/z3VD/s3v4DEIAJU9u03XTKCIj5cvfMY+9wwXl/lDM9pemReh49vSoIk995SQpRBlN2x/kudhUaai3KSW/xTMdphPZAgbjofUEYE3/vClbivOgAf9qHQ==
*/