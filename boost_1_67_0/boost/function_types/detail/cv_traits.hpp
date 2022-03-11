
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_DETAIL_CV_TRAITS_HPP_INCLUDED
#define BOOST_FT_DETAIL_CV_TRAITS_HPP_INCLUDED

#include <cstddef>
#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, <= 0x582)
#   include <boost/type_traits/remove_cv.hpp>
#   include <boost/type_traits/remove_pointer.hpp>
#   include <boost/type_traits/remove_reference.hpp>
#endif

#include <boost/function_types/property_tags.hpp>

namespace boost { namespace function_types { namespace detail {

#if !BOOST_WORKAROUND(__BORLANDC__, <= 0x582)

template<typename T> struct cv_traits 
{ typedef non_cv tag; typedef T type; };
template<typename T> struct cv_traits<T &>     
{ typedef non_cv tag; typedef T type; };
template<typename T> struct cv_traits<T *>    
{ typedef non_cv tag; typedef T type; };
template<typename T> struct cv_traits<T * const> 
{ typedef non_cv tag; typedef T type; };
template<typename T> struct cv_traits<T * volatile> 
{ typedef non_cv tag; typedef T type; };
template<typename T> struct cv_traits<T * const volatile> 
{ typedef non_cv tag; typedef T type; };

template<typename T> struct cv_traits<T const> 
{ typedef const_non_volatile tag; typedef T type; };
template<typename T> struct cv_traits<T const &>
{ typedef const_non_volatile tag; typedef T type; };
template<typename T> struct cv_traits<T const *> 
{ typedef const_non_volatile tag; typedef T type; };
template<typename T> struct cv_traits<T const * const> 
{ typedef const_non_volatile tag; typedef T type; };
template<typename T> struct cv_traits<T const * volatile> 
{ typedef const_non_volatile tag; typedef T type; };
template<typename T> struct cv_traits<T const * const volatile> 
{ typedef const_non_volatile tag; typedef T type; };

template<typename T> struct cv_traits<T volatile>  
{ typedef volatile_non_const tag; typedef T type; };
template<typename T> struct cv_traits<T volatile &>  
{ typedef volatile_non_const tag; typedef T type; };
template<typename T> struct cv_traits<T volatile *> 
{ typedef volatile_non_const tag; typedef T type; };
template<typename T> struct cv_traits<T volatile * const> 
{ typedef volatile_non_const tag; typedef T type; };
template<typename T> struct cv_traits<T volatile * volatile> 
{ typedef volatile_non_const tag; typedef T type; };
template<typename T> struct cv_traits<T volatile * const volatile> 
{ typedef volatile_non_const tag; typedef T type; };

template<typename T> struct cv_traits<T const volatile>   
{ typedef cv_qualified tag; typedef T type; };
template<typename T> struct cv_traits<T const volatile &>
{ typedef cv_qualified tag; typedef T type; };
template<typename T> struct cv_traits<T const volatile *>
{ typedef cv_qualified tag; typedef T type; };
template<typename T> struct cv_traits<T const volatile * const>
{ typedef cv_qualified tag; typedef T type; };
template<typename T> struct cv_traits<T const volatile * volatile>
{ typedef cv_qualified tag; typedef T type; };
template<typename T> struct cv_traits<T const volatile * const volatile>
{ typedef cv_qualified tag; typedef T type; };

#else
template<std::size_t> struct cv_tag_impl;

template<> struct cv_tag_impl<1> { typedef non_cv type;};
template<> struct cv_tag_impl<2> { typedef const_non_volatile type; };
template<> struct cv_tag_impl<3> { typedef volatile_non_const type; };
template<> struct cv_tag_impl<4> { typedef cv_qualified type; };

typedef char (& case_1)[1];
typedef char (& case_2)[2];
typedef char (& case_3)[3];
typedef char (& case_4)[4];

template<typename T> case_1 switch_cv(T *);
template<typename T> case_2 switch_cv(T const *);
template<typename T> case_3 switch_cv(T volatile *);
template<typename T> case_4 switch_cv(T const volatile *);

template<typename T> T                * ref_to_ptr(T &);
template<typename T> T const          * ref_to_ptr(T const &);
template<typename T> T volatile       * ref_to_ptr(T volatile &);
template<typename T> T const volatile * ref_to_ptr(T const volatile &);

template<typename T> T                * ref_to_ptr(T * const volatile &);

template<typename T>
struct cv_code
{
  static T _t;
  BOOST_STATIC_CONSTANT(std::size_t, value = 
      sizeof(::boost::function_types::detail::switch_cv(
         ::boost::function_types::detail::ref_to_ptr(_t) ) ));
};

template<typename T> struct cv_traits 
{
  typedef typename boost::function_types::detail::cv_tag_impl< 
    ::boost::function_types::detail::cv_code<T>::value >::type
  tag;

  // may require Boost.TypeTraits broken compiler specializations
  // to work
  typedef typename boost::remove_cv<
              typename boost::remove_pointer<
                  typename boost::remove_reference<T>::type 
              >::type 
          >::type type; 
};
#endif

} } } // namespace boost::function_types::detail

#endif
 

/* cv_traits.hpp
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
*/