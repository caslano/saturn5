/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/addressof.hpp
 *
 * This header defines \c addressof helper function. It is similar to \c boost::addressof but it is more
 * lightweight and also contains a workaround for some compiler warnings.
 */

#ifndef BOOST_ATOMIC_DETAIL_ADDRESSOF_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_ADDRESSOF_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

// Detection logic is based on boost/core/addressof.hpp
#if defined(BOOST_MSVC_FULL_VER) && BOOST_MSVC_FULL_VER >= 190024215
#define BOOST_ATOMIC_DETAIL_HAS_BUILTIN_ADDRESSOF
#elif defined(BOOST_GCC) && BOOST_GCC >= 70000
#define BOOST_ATOMIC_DETAIL_HAS_BUILTIN_ADDRESSOF
#elif defined(__has_builtin)
#if __has_builtin(__builtin_addressof)
#define BOOST_ATOMIC_DETAIL_HAS_BUILTIN_ADDRESSOF
#endif
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename T >
BOOST_FORCEINLINE T* addressof(T& value) BOOST_NOEXCEPT
{
#if defined(BOOST_ATOMIC_DETAIL_HAS_BUILTIN_ADDRESSOF)
    return __builtin_addressof(value);
#else
    // Note: The point of using a local struct as the intermediate type instead of char is to avoid gcc warnings
    // if T is a const volatile char*:
    // warning: casting 'const volatile char* const' to 'const volatile char&' does not dereference pointer
    // The local struct makes sure T is not related to the cast target type.
    struct opaque_type;
    return reinterpret_cast< T* >(&const_cast< opaque_type& >(reinterpret_cast< const volatile opaque_type& >(value)));
#endif
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_ADDRESSOF_HPP_INCLUDED_

/* addressof.hpp
Wfsuj338coaMX3phOiyAfWX9iOgUiX430ffAVNHPtvr4R9jPJbKfabKf6bIf1vV+GiPsZ7QlX5Pk6++Qb5Il38EI5U205GttZ3k837nmOy+Yj+cz9/2OtbZrO8triJBviiVfc4R8F1nr+1Q76/t0++zzPt0+++qfbp99TU+3z76D7bDPp3/3+O2UfD1hqREcf0+GvWEaTIMDYDocBrNgNsyEo2BfOBb2h1MkfZqM23tlfX8s7xTS4815A23OLThEvrgM/MKRfKQSmc5YcCUSOjYcN94/PjwEbn/cff5BZRtzEBImQCSXv/MmtH8+wh7+PoqMuYB9I0fZthya481rYegchV0yT+EQ3ALj8oLzFbLz3OcsrHWYt9DM3/sRx/kLE5EcxprhLCQwl2H/4+HzGdayvQnZzN9vQl/P2IjzG1bJGPhu5LCa68A2dMz5Dg30VcKkyDEBsycF5z7k8XcpcpS/jz8enAexfFJwXH0df29BAnMidk8KjrMnPMG+2ZYNcye3PUfiqGWexAgYmCvhg1uwfR3choTOnTh8gvMnKqeSH2lC9iAO8yk40YNzKsYgCdewLxnzbwwZ99/G+nF4wCQSOt8iNT845+J8/p6H1Mrci3WwCWng72bqehAx+sQbWUgeUoqsQR5GWpBWJDUz3shFZiF1yEbkGeQAYvSNN4b0jfoeRJfoEl2iS3T55C5xSNUpGP9fXFZb7p8BcPJzALYN5xlP3nV1k/FX05/0DLgdrh/N82Gj/714daG5ex8f76tV75Y2JKr4/9zqB2PuPa/y3uGRd3iiO9zy3rVO5Z2m03J1HPw31fq9nmA8I6L7Sdnp8LXG4Lfqy7X+KCOY3wwV5s9fodPP1t8vf0Wtb1Ll+9RYG18i5N9ksWf4t0nHw7Y7tQ/xz1dlVJFnlyrjUU+yTl9cXVrIO3YpJw3uU3lWGLMt34afs0l9x161w4hEtW8dU+Vstd+RHu4Wxe8+mP9c3sklSHyZQcm8g4WmjEmJJBFj6FwS8GNnH2ExdDao+ErSp2ybo99h15HHGkdJ9Y3aVq63qfaXWH+9JNZfeFzJW7CvaIM6pjiUzINKDe6qNt/vfy+qHOnlGJK8OtYO7ybbfs8b8DWgPOxS5dnsGhMXZpdyIG9db7VLxf9RdlWkhNlFXrtd/Ya13y7K03ZZ4wCtkVvdEnnf/CVkJXmb7lR2VVeWBk7CK8xIbNWlZUZou+m4OzuVjtf4DP+KzVJOsmXMylfKpUCfk6SHxPQiWR3eetxK5wn51oXabz7pL6j0Czjru+lvfO6QuFDvpbd9bMq7YmvfqW35epzLb3Oa7VsW2k5be87rEt7P19OeOXeFt2dZlWpPt/4WnSQZjwhpO52eqY+Hpzsw98l6POgxCV1XGfOSOo2QsftKqdNCZIM5frtJj0kUVy6srimsrS5cXOqvzwxlL5sNXR/JP0ClH0g2WMhtuZaPvM9MP4sazVVftPQRaOJ4okFuw7gNmZfY/lhuM1Rd2H/I+MozUpcBUpfech4mbtB1UXFnXfqEfB2Pw+VyDur2rZfx0Rdj+DWFzXD/QLbfFxzzWbzUHhc0hnR8pCrUsSbtd4fK/z2jH/9+Cbk1eB5KWWnS1h5jwv3mek8di4/eLZ5fVmlkyvytjSr/1hgzrtss5EYkWfrVMDCHplV9RxXr4bdV/gdjgr9jVRWlMmaUBA+q9M8bPfhvvJGg9vuuWVnalxlrer7bZpVvc8xpZqRYZCUScrzo+WdvbDbzviXrnAmqTj2sv6VXBNonA65XZT8ak27EGnOQryPBOi0uXroov3hpuaFjk+Wo8hfyTruvzIfjiztq223ye6zbzR8zUH6zq7/j/zZPDOU=
*/