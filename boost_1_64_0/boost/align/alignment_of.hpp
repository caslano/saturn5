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
zF6v2hui8SQgcD4NU+S0hWcniunoUpdeY7ycfs1TfTqIRlJG9pW53gU9OVt3cd+TLIKW12J/maBeOIvl8Gd0ronNhavefmpXsDuyPQX6iB71d8Wq/JkA41+4qrhR7/j9rHc+pAgCkOac6/YRe32OJq7dHxokmxWnOjWxDZxpjTTmUxmHq+E4QGXeV3CJoqeFmjmNPFv3Oot9xY2q+wLuSdEj35V+58XEiV39JaqlIw8GlyLI2gW5UdkGZ04MSmdzVAwLHRl5UxHKCjaOpor63PB4D/QrgMg59wlFTKV4CgNkPAX3EoJrBOIVah/9MbU4MXVcH0RzDzXTNSK4gCCEC7v7baqctTfTntX5enLrActi1Ppwt3xWcUBGK7mvXpHulTz7s5B8oDJkLmN/UkU0eDE9yVXrjbyXr6OfrhcIr68OCYIOQgGQMRZB4JDUNJFnx/vc2FrAHTLlG6IxkCX5BsYqTOtp6XXhkNcUv9lBvNIUsNhjdE9c1b+o0wJ+Y/75tBnJ8CGufOfYg1iG74m+A32ymgYnrd0bOISBQYS96ZUkwL2HWOtgspe0Ig==
*/