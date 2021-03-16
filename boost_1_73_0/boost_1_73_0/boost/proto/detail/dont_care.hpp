///////////////////////////////////////////////////////////////////////////////
/// \file dont_care.hpp
/// Definintion of dont_care, a dummy parameter
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_DONT_CARE_HPP_EAN_11_07_2007
#define BOOST_PROTO_DETAIL_DONT_CARE_HPP_EAN_11_07_2007

#include <boost/config.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        struct dont_care
        {
            BOOST_FORCEINLINE dont_care(...);
        };
    }
}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* dont_care.hpp
wHa0hVlzbRg1wIL8OwCWFjjQtN2G4s0oC5T3lgDazg0WXIx2tmWDA2/fYcH6+2y4eDOO1bc6UPWhDT+h3cfw3ei7kY99NqRD2OZlDvQaIHIuWzDhU8T9FnHw+dWXsW3fo45/sGBjCfanKy1YhXJZjDb9yH4bOhU5cNEYC+7biPpH3S2/04bDxovvKha8OcyBMWhbx32EOqlAmey1YDz65D+84UC42IZnWiz4Y54Fc9/A/ow8jZkIMBxlUHO7Bf8=
*/