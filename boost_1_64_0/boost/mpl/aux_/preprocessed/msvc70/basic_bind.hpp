
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
template< bool >
struct resolve_arg_impl
{
    template<
          typename T, typename U1, typename U2, typename U3
        , typename U4, typename U5
        >
    struct result_
    {
        typedef T type;
    };
};

template<>
struct resolve_arg_impl<true>
{
    template<
          typename T, typename U1, typename U2, typename U3
        , typename U4, typename U5
        >
    struct result_
    {
        typedef typename apply_wrap5<
              T
            , U1, U2, U3, U4, U5
            >::type type;
    };
};

template< typename T > struct is_bind_template;

template<
      typename T, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg
    : resolve_arg_impl< is_bind_template<T>::value >
            ::template result_< T,U1,U2,U3,U4,U5 >
{
};

template< int arity_ > struct bind_chooser;

aux::no_tag is_bind_helper(...);
template< typename T > aux::no_tag is_bind_helper(protect<T>*);

template< int N >
aux::yes_tag is_bind_helper(arg<N>*);

template< bool is_ref_  = true >
struct is_bind_template_impl
{
    template< typename T > struct result_
    {
        BOOST_STATIC_CONSTANT(bool, value  = false);
    };
};

template<>
struct is_bind_template_impl<false>
{
    template< typename T > struct result_
    {
        BOOST_STATIC_CONSTANT(bool, value =
              sizeof(aux::is_bind_helper(static_cast<T*>(0)))
                == sizeof(aux::yes_tag)
            );
    };
};

template< typename T > struct is_bind_template
    : is_bind_template_impl< ::boost::detail::is_reference_impl<T>::value >
        ::template result_<T>
{
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
      typename F
    >
aux::yes_tag
is_bind_helper(bind0<F>*);

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
      typename F, typename T1
    >
aux::yes_tag
is_bind_helper(bind1< F,T1 >*);

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
      typename F, typename T1, typename T2
    >
aux::yes_tag
is_bind_helper(bind2< F,T1,T2 >*);

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
      typename F, typename T1, typename T2, typename T3
    >
aux::yes_tag
is_bind_helper(bind3< F,T1,T2,T3 >*);

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
    >
aux::yes_tag
is_bind_helper(bind4< F,T1,T2,T3,T4 >*);

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
    , typename T5
    >
aux::yes_tag
is_bind_helper(bind5< F,T1,T2,T3,T4,T5 >*);

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(6, bind5)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(6, bind5)
}}


/* basic_bind.hpp
L3HfeuMPuP62SbybfXlWt6/O6NJ52kU6ixzp1H6rIo2EqvuHlrRbvyPQ7IDcB7bWloEI+WZeb/n+Uig2Yh6/g0554VSOQz38LoSSL5fnleZLfcZPvmcdt/S0TvEsr/zKK/cl2rw8XaLNy/wSF3mp+w5TXomLvGSa5KX1GxA9WcdqLvtTmLbFmk/SxzfztQpUEpWYPEmONfv8Ncjn1swYdqh0/rOab0ZIv+FMyw5W1iF9f2vWqf1+hXyqQrOdbmxnAtMesOZv6bctRrAOpSBPkfmVMpElcSFP7ec1zTf87pDzwmxCY+W88L62fY+qQFT4vMb+0uzfrozzjQl5BivfKUtLT9V/b2yaav8E68pFiPP5kPwq/3x4QtJ9jzxnyZBvPezRp1t7YrCmPcrk6bHgqpxLPkgatzDv4Qbsc356Sbomjnskk83y7DaecHVr5j3sHEfV/vH4Ga41Xhdx/yhpGyJpy5XvDKZI/sdJ2orLTltMemqcOTE9MYVqgirdFxcqzS73sTwLL7yEz8L9eijTYx6eud6cl/xGt8aHFuzI/6DH/98z8nnWfHti22N7D++fcWZu/R3+7a/4bTgHSpAy/dg95gefCvz55cKA+C9y5+9u9+d7pr6qnjUfItcMLNw8vVt2h7xDP5xbwnG0xvqsfefz+Qmneh5/befXD7Z6sVmLtpf2WXusSa735T4gurq2X7UT8qy9EFvgSeyD32J/LMJb8HtMxR9wHv6Id2Exynbkupz0utjOU7KdzbKdZzAMt2A4PodR+Dym4Faci9tkey/IdnJMcv2MZ2Q76n7I3pXtHEB/PIiN8BA2wzxsi4dxFH6AYzEfY/BDTMePcAl+jOvxE9yMx/Bt/BQ/0fXfehoLkHiiXO/KdbASz6uU7Ug80ySe6RLPDInnTInnbInnXLwJ78AxOA/HYRb/zca7ZD/cjQvxHrwPF+C7uBA/wkX4Gd6HBfgAfo2LJd5L8Cw+jNWJ7yPYGP+B1+BSHIyP4jBcJulcUU2uZeUaV0lnqLJeufdsJHUfwdgUG2N7bILdVf33NccZ2AIzsSXOx9a4Gtvia9gO38L2mIsd8FPsiF9iJ9kfnSU9XdCPuHTFDtgDh2BPHI29MBqvwwl4Pc7DG3At9saN2Ad3YTi+i30xD/vjzzgAq5P2gXglDkI/vBFbYgS2x8HYC4fgAByG0Tgc5+IIXImR+ByOxK04Cj/GMXgcb8bfMBprk+9jsR3eiqE4DqVfQLmupAwR2JamX8DtUg53YgvcJfvjdeyPu3Eq7sGZuFfK3Zuy/gjCHln/PbL+yzBM1r9S9v8q7ICrMRTX4nBchxn4uKwv3CTXWmiW9fliN1lfrNSpxWEQxmNvNGM8JqC9P8ViWU+KrEfdn+I0iVcSdsNkjEMLrveyjm6Ti3q6nPm+TnV16cUXr76up4s6u5ce8jHlEtzV3eUUl9bf7ZvvW6k6vAPF2nq8IrarrssrZP2ZaMr2qXSdXtBobb3emWJb3V4L1u2ufi8s26fK6/jUbYLbnNLW9aVn+1RZfV/EKc/q/La8WnX1fouzfS5K3Z+9nXDPTfQjSLidkEPIJRQT/LngDCOYnzbqBY3BGIzBGIzBGIzBGIyh6oeLVP/f01r9XwX1/1HlvP/flBHLbl39+dD+o3t60Q5dX8f0cLBndYjViWG/Mvr+a85Ijqu4xUSOGnxzzNCBY2MG3zRoRIXjeb8X8bTX1S2tro8ngZG83U71t17no7VepIL5OMhel+jjHL/Wysgep/hVKi+tca1gXjrei/Bx7tdgL+sJ3aOv91Qi6nk+6vdztsRNXd5WS116R9l2e0Jb5Vhwue3Syi9v+p3wtu7VUsl6LnU5yPI=
*/