//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_STATIC_STRING_HPP
#define BOOST_BEAST_STATIC_STRING_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/core/detail/static_string.hpp>
#include <algorithm>
#include <cstdint>
#include <initializer_list>
#include <iosfwd>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace boost {
namespace beast {

/** A modifiable string with a fixed-size storage area.

    These objects behave like `std::string` except that the storage
    is not dynamically allocated but rather fixed in size.

    These strings offer performance advantages when a protocol
    imposes a natural small upper limit on the size of a value.

    @note The stored string is always null-terminated.

    @see to_static_string 
*/
template<
    std::size_t N,
    class CharT = char,
    class Traits = std::char_traits<CharT>>
class static_string
{
    template<std::size_t, class, class>
    friend class static_string;

    void
    term()
    {
        Traits::assign(s_[n_], 0);
    }

    std::size_t n_;
    CharT s_[N+1];

public:
    //
    // Member types
    //

    using traits_type = Traits;
    using value_type = typename Traits::char_type;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using reference = value_type&;
    using const_pointer = value_type const*;
    using const_reference = value_type const&;
    using iterator = value_type*;
    using const_iterator = value_type const*;
    using reverse_iterator =
        std::reverse_iterator<iterator>;
    using const_reverse_iterator =
        std::reverse_iterator<const_iterator>;

    /// The type of `string_view` returned by the interface
    using string_view_type =
        basic_string_view<CharT, Traits>;

    //
    // Constants
    //

    /// Maximum size of the string excluding the null terminator
    static std::size_t constexpr max_size_n = N;

    /// A special index
    static constexpr size_type npos = size_type(-1);

    //
    // (constructor)
    //

    /// Default constructor (empty string).
    static_string();

    /** Construct with count copies of character `ch`.
    
        The behavior is undefined if `count >= npos`
    */
    static_string(size_type count, CharT ch);

    /// Construct with a substring (pos, other.size()) of `other`.
    template<std::size_t M>
    static_string(static_string<M, CharT, Traits> const& other,
        size_type pos);

    /// Construct with a substring (pos, count) of `other`.
    template<std::size_t M>
    static_string(static_string<M, CharT, Traits> const& other,
        size_type pos, size_type count);

    /// Construct with the first `count` characters of `s`, including nulls.
    static_string(CharT const* s, size_type count);

    /// Construct from a null terminated string.
    static_string(CharT const* s);

    /// Construct from a range of characters
    template<class InputIt>
    static_string(InputIt first, InputIt last);

    /// Copy constructor.
    static_string(static_string const& other);

    /// Copy constructor.
    template<std::size_t M>
    static_string(static_string<M, CharT, Traits> const& other);

    /// Construct from an initializer list
    static_string(std::initializer_list<CharT> init);

    /// Construct from a `string_view`
    explicit
    static_string(string_view_type sv);

    /** Construct from any object convertible to `string_view_type`.

        The range (pos, n) is extracted from the value
        obtained by converting `t` to `string_view_type`,
        and used to construct the string.
    */
#if BOOST_BEAST_DOXYGEN
    template<class T>
#else
    template<class T, class = typename std::enable_if<
        std::is_convertible<T, string_view_type>::value>::type>
#endif
    static_string(T const& t, size_type pos, size_type n);

    //
    // (assignment)
    //

    /// Copy assignment.
    static_string&
    operator=(static_string const& str)
    {
        return assign(str);
    }

    /// Copy assignment.
    template<std::size_t M>
    static_string&
    operator=(static_string<M, CharT, Traits> const& str)
    {
        return assign(str);
    }

    /// Assign from null-terminated string.
    static_string&
    operator=(CharT const* s);

    /// Assign from single character.
    static_string&
    operator=(CharT ch)
    {
        return assign_char(ch,
            std::integral_constant<bool, (N>0)>{});
    }

    /// Assign from initializer list.
    static_string&
    operator=(std::initializer_list<CharT> init)
    {
        return assign(init);
    }

    /// Assign from `string_view_type`.
    static_string&
    operator=(string_view_type sv)
    {
        return assign(sv);
    }

    /// Assign `count` copies of `ch`.
    static_string&
    assign(size_type count, CharT ch);

    /// Assign from another `static_string`
    static_string&
    assign(static_string const& str);

    // VFALCO NOTE this could come in two flavors,
    //             N>M and N<M, and skip the exception
    //             check when N>M

    /// Assign from another `static_string`
    template<std::size_t M>
    static_string&
    assign(static_string<M, CharT, Traits> const& str)
    {
        return assign(str.data(), str.size());
    }

    /// Assign `count` characterss starting at `npos` from `other`.
    template<std::size_t M>
    static_string&
    assign(static_string<M, CharT, Traits> const& str,
        size_type pos, size_type count = npos);

    /// Assign the first `count` characters of `s`, including nulls.
    static_string&
    assign(CharT const* s, size_type count);

    /// Assign a null terminated string.
    static_string&
    assign(CharT const* s)
    {
        return assign(s, Traits::length(s));
    }

    /// Assign from an iterator range of characters.
    template<class InputIt>
    static_string&
    assign(InputIt first, InputIt last);

    /// Assign from initializer list.
    static_string&
    assign(std::initializer_list<CharT> init)
    {
        return assign(init.begin(), init.end());
    }

    /// Assign from `string_view_type`.
    static_string&
    assign(string_view_type str)
    {
        return assign(str.data(), str.size());
    }

    /** Assign from any object convertible to `string_view_type`.

        The range (pos, n) is extracted from the value
        obtained by converting `t` to `string_view_type`,
        and used to assign the string.
    */
    template<class T>
#if BOOST_BEAST_DOXYGEN
    static_string&
#else
    typename std::enable_if<std::is_convertible<T,
        string_view_type>::value, static_string&>::type
#endif
    assign(T const& t,
        size_type pos, size_type count = npos);

    //
    // Element access
    //

    /// Access specified character with bounds checking.
    reference
    at(size_type pos);

    /// Access specified character with bounds checking.
    const_reference
    at(size_type pos) const;

    /// Access specified character.
    reference
    operator[](size_type pos)
    {
        return s_[pos];
    }

    /// Access specified character.
    const_reference
    operator[](size_type pos) const
    {
        return s_[pos];
    }

    /// Accesses the first character.
    CharT&
    front()
    {
        return s_[0];
    }

    /// Accesses the first character.
    CharT const&
    front() const
    {
        return s_[0];
    }

    /// Accesses the last character.
    CharT&
    back()
    {
        return s_[n_-1];
    }

    /// Accesses the last character.
    CharT const&
    back() const
    {
        return s_[n_-1];
    }

    /// Returns a pointer to the first character of a string.
    CharT*
    data()
    {
        return &s_[0];
    }

    /// Returns a pointer to the first character of a string.
    CharT const*
    data() const
    {
        return &s_[0];
    }

    /// Returns a non-modifiable standard C character array version of the string.
    CharT const*
    c_str() const
    {
        return data();
    }

    /// Convert a static string to a `string_view_type`
    operator string_view_type() const
    {
        return basic_string_view<
            CharT, Traits>{data(), size()};
    }

    //
    // Iterators
    //

    /// Returns an iterator to the beginning.
    iterator
    begin()
    {
        return &s_[0];
    }

    /// Returns an iterator to the beginning.
    const_iterator
    begin() const
    {
        return &s_[0];
    }

    /// Returns an iterator to the beginning.
    const_iterator
    cbegin() const
    {
        return &s_[0];
    }

    /// Returns an iterator to the end.
    iterator
    end()
    {
        return &s_[n_];
    }

    /// Returns an iterator to the end.
    const_iterator
    end() const
    {
        return &s_[n_];
    }

    /// Returns an iterator to the end.
    const_iterator
    cend() const
    {
        return &s_[n_];
    }

    /// Returns a reverse iterator to the beginning.
    reverse_iterator
    rbegin()
    {
        return reverse_iterator{end()};
    }

    /// Returns a reverse iterator to the beginning.
    const_reverse_iterator
    rbegin() const
    {
        return const_reverse_iterator{cend()};
    }

    /// Returns a reverse iterator to the beginning.
    const_reverse_iterator
    crbegin() const
    {
        return const_reverse_iterator{cend()};
    }

    /// Returns a reverse iterator to the end.
    reverse_iterator
    rend()
    {
        return reverse_iterator{begin()};
    }

    /// Returns a reverse iterator to the end.
    const_reverse_iterator
    rend() const
    {
        return const_reverse_iterator{cbegin()};
    }

    /// Returns a reverse iterator to the end.
    const_reverse_iterator
    crend() const
    {
        return const_reverse_iterator{cbegin()};
    }

    //
    // Capacity
    //

    /// Returns `true` if the string is empty.
    bool
    empty() const
    {
        return n_ == 0;
    }

    /// Returns the number of characters, excluding the null terminator.
    size_type
    size() const
    {
        return n_;
    }

    /// Returns the number of characters, excluding the null terminator.
    size_type
    length() const
    {
        return size();
    }

    /// Returns the maximum number of characters that can be stored, excluding the null terminator.
    size_type constexpr
    max_size() const
    {
        return N;
    }

    /** Reserves storage.

        This actually just throws an exception if `n > N`,
        otherwise does nothing since the storage is fixed.
    */
    void
    reserve(std::size_t n);

    /// Returns the number of characters that can be held in currently allocated storage.
    size_type constexpr
    capacity() const
    {
        return max_size();
    }
    
    /** Reduces memory usage by freeing unused memory.

        This actually does nothing, since the storage is fixed.
    */
    void
    shrink_to_fit()
    {
    }

    //
    // Operations
    //

    /// Clears the contents.
    void
    clear();

    static_string&
    insert(size_type index, size_type count, CharT ch);

    static_string&
    insert(size_type index, CharT const* s)
    {
        return insert(index, s, Traits::length(s));
    }

    static_string&
    insert(size_type index, CharT const* s, size_type count);

    template<std::size_t M>
    static_string&
    insert(size_type index,
        static_string<M, CharT, Traits> const& str)
    {
        return insert(index, str.data(), str.size());
    }

    template<std::size_t M>
    static_string&
    insert(size_type index,
        static_string<M, CharT, Traits> const& str,
            size_type index_str, size_type count = npos);

    iterator
    insert(const_iterator pos, CharT ch)
    {
        return insert(pos, 1, ch);
    }

    iterator
    insert(const_iterator pos, size_type count, CharT ch);

    template<class InputIt>
#if BOOST_BEAST_DOXYGEN
    iterator
#else
    typename std::enable_if<
        detail::is_input_iterator<InputIt>::value,
            iterator>::type
#endif
    insert(const_iterator pos, InputIt first, InputIt last);

    iterator
    insert(const_iterator pos, std::initializer_list<CharT> init)
    {
        return insert(pos, init.begin(), init.end());
    }

    static_string&
    insert(size_type index, string_view_type str)
    {
        return insert(index, str.data(), str.size());
    }

    template<class T>
#if BOOST_BEAST_DOXYGEN
    static_string&
#else
    typename std::enable_if<
        std::is_convertible<T const&, string_view_type>::value &&
        ! std::is_convertible<T const&, CharT const*>::value,
            static_string&>::type
#endif
    insert(size_type index, T const& t,
        size_type index_str, size_type count = npos);

    static_string&
    erase(size_type index = 0, size_type count = npos);

    iterator
    erase(const_iterator pos);

    iterator
    erase(const_iterator first, const_iterator last);

    void
    push_back(CharT ch);

    void
    pop_back()
    {
        Traits::assign(s_[--n_], 0);
    }

    static_string&
    append(size_type count, CharT ch)
    {
        insert(end(), count, ch);
        return *this;
    }

    template<std::size_t M>
    static_string&
    append(static_string<M, CharT, Traits> const& str)
    {
        insert(size(), str);
        return *this;
    }

    template<std::size_t M>
    static_string&
    append(static_string<M, CharT, Traits> const& str,
        size_type pos, size_type count = npos);

    static_string&
    append(CharT const* s, size_type count)
    {
        insert(size(), s, count);
        return *this;
    }

    static_string&
    append(CharT const* s)
    {
        insert(size(), s);
        return *this;
    }

    template<class InputIt>
#if BOOST_BEAST_DOXYGEN
    static_string&
#else
    typename std::enable_if<
        detail::is_input_iterator<InputIt>::value,
            static_string&>::type
#endif
    append(InputIt first, InputIt last)
    {
        insert(end(), first, last);
        return *this;
    }

    static_string&
    append(std::initializer_list<CharT> init)
    {
        insert(end(), init);
        return *this;
    }

    static_string&
    append(string_view_type sv)
    {
        insert(size(), sv);
        return *this;
    }

    template<class T>
    typename std::enable_if<
        std::is_convertible<T const&, string_view_type>::value &&
        ! std::is_convertible<T const&, CharT const*>::value,
            static_string&>::type
    append(T const& t, size_type pos, size_type count = npos)
    {
        insert(size(), t, pos, count);
        return *this;
    }

    template<std::size_t M>
    static_string&
    operator+=(static_string<M, CharT, Traits> const& str)
    {
        return append(str.data(), str.size());
    }

    static_string&
    operator+=(CharT ch)
    {
        push_back(ch);
        return *this;
    }

    static_string&
    operator+=(CharT const* s)
    {
        return append(s);
    }

    static_string&
    operator+=(std::initializer_list<CharT> init)
    {
        return append(init);
    }

    static_string&
    operator+=(string_view_type const& str)
    {
        return append(str);
    }

    template<std::size_t M>
    int
    compare(static_string<M, CharT, Traits> const& str) const
    {
        return detail::lexicographical_compare<CharT, Traits>(
            &s_[0], n_, &str.s_[0], str.n_);
    }

    template<std::size_t M>
    int
    compare(size_type pos1, size_type count1,
        static_string<M, CharT, Traits> const& str) const
    {
        return detail::lexicographical_compare<CharT, Traits>(
            substr(pos1, count1), str.data(), str.size());
    }

    template<std::size_t M>
    int
    compare(size_type pos1, size_type count1,
        static_string<M, CharT, Traits> const& str,
            size_type pos2, size_type count2 = npos) const
    {
        return detail::lexicographical_compare(
            substr(pos1, count1), str.substr(pos2, count2));
    }

    int
    compare(CharT const* s) const
    {
        return detail::lexicographical_compare<CharT, Traits>(
            &s_[0], n_, s, Traits::length(s));
    }

    int
    compare(size_type pos1, size_type count1,
        CharT const* s) const
    {
        return detail::lexicographical_compare<CharT, Traits>(
            substr(pos1, count1), s, Traits::length(s));
    }

    int
    compare(size_type pos1, size_type count1,
        CharT const*s, size_type count2) const
    {
        return detail::lexicographical_compare<CharT, Traits>(
            substr(pos1, count1), s, count2);
    }

    int
    compare(string_view_type str) const
    {
        return detail::lexicographical_compare<CharT, Traits>(
            &s_[0], n_, str.data(), str.size());
    }

    int
    compare(size_type pos1, size_type count1,
        string_view_type str) const
    {
        return detail::lexicographical_compare<CharT, Traits>(
            substr(pos1, count1), str);
    }

    template<class T>
#if BOOST_BEAST_DOXYGEN
    int
#else
    typename std::enable_if<
        std::is_convertible<T const&, string_view_type>::value &&
        ! std::is_convertible<T const&, CharT const*>::value,
            int>::type
#endif
    compare(size_type pos1, size_type count1,
        T const& t, size_type pos2,
            size_type count2 = npos) const
    {
        return compare(pos1, count1,
            string_view_type(t).substr(pos2, count2));
    }

    string_view_type
    substr(size_type pos = 0, size_type count = npos) const;

    /// Copy a substring (pos, pos+count) to character string pointed to by `dest`.
    size_type
    copy(CharT* dest, size_type count, size_type pos = 0) const;

    /** Changes the number of characters stored.

        If the resulting string is larger, the new
        characters are uninitialized.
    */
    void
    resize(std::size_t n);

    /** Changes the number of characters stored.

        If the resulting string is larger, the new
        characters are initialized to the value of `c`.
    */
    void
    resize(std::size_t n, CharT c);

    /// Exchange the contents of this string with another.
    void
    swap(static_string& str);

    /// Exchange the contents of this string with another.
    template<std::size_t M>
    void
    swap(static_string<M, CharT, Traits>& str);

    //
    // Search
    //

private:
    static_string&
    assign_char(CharT ch, std::true_type);

    static_string&
    assign_char(CharT ch, std::false_type);
};

//
// Disallowed operations
//

// These operations are explicitly deleted since
// there is no reasonable implementation possible.

template<std::size_t N, std::size_t M, class CharT, class Traits>
void
operator+(
    static_string<N, CharT, Traits>const&,
    static_string<M, CharT, Traits>const&) = delete;

template<std::size_t N, class CharT, class Traits>
void
operator+(CharT const*,
    static_string<N, CharT, Traits>const&) = delete;

template<std::size_t N, class CharT, class Traits>
void
operator+(CharT,
    static_string<N, CharT, Traits> const&) = delete;

template<std::size_t N, class CharT, class Traits>
void
operator+(static_string<N, CharT, Traits> const&,
    CharT const*) = delete;

template<std::size_t N, class CharT, class Traits>
void
operator+(static_string<N, CharT, Traits> const&, CharT) = delete;

//
// Non-member functions
//

template<std::size_t N, std::size_t M,
    class CharT, class Traits>
bool
operator==(
    static_string<N, CharT, Traits> const& lhs,
    static_string<M, CharT, Traits> const& rhs)
{
    return lhs.compare(rhs) == 0;
}

template<std::size_t N, std::size_t M,
    class CharT, class Traits>
bool
operator!=(
    static_string<N, CharT, Traits> const& lhs,
    static_string<M, CharT, Traits> const& rhs)
{
    return lhs.compare(rhs) != 0;
}

template<std::size_t N, std::size_t M,
    class CharT, class Traits>
bool
operator<(
    static_string<N, CharT, Traits> const& lhs,
    static_string<M, CharT, Traits> const& rhs)
{
    return lhs.compare(rhs) < 0;
}

template<std::size_t N, std::size_t M,
    class CharT, class Traits>
bool
operator<=(
    static_string<N, CharT, Traits> const& lhs,
    static_string<M, CharT, Traits> const& rhs)
{
    return lhs.compare(rhs) <= 0;
}

template<std::size_t N, std::size_t M,
    class CharT, class Traits>
bool
operator>(
    static_string<N, CharT, Traits> const& lhs,
    static_string<M, CharT, Traits> const& rhs)
{
    return lhs.compare(rhs) > 0;
}

template<std::size_t N, std::size_t M,
    class CharT, class Traits>
bool
operator>=(
    static_string<N, CharT, Traits> const& lhs,
    static_string<M, CharT, Traits> const& rhs)
{
    return lhs.compare(rhs) >= 0;
}

template<std::size_t N, class CharT, class Traits>
bool
operator==(
    CharT const* lhs,
    static_string<N, CharT, Traits> const& rhs)
{
    return detail::lexicographical_compare<CharT, Traits>(
        lhs, Traits::length(lhs),
        rhs.data(), rhs.size()) == 0;
}

template<std::size_t N, class CharT, class Traits>
bool
operator==(
    static_string<N, CharT, Traits> const& lhs,
    CharT const* rhs)
{
    return detail::lexicographical_compare<CharT, Traits>(
        lhs.data(), lhs.size(),
        rhs, Traits::length(rhs)) == 0;
}

template<std::size_t N, class CharT, class Traits>
bool
operator!=(
    CharT const* lhs,
    static_string<N, CharT, Traits> const& rhs)
{
    return detail::lexicographical_compare<CharT, Traits>(
        lhs, Traits::length(lhs),
        rhs.data(), rhs.size()) != 0;
}

template<std::size_t N, class CharT, class Traits>
bool
operator!=(
    static_string<N, CharT, Traits> const& lhs,
    CharT const* rhs)
{
    return detail::lexicographical_compare<CharT, Traits>(
        lhs.data(), lhs.size(),
        rhs, Traits::length(rhs)) != 0;
}

template<std::size_t N, class CharT, class Traits>
bool
operator<(
    CharT const* lhs,
    static_string<N, CharT, Traits> const& rhs)
{
    return detail::lexicographical_compare<CharT, Traits>(
        lhs, Traits::length(lhs),
        rhs.data(), rhs.size()) < 0;
}

template<std::size_t N, class CharT, class Traits>
bool
operator<(
    static_string<N, CharT, Traits> const& lhs,
    CharT const* rhs)
{
    return detail::lexicographical_compare<CharT, Traits>(
        lhs.data(), lhs.size(),
        rhs, Traits::length(rhs)) < 0;
}

template<std::size_t N, class CharT, class Traits>
bool
operator<=(
    CharT const* lhs,
    static_string<N, CharT, Traits> const& rhs)
{
    return detail::lexicographical_compare<CharT, Traits>(
        lhs, Traits::length(lhs),
        rhs.data(), rhs.size()) <= 0;
}

template<std::size_t N, class CharT, class Traits>
bool
operator<=(
    static_string<N, CharT, Traits> const& lhs,
    CharT const* rhs)
{
    return detail::lexicographical_compare<CharT, Traits>(
        lhs.data(), lhs.size(),
        rhs, Traits::length(rhs)) <= 0;
}

template<std::size_t N, class CharT, class Traits>
bool
operator>(
    CharT const* lhs,
    static_string<N, CharT, Traits> const& rhs)
{
    return detail::lexicographical_compare<CharT, Traits>(
        lhs, Traits::length(lhs),
        rhs.data(), rhs.size()) > 0;
}

template<std::size_t N, class CharT, class Traits>
bool
operator>(
    static_string<N, CharT, Traits> const& lhs,
    CharT const* rhs)
{
    return detail::lexicographical_compare<CharT, Traits>(
        lhs.data(), lhs.size(),
        rhs, Traits::length(rhs)) > 0;
}

template<std::size_t N, class CharT, class Traits>
bool
operator>=(
    CharT const* lhs,
    static_string<N, CharT, Traits> const& rhs)
{
    return detail::lexicographical_compare<CharT, Traits>(
        lhs, Traits::length(lhs),
        rhs.data(), rhs.size()) >= 0;
}

template<std::size_t N, class CharT, class Traits>
bool
operator>=(
    static_string<N, CharT, Traits> const& lhs,
    CharT const* rhs)
{
    return detail::lexicographical_compare<CharT, Traits>(
        lhs.data(), lhs.size(),
        rhs, Traits::length(rhs)) >= 0;
}

//
// swap
//

template<std::size_t N, class CharT, class Traits>
void
swap(
    static_string<N, CharT, Traits>& lhs,
    static_string<N, CharT, Traits>& rhs)
{
    lhs.swap(rhs);
}

template<std::size_t N, std::size_t M,
    class CharT, class Traits>
void
swap(
    static_string<N, CharT, Traits>& lhs,
    static_string<M, CharT, Traits>& rhs)
{
    lhs.swap(rhs);
}

//
// Input/Output
//

template<std::size_t N, class CharT, class Traits>
std::basic_ostream<CharT, Traits>& 
operator<<(std::basic_ostream<CharT, Traits>& os, 
    static_string<N, CharT, Traits> const& str)
{
    return os << static_cast<
        beast::basic_string_view<CharT, Traits>>(str);
}

//
// Numeric conversions
//

/** Returns a static string representing an integer as a decimal.

    @param x The signed or unsigned integer to convert.
    This must be an integral type.

    @return A @ref static_string with an implementation defined
    maximum size large enough to hold the longest possible decimal
    representation of any integer of the given type.
*/
template<
    class Integer
#ifndef BOOST_BEAST_DOXYGEN
    ,class = typename std::enable_if<
        std::is_integral<Integer>::value>::type
#endif
>
static_string<detail::max_digits(sizeof(Integer))>
to_static_string(Integer x);

} // beast
} // boost

#include <boost/beast/core/impl/static_string.hpp>

#endif

/* static_string.hpp
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
*/