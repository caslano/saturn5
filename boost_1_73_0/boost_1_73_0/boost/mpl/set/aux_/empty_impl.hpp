
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
xOqsq1TRElsqNIFQWLFMpqYn4VhmqwE+HWYsimvUAJgsEfCOami9pMZaoPB9KIxrXr+AUMw7AIUTI9Bz0b0CPhvtsBSGa2QkGNHYErh8xg3KYDkxl5qmZm6+gDFfMhQdAZZoXIPh4GpZinXFX1YWDmYOY3VQ4x9B/N5ofFSIXg7QKmkOY+UCtCgAfzs5NSOWOAg2AXgvxOZA2OvDNTepfg8lwoAx2tUsVPu0eFKPjWr7Se+F5zO2r69rQNRvDUA=
*/