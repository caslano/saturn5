
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F
    >
struct apply0

    : apply_wrap0<
          typename lambda<F>::type
       
        >
{
};

template<
      typename F
    >
struct apply< F,na,na,na,na,na >
    : apply0<F>
{
};

template<
      typename F, typename T1
    >
struct apply1

    : apply_wrap1<
          typename lambda<F>::type
        , T1
        >
{
};

template<
      typename F, typename T1
    >
struct apply< F,T1,na,na,na,na >
    : apply1< F,T1 >
{
};

template<
      typename F, typename T1, typename T2
    >
struct apply2

    : apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >
{
};

template<
      typename F, typename T1, typename T2
    >
struct apply< F,T1,T2,na,na,na >
    : apply2< F,T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

    : apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >
{
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply< F,T1,T2,T3,na,na >
    : apply3< F,T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

    : apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply< F,T1,T2,T3,T4,na >
    : apply4< F,T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

    : apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >
{
};

/// primary template (not a specialization!)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply
    : apply5< F,T1,T2,T3,T4,T5 >
{
};

}}


/* apply.hpp
GheOOK17IJVl/escpNpncXAFmf/k5bRvaO5ezjYxZD2+a+TKRNxhteZVZZXEka0SCZYehxg/LtovngxshGiSbtdG0kVEiMy4tQwzVXcwAbSyxugWXc/8BUXK2zzNHcaWKrBhscEbppJlCTXTECV/fs+rlRfsECimHg/jVeVAr4AK/Xr494vPkt539L86VHFVaa9oRInXo4HGY2dK2Dvkf8e9TnNniHs//gP32hxadfT9C+6V9O+4l/BfcC/t0rHev+FeQwP/gXvN/wX3alrREdNpbhVPdjApA3QR6aIzpfdWY2CNlsR0KK6U17apnsi/yFyXzQlrYdnjFwyyn69jQJmbYPM19rqNrx73MTo9R5vgdSpaOxfFuxnhvSRLbshWFnxbH7uABMNCwX3YJ9taB01vuaIswXZ1BFWLdv9me6UMtzUffVrcUzNtq4oVSnzOl69GDjeWwq5TvmtD8VBkSq3DPHxrEOhJvjfiFsgB1bGBHW/XDVx0jxtUn9Si6fJZjpVnrdbUJ7PM+1knr7udTj+WWVr7tYs/2tAImqPZaVN1yz8Q1EjsklZCuQ+9Ytfam1ecknx5JbG2sHq6MnID3JoW7EPCdr2gO4Z8fQERxP308nzqUmVbmnKf++uEhJqaqbUyGBSSqUyo0zBVM2Ny0r5h2/BbFGIrZXOoYrorz3Ykvogajk/f0YCHplncrk1mD5ppi7sDHAQTDwvL
*/