// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Note: custom allocators are not supported on VC6, since that compiler
// had trouble finding the function zlib_base::do_init.

#ifndef BOOST_IOSTREAMS_ZLIB_HPP_INCLUDED
#define BOOST_IOSTREAMS_ZLIB_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <cassert>                            
#include <iosfwd>            // streamsize.                 
#include <memory>            // allocator, bad_alloc.
#include <new>          
#include <boost/config.hpp>  // MSVC, STATIC_CONSTANT, DEDUCED_TYPENAME, DINKUM.
#include <boost/cstdint.hpp> // uint*_t
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/constants.hpp>   // buffer size.
#include <boost/iostreams/detail/config/auto_link.hpp>
#include <boost/iostreams/detail/config/dyn_link.hpp>
#include <boost/iostreams/detail/config/wide_streams.hpp>
#include <boost/iostreams/detail/config/zlib.hpp>
#include <boost/iostreams/detail/ios.hpp>  // failure, streamsize.
#include <boost/iostreams/filter/symmetric.hpp>                
#include <boost/iostreams/pipeline.hpp>                
#include <boost/type_traits/is_same.hpp>

// Must come last.
#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable:4251 4275 4231 4660)         // Dependencies not exported.
#endif
#include <boost/config/abi_prefix.hpp>           

namespace boost { namespace iostreams {

namespace zlib {
                    // Typedefs

typedef uint32_t uint;
typedef uint8_t byte;
typedef uint32_t ulong;

// Prefix 'x' prevents symbols from being redefined when Z_PREFIX is defined
typedef void* (*xalloc_func)(void*, zlib::uint, zlib::uint);
typedef void (*xfree_func)(void*, void*);

                    // Compression levels

BOOST_IOSTREAMS_DECL extern const int no_compression;
BOOST_IOSTREAMS_DECL extern const int best_speed;
BOOST_IOSTREAMS_DECL extern const int best_compression;
BOOST_IOSTREAMS_DECL extern const int default_compression;

                    // Compression methods

BOOST_IOSTREAMS_DECL extern const int deflated;

                    // Compression strategies

BOOST_IOSTREAMS_DECL extern const int default_strategy;
BOOST_IOSTREAMS_DECL extern const int filtered;
BOOST_IOSTREAMS_DECL extern const int huffman_only;

                    // Status codes

BOOST_IOSTREAMS_DECL extern const int okay;
BOOST_IOSTREAMS_DECL extern const int stream_end;
BOOST_IOSTREAMS_DECL extern const int stream_error;
BOOST_IOSTREAMS_DECL extern const int version_error;
BOOST_IOSTREAMS_DECL extern const int data_error;
BOOST_IOSTREAMS_DECL extern const int mem_error;
BOOST_IOSTREAMS_DECL extern const int buf_error;

                    // Flush codes

BOOST_IOSTREAMS_DECL extern const int finish;
BOOST_IOSTREAMS_DECL extern const int no_flush;
BOOST_IOSTREAMS_DECL extern const int sync_flush;

                    // Code for current OS

//BOOST_IOSTREAMS_DECL extern const int os_code;

                    // Null pointer constant.

const int null                               = 0;

                    // Default values

const int default_window_bits                = 15;
const int default_mem_level                  = 8;
const bool default_crc                       = false;
const bool default_noheader                  = false;

} // End namespace zlib. 

//
// Class name: zlib_params.
// Description: Encapsulates the parameters passed to deflateInit2
//      and inflateInit2 to customize compression and decompression.
//
struct zlib_params {

    // Non-explicit constructor.
    zlib_params( int level_          = zlib::default_compression,
                 int method_         = zlib::deflated,
                 int window_bits_    = zlib::default_window_bits, 
                 int mem_level_      = zlib::default_mem_level, 
                 int strategy_       = zlib::default_strategy,
                 bool noheader_      = zlib::default_noheader,
                 bool calculate_crc_ = zlib::default_crc )
        : level(level_), method(method_), window_bits(window_bits_),
          mem_level(mem_level_), strategy(strategy_),  
          noheader(noheader_), calculate_crc(calculate_crc_)
        { }
    int level;
    int method;
    int window_bits;
    int mem_level;
    int strategy;
    bool noheader;
    bool calculate_crc;
};

//
// Class name: zlib_error.
// Description: Subclass of std::ios::failure thrown to indicate
//     zlib errors other than out-of-memory conditions.
//
class BOOST_IOSTREAMS_DECL zlib_error : public BOOST_IOSTREAMS_FAILURE {
public:
    explicit zlib_error(int error);
    int error() const { return error_; }
    static void check BOOST_PREVENT_MACRO_SUBSTITUTION(int error);
private:
    int error_;
};

namespace detail {

template<typename Alloc>
struct zlib_allocator_traits {
#ifndef BOOST_NO_STD_ALLOCATOR
#if defined(BOOST_NO_CXX11_ALLOCATOR)
    typedef typename Alloc::template rebind<char>::other type;
#else
    typedef typename std::allocator_traits<Alloc>::template rebind_alloc<char> type;
#endif
#else
    typedef std::allocator<char> type;
#endif
};

template< typename Alloc,
          typename Base = // VC6 workaround (C2516)
              BOOST_DEDUCED_TYPENAME zlib_allocator_traits<Alloc>::type >
struct zlib_allocator : private Base {
private:
#if defined(BOOST_NO_CXX11_ALLOCATOR) || defined(BOOST_NO_STD_ALLOCATOR)
    typedef typename Base::size_type size_type;
#else
    typedef typename std::allocator_traits<Base>::size_type size_type;
#endif
public:
    BOOST_STATIC_CONSTANT(bool, custom = 
        (!is_same<std::allocator<char>, Base>::value));
    typedef typename zlib_allocator_traits<Alloc>::type allocator_type;
    static void* allocate(void* self, zlib::uint items, zlib::uint size);
    static void deallocate(void* self, void* address);
};

class BOOST_IOSTREAMS_DECL zlib_base { 
public:
    typedef char char_type;
protected:
    zlib_base();
    ~zlib_base();
    void* stream() { return stream_; }
    template<typename Alloc> 
    void init( const zlib_params& p, 
               bool compress,
               zlib_allocator<Alloc>& zalloc )
        {
            bool custom = zlib_allocator<Alloc>::custom;
            do_init( p, compress,
                     custom ? zlib_allocator<Alloc>::allocate : 0,
                     custom ? zlib_allocator<Alloc>::deallocate : 0,
                     &zalloc );
        }
    void before( const char*& src_begin, const char* src_end,
                 char*& dest_begin, char* dest_end );
    void after( const char*& src_begin, char*& dest_begin, 
                bool compress );
    int xdeflate(int flush);  // Prefix 'x' prevents symbols from being 
    int xinflate(int flush);  // redefined when Z_PREFIX is defined
    void reset(bool compress, bool realloc);
public:
    zlib::ulong crc() const { return crc_; }
    int total_in() const { return total_in_; }
    int total_out() const { return total_out_; }
private:
    void do_init( const zlib_params& p, bool compress, 
                  zlib::xalloc_func,
                  zlib::xfree_func, 
                  void* derived );
    void*        stream_;         // Actual type: z_stream*.
    bool         calculate_crc_;
    zlib::ulong  crc_;
    zlib::ulong  crc_imp_;
    int          total_in_;
    int          total_out_;
};

//
// Template name: zlib_compressor_impl
// Description: Model of C-Style Filte implementing compression by
//      delegating to the zlib function deflate.
//
template<typename Alloc = std::allocator<char> >
class zlib_compressor_impl : public zlib_base, public zlib_allocator<Alloc> { 
public: 
    zlib_compressor_impl(const zlib_params& = zlib::default_compression);
    ~zlib_compressor_impl();
    bool filter( const char*& src_begin, const char* src_end,
                 char*& dest_begin, char* dest_end, bool flush );
    void close();
};

//
// Template name: zlib_compressor
// Description: Model of C-Style Filte implementing decompression by
//      delegating to the zlib function inflate.
//
template<typename Alloc = std::allocator<char> >
class zlib_decompressor_impl : public zlib_base, public zlib_allocator<Alloc> {
public:
    zlib_decompressor_impl(const zlib_params&);
    zlib_decompressor_impl(int window_bits = zlib::default_window_bits);
    ~zlib_decompressor_impl();
    bool filter( const char*& begin_in, const char* end_in,
                 char*& begin_out, char* end_out, bool flush );
    void close();
    bool eof() const { return eof_; }
private:
    bool eof_;
};

} // End namespace detail.

//
// Template name: zlib_compressor
// Description: Model of InputFilter and OutputFilter implementing
//      compression using zlib.
//
template<typename Alloc = std::allocator<char> >
struct basic_zlib_compressor 
    : symmetric_filter<detail::zlib_compressor_impl<Alloc>, Alloc> 
{
private:
    typedef detail::zlib_compressor_impl<Alloc>         impl_type;
    typedef symmetric_filter<impl_type, Alloc>  base_type;
public:
    typedef typename base_type::char_type               char_type;
    typedef typename base_type::category                category;
    basic_zlib_compressor( const zlib_params& = zlib::default_compression, 
                           std::streamsize buffer_size = default_device_buffer_size );
    zlib::ulong crc() { return this->filter().crc(); }
    int total_in() {  return this->filter().total_in(); }
};
BOOST_IOSTREAMS_PIPABLE(basic_zlib_compressor, 1)

typedef basic_zlib_compressor<> zlib_compressor;

//
// Template name: zlib_decompressor
// Description: Model of InputFilter and OutputFilter implementing
//      decompression using zlib.
//
template<typename Alloc = std::allocator<char> >
struct basic_zlib_decompressor 
    : symmetric_filter<detail::zlib_decompressor_impl<Alloc>, Alloc> 
{
private:
    typedef detail::zlib_decompressor_impl<Alloc>       impl_type;
    typedef symmetric_filter<impl_type, Alloc>  base_type;
public:
    typedef typename base_type::char_type               char_type;
    typedef typename base_type::category                category;
    basic_zlib_decompressor( int window_bits = zlib::default_window_bits,
                             std::streamsize buffer_size = default_device_buffer_size );
    basic_zlib_decompressor( const zlib_params& p,
                             std::streamsize buffer_size = default_device_buffer_size );
    zlib::ulong crc() { return this->filter().crc(); }
    int total_out() {  return this->filter().total_out(); }
    bool eof() { return this->filter().eof(); }
};
BOOST_IOSTREAMS_PIPABLE(basic_zlib_decompressor, 1)

typedef basic_zlib_decompressor<> zlib_decompressor;

//----------------------------------------------------------------------------//

//------------------Implementation of zlib_allocator--------------------------//

namespace detail {

template<typename Alloc, typename Base>
void* zlib_allocator<Alloc, Base>::allocate
    (void* self, zlib::uint items, zlib::uint size)
{ 
    size_type len = items * size;
    char* ptr = 
        static_cast<allocator_type*>(self)->allocate
            (len + sizeof(size_type)
            #if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1)
                , (char*)0
            #endif
            );
    *reinterpret_cast<size_type*>(ptr) = len;
    return ptr + sizeof(size_type);
}

template<typename Alloc, typename Base>
void zlib_allocator<Alloc, Base>::deallocate(void* self, void* address)
{ 
    char* ptr = reinterpret_cast<char*>(address) - sizeof(size_type);
    size_type len = *reinterpret_cast<size_type*>(ptr) + sizeof(size_type);
    static_cast<allocator_type*>(self)->deallocate(ptr, len); 
}

//------------------Implementation of zlib_compressor_impl--------------------//

template<typename Alloc>
zlib_compressor_impl<Alloc>::zlib_compressor_impl(const zlib_params& p)
{ init(p, true, static_cast<zlib_allocator<Alloc>&>(*this)); }

template<typename Alloc>
zlib_compressor_impl<Alloc>::~zlib_compressor_impl()
{ reset(true, false); }

template<typename Alloc>
bool zlib_compressor_impl<Alloc>::filter
    ( const char*& src_begin, const char* src_end,
      char*& dest_begin, char* dest_end, bool flush )
{
    before(src_begin, src_end, dest_begin, dest_end);
    int result = xdeflate(flush ? zlib::finish : zlib::no_flush);
    after(src_begin, dest_begin, true);
    zlib_error::check BOOST_PREVENT_MACRO_SUBSTITUTION(result);
    return result != zlib::stream_end;
}

template<typename Alloc>
void zlib_compressor_impl<Alloc>::close() { reset(true, true); }

//------------------Implementation of zlib_decompressor_impl------------------//

template<typename Alloc>
zlib_decompressor_impl<Alloc>::zlib_decompressor_impl(const zlib_params& p)
  : eof_(false)
{ init(p, false, static_cast<zlib_allocator<Alloc>&>(*this)); }

template<typename Alloc>
zlib_decompressor_impl<Alloc>::~zlib_decompressor_impl()
{ reset(false, false); }

template<typename Alloc>
zlib_decompressor_impl<Alloc>::zlib_decompressor_impl(int window_bits)
{ 
    zlib_params p;
    p.window_bits = window_bits;
    init(p, false, static_cast<zlib_allocator<Alloc>&>(*this)); 
}

template<typename Alloc>
bool zlib_decompressor_impl<Alloc>::filter
    ( const char*& src_begin, const char* src_end,
      char*& dest_begin, char* dest_end, bool /* flush */ )
{
    before(src_begin, src_end, dest_begin, dest_end);
    int result = xinflate(zlib::sync_flush);
    after(src_begin, dest_begin, false);
    zlib_error::check BOOST_PREVENT_MACRO_SUBSTITUTION(result);
    return !(eof_ = result == zlib::stream_end);
}

template<typename Alloc>
void zlib_decompressor_impl<Alloc>::close() {
    eof_ = false;
    reset(false, true);
}

} // End namespace detail.

//------------------Implementation of zlib_decompressor-----------------------//

template<typename Alloc>
basic_zlib_compressor<Alloc>::basic_zlib_compressor
    (const zlib_params& p, std::streamsize buffer_size) 
    : base_type(buffer_size, p) { }

//------------------Implementation of zlib_decompressor-----------------------//

template<typename Alloc>
basic_zlib_decompressor<Alloc>::basic_zlib_decompressor
    (int window_bits, std::streamsize buffer_size) 
    : base_type(buffer_size, window_bits) { }

template<typename Alloc>
basic_zlib_decompressor<Alloc>::basic_zlib_decompressor
    (const zlib_params& p, std::streamsize buffer_size) 
    : base_type(buffer_size, p) { }

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#include <boost/config/abi_suffix.hpp> // Pops abi_suffix.hpp pragmas.
#ifdef BOOST_MSVC
# pragma warning(pop)
#endif

#endif // #ifndef BOOST_IOSTREAMS_ZLIB_HPP_INCLUDED

/* zlib.hpp
Q4dZ8TQnruaHOx98Cll0MCjiRIxcPmP/NszxLX0/SBv3aJKYul/gvTnE2ug89PP8cw1MrQ8K6srKClnZ9wanZENIWTgd9rKU3hJSmEG2Sr9LhzKS5ht3KYa7WEau/0SssqLYqG9hgbAO9hAvpmE6ymm8PmxbX6dVYlde7wPVWZuOziOvcMhxdXVbYauO+1/+EZLj15GNCZ2ehZGdL+KO1YoOnJbwidfd0HMcWLXi4rkNpkT8xW9HmvRHGj1dzoq5fHFj2LByzJWQG/D6i1VVJPmdkrgfx5jfoxXN2pf3h3S64q3o46cF5HWs7GoFXlaUnxj0e7QI0Wd/043UnuhE6fUHp2nBpd9H8SygroUclybm8e04xBBBg8JOU2ZFQCfywwdav3ru4Qu6tBgXXaEyPC58WeTEoNqAGmeHwf1+thMzJXL1z+xSnOgw4NNuLvKB9YTfeYGFe8+dMICCQbaK56Cwk8zx95C02ypc+dkKJJDVRHlPx0QQ5Ha6y2z8quY++riTisSYeLt9DWrvlhCwhTto784nJ5aTWHPm2hZe4mciYrDfClaKmFIAGSI5kYfxyDA7114berUs43r5fx6QTjWtrwlK54mYTXeeffyh8owJcpNpwy7f/pdP//azIc/+oZJ3DSdL3+OLbntq7Um+jOdwSSK2aOYhfbVoSfHwDuJ4ajeMJ1cMN3q5okC8xSGJeu9QJjzvmJuTj445m7TVxrM4GTHz99cGeb+LtIGGsykbjiRtEMeC26WYNYvjA15/fY1BN0vf1eY9jkXCqNSSm12M64/1D3uNU8ih/tMv0nJr1uMJ9w5njCke8LUp/y1NGJNHrs16fWmcrhBDPZNkaQeNwPCLdWKctLvkX1vfv5whmJgVEZp8psfVUerOmpnwv0nhHpvSIQf5xADnCvxhVnMMhYWXy6GkZukD6UPisJwzv0FlJlCUMLj79sRwUKiDRXGTNs91ZLxlsCEIlsQ6SZv9J6ZpzSh6hN1K3iLSxC/ec6PqXqeVM4jkJBUHdnMMJnKt4zZ4X/xJbzCvCv8WrQvSC/qYYDnwkXY9JO3Q3t2MQUJAfUQuWZMB9l9yK7Yet5W8GQ5pRwtHkukHqeKaygu/I+gq0Z9m72SYtUCLrZoWGzGhuLqreFrk8CGfLv0UPiL8gMdbJWfG31LapQRNiazA3Mix+Mp+IYZvFcvTVPbZym3JsAhOdHWd5Go87llNz4/9xeVdvil00etJX/BZpeArhEUz4djJImBnys8gTLUgFZI2U3VEvvQixuX7cRE4vycO2+wuKVe26/rZ9/jfC5u8gPcRvhJSb0bS5r7554vI9/1EoW08SbDCuj0foRQ9qcSdbhnuy0r96cF5Cw5cpGXvfaRNudwzrrs3I8vs/e+sqorVispWdVjuy3OjyL376S1GMUj7s3miHz41KhbaCRE/JpFv3ryYuKkdZIHWnfrYt+9Nyi/cvyKC+19pkniO2OUOIDOdtIhP0lIcxkuLoit7JVvKqkfHvHrWw0Y5V9mWZ0pEhLX3344grJrIoSr1NhwY5ZCjwyYXIZMt6DV0rtE/rSok0pPmvofxru1guKEkv58L6jzt4xqni9NdYRQ7hocv7IFdRFlUvvM1mj6/8LwgdWQINpq/oAAJLPbTEPOBQpzb4kRspWjvwWn8QQFCLIdTcmmJ6mQhP6TxR8m7QY3XbF1bGuqA7x8JdjbJxKL5LjJNILkB0Ozl1iIRS+oT5Wpua6ka93/Y/iy8DqzkHvq9yvHdl5LuwC1E3NRr4fjR29ONMR1FjWTnz+KsiiKI9T75CAbG3jHBlCji4Mwojrj33HP+DR1Ox5N+2BLb4IIe4CqaqGLN1wNVhOhi6i35LAOPzcY0X/W+Tet1GNLSMEPS9jMpagdzGTTVu9B5ZHY/UWo1GzxMhHTBZqzWFLvZ4nYlFQkXNZaGRwopsQm1FeadbcHB6XIkVjWPn2Fnj1YqdIye2WXMGYTF5NOtsRInH3snpgeBGOPT6kujr5il6WQOtehkurbRNc4QBvItiAxariuvBPvDb57+yrMdTsZB/AtfJKztee99MWk853MaME8OGeQALS/NrsKHbnZCsv5iZ23HASS7IMRy+q7lwrswSdG0rjbqPMNDDvqU18feeGF79CVQj2SrnsEj6ZMXi24X6MHIkCIWGBdEfN3bSFjCXEHARzvzLEYz956Zxm0GZWiZj4U0n4HdS9dV3qWd+/1G32Vec28ReBtvaAj7QHtzChrXwBdXIKRB3B85N5l7TxZpmFeqE4/aybfSX7zlzyIoQ+eNTvgbVuMvnjbTouzRQZSs7rGq7Vq+QK1flg1L4gdufWl7cCVWBkSmZfqfjJdozOEQjg59kSUkm6hHRJwfZEV831ZFwmMi6vnjxfdA/d0qVMK5EcLJCaU/vhyeoTJPmNNIfByvSCVFUJAue007kGOOJqkqB6zgih3LXJe9B+IHpjmsGdDOYWt4d8CO6Bkh5CrDkE0sFKY+zENyytCPcoyUib12L9cpGzqIUlKd03XPaNySB8cLdBdaObITW3k8C1XY1tvK45iwx3X6mCgivehShKiKAznKyfULuPNwEfAp6HNFhCUPt6Kw2gNlzJSnxl0JfzJpkjIZAeECmpGhcVUTl3UtUi9q4hvTyPGQM0BRew28DtdOGr59X045P/3t+YC2hnBpC0P2HYTB9xN/GcuyV64oQFanSovKNwVlOZ25uYdoLr9fEFvgWXfJTWTw9/oxqzrwFPOeX6KRHu6ATks35OHQQ+hvIffXnfMUTnTaVfm9zbrBaXw+4NnzsfGY/M7/bEY6gzmnDkpdZ4+uznpmCWKV98utbWatYvAMmsjoPGi6fb+Ic1YdaGfUnMIUeDLL+X+q2KTGfzVITpIslEQiW6dIVqKIlaRbLqul9C7GS3kH4XrHlXiXp2M1dc2jPbbddD7g7njgVBw/8MQsKL4Mrvk7z5Aoy2rRSeJJlOBwEI7WKotPRoV3LWJ7z7Q/INf8PGCik5zjxq/4bc1PqwWpSbDKBCFm5xfVNJX4N9PPaO83EMl7fi70k98wnaX83wXjmZ0+ulyYsL1gddWy4xbYQCxfJEL5I4n3Hxm8ttohSDkSz8qmjVrJoWvi9CVg2yAthUJBLt6VaguRwr0w2uBTmWGWZFZC3KEzPnMg+6AiPjcIRStKW0yaxPDjtwJXH5Hig/epIJ4nxqxHWF5biAn0v7u2HfIdD074nEHRh93FEY5zF06sX08eV/NW5Uhhp347s1/FYYwAYNDxohBwIM19tx8I3hGLhz+wXBRRr/Tk6O0r4zexfIkBZ5c/5BKMVU0VOqO+ZV6YNmE6zuPCGvBjHg9sW+L6iX+m0XiJlZ1tt4feSIGagqlhdn/R1cSs+uh5rGxWfzGsDbYx1oj/aH92ydVFoWKsqJ2H8pW9wqFZbMp6L+TwNzTpdL7af4NL1j3LcT6J2TdLVts7lqSItH+TN6hnkZey8d+XmjZrCY+HyfsHHZSQI7B4KLizpHvO5/e2FMCG6ffG/bcG5mWKT2Olh98PbChornJwXp6428mkeX6Pu7l88/9B3zXYJI1YqmigvN5PeDVjaTFE3mfQb3ejnpky7e7sOlJJdacUGCVjMrbQO3pHNbdzKyW3xhpQz+I1YGN+uXLEqrGGyDF1mHfIgvPpBNtJI8NVqJ3HlFpAOkFS0Bh8FQf8n40zDjfSsrcj45Px5HPLO1eYQby72P1dGL4aT3PE19aFuAEVW7VLlPQf2+uTjL7AxweHwR/1JsBFUj8Gx7cP4ya7QKZScScleLg6wFne6iet153ZDTWsmaLyL9TJsHPV/25rXCtDNXgdvobN7Upds6GzAwMgfZ4LORlkEP4FUqyPe6Cv7AbzAw+9KnqbBvtC/6vyI+6oivDieB8OLk926jWwz53JKquhBwOoZd63XWflNlOPzJ70+CqK72O10TUZxWwWltZco1ReOPPkLNXzA22m4++QpuqGXMKTfGjfmwZmtBzWTIpyA49TWzpKYcBXyGLHGzcggZjmXxIWa8bx8ZzYT+FsSDwLq2MEPWuCSLM8VgmRxyg/iGo321q35dgApxiXeXGqVRVmzOiJviWj1jbCi49HWhAZw7N0rzdu7pV1Jpf1RGp256fs5cYgzs1L38V5WgGbh8y0cXeb2wY/qjLTEyG11XIcYEq8Q8lRscAGDzGuRYYdEVqyueMGRo1yhJRj6VM2VrKrznYSspmqarkZ91RuhTNGeNueu5Dztr5yK2bdnM7OXcRQYWaXParS4VZofimNJ9PwCq8xqdIKWCoR5aLnQxfwibbq5I7I0vhdzigH7fIh93jBCFE0wZ8yA/r9s8JjjkF8A45xYCbJtPUU8NMQP5+TeW+Vuso7jNilhaXsFgb1xp+ytIk9r2Fqk5saJp589H6Id0R8xVtjgVeyIVqEZtcQ1HvWVWBMsqrbKyKjLd9YJxItUKrUP6KlmMG4QmH6LHYj06ds5H94iCXZ2Z6DR31mnQLgxyp0jfcUxu7K+SQDrKr+fttlJxN5H5qKGBsEU1us7Rwi8Q/G++JlOgKuXTrT6YV+cjwNGYc0RR9jDkV4H4LaC/nWQHsI6gj7ITOSRneoWTXtLA7m6M2NEIINWuhLMyLtc9Ymi2PgjqhV9Tc5wyrdY3N1Zav71Rik1CiDgyMQUi0WdovVa/jgu6D9CD5Moy1g8zKJs+5e1jlHXczbrqyIoHWVQ33Q401DtTb2WOVrMRR30MUzl2L48VI9JvjlbGnMQ+GDkc/Du+O0UuWObfmY65EORB7FXnTon+YOcdsPdxzdO1d6jPCQi9axb7db4SgrXbcP3R78iNXPj+CaLXiHNesfLB49XeVZ/KrGcUgzhBrq8iKHwv4dSpfmcYsYg0tF2nJvQjcr6XxpzoTMJcpn8KP+FiSJ2x2yqoWTio/AwfBOEaS17X3RtwJcQ2GCk3vOIQFmnvL/3nd0uxtPOVAAQgLFMwwI9/SHlDa9lmRTmXdJ09sijuKvNcWjHG/e/3AOd5CAW/GUqBij2txU2FPOJHB98OWyWe8ynLzIq7t0S5E4uCgSv22ROSM94nXIt3gjudgcDKjXeQTZRvqlffIBqo3hR+OAtT++9N778v26QPaLw/UXASdqamkvw4W/QlZX/ddXARSjlDgVM2rP6Dmh0kQXf/GG8Hh522RqoWjf17y1Pd7lIpCdLmAj8Vw3bnD65Yn7qG9WbYq9qNF2W8KOUoIO1x9FslEIGRehgizeEZjSn/oWtC+79q5MPXtg8T52D3nte+bOR+eqgPA+qcEayvDeRNVj6z9de48O4kvUG72JbfO/g61E6zooxM18tF1V6+t2JdzdWtPn9SMiPyWsd2b+X4d0E5MIdyfyCotblzIY38E0Yh8YlNvIEHXr/N5SI0YvSltntM0dGdgjTjvNoZXpRNxEvM0Wt+/W9gkWtdGfXiSigfbz6vhYb8Z1yHwH5m2eKWV/4J8In34ZsQzbVEfIR2Wn9E3dM6JFipryA0GWUvrp/lfghgNri6NErVcMnHexlOZJTKLdm7TxOahYtij08I974AhS0CFe/HkzUYz2adIt9alOvb1XYol4uO2O4XMRNf7YUa9zeZ7/Bf8SCL/Te4dais9EWZLYRveoUQxSPwEdna1ZE4JH51EZQIo/Xj1NPjeFw6OfcxQ4ifnOX294mS3aXlCBCUc9lpYVJNE5qL/v1xxAb10tP4MVw8VnosmgVZAeO7LlAsdLRIbetUqwROGYYIOZ/IbljNnix5Ea4KFU9Uii8ZEIWxJ1VfeaF6KDHvBxonP5dQsOv1K1Rp5yUKLBm0eRj/ppZsm+AzhomyMsylimBh+xAV8z560hiKWJROdIznsM4tpshqWEKJ9/ucd4A74+c/3oDLkXgxbN2WNotOxHwm3whaOxUgb16cMpX9861jd49ubQRx1SuMgxs6qq25cguwLXnoCMYfjoxcWvaBFnSQjODV5rT+beios6i6HdEr9DfOud4iWf7n2InYRzgyIdfbLkgSJrC/Kg7FT8jTKB85Okwp29xx+vnMLSIoSnybH+DTQsZ/s1zfP/3ddDyuBH6Q+oNJRMH3GD2BlEfvFEseW2HfUYDss/+UJTsUkowBbjAiYxYKhyoq7x1/JGz69s0+GQrqwVnp6NXrCMb8Ja+y8ZW3IaKN1s/QcxOAxfsekcTun63S/s7L2P6K+GyK7/8u98nJJnAEYZj6iBlUvqweWC/tMwcuDPqh6k2aI7s/Xtwb/HBbqXXKqK7WqN+a3PPx5qRiCt8XzaW/nZPop+vkLux1NCKKzkgNEXZYc3fVNOTkkGtAWQArvbhcECLtKaGoukx11FLJ7hbEoBZBKKBUA2thTFCgzVkwQrSOdGzk858N5Dop/HW50v10+v3y77b9WDKrYePXVzNai34bEFjh9HlL6BwSmi84yYiLZ//VUSYIZtUcA1oNINpvQWt38ATfuQab038nd/INbRx+2bpMqKrNcp0Zn5p60ua4A21mmxgpsTzsM8NfzdN6a9MUvGOUvtSANfQBLjGEDq2YFWOpL5Ongkvo47cg5fwwbj5krCuUypewaLSIiUSlsRmnT4hjMoL2Hyxy20bGk+8fnS5xp7WuNCjKIlfUJxHSUxZ4Bf/tgM7/eVVAu0ZtspqseOQXn42GN/u9oNICTwHPz/qUWxgrdDsk7ThKIWWS5VYYFNufrmbJsI5/ft0petGbUac1qzUaL0NdhM9RFgX12MDu9zGkfEab9Vp/xIheUxaAQWrpLosUXKYfjeH3iYW9UpEeYF67RzSYxSvRxMXa/zBKS+K8QI1XqEJuv7B6NmGTPk2z1Euk185uQruAlth3sjxnNHZdviCk2SH1KqZj5fjnEzZRSYARppGGGheQwrR/y1ojGF1GSzZbkKPETUWeMoTilK4cq92vxePd3qXV2tywbcZ6oP3yGWlwJ72pG8qTLvyrvFjo906hGneHEiSLo3NvmJxpzHWKRJ2SvKwcTT7HXAu2WmnZRw6CThcPylj9oFyodD/Lg1Cza4cY3Bvi88DvmBx3O6p8KzGzCasKTxpWkkMtoAlU45nvgdwOdu+0jkUXr2al9ID6/lNohr0vCl8L0nBJ3k+yuYe9l8+d9FcrMq6s6+7x5sMNvrF14/5kOf6jrukYeFvlgBLiXdYiQ96Opf+bBpR8TUBf2fzTIlZlyWa7BxvFjWhsq74TjiwjlK9Bxlrl72TCDfZumOKhI2jlQfIRCitTYznNbcR6fQZbvY97Lqw5kXtif+f4z7cbsh3ohxyyzeXDwh6C21/f2zhR3/Ms9p/xgJpyKIYDW/d+lkEmBDHvTvRaROe2EYF9hrwMjlefTncUBbDwVob6rR2hZYxAXAxusVhSOixGB9gZJoSPMotqfOZJ4eKyGcci1DkeSyepaxEuVlhTneE2OW2MWpCmhZ2qDQaA+YfFXgP41Ne2HdPsv7NcRy6wqec+kZShhk80iuqfn/IX4MiEfwu5Ervy36xaxxtM/FsfKcY6SvZqS4J3yy8D6RnxFXvp2s+bf3qGfw/TO7bq5IeLp47+w3YQ7xwRPFGsgRzylx1m1xI5SW2AmQczrO/FNnlcipyiZ45cXyju3jlX/8PHgVMO9Fy1tpuqL05Of+nuanVaU3I/u+WTWfp5Ua1oa/N/V2s8uqaTetK14ZgeG8fU14mTBG1CVfpemcBVcyP+vtS9DSoLygf/HCJT8dh89R6Ll8uFrb4kiDd8Dvu2m6DGngpHnmcTfcOhyoflSwkkNNFu425v0eYGuwr+0vpeGfO3clOH3p6qgNF6RtQAhZ25h1rza/ZMvPOCbwwPU1q+ybcN2Q3Y+tiyDO8JkVuutZFVTg7pEsBfn2Cu784xBWmNyx5MUJR8RWtY12O+RBjdqtXDUYo42RT8J22/l7mUilOE6PzHDmnBrUFltYt2yvvWr7881wf/uFe70coJuP3Jt5JfJSfWirVtUvCZMnDjGWNw/15ekafhjat80T5KzsJIoRv+1tUW/TX2CGowTRWr1VMNZVK846/u5HOzJFU5hUKWbQQmCi+pPvsykvr7YtO0l3HUtUmmi9FJzPc3c/Pq5BZpSCOFwEvjCqSMDrUNlDIUWAbLNIzOWILgVfSB8P7IidnHTK/IywrEffhVtyZYyVT4XIHLgjMr/trZXWA4SW+A97JCMUtfdMu4JWbW15MilHS3/ZIU/UMGmdeAtqUj+yXlfchItvpAfzfZ8hY/soj9VAkVhxRgW8AweKn25XSLgnP3C72dL0jrOUILK82B6FrcA2nL0CuZ0qhd9HoVHAPHyAfhuE4/nTIvHuJW7E5az9LjqUVZKNg04JLuYncldBuqFge4GZJP05iAy57WKqpZJCNyKllvVcm2GzG3Qk6vlCiA2+5vRUPY1HVIjm6XNX4UJuXiWUE5Z+NMfaeFcCYnEvUVtnNP6o6QqWZWoaISlvVejqkpLvv9wTRB9nHSaoLDaXyD7RapH4YhLBp2NGEqC/gjntAmE4qAomijp/jjrAIbk1EwS58Wy3mt+Q2cLGmAzhvi0S2zl4rsmuYZp7ntI7EjOfpU8f2OCwHT1hurU8SqUrEndsntR3Voilh+tcm12CqMWHtsUWvSSxI83bd1uSQfA8yho+kym8PKo8aXxd5L5nmeyb4kkV704fhjUti1Qo1uCOVOZGvUy3d24DqfXBhD3hwpf7YnYLTz2Yb/ibXvMYuR7GgnWwJM6ho7Lik3bD+OoevX+eWnH/2b60tETtiuYe5nSMHLcA/nKtjy/RZlVx7XddPvTibfHqAmZJNnSvO75+7puZDF3AcMdrYOZuNufIbtFZaeBXiptQCUpNA0go2IwYBg+CUm86txxoNkmDhkoeD5Y3gWl44/3zqxuJa9qQBlA80dX1kNtmbxWn5xBn98aDqyEu9oc3hUmR9D1/ivJ2HRhZ84+frE84sbbaCvUTwawOyQXd/lI7bzdm9uzGfQGgBClXBA9aiYqhYQ6ytdepzNtI7693R9kCk4ooDA8ODqCPOBERO39+KqV1JG14WtCMCrm1hAqPQ1mb2iBwcVcZwI0CoZd/2KfIgQu6jmrvkUcubBxaE3hrVCkyf/Wv2Y4M/3zsFGOlFhliXVJ2ChsH096omwRN2zJoNUKpasI/xO9TejVEnE+XtZSIwq16yrrfTRBp95uGnlzeYAVPdK4=
*/