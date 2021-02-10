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
k7v4bZ7vKmLYixI2zW/WIV0Seb8mvDQCqU+DgMo8Yvqy9BPuRz9h+2KOzH1hNoM+erW09KFAc04O3oMp1azXmN/THX3HjGOebVt8oS8AP/6MfRjH+vMAeinYV5h0C0zo5sECk+Ad0GeLD4Wj9XnK7eWj+sl7mKuoVtwhkDeynoB6VLRput2eItB95I2HNsGjqdWlv7D+A1BLAwQKAAAACAAtZ0pSpBiGlJkDAABoBgAALgAJAGN1cmwtbWFzdGVyL3BhY2thZ2VzL3Ztcy9nbnZfY3VybF9jb25maWd1cmUuc2hVVAUAAbZIJGCtVVFv4jgQfl5+xWjbR0Jb7nS6PYkHEwy4Cgkbh7YrrYRMYojVNI4cp8C/v7Gzbene6/FA4sl833wzmZlcwVxV8h841K/bvDPVNtf1Xh06I0dtObgaXME1K679DZcWugZEXYDparClhHdnaHOjGgt7bSBEGmg1OggLykIuatgrRCECaRqjG2lAN1bpuvWIhxUf+RChbs5GHUoL49vbbxDgZXw7hHtd1rAS1ctOmoN3XEvzotoWGcBq6Fo5RC3NeQgvulB7vKLKG2QuVGuN2nVWYnTVoqy9PQrU68KK+uz0dKbRrYSjsiWg1V11h6lICYgopZG7MxyMqK0shk7+qypk
*/