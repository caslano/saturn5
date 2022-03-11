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
dZgSElraWlJCMRmljpDCPWxde4V15Idq5nJL2BUGecsXwF+6tAbGCUb/OFuk2JQARPQjYotlNxOiqMy/fDvmTQ1A4UFBSEIldpCSmt7q5vaI5p55mK3+PH3cI9ZUIKyCDOS7oLp1AlMXb4q32su89Kt3+yQgp4/LgsAL3XIQ1SrQkvtD0Bvnb0QXn3v7PlECJ/JX6hdFyKtQmxX6SlTzAUfMYq7UH58V9/v0UMiQt2Fpxd8TLNfwXlRk7m5ptawv5pg0PkEWAF9CXS7yN8y3fWtxLBfMmbvj0ZleTAeudD5QVZUmn/YO66uyJaylS9ad6WBh66Tu/vfZraMgMwjas0Mr7l0Vqm+OJ3+yxSwPQKqJH3VJ0/HKE0sJKLmCT1+3XqriKK5S0a2uzk+YchuabCx4p4BD5sre+mC1CHgqy/hpWuGTe7jCKq8YyNoT99QJGhJD849KR+zLFr6c3jthEzWBY3lBSNfecmSNaHtbI6XWfWW9iPm/b+laB86JyLv7YR9x1V/whw9Be7aiODSALOnQI0x+DIozD39kzcMtbIIrT3xw0sNXmgT62w5loS6vkyHF28kyTGFq5ydxN8kfyvIKM3h6WF5uJJMBccb9SqAnT6pWwHUHbqj3mQp44meAlmjzbM8LE6lKb+x5zlgVRc7FcZ3bo/+MLCaRKj9LugDkGM0UzwGcWSGwEf8hBMU5ZwQPv/HGCjXwRG59e4FXcnxIyj9O4sA4pg5JWKTNNCSbnzC73+CxVUrJRQDzIZO745M3xS0eiwQGVBWxRnjMSeLSSO1c5UAy50UbsmETqgPkEL/0Z8SDAApSPrcvdXQ8lCbPay5BTsErAqiKCYm8DpFcAU9xSQ/zpJxpX0JhG5WUmL29G/kAM2CgdnjHd520VZ5Ixx2trsuBPXgFf3tUBDab7hh21+qX6uElvWI/4jPHHnecAaxQLioKfP87VoiMjdZrxwNrfePxK803T9m6oD0BOoUzkK6tuaEBOvkEf7TE28wr8YlURV1OslxLRj3feNNVt4j85wYYNvQsrBeNN6CHhtHKPWc9Tx+U9zzNmQOvVLtA6LpHJZSfOsvP1f0UDWXsOFCfuGVRevq6J2Y1iLrG0R7iNu/yQezXvFV+WqJQZJ7jnVjg97IP3LIxvhtbrNTX7RrkhsdzLsdmvS8JiMzM72160+EgO2nyBaO/3Xw6pl8UejoAjmHZ+2623cS3Wy4lFSG8kU75w3tzadnI8Vp1pVFixUW/0uP4fcXvcsIf+ODHfVO3vVR7rYnUOLCJpVuijGlMaKOHw+vBJUhLz3cwQHtRxINE58ARQTcOQE7u03OtelFPTXVDfJnwcDwWzUcYh45DSq+LyPoI9dL7eiCq3uN9JjPstcCp5SVbwr64EWlDb/aFyoBU4g1csbBzEFJu0GjauzxRLawlanm702Pe0f6C30aFIGEBs0mmtXo+sJO1KUCbCQxrXQW/FsddGs/82/6r3Wn70sUwYlNLPa+5qqq/XpW3JHzBP68tzy0wq79A+Sp5uCEym5kRS2il0b6fzXIsbEUnF8nId3LyaTmitkgX1igJPkw1lTSzWWECU1mS8YZWers0LBgOZQ8hjhtzQwbNJZVugIvPeXrd18SJ8lGXRGozmNldsBI3cQ9a1E892Ute2/p6M+AvG15MnIypDkGP2xUfd8lpuMvSmgobRA0FLIACj5RfEO6Sh3s4a2WoilmK2jHBFJNrZF6fuU6pJvJl17PQupekABl+xeKgUE7BOx5kQlq7kUTL7B+TGTiFB9CZ10dd3TxaeQgpskS8LjgFnaQVjOV6jRB0mqsKTt6VP3Ifpbsh44w/WwFovFAV2Z9h2mxkAo6GEzTWJ7VQh8mq87yOzbjl4GRudwzxi39jchzMS1Ov2HoKu1PPDA50OdpkhtesbXXFE47GvoFXnIncZt8q2QN244X11bdYaPBy4bdLXV67+M8KK4yokf2SFxIr79J0mNDbIh7UM2voZq8xmvSF6wv8RfG/cjHKXwlnNnirQSmkY80YsObbSLNBTQI+oW/V/+otQhIRSb/kwi6AcDHgsdlWoIDt56XF2fcRnVFLKhO52DpyCyBloMCanvxA1279STyAfThVD/KNkXPnppdsc9fWQ3HYrdp7lsQzNOz2dQ/P7puc7vbgQk7M9nmwCNc8XyY2rY8Zf5Q79FEpi6DlRlD0/4HTqPldsil2J9YuoNotycNLMjTUe5Lpef1mNm5jsQRu7VI+lH7G3gWWAFvhS/fHlNRQFr8NUXkn+cTcJIKrsXCtca3B3+1UB0PTyjeFZPm0tM6Fw+2OcWdf236QvCw0lrV4njKX1YIc3TAeX0AfBBZ6v16vtR9UulOe3qnKCRvgQYZFUmdVerc8eTHY2cG5eJ5aL4e4GJKN9sI1zXe8u12EGckp0nIeMkjAIGjZHPeron+IdgIO2VP3KoWC3kbvMPJNJFxdH084um7fT41tpbMXFJMtpruVfBhXgWZ4tbDrgAzJNTgsWp5vzt7gBda07eWT3OKTsN2XjM6XvXDeXH007/dtpkIjvPFfE73JbcXqYUrLk275ZO8yEy5BebPjhvRd9/SAq3Kc+f0HW9O2YIfRszo9f66OMxn35vXfpfm92JrCPsgnNrzwFhcEt9knzyY2qBPIb6KVeEJv8vhtkM1OjrPt+IaSgW6q2Le25h5IwQAzIDxeDqOBSxXi1/s7Nvq29/zCLUIJGE19GzD/42zt8h11qfa66gjJcycCrbPmOB9+9j6c4GLrjAs/CsfBDDDZqbjlUAiXUtiJz+Qo7mNSqro1GPHAr39CogcKbok6hFn8XHy58+AKtsOn9Eif/YUU//tZbGR8RgoaV+Yv+fC/9H+P9oQJQ1KiJGBExlnP0l6ZGxlFX1kejAIXbA4wlO2q/kWQGHeRo8JgAMysu7O5HDB5wOKvIkHm25qlVNSnMMnAGm16Ekh6whBFABc6SbXWOyIuzv8OgQIgGEjw6M5VX8XF5Veo77ymYk+H15P/KYUOj4WhsXmgFtmnuEC7yUUnS+Msu/nEUiw/wYgSEYubwq/pFn3zjYiCCSTaXm98vKTRZXOgpDK+alJjPFZ0bkfEtAZHjeRGozN8UTdWFCS/jsUTG0Lt36HaD2yVq9nq0mGGlW6cdOAPMgJ3bGMqV0QdezWCkiBvvFMVxQlsstoXxCUGR3ibAk01I6+YfvVrQiXDtA6UwMJmnBgV3t5ecNUKnmJ+1rd0u2BFvTA49m5kPv7O+uZfcXwN9MfzK4+RP2yoISEqgbdFp/IcabI7P615u2mB2M0tNbHfWLtKVzXWsuB9GfR6hi8v6iLaFGFs4UDAH3MFnapve7cAZC83WSDk5ntqnrARLx08f0aF+DrmLc33Ac+t0ON7nJtPej38I8Xzrnfl8Gt8hsj1d6TB6LObPtfiTJb6BQMDesiaRWQar42Qbv5ysDJIlS9k1OpQsPbIccOestQg6BItMo1SfzlcgPkKHbZ7/O98iEAbxUkft2o2yGWjEHn89w7UcjKnprTKnCFD5877ve6frcAWSq79e1lvj97uLZNIkv1IYzBj1ZmVgU+fWX+AiIojzF1UxrhiQG4kLMho5AzzKxpJ5+nWHpkypPl9ihE2n3jh/wBDgLx/CbF4/wteHupnMBjZU1o2noCiiVSfNwdFPrniVGP8k5QEo2PV282BWAcMr5AMa7caGqqZvdDkc3YPBEczAm2sHb2V3sTshm/4XJQnMm9AhyZjvN2euJoN7uwDXHXB6TQiPwKUE85AupAe5Zv1pPuv5ubqe71/ywPdjBiB/CnOXpW/jOlK0OuzHafXa4YlmqC+9aPSN3Y6/tM5t1y7HpcUH9gaLtOaK+NowrBVAV0NWVtyVUn30yE3PBnYqaCQ0zE0VD16pIYZO86YYW7fPwd7x1G7CLegH6/mDNrnS/x6iJ2zK1BKGRJ6i8sGASReJ3OA6ICt0vCfTnT2Q6x3r080oPyS+erFSzOs7IQLZC4XNzZqFAF8mGRHe55mO0g9oQMBwNYnddy31LWLy1mv7UtkC3bUNmVRqZFIaAP8F+VGz/9/WpNa3B1XFnG+S5l0SlcuRYQ/zvnuLfWIe4sQxRl5LRN99rDp3xVGgwAHAHXt7huPooNW2cKo1vnyr3VtJ/gAcA6fdojkE1wfRL/F6IFJgwnh9MvVanQfymy9/d+S7xr8AW4QRlN+Ypwq/FHYM9kyuc/fpOaX4GQmBdqWQTiEJJ09FxsOtGjdJrSfNLCQn8AfQATGACIBpjyNI/zEc8pPb7NZN54kbo2AIsn7nE7K5/vOdtLVA1IVDd30pJmqeviJsBARluN2EnPbM+aiaZ/BoTizBZ1hNbYAf0Z76CBWtxpvFCslSrL+4Uv3P8qHcI/UYV8jKzVt1kmlG6XSTQd3TFxAafMS34Eox/2Wlzb/SjaTk/eStNTL0nXv/WhGqGgpumzPdW5YxrOEdXJY7EEHAROZSlwKH9IlGIVzY7pHcC23skC1/6E73wUMfHtZ2UBTvXGdgsuCLFtY9kp5y4w5ZnB8n2rhigtTlv8pdB+nWrf7ja6Y+d+gcoMRHF+3sDNsfUWXoB0OFuqxfkqjhuXJ7G3qgjFDwpesC2d49AnwCEpLYaySvZ4dPhufgQhG8w5bCY76PH9Oaz/KL1bcQlRa+lwKfrnhCGYBlwsCP0CgBF7q3SjUKL2DlFRjshCnw27W5lh8VQxY08N5u8+G+yx+902Ld/DbLvvEp0H0W1ek592untMddpFaAtf+8UfA9eu1w936KGAlMP7yWaUvkbQHwXD8G8wec/ztbwdSfsySxDHOhtNYAnnpHKUVCFF+yy3ejFO/frq3McIIV86t1eu0wfB3DhRcBCiuNZBgtiUPalANQPxIgwDxVX8D/uL3FnrNw3l9W8s+cFAduNqyW7VsqGftNXbl+y8cMxpc2ePndJRTrAe3XYhAT4atVn2sq13u6YAUQHtlh6cYC2InG+/T8Qtn1kciE6jzyn2emE7lNi+rOg0xarNYB3RQHV02en5S14KtN/YFA3zlTgRY5H0bgXeIPkduqQ4iSo1ndS+uQTrhifnSlk0QYcd9h9YThMSz7Oe3a8y1Z/TRhKDQVJYMR/pk+MIrFbEDL0G1guC9z/GEQoip6Y1MZk2umRHlO4SrihcPdCAAnN2u6FZLO/Ed7puQwlHgbP+vQcEvmz/kGbh3GaMemEp27Uzrh7ol64jc/U1C6LNywCArjOk2RMe93RoC2GhgUzt9mBtkHPXQ6vgStGxAyYOudnPX48X7TPJ+7zGzkiemdXdxlBJ2VMCytEGwT7TKALINguof3xxrgzPFrL1lNOj0o1t5HXpsxLDAwkDAwauD7E5fW8UcG7rBJ19NZnMWcB6+ai/7D4OyFHjqCfGg2K1SnguErTl3seE401nydu4jJkQ25t//W0lR8lwVKAqEAP7ee3PQKzIUUP2DcByXk/PnapLNafyP+BnR2Z9Klj0+83NX1FPAbVqvzXVBQdshjYaaMbVP12V7/QXsUK2iWUkaBB5qhzA7b2UF9nEqxYO2AJ2SAOhSQ0tPI51nDypud4HKpSXnR0KAhNb9j9eDSsQ27ZEEqXlbv5jg9YTqp6OJhe10/FAJF+0SOlFfOvbDgqF+54W9ej37O3IEtFy/Ydd7eORgQJRWVAdDJeV7qgZugP3BApRukhmCbNriM0keJjY0PqxdJOPd+rUdFLdCAttOVOagHsfVo0QOj1azLAPU9Oafp1fP0vgTzTh53Ms65chqUr57dKyWmF3UA1l5N9QAuJjB8N5yCpldLKMJcVbSifq72NSDTDb67Kn9AnwxcF07xfD/2gY7ZRxwXPY6Be3hhDEsxyFnusAO8oPjvv/TYDlunNkXJ82YfTjjy85yhvh2p3e74WY1U7rOmpy3pkLCQ9EdQNthFIYKsQv/EKN4rV5W2GZjK1X/P2sf6YH8e7/9W8f/f1+8/3/mfIWCXyu+vuLiKyu+vuLiKyu+vuLiKyu+/+LTyrKB6f9ha7/39ot82T87Pfev7RfC/fDzwJz7uEWu/36D7xBzh4fwO/zvrz7EHxFLhBPhq/9+hW8RX4QY4Ub4+H++Rr8Re4eO8CN837/8j+87f4eQ8Dx8hw/+gw8BRcKR8CT8CZ/DL/jCvkl/EqOEKeFK+BK+hL/hs/gtvkv/EsOEN97Av/gyf3gTD+LhPPyEb+HP/OOfJhvQF/l8xcVXV3x8xcVXV3x8xcVXMPMQEAAAAAADAAATAAAqAKqqj6NUVZ5h059DU1BVxsYaM6qqoIaq2qqGzKAbajMYamgxhtCI0cyAWQAAAAHtPT+2xKWt0kaswlc4R9dGKgEk4JIQ8ditIAogEtrOzdQTzEiY9b5gZrbrEwcBY/s/eYKtGAtVGGzCMEiEszGssQYbNAFBhLNc9KgHFyCXrbFFDyJKWuCCAAgAAAgBAdERQT9zybuNEQIFIYggYUIKyEkCHeiIrJc6Il6Ef/9Xhh++4hNPfFWPpkDs/2G7AkCCkr+bcV51Cv0KCGyDAr/COPH/Lx4H9/S11MU4gTy/YfKo+ic/YQxvTIFOoV+BzNgoWC8w3vv6DPd//K87dPWP/5IwuDaF4P4fh4YcggLG/4WANz5RMPraw7/+1/7X/eff5gnc6Z/+VQ0AJP/5P/YHSSgH/h8E4vE+cPFtcGRBoIFHIUhhR/9HJdl1/38dSXL7+8T1+K/1w4/kCO6yH+3f/6RxZMf34/v7r/37bsRfkEDgVr/fgfpN6XfYfkKPvo9/qIN82v/HoVH30s/7eSSHdv/+IP/EZOf8n3/Dg3zc//NoXPfM/1gQ64c/wm/6/wLuI6eyJ/u3n18AIbjt3+uA0Pb/jx195P9PEsjr8D//44Pu78+VkBD/fhwf69j8//NCOPlf+n0ZtHH6P1YjTSL//5IDcPnfHHB2f/4gkdfk//81OQzx/fEf/IePor8/38Ef38L5/w5b7Wj1+z8po7J//Xd/5WGL1cf+j+8AQvfx/fvfun/9p4/UQNz7548kkO//dR8V6X8I0OmTVODQ/yMJD/Wvv5L9/D+O9uf/efjp/ZJ//hOJc/N//QLf8gj0fh3/xrGg/B8EGukD6zSa/vFPMTs5hZR//gkXWPbq/hxCAEi/xm/P8Iyn/0vAVNhfW8yx9fouA28/QzL79pf9Lf5or7cB8E988YknPvjEE5984gtxefrw/2/QbP1/0H/qKvpfQov1n0IrqIv0In1I//3HMGbq1/0NnyPvSGP79d/Ei6gf+kNfhIjv9f9E/qi/9E39kx8lT0m+/qsoCvWS/qTP0g/9W7/0fLCJTz7xxCef+OITT3zxiSc++MQfnz7ko6tgazYHHldL03J7eSGxyXjBVgY25kb25pa+f7tcxmwfqPV9RVE/xSHdboRlZEV0ff3FLbWFPZW1p//bTOKPAv/7X8D3+xDt/9+bleD/m4Ti/1cAIfYM/kkCY29tco/9ANvCkObc2sNvSG9s/XE1lv05VZNmb/ftXBhWWfE/vqL+pU3Tzo6LD73/jfAsrCn/TpZhf36erc+6foB0/Xuur8nSaNvk/v2DG7RLK0c7+m+A/67//68cHb3+Hf/A//q/5Sj9B3+1nP44Oob/MKr+9v+45sTt35weuX+l+zi5/rFoEY/gThDPz9HSjs5P0tIO+b5IO0BKSEFJSUo4Ojj9SlTlfpz8pGHlS2xsaf9l8pESQlnvvcXwnwG2B/8A7XQwPkBdMWVWaGNtVflpugb4q58FUPubD9u/fzv9stKeO+oLY18bzkfMgr1f6crIwf4PkDb10fgnfQpt9OjZ9Y1jsR/q92921Vzcf5k9xPYn8EdDeyMLcH/8B06xTo5+D3RY/S25ocB/cn/PHs/Uzq3hv/d3/5tS2GZmMu3W9v1+/z2W4Z++7f7i3/7J7Tg/Of85vNHj+yOo49OOruhHMR9OzhKPT9JB0Ph9+JP0eD9yPEf56Dr+Ou/8+Jf/QG/Vn/DUEeTa8dIBP0qj9ou+J6knaOfH159KPa354dHvJ/HPadfH369jHOvqf0Xw6EiWwnuAhvgAh0+Q/xGRh+oDLwB/vnCHpPPZQfjvtOvj8+C3+b8gN7f+voMpjP8n/zud3230R0m//n/skvZqPqSccHT5Ov6v7Tr4PXXsr/P39/t+n7Pr8SG9+CAB+R0B8Bwt7fMkOqNHVwQUwLOIR4HgJB0cIP4jT7U+vv/NjPz6P49QH+ziE0988Yk/PrpgKcrigp+ESeaEC5IG9Kn/3oTuP4SNUpJm6VvtCyYqhSN5UrUJkH5w5gBKir6BeHtffwid0AjbCZLRWWZ7RlRVqkteap/8oJ14KRl6LARxFUsJTfrtYWpwUvFRrfsPG1I3xo06nDhiGAN6iBl22Zf4PAkuExiiCeAwWORTUfboay+bez8/xdd157Pa6l+l+lu7y1fSbp2yP6sWH8X2t2/EuaeUko1k1+yLAGEaTuOIXb5QAuIgcXDaPdf25frorHQb3y3snfOjbYT4OXIpq2qqILv50vvkmfvNlivbnPQtXLUzNYyI8TLPmFYc6hm4GwZf/24ew/5UrR2UaybLsrKsnrv31qWEJ4tKTKkuifca7fUxOUXzOuZshI0WJZu7Ye+krzncnJ9WZg6+Sqtd+05iiU2Gyn9cridRFCqOSxPltL1Ls7WzP2bmdrn4IEaAAmEEgCPh3AsBj1S52Dswg2t2YYuhX88uBSf/qpqh8LLZMe4VSa4FNP61x1LhRZf92hfhGg4o8k2Lduzi7XfdKLWI6Zsj0Aw7IOJVPRlN3hJfjv5/Z4Ddzb5llYgt6u6lIBb1fOXrErS3jjaVykcyWOD9nwPrKitzARDqgKwSStCK74j0+7+xdnyEGhuyDK8ZKfPa5cYM0QyGV78hqufP7a+gTbX2TRK37A/VuB0vdiFeAiXm3fYI7OYidUs9ibRSGrJr3Y5/k5towdaiHpmUSeMe9t3+ysDykx0Ctgx2bs+AswmeGsceYKEJn1T3cG4VuDgxT7KSiLpFxisdBZMPN9mX5uvukE+7y+XwC8hgzjMFDIMXRjP2PPloBA+f9H4XVoUja0+YRSYFbj+Szq7yR7xGi6xYTGvBbS7RfViPpRUNyED0kccmloArnqVjMzkjawhKAyK8VfVjPEkJLycpRFnL69PnDp3bqfPqRO48SaPgrlbEvoU=
*/