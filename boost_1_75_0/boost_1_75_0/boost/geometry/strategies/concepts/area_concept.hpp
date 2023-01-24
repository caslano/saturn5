// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONCEPTS_AREA_CONCEPT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONCEPTS_AREA_CONCEPT_HPP


#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/geometries/point.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
    \brief Checks strategy for area
    \ingroup area
*/
template <typename Geometry, typename Strategy>
class AreaStrategy
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    // 1) must define state template,
    typedef typename Strategy::template state<Geometry> state_type;

    // 2) must define result_type template,
    typedef typename Strategy::template result_type<Geometry>::type return_type;

    struct check_methods
    {
        static void apply()
        {
            Strategy const* str = 0;
            state_type *st = 0;

            // 3) must implement a method apply with the following signature
            typename geometry::point_type<Geometry>::type const* sp = 0;
            str->apply(*sp, *sp, *st);

            // 4) must implement a static method result with the following signature
            return_type r = str->result(*st);

            boost::ignore_unused(r, str);
        }
    };

public :
    BOOST_CONCEPT_USAGE(AreaStrategy)
    {
        check_methods::apply();
    }

#endif
};


}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_STRATEGIES_CONCEPTS_AREA_CONCEPT_HPP

/* area_concept.hpp
sf5i1FFHmcJSkf5u1HXjisTXLJJ3UEne0DujbYkin2ktJn/cWpgVicGeHSEMNJi1gMp+Ma4/6i2bzY7RU4o9GNyvZbFOPFBRYIs6GLqyQK3v10tOC27uyLr50GpWXz5f2tJ6vDCRKcvW/MtDL/Tdxa6Wj5CDP4F1Azn98isfBzqV6LNRECpTRsw9bk6roqvXWakQmFUbAoOeNEWK5o+LRS04iqy39CEzzsFtPv8FqeP1ydTOq4LFjmwya1upTgAKBbAJc1ZQf87yN+dNvlLAbXwGfYDrmQvjruL9sNGelZxiA8CV7g+wQtu3vyB1UtWR8sZ1DtC9VLfe/FvZ7nBm7yHAj+irlKnL38VKYyaym3znUddEDd14MM15r8FIExB/AS6dUHlKB6HyIZ031nplQGUUi6VVFdJ3bQ0qJsuSvyF1A8I8CbS3dXRxM4Ded6M2sfoUTLuxr37HmGOtUqdPxKwFDoJp3nEzHvF9nKqKcEQ+GMjwEfp5BCFILUXnOvqRb0EU+P2vSB3307BO3SudsYqs2KWGjVWd5UEnRKPE55M3bNZpf0fq64VsGH7rhTbMfkQerGEvSCEDt/LDXjHelxSXw2N3p2/nIEsHM9wvb7lm4x3oPg3pcKF/Glhu8Dz9cEuhM73cSGadT7lg+d3nDq6ZlNtuXqPn4XHzx+1ZJo4OzfzqCdSECNZfyMf8WCK9Oa99qsNxmAK6aX/+
*/