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
      #if BOOST_WORKAROUND(__BORLANDC__, < 0x600)
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
      #if BOOST_WORKAROUND(__BORLANDC__, < 0x600)
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