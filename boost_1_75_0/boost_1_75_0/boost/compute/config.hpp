//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CONFIG_HPP
#define BOOST_COMPUTE_CONFIG_HPP

#include <boost/config.hpp>
#include <boost/version.hpp>
#include <boost/compute/cl.hpp>

// check for minimum required boost version
#if BOOST_VERSION < 105400
#error Boost.Compute requires Boost version 1.54 or later
#endif

// the BOOST_COMPUTE_NO_VARIADIC_TEMPLATES macro is defined
// if the compiler does not *fully* support variadic templates
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || \
    (defined(__GNUC__) && !defined(__clang__) && \
     __GNUC__ == 4 && __GNUC_MINOR__ <= 6)
  #define BOOST_COMPUTE_NO_VARIADIC_TEMPLATES
#endif // BOOST_NO_CXX11_VARIADIC_TEMPLATES

// the BOOST_COMPUTE_NO_STD_TUPLE macro is defined if the
// compiler/stdlib does not support std::tuple
#if defined(BOOST_NO_CXX11_HDR_TUPLE) || \
    defined(BOOST_COMPUTE_NO_VARIADIC_TEMPLATES)
  #define BOOST_COMPUTE_NO_STD_TUPLE
#endif // BOOST_NO_CXX11_HDR_TUPLE

// defines BOOST_COMPUTE_CL_CALLBACK to the value of CL_CALLBACK
// if it is defined (it was added in OpenCL 1.1). this is used to
// annotate certain callback functions registered with OpenCL
#ifdef CL_CALLBACK
#  define BOOST_COMPUTE_CL_CALLBACK CL_CALLBACK
#else
#  define BOOST_COMPUTE_CL_CALLBACK
#endif

// Maximum number of iterators acceptable for make_zip_iterator
#ifndef BOOST_COMPUTE_MAX_ARITY
   // should be no more than max boost::tuple size (10 by default)
#  define BOOST_COMPUTE_MAX_ARITY 10
#endif

#if !defined(BOOST_COMPUTE_DOXYGEN_INVOKED) && \
    defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#  define BOOST_COMPUTE_NO_RVALUE_REFERENCES
#endif // BOOST_NO_CXX11_RVALUE_REFERENCES

#if defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#  define BOOST_COMPUTE_NO_HDR_INITIALIZER_LIST
#endif // BOOST_NO_CXX11_HDR_INITIALIZER_LIST

#if defined(BOOST_NO_CXX11_HDR_CHRONO)
#  define BOOST_COMPUTE_NO_HDR_CHRONO
#endif // BOOST_NO_CXX11_HDR_CHRONO

#endif // BOOST_COMPUTE_CONFIG_HPP

/* config.hpp
WPOMsN6lwZp+izlorwQmg2o0KESvj9ImgwosoYzrUDcPZDQPYHlmKsloni6jeenoJ2MrvVvsgPTj0zMbPAfA6hPidhYycYWAX2r5Yj5OkjoG0YGgBhtl0aWCDfmQCA/iVCm+JMggNiS5oHS3rWQijqHUuZVHxBOtZGCXc2rA18RICbX4PFLJf2oNdGQvyRd6srHe5v0cZzUtSJEcfwrnrxfYj56fYXWbd56JEMvnSOWzoVV5IsoE42rRFGg+HwdWxD/+lFpV+zodEDBIVxbM3POIxIxtE09Y2LS0JLka5008OsBG/R8F7+b0ELyb3oOGnDdupmsd4+Uq6Dns/tgtmNVbpOwB/PO5gwonz6HzlFNwMddEmyuZJyB/0xIqEdXGsmpEoejFfpoLM9FFp4wJFswnQIe0rcqeNudUAuvnNN5fRWzEIVzFoEhj0RMtmlRB0Db0APpBEyzd9SdjSn3XHyFYnVC5+MlWcjneqLaSzhZiRB7sToFs4hYV7lvZLDR7FSp3X44bd0B/kol8LmFJUO+kGYUhn+pe1pnER1RlE21WchE8Z9VJLYT88/LvPd3JuTbv91wQCrLkMxi96m6QF1JEC7Q3XkISsBI29SrzTOAlZCtdgNI1HV85i2Ztss/AT6fPBkBgGrRmqt3+uJVaAdama6xN5awFuGPOEV+16ItKwTHiK5Zgnfl1ZlO5JofNON0wz0tFzQsm6oWU
*/