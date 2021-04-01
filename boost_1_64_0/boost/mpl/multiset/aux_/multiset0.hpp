
#ifndef BOOST_MPL_MULTISET_AUX_MULTISET0_HPP_INCLUDED
#define BOOST_MPL_MULTISET_AUX_MULTISET0_HPP_INCLUDED

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

#include <boost/mpl/multiset/aux_/tag.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace mpl {

template< int dummy_ = 0 >
struct multiset0
{
    typedef aux::multiset_tag tag;

    typedef int_<1> count_;
    static char (& key_count(...) )[count_::value];
    static char (& ref_key_count(...) )[count_::value];
};

}}

#endif // BOOST_MPL_MULTISET_AUX_MULTISET0_HPP_INCLUDED

/* multiset0.hpp
duYgH8q5lGgFOUMW+sm65QAMgcb4nh3c9K5e26iEh6Uovsp0yaMsjzFEIpv9nnODWg55a0z1e+FPAelrP6NXk/IHRFPVPS7qvd5YprZyzDvfdZx08vUbpwpeeTsnbGlppThIYo2GeFHdh93F/uU77PtUb1w3bqgG43h83pmi64cTfKgxWoQtcEbI1E+4UiJKwK6lYw5T/p1HxqarS/ePFU4ocMxYJOmhubF9fT98Jbxwmd9jqEoSe/FEFHBNP95kitV5X+zvr6lBHnHafEyOLTBe2A7G6wfUU/TogiUrAkGnd6KRe1NPvWcZ7Pvqk9cYiOFO34gAhrwG/RI4j+Np7OwaZ/km8FNMr/1dtjH8fXeQWc7flgWYyf7BoiLT8Nh7J+rA8Ajycgmx0zDW7Ipty/d6yQMbWN2b8xX7/FUAAy4jYS1k4eVP33cY4/bI4F5Y7jT8N/2l3ZzcZvA3LXTVLhR+f0hSQyyDjJbeL6KsZhe7iC232Om2yS+rkI6S6hAH5KtNIyBGkQFYc5dS6xjSQ2JXOIBw3L5Ld+0zfrikAoZUXwji3GRLJDUOWg==
*/