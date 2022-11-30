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
#include <boost/core/ignore_unused.hpp>

#ifndef BOOST_NO_EXCEPTIONS
#include <exception> //for std exception base

#  if defined(BOOST_CONTAINER_USE_STD_EXCEPTIONS)
   #include <stdexcept> //for std::out_of_range, std::length_error, std::logic_error, std::runtime_error
   #include <string>    //for implicit std::string conversion
   #include <new>       //for std::bad_alloc

namespace boost {
namespace container {

typedef std::bad_alloc bad_alloc_t;
typedef std::out_of_range out_of_range_t;
typedef std::length_error length_error_t;
typedef std::logic_error logic_error_t;
typedef std::runtime_error runtime_error_t;

}} //namespace boost::container

#  else	//!BOOST_CONTAINER_USE_STD_EXCEPTIONS

namespace boost {
namespace container {

class BOOST_SYMBOL_VISIBLE exception
   : public ::std::exception
{
   typedef ::std::exception std_exception_t;

   public:

   //msg must be a static string (guaranteed by callers)
   explicit exception(const char *msg)
      : std_exception_t(), m_msg(msg)
   {}

   virtual const char *what() const BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE
   {  return m_msg ? m_msg : "unknown boost::container exception"; }

   private:
   const char *m_msg;
};

class BOOST_SYMBOL_VISIBLE bad_alloc
   : public exception
{
   public:
   bad_alloc()
      : exception("boost::container::bad_alloc thrown")
   {}
};

typedef bad_alloc bad_alloc_t;

class BOOST_SYMBOL_VISIBLE out_of_range
   : public exception
{
   public:
   explicit out_of_range(const char *msg)
      : exception(msg)
   {}
};

typedef out_of_range out_of_range_t;

class BOOST_SYMBOL_VISIBLE length_error
   : public exception
{
   public:
   explicit length_error(const char *msg)
      : exception(msg)
   {}
};

typedef out_of_range length_error_t;

class BOOST_SYMBOL_VISIBLE logic_error
   : public exception
{
   public:
   explicit logic_error(const char *msg)
      : exception(msg)
   {}
};

typedef logic_error logic_error_t;

class BOOST_SYMBOL_VISIBLE runtime_error
   : public exception
{
   public:
   explicit runtime_error(const char *msg)
      : exception(msg)
   {}
};

typedef runtime_error runtime_error_t;

}  // namespace boost {
}  // namespace container {

#  endif
#else
   #include <boost/assert.hpp>
   #include <cstdlib>   //for std::abort
#endif

namespace boost {
namespace container {

#if defined(BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS)
   //The user must provide definitions for the following functions

   BOOST_NORETURN void throw_bad_alloc();

   BOOST_NORETURN void throw_out_of_range(const char* str);

   BOOST_NORETURN void throw_length_error(const char* str);

   BOOST_NORETURN void throw_logic_error(const char* str);

   BOOST_NORETURN void throw_runtime_error(const char* str);

#elif defined(BOOST_NO_EXCEPTIONS)

   BOOST_NORETURN inline void throw_bad_alloc()
   {
      BOOST_ASSERT(!"boost::container bad_alloc thrown");
      std::abort();
   }

   BOOST_NORETURN inline void throw_out_of_range(const char* str)
   {
      boost::ignore_unused(str);
      BOOST_ASSERT_MSG(!"boost::container out_of_range thrown", str);
      std::abort();
   }

   BOOST_NORETURN inline void throw_length_error(const char* str)
   {
      boost::ignore_unused(str);
      BOOST_ASSERT_MSG(!"boost::container length_error thrown", str);
      std::abort();
   }

   BOOST_NORETURN inline void throw_logic_error(const char* str)
   {
      boost::ignore_unused(str);
      BOOST_ASSERT_MSG(!"boost::container logic_error thrown", str);
      std::abort();
   }

   BOOST_NORETURN inline void throw_runtime_error(const char* str)
   {
      boost::ignore_unused(str);
      BOOST_ASSERT_MSG(!"boost::container runtime_error thrown", str);
      std::abort();
   }

#else //defined(BOOST_NO_EXCEPTIONS)

   //! Exception callback called by Boost.Container when fails to allocate the requested storage space.
   //! <ul>
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined and BOOST_CONTAINER_USE_STD_EXCEPTIONS is NOT defined
   //!   <code>boost::container::bad_alloc(str)</code> is thrown.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined and BOOST_CONTAINER_USE_STD_EXCEPTIONS is defined
   //!   <code>std::bad_alloc(str)</code> is thrown.</li>
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
      throw bad_alloc_t();
   }

   //! Exception callback called by Boost.Container to signal arguments out of range.
   //! <ul>
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined and BOOST_CONTAINER_USE_STD_EXCEPTIONS is NOT defined
   //!   <code>boost::container::out_of_range(str)</code> is thrown.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined and BOOST_CONTAINER_USE_STD_EXCEPTIONS is defined
   //!   <code>std::out_of_range(str)</code> is thrown.</li>
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
      throw out_of_range_t(str);
   }

   //! Exception callback called by Boost.Container to signal errors resizing.
   //! <ul>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined and BOOST_CONTAINER_USE_STD_EXCEPTIONS is NOT defined
   //!   <code>boost::container::length_error(str)</code> is thrown.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined and BOOST_CONTAINER_USE_STD_EXCEPTIONS is defined
   //!   <code>std::length_error(str)</code> is thrown.</li>
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
      throw length_error_t(str);
   }

   //! Exception callback called by Boost.Container  to report errors in the internal logical
   //! of the program, such as violation of logical preconditions or class invariants.
   //! <ul>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined and BOOST_CONTAINER_USE_STD_EXCEPTIONS is NOT defined
   //!   <code>boost::container::logic_error(str)</code> is thrown.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined and BOOST_CONTAINER_USE_STD_EXCEPTIONS is defined
   //!   <code>std::logic_error(str)</code> is thrown.</li>
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
      throw logic_error_t(str);
   }

   //! Exception callback called by Boost.Container  to report errors that can only be detected during runtime.
   //! <ul>
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined and BOOST_CONTAINER_USE_STD_EXCEPTIONS is NOT defined
   //!   <code>boost::container::runtime_error(str)</code> is thrown.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined and BOOST_CONTAINER_USE_STD_EXCEPTIONS is defined
   //!   <code>std::runtime_error(str)</code> is thrown.</li>
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
      throw runtime_error_t(str);
   }

#endif

}}  //namespace boost { namespace container {

#include <boost/container/detail/config_end.hpp>

#endif //#ifndef BOOST_CONTAINER_THROW_EXCEPTION_HPP

/* throw_exception.hpp
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
*/