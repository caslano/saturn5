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