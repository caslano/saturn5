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