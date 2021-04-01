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
m7Z1Wht8YjvFabVAkM1MsnnQChZiOqXhnOcfe1DmioRucxa7ccLTXB9IdeZs6XGbn22i/j1IGzd/LY9EShmMLCv7i//aGnZKlUS9V33U9h8a2Z6tKaX+oX641EkXRv7tbZNUyOVGRWdyKAwWOyTcBFZ00/WVp3rDwYf0Bd25CDTFjh0q+l8yleGIw0V+wOzgd5AngXWS/DWZPITzki1hug3BnsysKONfT7x8YxobqsHBqZue01M/bP4IkpHhWwr/cBomWwF0w1/aFEzxuHWSU2GezREjwaWS/2Nsb8UPODV5N+qJSvYsvGmYaM9K38hFWBYM5V7BTzIU39kkvZb4fxXs0E5DpUwhPZ5hnYPbLiao6U0EpTKWumv2G/1vSL55eRhW/LxzwZkewqVly3D2E83sL9aNQI9BDmp80Gz41kjgCdXplyaeB3a8pac1ZaE4MYinAAZIQWt6GfmM0oLg73Yz35SoUhX1g0g/l/EQdUDVKodfE5jiaIdCIglW0qoQnNM3nSkWCVB2DGFxLapHUGtCMRS1n2DeZhecCOyDQVgOsUQVRTeWnIwUaA==
*/