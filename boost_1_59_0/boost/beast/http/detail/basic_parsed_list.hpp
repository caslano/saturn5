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
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
*/