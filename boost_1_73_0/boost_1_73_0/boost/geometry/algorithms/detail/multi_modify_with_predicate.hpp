// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_WITH_PREDICATE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_WITH_PREDICATE_HPP


#include <boost/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename MultiGeometry, typename Predicate, typename Policy>
struct multi_modify_with_predicate
{
    static inline void apply(MultiGeometry& multi, Predicate const& predicate)
    {
        typedef typename boost::range_iterator<MultiGeometry>::type iterator_type;
        for (iterator_type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it, predicate);
        }
    }
};


} // namespace detail
#endif


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_WITH_PREDICATE_HPP

/* multi_modify_with_predicate.hpp
vk5XNe0DJBAEzjd2akgQhDRYFTpjkPl5GuVi812MPSofPm+A/VggTh3InLLpkDcVu52c1+lJ4wlDSX8GvUCXERIzykB6mpQgv8E86AiFloem3mE2WEwQm6HPH3lOmHWEHazDimJvfppx4Pu+9KmbTm2GQjPa5JpNreEpU2AWWMskkLOyAdhBgXJvWCNE0O9omMSQC5zILs31fu5Man7ghKJ2eGFJRKGJFl0jlxFBVlisY9AB2Awwt8dDZHaPbDgd0rv3jt478Kjilstvq1pNIKN1vEpuY4kN2E/n4wmCufBhqBEsMp1+748PnXYu3qa0jqcldWA8yqpKdJykXEoiGQl0GcKQMQbUxZMgshTGsWZhG//Y1qsmDBoxLTL65CQXF+mhrmoOKPql4iysMQlqDmwQhh+jt6enfQheMQrU78EsVJ8EPQerKvm/mAU3zBXHxyY6FsNTMDobNAPqerikeFf66dnr1+VtWzmuazTuaUHjSsovaZ3nUoUPHuc3daJdJv5zvslKl1203z2gJBDxVAR3O3XJyXjnGQVd9Oiw0+19PDl0VLPCqCtyaxIcgV3lXgH1Rf2ty3p1fOAjL5w5Spq+Ss3KtgFaXyaPfh8r5KXsKq9g0/4hhnHXj/UdmhK0SpFCqHQ9ehHVxll6
*/