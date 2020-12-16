
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
49aRBwI51+P53K0kDZa+rcr+YqenltTrybrprLuGlbYP0Mp/bC/5XvmeREfHWvKyfC/s8mG61M3PJEI/jK8k7/HoqXHtzTW3cv39nb7+Ds+jfH9N8V23Lle+03bnMaNKyRiGb/F5UC85N3LO1efGtl1CltSxR3nwHcRID2mX0F117DZjbPq68L0ru8wy2pZZljrdbI6PM+KwT/xZVbmkHGORfOYr2T1IzofS3iKTY9vE5/3Bpeej2FJfnxwzdbr9+QhX9auviR0kLxiC1OfDnAFcr/tuoLrmadPjUkyxOHHd5Tyoz4u6LYK7f+AfWJftuI74z6vjHn2vMn/j1HlXXthiXLqj4fTuVUdS7ahRx63Vj/Hm13GHhmn3v3pK/tw/jXrMUfcTK2O7D6X/x79Qj9tR2S7PQ+615B6M7ag/oi7UQ/pkyziHn2AA7sBOUmfdF3fjMPwMJ0q/sEelzmy51Jltwn3S/n+/1EkdwMvSr07Z+UGsioewOR7GO/BrHIZHpE72KEbiMYzH4zgfC/EV/BY34ne4FU/hh/g97sLT+AWewaP4bzyFZ/E3PIcNOfYfMQDPY3sswnD8Ce/GCxiPFzEDi/FxvITP4mV8C3/FT/B33IMeSr8erIyX0BOVfg1VsQVWw75YHcdjTYzBWpiBPvgo1sElWBe3Yj08ir74O9ZX4vOkDMf+2BDj0A8fw8a4FJvg++iPhdgUPapQHmNrbI6DMADjsQU+ga3wFWyD+7EdFmJ7/BE74M/YEWuTrzphHeyM7bAL9sWueDsGYX/sjuEYjEbsgWkYgunYW/JtmE7ub7Gf5PeqSJ5kQulveCs2wNvQH/thTwzFPni7xBfgIfeocs9KfIzJyfmU74HSb80PB0m/qTDprzgEw3AozsS78EG8W/qxDcNX0NyfbQQW4Eg8iqPwBxyNP0v/Nk/2PQbr4FhsguOxBUZiO7wf78YoHIPRmIYTcS7G4QKMx2cxQfq9TcFVOBU3YhK+hcm4FY3YmWNOwZcxFeuTn2Zgc5yFHXE2BuEcDMG5OAIfxPvxIYzHR/BBnI+ZmInL8FF8FbPwdXwcN2M2/gOfwkLMwTP4DJ7HZ/EyPif5fBHWId/+DRvi89geX8AQ/DsOwOU4EV/CnZiLwVznl/F2fAVH4wqMxDUYg6/hJHxd8km+Tu5ncab0i6qv5BkCk6ntiB+uxha4BjtLP9Ne0r/0blyPcfg6puAGqePfiNnSFuN5fAPXS5uMLfi29IfbghelDYaST/6JXXArDsX38C58H2Nwm5SXHyLHQb6Qe1O5Z+U4GEtWyV/2bSga4K3YXtpQ9JA2FJMxFI14uxzHHTgHB+DDOFDaLAyW/q5h+KK0cdiKQ3APDsXzOAx/wwjpfzscG+EIbIUjsROOQwPeK215JmIoxmAYxuJwjMOxOBmjMR4zMAEfxyn4LE7FF3Eavo5JeACT8ZC0TTqOKXgBp2N9zlsadsUZeDfOxDE4GyNxjqp/NPe+0k/Yvn90aznfbeR8B6I/tsdg7CD5oSMuxs7y97WLtAXqKufJgE0wCNtgMHbAHrjUQxlPo2R8YF+f8rX5+Cv1hysaWMWldh/0ibvh8YKdbfPh7gvnoC8ceS6CkEpYSthOOEvw45ddcB13Ow/35J7ck3tyT+7JPbkn9+TcVAH9/2Oip6fetPH/O50x1fcTZQ/pnF7aRz9KtYzOgZb5i1Tz42JK5+9QxzUxxtQ24Jl6Oksf+USNOvyibpY6fMvGztbdm+PeoRG3LsgqbjlI1+Ju7aExRrs6bjkZrqY7QyPuAFXccgFciLuk3su/suN3Afp0McVtOdd/xvi41yo7fBcgDw8kbZZrVXF9UrXeBRhAWq8=
*/