
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

}}


/* basic_bind.hpp
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
*/