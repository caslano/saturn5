//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_DETAIL_TYPE_TRAITS_HPP
#define BOOST_GIL_CONCEPTS_DETAIL_TYPE_TRAITS_HPP

#include <type_traits>

namespace boost { namespace gil { namespace detail {

// TODO: C++20: deprecate and replace with std::std_remove_cvref
template <typename T>
struct remove_const_and_reference
    : std::remove_const<typename std::remove_reference<T>::type>
{
};

}}} // namespace boost::gil::detail

#endif

/* type_traits.hpp
c8QAaHw6wgpmJmutisc0jQMA3TlJycVkg1d1ElwS61TLj068R1A/QsaXHmmtQLsYOwGY17RRPkGiikRTmv75DP06XQebcf+tXiI7Q774greKJ/NrXsea6/GlMzyYaVDK70MJEM802UPohDSLGDda9woat/3uy1K+WJpKrEF9R6KYIsmBuhPfjDQOxyIQKplpYDmukLmUqOSjSs3oFC91w/TvkDLSQnoqNGyk2oeX07BNW1OYkl75ZDEOx87tWQFBXfuYc/orymKPER66Te9UEhPoWiM56nHynUWzKXQw5IEAJkhJrSP1Oc4iOeqVI+IXW5pErmMr8a5JyYegg9uwQhDE5v0/7PpBhHyeyUdiCZgtHsTY7vqaOhEJKravR2qFvK9CTP/LeRTL3fnL0swdiBGjmEitIGZnbogtC5IHgISVy3ETz7Hwxg6t4+I8fp9UarAw2EGCts+bE/wH3eW6AM/W7p++r8zkIp3kVrG6KLk0PY/toXOT3YkA/22nLoRbVzg2bdhry+mIHSwub9mHzUSeNi8pcbLKBL/+R5hJHsJaTpEzcuHi3EXT9Q==
*/