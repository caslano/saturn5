/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined (BOOST_FUSION_PAIR_TIE_20060812_2058)
#define BOOST_FUSION_PAIR_TIE_20060812_2058

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion {

    template<typename Key, typename T>
    struct pair;

    namespace result_of
    {
        template<typename Key, typename T>
        struct pair_tie
        {
            typedef fusion::pair<Key, T&> type;
        };
    }

    template<typename Key, typename T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename disable_if<is_const<T>, typename result_of::pair_tie<Key, T>::type>::type
    pair_tie(T& t)
    {
        return typename result_of::pair_tie<Key, T>::type(t);
    }

    template<typename Key, typename T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::pair_tie<Key, T const>::type
    pair_tie(T const& t)
    {
        return typename result_of::pair_tie<Key, T const>::type(t);
    }
}}

#endif

/* pair_tie.hpp
Teci54lHWyERJNFL0W4nciCSxPGIsYWMHecPTCMeA7NFp7aCJ1x6qt+OXBynKJwfO/SSjnx/g9gKKXQdqBH35EwrkPP4jflLv8WlMCul2aHbYI8/Zu8O78h4/3a6dZorq6IGbXA++bziuOzi1pUUP+d2i+R7bz7Mu9XbQffMTnLJeTZvby5XrnF0hmYclbytDWVjEaS+XHj+chrn8rTLA0aeqlrtfFvQSenTi2q22KWzwa/k92NxG0+Yym+Nd/XQdHE93zUXnKDuqzg4if5q0fv+h1zTzWd0WnLF9b7yPWK1Ds9XG144Ps24FcvYckZpRs4dxT7T/XqVxkpsP10yMruxwax5QdVrr+91zwz0niw9XDT59aJu4YHjB9u4iIEljg3KccvorwN8mamgF1NTXnL+7LUQlnr4NUGBJOYS7yd049IDUZWdHBfbY9yoT4cb731/ciU406fxDHOUxv4RG6DffUPidL/sT+31bXbW00Muj8stdGeO47fnbu1MSje41fXLa0ygQ9K7YtGlQdmGDkJv928Jnolw3dktrOIKFOioZHvZcHIl81PU6xpPg47OQaJOdpZ02D0Tlzjvr3YRX78PIOB0aYAkP6/+0FUAqGrNUketMTfOc2GGDForgjXK19YOcvpA9wcSm2e1M5Itf0u62yJcvzw2efwIR4/1kyz5J20yJgmd8W1dMFZ9SzpuaO4XIlaSFEJJYvqo
*/