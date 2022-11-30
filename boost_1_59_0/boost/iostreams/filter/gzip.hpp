// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains the definitions of the class templates gzip_compressor and
// gzip_decompressor for reading and writing files in the gzip file format
// (RFC 1952). Based in part on work of Jonathan de Halleux; see [...]

#ifndef BOOST_IOSTREAMS_GZIP_HPP_INCLUDED
#define BOOST_IOSTREAMS_GZIP_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp> // STATIC_CONSTANT, STDC_NAMESPACE, 
                            // DINKUMWARE_STDLIB, __STL_CONFIG_H.
#include <algorithm>                      // min.
#include <boost/assert.hpp>
#include <cstdio>                         // EOF.
#include <cstddef>                        // size_t.
#include <ctime>                          // std::time_t.
#include <memory>                         // allocator.
#include <boost/config.hpp>               // Put size_t in std.
#include <boost/detail/workaround.hpp>
#include <boost/cstdint.hpp>              // uint8_t, uint32_t.
#include <boost/iostreams/checked_operations.hpp>
#include <boost/iostreams/constants.hpp>  // buffer size.
#include <boost/iostreams/detail/adapter/non_blocking_adapter.hpp>
#include <boost/iostreams/detail/adapter/range_adapter.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/ios.hpp> // failure, streamsize.
#include <boost/iostreams/detail/error.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/pipeline.hpp>     
#include <boost/iostreams/putback.hpp>
#include <boost/throw_exception.hpp>

// Must come last.
#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable:4244)    // Possible truncation
# pragma warning(disable:4251)    // Missing DLL interface for std::string
# pragma warning(disable:4309)    // Truncation of constant value.
#endif

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std { using ::time_t; }
#endif

namespace boost { namespace iostreams {
                    
//------------------Definitions of constants----------------------------------//

namespace gzip {

using namespace boost::iostreams::zlib;

    // Error codes used by gzip_error.

const int zlib_error        = 1;
const int bad_crc           = 2; // Recorded crc doesn't match data.
const int bad_length        = 3; // Recorded length doesn't match data.
const int bad_header        = 4; // Malformed header.
const int bad_footer        = 5; // Malformed footer.
const int bad_method        = 6; // Unsupported compression method.

namespace magic {

    // Magic numbers used by gzip header.

const int id1               = 0x1f;
const int id2               = 0x8b;

} // End namespace magic.

namespace method {

    // Codes used for the 'CM' byte of the gzip header.

const int deflate           = 8;

} // End namespace method.

namespace flags {

    // Codes used for the 'FLG' byte of the gzip header.

const int text              = 1;
const int header_crc        = 2;
const int extra             = 4;
const int name              = 8;
const int comment           = 16;

} // End namespace flags.

namespace extra_flags {

    // Codes used for the 'XFL' byte of the gzip header.

const int best_compression  = 2;
const int best_speed        = 4;

} // End namespace extra_flags.

    // Codes used for the 'OS' byte of the gzip header.

const int os_fat            = 0;
const int os_amiga          = 1;
const int os_vms            = 2;
const int os_unix           = 3;
const int os_vm_cms         = 4;
const int os_atari          = 5;
const int os_hpfs           = 6;
const int os_macintosh      = 7;
const int os_z_system       = 8;
const int os_cp_m           = 9;
const int os_tops_20        = 10;
const int os_ntfs           = 11;
const int os_qdos           = 12;
const int os_acorn          = 13;
const int os_unknown        = 255;

} // End namespace gzip.

//------------------Definition of gzip_params---------------------------------//

//
// Class name: gzip_params.
// Description: Subclass of zlib_params with an additional field
//      representing a file name.
//
struct gzip_params : zlib_params {

    // Non-explicit constructor.
    gzip_params( int level              = gzip::default_compression,
                 int method             = gzip::deflated,
                 int window_bits        = gzip::default_window_bits,
                 int mem_level          = gzip::default_mem_level,
                 int strategy           = gzip::default_strategy,
                 std::string file_name_  = "",
                 std::string comment_    = "",
                 std::time_t mtime_      = 0 )
        : zlib_params(level, method, window_bits, mem_level, strategy),
          file_name(file_name_), comment(comment_), mtime(mtime_)
        { }
    std::string  file_name;
    std::string  comment;
    std::time_t  mtime;
};

//------------------Definition of gzip_error----------------------------------//

//
// Class name: gzip_error.
// Description: Subclass of std::ios_base::failure thrown to indicate
//     zlib errors other than out-of-memory conditions.
//
class gzip_error : public BOOST_IOSTREAMS_FAILURE {
public:
    explicit gzip_error(int error)
        : BOOST_IOSTREAMS_FAILURE("gzip error"),
          error_(error), zlib_error_code_(zlib::okay) { }
    explicit gzip_error(const zlib_error& e)
        : BOOST_IOSTREAMS_FAILURE("gzip error"),
          error_(gzip::zlib_error), zlib_error_code_(e.error())
        { }
    int error() const { return error_; }
    int zlib_error_code() const { return zlib_error_code_; }
private:
    int error_;
    int zlib_error_code_;
};

//------------------Definition of gzip_compressor-----------------------------//

//
// Template name: gzip_compressor
// Description: Model of OutputFilter implementing compression in the
//      gzip format.
//
template<typename Alloc = std::allocator<char> >
class basic_gzip_compressor : basic_zlib_compressor<Alloc> {
private:
    typedef basic_zlib_compressor<Alloc>  base_type;
public:
    typedef char char_type;
    struct category
        : dual_use,
          filter_tag,
          multichar_tag,
          closable_tag
        { };
    basic_gzip_compressor( const gzip_params& = gzip::default_compression,
                           std::streamsize buffer_size = default_device_buffer_size );

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        std::streamsize result = 0;

        // Read header.
        if (!(flags_ & f_header_done))
            result += read_string(s, n, header_);

        // Read body.
        if (!(flags_ & f_body_done)) {

            // Read from basic_zlib_filter.
            std::streamsize amt = base_type::read(src, s + result, n - result);
            if (amt != -1) {
                result += amt;
                if (amt < n - result) { // Double-check for EOF.
                    amt = base_type::read(src, s + result, n - result);
                    if (amt != -1)
                        result += amt;
                }
            }
            if (amt == -1)
                prepare_footer();
        }

        // Read footer.
        if ((flags_ & f_body_done) != 0 && result < n)
            result += read_string(s + result, n - result, footer_);

        return result != 0 ? result : -1;
    }

    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    {
        if (!(flags_ & f_header_done)) {
            std::streamsize amt = 
                static_cast<std::streamsize>(header_.size() - offset_);
            offset_ += boost::iostreams::write_if(snk, header_.data() + offset_, amt);
            if (offset_ == header_.size())
                flags_ |= f_header_done;
            else
                return 0;
        }
        return base_type::write(snk, s, n);
    }

    template<typename Sink>
    void close(Sink& snk, BOOST_IOS::openmode m)
    {
        try {
            if (m == BOOST_IOS::out && !(flags_ & f_header_done))
                this->write(snk, 0, 0);

            // Close zlib compressor.
            base_type::close(snk, m);

            if (m == BOOST_IOS::out) {
                if (flags_ & f_header_done) {

                    // Write final fields of gzip file format.
                    write_long(this->crc(), snk);
                    write_long(this->total_in(), snk);
                }
            }
        } catch(...) {
            close_impl();
            throw;
        }
        close_impl();
    }
private:
    static gzip_params normalize_params(gzip_params p);
    void prepare_footer();
    std::streamsize read_string(char* s, std::streamsize n, std::string& str);

    template<typename Sink>
    static void write_long(long n, Sink& next, boost::mpl::true_)
    {
        boost::iostreams::put(next, static_cast<char>(0xFF & n));
        boost::iostreams::put(next, static_cast<char>(0xFF & (n >> 8)));
        boost::iostreams::put(next, static_cast<char>(0xFF & (n >> 16)));
        boost::iostreams::put(next, static_cast<char>(0xFF & (n >> 24)));
    }
    template<typename Sink>
    static void write_long(long, Sink&, boost::mpl::false_)
    {
    }
    template<typename Sink>
    static void write_long(long n, Sink& next)
    {
        typedef typename category_of<Sink>::type category;
        typedef is_convertible<category, output> can_write;
        write_long(n, next, can_write());
    }

    void close_impl()
    {
        footer_.clear();
        offset_ = 0;
        flags_ = 0;
    }

    enum state_type {
        f_header_done = 1,
        f_body_done = f_header_done << 1,
        f_footer_done = f_body_done << 1
    };
    std::string  header_;
    std::string  footer_;
    std::size_t  offset_;
    int          flags_;
};
BOOST_IOSTREAMS_PIPABLE(basic_gzip_compressor, 1)

typedef basic_gzip_compressor<> gzip_compressor;

//------------------Definition of helper templates for decompression----------//

namespace detail {

// Processes gzip headers
class BOOST_IOSTREAMS_DECL gzip_header {
public:
    gzip_header() { reset(); }

    // Members for processing header data
    void process(char c);
    bool done() const { return state_ == s_done; }
    void reset();

    // Members for accessing header data
    std::string file_name() const { return file_name_; }
    std::string comment() const { return comment_; }
    bool text() const { return (flags_ & gzip::flags::text) != 0; }
    int os() const { return os_; }
    std::time_t mtime() const { return mtime_; }
private:
    enum state_type {
        s_id1       = 1,
        s_id2       = s_id1 + 1,
        s_cm        = s_id2 + 1,
        s_flg       = s_cm + 1,
        s_mtime     = s_flg + 1,
        s_xfl       = s_mtime + 1,
        s_os        = s_xfl + 1,
        s_xlen      = s_os + 1,
        s_extra     = s_xlen + 1,
        s_name      = s_extra + 1,
        s_comment   = s_name + 1,
        s_hcrc      = s_comment + 1,
        s_done      = s_hcrc + 1
    };
    std::string  file_name_;
    std::string  comment_;
    int          os_;
    std::time_t  mtime_;
    int          flags_;
    int          state_;
    int          offset_;  // Offset within fixed-length region.
    int          xlen_;    // Bytes remaining in extra field.
};

// Processes gzip footers
class BOOST_IOSTREAMS_DECL gzip_footer {
public:
    gzip_footer() { reset(); }
    
    // Members for processing footer data
    void process(char c);
    bool done() const { return state_ == s_done; }
    void reset();
    
    // Members for accessing footer data
    zlib::ulong crc() const { return crc_; }
    zlib::ulong uncompressed_size() const { return isize_; }
private:
    enum state_type {
        s_crc     = 1,
        s_isize   = s_crc + 1,
        s_done    = s_isize + 1
    };
    zlib::ulong  crc_;
    zlib::ulong  isize_;
    int          state_;
    int          offset_; 
};

} // End namespace boost::iostreams::detail.

//------------------Definition of basic_gzip_decompressor---------------------//

//
// Template name: basic_gzip_decompressor
// Description: Model of InputFilter implementing compression in the
//      gzip format.
//
template<typename Alloc = std::allocator<char> >
class basic_gzip_decompressor : basic_zlib_decompressor<Alloc> {
private:
    typedef basic_zlib_decompressor<Alloc>   base_type;
    typedef typename base_type::string_type  string_type;
public:
    typedef char char_type;
    struct category
        : dual_use,
          filter_tag,
          multichar_tag,
          closable_tag
        { };
    basic_gzip_decompressor( int window_bits = gzip::default_window_bits,
                             std::streamsize buffer_size = default_device_buffer_size );

    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    {
        std::streamsize result = 0;
        while(result < n) {
            if(state_ == s_start) {
                state_ = s_header;
                header_.reset();
                footer_.reset();
            }
            if (state_ == s_header) {
                int c = s[result++];
                header_.process(c);
                if (header_.done())
                    state_ = s_body;
            } else if (state_ == s_body) {
                try {
                    std::streamsize amt = 
                        base_type::write(snk, s + result, n - result);
                    result += amt;
                    if (!this->eof()) {
                        break;
                    } else {
                        state_ = s_footer;
                    }
                } catch (const zlib_error& e) {
                    boost::throw_exception(gzip_error(e));
                }
            } else { // state_ == s_footer
                if (footer_.done()) {
                    if (footer_.crc() != this->crc())
                        boost::throw_exception(gzip_error(gzip::bad_crc));

                    base_type::close(snk, BOOST_IOS::out);
                    state_ = s_start;
                } else {
                    int c = s[result++];
                    footer_.process(c);
                }
            }
        }
        return result;
    }

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        typedef char_traits<char>  traits_type;
        std::streamsize            result = 0;
        peekable_source<Source>    peek(src, putback_);
        while (result < n && state_ != s_done) {
            if (state_ == s_start) {
                state_ = s_header;
                header_.reset();
                footer_.reset();
            }
            if (state_ == s_header) {
                int c = boost::iostreams::get(peek);
                if (traits_type::is_eof(c)) {
                    boost::throw_exception(gzip_error(gzip::bad_header));
                } else if (traits_type::would_block(c)) {
                    break;
                }
                header_.process(c);
                if (header_.done())
                    state_ = s_body;
            } else if (state_ == s_body) {
                try {
                    std::streamsize amt = 
                        base_type::read(peek, s + result, n - result);
                    if (amt != -1) {
                        result += amt;
                        if (amt < n - result)
                            break;
                    } else {
                        peek.putback(this->unconsumed_input());
                        state_ = s_footer;
                    }
                } catch (const zlib_error& e) {
                    boost::throw_exception(gzip_error(e));
                }
            } else { // state_ == s_footer
                int c = boost::iostreams::get(peek);
                if (traits_type::is_eof(c)) {
                    boost::throw_exception(gzip_error(gzip::bad_footer));
                } else if (traits_type::would_block(c)) {
                    break;
                }
                footer_.process(c);
                if (footer_.done()) {
                    if (footer_.crc() != this->crc())
                        boost::throw_exception(gzip_error(gzip::bad_crc));
                    c = boost::iostreams::get(peek);
                    if (traits_type::is_eof(c)) {
                        state_ = s_done;
                    } else {
                        peek.putback(c);
                        base_type::close(peek, BOOST_IOS::in);
                        state_ = s_start;
                        header_.reset();
                        footer_.reset();
                    }
                }
            }
        }
        if (peek.has_unconsumed_input()) {
            putback_ = peek.unconsumed_input();
        } else {
            putback_.clear();
        }
        return result != 0 || state_ != s_done ?
            result :
            -1;
    }

    template<typename Source>
    void close(Source& src, BOOST_IOS::openmode m)
    {
        try {
            base_type::close(src, m);
        } catch (const zlib_error& e) {
            state_ = s_start;
            boost::throw_exception(gzip_error(e));
        }
        if (m == BOOST_IOS::out) {
            if (state_ == s_start || state_ == s_header)
                boost::throw_exception(gzip_error(gzip::bad_header));
            else if (state_ == s_body)
                boost::throw_exception(gzip_error(gzip::bad_footer));
            else if (state_ == s_footer) {
                if (!footer_.done())
                    boost::throw_exception(gzip_error(gzip::bad_footer));
                else if(footer_.crc() != this->crc())
                    boost::throw_exception(gzip_error(gzip::bad_crc));
            } else {
                BOOST_ASSERT(!"Bad state");
            }
        }
        state_ = s_start;
    }

    std::string file_name() const { return header_.file_name(); }
    std::string comment() const { return header_.comment(); }
    bool text() const { return header_.text(); }
    int os() const { return header_.os(); }
    std::time_t mtime() const { return header_.mtime(); }
private:
    static gzip_params make_params(int window_bits);

    // Source adapter allowing an arbitrary character sequence to be put back.
    template<typename Source>
    struct peekable_source {
        typedef char char_type;
        struct category : source_tag, peekable_tag { };
        explicit peekable_source(Source& src, const string_type& putback = "") 
            : src_(src), putback_(putback), offset_(0)
            { }
        std::streamsize read(char* s, std::streamsize n)
        {
            std::streamsize result = 0;

            // Copy characters from putback buffer
            std::streamsize pbsize = 
                static_cast<std::streamsize>(putback_.size());
            if (offset_ < pbsize) {
                result = (std::min)(n, pbsize - offset_);
                BOOST_IOSTREAMS_CHAR_TRAITS(char)::copy(
                    s, putback_.data() + offset_, result);
                offset_ += result;
                if (result == n)
                    return result;
            }

            // Read characters from src_
            std::streamsize amt = 
                boost::iostreams::read(src_, s + result, n - result);
            return amt != -1 ? 
                result + amt : 
                result ? result : -1;
        }
        bool putback(char c)
        {
            if (offset_) {
                putback_[--offset_] = c;
            } else {
                boost::throw_exception(
                    boost::iostreams::detail::bad_putback());
            }
            return true;
        }
        void putback(const string_type& s)
        {
            putback_.replace(0, offset_, s);
            offset_ = 0;
        }

        // Returns true if some characters have been putback but not re-read.
        bool has_unconsumed_input() const 
        {
            return offset_ < static_cast<std::streamsize>(putback_.size());
        }

        // Returns the sequence of characters that have been put back but not re-read.
        string_type unconsumed_input() const
        {
            return string_type(putback_, offset_, putback_.size() - offset_);
        }
        Source&          src_;
        string_type      putback_;
        std::streamsize  offset_;
    };

    enum state_type {
        s_start   = 1,
        s_header  = s_start + 1,
        s_body    = s_header + 1,
        s_footer  = s_body + 1,
        s_done    = s_footer + 1
    };
    detail::gzip_header  header_;
    detail::gzip_footer  footer_;
    string_type          putback_;
    int                  state_;
};
BOOST_IOSTREAMS_PIPABLE(basic_gzip_decompressor, 1)

typedef basic_gzip_decompressor<> gzip_decompressor;

//------------------Implementation of gzip_compressor-------------------------//

template<typename Alloc>
basic_gzip_compressor<Alloc>::basic_gzip_compressor
    (const gzip_params& p, std::streamsize buffer_size)
    : base_type(normalize_params(p), buffer_size),
      offset_(0), flags_(0)
{
    // Calculate gzip header.
    bool has_name = !p.file_name.empty();
    bool has_comment = !p.comment.empty();

    std::string::size_type length =
        10 +
        (has_name ? p.file_name.size() + 1 : 0) +
        (has_comment ? p.comment.size() + 1 : 0);
        // + 2; // Header crc confuses gunzip.
    int flags =
        //gzip::flags::header_crc +
        (has_name ? gzip::flags::name : 0) +
        (has_comment ? gzip::flags::comment : 0);
    int extra_flags =
        ( p.level == zlib::best_compression ?
              gzip::extra_flags::best_compression :
              0 ) +
        ( p.level == zlib::best_speed ?
              gzip::extra_flags::best_speed :
              0 );
    header_.reserve(length);
    header_ += gzip::magic::id1;                         // ID1.
    header_ += static_cast<char>(gzip::magic::id2);      // ID2.
    header_ += gzip::method::deflate;                    // CM.
    header_ += static_cast<char>(flags);                 // FLG.
    header_ += static_cast<char>(0xFF & p.mtime);        // MTIME.
    header_ += static_cast<char>(0xFF & (p.mtime >> 8));
    header_ += static_cast<char>(0xFF & (p.mtime >> 16));
    header_ += static_cast<char>(0xFF & (p.mtime >> 24));
    header_ += static_cast<char>(extra_flags);           // XFL.
    header_ += static_cast<char>(gzip::os_unknown);      // OS.
    if (has_name) {
        header_ += p.file_name;
        header_ += '\0';
    }
    if (has_comment) {
        header_ += p.comment;
        header_ += '\0';
    }
}

template<typename Alloc>
gzip_params basic_gzip_compressor<Alloc>::normalize_params(gzip_params p)
{
    p.noheader = true;
    p.calculate_crc = true;
    return p;
}

template<typename Alloc>
void basic_gzip_compressor<Alloc>::prepare_footer()
{
    boost::iostreams::back_insert_device<std::string> out(footer_);
    write_long(this->crc(), out);
    write_long(this->total_in(), out);
    flags_ |= f_body_done;
    offset_ = 0;
}

template<typename Alloc>
std::streamsize basic_gzip_compressor<Alloc>::read_string
    (char* s, std::streamsize n, std::string& str)
{
    std::streamsize avail =
        static_cast<std::streamsize>(str.size() - offset_);
    std::streamsize amt = (std::min)(avail, n);
    std::copy( str.data() + offset_,
               str.data() + offset_ + amt,
               s );
    offset_ += amt;
    if ( !(flags_ & f_header_done) &&
         offset_ == static_cast<std::size_t>(str.size()) )
    {
        flags_ |= f_header_done;
    }
    return amt;
}

//------------------Implementation of gzip_decompressor-----------------------//

template<typename Alloc>
basic_gzip_decompressor<Alloc>::basic_gzip_decompressor
    (int window_bits, std::streamsize buffer_size)
    : base_type(make_params(window_bits), buffer_size),
      state_(s_start)
    { }

template<typename Alloc>
gzip_params basic_gzip_decompressor<Alloc>::make_params(int window_bits)
{
    gzip_params p;
    p.window_bits = window_bits;
    p.noheader = true;
    p.calculate_crc = true;
    return p;
}

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#if defined(BOOST_MSVC)
# pragma warning(pop)
#endif

#endif // #ifndef BOOST_IOSTREAMS_GZIP_HPP_INCLUDED

/* gzip.hpp
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
*/