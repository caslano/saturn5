//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_IMPL_STRING_HPP
#define BOOST_JSON_IMPL_STRING_HPP

#include <utility>

BOOST_JSON_NS_BEGIN

string::
string(
    detail::key_t const&,
    string_view s,
    storage_ptr sp)
    : sp_(std::move(sp))
    , impl_(detail::key_t{},
        s, sp_)
{
}

string::
string(
    detail::key_t const&,
    string_view s1,
    string_view s2,
    storage_ptr sp)
    : sp_(std::move(sp))
    , impl_(detail::key_t{},
        s1, s2, sp_)
{
}

template<class InputIt, class>
string::
string(
    InputIt first,
    InputIt last,
    storage_ptr sp)
    : sp_(std::move(sp))
    , impl_(first, last, sp_,
        iter_cat<InputIt>{})
{
}

template<class InputIt, class>
string&
string::
assign(
    InputIt first,
    InputIt last)
{
    assign(first, last,
        iter_cat<InputIt>{});
    return *this;
}

template<class InputIt, class>
string&
string::
append(InputIt first, InputIt last)
{
    append(first, last,
        iter_cat<InputIt>{});
    return *this;
}

// KRYSTIAN TODO: this can be done without copies when
// reallocation is not needed, when the iterator is a
// FowardIterator or better, as we can use std::distance
template<class InputIt, class>
auto
string::
insert(
    size_type pos,
    InputIt first,
    InputIt last) ->
        string&
{
    struct cleanup
    {
        detail::string_impl& s;
        storage_ptr const& sp;

        ~cleanup()
        {
            s.destroy(sp);
        }
    };

    // We use the default storage because
    // the allocation is immediately freed.
    storage_ptr dsp;
    detail::string_impl tmp(
        first, last, dsp,
        iter_cat<InputIt>{});
    cleanup c{tmp, dsp};
    std::memcpy(
        impl_.insert_unchecked(pos, tmp.size(), sp_),
        tmp.data(),
        tmp.size());
    return *this;
}

// KRYSTIAN TODO: this can be done without copies when
// reallocation is not needed, when the iterator is a
// FowardIterator or better, as we can use std::distance
template<class InputIt, class>
auto
string::
replace(
    const_iterator first,
    const_iterator last,
    InputIt first2,
    InputIt last2) ->
        string&
{
    struct cleanup
    {
        detail::string_impl& s;
        storage_ptr const& sp;

        ~cleanup()
        {
            s.destroy(sp);
        }
    };

    // We use the default storage because
    // the allocation is immediately freed.
    storage_ptr dsp;
    detail::string_impl tmp(
        first2, last2, dsp,
        iter_cat<InputIt>{});
    cleanup c{tmp, dsp};
    std::memcpy(
        impl_.replace_unchecked(
            first - begin(),
            last - first,
            tmp.size(),
            sp_),
        tmp.data(),
        tmp.size());
    return *this;
}

//----------------------------------------------------------

template<class InputIt>
void
string::
assign(
    InputIt first,
    InputIt last,
    std::random_access_iterator_tag)
{
    auto dest = impl_.assign(static_cast<
        size_type>(last - first), sp_);
    while(first != last)
        *dest++ = *first++;
}

template<class InputIt>
void
string::
assign(
    InputIt first,
    InputIt last,
    std::input_iterator_tag)
{
    if(first == last)
    {
        impl_.term(0);
        return;
    }
    detail::string_impl tmp(
        first, last, sp_,
        std::input_iterator_tag{});
    impl_.destroy(sp_);
    impl_ = tmp;
}

template<class InputIt>
void
string::
append(
    InputIt first,
    InputIt last,
    std::random_access_iterator_tag)
{
    auto const n = static_cast<
        size_type>(last - first);
    std::copy(first, last,
        impl_.append(n, sp_));
}

template<class InputIt>
void
string::
append(
    InputIt first,
    InputIt last,
    std::input_iterator_tag)
{
    struct cleanup
    {
        detail::string_impl& s;
        storage_ptr const& sp;

        ~cleanup()
        {
            s.destroy(sp);
        }
    };

    // We use the default storage because
    // the allocation is immediately freed.
    storage_ptr dsp;
    detail::string_impl tmp(
        first, last, dsp,
        std::input_iterator_tag{});
    cleanup c{tmp, dsp};
    std::memcpy(
        impl_.append(tmp.size(), sp_),
        tmp.data(), tmp.size());
}

BOOST_JSON_NS_END

#endif

/* string.hpp
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
*/