/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_IS_ACTOR_HPP
#define BOOST_PHOENIX_CORE_IS_ACTOR_HPP

#include <boost/mpl/bool.hpp>

// Note to Thomas and any future maintainer: please make this as
// lightweight as possible (as it is right now).

namespace boost { namespace phoenix
{
///////////////////////////////////////////////////////////////////////////////
//
//  is_actor<T>
//
//      Tests if T is an actor. Evaluates to mpl::true_ or mpl::false_
//
///////////////////////////////////////////////////////////////////////////////

    template <typename Expr>
    struct actor;

    template <typename T, typename Enable = void>
    struct is_actor
        : mpl::false_
    {};

    template <typename T>
    struct is_actor<T const>
        : is_actor<T>
    {};

    template <typename T>
    struct is_actor<T &>
        : is_actor<T>
    {};

    template <typename Expr>
    struct is_actor<actor<Expr> >
        : mpl::true_
    {};
}}

#endif

/* is_actor.hpp
rqEv+nqmtZS6084Ra7liO595fqaZD5meWc0Zp2ZoFqDYunaHa2PfJHNg9mfdW/kYM8WGDVh1BHOTjNf162d3sU4kKnZ1Z1YPjKcSQ6WZZ5ZhbipWu+GdVzjbkBmY/Ttvey72B8VarMv5CeNZ3zSGhtcnLcV4KvavlIp3MZ5kNZnlDJ4cp1mwYmerBl7DmJE5Mot0yl+F84RiL/r/8ATnArLqzPw3VVqEM59yv28Tl4diXBQ7UvJ9Nc10zqbjaTP94F84e5Px+52eE1kZc0yxi25Dsf8FkvHcHm2wH3kYTVaNWVTM3K2aRSq2OSckB7VExudf5TtV32JcFBv4x9ZzqBcyPp76L+58j7OGYv2H9YrH2tNAp6vH7Mm15W00c1fs44NfdcE8InNiZvvj0ZM4Tyi29/6J01hfyKow25WqQ80nkVXj8Q06irFOUyzUyrUUsZPx3K6xH4LYCxQbUND2DtYeMl4vi1rvtEFNNDS1HieO9kZNKGZt7nwJNaHYqeKAzZqNJ6vBLOteb8yxGMWm7v7oFsaFrDbPQ81dmZplKvak744sxK7YgCq/z0DeXUzt4eD/TMVaQMb7cst9zRzNfBUbNnn9JKyfZAZms4MPGWtCsaxzj/zw3KH0ZWTu9AGIXbH8lVNGIHYyB2aPP/1iE851ivUobl9Ls2LlmnPO6R/iGd3V1DLWWl1H3sn4NRu4rOmL+aDY1/uP/oq1gKwWMwfniFWIXbHci47/QexkfB5tcfrEHeugYi49h7hiv3U1rfkTG/2HIO9upvkrmDHga5zPFAt8VKEm9gAyHl+n/oHIURCZI7PrW83XIu+KLU1c9RfWOuWar7f52CN2pV3DQV9ibc1Q7MPBr415J+P5G/x4eSnmOxkfs+T2W5cg9kama13QxHuTcf4k4+MycXTTHzQLJePXrBFY8Aa5JeN9uRN/bhHiKzPjmW+/N+qazJ7X9en5xxAfWR2+tv66ejHiU8zB3eYEzpGNTdelp5s+w7nAm4zfr874OZjTgWT8mkM+m9gWuVXszcrn07C/K/er1elrC+xjZAZmkZfTSpBbMp7bzjenZCF2xQYWXEP+Ssh4LY29txjrrsHd9H5jFm80nnvI+DVdDvU7gLVOMf/048+x1pHx+83am3Qf5x6y+sxa1VoRgmcLxb5s4jIBeSery6zfgymF2MMVq3rpEs7e+iamY720QvBG7OGKXWz1HLXrR8bz9/zpjjtYsxRLPm6Rh7pW7F+5NV6jrhV7XZCWjfjIeAx7PzififgUe1BxzjPE19Q0Bnfd63zER1adWdOxleYiPrI63MbNrIb4lHaNJ+bewLMhWRVm/Tfdb4S6JrNmNqz30CvILVk1Zq7393fD+yzFmhSeTcS4KPfzfKMfimdKMktmi193+xzzQbFb9Stj7Skga8is3tM/a2E8mxmtNtmOEVa/Yi0gi6/wz7uLWmSbK9v9ibnSHO/53lunI0/2a+ZJpme2es+F25hHZJWYTXMrwrOvP1llZlm7Yv6NZwvFHpWk4rkxTOlLtE1rH8w/MktmNdu/sNNsttLuxcLE73EGU9p1fdblO+SdzJ7Z4d8v2uMdJ5kts8GXtrnh3EpmYHZzwp6nOLeS2TG7tHFGCPJHVoXZ0OXfzsT5haw2b9di3AOcX1qY5iH5wHefI39kPPbbjf46iPyR8fvtPHp1IfJHVpHZ62rz/JE/smrMVmaHHsMaSebK62WGczbGmsyh7F2sI9npl68wNxNbYN19b3+2Tu2sWTqZK7N6w+4uwRpCVplZF/9ejtgfFEtfY4n3KFYtKT5m2fUvNMPeQWbObOWvfjMw1mS1mPk0sN+BsyKZLbPPMzcPw7pE5lFmNd8=
*/