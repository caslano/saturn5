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