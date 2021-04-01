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
ofW3Gbh8E4dAYUynlh8hexEgptJyYaHlLq0+6wyPwo74DyOPZU+qJMJio5Fsk4d7pWy0a6mJJ6jeIQepMQo438Isx4NPJ98NipoLgl1QpzAdqy3orV0p5WvQieQMHdtVAruToeYbbFcfGRWRNkh3GDpaU99Vq9G1x8r6OFmHudSoUk9J1/9y99uFLs12eHOcaJAPgGlNe11q4utUO0FIU3G+olO197lggg8XHSA5Qdv6SIjSo66svA40oMNC3LNfOljPPG82640b8x3sPg5lPRr4sKmNpdkRDZEU6vukpcSzNT6vfQfrAQrDohz3DWxQgBHnDRQ5C7z9K2rCsRb1l0+/JADEwqLl9sk8VQV+NZwbe8AisWz4HQTiT9+llv4R5dhfAvyfZrV0F5ZbwdsOwqk2Fx3AryO5ypiAlJeIwrLTnQSLY8q5z8UOjqixU/X/PUpZWW9dAzrRHoyiJu2/FBgGOCIeUHjACgFdnd+Zt5AUbaxmfS7GDXX4WeymcmuDuBIe0lvkjfLqw2sNWmUOPLCDYU/G7jcYfgYQFeSuXmun1hyEnHXBniLTkw==
*/