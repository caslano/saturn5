//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_5_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_5_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_5.hpp
OZqzebx8m1asOpazuB/vasUZP+NKz+s+g8/vGCtYWUbXfX6n+/2/7q3jgi2vwHn5cfkKojrbRveJ6NCgTXTsg2Nx+E3WzhaPBoKcNMRNLd3f/HbrZ2Yb4CC/BnTsjDJU1r+xDQM1aDE/uznCqFI1rcGeAW83GLvJ49ybu3A7xzfGfQ9grvt01byRfzgbGgi195I/7Y0rSZrmZXrd/ncmPqorb39ZlSKJRKBWxPYMpavxP0P4OM8SWpekt3Jio/MZXzE9Fl128RUJcyaCIGTmSAjmTYppUY91D3Db8GSSBzmLIQ5oKWb0oeW8xk642Ikkj1gVFoy4e17zes79cBcr81BmIa1ymX298Xl08eSKfDVjfqmneSd0OWbQnDEN8ooFsSAHRvQ6klV9cZEXEU+ZJQULar1roZKAfvb6Ebmv1fgt6fXaM+UGpYJ5/Yw7/m3N5qDa5XP7QDEEuLZNROfd9ptijB//6onDmK6SUSOMxT1rWzvO928tbg44eDmjrqLZxwTFo5v7YibPf+unK9tmZfxqO2AG3+N4xS0QHdnvO+p0MAZsspF/7paIZmyweQvpVhv0hVV522a9g86VI3T/AOKPyWm5U4eh3rv5JN4/rYWI6zzjpJZ9tgn6f3hscnJUBtQ1jVG1K3tv9jeNDPlY/ekGao+dZL+7nbI94vVbwfZsCOt0ZrVNeo37XR+MwJxYH7LIpbS5L/cp/FZTSrMyitNrv4tyXP4jjh/gp71zjzjJacji5g0a+S/vwYs9aSVrP2XybsDB9DHBjJxnN74KrDbv0ER67YrkpSQKo6BicWXlaV0KtR+3P5dL4XEtyMQyHXNtGmV1XImAWimgGcvVWTd34VH6GalCeDkpKgaV59FhkdK+4tjyPBfJS0jOkybSeEt5mnrzi2NirLrlmQ7LNOdVLqwUWeuGS8KPwz3l7m7drvqaleoDW3eOj8JvqulslKZzR/V9SH9Xteby3EjTZMljXjUxvB4uv3MKXzbm94+EvyHw8eyhNFb3JZ+5gRF1Ws101LcfN9/M04TNN7HxLT5YP1oADuTL7gmzlvGx2fVmfn/apGd4oV+bN3viIVluOYtfd+PiDanvcEdy1gQMlgjLu/tGBoPeebrPFv0drJS1P5fNdzjkW1l1bdP6VpfWXPuwc41tmgatUc7E5Fssrm1cvTmid5c9+sQtEL0R7qb9vlsa+qlj3p3QS7dyaCZpSx/Z6dBN0lb2s27t0E25zPxX0XpywrgmN5iaSjB6fMUuQ5ejopW597bwvTkpNco3b+bdDtHmurLEri7YbkNXypYPicAesL5P/JPhZt52fDaOpH9xs6cmB4qFZfUo+YkTG4PqyprcZDq6DvZ9SPNeGcx7chCv9qXu/KKfV7ltn9SYkd+0YOaOLbqYHb9vwciNZPA51OPAaiumN3t0XSJlHmVFGOxrBmBlxFBZZdgf/NyVfqxqTsdNjIg/tWCW5NGbUk/jX6b1+edB+uy5LOaey95/tODlHo0MB7p0arHT1TgxGNd72hrcdVDpv0DjTspXQQxSVl93TZmLE1rmpa7CQpPSSOhuYytwZ3nd5LENJyFjgJU4o6fjLbjmzRtzV/LEmM7n3FWw+N7kgs4HOdrPo7ZdAHnK5PcTCjc3r1GwJXxKCka457boVKmtmQ4anQ7Emenl8QfptP85ENsEXdYcpl4H4yHmomlXlwbioI+bdm3w5/49EH+yDf/t/1wVP9c9uTF5ndI6GYhXNTK3AGvvJWk0wHCbdnxkaNuA/oF1/u2BOKPzns5750aDsO06J4Pxjc51G70wGNdELFixpmf5kTrGYBsPoLPVtRV4hW3h6cicAgz84DT/6hbLb/W6OX8=
*/