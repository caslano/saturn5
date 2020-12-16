#ifndef BOOST_ARCHIVE_POLYMORPHIC_XML_OARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_XML_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_xml_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_xml_oarchive :
    public detail::polymorphic_oarchive_route<xml_oarchive>
{
public:
    polymorphic_xml_oarchive(std::ostream & os, unsigned int flags = 0) :
        detail::polymorphic_oarchive_route<xml_oarchive>(os, flags)
    {}
    ~polymorphic_xml_oarchive(){}
};
} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_xml_oarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_XML_OARCHIVE_HPP


/* polymorphic_xml_oarchive.hpp
ZT+89eKVCuB+urMhqKcbneeASzk4rGVNnt400CnRdP26qiikY6HYcyMp5mSOifAksrCYyRehXDiWpu9IS29SPg7lAjJMwB2aRbDEFXhP203s8F0EcztT+gJXJvw9brCJx8ZZ+oblEv2ENFxKx9pNcRGF+rnfRkNpBfHqowNp2c51uF76LgzD73aINiYKSo2keazARqE+8h/0Ji8kFnn1WGTweHgwAkmnAOK8ZxkX2QCsM92yteNC6CwdnblesuEaorj+8kE+BJxJ9B9lltnD6fWDriiG8BVH0jWX47cJLUpx0BJIhdQhgWjEO6dIMLd3VFH/HulSwcZkUBmEDLKMeHnO8oPOAk3HO6l95fL9ZPeCyz7r1Y0rODdVGB7PYnL+fOSGeQeoHA4g7DtE5EBGijcSzXztdNVsDEPpORFUqWlmJFp/tSW14Myp9Dd1vaosH9eH0SESny8F9L6RSt2bdQmSrPTe3q9zNB0t/9ihthL+T1FBDS+Jr7RJ+1if8hXjX1MV/1LkK69DppQzIMnrIsVdsmHIhWRGk75d2nu0Xqkcn8pwYkPi2O6siUuqWfp7P0GtXif1WZGYHPuSEbOH2Hi+E/sojNY2VFM8JYD1GKwAgio68ctQGM7RZJ1z6fjW4AuKJDmLv1DmAHNSJOA1xsIYrK73AC2gHcLUVtFwhXL8sKWo5i+rrg5wiElo1bGBCr7cwC3tkGfyks+wBqhKPWOaPKMC0tJEphz2HEK+ArfxAvCJ75OPEVJXLEThkjjxwwZYT/zmH6opLJAxFy6Ek99xgHHyWckYhGUK0BdMhcZ8WTM1j5L0QEAJw8X7p4q64duCu+LXt/6Xfkz77/bqbnEUgN2IgptPdhjrcW73O+f2yct8e14nyPOIX9x8xU5PS1dNVYInsuhIiicWUjt3YFNeZuX8T/GfNwrRLhGatwAhWB2GEwny8PDiYvIRhpW8DebAjWP241PHbajCzze0E/zcFGJqf8MIPeRoZgwrIUCVk0BfN3f4m25gNclvmPoFgc2g+IsGZHmyiwY6smAzgv0+gP8Yk9+GO/4JOAB69GKC3i7nbW+4tDdYsC+6GhqMV+SVEN2p5HdyaFj5mHJ4lT5EorE+539r68l+JN6ttpM5um8XAJzlkwR/vbN8n3NurwJsQ4cciUHqaVlTmeCJ4oijsW61B1Xz9+E/bxTFnNB2FGS+Q3sgMXALIM3qn5e8e6iKeJuwosKzP2O95/RS92tFh0+fHxaRVDqcv4UXrU/KWO99AyLaPN8Bu/ctboCf7MZsWWPko8y/DpzBu0h+MOGMzKC09kBGY5+HeaWneEgMrJ8VL6ABK9uqQNuGtshDkEQm1rfikfKfnQ/BGuvvaFXYfkC+5PXcU37pyAD2KB8ILco+C6raZE6OPTWRHGrPL8kS77fjGYaP3bSA9klpYYKLiUaWTB/W45qSx4tvCMpRGCfRfxFoDsUT0EwCKi8AJAQ14lsQ0dJ7NcUB9kwfkO65jA5tOzxOX8XQ1QV2wJSicjq94iO0o+I66g9/LWhdbwraS3HV+5poXczfuW2ucr2AX6qx6AgBX898uMctT1Xx9S+JM0ZbMgFgkADjy4yTLO0roL0zWBtkLNycdM4FaTn/RzZCH4VsGASvRnEYBL+t1r+qNrE8Nhgy2MQob0gTEfL7vZix2iJWnprvnMyOfm3rb/MBfGSIM+p0xUsBTCRWWhQBgAngK+KcCZn71xRToSiBfh9ubZpoJJUvVHy9K5Redh8SWT0BkdUm3REpSotvxNFfbqyKGm8UeDTH90Lr443vwya1xzfOOr4FanwLZHzxPL4nMb7N+vQIGV/Xkx2f2P+2NtjsROBOp1EyoVs=
*/