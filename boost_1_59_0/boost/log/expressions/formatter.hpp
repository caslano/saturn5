/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatter.hpp
 * \author Andrey Semashev
 * \date   13.07.2012
 *
 * The header contains a formatter function object definition.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTER_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTER_HPP_INCLUDED_

#include <locale>
#include <ostream>
#include <boost/ref.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/log/detail/sfinae_tools.hpp>
#endif
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/light_function.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/attributes/value_visitation.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/utility/functional/bind_output.hpp>
#include <boost/log/expressions/message.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

// This reference class is a workaround for a Boost.Phoenix bug: https://svn.boost.org/trac/boost/ticket/9363
// It is needed to pass output streams by non-const reference to function objects wrapped in phoenix::bind and phoenix::function.
// It's an implementation detail and will be removed when Boost.Phoenix is fixed.
template< typename StreamT >
class stream_ref :
    public reference_wrapper< StreamT >
{
public:
    typedef typename StreamT::char_type char_type;
    typedef typename StreamT::traits_type traits_type;
    typedef typename StreamT::allocator_type allocator_type;
    typedef typename StreamT::streambuf_type streambuf_type;
    typedef typename StreamT::string_type string_type;
    typedef typename StreamT::ostream_type ostream_type;
    typedef typename StreamT::pos_type pos_type;
    typedef typename StreamT::off_type off_type;
    typedef typename StreamT::int_type int_type;

    typedef typename StreamT::failure failure;
    typedef typename StreamT::fmtflags fmtflags;
    typedef typename StreamT::iostate iostate;
    typedef typename StreamT::openmode openmode;
    typedef typename StreamT::seekdir seekdir;
    typedef typename StreamT::Init Init;

    typedef typename StreamT::event event;
    typedef typename StreamT::event_callback event_callback;

    typedef typename StreamT::sentry sentry;

    static BOOST_CONSTEXPR_OR_CONST fmtflags boolalpha = StreamT::boolalpha;
    static BOOST_CONSTEXPR_OR_CONST fmtflags dec = StreamT::dec;
    static BOOST_CONSTEXPR_OR_CONST fmtflags fixed = StreamT::fixed;
    static BOOST_CONSTEXPR_OR_CONST fmtflags hex = StreamT::hex;
    static BOOST_CONSTEXPR_OR_CONST fmtflags internal = StreamT::internal;
    static BOOST_CONSTEXPR_OR_CONST fmtflags left = StreamT::left;
    static BOOST_CONSTEXPR_OR_CONST fmtflags oct = StreamT::oct;
    static BOOST_CONSTEXPR_OR_CONST fmtflags right = StreamT::right;
    static BOOST_CONSTEXPR_OR_CONST fmtflags scientific = StreamT::scientific;
    static BOOST_CONSTEXPR_OR_CONST fmtflags showbase = StreamT::showbase;
    static BOOST_CONSTEXPR_OR_CONST fmtflags showpoint = StreamT::showpoint;
    static BOOST_CONSTEXPR_OR_CONST fmtflags skipws = StreamT::skipws;
    static BOOST_CONSTEXPR_OR_CONST fmtflags unitbuf = StreamT::unitbuf;
    static BOOST_CONSTEXPR_OR_CONST fmtflags uppercase = StreamT::uppercase;
    static BOOST_CONSTEXPR_OR_CONST fmtflags adjustfield = StreamT::adjustfield;
    static BOOST_CONSTEXPR_OR_CONST fmtflags basefield = StreamT::basefield;
    static BOOST_CONSTEXPR_OR_CONST fmtflags floatfield = StreamT::floatfield;

    static BOOST_CONSTEXPR_OR_CONST iostate badbit = StreamT::badbit;
    static BOOST_CONSTEXPR_OR_CONST iostate eofbit = StreamT::eofbit;
    static BOOST_CONSTEXPR_OR_CONST iostate failbit = StreamT::failbit;
    static BOOST_CONSTEXPR_OR_CONST iostate goodbit = StreamT::goodbit;

    static BOOST_CONSTEXPR_OR_CONST openmode app = StreamT::app;
    static BOOST_CONSTEXPR_OR_CONST openmode ate = StreamT::ate;
    static BOOST_CONSTEXPR_OR_CONST openmode binary = StreamT::binary;
    static BOOST_CONSTEXPR_OR_CONST openmode in = StreamT::in;
    static BOOST_CONSTEXPR_OR_CONST openmode out = StreamT::out;
    static BOOST_CONSTEXPR_OR_CONST openmode trunc = StreamT::trunc;

    static BOOST_CONSTEXPR_OR_CONST seekdir beg = StreamT::beg;
    static BOOST_CONSTEXPR_OR_CONST seekdir cur = StreamT::cur;
    static BOOST_CONSTEXPR_OR_CONST seekdir end = StreamT::end;

    static BOOST_CONSTEXPR_OR_CONST event erase_event = StreamT::erase_event;
    static BOOST_CONSTEXPR_OR_CONST event imbue_event = StreamT::imbue_event;
    static BOOST_CONSTEXPR_OR_CONST event copyfmt_event = StreamT::copyfmt_event;


    BOOST_FORCEINLINE explicit stream_ref(StreamT& strm) : reference_wrapper< StreamT >(strm)
    {
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template< typename T >
    BOOST_FORCEINLINE StreamT& operator<< (T&& val) const
    {
        StreamT& strm = this->get();
        strm << static_cast< T&& >(val);
        return strm;
    }
#if defined(BOOST_MSVC) && BOOST_MSVC < 1800
    // MSVC 10 and 11 generate broken code for the perfect forwarding version above if T is an array type (e.g. a string literal)
    template< typename T, unsigned int N >
    BOOST_FORCEINLINE StreamT& operator<< (T (&val)[N]) const
    {
        StreamT& strm = this->get();
        strm << val;
        return strm;
    }
#endif
#else
    template< typename T >
    BOOST_FORCEINLINE StreamT& operator<< (T& val) const
    {
        StreamT& strm = this->get();
        strm << val;
        return strm;
    }

    template< typename T >
    BOOST_FORCEINLINE StreamT& operator<< (T const& val) const
    {
        StreamT& strm = this->get();
        strm << val;
        return strm;
    }
#endif

    BOOST_FORCEINLINE void attach(string_type& str) const { this->get().attach(str); }
    BOOST_FORCEINLINE void detach() const { this->get().detach(); }
    BOOST_FORCEINLINE string_type const& str() const { return this->get().str(); }
    BOOST_FORCEINLINE ostream_type& stream() const { return this->get().stream(); }
    BOOST_FORCEINLINE fmtflags flags() const { return this->get().flags(); }
    BOOST_FORCEINLINE fmtflags flags(fmtflags f) const { return this->get().flags(f); }
    BOOST_FORCEINLINE fmtflags setf(fmtflags f) const { return this->get().setf(f); }
    BOOST_FORCEINLINE fmtflags setf(fmtflags f, fmtflags mask) const { return this->get().setf(f, mask); }
    BOOST_FORCEINLINE void unsetf(fmtflags f) const { this->get().unsetf(f); }

    BOOST_FORCEINLINE std::streamsize precision() const { return this->get().precision(); }
    BOOST_FORCEINLINE std::streamsize precision(std::streamsize p) const { return this->get().precision(p); }

    BOOST_FORCEINLINE std::streamsize width() const { return this->get().width(); }
    BOOST_FORCEINLINE std::streamsize width(std::streamsize w) const { return this->get().width(w); }

    BOOST_FORCEINLINE std::locale getloc() const { return this->get().getloc(); }
    BOOST_FORCEINLINE std::locale imbue(std::locale const& loc) const { return this->get().imbue(loc); }

    static BOOST_FORCEINLINE int xalloc() { return StreamT::xalloc(); }
    BOOST_FORCEINLINE long& iword(int index) const { return this->get().iword(index); }
    BOOST_FORCEINLINE void*& pword(int index) const { return this->get().pword(index); }

    BOOST_FORCEINLINE void register_callback(event_callback fn, int index) const { this->get().register_callback(fn, index); }

    static BOOST_FORCEINLINE bool sync_with_stdio(bool sync = true) { return StreamT::sync_with_stdio(sync); }

    BOOST_EXPLICIT_OPERATOR_BOOL()
    BOOST_FORCEINLINE bool operator! () const { return !this->get(); }

    BOOST_FORCEINLINE iostate rdstate() const { return this->get().rdstate(); }
    BOOST_FORCEINLINE void clear(iostate state = goodbit) const { this->get().clear(state); }
    BOOST_FORCEINLINE void setstate(iostate state) const { this->get().setstate(state); }
    BOOST_FORCEINLINE bool good() const { return this->get().good(); }
    BOOST_FORCEINLINE bool eof() const { return this->get().eof(); }
    BOOST_FORCEINLINE bool fail() const { return this->get().fail(); }
    BOOST_FORCEINLINE bool bad() const { return this->get().bad(); }

    BOOST_FORCEINLINE iostate exceptions() const { return this->get().exceptions(); }
    BOOST_FORCEINLINE void exceptions(iostate s) const { this->get().exceptions(s); }

    BOOST_FORCEINLINE ostream_type* tie() const { return this->get().tie(); }
    BOOST_FORCEINLINE ostream_type* tie(ostream_type* strm) const { return this->get().tie(strm); }

    BOOST_FORCEINLINE streambuf_type* rdbuf() const { return this->get().rdbuf(); }

    BOOST_FORCEINLINE StreamT& copyfmt(std::basic_ios< char_type, traits_type >& rhs) const { return this->get().copyfmt(rhs); }
    BOOST_FORCEINLINE StreamT& copyfmt(StreamT& rhs) const { return this->get().copyfmt(rhs); }

    BOOST_FORCEINLINE char_type fill() const { return this->get().fill(); }
    BOOST_FORCEINLINE char_type fill(char_type ch) const { return this->get().fill(ch); }

    BOOST_FORCEINLINE char narrow(char_type ch, char def) const { return this->get().narrow(ch, def); }
    BOOST_FORCEINLINE char_type widen(char ch) const { return this->get().widen(ch); }

    BOOST_FORCEINLINE StreamT& flush() const { return this->get().flush(); }

    BOOST_FORCEINLINE pos_type tellp() const { return this->get().tellp(); }
    BOOST_FORCEINLINE StreamT& seekp(pos_type pos) const { return this->get().seekp(pos); }
    BOOST_FORCEINLINE StreamT& seekp(off_type off, std::ios_base::seekdir dir) const { return this->get().seekp(off, dir); }

    template< typename CharT >
    BOOST_FORCEINLINE typename boost::log::aux::enable_if_streamable_char_type< CharT, StreamT& >::type
    put(CharT c) const { return this->get().put(c); }

    template< typename CharT >
    BOOST_FORCEINLINE typename boost::log::aux::enable_if_streamable_char_type< CharT, StreamT& >::type
    write(const CharT* p, std::streamsize size) const { return this->get().write(p, size); }
};

template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::fmtflags stream_ref< StreamT >::boolalpha;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::fmtflags stream_ref< StreamT >::dec;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::fmtflags stream_ref< StreamT >::fixed;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::fmtflags stream_ref< StreamT >::hex;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::fmtflags stream_ref< StreamT >::internal;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::fmtflags stream_ref< StreamT >::left;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::fmtflags stream_ref< StreamT >::oct;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::fmtflags stream_ref< StreamT >::right;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::fmtflags stream_ref< StreamT >::scientific;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::fmtflags stream_ref< StreamT >::showbase;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::fmtflags stream_ref< StreamT >::showpoint;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::fmtflags stream_ref< StreamT >::skipws;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::fmtflags stream_ref< StreamT >::unitbuf;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::fmtflags stream_ref< StreamT >::uppercase;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::fmtflags stream_ref< StreamT >::adjustfield;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::fmtflags stream_ref< StreamT >::basefield;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::fmtflags stream_ref< StreamT >::floatfield;

template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::iostate stream_ref< StreamT >::badbit;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::iostate stream_ref< StreamT >::eofbit;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::iostate stream_ref< StreamT >::failbit;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::iostate stream_ref< StreamT >::goodbit;

template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::openmode stream_ref< StreamT >::app;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::openmode stream_ref< StreamT >::ate;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::openmode stream_ref< StreamT >::binary;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::openmode stream_ref< StreamT >::in;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::openmode stream_ref< StreamT >::out;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::openmode stream_ref< StreamT >::trunc;

template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::seekdir stream_ref< StreamT >::beg;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::seekdir stream_ref< StreamT >::cur;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::seekdir stream_ref< StreamT >::end;

template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::event stream_ref< StreamT >::erase_event;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::event stream_ref< StreamT >::imbue_event;
template< typename StreamT >
BOOST_CONSTEXPR_OR_CONST typename stream_ref< StreamT >::event stream_ref< StreamT >::copyfmt_event;

//! Default log record message formatter
struct message_formatter
{
    typedef void result_type;

    message_formatter() : m_MessageName(expressions::tag::message::get_name())
    {
    }

    template< typename StreamT >
    BOOST_FORCEINLINE result_type operator() (record_view const& rec, StreamT& strm) const
    {
        boost::log::visit< expressions::tag::message::value_type >(m_MessageName, rec, boost::log::bind_output(strm));
    }

private:
    const attribute_name m_MessageName;
};

} // namespace aux

} // namespace expressions

/*!
 * Log record formatter function wrapper.
 */
template< typename CharT >
class basic_formatter
{
    typedef basic_formatter this_type;
    BOOST_COPYABLE_AND_MOVABLE(this_type)

public:
    //! Result type
    typedef void result_type;

    //! Character type
    typedef CharT char_type;
    //! Output stream type
    typedef basic_formatting_ostream< char_type > stream_type;

private:
    //! Filter function type
    typedef boost::log::aux::light_function< void (record_view const&, expressions::aux::stream_ref< stream_type >) > formatter_type;

private:
    //! Formatter function
    formatter_type m_Formatter;

public:
    /*!
     * Default constructor. Creates a formatter that only outputs log message.
     */
    basic_formatter() : m_Formatter(expressions::aux::message_formatter())
    {
    }
    /*!
     * Copy constructor
     */
    basic_formatter(basic_formatter const& that) : m_Formatter(that.m_Formatter)
    {
    }
    /*!
     * Move constructor. The moved-from formatter is left in an unspecified state.
     */
    basic_formatter(BOOST_RV_REF(this_type) that) BOOST_NOEXCEPT : m_Formatter(boost::move(that.m_Formatter))
    {
    }

    /*!
     * Initializing constructor. Creates a formatter which will invoke the specified function object.
     */
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template< typename FunT >
    basic_formatter(FunT&& fun) : m_Formatter(boost::forward< FunT >(fun))
    {
    }
#elif !defined(BOOST_MSVC) || BOOST_MSVC >= 1600
    template< typename FunT >
    basic_formatter(FunT const& fun, typename boost::disable_if_c< move_detail::is_rv< FunT >::value, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()) : m_Formatter(fun)
    {
    }
#else
    // MSVC 9 and older blows up in unexpected ways if we use SFINAE to disable constructor instantiation
    template< typename FunT >
    basic_formatter(FunT const& fun) : m_Formatter(fun)
    {
    }
    template< typename FunT >
    basic_formatter(rv< FunT >& fun) : m_Formatter(fun)
    {
    }
    template< typename FunT >
    basic_formatter(rv< FunT > const& fun) : m_Formatter(static_cast< FunT const& >(fun))
    {
    }
    basic_formatter(rv< this_type > const& that) : m_Formatter(that.m_Formatter)
    {
    }
#endif

    /*!
     * Move assignment. The moved-from formatter is left in an unspecified state.
     */
    basic_formatter& operator= (BOOST_RV_REF(this_type) that) BOOST_NOEXCEPT
    {
        m_Formatter.swap(that.m_Formatter);
        return *this;
    }
    /*!
     * Copy assignment.
     */
    basic_formatter& operator= (BOOST_COPY_ASSIGN_REF(this_type) that)
    {
        m_Formatter = that.m_Formatter;
        return *this;
    }
    /*!
     * Initializing assignment. Sets the specified function object to the formatter.
     */
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template< typename FunT >
    basic_formatter& operator= (FunT&& fun)
    {
        this_type(boost::forward< FunT >(fun)).swap(*this);
        return *this;
    }
#else
    template< typename FunT >
    typename boost::disable_if_c< is_same< typename remove_cv< FunT >::type, this_type >::value, this_type& >::type
    operator= (FunT const& fun)
    {
        this_type(fun).swap(*this);
        return *this;
    }
#endif

    /*!
     * Formatting operator.
     *
     * \param rec A log record to format.
     * \param strm A stream to put the formatted characters to.
     */
    result_type operator() (record_view const& rec, stream_type& strm) const
    {
        m_Formatter(rec, expressions::aux::stream_ref< stream_type >(strm));
    }

    /*!
     * Resets the formatter to the default. The default formatter only outputs message text.
     */
    void reset()
    {
        m_Formatter = expressions::aux::message_formatter();
    }

    /*!
     * Swaps two formatters
     */
    void swap(basic_formatter& that) BOOST_NOEXCEPT
    {
        m_Formatter.swap(that.m_Formatter);
    }
};

template< typename CharT >
inline void swap(basic_formatter< CharT >& left, basic_formatter< CharT >& right) BOOST_NOEXCEPT
{
    left.swap(right);
}

#ifdef BOOST_LOG_USE_CHAR
typedef basic_formatter< char > formatter;
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
typedef basic_formatter< wchar_t > wformatter;
#endif

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_FORMATTER_HPP_INCLUDED_

/* formatter.hpp
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
*/