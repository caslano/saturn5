/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_TIE_07222005_1247)
#define FUSION_MAP_TIE_07222005_1247

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/generation/detail/pp_map_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/pair.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...Key>
        struct map_tie
        {
            template <typename ...T>
            struct apply
            {
                typedef map<fusion::pair<Key, T&>...> type;
            };
        };
    }

    template <typename ...Key, typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair<Key, T&>...>
    map_tie(T&... arg)
    {
        typedef map<fusion::pair<Key, T&>...> result_type;
        return result_type(arg...);
    }
 }}

#endif
#endif

/* map_tie.hpp
/0bZNrP+y4348WEs3BjXztBrcH2D6I7ol+rG+JWObo7Atfnx/t9cBYolU9QjKchWn8uqlg0SqIrS469+0lC8Y6Lry78dUoi0XMwjjucT9rTg5rFHG2ZlGzYQOe5oqcgbw2OueP4PqG+lB5YhFBhv/FhlOpy/nm25MKZkbh7HeazaEB2yon+mC+Myzqx+Oyk7Wsq7DlQXt9S97RSQWAU0cAVZFra2dhDxdFzEun3Dk/o1dJqYB/ksk6sXq3xdxRVfw6gxjL7qil/JVqrKFo2qmMbCg65W9njxIJ1pWDc3wFbBaU3ZjR+4BvdEt9KRqO9SDSL/Nvcr7GSgGwAmcnMnkQyKwAg7EvfoD/o5XXzBLfAGxbYAQTNshytV6ouENmDegoEICB1N8y6mBYk1QUvaoRA4xFxopQLsezYJc2m8XCEjH07Q8aF9nRcNzKVFn6aydCDSufnFhOamfmmyBOqZn5yG8W+9yGOOlT8WT7f6+0/6ELShEDJw1jhKevyu074JxNG/VZheiLAKwyWRiHXUw3Ct8bL3wskKxgEVbo/ioIHGcF8o3R+iYyrjIw==
*/