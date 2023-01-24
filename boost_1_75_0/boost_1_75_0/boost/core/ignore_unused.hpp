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
/1nAieeYWPnYmBwYoKxKi5uQmBLL+rELym6XV1kfkukqDEVcH0J6l5hcB/yaaGQ0zNxgultu2P83BjRJxnB4VteNOEwdFxVjTiPw70n0s2A8saoYxOH6eyjZ/XUTnFgxQVfk/DDM56w7zsfvO/OIJmW87GM64ot+4iaFjBjNCC+cc9feFtHkuqBAGUWL9xgxryQ2BixTY17CeDHHB2FzckFmmJ7DfO/YI29J+0T5xlQYTVASi5EktLU7GeWm1/Pup1rF0ksc0Abx9ORkrbkM4ZluH9KPJhrjDQCs0hmmWrXNSU+UsVJlcyyX3tkLdePhQyhH6SqwsEzxOoMoDuZxph3W2+JCJhdcJMYA9udcL2x72VNN+yaTsXaos7d9xPVr6xiYVuKDabskJ6tLDFA4KDjnjKAfctAH9VzEv5nfBHzgmlmAD84zBQ7B3ORq7aCBgLQ1d4txL3mj3L3bHnw1vULLVRjCvXyZDCgwXzBh0WFkOJwTa/SD+pA+9w3mj22KcujriLp1+I9MMzHPTjR1CnxhnFo/5LXHktQqLfP7cJ/IDR9Mt09pPddq8Q0xDmcb/Gsn2IhmPwzhaW6ou+TvcDYYh0L4Qz+sr3ETQZYmqKbrhClQxkOEL7bz7Uu2aC3maQVKv9ltsxzxaoOKTS5ycWuZn/lDJIJTtdAN1MXTBVqYTygbo/9oYEl4BMLXe+I6zfYpwnw37kdwJtsz
*/