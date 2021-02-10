/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ERASE_KEY_10022005_1851)
#define FUSION_ERASE_KEY_10022005_1851

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/find.hpp>
#include <boost/fusion/algorithm/transformation/erase.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Key>
        struct erase_key
          : erase<Sequence, typename find<Sequence, Key>::type>
        {};
    }

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::erase_key<Sequence const, Key>::type
    erase_key(Sequence const& seq)
    {
        return erase(seq, find<Key>(seq));
    }
}}

#endif


/* erase_key.hpp
qjAD0dbn1rLrsFckVpOQUx3ngkcZq4rATPOxcL7xh0NiFvnGYU1vYtMGQXpxncNIn9w8gPYF+/325Pxbam4uG1mzCyLyDebPnt+ir7yGE8Xyq/Jr1qqMJ6qoM2bP+FTvoLfcrJZxEgIvM5hO74PZbMX4ybJ6cB/NH7V+I0UA+ZvtgtN4/j4v4gMGm+DBzsnvQrwYBP01Ee9iJY16rw/qbw6O2JwbraumI9eBaPMfvc0t7igYEonLvtnMNeG3Q1uqoM3luoFEkHfwMiuB/4iGQW9qZg9eqO2Nl+FCPfulHXbtTvUXzn3bw3/DJMnROT3K6ZzAPjHMHI6B2JaSr07fp6NZs4cFgfOwn1qWvGRDRCdJsD2G4OA7pa5tXbZr6rtpfH/P9xZhCglCKhwpvVszn4PZHPqjcXM4rsnnN2I6pi8ggQXmtgtm2S81kUsH7KB1UUy3bPm0adQkAA1qGSixNWurR7RVIwWpYNJcGKFcT0JE5VUOQmbUZWOe3s9yiMrz0DSIGqzn1sYDurd3R2s+f44Bgz3t77elO/jJYFjBaN3uwLf6sj/8JhoOXEVt/2Kk4lfYH0p7JuqghFcS68vXChEFibi+Zxtfjd3latrkV8PazjZL8RUTKTKGzQ5XKryB5o8HnnehfVyUpjNJ
*/