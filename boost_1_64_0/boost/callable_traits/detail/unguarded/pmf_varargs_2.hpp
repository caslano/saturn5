/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY

*/

template<typename T, typename Return, typename... Args>
struct set_varargs_member_function_qualifiers_t <
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    false, // IsTransactionSafe
    false, // IsNoexcept
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type =
        Return(BOOST_CLBL_TRTS_VARARGS_CC T::*)(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS;
};

template<typename T, typename Return, typename... Args>
struct set_varargs_member_function_qualifiers_t <
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    false,
    true,
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type =
        Return(BOOST_CLBL_TRTS_VARARGS_CC T::*)(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;
};

template<typename T, typename Return, typename... Args>
struct set_varargs_member_function_qualifiers_t <
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    true,
    false,
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type =
        Return(BOOST_CLBL_TRTS_VARARGS_CC T::*)(Args..., ...)
            BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
            BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER;
};

template<typename T, typename Return, typename... Args>
struct set_varargs_member_function_qualifiers_t <
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    true,
    true,
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type =
        Return(BOOST_CLBL_TRTS_VARARGS_CC T::*)(Args..., ...)
            BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
            BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER
            BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;
};

#define BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE std::false_type
#include <boost/callable_traits/detail/unguarded/pmf_varargs_3.hpp>

#undef BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#undef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE

#ifdef BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE

#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE std::true_type
#define BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE transaction_safe
#include <boost/callable_traits/detail/unguarded/pmf_varargs_3.hpp>
#endif

#undef BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#undef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE

/* pmf_varargs_2.hpp
/KrMu4zyNpJ5u5vyUvkEl8JepF3+SOmCUSNXzUNvU1GJ6DSxYTFBUfI7YGcobY5NZ3tx+I/83l46leO81hN2VwvyHPFOCxz0Tou5kOfhmE8IGecWAP08bscmq9S/71n5vgtho9IGhY06nkuHDRjehxFqaaOe4hn1l+icoV3kOzGeJx3xTed85b5yR90H1G/9W7lwHbE3Vth9PTEXMA9HA4EfIs2JZ812Tw8R6ewd9RPtc57SjpT2j7yG54e6PAcZ/2sBzqtqxLPh+LXB7e1dFb5Y8Bll6L/bRD3cRAZXHKeRzvc5cz1ocsO+4T5aE372Y0P/FXlwJSfPZsn95B+L9tU/E/NTdbHvSMQ7XxHv/CqXJ0SEO73PF98lFemRuwtax+yzx0n9SOxrbm3ho8U3GSnNEK2D2FfvK/PV0zzxTFBxNfCH8gZ6gLd6eCaoZY2qVWvXby/2FqMPkG82+3O5//4gXauKfJ6tvxPOhpj89miTn/ZV+2n5HeEowWsojk/t9mrJqwinJm49iFuRB1doj7KPh9+s8M9RlGacTOOvtYJ2pLENKI2vTBMMe6mDZ0zqWj6DNkmmC0J8qQcv3sIyPtYH/kjpfFCq++SzJuBftgPD8Vglx9LvVPZL9P0/C85HCs7bir387XHUFfOFZ+22/HxlzqMX4CmvqKCwmAUxwYiTC5HUFCPFd4wpL7hy2DnJ7nI/exDqueh3PFcj6mLwbYdFuT2FrdQX5V5budzLwgOXWsVypDU+jxb8O8aMVmXyEw9EDMDFmgPbAk8h3cFKZaIn5XQ2OVSUyZG2vRwzvEdyHcQ8mTZEfv9apm8jn3U6RXIjW8VcLoKK7puzJ0h/h034CpHf2xyfZVt+RfqvNXf4kufA+ZHaeHoKPNWunrbXwRvak/yDiLvyOcObDYBAfxF7HYef+E7n0tuMu1tfMMbdIdLeh6JcevsnbnBOP35E/U023/AOjf68hc17irg45MVK7YSnkcxGb23zkylvHdGO4looSQVHzp8DsrAt6Rs/uKNyDDyPdBGWZZYx0MruRR43avPW8jm7aMezLdD/vhgpyiufucI1IdM1DXEzoq51n02rXIfYMOq1luVHemO/DfsX+62jXBtFLa+LZ4g+x3Ec6bZZlCtiIe4PFDbwMqV/VZRT5LeI3aLvCn0H2dePkvy6ZSxuAnyD9G/J+6rZdF+F47bvq6rUjz9i6kum9hutixX/qWeFrJ8J+v3fMP296zR/1LNCW+mZoDueiujq+1OnV1u/euRUl3bTD/75rNC/86wQTI7+AsWzP7iMFiL+jaxiLU3M8wBbWOyrXyHWglKBjYBp+H9TIX9Pspi/AB6z2B+fiSTNgLnAfsBVwJHANcCxwAeAE4EPAgOAG4GpwM3AbLHmtQm4FrgbuA5YCswDvgG8X5SjibxPpzkJKof3b/vo6e9TUY6zwDuB54BdgF8A+wPPA+8GXgQOB14GzgF+DYwBXgEmAr8DZgC/B64GXhXluw7cAfwJWAK8ASwH/gx8Avgr8ARQE2tgbsCbwCpA/Jv0DYG3gB7AqjjfF1gd2B9YDzgWWB+4ENgQuAjYCJgBbAbMAXoB1wCbA9cBW8nnPcR9JnCexfMek8XzE1OADYTsAZwu1j5nCN5mArsDZwEHAGcD7wPOAc6g68nnLcR9Iepq8bzF2+L3jgFdgcd1zzP5iXzTLJ5n2iqeP9sGHAgsAg4Wsq+QHe/wOiGuEyWuo3+H105h16VAd+BeUc9yYHvgk8DOwH3A3sD9wMnAA8CpQj9LpA8VsqM/0dgc2N6iPz0tfu8ZoBfwWWArITvyrxX5PS3y/0WU+xVgfeCrwEZC/h54FMdBkX+A6Ace9Lw=
*/