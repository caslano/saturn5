//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_IMPL_RFC7230_HPP
#define BOOST_BEAST_HTTP_IMPL_RFC7230_HPP

#include <boost/beast/http/detail/rfc7230.hpp>
#include <iterator>

namespace boost {
namespace beast {
namespace http {

class param_list::const_iterator
{
    using iter_type = string_view::const_iterator;

    std::string s_;
    detail::param_iter pi_;

public:
    using value_type = param_list::value_type;
    using pointer = value_type const*;
    using reference = value_type const&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::input_iterator_tag;

    const_iterator() = default;

    bool
    operator==(const_iterator const& other) const
    {
        return
            other.pi_.it == pi_.it &&
            other.pi_.last == pi_.last &&
            other.pi_.first == pi_.first;
    }

    bool
    operator!=(const_iterator const& other) const
    {
        return !(*this == other);
    }

    reference
    operator*() const
    {
        return pi_.v;
    }

    pointer
    operator->() const
    {
        return &*(*this);
    }

    const_iterator&
    operator++()
    {
        increment();
        return *this;
    }

    const_iterator
    operator++(int)
    {
        auto temp = *this;
        ++(*this);
        return temp;
    }

private:
    friend class param_list;

    const_iterator(iter_type first, iter_type last)
    {
        pi_.it = first;
        pi_.first = first;
        pi_.last = last;
        increment();
    }

    BOOST_BEAST_DECL
    static
    std::string
    unquote(string_view sr);

    BOOST_BEAST_DECL
    void
    increment();
};

inline
auto
param_list::
begin() const ->
    const_iterator
{
    return const_iterator{s_.begin(), s_.end()};
}

inline
auto
param_list::
end() const ->
    const_iterator
{
    return const_iterator{s_.end(), s_.end()};
}

inline
auto
param_list::
cbegin() const ->
    const_iterator
{
    return const_iterator{s_.begin(), s_.end()};
}

inline
auto
param_list::
cend() const ->
    const_iterator
{
    return const_iterator{s_.end(), s_.end()};
}

//------------------------------------------------------------------------------

class ext_list::const_iterator
{
    ext_list::value_type v_;
    iter_type it_;
    iter_type first_;
    iter_type last_;

public:
    using value_type = ext_list::value_type;
    using pointer = value_type const*;
    using reference = value_type const&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    const_iterator() = default;

    bool
    operator==(const_iterator const& other) const
    {
        return
            other.it_ == it_ &&
            other.first_ == first_ &&
            other.last_ == last_;
    }

    bool
    operator!=(const_iterator const& other) const
    {
        return !(*this == other);
    }

    reference
    operator*() const
    {
        return v_;
    }

    pointer
    operator->() const
    {
        return &*(*this);
    }

    const_iterator&
    operator++()
    {
        increment();
        return *this;
    }

    const_iterator
    operator++(int)
    {
        auto temp = *this;
        ++(*this);
        return temp;
    }

private:
    friend class ext_list;

    const_iterator(iter_type begin, iter_type end)
    {
        it_ = begin;
        first_ = begin;
        last_ = end;
        increment();
    }

    BOOST_BEAST_DECL
    void
    increment();
};

inline
auto
ext_list::
begin() const ->
    const_iterator
{
    return const_iterator{s_.begin(), s_.end()};
}

inline
auto
ext_list::
end() const ->
    const_iterator
{
    return const_iterator{s_.end(), s_.end()};
}

inline
auto
ext_list::
cbegin() const ->
    const_iterator
{
    return const_iterator{s_.begin(), s_.end()};
}

inline
auto
ext_list::
cend() const ->
    const_iterator
{
    return const_iterator{s_.end(), s_.end()};
}


//------------------------------------------------------------------------------

class token_list::const_iterator
{
    token_list::value_type v_;
    iter_type it_;
    iter_type first_;
    iter_type last_;

public:
    using value_type = token_list::value_type;
    using pointer = value_type const*;
    using reference = value_type const&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    const_iterator() = default;

    bool
    operator==(const_iterator const& other) const
    {
        return
            other.it_ == it_ &&
            other.first_ == first_ &&
            other.last_ == last_;
    }

    bool
    operator!=(const_iterator const& other) const
    {
        return !(*this == other);
    }

    reference
    operator*() const
    {
        return v_;
    }

    pointer
    operator->() const
    {
        return &*(*this);
    }

    const_iterator&
    operator++()
    {
        increment();
        return *this;
    }

    const_iterator
    operator++(int)
    {
        auto temp = *this;
        ++(*this);
        return temp;
    }

private:
    friend class token_list;

    const_iterator(iter_type begin, iter_type end)
    {
        it_ = begin;
        first_ = begin;
        last_ = end;
        increment();
    }

    BOOST_BEAST_DECL
    void
    increment();
};

inline
auto
token_list::
begin() const ->
    const_iterator
{
    return const_iterator{s_.begin(), s_.end()};
}

inline
auto
token_list::
end() const ->
    const_iterator
{
    return const_iterator{s_.end(), s_.end()};
}

inline
auto
token_list::
cbegin() const ->
    const_iterator
{
    return const_iterator{s_.begin(), s_.end()};
}

inline
auto
token_list::
cend() const ->
    const_iterator
{
    return const_iterator{s_.end(), s_.end()};
}

template<class Policy>
bool
validate_list(detail::basic_parsed_list<
    Policy> const& list)
{
    auto const last = list.end();
    auto it = list.begin();
    if(it.error())
        return false;
    while(it != last)
    {
        ++it;
        if(it.error())
            return false;
        if(it == last)
            break;
    }
    return true;
}

} // http
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/http/impl/rfc7230.ipp>
#endif

#endif


/* rfc7230.hpp
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
*/