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

#if !defined( BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION ) && !defined( __BORLANDC__ )

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