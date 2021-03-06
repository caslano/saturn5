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
7VdshlEydh0ZP02crppkpP3ZeUNyTTjn3iogdEIpKHVAzUAAh5Q+SkMlI+7XXs1N70Z2JJLYF4cp3X53xe9DxbUCEImW/IPeB6Rc5dubtVlB+dWA8inEFdYqWIfpPl99scYv+l4aRZ0P57GCvAiJjo5WaxDc52YTwy7hyCoHsVyIPRG0/5UHzhN7e1FF8ZZoqUZkA5jABfoy93bdtHIpdymRIXSmqvOej+G8K7C0+WnpMLGRgKtEkIO78Jw5pC+iX7XInfyxxc/okvYGnAAxMVBD/Ebldy69wEdsQGsAxRr4ulZfXraVkY+V6epN4k9/BrfOREX7P9wU3kRDHGRrTb/XJO+xSVP+mQzQnOUDv2HkpUS7+em8CGnaD6lpbHRBISRK5xKz4sYK/aBB4/qwjC5LQqvvr5OVwgR8ZNhSguIWDTznRQkpHjU2xZOUOHm82NhCngjSuoiFvVa9STq8KKft7gBXXYZS6VvzT3xwCIH/aB0fCB6QEle/X5YUSggArlyAhiAUekT402ecCQc+4wpa+i/KLQ5npXhgNnFIC71WudVFoYD+aZiOrQ==
*/