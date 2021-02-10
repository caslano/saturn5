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
BQABtkgkYK1UbW+bSBD+zq8YcdLJjihO2p5yvaTVUYc2KC74ADdnyRJawxL2hHcpuyS2Lv3vN7vg+nK5qPlQLHtfPPPMM8/M4K5sOPphj+VqOPjuk5lvhg+ue6d5K/6iufp/hyy7h/6DjitcnxFqAgev+2wMz/K6h5HxyoZY53qfZc8It9Ik9c9EO68yvcWb3nPwn4pm17KbSsFoOoaTN29+hRfw8vjk1IELwhmtIVGUr2l748B5YW5+r8h260r6zgGqgNTuA8C0YhKkKNUdaSngvmY55ZIWQCQUVOYtW+OBcVAVhZLVFKbRfBmEHx24q1heDTg70YGsRFcXUJFbCi3NKbvtYRrSKhAlIiB+waRCzE4xwV0MT0HRdiMHGE2C1FIAuSWsJmsMRxRUSjXyt8kk79oaM5kUIpeTfC+FW6nNf7JaIpsN2YFoFCgBnaQOaHsHNqJgpV5RIrxsunXNZOUcaGFAXkxEC5LW9QCHrozKPgUKyaCWoy2hQfZM6UUKLnW0u0psHhiirANQ2bUcw6EsaFcIFN6Bjhe0NfZGiH2UQWUj+XdKduBegODICmwvgSCxYU0kkw5cB+lltEjh2otjL0yXEH0AL1wOeFdBeIG9wTBqC3TbtFQiixbYpqkZLR4E/6GTbrnpJUwX
*/