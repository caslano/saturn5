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