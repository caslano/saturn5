
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* less_equal.hpp
5/vQBfid8H0MdJ6kfwX1S/A7V9x3EHQL8EPkiMGWR8/At2LgFV09Ttu505ET+i3x4JEL7PPhpRi7g3Oh+H3j5NrYQHzS9wx8IGUe/jyTNuz5Y/rlEfc7Of6pT3wLCt3VwBPx3UHf+6CzA5p3M7aTtvniflM1OQd+jyX+C1KgR/s59dhO0IpCF5QAdnAz7tWUV0WMcX5CDrFVBO2J+Az93sV//Fz/ulrxHeTthccPU7GfWJsFLy6B8ZEvAT5ygE+tIuZyoTEfOembRjwOUC+G1jqOj6IthfOn4XGcG72A54LXo4F9UE6+hsdPoXcFetmUSgzWkXvFb/EAPukhH6EDj4OY5JpQ1oCvoa/L0FejHV9BX50OzpF7twvaYk2OvttCH/Hi+rgE36BsqWYM8ApoL4HeZuR+kXHeYkw3fR+g/ekk9IfuTqslnigrOFYoa+DvFbHfJQW9gRtgnPFz6Ye9z06CnthnJPYOUPI537IKeoxdjI1uV5hb5XBMmUq5DVq30G4ppb/QMzHdLfIJ8uxoIQ4nolPisr+EHN5I30n4PX7RVYRdl+IbVnLbSnJkE/AG4gxaP8dO36DcjZ+thbdJ6HJnBj7oYUz4TI/DDxOwA36QXAGuQhzT79lk5OL8I2R7kPZAOjBoX5QJ32Ltp43chPw7GL8wl5y+CPkZc5m43w6/3XnII353iHXv+RQF+08mhhZjQ+R7Hx7GtBMvy7E//U504jPit2AV/o7sDuK2Hf/9GzTugcczOf8JOiqC9gNWxkzAxi3wUok/0O+GWfAATvlC4iQded3EYSryK1wfbMQVbTuRay/8NiP3k9noMx7+xG9Byo3Y5ptF2By8Y6F7zQL4gif7dGAcfz8LmXM4X0IexbZOMS+hfYzQAfzb4NFHrYj1+zzophA7Yh0EndVR0kvJT+SDXPh7PRX/Z+xgBvaYii3FuioyvBpFPgR+JrCbZqM/SgJ8HleMS+Bz43zE4RTyTg1xLu7vwtd37IzlRoYy8qXYY+Wl/zJ4IEYrl+ML4HXN53rRAs/wvj2X8dFpcw55BL20YpMYzi+GvwJoBK3oFPw70dMU2rJjicN0Yha7vY3+Xmni2uWDb/RUg4w7OU8S6w7wdar47VtAf3zze2KvD7qpYpwc6Ftt4CvYSdwTLiSWsOMusbcKup8nYjMXMheL99Wj/3Z03Qw99PgmNF6yE28NjMG40+m33Y/vngAO+Fc2QQPZXNA4w4ns9L9E7IljjDcikQ/60zKJ83x8sx5bMM4gcqRnw1sMNkaXfwfnq+nQmIXdgd3lIWdgxyPj8HfsnIke3GItQiEmM/AlxvhIXBeh20DJDeCvC6ADzr3I2QWf76EDD3jJ4D0GrSbgcRHYJQ6ewNtODBczjr2RGn/sp/0kxv7Ai304n4W/zaRvXjq6Euu2Ip+RD6+iJIp7Dwpyz8N3qD9dRuznEe/Ie3kBvlBJPONLk6k3LaNd3CtNIf9RNljRkbjnhg8PcrwIPU6ETsMS7Iqse9OItwriE138OhU9IdvXpegU+K1J5CLyTDW8eWgbbIIvzq9lnPP8zG2Kicnl6AN4hLh/JebG2K0P3Xdw/lvgC6YS01XonjrYRB/qNZRTOX4aPT1ShD+BHwOtsYLeDHiDr+fEOgW8dDLu74F9Ln6/JtIm9kzT5w1sOgac15bCJ+O+C062H3uTx46oZexq9AlOLv2OI29WxDLubHRDeQodzxb7T9vwv6n04/wRxrwNvCaxZ5b699jsAjFfF2tzyDsV3CuauQbSfl4JOWIRdBjrE3j4FXUMfH4o1r3QW+9k4m8ePoWf7fFBz0NOKkf2E/AhN7BM6GaRN9PAA3cq4y2gnAAv92DTNLE=
*/