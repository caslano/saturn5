/*
Copyright 2019-2021 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_SMART_PTR_ALLOCATE_UNIQUE_HPP
#define BOOST_SMART_PTR_ALLOCATE_UNIQUE_HPP

#include <boost/smart_ptr/detail/sp_noexcept.hpp>
#include <boost/smart_ptr/detail/sp_nullptr_t.hpp>
#include <boost/core/allocator_access.hpp>
#include <boost/core/alloc_construct.hpp>
#include <boost/core/empty_value.hpp>
#include <boost/core/first_scalar.hpp>
#include <boost/core/noinit_adaptor.hpp>
#include <boost/core/pointer_traits.hpp>
#include <boost/type_traits/enable_if.hpp>
#include <boost/type_traits/extent.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_bounded_array.hpp>
#include <boost/type_traits/is_unbounded_array.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_extent.hpp>
#include <boost/type_traits/type_identity.hpp>
#include <boost/config.hpp>
#include <memory>
#include <utility>

namespace boost {
namespace detail {

template<class T>
struct sp_alloc_size {
    BOOST_STATIC_CONSTEXPR std::size_t value = 1;
};

template<class T>
struct sp_alloc_size<T[]> {
    BOOST_STATIC_CONSTEXPR std::size_t value = sp_alloc_size<T>::value;
};

template<class T, std::size_t N>
struct sp_alloc_size<T[N]> {
    BOOST_STATIC_CONSTEXPR std::size_t value = N * sp_alloc_size<T>::value;
};

template<class T>
struct sp_alloc_result {
    typedef T type;
};

template<class T, std::size_t N>
struct sp_alloc_result<T[N]> {
    typedef T type[];
};

template<class T>
struct sp_alloc_value {
    typedef typename boost::remove_cv<typename
        boost::remove_extent<T>::type>::type type;
};

template<class T, class P>
class sp_alloc_ptr {
public:
    typedef T element_type;

    sp_alloc_ptr() BOOST_SP_NOEXCEPT
        : p_() { }

#if defined(BOOST_MSVC) && BOOST_MSVC == 1600
    sp_alloc_ptr(T* p) BOOST_SP_NOEXCEPT
        : p_(const_cast<typename boost::remove_cv<T>::type*>(p)) { }
#endif

    sp_alloc_ptr(std::size_t, P p) BOOST_SP_NOEXCEPT
        : p_(p) { }

#if !defined(BOOST_NO_CXX11_NULLPTR)
    sp_alloc_ptr(detail::sp_nullptr_t) BOOST_SP_NOEXCEPT
        : p_() { }
#endif

    T& operator*() const {
        return *p_;
    }

    T* operator->() const BOOST_SP_NOEXCEPT {
        return boost::to_address(p_);
    }

#if !defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)
    explicit operator bool() const BOOST_SP_NOEXCEPT {
        return !!p_;
    }
#endif

    bool operator!() const BOOST_SP_NOEXCEPT {
        return !p_;
    }

    P ptr() const BOOST_SP_NOEXCEPT {
        return p_;
    }

    BOOST_STATIC_CONSTEXPR std::size_t size() BOOST_SP_NOEXCEPT {
        return 1;
    }

#if defined(BOOST_MSVC) && BOOST_MSVC < 1910
    static sp_alloc_ptr pointer_to(T& v) {
        return sp_alloc_ptr(1,
            std::pointer_traits<P>::pointer_to(const_cast<typename
                boost::remove_cv<T>::type&>(v)));
    }
#endif

private:
    P p_;
};

template<class T, class P>
class sp_alloc_ptr<T[], P> {
public:
    typedef T element_type;

    sp_alloc_ptr() BOOST_SP_NOEXCEPT
        : p_() { }

    sp_alloc_ptr(std::size_t n, P p) BOOST_SP_NOEXCEPT
        : p_(p)
        , n_(n) { }

#if !defined(BOOST_NO_CXX11_NULLPTR)
    sp_alloc_ptr(detail::sp_nullptr_t) BOOST_SP_NOEXCEPT
        : p_() { }
#endif

    T& operator[](std::size_t i) const {
        return p_[i];
    }

#if !defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)
    explicit operator bool() const BOOST_SP_NOEXCEPT {
        return !!p_;
    }
#endif

    bool operator!() const BOOST_SP_NOEXCEPT {
        return !p_;
    }

    P ptr() const BOOST_SP_NOEXCEPT {
        return p_;
    }

    std::size_t size() const BOOST_SP_NOEXCEPT {
        return n_;
    }

#if defined(BOOST_MSVC) && BOOST_MSVC < 1910
    static sp_alloc_ptr pointer_to(T& v) {
        return sp_alloc_ptr(n_,
            std::pointer_traits<P>::pointer_to(const_cast<typename
                boost::remove_cv<T>::type&>(v)));
    }
#endif

private:
    P p_;
    std::size_t n_;
};

template<class T, std::size_t N, class P>
class sp_alloc_ptr<T[N], P> {
public:
    typedef T element_type;

    sp_alloc_ptr() BOOST_SP_NOEXCEPT
        : p_() { }

    sp_alloc_ptr(std::size_t, P p) BOOST_SP_NOEXCEPT
        : p_(p) { }

#if !defined(BOOST_NO_CXX11_NULLPTR)
    sp_alloc_ptr(detail::sp_nullptr_t) BOOST_SP_NOEXCEPT
        : p_() { }
#endif

    T& operator[](std::size_t i) const {
        return p_[i];
    }

#if !defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)
    explicit operator bool() const BOOST_SP_NOEXCEPT {
        return !!p_;
    }
#endif

    bool operator!() const BOOST_SP_NOEXCEPT {
        return !p_;
    }

    P ptr() const BOOST_SP_NOEXCEPT {
        return p_;
    }

    BOOST_STATIC_CONSTEXPR std::size_t size() BOOST_SP_NOEXCEPT {
        return N;
    }

#if defined(BOOST_MSVC) && BOOST_MSVC < 1910
    static sp_alloc_ptr pointer_to(T& v) {
        return sp_alloc_ptr(N,
            std::pointer_traits<P>::pointer_to(const_cast<typename
                boost::remove_cv<T>::type&>(v)));
    }
#endif

private:
    P p_;
};

template<class T, class P>
inline bool
operator==(const sp_alloc_ptr<T, P>& lhs, const sp_alloc_ptr<T, P>& rhs)
{
    return lhs.ptr() == rhs.ptr();
}

template<class T, class P>
inline bool
operator!=(const sp_alloc_ptr<T, P>& lhs, const sp_alloc_ptr<T, P>& rhs)
{
    return !(lhs == rhs);
}

#if !defined(BOOST_NO_CXX11_NULLPTR)
template<class T, class P>
inline bool
operator==(const sp_alloc_ptr<T, P>& lhs,
    detail::sp_nullptr_t) BOOST_SP_NOEXCEPT
{
    return !lhs.ptr();
}

template<class T, class P>
inline bool
operator==(detail::sp_nullptr_t,
    const sp_alloc_ptr<T, P>& rhs) BOOST_SP_NOEXCEPT
{
    return !rhs.ptr();
}

template<class T, class P>
inline bool
operator!=(const sp_alloc_ptr<T, P>& lhs,
    detail::sp_nullptr_t) BOOST_SP_NOEXCEPT
{
    return !!lhs.ptr();
}

template<class T, class P>
inline bool
operator!=(detail::sp_nullptr_t,
    const sp_alloc_ptr<T, P>& rhs) BOOST_SP_NOEXCEPT
{
    return !!rhs.ptr();
}
#endif

template<class A>
inline void
sp_alloc_clear(A& a, typename boost::allocator_pointer<A>::type p, std::size_t,
    boost::false_type)
{
    boost::alloc_destroy(a, boost::to_address(p));
}

template<class A>
inline void
sp_alloc_clear(A& a, typename boost::allocator_pointer<A>::type p,
    std::size_t n, boost::true_type)
{
#if defined(BOOST_MSVC) && BOOST_MSVC < 1800
    if (!p) {
        return;
    }
#endif
    boost::alloc_destroy_n(a, boost::first_scalar(boost::to_address(p)),
        n * sp_alloc_size<typename A::value_type>::value);
}

} /* detail */

template<class T, class A>
class alloc_deleter
    : empty_value<typename allocator_rebind<A,
        typename detail::sp_alloc_value<T>::type>::type> {
    typedef typename allocator_rebind<A,
        typename detail::sp_alloc_value<T>::type>::type allocator;
    typedef empty_value<allocator> base;

public:
    typedef detail::sp_alloc_ptr<T,
        typename allocator_pointer<allocator>::type> pointer;

    explicit alloc_deleter(const allocator& a) BOOST_SP_NOEXCEPT
        : base(empty_init_t(), a) { }

    void operator()(pointer p) {
        detail::sp_alloc_clear(base::get(), p.ptr(), p.size(), is_array<T>());
        base::get().deallocate(p.ptr(), p.size());
    }
};

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
template<class T, class A>
using alloc_noinit_deleter = alloc_deleter<T, noinit_adaptor<A> >;
#endif

namespace detail {

template<class T, class A>
class sp_alloc_make {
public:
    typedef typename boost::allocator_rebind<A,
        typename sp_alloc_value<T>::type>::type allocator;

private:
    typedef boost::alloc_deleter<T, A> deleter;

public:
    typedef std::unique_ptr<typename sp_alloc_result<T>::type, deleter> type;

    sp_alloc_make(const A& a, std::size_t n)
        : a_(a)
        , n_(n)
        , p_(a_.allocate(n)) { }

    ~sp_alloc_make() {
        if (p_) {
            a_.deallocate(p_, n_);
        }
    }

    typename allocator::value_type* get() const BOOST_SP_NOEXCEPT {
        return boost::to_address(p_);
    }

    allocator& state() BOOST_SP_NOEXCEPT {
        return a_;
    }

    type release() BOOST_SP_NOEXCEPT {
        pointer p = p_;
        p_ = pointer();
        return type(typename deleter::pointer(n_, p), deleter(a_));
    }

private:
    typedef typename boost::allocator_pointer<allocator>::type pointer;

    allocator a_;
    std::size_t n_;
    pointer p_;
};

} /* detail */

template<class T, class A>
inline typename enable_if_<!is_array<T>::value,
    std::unique_ptr<T, alloc_deleter<T, A> > >::type
allocate_unique(const A& alloc)
{
    detail::sp_alloc_make<T, A> c(alloc, 1);
    boost::alloc_construct(c.state(), c.get());
    return c.release();
}

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
template<class T, class A, class... Args>
inline typename enable_if_<!is_array<T>::value,
    std::unique_ptr<T, alloc_deleter<T, A> > >::type
allocate_unique(const A& alloc, Args&&... args)
{
    detail::sp_alloc_make<T, A> c(alloc, 1);
    boost::alloc_construct(c.state(), c.get(), std::forward<Args>(args)...);
    return c.release();
}
#endif

template<class T, class A>
inline typename enable_if_<!is_array<T>::value,
    std::unique_ptr<T, alloc_deleter<T, A> > >::type
allocate_unique(const A& alloc, typename type_identity<T>::type&& value)
{
    detail::sp_alloc_make<T, A> c(alloc, 1);
    boost::alloc_construct(c.state(), c.get(), std::move(value));
    return c.release();
}

template<class T, class A>
inline typename enable_if_<!is_array<T>::value,
    std::unique_ptr<T, alloc_deleter<T, noinit_adaptor<A> > > >::type
allocate_unique_noinit(const A& alloc)
{
    return boost::allocate_unique<T, noinit_adaptor<A> >(alloc);
}

template<class T, class A>
inline typename enable_if_<is_unbounded_array<T>::value,
    std::unique_ptr<T, alloc_deleter<T, A> > >::type
allocate_unique(const A& alloc, std::size_t size)
{
    detail::sp_alloc_make<T, A> c(alloc, size);
    boost::alloc_construct_n(c.state(), boost::first_scalar(c.get()),
        size * detail::sp_alloc_size<T>::value);
    return c.release();
}

template<class T, class A>
inline typename enable_if_<is_bounded_array<T>::value,
    std::unique_ptr<typename detail::sp_alloc_result<T>::type,
        alloc_deleter<T, A> > >::type
allocate_unique(const A& alloc)
{
    detail::sp_alloc_make<T, A> c(alloc, extent<T>::value);
    boost::alloc_construct_n(c.state(), boost::first_scalar(c.get()),
        detail::sp_alloc_size<T>::value);
    return c.release();
}

template<class T, class A>
inline typename enable_if_<is_unbounded_array<T>::value,
    std::unique_ptr<T, alloc_deleter<T, noinit_adaptor<A> > > >::type
allocate_unique_noinit(const A& alloc, std::size_t size)
{
    return boost::allocate_unique<T, noinit_adaptor<A> >(alloc, size);
}

template<class T, class A>
inline typename enable_if_<is_bounded_array<T>::value,
    std::unique_ptr<typename detail::sp_alloc_result<T>::type,
        alloc_deleter<T, noinit_adaptor<A> > > >::type
allocate_unique_noinit(const A& alloc)
{
    return boost::allocate_unique<T, noinit_adaptor<A> >(alloc);
}

template<class T, class A>
inline typename enable_if_<is_unbounded_array<T>::value,
    std::unique_ptr<T, alloc_deleter<T, A> > >::type
allocate_unique(const A& alloc, std::size_t size,
    const typename remove_extent<T>::type& value)
{
    detail::sp_alloc_make<T, A> c(alloc, size);
    boost::alloc_construct_n(c.state(), boost::first_scalar(c.get()),
        size * detail::sp_alloc_size<T>::value, boost::first_scalar(&value),
        detail::sp_alloc_size<typename remove_extent<T>::type>::value);
    return c.release();
}

template<class T, class A>
inline typename enable_if_<is_bounded_array<T>::value,
    std::unique_ptr<typename detail::sp_alloc_result<T>::type,
        alloc_deleter<T, A> > >::type
allocate_unique(const A& alloc,
    const typename remove_extent<T>::type& value)
{
    detail::sp_alloc_make<T, A> c(alloc, extent<T>::value);
    boost::alloc_construct_n(c.state(), boost::first_scalar(c.get()),
        detail::sp_alloc_size<T>::value, boost::first_scalar(&value),
        detail::sp_alloc_size<typename remove_extent<T>::type>::value);
    return c.release();
}

template<class T, class U, class A>
inline typename allocator_pointer<typename allocator_rebind<A,
    typename detail::sp_alloc_value<T>::type>::type>::type
get_allocator_pointer(const std::unique_ptr<T,
    alloc_deleter<U, A> >& p) BOOST_NOEXCEPT
{
    return p.get().ptr();
}

} /* boost */

#endif

/* allocate_unique.hpp
ojyaK2Ic7n3tGyyGClGZ6/7EsQo+3NwlwhECL0TMe8i6Vh9bhikT7we7pHOeUbTiRoI6dqor+XtEIgLup1DBJX+LnjzYNn6ja7kTKH++K7xwKOx3mUaVKgZ7EqFiAFM1URGt1+YKs53aNfqiCeKh8d36vKiJhDTZdYi/zunSpW8AfE/kZ8QtARyX8MAGbuAo5sP8znlaXSHkFZfAY4RedSDNAjadEvRcs4nd0HfazsgjP78tvAjDesVlfPCy2glFGBG8n1ZEDcL2QIpbWQgXWgin4t6LNEdI6hvPpnuCSRonALj441Mxs9VowAq/2RdaDd0xYSWGL2KeJitY8udokw3P36fMQFIZPIdSVvp2+7cwHQCk5LdXH6x0aDWIwMDdeo3eBVkt1qTMk4vw6n9ET9zYj777kDJKq0F0hiJvsT9BHKXtKZIsHpgNfkdbXc4qeRCMLsMnnYVobGZRkb6Tn48I92f4wmz+wn3yC/sPx77AgcFxYqvVPEhZso8F9wIcdMfzb8/yFvvEj8/KQCv6zoWxDy3nD/F39J0cReUITkiRLP7xKb7GA6JcHV0QVDlWiLYaqyUoLHJpyBURSdNqVvJLZFFr+M1qvKG2X9/7rc4a1JVjtZplZuhH5xGBAIfi4rGsXprX52OJ8GIrfkbNvXYvwgaJ7ksg0797EDH26wAVgUskY9+h5aEyC3vdwGnTQi13rHauGt78DKcV2C8YxsaXnNNx/roTY2Iw4s9/IcOpGI83HIdaiDlwgb4DXDs2yD44WsQO++NzhlSfc176uVTtvELjEYTPD/roCD/YgS/4RIhurqAy2bVixiX9SsLSB/YE7RnAlPvtiiGamo4Bs1ZFrs56210FwKq4kLI4jXubpo6lv5GPRe4soiUb+oVthhXeZlZ6s+HIAGtEZN5zLu7QPNiWM8ApAGU8EZqS5vOqgeOqpzHqMNlR/R6v3z0DvE/0hjwNXosuWmzs12JqcoLqOaxZ+Iz4sBkQ1KQHnywHtiRy+gIxLFYc1GckEdv/EO0CWhr6rLHEvGiBRi3/sOENQvO0habaLKqnTQtCBt3T5DX8wkLipE2xaoHj2gVlmctosthYrVs74tVnlQUrmnRlMMhrDhIxVgtiDwz2JgSeRP2ew9LrM/icUHryxpUj05x+ZykxVFeIIS9LaTFO14qL/eayd6GFp6dOpDF4lTNaoARcXGwcB2j5x7MOvER7V9bb7/ZaQOHvy6qnFH6s9xbqqVtheAWRJhTBqp8G9gk0RhvgOWXxHPafgzDtHLvTkD3ztGgVIquiWUOIQXfPkgStJ+sAIlu/jJ2dKtcaNOMrZyz5p/jLan6t5Yjq2W85oOY30CSEArXyK0RlmDYTY6Mb7sOO0xt2H7ZZXwMmOSajOyDMhh8ldg0h8Wn2STgaL1LXp2C5rgdekZG71PV38e/dnALeXl1fxve9OOBZj9MfdW8L3wM/iEHfEMxfYOD3+ppT9CaR99RlXM9yLstqbpf36rBYBJMvsJQnXxhj8tNBKawGOpVMPo6YxCNlYOvLZaL4MT8pxlMRPy00njz89KDx9IMyCABy0LhyWsvEiViM05H/vkkU3+o0+WgSzW/GJAH3f/GtLlZeCAaiCt2Nik7TocNzX7epiOaymJY9kUgZ8HPCGBGnTp5eWl6V1uzTkF+XEq17iRbkMfUQ8RV8g7GwP4G48VIoSizWA+niS8IS2QddQbvMpiXDZUN+G6i9Mex8O90dBJKomES5NHypMrv6oGPlMmx3/FxRrgXh0SJkXenY5XTNSV8yyLErJ8HlSa+8Z7LMsuQfRiMrLXp+Ws8/iwGJdgMSRWm4mwXWbZpTD3SHII3uo9Ub6DWAqX2zjhAHRcQnb9afrU2Amd18eH8Rf8vHaY0a6FMDva5dsLCiJemhOeulW5NrF5C6ssaQ00SW95O1+i6sVkJbXxHAAD9IZT1CqTh5ndP2rR6z5HtSEHRcOSoqXX/hn98SBSWBZDfLoir6VJ5FdW86/47m30z+xcipPOXq3rH8O5F/J/AvMGt9DWADxKm6l/2C7PXy70z+xaCxuUzeIhZTAarE88s6ZLySbJnIIVKWysREcalMBGwKv0xMEoNkIsBXzJGJyaI7wIkAdJFDiepepjw5el2QKUadg7bYRIH0Kvb1BfE87dt9/USz6e8DLP6YBfhvKrEAiPkltuz/LpMMr65iEyokHvg1jPHoC+RmSgANoCdoJCziVEYZUGAnfOLdLFKXndNbsW1rQ0GLnxCSNpdyJX/i5h8R4fEd2vxCJH58IpLwcdOpoRlDiBhbaKePNYIc/7iJYDzr7RxaU9qUjKwpaVdR5cueSMwLNpzLCSTpnmbdI4DfEEbGcE5utCiEs5PjEs+JJUuJJmQtoQnBI3wIJ+VHTo3XlvtAIEkuxuAbd8nundLOKUNdr+NtIPGtv//976bgJCULUWknAIMSh/pVUPqqloeGcrn42NC+2Yv3v3z9DDhZCHA/oqyRB7T/h6KpJvH6byASO6WVHDekYsYqkcIxN7UMOlQsTfpHJwJhNdFX6j1NLDyaZerUxdkUoifSaKMKv4fpM6VIEYYdgXyE4xShsOce55NPu/isAuogq4dZ0JoadNhQB1k91CLVQeyGOkjZZ2DfUjio151W4QIuldGRvvqJjIK1MKWfjAEh4SvWzohttGKZG4FC12JpxfEagIQ/VqSuYH6kBsPPU/k0L9gVeBaD3WZKDD2NVUpM8tkfyscc+dj2Q4i3IP6vwWJ2PM1U/0nXeizeynHVJx0rl1KKm58docf5o1jq+ri1sk79UZs4erAHQgPkWXIYpfNipSdz6TwuPZ5LT42WzjFKPyNLMyY9THwFtx2/xIPwPRPMNbxXrriL73nHXMGmcUyEe0NPM+4Q99N2VLNQpjDi+IBTFJnCWGM/p5TLFEYZf+WUJTKF8cWG+2Fbiz1XXYFfSXCrK5jsZspcXcH0eQ3v1yvwqzGJrjGJrj7NRPkK3M83QlsyTTrezeNccb22GuhUH1clJ0vfhWRR00CbqDxc4XxLDrY+AkyybZoUz7HP88Bwqdhk13cyUXZfu0kkfg0Nw+BZXXlQnF1owOUdT0r1WoBb0e6+naOcYtVwdnt+jbZPriIvbmy4cezcx4C6fQR0qd/6hAGVPhI80F4svD+m8aiwQcmfSOBkkXM3K2wPY+r4qCgEu+axideHM/CG+3CYKinxuuyD7KvZzu6aU4h/rjdNJBRVn2MbDjSRlxajoiEKpPqCdRmiOP2sDmceV3ps3309Ufzge14XFkoRLwsXOxRPqCBDfLZIChipib/6OVGlJbbqk5WPGCkrfw4F7D7cVvycj/FRJDC7R59B9JxqC3wYmaovGkOvP7ybKO7cMfgirRTlBhxwoSS7Y6UyXz5wRtf5bOuPlBMHXUfFq3QHhjxwzDjjiq5ou+xi9WllkLDRx9SxkUTxnrUnzhcql0sUb3ikhjgXsIqRt8sTeuJOEIm7v+dF2jxrsY89ja30sP60Npaq70Q4uYu1Qhsx8ceUEdo+pAYGTwvWWt3fPNYZOaZV2qpx8jLdpuXas4/1dNzufvfx4SHrc9oESrfdjozvPtaJ+vLtxeoE8Yt7aNYRzcC5oFQ1s0PrejMms/U/u/oMt5E4OEaSeG9Xv0/O2jcH7J+OVoLiPw8zaA7/4FCBtT5pJgrB+5YReJPGdXR1NySlBRPFpXQXnDQuh3YPaNjQBrt+apeujkcK7dxuh9TmyUHFxdGKZZ3Bq7gY1fKW9aWR0VMt1SX+DtPfggxQp/S0S5G8OtrCfRIjqAPi02Go2R6e+zzV3DfUED6Jy3f10Eg4JUS0KdPEiocM1cAPFkfXnGCjBzBbVKeYBRVghCRu94rcMBx7tEeV8rvu6mDL7sBu8diwqFYf0xgafdA/V0zb810CYwfQwpRh8RTL2XP9FEvBnrgRt4V/hoGZxM0PVjpNgSz4xEkL5aZ4xej/4jQ7TXvXcmx6aGpjd7lDK3aqXpua6wwK5/QnOrRKZ3Ztte54oZbPy66aQvkX2PxOv8mnVrSLOcTyqAsQdBnmQPvteq4dEZkroMKCgaC1cPtLwBbihaH9cqvCwmK5gnpZMbVDlN3K0H0rHLCOgoMbeEF6ZxwRCJVWLIY/3d4lGXBxPZs09BFK0YoJFnu1lF9Qc+letf6CQLaUD5Tt4V+iy3eADjoBUeu0tJ5G7egWs1KkP24XW57go+8pdsfyPzOxYnNNsTlqXgVrOSX+CNwnbnqkyzgC94mabecfgU/BEfgjQoWLDE8bkUX37HXebHLSAiUqPL+tuKx2nMnpN/utPPH33pbApAHOxdupvvcf5roJVHzium04I28nrpVokibDNSyxz+oEo/Dt11NhgMkmMcMudaZWHWE8y76Ps3W1MkWtTAuVjlbd6pNW9Umb+qQ9VDBVrZyoVuaIv19jNgUL0vRgQYpepN6qVmaolXa10qZWWtVKp1o5tz43XV9KY1GZKSOfEKxVTqCSau5EBC+ZH/0Qr9ZlWCEPbaCZmAQH2wibnanmjlZzx6i5Y9XccWruBCqn5uZ463OhrWhSc9PU3HQ1N0P/kPqUm0l/ZlIB+pNPhehPARWkP3dSYfozhCrQP7w2d5wfIYlLJ/izs5r0D7OaFqilE4zGyAhYrkp75XVF1Xr5OHelveJGLdempYerTyqO0IypQlxtNhWJ23fTWphGr5c0zfdjgRPd83IpghXvE76cOH/8wco0E7YQZYyWm5mVm16kL5qolY7OKs3w6j/QU5dAMSxZX5QjzW/4cZp1vpY7zpVcmaAma4smuBZbKy3qYmtcNGvsS3FV36ZNs6Jah6wYakL8Lcg5UCNVn5VMvGAfcbsyJWsafGL3+oyIQw76Xvax7JPuhqXJtCm5GyqsWXVak3anFWLnhsokemqMDNEWjXUfoVcd2ge0M1ihXjWryKhj4I4EhKbRlExEAJ7cHK14dFZxhmzULK9oyvhap7kbwPp02wgt5Yltu76Llprgw2rroH7dE3nQwauvA+vPsZyPpG4RT82jrXIRPBKW8x3oiIf5zo6Dt3nYclNoEDQCHE+f3wZUQS+uCWCHswfLp5oXzUbk9qNiApfKoLsb6C5YmWFSfqgvyoRckZ79zlDuaJT8EpZbiybQXTJXPpErz4mv/B0Fdvm5M3F/56P0odyZILVp5ZiWJoqsW7t0RH3AIcJRsZ7ytg6lN0V8hPnDx3jnVZMM6uI64znXaiRcGE2wGQm2aIIdeNgn/tR+higUe/BJ6tliJBEegEswI/uJR43s6UZCQzQhg9BOrpH4ejQxE732iW+cPTr3/5B4GHXlTkCuEOUK5U6k9y76KO7o/WlYOiIe8VGR+SjGwWOn1VI6Fe8enN+t3x+ssJuUS4JPEpWyaKZjNbxNawd4QB7HNN710w52E2AY2QH9HkqKbcVAGNC37OMFS+t1AtZrNq3XkDWspUVX7C1XYsWu2RFdsR8Ye7JIW0eAVZRMgCVenQhiOCX8GT5Rxp+QCk49jYTfH9QXTaUWX+kDKNBQXiZBWSsYnVVAy01gsoWa34ZuffQYz7cd9wseYVc0lXYHa/1SCy9BC9OAUezh4iKRxUpr1KaWVpjMi3RqhgicpUGrnOpDhLs2MZ4o7+Bt5kWXBO9rJkTfwrrTReL4V2dYF4M2r5U8yO344FuP8CC3+3UmEAb9iI9nS+2VPv9dYvZ2qUKG3aIaQcAbRMo38lwBIwLO6knaB92ldkfoMWyIBTbV+hI/3sNqqtTotXzWo/TB3K3UvuR3mqet3sTSviFJA06QxMw4yiFlez/lwEpKWpJPxqLVen3iIScb1hR8QRzy7yOsTzpIS/abIVAjrGeI8kC/QtvmR0UIx2zTJsHOgfB4iV1rp5lOLNI/RE9oH0Wum7w0B1bLAfxJ4D9J9Kun3n0TdCJt2niYRWi9OiEyxVKkf6DVG2ef4W1DpL0HK6qWWgcoqs7Zbiiq3h5idVi/yVufZLenOlXWixW//sRMzBpu6023Y9/32LXVeBxqGmuCIqs6OUVcEmaPGkNlxqq8FKg8o3sya5j1VydfJ5/UyTfIfMrQ+lxl0ELKmZeSExlGD7aFsjQziFzV3Sn6tyx1Wmo1zJOMA22I7V56vZNXsWwet/o86dOjFnS2ABUs6tOMVd5H/zWKhxlaDipDZUwAsUU3IObuDJwkoYkr8Vufw60TVivj6eLQX5BdS4IDz4V2MQELe5g62aklaTnOfgPDYGUedKzXDqWtX3fE6VjnaQV5A3Sst91IrOYpbmK/jnXXU/+Pdazz4nWst0/43zrWb1r+/9SxLn3qOzrW4cNDoif1zM2wJuq0v3T2+//aNmCF+LQzYjMBm/a0BAKrvotHfy26clRrF+/QS/q4VTsQ1bsOVfGA26qmp8BkVh8rHqDMxpapyZc5drn2AxZvZKhXmgo5dtksDRz3/L+wmPbYYtv495UaFiuVl2AUC/+/K2Y1ilX1FytrIBgOe74gGPzSBOIaE9zuqrA5qv8A6J5SDvtI+HEyqtGIOnD3wJgYurOf39Kln85NIjLgc8riK7ObUkANh+BfTdwM5Mi3OKL/8BysfgOp9dVIwSzId60IFK151rnK7YFLtCmKu15J8opLuqC8Vy5S6a/6pKI+WR45wDyYrHojwGYsYRZtUjM1ivALDinqPRDTmOCzJjCHOTWZ+3dGbkZHxhEJ5bVE814b8rRE826P5rVy3vZkznTAMwR420p/zac97VbFoeW3BO9rPwuGL+HODgKm9gQktlHit0j8skAyjvTCrAzR8gUSmyhxWcUQk3ItdZTqo46O65QdHdOJnX6dlmdTZyjw6jWlvPVdrFxKy7HJvDYjT44dZMzr9NYrujuIbtlCt/2DPwa85I5vMPi4jfqbKAaCio7vm1SMJxcP2/BQXYuvxX2+vhql5UThDhuVGPYn2ile1s39+012rdbhyi2n5epltfBgZbncLa5nERkBydvjwJKWg8MrUHzaJOB/Nc+mLyrXP9QXKfqH2bU5ksIObx8aXauSztY4mAgcHh6VXvHhVQzhfjEAH+GZM7h2c0iCKwhxsLY6GkPoQGVLHG24PmshtYX9qoHUNjTaR7l2Q8dqiUMz+0Jzemfp3oWaU5trdX8YsLo/UWCCrsq43k51rjWyWH4q+2T2sSmu3S1GyaL+kuVWlJBWPs6IR+Ntigb4Fo3Rt7tHGeOqtCrXuMqtiCM/gZjKnHHu+iU2rcCrLZodsWYfzD7NeFddaI2AHVUnqOXWeOq+sDC4G5bqJj6TPgJ7CCIfoWnrFe+fJEAAx8vuZ+zB2gRmx8VdywE0sJwI1n4LnJy1DAlOZKD0PCSlcVIaZzCSEmVSHhKMgp1LY0lcPSV9IpOQgQMBiSNLY5XLhDc5wc6f5yJbKYGoyrToUXuGNgd2FSe0oDHV6pw+GjW3lleulpfLwwsOVBziQxU1v0/TkFMzz9qse5fIYixAKCc4Yg051xsYesdyKLloGg8+gc82rv5Ydu0sL29gT47t1bUgcmp5mThEzLMB8D3dG6Hoq07iX0+7zKKW2+RN9unc4mKfutAuH33Fanmm/jq+wWeExOjl92oaXomb/3Q2+oH8NjUvM3rfS8Afve/GqvC0v4qPyaZy2668
*/