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