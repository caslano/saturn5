/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGNED_ALLOCATOR_HPP
#define BOOST_ALIGN_ALIGNED_ALLOCATOR_HPP

#include <boost/align/detail/add_reference.hpp>
#include <boost/align/detail/is_alignment_constant.hpp>
#include <boost/align/detail/max_objects.hpp>
#include <boost/align/detail/max_size.hpp>
#include <boost/align/detail/throw_exception.hpp>
#include <boost/align/aligned_alloc.hpp>
#include <boost/align/aligned_allocator_forward.hpp>
#include <boost/align/alignment_of.hpp>
#include <boost/static_assert.hpp>
#include <new>

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

namespace boost {
namespace alignment {

template<class T, std::size_t Alignment>
class aligned_allocator {
    BOOST_STATIC_ASSERT(detail::is_alignment_constant<Alignment>::value);

public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef void* void_pointer;
    typedef const void* const_void_pointer;
    typedef typename detail::add_lvalue_reference<T>::type reference;
    typedef typename detail::add_lvalue_reference<const
        T>::type const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef detail::true_type propagate_on_container_move_assignment;
    typedef detail::true_type is_always_equal;

    template<class U>
    struct rebind {
        typedef aligned_allocator<U, Alignment> other;
    };

#if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)
    aligned_allocator() = default;
#else
    aligned_allocator() BOOST_NOEXCEPT { }
#endif

    template<class U>
    aligned_allocator(const aligned_allocator<U, Alignment>&)
        BOOST_NOEXCEPT { }

    pointer allocate(size_type size, const_void_pointer = 0) {
        enum {
            m = detail::max_size<Alignment,
                alignment_of<value_type>::value>::value
        };
        if (size == 0) {
            return 0;
        }
        void* p = boost::alignment::aligned_alloc(m, sizeof(T) * size);
        if (!p) {
            detail::throw_exception(std::bad_alloc());
        }
        return static_cast<T*>(p);
    }

    void deallocate(pointer ptr, size_type) {
        boost::alignment::aligned_free(ptr);
    }

    BOOST_CONSTEXPR size_type max_size() const BOOST_NOEXCEPT {
        return detail::max_objects<T>::value;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template<class U, class... Args>
    void construct(U* ptr, Args&&... args) {
        ::new((void*)ptr) U(std::forward<Args>(args)...);
    }
#else
    template<class U, class V>
    void construct(U* ptr, V&& value) {
        ::new((void*)ptr) U(std::forward<V>(value));
    }
#endif
#else
    template<class U, class V>
    void construct(U* ptr, const V& value) {
        ::new((void*)ptr) U(value);
    }

    template<class U, class V>
    void construct(U* ptr, V& value) {
        ::new((void*)ptr) U(value);
    }
#endif

    template<class U>
    void construct(U* ptr) {
        ::new((void*)ptr) U();
    }

    template<class U>
    void destroy(U* ptr) {
        (void)ptr;
        ptr->~U();
    }
};

template<class T, class U, std::size_t Alignment>
inline bool
operator==(const aligned_allocator<T, Alignment>&,
    const aligned_allocator<U, Alignment>&) BOOST_NOEXCEPT
{
    return true;
}

template<class T, class U, std::size_t Alignment>
inline bool
operator!=(const aligned_allocator<T, Alignment>&,
    const aligned_allocator<U, Alignment>&) BOOST_NOEXCEPT
{
    return false;
}

} /* alignment */
} /* boost */

#endif

/* aligned_allocator.hpp
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
*/