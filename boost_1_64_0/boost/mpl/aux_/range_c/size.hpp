
#ifndef BOOST_MPL_AUX_RANGE_C_SIZE_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_SIZE_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
        : minus<
              typename Range::finish
            , typename Range::start
            >
    {
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_SIZE_HPP_INCLUDED

/* size.hpp
wvCVReD3VDXSnDM0PuvOD0gigfmGObCf9DPxnqRj0CwUcqmNZQeV/uH8pkJ3axiUvLtWtdAjRr4ByDLpaxxR6j276WQou41MI/ynnZX4zbO9sbBTq1rOS4SQ5DDI2ZtOHiVpceCbCqnrj6S7aAQp47/c1EuIWaQbM/NzuAaOvVOYM4csunPHqQYMfJolAKafwGRZeXlXgJ+gPOpT9+L7XU0gttp7+1+u/bib9XX159DaXXlBembVH/2zIdHJ2icEHOQlAw7VbO1/n6HX/lGXsBjtsR9NEy6DlVjcO63HxxjEgVDIhPnjsIV8Glx1WAJ8X70N+V8qicvesrx4BQC7vfUSCT+j6oK7A5K7tUJMiDyw7XP8Lw2M9qA5kHIWiErx/PPWvwKb8gO6aFJKUxSi4SwGNB933DRTPRXLw8J+2CvK5D/RVQk2rafXrbZvG4Rp1oZZx7uM6+vzW/tA5dcUD6PXqfv0UezfO3J281rhEkGs2KJOpYs0S1yqsT0OILb3sL/CqpjkBk4FfvasEhbwnEoQZaEuRNRoIjKIpfG5mgGvS/h1Eekq1zJodQ==
*/