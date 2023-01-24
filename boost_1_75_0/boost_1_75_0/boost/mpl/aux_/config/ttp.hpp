
#ifndef BOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if !defined(BOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS) \
    && ( defined(BOOST_NO_TEMPLATE_TEMPLATES) \
      || BOOST_WORKAROUND( __BORLANDC__, BOOST_TESTED_AT( 0x590) ) \
       )

#   define BOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS

#endif


#if    !defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0302)) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        )

#   define BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING

#endif

#endif // BOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED

/* ttp.hpp
ZNaqfn2bidmjyyqmXirIfADNnNVe9GmfM3xt3OKwjWyIgDOBRUmzCTuIFjKbnyClcU7xULf9THZrbXUGJWLh5FxV9UohhBTyL06jEsIwL0r6fWCT2jY1+jN2iku6aDL5olEsk6krX7UMPwRGJEQ3R/LxdBwsTU8SYS5KkXyt/hgx0ac2wEi8u5qqTHEUWB5gRy5m7taLjAlyecDBKD0hQ5O/E1JnwflMygD6tucU50ZlxBwiBwXtzlQgKEy4T7t1/fkm/K8k//m8UOKSpLyqwZBukp0Lu1XcanoG5J/JntGzEgCMFGUoM/EGfY8yDCZeA3oI2NsQy8D9rkyqTGg6WvB4MVn7VZ7EFKoZoFgfGqcXqUIXxbcRl5fomTWhjoDcVIPA86A+dtUiaOEvvZfIp7hnp9xy9sOjrtDP8Dn33/N0XBULAjCgTyfFHFTdJtT4MJ9dURrWJPh2rRR88fMWkoPkwmEdwBoid6RXRWWEl/SQE3jkgFqLnIy+mnJiJ+5vX3rlhphspCZGZyLVRIapY+Oz67AGqhwqh+v3PQ+ixSvSg6BaSGtfSnJMdq7yuXBz7zaMRMnNJBcStoNsoZ5mUDNfkmc7oKgfUFB8rDYzvj2VjX9BjBjpIs1DGWfHXYwg8A48o7cxjPGU+EtyTeLMH7xnaABFkcug1ViW4BFCgHbpRZR3nK8KISCOnw6hLZhQpB4rv/rSG49udbsJ
*/