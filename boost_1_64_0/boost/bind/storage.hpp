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
Rq6RFGmlu56cr1Ama9jt87wh52yrfu85E21lKEVo4vC55G1zuXeWct+MZc7AE9a9U2ehz1aD3jctVKZMZbDv9X1srejYyE7O9r28591qzrtsQOB5k1XmADLlYgNsWVwIG2BG7kuf3IzYyAZBck1ULpuH5JPIRS67OzoiskV0VOyZZ9jnpgxEfgMuGZnr4jxl/67Ob7GP1adLngaXqz19q+t525wVHUO1ORM51tBFfUsRZ+bFPA3TtP3ZHWfaJMOlHN+nzw7CIfJy3urbkeF+9rMjUx4w5p/MsefNMdN2BNh94V5T2TRjr8rcf6Y9NM+pwDka2rP6SvsTf8WlIXt4l2kPMTZTmDvX2yy6HJ9HqtPBlFPtn6s9MXN/eG6PBL03pkp4b3ofEeaerMN9bL8fHhGZ5n52ob+R66zwswt9hchNCm5XtG2Ml/DH8A+RuUtR4n/NEzdb+6Ltk9x/a3hWHGxgnl2vh6pHrTnGI07rhKknpl4s03qRWcn7FOkMsPMc/FzLC9HfSIP15BjxD7Dnc1DtP67Q954CXBdkU3ebsl1YMm9S/rxh+fPoaASXq5ZBushPMuWMvl+fzK3PDH2maXhn01aPFv94z/NB5bV+mvIZKjIXiD/TnKONYxuQK+EDXY7tR8X9utGV9etIl9+9lQmJu7m3At8zN6qNwW9xnXFv4s6x3jND57V00l1+91Iuh829pHpdTf58J/4X7WVUnOMrI24UsbGsZeDVT3N6rod6Vpu6b7XXh6xUNdT2Ok2b6w61XMfTXreQuD0o94veQ9r/rl6baZXNZlNekl9ybLs5Rp5Us320l+EBbWBGaFt4Dq4HZRi3xz4fMbB7ThxNf3u2lp9Xp5Upv257fHb5SuP955+NMfItTJ6dtcdX/8lS/pcImz7YmRLezHzjitPz29uowirM69NvEdpfnm2eF8TRPs9M64x1jHgE5Ft5UvC8xuacr2iPmefnmG8N/PMNHf93mmvFn6L2+cy8QFPvV+3xn99YpH7/d7/qf5PRfFC7blzTm2ZtW3OTg+1AdUS3fI/dDhT3e8HcYrEpijEu7/3ePtj2E3rHb4+rvbHt5B/HAY2C49gZ2cNOcZSvSE5xVD1n+1SEH799qvZVsE81RNOVmhKcrkSrcB/1pmvk8PHDJw4emzV+8Ljhk7KKCov0qx5xlW+3QWlT3WRpFz9KtsItjYsWFeSYe9TImO+t1Ugf19T0+Wz0cR2OmeuYuZspx2GDq7pzK2vKZtfJts1VU7a22q2yjs8emNHgN2+8u+DVvi/f/MSfPn/Raa7qybfBFXpu6OmzzfVDs8FVka0tXfMk4x9p8D4c77JisyLVeh75/pdvgZluz3PpMdv/v7T9/6T+v05tc233jt/oeFemfb9+nUN7FuwFB8LecCTsB2fCAfBiOBCWwSFwPRwKb4Uj4HY4Eu6C4+CjcBR8HI6G+/X48zATfgInwWNwMvwGTvXNYdWxCF0v5LCP8S3eb+pglsoZGx9q0ysSLoZ14BJYH14GG8GfwGbwctgaLoUd4BWaH1fCNHgV7Kk2vAbAZXAwXA7HwpVwKrwaXghX2ef2avxaVJCObNwuldupcmb/c7UllQIvgO3ghbAfnKXlNVvLaS7MgflwBbwY3gYLTX7pd1H4aIj8StG5rU1hC9hMr9dc60MrTW8XOA22hfNhO1gI28NiDb8CdoDLYUd4NTwTXqfhm2BneK/6j8rDXr8f6vdMK36WLaIvoYwR6FzbB2FvuBeOg7+EM+Cv4EK4D/4E/gauhk/AtXA/3AqfhrvhM/Ax+AJ8Cr4ID8FX4J/hq/Az+JrWz9fh9/AtGEecfg+bwLdhC/W3Uv9Z0JIbAN+DGfA=
*/