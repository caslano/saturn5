/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   format.hpp
 * \author Andrey Semashev
 * \date   15.11.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_FORMAT_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_FORMAT_HPP_INCLUDED_

#include <cstddef>
#include <string>
#include <vector>
#include <iosfwd>
#include <boost/assert.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/core/uncaught_exceptions.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/cleanup_scope_guard.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! An element (either literal or placeholder) of the format string
struct format_element
{
    //! Argument placeholder number or -1 if it's not a placeholder (i.e. a literal)
    int arg_number;
    //! If the element describes a constant literal, the starting character and length of the literal
    unsigned int literal_start_pos, literal_len;

    format_element() : arg_number(0), literal_start_pos(0), literal_len(0)
    {
    }

    static format_element literal(unsigned int start_pos, unsigned int len)
    {
        format_element el;
        el.arg_number = -1;
        el.literal_start_pos = start_pos;
        el.literal_len = len;
        return el;
    }

    static format_element positional_argument(unsigned int arg_n)
    {
        format_element el;
        el.arg_number = arg_n;
        return el;
    }
};

//! Parsed format string description
template< typename CharT >
struct format_description
{
    BOOST_COPYABLE_AND_MOVABLE_ALT(format_description)

public:
    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;

    //! Array of format element descriptors
    typedef std::vector< format_element > format_element_list;

    //! Characters of all literal parts of the format string
    string_type literal_chars;
    //! Format element descriptors
    format_element_list format_elements;

    BOOST_DEFAULTED_FUNCTION(format_description(), {})

    format_description(format_description const& that) : literal_chars(that.literal_chars), format_elements(that.format_elements)
    {
    }

    format_description(BOOST_RV_REF(format_description) that) BOOST_NOEXCEPT
    {
        literal_chars.swap(that.literal_chars);
        format_elements.swap(that.format_elements);
    }

    format_description& operator= (format_description that) BOOST_NOEXCEPT
    {
        literal_chars.swap(that.literal_chars);
        format_elements.swap(that.format_elements);
        return *this;
    }
};

//! Parses format string
template< typename CharT >
BOOST_LOG_API format_description< CharT > parse_format(const CharT* begin, const CharT* end);

//! Parses format string
template< typename CharT >
BOOST_FORCEINLINE format_description< CharT > parse_format(const CharT* begin)
{
    return parse_format(begin, begin + std::char_traits< CharT >::length(begin));
}

//! Parses format string
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_FORCEINLINE format_description< CharT > parse_format(std::basic_string< CharT, TraitsT, AllocatorT > const& fmt)
{
    const CharT* begin = fmt.c_str();
    return parse_format(begin, begin + fmt.size());
}

//! Formatter object
template< typename CharT >
class basic_format
{
public:
    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;
    //! Stream type
    typedef basic_formatting_ostream< char_type > stream_type;
    //! Format description type
    typedef format_description< char_type > format_description_type;

    //! The pump receives arguments and formats them into strings. At destruction the pump composes the final string in the attached stream.
    class pump;
    friend class pump;

private:
    //! Formatting params for a single placeholder in the format string
    struct formatting_params
    {
        //! Formatting element index in the format description
        unsigned int element_idx;
        //! Formatting result
        string_type target;

        formatting_params() : element_idx(~0u) {}
    };
    typedef std::vector< formatting_params > formatting_params_list;

private:
    //! Format string description
    format_description_type m_format;
    //! Formatting parameters for all placeholders
    formatting_params_list m_formatting_params;
    //! Current formatting position
    unsigned int m_current_idx;

public:
    //! Initializing constructor
    explicit basic_format(string_type const& fmt) : m_format(aux::parse_format(fmt)), m_current_idx(0)
    {
        init_params();
    }
    //! Initializing constructor
    explicit basic_format(const char_type* fmt) : m_format(aux::parse_format(fmt)), m_current_idx(0)
    {
        init_params();
    }

    //! Clears all formatted strings and resets the current formatting position
    void clear() BOOST_NOEXCEPT
    {
        for (typename formatting_params_list::iterator it = m_formatting_params.begin(), end = m_formatting_params.end(); it != end; ++it)
        {
            it->target.clear();
        }
        m_current_idx = 0;
    }

    //! Creates a pump that will receive all format arguments and put the formatted string into the stream
    pump make_pump(stream_type& strm)
    {
        // Flush the stream beforehand so that the pump can safely switch the stream storage string
        strm.flush();
        return pump(*this, strm);
    }

    //! Composes the final string from the formatted pieces
    string_type str() const
    {
        string_type result;
        compose(result);
        return BOOST_LOG_NRVO_RESULT(result);
    }

private:
    //! Initializes the formatting params
    void init_params()
    {
        typename format_description_type::format_element_list::const_iterator it = m_format.format_elements.begin(), end = m_format.format_elements.end();
        for (; it != end; ++it)
        {
            if (it->arg_number >= 0)
            {
                if (static_cast< unsigned int >(it->arg_number) >= m_formatting_params.size())
                    m_formatting_params.resize(it->arg_number + 1);
                m_formatting_params[it->arg_number].element_idx = static_cast< unsigned int >(it - m_format.format_elements.begin());
            }
        }
    }

    //! Composes the final string from the formatted pieces
    template< typename T >
    void compose(T& str) const
    {
        typename format_description_type::format_element_list::const_iterator it = m_format.format_elements.begin(), end = m_format.format_elements.end();
        for (; it != end; ++it)
        {
            if (it->arg_number >= 0)
            {
                // This is a placeholder
                string_type const& target = m_formatting_params[it->arg_number].target;
                str.append(target.data(), target.size());
            }
            else
            {
                // This is a literal
                const char_type* p = m_format.literal_chars.c_str() + it->literal_start_pos;
                str.append(p, it->literal_len);
            }
        }
    }
};

//! The pump receives arguments and formats them into strings. At destruction the pump composes the final string in the attached stream.
template< typename CharT >
class basic_format< CharT >::pump
{
    BOOST_MOVABLE_BUT_NOT_COPYABLE(pump)

private:
    //! The guard temporarily replaces storage string in the specified stream
    struct scoped_storage
    {
        scoped_storage(stream_type& strm, string_type& storage) : m_stream(strm), m_storage_state_backup(strm.rdbuf()->get_storage_state())
        {
            strm.attach(storage);
        }
        ~scoped_storage()
        {
            m_stream.rdbuf()->set_storage_state(m_storage_state_backup);
        }

    private:
        stream_type& m_stream;
        typename stream_type::streambuf_type::storage_state m_storage_state_backup;
    };

private:
    //! Reference to the owner
    basic_format* m_owner;
    //! Reference to the stream
    stream_type* m_stream;
    //! Unhandled exception count
    const unsigned int m_exception_count;

public:
    //! Initializing constructor
    pump(basic_format& owner, stream_type& strm) BOOST_NOEXCEPT : m_owner(&owner), m_stream(&strm), m_exception_count(boost::core::uncaught_exceptions())
    {
    }

    //! Move constructor
    pump(BOOST_RV_REF(pump) that) BOOST_NOEXCEPT : m_owner(that.m_owner), m_stream(that.m_stream), m_exception_count(that.m_exception_count)
    {
        that.m_owner = NULL;
        that.m_stream = NULL;
    }

    //! Destructor
    ~pump() BOOST_NOEXCEPT_IF(false)
    {
        if (m_owner)
        {
            // Whether or not the destructor is called because of an exception, the format object has to be cleared
            boost::log::aux::cleanup_guard< basic_format< char_type > > cleanup1(*m_owner);

            BOOST_ASSERT(m_stream != NULL);
            if (m_exception_count >= boost::core::uncaught_exceptions())
            {
                // Compose the final string in the stream buffer
                m_stream->flush();
                m_owner->compose(*m_stream->rdbuf());
            }
        }
    }

    /*!
     * Puts an argument to the formatter. Note the pump has to be returned by value and not by reference in order this to
     * work with Boost.Phoenix expressions. Otherwise the pump that is returned from \c basic_format::make_pump is
     * destroyed after the first call to \c operator%, and the returned reference becomes dangling.
     */
    template< typename T >
    pump operator% (T const& val)
    {
        BOOST_ASSERT_MSG(m_owner != NULL && m_stream != NULL, "Boost.Log: This basic_format::pump has already been moved from");

        if (m_owner->m_current_idx < m_owner->m_formatting_params.size())
        {
            scoped_storage storage_guard(*m_stream, m_owner->m_formatting_params[m_owner->m_current_idx].target);

            *m_stream << val;
            m_stream->flush();

            ++m_owner->m_current_idx;
        }

        return boost::move(*this);
    }
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_FORMAT_HPP_INCLUDED_

/* format.hpp
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
*/