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
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
*/