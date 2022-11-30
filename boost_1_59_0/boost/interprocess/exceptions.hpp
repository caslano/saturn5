//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_EXCEPTIONS_HPP
#define BOOST_INTERPROCESS_EXCEPTIONS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/errors.hpp>
#include <stdexcept>

//!\file
//!Describes exceptions thrown by interprocess classes

namespace boost {

namespace interprocess {

//!This class is the base class of all exceptions
//!thrown by boost::interprocess
class BOOST_SYMBOL_VISIBLE interprocess_exception : public std::exception
{
   public:
   interprocess_exception(const char *err) BOOST_NOEXCEPT
      :  m_err(other_error)
   {
      BOOST_TRY   {  m_str = err; }
      BOOST_CATCH(...) {} BOOST_CATCH_END
   }

   interprocess_exception(const error_info &err_info, const char *str = 0)
      :  m_err(err_info)
   {
      BOOST_TRY{
         if(m_err.get_native_error() != 0){
            fill_system_message(m_err.get_native_error(), m_str);
         }
         else if(str){
            m_str = str;
         }
         else{
            m_str = "boost::interprocess_exception::library_error";
         }
      }
      BOOST_CATCH(...){} BOOST_CATCH_END
   }

   ~interprocess_exception() BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE {}

   const char * what() const BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE
   {  return m_str.c_str();  }

   native_error_t get_native_error() const BOOST_NOEXCEPT { return m_err.get_native_error(); }

   // Note: a value of other_error implies a library (rather than system) error
   error_code_t   get_error_code()  const BOOST_NOEXCEPT { return m_err.get_error_code(); }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   error_info        m_err;
   std::string       m_str;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

//!This is the exception thrown by shared interprocess_mutex family when a deadlock situation
//!is detected or when using a interprocess_condition the interprocess_mutex is not locked
class BOOST_SYMBOL_VISIBLE lock_exception : public interprocess_exception
{
   public:
   lock_exception(error_code_t err = lock_error) BOOST_NOEXCEPT
      :  interprocess_exception(err)
   {}

   const char* what() const BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE
   {  return "boost::interprocess::lock_exception";  }
};


//!This exception is thrown when a memory request can't be
//!fulfilled.
class BOOST_SYMBOL_VISIBLE bad_alloc : public interprocess_exception
{
 public:
   bad_alloc() : interprocess_exception("::boost::interprocess::bad_alloc") {}

   const char* what() const BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE
   {  return "boost::interprocess::bad_alloc";  }
};

}  // namespace interprocess {

}  // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_EXCEPTIONS_HPP

/* exceptions.hpp
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
*/