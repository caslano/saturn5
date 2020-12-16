
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F

    , typename has_apply_ = typename aux::has_apply<F>::type

    >
struct apply_wrap0

{
    typedef typename F::template apply<
        
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap0<int>
{
    typedef int type;
};

template<
      typename F, typename T1

    >
struct apply_wrap1

{
    typedef typename F::template apply<
         T1
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap1< int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2

    >
struct apply_wrap2

{
    typedef typename F::template apply<
         T1, T2
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap2< int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3

    >
struct apply_wrap3

{
    typedef typename F::template apply<
         T1, T2, T3
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap3< int,int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4

    >
struct apply_wrap4

{
    typedef typename F::template apply<
         T1, T2, T3, T4
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap4< int,int,int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5

    >
struct apply_wrap5

{
    typedef typename F::template apply<
         T1, T2, T3, T4, T5
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap5< int,int,int,int,int,int >
{
    typedef int type;
};

}}


/* apply_wrap.hpp
vBGjMAbHoBlvxtvxFrwLo3EljsVVeKvsp3H4Dt6Gn2MM/oixWIJx6EP+xeOVaMZWmIBdcRL2xsk4BKfgzZiI8TgVk3EazsHpuACT8BFMxrWYgjlokf2XaZK6NZwkx20ttH/DcKkcf8vwKlyOLXEFtse12AXXYRhuwIH4FN6Im3A4Po234PMYjy+YpPyYpH4Mq8n52l8pP7L9T6T8fIrN8DMMxQKMwC9wPB7HaXgCl+NXuBK/xnX4DW7FQnwBT+JO/BZfx+8wD4vwMH6Pn2AxFuBPWII/4zk8LfmXZ5J6LHxc4h/Iv/dJ/H+T+JdgUzyLXfEc9sA/cBCexzFoqs75CqrhZKyOFvTBTKyBd+DluABrofUeHrdjHdyFdTEP/bAQA3A2cWuAczEIs7AhrsJGuAaD8SdrX8pSR4SPSbm4AofZ2wsyX228FwNwAQbjA5iFi3EhPoj/wIdwGWbL+mm/I3U0St2Nbf09lHxDZXhUfqeXYVNcjh1wJV6Lq7AvrsahmIMj8XGcgU/iw7he8mcDvoxP4Wu4CT/Gp/E4bsZz+AxWJw7PYnt8HkNxK/bBF/AWfBEn4Us4HV/GhfgKLsYduAJfxY34GubiTjyIu/Asvo7sa9Mb2AZ3Y0fcg/1wL8bjmzgD38K7cB8+gW/jRvwnvozv4AnMxZP4L/Qjf/djfXwXW+MB7IMH8VY8hOMxDyfg+zgdD2MmHsGH8SPMwaP4Kn6Mu/HfaPtuodTh4EA5HtTfLRwr5eZWDMDx2Ahvk/08AcMwBvtjHA7EeNnPE3ESmjEJJ+HtOBnvxSmYg4m4EZNwK1pwF87AdzEVj2Eafo8Z6ENcZ+LlmIkBOBtDcQ52wzswDOdhX7xT0p1lkjobfE+Ol9qYLul+Rc6j2zEAX8NeuBOjcBdG4xsYh7txDu7BR3EvrsS3cB3uw+34T3wX30HJf6ljoe7FRf7vl/a9B7AJvoctMQ/D8H28BQ/jBMxHMx7BBfghLsGjuB4/xmfx3xKPT/Awforf4Wd4Cj/HWsSlAOvgcfTHL7EjnsAI/AqHYCFG4klMxO8wC3/AZfgjrsRiSTe/u1Jfwrol3W349zC0ljuTlDvJ/3HYCMdjM5yAHTEGu2MsDsc42T8TMQbNOBUTMBUn4f04GR/GRHwMp+JqnIZP4nTcgsm4D1PwGFrwS0zDIkzHc5gh+TQTA3GW5MccHIu3YxzegbNxHt4h7dHvxHtwEd6L2bgAn8GF+Dzeh9twMR7AJfg+PoQfYzZ+hg+X5q/U1yj1OM75u0Z+59ahP+ZgI3wc2+ETGIpPYiSux7G4AWPwKbwTN+IC3ISL8GnMxs24DJ/BtbgF38fn8CN8Hj/HrfgNbsNT+KJcj7+EfvgyBuErGILbsTW+ih3xNeyNu3A4vo7j8Q2chrtxDu7B+3EvPoZv4mZ8C1/EfXgY/4k/4jv4C+ZideW8jL64H3+ylgOp/8FZcv64Es1y3B6U/D0k+ZuH7fF97IKH8Vr8AIdjPk7EIzgNP0QLfoRpeFS2y3WA1NlY63LYru1dgVrSdvO8/A6bfDg/QzXsg9VxMPrgCKyBE9AX0/EytF6n4L14BS7HmrgG/4ab8ErcirVwJ9bG17EOFmJdPIV+WIu41UN/DMCrsQG2wUDsiFdhX2yIo7ARTsRgnIlNcCFeja9iCH6HTbEaaW6Gl2NzDMYW2BRbYkdshWHYBkdiWxyHHTEOO+FdGIqPYxfcjF3xbbwG92N3PIU98FfsiWexF5IXpuuwEV6PYRiGffEGHIG98S7sg/dgOG7GvrgFB+BOHIRv4Y14CAfjhzgMv8Lh+D3ehJex/0dgTYxE2/2B1AnhYy7uD6KYrzaOQX+8Ba/BaOw=
*/