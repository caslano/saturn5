
#ifndef BOOST_MPL_SINGLE_VIEW_HPP_INCLUDED
#define BOOST_MPL_SINGLE_VIEW_HPP_INCLUDED

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

#include <boost/mpl/aux_/single_element_iter.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct single_view
    : iterator_range<
          aux::sel_iter<T,0>
        , aux::sel_iter<T,1>
        >
{
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, single_view)

}}

#endif // BOOST_MPL_SINGLE_VIEW_HPP_INCLUDED

/* single_view.hpp
9fC9J46ZMLflJQbY/QyO/dAy2m5XwBnqgA2M5un/K2pFz/ALssoY3RcjLPVCvvCrW/wI4wlfRDv/2z99rwKqvmLzn94ySKcKyjnq78Fo1qAI8wD7kDv+GNGSQBMqXRdogV/9RhCslDn7WOVG170eNW9l7XAFXSfoW8yRfaIBOKIG/AUQbi+Bs1MO2naRx3MBzysDCk00vARo3mSRazJbgyPfz1w6wHYYILUUrrpQw2nw/tX7wNoKlKYSlpxiarl5ZtmHDV3WmbX/6vUpM6PtdVJKVUwyupwMEEViF21H3lfRhkTSVMUWqrdF7H0NemW4rJ45DKV5L1/HqC4zjgc5LcMAk7dNIjnRoGZU4/3upBsHy1v6+zHS9m8THYdjUjzu8TVrg38j0EqCHxUivFKXsZEoZ372sNnjA9rSpGHR5RXA9Ri50HEmiaEyj2mTEqVX8KsUjvP+QqCHXKDM7rX1K1d7SNvlIslU5wrcFQgxAAkPbvVL6JiIJr26xeyYBzIpjbq/jUV/3RKBNHbPi7ojptqeMma1vrzOIQvcn6ama4nr4r7NoUULbujMfg==
*/