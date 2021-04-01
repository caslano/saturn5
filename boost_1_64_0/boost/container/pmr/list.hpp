//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_LIST_HPP
#define BOOST_CONTAINER_PMR_LIST_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/list.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T>
using list = boost::container::list<T, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a list
//! that uses a polymorphic allocator
template<class T>
struct list_of
{
   typedef boost::container::list
      < T, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_VECTOR_HPP

/* list.hpp
CbZHiCZabpy0AN5BR17djevJ30Yv4YcA/yn0E2U629xMbEP2UPw442xd+yokOUwtI5s+tHf1HFiMO/3UhSszljPc07dvUgmccCnVk3Z3wEgEiNKkjz8tL+uXBNlA3cvYfJngIoXLcDsMeASm7VAjWrsMk9RPscMm/5NeS6QwDuTX+I2o2tUhcUB0YnL1KBEnDxo0kYOSpQd+a9puYQBa3A2aY3gWO7OPFmBphJXCcIPBKfsaErxbGVG7DNemCndvUpvvo7HljxbHkpPs9wwA1k72Fem6Ie1XfOiI5dd1Lq9aOIGqBmRx2gnoTItLdjthNF3sMr950UlhwmIfQSP3rtwnsDhIWnwKndbkvWcS6ovYEj5aGulfa9PK07grMQ8TKHTxNigwXBi83ztKnCFI7LFHG90Ls1wtgl32eDlBuQtLsSpTLhMQyjEfm149e6iMMPxHdF1fIF75YBB4vb+GvQcvtCz1YTcUc1VQSEI6meGgteC1Lu4xwo0uA/BF0XKDs+/yolnIZTo8ldtdx6qyJTs4W3Go89i/kuL0UQcCxXobnqDVzR3pM+1ZyA==
*/