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
   interprocess_exception(const char *err)
      :  m_err(other_error)
   {
      try   {  m_str = err; }
      catch (...) {}
   }

   interprocess_exception(const error_info &err_info, const char *str = 0)
      :  m_err(err_info)
   {
      try{
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
      catch(...){}
   }

   virtual ~interprocess_exception() BOOST_NOEXCEPT_OR_NOTHROW {}

   virtual const char * what() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return m_str.c_str();  }

   native_error_t get_native_error()const { return m_err.get_native_error(); }

   // Note: a value of other_error implies a library (rather than system) error
   error_code_t   get_error_code()  const { return m_err.get_error_code(); }

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
   lock_exception()
      :  interprocess_exception(lock_error)
   {}

   virtual const char* what() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return "boost::interprocess::lock_exception";  }
};


//!This exception is thrown when a memory request can't be
//!fulfilled.
class BOOST_SYMBOL_VISIBLE bad_alloc : public interprocess_exception
{
 public:
   bad_alloc() : interprocess_exception("::boost::interprocess::bad_alloc"){}
   virtual const char* what() const BOOST_NOEXCEPT_OR_NOTHROW
      {  return "boost::interprocess::bad_alloc";  }
};

}  // namespace interprocess {

}  // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_EXCEPTIONS_HPP

/* exceptions.hpp
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
*/