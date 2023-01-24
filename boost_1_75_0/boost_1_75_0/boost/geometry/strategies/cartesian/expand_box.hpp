// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017.
// Modifications copyright (c) 2015-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_BOX_HPP

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/expand/indexed.hpp>

#include <boost/geometry/strategies/expand.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace expand
{

struct cartesian_box
{
    template <typename BoxOut, typename BoxIn>
    static void apply(BoxOut & box_out, BoxIn const& box_in)
    {
        geometry::detail::expand::expand_indexed
            <
                0, dimension<BoxIn>::value
            >::apply(box_out, box_in);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<box_tag, cartesian_tag, CalculationType>
{
    typedef cartesian_box type;
};


} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::expand

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_BOX_HPP

/* expand_box.hpp
zqVDhmrPNHnwURpkox9E4fPPOx4OHQ+9/atdzQ2YfG48ecofafNPArlcdD26iLrTizx7FGuJERkVzfrFx1zfAOx/cOtZF7O5xC+L7T6bvDf4uA2Q87hLM/zWFT7drT1vWLgopY7D1WgAyCBJhd/i9wpFN3/cPjaJ6BIdOOmtLiRUG6RN9cNMq/QttWPcYROoTX+771SjQHuQqOKSF3rLejxeFDYdpWO3eGaqoUCy8uPpTZDmdNG1mxTQ8wiFd1gao6+tks60V8v8OSuHjx4gJML9OZ1DQ5eJfeNZqCLb1MWCKp0jVXd5s1oD0ivmFLV6qBaVAUXAvO8Hw+q7KS66TpIOBp/OTbosN9WfeLRVZANxzuQdiMU9mDeKj7vTNuUjD88qnsk347OnW0hceqlmUJF25IxjoIR+ham5T48uj6+H7m0TbyitZ5BUFurdMSvzklv1lxRnnr5V72nU7Usbj1xFxffpKuUNkg+qgGoUoNX8rQdk/ak+16REcS5+wp+XVGyeWedVxtxBo7FZLODpZIeR36nPNyW/LDffuBTkpngUJU/YLnzB4F9TJKkK5TTH4IdOfitT0UVb+ThJynceEMynOURa71cVw+17n5XssSItGMlpdvdHqc/eTNkPU5zmOt0Wqo8R7b1ruPKgi2JqQKICIa7owSxO9BpdBIhlR4RqyMU3zozRmvd7NZlRMvz27v00M1Za1OdYec+Z
*/