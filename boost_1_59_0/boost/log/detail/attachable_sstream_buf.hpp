/*
 *          Copyright Andrey Semashev 2007 - 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attachable_sstream_buf.hpp
 * \author Andrey Semashev
 * \date   29.07.2007
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_ATTACHABLE_SSTREAM_BUF_HPP_INCLUDED_
#define BOOST_LOG_ATTACHABLE_SSTREAM_BUF_HPP_INCLUDED_

#include <cstddef>
#include <memory>
#include <locale>
#include <string>
#include <streambuf>
#include <boost/assert.hpp>
#include <boost/cstdint.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! A streambuf that puts the formatted data to an external string
template<
    typename CharT,
    typename TraitsT = std::char_traits< CharT >,
    typename AllocatorT = std::allocator< CharT >
>
class basic_ostringstreambuf :
    public std::basic_streambuf< CharT, TraitsT >
{
    //! Self type
    typedef basic_ostringstreambuf< CharT, TraitsT, AllocatorT > this_type;
    //! Base type
    typedef std::basic_streambuf< CharT, TraitsT > base_type;

    //! Buffer size
    enum { buffer_size = 16 };

public:
    //! Character type
    typedef typename base_type::char_type char_type;
    //! Traits type
    typedef typename base_type::traits_type traits_type;
    //! String type
    typedef std::basic_string< char_type, traits_type, AllocatorT > string_type;
    //! Size type
    typedef typename string_type::size_type size_type;
    //! Int type
    typedef typename base_type::int_type int_type;

    struct storage_state
    {
        //! A reference to the string that will be filled
        string_type* storage;
        //! Max size of the storage, in characters
        size_type max_size;
        //! Indicates that storage overflow happened
        bool overflow;

        BOOST_CONSTEXPR storage_state() BOOST_NOEXCEPT : storage(NULL), max_size(0u), overflow(false)
        {
        }
    };

private:
    //! Buffer storage state
    storage_state m_storage_state;
    //! A buffer used to temporarily store output
    char_type m_buffer[buffer_size];

public:
    //! Constructor
    basic_ostringstreambuf() BOOST_NOEXCEPT
    {
        base_type::setp(m_buffer, m_buffer + (sizeof(m_buffer) / sizeof(*m_buffer)));
    }
    //! Constructor
    explicit basic_ostringstreambuf(string_type& storage) BOOST_NOEXCEPT
    {
        base_type::setp(m_buffer, m_buffer + (sizeof(m_buffer) / sizeof(*m_buffer)));
        attach(storage);
    }

    storage_state const& get_storage_state() const BOOST_NOEXCEPT { return m_storage_state; }
    void set_storage_state(storage_state const& st) BOOST_NOEXCEPT { m_storage_state = st; }

    //! Detaches the buffer from the string
    void detach()
    {
        if (m_storage_state.storage)
        {
            this_type::sync();
            m_storage_state.storage = NULL;
            m_storage_state.max_size = 0u;
            m_storage_state.overflow = false;
        }
    }

    //! Attaches the buffer to another string
    void attach(string_type& storage)
    {
        attach(storage, storage.max_size());
    }

    //! Attaches the buffer to another string
    void attach(string_type& storage, size_type max_size)
    {
        detach();
        m_storage_state.storage = &storage;
        this->max_size(max_size);
    }

    //! Returns a pointer to the attached string
    string_type* storage() const BOOST_NOEXCEPT { return m_storage_state.storage; }

    //! Returns the maximum size of the storage
    size_type max_size() const BOOST_NOEXCEPT { return m_storage_state.max_size; }
    //! Sets the maximum size of the storage
    void max_size(size_type size)
    {
        if (m_storage_state.storage)
        {
            const size_type storage_max_size = m_storage_state.storage->max_size();
            size = size > storage_max_size ? storage_max_size : size;
        }

        m_storage_state.max_size = size;
        ensure_max_size();
    }
    //! Makes sure the storage does not exceed the max size limit. Should be called after the storage is modified externally.
    void ensure_max_size()
    {
        if (m_storage_state.storage && m_storage_state.storage->size() > m_storage_state.max_size)
        {
            const size_type len = length_until_boundary(m_storage_state.storage->c_str(), m_storage_state.storage->size(), m_storage_state.max_size);
            m_storage_state.storage->resize(len);
            m_storage_state.overflow = true;
        }
    }

    //! Returns true if the max size limit has been exceeded
    bool storage_overflow() const BOOST_NOEXCEPT { return m_storage_state.overflow; }
    //! Sets the overflow flag
    void storage_overflow(bool f) BOOST_NOEXCEPT { m_storage_state.overflow = f; }

    //! Returns the size left in the storage
    size_type size_left() const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(m_storage_state.storage != NULL);

        const size_type size = m_storage_state.storage->size();
        return size < m_storage_state.max_size ? m_storage_state.max_size - size : static_cast< size_type >(0u);
    }

    //! Appends a string to the storage and returns the number of written characters
    size_type append(const char_type* s, size_type n)
    {
        if (!m_storage_state.overflow)
        {
            BOOST_ASSERT(m_storage_state.storage != NULL);

            size_type left = size_left();
            BOOST_LOG_ASSUME(left <= m_storage_state.storage->max_size());
            if (BOOST_LIKELY(n <= left))
            {
                m_storage_state.storage->append(s, n);
                return n;
            }
            else
            {
                // We have to find out where the last character that fits before the limit ends
                left = length_until_boundary(s, n, left);
                m_storage_state.storage->append(s, left);
                m_storage_state.overflow = true;
                return left;
            }
        }
        return 0u;
    }

    //! Appends the specified number of characters to the storage and returns the number of written characters
    size_type append(size_type n, char_type c)
    {
        if (!m_storage_state.overflow)
        {
            BOOST_ASSERT(m_storage_state.storage != NULL);

            const size_type left = size_left();
            BOOST_LOG_ASSUME(left <= m_storage_state.storage->max_size());
            if (BOOST_LIKELY(n <= left))
            {
                m_storage_state.storage->append(n, c);
                return n;
            }
            else
            {
                m_storage_state.storage->append(left, c);
                m_storage_state.overflow = true;
                return left;
            }
        }
        return 0u;
    }

    //! Appends a character to the storage and returns the number of written characters
    size_type push_back(char_type c)
    {
        if (!m_storage_state.overflow)
        {
            BOOST_ASSERT(m_storage_state.storage != NULL);

            BOOST_LOG_ASSUME(m_storage_state.max_size <= m_storage_state.storage->max_size());
            if (BOOST_LIKELY(m_storage_state.storage->size() < m_storage_state.max_size))
            {
                m_storage_state.storage->push_back(c);
                return 1u;
            }
            else
            {
                m_storage_state.overflow = true;
                return 0u;
            }
        }
        return 0u;
    }

protected:
    //! Puts all buffered data to the string
    int sync() BOOST_OVERRIDE
    {
        char_type* pBase = this->pbase();
        char_type* pPtr = this->pptr();
        if (pBase != pPtr)
        {
            this->append(pBase, static_cast< size_type >(pPtr - pBase));
            this->pbump(static_cast< int >(pBase - pPtr));
        }
        return 0;
    }
    //! Puts an unbuffered character to the string
    int_type overflow(int_type c) BOOST_OVERRIDE
    {
        this_type::sync();
        if (!traits_type::eq_int_type(c, traits_type::eof()))
        {
            this->push_back(traits_type::to_char_type(c));
            return c;
        }
        else
            return traits_type::not_eof(c);
    }
    //! Puts a character sequence to the string
    std::streamsize xsputn(const char_type* s, std::streamsize n) BOOST_OVERRIDE
    {
        this_type::sync();
        return static_cast< std::streamsize >(this->append(s, static_cast< size_type >(n)));
    }

    //! Finds the string length so that it includes only complete characters, and does not exceed \a max_size
    size_type length_until_boundary(const char_type* s, size_type n, size_type max_size) const
    {
        BOOST_ASSERT(max_size <= n);
        return length_until_boundary(s, n, max_size, boost::integral_constant< std::size_t, sizeof(char_type) >());
    }

private:
    //! Finds the string length so that it includes only complete characters, and does not exceed \a max_size
    size_type length_until_boundary(const char_type* s, size_type, size_type max_size, boost::integral_constant< std::size_t, 1u >) const
    {
        std::locale loc = this->getloc();
        std::codecvt< wchar_t, char, std::mbstate_t > const& fac = std::use_facet< std::codecvt< wchar_t, char, std::mbstate_t > >(loc);
        std::mbstate_t mbs = std::mbstate_t();
        return static_cast< size_type >(fac.length(mbs, s, s + max_size, ~static_cast< std::size_t >(0u)));
    }

    //! Finds the string length so that it includes only complete characters, and does not exceed \a max_size
    static size_type length_until_boundary(const char_type* s, size_type n, size_type max_size, boost::integral_constant< std::size_t, 2u >)
    {
        // Note: Although it's not required to be true for wchar_t, here we assume that the string has Unicode encoding (UTF-16 or UCS-2).
        // Compilers use some version of Unicode for wchar_t on all tested platforms, and std::locale doesn't offer a way
        // to find the character boundary for character types other than char anyway.
        size_type pos = max_size;
        while (pos > 0u)
        {
            --pos;
            uint_fast16_t c = static_cast< uint_fast16_t >(s[pos]);
            // Check if this is a leading surrogate
            if ((c & 0xFC00u) != 0xD800u)
                return pos + 1u;
        }

        return 0u;
    }

    //! Finds the string length so that it includes only complete characters, and does not exceed \a max_size
    static size_type length_until_boundary(const char_type* s, size_type n, size_type max_size, boost::integral_constant< std::size_t, 4u >)
    {
        // In UTF-32 and UCS-4 one code point is encoded as one code unit
        return max_size;
    }

    //! Copy constructor (closed)
    BOOST_DELETED_FUNCTION(basic_ostringstreambuf(basic_ostringstreambuf const& that))
    //! Assignment (closed)
    BOOST_DELETED_FUNCTION(basic_ostringstreambuf& operator= (basic_ostringstreambuf const& that))
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTACHABLE_SSTREAM_BUF_HPP_INCLUDED_

/* attachable_sstream_buf.hpp
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
*/