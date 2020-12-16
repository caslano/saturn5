#ifndef BOOST_PP_IS_ITERATING
/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VECTOR50_FWD_HPP_INCLUDED)
#define BOOST_FUSION_VECTOR50_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector50_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector50_fwd.hpp")
#endif

/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    // expand vector41 to vector50
    #define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector50_fwd.hpp>
    #define BOOST_PP_ITERATION_LIMITS (41, 50)
    #include BOOST_PP_ITERATE()
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

#else

    template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename T)>
    struct BOOST_PP_CAT(vector, BOOST_PP_ITERATION());

#endif

/* vector50_fwd.hpp
Xo3TsPJ7ZRf53gT53kT53iR9rGqUNhZB/VqXNhbBSYvcj8t9eqjLGA65Egu2GCNwCY7CpTgOl2EGLscsXIkrcBWuwgJ8EG/Gx3ANPolr8Riuw9O4Hs/gBgygHLdhCG7EzrgZx+HteB/egQ9iIb6KW/ANvBvfx634IW5TY2jlvh8WkUJdYglnSL3FSn3diANxNo7FOTgP43ABzsMMjFe3i9zH42hZvn67LJflr0ArrsRBuAqH4k0YiQXq8uReHfuaLO8WWd5abIPrsC2ux1C8FXviBlTbFMj+NkSWp49BVEIeWuMS7INLcSDmoxqDLPU30qT+siTGOhsD0I5NMQetmIthmIc3oDrGir7NwkWWP1+WnyTLT5blp8jyF8jyU2X5C2X56aiOVSTr39nkeFvBejbAldgJV6GMTSH3uc7zZKjL2BSbJAb1duyEd+EQ3IojcRvG4D24HLfj/fgbfBB34AG8Dw/iA3gIi6Tc++vK/arcx5I/y+Z3nDxveUj210dwIO7CYfgYjsU9GI2/xzh8Am1YjMtwL27Cp/FJ3If78Fl8F/fjX/E5/DcewDoU5gVsgS9iOL6EN+DLOAtfwfl4ENfjq7gJD+Hd+Ab+Fg/jfjyCJ/BN/Bjfxh+wFGuzzu9gG3wXe+NRjMJjOBPfwzn4PibhX3AhHsd78AO8Fz/EnXgCH8GT+AJ+jK/jp/gensK/4xn8Gs9hBZ7HOnW4dmE7LMf1+A8sxAu4Hb/HB/AH3In/wj34I76A/8Z38Wc8hxYlBrguYGusjaHoiPnGejgFr8Z4bIDLsCEWYiO8DxvjfgzAV7EJvo6BeBabYRm2wApsiUEcWK3wOmyNIzAI4/BXuADb4CYMxkJsi9uwHd6LVtyFIViM7fF17ID/wI74E3bCRvU4BjEIu2AnDMUI7IbTsTsmYA9ciz3xNuyNWzAM78c+uB/74kfYD7/C/vgDDsDeXEAH4lAchBMwHKfjYFyKQ/C3GIFFOBR34zDci5F4EofjVzgCv8eReB0nqlHYHsfgRByLSzAKV+B4vAMn4tM4Cd/EyXgcp+CPOBVrNSBWG+tgDDbHGdgHZ+IMnIWz8EZMwDlowzjMxrm4HudhISbgvZiIT+F8fB6T8M+YjKfRhrU4z6Rga1yAoZiK4bgQIzEd52AGLsFMvB2z8U60q2OfyXMQbGZy3i2Q8+7N2BTXoLMtiTzDwFz5nr4tSbpcrzKwA2biDMzGLLSjxPjLcwiWJ8vRx/iHy3IG42AcgpswAm/HobgXh+FzGImv4XA8jCPU8sqzBrSZlLcP8zXEvhiN/TAe+2MyDkAZG0OeHfCZLEc/NkaOzFdokXt4fErm0495OEvWKxbb42zsjXNwGsZJ/nMxE+fhcozHlZiAqzFJ6iNZ6sOG92IK7sIFuAdTpVwbLHI/j19LuZrgSinXaCnXGClXlJRrnJRnPK7BCXgnTpT6nyT1P0XqP1rqfyoex2n4GU7HMxgj5Smoo97Tc6/vLI+yvnnyLma7tCX6DV6P9+EEvB+nYRHa8He4Eh/Em/FhfAIfwRdwF5bibmxGZo/iEHwMJ+PjuBT34DJ8Avfik/gsFuMhfAo/xL14DWV9GtviPuyDz+Bs/AOm47O4CvdjIT6Hd+EB3Iov4Jv4Ir6LL+GnWIIX8E8YSl28jEPwFZyLB7EAX8Vb8TXcgq/jdjyED+Ib+Cj+GZ/Gw3gAj+BBfBPfwLfwPL4t17dSDMF3cAC+h0PxfZyNf8EFeBwX4Qe4Gv+KG/AEFuJH+Gv8O+7Ek7gPP8ZD+AmW4af4M57CPhyYn+FQ/Byj8AuMwdMYh1/iQjyDeXgWd+A5fBzP47P4Nb6EZXgEv8Gj+C3+Db/DWlw=
*/