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