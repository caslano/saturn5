//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_STRING_PARAM_HPP
#define BOOST_BEAST_IMPL_STRING_PARAM_HPP

namespace boost {
namespace beast {

template<class T>
typename std::enable_if<
    std::is_integral<T>::value>::type
string_param::
print(T const& t)
{
    auto const last = buf_ + sizeof(buf_);
    auto const it = detail::raw_to_string<
        char, T, std::char_traits<char>>(
            last, sizeof(buf_), t);
    sv_ = {it, static_cast<std::size_t>(
        last - it)};
}

template<class T>
typename std::enable_if<
    ! std::is_integral<T>::value &&
    ! std::is_convertible<T, string_view>::value
>::type
string_param::
print(T const& t)
{
    os_.emplace(buf_, sizeof(buf_));
    *os_ << t;
    os_->flush();
    sv_ = os_->str();
}

inline
void
string_param::
print(string_view sv)
{
    sv_ = sv;
}

template<class T>
typename std::enable_if<
    std::is_integral<T>::value>::type
string_param::
print_1(T const& t)
{
    char buf[detail::max_digits(sizeof(T))];
    auto const last = buf + sizeof(buf);
    auto const it = detail::raw_to_string<
        char, T, std::char_traits<char>>(
            last, sizeof(buf), t);
    *os_ << string_view{it,
        static_cast<std::size_t>(last - it)};
}

template<class T>
typename std::enable_if<
    ! std::is_integral<T>::value>::type
string_param::
print_1(T const& t)
{
    *os_ << t;
}

template<class T0, class... TN>
void
string_param::
print_n(T0 const& t0, TN const&... tn)
{
    print_1(t0);
    print_n(tn...);
}

template<class T0, class T1, class... TN>
void
string_param::
print(T0 const& t0, T1 const& t1, TN const&... tn)
{
    os_.emplace(buf_, sizeof(buf_));
    print_1(t0);
    print_1(t1);
    print_n(tn...);
    os_->flush();
    sv_ = os_->str();
}

template<class... Args>
string_param::
string_param(Args const&... args)
{
    print(args...);
}

} // beast
} // boost

#endif

/* string_param.hpp
oKUXn8yI9I9BOsp9J5h/TDB9zySzgA4yV6yM7SCz55aOHWSGdScPigEL/791kCn9OAZd3Sv/s7c+FgzfFc+4giMyRf9OmyswQi4KjjESIZSVr5BPXFtsYDa3dPlWrNP/UjHjD8fZ5AAKLPXTwFd0pChTH65i8HSTfjfTj7k1moY/F9LG3lYkySjCuWnUq9E9qRoxcHGJ/rxrvgAUBFp2SnPQ3VbeZERep9VZedw7ER6FPmFhQp4SMrokJ1DC65Jc0iiR7fWAghm6wDW0/aclMTaCjzUdy7wuCeQP0V9rdBb+tPA1nCR74P7Z0GO7/6USxgPxY5sfzow4whJxVrOGYTPMw7GPUmLH0yfhgZ0NGw4o+D+PfRW1NyJOu77N0B05OkV7owNdAqIjimXNjD5N7Kw8aV59P++nFZmj5c68487gsmwDfPJOlu7HUSikIVkkFo6yLUyECQhdLNWLMNZuaWg93uuToYv3gZMauNIZf0L07zIyMd3wDlbCqnIWfr1wk0T1FVCC3Tzic3J/dgQGhNLxbQz7zI7MEtzFM2IeH4qKHH7rhyna8SF1K2PEYfVF+vPXEfQgvTlqz4o4f3ZiekcnnhzSWgTSKe10DKqV1mJP2CGownrziMZgQgb0a2eAeogVPTa9Mz1Yf6j9KuY2KB7/RY7gBKOmt6BDaDky0/m32JBEHcW6QIOERcCKjLeO++eHJzRQPG5dRBK2
*/