/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_ALGORITHM_ITERATION_FOLD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_FOLD_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/fold_fwd.hpp>
#include <boost/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/add_reference.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/algorithm/iteration/detail/preprocessed/fold.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/preprocessed/fold.hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#include <boost/fusion/algorithm/iteration/detail/fold.hpp>

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#include <boost/fusion/algorithm/iteration/detail/segmented_fold.hpp>

#endif

/* fold.hpp
Dhhh1yCm3CbWIcQi9XEP7GFoHNVLuYipC1XvEOGxa7T22kTh5uVUorEdFQSMzenJXMWpmmgWFx9iT04Es0CbW38Plxxg9BiekA5LnZXjDodhW3IhxLI2PiKk923ZRauaoUNLj9nBRE6ifduQKgxnFGiNQgcUHqsekqK7uzgcYqFo74DpoVI0WIa1dNvH/fBEa1ZSu8KYgsdpQklXClY9UuyedYml7OkdpRZ4VROBMAOGF6gjDOpza84Glr60wusGshR70J6OiXM5tpjyWE1UVcaoXgsuSPNZbFBjdJS0PVFojsPk7QUv7JZh0vpQMevZkIuYislFTGAu9J2JG8OYOI7VdXFz37odnl6eXHNscXMTpUlUGapb3aDd3QcwKL15gxQUix3Ug6U73O1AacNjw5gil2dZfL1brVll3OCsG1jB8dCkNZEaGxf8d/o3eO3y8RbO3xqbsGUzo8Fh4Yhn4DRMhmXMhovGlkoOGViwzMs7E+o02JPqdj21WXdpVMNXYdo0Kg84tgzvwpr6x5vfMamJHtkoZ4vWgAlDlWD5rk5V5ToctQRM1a4pVvTPaEhpeB/p7oHJa3nMhhgw6uOizq32wZjCXTZ076oM1xbRjZgOO7sL/4rWgde3h3J7m5pHIxeu5WQiLQ3f45w+
*/