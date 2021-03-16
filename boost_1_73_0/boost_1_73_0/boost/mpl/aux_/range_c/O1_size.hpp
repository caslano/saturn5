
#ifndef BOOST_MPL_AUX_RANGE_C_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_O1_SIZE_HPP_INCLUDED

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
#include <boost/mpl/aux_/range_c/size.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct O1_size_impl< aux::half_open_range_tag >
    : size_impl< aux::half_open_range_tag >
{
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_O1_SIZE_HPP_INCLUDED

/* O1_size.hpp
vtCjj8Sv9Gh7j5upwF+8+mD9XT7t3lu+1N3rHS66/D+5+37fJ3evXwXvSem+5U2V9vY1xTjDn9q+HhDUO7u4t6Z8cW5N21vJvANNogKKQpB3A6Nz53Cvf4rLOQovEM5t5KZww/wIRhKL6+yD6clHxOVGMzw144S0I+M0t6gwH2AKIg/BB9XGaPKlp/bkIrIkkrSvmYv8UfMD2l6uNC46ToEPU7MK+WIBz3WqzHNj/aKa+XIPOAzBhgk8P3Ge1S8=
*/