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
xvP/fkvfSnuAhlI+f595nQYPp52pnW+lCNpalEu+Po4kPKFcm01bU1d5CVprSYcbz8uaryMKa9cDcHcNZv/v6GHaV3oLO/8pLKOn8sO0Tej92gSU0MK4p8rt52irhUm5m7H69IPW1NsnE/0V/l3KSHQkak24bg39nNzb4piIGf5LWhLXjVzP76TZ+RV8VOI30RYM+hOjLsw/WuXvr+xEzgo92ssPSzhtLJ6X+EWObnpnPZx5Nsi9Mscw5DOtpbJsnmNfic/AZyXdUlXH74SOV+eK7RT6B+gSboQeLox+lXCqvrzLSj1TCzKd5eX+3GOevgW5TtRwP9JAOx1OOw2H0P3QYb6Xev4t1v3M/AQTf2loE7NfvCipRwN1vuFp5/dDGzQWHjDzVmOtGXggT/FVpJFHxbdX8ae0YU7+ELsZ8FxykbLVaStpw5DXir/yhLcuvnOaWnO6U9Jdp0XQ5iVF6BN6CFbzsrXRts/bLOnqIR9ole89vT/uPUw+fryZtEsesql2WSPpGqGeoFW+9/WeuDdbD8OXa2HpT6qvfIs13Ody8dvURhv3xv3vtIayNjarCvuLJJP9RZmFH5vtFrYW5RY+pvZa+LE5aOHH5pi3zxrhG/AS7oGXaItR63l324rpHnS9/dZ2ptuDNbmOI7IZURYrD3jIxWr6nHPm66W+cy+hS9XeqFdfrNSfI/P3ULZPPYReqUu8Ob9Zzpn6TVtJv03SJ6ny2lK2Mb+9L0emj1W2oLFCr9cl3rL+/Fa0oWsl6R/TW2u3muQWy6X8yK/Ez2JXSbfMJHvc886ykT0nne9NGlYRUs9QT/mi9ij0lfQr9CbQVLfRu0v9b1H5hiFnv2rZASRZ9IFxFn0gxaIPZFn0gXyLPjDLwn/a/APu/L3sxSvrs6mhrFUfW1FvTJ1/nYiYtPKjkacyZw/96axVc/2Hv2MYB1ms/yRyXeBm4BjgGGAGz/vOAk4B5pGeQ7oUmAHcCMzk+mwWfTlN4/nh03nefR7Xo2dwPXo+12kXAv/Nc9N1w88YMBJ4H7AVcBmwA/B+rk+XAlcCVwJ/AVwF3AdcDTwOXAP8ALgW+GfS35MOcjjpFkCDjiZ9HekkoFFeMnAdMAO4BXgX6dnA9cBS4AbgHvoE4nlm7KuQo97nman1nybAZlwHiuW6TBLXZVK5LjMT2InnwnfmOfhxwKXArvRJ1ZPtGw/8E7AX8EbdSY8F9gbm0/fTAvp+egB4Hdcd+wHXAq/n+mMCcBdwEPAl4A3AnKvku2gT1iYO+tYnfJfv+p+9/BGmXsH5f0YurE3TZOp/yXP/R9toaq9FEn/f/PgeDoQvjEXvveYxLh5dXJCRnJpWVJyak1yYPcf46TPZ/+YXmWztmNdPxmQYAlTbttdppytluY3DKyzq+FfUsdSyjjkYB6UW4cBYjmO961f6I+uHslg/dzvXb40K8UzPOgxzEVNmVb+pBRkZ9m3HPBESHy11n4rvxjmAOV75Xs3JzmN8lim+tjb+GpBaapjz/aKrYbOq2t9ksxot7+ysA+dX9B0qz1XtwE7g1Q6zEXPQqh1y5UNxrkKf0eYziytvB8bbt8NBj3ZIrrwdhpvagWNx1KeG7eDqU1n+3vy6rynsX+zbITl9BkqpBi+an5MU4P2cIjynopLncEuAqd2N3myys/boG+GqfXOz85xJqTdwTxtWjbqzH7F9pTCxqQ1Tbcln8D2HuPY8BFi2J/5U/p7ZqTkoLL3Kepl5uFmg97O+NOY9Vs8qLsxIr8Z7m8vPCaJdK+1qurOPRFmVP6fSPsI8EUofEC90e7s+w/RNbfsM4037xwoyikz6gwH7XGf7j5L5fSjeZXUjYLBbP5P9OtU=
*/