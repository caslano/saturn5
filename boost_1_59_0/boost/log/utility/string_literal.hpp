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
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
*/