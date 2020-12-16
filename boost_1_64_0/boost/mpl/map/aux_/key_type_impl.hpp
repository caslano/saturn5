
#ifndef BOOST_MPL_MAP_AUX_KEY_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/key_type_fwd.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost {
namespace mpl {

template<>
struct key_type_impl< aux::map_tag >
{
    template< typename Map, typename T > struct apply
        : first<T>
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

/* key_type_impl.hpp
2kSS/pUe732aSCtIq0lynyP3N/Z7m6hRnu9n5F5G7mPU9y7+3bdo3KfIPQqfO92XyD2Jy33INtIcuff4mbRMv5/QF33RF33RF33RF335Ty97qP5f11n1/7tV9f/ZUv+/R+r/d0r9vznGXv+vq5pVYq6wBAB8mDfbc/1f6QO9lvfl5JuB3yj5yHo/W+djrzDbntmOD+fv0ixxAz47KuQVWb8u3R5LaOnEWIJG25pmjOGaEEtdP//arM9ur05dnLT1ha9/X5SgVcft+piE+zaxf3+sYl6E8vk755dfckv49/d/1qP0g82Njw3wP4Yx1xLDuLb2tSVn3/zC1WtXLC0ztTZHasUwtNpIO6+NjhgGA+LK7w3vkTaiA9Hspp92LIbhcOyJx2M4TsEIrMBDcQb2wnMxEi/G3ngpRuPtGIN3Yh8sD/At1uG5zcke+zC3/X3Psq69NMCwmaTV7tTc1jltT1vaHNufdpCnc0zFsDjAQzuU9zYo53jLz23tMZc4tqvVDpW+uOPtUN7aoBK/dWyHMiv7N6pz2qByvvWtHWr1us5ri2paHOB3e1RH26IMl+hxIX3RF33RF33Rl//K0vX1/0pljDLq8bs//59S/79HVf+fLP3Q1wVQ58D70aw8s93LUv8voQ/xqIK8wcaCwonj8sa21/8zWM/TeG/f9baO92aPB8wMpk5msscDkkN4X2/vT2wK5P3plY5j1lWdVQGWzzZb5wqbWlJVI59tl8/4O2VVy7ba5LOa02fK3GHyXp7n3iTv600VZcYyDrvEHl61jhknZdwl61U5xSamy/ud1vWlLBvkPWVhC47zlNXTUdr6Wat8VllVV4+WbX0mn82Q91vk/UyncQXTpZ/7QBmfrz9mUpmLiZZYTYnDufJpbL7sGO/n6huJ5djH5SOdaaoAORb2Y3wQ/fWVlUxsKMAwTY6d6ljKsf0m2nKsfOoPohGr0YiNaMVqOi8m428sxd8Yhb+xF/exC/9jMu5jZf7Hau6zxFhqVq2eMnHl93ltz9/w29Ff9j1PK2bVubGUlL3k2iXXtM28GMPrOLnODZZYylAMwyOwPx6JGXgUZuNwzMURWIAjsQiPQSOOwgocjWYcgxdiJjZhFl6G2diMY/FezMEWHIeP4Hj8EHNxF+ZhpcxrVI0nYx2egmY8Fc/EKTgPS3EBluEirMClOBWvxml4E1bhgzgdX8QZ+CFW4+dYgzuxFv9EE0ZzzE7DfliHw7Eej0MzFuIsPBnPwEo8ExfhWXgbno1P4BzcjOdgK56H32MD//yK87AH5+t8HIyNOAwvwBF4IWbifByPC7AML8YKXIjTsQnrcBGejZfgPLwMr8UleB8uxftxmfTT3mqQ66hcXzeTwnm9SS6YIfK9OQTDsCf2wnDsg4fK96gXjsJI+R5F4XHYGyfiYViH0TgfY/B67IMrMRbvxDh8DfvhrxiPIZQpAUMxEaOwP/bBwzEeB2J/HITpev8lvf9SB/ovrSBOtV6PVemLvuiLvnhdun78v0pjVY15t8f/U+r+9/Xk3tZp3v7x0vafbZC6f6hj3T8rb9JxWRNH8bCu7/3/d6e+r65/181yrAPvlPv4JyVe8bjEK7Y6lXlcXmHW2KyJlvKmSQG16sBTwr3Xgf0pv1a84h038YqdTvGKz6zv5Ths9TMu0eYUl9jhJi6x3U1c4lU3cYlWL3EJvkcOz/z3IAXIc5gPcEO7OMIal3D+Hvn+vLVWLEL9nciQL2SJxEVORSX/NU75y3fCp7jIAb28fyekLHIeXGMg1aoYyE49BvK/ioF8aomBDIiZ/VLSUeOrBuYm9Uoa2mjaMzGQHINcw+Xavtlp3L8bpS57EybiShyEN+M=
*/