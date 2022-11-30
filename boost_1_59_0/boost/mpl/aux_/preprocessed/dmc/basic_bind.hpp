
// Copyright Peter Dimov 2001
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/basic_bind.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template<
      typename T, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg
{
    typedef T type;
};

template<
      int N, typename U1, typename U2, typename U3, typename U4, typename U5
    >
struct resolve_bind_arg< arg<N>, U1, U2, U3, U4, U5 >
{
    typedef typename apply_wrap5<mpl::arg<N>, U1, U2, U3, U4, U5>::type type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg< bind< F,T1,T2,T3,T4,T5 >, U1, U2, U3, U4, U5 >
{
    typedef bind< F,T1,T2,T3,T4,T5 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

template<
      typename F, int dummy_
    >
struct bind0
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;

     public:
        typedef typename apply_wrap0<
              f_
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg<
      bind0<F>, U1, U2, U3, U4, U5
    >
{
    typedef bind0<F> f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(1, bind0)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(1, bind0)

template<
      typename F, int dummy_
    >
struct bind< F,na,na,na,na,na >
    : bind0<F>
{
};

template<
      typename F, typename T1, int dummy_
    >
struct bind1
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;

     public:
        typedef typename apply_wrap1<
              f_
            , typename t1::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename U1, typename U2, typename U3
    , typename U4, typename U5
    >
struct resolve_bind_arg<
      bind1< F,T1 >, U1, U2, U3, U4, U5
    >
{
    typedef bind1< F,T1 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(2, bind1)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(2, bind1)

template<
      typename F, typename T1, int dummy_
    >
struct bind< F,T1,na,na,na,na >
    : bind1< F,T1 >
{
};

template<
      typename F, typename T1, typename T2, int dummy_
    >
struct bind2
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;

     public:
        typedef typename apply_wrap2<
              f_
            , typename t1::type, typename t2::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename U1, typename U2
    , typename U3, typename U4, typename U5
    >
struct resolve_bind_arg<
      bind2< F,T1,T2 >, U1, U2, U3, U4, U5
    >
{
    typedef bind2< F,T1,T2 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(3, bind2)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(3, bind2)

template<
      typename F, typename T1, typename T2, int dummy_
    >
struct bind< F,T1,T2,na,na,na >
    : bind2< F,T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, int dummy_
    >
struct bind3
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;

     public:
        typedef typename apply_wrap3<
              f_
            , typename t1::type, typename t2::type, typename t3::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename T3, typename U1
    , typename U2, typename U3, typename U4, typename U5
    >
struct resolve_bind_arg<
      bind3< F,T1,T2,T3 >, U1, U2, U3, U4, U5
    >
{
    typedef bind3< F,T1,T2,T3 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(4, bind3)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(4, bind3)

template<
      typename F, typename T1, typename T2, typename T3, int dummy_
    >
struct bind< F,T1,T2,T3,na,na >
    : bind3< F,T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , int dummy_
    >
struct bind4
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;
        typedef aux::resolve_bind_arg< T4,U1,U2,U3,U4,U5 > t4;

     public:
        typedef typename apply_wrap4<
              f_
            , typename t1::type, typename t2::type, typename t3::type
            , typename t4::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename U1, typename U2, typename U3, typename U4, typename U5
    >
struct resolve_bind_arg<
      bind4< F,T1,T2,T3,T4 >, U1, U2, U3, U4, U5
    >
{
    typedef bind4< F,T1,T2,T3,T4 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(5, bind4)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(5, bind4)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , int dummy_
    >
struct bind< F,T1,T2,T3,T4,na >
    : bind4< F,T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5, int dummy_
    >
struct bind5
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;
        typedef aux::resolve_bind_arg< T4,U1,U2,U3,U4,U5 > t4;
        typedef aux::resolve_bind_arg< T5,U1,U2,U3,U4,U5 > t5;

     public:
        typedef typename apply_wrap5<
              f_
            , typename t1::type, typename t2::type, typename t3::type
            , typename t4::type, typename t5::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg<
      bind5< F,T1,T2,T3,T4,T5 >, U1, U2, U3, U4, U5
    >
{
    typedef bind5< F,T1,T2,T3,T4,T5 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(6, bind5)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(6, bind5)

/// primary template (not a specialization!)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5, int dummy_
    >
struct bind
    : bind5< F,T1,T2,T3,T4,T5 >
{
};

/// if_/eval_if specializations
template< template< typename T1, typename T2, typename T3 > class F, typename Tag >
struct quote3;

template< typename T1, typename T2, typename T3 > struct if_;

template<
      typename Tag, typename T1, typename T2, typename T3
    >
struct bind3<
      quote3< if_,Tag >
    , T1, T2, T3
    >
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef mpl::arg<1> n1;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;
        typedef typename if_<
              typename t1::type
            , t2, t3
            >::type f_;

     public:
        typedef typename f_::type type;
    };
};

}}


/* basic_bind.hpp
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
*/