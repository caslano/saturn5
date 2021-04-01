// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_TAGGED_ARGUMENT_FWD_HPP
#define BOOST_PARAMETER_TAGGED_ARGUMENT_FWD_HPP

namespace boost { namespace parameter { namespace aux {

    template <typename Keyword, typename Arg>
    class tagged_argument;
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux {

    template <typename Keyword, typename Arg>
    struct tagged_argument_rref;
}}} // namespace boost::parameter::aux

#endif

#if defined(BOOST_PARAMETER_CAN_USE_MP11)

namespace boost { namespace parameter { namespace aux {

    template <typename TaggedArg>
    struct tagged_argument_list_of_1;
}}} // namespace boost::parameter::aux

#endif
#endif  // include guard


/* tagged_argument_fwd.hpp
mVg5o7n2SdXVxVxnVG/5scZjkeacCrx98LypJDgFGhCFcx/V7EJcsFft8UVd59ooqICzV8BCHa4DJCTyXreeLEjdzEJdXWx2SpJIPwxz+o0ftjsCMtY4oJdYhVeU3sqMgxEKx8TlcBv3D2mrw/BkAI3YjgUeT3ic8riShaQRrXRwIhXWeJseTAXK5Pz5eKuUC43h5YHCOptx+j27RDyDIpCcrXVLFhZqZ7exqisfZFylqfQqLXOuU0bUJOAeqMagsCGIpvEK/XctBbEOQri9qsIB1ikqwvI16YhXtACmzYC3zWKWL/PZ3iQ1n/lP4VSEeEx+h1cjHycXX17UOyLZrYOxYDEPTcKw/zwnQb8EM2c8nDrjqmE4R5IajCXk6q1Yc63FFlF1L0D5ETQL7V/IW6yp3X/hb3A/iSOz7HTqkdBP5vgB25DrIo3wbXEuTaz1lRqbjy7ODR31g2NjzhUVtnAheZWCFI1vt+dYxgAQGO+7TQ1fPzebmI8b7TqX1vn7BnQHvFOBid5dTeQhN/ae2v6q2il1ZvBzDImbmNHt2qFKSYkloV10Te/bSg==
*/