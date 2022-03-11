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