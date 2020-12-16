
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "inherit.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct inherit2
    : T1, T2
{
    typedef inherit2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1, T2))
};

template< typename T1 >
struct inherit2< T1,empty_base >
{
    typedef T1 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (T1, empty_base))
};

template< typename T2 >
struct inherit2< empty_base,T2 >
{
    typedef T2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, T2))
};

template<>
struct inherit2< empty_base,empty_base >
{
    typedef empty_base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, empty_base))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit2)

template<
      typename T1 = na, typename T2 = na, typename T3 = na
    >
struct inherit3
    : inherit2<
          typename inherit2<
              T1, T2
            >::type
        , T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , inherit3
        , ( T1, T2, T3)
        )
};

BOOST_MPL_AUX_NA_SPEC(3, inherit3)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    >
struct inherit4
    : inherit2<
          typename inherit3<
              T1, T2, T3
            >::type
        , T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , inherit4
        , ( T1, T2, T3, T4)
        )
};

BOOST_MPL_AUX_NA_SPEC(4, inherit4)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    , typename T5 = na
    >
struct inherit5
    : inherit2<
          typename inherit4<
              T1, T2, T3, T4
            >::type
        , T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , inherit5
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC(5, inherit5)

/// primary template

template<
      typename T1 = empty_base, typename T2 = empty_base
    , typename T3 = empty_base, typename T4 = empty_base
    , typename T5 = empty_base
    >
struct inherit
    : inherit5< T1,T2,T3,T4,T5 >
{
};

template<>
struct inherit< na,na,na,na,na >
{
    template<

          typename T1, typename T2, typename T3, typename T4, typename T5

        >
    struct apply
        : inherit< T1,T2,T3,T4,T5 >
    {
    };
};

BOOST_MPL_AUX_NA_SPEC_LAMBDA(5, inherit)
BOOST_MPL_AUX_NA_SPEC_ARITY(5, inherit)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(5, 5, inherit)
}}


/* inherit.hpp
fZloyWH2ZfwbsHSD3RXqFaAOcN4vZ3WtodYWSz8YPRzp/jjrAaOdf4O0K2LGJ0du4Xh4D/FzXHyr1dbbi85O1NEwS2CDTliGYWOa2msYrTnEe/jPdX+sdQtlhCdCbF+H/o6X50MopxvP9zwg6yLZT9Tvf/31e6VqfXy2Cm+yj1e7HCHxlAwm/cso4ub411M5nmzZ758/a0GDqMdQgpSIrxVLxJ8VQ9uxAk5ZT9t62toth/437iexVutX2u+LOKvpRfuH/w7/Hf47/Hf47/Df4b/Df4f/Dv8d/jv8d/jv8N/hv8N//9N/2/ZEW/7f/9yeYs/4dRsqrr72M+eFn70cOa79pVtC34bLCd2sUd/7MHTfpnmgo9Mv794krwmmp6ZlDbUNZi9ODrb7eO9DcujGitbOc8/q8wSVxf6Fvf5mddy+MWoRf5GWw3+H/w7/Hf47/Hcgf1/J97LcTq2dH/VMtDWZom9/QmuX9RvPGdufM7V7nje279K1j90dbU3Zvf/nHv/f/1rkPZpNW2eHbp88dbxa1h8127LDPtvy6RmzLbmF3A+ahV59fCMklmesU3n3VYbF8t4SnsPk2w9ZbN54gKnJldSn8bLVzxotlos5vgfYT2LoixXu5jniiArulVfzjqxynkuFDt88sIyfTSkOfR/C8jdesnIqfR5bLJ4p5t0Cc0Lv27b0Ted5kEUWyySO/8GXcV7iRceXU2bCgxd61pm8s6sZvqH5PfqnLQm9M86yheOLKTuWs/cQ3HPh4WHwxvPVpUvzwCtiv2QLdNsYB9hmHk68fyJzjNXs5eNJmugI8Q4iaPJRvhsioUd5n7toHwO/M433ZULDS9sE4JuB3QpsZx00GH8B/EYw5iD8lXPHLckHvxwno8fbUhl7PvO5BN5LUiWe2wWOvmqA3QK/S5ain1r246VYLHObiQNgWasslkXg/gDa32hE91Mslr9Sni8Dj3o5uryOnVI9PMUYBNdagj4nsf8vB54CPHMM3msziBFkPWoltlwBHfq0AtsJXx/Qr9mDjODOSoBfBdthm3fnWSy/geff0c9XYLF8Cb0O5P4WOE/NRG/g3MtYvwfvC87L2DP86yp0uoD7fhx75kKHcudieEaXUejraeyhcF7gxtZJ4IPLt4Itr8D3b+N4XroRfjPBm4wOI9E/On8V/Z5ih0YlvHLcB613qKsZ+1L0W4jt87IslomMeT/9W8HdjUwzOJ7lRw7GO7MYvafQhsdPQM4bqc9ClnxwM6CV6uD9AkvAo17JmDPh1U9Joe9P6efAR/+AnyTA4wZs8vhU+MGn9qLDnyHzJYx9IW0dtBW64Bd9xTLO6zHox4mPoqsx+NsehX6U3cTBGZz/Al0uFT6DX9zXTB/i7Rh8Ip367/A4bT7tjP8ktOzI/Q83tgaeRn18HHUmtk0CTttn4N2Tge6n8dwrcl+2lLxZQ3w74B/eZ9fjX/AbUY1dC7EffC+G/t/mouMS7BqFjMh1KTJUcH4+45wETmmueK8UdlyNrDHi+0rwUgkcvV/jgAYxOoitTkTmj+ibGEGsgbenFT0yzifA/w5PJRXQWwSvjFmRgF4Vjn1cG+i/Afs/hM1/5cLnA8hVBk3qSPjIKcZmVmghr5dY+WEWeoOnU+lzJzxeN4e4BO+DKGil0I5ui/Czby8ADt/J8LTbxjH8LnIgN7ZUaD8PH0lYCG18vCwNf6TshsbLs4lbxq5qg0dkzUaeP5ehP84joTHgJOeVou8l2B3/uQKaD4JzlJ/8tJjcRm75HLoXx8EjpSqV+GD89Yz3HXRhTcAnwEtZjZ/ARxT2mM7YJ8P7p1XwDv0K9PAXaH4D3RQvAgc6p1N/m3IGfW4iXtc=
*/