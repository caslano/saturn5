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
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
*/