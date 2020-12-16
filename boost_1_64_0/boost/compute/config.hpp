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
aaM+AVhAvkmMs/6YQ5qPq4Gsfxrr7+C4GsL7izh/kuPKz7fqXNa/ivlUc3wdyfF1FDCT8d/D8f11wH55kC0kP0mq/bMTBHtg1RZY2omn4/4WYCHQ3168AtfcwMb8Xj1iN74I5QWzHW8bHbXV7MeXXBajLB9k67AduZ8N+TZnP752kG2r25DDfrzDtuOxq/T245tQr99BiYPR56BC0EyQG7QEtBq0DrQJpAyBv09QLmgayAVaDFoFWgtqHWLZm1vBClawghWsYAUrWMEKVrCCFXre/v+Io7vu/0+15+9n4P9/FiiBaLdD7vaBz3d+8eSJB2j9/8f5+f+PbqWNHHWJuFfn/7+0Ve//fwDKHwhKS+y4//84A///ceF6PfwkUHSqorha9W2Q/v/ZBumDh7YpSwT/UMbDlPtEPEr6nvtGY3OSa15Xy9//NuTv//DLRD9nl79zbvrgeQnLhy1/+ZIHH7L8/Wv9/TsVvrN8/5vCaFOtkTd7z3ZOYDyJ/vMHUu48jGd0ZfE8gImUsx8KHCbl0nwn+a76y6XjKZdOpI+SPpRvJ1Hvkkw5eT/Lb7/lt9/y298lv/0l6TalJt2Sb1vBClawghWs0NkQCart9vX/bPiVbpjnkQB0TQbAvf5i9RyhePJV9/qn8nqpuD7Hl8DzAXZIVHz7n8NM9j975AbjiydNPmj/Du7vjplvvt96ndl5BJ7yCjwFdmy/de5883MC8rm/+2aeT3wJaLraZ++L8mbXcp+S2TkBuwm+BsgibEoliLIR3j/UbH8S0weLfEoQzxbxU5QDULd5IKNzA1KAIwXf2cp0USr3Jsn80sz2JjE9k/EwpVDEd/DYaIewNwn36+y0zfcm6XnLuOdnPdLKIrD2U/f8xAyTdt7fcs/PTuS5OAL84ImYaCuCM/QoW3R07HbbRUcI1+jb+WQ0CeD5kfd683oiBPmSud194D6hfIN9QkUG+4RKTfYJlQXxW57D8/ALuV9hLPfNKO9x3BnvmeEZlkDBNwpPXJ5NwXvthn7x95Ppu2NU7iD3cowV16L1/bqV9y942/xQNO01KYM8gvtonLLNQffQkG+k/x4a2SfHi/QDxajme8Z7+prvo5E8e7S7j4Z8un0NfcXeoNm13n5W7X2PFXzzlD7437uXbR369Nk4YBfHaFf2ynifw1X0MbEzx14698o0vcvn0M4+mQsFXzKfC+8z3yfD9OSAfTLfdtM4y+vFzmT78rhPxvUB22e8R0aOo9M+4LfS927x3j5m+2aQbt4HpTI9NSQ/++QNaf8MePXfZb7HSXiP+9lDH2s9sYfG62vfSXHETJ6lX8C/uZvl39z6yjkNdZX802s6Dgf8zd6VgNc1ROGbrQ1JeVmkSVQFQVEERVC8aEJK1ENKrHnRhJRIn+aF2IPat9hrj30nqH2LvfbYiyL2nXzUvv533n/n3fvezL3vJWn5Pnn9Ticzc2bmnDPrnTMzR/C+POvISr+2bs5l/JrCPw3+YpF+ldi5VtrLGCvi1xL+Zpl+deUcWwh/vsDfgPVo4Zd6zq0D7yVus8eO28y51b9U5P2FQjG3riv7V1G+c3705f/37elYbaQ6Wz1G9S50thEOVdo28krMWNXrMVb1xo9VlOXwjlUjNhaW7L2xLqEfOrX3h4oLOh8a82Ru41EDF5S8+/+8NzbB0sPYbCwU8u8asx3z7+nyPhm/9zS2FDah3mgzuNJWgwv+5sTfkvjN1jcDv8OaY+xQt/NeSwfv7RxOvdMRcPeGeyTcIP378d7RIfQfx/jjGR7Rg3EtzPV3c4weDG5nLu/HFMPdlXqqOuqp9oA7kfdh1uc9mY0ZvoUZznJCgCDLmcNysuA2spwg9Ww=
*/