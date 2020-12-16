
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/and.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct and_impl
    : false_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct and_impl< true,T1,T2,T3,T4 >
    : and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , true_
        >
{
};

template<>
struct and_impl<
          true
        , true_, true_, true_, true_
        >
    : true_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = true_, typename T4 = true_, typename T5 = true_
    >
struct and_

    : aux::and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , and_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , and_
    )

}}

/* and.hpp
sTaewq74EQ7Hj3E0nsEELMC78SwuxS/xEH6FZ/BrLMRvsIobfeNhC/wOW+MFnIw/4Cwswjl4ER/GS7gHL2MO/oQv4M94HIvxPP6CF/AaXsEbeBV/w2rMR4MH04OVsQm6YVusgkasiiF4Cw7Hajgeq2McumMq1sA7sSY+wviX+rmXe89/I3kOkc6RPFq5GwJIUaQs0jpSHqmQVL21u6ETKZJkIq0m7SMVkKq0cTf4kyJI6aSVpO2kQ6RzJI+2jJcURcoirSPlkQpJ1dsxXlIkyURaTdpHKiBV8We8pAhSOukRUi7pNMnQ3t3QmhROSiGtIu0lnSJdI/l2cDeEkZJIK0nbSUdI50geHYmHFEXKIq0j5ZEKSX2po+qdiIkUSTKRVpP2kQo6ubvaSPyftpG41sm9wu0kvDu7G0JJMaRs0ubOrjYTro/r4/q4Pq6P6/Nn3v9Xeq//Pe7/K9dhZ6jeAbhSngE4ibXwOF7oyjlusd11WEsABuf6zv/gFw/NtTPNeyzkup9O3/m2dvLXHPSdrwxjbscv19yKS/cxL9eUKn7tSP/azh9/Tek/7dqR/rUgx9eU9K/dOb52pH8NyvE1pehk5feOe75/5PKcWU80/jF7TeCtBRGOrjXd3DWl8EqyzMu6cISk7pOttrRvr4PeWBd90Av9sD52wQYYjI0wBBtjBDbBMeiD07EppmFLXIJ+uBZb4UZshzvQH/djezyMHfEsdsJfsDPewECsV0n6TMZu2A6DsDN2RyP2wIHYE2/HYIzGPng39sVF2A//hiH4FPbHp3EgvoCD8QAOwXdwKB7HcOSUrtzz9r69XO31/1/PRSt6Htq0i+u80/VxfVwf18f1cX1cn/+sz5/w/L/yQlHl9P9fOvdvS/usGg25r9lXaZ8l7dIHj4oaMGr0yGEDIniz4Z3RJpOl/V/dBpyj9FPyWV8fGJ2QOM38Z0MX/v4MJ0cB5r+XtC0cMChq8Bhaqg4bFB01YXR0bEKcKS5FyS/lPlJ2fim+pPzz5vzTkhNTEoaF2YqXNn+N+E9IyfiGDBscEUYuKdScpy/jiNDJYy3IT+JaFaKKa9yY8YMlh7Ws78lzzpxn8KBIwh45mLjH2jLZxrOgv+QZocoVn2QraykngUWSR2mpPn5A1GDejlhS7xJzaKglT9jYAdFjhw2Vv1va0JlU125OyX3zUOmDMYSUq7SZPiLXbmQE5tfcO/HeOmv7rGNdaTOUfIfde94S3KRNgJTVmvQyZQW8qSlLeaV6Bco6IWVZrwn1YsTpGdK3gvV7puW6jlHafZ2QWGpILNVJRbS7itHGkmwqN44G1Lkfdb7dvE6kpMXHpiiD2U17qDSuiyDVkrYdrwQSl7Y8Lkw50x7P2sZNr56PyYDhMm1DSP+grHxtWZkVq2cpy+7dohmofrdopkHqWfPe/t0y3dvlfe8Bb6liyUyeZ122fJ2I47muUq7mmp/mPZ+2NnINiCQus6QdoHtr83sIbdf+bNcVNe0oiyX2hlKP9ZVpVNrdH5XYVauosno48z5J6zSsZjyxaPce1Fv0l8n8I6XLS3bi3dXW5TKmv+Pl8oiUWU/KVH7MI7YAnWlk0Sy3THX9BVcrXX8HGHekbdwjNDVY/jRZ62+D1J+6vJxq+vWXd0SnPGrCmfllrcNcTR2qy/WsXroODyrrtt503sS7/FfL+OfJOjSb9B3rwKqjdtfXLS1qYzN5Xa9pbnpi+dsQ3evq6nVI827ZzXIJ5Xl5x8Az+LqyrBwrHUdivLm1aqIpMUPZJDj1PuO33ynrmr+09ZV1R9rH2uLlN9t1//Ml74qflphR8v7hR6gzeRW57V7Aq+r3FqvuBfCeYtm+qN4zr6o=
*/