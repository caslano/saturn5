
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