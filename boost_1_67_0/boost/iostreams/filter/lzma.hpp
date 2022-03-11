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