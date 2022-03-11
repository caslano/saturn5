
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