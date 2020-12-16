// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CENTROID_HPP
#define BOOST_GEOMETRY_STRATEGIES_CENTROID_HPP


#include <cstddef>

#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/strategies/tags.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace centroid
{

struct not_applicable_strategy
{
};


namespace services
{

/*!
    \brief Traits class binding a centroid calculation strategy to a coordinate system
    \ingroup centroid
    \tparam CsTag tag of coordinate system, for specialization
    \tparam GeometryTag tag of geometry, for specialization
    \tparam Dimension dimension of geometry, for specialization
    \tparam Point point-type
    \tparam Geometry
*/
template
<
    typename CsTag,
    typename GeometryTag,
    std::size_t Dimension,
    typename Point,
    typename Geometry
>
struct default_strategy
{
    typedef not_applicable_strategy type;
};


} // namespace services


}} // namespace strategy::centroid


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CENTROID_HPP

/* centroid.hpp
X5BIdth0xf+jFf/nip1lia7+GrQF6J9qituUKJofoi6SxYdON9Bk0WT2Ek64OyR7iVkCzbvUC0g5W2hUhiBcypyCFoWnSvy+eoKaqSLT3TZ6k/8Qjzuxf0c+bPwizkhTZuPW11LuyBRqMt2eV5CZCSREjpMWq9RvVdzl0St1znZQZywRrZAr/X9Np75b/B+5JWMGbUPKNx5NDKqRojLRs+hye7kHTnHJLbK4qXWrW6ZADkZBPMq+yBYXnVjjW2VImsIM4aF0LduZUGDbsJmj7ccSf48l5QzeQoeOId/X2BVeVVvojEGkkjBGlZukcFvjHFULUbXJURADEXWOEZXtbWG31Jxyg7FND5v1rOaQEkBFSgillddXtuObWj9cibQ9D0LA7hffr68/mu153ZZrCWmv5g36Cq74CUfTusWs+EDI0DXWcsIz2N5W7VzpGjQk4ybxENtFqlGoZe0SqlBvyEbWDEX52P3tYyqKJeXiTsi1tyTzxeYmvIlp6RHKhEsnragvkhHm/aGWxsJAwzAHaPzrMZO3x0zMuxbLZKugC7btvXH+3/Wz968JioPrvka9F49Y8hryhKL0NOxLYVxqTJfKYAV0nrHCsiWyCISN5eNbMWkqhagY7C1V5EiKOmpn9Gk4MemfyliP+GYxviZaq/cMrYNTRyvB39HiCoVF0CAOgA4h6PVeCBHS3QA79ZJbF9Q06dPlkK2fMqwiQT9lyLwx8H9w/eHw3xWeAv/TwuPhf+bcCfA/d+5I+J8XLoyNgOcocDxSXhSeDN1nALxYcXhxxzJY3OgmlbKCFGrv3B5tNEIFCT3pvDVcqHWqoGwctmES2z8pboWMI/U30gSwV4usJ8Y3H5SNt5nCxhuf7NHxWxl8+VtmuTUvS7aLh9kQKdjBY5HpU4XqcARRAqtG9nTmjt0WYi2mRp8Lvr5vf4XPlysYCvM/CU/isukFzGTq7LRKn6j4ou1ymS1e7VPuaxbgxmMT1J6+YBQNCK3dUqUFMJYkMC07vfMPcoyIerHmobkIab6lUOvZN7FIkJpfYvgK9eLmmuJT83FN7i3Ch1RRDrxkw0pjO4WmaSjJL7BqFbc4tq7mDiRXXWzvGiNqiC9GwOQobugf5YZHzu/hEV0MPowwCeZVIDvd1HDtFV7ZuLlwgmU0ahU0KuDq0Hq5XVd9Lg3aKEs2PupL/xuThNN4x4PQDeVqvAtQx/QWYRfzEf2HYbBP9EtYbENcy4YSSsPpuY/66gdjHNAZPoob0vEj5o09m9IopOHiM3HhQjd7ixgXhEqocOk+RgVeNFy8RfUDKRJumlKurX1i4DT+ldL4dwRjw5eh/MJ8PPbJQy1eHUYrSmk6HYgdIY+i/BDVDF9x6D9zWWrBUwefWi3azUr2GPMOxIhpJkg0nr2hpGLtFhfJnF4qd9MmiON90eAAixU9EY1ilm7caQPAkardxx+zgz42HyiGxQBbs+QzvUC0ZhL3zoBY+oYC6qsavnzqayZ85dKX/0mo7AXtdlQNRBWorzr4KtZrwqW3V0AP2ktO+F5MRb6UoP68rkyuf2pdYeLkmqSZqzQ21IxYISN4qKPFOwg6ufU2/iMe150r0E6HdTqplIYic4QbLCXFm12XkEcr8sNhzE3hPDvNJEoT+5Y9plmJY1rA1SCm+DIO6ggWhxwPWqXHj0aJfo0Y6wL/Yl1eXcqBzTC5VHXqUp5yq+kd+RT4/Tbm99+VKX4vRX4/1mdJ29uWqHypC0Vk3GDI4Jhwug94T7FZcSrVSrxfc/1XFX4zxaATUPv72AEYXixGwGJieTnuBCiLHAOL678i+ooLqkGL7et2mezijj2qcA90TPe2h7yxlYB7yktV+mk=
*/