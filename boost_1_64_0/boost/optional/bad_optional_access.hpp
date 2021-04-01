// Copyright (C) 2014, Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  akrzemi1@gmail.com
//
#ifndef BOOST_BAD_OPTIONAL_ACCESS_22MAY2014_HPP
#define BOOST_BAD_OPTIONAL_ACCESS_22MAY2014_HPP

#include <stdexcept>
#if __cplusplus < 201103L
#include <string> // to make converting-ctor std::string(char const*) visible
#endif

namespace boost {

#if defined(__clang__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wweak-vtables"
#endif

class bad_optional_access : public std::logic_error
{
public:
  bad_optional_access()
    : std::logic_error("Attempted to access the value of an uninitialized optional object.")
    {}
};

#if defined(__clang__)
# pragma clang diagnostic pop
#endif

} // namespace boost

#endif

/* bad_optional_access.hpp
M7tVcV1kjFrEDW+AyFWBn5piGghuQ3pYKL2YtKoL3TkI6Q0f7amAUoeZMhdA3WrIQMqmdxoFcr5sn6JUp49VeuqpO155csenLI1+Dg/cd/OaZL/YjS35+levP9GT7L4i3WttfCUmMOiZpFCtvRQ/hAPrQRm4AjyZIb2wA1pG9f9DP7YwucHdV/EIwkC4fzkZzdGVkrQbapkGbvrxvbN4lcMocvBrrmDa0/MmQRrhBG63XBmBj3PTKBolIO4Tbb5eGyrUcF8wWd8muMoaRnNwpihMj6f6lcjDLexGwwBkPt5YgMruOxbmb+SZx6axv8r8vtu87TrzWCsWRGeQ3iFNmfSahdg+12F9QmdsxVFnikq/Da4+pdWzqk8BnvWVli6p/pVahhmwD5MbykVtOLmmSSGLkCmSGJb1EH930JaVPipPlvB+eCTDg8ger5+EtCALjyjQ4iqDSQuii25iU+wFUF9DnRq+tGzrTbDnOhyUgPBGeq7OvXYL8Y/WEo8p34dKzHEFgoOvyatsHxsyfjYIyU6NIrF4r+Au1cxv0UlSEd+KvK7SXTu4smwjjQ==
*/