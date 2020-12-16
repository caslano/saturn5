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
X/iq+v81eC58Hc6Cb8B8uAcuhW/CW2G9vp8j8C64G/5K7zfBd+Bv4HtwJ3wfvg0/gH+BH8JP4AEYiT//CnvBepgKj8B0+Ck8U/WzVX8kPATPgX+HU1U/Fx6GF+j955KRjPEz3onGRyfUIZ812WvgQPgsHAxvgTmwFi6Et8Fr4B2wBq6Dm+B6+By8B74C74VvwU3wHXgf/Cu8H34JH4CH4a9hDP55CHaCW2AX+AhMg4/CAfAxeBq8Gw6DG+AI+AScCZ+EhfApeCF8GpbDZ+ASSHgkHg4YYyqwo8ZDEmqvxsPzuofATijpAWbA3Rovr8Ph8A04Bv4J5sI34Sz4Zzhf3MMf8G14EXwXXg3fh6vgfngT/ADeDA/AdfCvGp+fwF3wM7gHHoZvwpc0HIdgqOe9w9bwSxgPv4JJEHkz/9Q0kX9u1Pxzk+afNWa+0z502M3B3iC1dwbsCoeovXqjXxqeqvF7Mmq/2ovX+E2GmbAbHAt7wKmwF8yDp8BK2AdeDvvC5TANXgszNf5O0/jrp/GXDu+B/TUeB8Fn4RlwJzwTvgyHwHfhUE2PY+AROFbjdRyMhGfDNnA4bA9HwG5wJDxFzTV/aR+n9Ls2yl+TkGsFp8EucDocAHPhmfB8OBTOgFPgpbAAXgZL4DK4GF4OK+CPND1doOkpD/4Y5sOfwDmaPwvgjbBQ42kuXA/nw42wGN4LL4Sb4UL4CCyFT8My+Ht4EdwOF2s8VsIv4CUab5db0ltZE+lttaab6zS9XQ8Ne/uaqA+Eqr0w2A6Gq71al/ahaB/UHrW/Wu3dq+X2/VquPKDl1gswA26BA+HDcCL8jX73H4OF8HG4DD4Ja+FT8FH4HHwa/h4+r+79AW7X7zv3Gi5t+8O2DuHK1nANg23gcIu9dU3Exze6J8MR2A5+C7Ucp/3qvxyv1efdDhPgWo2Pn8N0+Astx++E2XAdHKX66i/ae/7L8fXq/t0a3xvgrFDKnqtkz4Sj7pWwZTn7H0xkTTzK2C8h98qGPRPqYQn3NaitqOhJDfsn7PmU31exPh9l7KVwkE3Ns7gfhFyuz74K+ej77q1wGEZ59k3AbD1qB2ov+qnoHeF31NXevReSYeP9FyD6xh4MVfwuhFu534day/0W1G7UYdSgFciheuRgD9XxsxDZryEbzud+xQpkrw92HUDVetxD73G4Gf0yZKz7OYTUswcDjLtG93aA+ahdOQ37PNTzuwq9NShjz4dE9m+ogBvRWw23w0b7P6BXZdkHIr0e/3vsrsQv3D+LqsU/UTcEm/tD5GOWBatgDSqf3xthMjIHkN/O74jJvAv0E1cRh/zORg3idy5K95Pg44bbKGNPicf5vYtnWfeWOIJeFbJrUSO53wYPIeO730SPz0Ncg6oJE2pWPeFFf3k1dvBTDuZlqFrua+AW1B7dl2IW5rvQ38zvg/Aw+iE/Jgzcp0B/+1XkYFYIE6fiB5gKc1DG2WHz+b0erkFuN+ogir0sKAjRQ8Vdix88bsFDcHU9/kI/36MPa+ARuAb/hQwjbs9req+LfbrfxTbsZaMXN61h34tZcDlqHWozz9l/rX0vjD0++2Gk/6RhT4wJ/I5+lHxB/C7n93pU4nTkodM+GfvQz0W/CvkquBa1FeVv/4yD6EWsJjzI7+U+hd+bCXNELmkBvRzue+j+GqtRE/TcszrPPdwNrXturENvJEy8Dn/AdLgdvamwCrWf37XQuidHHffr4B7oOp94hNu4T74e/3A/Eo6F+bpnRwX3y/m9FrWP+83cl/ENXI1aj9qOOoiKuzrSlYmaiqpA1aDqULtQ9aioFZGuVNQE1HxUNWo9ahtqL8p1TWAvj8AVuAJX4ApcgStwBa4=
*/