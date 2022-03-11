//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_THROW_EXCEPTION_HPP
#define BOOST_CONTAINER_THROW_EXCEPTION_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#ifndef BOOST_NO_EXCEPTIONS
   #include <stdexcept> //for std exception types
   #include <string>    //for implicit std::string conversion
   #include <new>       //for std::bad_alloc
#else
   #include <boost/assert.hpp>
   #include <cstdlib>   //for std::abort
#endif

namespace boost {
namespace container {

#if defined(BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS)
   //The user must provide definitions for the following functions

   void throw_bad_alloc();

   void throw_out_of_range(const char* str);

   void throw_length_error(const char* str);

   void throw_logic_error(const char* str);

   void throw_runtime_error(const char* str);

#elif defined(BOOST_NO_EXCEPTIONS)

   BOOST_NORETURN inline void throw_bad_alloc()
   {
      const char msg[] = "boost::container bad_alloc thrown";
      (void)msg;
      BOOST_ASSERT(!msg);
      std::abort();
   }

   BOOST_NORETURN inline void throw_out_of_range(const char* str)
   {
      const char msg[] = "boost::container out_of_range thrown";
      (void)msg; (void)str;
      BOOST_ASSERT_MSG(!msg, str);
      std::abort();
   }

   BOOST_NORETURN inline void throw_length_error(const char* str)
   {
      const char msg[] = "boost::container length_error thrown";
      (void)msg; (void)str;
      BOOST_ASSERT_MSG(!msg, str);
      std::abort();
   }

   BOOST_NORETURN inline void throw_logic_error(const char* str)
   {
      const char msg[] = "boost::container logic_error thrown";
      (void)msg; (void)str;
      BOOST_ASSERT_MSG(!msg, str);
      std::abort();
   }

   BOOST_NORETURN inline void throw_runtime_error(const char* str)
   {
      const char msg[] = "boost::container runtime_error thrown";
      (void)msg; (void)str;
      BOOST_ASSERT_MSG(!msg, str);
      std::abort();
   }

#else //defined(BOOST_NO_EXCEPTIONS)

   //! Exception callback called by Boost.Container when fails to allocate the requested storage space.
   //! <ul>
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined <code>std::bad_alloc()</code> is thrown.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS is defined and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS
   //!   is NOT defined <code>BOOST_ASSERT(!"boost::container bad_alloc thrown")</code> is called
   //!   and <code>std::abort()</code> if the former returns.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS are defined
   //!   the user must provide an implementation and the function should not return.</li>
   //! </ul>
   BOOST_NORETURN inline void throw_bad_alloc()
   {
      throw std::bad_alloc();
   }

   //! Exception callback called by Boost.Container to signal arguments out of range.
   //! <ul>
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined <code>std::out_of_range(str)</code> is thrown.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS is defined and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS
   //!   is NOT defined <code>BOOST_ASSERT_MSG(!"boost::container out_of_range thrown", str)</code> is called
   //!   and <code>std::abort()</code> if the former returns.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS are defined
   //!   the user must provide an implementation and the function should not return.</li>
   //! </ul>
   BOOST_NORETURN inline void throw_out_of_range(const char* str)
   {
      throw std::out_of_range(str);
   }

   //! Exception callback called by Boost.Container to signal errors resizing.
   //! <ul>
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined <code>std::length_error(str)</code> is thrown.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS is defined and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS
   //!   is NOT defined <code>BOOST_ASSERT_MSG(!"boost::container length_error thrown", str)</code> is called
   //!   and <code>std::abort()</code> if the former returns.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS are defined
   //!   the user must provide an implementation and the function should not return.</li>
   //! </ul>
   BOOST_NORETURN inline void throw_length_error(const char* str)
   {
      throw std::length_error(str);
   }

   //! Exception callback called by Boost.Container  to report errors in the internal logical
   //! of the program, such as violation of logical preconditions or class invariants.
   //! <ul>
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined <code>std::logic_error(str)</code> is thrown.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS is defined and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS
   //!   is NOT defined <code>BOOST_ASSERT_MSG(!"boost::container logic_error thrown", str)</code> is called
   //!   and <code>std::abort()</code> if the former returns.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS are defined
   //!   the user must provide an implementation and the function should not return.</li>
   //! </ul>
   BOOST_NORETURN inline void throw_logic_error(const char* str)
   {
      throw std::logic_error(str);
   }

   //! Exception callback called by Boost.Container  to report errors that can only be detected during runtime.
   //! <ul>
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined <code>std::runtime_error(str)</code> is thrown.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS is defined and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS
   //!   is NOT defined <code>BOOST_ASSERT_MSG(!"boost::container runtime_error thrown", str)</code> is called
   //!   and <code>std::abort()</code> if the former returns.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS are defined
   //!   the user must provide an implementation and the function should not return.</li>
   //! </ul>
   BOOST_NORETURN inline void throw_runtime_error(const char* str)
   {
      throw std::runtime_error(str);
   }

#endif

}}  //namespace boost { namespace container {

#include <boost/container/detail/config_end.hpp>

#endif //#ifndef BOOST_CONTAINER_THROW_EXCEPTION_HPP

/* throw_exception.hpp
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
*/