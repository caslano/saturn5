//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_SPAN_HPP
#define BOOST_BEAST_CORE_SPAN_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/detail/type_traits.hpp>
#include <algorithm>
#include <iterator>
#include <string>
#include <type_traits>

namespace boost {
namespace beast {

/** A range of bytes expressed as a ContiguousContainer

    This class implements a non-owning reference to a storage
    area of a certain size and having an underlying integral
    type with size of 1.

    @tparam T The type pointed to by span iterators
*/
template<class T>
class span
{
    T* data_ = nullptr;
    std::size_t size_ = 0;

public:
    /// The type of value, including cv qualifiers
    using element_type = T;

    /// The type of value of each span element
    using value_type = typename std::remove_const<T>::type;

    /// The type of integer used to index the span
    using index_type = std::ptrdiff_t;

    /// A pointer to a span element
    using pointer = T*;

    /// A reference to a span element
    using reference = T&;

    /// The iterator used by the container
    using iterator = pointer;

    /// The const pointer used by the container
    using const_pointer = T const*;

    /// The const reference used by the container
    using const_reference = T const&;

    /// The const iterator used by the container
    using const_iterator = const_pointer;

    /// Constructor
    span() = default;

    /// Constructor
    span(span const&) = default;

    /// Assignment
    span& operator=(span const&) = default;

    /** Constructor

        @param data A pointer to the beginning of the range of elements

        @param size The number of elements pointed to by `data`
    */
    span(T* data, std::size_t size)
        : data_(data), size_(size)
    {
    }

    /** Constructor

        @param container The container to construct from
    */
    template<class ContiguousContainer
#if ! BOOST_BEAST_DOXYGEN
        , class = typename std::enable_if<
          detail::is_contiguous_container<
                ContiguousContainer, T>::value>::type
#endif
    >
    explicit
    span(ContiguousContainer&& container)
        : data_(container.data())
        , size_(container.size())
    {
    }

#if ! BOOST_BEAST_DOXYGEN
    template<class CharT, class Traits, class Allocator>
    explicit
    span(std::basic_string<CharT, Traits, Allocator>& s)
        : data_(&s[0])
        , size_(s.size())
    {
    }

    template<class CharT, class Traits, class Allocator>
    explicit
    span(std::basic_string<CharT, Traits, Allocator> const& s)
        : data_(s.data())
        , size_(s.size())
    {
    }
#endif

    /** Assignment

        @param container The container to assign from
    */
    template<class ContiguousContainer>
#if BOOST_BEAST_DOXYGEN
    span&
#else
    typename std::enable_if<detail::is_contiguous_container<
        ContiguousContainer, T>::value,
    span&>::type
#endif
    operator=(ContiguousContainer&& container)
    {
        data_ = container.data();
        size_ = container.size();
        return *this;
    }

#if ! BOOST_BEAST_DOXYGEN
    template<class CharT, class Traits, class Allocator>
    span&
    operator=(std::basic_string<
        CharT, Traits, Allocator>& s)
    {
        data_ = &s[0];
        size_ = s.size();
        return *this;
    }

    template<class CharT, class Traits, class Allocator>
    span&
    operator=(std::basic_string<
        CharT, Traits, Allocator> const& s)
    {
        data_ = s.data();
        size_ = s.size();
        return *this;
    }
#endif

    /// Returns `true` if the span is empty
    bool
    empty() const
    {
        return size_ == 0;
    }

    /// Returns a pointer to the beginning of the span
    T*
    data() const
    {
        return data_;
    }

    /// Returns the number of elements in the span
    std::size_t
    size() const
    {
        return size_;
    }

    /// Returns an iterator to the beginning of the span
    const_iterator
    begin() const
    {
        return data_;
    }

    /// Returns an iterator to the beginning of the span
    const_iterator
    cbegin() const
    {
        return data_;
    }

    /// Returns an iterator to one past the end of the span
    const_iterator
    end() const
    {
        return data_ + size_;
    }

    /// Returns an iterator to one past the end of the span
    const_iterator
    cend() const
    {
        return data_ + size_;
    }
};

} // beast
} // boost

#endif

/* span.hpp
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
*/