
// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      int N, typename F
    >
struct apply_wrap_impl0;

template< typename F, bool F_has_apply >
struct apply_wrap_impl0_bcb {
    typedef typename F::template apply<na> type;
};

template< typename F >
struct apply_wrap_impl0_bcb< F,true > {
    typedef typename F::apply type;
};

template<
      typename F
    >
struct apply_wrap_impl0<
          0
        , F
       
        >
{
    typedef apply_wrap_impl0_bcb< F, aux::has_apply<F>::value >::type type;
};

template<
      typename F
    >
struct apply_wrap_impl0<
          1
        , F
       
        >
{
    typedef typename F::template apply<
         
        na
        > type;
};

template<
      typename F
    >
struct apply_wrap_impl0<
          2
        , F
       
        >
{
    typedef typename F::template apply<
         
        na, na

        > type;
};

template<
      typename F
    >
struct apply_wrap_impl0<
          3
        , F
       
        >
{
    typedef typename F::template apply<
         
        na, na, na

        > type;
};

template<
      typename F
    >
struct apply_wrap_impl0<
          4
        , F
       
        >
{
    typedef typename F::template apply<
         
        na, na, na, na

        > type;
};

template<
      typename F
    >
struct apply_wrap_impl0<
          5
        , F
       
        >
{
    typedef typename F::template apply<
         
        na, na, na, na, na

        > type;
};

template<
      typename F
    >
struct apply_wrap0
    : apply_wrap_impl0<
          ::boost::mpl::aux::arity< F,0 >::value
        , F
       
        >::type
{
};

template<
      int N, typename F, typename T1
    >
struct apply_wrap_impl1;

template<
      typename F, typename T1
    >
struct apply_wrap_impl1<
          1
        , F
        , T1
        >
{
    typedef typename F::template apply<
          T1
        > type;
};

template<
      typename F, typename T1
    >
struct apply_wrap_impl1<
          2
        , F
        , T1
        >
{
    typedef typename F::template apply<
          T1
        , na

        > type;
};

template<
      typename F, typename T1
    >
struct apply_wrap_impl1<
          3
        , F
        , T1
        >
{
    typedef typename F::template apply<
          T1
        , na, na

        > type;
};

template<
      typename F, typename T1
    >
struct apply_wrap_impl1<
          4
        , F
        , T1
        >
{
    typedef typename F::template apply<
          T1
        , na, na, na

        > type;
};

template<
      typename F, typename T1
    >
struct apply_wrap_impl1<
          5
        , F
        , T1
        >
{
    typedef typename F::template apply<
          T1
        , na, na, na, na

        > type;
};

template<
      typename F, typename T1
    >
struct apply_wrap1
    : apply_wrap_impl1<
          ::boost::mpl::aux::arity< F,1 >::value
        , F
        , T1
        >::type
{
};

template<
      int N, typename F, typename T1, typename T2
    >
struct apply_wrap_impl2;

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap_impl2<
          2
        , F
        , T1, T2
        >
{
    typedef typename F::template apply<
          T1, T2

        > type;
};

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap_impl2<
          3
        , F
        , T1, T2
        >
{
    typedef typename F::template apply<
          T1, T2

        , na

        > type;
};

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap_impl2<
          4
        , F
        , T1, T2
        >
{
    typedef typename F::template apply<
          T1, T2

        , na, na

        > type;
};

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap_impl2<
          5
        , F
        , T1, T2
        >
{
    typedef typename F::template apply<
          T1, T2

        , na, na, na

        > type;
};

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap2
    : apply_wrap_impl2<
          ::boost::mpl::aux::arity< F,2 >::value
        , F
        , T1, T2
        >::type
{
};

template<
      int N, typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap_impl3;

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap_impl3<
          3
        , F
        , T1, T2, T3
        >
{
    typedef typename F::template apply<
          T1, T2, T3

        > type;
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap_impl3<
          4
        , F
        , T1, T2, T3
        >
{
    typedef typename F::template apply<
          T1, T2, T3

        , na

        > type;
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap_impl3<
          5
        , F
        , T1, T2, T3
        >
{
    typedef typename F::template apply<
          T1, T2, T3

        , na, na

        > type;
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap3
    : apply_wrap_impl3<
          ::boost::mpl::aux::arity< F,3 >::value
        , F
        , T1, T2, T3
        >::type
{
};

template<
      int N, typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply_wrap_impl4;

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply_wrap_impl4<
          4
        , F
        , T1, T2, T3, T4
        >
{
    typedef typename F::template apply<
          T1, T2, T3, T4

        > type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply_wrap_impl4<
          5
        , F
        , T1, T2, T3, T4
        >
{
    typedef typename F::template apply<
          T1, T2, T3, T4

        , na

        > type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply_wrap4
    : apply_wrap_impl4<
          ::boost::mpl::aux::arity< F,4 >::value
        , F
        , T1, T2, T3, T4
        >::type
{
};

template<
      int N, typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply_wrap_impl5;

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply_wrap_impl5<
          5
        , F
        , T1, T2, T3, T4, T5
        >
{
    typedef typename F::template apply<
          T1, T2, T3, T4, T5

        > type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply_wrap5
    : apply_wrap_impl5<
          ::boost::mpl::aux::arity< F,5 >::value
        , F
        , T1, T2, T3, T4, T5
        >::type
{
};

}}


/* apply_wrap.hpp
1DyyXq1bilbFIwtX8JAE9TPVKS8o59jFwqpJ5jRMjWIoZLlWs8mpvtJwWPGumY1i6fh/WlWpGOca8mi8Sh+B0alwXD3mk9+LCkzBuFArY/HJgzGsBhWXb4tvTqkcVevDkUU28iSzoRRoxtZUf87GzDRY1spYoWmG4nxdt7jinoVKeWRiJDM/z1jlRk6N5NpkFzQQQO54xcOBerG3hRaQaosDDFYalCaFTbNykIOjoa8zuclGQoWMRSzrD6GdtpKUslpXEtpjvJNn71qZTWpKobo815QrALhqkGmXkFcb11PcCn5VOTKmepxPWiH7mSYee0uaTWyZL5UU5/Z2ctWmTbLBYCagA8Wo9u3deEu++Gqa5ZitQUCRmoQkBMO+5zQ8YnSAIK7wHtinz7Rp03pT+L0ttkl9jJYse5+Jhim9sx25Zp3zKzyc/U1hfZxMtlmKv19OjJUqExGTccfr8rAH3qQz6wRdnM6gs+mMumkiNYETBTpdZ4ULi24SfhvwO1uXo8uCLFVnAmcqexLdJuPJwp4RApPc60oW0zctE2nURegSddG64UhJgi6GO0BaknSj6HkM4oqBy2TcSWqXkIzHnYbnUaI0Cb/5FTUQ9WOTTPWvBT8dbPPpG9/6f/Xr9BHFF549/Fj/OfdNTV2emWBcGL3kl42tnxn/w4KdSS0MMbnLGs6aGfzeivBv5r/1aKPKJzp1njA5cXbah6bVpzJ2+NrHlnq/tPTGxeb5xzoO2nv1TOSQ84GbBr/ZzfJ+k4+H5zS4v/vN9uv2rIlyu9PsyN+Lvh/6t/oHPuhTNrHDRx7Xvv6sMOW7H+e+YtvWd9QjPZ9se3bKAy3jHSOfL3/Y3Wfz9f0VEXlNRx8/4bfy9eQNt60Dnp4xcF6X3bv+cte134NdxzwV1Ouhn9deWbzqtXqf99BPMr9z9Jzuy9OXntsSkNXKZdi4y4tebhwW2m5ryO8l78Z5pb+9/WTvQ7c+if3ihfXTPF8Usn97fN+ruj9x2bJC/dkyiR70m60T4LL6dLvjjg7roJ/bRNBbp3jry63eesHmrQ80e+sr7aC4M/A72eGtt+Iuwl1TfEVwVwJ5YS7cIQy9HbcFv3G3oPhcdP97FzdbtoYzV/x8Wi2wwW5gd7qBeVCAA610Y2dHDxT8uxrZCX18bTkdwjqQ/ZZWbsUUSIuLwGJ+RZ5Tr7pRCr9KX7RCTMlivFxTEPtJv4Ol3yZyBJHqGWLqJ5jYF/9yeDiCf3zi2Ahs8xOSU1MVyyt4oqptdKDvrAj+WAFpyDdzbRtlsE/WuhOPHsUvigEc6Vs9El8TCl2pBrND4Jt/AgtEXlCo2l2ajS2ZsQnD2d40csWuyCi1O+1VslSt1+40n1LfWz13eK25oL/po5k71PB8cFeC17CVzPPFfdutvYon4PZ3V/P8mDuNX3/cdzW8ANzuLSRe1XyeHs+gBaDjyK5rymdt88TDLmgmiPNSGaAUdpXsAnjKealwpAvz8NpzMcBTnKEAN+Cp9rgL4PF9727MDe5ABY9faeBpw8twEp6VeDyd/siTco60sMV/bj4qD7cJt5HdudYgnUiniDRninTmUi7sJNaUF6F832GHzksqL4XjkPR7ON96CcxKh3Wmi9aZKu9TH56fl6UIkx5RJqmWfFuWSXom/+yLShRArXEvK3tyrd8Bkx/tQgJaX26VBgXpuUbGo1Gk+FqH9pOlw69qAy/2ZIk8hn3pitW+bJ0YE9CQWP2cbqdZJgWfutH0rIxEy7Mhlqqz4cCW5o3SHRaWbM7LzM8xYwjD5pGkV7FUvlI+wdU+Y1jP/Wbl2uWRNvHYy2qKvyos1tzQIVbyM942q57tbAswnV5NYTFs5ck=
*/