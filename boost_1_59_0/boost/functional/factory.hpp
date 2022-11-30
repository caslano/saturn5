/*
Copyright 2007 Tobias Schwinger

Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_FUNCTIONAL_FACTORY_HPP
#define BOOST_FUNCTIONAL_FACTORY_HPP

#include <boost/config.hpp>
#include <boost/core/empty_value.hpp>
#include <boost/core/pointer_traits.hpp>
#include <boost/type_traits/remove_cv.hpp>
#if !defined(BOOST_NO_CXX11_ALLOCATOR)
#include <memory>
#endif
#include <new>
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && \
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <utility>
#endif

namespace boost {

enum factory_alloc_propagation {
    factory_alloc_for_pointee_and_deleter,
    factory_passes_alloc_to_smart_pointer
};

namespace detail {

template<factory_alloc_propagation>
struct fc_tag { };

#if !defined(BOOST_NO_CXX11_ALLOCATOR)
template<class A, class T>
struct fc_rebind {
    typedef typename std::allocator_traits<A>::template rebind_alloc<T> type;
};

template<class A>
struct fc_pointer {
    typedef typename std::allocator_traits<A>::pointer type;
};
#else
template<class A, class T>
struct fc_rebind {
    typedef typename A::template rebind<T>::other type;
};

template<class A>
struct fc_pointer {
    typedef typename A::pointer type;
};
#endif

#if !defined(BOOST_NO_CXX11_ALLOCATOR) && \
    !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && \
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
template<class A, class T>
inline void
fc_destroy(A& a, T* p)
{
    std::allocator_traits<A>::destroy(a, p);
}
#else
template<class A, class T>
inline void
fc_destroy(A&, T* p)
{
    p->~T();
}
#endif

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && \
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#if !defined(BOOST_NO_CXX11_ALLOCATOR)
template<class A, class T, class... Args>
inline void
fc_construct(A& a, T* p, Args&&... args)
{
    std::allocator_traits<A>::construct(a, p, std::forward<Args>(args)...);
}
#else
template<class A, class T, class... Args>
inline void
fc_construct(A&, T* p, Args&&... args)
{
    ::new((void*)p) T(std::forward<Args>(args)...);
}
#endif
#endif

template<class A>
class fc_delete
    : boost::empty_value<A> {
    typedef boost::empty_value<A> base;

public:
    explicit fc_delete(const A& a) BOOST_NOEXCEPT
        : base(boost::empty_init_t(), a) { }

    void operator()(typename fc_pointer<A>::type p) {
        boost::detail::fc_destroy(base::get(), boost::to_address(p));
        base::get().deallocate(p, 1);
    }
};

template<class R, class A>
class fc_allocate {
public:
    explicit fc_allocate(const A& a)
        : a_(a)
        , p_(a_.allocate(1)) { }

    ~fc_allocate() {
        if (p_) {
            a_.deallocate(p_, 1);
        }
    }

    A& state() BOOST_NOEXCEPT {
        return a_;
    }

    typename A::value_type* get() const BOOST_NOEXCEPT {
        return boost::to_address(p_);
    }

    R release(fc_tag<factory_alloc_for_pointee_and_deleter>) {
        return R(release(), fc_delete<A>(a_), a_);
    }

    R release(fc_tag<factory_passes_alloc_to_smart_pointer>) {
        return R(release(), fc_delete<A>(a_));
    }

private:
    typedef typename fc_pointer<A>::type pointer;

    pointer release() BOOST_NOEXCEPT {
        pointer p = p_;
        p_ = pointer();
        return p;
    }

    fc_allocate(const fc_allocate&);
    fc_allocate& operator=(const fc_allocate&);

    A a_;
    pointer p_;
};

} /* detail */

template<class Pointer, class Allocator = void,
    factory_alloc_propagation Policy = factory_alloc_for_pointee_and_deleter>
class factory;

template<class Pointer, factory_alloc_propagation Policy>
class factory<Pointer, void, Policy> {
public:
    typedef typename remove_cv<Pointer>::type result_type;

private:
    typedef typename pointer_traits<result_type>::element_type type;

public:
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && \
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template<class... Args>
    result_type operator()(Args&&... args) const {
        return result_type(new type(std::forward<Args>(args)...));
    }
#else
    result_type operator()() const {
        return result_type(new type());
    }

    template<class A0>
    result_type operator()(A0& a0) const {
        return result_type(new type(a0));
    }

    template<class A0, class A1>
    result_type operator()(A0& a0, A1& a1) const {
        return result_type(new type(a0, a1));
    }

    template<class A0, class A1, class A2>
    result_type operator()(A0& a0, A1& a1, A2& a2) const {
        return result_type(new type(a0, a1, a2));
    }

    template<class A0, class A1, class A2, class A3>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3) const {
        return result_type(new type(a0, a1, a2, a3));
    }

    template<class A0, class A1, class A2, class A3, class A4>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4) const {
        return result_type(new type(a0, a1, a2, a3, a4));
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4,
        A5& a5) const {
        return result_type(new type(a0, a1, a2, a3, a4, a5));
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5,
        class A6>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
        A6& a6) const {
        return result_type(new type(a0, a1, a2, a3, a4, a5, a6));
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5,
        class A6, class A7>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
        A6& a6, A7& a7) const {
        return result_type(new type(a0, a1, a2, a3, a4, a5, a6, a7));
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5,
        class A6, class A7, class A8>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
        A6& a6, A7& a7, A8& a8) const {
        return result_type(new type(a0, a1, a2, a3, a4, a5, a6, a7, a8));
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5,
        class A6, class A7, class A8, class A9>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
        A6& a6, A7& a7, A8& a8, A9& a9) const {
        return result_type(new type(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9));
    }
#endif
};

template<class Pointer, class Allocator, factory_alloc_propagation Policy>
class factory
    : empty_value<typename detail::fc_rebind<Allocator,
        typename pointer_traits<typename
            remove_cv<Pointer>::type>::element_type>::type> {
public:
    typedef typename remove_cv<Pointer>::type result_type;

private:
    typedef typename pointer_traits<result_type>::element_type type;
    typedef typename detail::fc_rebind<Allocator, type>::type allocator;
    typedef empty_value<allocator> base;

public:
    factory() BOOST_NOEXCEPT
        : base(empty_init_t()) { }

    explicit factory(const Allocator& a) BOOST_NOEXCEPT
        : base(empty_init_t(), a) { }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && \
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template<class... Args>
    result_type operator()(Args&&... args) const {
        detail::fc_allocate<result_type, allocator> s(base::get());
        detail::fc_construct(s.state(), s.get(), std::forward<Args>(args)...);
        return s.release(detail::fc_tag<Policy>());
    }
#else
    result_type operator()() const {
        detail::fc_allocate<result_type, allocator> s(base::get());
        ::new((void*)s.get()) type();
        return s.release(detail::fc_tag<Policy>());
    }

    template<class A0>
    result_type operator()(A0& a0) const {
        detail::fc_allocate<result_type, allocator> s(base::get());
        ::new((void*)s.get()) type(a0);
        return s.release(detail::fc_tag<Policy>());
    }

    template<class A0, class A1>
    result_type operator()(A0& a0, A1& a1) const {
        detail::fc_allocate<result_type, allocator> s(base::get());
        ::new((void*)s.get()) type(a0, a1);
        return s.release(detail::fc_tag<Policy>());
    }

    template<class A0, class A1, class A2>
    result_type operator()(A0& a0, A1& a1, A2& a2) const {
        detail::fc_allocate<result_type, allocator> s(base::get());
        ::new((void*)s.get()) type(a0, a1, a2);
        return s.release(detail::fc_tag<Policy>());
    }

    template<class A0, class A1, class A2, class A3>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3) const {
        detail::fc_allocate<result_type, allocator> s(base::get());
        ::new((void*)s.get()) type(a0, a1, a2, a3);
        return s.release(detail::fc_tag<Policy>());
    }

    template<class A0, class A1, class A2, class A3, class A4>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4) const {
        detail::fc_allocate<result_type, allocator> s(base::get());
        ::new((void*)s.get()) type(a0, a1, a2, a3, a4);
        return s.release(detail::fc_tag<Policy>());
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4,
        A5& a5) const {
        detail::fc_allocate<result_type, allocator> s(base::get());
        ::new((void*)s.get()) type(a0, a1, a2, a3, a4, a5);
        return s.release(detail::fc_tag<Policy>());
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5,
        class A6>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
        A6& a6) const {
        detail::fc_allocate<result_type, allocator> s(base::get());
        ::new((void*)s.get()) type(a0, a1, a2, a3, a4, a5, a6);
        return s.release(detail::fc_tag<Policy>());
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5,
        class A6, class A7>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
        A6& a6, A7& a7) const {
        detail::fc_allocate<result_type, allocator> s(base::get());
        ::new((void*)s.get()) type(a0, a1, a2, a3, a4, a5, a6, a7);
        return s.release(detail::fc_tag<Policy>());
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5,
        class A6, class A7, class A8>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
        A6& a6, A7& a7, A8& a8) const {
        detail::fc_allocate<result_type, allocator> s(base::get());
        ::new((void*)s.get()) type(a0, a1, a2, a3, a4, a5, a6, a7, a8);
        return s.release(detail::fc_tag<Policy>());
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5,
        class A6, class A7, class A8, class A9>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
        A6& a6, A7& a7, A8& a8, A9& a9) const {
        detail::fc_allocate<result_type, allocator> s(base::get());
        ::new((void*)s.get()) type(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
        return s.release(detail::fc_tag<Policy>());
    }
#endif
};

template<class Pointer, class Allocator, factory_alloc_propagation Policy>
class factory<Pointer&, Allocator, Policy> { };

} /* boost */

#endif

/* factory.hpp
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
*/