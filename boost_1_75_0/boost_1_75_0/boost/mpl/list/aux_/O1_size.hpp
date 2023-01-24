
#ifndef BOOST_MPL_LIST_AUX_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_O1_SIZE_HPP_INCLUDED

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

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct O1_size_impl< aux::list_tag >
{
    template< typename List > struct apply
        : List::size
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_O1_SIZE_HPP_INCLUDED

/* O1_size.hpp
l08i+c551wb3oruOrDsS2MqS+Q76+J/yl3dbU45nvqK5vcCis2tgsI7t9z+OToTfnyJABlAYCJ04+zOQ49wIvHaK2oVWbIz23lz/3cdSGYaoIT6rBMNzWM+pn9mV+PIGo3t0OUCY3Zb6jYj/fjBN5Wd00/11BxboWol6v8q1glow88SU5vP6CpPIPRLTN9QHoOX+GHbLhKnwFcLy4f6G2uJrFkYk/3cs339XePP/u8Kb9z8U3tH4DOpYE00cq8vJKopLsV0GyUUs0fvix6W1Ga24Fnoax8q3MQY+ncpXWwSyAMf0toXXYQUl9lGbnkJ4GclgXxwhhx9/IeysouLQrgCKkxDkBXeCPQIECO7u7oNLsMHdnWDB3d3dLTgJ7s7g7jbI4AxTWW0/2q72837c77v2unufg++oV3Qc92YDw3UKwpdB5Aw45fpB8lNmz/IlJ6N9XD5S3zkC3w5u+lfbLR878HAig/3hcr33Za1F+Oky/AHWlI6DGYHmVKbCWGlgXkwpHgwXPrZFj4um5LQzfqWH54/oWW9/dscHoDzkrIMHwLWIkNVjl6MC4KuCOMeQBnSNyeo/LsOtF7203wYI1LH0z/1+n4C08vuPbwki2dg4Lgaio/WqGngPAmvDKWHeOm8NlZdOt4a9z02teWWwXIaEKaHysUoJDbOBzyPJjT6skR8IVeVSl6nCXAtDXsl+s48ffTGf6BcZKZoz
*/