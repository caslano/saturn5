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
#include <boost/type_traits/integral_constant.hpp>
#include <boost/locale/utf.hpp>
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
    int sync()
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
    int_type overflow(int_type c)
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
    std::streamsize xsputn(const char_type* s, std::streamsize n)
    {
        this_type::sync();
        return static_cast< std::streamsize >(this->append(s, static_cast< size_type >(n)));
    }

    //! Finds the string length so that it includes only complete characters, and does not exceed \a max_size
    size_type length_until_boundary(const char_type* s, size_type n, size_type max_size) const
    {
        BOOST_ASSERT(max_size <= n);
        return length_until_boundary(s, n, max_size, boost::integral_constant< bool, sizeof(char_type) == 1u >());
    }

private:
    //! Finds the string length so that it includes only complete characters, and does not exceed \a max_size
    size_type length_until_boundary(const char_type* s, size_type, size_type max_size, boost::true_type) const
    {
        std::locale loc = this->getloc();
        std::codecvt< wchar_t, char, std::mbstate_t > const& fac = std::use_facet< std::codecvt< wchar_t, char, std::mbstate_t > >(loc);
        std::mbstate_t mbs = std::mbstate_t();
        return static_cast< size_type >(fac.length(mbs, s, s + max_size, ~static_cast< std::size_t >(0u)));
    }

    //! Finds the string length so that it includes only complete characters, and does not exceed \a max_size
    static size_type length_until_boundary(const char_type* s, size_type n, size_type max_size, boost::false_type)
    {
        // Note: Although it's not required to be true for wchar_t, here we assume that the string has Unicode encoding.
        // Compilers use some version of Unicode for wchar_t on all tested platforms, and std::locale doesn't offer a way
        // to find the character boundary for character types other than char anyway.
        typedef boost::locale::utf::utf_traits< char_type > utf_traits;

        size_type pos = max_size;
        while (pos > 0u)
        {
            --pos;
            if (utf_traits::is_lead(s[pos]))
            {
                const char_type* p = s + pos;
                boost::locale::utf::code_point cp = utf_traits::decode(p, s + n);
                if (boost::locale::utf::is_valid_codepoint(cp) && p <= (s + max_size))
                    return static_cast< size_type >(p - s);
            }
        }

        return 0u;
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