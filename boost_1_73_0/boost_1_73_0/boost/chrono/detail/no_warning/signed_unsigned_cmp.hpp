//  is_evenly_divisible_by.hpp  --------------------------------------------------------------//

//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHRONO_DETAIL_NO_WARNING_SIGNED_UNSIGNED_CMP_HPP
#define BOOST_CHRONO_DETAIL_NO_WARNING_SIGNED_UNSIGNED_CMP_HPP

//
// We simply cannot include this header on gcc without getting copious warnings of the kind:
//
//../../../boost/chrono/detail/no_warning/signed_unsigned_cmp.hpp:37: warning: comparison between signed and unsigned integer expressions
//
// And yet there is no other reasonable implementation, so we declare this a system header
// to suppress these warnings.
//

#if defined(__GNUC__) && (__GNUC__ >= 4)
#pragma GCC system_header
#elif defined __SUNPRO_CC
#pragma disable_warn
#elif defined _MSC_VER
#pragma warning(push, 1)
#endif

namespace boost {
namespace chrono {
namespace detail {

  template <class T, class U>
  bool lt(T t, U u)
  {
    return t < u;
  }

  template <class T, class U>
  bool gt(T t, U u)
  {
    return t > u;
  }

} // namespace detail
} // namespace detail
} // namespace chrono

#if defined __SUNPRO_CC
#pragma enable_warn
#elif defined _MSC_VER
#pragma warning(pop)
#endif

#endif // BOOST_CHRONO_DETAIL_NO_WARNING_SIGNED_UNSIGNED_CMP_HPP

/* signed_unsigned_cmp.hpp
VCXl6wds5D53f+KbY9qfzacj+LU3nPfJFkdb9q4fzYdDLJFeYxFJrw2RbkghXwPyUsYU6dPoHAXb+77eez8w9n/r3U+G/ShRRXRoXPjhZNS0O5eRKNr0sgN/RuD7LtM5/W7ZS3w+bLfc4a+I3xr7bePJbImXGFq7nyX+zMj8CfZAq0PRCHJEiXVA3daB7xh+11vN0l9RUgh/klba70NvmI5xzlxP/xkBLawYJgGnPjhe8CGYD9+/P4FrcvOruPg3UEsDBAoAAAAIAC1nSlJi9+FThwMAAPwHAAAxAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL2N1cmxfZWFzeV9vcHRpb25fYnlfaWQuM1VUBQABtkgkYK1UTW/bOBC961cM1EtSKHI3OWS7DYpVHG8jrGsbltPCgAGBFimLC5oUSMofQH78Dik5jtMUzaEKYknDmTczb94oXoTw/rddQezg4JdX7v9zvPB+CJpo9R8r7OsBef4I7R8GLvD+hlQ9OEY95ufwpqhHOPNReZfrxj3n+RvSLVyR7qfnghe5e0RLG9nF91W913xVWTjrn8MfHz/+CRdw+eHyQwR3RHImILNMLpleRXBDveXviux2sWGfI2AWiIhPAGcVN2BUabdEM8BnwQsmDaNADFBm
*/