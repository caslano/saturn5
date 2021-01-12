
#ifndef BOOST_MPL_AUX_FOLD_OP_HPP_INCLUDED
#define BOOST_MPL_AUX_FOLD_OP_HPP_INCLUDED

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

#include <boost/mpl/apply.hpp>

namespace boost { namespace mpl { namespace aux {

// hand-written version is more efficient than bind/lambda expression
template< typename Op >
struct fold_op
{
    template< typename T1, typename T2 > struct apply
    {
        typedef typename apply2<
              Op
            , T1
            , typename T2::type
            >::type type;
    };
};

}}}

#endif // BOOST_MPL_AUX_FOLD_OP_HPP_INCLUDED

/* fold_op.hpp
/b7pVp5/GErlJYjOjBNLWbFdrE2LbBOOYkEhoaFae2xoJs4Pcav05T/FEI81xPsZ4r6rMnf+cKyXP8vxjHMEbcj8/BSstaXJ9pZ9ynE7au2KWmtPxu2DyjY7yPZyLUdbLOOMWiZ5dtjmlJdSxjIu68G4uRgp53JZH+0dHJz7hiuj68afyPhDGO/kChlfew8P143Kbz6BuvGTGH8w442I18Y/8ifjpzF+Z8b7+W/a+Hulbpoj
*/