
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
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
*/