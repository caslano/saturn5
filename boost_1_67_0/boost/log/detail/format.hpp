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

    format_description(BOOST_RV_REF(format_description) that)
    {
        literal_chars.swap(that.literal_chars);
        format_elements.swap(that.format_elements);
    }

    format_description& operator= (format_description that)
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