// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Note: custom allocators are not supported on VC6, since that compiler
// had trouble finding the function zlib_base::do_init.

#ifndef BOOST_IOSTREAMS_BZIP2_HPP_INCLUDED
#define BOOST_IOSTREAMS_BZIP2_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif
                   
#include <cassert>                            
#include <memory>            // allocator.
#include <new>               // bad_alloc.
#include <boost/config.hpp>  // MSVC, STATIC_CONSTANT, DEDUCED_TYPENAME, DINKUM.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/constants.hpp>   // buffer size.
#include <boost/iostreams/detail/config/auto_link.hpp>
#include <boost/iostreams/detail/config/bzip2.hpp>
#include <boost/iostreams/detail/config/dyn_link.hpp>
#include <boost/iostreams/detail/config/wide_streams.hpp>
#include <boost/iostreams/detail/ios.hpp>  // failure, streamsize.
#include <boost/iostreams/filter/symmetric.hpp>               
#include <boost/iostreams/pipeline.hpp>       
#include <boost/type_traits/is_same.hpp>     

// Must come last.
#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable:4251 4231 4660)
#endif
#include <boost/config/abi_prefix.hpp>           

// Temporary fix.
#undef small

namespace boost { namespace iostreams {

namespace bzip2 {

                    // Typedefs.

typedef void* (*alloc_func)(void*, int, int);
typedef void (*free_func)(void*, void*);

                    // Status codes

BOOST_IOSTREAMS_DECL extern const int ok;
BOOST_IOSTREAMS_DECL extern const int run_ok;
BOOST_IOSTREAMS_DECL extern const int flush_ok;
BOOST_IOSTREAMS_DECL extern const int finish_ok;
BOOST_IOSTREAMS_DECL extern const int stream_end;    
BOOST_IOSTREAMS_DECL extern const int sequence_error;
BOOST_IOSTREAMS_DECL extern const int param_error;
BOOST_IOSTREAMS_DECL extern const int mem_error;
BOOST_IOSTREAMS_DECL extern const int data_error;
BOOST_IOSTREAMS_DECL extern const int data_error_magic;
BOOST_IOSTREAMS_DECL extern const int io_error;
BOOST_IOSTREAMS_DECL extern const int unexpected_eof;
BOOST_IOSTREAMS_DECL extern const int outbuff_full;
BOOST_IOSTREAMS_DECL extern const int config_error;

                    // Action codes

BOOST_IOSTREAMS_DECL extern const int finish;
BOOST_IOSTREAMS_DECL extern const int run;

                    // Default values

const int default_block_size   = 9;
const int default_work_factor  = 30;
const bool default_small       = false;

} // End namespace bzip2. 

//
// Class name: bzip2_params.
// Description: Encapsulates the parameters passed to deflateInit2
//      to customize compression.
//
struct bzip2_params {

    // Non-explicit constructor for compression.
    bzip2_params( int block_size_  = bzip2::default_block_size,
                  int work_factor_ = bzip2::default_work_factor )
        : block_size(block_size_), work_factor(work_factor_)
        { }

    // Constructor for decompression.
    bzip2_params(bool small)
        : small(small), work_factor(0)
        { }

    union {
        int   block_size;    // For compression.
        bool  small;         // For decompression.
    };
    int       work_factor;
};

//
// Class name: bzip2_error.
// Description: Subclass of std::ios_base::failure thrown to indicate
//     bzip2 errors other than out-of-memory conditions.
//
class BOOST_IOSTREAMS_DECL bzip2_error : public BOOST_IOSTREAMS_FAILURE {
public:
    explicit bzip2_error(int error);
    int error() const { return error_; }
    static void check BOOST_PREVENT_MACRO_SUBSTITUTION(int error);
private:
    int error_;
};

namespace detail {

template<typename Alloc>
struct bzip2_allocator_traits {
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
              BOOST_DEDUCED_TYPENAME bzip2_allocator_traits<Alloc>::type >
struct bzip2_allocator : private Base {
private:
#if defined(BOOST_NO_CXX11_ALLOCATOR) || defined(BOOST_NO_STD_ALLOCATOR)
    typedef typename Base::size_type size_type;
#else
    typedef typename std::allocator_traits<Base>::size_type size_type;
#endif
public:
    BOOST_STATIC_CONSTANT(bool, custom = 
        (!is_same<std::allocator<char>, Base>::value));
    typedef typename bzip2_allocator_traits<Alloc>::type allocator_type;
    static void* allocate(void* self, int items, int size);
    static void deallocate(void* self, void* address);
};

class BOOST_IOSTREAMS_DECL bzip2_base  { 
public:
    typedef char char_type;
protected:
    bzip2_base(const bzip2_params& params);
    ~bzip2_base();
    bzip2_params& params() { return params_; }
    bool& ready() { return ready_; }
    template<typename Alloc> 
    void init( bool compress,
               bzip2_allocator<Alloc>& alloc )
        {
            bool custom = bzip2_allocator<Alloc>::custom;
            do_init( compress,
                     custom ? bzip2_allocator<Alloc>::allocate : 0,
                     custom ? bzip2_allocator<Alloc>::deallocate : 0,
                     custom ? &alloc : 0 );
        }
    void before( const char*& src_begin, const char* src_end,
                 char*& dest_begin, char* dest_end );
    void after(const char*& src_begin, char*& dest_begin);
    int check_end(const char* src_begin, const char* dest_begin);
    int compress(int action);
    int decompress();
    int end(bool compress, std::nothrow_t);
    void end(bool compress);
private:
    void do_init( bool compress, 
                  bzip2::alloc_func,
                  bzip2::free_func, 
                  void* derived );
    bzip2_params  params_;
    void*         stream_; // Actual type: bz_stream*.
    bool          ready_;
};

//
// Template name: bzip2_compressor_impl
// Description: Model of SymmetricFilter implementing compression by
//      delegating to the libbzip2 function BZ_bzCompress.
//
template<typename Alloc = std::allocator<char> >
class bzip2_compressor_impl 
    : public bzip2_base, 
      #if BOOST_WORKAROUND(BOOST_BORLANDC, < 0x600)
          public
      #endif
      bzip2_allocator<Alloc> 
{
public: 
    bzip2_compressor_impl(const bzip2_params&);
    ~bzip2_compressor_impl();
    bool filter( const char*& src_begin, const char* src_end,
                 char*& dest_begin, char* dest_end, bool flush );
    void close();
private:
    void init();
    bool eof_; // Guard to make sure filter() isn't called after it returns false.
};

//
// Template name: bzip2_compressor
// Description: Model of SymmetricFilter implementing decompression by
//      delegating to the libbzip2 function BZ_bzDecompress.
//
template<typename Alloc = std::allocator<char> >
class bzip2_decompressor_impl 
    : public bzip2_base, 
      #if BOOST_WORKAROUND(BOOST_BORLANDC, < 0x600)
          public
      #endif
      bzip2_allocator<Alloc> 
{ 
public:
    bzip2_decompressor_impl(bool small = bzip2::default_small);
    ~bzip2_decompressor_impl();
    bool filter( const char*& begin_in, const char* end_in,
                 char*& begin_out, char* end_out, bool flush );
    void close();
private:
    void init();
    bool eof_; // Guard to make sure filter() isn't called after it returns false.
};

} // End namespace detail.

//
// Template name: bzip2_compressor
// Description: Model of InputFilter and OutputFilter implementing
//      compression using libbzip2.
//
template<typename Alloc = std::allocator<char> >
struct basic_bzip2_compressor 
    : symmetric_filter<detail::bzip2_compressor_impl<Alloc>, Alloc> 
{
private:
    typedef detail::bzip2_compressor_impl<Alloc>        impl_type;
    typedef symmetric_filter<impl_type, Alloc>  base_type;
public:
    typedef typename base_type::char_type               char_type;
    typedef typename base_type::category                category;
    basic_bzip2_compressor( const bzip2_params& = bzip2::default_block_size, 
                            std::streamsize buffer_size =  default_device_buffer_size );
};
BOOST_IOSTREAMS_PIPABLE(basic_bzip2_compressor, 1)

typedef basic_bzip2_compressor<> bzip2_compressor;

//
// Template name: bzip2_decompressor
// Description: Model of InputFilter and OutputFilter implementing
//      decompression using libbzip2.
//
template<typename Alloc = std::allocator<char> >
struct basic_bzip2_decompressor 
    : symmetric_filter<detail::bzip2_decompressor_impl<Alloc>, Alloc> 
{
private:
    typedef detail::bzip2_decompressor_impl<Alloc>      impl_type;
    typedef symmetric_filter<impl_type, Alloc>  base_type;
public:
    typedef typename base_type::char_type               char_type;
    typedef typename base_type::category                category;
    basic_bzip2_decompressor( bool small = bzip2::default_small,
                              std::streamsize buffer_size = default_device_buffer_size );
};
BOOST_IOSTREAMS_PIPABLE(basic_bzip2_decompressor, 1)

typedef basic_bzip2_decompressor<> bzip2_decompressor;

//----------------------------------------------------------------------------//

//------------------Implementation of bzip2_allocator-------------------------//

namespace detail {

template<typename Alloc, typename Base>
void* bzip2_allocator<Alloc, Base>::allocate(void* self, int items, int size)
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
void bzip2_allocator<Alloc, Base>::deallocate(void* self, void* address)
{ 
    char* ptr = reinterpret_cast<char*>(address) - sizeof(size_type);
    size_type len = *reinterpret_cast<size_type*>(ptr) + sizeof(size_type);
    static_cast<allocator_type*>(self)->deallocate(ptr, len); 
}

//------------------Implementation of bzip2_compressor_impl-------------------//

template<typename Alloc>
bzip2_compressor_impl<Alloc>::bzip2_compressor_impl(const bzip2_params& p)
    : bzip2_base(p), eof_(false) { }

template<typename Alloc>
bzip2_compressor_impl<Alloc>::~bzip2_compressor_impl()
{ (void) bzip2_base::end(true, std::nothrow); }

template<typename Alloc>
bool bzip2_compressor_impl<Alloc>::filter
    ( const char*& src_begin, const char* src_end,
      char*& dest_begin, char* dest_end, bool flush )
{
    if (!ready()) init();
    if (eof_) return false;
    before(src_begin, src_end, dest_begin, dest_end);
    int result = compress(flush ? bzip2::finish : bzip2::run);
    after(src_begin, dest_begin);
    bzip2_error::check BOOST_PREVENT_MACRO_SUBSTITUTION(result);
    return !(eof_ = result == bzip2::stream_end);
}

template<typename Alloc>
void bzip2_compressor_impl<Alloc>::close() 
{ 
    try {
        end(true);
    } catch (...) { 
        eof_ = false; 
        throw;
    }
    eof_ = false;
}

template<typename Alloc>
inline void bzip2_compressor_impl<Alloc>::init() 
{ bzip2_base::init(true, static_cast<bzip2_allocator<Alloc>&>(*this)); }

//------------------Implementation of bzip2_decompressor_impl-----------------//

template<typename Alloc>
bzip2_decompressor_impl<Alloc>::bzip2_decompressor_impl(bool small)
    : bzip2_base(bzip2_params(small)), eof_(false) { }

template<typename Alloc>
bzip2_decompressor_impl<Alloc>::~bzip2_decompressor_impl()
{ (void) bzip2_base::end(false, std::nothrow); }

template<typename Alloc>
bool bzip2_decompressor_impl<Alloc>::filter
    ( const char*& src_begin, const char* src_end,
      char*& dest_begin, char* dest_end, bool flush )
{
    do {
        if (eof_) {
            // reset the stream if there are more characters
            if(src_begin == src_end)
                return false;
            else
                close();
        }
        if (!ready()) 
            init();
        before(src_begin, src_end, dest_begin, dest_end);
        int result = decompress();
        if(result == bzip2::ok && flush)
            result = check_end(src_begin, dest_begin);
        after(src_begin, dest_begin);
        bzip2_error::check BOOST_PREVENT_MACRO_SUBSTITUTION(result);
        eof_ = result == bzip2::stream_end;
    } while (eof_ && src_begin != src_end && dest_begin != dest_end);
    return true; 
}

template<typename Alloc>
void bzip2_decompressor_impl<Alloc>::close() 
{ 
    try {
        end(false);
    } catch (...) { 
        eof_ = false; 
        throw;
    }
    eof_ = false;
}

template<typename Alloc>
inline void bzip2_decompressor_impl<Alloc>::init()
{ bzip2_base::init(false, static_cast<bzip2_allocator<Alloc>&>(*this)); }
} // End namespace detail.

//------------------Implementation of bzip2_decompressor----------------------//

template<typename Alloc>
basic_bzip2_compressor<Alloc>::basic_bzip2_compressor
        (const bzip2_params& p, std::streamsize buffer_size) 
    : base_type(buffer_size, p) 
    { }

//------------------Implementation of bzip2_decompressor----------------------//

template<typename Alloc>
basic_bzip2_decompressor<Alloc>::basic_bzip2_decompressor
        (bool small, std::streamsize buffer_size) 
    : base_type(buffer_size, small)
    { }

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#include <boost/config/abi_suffix.hpp> // Pops abi_suffix.hpp pragmas.
#ifdef BOOST_MSVC
# pragma warning(pop)
#endif

#endif // #ifndef BOOST_IOSTREAMS_BZIP2_HPP_INCLUDED

/* bzip2.hpp
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
*/