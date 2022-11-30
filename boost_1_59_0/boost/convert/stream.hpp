// Copyright (c) 2009-2020 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_STRINGSTREAM_BASED_CONVERTER_HPP
#define BOOST_CONVERT_STRINGSTREAM_BASED_CONVERTER_HPP

#include <boost/convert/parameters.hpp>
#include <boost/convert/detail/is_string.hpp>
#include <boost/make_default.hpp>
#include <sstream>
#include <iomanip>

#define BOOST_CNV_STRING_ENABLE                                             \
    template<typename string_type, typename type>                           \
    typename std::enable_if<cnv::is_string<string_type>::value, void>::type \
    operator()

#define BOOST_CNV_PARAM_SET(param_name)   \
    template <typename argument_pack>     \
    void set_(                            \
        argument_pack const& arg,         \
        cnv::parameter::type::param_name, \
        mpl::true_)

#define BOOST_CNV_PARAM_TRY(param_name)     \
    this->set_(                             \
        arg,                                \
        cnv::parameter::type::param_name(), \
        typename mpl::has_key<              \
            argument_pack, cnv::parameter::type::param_name>::type());

namespace boost { namespace cnv
{
    template<class Char> struct basic_stream;

    using cstream = boost::cnv::basic_stream<char>;
    using wstream = boost::cnv::basic_stream<wchar_t>;
}}

template<class Char>
struct boost::cnv::basic_stream
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

    basic_stream () : stream_(std::ios_base::in | std::ios_base::out) {}
    basic_stream (this_type&& other) : stream_(std::move(other.stream_)) {}

    basic_stream(this_type const&) = delete;
    this_type& operator=(this_type const&) = delete;

    BOOST_CNV_STRING_ENABLE(type const& v, optional<string_type>& s) const { to_str(v, s); }
    BOOST_CNV_STRING_ENABLE(string_type const& s, optional<type>& r) const { str_to(cnv::range<string_type const>(s), r); }

    // Resolve ambiguity of string-to-string
    template<typename type> void operator()(  char_type const* s, optional<type>& r) const { str_to(cnv::range< char_type const*>(s), r); }
    template<typename type> void operator()(stdstr_type const& s, optional<type>& r) const { str_to(cnv::range<stdstr_type const>(s), r); }

    // Formatters
    template<typename manipulator>
    typename boost::disable_if<boost::parameter::is_argument_pack<manipulator>, this_type&>::type
    operator()(manipulator m) { return (this->stream_ << m, *this); }

    this_type& operator() (manipulator_type m) { return (m(stream_), *this); }
    this_type& operator() (std::locale const& l) { return (stream_.imbue(l), *this); }

    template<typename argument_pack>
    typename std::enable_if<boost::parameter::is_argument_pack<argument_pack>::value, this_type&>::type
    operator()(argument_pack const& arg)
    {
        BOOST_CNV_PARAM_TRY(precision);
        BOOST_CNV_PARAM_TRY(width);
        BOOST_CNV_PARAM_TRY(fill);
        BOOST_CNV_PARAM_TRY(uppercase);
        BOOST_CNV_PARAM_TRY(skipws);
        BOOST_CNV_PARAM_TRY(adjust);
        BOOST_CNV_PARAM_TRY(base);
        BOOST_CNV_PARAM_TRY(notation);

        return *this;
    }

    private:

    template<typename argument_pack, typename keyword_tag>
    void set_(argument_pack const&, keyword_tag, mpl::false_) {}

    BOOST_CNV_PARAM_SET (locale)    { stream_.imbue(arg[cnv::parameter::locale]); }
    BOOST_CNV_PARAM_SET (precision) { stream_.precision(arg[cnv::parameter::precision]); }
    BOOST_CNV_PARAM_SET (width)     { stream_.width(arg[cnv::parameter::width]); }
    BOOST_CNV_PARAM_SET (fill)      { stream_.fill(arg[cnv::parameter::fill]); }
    BOOST_CNV_PARAM_SET (uppercase)
    {
        bool uppercase = arg[cnv::parameter::uppercase];
        uppercase ? (void) stream_.setf(std::ios::uppercase) : stream_.unsetf(std::ios::uppercase);
    }
    BOOST_CNV_PARAM_SET (skipws)
    {
        bool skipws = arg[cnv::parameter::skipws];
        skipws ? (void) stream_.setf(std::ios::skipws) : stream_.unsetf(std::ios::skipws);
    }
    BOOST_CNV_PARAM_SET (adjust)
    {
        cnv::adjust adjust = arg[cnv::parameter::adjust];

        /**/ if (adjust == cnv::adjust:: left) stream_.setf(std::ios::adjustfield, std::ios:: left);
        else if (adjust == cnv::adjust::right) stream_.setf(std::ios::adjustfield, std::ios::right);
        else BOOST_ASSERT(!"Not implemented");
    }
    BOOST_CNV_PARAM_SET (base)
    {
        cnv::base base = arg[cnv::parameter::base];

        /**/ if (base == cnv::base::dec) std::dec(stream_);
        else if (base == cnv::base::hex) std::hex(stream_);
        else if (base == cnv::base::oct) std::oct(stream_);
        else BOOST_ASSERT(!"Not implemented");
    }
    BOOST_CNV_PARAM_SET (notation)
    {
        cnv::notation notation = arg[cnv::parameter::notation];

        /**/ if (notation == cnv::notation::     fixed)      std::fixed(stream_);
        else if (notation == cnv::notation::scientific) std::scientific(stream_);
        else BOOST_ASSERT(!"Not implemented");
    }

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
#undef BOOST_CNV_PARAM_SET
#undef BOOST_CNV_PARAM_TRY

#endif // BOOST_CONVERT_STRINGSTREAM_BASED_CONVERTER_HPP

/* stream.hpp
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
*/