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