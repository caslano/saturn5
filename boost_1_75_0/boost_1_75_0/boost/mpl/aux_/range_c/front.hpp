
#ifndef BOOST_MPL_AUX_RANGE_C_FRONT_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_FRONT_HPP_INCLUDED

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

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct front_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
    {
        typedef typename Range::start type;
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_FRONT_HPP_INCLUDED

/* front.hpp
Wj/2izhb9z4vFc9MT8Pspj2Ux95qPSDskHOZALgB9xcbCpXrlLiDe/duAf7/rrRg4/7LWdTVBehg9xeLMnf4e0iH186WeMTVIYX/RtRgIczM10ZcG8cqnvxKLD7h6/d93xlJ6dfaGHIqFbDVqE7CEfHV8QafShLD0fKynJ9mqd2geGJ6bkimJQ+azngTyWi0XouUUQFr5vuADMSPM4VqAc1Op8MftWmcJrq52N11/bI8gjEXhMyv3cwtNie87w67uMg6tl4u03N027qfSljoiQMYHk3p0FO0xn6+J0V+xzr4QqOiojK6W7YVNq36yBgYeNcsP1XwUSX9jjhYN5g/2Cf44I/0GOrklSKajKr+LdKh949+I5X1W2GwrR1KMRYJYQT0YFYOQ9NmeikiTn9Gs7tCsli8yu0Dh4hTCXr7tZzFq6den1gzlTdqJXN4skFDjIJhK64v+L6/4vtk8jEGfbg/vmEpmj9mDl37EOfJYj55XR3FIn6iy/y9ORS78kndv/8X9S8JPBkDyWU06WdJGwCQxNHggSHNb3ivRvK6eBgEPq6l2ffb/iVzGUH1K9fwA1gGs9s0Q7wHknJUXTRrsR8rVYInk9N/+kr5BnC7sq90FDzovNy8Wl+8rqlOiGpd9gePclVP+UOl/Rfa0wt7ft/7v6QcddKwn747S/0M82YEW71Rq+U2ZZr+LIMZBNXiDT7Hg2FEGJdiyz+E
*/