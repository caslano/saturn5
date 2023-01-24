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
vdr4cWyoVwwALjqarwapKHx3juG7J/h3+Q73MbXWlcu2x4wHUQt0WDqogX7x6XGDGug25bXTW6mBPoZJvvmgBqo2b2H/kW0AQwqq85tFdqkpXnMV0a9Yx//FRGVt+rumB1qzSBwZg27l/t/+HtVORtDoVZdqNLpH+IrIzzrkzn6duEITNF7cqEXAKikBVkkJ6IixVc7anQ/q6qGkR5+Il5RbU+wYR6I0VcR9RyURtqABbv8d6ewARNB/A8CKr7FKPJJQJiBddlySSMnGaU44afdwajkJOTirkGeRc5X/fL3EXr53f5aIpeLg+lBNnBanUqfycFsfsVSG5EZRzHCeixEiKPZWjYRC75L07JJ+W2Y9j9eWnInd/WfU9uE8uwGtNfk0VaqrBK0d3rlSPycHwmnqcgy8WCLiOPB7sgfQ+1mpbdHaDHLG3kKrXFOMpPVaetx4Cz6W0tuL9Hi2ONwvepiKBFIGlscu1riEeFkkeIBAF68PIUqoVBk5CiM9O5cPEVT19TxlGU/JU67jKRt5SrFyCU95b4hgoJ7BU+p5SqFihxS2i2H7ZXuDS4nXxe9YxG6qxFkuAndmJPdgVM2F8cSXq6LNpDqPVZHW8unxEDmGBGuuDXng3yFwJMl/hmNVr5hRrnNrR7lya/1Ja+wSRQeGYnicjcrd4Sj/CtiXwWF0H3T+E/Y4erpq7CRJPOqum3XxE8A2O4SQnStE
*/