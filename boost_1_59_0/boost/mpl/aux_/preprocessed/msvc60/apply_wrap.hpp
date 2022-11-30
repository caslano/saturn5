
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template< typename F>
struct msvc_apply0
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template< typename P  = int > struct apply
        {
            typedef int type;
        };
    };

    template< typename T  = int > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply<>
    {
    };

};

template<
      typename F
    >
struct apply_wrap0
{
    typedef typename msvc_apply0<F>::template result_<
         
        >::type type;
};

/// workaround for ETI bug
template<>
struct apply_wrap0<int>
{
    typedef int type;
};

template< typename F>
struct msvc_apply1
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template< typename P1 > struct apply
        {
            typedef int type;
        };
    };

    template< typename T1 > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply<T1>
    {
    };
};

template<
      typename F, typename T1
    >
struct apply_wrap1
{
    typedef typename msvc_apply1<F>::template result_<
          T1
        >::type type;
};

/// workaround for ETI bug
template<>
struct apply_wrap1< int,int >
{
    typedef int type;
};

template< typename F>
struct msvc_apply2
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template< typename P1, typename P2 > struct apply
        {
            typedef int type;
        };
    };

    template< typename T1, typename T2 > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply< T1,T2 >
    {
    };
};

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap2
{
    typedef typename msvc_apply2<F>::template result_<
          T1, T2
        >::type type;
};

/// workaround for ETI bug
template<>
struct apply_wrap2< int,int,int >
{
    typedef int type;
};

template< typename F>
struct msvc_apply3
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template< typename P1, typename P2, typename P3 > struct apply
        {
            typedef int type;
        };
    };

    template< typename T1, typename T2, typename T3 > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply< T1,T2,T3 >
    {
    };
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap3
{
    typedef typename msvc_apply3<F>::template result_<
          T1, T2, T3
        >::type type;
};

/// workaround for ETI bug
template<>
struct apply_wrap3< int,int,int,int >
{
    typedef int type;
};

template< typename F>
struct msvc_apply4
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template<
              typename P1, typename P2, typename P3, typename P4
            >
        struct apply
        {
            typedef int type;
        };
    };

    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply< T1,T2,T3,T4 >
    {
    };
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply_wrap4
{
    typedef typename msvc_apply4<F>::template result_<
          T1, T2, T3, T4
        >::type type;
};

/// workaround for ETI bug
template<>
struct apply_wrap4< int,int,int,int,int >
{
    typedef int type;
};

template< typename F>
struct msvc_apply5
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template<
              typename P1, typename P2, typename P3, typename P4
            , typename P5
            >
        struct apply
        {
            typedef int type;
        };
    };

    template<
          typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply< T1,T2,T3,T4,T5 >
    {
    };
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply_wrap5
{
    typedef typename msvc_apply5<F>::template result_<
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
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
*/