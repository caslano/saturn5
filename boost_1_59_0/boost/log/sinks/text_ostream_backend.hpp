/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   text_ostream_backend.hpp
 * \author Andrey Semashev
 * \date   22.04.2007
 *
 * The header contains implementation of a text output stream sink backend.
 */

#ifndef BOOST_LOG_SINKS_TEXT_OSTREAM_BACKEND_HPP_INCLUDED_
#define BOOST_LOG_SINKS_TEXT_OSTREAM_BACKEND_HPP_INCLUDED_

#include <ostream>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/parameter_tools.hpp>
#include <boost/log/keywords/auto_flush.hpp>
#include <boost/log/keywords/auto_newline_mode.hpp>
#include <boost/log/sinks/auto_newline_mode.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

/*!
 * \brief An implementation of a text output stream logging sink backend
 *
 * The sink backend puts formatted log records to one or more text streams.
 */
template< typename CharT >
class basic_text_ostream_backend :
    public basic_formatted_sink_backend<
        CharT,
        combine_requirements< synchronized_feeding, flushing >::type
    >
{
    //! Base type
    typedef basic_formatted_sink_backend<
        CharT,
        combine_requirements< synchronized_feeding, flushing >::type
    > base_type;

public:
    //! Character type
    typedef typename base_type::char_type char_type;
    //! String type to be used as a message text holder
    typedef typename base_type::string_type string_type;
    //! Output stream type
    typedef std::basic_ostream< char_type > stream_type;

private:
    //! \cond

    struct implementation;
    implementation* m_pImpl;

    //! \endcond

public:
    /*!
     * Constructor. No streams attached to the constructed backend, auto flush feature disabled.
     */
    BOOST_LOG_API basic_text_ostream_backend();

    /*!
     * Constructor. Creates a sink backend with the specified named parameters.
     * The following named parameters are supported:
     *
     * \li \c auto_flush - Specifies a flag, whether or not to automatically flush the attached streams after each
     *                     written log record. By default, is \c false.
     * \li \c auto_newline_mode - Specifies automatic trailing newline insertion mode. Must be a value of
     *                            the \c auto_newline_mode enum. By default, is <tt>auto_newline_mode::insert_if_missing</tt>.
     */
#ifndef BOOST_LOG_DOXYGEN_PASS
    BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_CALL(basic_text_ostream_backend, construct)
#else
    template< typename... ArgsT >
    explicit basic_text_ostream_backend(ArgsT... const& args);
#endif

    /*!
     * Destructor
     */
    BOOST_LOG_API ~basic_text_ostream_backend();

    /*!
     * The method adds a new stream to the sink.
     *
     * \param strm Pointer to the stream. Must not be NULL.
     */
    BOOST_LOG_API void add_stream(shared_ptr< stream_type > const& strm);
    /*!
     * The method removes a stream from the sink. If the stream is not attached to the sink,
     * the method has no effect.
     *
     * \param strm Pointer to the stream. Must not be NULL.
     */
    BOOST_LOG_API void remove_stream(shared_ptr< stream_type > const& strm);

    /*!
     * Sets the flag to automatically flush buffers of all attached streams after each log record.
     *
     * \param enable The flag indicates whether the automatic buffer flush should be performed.
     */
    BOOST_LOG_API void auto_flush(bool enable = true);

    /*!
     * Selects whether a trailing newline should be automatically inserted after every log record. See
     * \c auto_newline_mode description for the possible modes of operation.
     *
     * \param mode The trailing newline insertion mode.
     */
    BOOST_LOG_API void set_auto_newline_mode(auto_newline_mode mode);

    /*!
     * The method writes the message to the sink.
     */
    BOOST_LOG_API void consume(record_view const& rec, string_type const& formatted_message);

    /*!
     * The method flushes all attached streams.
     */
    BOOST_LOG_API void flush();

private:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Constructor implementation
    template< typename ArgsT >
    void construct(ArgsT const& args)
    {
        construct(
            args[keywords::auto_newline_mode | insert_if_missing],
            args[keywords::auto_flush | false]);
    }
    //! Constructor implementation
    BOOST_LOG_API void construct(auto_newline_mode auto_newline, bool auto_flush);
#endif // BOOST_LOG_DOXYGEN_PASS
};

#ifdef BOOST_LOG_USE_CHAR
typedef basic_text_ostream_backend< char > text_ostream_backend;        //!< Convenience typedef for narrow-character logging
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
typedef basic_text_ostream_backend< wchar_t > wtext_ostream_backend;    //!< Convenience typedef for wide-character logging
#endif

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_TEXT_OSTREAM_BACKEND_HPP_INCLUDED_

/* text_ostream_backend.hpp
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
*/