
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

}}


/* bind.hpp
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
*/