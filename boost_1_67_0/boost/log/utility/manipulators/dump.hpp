/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   dump.hpp
 * \author Andrey Semashev
 * \date   03.05.2013
 *
 * This header contains the \c dump output manipulator.
 */

#ifndef BOOST_LOG_UTILITY_MANIPULATORS_DUMP_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_MANIPULATORS_DUMP_HPP_INCLUDED_

#include <cstddef>
#include <iosfwd>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

typedef void dump_data_char_t(const void* data, std::size_t size, std::basic_ostream< char >& strm);
extern BOOST_LOG_API dump_data_char_t* dump_data_char;
BOOST_FORCEINLINE void dump_data(const void* data, std::size_t size, std::basic_ostream< char >& strm)
{
    (dump_data_char)(data, size, strm);
}

typedef void dump_data_wchar_t(const void* data, std::size_t size, std::basic_ostream< wchar_t >& strm);
extern BOOST_LOG_API dump_data_wchar_t* dump_data_wchar;
BOOST_FORCEINLINE void dump_data(const void* data, std::size_t size, std::basic_ostream< wchar_t >& strm)
{
    (dump_data_wchar)(data, size, strm);
}

#if !defined(BOOST_NO_CXX11_CHAR16_T)
typedef void dump_data_char16_t(const void* data, std::size_t size, std::basic_ostream< char16_t >& strm);
extern BOOST_LOG_API dump_data_char16_t* dump_data_char16;
BOOST_FORCEINLINE void dump_data(const void* data, std::size_t size, std::basic_ostream< char16_t >& strm)
{
    (dump_data_char16)(data, size, strm);
}
#endif

#if !defined(BOOST_NO_CXX11_CHAR32_T)
typedef void dump_data_char32_t(const void* data, std::size_t size, std::basic_ostream< char32_t >& strm);
extern BOOST_LOG_API dump_data_char32_t* dump_data_char32;
BOOST_FORCEINLINE void dump_data(const void* data, std::size_t size, std::basic_ostream< char32_t >& strm)
{
    (dump_data_char32)(data, size, strm);
}
#endif

template< std::size_t SizeV, typename R >
struct enable_dump_size_based
{
};

template< typename R >
struct enable_dump_size_based< 1u, R >
{
    typedef R type;
};

template< typename T, typename R >
struct enable_dump :
    public enable_dump_size_based< sizeof(T), R >
{
};

template< typename R >
struct enable_dump< void, R >
{
    typedef R type;
};

template< typename R >
struct enable_dump< const void, R >
{
    typedef R type;
};

template< typename R >
struct enable_dump< volatile void, R >
{
    typedef R type;
};

template< typename R >
struct enable_dump< const volatile void, R >
{
    typedef R type;
};

} // namespace aux

/*!
 * \brief Manipulator for printing binary representation of the data
 */
class dump_manip
{
private:
    //! Beginning of the data
    const void* m_data;
    //! Size of the data, in bytes
    std::size_t m_size;

public:
    dump_manip(const void* data, std::size_t size) BOOST_NOEXCEPT : m_data(data), m_size(size) {}
    dump_manip(dump_manip const& that) BOOST_NOEXCEPT : m_data(that.m_data), m_size(that.m_size) {}

    const void* get_data() const BOOST_NOEXCEPT { return m_data; }
    std::size_t get_size() const BOOST_NOEXCEPT { return m_size; }
};

//! The operator outputs binary data to a stream
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (std::basic_ostream< CharT, TraitsT >& strm, dump_manip const& manip)
{
    if (BOOST_LIKELY(strm.good()))
        aux::dump_data(manip.get_data(), manip.get_size(), strm);

    return strm;
}

/*!
 * \brief Manipulator for printing binary representation of the data with a size limit
 */
class bounded_dump_manip :
    public dump_manip
{
private:
    //! Maximum size to output, in bytes
    std::size_t m_max_size;

public:
    bounded_dump_manip(const void* data, std::size_t size, std::size_t max_size) BOOST_NOEXCEPT : dump_manip(data, size), m_max_size(max_size) {}
    bounded_dump_manip(bounded_dump_manip const& that) BOOST_NOEXCEPT : dump_manip(static_cast< dump_manip const& >(that)), m_max_size(that.m_max_size) {}

    std::size_t get_max_size() const BOOST_NOEXCEPT { return m_max_size; }
};

//! The operator outputs binary data to a stream
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (std::basic_ostream< CharT, TraitsT >& strm, bounded_dump_manip const& manip)
{
    if (BOOST_LIKELY(strm.good()))
    {
        const std::size_t size = manip.get_size(), max_size = manip.get_max_size();
        if (max_size >= size)
        {
            aux::dump_data(manip.get_data(), size, strm);
        }
        else
        {
            aux::dump_data(manip.get_data(), max_size, strm);
            strm << " and " << (size - max_size) << " bytes more";
        }
    }

    return strm;
}

/*!
 * \brief Creates a stream manipulator that will output contents of a memory region in hexadecimal form
 * \param data The pointer to the beginning of the region
 * \param size The size of the region, in bytes
 * \return The manipulator that is to be put to a stream
 */
template< typename T >
inline typename aux::enable_dump< T, dump_manip >::type dump(T* data, std::size_t size) BOOST_NOEXCEPT
{
    return dump_manip((const void*)data, size);
}

/*!
 * \brief Creates a stream manipulator that will dump elements of an array in hexadecimal form
 * \param data The pointer to the beginning of the array
 * \param count The size of the region, in number of \c T elements
 * \return The manipulator that is to be put to a stream
 */
template< typename T >
inline dump_manip dump_elements(T* data, std::size_t count) BOOST_NOEXCEPT
{
    return dump_manip((const void*)data, count * sizeof(T));
}

/*!
 * \brief Creates a stream manipulator that will output contents of a memory region in hexadecimal form
 * \param data The pointer to the beginning of the region
 * \param size The size of the region, in bytes
 * \param max_size The maximum number of bytes of the region to output
 * \return The manipulator that is to be put to a stream
 */
template< typename T >
inline typename aux::enable_dump< T, bounded_dump_manip >::type dump(T* data, std::size_t size, std::size_t max_size) BOOST_NOEXCEPT
{
    return bounded_dump_manip((const void*)data, size, max_size);
}

/*!
 * \brief Creates a stream manipulator that will dump elements of an array in hexadecimal form
 * \param data The pointer to the beginning of the array
 * \param count The size of the region, in number of \c T elements
 * \param max_count The maximum number of elements to output
 * \return The manipulator that is to be put to a stream
 */
template< typename T >
inline bounded_dump_manip dump_elements(T* data, std::size_t count, std::size_t max_count) BOOST_NOEXCEPT
{
    return bounded_dump_manip((const void*)data, count * sizeof(T), max_count * sizeof(T));
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_MANIPULATORS_DUMP_HPP_INCLUDED_

/* dump.hpp
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
*/