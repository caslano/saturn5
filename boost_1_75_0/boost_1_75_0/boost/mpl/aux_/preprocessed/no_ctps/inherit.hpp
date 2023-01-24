
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
r9ddGkaA9tQXhlLYlvLXqICIaKIzBQ617Zeh0+S16e2asKAu0OubXo4lPj+XSYabxLDueRjtqMjv6ZBuTDjz6MsVMKQbv17Gj2gr7AYsEnUD60I97HkU+v54kPFpK3Fb8hecf+zlTu/TViXg7WGPfy39Zb6DRHN3W8LDUkxcotcWJf0qry+6OAplJNMTklEkqSs+ZMfn45JuCghbHBmk3P3mahEQ+Ibc0Gir6sh9KSa8aJ8LKksrD2wxn0fxu5x6PIPqspqH32/5UlvJeQGFCBPUrghq2CUgdyaQKlI+WvHt5Wqb3j/IeC3K2J2ZePTxEi9fu2qpRN7HmkSfb1WIEaYRxVYB7y1H4hpIeCwK7kg1XY4fUUeTr7M9yldGfWLiA/9xdPrETCuL9T4fLvsswldzRj2fAlxZrODlfda9kY8KezQ+A25iVjnp+T48P0xxDMqCD3vZtpRMpe/0WZ3pVUTekiydns+T8VRIUQpcJJHMAp+FguAK2GiQ7jbyujIbGFuRtpj0TduKHkEqQerIr6KBokCJ1ZQ7DYpcz1Q4CfCOduS0M/s3dPfg4WCkwofPL5zuQEwS4cKWEd9a26mib/WtV9bAA+c3VzQOiyRRCJ1orPrsVAYsxidHvquTgDLoAxGlKb2ac/Pl9u+nOMPn45yJHzo7IhoBNNUyMHKGv8HSTIKpvRQqxr353fllWjJJRX7+Zzfa7kpdQ7Mi
*/