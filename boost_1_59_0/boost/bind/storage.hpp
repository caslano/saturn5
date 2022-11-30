#ifndef BOOST_BIND_STORAGE_HPP_INCLUDED
#define BOOST_BIND_STORAGE_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  bind/storage.hpp
//
//  boost/bind.hpp support header, optimized storage
//
//  Copyright (c) 2006 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  See http://www.boost.org/libs/bind/bind.html for documentation.
//

#include <boost/config.hpp>
#include <boost/bind/arg.hpp>

#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable: 4512) // assignment operator could not be generated
#endif

namespace boost
{

namespace _bi
{

// 1

template<class A1> struct storage1
{
    explicit storage1( A1 a1 ): a1_( a1 ) {}

    template<class V> void accept(V & v) const
    {
        BOOST_BIND_VISIT_EACH(v, a1_, 0);
    }

    A1 a1_;
};

#if !defined( BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION ) && !defined( BOOST_BORLANDC )

template<int I> struct storage1< boost::arg<I> >
{
    explicit storage1( boost::arg<I> ) {}

    template<class V> void accept(V &) const { }

    static boost::arg<I> a1_() { return boost::arg<I>(); }
};

template<int I> struct storage1< boost::arg<I> (*) () >
{
    explicit storage1( boost::arg<I> (*) () ) {}

    template<class V> void accept(V &) const { }

    static boost::arg<I> a1_() { return boost::arg<I>(); }
};

#endif

// 2

template<class A1, class A2> struct storage2: public storage1<A1>
{
    typedef storage1<A1> inherited;

    storage2( A1 a1, A2 a2 ): storage1<A1>( a1 ), a2_( a2 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
        BOOST_BIND_VISIT_EACH(v, a2_, 0);
    }

    A2 a2_;
};

#if !defined( BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION )

template<class A1, int I> struct storage2< A1, boost::arg<I> >: public storage1<A1>
{
    typedef storage1<A1> inherited;

    storage2( A1 a1, boost::arg<I> ): storage1<A1>( a1 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
    }

    static boost::arg<I> a2_() { return boost::arg<I>(); }
};

template<class A1, int I> struct storage2< A1, boost::arg<I> (*) () >: public storage1<A1>
{
    typedef storage1<A1> inherited;

    storage2( A1 a1, boost::arg<I> (*) () ): storage1<A1>( a1 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
    }

    static boost::arg<I> a2_() { return boost::arg<I>(); }
};

#endif

// 3

template<class A1, class A2, class A3> struct storage3: public storage2< A1, A2 >
{
    typedef storage2<A1, A2> inherited;

    storage3( A1 a1, A2 a2, A3 a3 ): storage2<A1, A2>( a1, a2 ), a3_( a3 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
        BOOST_BIND_VISIT_EACH(v, a3_, 0);
    }

    A3 a3_;
};

#if !defined( BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION )

template<class A1, class A2, int I> struct storage3< A1, A2, boost::arg<I> >: public storage2< A1, A2 >
{
    typedef storage2<A1, A2> inherited;

    storage3( A1 a1, A2 a2, boost::arg<I> ): storage2<A1, A2>( a1, a2 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
    }

    static boost::arg<I> a3_() { return boost::arg<I>(); }
};

template<class A1, class A2, int I> struct storage3< A1, A2, boost::arg<I> (*) () >: public storage2< A1, A2 >
{
    typedef storage2<A1, A2> inherited;

    storage3( A1 a1, A2 a2, boost::arg<I> (*) () ): storage2<A1, A2>( a1, a2 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
    }

    static boost::arg<I> a3_() { return boost::arg<I>(); }
};

#endif

// 4

template<class A1, class A2, class A3, class A4> struct storage4: public storage3< A1, A2, A3 >
{
    typedef storage3<A1, A2, A3> inherited;

    storage4( A1 a1, A2 a2, A3 a3, A4 a4 ): storage3<A1, A2, A3>( a1, a2, a3 ), a4_( a4 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
        BOOST_BIND_VISIT_EACH(v, a4_, 0);
    }

    A4 a4_;
};

#if !defined( BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION )

template<class A1, class A2, class A3, int I> struct storage4< A1, A2, A3, boost::arg<I> >: public storage3< A1, A2, A3 >
{
    typedef storage3<A1, A2, A3> inherited;

    storage4( A1 a1, A2 a2, A3 a3, boost::arg<I> ): storage3<A1, A2, A3>( a1, a2, a3 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
    }

    static boost::arg<I> a4_() { return boost::arg<I>(); }
};

template<class A1, class A2, class A3, int I> struct storage4< A1, A2, A3, boost::arg<I> (*) () >: public storage3< A1, A2, A3 >
{
    typedef storage3<A1, A2, A3> inherited;

    storage4( A1 a1, A2 a2, A3 a3, boost::arg<I> (*) () ): storage3<A1, A2, A3>( a1, a2, a3 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
    }

    static boost::arg<I> a4_() { return boost::arg<I>(); }
};

#endif

// 5

template<class A1, class A2, class A3, class A4, class A5> struct storage5: public storage4< A1, A2, A3, A4 >
{
    typedef storage4<A1, A2, A3, A4> inherited;

    storage5( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5 ): storage4<A1, A2, A3, A4>( a1, a2, a3, a4 ), a5_( a5 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
        BOOST_BIND_VISIT_EACH(v, a5_, 0);
    }

    A5 a5_;
};

#if !defined( BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION )

template<class A1, class A2, class A3, class A4, int I> struct storage5< A1, A2, A3, A4, boost::arg<I> >: public storage4< A1, A2, A3, A4 >
{
    typedef storage4<A1, A2, A3, A4> inherited;

    storage5( A1 a1, A2 a2, A3 a3, A4 a4, boost::arg<I> ): storage4<A1, A2, A3, A4>( a1, a2, a3, a4 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
    }

    static boost::arg<I> a5_() { return boost::arg<I>(); }
};

template<class A1, class A2, class A3, class A4, int I> struct storage5< A1, A2, A3, A4, boost::arg<I> (*) () >: public storage4< A1, A2, A3, A4 >
{
    typedef storage4<A1, A2, A3, A4> inherited;

    storage5( A1 a1, A2 a2, A3 a3, A4 a4, boost::arg<I> (*) () ): storage4<A1, A2, A3, A4>( a1, a2, a3, a4 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
    }

    static boost::arg<I> a5_() { return boost::arg<I>(); }
};

#endif

// 6

template<class A1, class A2, class A3, class A4, class A5, class A6> struct storage6: public storage5< A1, A2, A3, A4, A5 >
{
    typedef storage5<A1, A2, A3, A4, A5> inherited;

    storage6( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6 ): storage5<A1, A2, A3, A4, A5>( a1, a2, a3, a4, a5 ), a6_( a6 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
        BOOST_BIND_VISIT_EACH(v, a6_, 0);
    }

    A6 a6_;
};

#if !defined( BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION )

template<class A1, class A2, class A3, class A4, class A5, int I> struct storage6< A1, A2, A3, A4, A5, boost::arg<I> >: public storage5< A1, A2, A3, A4, A5 >
{
    typedef storage5<A1, A2, A3, A4, A5> inherited;

    storage6( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, boost::arg<I> ): storage5<A1, A2, A3, A4, A5>( a1, a2, a3, a4, a5 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
    }

    static boost::arg<I> a6_() { return boost::arg<I>(); }
};

template<class A1, class A2, class A3, class A4, class A5, int I> struct storage6< A1, A2, A3, A4, A5, boost::arg<I> (*) () >: public storage5< A1, A2, A3, A4, A5 >
{
    typedef storage5<A1, A2, A3, A4, A5> inherited;

    storage6( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, boost::arg<I> (*) () ): storage5<A1, A2, A3, A4, A5>( a1, a2, a3, a4, a5 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
    }

    static boost::arg<I> a6_() { return boost::arg<I>(); }
};

#endif

// 7

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> struct storage7: public storage6< A1, A2, A3, A4, A5, A6 >
{
    typedef storage6<A1, A2, A3, A4, A5, A6> inherited;

    storage7( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7 ): storage6<A1, A2, A3, A4, A5, A6>( a1, a2, a3, a4, a5, a6 ), a7_( a7 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
        BOOST_BIND_VISIT_EACH(v, a7_, 0);
    }

    A7 a7_;
};

#if !defined( BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION )

template<class A1, class A2, class A3, class A4, class A5, class A6, int I> struct storage7< A1, A2, A3, A4, A5, A6, boost::arg<I> >: public storage6< A1, A2, A3, A4, A5, A6 >
{
    typedef storage6<A1, A2, A3, A4, A5, A6> inherited;

    storage7( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, boost::arg<I> ): storage6<A1, A2, A3, A4, A5, A6>( a1, a2, a3, a4, a5, a6 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
    }

    static boost::arg<I> a7_() { return boost::arg<I>(); }
};

template<class A1, class A2, class A3, class A4, class A5, class A6, int I> struct storage7< A1, A2, A3, A4, A5, A6, boost::arg<I> (*) () >: public storage6< A1, A2, A3, A4, A5, A6 >
{
    typedef storage6<A1, A2, A3, A4, A5, A6> inherited;

    storage7( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, boost::arg<I> (*) () ): storage6<A1, A2, A3, A4, A5, A6>( a1, a2, a3, a4, a5, a6 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
    }

    static boost::arg<I> a7_() { return boost::arg<I>(); }
};

#endif

// 8

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> struct storage8: public storage7< A1, A2, A3, A4, A5, A6, A7 >
{
    typedef storage7<A1, A2, A3, A4, A5, A6, A7> inherited;

    storage8( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8 ): storage7<A1, A2, A3, A4, A5, A6, A7>( a1, a2, a3, a4, a5, a6, a7 ), a8_( a8 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
        BOOST_BIND_VISIT_EACH(v, a8_, 0);
    }

    A8 a8_;
};

#if !defined( BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION )

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, int I> struct storage8< A1, A2, A3, A4, A5, A6, A7, boost::arg<I> >: public storage7< A1, A2, A3, A4, A5, A6, A7 >
{
    typedef storage7<A1, A2, A3, A4, A5, A6, A7> inherited;

    storage8( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, boost::arg<I> ): storage7<A1, A2, A3, A4, A5, A6, A7>( a1, a2, a3, a4, a5, a6, a7 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
    }

    static boost::arg<I> a8_() { return boost::arg<I>(); }
};

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, int I> struct storage8< A1, A2, A3, A4, A5, A6, A7, boost::arg<I> (*) () >: public storage7< A1, A2, A3, A4, A5, A6, A7 >
{
    typedef storage7<A1, A2, A3, A4, A5, A6, A7> inherited;

    storage8( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, boost::arg<I> (*) () ): storage7<A1, A2, A3, A4, A5, A6, A7>( a1, a2, a3, a4, a5, a6, a7 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
    }

    static boost::arg<I> a8_() { return boost::arg<I>(); }
};

#endif

// 9

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> struct storage9: public storage8< A1, A2, A3, A4, A5, A6, A7, A8 >
{
    typedef storage8<A1, A2, A3, A4, A5, A6, A7, A8> inherited;

    storage9( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9 ): storage8<A1, A2, A3, A4, A5, A6, A7, A8>( a1, a2, a3, a4, a5, a6, a7, a8 ), a9_( a9 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
        BOOST_BIND_VISIT_EACH(v, a9_, 0);
    }

    A9 a9_;
};

#if !defined( BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION )

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, int I> struct storage9< A1, A2, A3, A4, A5, A6, A7, A8, boost::arg<I> >: public storage8< A1, A2, A3, A4, A5, A6, A7, A8 >
{
    typedef storage8<A1, A2, A3, A4, A5, A6, A7, A8> inherited;

    storage9( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, boost::arg<I> ): storage8<A1, A2, A3, A4, A5, A6, A7, A8>( a1, a2, a3, a4, a5, a6, a7, a8 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
    }

    static boost::arg<I> a9_() { return boost::arg<I>(); }
};

template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, int I> struct storage9< A1, A2, A3, A4, A5, A6, A7, A8, boost::arg<I> (*) () >: public storage8< A1, A2, A3, A4, A5, A6, A7, A8 >
{
    typedef storage8<A1, A2, A3, A4, A5, A6, A7, A8> inherited;

    storage9( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, boost::arg<I> (*) () ): storage8<A1, A2, A3, A4, A5, A6, A7, A8>( a1, a2, a3, a4, a5, a6, a7, a8 ) {}

    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
    }

    static boost::arg<I> a9_() { return boost::arg<I>(); }
};

#endif

} // namespace _bi

} // namespace boost

#ifdef BOOST_MSVC
# pragma warning(default: 4512) // assignment operator could not be generated
# pragma warning(pop)
#endif

#endif // #ifndef BOOST_BIND_STORAGE_HPP_INCLUDED

/* storage.hpp
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
*/