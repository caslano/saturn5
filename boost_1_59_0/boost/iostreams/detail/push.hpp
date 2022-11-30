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

#if !BOOST_WORKAROUND(BOOST_BORLANDC, < 0x600) \
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