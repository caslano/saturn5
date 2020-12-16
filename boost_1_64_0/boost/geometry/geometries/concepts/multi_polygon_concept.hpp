// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_MULTI_POLYGON_CONCEPT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_MULTI_POLYGON_CONCEPT_HPP


#include <boost/concept_check.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/metafunctions.hpp>

#include <boost/geometry/geometries/concepts/polygon_concept.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
\brief multi-polygon concept
\ingroup concepts
\par Formal definition:
The multi polygon concept is defined as following:
- there must be a specialization of traits::tag defining multi_polygon_tag
  as type
- it must behave like a Boost.Range
- its range value must fulfil the Polygon concept

*/
template <typename Geometry>
class MultiPolygon
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename boost::range_value<Geometry>::type polygon_type;

    BOOST_CONCEPT_ASSERT( (concepts::Polygon<polygon_type>) );
    BOOST_CONCEPT_ASSERT( (boost::RandomAccessRangeConcept<Geometry>) );


public :

    BOOST_CONCEPT_USAGE(MultiPolygon)
    {
        Geometry* mp = 0;
        traits::clear<Geometry>::apply(*mp);
        traits::resize<Geometry>::apply(*mp, 0);
        polygon_type* poly = 0;
        traits::push_back<Geometry>::apply(*mp, *poly);
    }
#endif
};


/*!
\brief concept for multi-polygon (const version)
\ingroup const_concepts
*/
template <typename Geometry>
class ConstMultiPolygon
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename boost::range_value<Geometry>::type polygon_type;

    BOOST_CONCEPT_ASSERT( (concepts::ConstPolygon<polygon_type>) );
    BOOST_CONCEPT_ASSERT( (boost::RandomAccessRangeConcept<Geometry>) );


public :

    BOOST_CONCEPT_USAGE(ConstMultiPolygon)
    {
    }
#endif
};


}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_MULTI_POLYGON_CONCEPT_HPP

/* multi_polygon_concept.hpp
mnsdv4N01HfAN1BOh4KlaZFnKU6CtjvuX+o33f5GO7IvOm8CEu2yq2AIX+lZWFC63C4/218X0eW8S/H3SP2xnp1/aWJ/OXHR+4o1Bvf57jxR3PzCbjuROha01o9ni/15hDGSduv9RYnZADUzxGycmC3WsvAfs/78JMsiUcqiYd+Q7Pc9qG/e6FpvLav9WlYo8otG1pn50s+nrPiUtO5zFrsH4ToB18aq35gTtpl6a1z121+Jly44oz7rmujRcKP5rYhvvNgkSBdG23Up8D5e+Bd/nY0LeJP/FqJx1fA6N9avqZv2jkQt/2Gi9zcuJ77v67e9spzYt95qvzlU3Lasc0P46sReRz1W3PQxLub/dxH/8PQepfeWEeI2yf62Z3imrpFn/HCgOXEl3z43xxdxmX7fat8ha9t/3LdUAfpmrUeyNlR+p5nrcJSbKK/9mb7lpYXFBmKkKo9eMuDzqJaN+u1vfyMW1t/Um4XMMbx5dFtKwPJSf6fjRtur+DtmjDdCfL5FKaNJaznZfkaKn1z0OPHzrTHBCNV+ya987e8+Q8SdO2SSEdfw+VG/KW0tbr40hhuRQZ+HM6Dft0Y6To4Wv38zphjO+s/Ldp2oHCDfm0h9momeK34eMX6LWXsj296jopu4u4z+6nzMcGubXUGZ5Urc4qQcizxLFlWXlmrcqAtSv1ZRt2pitH5F13xk1q806leEWd6Yf4U5z+jy3DoUfZjPen7yuNHn12xDn19Z2+8Y6F3bz8p+qYtrDP+6uB6dsq+ri3pP2mhY38NQtlbf2PAZ1/4mnrRibqdVxqJtB/h/I/ORrft/s1ETp+MtvW9fZO39NNCnvtPtFuXNz2fypyjo/oLivtzRm7A9iNZ9DSfJ59m4sKyo7tlY7RPsbyweFH0ZdxhaBKLfWEh7fwf5GlmFrEFe+wF9QKzft7USF7/+mu+O5VfmpP0rzfY/L8svP/Q25AnaX2v61d8Quw3dJHqmc4kR2Vjbx59/n3Gd6IOdFxlG4LZv+xllt/1NovdwLj5B218r7k51VgVq+9q33ylu0p1lhrOxth+0bXN4Jf5H2207YpCpL2duLYJ1AoPstr1ezHMcYdqHzbTNluJyuF/fkqzzIbdK3I6GfI2LSUYPx0VGkRErdpbfn2IzhWvbfitlb75SD/M9dWOzUySOfXGHbvt91zD9nu2oMhrpV3RPBAm7hP/s56xeg7X8RWdmTfRefNca18BPrLaJK8XNKPIgNGi4Q4boPmmiW3E9InFd6ZhqSD9HYMWJ2s/F5Mp9tAvtKVL7Oe3jpG+7/kf2dW8O+vf1dVcO8u/rXkb37evGW88o+s2zeW5rplD3Chzq27aZMspfVLmwpEqnmpkp05t7ZYM2PkLi+rn4z9TvRa3wTrPHRR+LPijkHGOKIyaE/NJ9pmadJt+zN2hzVjhtT5UyDjq/3ELsnzUSHbcbfm7IXOv76gLqwTwaibsNaZW5owpzyxwmnbuGt3CHNpP/3JHNmE+a6BrlmukaG97F2Tq8qzMiPN7Zlvml1PBw5ql7eP/hNSo82tke817s/dSmWXiJO61A+mitU1OQw9Felus4LdAeM/HwQkn/ZN3rj90aJD0tQqaxouwVIyFQvpBvaOLus6D9UHYjc/Jnit/njL6sckvEzXD8Rzoq85dQzPKSBB/ms421Nu8Dcf++mNFvyTN7rZgdEjP5hgyzr8XsDTGbrGP9ZqdJ+TiSJTwJ0E7jfsL8E+M47KSPi/Sxe52w/2BEYkf42EX72L3NNd4xwsVuMnZJPnbNWDH3mtGPdyfsBYdFJGV+zJyDa+aOqPkD5RUWzzRcRHPXacwdppt/8m293Bf8vzOPhVslzFj++cw=
*/