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
n2CH3TsOImA6mUlN0NjszsNeVF631xugWQnidA2lx82QQdUH+8ME04v9CNOFeDqO16PD7+Ea6UGzkUHQlV1TWnqiB0uVDow8DGVjXJkJ4xybZunMBvOZ0ahkRACx4NEX+cPcioEo4txlhjPuHCy6s+54Tht45pQRF10IgE5bc7pLEBv73Vsc+GoZ6GDWZUSZjGn4eXfUGcxmk5nh4LB9gK4h4X3BcSl93E5KEz2FfCq8F95yOIbCkBvF2+BeVw8udxlH0A6DmSV6w+ntPTEajgcR97BvA2PG0s6c+jt6MRqZIIoZDRs3B4mDLdYYWN9+shj1gxbbR/qO7zB0BgkwHpjcaS1niYEtgHpVpwCLrdmBB/vI4QhsOabpcczbp57Gh0v+9LpGvXf1iO89EKYaHagEwVT0ZOxAKr2Y9yd38cCyyL27Lbu5Q4y13x7ZpB+GTc+Uw9s27aPng7EJTiZ3XBjZD8m3UZtQZBz3sYSFmPM4eh4Lm0akyd1ikP86QphnpAi592OEHheWh3KF0O2y6oKsYHmsXFadyaozWXUmq85knWDQNJfQYrO+Gvx21m+448LNJqUnbnT99Z3LO8oasyfpVbj04cwBkZuDNk7EUXQjCQ7pcZ6Y+uAhs0y6sKel28hANl5WWkKXaoKcsuwNZkYfQjfacDY3NqqRYJPSzkKXpr0cUgw0aSQyU+Z9E5zPfLvRDvr2KwR8g0i5OtARBBqyIVENVNOTvW447LKJRS8aVViueCtNC/cEF+VEVuiA3KcAiseEFBcDkbgYaD+eQYUOBkJaQ5ech06cBwDzy960g2cYde9moLGot6mKOFxIs5CcCCWlQ6Ve2jMyP22VJEHqwXbGKATGrpUYIcJKMyAxD2iCd/YO6s5easJRHax5bXWueYPNrWuZ3cgxi5B5CUPXIWz9BMaIUUQMCo4yla3eCB3mJQ1LBTGxt0sCN+GPuCM0EgF0woimIY9Kr0vCsTZI80W3feoL1KxwmIq4IPX1MFV1QeSwQcpAgEGIsBYxdedEbP2ajd17qslQKLJcdgcByEYIxA8JVqAjBAO49uohk/AgPJutTidMhx3AFkoYXkaI6P7wzimdxqGlpimdxaFREzrP53AxSuk0DqY/uvOgc6cF7VeG8xR3yuhSnHkGRLGWSlu1wA2P27LrbWbEAogRCEArRTRtk9LYLr25qc72xvqNfD4RQD5CSz43v+Kl2YFiv4DK06MPB+je4bL5dPPpnVIwjt7d08v+dZfJDDEg++5HIN1b3RsTYmQYuxCBYRCa0iaGYFlpQ8ywbGg0iKIcTocm1PguVgR9SLMc8QHKmnvC64Q9UX7M1h17o6yk7tJdIq410IeTFWO1PzjE3tSGfaWYufNjzdflz+9kaQPj+cHkcIAzBjro9fkR3fV1F0/O3jFoolGQoo7N8cyYmaRFj11xtQSvrl6mCF/2ciX40lcoxr7s6jHg2ONCGC/tqdl+b/Uyl7qik+dSlFzkXP5yVwgYl77s6uVckste+nJlzuqlLtOS5tKXuvxqmUOBLbld7thlLlPmXEG06FsVk7PNj0ljQbavQNGLDrpz+oolJ9i5DY0t1uQbhWm+kGT0xuyw2SLoI3tpCN59MJusELzjjGLo6jMIztmkI4307Yf7cwkdI2hOsBCf5oLAJdEdgyC+btgMTd4DS3C1Md8AKNLSg1KOFV5AOk+YP3uaHMW6ZGa81p6U2gh1LCFFegFjDN8fBKP+KChyDdkVYtwEDZy9d+E+vNgLglFJvrJ4JNseZG1/HNP636aPNYmwu4im20Y0/TWi6agRTQ+N6P3FGJcJMLYDMusA2/oSdtLIBtyWmer7AEuSJqwHi/6k8ao=
*/