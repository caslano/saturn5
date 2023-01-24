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
bQ2U7J94M2eV/UgDZad65sFkuf5p45MO7jnO3r0F4cNYS9NSatb+r/b1C6k78wnXNJdoTdqUgvHJnOyR+4L69lnB0dG0B7wpx/FYXqGi5PgS1tNSr3lB9gzBQXFhyX+X9UUNE/u46vX+Bxp42/SuqKcULZXUB4erm1ehP8uXEtPe68Er2aYotkP5t4tK9VWxoY7SXc4mIvuRTApO7VkN+2mFPc3pF2uKvjzLu0rCfu9Mbz2S2suPvgqMadJYRdTiZr5ZfP/SAMydz4sjUOKgtE48BX++P6d9baqj71J2pC11lJenX1QB/uaXas+l43WOV4wDEzpNvR68xum7GonDY9JJY1apmCdVrzzFw4az0Zp06fj3dtPK0xagfYJ3vAxmmp+t6WoLScqazxE1TLk4Zp/yZ/9RUVH+qqTPp3kYxt/J6+P6enFDoA/L9tLsTePOvp2vqrBv78njWD68U64qylm0XHvfiQVooa7VhlzrSS4O9K48Mz9JhKclt+LTJKjF49YaFa4VvtH0duDcclCkolj4I2lSWUZ5h5qtDYf2m/IZ4d1Nh/++AP0XiX9BlP/XC0oX5XdtxWmmeFl5e03Zt8WUddCWl4eJYhHsfhnoj/Qb1BNPNan+JwSt1E6qmdrf72l6LdKoeiBYN8e0LVrzPVnk2zLtNrX5PAyko3XcGcB8KFpYj9QYQnXZNvrw3juePXlHTUWkte8j1r7Y
*/