/*=============================================================================
    Copyright (c) 2016 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef PHOENIX_BIND_BIND_FUNCTION_OBJECT_HPP
#define PHOENIX_BIND_BIND_FUNCTION_OBJECT_HPP

#include <boost/phoenix/core/limits.hpp>

#if defined(BOOST_PHOENIX_NO_VARIADIC_BIND)
# include <boost/phoenix/bind/detail/cpp03/bind_function_object.hpp>
#else

#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>

namespace boost { namespace phoenix
{
    template <typename F>
    inline typename detail::expression::function_eval<F>::type const
    bind(F f)
    {
        return detail::expression::function_eval<F>::make(f);
    }

    template <typename F, typename... A>
    inline typename detail::expression::function_eval<F, A...>::type const
    bind(F f, A const&... a)
    {
        return detail::expression::function_eval<F, A...>::make(f, a...);
    }
}} // namespace boost::phoenix

#endif
#endif

/* bind_function_object.hpp
UyaARuuMuTX9tOJuh0pNi1BLYzsxaMCbtPjsn5NuJaQ2UD+Sx0z+U+zqtdHHrl36nW3Pr+57G88gXSCLFaMB5ArN8XyNzJv3WtLZylhxZFmAZ0o++uBvE2QeXzNvnb4w5FSxQBdzy0K0xK3Em/YA6iLI4PXo57uXqdo+Kz6lsW+PwEePR59QmGaCUQWfitQwa8IKjj++G1owWnBasE4UB3d2QXbBZ0E0zkL1sL9gvamuaYypnKlu1mjWqkfWv79pGuM4EzsLzKDZI71yKrKFjzezXX6Jd4h8hF0PJu2DqcchWAjwnu+oKYZCl11HiRr9qlNU3oy7REhbQrAYiciPCUlbBfZm75WZrGnfsJN21KnJzo737KwEl8h3xnck/VcAxdJX/mekSZAF45V4dPRSftUKyX1zfgtav3OOCpZ1+RIcz6uLqEABrCgMBEo2RjbfhehSttcZZ0HLEdVu0qjg+08MyeUzXb29yhjS2J5GDHkEFwEpQr4r8hjioeqUZBqFj6dlWxLGBK1FA6/tFGVvhtsSXmayPirggdxy+ZN4fFuhJPUFzzcPKeyx1LdPzUo6J9Y7DfPRD6sqNZZif/ZVBJIQjuA17SkcMFaQKcfUKQKlCb2T5YWuME/fRJny6PKiLkdFv8UTx1JHFC2V59Adr+QSxa0ZaOZPYWwm+XkX7qKsEkUWJ8vYVwFHPX2GAFJIcygxFz9lFPO/lVJW
*/