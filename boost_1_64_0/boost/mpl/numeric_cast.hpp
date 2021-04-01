
#ifndef BOOST_MPL_NUMERIC_CAST_HPP_INCLUDED
#define BOOST_MPL_NUMERIC_CAST_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// agurt 21/sep/04: portability macro for the sake of MSVC 6.x-7.0;
// resolves conflicts with 'boost::numeric_cast' function template.
// use it in your own code _only_ if you care about compatibility with
// these outdated compilers!
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x570) )
#   define BOOST_MPL_AUX_NUMERIC_CAST numeric_cast_
#else
#   define BOOST_MPL_AUX_NUMERIC_CAST numeric_cast
#endif

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename SourceTag, typename TargetTag > struct BOOST_MPL_AUX_NUMERIC_CAST
{
    template< typename N > struct apply;
};

}}

#endif // BOOST_MPL_NUMERIC_CAST_HPP_INCLUDED

/* numeric_cast.hpp
Rpgg0Q7ycpIgJgT3E7FkuZ/n5rdFzwqVY7jG58AD48q+IA3ICXQkl/98mvRZHggMIqYQcNdGwzE9+pmtPU3vX4W+0S+vPsfJtx4JBquXUe6urFeG7zHvPzR/93LmscD7gvLW1T3mlazcOK7mYnUJYp1LvpRQ7RjOwFxLfPeb4JxvKmTHlA1ZIjfI812wm9ddfUgqkCTkJcuUAS5snnfBWs3/V6NqJ6n/3X4yrOVE5J79DMCBCUkonwQjpx0DtI+sB1KmKhiF8wfh89C7lOn7p+V9nI+0ki0MnW34xUaG+1M7ejmvuWgFB+dLs4GrutmOTcgIUJW7utnlqeIxQaVsrzVd2MRxd55KEvQypVPVymLPltcYhAaaJpYU9Jp3OdBz3vEuHqq2eNiAjSE3twwaphmJOUqM6jV2BRkVjQNGDuDNAKqeiSmGCrKePGTkx0c9nYafYB+ZRYW7Re1DSI0lVGRT0A2s6iJfl91F0lgzj87cyR2WLE6Mr+qBW0HT2CWQqm9zLNyhW+RTxmQe7eFtpT9wRwgINUqJXnLbMZUNwzrl9x5vGBnDxSKCVg==
*/