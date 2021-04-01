
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
D59ZeGmKlY9wYB9oAKYe/Jjkxokf5+O0pHdnVC3Hqw7vrJtCmgRfUZACzXRc+qio+J5XC2Yu5RwOArFuzRBPHjReuE4XDU4bqf11AqmODTZY6JLvQv9mLQBnMRD/L4d6TnxLucuLHZMIYB+0R1jRFhOqpW/EW1R7I0Zyc1Jo+TfYX7nIPaRX7gruO79IzKKNluCj9RDgWz+NMynqNmJBj0r9TFYo0tIt+A5h+Uj4OQ/2ovDqvgdWvyij/CLMOrk1gHJiwOGV7G1JRa2ZHVDqCh/6OU7TdieHAFxLawLRz1QZEtPnCd4BV+PQyHXeU7J11IIeQYrIoiYpdQ1XfAy0GQcVrz8Z2I6Cpw6giHQU6zxltdaq24ZtgMOtBOpZUARwK4AFQLW+c3uFOP7/wR5bYbmQ4wYYl3RwGm6W1Qt7vyXnngznWWWwFjZWRUf/vXlmDq4EGH56aKu/mw5pZ9daKTaocr1FtTPoaOQAGaCs01q2ERO3bVaCXqCApoLnXv1fMb8iKn5HQ5fMKLiu5cc08bQp/DOQfdBNDol2R5qPTUN8nOKj6MEaAidfng==
*/