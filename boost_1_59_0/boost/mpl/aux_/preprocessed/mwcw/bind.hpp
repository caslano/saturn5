
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