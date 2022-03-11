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