//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_DETAIL_BASIC_PARSED_LIST_HPP
#define BOOST_BEAST_HTTP_DETAIL_BASIC_PARSED_LIST_HPP

#include <boost/beast/core/string.hpp>
#include <boost/core/empty_value.hpp>
#include <cstddef>
#include <iterator>

namespace boost {
namespace beast {
namespace http {
namespace detail {

/** A list parser which presents the sequence as a container.
*/
template<class Policy>
class basic_parsed_list
{
    string_view s_;

public:
    /// The type of policy this list uses for parsing.
    using policy_type = Policy;

    /// The type of each element in the list.
    using value_type = typename Policy::value_type;

    /// A constant iterator to a list element.
#if BOOST_BEAST_DOXYGEN
    using const_iterator = __implementation_defined__;
#else
    class const_iterator;
#endif

    class const_iterator
        : private boost::empty_value<Policy>
    {
        basic_parsed_list const* list_ = nullptr;
        char const* it_ = nullptr;
        typename Policy::value_type v_;
        bool error_ = false;

    public:
        using value_type =
            typename Policy::value_type;
        using reference = value_type const&;
        using pointer = value_type const*;
        using difference_type = std::ptrdiff_t;
        using iterator_category =
            std::forward_iterator_tag;

        const_iterator() = default;

        bool
        operator==(
            const_iterator const& other) const
        {
            return
                other.list_ == list_ &&
                other.it_ == it_;
        }

        bool
        operator!=(
            const_iterator const& other) const
        {
            return ! (*this == other);
        }

        reference
        operator*() const
        {
            return v_;
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

        bool
        error() const
        {
            return error_;
        }

    private:
        friend class basic_parsed_list;

        const_iterator(
            basic_parsed_list const& list, bool at_end)
            : list_(&list)
            , it_(at_end ? nullptr :
                list.s_.data())
        {
            if(! at_end)
                increment();
        }

        void
        increment()
        {
            if(! this->get()(
                    v_, it_, list_->s_))
            {
                it_ = nullptr;
                error_ = true;
            }
        }
    };

    /// Construct a list from a string
    explicit
    basic_parsed_list(string_view s)
        : s_(s)
    {
    }

    /// Return a const iterator to the beginning of the list
    const_iterator begin() const;

    /// Return a const iterator to the end of the list
    const_iterator end() const;

    /// Return a const iterator to the beginning of the list
    const_iterator cbegin() const;

    /// Return a const iterator to the end of the list
    const_iterator cend() const;
};

template<class Policy>
inline
auto
basic_parsed_list<Policy>::
begin() const ->
    const_iterator
{
    return const_iterator{*this, false};
}

template<class Policy>
inline
auto
basic_parsed_list<Policy>::
end() const ->
    const_iterator
{
    return const_iterator{*this, true};
}

template<class Policy>
inline
auto
basic_parsed_list<Policy>::
cbegin() const ->
    const_iterator
{
    return const_iterator{*this, false};
}

template<class Policy>
inline
auto
basic_parsed_list<Policy>::
cend() const ->
    const_iterator
{
    return const_iterator{*this, true};
}

} // detail
} // http
} // beast
} // boost

#endif


/* basic_parsed_list.hpp
wNthKpwB0+BqmAHXwrFwH8yEz8Es+AGcCIuLzU8QnAxD4G0wAk6FDeF02BPmwbFwNhwH74QT4FB4OxwGZ8M5cDFcBO+Gi+FOuBQeg8vgu/Ae+D5cAf8N74NV7TzHsA3Ml3Z4P+wK18Me8AF4E9wAk+BGOAk+CPPgQ3ANfETa51Z4GG6DZyTdObgD/gA3Q537/hgMh3NhfThf2t8C2Bhugq2gEb8tXAV7wHTYG3YupI1DEv5RDQK92jjENwj02zlc4z2f/ltsHApj39CL9pGBzEI2Ik8jJ5BzSEBD8m7ot3H4Xzl+b/1/drYhiVnZY3+7/t/Q8QdEaea3+NbYJkp0GRWRfMZ9O+epObEOffpw3vSxuYmUIDM7x8f61RKf1KY+oWgh9Ale1oMW3bvsPxAgkcmwHoyEp+si3suWOHKEpsr3HnF0DZdVPjNNrPU9ffB8w11WL2HpdMfLnJ0Zt4HMG1MvKm6wXjD3lpqRfEuOmqNPkLnC6vLGbc77xqo0rzCnvsGa9/1Z+dVSZTxcUb7zaaypfJJ0S5/DoTZWV/6dNWf/VO6hw7+X+M+rLPlokg8sKGdG+liJ3178P1Tzgrnppp68PIygXJRO7dvO+zizbta+7YdK1jP2bQ/mvwCf+7Y/otLX9GmLsUGFxyl9k6mXGxXKuJXByevIymDjb9nXnwTm4XVf/7Lmvv7MGfM39xq3ea+ZNy5r6lrHu63H7Lhn+Km6pv7xU/XvtiawqnvR5Zp+qt4dafGjzl3WKm9vnUPVt5qDflNdsyqfS5s+J206QfS9rZCPiJO3wHubTs1y3Le7Sc08vfMzRxp3Ww/MhJzme1ep8NrMuRSx1idvVNbxbI4JLrwelHOLPYfrfPrKIj7seBZchR3PgivY8Sz4bXY8Zlm3iO1JdennwpF3jWfBMffvqHOqz3dZJa5841UDp+5U1m5WeKjYibj2kZ0JD1bhIcrdy4ofbPaZzCUXvs90uk5LD0uZ8FNlsto+5XDpWy/AhL/g/PHVzgdf7Xyz9/nd339euYOaP+7eOvDTZS1eLp9yMGH9ilb95//vzRNf0q15Yua15H0ARnmZ12oq87txsCJsBisrt8zDIqclfTux1Q9U826yJz/xYmENmceqBZNgbZgN68BDsC78ScIjdc5v5S99p/TD7vm3IrgMbA3DYTysAtvABjBBzt8Wxom7lft8t+QfgVzSf9t8dwtN+gpQ3Ut9Xke8YBgr5W0EI8V9RC/cONeb7f4FhDGsjF+9jl1lzOp9vOp7rEo8pB/iY3wqY1Pf49ITyDnEyzj0V41BZyHOY80TiOv40vvY0nM86TGWlPEjaQ8FXHEM6Rg/QsaH65DDyFlEu84/XvQf/uOvePxB43/MzK/N+P9CVX5XZTyyXMb/ibAUHAJbVUAXMUe9FxvnzchMTkl0lMV4pSe7nETelpl/5r01kjTvkN/6UN4J4Eh+uL6Diyvyuwe/R37G7wd4iDMeD2eevxJztnAfiTtyrh8J+8mIh/wbSYzgPQWerOJ4gdCRnWHM25NudXneYwsxt2C+60bTjecqXf2szav//vHfYmNn/K3vpPRFm875fket19fwT1w6YWPKsbH7m0a+eue+E280v3rbB1/vkA+p8uRWmvftjN73DZldb+Da4KbFzzDIVfHjv4uu0+/i1DlbOw0JO1dswXRf72C+3tl82SZc/bvrhuqG/wO77jt0/KVxl6aE7CtfP/C7HoxbR6t30d6nB7UJKfP8odxXR544UWyj73fRw2o/meeOD/rnQxmVz/6ybF37kzUe+4Y2ofx3fjS42qqkh0vMLnlUD724+QnGS+0N/7vjqsaN+SjniV7rF1ya/+IQyl+8teE=
*/