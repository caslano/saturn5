
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/inherit.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct inherit2
    : T1, T2
{
    typedef inherit2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1, T2))
};

template< typename T1 >
struct inherit2< T1,empty_base >
{
    typedef T1 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (T1, empty_base))
};

template< typename T2 >
struct inherit2< empty_base,T2 >
{
    typedef T2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, T2))
};

template<>
struct inherit2< empty_base,empty_base >
{
    typedef empty_base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, empty_base))
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
bAN/rwQeOEm8Ky7A5W0i22HFs6HrSpqDwYEPwCGNtcTf7lRJCPNxZaIzwzkPZ9SDj5+Jk1rAKw5el+TtQe+skoi58M8EwVmd6/eQdFR7A42/UlfDPdkH9+2q+E0URs9ITTxbnGwt+8kh8Gany2Vypdwot8nzgbMwCtfC0Bs99rdouPgDnLufRCmwhMlQoDdkFesuzl+Yfz5WkgKqDsZ4Xl1Ma8M7uwefcYdelc8E22gnMtF1HzhbYUoUhlHqQbbJOMKLBCYgG/OGIYq345NErPynpBzPbVuNsRu72jfsveAUP6Pm5s9bRbKTVISj1xOVdx20agnjMzDsvehFCWQt/fhwVPYbQIx4PNXHZivU2jAfa2ux77VP9QSjFh/Cf4RiTRap8Oiy0EuQI46LcPQwvI0z97q9HYldbbC6rfC3Krq93M/d46hzYT7WbFGP0yXIROPA+2/BGxwED1QAnS3eC27bHa6KIXB4D4NHlIE63SmbgbV+bT4yO1jvWl3dVeBC3MvxNWSY0hlDFN56KYE+oXm0P/vYR46dWowu+AfYNy66uOfD/88TddFP8T1w7030zXSx52K3hiK1XeScQj/sEHjF1dHDoOCnuO9j3CF10R3dgr4BX7MeWON6RrTO0NCb9YrwU9LBE97GznsDjv8h8O0BwNTPzW/MIOtDMJMX6G38BL0Tbzv1wZYvuTXB2rZ5v6NuFvfXOgFa/Y8k3x15DafY1ruBK9X1/bgvnFHoM6DQk8V9LDxA39J+QgV7B92/Kh8Bj/QmOvQn4DR/izdt9tgOetC/dC47I9xcVyHF/bUdQDaqOWDBRWkL2gdodoe+Ar4boZWHh7ZBP6rfkuWR+9+zOtoD4PpmoV+heP48QoUXpvXxW33xfsMCZC6p6FMcqQfxplzDSlfE6i6UwejTy4JW/Akpk21vRD3q7ExAKlbVTcU5ikKmloVuMyWhuL/Wp+EHVlVt9OPlgoemwicuyVIxm2FaMvA9HO5oHdEA6LQC3mpD6Pcl8rTZEnM4Aj1M+9F9UgiOQnWvB85kcd/ba0BawiH4AR3sTXEit6sngNcNaCd8a4YRyE3/BITuxhmyi0JgXgudX5w85Lb5a9qCFMcbCiabBmevplYZ7zw5xgDjIHqqH6GnujJ6cmbIFdaYv73Jcs2+ic6v++i1f4bMNNgJdVyg92X3MdTPQO8DOAVIvFPy7+sS5jwNvR4TtPfh1n5g3Oa1gH7rkHWGwF1aYxaAErLQgz3VfeKqqHf572Zg3jGEgxPMAOreJp3x7k4Z1oy9ib6x59hxKeAxr+pbwV90Y47xnVEP+iMN++yB6VhpQM+69mj7W7xdFA/mtA8qLYAR+E4M7UiIaqKS/Iz+zk/h3nZD9vALq631hIPxu2ZCWabzBKRV0cCsTHObWcw6DO84EanhJrxlVALK4w/uIvCX64Eu8ezi/tkPUVfiRByhTVgBrbhWS2uOnVkd+HAJmfvH6ERLB6Kfh7KpbtdH3SuFHVkWiPrRX3qCsfcxNMP7QOPgigaxxuDkZ7Q4fSGY5j70ZHW0RgLlpjpdgBPFfQ6RYW60FvheNv4dQy65pGlSCcyYv54D4Cm8qm1EIlkeb3rd0G8by4EeZcRt4FAsku+30ZOzzNyNzthyQMIEawY6fIgj0X85GGn1LJz8i5izom4NKK1grwj6qt7DGQ2HL4UfODcvkS5kDHhRBtlEItVYtRl6WZer9ZDgdYerMQ77aCZbyG6hF7oGvLVCxltAzzI4K2/yR7wyckALXbou9N92OJ1NUX8OwOfuD/+uGDyEnYE5iQ5XMjBUR+V/l6Sh8h76h4z6GVHARly4J1lw8johUfkjiwbbT9c2aL/imWs=
*/