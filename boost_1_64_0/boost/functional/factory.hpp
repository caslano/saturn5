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
796m+6/8Ouwdnv/c9wH+/a+76/RX3s+UhvvrX3cG78nCnqf9PX98fvQPz7P8gT8+j/f75wV/zx+fNyH4/fNSf+CPzxP9/nmTP/DH50l//7zfH/jj8+Rcf/X9glZ/4/k7f+P5ceL5egHG5lR9WbfAAzGN/Wd5Dgnrbb0C9XZORBerF60WdI9aWGzwNgXTdnrxJmkHKBsWWxesP/xY/lnLtLT/veGnwTATRgPlhxMRlerfB/pGR5tjP1MqSYj1+M89cRlx+ex2mzP5mlBGyuGLONcQUyeTmabonUM/hZM/R5UUVB4qXHq7LfLpYNytU4X9mXIcBS3VWrMMR2TGdGSKYowRjhn/5i+8ZW9mBcJ939Tmjl/h8g78taJ964qzzESkr9192V/cbz/4TQXHpT6BIe4n58Tj8UYcNiKT+S7vR1ClP/+meVVS1W2vuGnIP1BL8VJ51fjhFJOkk2EelS3F5/y7ViwXvMPxR77OsD17q13uJ/uzK03ikR4Vr6fJxNXcZo3hNm4HbWM1Y5V2uqumuUu1ftdePV1nzBx66/WS5sHp1WJPbvHKwovLz51xV1KYj2dT/Hj4ec9p/HaSq5bxdXv2YZEJz9QBgpayx+W7Q7M/RX69G9DYlbOWqHN6gLTRi4GwPZlX8yOBs2pI4ZTnJOEjbhPTeyUCG0O7Zwh2FrpduT2zje73FXGUsctrKbn/DJ06+1z/lAJNCEll96q/uZ2sJ0uNG7XfLvuF0oQPEu4nbeWYeBizLzf2SXfdcHbBrQ8dcjmSM2eUsBDnsa39Ju6wwJNcWt6ZvJ2+XaJTFiUXqJ/RxJt0FllWLFqLk86o7xMO5ir5dhwRIriaf4K971K6pbvraJz/4tO00jZe5xfqJmWXHscK7ZEshdDdLncqFNALozQatlhNenblrPSQ7SvcHx4fui/ksnwKuPrw2P7onv6QrFD+pEuaGnw5vcKXqvpQMnc7Q1NPXZqxt+QsXjS0fMzXzW1aLjvjuw2Yk4Z/Id4RWLVd6j7F1T3+8bkp55XRx5FM/cJkQ5G/buS/nxjLCqZIKLlPTmyoe3cu/NDykB5h8O6CeRXDSD6rdo6wpzrhERrhAv7f5IXffOhEdYxoJ5GWq5tq0iZ+zls5XpyWRi9+s41vuPX6NccVw6ay6AyShYxA7iSCB0dpz7injEt8PP+LgtGjs96stB9I7VxWCROrr6iKkFvaP3lyh4S3L+Xt9WAWnbVbDE8KXnxlN7wdaNzJsZ8jSW39rEeb4bzSYCJRnVn6G2/UcEl/YkHDgkd5ivmq93GO1F8zU8Nu7tqKLS1WEK+XG+AO2y6KZs3KXFtv9jG65VYWPCHfoGFvLzKmJnrS+If9IT5BetkLHSV08cvfCM899CC9osGWRCmRVXsY36XdMpxUFZ/3E8NXv4hbzb8512DFmjFI0Yr7i8dTIeJzrSLrKtH1WY++VuAevPsWHZU4VxqXe7OojzuGuItB6Q6r2zf6N4X93z/e4TVlXpzW13iQLsGe0fgoTe3J66eG9baqije8ebI+1DKf3Hv4y/bDYcKhhrdDM9d6T3+YDeQcPExVfs7q8amL39dtaLkbn3LpV9Uce3Y3tH8qJPvERadTeKSs/3/9/42vP4dUuz3T9uOpzy4uh/X5604smShJWkRfJrQivOjQP+MrdvbJj18WWnUGDfooXxS3082v1DGHX8pT33AbbKqI6Esn5hlP+rFElZA9KupH0W3UfnJgTKnOxz66PU9Lmu81Se/Vppt6uAp5Rora0PbzPp657Gsz72t9W6dvpDAcfiQklVMWQJ6oIHDHqG/zwMXhY3/AOgGj0yequbMrC7FXm/E+BN6o644UxVt/4yhT2M8=
*/