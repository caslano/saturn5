
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