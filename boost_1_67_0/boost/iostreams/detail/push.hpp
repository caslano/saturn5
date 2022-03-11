// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_PUSH_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_PUSH_HPP_INCLUDED 

#if defined(_MSC_VER)
# pragma once
#endif                    
 
#include <boost/config.hpp> // BOOST_MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/adapter/range_adapter.hpp>
#include <boost/iostreams/detail/config/wide_streams.hpp>
#include <boost/iostreams/detail/enable_if_stream.hpp>   
#include <boost/iostreams/pipeline.hpp>   
#include <boost/iostreams/detail/push_params.hpp>   
#include <boost/iostreams/detail/resolve.hpp>
#include <boost/mpl/bool.hpp>   
#include <boost/preprocessor/cat.hpp> 
#include <boost/preprocessor/control/iif.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

//
// Macro: BOOST_IOSTREAMS_DEFINE_PUSH_CONSTRUCTOR(name, mode, ch, helper).
// Description: Defines overloads with name 'name' which forward to a function
//      'helper' which takes a filter or devide by const reference.
//
#define BOOST_IOSTREAMS_DEFINE_PUSH_CONSTRUCTOR(name, mode, ch, helper) \
    BOOST_IOSTREAMS_DEFINE_PUSH_IMPL(name, mode, ch, helper, 0, ?) \
    /**/

//
// Macro: BOOST_IOSTREAMS_DEFINE_PUSH(name, mode, ch, helper).
// Description: Defines constructors which forward to a function
//      'helper' which takes a filter or device by const reference.
//
#define BOOST_IOSTREAMS_DEFINE_PUSH(name, mode, ch, helper) \
    BOOST_IOSTREAMS_DEFINE_PUSH_IMPL(name, mode, ch, helper, 1, void) \
    /**/

//--------------------Definition of BOOST_IOSTREAMS_DEFINE_PUSH_IMPL----------//
          
#define BOOST_IOSTREAMS_ADAPT_STREAM(mode, ch, arg, helper, has_return) \
    this->helper( ::boost::iostreams::detail::resolve<mode, ch>(arg) \
                  BOOST_IOSTREAMS_PUSH_ARGS() ); \
    /**/

#if !BOOST_WORKAROUND(__BORLANDC__, < 0x600) \
    /**/
# ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
#  define BOOST_IOSTREAMS_DEFINE_PUSH_IMPL(name, mode, ch, helper, has_return, result) \
    template<typename CharType, typename TraitsType> \
    BOOST_PP_IIF(has_return, result, explicit) \
    name(::std::basic_streambuf<CharType, TraitsType>& sb BOOST_IOSTREAMS_PUSH_PARAMS()) \
    { BOOST_IOSTREAMS_ADAPT_STREAM(mode, ch, sb, helper, has_return); } \
    template<typename CharType, typename TraitsType> \
    BOOST_PP_IIF(has_return, result, explicit) \
    name(::std::basic_istream<CharType, TraitsType>& is BOOST_IOSTREAMS_PUSH_PARAMS()) \
    { BOOST_STATIC_ASSERT((!is_convertible<mode, output>::value)); \
      BOOST_IOSTREAMS_ADAPT_STREAM(mode, ch, is, helper, has_return); } \
    template<typename CharType, typename TraitsType> \
    BOOST_PP_IIF(has_return, result, explicit) \
    name(::std::basic_ostream<CharType, TraitsType>& os BOOST_IOSTREAMS_PUSH_PARAMS()) \
    { BOOST_STATIC_ASSERT((!is_convertible<mode, input>::value)); \
      BOOST_IOSTREAMS_ADAPT_STREAM(mode, ch, os, helper, has_return); } \
    template<typename CharType, typename TraitsType> \
    BOOST_PP_IIF(has_return, result, explicit) \
    name(::std::basic_iostream<CharType, TraitsType>& io BOOST_IOSTREAMS_PUSH_PARAMS()) \
    { BOOST_IOSTREAMS_ADAPT_STREAM(mode, ch, io, helper, has_return); } \
    template<typename Iter> \
    BOOST_PP_IIF(has_return, result, explicit) \
    name(const iterator_range<Iter>& rng BOOST_IOSTREAMS_PUSH_PARAMS()) \
    { BOOST_PP_EXPR_IF(has_return, return) \
    this->helper( ::boost::iostreams::detail::range_adapter< \
                      mode, iterator_range<Iter> \
                  >(rng) \
                  BOOST_IOSTREAMS_PUSH_ARGS() ); } \
    template<typename Pipeline, typename Concept> \
    BOOST_PP_IIF(has_return, result, explicit) \
    name(const ::boost::iostreams::pipeline<Pipeline, Concept>& p) \
    { p.push(*this); } \
    template<typename T> \
    BOOST_PP_IIF(has_return, result, explicit) \
    name(const T& t BOOST_IOSTREAMS_PUSH_PARAMS() BOOST_IOSTREAMS_DISABLE_IF_STREAM(T)) \
    { this->helper( ::boost::iostreams::detail::resolve<mode, ch>(t) \
                    BOOST_IOSTREAMS_PUSH_ARGS() ); } \
    /**/
# else // # ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
#  define BOOST_IOSTREAMS_DEFINE_PUSH_IMPL(name, mode, ch, helper, has_return, result) \
    BOOST_PP_IF(has_return, result, explicit) \
    name(::std::streambuf& sb BOOST_IOSTREAMS_PUSH_PARAMS()) \
    { BOOST_IOSTREAMS_ADAPT_STREAM(mode, ch, sb, helper, has_return); } \
    BOOST_PP_IF(has_return, result, explicit) \
    name(::std::istream& is BOOST_IOSTREAMS_PUSH_PARAMS()) \
    { BOOST_STATIC_ASSERT((!is_convertible<mode, output>::value)); \
      BOOST_IOSTREAMS_ADAPT_STREAM(mode, ch, is, helper, has_return); } \
    BOOST_PP_IF(has_return, result, explicit) \
    name(::std::ostream& os BOOST_IOSTREAMS_PUSH_PARAMS()) \
    { BOOST_STATIC_ASSERT((!is_convertible<mode, input>::value)); \
      BOOST_IOSTREAMS_ADAPT_STREAM(mode, ch, os, helper, has_return); } \
    BOOST_PP_IF(has_return, result, explicit) \
    name(::std::iostream& io BOOST_IOSTREAMS_PUSH_PARAMS()) \
    { BOOST_IOSTREAMS_ADAPT_STREAM(mode, ch, io, helper, has_return); } \
    template<typename Iter> \
    BOOST_PP_IF(has_return, result, explicit) \
    name(const iterator_range<Iter>& rng BOOST_IOSTREAMS_PUSH_PARAMS()) \
    { BOOST_PP_EXPR_IF(has_return, return) \
    this->helper( ::boost::iostreams::detail::range_adapter< \
                      mode, iterator_range<Iter> \
                  >(rng) \
                  BOOST_IOSTREAMS_PUSH_ARGS() ); } \
    template<typename Pipeline, typename Concept> \
    BOOST_PP_IF(has_return, result, explicit) \
    name(const ::boost::iostreams::pipeline<Pipeline, Concept>& p) \
    { p.push(*this); } \
    template<typename T> \
    BOOST_PP_EXPR_IF(has_return, result) \
    name(const T& t BOOST_IOSTREAMS_PUSH_PARAMS() BOOST_IOSTREAMS_DISABLE_IF_STREAM(T)) \
    { this->helper( ::boost::iostreams::detail::resolve<mode, ch>(t) \
                    BOOST_IOSTREAMS_PUSH_ARGS() ); } \
    /**/
# endif // # ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
#else // #if VC6, VC7.0, Borland 5.x
# define BOOST_IOSTREAMS_DEFINE_PUSH_IMPL(name, mode, ch, helper, has_return, result) \
    template<typename T> \
    void BOOST_PP_CAT(name, _msvc_impl) \
    ( ::boost::mpl::true_, const T& t BOOST_IOSTREAMS_PUSH_PARAMS() ) \
    { t.push(*this); } \
    template<typename T> \
    void BOOST_PP_CAT(name, _msvc_impl) \
    ( ::boost::mpl::false_, const T& t BOOST_IOSTREAMS_PUSH_PARAMS() ) \
    { this->helper( ::boost::iostreams::detail::resolve<mode, ch>(t) \
                    BOOST_IOSTREAMS_PUSH_ARGS() ); } \
    template<typename T> \
    BOOST_PP_IF(has_return, result, explicit) \
    name(const T& t BOOST_IOSTREAMS_PUSH_PARAMS()) \
    { \
        this->BOOST_PP_CAT(name, _msvc_impl) \
              ( ::boost::iostreams::detail::is_pipeline<T>(), \
                t BOOST_IOSTREAMS_PUSH_ARGS() ); \
    } \
    /**/
#endif // #if VC6, VC7.0, Borland 5.x

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_PUSH_HPP_INCLUDED

/* push.hpp
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
*/