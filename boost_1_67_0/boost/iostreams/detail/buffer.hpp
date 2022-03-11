// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_BUFFERS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_BUFFERS_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <algorithm>                           // swap.
#include <memory>                              // allocator.
#include <boost/config.hpp>                    // member templates.
#include <boost/iostreams/char_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>      // streamsize.
#include <boost/iostreams/read.hpp>
#include <boost/iostreams/traits.hpp>          // int_type_of.
#include <boost/iostreams/checked_operations.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace iostreams { namespace detail {

//----------------Buffers-----------------------------------------------------//

//
// Template name: buffer
// Description: Character buffer.
// Template parameters:
//     Ch - The character type.
//     Alloc - The Allocator type.
//
template< typename Ch,
          typename Alloc = std::allocator<Ch> >
class basic_buffer {
private:
#ifndef BOOST_NO_STD_ALLOCATOR
#if defined(BOOST_NO_CXX11_ALLOCATOR)
    typedef typename Alloc::template rebind<Ch>::other allocator_type;
#else
    typedef typename std::allocator_traits<Alloc>::template rebind_alloc<Ch> allocator_type;
    typedef std::allocator_traits<allocator_type> allocator_traits;
#endif
#else
    typedef std::allocator<Ch> allocator_type;
#endif
    static Ch* allocate(std::streamsize buffer_size);
public:
    basic_buffer();
    basic_buffer(std::streamsize buffer_size);
    ~basic_buffer();
    void resize(std::streamsize buffer_size);
    Ch* begin() const { return buf_; }
    Ch* end() const { return buf_ + size_; }
    Ch* data() const { return buf_; }
    std::streamsize size() const { return size_; }
    void swap(basic_buffer& rhs);
private:
    // Disallow copying and assignment.
    basic_buffer(const basic_buffer&);
    basic_buffer& operator=(const basic_buffer&);
    Ch*              buf_;
    std::streamsize  size_;
};

template<typename Ch, typename Alloc>
void swap(basic_buffer<Ch, Alloc>& lhs, basic_buffer<Ch, Alloc>& rhs)
{ lhs.swap(rhs); }

//
// Template name: buffer
// Description: Character buffer with two pointers accessible via ptr() and
//      eptr().
// Template parameters:
//     Ch - A character type.
//
template< typename Ch,
          typename Alloc = std::allocator<Ch> >
class buffer : public basic_buffer<Ch, Alloc> {
private:
    typedef basic_buffer<Ch, Alloc> base;
public:
    typedef iostreams::char_traits<Ch> traits_type;
    using base::resize; 
    using base::data; 
    using base::size;
    typedef Ch* const const_pointer;
    buffer(std::streamsize buffer_size);
    Ch* & ptr() { return ptr_; }
    const_pointer& ptr() const { return ptr_; }
    Ch* & eptr() { return eptr_; }
    const_pointer& eptr() const { return eptr_; }
    void set(std::streamsize ptr, std::streamsize end);
    void swap(buffer& rhs);

    // Returns an int_type as a status code.
    template<typename Source>
    typename int_type_of<Source>::type fill(Source& src) 
    {
        using namespace std;
        std::streamsize keep;
        if ((keep = static_cast<std::streamsize>(eptr_ - ptr_)) > 0)
            traits_type::move(
                this->data(),
                ptr_, 
                static_cast<size_t>(keep)
            );
        set(0, keep);
        std::streamsize result = 
            iostreams::read(src, this->data() + keep, this->size() - keep);
        if (result != -1)
            this->set(0, keep + result);
        return result == -1 ?
            traits_type::eof() :
                result == 0 ?
                    traits_type::would_block() :
                    traits_type::good();

    }

    // Returns true if one or more characters were written.
    template<typename Sink>
    bool flush(Sink& dest) 
    {
        using namespace std;
        std::streamsize amt = static_cast<std::streamsize>(eptr_ - ptr_);
        std::streamsize result = iostreams::write_if(dest, ptr_, amt);
        if (result < amt) {
            traits_type::move( this->data(), 
                               ptr_ + static_cast<size_t>(result), 
                               static_cast<size_t>(amt - result) );
        }
        this->set(0, amt - result);
        return result != 0;
    }
private:
    Ch *ptr_, *eptr_;
};

template<typename Ch, typename Alloc>
void swap(buffer<Ch, Alloc>& lhs, buffer<Ch, Alloc>& rhs)
{ lhs.swap(rhs); }

//--------------Implementation of basic_buffer--------------------------------//

template<typename Ch, typename Alloc>
basic_buffer<Ch, Alloc>::basic_buffer() : buf_(0), size_(0) { }

template<typename Ch, typename Alloc>
inline Ch* basic_buffer<Ch, Alloc>::allocate(std::streamsize buffer_size)
{
#if defined(BOOST_NO_CXX11_ALLOCATOR) || defined(BOOST_NO_STD_ALLOCATOR)
    return static_cast<Ch*>(allocator_type().allocate(
           static_cast<BOOST_DEDUCED_TYPENAME Alloc::size_type>(buffer_size), 0));
#else
    allocator_type alloc;
    return static_cast<Ch*>(allocator_traits::allocate(alloc,
           static_cast<BOOST_DEDUCED_TYPENAME allocator_traits::size_type>(buffer_size)));
#endif
}

template<typename Ch, typename Alloc>
basic_buffer<Ch, Alloc>::basic_buffer(std::streamsize buffer_size)
    : buf_(allocate(buffer_size)),
      size_(buffer_size) // Cast for SunPro 5.3.
    { }

template<typename Ch, typename Alloc>
inline basic_buffer<Ch, Alloc>::~basic_buffer()
{
    if (buf_) {
#if defined(BOOST_NO_CXX11_ALLOCATOR) || defined(BOOST_NO_STD_ALLOCATOR)
        allocator_type().deallocate(buf_,
            static_cast<BOOST_DEDUCED_TYPENAME Alloc::size_type>(size_));
#else
        allocator_type alloc;
        allocator_traits::deallocate(alloc, buf_,
            static_cast<BOOST_DEDUCED_TYPENAME allocator_traits::size_type>(size_));
#endif
    }
}

template<typename Ch, typename Alloc>
inline void basic_buffer<Ch, Alloc>::resize(std::streamsize buffer_size)
{
    if (size_ != buffer_size) {
        basic_buffer<Ch, Alloc> temp(buffer_size);
        std::swap(size_, temp.size_);
        std::swap(buf_, temp.buf_);
    }
}

template<typename Ch, typename Alloc>
void basic_buffer<Ch, Alloc>::swap(basic_buffer& rhs) 
{ 
    std::swap(buf_, rhs.buf_); 
    std::swap(size_, rhs.size_); 
}

//--------------Implementation of buffer--------------------------------------//

template<typename Ch, typename Alloc>
buffer<Ch, Alloc>::buffer(std::streamsize buffer_size)
    : basic_buffer<Ch, Alloc>(buffer_size), ptr_(data()), eptr_(data() + buffer_size) { }

template<typename Ch, typename Alloc>
inline void buffer<Ch, Alloc>::set(std::streamsize ptr, std::streamsize end)
{ 
    ptr_ = data() + ptr; 
    eptr_ = data() + end; 
}

template<typename Ch, typename Alloc>
inline void buffer<Ch, Alloc>::swap(buffer& rhs) 
{ 
    base::swap(rhs); 
    std::swap(ptr_, rhs.ptr_); 
    std::swap(eptr_, rhs.eptr_); 
}

//----------------------------------------------------------------------------//

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_BUFFERS_HPP_INCLUDED

/* buffer.hpp
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
*/