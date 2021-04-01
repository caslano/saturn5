
#ifndef BOOST_MPL_FRONT_INSERTER_HPP_INCLUDED
#define BOOST_MPL_FRONT_INSERTER_HPP_INCLUDED

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

#include <boost/mpl/push_front.hpp>
#include <boost/mpl/inserter.hpp>

namespace boost { namespace mpl {

template<
      typename Sequence
    >
struct front_inserter
    : inserter< Sequence,push_front<> >
{
};

}}

#endif // BOOST_MPL_FRONT_INSERTER_HPP_INCLUDED

/* front_inserter.hpp
5O9LbvhqAKnYxBogj5pgoLLWPiXQ+eAGcGAh55Ki+Tu3GwDZJTo/Hixu46W2AP8y4I0PkVa5TSz5dZ2i175PRfX5WvT4rvVm5z8FbUz+80Q0tYjzbUXqiW9XpEilk858Q7ntc4oxPUN3GP7ldYLute1TrhXwWYjsKnwLgQJ2gD/o5+2BYJFlDzjYhNr2OaMKczrRGtT0a2ERKRYLnu7xFsvDb/+LpKZXAHgdzyn/nt8gh/PWNI7vJdgUdSr0XYNtoigy0JNVfZzp9TuO46M5uS87yKg7Ijtcs1AgNjPY02SuQtQKcSRU8i7W+d26M9oz3sR29cKaCTxf3K4udHoOgLg2oO0zME32Fx/Uz5l3moL+hyhsG9O1jsdTX3dvNimzHtvHV+j4dKbivLp6FZgG1CCSQNOdvR3Ik4EM3eqH1W3iUc1DYT6KN0lG16GuirQfspVB5F66ZqrJi0sTVXjiKPPY8Q7UNn3GDaxZSdQuNSlO9Yj80V3BouXW/xR79RM6ja7qqiV6QfdPpaDqtRyMKL2O/Fqup5NY+JHkjPaqT79jl41tyyxqWDyJYw==
*/