
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