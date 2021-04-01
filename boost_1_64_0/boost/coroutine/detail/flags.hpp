
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_FLAGS_H
#define BOOST_COROUTINES_DETAIL_FLAGS_H

#include <boost/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

enum flag_t
{
    flag_started        = 1 << 1,
    flag_running        = 1 << 2,
    flag_complete       = 1 << 3,
    flag_unwind_stack   = 1 << 4,
    flag_force_unwind   = 1 << 5
};

struct unwind_t
{
    enum flag_t
    { force_unwind = 1 };
};

struct synthesized_t
{
    enum flag_t
    { syntesized = 1 };
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_FLAGS_H

/* flags.hpp
YLtVnWJhPZccJvnJI6X5m7dsvVh5pL6e93jqXUjwM9wmHzJJNLyTglnScPfBEAfB0gfBxJbO4wLwKSF6A6YMq5o15M3ga1FCGmJKY18nYYUbhmouSy0Z7qwHVrjTiLn7ZDls9Kd1gb6XESxD530RaM6UiqpRcy3v5Kum/iNq6mXiZ0Ck1tfAFqeBE0QcXynWCz6AtU752lyWXePrW+MYX+KDMlcB3cnhcTjM+t6Aoi6fq05KjAax6BMW6tHCfBULLIFNJ3+FZVgzsSW8EmvMnfoM3KOM+rQaE2O2i+k679YCqg46bvWLD9CEwT+7ACHLRAHhpyNkxMLSBZLAfCrU+VHzrGEH9nE95diS9uuSBHLnbMMoCQ1lpnSbU9v0eYUMpctJm8u91shs2tBunmPkEmfgeIa9I+87Ek4D0HJe0Gyy2JXrvCJxtkqndHXL2T3HYjKYvSTrJ89Ro20nazJJTo6u2GstKoE5HKfgkfEo7jZkR+VGJMFZoQmkNEHyVMBkJWVhgONu1vjLVaCjPELWS6jbzuhj/ykQMEc0EBa8hO/vT6PrGXRZ0nnMIw==
*/