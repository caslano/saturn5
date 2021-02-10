/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAKE_MAP_07222005_1247)
#define FUSION_MAKE_MAP_07222005_1247

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/generation/detail/pp_make_map.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/support/pair.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...Key>
        struct make_map
        {
            template <typename ...T>
            struct apply
            {
                typedef map<
                    fusion::pair<
                        Key
                      , typename detail::as_fusion_element<T>::type
                    >...>
                type;
            };
        };
    }

    template <typename ...Key, typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<
        fusion::pair<
            Key
          , typename detail::as_fusion_element<T>::type
        >...>
    make_map(T const&... arg)
    {
        typedef map<
            fusion::pair<
                Key
              , typename detail::as_fusion_element<T>::type
            >...>
        result_type;

        return result_type(arg...);
    }
 }}

#endif
#endif

/* make_map.hpp
sL+l5AYZEjkMsVRjquhIyFy9iC7qS1pmYcPM2EBaz6lIKyBVQb7kcZPQ2PZ9e2UvLW9fJCK/ra+Wh6/rjco0lKx9ZLi9G0klkXZ1lMOyHE+7UD/k54wVkE4aQzptDOmsMaTXjSG9gfaBpgFmzXJISJdbh7k10+IJWCcsFv8Nh0TfSeGciHH42JUS2qkYLYy3cjhn7XBgt6Z0r8U4FaR7I0bbSqfm2zKrosud2/ZqWiXvlnFuaQ+pvthDxbkxhvO8m7xzSyupops0c6B2vFtlpB3vVhlpx7tVRtrxbpWRdrxbZaQC75atGt6jI1WdXLZ+iuH2JM1fzmlka7RElDLPmK3WVpKLupp5XQL3LTXzpkyUil41c1B4uVfdXoFcx6t+65QxR7RavjANVccXppHq+MI0Uh1fmEY6S/gd/Nl2qedtrTKrCbaoAe0Rupo57akM4CQDIGgaZTCnMQwvOl3NKnBzlguT4Umtfe2chl/ewhLXcFcfBPm3tLCscDVsMAuVaWM1kE4S9ozTdVHV71LcZqypZUr8I35iQw7vpMBOsu46DSkZKTKEFecPcq46cD2kXGJ/6YvSlWYZ/s32lyNiipyC1eRAJU2wHtJJY0injSFl3Xy8LC+y6VyVYC0nbToyz87OEj9rNvN2vK8U
*/