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