#ifndef BOOST_MP11_DETAIL_MP_IS_LIST_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_IS_LIST_HPP_INCLUDED

// Copyright 2015-2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>

namespace boost
{
namespace mp11
{

// mp_is_list<L>
namespace detail
{

template<class L> struct mp_is_list_impl
{
    using type = mp_false;
};

template<template<class...> class L, class... T> struct mp_is_list_impl<L<T...>>
{
    using type = mp_true;
};

} // namespace detail

template<class L> using mp_is_list = typename detail::mp_is_list_impl<L>::type;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_IS_LIST_HPP_INCLUDED

/* mp_is_list.hpp
o47Gl+RouMCgsFu9wzW+iMCSSo9/F9W4U39pOd5wIa91Vl4xQ0TVx6nq828/4nX2q76JqL4m/n3eNeA3yU83EpLWXZdB0r5sTFChJ1woYSoBaKY+8w7Qu8kSkMAWDFMHRj8ToUSWaFpJwHDyTmE1cLigZlm/hMbSJaAOzzemDVPwAWQ9KJbjeNSJXJGh8e9Pj1QAX+0pR+S8OUVyVWKcGT87fRxhCrgFeVa7uG4cefYOULaZ601jeG4pYqAtQInmuh9Bjyc/roL3xfRzlVW757fsESoSaHC4Wf72ardz8A9APFKgCllbgklVmx2WC74A+Kqr9SufipikuCptBXjQ3VBfwEBiPVbnSOq8sM7rgDdqc0VTXKYPdFNLYl5xtKkxjQRqoAtL93OGEJ6urqypLc9Jn7C9dMGTYXtJk1G0F1T7lckaXWKBRIv8hfo1XwsvKOQKmAUQw2+/bxKwza8xTEvyM9GaFnzOVH5zoO74PCLH48dTNTXC/NxwHPmZT935lUCN/pZfEqB+OWA4WCRWbxZOkH2MPSVq7wJ7e3lme0gM9nmwuaznPkMr2hSgx/a3kfwfPE3x9kNEYTav338h283kdGvasRtW6UugHxxH778WaEkizqtlN+1oDaFb8CGcaL0laLnAP6fu+JEwWJ/LgZXWhbDriweEx+lCyAGoda/Iqc+F/rMMh5/+7k8TEyB7Ye03wy3fTS1/8Yei5bYcdHgNORpeE/Yw3vcpo73Gl5PBeonwSOjrBkXfuHBV06s4uwxXxW+/ScU0eMdKoRQJrn/kN4ZHJb9a/9xew6odwOGkf0z8DFHNZvEzSMNxAb3yLpE5OT4LeoHlkGTehWgN18O4HXDUzzI8h99wGaj3HqF3Fi10OHZuz6lo6h9Z+V2c8CX9dCNNvzGQg6DasLuG/Hdb8XUl2LdaYh72N/UU0sdt+5EuPODvttS/1cULK0p5JuL85k4HtSHmcuimVa4PvEVkGMLi/s+ZPsPzTvJkQjHsmeHCr9MZMz38yk2y3riA3G+we9bnup+8wUMAO4yrpiPon1erXOMrsQZmZDGYCy1d7IUuuJj8d32u3SySQ2EgQeBwfyANuSbdr9MDux+qPNwnt9MLDMOwX7pf9bWSYtLG7sQSDJ/FK0tQ3wpoa1pDcJMRqGZZDbBd0EsAz0fDFI8raeW7gxiPhcFYnQADvtLjp1dGoHGAp0oDYaPf+VkTgV9lk08cJ8wdUmmFhPtDd0hQu0QegsoE/SQ2NMwNwVZhgBsaqNYvsjT00WxjrFcAsDV+ubVK79hjFO9YBLBXIxLIpVZItdbop0ZYtsijfY4swgP6QzqjJTYJhNd8o7TfMQoQkDdagvy+lRIhPRtLx7DU2B0aB01HBx6Rz3eErkwbAahhwbvJp8/3f5AUwRORHxkbof2abmO/Bpy8I7Rf06X5ust8xxok2NQ6D8/YASgvPa7J3Rh6BQp56dG5ctfcQc13rPT511bXVOkbyUs+Abtf87+OF011lRyhaNnOU3dN8K1k+PoJPHo4IHZnj57TGkZKz891zZv7lHHPlnKgTNn3XukeWJ33l8l734uGoW+C1mxo+wTFp56AdjA+NXv8otKjmrK/RIHInwOXHObvCo9/Al4A+gZqaFBAagCXyud+SLSmEJUBGGk4FA/RythKO7etJlfJFd1KbNLXkBnmASm3DFAjJWcCauLstlb7eLjaBUjCbBr4I2oW7CBT66PAYwBLdY+t4wOkNfo3f8KOPRSBN9AGi6T6DrL0CLE8LCXfj0QOvewHDXELhhUqawfJYzeEdgmus3dxayTnLqdBx4v8+DyScp49xor5X7NTnHni6+u8dbq7p/JyWC6HPik=
*/