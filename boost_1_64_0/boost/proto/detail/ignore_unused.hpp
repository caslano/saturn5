///////////////////////////////////////////////////////////////////////////////
/// \file ignore_unused.hpp
/// Definintion of ignore_unused, a dummy function for suppressing compiler
/// warnings
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_IGNORE_UNUSED_HPP_EAN_03_03_2008
#define BOOST_PROTO_DETAIL_IGNORE_UNUSED_HPP_EAN_03_03_2008

#include <boost/config.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename T>
        BOOST_FORCEINLINE void ignore_unused(T const &)
        {}
    }
}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* ignore_unused.hpp
Q6mkwK8HNcSF04eR6kbtwlw2peZdjaTs+97JuEK5YxtgogojQujrJvJDNWaBjcN0iYB/qyGGWJa+1tO0QgGHX3i7/ebwOr4+3gSK2GbE+YrtEBOs3HM1Np+42As2rHW1LkehBHPEFwDgs+p4fEdrp8+L7L+JTtei6EoIpOuWX6/ec/ZQ58kGHOrzrROImATQjObeFRwg/daxmxP9OUHfr+9d6hE11dFVyFyv5JrbqVeb/C1HoXumC8AA3Hi9TNmtsAJwMYaZw6aygTocNTjzAB9ouKPAuqKY5MmGM37myGoxroN0eYK9h3pvXTK8MXaSiBo4Q8wa1B35OgWDV02Kmt2nEtteZ9ezZPbZdMdfIuwwfp77xbfSF8rrJMbSsBw9pzGyRASwMtCYhQLsBl0lIumnqoPW9fk8WGFcSdYhWYlk637cN4qpdI+BGRoV7AUWsSAXfR7fyk0Gcycj9P5T531djV7xbOBou5hdFM8PBp5lq5ghS5clgiYgd6VqwiUcICTzeJM6FBcB/Or4K8N0zD2OTFShOQaAi86Gw6y2Y9tGGpKPeM12WyProA==
*/