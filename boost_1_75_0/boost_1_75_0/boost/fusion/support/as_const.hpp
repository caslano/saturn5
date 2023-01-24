/*=============================================================================
    Copyright (c) 2012 Nathan Ridge

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_SUPPORT_AS_CONST_HPP
#define BOOST_FUSION_SUPPORT_AS_CONST_HPP

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion { namespace extension
{
    // A customization point that allows certain wrappers around
    // Fusion sequence elements (e.g. adt_attribute_proxy) to be
    // unwrapped in contexts where the element only needs to be
    // read. The library wraps accesses to Fusion elements in
    // such contexts with calls to this function. Users can
    // specialize this function for their own wrappers.
    template <typename T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline const T& as_const(const T& obj) BOOST_NOEXCEPT
    {
        return obj;
    }

}}}

#endif

/* as_const.hpp
YHslpanMFpq8hvTD/EmcN/l2YPOmbh2w8zvtuGQPEh39XmS2syKfsydp/hQh7NjJwqKEVi+65DluIvL8Spp64Y44+89JFWev7yDO7EJCgMzZZ8TZ530Vzma1Z5x91B6cleacfdkcnLWWOauyk832bKptZb+8r3dSw9z0qMFpQzWBdYMjZ27Kq0HfaSYimuSM2uDuU8VTsaxYBt1xCsug9zZIeZWFtZejbUO1Ncnb0UhD+zrKvaimrY7HzdW0v+OGhg5wXNXQgY6TGjrBsa95rrzT8+xonVGBTEwm5ilbT/5X4tWoiPsbRYuFtRFNnTczFPlcPM5ar9hoPH+TPvFOlktmj6BWWxDiagzKaMtar4NBCvtUS/BRqZEyd5FPwnHWdilk4MfcKmRPns80CDE2m2SEqAMjRGADhtbD0nWG7KKUIDHfdAiUnYu3CTdek0wSYTBJWG46myScFrMob38fY3mbxDm5spV1zhFxkmHkclO5f0q3e4k5rRKi9M+f27AcllHlcMwRqYuSu1IT9NIlx1Q5Hb8dOWUJvNEUG7R5ntmm7E7ypuzatCk7NbSURfj9tsb8pNl+YzR2DMw0mPxq+m2Rz+/fslIZzQ7cHvuIisQmcfxtE7lI/qLKL+qtFMmp1qxI7jMQXx3IFlVER8nGKIzZ35LIihNe3oaSYPFObIJzNsrxmq5yMdSlYkgJEYvh2p9PdMQaGYZjDYoh
*/