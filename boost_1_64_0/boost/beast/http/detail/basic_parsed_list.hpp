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
8wvh2E3fMFI3jD+lufFBAC/tMMPcXK63CAuifnzm4UKXkJq0zLaAdobpfVyvLhP1UQFtXx7N5n3/LoMc04hBoAUr31gx7Uk0xnhOR/EIiIh2sEv92nPGCUl+rZepwez1cadyR6oH4XnsD68BtMe5eIrQRvHClGraZak/rcJ7y50NCS5Ofx3kOVG7Icvnv5vWZDDUTurv//ZknYiGUtBeDhVsTtgNpeenvBFFTkL/Apo9qyBuc6krPcfI9k378COSKWkc3vB/zdQEqbiPeWCALB91gIldhuECe+AkpDRBmVAFUpCvE5aFXl7kPwnhGa/2brkC1PUuMod2T0y0DS9krVFkdEGR0z3Gh6ravfXEi0QoQlF6ecAVTJOaSmUdTZ4+Z/p28S0qxogYSD+DjYkMI9nf9CcVOZ1Ls3iWzaaXcL9e3gUd1O55Bd2g3qhjdQsEeFsjjV2A3FzNQG70goW41YtxzBVgaAJL1cr/YjgjMsDSL+iyCOTBI/bKeDUp9uVE7buScsIkHg6tiGhp5/NNKgGmNobN5EX8tbpBjdFP+sDgm3Uy+6at0qLbOg==
*/