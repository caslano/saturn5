/* Copyright 2003-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_HEADER_HOLDER_HPP
#define BOOST_MULTI_INDEX_DETAIL_HEADER_HOLDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/noncopyable.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* A utility class used to hold a pointer to the header node.
 * The base from member idiom is used because index classes, which are
 * superclasses of multi_index_container, need this header in construction
 * time. The allocation is made by the allocator of the multi_index_container
 * class --hence, this allocator needs also be stored resorting
 * to the base from member trick.
 */

template<typename NodeTypePtr,typename Final>
struct header_holder:private noncopyable
{
  header_holder():member(final().allocate_node()){}
  ~header_holder(){final().deallocate_node(&*member);}

  NodeTypePtr member;

private:
  Final& final(){return *static_cast<Final*>(this);}
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* header_holder.hpp
LcMAffgfT8gDobhmXnoQcOPtKOL+yDfhh+1AKBt3RN3weXZ3ZRwF1b3t7Y2hzj+VAsxIqMTL55rYu4BhWhQFEcmxN/kguJYxmTJHee1PLlhRLBjqAkGQ3SW1VsfiNdNB5zYBCao37sVFMA7GkQ5ktvDuQkSA3RVszTyqsjlhGUaYVIDalUXnAsQAARWhtw29q2nd9dIlBCapy/iL/+4tQ6P9hypn4nsSYAPcsWIwe7puvqA4QvUGik+aQSYB0jjWTxz8RPfXmIcwgC+3aJvD/eG25875YWWJ2UPgYLRIVC+o6viCWQ8rdHegkk3Ty6Rj/kLlzF4NUroUNoVT+xXDFNgJ6io6GFjosAXAJ4HKypBr+BEYnmZmANnFXyYHf5Orx83NcTRdLuNtd7kXErzFkcSIujTKLyj2a00xOlocl7Oq5CKeQ2OMWRDdwhY7Af3sKEyjbZ6hMXa8xdCPlmR6FlPuZg4nIBAC0hLkWySEY1oAMvuFk1n9RE+6A/K1IffP7ADCkPC92PBH2IwTRpNd3bGYKrWUr9wuhaDq446H2XzzO2+KdvQmKfzr9g==
*/