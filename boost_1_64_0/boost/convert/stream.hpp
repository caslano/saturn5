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
FrvhLky0ndj2HJi85gx64gRzR5MPAIverAe398P2N4A9rTg/8kRn4CQ5pxkD21v/KjyPeKgS9vw87wALG2I3c8C+8f5gBpwcnV4CL4gOA3d+VL+jdToxzXL84w97sK3PiftnM+4wsLUxnPIMsmuOjB7BruDDjyL3hyuDhV/Bl/Bnt8+Bg8IZfsGGvkkE45mnSiI5B3E/gnyj4VO/k0N+Afu48iS6P5f4ZAr6FkeOzgEOw6+ufAcmE6dWxbc+s4xzAgtbxMNB5uBv8PcDuYdzsE/nC3DpfxGvocP70Pf53eAg2FcjFzp9P3axiVzseHgNcfIYfF4q9p7FuQV/AE+6E3x4Fo5SDH8dgC09BNYG4q+vITuwrA+Ym38M25uILg3ER8NzapCXHnUFHN3OPH7kitKJjQKIh+CUsdyrxcE1fnESp3/JfmYSsxCvhL2JjoK3O7hje5a+67ei45xPefDpu585C/JF1xqAE/3pUwe/0pg31ZvJF07g/oj3cQerEG8PQR60DSROSv+Ac0RfZ6Oj9zjAaeqLhhEbM749gLgQXl98Eh15lj135d+tKYfHhtuI0dGDVHBm0QzibN4f/EZcZkefXYfxYdhB8tf4rSD29hnxHva6fxI+bTF6/T3xJWsotxVZgk+LiDPXsu6jA8D6C8j0B/gg97FVwcDZMbwzQOa3/YxPJh7gvxdCPW8gWEsj9GToFfB+GmtK444Nm/zJj3GY+/oA/HQCvOpTcpcVmAMftG2AiGHRNep7g/W7wfNHDuD7yGs9UA55p2AT5DBRA1sU67q/PXrbG/3iHIYM4VybEpsiqyfJB/Z6nlh5BXGLnfV+iD3C85uBi6VwwqXD4VU/EmMMRf+eQcZnwQT80bCafjhJ4sYG4PZiYhl8wk+T8cWc3wmw/thO8Bg9L6mGvyV+TIfPj7zOueKLIrcwP3xgEjj7ElxhXCf4zVXiSQd21BpsfQq5VoODsq7Pl7E/Nz6LmLnnONZ+ArmAv8mp4D+x+8RKxF3vIY8ofFFD5uQsNwlcrURMAra2y+O97hv4rVXoDBgRzDpmMWetcWDMSRs5L2K2yfim4YwPh+z6NjYyD9+HHmcMBkdeI/bYha2uhmPjL6oh093giQ1MXFUP7JzLubbnba4LbsP9YJUW5DomEufSbnpdfD52VIC8hn5NDuNd8jP4t/afEgMT84zpQv5vMng+WfhL8h1N4dRwkUK46dsPw8XhXCf3kncbCf4UYFvgwDz2uY0c0kbkvOwAPB7Magpvj+/C3X8RNj0NO+kNXw3CTn/F/1SEA+IPr5BfbDAf3gkfPT+G816DX+V+Y9gqclHYcc9vwUb8YBj81N4Gf/cg/vwYn4NHTwK+B8Ph+X4d8FviLmwNdjcP7C8F798DI4lHRn9CPA62v4H9NKuCf0lG18kVTD2EHA+BZ/3I1a3E9loQ3y8gPjtAzH4Czh3MGXfHFpHtQ6FgLVjoNxPdgMfMB4sPhvLm4Ul8LTbePRDfD/5GgPF78FfNxuDr8fkB4+BcNYiz66O3yGAaMf/ui8QdyOWODO4PGuO/HMRWxAwfwBUDvwaPkfUdheQK4P4T1oKXU7Ad8uP5m8npLSFftxX7wla6gz+Nwawx5ExavwlvhUf4zybmBPOPZcChH8OfTcW2FuH7WdsQML3iPuIu4qFaxHoFu9CR5zhb7hQ++hLeFo6vTePsXsUXH4SXnCTXwpo2RVP2CPO2B5vBCgdrH74E/oX95E0gTrod3RqNDkI2v/+FvXB2fHcmbz3wJax5xBNgwGX4Gz6/4W4w/mPkxblmfsBdYGd4OzhxmLMfh7615f65Fbg1i/jgExe8l7xC69/gGoG8MwbL/eLhQZM=
*/