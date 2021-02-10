
#ifndef BOOST_MPL_MAP_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

// Copyright Bruno Dutra 2015
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/insert_range_fwd.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>

namespace boost { namespace mpl {

template<>
struct insert_range_impl< aux::map_tag >
{
    template<
          typename Sequence
        , typename /*Pos*/
        , typename Range
        >
    struct apply
        : fold<Range, Sequence, insert<_1, _2> >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

/* insert_range_impl.hpp
DYcd5dlqUuvmYczdIsdK3sxTAxSlMZFskpf8pBb+INCKl9i2BV0RBv86DhXDailA07oseZW1IgvL6q/DmPnRoq+3o3DLYLRrRUZnOCuLRYOpQKn87qtqvEUyYd9R5Icr6B7ADxIFyCOCfhc48gY+deVuc6xll9CL4SqJk6hlndaFTZzxeAKuEznP/sZnHx19MIVNuPIDEwDaAOZ8ZqKZca4pYcL0FT7EqHV3sB5/xi9QSwMECgAAAAgALWdKUu3OYN26AQAAxwIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4MTlVVAUAAbZIJGBdUl1vmzAUfbeU/3DVqurDFBm6ruoyD5VS0qDRgAqNmk17cOFGYQWMbKcV+/U1Tpa0e8H43uPz4WumUemCK/QIq9qVMMsz9q9Clsoj0Z2fkszPYvsB/yGfQRr70ZzcT4PzC/eCMHpAM7olIMfkGDKULyjHqiqRMIld3RuAssWiKT3ynitM46UlD+d5FPh5CJ/+FWeLvz8fI784W/wpmoUDvuOcQfLjI7oQTVejxtJYeCfBSq65R6ZSNBNo8EqJBl/XKHFEcjGBFX/Gq1bsKiPyJMp+WMfjEQHoxUYqUFVbmHZtGoxu6RjdpbExg7rCVu9iFnazz+mR
*/