    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_expr.hpp
    /// Contains overloads of make_expr() free function.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    
    
    template<typename Tag , typename A0 , typename A1>
    BOOST_FORCEINLINE
    typename lazy_disable_if<
        is_domain<A0>
      , result_of::make_expr<
            Tag
            , const A0 , const A1
        >
    >::type const
    make_expr(const A0 &a0 , const A1 &a1)
    {
        return proto::detail::make_expr_<
            Tag
          , deduce_domain
            , const A0 , const A1
        >()(a0 , a1);
    }
    
    
    template<typename Tag, typename Domain , typename C0 , typename C1>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        , const C0 , const C1
    >::type const
    make_expr(const C0 &c0 , const C1 &c1)
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const C0 , const C1
        >()(c0 , c1);
    }
    
    
    template<typename Tag , typename A0 , typename A1 , typename A2>
    BOOST_FORCEINLINE
    typename lazy_disable_if<
        is_domain<A0>
      , result_of::make_expr<
            Tag
            , const A0 , const A1 , const A2
        >
    >::type const
    make_expr(const A0 &a0 , const A1 &a1 , const A2 &a2)
    {
        return proto::detail::make_expr_<
            Tag
          , deduce_domain
            , const A0 , const A1 , const A2
        >()(a0 , a1 , a2);
    }
    
    
    template<typename Tag, typename Domain , typename C0 , typename C1 , typename C2>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        , const C0 , const C1 , const C2
    >::type const
    make_expr(const C0 &c0 , const C1 &c1 , const C2 &c2)
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const C0 , const C1 , const C2
        >()(c0 , c1 , c2);
    }
    
    
    template<typename Tag , typename A0 , typename A1 , typename A2 , typename A3>
    BOOST_FORCEINLINE
    typename lazy_disable_if<
        is_domain<A0>
      , result_of::make_expr<
            Tag
            , const A0 , const A1 , const A2 , const A3
        >
    >::type const
    make_expr(const A0 &a0 , const A1 &a1 , const A2 &a2 , const A3 &a3)
    {
        return proto::detail::make_expr_<
            Tag
          , deduce_domain
            , const A0 , const A1 , const A2 , const A3
        >()(a0 , a1 , a2 , a3);
    }
    
    
    template<typename Tag, typename Domain , typename C0 , typename C1 , typename C2 , typename C3>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        , const C0 , const C1 , const C2 , const C3
    >::type const
    make_expr(const C0 &c0 , const C1 &c1 , const C2 &c2 , const C3 &c3)
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const C0 , const C1 , const C2 , const C3
        >()(c0 , c1 , c2 , c3);
    }
    
    
    template<typename Tag , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    BOOST_FORCEINLINE
    typename lazy_disable_if<
        is_domain<A0>
      , result_of::make_expr<
            Tag
            , const A0 , const A1 , const A2 , const A3 , const A4
        >
    >::type const
    make_expr(const A0 &a0 , const A1 &a1 , const A2 &a2 , const A3 &a3 , const A4 &a4)
    {
        return proto::detail::make_expr_<
            Tag
          , deduce_domain
            , const A0 , const A1 , const A2 , const A3 , const A4
        >()(a0 , a1 , a2 , a3 , a4);
    }
    
    
    template<typename Tag, typename Domain , typename C0 , typename C1 , typename C2 , typename C3 , typename C4>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        , const C0 , const C1 , const C2 , const C3 , const C4
    >::type const
    make_expr(const C0 &c0 , const C1 &c1 , const C2 &c2 , const C3 &c3 , const C4 &c4)
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const C0 , const C1 , const C2 , const C3 , const C4
        >()(c0 , c1 , c2 , c3 , c4);
    }
    
    
    template<typename Tag , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    BOOST_FORCEINLINE
    typename lazy_disable_if<
        is_domain<A0>
      , result_of::make_expr<
            Tag
            , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
        >
    >::type const
    make_expr(const A0 &a0 , const A1 &a1 , const A2 &a2 , const A3 &a3 , const A4 &a4 , const A5 &a5)
    {
        return proto::detail::make_expr_<
            Tag
          , deduce_domain
            , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
        >()(a0 , a1 , a2 , a3 , a4 , a5);
    }
    
    
    template<typename Tag, typename Domain , typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        , const C0 , const C1 , const C2 , const C3 , const C4 , const C5
    >::type const
    make_expr(const C0 &c0 , const C1 &c1 , const C2 &c2 , const C3 &c3 , const C4 &c4 , const C5 &c5)
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const C0 , const C1 , const C2 , const C3 , const C4 , const C5
        >()(c0 , c1 , c2 , c3 , c4 , c5);
    }
    
    
    template<typename Tag , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    BOOST_FORCEINLINE
    typename lazy_disable_if<
        is_domain<A0>
      , result_of::make_expr<
            Tag
            , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
        >
    >::type const
    make_expr(const A0 &a0 , const A1 &a1 , const A2 &a2 , const A3 &a3 , const A4 &a4 , const A5 &a5 , const A6 &a6)
    {
        return proto::detail::make_expr_<
            Tag
          , deduce_domain
            , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
        >()(a0 , a1 , a2 , a3 , a4 , a5 , a6);
    }
    
    
    template<typename Tag, typename Domain , typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5 , typename C6>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        , const C0 , const C1 , const C2 , const C3 , const C4 , const C5 , const C6
    >::type const
    make_expr(const C0 &c0 , const C1 &c1 , const C2 &c2 , const C3 &c3 , const C4 &c4 , const C5 &c5 , const C6 &c6)
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const C0 , const C1 , const C2 , const C3 , const C4 , const C5 , const C6
        >()(c0 , c1 , c2 , c3 , c4 , c5 , c6);
    }
    
    
    template<typename Tag , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    BOOST_FORCEINLINE
    typename lazy_disable_if<
        is_domain<A0>
      , result_of::make_expr<
            Tag
            , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
        >
    >::type const
    make_expr(const A0 &a0 , const A1 &a1 , const A2 &a2 , const A3 &a3 , const A4 &a4 , const A5 &a5 , const A6 &a6 , const A7 &a7)
    {
        return proto::detail::make_expr_<
            Tag
          , deduce_domain
            , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
        >()(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
    }
    
    
    template<typename Tag, typename Domain , typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5 , typename C6 , typename C7>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        , const C0 , const C1 , const C2 , const C3 , const C4 , const C5 , const C6 , const C7
    >::type const
    make_expr(const C0 &c0 , const C1 &c1 , const C2 &c2 , const C3 &c3 , const C4 &c4 , const C5 &c5 , const C6 &c6 , const C7 &c7)
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const C0 , const C1 , const C2 , const C3 , const C4 , const C5 , const C6 , const C7
        >()(c0 , c1 , c2 , c3 , c4 , c5 , c6 , c7);
    }
    
    
    template<typename Tag , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    BOOST_FORCEINLINE
    typename lazy_disable_if<
        is_domain<A0>
      , result_of::make_expr<
            Tag
            , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
        >
    >::type const
    make_expr(const A0 &a0 , const A1 &a1 , const A2 &a2 , const A3 &a3 , const A4 &a4 , const A5 &a5 , const A6 &a6 , const A7 &a7 , const A8 &a8)
    {
        return proto::detail::make_expr_<
            Tag
          , deduce_domain
            , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
        >()(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
    }
    
    
    template<typename Tag, typename Domain , typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5 , typename C6 , typename C7 , typename C8>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        , const C0 , const C1 , const C2 , const C3 , const C4 , const C5 , const C6 , const C7 , const C8
    >::type const
    make_expr(const C0 &c0 , const C1 &c1 , const C2 &c2 , const C3 &c3 , const C4 &c4 , const C5 &c5 , const C6 &c6 , const C7 &c7 , const C8 &c8)
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const C0 , const C1 , const C2 , const C3 , const C4 , const C5 , const C6 , const C7 , const C8
        >()(c0 , c1 , c2 , c3 , c4 , c5 , c6 , c7 , c8);
    }
    
    
    template<typename Tag , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    BOOST_FORCEINLINE
    typename lazy_disable_if<
        is_domain<A0>
      , result_of::make_expr<
            Tag
            , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8 , const A9
        >
    >::type const
    make_expr(const A0 &a0 , const A1 &a1 , const A2 &a2 , const A3 &a3 , const A4 &a4 , const A5 &a5 , const A6 &a6 , const A7 &a7 , const A8 &a8 , const A9 &a9)
    {
        return proto::detail::make_expr_<
            Tag
          , deduce_domain
            , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8 , const A9
        >()(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
    }
    
    
    template<typename Tag, typename Domain , typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5 , typename C6 , typename C7 , typename C8 , typename C9>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        , const C0 , const C1 , const C2 , const C3 , const C4 , const C5 , const C6 , const C7 , const C8 , const C9
    >::type const
    make_expr(const C0 &c0 , const C1 &c1 , const C2 &c2 , const C3 &c3 , const C4 &c4 , const C5 &c5 , const C6 &c6 , const C7 &c7 , const C8 &c8 , const C9 &c9)
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const C0 , const C1 , const C2 , const C3 , const C4 , const C5 , const C6 , const C7 , const C8 , const C9
        >()(c0 , c1 , c2 , c3 , c4 , c5 , c6 , c7 , c8 , c9);
    }

/* make_expr.hpp
g++/MEbrZVLfuXvPK7OnOhYqZvMw+YVXB+m+iIUbOzNjzFOO+Vxxuy7O1TMuyWXTYt8/zrEUMX9jj917pd4n0sRONHbHuyG992uxocYCvuy6Uc8/sUHGHll0YbPutZid1+3ejn/oHHQ9887C+z92rMIV13y5d5bOQbFxxk7J9/1Va1dsiLFJ/3z0Wj3HXPsyYUPUAK1dseOMFd9/+D3HPMf3rYnu96Zfp9+pYnY//9h+9R8dC3PZlV3Fui8RYvZd3ilY8IJjUS577h+zztEzTmySsc3BtxQ6lixm6/ryp9/QZ2aK2frc8XR0kmN5Ynbtd3y2Ld2xErExtnanffWc9oqY/FPt7BNitM4aBSKMeddmHND9DO3bt4HZFw/R7xUxm7+/Za2+T/dabKCxOYdvTdE+EptubMn2GVqfCWIT7F7//psQrXkxW4O+2o/P0vki5m/XkLF0pc5kV9zMueUfOJYjNsrYTTcvu0j7SGyusei8NJ1Lta41LC0eMtmxDrERxv7wYPSbOnvEbN6X1Rds1/2c3Hdet9UvSNY7u9ggY6ffE1Giey1mn7n6gxO1b6PE7Boe2hB1ru6n2DRjIeeuWKhrF7Pz5bbUWVq7VWLHGDvjlHF6vteJDTcWdsraSK0zscHGzowaq/lrFhtirPnZh0/Xc0xsorFZe7L1TPWb0vf31r9SuFdnudhga79Pf0/3U8zm6Hf/a3lLZ4Er7onlE3ReR4hNNXbNx8OvdyxR7ARj143d+Y7WoFioMd/fLzyiM1nM1u6l/9xfrz0tdpqxiW/v2aEzUizG2JJxXVdqTZzQt/8+XfFptvaf2CBjc8sOTtK1u2zCM3t6/ybnso4bbxii+yJm83DS6f9+w7FoMbu+SZcufNaxWJe981FAg2PxYmOMfTsy9SSdn671HV4xI9SxFDFbu1fkl43V+Sk21K5h21OXas2L2bmb0RDS5Vip2HhjIyM26cyqERti7LnyW/K0H3R9sb/V7n9P0ztfwwm9dRYlNiojXvesSWyssWlLHk7X+fLbGtQydvxTv4G6xCYZG3r53WVa82GSP2Mbn82q1noRG2Hsvu1Rn2rexfyMhXwdcbPmXWyGsckpl+/Uu43YQGNfNSyu1PyJHWvsp9oBGTrLxYYYe/K2igu0j8TGG6ubMPdx/bYQs/vyZVvr63q3ERttLPqR625yrMIV9+YjntU661y/d/15XRt0nonZvX5o+20b9XtMzOZ2e8mqlXoGiI0zNmv4K12aoxP7vkva252/074Vm2fXN33oBN1rsWHGqvZX6V0/VWy2sbhzXjtN90xsirHdLzzeoWt3vUvY178bqjUvNs3YOc/8Qb/728T8jQ1LvfpHrV0x+afatoSHMnXtMlgnGJsxKOgRx6LEhhv7sDL8FJ0hYnOMfZE0catjmWLHG3t87/3ZunaxEGNnHPfFS1oTYsHG/nzl+Jna0673LA2M0/nSKmZz+90Tq3rvptP69vQFlx7bpmsXs3HP5bVcp2sXCzJW+9k+vbcmiNn9vOOe74bo2sVsDR5XUa9/r8sWszl69NGn9W+juWJ2fcvO3J7rWImJO1nM+8Hbp+o3gthkY6varzxPv2/Fhhp7Y9OwIO0jsZHGtgbdUqz7+dsa1N5/eKLWUrtYmI17erLeswLC+8btu2jffN1rsRON/bj2oUCtJbEZxv4c/N5hx9LF7Hv+8YtTdup+ikUZa163vVBrSWyUsc13vvqO9pGYXUPxay/cqmsXG27slOI1H2sfiU0ytubCrVfr2qf3zdHOvS/29pjYLGOjNq/QsyNezO7ZgOjxFY75xKYZC9o/oV1nstggYw1HH16i+yIWbixt5eJFeqaK2Zp4ous=
*/