
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitand.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitand_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitand_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitand_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitand_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitand_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitand_
    : bitand_< bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitand_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitand_< N1,N2,N3,N4,na >

    : bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitand_< N1,N2,N3,na,na >

    : bitand_< bitand_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitand_< N1,N2,na,na,na >
    : bitand_impl<
          typename bitand_tag<N1>::type
        , typename bitand_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitand_)

}}

namespace boost { namespace mpl {
template<>
struct bitand_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  & BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitand.hpp
JMyDU6ANpsNiWALnwOWwBJbBeXAdnA/XwwvhfbAUPgQvho/DRfBpuAR+AJfCr+ElsB62L4NhcDlsDS+FbeEKeCq8HA6EV8ChcCUcDsvgaHgVLIBroA1eDZfCa+BKeAO8Ht4IK2A5vBPeBO+Ht8DNkL9JPZL5LDjdoB49Jfn8LIyEz8EBcDscC3fAc+HzMA2+ADPhixL/1Yhjvom4JP4QuELibyXxR0r8UbAjbA/PgB3gmfAEmAJPgpNhJ1gMO8M58FS4CnaBq2FXeC/sDjfDWLgV9pBy6gkd7VrmmuAWg3a9TNr1ZbAdXAG7wivgKLgSjoNl0p5WwZnwKlgCV8OFcA28DK6Fq+A6eB+8Fm6C10m9L7XIvBN4W+xpCm1izxfS7vbDDvBr2Al+A7vBb6V9fwenwR/gCngA3gp/hE/An+B2eBA+D3+GL8JfXP2LzA3BfIN68ZvkC3Xa3s8dI+0rSOpBMMyG9eF0eCzMhcdJvicg5RJ/lMRfH8ZJ/I24Lgg2hg1hE6knTaWeHA9de7hKPI0N+vPZ0p9bYUOPPUCrfYRLlnDjJdwE6LS7xofdoWJ3mNjdXOwOF7tbqOyOXuRd/0zRP0v056nvXz7CZUu4HAk3XVWeCRJuokF5hkt5toLNYWuIWNrAnrAt7A0j5T7WTup9lMRfqYjEnyD9tRJPhcTfUertCTAKnij3i85yvzgF9oCnwqGwC0yFMTALdoVLYDd4Kewu961Y+Cg8DT4G4+AeeDp8H/aCJ2BPX9gd9oM9oXrv54Ql3scRCZKfAyU/BqnCWSVceC17uoZ57Ola5iNcqoRLk3DpqnCVPuxMlHBniZ1D1fV8Sd325LUs9R5unoSbL+EWSLgdSLSE+1zCRcCtEq6/tIczYThMgF3hQLkvD4Ij4GA4Hg6BWfAsmA/PhgvgCLgIjoRlcJTcn8fADTBJ7s/nwG1wLNwOx8HXYDJ8B46He+AE+DFMgZ/ASdJOoy3yrApDxeda8oRDykeus/p5XZlc18LLdckB7nFr7m9r7m97OPvbHtpi7nFr7nF79Pa4LevJHrVIFVKDNDmN/WuRJKQEuRrZhryFNIjjb8hIxIZcjWxB9iCW0/kbkoIsQMqRHch+JLwX3/xHpiIlyOpepi+xeZiHeZiHeZiHeZiHefw3jqPk/59uO0Lf/0/AUqf/zon19P5pzRSfpDy3b8XA5OSxwweNT060f4Gx9m94Ov0cXkMDRhdaPPw5Gog/+1zxqyhGQtFZbayTzQZt2fIBT799LBpEim7f3/DkmkLbXGu2y8+5JX/ISrelO8O1kuvysgtcvl27PPyEY+Q7nOo07pc0Pi1pfAJpThpL832nkQ+C+uFrWz+0Q4HLv8tnmuUboYeV5kPuNGvS+FaQrNFIGhcjLZQ0FvhOo62kdt9WgzRp9o8gDYqrjyZdSqKAK10fMwGeMdeWXaRPl67swlRlWyAK1X5P66VAsiStaUhL0ho72yCtDq9VJUtrLUtnOtEr6dT5oPgsu6BgKTvVvhlK+7bZ8q2e7a6VwTf9Wylt3XsayJrsTH++uapLh6evr+juKLqjkTborvKum3TW7nvrT/5p7BCf/Ap576IcRmKHxWpkB/uH9LCXox9+o/VDZ53napM6u7S+Xo5z6voaYtAOw1X1NUz8TB1hCagqb7ufupS31GOvdSBG/P2nSD2eiESR/pBCb+mXOuDHe0W6NOv7Ie03q8WW18WWXUgHbClz25Juc3z5W4mu1j5DKYPuRa4ysP8e6vrd0+Xr1b695nvFWnslTwvCHP5gEep+IXtOqlHd3i1GTZZ0TEBOQEd5kWE65FZWu7+g297av0UdaN93UNJIn+6qR97a7qaG+vQ=
*/