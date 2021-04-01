
// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "quote.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template< typename T, bool has_type_ >
struct quote_impl

{
    typedef typename T::type type;
};

template< typename T >
struct quote_impl< T,false >
{
    typedef T type;
};

template<
      template< typename P1 > class F
    , typename Tag = void_
    >
struct quote1
{
    template< typename U1 > struct apply

    {
        typedef typename quote_impl<
              F<U1>
            , aux::has_type< F<U1> >::value
            >::type type;
    };
};

template<
      template< typename P1, typename P2 > class F
    , typename Tag = void_
    >
struct quote2
{
    template< typename U1, typename U2 > struct apply

    {
        typedef typename quote_impl<
              F< U1,U2 >
            , aux::has_type< F< U1,U2 > >::value
            >::type type;
    };
};

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename Tag = void_
    >
struct quote3
{
    template< typename U1, typename U2, typename U3 > struct apply

    {
        typedef typename quote_impl<
              F< U1,U2,U3 >
            , aux::has_type< F< U1,U2,U3 > >::value
            >::type type;
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

    {
        typedef typename quote_impl<
              F< U1,U2,U3,U4 >
            , aux::has_type< F< U1,U2,U3,U4 > >::value
            >::type type;
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

    {
        typedef typename quote_impl<
              F< U1,U2,U3,U4,U5 >
            , aux::has_type< F< U1,U2,U3,U4,U5 > >::value
            >::type type;
    };
};

}}


/* quote.hpp
ssEUTIAN4LAZlLT2IqPefjn8u2r/yfqMRkBLsk5+WwWHm/FtUDrHiOh9SErvTNq/svnGKpkR7vEjgz1LAK39PKAwM4G4nHwvbuFpgfUC/F8TfE4UsW+vqAA43ODxxTrjlMbx0ttEY3zwA5hxz8i27Qs0SRadrM0SRxEDp9RL9LMCf3r2g1s/Gds7LFlKAFhBQdpa/DKwL2Nhw3OOUAuuKaZtZyY1SHKIvSOBZnKHeGRXuycc4aUO4oiZpIUV5K+9HllqmJDlbn5yIvdwIjYa8NyhmG13Ti0u5x3oYd4ml1MIUK5HDy9OjXVfU2aqGNYp+BZx9xQ825WGOsQ+c3Klvch0GSAtTVKzhuJqC8peSPz4P7WhGcIXX3Qm3RJp2UnVN1BvFvZ+Xna3z0BS0x4n2MoVEY/tSuBBWoOtnbi5cwTSrpVoqBBd/ZziDeKjdC7gFpHZzOsfqL4o6fyOCkTssH4BZk214inJvyXRBRycJPRjg1Dk3vktGI4tSXZPkNXYAY79quAdBbb9kche/VK7HdHkH6iE+naS24vO5NZT4dV0V78g0BJeFSC0HA==
*/