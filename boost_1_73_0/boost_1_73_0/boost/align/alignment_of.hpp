/*
Copyright 2014-2016 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGNMENT_OF_HPP
#define BOOST_ALIGN_ALIGNMENT_OF_HPP

#include <boost/align/detail/element_type.hpp>
#include <boost/align/alignment_of_forward.hpp>

#if defined(_MSC_VER) && defined(__clang__)
#include <boost/align/detail/alignment_of_cxx11.hpp>
#elif defined(BOOST_MSVC)
#include <boost/align/detail/alignment_of_msvc.hpp>
#elif defined(__GNUC__) && defined(__unix__) && !defined(__LP64__)
#include <boost/align/detail/alignment_of.hpp>
#elif defined(BOOST_CLANG) && !defined(__x86_64__)
#include <boost/align/detail/alignment_of.hpp>
#elif !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <boost/align/detail/alignment_of_cxx11.hpp>
#elif defined(__ghs__) && (__GHS_VERSION_NUMBER >= 600)
#include <boost/align/detail/alignment_of_gcc.hpp>
#elif defined(__CODEGEARC__)
#include <boost/align/detail/alignment_of_codegear.hpp>
#elif defined(BOOST_CLANG)
#include <boost/align/detail/alignment_of_clang.hpp>
#elif __GNUC__ > 4
#include <boost/align/detail/alignment_of_gcc.hpp>
#elif (__GNUC__ == 4) && (__GNUC_MINOR__ >= 3)
#include <boost/align/detail/alignment_of_gcc.hpp>
#else
#include <boost/align/detail/alignment_of.hpp>
#endif

namespace boost {
namespace alignment {

template<class T>
struct alignment_of
    : detail::alignment_of<typename
        detail::element_type<T>::type>::type { };

#if !defined(BOOST_NO_CXX14_VARIABLE_TEMPLATES)
template<class T>
constexpr std::size_t alignment_of_v = alignment_of<T>::value;
#endif

} /* alignment */
} /* boost */

#endif

/* alignment_of.hpp
7gre/tsmX8IiRnul2iUajJ1e7CjzQiEvu/X9hZtP4QeWfrECr1RteqaOBTwe7HkyGuhUmexQ7ThU1/UdkVMr0vtJIedUyioTsmY7AwR0b7sQg227VXHb1yrDhQ1EYY+TiM5fdg8citAXEr9Bz8oe5HToVUKRoDtANjAdTw4f9hQqF7pTDLObaIA90iVa62pe7D0wuy9dXS6KTbhATU7WrYAy1KORn0LhYgk+PiBkg3DWrCrYD2ekpX3evDlgTzrLKWfIEoWQUbYSyIH608BdCXnEAHMMK5exBaz27stcKm1R8tpyaUukrKzopnbrf0pwgooEcxHDhJFei96uirUsgAZ+wVVT1YWECtOERb1OBlIRyN1AE9ppRxhRZnA2MxF+IL9ghFwkrlsBG62TWBu0uXrBPZqtnPJYfWXHdhDObzhMOWgid8kXZatUZZFzDpim5IiXN5CYe2/IYHinf/m/eX/SAqmu8mq6NoRnjEO+zCel3E+qA8ntmIuKAPShCKRclyuJJha3PBp4BRjEvdksIzXhco3Jyys6hPJiYsGnvJyrE7yGJJfPIcPCwK1Kp10MkymgB46c/tarbrlSDRnKcbmkwg0+agt17Ofq3V0tDyWPkKi6LFAVd1287bXe9WVTdL63q3q6okXf2XGQ
*/