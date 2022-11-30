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
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
*/