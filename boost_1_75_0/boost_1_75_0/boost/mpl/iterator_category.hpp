
#ifndef BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED
#define BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED

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

#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost {  namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Iterator)
    >
struct iterator_category
{
    typedef typename Iterator::category type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,iterator_category,(Iterator))
};

BOOST_MPL_AUX_NA_SPEC(1, iterator_category)

}}

#endif // BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED

/* iterator_category.hpp
M6hQuGhf7xCVqThqW451MSK3hgFi40+BhtFzOaOc00ALZ9OnH7rP0rEr3BAyrsEzvfGe4ii9rLuvK1taHw/KfNlSP4jAMH8K+mYrA0CfnqG3uAam4paaX0PtilZKVlt36/ZSBXP3NnVFGbSGmFjZETSTjUY7RuKOfHfHl04Zna0+lbx+81SUe54HN5IiCXH9uBedmo3LWVxlA8Qlx4NxXj5X5K2CD2/mF9677KC8ptYkWHfjjzyV1BMjp1TD8X7pJNOa+8ifUMG4y+o1rjRkTapSplT5YR0NzdeITjB1qATTkLbBTwehwGkUDytS7cIl3gj8dsWljwIZDiDXDhUuEUt72diT2WACse3nkPXKkSNZzXi+z97P31SrhYs21ZLnp5wfRBo/CgnRKpOe6uFDduOrdXuqeblVvsxWq55ehj2RdDV31KgOVZl2eRX6OTIZfAgV7qa5Ww8OYJ7+OrQSrFsRiPbZNpZdYBh6v7JQFdLcl8181jFb57rR5lRaPZqDO19zApYv8DvXi6/7IOL3He0ytG7DOAMIb4kwYK8DV/Y5tX54Bjzrm+EAP0HE6Vr68ml5mE6JDY/uG1UvcN4QfAK4Sdfef/3IeSoUW+3QbfDs3Q3dZIv/1C7EbkuNBLdoTjbrKQ0Kaf12auZ1lnxGiO/B6XvHdhN13jHF+dXaqj3OS9mw/cnztE4//9nEqNdjjBKQyJ+AdNkwdolc
*/