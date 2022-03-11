// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_STRINGSTREAM_BASED_CONVERTER_HPP
#define BOOST_CONVERT_STRINGSTREAM_BASED_CONVERTER_HPP

#include <boost/convert/parameters.hpp>
#include <boost/convert/detail/is_string.hpp>
#include <boost/make_default.hpp>
#include <boost/noncopyable.hpp>
#include <sstream>
#include <iomanip>

#define BOOST_CNV_STRING_ENABLE                                         \
    template<typename string_type, typename type>                       \
    typename boost::enable_if<cnv::is_string<string_type>, void>::type  \
    operator()

#define BOOST_CNV_PARAM(PARAM_NAME, PARAM_TYPE) \
    this_type&                                  \
    operator()(boost::parameter::aux::tag<boost::cnv::parameter::type::PARAM_NAME, PARAM_TYPE const>::type const& arg)

namespace boost { namespace cnv
{
    template<class Char> struct basic_stream;

    using cstream = boost::cnv::basic_stream<char>;
    using wstream = boost::cnv::basic_stream<wchar_t>;
}}

template<class Char>
struct boost::cnv::basic_stream : boost::noncopyable
{
    // C01. In string-to-type conversions the "string" must be a CONTIGUOUS ARRAY of
    //      characters because "ibuffer_type" uses/relies on that (it deals with char_type*).
    // C02. Use the provided "string_in" as the input (read-from) buffer and, consequently,
    //      avoid the overhead associated with stream_.str(string_in) --
    //      copying of the content into internal buffer.
    // C03. The "strbuf.gptr() != strbuf.egptr()" check replaces "istream.eof() != true"
    //      which for some reason does not work when we try converting the "true" string
    //      to "bool" with std::boolalpha set. Seems that istream state gets unsynced compared
    //      to the actual underlying buffer.

    using        char_type = Char;
    using        this_type = boost::cnv::basic_stream<char_type>;
    using      stream_type = std::basic_stringstream<char_type>;
    using     istream_type = std::basic_istream<char_type>;
    using      buffer_type = std::basic_streambuf<char_type>;
    using      stdstr_type = std::basic_string<char_type>;
    using manipulator_type = std::ios_base& (*)(std::ios_base&);

    struct ibuffer_type : buffer_type
    {
        using buffer_type::eback;
        using buffer_type::gptr;
        using buffer_type::egptr;

        ibuffer_type(char_type const* beg, std::size_t sz) //C01
        {
            char_type* b = const_cast<char_type*>(beg);

            buffer_type::setg(b, b, b + sz);
        }
    };
    struct obuffer_type : buffer_type
    {
        using buffer_type::pbase;
        using buffer_type::pptr;
        using buffer_type::epptr;
    };

    basic_stream() : stream_(std::ios_base::in | std::ios_base::out) {}
#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )
    basic_stream(this_type&& other) : stream_(std::move(other.stream_)) {}
#endif

    BOOST_CNV_STRING_ENABLE(type const& v, optional<string_type>& s) const { to_str(v, s); }
    BOOST_CNV_STRING_ENABLE(string_type const& s, optional<type>& r) const { str_to(cnv::range<string_type const>(s), r); }
    // Resolve ambiguity of string-to-string
    template<typename type> void operator()(  char_type const* s, optional<type>& r) const { str_to(cnv::range< char_type const*>(s), r); }
    template<typename type> void operator()(stdstr_type const& s, optional<type>& r) const { str_to(cnv::range<stdstr_type const>(s), r); }

    // Formatters
    template<typename manipulator>
    this_type& operator() (manipulator m) { return (stream_ << m, *this); }
    this_type& operator() (manipulator_type m) { return (m(stream_), *this); }
    this_type& operator() (std::locale const& l) { return (stream_.imbue(l), *this); }

    BOOST_CNV_PARAM(locale, std::locale) { return (stream_.imbue(arg[cnv::parameter::locale]), *this); }
    BOOST_CNV_PARAM(precision,      int) { return (stream_.precision(arg[cnv::parameter::precision]), *this); }
    BOOST_CNV_PARAM(width,          int) { return (stream_.width(arg[cnv::parameter::width]), *this); }
    BOOST_CNV_PARAM(fill,          char) { return (stream_.fill(arg[cnv::parameter::fill]), *this); }
    BOOST_CNV_PARAM(uppercase,     bool)
    {
        bool uppercase = arg[cnv::parameter::uppercase];
        uppercase ? (void) stream_.setf(std::ios::uppercase) : stream_.unsetf(std::ios::uppercase);
        return *this;
    }
    BOOST_CNV_PARAM(skipws, bool)
    {
        bool skipws = arg[cnv::parameter::skipws];
        skipws ? (void) stream_.setf(std::ios::skipws) : stream_.unsetf(std::ios::skipws);
        return *this;
    }
    BOOST_CNV_PARAM(adjust, boost::cnv::adjust)
    {
        cnv::adjust adjust = arg[cnv::parameter::adjust];

        /**/ if (adjust == cnv::adjust:: left) stream_.setf(std::ios::adjustfield, std::ios:: left);
        else if (adjust == cnv::adjust::right) stream_.setf(std::ios::adjustfield, std::ios::right);
        else BOOST_ASSERT(!"Not implemented");

        return *this;
    }
    BOOST_CNV_PARAM(base, boost::cnv::base)
    {
        cnv::base base = arg[cnv::parameter::base];

        /**/ if (base == cnv::base::dec) std::dec(stream_);
        else if (base == cnv::base::hex) std::hex(stream_);
        else if (base == cnv::base::oct) std::oct(stream_);
        else BOOST_ASSERT(!"Not implemented");

        return *this;
    }
    BOOST_CNV_PARAM(notation, boost::cnv::notation)
    {
        cnv::notation notation = arg[cnv::parameter::notation];

        /**/ if (notation == cnv::notation::     fixed)      std::fixed(stream_);
        else if (notation == cnv::notation::scientific) std::scientific(stream_);
        else BOOST_ASSERT(!"Not implemented");

        return *this;
    }

    private:

    template<typename string_type, typename out_type> void str_to(cnv::range<string_type>, optional<out_type>&) const;
    template<typename string_type, typename  in_type> void to_str(in_type const&, optional<string_type>&) const;

    mutable stream_type stream_;
};

template<typename char_type>
template<typename string_type, typename in_type>
inline
void
boost::cnv::basic_stream<char_type>::to_str(
    in_type const& value_in,
    boost::optional<string_type>& string_out) const
{
    stream_.clear();            // Clear the flags
    stream_.str(stdstr_type()); // Clear/empty the content of the stream

    if (!(stream_ << value_in).fail())
    {
        buffer_type*     buf = stream_.rdbuf();
        obuffer_type*   obuf = reinterpret_cast<obuffer_type*>(buf);
        char_type const* beg = obuf->pbase();
        char_type const* end = obuf->pptr();

        string_out = string_type(beg, end); // Instead of stream_.str();
    }
}

template<typename char_type>
template<typename string_type, typename out_type>
inline
void
boost::cnv::basic_stream<char_type>::str_to(
    boost::cnv::range<string_type> string_in,
    boost::optional<out_type>& result_out) const
{
    if (string_in.empty ()) return;

    istream_type& istream = stream_;
    buffer_type*   oldbuf = istream.rdbuf();
    char_type const*  beg = &*string_in.begin();
    std::size_t        sz = string_in.end() - string_in.begin();
    ibuffer_type   newbuf (beg, sz); //C02

    istream.rdbuf(&newbuf);
    istream.clear(); // Clear the flags

    istream >> *(result_out = boost::make_default<out_type>());

    if (istream.fail() || newbuf.gptr() != newbuf.egptr()/*C03*/)
        result_out = boost::none;

    istream.rdbuf(oldbuf);
}

#undef BOOST_CNV_STRING_ENABLE
#undef BOOST_CNV_PARAM

#endif // BOOST_CONVERT_STRINGSTREAM_BASED_CONVERTER_HPP

/* stream.hpp
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
*/