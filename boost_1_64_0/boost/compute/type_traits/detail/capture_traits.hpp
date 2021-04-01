//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_DETAIL_CAPTURE_TRAITS_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_DETAIL_CAPTURE_TRAITS_HPP

#include <boost/compute/type_traits/type_name.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
struct capture_traits
{
    static std::string type_name()
    {
        return ::boost::compute::type_name<T>();
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_DETAIL_CAPTURE_TRAITS_HPP

/* capture_traits.hpp
YOIR9hcGZ8nhTwEU8vd0cx1zEoEQz7+Hprbrph085R2sbnmmVS2NrzvGHwrOGilYzdImXPf/97u2jXPPxdvhoMIg0ZBQvdRwZQIsKSgD28EclLRnE4Aluy7sFi09+72yEnY/3rnhinaBaWlfm98Wvxjoef/M6hSjZSBG2IoMFkx03wrtl9JV2rErivbSOx95PGhKLmWw7ay5S6A5r0+aTfP2pS+jr+lGyMxKK30wznl7c9RuyLPUo1x1OpjGFHWWtQtRsA7DqYfBLul0ZO52CKNpCGEKThQYzrKRTd9Ftguw9K4vyAxmg+xi94BlRfATc81NC6eItBU26VdifWcVkeObvaliIMn+3/y0H/tlTR/yiiza8yVT5yMNre0ScENODmeX3iRyWylOk5ngakwfuQjIDTuGtByTUmfTACwiwROIM5X4NPyoT0NpiCCgzfCKg7IXDo+B0Iji/Iui7XZbrlG6mQG3H9XavJHT2zUoF8nHhs13q9r6lS0c8Ha0Ch2Pdaq7MWKOsuZCrJEGGdfbvwGlMCsonMbxo/9Cv8gfgtV3tD9K00Gu20ye8Q==
*/