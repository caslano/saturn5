// (C) Copyright Milan Svoboda 2008.
// Originally developed under the fusecompress project.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Note: custom allocators are not supported on VC6, since that compiler
// had trouble finding the function lzma_base::do_init.

#ifndef BOOST_IOSTREAMS_LZMA_HPP_INCLUDED
#define BOOST_IOSTREAMS_LZMA_HPP_INCLUDED

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

namespace lzma {

typedef void* (*alloc_func)(void*, size_t, size_t);
typedef void (*free_func)(void*, void*);

                    // Compression levels

BOOST_IOSTREAMS_DECL extern const uint32_t no_compression;
BOOST_IOSTREAMS_DECL extern const uint32_t best_speed;
BOOST_IOSTREAMS_DECL extern const uint32_t best_compression;
BOOST_IOSTREAMS_DECL extern const uint32_t default_compression;

                    // Status codes

BOOST_IOSTREAMS_DECL extern const int okay;
BOOST_IOSTREAMS_DECL extern const int stream_end;
BOOST_IOSTREAMS_DECL extern const int unsupported_check;
BOOST_IOSTREAMS_DECL extern const int mem_error;
BOOST_IOSTREAMS_DECL extern const int options_error;
BOOST_IOSTREAMS_DECL extern const int data_error;
BOOST_IOSTREAMS_DECL extern const int buf_error;
BOOST_IOSTREAMS_DECL extern const int prog_error;

                    // Flush codes

BOOST_IOSTREAMS_DECL extern const int finish;
BOOST_IOSTREAMS_DECL extern const int full_flush;
BOOST_IOSTREAMS_DECL extern const int sync_flush;
BOOST_IOSTREAMS_DECL extern const int run;

                    // Code for current OS

                    // Null pointer constant.

const int null                               = 0;

                    // Default values

} // End namespace lzma.

//
// Class name: lzma_params.
// Description: Encapsulates the parameters passed to lzmadec_init
//      to customize compression and decompression.
//
struct lzma_params {

    // Non-explicit constructor.
    lzma_params( uint32_t level = lzma::default_compression, uint32_t threads = 1 )
        : level(level)
        , threads(threads)
        { }
    uint32_t level;
    uint32_t threads;
};

//
// Class name: lzma_error.
// Description: Subclass of std::ios::failure thrown to indicate
//     lzma errors other than out-of-memory conditions.
//
class BOOST_IOSTREAMS_DECL lzma_error : public BOOST_IOSTREAMS_FAILURE {
public:
    explicit lzma_error(int error);
    int error() const { return error_; }
    static void check BOOST_PREVENT_MACRO_SUBSTITUTION(int error);
private:
    int error_;
};

namespace detail {

template<typename Alloc>
struct lzma_allocator_traits {
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
              BOOST_DEDUCED_TYPENAME lzma_allocator_traits<Alloc>::type >
struct lzma_allocator : private Base {
private:
#if defined(BOOST_NO_CXX11_ALLOCATOR) || defined(BOOST_NO_STD_ALLOCATOR)
    typedef typename Base::size_type size_type;
#else
    typedef typename std::allocator_traits<Base>::size_type size_type;
#endif
public:
    BOOST_STATIC_CONSTANT(bool, custom =
        (!is_same<std::allocator<char>, Base>::value));
    typedef typename lzma_allocator_traits<Alloc>::type allocator_type;
    static void* allocate(void* self, size_t items, size_t size);
    static void deallocate(void* self, void* address);
};

class BOOST_IOSTREAMS_DECL lzma_base {
public:
    typedef char char_type;
protected:
    lzma_base();
    ~lzma_base();
    void* stream() { return stream_; }
    template<typename Alloc>
    void init( const lzma_params& p,
               bool compress,
               lzma_allocator<Alloc>& zalloc )
        {
            bool custom = lzma_allocator<Alloc>::custom;
            do_init( p, compress,
                     custom ? lzma_allocator<Alloc>::allocate : 0,
                     custom ? lzma_allocator<Alloc>::deallocate : 0,
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
    void do_init( const lzma_params& p, bool compress,
                  lzma::alloc_func,
                  lzma::free_func,
                  void* derived );
    void init_stream(bool compress);
    void*    stream_;         // Actual type: lzma_stream*.
    uint32_t level_;
    uint32_t threads_;
};

//
// Template name: lzma_compressor_impl
// Description: Model of C-Style Filter implementing compression by
//      delegating to the lzma function deflate.
//
template<typename Alloc = std::allocator<char> >
class lzma_compressor_impl : public lzma_base, public lzma_allocator<Alloc> {
public:
    lzma_compressor_impl(const lzma_params& = lzma_params());
    ~lzma_compressor_impl();
    bool filter( const char*& src_begin, const char* src_end,
                 char*& dest_begin, char* dest_end, bool flush );
    void close();
};

//
// Template name: lzma_compressor_impl
// Description: Model of C-Style Filte implementing decompression by
//      delegating to the lzma function inflate.
//
template<typename Alloc = std::allocator<char> >
class lzma_decompressor_impl : public lzma_base, public lzma_allocator<Alloc> {
public:
    lzma_decompressor_impl(const lzma_params&);
    lzma_decompressor_impl();
    ~lzma_decompressor_impl();
    bool filter( const char*& begin_in, const char* end_in,
                 char*& begin_out, char* end_out, bool flush );
    void close();
};

} // End namespace detail.

//
// Template name: lzma_compressor
// Description: Model of InputFilter and OutputFilter implementing
//      compression using lzma.
//
template<typename Alloc = std::allocator<char> >
struct basic_lzma_compressor
    : symmetric_filter<detail::lzma_compressor_impl<Alloc>, Alloc>
{
private:
    typedef detail::lzma_compressor_impl<Alloc> impl_type;
    typedef symmetric_filter<impl_type, Alloc>  base_type;
public:
    typedef typename base_type::char_type               char_type;
    typedef typename base_type::category                category;
    basic_lzma_compressor( const lzma_params& = lzma_params(),
                           std::streamsize buffer_size = default_device_buffer_size );
};
BOOST_IOSTREAMS_PIPABLE(basic_lzma_compressor, 1)

typedef basic_lzma_compressor<> lzma_compressor;

//
// Template name: lzma_decompressor
// Description: Model of InputFilter and OutputFilter implementing
//      decompression using lzma.
//
template<typename Alloc = std::allocator<char> >
struct basic_lzma_decompressor
    : symmetric_filter<detail::lzma_decompressor_impl<Alloc>, Alloc>
{
private:
    typedef detail::lzma_decompressor_impl<Alloc> impl_type;
    typedef symmetric_filter<impl_type, Alloc>    base_type;
public:
    typedef typename base_type::char_type               char_type;
    typedef typename base_type::category                category;
    basic_lzma_decompressor( std::streamsize buffer_size = default_device_buffer_size );
    basic_lzma_decompressor( const lzma_params& p,
                             std::streamsize buffer_size = default_device_buffer_size );
};
BOOST_IOSTREAMS_PIPABLE(basic_lzma_decompressor, 1)

typedef basic_lzma_decompressor<> lzma_decompressor;

//----------------------------------------------------------------------------//

//------------------Implementation of lzma_allocator--------------------------//

namespace detail {

template<typename Alloc, typename Base>
void* lzma_allocator<Alloc, Base>::allocate
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
void lzma_allocator<Alloc, Base>::deallocate(void* self, void* address)
{
    char* ptr = reinterpret_cast<char*>(address) - sizeof(size_type);
    size_type len = *reinterpret_cast<size_type*>(ptr) + sizeof(size_type);
    static_cast<allocator_type*>(self)->deallocate(ptr, len);
}

//------------------Implementation of lzma_compressor_impl--------------------//

template<typename Alloc>
lzma_compressor_impl<Alloc>::lzma_compressor_impl(const lzma_params& p)
{ init(p, true, static_cast<lzma_allocator<Alloc>&>(*this)); }

template<typename Alloc>
lzma_compressor_impl<Alloc>::~lzma_compressor_impl()
{ reset(true, false); }

template<typename Alloc>
bool lzma_compressor_impl<Alloc>::filter
    ( const char*& src_begin, const char* src_end,
      char*& dest_begin, char* dest_end, bool flush )
{
    before(src_begin, src_end, dest_begin, dest_end);
    int result = deflate(flush ? lzma::finish : lzma::run);
    after(src_begin, dest_begin, true);
    lzma_error::check BOOST_PREVENT_MACRO_SUBSTITUTION(result);
    return result != lzma::stream_end;
}

template<typename Alloc>
void lzma_compressor_impl<Alloc>::close() { reset(true, true); }

//------------------Implementation of lzma_decompressor_impl------------------//

template<typename Alloc>
lzma_decompressor_impl<Alloc>::lzma_decompressor_impl(const lzma_params& p)
{ init(p, false, static_cast<lzma_allocator<Alloc>&>(*this)); }

template<typename Alloc>
lzma_decompressor_impl<Alloc>::~lzma_decompressor_impl()
{ reset(false, false); }

template<typename Alloc>
lzma_decompressor_impl<Alloc>::lzma_decompressor_impl()
{
    lzma_params p;
    init(p, false, static_cast<lzma_allocator<Alloc>&>(*this));
}

template<typename Alloc>
bool lzma_decompressor_impl<Alloc>::filter
    ( const char*& src_begin, const char* src_end,
      char*& dest_begin, char* dest_end, bool flush )
{
    before(src_begin, src_end, dest_begin, dest_end);
    int result = inflate(flush ? lzma::finish : lzma::run);
    after(src_begin, dest_begin, false);
    lzma_error::check BOOST_PREVENT_MACRO_SUBSTITUTION(result);
    return result != lzma::stream_end;
}

template<typename Alloc>
void lzma_decompressor_impl<Alloc>::close() { reset(false, true); }

} // End namespace detail.

//------------------Implementation of lzma_compressor-----------------------//

template<typename Alloc>
basic_lzma_compressor<Alloc>::basic_lzma_compressor
    (const lzma_params& p, std::streamsize buffer_size)
    : base_type(buffer_size, p) { }

//------------------Implementation of lzma_decompressor-----------------------//

template<typename Alloc>
basic_lzma_decompressor<Alloc>::basic_lzma_decompressor
    (std::streamsize buffer_size)
    : base_type(buffer_size) { }

template<typename Alloc>
basic_lzma_decompressor<Alloc>::basic_lzma_decompressor
    (const lzma_params& p, std::streamsize buffer_size)
    : base_type(buffer_size, p) { }

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#include <boost/config/abi_suffix.hpp> // Pops abi_suffix.hpp pragmas.
#ifdef BOOST_MSVC
# pragma warning(pop)
#endif

#endif // #ifndef BOOST_IOSTREAMS_LZMA_HPP_INCLUDED

/* lzma.hpp
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
*/