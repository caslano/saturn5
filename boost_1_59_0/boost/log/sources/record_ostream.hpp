/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   record_ostream.hpp
 * \author Andrey Semashev
 * \date   09.03.2009
 *
 * This header contains a wrapper class around a logging record that allows to compose the
 * record message with a streaming expression.
 */

#ifndef BOOST_LOG_SOURCES_RECORD_OSTREAM_HPP_INCLUDED_
#define BOOST_LOG_SOURCES_RECORD_OSTREAM_HPP_INCLUDED_

#include <string>
#include <iosfwd>
#include <ostream>
#include <boost/assert.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/core/addressof.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/core/uncaught_exceptions.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/native_typeof.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/utility/unique_identifier_name.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

template< typename CharT >
class basic_record_ostream;

namespace aux {

template< typename StreamT, typename T, bool ByValueV, typename R >
struct enable_record_ostream_generic_operator {};

template< typename CharT, typename T, typename R >
struct enable_record_ostream_generic_operator< basic_record_ostream< CharT >, T, false, R > :
    public boost::disable_if_c< boost::is_scalar< typename boost::remove_cv< T >::type >::value, R >
{
};

template< typename CharT, typename T, typename R >
struct enable_record_ostream_generic_operator< basic_record_ostream< CharT >, T, true, R > :
    public boost::enable_if_c< boost::is_enum< typename boost::remove_cv< T >::type >::value, R >
{
};

template< typename CharT, typename T, typename R >
struct enable_record_ostream_generic_operator< basic_record_ostream< CharT >, T*, true, R > :
    public disable_if_streamable_char_type< typename boost::remove_cv< T >::type, R >
{
};

} // namespace aux

/*!
 * \brief Logging record adapter with a streaming capability
 *
 * This class allows to compose the logging record message by streaming operations. It
 * aggregates the log record and provides the standard output stream interface.
 */
template< typename CharT >
class basic_record_ostream :
    public basic_formatting_ostream< CharT >
{
    //! Self type
    typedef basic_record_ostream< CharT > this_type;
    //! Base stream class
    typedef basic_formatting_ostream< CharT > base_type;

public:
    //! Character type
    typedef CharT char_type;
    //! String type to be used as a message text holder
    typedef std::basic_string< char_type > string_type;
    //! Stream type
    typedef std::basic_ostream< char_type > stream_type;
    //! Character traits
    typedef typename base_type::traits_type traits_type;

private:
    //! Log record
    record* m_record;

public:
    /*!
     * Default constructor. Creates an empty record that is equivalent to the invalid record handle.
     * The stream capability is not available after construction.
     *
     * \post <tt>!*this == true</tt>
     */
    basic_record_ostream() BOOST_NOEXCEPT : m_record(NULL) {}

    /*!
     * Constructor from a record object. Attaches to the provided record.
     *
     * \pre <tt>!!rec == true</tt>
     * \post <tt>&this->get_record() == &rec</tt>
     * \param rec The record handle being attached to
     */
    explicit basic_record_ostream(record& rec)
    {
        BOOST_ASSERT_MSG(!!rec, "Boost.Log: basic_record_ostream should only be attached to a valid record");
        m_record = &rec;
        init_stream();
    }

    /*!
     * Destructor. Destroys the record, releases any sinks and attribute values that were involved in processing this record.
     */
    ~basic_record_ostream() BOOST_NOEXCEPT
    {
        detach_from_record();
    }

    /*!
     * Conversion to an unspecified boolean type
     *
     * \return \c true, if stream is valid and ready for formatting, \c false, if the stream is not valid. The latter also applies to
     *         the case when the stream is not attached to a log record.
     */
    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()

    /*!
     * Inverted conversion to an unspecified boolean type
     *
     * \return \c false, if stream is valid and ready for formatting, \c true, if the stream is not valid. The latter also applies to
     *         the case when the stream is not attached to a log record.
     */
    bool operator! () const BOOST_NOEXCEPT
    {
        return (!m_record || base_type::fail());
    }

    /*!
     * Flushes internal buffers to complete all pending formatting operations and returns the aggregated log record
     *
     * \return The aggregated record object
     */
    record& get_record()
    {
        BOOST_ASSERT(m_record != NULL);
        this->flush();
        return *m_record;
    }

    /*!
     * Flushes internal buffers to complete all pending formatting operations and returns the aggregated log record
     *
     * \return The aggregated record object
     */
    record const& get_record() const
    {
        BOOST_ASSERT(m_record != NULL);
        const_cast< this_type* >(this)->flush();
        return *m_record;
    }

    /*!
     * If the stream is attached to a log record, flushes internal buffers to complete all pending formatting operations.
     * Then reattaches the stream to another log record.
     *
     * \param rec New log record to attach to
     */
    void attach_record(record& rec)
    {
        BOOST_ASSERT_MSG(!!rec, "Boost.Log: basic_record_ostream should only be attached to a valid record");
        detach_from_record();
        m_record = &rec;
        init_stream();
    }

    //! The function resets the stream into a detached (default initialized) state
    BOOST_LOG_API void detach_from_record() BOOST_NOEXCEPT;

    basic_record_ostream& operator<< (typename base_type::ios_base_manip manip)
    {
        static_cast< base_type& >(*this) << manip;
        return *this;
    }
    basic_record_ostream& operator<< (typename base_type::basic_ios_manip manip)
    {
        static_cast< base_type& >(*this) << manip;
        return *this;
    }
    basic_record_ostream& operator<< (typename base_type::stream_manip manip)
    {
        static_cast< base_type& >(*this) << manip;
        return *this;
    }

    basic_record_ostream& operator<< (char c)
    {
        static_cast< base_type& >(*this) << c;
        return *this;
    }
    basic_record_ostream& operator<< (const char* p)
    {
        static_cast< base_type& >(*this) << p;
        return *this;
    }

    // When no native character type is supported, the following overloads are disabled as they have ambiguous meaning.
    // Use basic_string_view or basic_string to explicitly indicate that the data is a string.
#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
    basic_record_ostream& operator<< (wchar_t c)
    {
        static_cast< base_type& >(*this) << c;
        return *this;
    }
    basic_record_ostream& operator<< (const wchar_t* p)
    {
        static_cast< base_type& >(*this) << p;
        return *this;
    }
#endif
#if !defined(BOOST_LOG_NO_CXX11_CODECVT_FACETS)
#if !defined(BOOST_NO_CXX11_CHAR16_T)
    basic_record_ostream& operator<< (char16_t c)
    {
        static_cast< base_type& >(*this) << c;
        return *this;
    }
    basic_record_ostream& operator<< (const char16_t* p)
    {
        static_cast< base_type& >(*this) << p;
        return *this;
    }
#endif
#if !defined(BOOST_NO_CXX11_CHAR32_T)
    basic_record_ostream& operator<< (char32_t c)
    {
        static_cast< base_type& >(*this) << c;
        return *this;
    }
    basic_record_ostream& operator<< (const char32_t* p)
    {
        static_cast< base_type& >(*this) << p;
        return *this;
    }
#endif
#endif

    basic_record_ostream& operator<< (bool value)
    {
        static_cast< base_type& >(*this) << value;
        return *this;
    }
    basic_record_ostream& operator<< (signed char value)
    {
        static_cast< base_type& >(*this) << value;
        return *this;
    }
    basic_record_ostream& operator<< (unsigned char value)
    {
        static_cast< base_type& >(*this) << value;
        return *this;
    }
    basic_record_ostream& operator<< (short value)
    {
        static_cast< base_type& >(*this) << value;
        return *this;
    }
    basic_record_ostream& operator<< (unsigned short value)
    {
        static_cast< base_type& >(*this) << value;
        return *this;
    }
    basic_record_ostream& operator<< (int value)
    {
        static_cast< base_type& >(*this) << value;
        return *this;
    }
    basic_record_ostream& operator<< (unsigned int value)
    {
        static_cast< base_type& >(*this) << value;
        return *this;
    }
    basic_record_ostream& operator<< (long value)
    {
        static_cast< base_type& >(*this) << value;
        return *this;
    }
    basic_record_ostream& operator<< (unsigned long value)
    {
        static_cast< base_type& >(*this) << value;
        return *this;
    }
#if !defined(BOOST_NO_LONG_LONG)
    basic_record_ostream& operator<< (long long value)
    {
        static_cast< base_type& >(*this) << value;
        return *this;
    }
    basic_record_ostream& operator<< (unsigned long long value)
    {
        static_cast< base_type& >(*this) << value;
        return *this;
    }
#endif

    basic_record_ostream& operator<< (float value)
    {
        static_cast< base_type& >(*this) << value;
        return *this;
    }
    basic_record_ostream& operator<< (double value)
    {
        static_cast< base_type& >(*this) << value;
        return *this;
    }
    basic_record_ostream& operator<< (long double value)
    {
        static_cast< base_type& >(*this) << value;
        return *this;
    }

    basic_record_ostream& operator<< (std::basic_streambuf< char_type, traits_type >* buf)
    {
        static_cast< base_type& >(*this) << buf;
        return *this;
    }

private:
    //! The function initializes the stream and the stream buffer
    BOOST_LOG_API void init_stream();

    //  Copy and assignment are closed
    BOOST_DELETED_FUNCTION(basic_record_ostream(basic_record_ostream const&))
    BOOST_DELETED_FUNCTION(basic_record_ostream& operator= (basic_record_ostream const&))
};


#ifdef BOOST_LOG_USE_CHAR
typedef basic_record_ostream< char > record_ostream;        //!< Convenience typedef for narrow-character logging
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
typedef basic_record_ostream< wchar_t > wrecord_ostream;    //!< Convenience typedef for wide-character logging
#endif

// Implementation note: these operators below should be the least attractive for the compiler
// so that user's overloads are chosen, when present. We use function template partial ordering for this purpose.
// We also don't use perfect forwarding for the right hand argument because in ths case the generic overload
// would be more preferred than the typical one written by users:
//
// record_ostream& operator<< (record_ostream& strm, my_type const& arg);
//
// This is because my_type rvalues require adding const to the type, which counts as a conversion that is not required
// if there is a perfect forwarding overload.
template< typename StreamT, typename T >
inline typename boost::log::aux::enable_record_ostream_generic_operator< StreamT, T, true, StreamT& >::type
operator<< (StreamT& strm, T value)
{
    typedef basic_formatting_ostream< typename StreamT::char_type > formatting_ostream_type;
    static_cast< formatting_ostream_type& >(strm) << value;
    return strm;
}

template< typename StreamT, typename T >
inline typename boost::log::aux::enable_record_ostream_generic_operator< StreamT, T, false, StreamT& >::type
operator<< (StreamT& strm, T const& value)
{
    typedef basic_formatting_ostream< typename StreamT::char_type > formatting_ostream_type;
    static_cast< formatting_ostream_type& >(strm) << value;
    return strm;
}

template< typename StreamT, typename T >
inline typename boost::log::aux::enable_record_ostream_generic_operator< StreamT, T, false, StreamT& >::type
operator<< (StreamT& strm, T& value)
{
    typedef basic_formatting_ostream< typename StreamT::char_type > formatting_ostream_type;
    static_cast< formatting_ostream_type& >(strm) << value;
    return strm;
}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

template< typename StreamT, typename T >
inline typename boost::log::aux::enable_record_ostream_generic_operator< StreamT, T, true, StreamT& >::type
operator<< (StreamT&& strm, T value)
{
    typedef basic_formatting_ostream< typename StreamT::char_type > formatting_ostream_type;
    static_cast< formatting_ostream_type& >(strm) << value;
    return strm;
}

template< typename StreamT, typename T >
inline typename boost::log::aux::enable_record_ostream_generic_operator< StreamT, T, false, StreamT& >::type
operator<< (StreamT&& strm, T const& value)
{
    typedef basic_formatting_ostream< typename StreamT::char_type > formatting_ostream_type;
    static_cast< formatting_ostream_type& >(strm) << value;
    return strm;
}

template< typename StreamT, typename T >
inline typename boost::log::aux::enable_record_ostream_generic_operator< StreamT, T, false, StreamT& >::type
operator<< (StreamT&& strm, T& value)
{
    typedef basic_formatting_ostream< typename StreamT::char_type > formatting_ostream_type;
    static_cast< formatting_ostream_type& >(strm) << value;
    return strm;
}

#endif // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

namespace aux {

//! Internal class that provides formatting streams for record pumps
template< typename CharT >
struct stream_provider
{
    //! Character type
    typedef CharT char_type;

    //! Formatting stream compound
    struct stream_compound
    {
        stream_compound* next;

        //! Log record stream adapter
        basic_record_ostream< char_type > stream;

        //! Initializing constructor
        explicit stream_compound(record& rec) : next(NULL), stream(rec) {}
    };

    //! The method returns an allocated stream compound
    BOOST_LOG_API static stream_compound* allocate_compound(record& rec);
    //! The method releases a compound
    BOOST_LOG_API static void release_compound(stream_compound* compound) BOOST_NOEXCEPT;

    //  Non-constructible, non-copyable, non-assignable
    BOOST_DELETED_FUNCTION(stream_provider())
    BOOST_DELETED_FUNCTION(stream_provider(stream_provider const&))
    BOOST_DELETED_FUNCTION(stream_provider& operator= (stream_provider const&))
};


/*!
 * \brief Logging record pump implementation
 *
 * The pump is used to format the logging record message text and then
 * push it to the logging core. It is constructed on each attempt to write
 * a log record and destroyed afterwards.
 *
 * The pump class template is instantiated on the logger type.
 */
template< typename LoggerT >
class record_pump
{
    BOOST_MOVABLE_BUT_NOT_COPYABLE(record_pump)

private:
    //! Logger type
    typedef LoggerT logger_type;
    //! Character type
    typedef typename logger_type::char_type char_type;
    //! Stream compound provider
    typedef stream_provider< char_type > stream_provider_type;
    //! Stream compound type
    typedef typename stream_provider_type::stream_compound stream_compound;

    //! Stream compound release guard
    class auto_release;
    friend class auto_release;
    class auto_release
    {
        stream_compound* m_pCompound;

    public:
        explicit auto_release(stream_compound* p) BOOST_NOEXCEPT : m_pCompound(p) {}
        ~auto_release() BOOST_NOEXCEPT { stream_provider_type::release_compound(m_pCompound); }
    };

protected:
    //! A reference to the logger
    logger_type* m_pLogger;
    //! Stream compound
    stream_compound* m_pStreamCompound;
    //! Exception state
    const unsigned int m_ExceptionCount;

public:
    //! Constructor
    explicit record_pump(logger_type& lg, record& rec) :
        m_pLogger(boost::addressof(lg)),
        m_pStreamCompound(stream_provider_type::allocate_compound(rec)),
        m_ExceptionCount(boost::core::uncaught_exceptions())
    {
    }
    //! Move constructor
    record_pump(BOOST_RV_REF(record_pump) that) BOOST_NOEXCEPT :
        m_pLogger(that.m_pLogger),
        m_pStreamCompound(that.m_pStreamCompound),
        m_ExceptionCount(that.m_ExceptionCount)
    {
        that.m_pLogger = 0;
        that.m_pStreamCompound = 0;
    }
    //! Destructor. Pushes the composed message to log.
    ~record_pump() BOOST_NOEXCEPT_IF(false)
    {
        if (m_pLogger)
        {
            auto_release cleanup(m_pStreamCompound); // destructor doesn't throw
            // Only push the record if no exception has been thrown in the streaming expression (if possible)
            if (m_ExceptionCount >= boost::core::uncaught_exceptions())
                m_pLogger->push_record(boost::move(m_pStreamCompound->stream.get_record()));
        }
    }

    //! Returns the stream to be used for message text formatting
    basic_record_ostream< char_type >& stream() const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(m_pStreamCompound != 0);
        return m_pStreamCompound->stream;
    }
};

template< typename LoggerT >
BOOST_FORCEINLINE record_pump< LoggerT > make_record_pump(LoggerT& lg, record& rec)
{
    return record_pump< LoggerT >(lg, rec);
}

} // namespace aux

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_STREAM_INTERNAL(logger, rec_var)\
    for (::boost::log::record rec_var = (logger).open_record(); !!rec_var;)\
        ::boost::log::aux::make_record_pump((logger), rec_var).stream()

#define BOOST_LOG_STREAM_WITH_PARAMS_INTERNAL(logger, rec_var, params_seq)\
    for (::boost::log::record rec_var = (logger).open_record((BOOST_PP_SEQ_ENUM(params_seq))); !!rec_var;)\
        ::boost::log::aux::make_record_pump((logger), rec_var).stream()

#endif // BOOST_LOG_DOXYGEN_PASS

//! The macro writes a record to the log
#define BOOST_LOG_STREAM(logger)\
    BOOST_LOG_STREAM_INTERNAL(logger, BOOST_LOG_UNIQUE_IDENTIFIER_NAME(_boost_log_record_))

//! The macro writes a record to the log and allows to pass additional named arguments to the logger
#define BOOST_LOG_STREAM_WITH_PARAMS(logger, params_seq)\
    BOOST_LOG_STREAM_WITH_PARAMS_INTERNAL(logger, BOOST_LOG_UNIQUE_IDENTIFIER_NAME(_boost_log_record_), params_seq)

#ifndef BOOST_LOG_NO_SHORTHAND_NAMES

//! An equivalent to BOOST_LOG_STREAM(logger)
#define BOOST_LOG(logger) BOOST_LOG_STREAM(logger)

//! An equivalent to BOOST_LOG_STREAM_WITH_PARAMS(logger, params_seq)
#define BOOST_LOG_WITH_PARAMS(logger, params_seq) BOOST_LOG_STREAM_WITH_PARAMS(logger, params_seq)

#endif // BOOST_LOG_NO_SHORTHAND_NAMES

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SOURCES_RECORD_OSTREAM_HPP_INCLUDED_

/* record_ostream.hpp
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
*/