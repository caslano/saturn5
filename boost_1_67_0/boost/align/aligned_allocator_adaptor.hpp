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