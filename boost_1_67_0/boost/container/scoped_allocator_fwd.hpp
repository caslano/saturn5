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
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
*/