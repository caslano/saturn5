
#ifndef BOOST_MPL_AUX_CONFIG_GPU_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_GPU_HPP_INCLUDED

// Copyright Eric Niebler 2014
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/config.hpp>

#if !defined(BOOST_MPL_CFG_GPU_ENABLED) \

#   define BOOST_MPL_CFG_GPU_ENABLED BOOST_GPU_ENABLED

#endif

#if defined __CUDACC__

#    define BOOST_MPL_CFG_GPU 1

#else

#    define BOOST_MPL_CFG_GPU 0

#endif

#endif // BOOST_MPL_AUX_CONFIG_GPU_HPP_INCLUDED

/* gpu.hpp
CxDuM9a+rjRVk+Riw0Lu1vZYa+F9WR509lP7OrIzduEiy9jHqwPNQjSCby4NNoWnDPTwtnOSx2VYGjsv5zD+/Sy1ZKGqVudoiTsW0Wb+sP091W4VN3L0D6AXVFPZIJG4fWXrvcVwBaENeE8LnV6U6ansu8vVFb4FWHSMuUulTkW3Z+Ce+wRdIIBbX2HDOiZc8u3yQXLZ6hoFC5vapjbjnHm3aG9SYJ43hvZ23MsmQylveyN3KYx+puKx4TBw4rZ6GD/R416XR3RGAcEUWSnyoPtY5tRhB62HFSduMgV/TZ9dPQ50VY7haWnh+CqHGr+rmaNSZLCzLf0W4/YgxwuTU8UrzlAG8HQhH7QPmCdRrChgehYBgEKn5QHV3YfWRmFXHewSiXdsioi+q97PT0yhFfVzkeSeB17INQFMGopZKH4LIuWQ5Q40suujF4jcg4TG4vCfM5kUg09t5y//4oAdzB22lNe/myUaWvuKT6En3KaNGQJyOOs6HCqzzavdEM3H2irnMLN4bfVN75iLH9oTUAI4HAq4/IBKoEEl0SmBanyoJBNqJ+aFfseFMQ==
*/