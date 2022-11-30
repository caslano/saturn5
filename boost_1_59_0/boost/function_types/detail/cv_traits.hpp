
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_DETAIL_CV_TRAITS_HPP_INCLUDED
#define BOOST_FT_DETAIL_CV_TRAITS_HPP_INCLUDED

#include <cstddef>
#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_BORLANDC, <= 0x582)
#   include <boost/type_traits/remove_cv.hpp>
#   include <boost/type_traits/remove_pointer.hpp>
#   include <boost/type_traits/remove_reference.hpp>
#endif

#include <boost/function_types/property_tags.hpp>

namespace boost { namespace function_types { namespace detail {

#if !BOOST_WORKAROUND(BOOST_BORLANDC, <= 0x582)

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