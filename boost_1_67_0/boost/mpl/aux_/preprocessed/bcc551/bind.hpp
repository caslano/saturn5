
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