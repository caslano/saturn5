/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_DETAIL_STD_SET_HPP_JOFA_101007
#define BOOST_ICL_DETAIL_STD_SET_HPP_JOFA_101007

#include <set>
#include <boost/config.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>
#include <boost/icl/type_traits/is_set.hpp>


namespace boost{namespace icl
{

template <class Type>
struct is_set<std::set<Type> >
{ 
    typedef is_set<std::set<Type> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};


template <class Type>
struct type_to_string<std::set<Type> >
{
    static std::string apply()
    { return "set<"+ type_to_string<Type>::apply() +">"; }
};

template <class Type>
struct type_to_string<std::set<Type, std::greater<Type> > >
{
    static std::string apply()
    { return "set<"+ type_to_string<Type>::apply() +" g>"; }
};

}} // namespace icl boost

#endif // BOOST_ICL_DETAIL_STD_SET_HPP_JOFA_101007


/* std_set.hpp
dCmrxHfFbh9kjMF0lw14SJ/neWVoJsNonWKyJ21X+iYPl8eaPQVhz1aHUtStMfoG6xXLmZ1W11fwJcjlL/VjFgBQw//Sj6mW3CH9DTRaZz0xsxlgF6a1kszaOHdARWZuXkC+zTYpC+K/fO6/0Hus+8Su4dGQhtYgI23eA+8PrW87EwKrjMrXUgwePnkzgdRyiu15KWNU3aWzNVTW4X0AGFY9a57KeTvUjf2FMBKyaI+rbfeOYBc5tdS/v+0zH2uc/BokmryvstWPlO75ub0XLxnFMSoTyjBDsdWy26uokh2Np5SV5BJ5Y/2DVpsEFQUEk1GNf3wxcbR09YeRMhkR0UnxsBX5Extu7r/FUXiIweSoV9rcMeEw6pTHX3Z7eUy/mbpu3OsaERZDGq0/xGr9/KNu4E354U9jua48if3ON+/6aZ8/722Xffe8tS35D3vPVVpKqFddQP3YWNNTh/4dS/WiAACBs2ki3V+vrvbwOPLyhv9tvZREsUCTAse5fs404ww/W+4nBnQllA48dsGVxoYDlrqb39krpjwYbdl3+fpOkQfC8jOB+tHlqj4ipO9aKjX4Zh9qJ4NzY+eOnGhJPODRVah8NiI25ZXNtkIzj9zYUUJTtWSiPGfLxVPPLAS9zx+zMQ43NJie8+CIaJRYY/QdtnryRXNnivXNd6/ZzqUvtFQvagDIovT8Ol+967NfBc6yKf5tvTDOWD8HF8cAd4eA6aCBgArndEYHh4FYB/dYhzsu2S7HmQOrs12U9dKL5vUoItpjp5hvD5crVvUr0naxKnh9GnqoxZepHX9ka5/B8i9DpKnhSpe2t8vUs3RpZx4VNqMp8bCgI78KWq3mNM/wXfnGVBPSmxsZni8PnrRe0fwditRXP+roTpabjTuYQKOJFr8fTgCgQH9jw/K1aDkcyTkyusWyeufl5slM7Vccq0r5vIWU6vw3Cios06puKY/5zAbejiP3Nl7uaw1LKESSvQKZRl6kz+7KepaAfPqn5gP73ihMgzVVdY3gx2vTseQJ5G51K3AboUDOvPieBMpiupGVhDbvV4lAuOtswhC9fsS14FOssLXS50eKVaLIYr5ouKnUggT2dJ3iBMBgborOsKcvS+1ot4dYpk8jAwPpnGphaHoCQ2jSepsT7N+vd7wAIIz/4saMihK+rHQWU89l+qQ30DkQyRa9OcIyTohFb7kKA/hd54sM2mRGmtI4EAW1L1PfGJ2hTj6sXLou+PCZF2eDktbnBWvPT3k7VF1XkLFab7TPV6EOmEMpD1hkvO5webnKcuteQVQbIldVgd803/t0L8+rT3xmdjp+1Dz00JtdV+mxMtdbL+KBAosuX8YoPUE8Tj8kQ9GFYBHJs9wwu5PlaMMWAAxrNzYRuFAU+S1DImR+5BWjfFK59QundAYVZXLW7+ONEABoAsBGKXW2ym/r0u5cCaE7kfD3QVhIMWNHRxd7DTZ/HSmP82yMHduNw7Y7GhmPnTDO2c5Q7viI80yPsfFnw2SG8w7GZ0y4fF4/ZA5T3yS/YXCq4iXlHv2K4+F0ew6dVo3cI3NN0piHKiXWb6Mt/yBFJCdz3FbuwxNkgY6DH3rGvhQGv/gorbjJhU6YQbb1yQcurDvTtbMr7e0gZUMIh8yl0lSDZz3R/IZeaqvXZ56YCGZ9TpYiozahUxw6qX2O074zyAk36S8Wek0raqbgTVaLlfC5Nq0dj7mWuzRz73OSa/Rt43hBtoL3KTqD3ll+k8n+iVu+9xsRAPBCv+Y3bEvWnJ5HH7mX6VNMvT49+4EjewO3R3DO6ytGqSsTV8bs7tgRdDvgqQh1pV5mi8DaZJe+lTC/mvGJOHWyqmAAtemHFtHGVxQ=
*/