// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CORE_IGNORE_UNUSED_HPP
#define BOOST_CORE_IGNORE_UNUSED_HPP

#include <boost/config.hpp>

namespace boost {

#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES

template <typename... Ts>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(Ts const& ...)
{}

template <typename... Ts>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused()
{}

#else

template <typename T1>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1 const&)
{}

template <typename T1, typename T2>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1 const&, T2 const&)
{}

template <typename T1, typename T2, typename T3>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1 const&, T2 const&, T3 const&)
{}

template <typename T1, typename T2, typename T3, typename T4>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1 const&, T2 const&, T3 const&, T4 const&)
{}

template <typename T1, typename T2, typename T3, typename T4, typename T5>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused(T1 const&, T2 const&, T3 const&, T4 const&, T5 const&)
{}

template <typename T1>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused()
{}

template <typename T1, typename T2>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused()
{}

template <typename T1, typename T2, typename T3>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused()
{}

template <typename T1, typename T2, typename T3, typename T4>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused()
{}

template <typename T1, typename T2, typename T3, typename T4, typename T5>
BOOST_FORCEINLINE BOOST_CXX14_CONSTEXPR void ignore_unused()
{}

#endif

} // namespace boost

#endif // BOOST_CORE_IGNORE_UNUSED_HPP

/* ignore_unused.hpp
Lt0f5g2q31HZ8XRWUK/YzVyW8O7rvoSp1RsK8KvD7cTDwEaVUOX3BaRItZxYnnWYe7N+rJsgOPic0VftrRQ/5LGpij8aX3motxkKhhCIZyU32wprYRLybDhjPw88dgoM10HobMssDwJMkvNZr9DcgY9hFgSCWF+FJbIuG47twZzjdqh+Nbjs+DOrhrfV37ksi6cYoP7vIownqnnqbTnD6A8UykCk0m3tjjiDjQQEW69wxK3XCrVAzKdeTs9tylgu1N+k/N8BeomVMJp2bW+ZRRjWmqs6AT9a6TtjSznuo6055vLUhx4xmhWLzz8JVZoAoDmcJFs12rvFNNxip0V1vdFB/Yk/uy4M/PuXwKAdT0wdm/Wy8uAYE87GGeeToFLCS74dQk4w6Ar2DwsdA3hMtAdeO9YOkQORgf01Htwa+GAulA7OnPFx9FVVeLwo8lDApV5ary9DtWI0xe7VUiF6HmDT0tUqUtSXgEnCavjrtWaAAAuH51HH4yqBweMzhMSRZLKU2S3/WRfqRVNaGjBJUw4aX5Kie5tdhEiVkGjpnOeZNIqE5lV7t+JBxw==
*/