
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
      typename F
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
      typename F
    >
struct bind< F,na,na,na,na,na >
    : bind0<F>
{
};

template<
      typename F, typename T1
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
      typename F, typename T1
    >
struct bind< F,T1,na,na,na,na >
    : bind1< F,T1 >
{
};

template<
      typename F, typename T1, typename T2
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
      typename F, typename T1, typename T2
    >
struct bind< F,T1,T2,na,na,na >
    : bind2< F,T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3
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
      typename F, typename T1, typename T2, typename T3
    >
struct bind< F,T1,T2,T3,na,na >
    : bind3< F,T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
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
    >
struct bind< F,T1,T2,T3,T4,na >
    : bind4< F,T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
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
    , typename T5
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

template<
      template< typename T1, typename T2, typename T3 > class F, typename Tag
    >
struct quote3;

template< typename T1, typename T2, typename T3 > struct eval_if;

template<
      typename Tag, typename T1, typename T2, typename T3
    >
struct bind3<
      quote3< eval_if,Tag >
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
        typedef typename eval_if<
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