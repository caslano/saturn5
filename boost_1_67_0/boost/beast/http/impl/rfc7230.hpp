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