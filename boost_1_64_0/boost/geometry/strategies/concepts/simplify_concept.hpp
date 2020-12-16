// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONCEPTS_SIMPLIFY_CONCEPT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONCEPTS_SIMPLIFY_CONCEPT_HPP

#include <vector>
#include <iterator>

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/strategies/concepts/distance_concept.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
    \brief Checks strategy for simplify
    \ingroup simplify
*/
template <typename Strategy, typename Point>
struct SimplifyStrategy
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
private :

    // 1) must define distance_strategy_type,
    //    defining point-segment distance strategy (to be checked)
    typedef typename Strategy::distance_strategy_type ds_type;


    struct checker
    {
        template <typename ApplyMethod>
        static void apply(ApplyMethod)
        {
            namespace ft = boost::function_types;
            typedef typename ft::parameter_types
                <
                    ApplyMethod
                >::type parameter_types;

            typedef typename boost::mpl::if_
                <
                    ft::is_member_function_pointer<ApplyMethod>,
                    boost::mpl::int_<1>,
                    boost::mpl::int_<0>
                >::type base_index;

            BOOST_CONCEPT_ASSERT
                (
                    (concepts::PointSegmentDistanceStrategy<ds_type, Point, Point>)
                );

            Strategy *str = 0;
            std::vector<Point> const* v1 = 0;
            std::vector<Point> * v2 = 0;

            // 2) must implement method apply with arguments
            //    - Range
            //    - OutputIterator
            //    - floating point value
            str->apply(*v1, std::back_inserter(*v2), 1.0);

            boost::ignore_unused<parameter_types, base_index>();
            boost::ignore_unused(str);
        }
    };

public :
    BOOST_CONCEPT_USAGE(SimplifyStrategy)
    {
        checker::apply(&ds_type::template apply<Point, Point>);
    }
#endif
};



}}} // namespace boost::geometry::concepts

#endif // BOOST_GEOMETRY_STRATEGIES_CONCEPTS_SIMPLIFY_CONCEPT_HPP

/* simplify_concept.hpp
uhgkpoqFYpXYKIpsVIaigxgkJoslYr3YJmp8oI6JdLFArBZZotKHlilGiflijcgS1T6yz4l0sVisFdtE/U22kZgsForV4stNRXa/dr92v3a/dr92v3a/dr92v3a/dr92v3a//gteJcSIIkUroEinNoPS0lPHZ6RNnDA8Nf7PjLFNhk0cPTalSfOmzZs2G9FkUsZhzZq3Svxt8hEtm8THd2qSkjps4sicv/vboPhIyYGmacPO0N66XQUNQrXV3FcbxoeGFiHZY/TwCWkZaSMya9fv26B2r3SdW48+x4AHtY/V0ezosakTPDbuXqFYpSJhLMnc39l2FvuITrHw99gXZP7Uu+Ox3Tr3H2zcEWPxjc78fWMHx/sDtawwrRrzjyd8ROireEXI196ipCgnJlT3fCCer9jAsiP14K1UcsdSRLJXJF/nZ+dBueZLr3b4vUQHUVG0DWPgTE+kpwAGD0s1inIivWrb6YezNvOOeXNYSGtmsXzrFtJanzet7ZZ3bjql86XTJqSzrZB1ysqTTkZ2OoNH+H/GqNSUXVyvMC5q+C67b1ivPiKjuvQ/z04vtr2GDx07dpjxqHdpvXLq7M8hnXmiqpgjMqWzPKQzIe2s+FqparsyplLFyPgzGaPPscWrh/VOjKs2OG3EiIxUWyja3++MEvEFHxrKvKEYv69nPF9k5022wujz2TV38Lihw3ULm7rz9UkeTY6MCR7JR9mSyfOxPJGPMOp6NCN/WD5y6uDUkI+DQz4OzKmDsXxEx4IfOnx4qk6Hw3i128lDMyYbT6p0qfiMN4b0FoX0an9ZML309MGxwTIGq5NpZ+1C3d/euk8OeTlClBSHh22QVTAvhikbOmFHjmO/tb9vDunVDet+QFj3DlsKppc2frzR/H9fWQ/ZI/lxLL1gevb92DHN+B4pznNjUn/Xeq4P6VYP6e4nZinXuQXTlaYeytMm7HB64fwQ6Te/U+wPoUxLigo5+1LB9BwRshPc5W15QkhzTUizYUizQUhzfbI0w5BoYVCq2OgDO3RODOkn27baOcdnbCXKiCPE87F+ar8qmP7v3bZVwvVB6KN/fGxJ/hnZBu+E/FQJ+akc8jMkaX52/fxZMV9eLCNaLnv6X9i3SoqaYbtMT5qP+DDGaZmjTdj5vOTtK7xG2fiM/SRakd04KXbOi6eb7JSyA+M25BuTITqmDJKOMxH6cY8e9w4wLZ1nZ0/L6bZ8nP8NHZka/j6KU6qH8Wpy/jY4nF9DX+ptZcz4LBOGjs8YnWlYhJCH0C9/9JpyIG0V0+LjKdcxbTLPi+chNkRxgYyEMfbMGx0brleWcgzLi70fle/95PC+bXh/T3hvfbLfz94af392eN/2G+9DXvJeu4wqF98Ab5ZUl/kq2/jLkO+y549swh0dR/PdH4vHx2Kw2+QfI6dKKJNMkdNfe06ZtmSBsaai2zWM7xIt52idyMjw6cQ100+Ja/z8Y/P11318vGxez15X56VK8fdP/CNa1lV/ir5vnHgfLcttoSz/LCqKy8L5Z/nPuWU5ztEwfqGza9eBtSPlEbbtL/H8PC7/ea/rh4SOr08M+emdcz78JW9+RoydmDFql867DcN6vxrSqRPSqSkOlpeN8XQyFfQOj/lfL/s+bXBs42Sv2/dh3RqYnvf40z0cuZ4K4/0/xtjxp/w/s+dPcim5a2NYJBv/LLoNwthmeffzMBR5GEdXQ7KCx5ADwvFlW3ZauUMNhgNDqPuReh7G90ikMyE1nkx8PM1fo3W0U773vcP76eF4cGt4f154/1N4Lz/Z7y8sUiJyvPg2u8PeP66P/+RjIBTeB3/yvvYLGwPhjxsrIHlf/oWNUbDzYyYkH1ug8L4=
*/