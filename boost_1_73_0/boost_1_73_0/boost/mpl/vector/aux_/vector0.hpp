
#ifndef BOOST_MPL_VECTOR_AUX_VECTOR0_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_VECTOR0_HPP_INCLUDED

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

#include <boost/mpl/long.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>

#include <boost/mpl/vector/aux_/iterator.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

namespace boost { namespace mpl {

template< typename Dummy = na > struct vector0;

template<> struct vector0<na>
{
#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
    typedef aux::vector_tag tag;
    typedef vector0         type;
    typedef long_<32768>    lower_bound_;
    typedef lower_bound_    upper_bound_;
    typedef long_<0>        size;

    static aux::type_wrapper<void_> item_(...);
#else
    typedef aux::vector_tag<0> tag;
    typedef vector0 type;
    typedef void_ item0;
    
    typedef v_iter<vector0<>,0> begin;
    typedef v_iter<vector0<>,0> end;
#endif
};

}}

#endif // BOOST_MPL_VECTOR_AUX_VECTOR0_HPP_INCLUDED

/* vector0.hpp
iz4KumM20Eq3LVdiNJSl6WxV7Nl6l82Ck11RsvTh7h7iuOWyiU3VOTBYyS5084ifvO0aTHyNK1F7O2BRCTQ/XzOIvey3mg8vExlm9YZG1v3QIvDaoQHvH8LXgSO3cEBUMLFH7SaEngbWl+iMdrrSTU6eV5sCvM+IbOfrDSzLYpvR3y7yiJSLHQNWZPTPLjzwNGfziLy8rlkY002CfnSN5uJfA0/G67qOM09CvWsRmn53kd7+wS9QSwMECgAAAAgALWdKUqdugoiWAQAA0wIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q5MDJVVAUAAbZIJGCNUk9r2zAUvz/wd3i0FLaD66ww2IwwC1lCAgn2HK+wo2o9N6K2JCSlm/fpK9tpsrEderFk6/f3ycyT8zV3lAGTqtFheaL+p7bCZbDfVcX4wPVym0O5Wny6+wAsuSBYMpHgGq5xT/aZbOykIGCWTNsHgBs/1p3IoFwW2x+4XG9z/Dib4UJ3HVcCj8pSrR+V/E0iCP5BYMlJZZRftJKUP8nX48tZPwPXeXNmZ4BM8S6UmjLHWrU9jk0mAL4bYyjt0R2N0daTeB9IycRizgupMlhZ3aUoZNOQDXYRVDpFHlgHshFE8KBFHw2uExxZPXWa4qRJ
*/