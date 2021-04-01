
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_DETAIL_CLASSIFIER_HPP_INCLUDED
#define BOOST_FT_DETAIL_CLASSIFIER_HPP_INCLUDED

#include <boost/type.hpp>
#include <boost/config.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/add_reference.hpp>

#include <boost/function_types/config/config.hpp>
#include <boost/function_types/property_tags.hpp>

namespace boost { namespace function_types { namespace detail {

template<typename T> struct classifier;

template<std::size_t S> struct char_array { typedef char (&type)[S]; };

template<bits_t Flags, bits_t CCID, std::size_t Arity> struct encode_charr
{
  typedef typename char_array<
    ::boost::function_types::detail::encode_charr_impl<Flags,CCID,Arity>::value 
  >::type type;
};

#if defined(BOOST_MSVC) || (defined(__BORLANDC__) && !defined(BOOST_DISABLE_WIN32))
#   define BOOST_FT_DECL __cdecl
#else
#   define BOOST_FT_DECL /**/
#endif

char BOOST_FT_DECL classifier_impl(...);

#define BOOST_FT_variations BOOST_FT_function|BOOST_FT_pointer|\
                            BOOST_FT_member_pointer

#define BOOST_FT_type_function(cc,name) BOOST_FT_SYNTAX( \
    R BOOST_PP_EMPTY,BOOST_PP_LPAREN,cc,* BOOST_PP_EMPTY,name,BOOST_PP_RPAREN)

#define BOOST_FT_type_function_pointer(cc,name) BOOST_FT_SYNTAX( \
    R BOOST_PP_EMPTY,BOOST_PP_LPAREN,cc,** BOOST_PP_EMPTY,name,BOOST_PP_RPAREN)

#define BOOST_FT_type_member_function_pointer(cc,name) BOOST_FT_SYNTAX( \
    R BOOST_PP_EMPTY,BOOST_PP_LPAREN,cc,T0::** BOOST_PP_EMPTY,name,BOOST_PP_RPAREN)

#define BOOST_FT_al_path boost/function_types/detail/classifier_impl
#include <boost/function_types/detail/pp_loop.hpp>

template<typename T> struct classifier_bits
{
  static typename boost::add_reference<T>::type tester;

  BOOST_STATIC_CONSTANT(bits_t,value = (bits_t)sizeof(
    boost::function_types::detail::classifier_impl(& tester) 
  )-1);
};

template<typename T> struct classifier
{
  typedef detail::constant<
    ::boost::function_types::detail::decode_bits<
      ::boost::function_types::detail::classifier_bits<T>::value
    >::tag_bits > 
  bits;

  typedef detail::full_mask mask;
 
  typedef detail::constant<
    ::boost::function_types::detail::decode_bits<
      ::boost::function_types::detail::classifier_bits<T>::value
    >::arity > 
  function_arity;
};



} } } // namespace ::boost::function_types::detail

#endif


/* classifier.hpp
M5UBfntZJ2u21Q3RBB8hYHzDcojKxTb5pIRaNdLOM/n1IHKlakPklKF6d713lNBKWK7ucZqwKhTnrxf9sbyplllJg3CHgCudXIyTSh2ICs18OhtnzXzqNCJ8D1zbEYYAKNt5jrLXKY2hs8XyFWZA/tja5KKVMGs14uUzruPTvDWy4Q4UNmLUEhks93e4lAaMxvs2D30d8RpdHKZeTpIwn/gSCYOh+s6d9blzPlJ/dYPFYEqZ9IZOvxjhFQe+RamQXypoRXHnProsFKtn4FyvT1n6CflMCamytxyk5Zp84lGizaFhyqu9MSxqoBkHB9R4SrWbMe2sY3x3QfzdjBJ9s/6+RdSqkmZjR0TktrXI/AfUDKWRERPRr14MSSEeKY6slWvCEQr+3r263j8QwcAT9TwwuH575Y77gNPN6T0CJ5ph61O+sRQk31f5iKora0RHIuDEn/nkDxCW4RlhHqAuAG1frHuZ+kdkip1/FQw0vULadLH/kLqsPjmINZ3C32PAoirAO4pk0CyLEkeX7aGKQKgxODIDL0VN+XXJh2xXJgsAulJvl68CdCS1NQ==
*/