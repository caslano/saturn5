// (C) Copyright Reimar Döffinger 2018.
// Based on zstd.hpp by:
// (C) Copyright Milan Svoboda 2008.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_ZSTD_HPP_INCLUDED
#define BOOST_IOSTREAMS_ZSTD_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <cassert>
#include <iosfwd>            // streamsize.
#include <memory>            // allocator, bad_alloc.
#include <new>
#include <boost/config.hpp>  // MSVC, STATIC_CONSTANT, DEDUCED_TYPENAME, DINKUM.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/constants.hpp>   // buffer size.
#include <boost/iostreams/detail/config/auto_link.hpp>
#include <boost/iostreams/detail/config/dyn_link.hpp>
#include <boost/iostreams/detail/config/wide_streams.hpp>
#include <boost/iostreams/detail/ios.hpp>  // failure, streamsize.
#include <boost/iostreams/filter/symmetric.hpp>
#include <boost/iostreams/pipeline.hpp>
#include <boost/type_traits/is_same.hpp>

// Must come last.
#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable:4251 4231 4660)         // Dependencies not exported.
#endif
#include <boost/config/abi_prefix.hpp>

namespace boost { namespace iostreams {

namespace zstd {

typedef void* (*alloc_func)(void*, size_t, size_t);
typedef void (*free_func)(void*, void*);

                    // Compression levels

BOOST_IOSTREAMS_DECL extern const uint32_t best_speed;
BOOST_IOSTREAMS_DECL extern const uint32_t best_compression;
BOOST_IOSTREAMS_DECL extern const uint32_t default_compression;

                    // Status codes

BOOST_IOSTREAMS_DECL extern const int okay;
BOOST_IOSTREAMS_DECL extern const int stream_end;

                    // Flush codes

BOOST_IOSTREAMS_DECL extern const int finish;
BOOST_IOSTREAMS_DECL extern const int flush;
BOOST_IOSTREAMS_DECL extern const int run;

                    // Code for current OS

                    // Null pointer constant.

const int null                               = 0;

                    // Default values

} // End namespace zstd.

//
// Class name: zstd_params.
// Description: Encapsulates the parameters passed to zstddec_init
//      to customize compression and decompression.
//
struct zstd_params {

    // Non-explicit constructor.
    zstd_params( uint32_t level = zstd::default_compression )
        : level(level)
        { }
    uint32_t level;
};

//
// Class name: zstd_error.
// Description: Subclass of std::ios::failure thrown to indicate
//     zstd errors other than out-of-memory conditions.
//
class BOOST_IOSTREAMS_DECL zstd_error : public BOOST_IOSTREAMS_FAILURE {
public:
    explicit zstd_error(size_t error);
    int error() const { return error_; }
    static void check BOOST_PREVENT_MACRO_SUBSTITUTION(size_t error);
private:
    size_t error_;
};

namespace detail {

template<typename Alloc>
struct zstd_allocator_traits {
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
              BOOST_DEDUCED_TYPENAME zstd_allocator_traits<Alloc>::type >
struct zstd_allocator : private Base {
private:
#if defined(BOOST_NO_CXX11_ALLOCATOR) || defined(BOOST_NO_STD_ALLOCATOR)
    typedef typename Base::size_type size_type;
#else
    typedef typename std::allocator_traits<Base>::size_type size_type;
#endif
public:
    BOOST_STATIC_CONSTANT(bool, custom =
        (!is_same<std::allocator<char>, Base>::value));
    typedef typename zstd_allocator_traits<Alloc>::type allocator_type;
    static void* allocate(void* self, size_t items, size_t size);
    static void deallocate(void* self, void* address);
};

class BOOST_IOSTREAMS_DECL zstd_base {
public:
    typedef char char_type;
protected:
    zstd_base();
    ~zstd_base();
    template<typename Alloc>
    void init( const zstd_params& p,
               bool compress,
               zstd_allocator<Alloc>& zalloc )
        {
            bool custom = zstd_allocator<Alloc>::custom;
            do_init( p, compress,
                     custom ? zstd_allocator<Alloc>::allocate : 0,
                     custom ? zstd_allocator<Alloc>::deallocate : 0,
                     &zalloc );
        }
    void before( const char*& src_begin, const char* src_end,
                 char*& dest_begin, char* dest_end );
    void after( const char*& src_begin, char*& dest_begin,
                bool compress );
    int deflate(int action);
    int inflate(int action);
    void reset(bool compress, bool realloc);
private:
    void do_init( const zstd_params& p, bool compress,
                  zstd::alloc_func,
                  zstd::free_func,
                  void* derived );
    void*         cstream_;         // Actual type: ZSTD_CStream *
    void*         dstream_;         // Actual type: ZSTD_DStream *
    void*         in_;              // Actual type: ZSTD_inBuffer *
    void*         out_;             // Actual type: ZSTD_outBuffer *
    int eof_;
    uint32_t level;
};

//
// Template name: zstd_compressor_impl
// Description: Model of C-Style Filter implementing compression by
//      delegating to the zstd function deflate.
//
template<typename Alloc = std::allocator<char> >
class zstd_compressor_impl : public zstd_base, public zstd_allocator<Alloc> {
public:
    zstd_compressor_impl(const zstd_params& = zstd::default_compression);
    ~zstd_compressor_impl();
    bool filter( const char*& src_begin, const char* src_end,
                 char*& dest_begin, char* dest_end, bool flush );
    void close();
};

//
// Template name: zstd_compressor_impl
// Description: Model of C-Style Filte implementing decompression by
//      delegating to the zstd function inflate.
//
template<typename Alloc = std::allocator<char> >
class zstd_decompressor_impl : public zstd_base, public zstd_allocator<Alloc> {
public:
    zstd_decompressor_impl(const zstd_params&);
    zstd_decompressor_impl();
    ~zstd_decompressor_impl();
    bool filter( const char*& begin_in, const char* end_in,
                 char*& begin_out, char* end_out, bool flush );
    void close();
};

} // End namespace detail.

//
// Template name: zstd_compressor
// Description: Model of InputFilter and OutputFilter implementing
//      compression using zstd.
//
template<typename Alloc = std::allocator<char> >
struct basic_zstd_compressor
    : symmetric_filter<detail::zstd_compressor_impl<Alloc>, Alloc>
{
private:
    typedef detail::zstd_compressor_impl<Alloc> impl_type;
    typedef symmetric_filter<impl_type, Alloc>  base_type;
public:
    typedef typename base_type::char_type               char_type;
    typedef typename base_type::category                category;
    basic_zstd_compressor( const zstd_params& = zstd::default_compression,
                           std::streamsize buffer_size = default_device_buffer_size );
};
BOOST_IOSTREAMS_PIPABLE(basic_zstd_compressor, 1)

typedef basic_zstd_compressor<> zstd_compressor;

//
// Template name: zstd_decompressor
// Description: Model of InputFilter and OutputFilter implementing
//      decompression using zstd.
//
template<typename Alloc = std::allocator<char> >
struct basic_zstd_decompressor
    : symmetric_filter<detail::zstd_decompressor_impl<Alloc>, Alloc>
{
private:
    typedef detail::zstd_decompressor_impl<Alloc> impl_type;
    typedef symmetric_filter<impl_type, Alloc>    base_type;
public:
    typedef typename base_type::char_type               char_type;
    typedef typename base_type::category                category;
    basic_zstd_decompressor( std::streamsize buffer_size = default_device_buffer_size );
    basic_zstd_decompressor( const zstd_params& p,
                             std::streamsize buffer_size = default_device_buffer_size );
};
BOOST_IOSTREAMS_PIPABLE(basic_zstd_decompressor, 1)

typedef basic_zstd_decompressor<> zstd_decompressor;

//----------------------------------------------------------------------------//

//------------------Implementation of zstd_allocator--------------------------//

namespace detail {

template<typename Alloc, typename Base>
void* zstd_allocator<Alloc, Base>::allocate
    (void* self, size_t items, size_t size)
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
void zstd_allocator<Alloc, Base>::deallocate(void* self, void* address)
{
    char* ptr = reinterpret_cast<char*>(address) - sizeof(size_type);
    size_type len = *reinterpret_cast<size_type*>(ptr) + sizeof(size_type);
    static_cast<allocator_type*>(self)->deallocate(ptr, len);
}

//------------------Implementation of zstd_compressor_impl--------------------//

template<typename Alloc>
zstd_compressor_impl<Alloc>::zstd_compressor_impl(const zstd_params& p)
{ init(p, true, static_cast<zstd_allocator<Alloc>&>(*this)); }

template<typename Alloc>
zstd_compressor_impl<Alloc>::~zstd_compressor_impl()
{ reset(true, false); }

template<typename Alloc>
bool zstd_compressor_impl<Alloc>::filter
    ( const char*& src_begin, const char* src_end,
      char*& dest_begin, char* dest_end, bool flush )
{
    before(src_begin, src_end, dest_begin, dest_end);
    int result = deflate(flush ? zstd::finish : zstd::run);
    after(src_begin, dest_begin, true);
    return result != zstd::stream_end;
}

template<typename Alloc>
void zstd_compressor_impl<Alloc>::close() { reset(true, true); }

//------------------Implementation of zstd_decompressor_impl------------------//

template<typename Alloc>
zstd_decompressor_impl<Alloc>::zstd_decompressor_impl(const zstd_params& p)
{ init(p, false, static_cast<zstd_allocator<Alloc>&>(*this)); }

template<typename Alloc>
zstd_decompressor_impl<Alloc>::~zstd_decompressor_impl()
{ reset(false, false); }

template<typename Alloc>
zstd_decompressor_impl<Alloc>::zstd_decompressor_impl()
{
    zstd_params p;
    init(p, false, static_cast<zstd_allocator<Alloc>&>(*this));
}

template<typename Alloc>
bool zstd_decompressor_impl<Alloc>::filter
    ( const char*& src_begin, const char* src_end,
      char*& dest_begin, char* dest_end, bool flush )
{
    before(src_begin, src_end, dest_begin, dest_end);
    int result = inflate(flush ? zstd::finish : zstd::run);
    after(src_begin, dest_begin, false);
    return result != zstd::stream_end;
}

template<typename Alloc>
void zstd_decompressor_impl<Alloc>::close() { reset(false, true); }

} // End namespace detail.

//------------------Implementation of zstd_compressor-----------------------//

template<typename Alloc>
basic_zstd_compressor<Alloc>::basic_zstd_compressor
    (const zstd_params& p, std::streamsize buffer_size)
    : base_type(buffer_size, p) { }

//------------------Implementation of zstd_decompressor-----------------------//

template<typename Alloc>
basic_zstd_decompressor<Alloc>::basic_zstd_decompressor
    (std::streamsize buffer_size)
    : base_type(buffer_size) { }

template<typename Alloc>
basic_zstd_decompressor<Alloc>::basic_zstd_decompressor
    (const zstd_params& p, std::streamsize buffer_size)
    : base_type(buffer_size, p) { }

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#include <boost/config/abi_suffix.hpp> // Pops abi_suffix.hpp pragmas.
#ifdef BOOST_MSVC
# pragma warning(pop)
#endif

#endif // #ifndef BOOST_IOSTREAMS_ZSTD_HPP_INCLUDED

/* zstd.hpp
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
*/