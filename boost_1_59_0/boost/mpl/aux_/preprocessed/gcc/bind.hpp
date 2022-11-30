
// Copyright Peter Dimov 2001
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bind.hpp" header
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
      typename T
    , typename Arg
    >
struct replace_unnamed_arg
{
    typedef Arg next;
    typedef T type;
};

template<
      typename Arg
    >
struct replace_unnamed_arg< arg< -1 >, Arg >
{
    typedef typename Arg::next next;
    typedef Arg type;
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
        typedef aux::replace_unnamed_arg< F, mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg< a0,U1,U2,U3,U4,U5 >::type f_;
        ///
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
        typedef aux::replace_unnamed_arg< F, mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg< a0,U1,U2,U3,U4,U5 >::type f_;
        ///
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
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
        typedef aux::replace_unnamed_arg< F, mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg< a0,U1,U2,U3,U4,U5 >::type f_;
        ///
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
        typedef aux::replace_unnamed_arg< T2,n2 > r2;
        typedef typename r2::type a2;
        typedef typename r2::next n3;
        typedef aux::resolve_bind_arg< a2,U1,U2,U3,U4,U5 > t2;
        ///
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
        typedef aux::replace_unnamed_arg< F, mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg< a0,U1,U2,U3,U4,U5 >::type f_;
        ///
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
        typedef aux::replace_unnamed_arg< T2,n2 > r2;
        typedef typename r2::type a2;
        typedef typename r2::next n3;
        typedef aux::resolve_bind_arg< a2,U1,U2,U3,U4,U5 > t2;
        ///
        typedef aux::replace_unnamed_arg< T3,n3 > r3;
        typedef typename r3::type a3;
        typedef typename r3::next n4;
        typedef aux::resolve_bind_arg< a3,U1,U2,U3,U4,U5 > t3;
        ///
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
        typedef aux::replace_unnamed_arg< F, mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg< a0,U1,U2,U3,U4,U5 >::type f_;
        ///
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
        typedef aux::replace_unnamed_arg< T2,n2 > r2;
        typedef typename r2::type a2;
        typedef typename r2::next n3;
        typedef aux::resolve_bind_arg< a2,U1,U2,U3,U4,U5 > t2;
        ///
        typedef aux::replace_unnamed_arg< T3,n3 > r3;
        typedef typename r3::type a3;
        typedef typename r3::next n4;
        typedef aux::resolve_bind_arg< a3,U1,U2,U3,U4,U5 > t3;
        ///
        typedef aux::replace_unnamed_arg< T4,n4 > r4;
        typedef typename r4::type a4;
        typedef typename r4::next n5;
        typedef aux::resolve_bind_arg< a4,U1,U2,U3,U4,U5 > t4;
        ///
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
        typedef aux::replace_unnamed_arg< F, mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next n1;
        typedef typename aux::resolve_bind_arg< a0,U1,U2,U3,U4,U5 >::type f_;
        ///
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
        typedef aux::replace_unnamed_arg< T2,n2 > r2;
        typedef typename r2::type a2;
        typedef typename r2::next n3;
        typedef aux::resolve_bind_arg< a2,U1,U2,U3,U4,U5 > t2;
        ///
        typedef aux::replace_unnamed_arg< T3,n3 > r3;
        typedef typename r3::type a3;
        typedef typename r3::next n4;
        typedef aux::resolve_bind_arg< a3,U1,U2,U3,U4,U5 > t3;
        ///
        typedef aux::replace_unnamed_arg< T4,n4 > r4;
        typedef typename r4::type a4;
        typedef typename r4::next n5;
        typedef aux::resolve_bind_arg< a4,U1,U2,U3,U4,U5 > t4;
        ///
        typedef aux::replace_unnamed_arg< T5,n5 > r5;
        typedef typename r5::type a5;
        typedef typename r5::next n6;
        typedef aux::resolve_bind_arg< a5,U1,U2,U3,U4,U5 > t5;
        ///
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
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
        typedef aux::replace_unnamed_arg< T2,n2 > r2;
        typedef typename r2::type a2;
        typedef typename r2::next n3;
        typedef aux::resolve_bind_arg< a2,U1,U2,U3,U4,U5 > t2;
        ///
        typedef aux::replace_unnamed_arg< T3,n3 > r3;
        typedef typename r3::type a3;
        typedef typename r3::next n4;
        typedef aux::resolve_bind_arg< a3,U1,U2,U3,U4,U5 > t3;
        ///
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
        typedef aux::replace_unnamed_arg< T1,n1 > r1;
        typedef typename r1::type a1;
        typedef typename r1::next n2;
        typedef aux::resolve_bind_arg< a1,U1,U2,U3,U4,U5 > t1;
        ///
        typedef aux::replace_unnamed_arg< T2,n2 > r2;
        typedef typename r2::type a2;
        typedef typename r2::next n3;
        typedef aux::resolve_bind_arg< a2,U1,U2,U3,U4,U5 > t2;
        ///
        typedef aux::replace_unnamed_arg< T3,n3 > r3;
        typedef typename r3::type a3;
        typedef typename r3::next n4;
        typedef aux::resolve_bind_arg< a3,U1,U2,U3,U4,U5 > t3;
        ///
        typedef typename eval_if<
              typename t1::type
            , t2, t3
            >::type f_;

     public:
        typedef typename f_::type type;
    };
};

}}


/* bind.hpp
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
*/