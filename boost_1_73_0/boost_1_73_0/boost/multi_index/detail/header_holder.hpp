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
0aurDlxv65nKPP/R8lMi9Gg805jnHo2no2VrOvO4bWbqruJxti1u4Y02Ybqlp5R5uoKQ/u0nQ8+z9cxknl2anlJLz2nMM03yZE56/Ge2ntOZRx9LnGbpmcU8NHOjUc4DeQczbD3cggXqA97IfJalZw7z0JyRRl3nv/LAIVvPXPC3LXMsX8yzeDpYtuYzD7XS5Isev5jytW2Le5PAAfD0zLf0LGSedyRP2egpi209i5jnWU3PQkvPYuaheT/Vz94=
*/