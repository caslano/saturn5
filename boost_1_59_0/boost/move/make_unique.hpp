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

#if defined(_MSC_VER) && (_MSC_VER >= 1915)
   #pragma warning (push)
   #pragma warning (disable : 4643) // Forward declaring 'X' in namespace std is not permitted by the C++ Standard
#endif

namespace std {   //no namespace versioning in clang+libc++

struct nothrow_t;

}  //namespace std {

#if defined(_MSC_VER) && (_MSC_VER >= 1915)
   #pragma warning (pop)
#endif


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