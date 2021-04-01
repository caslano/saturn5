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
gs+kvVqoYPm4L710Xz7t+z3GJBDWLoX7NBSFWT95RTqb5w3edgyx1uo0vYmsa8kFpL3uQQTOFjkXIe0dAPzGDd2mZKMDGcz01NGy3kOXE+YTsKFRATk7/ufebTYue86OGjTW42WvAyYyLMoT8izUASVHn3Atf1LXYo6pyd2hz9oGquFonwemAdW51fOryjanLxq0GltF6HZ3iTG/Nm9x1VxAmI9NpFPvMeZnyf3XFgENogZEG7mBE/pZZvVWhWFSPB2j+kokCmh5WLNP5vvYBEeaF9xI/SGAc3mgN5qAuDuRCGdWEn6fmrWLkajaSmiAjDMM1DN8ZAiWKRnVgUVg3//H5CHKcwsxABKxUVvLa5q43/y3YCEFOXB9pnIc5dOS3B3BDvmNqTh+Rf2KYal/WwSOeeUMxnLzevZ+sJnIL5oezBcn7KdHWFTC+uq5QyoVv2XHHqAXLfKIQU/vjYp/SUEl72tpgyJz3dMICas1rjHrhQ2kkHewFbWHhd90o4DiHUoi/QlvRRNfsUSm0CsfUhb2lOMkhi/TE9WXYV3NetlUc79/8sEjJaj0CQ==
*/