
#ifndef BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>

namespace boost { namespace mpl { namespace aux {

struct v_iter_tag;

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
struct vector_tag;
#else
template< BOOST_MPL_AUX_NTTP_DECL(long, N) > struct vector_tag;
#endif

}}}

#endif // BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED

/* tag.hpp
RHtBGzslkTCLTdV2wLjpiVWlUPuRKPoiIK7vS4mrfRMariUwLWocTYHRoWLOS6VTsramTkCqskQbZCLCTQJCG39GG5GInIxso05twIEVpq6FloNNQulskx35Nk9mnX6eHTh9WCwgjmuhqtgWjQeLhWq6jI/4JeqmwnnQuBJl8AeHWqL9ec0hDrY3t7Ad39lP4A2tKluQwgsQpUcLITB0M4ezcHBC1DBxZ+MnhF16Nkg01nhTmColz5tdBiFnRPbL7Q7Wh2yfsN8p0ogcVjkHniXsz1cE4GnJlxF5ed3ybkx3C/bRVEbI/0543nVfWxi9Zab3f/QNUEsDBAoAAAAIAC1nSlK8ksD9ZwEAAI8CAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0OTAxVVQFAAG2SCRgjZJRb4IwEMffm/AdLhofge1xpCEzbkYTDQ67vVd6xGbQkrbT8e3Xgs4s28MClCv87v7/O6AOrau4xZxQqWrtb+/Yn7URNif7LdsRmt4e0HRkyJRMYY/mhCa2UiChBrumD8AlGIhFI1G5C1ENG4/YIS8ntnWdT7hugSre4igKZ+mOsCg3y1hoF4cApALBHfdcOoLUOiFVTpZGtxkIWddovEJEmM6AK+2OaCISjmQ4L8tB
*/