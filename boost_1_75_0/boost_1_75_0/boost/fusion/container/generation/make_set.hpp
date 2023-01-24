/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_MAKE_SET_11112014_2255
#define FUSION_MAKE_SET_11112014_2255

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/set.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_SET)
# include <boost/fusion/container/generation/detail/pp_make_set.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <utility>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct make_set
        {
            typedef set<
                typename detail::as_fusion_element<
                    typename remove_const<
                        typename remove_reference<T>::type
                    >::type
                >::type...
            > type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::make_set<T...>::type
    make_set(T&&... arg)
    {
        return typename result_of::make_set<T...>::type(std::forward<T>(arg)...);
    }
 }}


#endif
#endif


/* make_set.hpp
gk33fJFYZxUsfPb1yc9QdmW7pud/RdqS69ZDuTTvv2ZQXxCNeASmFOO9ZLSnbnJWlroeko2XZ/lxaV5bzFP8lJLvCfM24ih8M15bG3lj+TDxJDW0wOW9Yv1M30PaF+lwm/5vFh05fDoDzSKYttM1R2exWgW/Ff+4SbTD5ZvvJzmKt/0dims3BrIGCeq/lZXND5YeGpOaWP7yUC5UYLl8XTjCI6p4q+uVSdErmsPYJsckR+syNsy4chkb4g6omv5QXTxmcmn9H8Jzw7051W1EmlARp+nDaBh+2veqNGkn2VRPX8k3ci9Sl5pTuWl33UE4C/a4eMjqHLlPj2zYQocy9QVJKffKFRjk2WpFtaouuYiev8ih/11OYmjWsK29ofhalMUqKX+rJQf9zUmngV/Y/3rueLGyRqtHTGBMrse878oV2aYrMFuz843tvsTSLBoysPHsIfDMZ1pzhQDinQm9GcKktJ5/62lFP1cP779Xl/J4/BDjIQP0A5Quo0X7PtTP/vdLreUq0h/cmivqak74ZwLc+Vl42ECumbCgP4W0kdjy9+t2i3qF6qc3KPrtweF0i232PLDdIcNbOJJDkloVT09mWrskEQTJdcrQn8VDB/Ka6nIbP8siakn3Is101V/RQYONun1/ULBN9TdUwyARAIVRNwj/m7NnIj7zNEzoPoT3cEECdlhS9Kmy9FxcS8JLu1A3Xc0PdxbDO3o3
*/