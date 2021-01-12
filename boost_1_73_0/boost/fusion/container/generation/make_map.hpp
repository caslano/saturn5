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
R2XlB0Y3/Lr+ign/ZcItgTWtwVLX9x9xHqqKY0xmvaGEGXvcPj74Ph1J+um7R2fu07s/TZ98ZemzwzUZxnK7L+rXDv5uOu5+FS1HSDlq2MHlmK6Hnk9BKiGTkQzsDrqnM3Nc7rgTSiv+TVvUQPZfjDP6UA7LtVIrlxjd2r1gvxEJEo/R9/OjXBvu2v4F+4uR7/Eis7a30r2OeShDkZVd275gv7Hit1jXyXIPxe+51PUY170m
*/