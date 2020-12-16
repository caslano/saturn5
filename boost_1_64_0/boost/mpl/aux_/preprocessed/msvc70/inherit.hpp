
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/inherit.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C1, bool C2 >
struct inherit2_impl
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T1, T2
    {
        typedef Derived type_;
    };
};

template<>
struct inherit2_impl< false,true >
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T1
    {
        typedef T1 type_;
    };
};

template<>
struct inherit2_impl< true,false >
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T2
    {
        typedef T2 type_;
    };
};

template<>
struct inherit2_impl< true,true >
{
    template< typename Derived, typename T1, typename T2 > struct result_
    {
        typedef T1 type_;
    };
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct inherit2
    : aux::inherit2_impl<
          is_empty_base<T1>::value
        , is_empty_base<T2>::value
        >::template result_< inherit2< T1,T2 >,T1, T2 >
{
    typedef typename inherit2::type_ type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1, T2))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit2)

template<
      typename T1 = na, typename T2 = na, typename T3 = na
    >
struct inherit3
    : inherit2<
          typename inherit2<
              T1, T2
            >::type
        , T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , inherit3
        , ( T1, T2, T3)
        )
};

BOOST_MPL_AUX_NA_SPEC(3, inherit3)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    >
struct inherit4
    : inherit2<
          typename inherit3<
              T1, T2, T3
            >::type
        , T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , inherit4
        , ( T1, T2, T3, T4)
        )
};

BOOST_MPL_AUX_NA_SPEC(4, inherit4)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    , typename T5 = na
    >
struct inherit5
    : inherit2<
          typename inherit4<
              T1, T2, T3, T4
            >::type
        , T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , inherit5
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC(5, inherit5)

/// primary template

template<
      typename T1 = empty_base, typename T2 = empty_base
    , typename T3 = empty_base, typename T4 = empty_base
    , typename T5 = empty_base
    >
struct inherit
    : inherit5< T1,T2,T3,T4,T5 >
{
};

template<>
struct inherit< na,na,na,na,na >
{
    template<

          typename T1 = empty_base, typename T2 = empty_base
        , typename T3 = empty_base, typename T4 = empty_base
        , typename T5 = empty_base

        >
    struct apply
        : inherit< T1,T2,T3,T4,T5 >
    {
    };
};

BOOST_MPL_AUX_NA_SPEC_LAMBDA(5, inherit)
BOOST_MPL_AUX_NA_SPEC_ARITY(5, inherit)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(5, 5, inherit)
}}


/* inherit.hpp
5w8LxZnVvj8sGF/Yttd/OXuXG/nBDr9+dnxhJ15HlyTO7a6dPcxrwxcW8oHpfWDHPw23RBzDP4iMRnKRFcdCfq7QETpCR+gIHaEjdISO0BE6Qkfo+CUf58j/n2d3uP/P3P9f3sLijkdOk++u65B6yFrkMs33ebFX/H/miIwpzhXX86xZuVb/8cgu//IMLU6cjdxV/7LmLHS6jcV3KOck0NHLN7tb9EsR/UYgw9Bv6SV6/bQ9UAOJAzbSTV1/OlHmKZwnZTZEEimzSl+mc5FtzVuanR/QeuG6sn3qWy1lJ0vZw6U9qvVl0yHsttMts6nSFsU273YQd60jhnxGB3QpCENHSqMP5pZ4z+l4Rnz4pUgTpFjTGX3TBuj1ze+X69dvXpOuX+NIybfzW3TFnav1GdKovvS5hJY7dR+BHmEO3Tmrqe5j6xOiyOhwdBcma+1soHsR7RvY/vONHXlHX0YeUPOpN3T+u0vq+P6DLHLu5CDXuX59XedS3Of6DnCd+3Kg+1x/R5twLn0w55zbCDApqMjqvnaA5zzamtrylGtOivyuVtd/EFt+3FJ87/jJFzvLs2xt5bN/hXzOulbafh4yUrs3hxrbLzO3H0UEPjfFaOyoPh+9aHRXXSJ9+sW3qu5qv5jnXXc6iasfe8X2vyp12YGMoi6xwwzqYp3vtx+raw1IW0gsNueyFmjN5u63aj1V+x4UndrJWNAGGYNOkYl6ndggpG8m3fxMxwNZo97LNmslJv86sc0iZBx6JHr0oPyiXNJpw6Df9vVahwGKbZSxR9pWXTNfsRUqy9wiWZ+e9TJ8+zbt7b0GSITeluO1e92gDkVBjuWp8egtSkhdVNt62fJ4hN6WaVqbJun0CLCfhTdfnGS4zgz9LjDbOubqBNg3Xc9Iu6zJHyv27IBMpB4VXvWwZ5KfZz0TbrpZ9ryA7WrUP+Pk3lXXUVgh6+Z3k/lScTBda1unLs45To7Hl1a1vn7nS7nKt2F4GV+95iBhZq85SnNdfU9+u/pBtWd+V05xrtUxljYb7hxLz2vtHFuv8vn9is/vyBHO31+2cf4eOsL7/1cov11zmLaZzmEyn6tkPDfIbK5S8HODgp3DFOwe68HO3TGeA2Q+d8p4Lo7ZnJuzP+fJeC6a2Vyo4Ocemc0J+51jztPlA74+vDn2mtt+uHLCO13S550wm7sW/LoeqMScDPn7Q/4umUIezeByxCLrkNeDj8KGcCOMhI/B7vBx2As+AfvCTTAVPgnT4FNwFnwazoHPwpvgc/AW+Dy8C1bAtXAz/AamWeTvDpgiejWAyaLXZNFriug1FZ4Hr4Jt4TSYAK+GI+A1Snx4leSrXT/FJz58huSbJflmu9dtl78LRIcpPuu23yHp7pR0q8VOa0SPu2F/eA+8DN4Lh8O17jlB8h4PS5EpPnOCCmWuzlwYB0vgUFgq+djhNbAMZsF5cDacD4vhAiknsZ68c8s7uFaOlX/3l78tmssewK1gW9gaDobRMBG2gZNgW3gNbAdzYSy8AXaCt0DXnsbdYTyMh31hDzgQ9oJJ8AJ4NbwQWmE/eB3sDx+Dl8Cn4QBYCQfCvXAQfBcOhofhZfAYHAarYSL8Dg6HP8Fk2LIudYa94FjYF46Dg2EqHAYnwAyYBq+GE6EVpsMCeCUshTnwdpgLn4JWuBXOhK/CWXAPzIe/hXPg57AQVsMiGI7Ni2EjaIMt4VzYFpbBrnAevADOhxfDRfAyWA7T4GI4FS6B0+F1cAZcCvPhMmiDN8ASeCNcBW+Cj8Ob4Sa4Aj4FV8It8Ba4Hd4GX4Nr4RF4H/wrXAePwQfgv+GDMIJx7CHYDD4KO8FNsDt8EvaGT8GB8BmYCJ+FY+A=
*/