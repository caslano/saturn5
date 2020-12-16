// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/detail/non_unique_container_helper.hpp
/// \brief Details for non unique containers

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_NON_UNIQUE_CONTAINER_HELPER_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_NON_UNIQUE_CONTAINER_HELPER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

/*****************************************************************************/
#define BOOST_BIMAP_NON_UNIQUE_CONTAINER_ADAPTOR_INSERT_FUNCTIONS             \
                                                                              \
template <class InputIterator>                                                \
void insert(InputIterator iterBegin, InputIterator iterEnd)                   \
{                                                                             \
    for( ; iterBegin != iterEnd ; ++iterBegin )                               \
    {                                                                         \
        this->base().insert(                                                  \
            this->template functor<                                           \
                BOOST_DEDUCED_TYPENAME base_::value_to_base>()(               \
                    BOOST_DEDUCED_TYPENAME base_::value_type(*iterBegin)) );  \
    }                                                                         \
}                                                                             \
                                                                              \
BOOST_DEDUCED_TYPENAME base_::iterator insert(                                \
    BOOST_DEDUCED_TYPENAME ::boost::call_traits<                              \
        BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x)             \
{                                                                             \
    return this->base().insert( this->template functor<                       \
                                   BOOST_DEDUCED_TYPENAME base_::             \
                                        value_to_base>()(x) );                \
}                                                                             \
                                                                              \
BOOST_DEDUCED_TYPENAME base_::iterator                                        \
    insert(BOOST_DEDUCED_TYPENAME base_::iterator pos,                        \
               BOOST_DEDUCED_TYPENAME ::boost::call_traits<                   \
                    BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x) \
{                                                                             \
    return this->template functor<                                            \
        BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(                  \
            this->base().insert(this->template functor<                       \
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(pos),       \
            this->template functor<                                           \
                BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x))            \
    );                                                                        \
}
/*****************************************************************************/

#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_NON_UNIQUE_CONTAINER_HELPER_HPP



/* non_unique_container_helper.hpp
vzD+vfELtKlLTXznOupkQRllZF/XR5vwkXLbx8cdqItkIvA+Y8KL7HeX64w7W3NdffE718xfb9J0ssd/Lf9XjO/57inO4aEOpk6a6/aADoF1h/dFe/3rv5Z7+wNIb63+gCUhdS039DlRfpoDVhb63NvGtG+Or+fEOD0nrn00qH7oMTHsc6L0k8I+J65twHOi4gj3nKjwuP+q50R/v9orKsdBKscB6rNY+1ygHOlgot/Cta9CegnOfgl7DfoaExYXKEvjjg68Q8TXn/+G9EX468SGTr4dy4k8Af4QFqG37UlnXnSLDf/MK/1Eew7+n4x7kifZ09zUgwKTT6Iye6mu2Pv1qXXPi9Xc1q7bCGd99Q7mXjzKXIf/YfbJCHsf7L0tcB/McLkPZoW5D2bWcR/8xBzzB55mLDIaH7iGmbkc6kq0r2O3muOvts7jv/M69paJozzo2WCq0a2xxltprvfXqpD8nuFyf/VfgzJ17+S+Sd+K7x76hObFPqf7JeT+Wf/90nsNentb6BxX5z0wYCeUc4uf/9zqfulyH8xwuQ9mhdwHM13ug1Wu90HcYe6DqV0ss00n8YniHNK48ilnndZtUOe8QNcxx3VO+sn2c+MW4x7iMfOqXe6F2fY+f2A95h+rjtML+Wv8SJ9jDX+OHbiXPGz2GeghXPWKFXUcfXwHTXiUJ5s9llpNTJ3SJcjabMJORBc/1alPjN8n9HsNdG1XnXDNMmlaRrmRF+Pn0X72/HmlkxJ39NnfaPabJLd/n9G1243awiYT/izjeieoH9C/z2mO50JOR4nuD9qv0hynstY+A6jrrXS/dd5Xnffe5+DnyKmJ9fcreet521/XvteqTs9p2L3WnM+gOliV6H6vLXvUWQd1q63jXltWz722rAH32rJ67rVl/4X3Wn9feUJXt28WSKDPdmHh7MrykorFvo8XdfTXVod8v3i1EfkL1y+7P8no0pPiS1sLuNx7nh8LpK/kvAacZ6PfxYpX/b/KuD+yutE+X0FizbuVbDCYK56uOfa+o63e6lcr1nFG+vUd15IrjO4RqzOlkM8q7LJ/ozg6udajeLX9S43OP6xkSuANRN/ltG9HR/0q40QG23pBJ9TWtuw0qIgsy352+I3R3cjcjBZB9+5Y3f9vNuHv0EfDt1H7m165fT8M+C0Meu/VezefmAL9P++ZuC6yv+UlxvrmPb2G3Or4nvc67jcaaF97/OMh982Q9qH7pt7jdD4d982Rfn/pVoVpN9V2u/GVdzvtr/un/RyY4rBDlCE38Qc901YdW7udrUBvv++ZltprPhbLxpjrMyC6we1rQyPal/O5wpmu6O7u7T9zhzNdVKALw/fTZ4a0+7caka5w3y3ze7h/j9ntu77PLy3Iq7d/yv9s+dajod9kFE/4bzKE1/9NBp06v8n8mfDQbzIHjvI3GX95pvd0/yaT81jt8tSDW9jzzT7hv8so3Pld5t2vWB9cv8to7m5Ck29/7m50MzOHM+fWsQfvKU1fmbL7hb99eU2f7++c3sbO3X3JzNG9eMz8zz+buPf2+7q9uev6vT85lb4hE/+wz/r2mfrp0is2jJuecOiYq3/MO5OZM1zR5cpPLp500/TL+p11W3R6ywPh5hJ/+3N9s0/z+o8f89DYvBP/tSzujpQL36k4udKMH8D/6T25f/1laeLBf1+3dsyrvR74kPdE41/z9tk9bsy/p9VlrXd54j+9++Hwc4ZzjP6+nxRcu67TRw8ejJv15s5Ln+xHOzX5vfTum19+Z0dq6sU7plSVXLPu0Dc3x5ikWjstjefRuKRq9fE/pkY3lkbfA54KU+BpMA1mwyEwBw6Dp8MR8Aw4Rv6nwclwMpwKc+E=
*/