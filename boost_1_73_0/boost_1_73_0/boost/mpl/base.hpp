
#ifndef BOOST_MPL_BASE_HPP_INCLUDED
#define BOOST_MPL_BASE_HPP_INCLUDED

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

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct base
{
    typedef typename T::base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,base,(T))
};

BOOST_MPL_AUX_NA_SPEC(1, base)

}}

#endif // BOOST_MPL_BASE_HPP_INCLUDED

/* base.hpp
7jtssIKcaRrlQhF24hJJXjqyOgiT0buzp9y2/O7Qhzl4UtTyifdKnPaqe8CiCPPZI1vGU/1Q0ynxY2g5msb/2Y3Qdd+SROes0zZnP2O+fxfK6Kw4uvyNr1BLAwQKAAAACAAtZ0pSD9QoytQBAAAiAwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE1MlVUBQABtkgkYGVTwY7aMBC9W+IfRlQIabVgWLWXyBuJ3aKyl4KWdKUeXWdILIId2QM0f99JQmHbvSQZv/G8N28mijCS0RFToazbeX7tsTn7kMdUrLJs0z3g2zITk8lO20ooeUtQsr8jPsEWwwnDJNochQpYVw3DuSYNzpsSzf5x2GAc9kXlfDqDz7M5PC2+wtP6p+hvJxDP0VQ+onj2jtDRJGtqTIDwN8mSDpUQWWkjGEa1dRE0BIy1dxH5LEdIH7ns7B6iB3MMFcTSH6vcjQlyG+tKN0B8fwqwPKETxGhRgqXxx0pUagIKtigwMHqkkuVYo8l6dw9nHAfkzgiO0bpC/Iu39Ge8kEMkW1XQejdlw1pLWuMuFrFzz5VtO+2dM13ACbFzJBUlUc3pf0NQTh8wvU4FzpZK0A4wBB/eST/YouwaMPv/1HN2DpdhgpJ9PVDGHw6M9IyJ
*/