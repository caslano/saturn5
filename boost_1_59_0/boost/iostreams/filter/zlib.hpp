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
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
*/