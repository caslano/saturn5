//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_MOVE_MAKE_UNIQUE_HPP_INCLUDED
#define BOOST_MOVE_MAKE_UNIQUE_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>
#include <boost/move/detail/workaround.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/move/unique_ptr.hpp>
#include <cstddef>   //for std::size_t
#include <boost/move/detail/unique_ptr_meta_utils.hpp>
#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
#  include <boost/move/detail/fwd_macros.hpp>
#endif

//!\file
//! Defines "make_unique" functions, which are factories to create instances
//! of unique_ptr depending on the passed arguments.
//!
//! This header can be a bit heavyweight in C++03 compilers due to the use of the
//! preprocessor library, that's why it's a a separate header from <tt>unique_ptr.hpp</tt>
 
#if !defined(BOOST_MOVE_DOXYGEN_INVOKED)

namespace std {   //no namespace versioning in clang+libc++

struct nothrow_t;

}  //namespace std {

namespace boost{
namespace move_upmu {

//Compile time switch between
//single element, unknown bound array
//and known bound array
template<class T>
struct unique_ptr_if
{
   typedef ::boost::movelib::unique_ptr<T> t_is_not_array;
};

template<class T>
struct unique_ptr_if<T[]>
{
   typedef ::boost::movelib::unique_ptr<T[]> t_is_array_of_unknown_bound;
};

template<class T, std::size_t N>
struct unique_ptr_if<T[N]>
{
   typedef void t_is_array_of_known_bound;
};

template <int Dummy = 0>
struct nothrow_holder
{
   static std::nothrow_t *pnothrow;   
};

template <int Dummy>
std::nothrow_t *nothrow_holder<Dummy>::pnothrow = 
   reinterpret_cast<std::nothrow_t *>(0x1234);  //Avoid reference to null errors in sanitizers

}  //namespace move_upmu {
}  //namespace boost{

#endif   //!defined(BOOST_MOVE_DOXYGEN_INVOKED)

namespace boost{
namespace movelib {

#if defined(BOOST_MOVE_DOXYGEN_INVOKED) || !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

//! <b>Remarks</b>: This function shall not participate in overload resolution unless T is not an array.
//!
//! <b>Returns</b>: <tt>unique_ptr<T>(new T(std::forward<Args>(args)...))</tt>.
template<class T, class... Args>
inline BOOST_MOVE_DOC1ST(unique_ptr<T>, 
   typename ::boost::move_upmu::unique_ptr_if<T>::t_is_not_array)
      make_unique(BOOST_FWD_REF(Args)... args)
{  return unique_ptr<T>(new T(::boost::forward<Args>(args)...));  }

//! <b>Remarks</b>: This function shall not participate in overload resolution unless T is not an array.
//!
//! <b>Returns</b>: <tt>unique_ptr<T>(new T(std::nothrow)(std::forward<Args>(args)...))</tt>.
template<class T, class... Args>
inline BOOST_MOVE_DOC1ST(unique_ptr<T>, 
   typename ::boost::move_upmu::unique_ptr_if<T>::t_is_not_array)
      make_unique_nothrow(BOOST_FWD_REF(Args)... args)
{  return unique_ptr<T>(new (*boost::move_upmu::nothrow_holder<>::pnothrow)T(::boost::forward<Args>(args)...));  }

#else
   #define BOOST_MOVE_MAKE_UNIQUE_CODE(N)\
      template<class T BOOST_MOVE_I##N BOOST_MOVE_CLASS##N>\
      typename ::boost::move_upmu::unique_ptr_if<T>::t_is_not_array\
         make_unique( BOOST_MOVE_UREF##N)\
      {  return unique_ptr<T>( new T( BOOST_MOVE_FWD##N ) );  }\
      \
      template<class T BOOST_MOVE_I##N BOOST_MOVE_CLASS##N>\
      typename ::boost::move_upmu::unique_ptr_if<T>::t_is_not_array\
         make_unique_nothrow( BOOST_MOVE_UREF##N)\
      {  return unique_ptr<T>( new (*boost::move_upmu::nothrow_holder<>::pnothrow)T ( BOOST_MOVE_FWD##N ) );  }\
      //
   BOOST_MOVE_ITERATE_0TO9(BOOST_MOVE_MAKE_UNIQUE_CODE)
   #undef BOOST_MOVE_MAKE_UNIQUE_CODE

#endif

//! <b>Remarks</b>: This function shall not participate in overload resolution unless T is not an array.
//!
//! <b>Returns</b>: <tt>unique_ptr<T>(new T)</tt> (default initialization)
template<class T>
inline BOOST_MOVE_DOC1ST(unique_ptr<T>, 
   typename ::boost::move_upmu::unique_ptr_if<T>::t_is_not_array)
      make_unique_definit()
{
    return unique_ptr<T>(new T);
}

//! <b>Remarks</b>: This function shall not participate in overload resolution unless T is not an array.
//!
//! <b>Returns</b>: <tt>unique_ptr<T>(new T(std::nothrow)</tt> (default initialization)
template<class T>
inline BOOST_MOVE_DOC1ST(unique_ptr<T>, 
   typename ::boost::move_upmu::unique_ptr_if<T>::t_is_not_array)
      make_unique_nothrow_definit()
{
    return unique_ptr<T>(new (*boost::move_upmu::nothrow_holder<>::pnothrow)T);
}

//! <b>Remarks</b>: This function shall not participate in overload resolution unless T is an array of 
//!   unknown bound.
//!
//! <b>Returns</b>: <tt>unique_ptr<T>(new remove_extent_t<T>[n]())</tt> (value initialization)
template<class T>
inline BOOST_MOVE_DOC1ST(unique_ptr<T>, 
   typename ::boost::move_upmu::unique_ptr_if<T>::t_is_array_of_unknown_bound)
      make_unique(std::size_t n)
{
    typedef typename ::boost::move_upmu::remove_extent<T>::type U;
    return unique_ptr<T>(new U[n]());
}

//! <b>Remarks</b>: This function shall not participate in overload resolution unless T is an array of 
//!   unknown bound.
//!
//! <b>Returns</b>: <tt>unique_ptr<T>(new (std::nothrow)remove_extent_t<T>[n]())</tt> (value initialization)
template<class T>
inline BOOST_MOVE_DOC1ST(unique_ptr<T>, 
   typename ::boost::move_upmu::unique_ptr_if<T>::t_is_array_of_unknown_bound)
      make_unique_nothrow(std::size_t n)
{
    typedef typename ::boost::move_upmu::remove_extent<T>::type U;
    return unique_ptr<T>(new (*boost::move_upmu::nothrow_holder<>::pnothrow)U[n]());
}

//! <b>Remarks</b>: This function shall not participate in overload resolution unless T is an array of 
//!   unknown bound.
//!
//! <b>Returns</b>: <tt>unique_ptr<T>(new remove_extent_t<T>[n])</tt> (default initialization)
template<class T>
inline BOOST_MOVE_DOC1ST(unique_ptr<T>, 
   typename ::boost::move_upmu::unique_ptr_if<T>::t_is_array_of_unknown_bound)
      make_unique_definit(std::size_t n)
{
    typedef typename ::boost::move_upmu::remove_extent<T>::type U;
    return unique_ptr<T>(new U[n]);
}

//! <b>Remarks</b>: This function shall not participate in overload resolution unless T is an array of 
//!   unknown bound.
//!
//! <b>Returns</b>: <tt>unique_ptr<T>(new (std::nothrow)remove_extent_t<T>[n])</tt> (default initialization)
template<class T>
inline BOOST_MOVE_DOC1ST(unique_ptr<T>, 
   typename ::boost::move_upmu::unique_ptr_if<T>::t_is_array_of_unknown_bound)
      make_unique_nothrow_definit(std::size_t n)
{
    typedef typename ::boost::move_upmu::remove_extent<T>::type U;
    return unique_ptr<T>(new (*boost::move_upmu::nothrow_holder<>::pnothrow) U[n]);
}

#if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)

//! <b>Remarks</b>: This function shall not participate in overload resolution unless T is
//!   an array of known bound.
template<class T, class... Args>
inline BOOST_MOVE_DOC1ST(unspecified, 
   typename ::boost::move_upmu::unique_ptr_if<T>::t_is_array_of_known_bound)
      make_unique(BOOST_FWD_REF(Args) ...) = delete;

//! <b>Remarks</b>: This function shall not participate in overload resolution unless T is
//!   an array of known bound.
template<class T, class... Args>
inline BOOST_MOVE_DOC1ST(unspecified, 
   typename ::boost::move_upmu::unique_ptr_if<T>::t_is_array_of_known_bound)
      make_unique_definit(BOOST_FWD_REF(Args) ...) = delete;

//! <b>Remarks</b>: This function shall not participate in overload resolution unless T is
//!   an array of known bound.
template<class T, class... Args>
inline BOOST_MOVE_DOC1ST(unspecified, 
   typename ::boost::move_upmu::unique_ptr_if<T>::t_is_array_of_known_bound)
      make_unique_nothrow(BOOST_FWD_REF(Args) ...) = delete;

//! <b>Remarks</b>: This function shall not participate in overload resolution unless T is
//!   an array of known bound.
template<class T, class... Args>
inline BOOST_MOVE_DOC1ST(unspecified, 
   typename ::boost::move_upmu::unique_ptr_if<T>::t_is_array_of_known_bound)
      make_unique_nothrow_definit(BOOST_FWD_REF(Args) ...) = delete;

#endif

}  //namespace movelib {

}  //namespace boost{

#include <boost/move/detail/config_end.hpp>

#endif   //#ifndef BOOST_MOVE_MAKE_UNIQUE_HPP_INCLUDED

/* make_unique.hpp
paPOF0uJLGvHgdcRwL+C13+E36GvtSDWLD5Ys1aQiCosN2N8zha2hZIXEIyjjx5FhRW3L1xBF8n2KyvocovXdeNg+RKcj8M9/uF2xcbhhXhs7NzUPSqYdvUZKQBtLpo3k+q0uehON/+ab/CvJdx1b6TYq9NirxWx+CVLa5URUEwAeVqhUEBHE9CsjoC4bmdRiLg+4ppHGgWb2dnfbAAvuJbeuFxhETpPh6I8NJSHuGjVl2BHjqzbtqVeiFQXXN0MOexSJZFfik4CP3dLCzkqmHzLoykagqW8WgQXEOCHbub+ZvN7cjpZDHOJS0uFJFAHVq3jpgThUZLF5KdPCEjGchvHj6wpWUJp5mNfBWGEozGnc9YrvCVLEiUrLFpn3ElA87h3pwOOBmD5Cm/5neyRL2zvnMZ/kdY9cgFYtMIr+9HiUvOFvZIQKExN+eIyc+9GGWIgBAVe/VsZMk07IyRtrU0ycBb9rFwHyhKNqYPBcKL6PYHOU6vWAcIVHxp1CxeDZdEIvF+aEcYQksdPdKaTKFlknVdFSQF+OIXngGS1SF5m/niDFIIvsk5Q6PMF2GEA43JEzH/YYF2BmTvRIrZQC5eNexZIncbqmvJqouaiNqgJ2ykUW1h+f8VY0XVcnthIOhArKKm2B97uz9MoC0G1APGWrKDmqqm9FsWu4e7YRiaVIhMvg3nLV1DDKUL1kpm64cp3Bnozb9vEOypku3TNrUWYfSVwurTVsOBC9vaIp1x1hNE/ahFAOaV6ULfQ5+rlf/16zhVfx49eX71HDAS3gIkFDMG8jb05VqjYrjcKawWIg8+m6VgsmqN44ciLUSxCL6jijsgeUrAZYscdzvkj1pMmlWnEx1rzhXvdvLnhzUkDsZvK3VqtpZk+1hmccT4HuKWeS6NrTk969q8I1mCPz2IDKqmVJRNRXDPbZmGDQnF1ts3B45wzDrPPEygN+hnrPsm1N9bSfCm5XmzvUv9QJAjF8lgqqsuTTWWgIwGa7YXB0WRRcwR7eWk5Oky6aEosaTUgp75pOd0rNndebB4bIK+gI9BsFgp4lDyMbzzPEuKPWB+i5IV6enYuC85VIydK6zktSA2TlEuddlwl8qfbk2INJrLTKJE+HaX3X3pf+st+lP69vBYzME3MduzTvFUpLAo5LvVM/+VB4BuiekjUzcTuWcyXhUKdRmnbPyLxMPPZvfQT40bbL/ozRJL7HmapeqWQaX/6njrpnYzWn42LF9AZKYU9KvzESi2UKBZ3TXDLAiupSQHhLx0XXF91s0WZDu9HtVvebSat35bdPSikCuqxDt+cgQAWoS6+0i1Mt97C+0Q/sjigfluF2Ur+Y1adzPhixybBK3rSD6w0PIxQCkRm92S5exfElZpnicysHmQytZp6K29/E5RAG+s4zzo43k/lWz5+wiDIptP1e7b9GevjBu3uAps/UsfBLsV8l3il3YSxs/n4R11wKw3R1Zk4VBoHZQCzCvaXCXs/2Ga3Pou/cv1+wRYa6Tp3F6Sr/AAX11s7jN28f79DRC30RCBoPZhWbqkPdZ8mgZYvb/sTyTMyjC3UL1HA5p5T0fOZLZwmTUogW9j9J4EsRJ1QlyeJBGoH5aUMSjNFpEGDs3sGqT5yO4bWbGO7xG2eVIG5Axr5MLzT/A6x/IuMXYjFGuCwtNjPMSFMMPYgFuT4fLYz1pUPJmA0KMzvpcXyZAKCdeOuO/1PoORXq9lB9DMiV7lD0XBao2Vt5UZDHu3rq9U+376+2rZ6pa/Wfvq/f6TStx0/8jcHjr/Mai//GlYW9dRkF/hrNrYVX0zyR9w28rjBy1TbrN+Wrjzn7F/foWN7Of7JwNG1xE5MUodEHe9DoIo=
*/