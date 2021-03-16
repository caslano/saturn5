//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_ALLOCATOR_SCOPED_ALLOCATOR_FWD_HPP
#define BOOST_CONTAINER_ALLOCATOR_SCOPED_ALLOCATOR_FWD_HPP

//! \file
//! This header file forward declares boost::container::scoped_allocator_adaptor

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/detail/std_fwd.hpp>
#include <boost/container/uses_allocator_fwd.hpp>

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#endif

namespace boost { namespace container {

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #if !defined(BOOST_CONTAINER_UNIMPLEMENTED_PACK_EXPANSION_TO_FIXED_LIST)

      template <typename OuterAlloc, typename ...InnerAllocs>
      class scoped_allocator_adaptor;

   #else // #if !defined(BOOST_CONTAINER_UNIMPLEMENTED_PACK_EXPANSION_TO_FIXED_LIST)

      template <typename ...InnerAllocs>
      class scoped_allocator_adaptor;

      template <typename OuterAlloc, typename ...InnerAllocs>
      class scoped_allocator_adaptor<OuterAlloc, InnerAllocs...>;

   #endif   // #if !defined(BOOST_CONTAINER_UNIMPLEMENTED_PACK_EXPANSION_TO_FIXED_LIST)

#else    // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   template <typename OuterAlloc, BOOST_MOVE_CLASSDFLT9>
   class scoped_allocator_adaptor;

#endif


#else    //BOOST_CONTAINER_DOXYGEN_INVOKED

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

}} // namespace boost { namespace container {

#include <boost/container/detail/config_end.hpp>

#endif //  BOOST_CONTAINER_ALLOCATOR_SCOPED_ALLOCATOR_FWD_HPP

/* scoped_allocator_fwd.hpp
TrjLI6x02XNyhIbfjuQ5PWaXHqU53YRmH5ifHJLTXWis9VDwZvWTdL/owez7V3eS01No+Csvd7d7KPEFmvOI0PzBTE5PktPrPnJ6Cw08H+tFcvrcR05fZp+fPiSn333kPCo0B5mZn34kp/995OQy+/z0JzkD7iNnoNAcY2Z+BpCcQfeR85jQ+ID1PojkDL6PnCHMvlyDSc7Q+8gZJjTrmXnHMZTkPH4fOX9l9u35cZKTdx85w4UGvl7kkZwR95E=
*/