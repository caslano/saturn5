
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
}}


/* bind.hpp
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
*/