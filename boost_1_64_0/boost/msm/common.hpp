// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_COMMON_H
#define BOOST_MSM_COMMON_H

namespace boost { namespace msm
{
// wrapper for mpl::for_each as showed in the C++ Template Metaprogramming ch. 9
template <class T>
struct wrap{};

// tag to use in grammars where states are seen (init_<<, states_<<...)
struct state_tag{};

} } // boost::msm
#endif //BOOST_MSM_COMMON_H


/* common.hpp
UzA+1YkjUW3GK0tdiKmb6Y6xyZVLtLsL1zTRbpQZsD5S8ySxqDPl9QVuOYQBPCtSMxrqd4zU3TpsBniVvHff9qyx3GvOJkur3AgMGETw32WtU7qkKp0lJDpNOAcfgLBSyu1zz9XzcfGk+tWhNlLG6vlL+nZ/npP5//Z0jQtSapeWAvwZ/B1f6ux+JF15HSv9QULJSx9t0Fv9dZW3KNGj32H/VmECXtywvyy6tg01oNoJFeC4so8mTBhX9QlQRCerDEZSBXxoRAZIp5Qta8GpUcl9ueC4Gkr8LOSs4Lx57usio9dEukCI8KnqTmwTa9+tc0T+NDFSjep7DMP3CW0RxO/lnUuLagy1azbbgwntAzuzQg/KfqVpGyElkg60WJ02FtiRw6WnPw85s4HFJdWTZF/vVuYcP/GtwxVEbhVFvyq/s7dridpWMw/cssCBONMtjDCYetmNwyqBZrN406JtoYA/bWO39b8LKyXlxHPYtC1QdHN1l/zEZCJoRoHbDIv2ShGJwqh2oQHonpZSPVFEm3jZS5+zywvLl7Plvr6YBr7S57/ARB7tCLyBGQ==
*/