
#ifndef BOOST_MPL_BACK_INSERTER_HPP_INCLUDED
#define BOOST_MPL_BACK_INSERTER_HPP_INCLUDED

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

#include <boost/mpl/push_back.hpp>
#include <boost/mpl/inserter.hpp>

namespace boost {
namespace mpl {

template<
      typename Sequence
    >
struct back_inserter
    : inserter< Sequence,push_back<> >
{
};

}}

#endif // BOOST_MPL_BACK_INSERTER_HPP_INCLUDED

/* back_inserter.hpp
LWdKUtL8cxkIAgAAmQMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTE5VVQFAAG2SCRgfVNNb9swDL3rVxAJgl6W2E7SfXhqgCEb1gItGjTusKsi07MQxzIkOmn+fSm7SXoYerIoPfLxPdKS0JNWHhdCmrqw/Nni8WBd7hfiNstWQkaXCxn1mKEYQlYaDw4bZ/NWowfjfYswnM3mcfe+RrdHN/YmRyEZVx05P1ekoLa6RL29GRzRD3qWKJkkMIunXDA3DjUBWdg4u8Uanp/uxU9FmDJl+wmSL/CgHEzj5DMk83SepHEMvx8y0ROmEBSNfRdEhdqiWNqasKZxdmwwPL9Q1FTK1N9Bl8p5pJvn9fjHenl3J/6O1w1qo6oU/MHrynoU91YrMrZOoQSiJo242elkPrmOAtO5+j3W/6hMIQ43NUvoUvoSbFxQHgx8c4INWlYm5PUG6S5gQN/4QpRMxfBTOGRDbMUmw6FUnTutRzC1J1Q52AKudOuqKyEDbCEqs0muk69coI8FyFrteMi/Xsgptvci6mCoPFmtNt5WLWHnOciozwGp7W6n6rzvig0Y3T6us7tVOgqzWz0+ZRGzfWO2M5CPb4q6ZfiDzhRH6MavCkIHVGI3KSiVhw0y+cCXlgZC
*/