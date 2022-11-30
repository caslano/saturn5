/*
Copyright 2014-2016 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGNED_ALLOCATOR_ADAPTOR_HPP
#define BOOST_ALIGN_ALIGNED_ALLOCATOR_ADAPTOR_HPP

#include <boost/align/detail/is_alignment_constant.hpp>
#include <boost/align/detail/max_align.hpp>
#include <boost/align/detail/max_size.hpp>
#include <boost/align/align.hpp>
#include <boost/align/aligned_allocator_adaptor_forward.hpp>
#include <boost/align/alignment_of.hpp>
#include <boost/core/pointer_traits.hpp>
#include <boost/static_assert.hpp>
#include <new>

#if !defined(BOOST_NO_CXX11_ALLOCATOR)
#include <memory>
#endif

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

namespace boost {
namespace alignment {

template<class Allocator, std::size_t Alignment>
class aligned_allocator_adaptor
    : public Allocator {
    BOOST_STATIC_ASSERT(detail::is_alignment_constant<Alignment>::value);

#if !defined(BOOST_NO_CXX11_ALLOCATOR)
    typedef std::allocator_traits<Allocator> traits;
    typedef typename traits::template rebind_alloc<char> char_alloc;
    typedef typename traits::template rebind_traits<char> char_traits;
    typedef typename char_traits::pointer char_ptr;
#else
    typedef typename Allocator::template rebind<char>::other char_alloc;
    typedef typename char_alloc::pointer char_ptr;
#endif

public:
    typedef typename Allocator::value_type value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef void* void_pointer;
    typedef const void* const_void_pointer;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

private:
    template<class U>
    struct min_align {
        enum {
            value = detail::max_size<Alignment,
                detail::max_align<U, char_ptr>::value>::value
        };
    };

public:
    template<class U>
    struct rebind {
#if !defined(BOOST_NO_CXX11_ALLOCATOR)
        typedef aligned_allocator_adaptor<typename traits::template
            rebind_alloc<U>, Alignment> other;
#else
        typedef aligned_allocator_adaptor<typename Allocator::template
            rebind<U>::other, Alignment> other;
#endif
    };

    aligned_allocator_adaptor()
        : Allocator() { }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template<class A>
    explicit aligned_allocator_adaptor(A&& alloc) BOOST_NOEXCEPT
        : Allocator(std::forward<A>(alloc)) { }
#else
    template<class A>
    explicit aligned_allocator_adaptor(const A& alloc) BOOST_NOEXCEPT
        : Allocator(alloc) { }
#endif

    template<class U>
    aligned_allocator_adaptor(const aligned_allocator_adaptor<U,
        Alignment>& other) BOOST_NOEXCEPT
        : Allocator(other.base()) { }

    Allocator& base() BOOST_NOEXCEPT {
        return static_cast<Allocator&>(*this);
    }

    const Allocator& base() const BOOST_NOEXCEPT {
        return static_cast<const Allocator&>(*this);
    }

    pointer allocate(size_type size) {
        enum {
            m = min_align<value_type>::value
        };
        std::size_t s = size * sizeof(value_type);
        std::size_t n = s + m - 1;
        char_alloc a(base());
        char_ptr p = a.allocate(sizeof p + n);
        void* r = boost::to_address(p) + sizeof p;
        (void)boost::alignment::align(m, s, r, n);
        ::new(static_cast<void*>(static_cast<char_ptr*>(r) - 1)) char_ptr(p);
        return static_cast<pointer>(r);
    }

    pointer allocate(size_type size, const_void_pointer hint) {
        enum {
            m = min_align<value_type>::value
        };
        std::size_t s = size * sizeof(value_type);
        std::size_t n = s + m - 1;
        char_ptr h = char_ptr();
        if (hint) {
            h = *(static_cast<const char_ptr*>(hint) - 1);
        }
        char_alloc a(base());
#if !defined(BOOST_NO_CXX11_ALLOCATOR)
        char_ptr p = char_traits::allocate(a, sizeof p + n, h);
#else
        char_ptr p = a.allocate(sizeof p + n, h);
#endif
        void* r = boost::to_address(p) + sizeof p;
        (void)boost::alignment::align(m, s, r, n);
        ::new(static_cast<void*>(static_cast<char_ptr*>(r) - 1)) char_ptr(p);
        return static_cast<pointer>(r);
    }

    void deallocate(pointer ptr, size_type size) {
        enum {
            m = min_align<value_type>::value
        };
        char_ptr* p = reinterpret_cast<char_ptr*>(ptr) - 1;
        char_ptr r = *p;
        p->~char_ptr();
        char_alloc a(base());
        a.deallocate(r, sizeof r + size * sizeof(value_type) + m - 1);
    }
};

template<class A, class B, std::size_t Alignment>
inline bool
operator==(const aligned_allocator_adaptor<A, Alignment>& a,
    const aligned_allocator_adaptor<B, Alignment>& b) BOOST_NOEXCEPT
{
    return a.base() == b.base();
}

template<class A, class B, std::size_t Alignment>
inline bool
operator!=(const aligned_allocator_adaptor<A, Alignment>& a,
    const aligned_allocator_adaptor<B, Alignment>& b) BOOST_NOEXCEPT
{
    return !(a == b);
}

} /* alignment */
} /* boost */

#endif

/* aligned_allocator_adaptor.hpp
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
*/