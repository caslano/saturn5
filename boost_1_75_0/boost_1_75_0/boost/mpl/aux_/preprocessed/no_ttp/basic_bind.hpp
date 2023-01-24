
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
+gH1bg8MO9fYx5hOI6Eq5Oz9cFWzGLlfJ9LBA9WnvC4U6Bz2xM8eSr/vt9ztfyG7epe/NdZhCbjxfWH6FTnpCUhpLhUzDTYdPU+enJW7pT5np1IZ8zTwfnNkEOVT5Lv35zx9a2/2bsbz5bDB2oLeZq2qQ0Z4qxyynUz2dNue6/zlOuAKuKQL5IlfhL4yU9WJFWv5hw7iFU7UlM5Rt0RM7hfyUwonS+Oy3d9kfR3jUaxbKwczUOa8h5/iBPDngptz4ofXCzN8csJwDDkGMgSWv8oUiTEq5y0q/G3yXDyTIhLxrnNYbGvGPaFouM7y6xfTuh6uwPK20KuB5s/D5nb9x6sohKffbJNW7IlsBxbsD9556P/g/XbXJIafAex9s0FzyS0eFGf4drN51rRQuFvAe1by15rEvolH6lrlGsPgghvmsvAWoQ8j6pGX6LMl8hLLD0FmUvRYyGAeGUhg4KJFfAzh3p2jSVW9ejnxXaFRYMPRUzxzZmJ7ZsND1CilUtowfs/RJJ3fc7/tGU/16G4dUvSmwos7k648ZWyuSIOHC7ZQ5FcafkOZrqVKlRavbsaeeVXkQ3icmUlD7ggoN6fJXZJPH9ytZarIQa2mPfccZn+bMbJkPuA/6YIzsvj2LyPsyG9h1WxiKVyW7otPvRjcfM0wovBQchovHKxBH6xSCTuyPiFuXu/sbzz11ZkSSwHIrqB572WoJpd4szc4
*/