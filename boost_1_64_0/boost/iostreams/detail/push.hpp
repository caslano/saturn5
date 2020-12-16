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
JvYPbtxeE/sTSJf9jUiXePaaCD87+ZOi41rJ/TWuuObnz5w89uz8CfMLV5agIm34evYRccXhaGr8ccBt47OzzxDev3cl3b3Cq3d0sBLe0yFso9VnRPtZS/isIR5+kn/jtZE1pOH518tG5ZOjw3urXRfyCm/JihIGuBUVxdnGwx1dj/mnqgPbNy9euXyROS+LvuP7XPxx1O0zRx0SPzmn/YxIq8Ip0XF/JBNXPePOThxxxhs3nO1V7704lG7D9+IwtUn/qPfiiIzv5jPd8eUcaZ3jFV++Acfbls8ZEn95lWOyjbleq3V1P10C5QJh9i7bdHvC217rzoq217s8R7le9lLle3zPcm4C9sod0vDy/e2e9Zfvx3qvFvOeLF57miS+98pctfdKsx6+uyatmN/m3IcveehQ6kcjjt3eK//tPVbMe5Ecu71XzHvleO/JMrmtff6Z38/+4MfFXQ9+c2vV+D/1/vnHvG7a2ed3vj2n150FD7S6tvVLvvTP7n/caw+d//4eLrH2atnr2Kulv1/2atF/h75FLPGptboZA6L/Vv3E2+GgoPoWoc/zDUH/fZrj7zsd997h+DuAOwVQrZuv/1bjDtXfJyNX6r/VWDzlbxfkNvl7ZJBnW+UlWd9O1tazr/VEgrJO99BAaF39E+HxcCQ8CV4Ex8CT4QR4CpwMR8Oz4QRYCBfBJXAxVLaBa+ASuF7cuQHmwnvgePik3P9rOBG+BCfDd+CZsBZOhQHCOB2mwxnwRDgL5sF8OBueA1fA8+AGOBduhfPhPXABfAQugk/Bi6Btl/56LTW1Xpmyix/pJmlfGgytY18Gw/rVMfSLRX+Z6G/Xa2CRJnKcimwV/VGyPvopsCMcDTvBU2FnmAuPh6fDkXAszIXj4Fg4EU6Fk+B58Aw4D06HC+HZcBGcDC+GU+B6OBPeDGfBW0XvY7gvIGsyyTpW2+EqZA/nLdlnow0sgu1gMWwPS2AGLIVnwTJ4IZzsD60nPwVeLPturIKr4U1yfbNc3yLr1d8Lr4Q/glfDx+GP4bPwAfhrWAlfhrfAV+Bt8E9wMzwIb4d+H88EbAXvgOnwTtgV3g17we/DbFgFh8MfwrPgPTAf3gsL4H1wIbwOLoMb4FZ4PXwM3gifhOP85GM4Hr4NJ8C/w4nwQzgJHoFnwKA/FP9WcApMhZtwJws+CAfDn8FRcCc8Fe6Ck+EjcDZ8FC6Cj8HL4R64Hj4Fb4dPwzvhXng/fBb+BD4Hfwb3wcfFvRfhy/A1+Bt4CP4WNguQh2Fr+AvYCf4SdoO7YX/4OBwC/wpHwb/AsXI8Eb4Jp8IaWCDnl8N34Qb4PtwE34G3wC/gg/Ao/CX8CO6HH8PX4WH4IfwMHpbr/mDofCr8FPaGlp/nBfrgBTAAL4XN4FrYHN4NW8D7YCv4BEyGT8M28FewHfwTTIX/gBnwS9gFJifR1wnbwu6wN+wF+8MsOA72hfkwG5bAgbAcDoKXwSFwE8yBt8Pj4Q/gCPgQPBG+DEfCP8CT4N/hKfBLOAYm8bzmwtZwClT7H/llLRFZB2U7nIVs4zw/jEZ44Ro4CN4Aj4M3wqlwI5wBBwVIN3gzx4thJSyFt8ByuBleCW+Ha+B34SZ4B7wFfg/eBe+C98G74W74A/gkrILV8F74nAof6Q3vgwfgj+Cb8H74NtwOP4Q/hofhT+BX8KfwGxXv0H41D8EU+DDsBH8Ou8JdMBs+AgfDx+AJ8HF4MnwS5sI9cBp8Gl4EfwFL4C/hVfBVuB7+AVbB1+AO+Dp8FP4JVsO/wt/DGvgn+B78GH4IfaRFLUyHH8MM+CnMhJ/BU+DncBz8As6D38AV8A/wBvglvBsehbvhV/Ap+Bz8Ndw=
*/