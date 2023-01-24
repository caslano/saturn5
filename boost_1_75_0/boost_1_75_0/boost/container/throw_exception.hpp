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
WSvMLJIiCrc9+Zf0lm7OtVaoIdORTv9RtK6d5o/q6L1yKvPkhLwsf4DOxFgXsaeUp/8xkBa10M5jq98vnMzqpz//rOIVd6q4OVZHqdQdAXbRH+z2chaO7OTvz17Ww0ZHO618f73oYfmnXswVx+oDnYwkqnbDiN2twkTL/bBf3XJiToRklmkxXO8Fn5M210bcJmAFEHLYL24ai/32edNmYuVmspjdJ9k6vwyhBbm28TlT7DRhAkWQ52gZa7DYzt+Yj0AsS27adrcYE5mc9l/PA8m++z/Ru9O3fPZWFBrvWDz/wRdZZvGYVB0J4UJjGuanGMY4BmaKDxeUMJ29aBdgr6DD7GNtBL8sL0zzSqJT3e8Y3Op2HEgXmehze3ZlouJe94Gv3CQp1JFHbm9O1Uda+DVbqsw9DaNquLynQUCyTrv/qEDjweYxcSWplEgskiNqjnzHp7QmQ+Hab0gOWz3HOB9gDdZ0G9DY5xfkRNzjgfQF0n7zWIy+2wj5pdzo2RuWe8ov7E05tfXs3xLk8wULC8SBmHiiehrg/UNRYq7e0dfmPNWYBGTvqoG5HyPPHrzh/poy8ergILKYLQ6TMtZqs4X6XLUwQuvzYZqjEf5LsRE+qIkPZEMRJAPuh3i5+EDK8kuNiSmlrzGEdfnGQgJgnLvbL+x8XdY3wCN5yzpn/2Sf0R3eopZ4eNWvyh2cMw8sJkeSvtuWI1N3GoVq
*/