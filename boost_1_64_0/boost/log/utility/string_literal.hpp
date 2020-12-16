/*
 *          Copyright Andrey Semashev 2007 - 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   string_literal.hpp
 * \author Andrey Semashev
 * \date   24.06.2007
 *
 * The header contains implementation of a constant string literal wrapper.
 */

#ifndef BOOST_LOG_UTILITY_STRING_LITERAL_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_STRING_LITERAL_HPP_INCLUDED_

#include <cstddef>
#include <stdexcept>
#include <iosfwd>
#include <ios> // std::streamsize
#include <string>
#include <iterator>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/utility/string_literal_fwd.hpp>
#include <boost/log/detail/sfinae_tools.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief String literal wrapper
 *
 * The \c basic_string_literal is a thin wrapper around a constant string literal.
 * It provides interface similar to STL strings, but because of read-only nature
 * of string literals, lacks ability to modify string contents. However,
 * \c basic_string_literal objects can be assigned to and cleared.
 *
 * The main advantage of this class comparing to other string classes is that
 * it doesn't dynamically allocate memory and therefore is fast, thin and exception safe.
 */
template< typename CharT, typename TraitsT >
class basic_string_literal
{
    //! Self type
    typedef basic_string_literal< CharT, TraitsT > this_type;

public:
    typedef CharT value_type;
    typedef TraitsT traits_type;

    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef const value_type* const_pointer;
    typedef value_type const& const_reference;
    typedef const value_type* const_iterator;
    typedef std::reverse_iterator< const_iterator > const_reverse_iterator;

    //! Corresponding STL string type
    typedef std::basic_string< value_type, traits_type > string_type;

private:
    //! Pointer to the beginning of the literal
    const_pointer m_pStart;
    //! Length
    size_type m_Len;

    //! Empty string literal to support \c clear
#if !defined(BOOST_LOG_NO_CXX11_CONSTEXPR_DATA_MEMBER_BRACE_INITIALIZERS)
    static constexpr value_type g_EmptyString[1] = { 0 };
#else
    static const value_type g_EmptyString[1];
#endif

public:
    /*!
     * Constructor
     *
     * \post <tt>empty() == true</tt>
     */
    BOOST_CONSTEXPR basic_string_literal() BOOST_NOEXCEPT : m_pStart(g_EmptyString), m_Len(0) { }

    /*!
     * Constructor from a string literal
     *
     * \post <tt>*this == p</tt>
     * \param p A zero-terminated constant sequence of characters
     */
    template< typename T, size_type LenV >
    BOOST_CONSTEXPR basic_string_literal(T(&p)[LenV]
        //! \cond
        , typename boost::enable_if_c< is_same< T, const value_type >::value, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()
        //! \endcond
        ) BOOST_NOEXCEPT
        : m_pStart(p), m_Len(LenV - 1)
    {
    }

    /*!
     * Copy constructor
     *
     * \post <tt>*this == that</tt>
     * \param that Source literal to copy string from
     */
    BOOST_CONSTEXPR basic_string_literal(basic_string_literal const& that) BOOST_NOEXCEPT : m_pStart(that.m_pStart), m_Len(that.m_Len) {}

    /*!
     * Assignment operator
     *
     * \post <tt>*this == that</tt>
     * \param that Source literal to copy string from
     */
    BOOST_CXX14_CONSTEXPR this_type& operator= (this_type const& that) BOOST_NOEXCEPT
    {
        return assign(that);
    }
    /*!
     * Assignment from a string literal
     *
     * \post <tt>*this == p</tt>
     * \param p A zero-terminated constant sequence of characters
     */
    template< typename T, size_type LenV >
    BOOST_CXX14_CONSTEXPR
#ifndef BOOST_LOG_DOXYGEN_PASS
    typename boost::enable_if_c<
        is_same< T, const value_type >::value,
        this_type&
    >::type
#else
    this_type&
#endif // BOOST_LOG_DOXYGEN_PASS
    operator= (T(&p)[LenV]) BOOST_NOEXCEPT
    {
        return assign(p);
    }

    /*!
     * Lexicographical comparison (equality)
     *
     * \param that Comparand
     * \return \c true if the comparand string equals to this string, \c false otherwise
     */
    bool operator== (this_type const& that) const BOOST_NOEXCEPT
    {
        return (compare_internal(m_pStart, m_Len, that.m_pStart, that.m_Len) == 0);
    }
    /*!
     * Lexicographical comparison (equality)
     *
     * \param str Comparand. Must point to a zero-terminated sequence of characters, must not be NULL.
     * \return \c true if the comparand string equals to this string, \c false otherwise
     */
    bool operator== (const_pointer str) const BOOST_NOEXCEPT
    {
        return (compare_internal(m_pStart, m_Len, str, traits_type::length(str)) == 0);
    }
    /*!
     * Lexicographical comparison (equality)
     *
     * \param that Comparand
     * \return \c true if the comparand string equals to this string, \c false otherwise
     */
    bool operator== (string_type const& that) const BOOST_NOEXCEPT
    {
        return (compare_internal(m_pStart, m_Len, that.c_str(), that.size()) == 0);
    }

    /*!
     * Lexicographical comparison (inequality)
     *
     * \param that Comparand
     * \return \c true if the comparand string is not equal to this string, \c false otherwise
     */
    bool operator!= (this_type const& that) const BOOST_NOEXCEPT
    {
        return (compare_internal(m_pStart, m_Len, that.m_pStart, that.m_Len) != 0);
    }
    /*!
     * Lexicographical comparison (inequality)
     *
     * \param str Comparand. Must point to a zero-terminated sequence of characters, must not be NULL.
     * \return \c true if the comparand string is not equal to this string, \c false otherwise
     */
    bool operator!= (const_pointer str) const BOOST_NOEXCEPT
    {
        return (compare_internal(m_pStart, m_Len, str, traits_type::length(str)) != 0);
    }
    /*!
     * Lexicographical comparison (inequality)
     *
     * \param that Comparand
     * \return \c true if the comparand string is not equal to this string, \c false otherwise
     */
    bool operator!= (string_type const& that) const BOOST_NOEXCEPT
    {
        return (compare_internal(m_pStart, m_Len, that.c_str(), that.size()) != 0);
    }

    /*!
     * Lexicographical comparison (less ordering)
     *
     * \param that Comparand
     * \return \c true if this string is less than the comparand, \c false otherwise
     */
    bool operator< (this_type const& that) const BOOST_NOEXCEPT
    {
        return (compare_internal(m_pStart, m_Len, that.m_pStart, that.m_Len) < 0);
    }
    /*!
     * Lexicographical comparison (less ordering)
     *
     * \param str Comparand. Must point to a zero-terminated sequence of characters, must not be NULL.
     * \return \c true if this string is less than the comparand, \c false otherwise
     */
    bool operator< (const_pointer str) const BOOST_NOEXCEPT
    {
        return (compare_internal(m_pStart, m_Len, str, traits_type::length(str)) < 0);
    }
    /*!
     * Lexicographical comparison (less ordering)
     *
     * \param that Comparand
     * \return \c true if this string is less than the comparand, \c false otherwise
     */
    bool operator< (string_type const& that) const BOOST_NOEXCEPT
    {
        return (compare_internal(m_pStart, m_Len, that.c_str(), that.size()) < 0);
    }

    /*!
     * Lexicographical comparison (less or equal ordering)
     *
     * \param that Comparand
     * \return \c true if this string is less or equal to the comparand, \c false otherwise
     */
    bool operator<= (this_type const& that) const BOOST_NOEXCEPT
    {
        return (compare_internal(m_pStart, m_Len, that.m_pStart, that.m_Len) <= 0);
    }
    /*!
     * Lexicographical comparison (less or equal ordering)
     *
     * \param str Comparand. Must point to a zero-terminated sequence of characters, must not be NULL.
     * \return \c true if this string is less or equal to the comparand, \c false otherwise
     */
    bool operator<= (const_pointer str) const BOOST_NOEXCEPT
    {
        return (compare_internal(m_pStart, m_Len, str, traits_type::length(str)) <= 0);
    }
    /*!
     * Lexicographical comparison (less or equal ordering)
     *
     * \param that Comparand
     * \return \c true if this string is less or equal to the comparand, \c false otherwise
     */
    bool operator<= (string_type const& that) const BOOST_NOEXCEPT
    {
        return (compare_internal(m_pStart, m_Len, that.c_str(), that.size()) <= 0);
    }

    /*!
     * Lexicographical comparison (greater ordering)
     *
     * \param that Comparand
     * \return \c true if this string is greater than the comparand, \c false otherwise
     */
    bool operator> (this_type const& that) const BOOST_NOEXCEPT
    {
        return (compare_internal(m_pStart, m_Len, that.m_pStart, that.m_Len) > 0);
    }
    /*!
     * Lexicographical comparison (greater ordering)
     *
     * \param str Comparand. Must point to a zero-terminated sequence of characters, must not be NULL.
     * \return \c true if this string is greater than the comparand, \c false otherwise
     */
    bool operator> (const_pointer str) const BOOST_NOEXCEPT
    {
        return (compare_internal(m_pStart, m_Len, str, traits_type::length(str)) > 0);
    }
    /*!
     * Lexicographical comparison (greater ordering)
     *
     * \param that Comparand
     * \return \c true if this string is greater than the comparand, \c false otherwise
     */
    bool operator> (string_type const& that) const BOOST_NOEXCEPT
    {
        return (compare_internal(m_pStart, m_Len, that.c_str(), that.size()) > 0);
    }

    /*!
     * Lexicographical comparison (greater or equal ordering)
     *
     * \param that Comparand
     * \return \c true if this string is greater or equal to the comparand, \c false otherwise
     */
    bool operator>= (this_type const& that) const BOOST_NOEXCEPT
    {
        return (compare_internal(m_pStart, m_Len, that.m_pStart, that.m_Len) >= 0);
    }
    /*!
     * Lexicographical comparison (greater or qual ordering)
     *
     * \param str Comparand. Must point to a zero-terminated sequence of characters, must not be NULL.
     * \return \c true if this string is greater or equal to the comparand, \c false otherwise
     */
    bool operator>= (const_pointer str) const BOOST_NOEXCEPT
    {
        return (compare_internal(m_pStart, m_Len, str, traits_type::length(str)) >= 0);
    }
    /*!
     * Lexicographical comparison (greater or equal ordering)
     *
     * \param that Comparand
     * \return \c true if this string is greater or equal to the comparand, \c false otherwise
     */
    bool operator>= (string_type const& that) const BOOST_NOEXCEPT
    {
        return (compare_internal(m_pStart, m_Len, that.c_str(), that.size()) >= 0);
    }

    /*!
     * Subscript operator
     *
     * \pre <tt>i < size()</tt>
     * \param i Requested character index
     * \return Constant reference to the requested character
     */
    BOOST_CONSTEXPR const_reference operator[] (size_type i) const BOOST_NOEXCEPT
    {
        return m_pStart[i];
    }
    /*!
     * Checked subscript
     *
     * \param i Requested character index
     * \return Constant reference to the requested character
     *
     * \b Throws: An <tt>std::exception</tt>-based exception if index \a i is out of string boundaries
     */
    const_reference at(size_type i) const
    {
        if (BOOST_UNLIKELY(i >= m_Len))
            BOOST_THROW_EXCEPTION(std::out_of_range("basic_string_literal::at: the index value is out of range"));
        return m_pStart[i];
    }

    /*!
     * \return Pointer to the beginning of the literal
     */
    BOOST_CONSTEXPR const_pointer c_str() const BOOST_NOEXCEPT { return m_pStart; }
    /*!
     * \return Pointer to the beginning of the literal
     */
    BOOST_CONSTEXPR const_pointer data() const BOOST_NOEXCEPT { return m_pStart; }
    /*!
     * \return Length of the literal
     */
    BOOST_CONSTEXPR size_type size() const BOOST_NOEXCEPT { return m_Len; }
    /*!
     * \return Length of the literal
     */
    BOOST_CONSTEXPR size_type length() const BOOST_NOEXCEPT { return m_Len; }

    /*!
     * \return \c true if the literal is an empty string, \c false otherwise
     */
    BOOST_CONSTEXPR bool empty() const BOOST_NOEXCEPT
    {
        return (m_Len == 0);
    }

    /*!
     * \return Iterator that points to the first character of the literal
     */
    BOOST_CONSTEXPR const_iterator begin() const BOOST_NOEXCEPT { return m_pStart; }
    /*!
     * \return Iterator that points after the last character of the literal
     */
    BOOST_CONSTEXPR const_iterator end() const BOOST_NOEXCEPT { return m_pStart + m_Len; }
    /*!
     * \return Reverse iterator that points to the last character of the literal
     */
    const_reverse_iterator rbegin() const BOOST_NOEXCEPT { return const_reverse_iterator(end()); }
    /*!
     * \return Reverse iterator that points before the first character of the literal
     */
    const_reverse_iterator rend() const BOOST_NOEXCEPT { return const_reverse_iterator(begin()); }

    /*!
     * \return STL string constructed from the literal
     */
    string_type str() const
    {
        return string_type(m_pStart, m_Len);
    }

    /*!
     * The method clears the literal
     *
     * \post <tt>empty() == true</tt>
     */
    BOOST_CXX14_CONSTEXPR void clear() BOOST_NOEXCEPT
    {
        m_pStart = g_EmptyString;
        m_Len = 0;
    }
    /*!
     * The method swaps two literals
     */
    BOOST_CXX14_CONSTEXPR void swap(this_type& that) BOOST_NOEXCEPT
    {
        const_pointer p = m_pStart;
        m_pStart = that.m_pStart;
        that.m_pStart = p;

        size_type l = m_Len;
        m_Len = that.m_Len;
        that.m_Len = l;
    }

    /*!
     * Assignment from another literal
     *
     * \post <tt>*this == that</tt>
     * \param that Source literal to copy string from
     */
    BOOST_CXX14_CONSTEXPR this_type& assign(this_type const& that) BOOST_NOEXCEPT
    {
        m_pStart = that.m_pStart;
        m_Len = that.m_Len;
        return *this;
    }
    /*!
     * Assignment from another literal
     *
     * \post <tt>*this == p</tt>
     * \param p A zero-terminated constant sequence of characters
     */
    template< typename T, size_type LenV >
    BOOST_CXX14_CONSTEXPR
#ifndef BOOST_LOG_DOXYGEN_PASS
    typename boost::enable_if_c<
        is_same< T, const value_type >::value,
        this_type&
    >::type
#else
    this_type&
#endif // BOOST_LOG_DOXYGEN_PASS
    assign(T(&p)[LenV]) BOOST_NOEXCEPT
    {
        m_pStart = p;
        m_Len = LenV - 1;
        return *this;
    }

    /*!
     * The method copies the literal or its portion to an external buffer
     *
     * \pre <tt>pos <= size()</tt>
     * \param str Pointer to the external buffer beginning. Must not be NULL.
     *            The buffer must have enough capacity to accommodate the requested number of characters.
     * \param n Maximum number of characters to copy
     * \param pos Starting position to start copying from
     * \return Number of characters copied
     *
     * \b Throws: An <tt>std::exception</tt>-based exception if \a pos is out of range.
     */
    size_type copy(value_type* str, size_type n, size_type pos = 0) const
    {
        if (BOOST_UNLIKELY(pos > m_Len))
            BOOST_THROW_EXCEPTION(std::out_of_range("basic_string_literal::copy: the position is out of range"));

        size_type len = m_Len - pos;
        if (len > n)
            len = n;
        traits_type::copy(str, m_pStart + pos, len);
        return len;
    }

    /*!
     * Lexicographically compares the argument string to a part of this string
     *
     * \pre <tt>pos <= size()</tt>
     * \param pos Starting position within this string to perform comparison to
     * \param n Length of the substring of this string to perform comparison to
     * \param str Comparand. Must point to a sequence of characters, must not be NULL.
     * \param len Number of characters in the sequence \a str.
     * \return Zero if the comparand equals this string, a negative value if this string is less than the comparand,
     *         a positive value if this string is greater than the comparand.
     *
     * \b Throws: An <tt>std::exception</tt>-based exception if \a pos is out of range.
     */
    int compare(size_type pos, size_type n, const_pointer str, size_type len) const
    {
        if (BOOST_UNLIKELY(pos > m_Len))
            BOOST_THROW_EXCEPTION(std::out_of_range("basic_string_literal::compare: the position is out of range"));

        size_type compare_size = m_Len - pos;
        if (compare_size > len)
            compare_size = len;
        if (compare_size > n)
            compare_size = n;
        return compare_internal(m_pStart + pos, compare_size, str, compare_size);
    }
    /*!
     * Lexicographically compares the argument string to a part of this string
     *
     * \pre <tt>pos <= size()</tt>
     * \param pos Starting position within this string to perform comparison to
     * \param n Length of the substring of this string to perform comparison to
     * \param str Comparand. Must point to a zero-terminated sequence of characters, must not be NULL.
     * \return Zero if the comparand equals this string, a negative value if this string is less than the comparand,
     *         a positive value if this string is greater than the comparand.
     *
     * \b Throws: An <tt>std::exception</tt>-based exception if \a pos is out of range.
     */
    int compare(size_type pos, size_type n, const_pointer str) const BOOST_NOEXCEPT
    {
        return compare(pos, n, str, traits_type::length(str));
    }
    /*!
     * Lexicographically compares the argument string literal to a part of this string
     *
     * \pre <tt>pos <= size()</tt>
     * \param pos Starting position within this string to perform comparison to
     * \param n Length of the substring of this string to perform comparison to
     * \param that Comparand
     * \return Zero if the comparand equals this string, a negative value if this string is less than the comparand,
     *         a positive value if this string is greater than the comparand.
     *
     * \b Throws: An <tt>std::exception</tt>-based exception if \a pos is out of range.
     */
    int compare(size_type pos, size_type n, this_type const& that) const BOOST_NOEXCEPT
    {
        return compare(pos, n, that.c_str(), that.size());
    }
    /*!
     * Lexicographically compares the argument string to this string
     *
     * \param str Comparand. Must point to a sequence of characters, must not be NULL.
     * \param len Number of characters in the sequence \a str.
     * \return Zero if the comparand equals this string, a negative value if this string is less than the comparand,
     *         a positive value if this string is greater than the comparand.
     */
    int compare(const_pointer str, size_type len) const BOOST_NOEXCEPT
    {
        return compare(0, m_Len, str, len);
    }
    /*!
     * Lexicographically compares the argument string to this string
     *
     * \param str Comparand. Must point to a zero-terminated sequence of characters, must not be NULL.
     * \return Zero if the comparand equals this string, a negative value if this string is less than the comparand,
     *         a positive value if this string is greater than the comparand.
     */
    int compare(const_pointer str) const BOOST_NOEXCEPT
    {
        return compare(0, m_Len, str, traits_type::length(str));
    }
    /*!
     * Lexicographically compares the argument string to this string
     *
     * \param that Comparand
     * \return Zero if the comparand equals this string, a negative value if this string is less than the comparand,
     *         a positive value if this string is greater than the comparand.
     */
    int compare(this_type const& that) const BOOST_NOEXCEPT
    {
        return compare(0, m_Len, that.c_str(), that.size());
    }

private:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Internal comparison implementation
    static int compare_internal(const_pointer pLeft, size_type LeftLen, const_pointer pRight, size_type RightLen) BOOST_NOEXCEPT
    {
        if (pLeft != pRight)
        {
            const int result = traits_type::compare(pLeft, pRight, (LeftLen < RightLen ? LeftLen : RightLen));
            if (result != 0)
                return result;
        }
        return LeftLen < RightLen ? -1 : (LeftLen > RightLen ? 1 : 0);
    }
#endif // BOOST_LOG_DOXYGEN_PASS
};

#if !defined(BOOST_LOG_NO_CXX11_CONSTEXPR_DATA_MEMBER_BRACE_INITIALIZERS)
template< typename CharT, typename TraitsT >
constexpr typename basic_string_literal< CharT, TraitsT >::value_type
basic_string_literal< CharT, TraitsT >::g_EmptyString[1];
#else
template< typename CharT, typename TraitsT >
const typename basic_string_literal< CharT, TraitsT >::value_type
basic_string_literal< CharT, TraitsT >::g_EmptyString[1] = { 0 };
#endif

namespace aux {

template< typename CharT, typename TraitsT >
inline void insert_fill_chars(std::basic_ostream< CharT, TraitsT >& strm, std::size_t n)
{
    enum { chunk_size = 8 };
    CharT fill_chars[chunk_size];
    const CharT filler = strm.fill();
    for (unsigned int i = 0; i < chunk_size; ++i)
        fill_chars[i] = filler;
    for (; n >= chunk_size && strm.good(); n -= chunk_size)
        strm.write(fill_chars, static_cast< std::size_t >(chunk_size));
    if (n > 0 && strm.good())
        strm.write(fill_chars, n);
}

template< typename CharT, typename TraitsT >
void insert_aligned(std::basic_ostream< CharT, TraitsT >& strm, const CharT* p, std::size_t size)
{
    const std::size_t alignment_size = static_cast< std::size_t >(strm.width()) - size;
    const bool align_left = (strm.flags() & std::basic_ostream< CharT, TraitsT >::adjustfield) == std::basic_ostream< CharT, TraitsT >::left;
    if (align_left)
    {
        strm.write(p, size);
        if (strm.good())
            aux::insert_fill_chars(strm, alignment_size);
    }
    else
    {
        aux::insert_fill_chars(strm, alignment_size);
        if (strm.good())
            strm.write(p, size);
    }
}

} // namespace aux

//! Output operator
template< typename CharT, typename StrmTraitsT, typename LitTraitsT >
inline std::basic_ostream< CharT, StrmTraitsT >& operator<< (
    std::basic_ostream< CharT, StrmTraitsT >& strm, basic_string_literal< CharT, LitTraitsT > const& lit)
{
    if (strm.good())
    {
        const std::size_t size = lit.size();
        const std::size_t w = static_cast< std::size_t >(strm.width());
        if (w <= size)
            strm.write(lit.c_str(), static_cast< std::streamsize >(size));
        else
            aux::insert_aligned(strm, lit.c_str(), lit.size());
        strm.width(0);
    }
    return strm;
}

//! External swap
template< typename CharT, typename TraitsT >
inline BOOST_CXX14_CONSTEXPR void swap(basic_string_literal< CharT, TraitsT >& left, basic_string_literal< CharT, TraitsT >& right) BOOST_NOEXCEPT
{
    left.swap(right);
}

//! Creates a string literal wrapper from a constant string literal
#ifdef BOOST_LOG_USE_CHAR
template< typename T, std::size_t LenV >
inline BOOST_CONSTEXPR
#ifndef BOOST_LOG_DOXYGEN_PASS
typename boost::enable_if_c<
    is_same< T, const char >::value,
    string_literal
>::type
#else
basic_string_literal< T >
#endif // BOOST_LOG_DOXYGEN_PASS
str_literal(T(&p)[LenV]) BOOST_NOEXCEPT
{
    return string_literal(p);
}
#endif

#ifndef BOOST_LOG_DOXYGEN_PASS

#ifdef BOOST_LOG_USE_WCHAR_T
template< typename T, std::size_t LenV >
inline BOOST_CONSTEXPR typename boost::enable_if_c<
    is_same< T, const wchar_t >::value,
    wstring_literal
>::type
str_literal(T(&p)[LenV]) BOOST_NOEXCEPT
{
    return wstring_literal(p);
}
#endif

#endif // BOOST_LOG_DOXYGEN_PASS

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_STRING_LITERAL_HPP_INCLUDED_

/* string_literal.hpp
RMjhDnK8pc3d+evvyNr4bwdxK+swj/+etchXj/Mqwe7zKm5pxvNczD/tCSf8OhmB+4L7wL0Ic/wqrnNeA5SOtmtw5pAhbnmewnXYibL0G3ebFpH3TvsL/PdrEWfDAqiHcoCwRX6K/IDffgPT+w6Blf6O8VXuJj4ikoREeGhfEEbB+Suum8f8d78f3PL8Tx+c2T9zwFD9rIMc7ub5iInkrfBcvfZArz+4rHNErs7fRuG+eKutk9v3WC6vzrUfHBJIBtG5tD79C6tFS8k1aS+lAX1VrUnvanWoy7s2nWeoQ7/0qU1L+tahfUw1aY5ffXrHvzZtYq5P5wfWpF8ENaFlgutR929UzV3Dv4GT79tDe3l89uEdv26khts3gMJeypUPCAkgu9gJNp51V2axG9pkNs0whYX5TmGb/aaweuYp7HjQXOb+LZYlr/MzO3hYgUJ26EWeDiElcIK4UUpli5W+rKJXJnvdMIgl+2ayb/16saHmp5lq6cvS3L6pe47H7UZYMXIRZ8XXwDeGa1N/+XfSWSlNV6m3yY+anVb1vouXBKPoYZ+bxMc3mnY03SZr/KLoBX8DrWEuS58JvEkOBtmpX/Bt0inETteEBlIeX5Hnm/k9wvHuIuIrZKV5HrwcZiNd6VZanspSMRovR9KFSjH6rRpJHV4WOsg7kr5uCKeSMZIm+haj2aYK9KxfKC0bEEkHmUvQ3YE2KlmK0RbBtehzIT/QKiIfvGB+5Gl7x+JLPpZ+kZCm6lgW4j2ebfYZy2qbJrDj/mNZauBMFi3yyQtm4jp+joQ5AKdvv8QmsOrKBHZYm8BSDNPYj8YJ7Bm/CSw3X0OE+0Zrc91fthjJSxauryi3R7i+MsYa0FfIpnJ994facJL7r2w0m6ZMZiW8xrIthmdYHd9J7BOEnWaexG4FTWMLQyK5LsHC7wJ+nw1BAThNfCWbzKoiXgcRr1aGyey8cTIbDb++5vu6hAg/frwcFjdbyTC2nQ1ijZVB7HNtEOuF8nDbOIjN9hvEGoo4+8PsepHnUbiKk4+pNJ3NU+axKK8ZbIdhNmviO5t94Teb9TbPY7eDFrAFIWa2Pqwc+TisKfpk6CjCeJaHUScE52woDZU+7FOtD+th6MNuGvuwmX59mNXch70c1Ifx+iL83OH5VJ+nVYiQfcXTb2BERTJRypGeZS51PvuL1yzWx2cuu+M7l831n8siA+ezXZb5LD70Vx5egHgvd8lr/DwiXjfMQnach1ctRCb92HD2BnMq05B+z7KnDDPYT8bZbCx0M5qz2eqg2Tx/A4W/G1wfLVwmV8I65cZPyP14nNNDMJtCT9KLOGN/Ps2UL5GOylJ6W71Eftay6Qzvy6gzz9HixkvE7LuAbjVdQp15jjYMuERqmJ+jnwZeIkeCltLewVd5WxHKw4ZZzcstjlq/quuVa3dW6MXLmZB9zvXyyitnXJbC/b8dpuFk/2/ZHDZYWcA0r+lsKfKxgu8c9prfPNbSPJudCVrKxoRUZ0kiL0JhEnn53xVoIIvoi/QKWcEW0zj5HKmsLKafqN+Rd7TFtJP3FZJiWEiv+Vwg54wr6HTTd2So3zIaHnCOeJtX8XIbIsIry8N7MUjF6fTL2CxWWZnC3tJmoT5NZ+eMU9hQv+nM2zxX19MKM+m1vP4YegrZGa5npQgvYovg7biQb+a69g71xmpbXfo8PYs2dIBymWSqi6nq9QP5zWsxXWL4gczwWUztvj+QCNNCutfvEtnqv5gmmc+S2MDF9HTQD+Rjyyo6OuQs4eVShP0tD1sl7SALFjKN16kmwQac4vwyvYwz7BfSOvIvpKqygH6kXiEHkT5pSJ/2hsX0us8VctGYTSeZfiGj/RY=
*/