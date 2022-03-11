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