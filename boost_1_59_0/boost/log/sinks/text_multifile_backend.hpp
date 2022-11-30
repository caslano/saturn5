/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   text_multifile_backend.hpp
 * \author Andrey Semashev
 * \date   09.06.2009
 *
 * The header contains implementation of a text multi-file sink backend.
 */

#ifndef BOOST_LOG_SINKS_TEXT_MULTIFILE_BACKEND_HPP_INCLUDED_
#define BOOST_LOG_SINKS_TEXT_MULTIFILE_BACKEND_HPP_INCLUDED_

#include <ios>
#include <string>
#include <locale>
#include <ostream>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/light_function.hpp>
#include <boost/log/detail/parameter_tools.hpp>
#include <boost/log/detail/cleanup_scope_guard.hpp>
#include <boost/log/keywords/auto_newline_mode.hpp>
#include <boost/log/sinks/auto_newline_mode.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

namespace file {

    /*!
     * An adapter class that allows to use regular formatters as file name generators.
     */
    template< typename FormatterT >
    class file_name_composer_adapter
    {
    public:
        //! Functor result type
        typedef filesystem::path result_type;
        //! File name character type
        typedef result_type::string_type::value_type native_char_type;
        //! The adopted formatter type
        typedef FormatterT formatter_type;
        //! Formatting stream type
        typedef basic_formatting_ostream< native_char_type > stream_type;

    private:
        //! The adopted formatter
        formatter_type m_Formatter;
        //! Formatted file name storage
        mutable result_type::string_type m_FileName;
        //! Formatting stream
        mutable stream_type m_FormattingStream;

    public:
        /*!
         * Initializing constructor
         */
        explicit file_name_composer_adapter(formatter_type const& formatter, std::locale const& loc = std::locale()) :
            m_Formatter(formatter),
            m_FormattingStream(m_FileName)
        {
            m_FormattingStream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
            m_FormattingStream.imbue(loc);
        }
        /*!
         * Copy constructor
         */
        file_name_composer_adapter(file_name_composer_adapter const& that) :
            m_Formatter(that.m_Formatter),
            m_FormattingStream(m_FileName)
        {
            m_FormattingStream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
            m_FormattingStream.imbue(that.m_FormattingStream.getloc());
        }
        /*!
         * Assignment
         */
        file_name_composer_adapter& operator= (file_name_composer_adapter const& that)
        {
            m_Formatter = that.m_Formatter;
            return *this;
        }

        /*!
         * The operator generates a file name based on the log record
         */
        result_type operator() (record_view const& rec) const
        {
            boost::log::aux::cleanup_guard< stream_type > cleanup1(m_FormattingStream);
            boost::log::aux::cleanup_guard< result_type::string_type > cleanup2(m_FileName);

            m_Formatter(rec, m_FormattingStream);
            m_FormattingStream.flush();

            return result_type(m_FileName);
        }
    };

    /*!
     * The function adopts a log record formatter into a file name generator
     *
     * \param fmt The formatter function object to adopt
     * \param loc The locale to use to character code conversion and formatting
     */
    template< typename FormatterT >
    inline file_name_composer_adapter< FormatterT > as_file_name_composer(
        FormatterT const& fmt, std::locale const& loc = std::locale())
    {
        return file_name_composer_adapter< FormatterT >(fmt, loc);
    }

} // namespace file


/*!
 * \brief An implementation of a text multiple files logging sink backend
 *
 * The sink backend puts formatted log records to one of the text files.
 * The particular file is chosen upon each record's attribute values, which allows
 * to distribute records into individual files or to group records related to
 * some entity or process in a separate file.
 */
class text_multifile_backend :
    public basic_formatted_sink_backend< char >
{
    //! Base type
    typedef basic_formatted_sink_backend< char > base_type;

public:
    //! Character type
    typedef base_type::char_type char_type;
    //! String type to be used as a message text holder
    typedef base_type::string_type string_type;

    //! File name composer functor type
    typedef boost::log::aux::light_function< filesystem::path (record_view const&) > file_name_composer_type;

private:
    //! \cond

    struct implementation;
    implementation* m_pImpl;

    //! \endcond

public:
    /*!
     * Default constructor. The constructed sink backend has no file name composer and
     * thus will not write any files. All other parameters are set to their defaults.
     */
    BOOST_LOG_API text_multifile_backend();

    /*!
     * Constructor. Creates a sink backend with the specified named parameters.
     * The following named parameters are supported:
     *
     * \li \c auto_newline_mode - Specifies automatic trailing newline insertion mode. Must be a value of
     *                            the \c auto_newline_mode enum. By default, is <tt>auto_newline_mode::insert_if_missing</tt>.
     */
#ifndef BOOST_LOG_DOXYGEN_PASS
    BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_CALL(text_multifile_backend, construct)
#else
    template< typename... ArgsT >
    explicit text_multifile_backend(ArgsT... const& args);
#endif

    /*!
     * Destructor
     */
    BOOST_LOG_API ~text_multifile_backend();

    /*!
     * The method sets file name composer functional object. Log record formatters are accepted, too.
     *
     * \param composer File name composer functor
     */
    template< typename ComposerT >
    void set_file_name_composer(ComposerT const& composer)
    {
        set_file_name_composer_internal(composer);
    }

    /*!
     * Selects whether a trailing newline should be automatically inserted after every log record. See
     * \c auto_newline_mode description for the possible modes of operation.
     *
     * \param mode The trailing newline insertion mode.
     */
    BOOST_LOG_API void set_auto_newline_mode(auto_newline_mode mode);

    /*!
     * The method writes the message to the sink
     */
    BOOST_LOG_API void consume(record_view const& rec, string_type const& formatted_message);

private:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Constructor implementation
    template< typename ArgsT >
    void construct(ArgsT const& args)
    {
        construct(args[keywords::auto_newline_mode | insert_if_missing]);
    }
    //! Constructor implementation
    BOOST_LOG_API void construct(auto_newline_mode auto_newline);

    //! The method sets the file name composer
    BOOST_LOG_API void set_file_name_composer_internal(file_name_composer_type const& composer);
#endif // BOOST_LOG_DOXYGEN_PASS
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_TEXT_MULTIFILE_BACKEND_HPP_INCLUDED_

/* text_multifile_backend.hpp
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
*/