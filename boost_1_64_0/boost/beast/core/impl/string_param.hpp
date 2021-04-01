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
GkKu2HC/GExxdPRFTRUnCpWiypJs9focj8NXeqI66sh2IjCVViC3PSZv0axCQm4EXUrgUSuxTBDSzj+DSVVsCDRFb93m6E40KlAu8c4aPSB9fQihCOnRUQW+HyQE3aULcF4ktO1NuTjitMBg7SnzVIRaZxD5nz3rTwUt5//QQIps8NR3Jpu8w/R7t54OxWDGJoqL124qRml+S11D1zLbrQeHKy9e8l7z5lLVxQqRd/3/W2M1aFdKmim+V9eRu2NhTCKwHRGxVqUHrDrWuwNV3ZNlUAfnhUcohTahopYgeMKQKkZus032LQzZea1zR1oRIeGCIcB5fxHQxtXtztv1JzGNKi3aOwsgITRa8adV37nvupCSOkEjWwJEafZb8p9AhSb0cdBiIXdS+0xtKSmhHDz9rrCrE4Qf2RiPjRM8TNff2T9M8vmYD6TWlZVUW979923NRr+Jbio5cRzHXqD+ID8y+N22NacBQmgcBrHC15x8htJULOiFJGqBy9wxOj4pe8N/RCqG+GvCyY/0taA8Y7P4EGUsigH/TQWL4xk6nuC+a4WlTxc7epq5XQ==
*/