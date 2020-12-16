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
XM+xyXpyeVm7rMc4H2yXtelRv7LN2q2AvCHjyQt2WulgEY50OfZa1xaUtdk6nvPFuG/k78PQsd3qv5q84NYCmmy4jri68nZcV+P3DeQwott0TVhBOuz44DG46ghpwz3ddoeF8KTt9zrfT7L1umNFxfZeN3LNgyvKt/uaurLU9utQ/o5/lHuFMl/E3xuQZNy3Q5M92P0rxSbsUX+l7cJGriJP+N/H7xb8vZH8R6ahG7iN4LdjL3aVZjO2yP4N34Am27HJ15AOmAp34TYa5iMH07g+1O3JFvF7PXwHWhdSlnAHv1OuJT387g91G7N5/NbtzG7k92Haxsj2YVZTpA+SgRQg9yE7kP2I1QEbs0hPZDySj6xFtiHvICeQ5I5hVjdkNJKHrEa2IG8gJ5DkTmFWJ2Q0kocUIkWdqu3TVh/VR/VRfVQf1Uf1UX1UH9VH9VF9VB//P8e/2v7/9NzMrIzxc7BHk5OdaX8A4Bew/39E2f+X7/PKN+hXIC2R2UgxA8aFf1Drps8fPGLAsP7tu6Ti7Ow9wT3D3Vf1hPI30oo123iWeDwq7Dw1lZNt/k4v/vQ9F54gOyL3q/NxxjXR+jVy1ZriycrfOm1/y9/J81HkK+Rh2XeRYV473K+WyuuZaj9FIvE6e4VK9q9kuHuFyA+/s921w2rvhaQbP+r6pAe3ycoGgz+JOTsG3X1WlrsuONJT9XXBNzxnu9/x2Liw2z/6665h1oNnZYxKe67q6y7N62FDr881r/cMtd626utJ1RoEpz5FJ1MRfQ1CvMytJMGesAEcApPhOHgKzIT14Gw5Pw3a8wCWfKfsCMLYuhovXyvfDGMMW41b95Rx4f5IOrJEvpH1cifGy+Ba7TtVGYg+Dniwekys+qg+qo/qo/qoPqqP6qP6qD7+p49f7/0/Y+rcPHsA4Oe//39dl7VW8v7fVN7/O8ta704wvxnryFYGvv9POGd69sRZlvH9vA70r7L9X2/e772y9P18TjO1R9/dM5+pzrXzmMYE9HDzVCqz3b30WepcE0+NUhsN7h7iGercqcoWTGMVbtYs9Q0l+YbRD+r8NeqbYt2Q0Uiu9n2x43URNU5QeVtWwe/+kXCOvPt7iVvKm71e7hpH0kBdInn4O7IqqLwHZyvjz1qZuXn/WvntbCpricdToe1pNaYRlMYzJY0bfWW/iXUZ/vpcE5TG0XMmZs+dkjMnKyCdhnRJWP6LLR1Dmpg30Wh/A7+B9gGOV8I+QFB+xA6CjNnItfR62CKv6m+KrZo3kPmETQ/O4wW5BM7U8+fabl6g/P6J9aw+s95rea4b7+R5ginPul8ZJ5NvRDg6rc4/Z40x2wsjfNl7pbbo+yp1rgfrTePdvfw7lVsmlpXau9/y+l65ebU4Sr/7dbk6F+fWnyVl6tgTy1Tn91rj+Ve7J93vkLyrzg+3IrjiaaSktrQbtyr3M61k0iY2fOT+q4y9MHOdU9ZS5xOUW4w7VqfKVJXg2aIH6xLEtk+S2PaBlzaD1yo9KGl/bT2YNCtn8swJKtKcOXwuT13f0QmxDSZ5XaHCjkky6ATxSj25OpFr0gf8BetD9rws6NTpFer8lKS+VnySSR8kvFaX/awpErbPDfa5ltgFjbIakKq27GT50FtgZfmWWsd9K62l/gKrVliBdXvYGn+nGldbT9cosIZFF1jvIpkxS60vYlZal9cssKJiC6w1SKO4AuuPSPf4ddb7LDpvJXVb60alE7VaWndE7o/Mj5gUH27lxLOOMn6W1YccD6d0suVestbZfm8Pn0PtLEB+oFRqYB/sap4MN8FEb7iVwgL4u+BG2MrHvYxh2EfhCyzKH+APt85nYfyrcJ/fb10cFm7NYIE=
*/