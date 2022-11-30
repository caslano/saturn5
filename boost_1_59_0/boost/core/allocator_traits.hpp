/*
Copyright 2021 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_ALLOCATOR_TRAITS_HPP
#define BOOST_CORE_ALLOCATOR_TRAITS_HPP

#include <boost/core/allocator_access.hpp>

namespace boost {

template<class A>
struct allocator_traits {
    typedef A allocator_type;

    typedef typename allocator_value_type<A>::type value_type;

    typedef typename allocator_pointer<A>::type pointer;

    typedef typename allocator_const_pointer<A>::type const_pointer;

    typedef typename allocator_void_pointer<A>::type void_pointer;

    typedef typename allocator_const_void_pointer<A>::type const_void_pointer;

    typedef typename allocator_difference_type<A>::type difference_type;

    typedef typename allocator_size_type<A>::type size_type;

    typedef typename allocator_propagate_on_container_copy_assignment<A>::type
        propagate_on_container_copy_assignment;

    typedef typename allocator_propagate_on_container_move_assignment<A>::type
        propagate_on_container_move_assignment;

    typedef typename allocator_propagate_on_container_swap<A>::type
        propagate_on_container_swap;

    typedef typename allocator_is_always_equal<A>::type is_always_equal;

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
    template<class T>
    using rebind_traits = allocator_traits<typename
        allocator_rebind<A, T>::type>;
#else
    template<class T>
    struct rebind_traits
        : allocator_traits<typename allocator_rebind<A, T>::type> { };
#endif

    static pointer allocate(A& a, size_type n) {
        return boost::allocator_allocate(a, n);
    }

    static pointer allocate(A& a, size_type n, const_void_pointer h) {
        return boost::allocator_allocate(a, n, h);
    }

    static void deallocate(A& a, pointer p, size_type n) {
        return boost::allocator_deallocate(a, p, n);
    }

    template<class T>
    static void construct(A& a, T* p) {
        boost::allocator_construct(a, p);
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template<class T, class V, class... Args>
    static void construct(A& a, T* p, V&& v, Args&&... args) {
        boost::allocator_construct(a, p, std::forward<V>(v),
            std::forward<Args>(args)...);
    }
#else
    template<class T, class V>
    static void construct(A& a, T* p, V&& v) {
        boost::allocator_construct(a, p, std::forward<V>(v));
    }
#endif
#else
    template<class T, class V>
    static void construct(A& a, T* p, const V& v) {
        boost::allocator_construct(a, p, v);
    }

    template<class T, class V>
    static void construct(A& a, T* p, V& v) {
        boost::allocator_construct(a, p, v);
    }
#endif

    template<class T>
    static void destroy(A& a, T* p) {
        boost::allocator_destroy(a, p);
    }

    static size_type max_size(const A& a) BOOST_NOEXCEPT {
        return boost::allocator_max_size(a);
    }

    static A select_on_container_copy_construction(const A& a) {
        return boost::allocator_select_on_container_copy_construction(a);
    }
};

} /* boost */

#endif

/* allocator_traits.hpp
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
*/