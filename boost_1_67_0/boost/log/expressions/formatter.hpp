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