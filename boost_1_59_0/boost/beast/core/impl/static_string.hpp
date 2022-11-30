//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_STATIC_STRING_HPP
#define BOOST_BEAST_IMPL_STATIC_STRING_HPP

#include <boost/beast/core/detail/static_string.hpp>
#include <boost/throw_exception.hpp>

namespace boost {
namespace beast {

//
// (constructor)
//

template<std::size_t N, class CharT, class Traits>
static_string<N, CharT, Traits>::
static_string()
{
    n_ = 0;
    term();
}

template<std::size_t N, class CharT, class Traits>
static_string<N, CharT, Traits>::
static_string(size_type count, CharT ch)
{
    assign(count, ch);
}

template<std::size_t N, class CharT, class Traits>
template<std::size_t M>
static_string<N, CharT, Traits>::
static_string(static_string<M, CharT, Traits> const& other,
    size_type pos)
{
    assign(other, pos);
}

template<std::size_t N, class CharT, class Traits>
template<std::size_t M>
static_string<N, CharT, Traits>::
static_string(static_string<M, CharT, Traits> const& other,
    size_type pos, size_type count)
{
    assign(other, pos, count);
}

template<std::size_t N, class CharT, class Traits>
static_string<N, CharT, Traits>::
static_string(CharT const* s, size_type count)
{
    assign(s, count);
}

template<std::size_t N, class CharT, class Traits>
static_string<N, CharT, Traits>::
static_string(CharT const* s)
{
    auto const count = Traits::length(s);
    if(count > max_size())
        BOOST_THROW_EXCEPTION(std::length_error{
            "count > max_size()"});
    n_ = count;
    Traits::copy(&s_[0], s, n_ + 1);
}

template<std::size_t N, class CharT, class Traits>
template<class InputIt>
static_string<N, CharT, Traits>::
static_string(InputIt first, InputIt last)
{
    assign(first, last);
}

template<std::size_t N, class CharT, class Traits>
static_string<N, CharT, Traits>::
static_string(static_string const& s)
{
    assign(s);
}

template<std::size_t N, class CharT, class Traits>
template<std::size_t M>
static_string<N, CharT, Traits>::
static_string(static_string<M, CharT, Traits> const& s)
{
    assign(s);
}

template<std::size_t N, class CharT, class Traits>
static_string<N, CharT, Traits>::
static_string(std::initializer_list<CharT> init)
{
    assign(init.begin(), init.end());
}

template<std::size_t N, class CharT, class Traits>
static_string<N, CharT, Traits>::
static_string(string_view_type sv)
{
    assign(sv);
}

template<std::size_t N, class CharT, class Traits>
template<class T, class>
static_string<N, CharT, Traits>::
static_string(T const& t, size_type pos, size_type n)
{
    assign(t, pos, n);
}

//
// (assignment)
//

template<std::size_t N, class CharT, class Traits>
auto
static_string<N, CharT, Traits>::
operator=(CharT const* s) ->
    static_string&
{
    auto const count = Traits::length(s);
    if(count > max_size())
        BOOST_THROW_EXCEPTION(std::length_error{
            "count > max_size()"});
    n_ = count;
    Traits::copy(&s_[0], s, n_ + 1);
    return *this;
}

template<std::size_t N, class CharT, class Traits>
auto
static_string<N, CharT, Traits>::
assign(size_type count, CharT ch) ->
    static_string&
{
    if(count > max_size())
        BOOST_THROW_EXCEPTION(std::length_error{
            "count > max_size()"});
    n_ = count;
    Traits::assign(&s_[0], n_, ch);
    term();
    return *this;
}

template<std::size_t N, class CharT, class Traits>
auto
static_string<N, CharT, Traits>::
assign(static_string const& str) ->
    static_string&
{
    n_ = str.n_;
    auto const n = n_ + 1;
    BOOST_BEAST_ASSUME(n != 0);
    Traits::copy(&s_[0], &str.s_[0], n);
    return *this;
}

template<std::size_t N, class CharT, class Traits>
template<std::size_t M>
auto
static_string<N, CharT, Traits>::
assign(static_string<M, CharT, Traits> const& str,
        size_type pos, size_type count) ->
    static_string&
{
    auto const ss = str.substr(pos, count);
    return assign(ss.data(), ss.size());
}

template<std::size_t N, class CharT, class Traits>
auto
static_string<N, CharT, Traits>::
assign(CharT const* s, size_type count) ->
    static_string&
{
    if(count > max_size())
        BOOST_THROW_EXCEPTION(std::length_error{
            "count > max_size()"});
    n_ = count;
    Traits::copy(&s_[0], s, n_);
    term();
    return *this;
}

template<std::size_t N, class CharT, class Traits>
template<class InputIt>
auto
static_string<N, CharT, Traits>::
assign(InputIt first, InputIt last) ->
    static_string&
{
    std::size_t const n = std::distance(first, last);
    if(n > max_size())
        BOOST_THROW_EXCEPTION(std::length_error{
            "n > max_size()"});
    n_ = n;
    for(auto it = &s_[0]; first != last; ++it, ++first)
        Traits::assign(*it, *first);
    term();
    return *this;
}

template<std::size_t N, class CharT, class Traits>
template<class T>
auto
static_string<N, CharT, Traits>::
assign(T const& t, size_type pos, size_type count) ->
    typename std::enable_if<std::is_convertible<T,
        string_view_type>::value, static_string&>::type
{
    auto const sv = string_view_type(t).substr(pos, count);
    if(sv.size() > max_size())
        BOOST_THROW_EXCEPTION(std::length_error{
            "sv.size() > max_size()"});
    n_ = sv.size();
    Traits::copy(&s_[0], &sv[0], n_);
    term();
    return *this;
}

//
// Element access
//

template<std::size_t N, class CharT, class Traits>
auto
static_string<N, CharT, Traits>::
at(size_type pos) ->
    reference
{
    if(pos >= size())
        BOOST_THROW_EXCEPTION(std::out_of_range{
            "pos >= size()"});
    return s_[pos];
}

template<std::size_t N, class CharT, class Traits>
auto
static_string<N, CharT, Traits>::
at(size_type pos) const ->
    const_reference
{
    if(pos >= size())
        BOOST_THROW_EXCEPTION(std::out_of_range{
            "pos >= size()"});
    return s_[pos];
}

//
// Capacity
//

template<std::size_t N, class CharT, class Traits>
void
static_string<N, CharT, Traits>::
reserve(std::size_t n)
{
    if(n > max_size())
        BOOST_THROW_EXCEPTION(std::length_error{
            "n > max_size()"});
}

//
// Operations
//

template<std::size_t N, class CharT, class Traits>
void
static_string<N, CharT, Traits>::
clear()
{
    n_ = 0;
    term();
}

template<std::size_t N, class CharT, class Traits>
auto
static_string<N, CharT, Traits>::
insert(size_type index, size_type count, CharT ch) ->
    static_string&
{
    if(index > size())
        BOOST_THROW_EXCEPTION(std::out_of_range{
            "index > size()"});
    insert(begin() + index, count, ch);
    return *this;
}

template<std::size_t N, class CharT, class Traits>
auto
static_string<N, CharT, Traits>::
insert(size_type index, CharT const* s, size_type count) ->
    static_string&
{
    if(index > size())
        BOOST_THROW_EXCEPTION(std::out_of_range{
            "index > size()"});
    if(size() + count > max_size())
        BOOST_THROW_EXCEPTION(std::length_error{
            "size() + count > max_size()"});
    Traits::move(
        &s_[index + count], &s_[index], size() - index);
    n_ += count;
    Traits::copy(&s_[index], s, count);
    term();
    return *this;
}

template<std::size_t N, class CharT, class Traits>
template<std::size_t M>
auto
static_string<N, CharT, Traits>::
insert(size_type index,
    static_string<M, CharT, Traits> const& str,
        size_type index_str, size_type count) ->
    static_string&
{
    auto const ss = str.substr(index_str, count);
    return insert(index, ss.data(), ss.size());
}

template<std::size_t N, class CharT, class Traits>
auto
static_string<N, CharT, Traits>::
insert(const_iterator pos, size_type count, CharT ch) ->
    iterator
{
    if(size() + count > max_size())
        BOOST_THROW_EXCEPTION(std::length_error{
            "size() + count() > max_size()"});
    auto const index = pos - &s_[0];
    Traits::move(
        &s_[index + count], &s_[index], size() - index);
    n_ += count;
    Traits::assign(&s_[index], count, ch);
    term();
    return &s_[index];
}

template<std::size_t N, class CharT, class Traits>
template<class InputIt>
auto
static_string<N, CharT, Traits>::
insert(const_iterator pos, InputIt first, InputIt last) ->
    typename std::enable_if<
        detail::is_input_iterator<InputIt>::value,
            iterator>::type
{
    std::size_t const count = std::distance(first, last);
    if(size() + count > max_size())
        BOOST_THROW_EXCEPTION(std::length_error{
            "size() + count > max_size()"});
    std::size_t const index = pos - begin();
    Traits::move(
        &s_[index + count], &s_[index], size() - index);
    n_ += count;
    for(auto it = begin() + index;
            first != last; ++it, ++first)
        Traits::assign(*it, *first);
    term();
    return begin() + index;
}

template<std::size_t N, class CharT, class Traits>
template<class T>
auto
static_string<N, CharT, Traits>::
insert(size_type index, const T& t,
        size_type index_str, size_type count) ->
    typename std::enable_if<std::is_convertible<
        T const&, string_view_type>::value &&
        ! std::is_convertible<T const&, CharT const*>::value,
            static_string&>::type
{
    auto const str =
        string_view_type(t).substr(index_str, count);
    return insert(index, str.data(), str.size());
}

template<std::size_t N, class CharT, class Traits>
auto
static_string<N, CharT, Traits>::
erase(size_type index, size_type count) ->
    static_string&
{
    if(index > size())
        BOOST_THROW_EXCEPTION(std::out_of_range{
            "index > size()"});
    auto const n = (std::min)(count, size() - index);
    Traits::move(
        &s_[index], &s_[index + n], size() - (index + n) + 1);
    n_ -= n;
    return *this;
}

template<std::size_t N, class CharT, class Traits>
auto
static_string<N, CharT, Traits>::
erase(const_iterator pos) ->
    iterator
{
    erase(pos - begin(), 1);
    return begin() + (pos - begin());
}

template<std::size_t N, class CharT, class Traits>
auto
static_string<N, CharT, Traits>::
erase(const_iterator first, const_iterator last) ->
    iterator
{
    erase(first - begin(),
        std::distance(first, last));
    return begin() + (first - begin());
}

template<std::size_t N, class CharT, class Traits>
void
static_string<N, CharT, Traits>::
push_back(CharT ch)
{
    if(size() >= max_size())
        BOOST_THROW_EXCEPTION(std::length_error{
            "size() >= max_size()"});
    Traits::assign(s_[n_++], ch);
    term();
}

template<std::size_t N, class CharT, class Traits>
template<std::size_t M>
auto
static_string<N, CharT, Traits>::
append(static_string<M, CharT, Traits> const& str,
        size_type pos, size_type count) ->
    static_string&
{
    // Valid range is [0, size)
    if(pos >= str.size())
        BOOST_THROW_EXCEPTION(std::out_of_range{
            "pos > str.size()"});
    string_view_type const ss{&str.s_[pos],
        (std::min)(count, str.size() - pos)};
    insert(size(), ss.data(), ss.size());
    return *this;
}

template<std::size_t N, class CharT, class Traits>
auto
static_string<N, CharT, Traits>::
substr(size_type pos, size_type count) const ->
    string_view_type
{
    if(pos > size())
        BOOST_THROW_EXCEPTION(std::out_of_range{
            "pos > size()"});
    return{&s_[pos], (std::min)(count, size() - pos)};
}

template<std::size_t N, class CharT, class Traits>
auto
static_string<N, CharT, Traits>::
copy(CharT* dest, size_type count, size_type pos) const ->
    size_type
{
    auto const str = substr(pos, count);
    Traits::copy(dest, str.data(), str.size());
    return str.size();
}

template<std::size_t N, class CharT, class Traits>
void
static_string<N, CharT, Traits>::
resize(std::size_t n)
{
    if(n > max_size())
        BOOST_THROW_EXCEPTION(std::length_error{
            "n > max_size()"});
    if(n > n_)
        Traits::assign(&s_[n_], n - n_, CharT{});
    n_ = n;
    term();
}

template<std::size_t N, class CharT, class Traits>
void
static_string<N, CharT, Traits>::
resize(std::size_t n, CharT c)
{
    if(n > max_size())
        BOOST_THROW_EXCEPTION(std::length_error{
            "n > max_size()"});
    if(n > n_)
        Traits::assign(&s_[n_], n - n_, c);
    n_ = n;
    term();
}

template<std::size_t N, class CharT, class Traits>
void
static_string<N, CharT, Traits>::
swap(static_string& str)
{
    static_string tmp(str);
    str.n_ = n_;
    Traits::copy(&str.s_[0], &s_[0], n_ + 1);
    n_ = tmp.n_;
    Traits::copy(&s_[0], &tmp.s_[0], n_ + 1);
}

template<std::size_t N, class CharT, class Traits>
template<std::size_t M>
void
static_string<N, CharT, Traits>::
swap(static_string<M, CharT, Traits>& str)
{
    if(size() > str.max_size())
        BOOST_THROW_EXCEPTION(std::length_error{
            "size() > str.max_size()"});
    if(str.size() > max_size())
        BOOST_THROW_EXCEPTION(std::length_error{
            "str.size() > max_size()"});
    static_string tmp(str);
    str.n_ = n_;
    Traits::copy(&str.s_[0], &s_[0], n_ + 1);
    n_ = tmp.n_;
    Traits::copy(&s_[0], &tmp.s_[0], n_ + 1);
}


template<std::size_t N, class CharT, class Traits>
auto
static_string<N, CharT, Traits>::
assign_char(CharT ch, std::true_type) ->
    static_string&
{
    n_ = 1;
    Traits::assign(s_[0], ch);
    term();
    return *this;
}

template<std::size_t N, class CharT, class Traits>
auto
static_string<N, CharT, Traits>::
assign_char(CharT, std::false_type) ->
    static_string&
{
    BOOST_THROW_EXCEPTION(std::length_error{
        "max_size() == 0"});
}

template<class Integer, class>
static_string<detail::max_digits(sizeof(Integer))>
to_static_string(Integer x)
{
    using CharT = char;
    using Traits = std::char_traits<CharT>;
    BOOST_STATIC_ASSERT(std::is_integral<Integer>::value);
    char buf[detail::max_digits(sizeof(Integer))];
    auto last = buf + sizeof(buf);
    auto it = detail::raw_to_string<
        CharT, Integer, Traits>(last, sizeof(buf), x);
    static_string<detail::max_digits(sizeof(Integer))> s;
    s.resize(static_cast<std::size_t>(last - it));
    auto p = s.data();
    while(it < last)
        Traits::assign(*p++, *it++);
    return s;
}

} // beast
} // boost

#endif

/* static_string.hpp
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
*/