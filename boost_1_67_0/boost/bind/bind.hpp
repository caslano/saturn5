#ifndef BOOST_BIND_BIND_HPP_INCLUDED
#define BOOST_BIND_BIND_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  bind.hpp - binds function objects to arguments
//
//  Copyright (c) 2001-2004 Peter Dimov and Multi Media Ltd.
//  Copyright (c) 2001 David Abrahams
//  Copyright (c) 2005 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/bind/bind.html for documentation.
//

#include <boost/config.hpp>
#include <boost/ref.hpp>
#include <boost/mem_fn.hpp>
#include <boost/type.hpp>
#include <boost/is_placeholder.hpp>
#include <boost/bind/arg.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/visit_each.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/core/is_same.hpp>

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )
#include <utility> // std::forward
#endif

// Borland-specific bug, visit_each() silently fails to produce code

#if defined(__BORLANDC__)
#  define BOOST_BIND_VISIT_EACH boost::visit_each
#else
#  define BOOST_BIND_VISIT_EACH visit_each
#endif

#include <boost/bind/storage.hpp>

#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable: 4512) // assignment operator could not be generated
#endif

namespace boost
{

template<class T> class weak_ptr;

namespace _bi // implementation details
{

// result_traits

template<class R, class F> struct result_traits
{
    typedef R type;
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)

struct unspecified {};

template<class F> struct result_traits<unspecified, F>
{
    typedef typename F::result_type type;
};

template<class F> struct result_traits< unspecified, reference_wrapper<F> >
{
    typedef typename F::result_type type;
};

#endif

// ref_compare

template<class T> bool ref_compare( T const & a, T const & b, long )
{
    return a == b;
}

template<int I> bool ref_compare( arg<I> const &, arg<I> const &, int )
{
    return true;
}

template<int I> bool ref_compare( arg<I> (*) (), arg<I> (*) (), int )
{
    return true;
}

template<class T> bool ref_compare( reference_wrapper<T> const & a, reference_wrapper<T> const & b, int )
{
    return a.get_pointer() == b.get_pointer();
}

// bind_t forward declaration for listN

template<class R, class F, class L> class bind_t;

template<class R, class F, class L> bool ref_compare( bind_t<R, F, L> const & a, bind_t<R, F, L> const & b, int )
{
    return a.compare( b );
}

// value

template<class T> class value
{
public:

    value(T const & t): t_(t) {}

    T & get() { return t_; }
    T const & get() const { return t_; }

    bool operator==(value const & rhs) const
    {
        return t_ == rhs.t_;
    }

private:

    T t_;
};

// ref_compare for weak_ptr

template<class T> bool ref_compare( value< weak_ptr<T> > const & a, value< weak_ptr<T> > const & b, int )
{
    return !(a.get() < b.get()) && !(b.get() < a.get());
}

// type

template<class T> class type {};

// unwrap

template<class F> struct unwrapper
{
    static inline F & unwrap( F & f, long )
    {
        return f;
    }

    template<class F2> static inline F2 & unwrap( reference_wrapper<F2> rf, int )
    {
        return rf.get();
    }

    template<class R, class T> static inline _mfi::dm<R, T> unwrap( R T::* pm, int )
    {
        return _mfi::dm<R, T>( pm );
    }
};

// listN

class list0
{
public:

    list0() {}

    template<class T> T & operator[] (_bi::value<T> & v) const { return v.get(); }

    template<class T> T const & operator[] (_bi::value<T> const & v) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }

    template<class R, class F, class A> R operator()(type<R>, F & f, A &, long)
    {
        return unwrapper<F>::unwrap(f, 0)();
    }

    template<class R, class F, class A> R operator()(type<R>, F const & f, A &, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)();
    }

    template<class F, class A> void operator()(type<void>, F & f, A &, int)
    {
        unwrapper<F>::unwrap(f, 0)();
    }

    template<class F, class A> void operator()(type<void>, F const & f, A &, int) const
    {
        unwrapper<F const>::unwrap(f, 0)();
    }

    template<class V> void accept(V &) const
    {
    }

    bool operator==(list0 const &) const
    {
        return true;
    }
};

#ifdef BOOST_MSVC
// MSVC is bright enough to realise that the parameter rhs 
// in operator==may be unused for some template argument types:
#pragma warning(push)
#pragma warning(disable:4100)
#endif

template< class A1 > class list1: private storage1< A1 >
{
private:

    typedef storage1< A1 > base_type;

public:

    explicit list1( A1 a1 ): base_type( a1 ) {}

    A1 operator[] (boost::arg<1>) const { return base_type::a1_; }

    A1 operator[] (boost::arg<1> (*) ()) const { return base_type::a1_; }

    template<class T> T & operator[] ( _bi::value<T> & v ) const { return v.get(); }

    template<class T> T const & operator[] ( _bi::value<T> const & v ) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }

    template<class R, class F, class A> R operator()(type<R>, F & f, A & a, long)
    {
        return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_]);
    }

    template<class R, class F, class A> R operator()(type<R>, F const & f, A & a, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_]);
    }

    template<class F, class A> void operator()(type<void>, F & f, A & a, int)
    {
        unwrapper<F>::unwrap(f, 0)(a[base_type::a1_]);
    }

    template<class F, class A> void operator()(type<void>, F const & f, A & a, int) const
    {
        unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_]);
    }

    template<class V> void accept(V & v) const
    {
        base_type::accept(v);
    }

    bool operator==(list1 const & rhs) const
    {
        return ref_compare(base_type::a1_, rhs.a1_, 0);
    }
};

struct logical_and;
struct logical_or;

template< class A1, class A2 > class list2: private storage2< A1, A2 >
{
private:

    typedef storage2< A1, A2 > base_type;

public:

    list2( A1 a1, A2 a2 ): base_type( a1, a2 ) {}

    A1 operator[] (boost::arg<1>) const { return base_type::a1_; }
    A2 operator[] (boost::arg<2>) const { return base_type::a2_; }

    A1 operator[] (boost::arg<1> (*) ()) const { return base_type::a1_; }
    A2 operator[] (boost::arg<2> (*) ()) const { return base_type::a2_; }

    template<class T> T & operator[] (_bi::value<T> & v) const { return v.get(); }

    template<class T> T const & operator[] (_bi::value<T> const & v) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }

    template<class R, class F, class A> R operator()(type<R>, F & f, A & a, long)
    {
        return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_]);
    }

    template<class R, class F, class A> R operator()(type<R>, F const & f, A & a, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_]);
    }

    template<class F, class A> void operator()(type<void>, F & f, A & a, int)
    {
        unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_]);
    }

    template<class F, class A> void operator()(type<void>, F const & f, A & a, int) const
    {
        unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_]);
    }

    template<class A> bool operator()( type<bool>, logical_and & /*f*/, A & a, int )
    {
        return a[ base_type::a1_ ] && a[ base_type::a2_ ];
    }

    template<class A> bool operator()( type<bool>, logical_and const & /*f*/, A & a, int ) const
    {
        return a[ base_type::a1_ ] && a[ base_type::a2_ ];
    }

    template<class A> bool operator()( type<bool>, logical_or & /*f*/, A & a, int )
    {
        return a[ base_type::a1_ ] || a[ base_type::a2_ ];
    }

    template<class A> bool operator()( type<bool>, logical_or const & /*f*/, A & a, int ) const
    {
        return a[ base_type::a1_ ] || a[ base_type::a2_ ];
    }

    template<class V> void accept(V & v) const
    {
        base_type::accept(v);
    }

    bool operator==(list2 const & rhs) const
    {
        return ref_compare(base_type::a1_, rhs.a1_, 0) && ref_compare(base_type::a2_, rhs.a2_, 0);
    }
};

template< class A1, class A2, class A3 > class list3: private storage3< A1, A2, A3 >
{
private:

    typedef storage3< A1, A2, A3 > base_type;

public:

    list3( A1 a1, A2 a2, A3 a3 ): base_type( a1, a2, a3 ) {}

    A1 operator[] (boost::arg<1>) const { return base_type::a1_; }
    A2 operator[] (boost::arg<2>) const { return base_type::a2_; }
    A3 operator[] (boost::arg<3>) const { return base_type::a3_; }

    A1 operator[] (boost::arg<1> (*) ()) const { return base_type::a1_; }
    A2 operator[] (boost::arg<2> (*) ()) const { return base_type::a2_; }
    A3 operator[] (boost::arg<3> (*) ()) const { return base_type::a3_; }

    template<class T> T & operator[] (_bi::value<T> & v) const { return v.get(); }

    template<class T> T const & operator[] (_bi::value<T> const & v) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }

    template<class R, class F, class A> R operator()(type<R>, F & f, A & a, long)
    {
        return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_]);
    }

    template<class R, class F, class A> R operator()(type<R>, F const & f, A & a, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_]);
    }

    template<class F, class A> void operator()(type<void>, F & f, A & a, int)
    {
        unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_]);
    }

    template<class F, class A> void operator()(type<void>, F const & f, A & a, int) const
    {
        unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_]);
    }

    template<class V> void accept(V & v) const
    {
        base_type::accept(v);
    }

    bool operator==(list3 const & rhs) const
    {
        return
            
            ref_compare( base_type::a1_, rhs.a1_, 0 ) &&
            ref_compare( base_type::a2_, rhs.a2_, 0 ) &&
            ref_compare( base_type::a3_, rhs.a3_, 0 );
    }
};

template< class A1, class A2, class A3, class A4 > class list4: private storage4< A1, A2, A3, A4 >
{
private:

    typedef storage4< A1, A2, A3, A4 > base_type;

public:

    list4( A1 a1, A2 a2, A3 a3, A4 a4 ): base_type( a1, a2, a3, a4 ) {}

    A1 operator[] (boost::arg<1>) const { return base_type::a1_; }
    A2 operator[] (boost::arg<2>) const { return base_type::a2_; }
    A3 operator[] (boost::arg<3>) const { return base_type::a3_; }
    A4 operator[] (boost::arg<4>) const { return base_type::a4_; }

    A1 operator[] (boost::arg<1> (*) ()) const { return base_type::a1_; }
    A2 operator[] (boost::arg<2> (*) ()) const { return base_type::a2_; }
    A3 operator[] (boost::arg<3> (*) ()) const { return base_type::a3_; }
    A4 operator[] (boost::arg<4> (*) ()) const { return base_type::a4_; }

    template<class T> T & operator[] (_bi::value<T> & v) const { return v.get(); }

    template<class T> T const & operator[] (_bi::value<T> const & v) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }

    template<class R, class F, class A> R operator()(type<R>, F & f, A & a, long)
    {
        return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_]);
    }

    template<class R, class F, class A> R operator()(type<R>, F const & f, A & a, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_]);
    }

    template<class F, class A> void operator()(type<void>, F & f, A & a, int)
    {
        unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_]);
    }

    template<class F, class A> void operator()(type<void>, F const & f, A & a, int) const
    {
        unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_]);
    }

    template<class V> void accept(V & v) const
    {
        base_type::accept(v);
    }

    bool operator==(list4 const & rhs) const
    {
        return

            ref_compare( base_type::a1_, rhs.a1_, 0 ) &&
            ref_compare( base_type::a2_, rhs.a2_, 0 ) &&
            ref_compare( base_type::a3_, rhs.a3_, 0 ) &&
            ref_compare( base_type::a4_, rhs.a4_, 0 );
    }
};

template< class A1, class A2, class A3, class A4, class A5 > class list5: private storage5< A1, A2, A3, A4, A5 >
{
private:

    typedef storage5< A1, A2, A3, A4, A5 > base_type;

public:

    list5( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5 ): base_type( a1, a2, a3, a4, a5 ) {}

    A1 operator[] (boost::arg<1>) const { return base_type::a1_; }
    A2 operator[] (boost::arg<2>) const { return base_type::a2_; }
    A3 operator[] (boost::arg<3>) const { return base_type::a3_; }
    A4 operator[] (boost::arg<4>) const { return base_type::a4_; }
    A5 operator[] (boost::arg<5>) const { return base_type::a5_; }

    A1 operator[] (boost::arg<1> (*) ()) const { return base_type::a1_; }
    A2 operator[] (boost::arg<2> (*) ()) const { return base_type::a2_; }
    A3 operator[] (boost::arg<3> (*) ()) const { return base_type::a3_; }
    A4 operator[] (boost::arg<4> (*) ()) const { return base_type::a4_; }
    A5 operator[] (boost::arg<5> (*) ()) const { return base_type::a5_; }

    template<class T> T & operator[] (_bi::value<T> & v) const { return v.get(); }

    template<class T> T const & operator[] (_bi::value<T> const & v) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }

    template<class R, class F, class A> R operator()(type<R>, F & f, A & a, long)
    {
        return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_]);
    }

    template<class R, class F, class A> R operator()(type<R>, F const & f, A & a, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_]);
    }

    template<class F, class A> void operator()(type<void>, F & f, A & a, int)
    {
        unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_]);
    }

    template<class F, class A> void operator()(type<void>, F const & f, A & a, int) const
    {
        unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_]);
    }

    template<class V> void accept(V & v) const
    {
        base_type::accept(v);
    }

    bool operator==(list5 const & rhs) const
    {
        return

            ref_compare( base_type::a1_, rhs.a1_, 0 ) &&
            ref_compare( base_type::a2_, rhs.a2_, 0 ) &&
            ref_compare( base_type::a3_, rhs.a3_, 0 ) &&
            ref_compare( base_type::a4_, rhs.a4_, 0 ) &&
            ref_compare( base_type::a5_, rhs.a5_, 0 );
    }
};

template<class A1, class A2, class A3, class A4, class A5, class A6> class list6: private storage6< A1, A2, A3, A4, A5, A6 >
{
private:

    typedef storage6< A1, A2, A3, A4, A5, A6 > base_type;

public:

    list6( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6 ): base_type( a1, a2, a3, a4, a5, a6 ) {}

    A1 operator[] (boost::arg<1>) const { return base_type::a1_; }
    A2 operator[] (boost::arg<2>) const { return base_type::a2_; }
    A3 operator[] (boost::arg<3>) const { return base_type::a3_; }
    A4 operator[] (boost::arg<4>) const { return base_type::a4_; }
    A5 operator[] (boost::arg<5>) const { return base_type::a5_; }
    A6 operator[] (boost::arg<6>) const { return base_type::a6_; }

    A1 operator[] (boost::arg<1> (*) ()) const { return base_type::a1_; }
    A2 operator[] (boost::arg<2> (*) ()) const { return base_type::a2_; }
    A3 operator[] (boost::arg<3> (*) ()) const { return base_type::a3_; }
    A4 operator[] (boost::arg<4> (*) ()) const { return base_type::a4_; }
    A5 operator[] (boost::arg<5> (*) ()) const { return base_type::a5_; }
    A6 operator[] (boost::arg<6> (*) ()) const { return base_type::a6_; }

    template<class T> T & operator[] (_bi::value<T> & v) const { return v.get(); }

    template<class T> T const & operator[] (_bi::value<T> const & v) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }

    template<class R, class F, class A> R operator()(type<R>, F & f, A & a, long)
    {
        return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_]);
    }

    template<class R, class F, class A> R operator()(type<R>, F const & f, A & a, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_]);
    }

    template<class F, class A> void operator()(type<void>, F & f, A & a, int)
    {
        unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_]);
    }

    template<class F, class A> void operator()(type<void>, F const & f, A & a, int) const
    {
        unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_]);
    }

    template<class V> void accept(V & v) const
    {
        base_type::accept(v);
    }

    bool operator==(list6 const & rhs) const
    {
        return

            ref_compare( base_type::a1_, rhs.a1_, 0 ) &&
            ref_compare( base_type::a2_, rhs.a2_, 0 ) &&
            ref_compare( base_type::a3_, rhs.a3_, 0 ) &&
            ref_compare( base_type::a4_, rhs.a4_, 0 ) &&
            ref_compare( base_type::a5_, rhs.a5_, 0 ) &&
            ref_compare( base_type::a6_, rhs.a6_, 0 );
    }
};

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> class list7: private storage7< A1, A2, A3, A4, A5, A6, A7 >
{
private:

    typedef storage7< A1, A2, A3, A4, A5, A6, A7 > base_type;

public:

    list7( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7 ): base_type( a1, a2, a3, a4, a5, a6, a7 ) {}

    A1 operator[] (boost::arg<1>) const { return base_type::a1_; }
    A2 operator[] (boost::arg<2>) const { return base_type::a2_; }
    A3 operator[] (boost::arg<3>) const { return base_type::a3_; }
    A4 operator[] (boost::arg<4>) const { return base_type::a4_; }
    A5 operator[] (boost::arg<5>) const { return base_type::a5_; }
    A6 operator[] (boost::arg<6>) const { return base_type::a6_; }
    A7 operator[] (boost::arg<7>) const { return base_type::a7_; }

    A1 operator[] (boost::arg<1> (*) ()) const { return base_type::a1_; }
    A2 operator[] (boost::arg<2> (*) ()) const { return base_type::a2_; }
    A3 operator[] (boost::arg<3> (*) ()) const { return base_type::a3_; }
    A4 operator[] (boost::arg<4> (*) ()) const { return base_type::a4_; }
    A5 operator[] (boost::arg<5> (*) ()) const { return base_type::a5_; }
    A6 operator[] (boost::arg<6> (*) ()) const { return base_type::a6_; }
    A7 operator[] (boost::arg<7> (*) ()) const { return base_type::a7_; }

    template<class T> T & operator[] (_bi::value<T> & v) const { return v.get(); }

    template<class T> T const & operator[] (_bi::value<T> const & v) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }

    template<class R, class F, class A> R operator()(type<R>, F & f, A & a, long)
    {
        return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_]);
    }

    template<class R, class F, class A> R operator()(type<R>, F const & f, A & a, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_]);
    }

    template<class F, class A> void operator()(type<void>, F & f, A & a, int)
    {
        unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_]);
    }

    template<class F, class A> void operator()(type<void>, F const & f, A & a, int) const
    {
        unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_]);
    }

    template<class V> void accept(V & v) const
    {
        base_type::accept(v);
    }

    bool operator==(list7 const & rhs) const
    {
        return

            ref_compare( base_type::a1_, rhs.a1_, 0 ) &&
            ref_compare( base_type::a2_, rhs.a2_, 0 ) &&
            ref_compare( base_type::a3_, rhs.a3_, 0 ) &&
            ref_compare( base_type::a4_, rhs.a4_, 0 ) &&
            ref_compare( base_type::a5_, rhs.a5_, 0 ) &&
            ref_compare( base_type::a6_, rhs.a6_, 0 ) &&
            ref_compare( base_type::a7_, rhs.a7_, 0 );
    }
};

template< class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8 > class list8: private storage8< A1, A2, A3, A4, A5, A6, A7, A8 >
{
private:

    typedef storage8< A1, A2, A3, A4, A5, A6, A7, A8 > base_type;

public:

    list8( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8 ): base_type( a1, a2, a3, a4, a5, a6, a7, a8 ) {}

    A1 operator[] (boost::arg<1>) const { return base_type::a1_; }
    A2 operator[] (boost::arg<2>) const { return base_type::a2_; }
    A3 operator[] (boost::arg<3>) const { return base_type::a3_; }
    A4 operator[] (boost::arg<4>) const { return base_type::a4_; }
    A5 operator[] (boost::arg<5>) const { return base_type::a5_; }
    A6 operator[] (boost::arg<6>) const { return base_type::a6_; }
    A7 operator[] (boost::arg<7>) const { return base_type::a7_; }
    A8 operator[] (boost::arg<8>) const { return base_type::a8_; }

    A1 operator[] (boost::arg<1> (*) ()) const { return base_type::a1_; }
    A2 operator[] (boost::arg<2> (*) ()) const { return base_type::a2_; }
    A3 operator[] (boost::arg<3> (*) ()) const { return base_type::a3_; }
    A4 operator[] (boost::arg<4> (*) ()) const { return base_type::a4_; }
    A5 operator[] (boost::arg<5> (*) ()) const { return base_type::a5_; }
    A6 operator[] (boost::arg<6> (*) ()) const { return base_type::a6_; }
    A7 operator[] (boost::arg<7> (*) ()) const { return base_type::a7_; }
    A8 operator[] (boost::arg<8> (*) ()) const { return base_type::a8_; }

    template<class T> T & operator[] (_bi::value<T> & v) const { return v.get(); }

    template<class T> T const & operator[] (_bi::value<T> const & v) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }

    template<class R, class F, class A> R operator()(type<R>, F & f, A & a, long)
    {
        return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_], a[base_type::a8_]);
    }

    template<class R, class F, class A> R operator()(type<R>, F const & f, A & a, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_], a[base_type::a8_]);
    }

    template<class F, class A> void operator()(type<void>, F & f, A & a, int)
    {
        unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_], a[base_type::a8_]);
    }

    template<class F, class A> void operator()(type<void>, F const & f, A & a, int) const
    {
        unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_], a[base_type::a8_]);
    }

    template<class V> void accept(V & v) const
    {
        base_type::accept(v);
    }

    bool operator==(list8 const & rhs) const
    {
        return
            
            ref_compare( base_type::a1_, rhs.a1_, 0 ) &&
            ref_compare( base_type::a2_, rhs.a2_, 0 ) &&
            ref_compare( base_type::a3_, rhs.a3_, 0 ) &&
            ref_compare( base_type::a4_, rhs.a4_, 0 ) &&
            ref_compare( base_type::a5_, rhs.a5_, 0 ) &&
            ref_compare( base_type::a6_, rhs.a6_, 0 ) &&
            ref_compare( base_type::a7_, rhs.a7_, 0 ) &&
            ref_compare( base_type::a8_, rhs.a8_, 0 );
    }
};

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> class list9: private storage9< A1, A2, A3, A4, A5, A6, A7, A8, A9 >
{
private:

    typedef storage9< A1, A2, A3, A4, A5, A6, A7, A8, A9 > base_type;

public:

    list9( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9 ): base_type( a1, a2, a3, a4, a5, a6, a7, a8, a9 ) {}

    A1 operator[] (boost::arg<1>) const { return base_type::a1_; }
    A2 operator[] (boost::arg<2>) const { return base_type::a2_; }
    A3 operator[] (boost::arg<3>) const { return base_type::a3_; }
    A4 operator[] (boost::arg<4>) const { return base_type::a4_; }
    A5 operator[] (boost::arg<5>) const { return base_type::a5_; }
    A6 operator[] (boost::arg<6>) const { return base_type::a6_; }
    A7 operator[] (boost::arg<7>) const { return base_type::a7_; }
    A8 operator[] (boost::arg<8>) const { return base_type::a8_; }
    A9 operator[] (boost::arg<9>) const { return base_type::a9_; }

    A1 operator[] (boost::arg<1> (*) ()) const { return base_type::a1_; }
    A2 operator[] (boost::arg<2> (*) ()) const { return base_type::a2_; }
    A3 operator[] (boost::arg<3> (*) ()) const { return base_type::a3_; }
    A4 operator[] (boost::arg<4> (*) ()) const { return base_type::a4_; }
    A5 operator[] (boost::arg<5> (*) ()) const { return base_type::a5_; }
    A6 operator[] (boost::arg<6> (*) ()) const { return base_type::a6_; }
    A7 operator[] (boost::arg<7> (*) ()) const { return base_type::a7_; }
    A8 operator[] (boost::arg<8> (*) ()) const { return base_type::a8_; }
    A9 operator[] (boost::arg<9> (*) ()) const { return base_type::a9_; }

    template<class T> T & operator[] (_bi::value<T> & v) const { return v.get(); }

    template<class T> T const & operator[] (_bi::value<T> const & v) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }

    template<class R, class F, class A> R operator()(type<R>, F & f, A & a, long)
    {
        return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_], a[base_type::a8_], a[base_type::a9_]);
    }

    template<class R, class F, class A> R operator()(type<R>, F const & f, A & a, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_], a[base_type::a8_], a[base_type::a9_]);
    }

    template<class F, class A> void operator()(type<void>, F & f, A & a, int)
    {
        unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_], a[base_type::a8_], a[base_type::a9_]);
    }

    template<class F, class A> void operator()(type<void>, F const & f, A & a, int) const
    {
        unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_], a[base_type::a8_], a[base_type::a9_]);
    }

    template<class V> void accept(V & v) const
    {
        base_type::accept(v);
    }

    bool operator==(list9 const & rhs) const
    {
        return

            ref_compare( base_type::a1_, rhs.a1_, 0 ) &&
            ref_compare( base_type::a2_, rhs.a2_, 0 ) &&
            ref_compare( base_type::a3_, rhs.a3_, 0 ) &&
            ref_compare( base_type::a4_, rhs.a4_, 0 ) &&
            ref_compare( base_type::a5_, rhs.a5_, 0 ) &&
            ref_compare( base_type::a6_, rhs.a6_, 0 ) &&
            ref_compare( base_type::a7_, rhs.a7_, 0 ) &&
            ref_compare( base_type::a8_, rhs.a8_, 0 ) &&
            ref_compare( base_type::a9_, rhs.a9_, 0 );
    }
};

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

// bind_t

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

template< class A1 > class rrlist1
{
private:

    A1 & a1_; // not A1&& because of msvc-10.0

public:

    explicit rrlist1( A1 & a1 ): a1_( a1 ) {}

    A1 && operator[] (boost::arg<1>) const { return std::forward<A1>( a1_ ); } // not static_cast because of g++ 4.9

    A1 && operator[] (boost::arg<1> (*) ()) const { return std::forward<A1>( a1_ ); }

    template<class T> T & operator[] ( _bi::value<T> & v ) const { return v.get(); }

    template<class T> T const & operator[] ( _bi::value<T> const & v ) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const
    {
        rrlist1<A1&> a( a1_ );
        return b.eval( a );
    }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const
    {
        rrlist1<A1&> a( a1_ );
        return b.eval( a );
    }
};

template< class A1, class A2 > class rrlist2
{
private:

    A1 & a1_;
    A2 & a2_;

public:

    rrlist2( A1 & a1, A2 & a2 ): a1_( a1 ), a2_( a2 ) {}

    A1 && operator[] (boost::arg<1>) const { return std::forward<A1>( a1_ ); }
    A2 && operator[] (boost::arg<2>) const { return std::forward<A2>( a2_ ); }

    A1 && operator[] (boost::arg<1> (*) ()) const { return std::forward<A1>( a1_ ); }
    A2 && operator[] (boost::arg<2> (*) ()) const { return std::forward<A2>( a2_ ); }

    template<class T> T & operator[] ( _bi::value<T> & v ) const { return v.get(); }

    template<class T> T const & operator[] ( _bi::value<T> const & v ) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const
    {
        rrlist2<A1&, A2&> a( a1_, a2_ );
        return b.eval( a );
    }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const
    {
        rrlist2<A1&, A2&> a( a1_, a2_ );
        return b.eval( a );
    }
};

template< class A1, class A2, class A3 > class rrlist3
{
private:

    A1 & a1_;
    A2 & a2_;
    A3 & a3_;

public:

    rrlist3( A1 & a1, A2 & a2, A3 & a3 ): a1_( a1 ), a2_( a2 ), a3_( a3 ) {}

    A1 && operator[] (boost::arg<1>) const { return std::forward<A1>( a1_ ); }
    A2 && operator[] (boost::arg<2>) const { return std::forward<A2>( a2_ ); }
    A3 && operator[] (boost::arg<3>) const { return std::forward<A3>( a3_ ); }

    A1 && operator[] (boost::arg<1> (*) ()) const { return std::forward<A1>( a1_ ); }
    A2 && operator[] (boost::arg<2> (*) ()) const { return std::forward<A2>( a2_ ); }
    A3 && operator[] (boost::arg<3> (*) ()) const { return std::forward<A3>( a3_ ); }

    template<class T> T & operator[] ( _bi::value<T> & v ) const { return v.get(); }

    template<class T> T const & operator[] ( _bi::value<T> const & v ) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const
    {
        rrlist3<A1&, A2&, A3&> a( a1_, a2_, a3_ );
        return b.eval( a );
    }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const
    {
        rrlist3<A1&, A2&, A3&> a( a1_, a2_, a3_ );
        return b.eval( a );
    }
};

template< class A1, class A2, class A3, class A4 > class rrlist4
{
private:

    A1 & a1_;
    A2 & a2_;
    A3 & a3_;
    A4 & a4_;

public:

    rrlist4( A1 & a1, A2 & a2, A3 & a3, A4 & a4 ): a1_( a1 ), a2_( a2 ), a3_( a3 ), a4_( a4 ) {}

    A1 && operator[] (boost::arg<1>) const { return std::forward<A1>( a1_ ); }
    A2 && operator[] (boost::arg<2>) const { return std::forward<A2>( a2_ ); }
    A3 && operator[] (boost::arg<3>) const { return std::forward<A3>( a3_ ); }
    A4 && operator[] (boost::arg<4>) const { return std::forward<A4>( a4_ ); }

    A1 && operator[] (boost::arg<1> (*) ()) const { return std::forward<A1>( a1_ ); }
    A2 && operator[] (boost::arg<2> (*) ()) const { return std::forward<A2>( a2_ ); }
    A3 && operator[] (boost::arg<3> (*) ()) const { return std::forward<A3>( a3_ ); }
    A4 && operator[] (boost::arg<4> (*) ()) const { return std::forward<A4>( a4_ ); }

    template<class T> T & operator[] ( _bi::value<T> & v ) const { return v.get(); }

    template<class T> T const & operator[] ( _bi::value<T> const & v ) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const
    {
        rrlist4<A1&, A2&, A3&, A4&> a( a1_, a2_, a3_, a4_ );
        return b.eval( a );
    }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const
    {
        rrlist4<A1&, A2&, A3&, A4&> a( a1_, a2_, a3_, a4_ );
        return b.eval( a );
    }
};

template< class A1, class A2, class A3, class A4, class A5 > class rrlist5
{
private:

    A1 & a1_;
    A2 & a2_;
    A3 & a3_;
    A4 & a4_;
    A5 & a5_;

public:

    rrlist5( A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5 ): a1_( a1 ), a2_( a2 ), a3_( a3 ), a4_( a4 ), a5_( a5 ) {}

    A1 && operator[] (boost::arg<1>) const { return std::forward<A1>( a1_ ); }
    A2 && operator[] (boost::arg<2>) const { return std::forward<A2>( a2_ ); }
    A3 && operator[] (boost::arg<3>) const { return std::forward<A3>( a3_ ); }
    A4 && operator[] (boost::arg<4>) const { return std::forward<A4>( a4_ ); }
    A5 && operator[] (boost::arg<5>) const { return std::forward<A5>( a5_ ); }

    A1 && operator[] (boost::arg<1> (*) ()) const { return std::forward<A1>( a1_ ); }
    A2 && operator[] (boost::arg<2> (*) ()) const { return std::forward<A2>( a2_ ); }
    A3 && operator[] (boost::arg<3> (*) ()) const { return std::forward<A3>( a3_ ); }
    A4 && operator[] (boost::arg<4> (*) ()) const { return std::forward<A4>( a4_ ); }
    A5 && operator[] (boost::arg<5> (*) ()) const { return std::forward<A5>( a5_ ); }

    template<class T> T & operator[] ( _bi::value<T> & v ) const { return v.get(); }

    template<class T> T const & operator[] ( _bi::value<T> const & v ) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const
    {
        rrlist5<A1&, A2&, A3&, A4&, A5&> a( a1_, a2_, a3_, a4_, a5_ );
        return b.eval( a );
    }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const
    {
        rrlist5<A1&, A2&, A3&, A4&, A5&> a( a1_, a2_, a3_, a4_, a5_ );
        return b.eval( a );
    }
};

template< class A1, class A2, class A3, class A4, class A5, class A6 > class rrlist6
{
private:

    A1 & a1_;
    A2 & a2_;
    A3 & a3_;
    A4 & a4_;
    A5 & a5_;
    A6 & a6_;

public:

    rrlist6( A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6 ): a1_( a1 ), a2_( a2 ), a3_( a3 ), a4_( a4 ), a5_( a5 ), a6_( a6 ) {}

    A1 && operator[] (boost::arg<1>) const { return std::forward<A1>( a1_ ); }
    A2 && operator[] (boost::arg<2>) const { return std::forward<A2>( a2_ ); }
    A3 && operator[] (boost::arg<3>) const { return std::forward<A3>( a3_ ); }
    A4 && operator[] (boost::arg<4>) const { return std::forward<A4>( a4_ ); }
    A5 && operator[] (boost::arg<5>) const { return std::forward<A5>( a5_ ); }
    A6 && operator[] (boost::arg<6>) const { return std::forward<A6>( a6_ ); }

    A1 && operator[] (boost::arg<1> (*) ()) const { return std::forward<A1>( a1_ ); }
    A2 && operator[] (boost::arg<2> (*) ()) const { return std::forward<A2>( a2_ ); }
    A3 && operator[] (boost::arg<3> (*) ()) const { return std::forward<A3>( a3_ ); }
    A4 && operator[] (boost::arg<4> (*) ()) const { return std::forward<A4>( a4_ ); }
    A5 && operator[] (boost::arg<5> (*) ()) const { return std::forward<A5>( a5_ ); }
    A6 && operator[] (boost::arg<6> (*) ()) const { return std::forward<A6>( a6_ ); }

    template<class T> T & operator[] ( _bi::value<T> & v ) const { return v.get(); }

    template<class T> T const & operator[] ( _bi::value<T> const & v ) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const
    {
        rrlist6<A1&, A2&, A3&, A4&, A5&, A6&> a( a1_, a2_, a3_, a4_, a5_, a6_ );
        return b.eval( a );
    }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const
    {
        rrlist6<A1&, A2&, A3&, A4&, A5&, A6&> a( a1_, a2_, a3_, a4_, a5_, a6_ );
        return b.eval( a );
    }
};

template< class A1, class A2, class A3, class A4, class A5, class A6, class A7 > class rrlist7
{
private:

    A1 & a1_;
    A2 & a2_;
    A3 & a3_;
    A4 & a4_;
    A5 & a5_;
    A6 & a6_;
    A7 & a7_;

public:

    rrlist7( A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7 ): a1_( a1 ), a2_( a2 ), a3_( a3 ), a4_( a4 ), a5_( a5 ), a6_( a6 ), a7_( a7 ) {}

    A1 && operator[] (boost::arg<1>) const { return std::forward<A1>( a1_ ); }
    A2 && operator[] (boost::arg<2>) const { return std::forward<A2>( a2_ ); }
    A3 && operator[] (boost::arg<3>) const { return std::forward<A3>( a3_ ); }
    A4 && operator[] (boost::arg<4>) const { return std::forward<A4>( a4_ ); }
    A5 && operator[] (boost::arg<5>) const { return std::forward<A5>( a5_ ); }
    A6 && operator[] (boost::arg<6>) const { return std::forward<A6>( a6_ ); }
    A7 && operator[] (boost::arg<7>) const { return std::forward<A7>( a7_ ); }

    A1 && operator[] (boost::arg<1> (*) ()) const { return std::forward<A1>( a1_ ); }
    A2 && operator[] (boost::arg<2> (*) ()) const { return std::forward<A2>( a2_ ); }
    A3 && operator[] (boost::arg<3> (*) ()) const { return std::forward<A3>( a3_ ); }
    A4 && operator[] (boost::arg<4> (*) ()) const { return std::forward<A4>( a4_ ); }
    A5 && operator[] (boost::arg<5> (*) ()) const { return std::forward<A5>( a5_ ); }
    A6 && operator[] (boost::arg<6> (*) ()) const { return std::forward<A6>( a6_ ); }
    A7 && operator[] (boost::arg<7> (*) ()) const { return std::forward<A7>( a7_ ); }

    template<class T> T & operator[] ( _bi::value<T> & v ) const { return v.get(); }

    template<class T> T const & operator[] ( _bi::value<T> const & v ) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const
    {
        rrlist7<A1&, A2&, A3&, A4&, A5&, A6&, A7&> a( a1_, a2_, a3_, a4_, a5_, a6_, a7_ );
        return b.eval( a );
    }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const
    {
        rrlist7<A1&, A2&, A3&, A4&, A5&, A6&, A7&> a( a1_, a2_, a3_, a4_, a5_, a6_, a7_ );
        return b.eval( a );
    }
};

template< class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8 > class rrlist8
{
private:

    A1 & a1_;
    A2 & a2_;
    A3 & a3_;
    A4 & a4_;
    A5 & a5_;
    A6 & a6_;
    A7 & a7_;
    A8 & a8_;

public:

    rrlist8( A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8 ): a1_( a1 ), a2_( a2 ), a3_( a3 ), a4_( a4 ), a5_( a5 ), a6_( a6 ), a7_( a7 ), a8_( a8 ) {}

    A1 && operator[] (boost::arg<1>) const { return std::forward<A1>( a1_ ); }
    A2 && operator[] (boost::arg<2>) const { return std::forward<A2>( a2_ ); }
    A3 && operator[] (boost::arg<3>) const { return std::forward<A3>( a3_ ); }
    A4 && operator[] (boost::arg<4>) const { return std::forward<A4>( a4_ ); }
    A5 && operator[] (boost::arg<5>) const { return std::forward<A5>( a5_ ); }
    A6 && operator[] (boost::arg<6>) const { return std::forward<A6>( a6_ ); }
    A7 && operator[] (boost::arg<7>) const { return std::forward<A7>( a7_ ); }
    A8 && operator[] (boost::arg<8>) const { return std::forward<A8>( a8_ ); }

    A1 && operator[] (boost::arg<1> (*) ()) const { return std::forward<A1>( a1_ ); }
    A2 && operator[] (boost::arg<2> (*) ()) const { return std::forward<A2>( a2_ ); }
    A3 && operator[] (boost::arg<3> (*) ()) const { return std::forward<A3>( a3_ ); }
    A4 && operator[] (boost::arg<4> (*) ()) const { return std::forward<A4>( a4_ ); }
    A5 && operator[] (boost::arg<5> (*) ()) const { return std::forward<A5>( a5_ ); }
    A6 && operator[] (boost::arg<6> (*) ()) const { return std::forward<A6>( a6_ ); }
    A7 && operator[] (boost::arg<7> (*) ()) const { return std::forward<A7>( a7_ ); }
    A8 && operator[] (boost::arg<8> (*) ()) const { return std::forward<A8>( a8_ ); }

    template<class T> T & operator[] ( _bi::value<T> & v ) const { return v.get(); }

    template<class T> T const & operator[] ( _bi::value<T> const & v ) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const
    {
        rrlist8<A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8&> a( a1_, a2_, a3_, a4_, a5_, a6_, a7_, a8_ );
        return b.eval( a );
    }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const
    {
        rrlist8<A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8&> a( a1_, a2_, a3_, a4_, a5_, a6_, a7_, a8_ );
        return b.eval( a );
    }
};

template< class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9 > class rrlist9
{
private:

    A1 & a1_;
    A2 & a2_;
    A3 & a3_;
    A4 & a4_;
    A5 & a5_;
    A6 & a6_;
    A7 & a7_;
    A8 & a8_;
    A9 & a9_;

public:

    rrlist9( A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8, A9 & a9 ): a1_( a1 ), a2_( a2 ), a3_( a3 ), a4_( a4 ), a5_( a5 ), a6_( a6 ), a7_( a7 ), a8_( a8 ), a9_( a9 ) {}

    A1 && operator[] (boost::arg<1>) const { return std::forward<A1>( a1_ ); }
    A2 && operator[] (boost::arg<2>) const { return std::forward<A2>( a2_ ); }
    A3 && operator[] (boost::arg<3>) const { return std::forward<A3>( a3_ ); }
    A4 && operator[] (boost::arg<4>) const { return std::forward<A4>( a4_ ); }
    A5 && operator[] (boost::arg<5>) const { return std::forward<A5>( a5_ ); }
    A6 && operator[] (boost::arg<6>) const { return std::forward<A6>( a6_ ); }
    A7 && operator[] (boost::arg<7>) const { return std::forward<A7>( a7_ ); }
    A8 && operator[] (boost::arg<8>) const { return std::forward<A8>( a8_ ); }
    A9 && operator[] (boost::arg<9>) const { return std::forward<A9>( a9_ ); }

    A1 && operator[] (boost::arg<1> (*) ()) const { return std::forward<A1>( a1_ ); }
    A2 && operator[] (boost::arg<2> (*) ()) const { return std::forward<A2>( a2_ ); }
    A3 && operator[] (boost::arg<3> (*) ()) const { return std::forward<A3>( a3_ ); }
    A4 && operator[] (boost::arg<4> (*) ()) const { return std::forward<A4>( a4_ ); }
    A5 && operator[] (boost::arg<5> (*) ()) const { return std::forward<A5>( a5_ ); }
    A6 && operator[] (boost::arg<6> (*) ()) const { return std::forward<A6>( a6_ ); }
    A7 && operator[] (boost::arg<7> (*) ()) const { return std::forward<A7>( a7_ ); }
    A8 && operator[] (boost::arg<8> (*) ()) const { return std::forward<A8>( a8_ ); }
    A9 && operator[] (boost::arg<9> (*) ()) const { return std::forward<A9>( a9_ ); }

    template<class T> T & operator[] ( _bi::value<T> & v ) const { return v.get(); }

    template<class T> T const & operator[] ( _bi::value<T> const & v ) const { return v.get(); }

    template<class T> T & operator[] (reference_wrapper<T> const & v) const { return v.get(); }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const
    {
        rrlist9<A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8&, A9&> a( a1_, a2_, a3_, a4_, a5_, a6_, a7_, a8_, a9_ );
        return b.eval( a );
    }

    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const
    {
        rrlist9<A1&, A2&, A3&, A4&, A5&, A6&, A7&, A8&, A9&> a( a1_, a2_, a3_, a4_, a5_, a6_, a7_, a8_, a9_ );
        return b.eval( a );
    }
};

template<class R, class F, class L> class bind_t
{
private:

    F f_;
    L l_;

public:

    typedef typename result_traits<R, F>::type result_type;
    typedef bind_t this_type;

    bind_t( F f, L const & l ): f_( f ), l_( l ) {}

    //

    result_type operator()()
    {
        list0 a;
        return l_( type<result_type>(), f_, a, 0 );
    }

    result_type operator()() const
    {
        list0 a;
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class A1> result_type operator()( A1 && a1 )
    {
        rrlist1< A1 > a( a1 );
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class A1> result_type operator()( A1 && a1 ) const
    {
        rrlist1< A1 > a( a1 );
        return l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2> result_type operator()( A1 && a1, A2 && a2 )
    {
        rrlist2< A1, A2 > a( a1, a2 );
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class A1, class A2> result_type operator()( A1 && a1, A2 && a2 ) const
    {
        rrlist2< A1, A2 > a( a1, a2 );
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class A1, class A2, class A3> result_type operator()( A1 && a1, A2 && a2, A3 && a3 )
    {
        rrlist3< A1, A2, A3 > a( a1, a2, a3 );
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class A1, class A2, class A3> result_type operator()( A1 && a1, A2 && a2, A3 && a3 ) const
    {
        rrlist3< A1, A2, A3 > a( a1, a2, a3 );
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class A1, class A2, class A3, class A4> result_type operator()( A1 && a1, A2 && a2, A3 && a3, A4 && a4 )
    {
        rrlist4< A1, A2, A3, A4 > a( a1, a2, a3, a4 );
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class A1, class A2, class A3, class A4> result_type operator()( A1 && a1, A2 && a2, A3 && a3, A4 && a4 ) const
    {
        rrlist4< A1, A2, A3, A4 > a( a1, a2, a3, a4 );
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class A1, class A2, class A3, class A4, class A5> result_type operator()( A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5 )
    {
        rrlist5< A1, A2, A3, A4, A5 > a( a1, a2, a3, a4, a5 );
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class A1, class A2, class A3, class A4, class A5> result_type operator()( A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5 ) const
    {
        rrlist5< A1, A2, A3, A4, A5 > a( a1, a2, a3, a4, a5 );
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6> result_type operator()( A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5, A6 && a6 )
    {
        rrlist6< A1, A2, A3, A4, A5, A6 > a( a1, a2, a3, a4, a5, a6 );
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6> result_type operator()( A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5, A6 && a6 ) const
    {
        rrlist6< A1, A2, A3, A4, A5, A6 > a( a1, a2, a3, a4, a5, a6 );
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> result_type operator()( A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5, A6 && a6, A7 && a7 )
    {
        rrlist7< A1, A2, A3, A4, A5, A6, A7 > a( a1, a2, a3, a4, a5, a6, a7 );
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> result_type operator()( A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5, A6 && a6, A7 && a7 ) const
    {
        rrlist7< A1, A2, A3, A4, A5, A6, A7 > a( a1, a2, a3, a4, a5, a6, a7 );
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> result_type operator()( A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5, A6 && a6, A7 && a7, A8 && a8 )
    {
        rrlist8< A1, A2, A3, A4, A5, A6, A7, A8 > a( a1, a2, a3, a4, a5, a6, a7, a8 );
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> result_type operator()( A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5, A6 && a6, A7 && a7, A8 && a8 ) const
    {
        rrlist8< A1, A2, A3, A4, A5, A6, A7, A8 > a( a1, a2, a3, a4, a5, a6, a7, a8 );
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> result_type operator()( A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5, A6 && a6, A7 && a7, A8 && a8, A9 && a9 )
    {
        rrlist9< A1, A2, A3, A4, A5, A6, A7, A8, A9 > a( a1, a2, a3, a4, a5, a6, a7, a8, a9 );
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> result_type operator()( A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5, A6 && a6, A7 && a7, A8 && a8, A9 && a9 ) const
    {
        rrlist9< A1, A2, A3, A4, A5, A6, A7, A8, A9 > a( a1, a2, a3, a4, a5, a6, a7, a8, a9 );
        return l_( type<result_type>(), f_, a, 0 );
    }

    //

    template<class A> result_type eval( A & a )
    {
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class A> result_type eval( A & a ) const
    {
        return l_( type<result_type>(), f_, a, 0 );
    }

    template<class V> void accept( V & v ) const
    {
#if !defined( BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP ) && !defined( __BORLANDC__ )
        using boost::visit_each;
#endif

        BOOST_BIND_VISIT_EACH( v, f_, 0 );
        l_.accept( v );
    }

    bool compare( this_type const & rhs ) const
    {
        return ref_compare( f_, rhs.f_, 0 ) && l_ == rhs.l_;
    }
};

#elif !defined( BOOST_NO_VOID_RETURNS )

template<class R, class F, class L> class bind_t
{
public:

    typedef bind_t this_type;

    bind_t(F f, L const & l): f_(f), l_(l) {}

#define BOOST_BIND_RETURN return
#include <boost/bind/bind_template.hpp>
#undef BOOST_BIND_RETURN

};

#else // no void returns

template<class R> struct bind_t_generator
{

template<class F, class L> class implementation
{
public:

    typedef implementation this_type;

    implementation(F f, L const & l): f_(f), l_(l) {}

#define BOOST_BIND_RETURN return
#include <boost/bind/bind_template.hpp>
#undef BOOST_BIND_RETURN

};

};

template<> struct bind_t_generator<void>
{

template<class F, class L> class implementation
{
private:

    typedef void R;

public:

    typedef implementation this_type;

    implementation(F f, L const & l): f_(f), l_(l) {}

#define BOOST_BIND_RETURN
#include <boost/bind/bind_template.hpp>
#undef BOOST_BIND_RETURN

};

};

template<class R2, class F, class L> class bind_t: public bind_t_generator<R2>::BOOST_NESTED_TEMPLATE implementation<F, L>
{
public:

    bind_t(F f, L const & l): bind_t_generator<R2>::BOOST_NESTED_TEMPLATE implementation<F, L>(f, l) {}

};

#endif

// function_equal

#ifndef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP

// put overloads in _bi, rely on ADL

# ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING

template<class R, class F, class L> bool function_equal( bind_t<R, F, L> const & a, bind_t<R, F, L> const & b )
{
    return a.compare(b);
}

# else

template<class R, class F, class L> bool function_equal_impl( bind_t<R, F, L> const & a, bind_t<R, F, L> const & b, int )
{
    return a.compare(b);
}

# endif // #ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING

#else // BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP

// put overloads in boost

} // namespace _bi

# ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING

template<class R, class F, class L> bool function_equal( _bi::bind_t<R, F, L> const & a, _bi::bind_t<R, F, L> const & b )
{
    return a.compare(b);
}

# else

template<class R, class F, class L> bool function_equal_impl( _bi::bind_t<R, F, L> const & a, _bi::bind_t<R, F, L> const & b, int )
{
    return a.compare(b);
}

# endif // #ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING

namespace _bi
{

#endif // BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP

// add_value

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) || (__SUNPRO_CC >= 0x530)

#if defined( __BORLANDC__ ) && BOOST_WORKAROUND( __BORLANDC__, BOOST_TESTED_AT(0x582) )

template<class T> struct add_value
{
    typedef _bi::value<T> type;
};

#else

template< class T, int I > struct add_value_2
{
    typedef boost::arg<I> type;
};

template< class T > struct add_value_2< T, 0 >
{
    typedef _bi::value< T > type;
};

template<class T> struct add_value
{
    typedef typename add_value_2< T, boost::is_placeholder< T >::value >::type type;
};

#endif

template<class T> struct add_value< value<T> >
{
    typedef _bi::value<T> type;
};

template<class T> struct add_value< reference_wrapper<T> >
{
    typedef reference_wrapper<T> type;
};

template<int I> struct add_value< arg<I> >
{
    typedef boost::arg<I> type;
};

template<int I> struct add_value< arg<I> (*) () >
{
    typedef boost::arg<I> (*type) ();
};

template<class R, class F, class L> struct add_value< bind_t<R, F, L> >
{
    typedef bind_t<R, F, L> type;
};

#else

template<int I> struct _avt_0;

template<> struct _avt_0<1>
{
    template<class T> struct inner
    {
        typedef T type;
    };
};

template<> struct _avt_0<2>
{
    template<class T> struct inner
    {
        typedef value<T> type;
    };
};

typedef char (&_avt_r1) [1];
typedef char (&_avt_r2) [2];

template<class T> _avt_r1 _avt_f(value<T>);
template<class T> _avt_r1 _avt_f(reference_wrapper<T>);
template<int I> _avt_r1 _avt_f(arg<I>);
template<int I> _avt_r1 _avt_f(arg<I> (*) ());
template<class R, class F, class L> _avt_r1 _avt_f(bind_t<R, F, L>);

_avt_r2 _avt_f(...);

template<class T> struct add_value
{
    static T t();
    typedef typename _avt_0<sizeof(_avt_f(t()))>::template inner<T>::type type;
};

#endif

// list_av_N

template<class A1> struct list_av_1
{
    typedef typename add_value<A1>::type B1;
    typedef list1<B1> type;
};

template<class A1, class A2> struct list_av_2
{
    typedef typename add_value<A1>::type B1;
    typedef typename add_value<A2>::type B2;
    typedef list2<B1, B2> type;
};

template<class A1, class A2, class A3> struct list_av_3
{
    typedef typename add_value<A1>::type B1;
    typedef typename add_value<A2>::type B2;
    typedef typename add_value<A3>::type B3;
    typedef list3<B1, B2, B3> type;
};

template<class A1, class A2, class A3, class A4> struct list_av_4
{
    typedef typename add_value<A1>::type B1;
    typedef typename add_value<A2>::type B2;
    typedef typename add_value<A3>::type B3;
    typedef typename add_value<A4>::type B4;
    typedef list4<B1, B2, B3, B4> type;
};

template<class A1, class A2, class A3, class A4, class A5> struct list_av_5
{
    typedef typename add_value<A1>::type B1;
    typedef typename add_value<A2>::type B2;
    typedef typename add_value<A3>::type B3;
    typedef typename add_value<A4>::type B4;
    typedef typename add_value<A5>::type B5;
    typedef list5<B1, B2, B3, B4, B5> type;
};

template<class A1, class A2, class A3, class A4, class A5, class A6> struct list_av_6
{
    typedef typename add_value<A1>::type B1;
    typedef typename add_value<A2>::type B2;
    typedef typename add_value<A3>::type B3;
    typedef typename add_value<A4>::type B4;
    typedef typename add_value<A5>::type B5;
    typedef typename add_value<A6>::type B6;
    typedef list6<B1, B2, B3, B4, B5, B6> type;
};

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> struct list_av_7
{
    typedef typename add_value<A1>::type B1;
    typedef typename add_value<A2>::type B2;
    typedef typename add_value<A3>::type B3;
    typedef typename add_value<A4>::type B4;
    typedef typename add_value<A5>::type B5;
    typedef typename add_value<A6>::type B6;
    typedef typename add_value<A7>::type B7;
    typedef list7<B1, B2, B3, B4, B5, B6, B7> type;
};

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> struct list_av_8
{
    typedef typename add_value<A1>::type B1;
    typedef typename add_value<A2>::type B2;
    typedef typename add_value<A3>::type B3;
    typedef typename add_value<A4>::type B4;
    typedef typename add_value<A5>::type B5;
    typedef typename add_value<A6>::type B6;
    typedef typename add_value<A7>::type B7;
    typedef typename add_value<A8>::type B8;
    typedef list8<B1, B2, B3, B4, B5, B6, B7, B8> type;
};

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> struct list_av_9
{
    typedef typename add_value<A1>::type B1;
    typedef typename add_value<A2>::type B2;
    typedef typename add_value<A3>::type B3;
    typedef typename add_value<A4>::type B4;
    typedef typename add_value<A5>::type B5;
    typedef typename add_value<A6>::type B6;
    typedef typename add_value<A7>::type B7;
    typedef typename add_value<A8>::type B8;
    typedef typename add_value<A9>::type B9;
    typedef list9<B1, B2, B3, B4, B5, B6, B7, B8, B9> type;
};

// operator!

struct logical_not
{
    template<class V> bool operator()(V const & v) const { return !v; }
};

template<class R, class F, class L>
    bind_t< bool, logical_not, list1< bind_t<R, F, L> > >
    operator! (bind_t<R, F, L> const & f)
{
    typedef list1< bind_t<R, F, L> > list_type;
    return bind_t<bool, logical_not, list_type> ( logical_not(), list_type(f) );
}

// relational operators

#define BOOST_BIND_OPERATOR( op, name ) \
\
struct name \
{ \
    template<class V, class W> bool operator()(V const & v, W const & w) const { return v op w; } \
}; \
 \
template<class R, class F, class L, class A2> \
    bind_t< bool, name, list2< bind_t<R, F, L>, typename add_value<A2>::type > > \
    operator op (bind_t<R, F, L> const & f, A2 a2) \
{ \
    typedef typename add_value<A2>::type B2; \
    typedef list2< bind_t<R, F, L>, B2> list_type; \
    return bind_t<bool, name, list_type> ( name(), list_type(f, a2) ); \
}

BOOST_BIND_OPERATOR( ==, equal )
BOOST_BIND_OPERATOR( !=, not_equal )

BOOST_BIND_OPERATOR( <, less )
BOOST_BIND_OPERATOR( <=, less_equal )

BOOST_BIND_OPERATOR( >, greater )
BOOST_BIND_OPERATOR( >=, greater_equal )

BOOST_BIND_OPERATOR( &&, logical_and )
BOOST_BIND_OPERATOR( ||, logical_or )

#undef BOOST_BIND_OPERATOR

#if defined(__GNUC__) && BOOST_WORKAROUND(__GNUC__, < 3)

// resolve ambiguity with rel_ops

#define BOOST_BIND_OPERATOR( op, name ) \
\
template<class R, class F, class L> \
    bind_t< bool, name, list2< bind_t<R, F, L>, bind_t<R, F, L> > > \
    operator op (bind_t<R, F, L> const & f, bind_t<R, F, L> const & g) \
{ \
    typedef list2< bind_t<R, F, L>, bind_t<R, F, L> > list_type; \
    return bind_t<bool, name, list_type> ( name(), list_type(f, g) ); \
}

BOOST_BIND_OPERATOR( !=, not_equal )
BOOST_BIND_OPERATOR( <=, less_equal )
BOOST_BIND_OPERATOR( >, greater )
BOOST_BIND_OPERATOR( >=, greater_equal )

#endif

// visit_each, ADL

#if !defined( BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP ) && !defined( __BORLANDC__ ) \
   && !(defined(__GNUC__) && __GNUC__ == 3 && __GNUC_MINOR__ <= 3)

template<class V, class T> void visit_each( V & v, value<T> const & t, int )
{
    using boost::visit_each;
    BOOST_BIND_VISIT_EACH( v, t.get(), 0 );
}

template<class V, class R, class F, class L> void visit_each( V & v, bind_t<R, F, L> const & t, int )
{
    t.accept( v );
}

#endif

} // namespace _bi

// visit_each, no ADL

#if defined( BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP ) || defined( __BORLANDC__ ) \
  || (defined(__GNUC__) && __GNUC__ == 3 && __GNUC_MINOR__ <= 3)

template<class V, class T> void visit_each( V & v, _bi::value<T> const & t, int )
{
    BOOST_BIND_VISIT_EACH( v, t.get(), 0 );
}

template<class V, class R, class F, class L> void visit_each( V & v, _bi::bind_t<R, F, L> const & t, int )
{
    t.accept( v );
}

#endif

// is_bind_expression

template< class T > struct is_bind_expression
{
    enum _vt { value = 0 };
};

#if !defined( BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION )

template< class R, class F, class L > struct is_bind_expression< _bi::bind_t< R, F, L > >
{
    enum _vt { value = 1 };
};

#endif

// bind

#ifndef BOOST_BIND
#define BOOST_BIND bind
#endif

// generic function objects

template<class R, class F>
    _bi::bind_t<R, F, _bi::list0>
    BOOST_BIND(F f)
{
    typedef _bi::list0 list_type;
    return _bi::bind_t<R, F, list_type> (f, list_type());
}

template<class R, class F, class A1>
    _bi::bind_t<R, F, typename _bi::list_av_1<A1>::type>
    BOOST_BIND(F f, A1 a1)
{
    typedef typename _bi::list_av_1<A1>::type list_type;
    return _bi::bind_t<R, F, list_type> (f, list_type(a1));
}

template<class R, class F, class A1, class A2>
    _bi::bind_t<R, F, typename _bi::list_av_2<A1, A2>::type>
    BOOST_BIND(F f, A1 a1, A2 a2)
{
    typedef typename _bi::list_av_2<A1, A2>::type list_type;
    return _bi::bind_t<R, F, list_type> (f, list_type(a1, a2));
}

template<class R, class F, class A1, class A2, class A3>
    _bi::bind_t<R, F, typename _bi::list_av_3<A1, A2, A3>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3)
{
    typedef typename _bi::list_av_3<A1, A2, A3>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3));
}

template<class R, class F, class A1, class A2, class A3, class A4>
    _bi::bind_t<R, F, typename _bi::list_av_4<A1, A2, A3, A4>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4)
{
    typedef typename _bi::list_av_4<A1, A2, A3, A4>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4));
}

template<class R, class F, class A1, class A2, class A3, class A4, class A5>
    _bi::bind_t<R, F, typename _bi::list_av_5<A1, A2, A3, A4, A5>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
    typedef typename _bi::list_av_5<A1, A2, A3, A4, A5>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5));
}

template<class R, class F, class A1, class A2, class A3, class A4, class A5, class A6>
    _bi::bind_t<R, F, typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
    typedef typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6));
}

template<class R, class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    _bi::bind_t<R, F, typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
    typedef typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7));
}

template<class R, class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    _bi::bind_t<R, F, typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
    typedef typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7, a8));
}

template<class R, class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    _bi::bind_t<R, F, typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{
    typedef typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

// generic function objects, alternative syntax

template<class R, class F>
    _bi::bind_t<R, F, _bi::list0>
    BOOST_BIND(boost::type<R>, F f)
{
    typedef _bi::list0 list_type;
    return _bi::bind_t<R, F, list_type> (f, list_type());
}

template<class R, class F, class A1>
    _bi::bind_t<R, F, typename _bi::list_av_1<A1>::type>
    BOOST_BIND(boost::type<R>, F f, A1 a1)
{
    typedef typename _bi::list_av_1<A1>::type list_type;
    return _bi::bind_t<R, F, list_type> (f, list_type(a1));
}

template<class R, class F, class A1, class A2>
    _bi::bind_t<R, F, typename _bi::list_av_2<A1, A2>::type>
    BOOST_BIND(boost::type<R>, F f, A1 a1, A2 a2)
{
    typedef typename _bi::list_av_2<A1, A2>::type list_type;
    return _bi::bind_t<R, F, list_type> (f, list_type(a1, a2));
}

template<class R, class F, class A1, class A2, class A3>
    _bi::bind_t<R, F, typename _bi::list_av_3<A1, A2, A3>::type>
    BOOST_BIND(boost::type<R>, F f, A1 a1, A2 a2, A3 a3)
{
    typedef typename _bi::list_av_3<A1, A2, A3>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3));
}

template<class R, class F, class A1, class A2, class A3, class A4>
    _bi::bind_t<R, F, typename _bi::list_av_4<A1, A2, A3, A4>::type>
    BOOST_BIND(boost::type<R>, F f, A1 a1, A2 a2, A3 a3, A4 a4)
{
    typedef typename _bi::list_av_4<A1, A2, A3, A4>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4));
}

template<class R, class F, class A1, class A2, class A3, class A4, class A5>
    _bi::bind_t<R, F, typename _bi::list_av_5<A1, A2, A3, A4, A5>::type>
    BOOST_BIND(boost::type<R>, F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
    typedef typename _bi::list_av_5<A1, A2, A3, A4, A5>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5));
}

template<class R, class F, class A1, class A2, class A3, class A4, class A5, class A6>
    _bi::bind_t<R, F, typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type>
    BOOST_BIND(boost::type<R>, F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
    typedef typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6));
}

template<class R, class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    _bi::bind_t<R, F, typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type>
    BOOST_BIND(boost::type<R>, F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
    typedef typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7));
}

template<class R, class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    _bi::bind_t<R, F, typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type>
    BOOST_BIND(boost::type<R>, F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
    typedef typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7, a8));
}

template<class R, class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    _bi::bind_t<R, F, typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type>
    BOOST_BIND(boost::type<R>, F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{
    typedef typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)

// adaptable function objects

template<class F>
    _bi::bind_t<_bi::unspecified, F, _bi::list0>
    BOOST_BIND(F f)
{
    typedef _bi::list0 list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type> (f, list_type());
}

template<class F, class A1>
    _bi::bind_t<_bi::unspecified, F, typename _bi::list_av_1<A1>::type>
    BOOST_BIND(F f, A1 a1)
{
    typedef typename _bi::list_av_1<A1>::type list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type> (f, list_type(a1));
}

template<class F, class A1, class A2>
    _bi::bind_t<_bi::unspecified, F, typename _bi::list_av_2<A1, A2>::type>
    BOOST_BIND(F f, A1 a1, A2 a2)
{
    typedef typename _bi::list_av_2<A1, A2>::type list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type> (f, list_type(a1, a2));
}

template<class F, class A1, class A2, class A3>
    _bi::bind_t<_bi::unspecified, F, typename _bi::list_av_3<A1, A2, A3>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3)
{
    typedef typename _bi::list_av_3<A1, A2, A3>::type list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3));
}

template<class F, class A1, class A2, class A3, class A4>
    _bi::bind_t<_bi::unspecified, F, typename _bi::list_av_4<A1, A2, A3, A4>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4)
{
    typedef typename _bi::list_av_4<A1, A2, A3, A4>::type list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3, a4));
}

template<class F, class A1, class A2, class A3, class A4, class A5>
    _bi::bind_t<_bi::unspecified, F, typename _bi::list_av_5<A1, A2, A3, A4, A5>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
    typedef typename _bi::list_av_5<A1, A2, A3, A4, A5>::type list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3, a4, a5));
}

template<class F, class A1, class A2, class A3, class A4, class A5, class A6>
    _bi::bind_t<_bi::unspecified, F, typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
    typedef typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6));
}

template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    _bi::bind_t<_bi::unspecified, F, typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
    typedef typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7));
}

template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    _bi::bind_t<_bi::unspecified, F, typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
    typedef typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7, a8));
}

template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    _bi::bind_t<_bi::unspecified, F, typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{
    typedef typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

#endif // !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)

// function pointers

#define BOOST_BIND_CC
#define BOOST_BIND_ST
#define BOOST_BIND_NOEXCEPT

#include <boost/bind/bind_cc.hpp>

# if defined( __cpp_noexcept_function_type ) || defined( _NOEXCEPT_TYPES_SUPPORTED )
#   undef BOOST_BIND_NOEXCEPT
#   define BOOST_BIND_NOEXCEPT noexcept
#   include <boost/bind/bind_cc.hpp>
# endif

#undef BOOST_BIND_CC
#undef BOOST_BIND_ST
#undef BOOST_BIND_NOEXCEPT

#if defined(BOOST_BIND_ENABLE_STDCALL) && !defined(_M_X64)

#define BOOST_BIND_CC __stdcall
#define BOOST_BIND_ST
#define BOOST_BIND_NOEXCEPT

#include <boost/bind/bind_cc.hpp>

#undef BOOST_BIND_CC
#undef BOOST_BIND_ST
#undef BOOST_BIND_NOEXCEPT

#endif

#if defined(BOOST_BIND_ENABLE_FASTCALL) && !defined(_M_X64)

#define BOOST_BIND_CC __fastcall
#define BOOST_BIND_ST
#define BOOST_BIND_NOEXCEPT

#include <boost/bind/bind_cc.hpp>

#undef BOOST_BIND_CC
#undef BOOST_BIND_ST
#undef BOOST_BIND_NOEXCEPT

#endif

#ifdef BOOST_BIND_ENABLE_PASCAL

#define BOOST_BIND_ST pascal
#define BOOST_BIND_CC
#define BOOST_BIND_NOEXCEPT

#include <boost/bind/bind_cc.hpp>

#undef BOOST_BIND_ST
#undef BOOST_BIND_CC
#undef BOOST_BIND_NOEXCEPT

#endif

// member function pointers

#define BOOST_BIND_MF_NAME(X) X
#define BOOST_BIND_MF_CC
#define BOOST_BIND_MF_NOEXCEPT

#include <boost/bind/bind_mf_cc.hpp>
#include <boost/bind/bind_mf2_cc.hpp>

# if defined( __cpp_noexcept_function_type ) || defined( _NOEXCEPT_TYPES_SUPPORTED )
#   undef BOOST_BIND_MF_NOEXCEPT
#   define BOOST_BIND_MF_NOEXCEPT noexcept
#   include <boost/bind/bind_mf_cc.hpp>
# endif

#undef BOOST_BIND_MF_NAME
#undef BOOST_BIND_MF_CC
#undef BOOST_BIND_MF_NOEXCEPT

#if defined(BOOST_MEM_FN_ENABLE_CDECL) && !defined(_M_X64)

#define BOOST_BIND_MF_NAME(X) X##_cdecl
#define BOOST_BIND_MF_CC __cdecl
#define BOOST_BIND_MF_NOEXCEPT

#include <boost/bind/bind_mf_cc.hpp>
#include <boost/bind/bind_mf2_cc.hpp>

#undef BOOST_BIND_MF_NAME
#undef BOOST_BIND_MF_CC
#undef BOOST_BIND_MF_NOEXCEPT

#endif

#if defined(BOOST_MEM_FN_ENABLE_STDCALL) && !defined(_M_X64)

#define BOOST_BIND_MF_NAME(X) X##_stdcall
#define BOOST_BIND_MF_CC __stdcall
#define BOOST_BIND_MF_NOEXCEPT

#include <boost/bind/bind_mf_cc.hpp>
#include <boost/bind/bind_mf2_cc.hpp>

#undef BOOST_BIND_MF_NAME
#undef BOOST_BIND_MF_CC
#undef BOOST_BIND_MF_NOEXCEPT

#endif

#if defined(BOOST_MEM_FN_ENABLE_FASTCALL) && !defined(_M_X64)

#define BOOST_BIND_MF_NAME(X) X##_fastcall
#define BOOST_BIND_MF_CC __fastcall
#define BOOST_BIND_MF_NOEXCEPT

#include <boost/bind/bind_mf_cc.hpp>
#include <boost/bind/bind_mf2_cc.hpp>

#undef BOOST_BIND_MF_NAME
#undef BOOST_BIND_MF_CC
#undef BOOST_BIND_MF_NOEXCEPT

#endif

// data member pointers

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) || defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
    || ( defined(__BORLANDC__) && BOOST_WORKAROUND( __BORLANDC__, BOOST_TESTED_AT( 0x620 ) ) )

template<class R, class T, class A1>
_bi::bind_t< R, _mfi::dm<R, T>, typename _bi::list_av_1<A1>::type >
    BOOST_BIND(R T::*f, A1 a1)
{
    typedef _mfi::dm<R, T> F;
    typedef typename _bi::list_av_1<A1>::type list_type;
    return _bi::bind_t<R, F, list_type>( F(f), list_type(a1) );
}

#else

namespace _bi
{

template< class Pm, int I > struct add_cref;

template< class M, class T > struct add_cref< M T::*, 0 >
{
    typedef M type;
};

template< class M, class T > struct add_cref< M T::*, 1 >
{
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4180)
#endif
    typedef M const & type;
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
};

template< class R, class T > struct add_cref< R (T::*) (), 1 >
{
    typedef void type;
};

#if !defined(__IBMCPP__) || __IBMCPP_FUNC_CV_TMPL_ARG_DEDUCTION

template< class R, class T > struct add_cref< R (T::*) () const, 1 >
{
    typedef void type;
};

#if defined( __cpp_noexcept_function_type ) || defined( _NOEXCEPT_TYPES_SUPPORTED )

template< class R, class T > struct add_cref< R (T::*) () const noexcept, 1 >
{
    typedef void type;
};

#endif // __cpp_noexcept_function_type

#endif // __IBMCPP__

template<class R> struct isref
{
    enum value_type { value = 0 };
};

template<class R> struct isref< R& >
{
    enum value_type { value = 1 };
};

template<class R> struct isref< R* >
{
    enum value_type { value = 1 };
};

template<class Pm, class A1> struct dm_result
{
    typedef typename add_cref< Pm, 1 >::type type;
};

template<class Pm, class R, class F, class L> struct dm_result< Pm, bind_t<R, F, L> >
{
    typedef typename bind_t<R, F, L>::result_type result_type;
    typedef typename add_cref< Pm, isref< result_type >::value >::type type;
};

} // namespace _bi

template< class A1, class M, class T >

_bi::bind_t<
    typename _bi::dm_result< M T::*, A1 >::type,
    _mfi::dm<M, T>,
    typename _bi::list_av_1<A1>::type
>

BOOST_BIND( M T::*f, A1 a1 )
{
    typedef typename _bi::dm_result< M T::*, A1 >::type result_type;
    typedef _mfi::dm<M, T> F;
    typedef typename _bi::list_av_1<A1>::type list_type;
    return _bi::bind_t< result_type, F, list_type >( F( f ), list_type( a1 ) );
}

#endif

} // namespace boost

#ifndef BOOST_BIND_NO_PLACEHOLDERS

# include <boost/bind/placeholders.hpp>

#endif

#ifdef BOOST_MSVC
# pragma warning(default: 4512) // assignment operator could not be generated
# pragma warning(pop)
#endif

#endif // #ifndef BOOST_BIND_BIND_HPP_INCLUDED

/* bind.hpp
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
*/