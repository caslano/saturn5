
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/quote.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {
template< bool > struct quote_impl
{
    template< typename T > struct result_
        : T
    {
    };
};

template<> struct quote_impl<false>
{
    template< typename T > struct result_
    {
        typedef T type;
    };
};

template<
      template< typename P1 > class F
    , typename Tag = void_
    >
struct quote1
{
    template< typename U1 > struct apply

        : quote_impl< aux::has_type< F<U1> >::value >
            ::template result_< F<U1> >

    {
    };
};

template<
      template< typename P1, typename P2 > class F
    , typename Tag = void_
    >
struct quote2
{
    template< typename U1, typename U2 > struct apply

        : quote_impl< aux::has_type< F< U1,U2 > >::value >
            ::template result_< F< U1,U2 > >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename Tag = void_
    >
struct quote3
{
    template< typename U1, typename U2, typename U3 > struct apply

        : quote_impl< aux::has_type< F< U1,U2,U3 > >::value >
            ::template result_< F< U1,U2,U3 > >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename Tag = void_
    >
struct quote4
{
    template<
          typename U1, typename U2, typename U3, typename U4
        >
    struct apply

        : quote_impl< aux::has_type< F< U1,U2,U3,U4 > >::value >
            ::template result_< F< U1,U2,U3,U4 > >

    {
    };
};

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5
        >
      class F
    , typename Tag = void_
    >
struct quote5
{
    template<
          typename U1, typename U2, typename U3, typename U4
        , typename U5
        >
    struct apply

        : quote_impl< aux::has_type< F< U1,U2,U3,U4,U5 > >::value >
            ::template result_< F< U1,U2,U3,U4,U5 > >

    {
    };
};

}}


/* quote.hpp
r334lRUfkYGltvqmwsVGlPRmZOYyQUQODVCbq8iPXvE8CoqPbNN2cp7jO/hUoSz1y5FGcqx7jJUqB/wO4+PlJ1LiXzdCdZ6M0Zp3TjaTCNPyS2bK+02f1PMeB2/aROpK2kSuzTGr+8nc8PR6CYM2V6y1OLD0BrjrpKogk9o0fs1WptudyLYlmMxHGWijNkZU2CMS5/FWBY83bcwt2+aP/KuZRYIfsQimVHkshC7bb9qWq3AC2H1ut0RBstlNWWIH+f7XRSguiUqQclQOo/hWww/rpa5IYH/8ISbywoD7b0qU+dWI765dAZjcTEGNPn/gSz6xxPZf2B1kPy10i7gSBRKUNX4CQ1mZZlb8FpKmX06m+SHVz4krZJwd8QGZAeGq952cClgzOGuSoPBuU/I1jbnS06dZVdOw6TnKOXa5ecrIhQG3LFgahShk1gdX3omVMiQFiCIIz6IIt3i4JxplLp2el+VnVXXwCc7BpzNq2t48OZafuRxfSZ/aWXj5Ihj9K7YJTeaEb8GHwiOBpjXhG8YfZ4xmjcT1rCcPv1xim+14eP/s+WmZ61jBj3HfugMqdL3HpQWSlWIOsGSVpv6EkO8RX1CedN4Lvgq9BcJ+wtDoMHitt5h1A/7geOgmGnMpfW+WxUNvUJQ7A5oBzYFmQfPAg53yZZNEFO3iT/aOP7J8/3gW7nSrPscWuCJlz+P9m2uP1Lnok/Qn6Qbr
*/