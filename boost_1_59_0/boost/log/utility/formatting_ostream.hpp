/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatting_ostream.hpp
 * \author Andrey Semashev
 * \date   11.07.2012
 *
 * The header contains implementation of a string stream used for log record formatting.
 */

#ifndef BOOST_LOG_UTILITY_FORMATTING_OSTREAM_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FORMATTING_OSTREAM_HPP_INCLUDED_

#include <ostream>
#include <string>
#include <memory>
#include <locale>
#include <boost/core/enable_if.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/utility/string_ref_fwd.hpp>
#include <boost/utility/string_view_fwd.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/log/detail/config.hpp>
#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)
#include <string_view>
#endif
#include <boost/log/detail/attachable_sstream_buf.hpp>
#include <boost/log/detail/code_conversion.hpp>
#include <boost/log/utility/string_literal_fwd.hpp>
#include <boost/log/utility/formatting_ostream_fwd.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

template< typename T, typename R >
struct enable_if_streamable_char_type {};
template< typename T, typename R >
struct disable_if_streamable_char_type { typedef R type; };
template< typename R >
struct enable_if_streamable_char_type< char, R > { typedef R type; };
template< typename R >
struct disable_if_streamable_char_type< char, R > {};
template< typename R >
struct enable_if_streamable_char_type< wchar_t, R > { typedef R type; };
template< typename R >
struct disable_if_streamable_char_type< wchar_t, R > {};
#if !defined(BOOST_LOG_NO_CXX11_CODECVT_FACETS)
#if !defined(BOOST_NO_CXX11_CHAR16_T)
template< typename R >
struct enable_if_streamable_char_type< char16_t, R > { typedef R type; };
template< typename R >
struct disable_if_streamable_char_type< char16_t, R > {};
#endif
#if !defined(BOOST_NO_CXX11_CHAR32_T)
template< typename R >
struct enable_if_streamable_char_type< char32_t, R > { typedef R type; };
template< typename R >
struct disable_if_streamable_char_type< char32_t, R > {};
#endif
#endif

template< typename StreamT, typename T, bool ByValueV, typename R >
struct enable_formatting_ostream_generic_operator {};

template< typename CharT, typename TraitsT, typename AllocatorT, typename T, typename R >
struct enable_formatting_ostream_generic_operator< basic_formatting_ostream< CharT, TraitsT, AllocatorT >, T, false, R > :
    public boost::disable_if_c< boost::is_scalar< typename boost::remove_cv< T >::type >::value, R >
{
};

template< typename CharT, typename TraitsT, typename AllocatorT, typename T, typename R >
struct enable_formatting_ostream_generic_operator< basic_formatting_ostream< CharT, TraitsT, AllocatorT >, T, true, R > :
    public boost::enable_if_c< boost::is_enum< typename boost::remove_cv< T >::type >::value, R >
{
};

template< typename CharT, typename TraitsT, typename AllocatorT, typename T, typename R >
struct enable_formatting_ostream_generic_operator< basic_formatting_ostream< CharT, TraitsT, AllocatorT >, T*, true, R > :
    public disable_if_streamable_char_type< typename boost::remove_cv< T >::type, R >
{
};

} // namespace aux

/*!
 * \brief Stream wrapper for log records formatting.
 *
 * This stream wrapper is used by the library for log record formatting. It implements the standard string stream interface
 * with a few differences:
 *
 * \li It does not derive from standard types <tt>std::basic_ostream</tt>, <tt>std::basic_ios</tt> and <tt>std::ios_base</tt>,
 *     although it tries to implement their interfaces closely. There are a few small differences, mostly regarding <tt>rdbuf</tt>
 *     and <tt>str</tt> signatures, as well as the supported insertion operator overloads. The actual wrapped stream can be accessed
 *     through the <tt>stream</tt> methods.
 * \li By default, \c bool values are formatted using alphabetical representation rather than numeric.
 * \li The stream supports writing strings of character types different from the stream character type. The stream will perform
 *     character code conversion as needed using the imbued locale.
 * \li The stream operates on an external string object rather than on the embedded one. The string can be attached or detached
 *     from the stream dynamically.
 *
 * Although <tt>basic_formatting_ostream</tt> does not derive from <tt>std::basic_ostream</tt>, users are not required to add
 * special overloads of \c operator<< for it since the stream will by default reuse the operators for <tt>std::basic_ostream</tt>.
 * However, one can define special overloads of \c operator<< for <tt>basic_formatting_ostream</tt> if a certain type needs
 * special formatting when output to log.
 */
template< typename CharT, typename TraitsT, typename AllocatorT >
class basic_formatting_ostream
{
public:
    //! Character type
    typedef CharT char_type;
    //! Character traits
    typedef TraitsT traits_type;
    //! Memory allocator
    typedef AllocatorT allocator_type;
    //! Stream buffer type
    typedef boost::log::aux::basic_ostringstreambuf< char_type, traits_type, allocator_type > streambuf_type;
    //! Target string type
    typedef typename streambuf_type::string_type string_type;

    //! Stream type
    typedef std::basic_ostream< char_type, traits_type > ostream_type;
    //! Stream position type
    typedef typename ostream_type::pos_type pos_type;
    //! Stream offset type
    typedef typename ostream_type::off_type off_type;
    //! Integer type for characters
    typedef typename ostream_type::int_type int_type;

    typedef typename ostream_type::failure failure;
    typedef typename ostream_type::fmtflags fmtflags;
    typedef typename ostream_type::iostate iostate;
    typedef typename ostream_type::openmode openmode;
    typedef typename ostream_type::seekdir seekdir;
    typedef typename ostream_type::Init Init;

    typedef typename ostream_type::event event;
    typedef typename ostream_type::event_callback event_callback;

    class sentry :
        public ostream_type::sentry
    {
        typedef typename ostream_type::sentry base_type;

    public:
        explicit sentry(basic_formatting_ostream& strm) : base_type(strm.stream())
        {
        }

        // A workaround for Solaris Studio 12.4 compiler, see: https://svn.boost.org/trac/boost/ticket/11545
        BOOST_EXPLICIT_OPERATOR_BOOL()
        bool operator! () const { return !static_cast< base_type const& >(*this); }

        BOOST_DELETED_FUNCTION(sentry(sentry const&))
        BOOST_DELETED_FUNCTION(sentry& operator= (sentry const&))
    };

protected:
    //  Function types
    typedef std::ios_base& (*ios_base_manip)(std::ios_base&);
    typedef std::basic_ios< char_type, traits_type >& (*basic_ios_manip)(std::basic_ios< char_type, traits_type >&);
    typedef ostream_type& (*stream_manip)(ostream_type&);

public:
    static BOOST_CONSTEXPR_OR_CONST fmtflags boolalpha = ostream_type::boolalpha;
    static BOOST_CONSTEXPR_OR_CONST fmtflags dec = ostream_type::dec;
    static BOOST_CONSTEXPR_OR_CONST fmtflags fixed = ostream_type::fixed;
    static BOOST_CONSTEXPR_OR_CONST fmtflags hex = ostream_type::hex;
    static BOOST_CONSTEXPR_OR_CONST fmtflags internal = ostream_type::internal;
    static BOOST_CONSTEXPR_OR_CONST fmtflags left = ostream_type::left;
    static BOOST_CONSTEXPR_OR_CONST fmtflags oct = ostream_type::oct;
    static BOOST_CONSTEXPR_OR_CONST fmtflags right = ostream_type::right;
    static BOOST_CONSTEXPR_OR_CONST fmtflags scientific = ostream_type::scientific;
    static BOOST_CONSTEXPR_OR_CONST fmtflags showbase = ostream_type::showbase;
    static BOOST_CONSTEXPR_OR_CONST fmtflags showpoint = ostream_type::showpoint;
    static BOOST_CONSTEXPR_OR_CONST fmtflags skipws = ostream_type::skipws;
    static BOOST_CONSTEXPR_OR_CONST fmtflags unitbuf = ostream_type::unitbuf;
    static BOOST_CONSTEXPR_OR_CONST fmtflags uppercase = ostream_type::uppercase;
    static BOOST_CONSTEXPR_OR_CONST fmtflags adjustfield = ostream_type::adjustfield;
    static BOOST_CONSTEXPR_OR_CONST fmtflags basefield = ostream_type::basefield;
    static BOOST_CONSTEXPR_OR_CONST fmtflags floatfield = ostream_type::floatfield;

    static BOOST_CONSTEXPR_OR_CONST iostate badbit = ostream_type::badbit;
    static BOOST_CONSTEXPR_OR_CONST iostate eofbit = ostream_type::eofbit;
    static BOOST_CONSTEXPR_OR_CONST iostate failbit = ostream_type::failbit;
    static BOOST_CONSTEXPR_OR_CONST iostate goodbit = ostream_type::goodbit;

    static BOOST_CONSTEXPR_OR_CONST openmode app = ostream_type::app;
    static BOOST_CONSTEXPR_OR_CONST openmode ate = ostream_type::ate;
    static BOOST_CONSTEXPR_OR_CONST openmode binary = ostream_type::binary;
    static BOOST_CONSTEXPR_OR_CONST openmode in = ostream_type::in;
    static BOOST_CONSTEXPR_OR_CONST openmode out = ostream_type::out;
    static BOOST_CONSTEXPR_OR_CONST openmode trunc = ostream_type::trunc;

    static BOOST_CONSTEXPR_OR_CONST seekdir beg = ostream_type::beg;
    static BOOST_CONSTEXPR_OR_CONST seekdir cur = ostream_type::cur;
    static BOOST_CONSTEXPR_OR_CONST seekdir end = ostream_type::end;

    static BOOST_CONSTEXPR_OR_CONST event erase_event = ostream_type::erase_event;
    static BOOST_CONSTEXPR_OR_CONST event imbue_event = ostream_type::imbue_event;
    static BOOST_CONSTEXPR_OR_CONST event copyfmt_event = ostream_type::copyfmt_event;

private:
    mutable streambuf_type m_streambuf;
    ostream_type m_stream;

public:
    /*!
     * Default constructor. Creates an empty record that is equivalent to the invalid record handle.
     * The stream capability is not available after construction.
     *
     * \post <tt>!*this == true</tt>
     */
    basic_formatting_ostream() : m_stream(&m_streambuf)
    {
        init_stream();
    }

    /*!
     * Initializing constructor. Attaches the string to the constructed stream.
     * The string will be used to store the formatted characters.
     *
     * \post <tt>!*this == false</tt>
     * \param str The string buffer to attach.
     */
    explicit basic_formatting_ostream(string_type& str) :
        m_streambuf(str),
        m_stream(&m_streambuf)
    {
        init_stream();
    }

    /*!
     * Destructor. Destroys the record, releases any sinks and attribute values that were involved in processing this record.
     */
    ~basic_formatting_ostream()
    {
        if (m_streambuf.storage())
            flush();
    }

    /*!
     * Attaches the stream to the string. The string will be used to store the formatted characters.
     *
     * \param str The string buffer to attach.
     */
    void attach(string_type& str)
    {
        m_streambuf.attach(str);
        m_stream.clear(ostream_type::goodbit);
    }
    /*!
     * Detaches the stream from the string. Any buffered data is flushed to the string.
     */
    void detach()
    {
        m_streambuf.detach();
        m_stream.clear(ostream_type::badbit);
    }

    /*!
     * \returns Reference to the attached string. The string must be attached before calling this method.
     */
    string_type const& str() const
    {
        string_type* const storage = m_streambuf.storage();
        BOOST_ASSERT(storage != NULL);

        m_streambuf.pubsync();

        return *storage;
    }

    /*!
     * \returns Reference to the wrapped stream
     */
    ostream_type& stream() { return m_stream; }

    /*!
     * \returns Reference to the wrapped stream
     */
    ostream_type const& stream() const { return m_stream; }

    // std::ios_base method forwarders
    fmtflags flags() const { return m_stream.flags(); }
    fmtflags flags(fmtflags f) { return m_stream.flags(f); }
    fmtflags setf(fmtflags f) { return m_stream.setf(f); }
    fmtflags setf(fmtflags f, fmtflags mask) { return m_stream.setf(f, mask); }
    void unsetf(fmtflags f) { m_stream.unsetf(f); }

    std::streamsize precision() const { return m_stream.precision(); }
    std::streamsize precision(std::streamsize p) { return m_stream.precision(p); }

    std::streamsize width() const { return m_stream.width(); }
    std::streamsize width(std::streamsize w) { return m_stream.width(w); }

    std::locale getloc() const { return m_stream.getloc(); }
    std::locale imbue(std::locale const& loc) { return m_stream.imbue(loc); }

    static int xalloc() { return ostream_type::xalloc(); }
    long& iword(int index) { return m_stream.iword(index); }
    void*& pword(int index) { return m_stream.pword(index); }

    void register_callback(event_callback fn, int index) { m_stream.register_callback(fn, index); }

    static bool sync_with_stdio(bool sync = true) { return ostream_type::sync_with_stdio(sync); }

    // std::basic_ios method forwarders
    BOOST_EXPLICIT_OPERATOR_BOOL()
    bool operator! () const { return !m_stream; }

    iostate rdstate() const { return m_stream.rdstate(); }
    void clear(iostate state = goodbit) { m_stream.clear(state); }
    void setstate(iostate state) { m_stream.setstate(state); }
    bool good() const { return m_stream.good(); }
    bool eof() const { return m_stream.eof(); }
    bool fail() const { return m_stream.fail(); }
    bool bad() const { return m_stream.bad(); }

    iostate exceptions() const { return m_stream.exceptions(); }
    void exceptions(iostate s) { m_stream.exceptions(s); }

    ostream_type* tie() const { return m_stream.tie(); }
    ostream_type* tie(ostream_type* strm) { return m_stream.tie(strm); }

    streambuf_type* rdbuf() const { return &m_streambuf; }

    basic_formatting_ostream& copyfmt(std::basic_ios< char_type, traits_type >& rhs)
    {
        m_stream.copyfmt(rhs);
        return *this;
    }
    basic_formatting_ostream& copyfmt(basic_formatting_ostream& rhs)
    {
        m_stream.copyfmt(rhs.stream());
        return *this;
    }

    char_type fill() const { return m_stream.fill(); }
    char_type fill(char_type ch) { return m_stream.fill(ch); }

    char narrow(char_type ch, char def) const { return m_stream.narrow(ch, def); }
    char_type widen(char ch) const { return m_stream.widen(ch); }

    // std::basic_ostream method forwarders
    basic_formatting_ostream& flush()
    {
        m_stream.flush();
        return *this;
    }

    pos_type tellp() { return m_stream.tellp(); }
    basic_formatting_ostream& seekp(pos_type pos)
    {
        m_stream.seekp(pos);
        return *this;
    }
    basic_formatting_ostream& seekp(off_type off, std::ios_base::seekdir dir)
    {
        m_stream.seekp(off, dir);
        return *this;
    }

    basic_formatting_ostream& put(char_type c)
    {
        m_stream.put(c);
        return *this;
    }

    template< typename OtherCharT >
    typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    put(OtherCharT c)
    {
        write(&c, 1);
        return *this;
    }

    basic_formatting_ostream& write(const char_type* p, std::streamsize size)
    {
        m_stream.write(p, size);
        return *this;
    }

    template< typename OtherCharT >
    typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    write(const OtherCharT* p, std::streamsize size)
    {
        sentry guard(*this);
        if (!!guard)
        {
            m_stream.flush();

            if (!m_streambuf.storage_overflow())
            {
                string_type* storage = m_streambuf.storage();
                if (!aux::code_convert(p, static_cast< std::size_t >(size), *storage, m_streambuf.max_size(), m_stream.getloc()))
                    m_streambuf.storage_overflow(true);
            }
        }

        return *this;
    }

    basic_formatting_ostream& operator<< (ios_base_manip manip)
    {
        m_stream << manip;
        return *this;
    }
    basic_formatting_ostream& operator<< (basic_ios_manip manip)
    {
        m_stream << manip;
        return *this;
    }
    basic_formatting_ostream& operator<< (stream_manip manip)
    {
        m_stream << manip;
        return *this;
    }

    basic_formatting_ostream& operator<< (char c)
    {
        return this->formatted_write(&c, 1);
    }
    basic_formatting_ostream& operator<< (const char* p)
    {
        return this->formatted_write(p, static_cast< std::streamsize >(std::char_traits< char >::length(p)));
    }

    // When no native character type is supported, the following overloads are disabled as they have ambiguous meaning.
    // Use basic_string_view or basic_string to explicitly indicate that the data is a string.
#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
    basic_formatting_ostream& operator<< (wchar_t c)
    {
        return this->formatted_write(&c, 1);
    }
    basic_formatting_ostream& operator<< (const wchar_t* p)
    {
        return this->formatted_write(p, static_cast< std::streamsize >(std::char_traits< wchar_t >::length(p)));
    }
#endif
#if !defined(BOOST_LOG_NO_CXX11_CODECVT_FACETS)
#if !defined(BOOST_NO_CXX11_CHAR16_T)
    basic_formatting_ostream& operator<< (char16_t c)
    {
        return this->formatted_write(&c, 1);
    }
    basic_formatting_ostream& operator<< (const char16_t* p)
    {
        return this->formatted_write(p, static_cast< std::streamsize >(std::char_traits< char16_t >::length(p)));
    }
#endif
#if !defined(BOOST_NO_CXX11_CHAR32_T)
    basic_formatting_ostream& operator<< (char32_t c)
    {
        return this->formatted_write(&c, 1);
    }
    basic_formatting_ostream& operator<< (const char32_t* p)
    {
        return this->formatted_write(p, static_cast< std::streamsize >(std::char_traits< char32_t >::length(p)));
    }
#endif
#endif

    basic_formatting_ostream& operator<< (bool value)
    {
        m_stream << value;
        return *this;
    }
    basic_formatting_ostream& operator<< (signed char value)
    {
        m_stream << value;
        return *this;
    }
    basic_formatting_ostream& operator<< (unsigned char value)
    {
        m_stream << value;
        return *this;
    }
    basic_formatting_ostream& operator<< (short value)
    {
        m_stream << value;
        return *this;
    }
    basic_formatting_ostream& operator<< (unsigned short value)
    {
        m_stream << value;
        return *this;
    }
    basic_formatting_ostream& operator<< (int value)
    {
        m_stream << value;
        return *this;
    }
    basic_formatting_ostream& operator<< (unsigned int value)
    {
        m_stream << value;
        return *this;
    }
    basic_formatting_ostream& operator<< (long value)
    {
        m_stream << value;
        return *this;
    }
    basic_formatting_ostream& operator<< (unsigned long value)
    {
        m_stream << value;
        return *this;
    }
#if !defined(BOOST_NO_LONG_LONG)
    basic_formatting_ostream& operator<< (long long value)
    {
        m_stream << value;
        return *this;
    }
    basic_formatting_ostream& operator<< (unsigned long long value)
    {
        m_stream << value;
        return *this;
    }
#endif

    basic_formatting_ostream& operator<< (float value)
    {
        m_stream << value;
        return *this;
    }
    basic_formatting_ostream& operator<< (double value)
    {
        m_stream << value;
        return *this;
    }
    basic_formatting_ostream& operator<< (long double value)
    {
        m_stream << value;
        return *this;
    }

    basic_formatting_ostream& operator<< (std::basic_streambuf< char_type, traits_type >* buf)
    {
        m_stream << buf;
        return *this;
    }

    template< typename OtherCharT, typename OtherTraitsT, typename OtherAllocatorT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream& strm, std::basic_string< OtherCharT, OtherTraitsT, OtherAllocatorT > const& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }

#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)
    template< typename OtherCharT, typename OtherTraitsT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream& strm, std::basic_string_view< OtherCharT, OtherTraitsT > const& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }
#endif

    template< typename OtherCharT, typename OtherTraitsT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream& strm, basic_string_literal< OtherCharT, OtherTraitsT > const& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }

    template< typename OtherCharT, typename OtherTraitsT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream& strm, basic_string_view< OtherCharT, OtherTraitsT > const& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }

    // Deprecated overload
    template< typename OtherCharT, typename OtherTraitsT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream& strm, basic_string_ref< OtherCharT, OtherTraitsT > const& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }

    template< typename OtherCharT, typename OtherTraitsT, typename OtherAllocatorT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream& strm, std::basic_string< OtherCharT, OtherTraitsT, OtherAllocatorT >& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }

#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)
    template< typename OtherCharT, typename OtherTraitsT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream& strm, std::basic_string_view< OtherCharT, OtherTraitsT >& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }
#endif

    template< typename OtherCharT, typename OtherTraitsT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream& strm, basic_string_literal< OtherCharT, OtherTraitsT >& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }

    template< typename OtherCharT, typename OtherTraitsT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream& strm, basic_string_view< OtherCharT, OtherTraitsT >& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }

    // Deprecated overload
    template< typename OtherCharT, typename OtherTraitsT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream& strm, basic_string_ref< OtherCharT, OtherTraitsT >& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template< typename OtherCharT, typename OtherTraitsT, typename OtherAllocatorT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream&& strm, std::basic_string< OtherCharT, OtherTraitsT, OtherAllocatorT > const& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }

#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)
    template< typename OtherCharT, typename OtherTraitsT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream&& strm, std::basic_string_view< OtherCharT, OtherTraitsT > const& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }
#endif

    template< typename OtherCharT, typename OtherTraitsT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream&& strm, basic_string_literal< OtherCharT, OtherTraitsT > const& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }

    template< typename OtherCharT, typename OtherTraitsT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream&& strm, basic_string_view< OtherCharT, OtherTraitsT > const& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }

    // Deprecated overload
    template< typename OtherCharT, typename OtherTraitsT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream&& strm, basic_string_ref< OtherCharT, OtherTraitsT > const& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }

    template< typename OtherCharT, typename OtherTraitsT, typename OtherAllocatorT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream&& strm, std::basic_string< OtherCharT, OtherTraitsT, OtherAllocatorT >& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }

#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)
    template< typename OtherCharT, typename OtherTraitsT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream&& strm, std::basic_string_view< OtherCharT, OtherTraitsT >& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }
#endif

    template< typename OtherCharT, typename OtherTraitsT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream&& strm, basic_string_literal< OtherCharT, OtherTraitsT >& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }

    template< typename OtherCharT, typename OtherTraitsT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream&& strm, basic_string_view< OtherCharT, OtherTraitsT >& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }

    // Deprecated overload
    template< typename OtherCharT, typename OtherTraitsT >
    friend typename aux::enable_if_streamable_char_type< OtherCharT, basic_formatting_ostream& >::type
    operator<< (basic_formatting_ostream&& strm, basic_string_ref< OtherCharT, OtherTraitsT >& str)
    {
        return strm.formatted_write(str.data(), static_cast< std::streamsize >(str.size()));
    }
#endif // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

protected:
    void init_stream()
    {
        m_stream.exceptions(ostream_type::goodbit);
        m_stream.clear(m_streambuf.storage() ? ostream_type::goodbit : ostream_type::badbit);
        m_stream.flags
        (
            ostream_type::dec |
            ostream_type::skipws |
            ostream_type::boolalpha // this differs from the default stream flags but makes logs look better
        );
        m_stream.width(0);
        m_stream.precision(6);
        m_stream.fill(static_cast< char_type >(' '));
    }

private:
    basic_formatting_ostream& formatted_write(const char_type* p, std::streamsize size)
    {
        sentry guard(*this);
        if (!!guard)
        {
            m_stream.flush();

            if (m_stream.width() <= size)
                m_streambuf.append(p, static_cast< std::size_t >(size));
            else
                this->aligned_write(p, size);

            m_stream.width(0);
        }

        return *this;
    }

    template< typename OtherCharT >
    basic_formatting_ostream& formatted_write(const OtherCharT* p, std::streamsize size)
    {
        sentry guard(*this);
        if (!!guard)
        {
            m_stream.flush();

            if (m_stream.width() <= size)
            {
                if (!m_streambuf.storage_overflow())
                {
                    if (!aux::code_convert(p, static_cast< std::size_t >(size), *m_streambuf.storage(), m_streambuf.max_size(), m_stream.getloc()))
                        m_streambuf.storage_overflow(true);
                }
            }
            else
                this->aligned_write(p, size);

            m_stream.width(0);
        }

        return *this;
    }

    void aligned_write(const char_type* p, std::streamsize size);

    template< typename OtherCharT >
    void aligned_write(const OtherCharT* p, std::streamsize size);

    //! Copy constructor (closed)
    BOOST_DELETED_FUNCTION(basic_formatting_ostream(basic_formatting_ostream const& that))
    //! Assignment (closed)
    BOOST_DELETED_FUNCTION(basic_formatting_ostream& operator= (basic_formatting_ostream const& that))
};

template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::fmtflags basic_formatting_ostream< CharT, TraitsT, AllocatorT >::boolalpha;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::fmtflags basic_formatting_ostream< CharT, TraitsT, AllocatorT >::dec;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::fmtflags basic_formatting_ostream< CharT, TraitsT, AllocatorT >::fixed;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::fmtflags basic_formatting_ostream< CharT, TraitsT, AllocatorT >::hex;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::fmtflags basic_formatting_ostream< CharT, TraitsT, AllocatorT >::internal;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::fmtflags basic_formatting_ostream< CharT, TraitsT, AllocatorT >::left;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::fmtflags basic_formatting_ostream< CharT, TraitsT, AllocatorT >::oct;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::fmtflags basic_formatting_ostream< CharT, TraitsT, AllocatorT >::right;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::fmtflags basic_formatting_ostream< CharT, TraitsT, AllocatorT >::scientific;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::fmtflags basic_formatting_ostream< CharT, TraitsT, AllocatorT >::showbase;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::fmtflags basic_formatting_ostream< CharT, TraitsT, AllocatorT >::showpoint;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::fmtflags basic_formatting_ostream< CharT, TraitsT, AllocatorT >::skipws;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::fmtflags basic_formatting_ostream< CharT, TraitsT, AllocatorT >::unitbuf;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::fmtflags basic_formatting_ostream< CharT, TraitsT, AllocatorT >::uppercase;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::fmtflags basic_formatting_ostream< CharT, TraitsT, AllocatorT >::adjustfield;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::fmtflags basic_formatting_ostream< CharT, TraitsT, AllocatorT >::basefield;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::fmtflags basic_formatting_ostream< CharT, TraitsT, AllocatorT >::floatfield;

template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::iostate basic_formatting_ostream< CharT, TraitsT, AllocatorT >::badbit;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::iostate basic_formatting_ostream< CharT, TraitsT, AllocatorT >::eofbit;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::iostate basic_formatting_ostream< CharT, TraitsT, AllocatorT >::failbit;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::iostate basic_formatting_ostream< CharT, TraitsT, AllocatorT >::goodbit;

template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::openmode basic_formatting_ostream< CharT, TraitsT, AllocatorT >::app;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::openmode basic_formatting_ostream< CharT, TraitsT, AllocatorT >::ate;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::openmode basic_formatting_ostream< CharT, TraitsT, AllocatorT >::binary;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::openmode basic_formatting_ostream< CharT, TraitsT, AllocatorT >::in;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::openmode basic_formatting_ostream< CharT, TraitsT, AllocatorT >::out;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::openmode basic_formatting_ostream< CharT, TraitsT, AllocatorT >::trunc;

template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::seekdir basic_formatting_ostream< CharT, TraitsT, AllocatorT >::beg;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::seekdir basic_formatting_ostream< CharT, TraitsT, AllocatorT >::cur;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::seekdir basic_formatting_ostream< CharT, TraitsT, AllocatorT >::end;

template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::event basic_formatting_ostream< CharT, TraitsT, AllocatorT >::erase_event;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::event basic_formatting_ostream< CharT, TraitsT, AllocatorT >::imbue_event;
template< typename CharT, typename TraitsT, typename AllocatorT >
BOOST_CONSTEXPR_OR_CONST typename basic_formatting_ostream< CharT, TraitsT, AllocatorT >::event basic_formatting_ostream< CharT, TraitsT, AllocatorT >::copyfmt_event;

template< typename CharT, typename TraitsT, typename AllocatorT >
void basic_formatting_ostream< CharT, TraitsT, AllocatorT >::aligned_write(const char_type* p, std::streamsize size)
{
    typename string_type::size_type const alignment_size =
        static_cast< typename string_type::size_type >(m_stream.width() - size);
    const bool align_left = (m_stream.flags() & ostream_type::adjustfield) == ostream_type::left;
    if (align_left)
    {
        m_streambuf.append(p, static_cast< std::size_t >(size));
        m_streambuf.append(alignment_size, m_stream.fill());
    }
    else
    {
        m_streambuf.append(alignment_size, m_stream.fill());
        m_streambuf.append(p, static_cast< std::size_t >(size));
    }
}

template< typename CharT, typename TraitsT, typename AllocatorT >
template< typename OtherCharT >
void basic_formatting_ostream< CharT, TraitsT, AllocatorT >::aligned_write(const OtherCharT* p, std::streamsize size)
{
    string_type* const storage = m_streambuf.storage();
    typename string_type::size_type const alignment_size =
        static_cast< typename string_type::size_type >(m_stream.width() - size);
    const bool align_left = (m_stream.flags() & ostream_type::adjustfield) == ostream_type::left;
    if (align_left)
    {
        if (!m_streambuf.storage_overflow())
        {
            if (!aux::code_convert(p, static_cast< std::size_t >(size), *storage, m_streambuf.max_size(), m_stream.getloc()))
                m_streambuf.storage_overflow(true);
        }
        m_streambuf.append(alignment_size, m_stream.fill());
    }
    else
    {
        m_streambuf.append(alignment_size, m_stream.fill());
        if (!m_streambuf.storage_overflow())
        {
            if (!aux::code_convert(p, static_cast< std::size_t >(size), *storage, m_streambuf.max_size(), m_stream.getloc()))
                m_streambuf.storage_overflow(true);
        }
    }
}

// Implementation note: these operators below should be the least attractive for the compiler
// so that user's overloads are chosen, when present. We use function template partial ordering for this purpose.
// We also don't use perfect forwarding for the right hand argument because in this case the generic overload
// would be more preferred than the typical one written by users:
//
// formatting_ostream& operator<< (formatting_ostream& strm, my_type const& arg);
//
// This is because my_type rvalues require adding const to the type, which counts as a conversion that is not required
// if there is a perfect forwarding overload.
template< typename StreamT, typename T >
inline typename boost::log::aux::enable_formatting_ostream_generic_operator< StreamT, T, true, StreamT& >::type
operator<< (StreamT& strm, T value)
{
    strm.stream() << value;
    return strm;
}

template< typename StreamT, typename T >
inline typename boost::log::aux::enable_formatting_ostream_generic_operator< StreamT, T, false, StreamT& >::type
operator<< (StreamT& strm, T const& value)
{
    strm.stream() << value;
    return strm;
}

template< typename StreamT, typename T >
inline typename boost::log::aux::enable_formatting_ostream_generic_operator< StreamT, T, false, StreamT& >::type
operator<< (StreamT& strm, T& value)
{
    strm.stream() << value;
    return strm;
}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

template< typename StreamT, typename T >
inline typename boost::log::aux::enable_formatting_ostream_generic_operator< StreamT, T, true, StreamT& >::type
operator<< (StreamT&& strm, T value)
{
    strm.stream() << value;
    return strm;
}

template< typename StreamT, typename T >
inline typename boost::log::aux::enable_formatting_ostream_generic_operator< StreamT, T, false, StreamT& >::type
operator<< (StreamT&& strm, T const& value)
{
    strm.stream() << value;
    return strm;
}

template< typename StreamT, typename T >
inline typename boost::log::aux::enable_formatting_ostream_generic_operator< StreamT, T, false, StreamT& >::type
operator<< (StreamT&& strm, T& value)
{
    strm.stream() << value;
    return strm;
}

#endif // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FORMATTING_OSTREAM_HPP_INCLUDED_

/* formatting_ostream.hpp
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
*/