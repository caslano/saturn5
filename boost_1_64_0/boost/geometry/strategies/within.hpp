// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_WITHIN_HPP
#define BOOST_GEOMETRY_STRATEGIES_WITHIN_HPP

#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/tag_cast.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace within
{


namespace services
{

/*!
\brief Traits class binding a within determination strategy to a coordinate system
\ingroup within
\tparam GeometryContained geometry-type of input (possibly) contained type
\tparam GeometryContaining geometry-type of input (possibly) containing type
\tparam TagContained casted tag of (possibly) contained type
\tparam TagContaining casted tag of (possibly) containing type
\tparam CsTagContained tag of coordinate system of (possibly) contained type
\tparam CsTagContaining tag of coordinate system of (possibly) containing type
*/
template
<
    typename GeometryContained,
    typename GeometryContaining,
    typename TagContained = typename tag<GeometryContained>::type,
    typename TagContaining = typename tag<GeometryContaining>::type,
    typename CastedTagContained = typename tag_cast
                                    <
                                        typename tag<GeometryContained>::type,
                                        pointlike_tag, linear_tag, polygonal_tag, areal_tag
                                    >::type,
    typename CastedTagContaining = typename tag_cast
                                    <
                                        typename tag<GeometryContaining>::type,
                                        pointlike_tag, linear_tag, polygonal_tag, areal_tag
                                    >::type,
    typename CsTagContained = typename tag_cast
                                <
                                    typename cs_tag<typename point_type<GeometryContained>::type>::type,
                                    spherical_tag
                                >::type,
    typename CsTagContaining = typename tag_cast
                                <
                                    typename cs_tag<typename point_type<GeometryContaining>::type>::type,
                                    spherical_tag
                                >::type
>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THESE_TYPES
            , (types<GeometryContained, GeometryContaining>)
        );
};


} // namespace services


}} // namespace strategy::within


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_WITHIN_HPP


/* within.hpp
x4PV+7jjwer2br2sMnqO23+s3tfNv9UvufOr1V1sf6Orjd7B9d/qn4I2fqt3DNn4re5mdeR7e31g9Qir93Xjb3Whq2/1UDd/P9j+ufat/tm232h1gZv/H43u7+K3+neuvtUnWr3Y6hOsDq+x+5fVpVYfb3W91ePd+cvqCW69/2T0RKtrrb7Bvb+x+jq33/9sdB93fFr9hdufrP7K7UdWf+3OT2uN/sbtH1Z/6/YzXyNce5Lv6+9cfatXuf3d6tXu/Gb191aLZ/S51l+h1Ze485PVcXd+svoHd36x+kfXfsDoNe56w+qfXftWr3X9t3qY9d89aLTnrresPtjtL1YH3PsJq4Pu/BQyeojbn6w+zcVv9e0ufqtnufnOM/oc177Vea6+1We449vqfBd/G6O3tLrS6mpX3+qtXH2rt3b1tzC6rTu+rW7nrr99neXV0NG0p++H/IKdzPHodJPRzU7H25j1o+9//PomP4Y29QvM+nO63uglTse2NfE7XWv8dX/F+Tf5pU43dzDr3+mw0c1Oy3a+jrzq/O1g6jsdDpv+OB0Jm/pOR038EX3/41c08Y5wutGUr1PtV7Tj4XR0ezMey117tr7TEZNfn9Qmf4XTpcZf93+4+jZ+pyNGL3ZaOvtaXnfl831d7HTE6JlOx9qZ80FSm/zwG06b8StyusjoWqeb2pv9yunmbUz7b7ryBaa+0y22fbSpb/IXOx3d0vQ/Wd/o7m+5eIwuRZv6Rtc53Wj0EqejJl5528Vn8oudbjG61unGDiaeZD5ayel646/7Oy4e0/+pTkdtfafjjK/frlt/RsecbjD+5jhdavw1O11k/BWY9z96hJv6Tjd2NOPpdNjkL3G63qyf/H+68TLtFzsdMeVrnS4y5Rucjpr8FqdrTXzd33P9MzrudOk2pv/JfKNXO11k/EXfd+NndKnTzaY/C1T7GSa/yela4y/8gdMmvwht6tv15HSsg1lPTteZ8pEPXXx2f3K6yR7PTke2M+PpdKPxn/+Rmz87n07XG//1yXyjlzvdaHT+CteenU+nm42e6XSLnU+jdUc36+Fjp+36czps8hudjhjd4nTU6O6fuPqdTH2nw3b+nY52MfVV+xkFpv1P3fgZHXO6yPivdbq2i/HndMToZqdjpnz+Sjc/ZjyLnI50NP6cjpvyi52utf1L1jc6+pnLN/HFna43+QucbtzOrA+nm+1+97lbfx3MfDjdRL6S0y12P/jCxWfKx51uDpv5cLqF/vnsxt/0L+p02PbX6cZOZv043WTn/0vn3+gRTsd3MOvP6doOpn5S2/PJVy4eU780qU28c5K6wNR3Wtqa+l+7eNua+k5H2pr6TkeNbnK63vQ//xs3vmb8Yk4XmfL1Tss2pr7TdR1M/W/d+rHrL6lN/ZlOF21rjh+nS01+/nduvIwudLrW6KlO1xnd6HS90audbjC6aJUbj/Zm/pxuNPlLnG4yOrzazZ/RMaeli9l/nG6x45fMb2fqf+/aM+f7Yqeb7Pkgmd/O1Hc61snU/8HldzHz53S9vZ5yOmLKr3C60fQv8qObX7v/Od3S0dR3OtLZ1He6aHsz3mucNu3XOh0zeonTpUaHf3LzZfQIp+uMrne6votpz+moab/7z649o6c6HTN6idOlRhesde0ZXel0zF6vOd24g9nP0Ka+yS+QfFvf6BFO1xo9x+k6o5c73dLJ1Pesjtr17XS9KT/T135JE7/n/Nv4A86/0SMCrr7Rc5xuMP6aktrkS9BpO95ON3Yx9VX7FbuY+J1uNrog5Ppj15fTsoOp73SjbT/k/BkdznP+jC52utHEV5fnyqOVkuVt/G1c+7Z+Upv8mU6Lbd/psL1e38KNv4k=
*/