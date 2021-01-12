
#ifndef BOOST_MPL_SET_AUX_EMPTY_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_EMPTY_IMPL_HPP_INCLUDED

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

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::set_tag >
{
    template< typename Set > struct apply
        : not_< typename Set::size >
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_EMPTY_IMPL_HPP_INCLUDED

/* empty_impl.hpp
sdVEDKXVew2hOESo8uV7quhqjyZ9vFnP4bz86135tH6ucUNlVeBXDUG7bOQB2mYS+nlX2O0k4a6KJOBk+eymwN8rjeY2rdpPz3OkxggV3uTTIkGdaUVdYK/Nfp7xSC1VzRn2bvLpG+189TZzk1XXzwjypsJqEmLx6TcFdHqdaDVhkmAcpL/F7suqG+qMiHZ7uzXotzZWa8PVx3i29vNWqV7XY/lUf312e/U8yrZdLKteN0Zs
*/