// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/is_set_type_of.hpp
/// \brief Is set type of and is set type of relation metafunctions.

#ifndef BOOST_BIMAP_DETAIL_IS_SET_TYPE_OF_HPP
#define BOOST_BIMAP_DETAIL_IS_SET_TYPE_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/type_traits/is_base_of.hpp>
#include <boost/bimap/detail/concept_tags.hpp>

/** \struct boost::bimaps::detail::is_set_type_of

\brief Type trait to check if a class is a set_type_of specification

\code
template< class Type >
struct is_set_type_of : {true_|false_} {};
\endcode
                                                                        **/

/** \struct boost::bimaps::detail::is_set_type_of_relation

\brief Type trait to check if a class is a set_type_of_relation specification

\code
template< class Type >
struct is_set_type_of_relation : {true_|false_} {};
\endcode

                                                                               **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace detail {

template< class Type >
struct is_set_type_of :
    is_base_of< set_type_of_tag, Type > {};

template< class Type >
struct is_set_type_of_relation :
    is_base_of< set_type_of_relation_tag, Type > {};

} // namespace detail
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_DETAIL_IS_SET_TYPE_OF_HPP


/* is_set_type_of.hpp
3SHGyZXOtp7QbV+N/u1rs8I3Kj1fgl1kd9uXwqd6lPNvlL83YBv4W1suR+G6eTz3FD33VHg8PA2eYOx6bnieRHMuTZj84HOhIzm7HDgKDpEc2zB4htrhp+EkWAFnwgI4G54Nq+BoWAfPgevhGHgfPBfer3A74Fi4G46HP4YT4M/hRPh7eD58B14gHZWF8D04Cb4PL4IdSPNkmAOnwBPhxbAfvAQOhVPhcDgTjoCXwUmwBM6Fs+BKWApvgmXwZlgON8AKlVuho/kNeKHKPR2OUbk/qHJrgifCh+Ag+DA8BX4dFsBH4XjZJUep3/jMVSheW47yoHRF/lO6UN9TfbSTLtn3sX8GfgAnQCIy9ZQCp8A28LMwFZYo3Ntwo6PfvuBuPTcTrsVob2xDPvw+PAe+AM+DL8KJ8IdqB7ula/VlOB3+SO3hFTgX/hhWSpflIumyXAJ/LnmzPXA1fB3eCPfacotb/fuhE/R+dIbpsIstN7bV/73cpPfjdr2Xd8Ausuu5DAL+72UX9X85sA3sCl15L4Vr7/HcfUrvm3qf/wDN7zCrHeQp/CyPdnCi3uP+6s8GQIwzUHKtGKNjdrDa2RA4Bp4snbgfhxfBT8CpcKgtx6rnDvTI7/0qrwdgX/hlu37u8R8fM1VOWRofs61xYq/CneUxTtyo592sfK2HJ8EvwqHwVni67DvahM5v7nZ1+xbrQ1yVUCfif08fYrez4nQiHlNdiLE6EP31H7ZM9+EhGKP/0E/34THXe/ih13d4jHQdjuS9KsRUY1ZhtmGewezFpCJt2g9TgJmGqcNswDRhXsAcwGRe094ZghmLKcUsxWy8JikXmbySV/JKXskreSWv5JW8klfySl4fpuuYyP8jhXQ05P9zkP/fkO+Yg1XaOMRbRRqwBuX+qyy9gHmBGNkbybg23Blew72Q9E+ezPxns2vI9vr20BTJU1uyM6uJd50bb5TOE88zXscH5F/y0kN8ZM/kx1PuoTDi3uz6sdbs484lHQmHRMuPSX4mVgZqVNY95lnMFedHdNTYgjRf1BpGg8qjyas8UFdRWlpW6viXi8L1dc++fdnYq0hvWqKyUrj+vvJ/PzTuY5hj7qjyUxjrjOWhd8WesUx69YwsmGHcu8oe9p9u+a+53LH8v2rib+Pq0PqpsS9gfjug9f/WyaUdSf29HKk/Y++ldc3lPaLbd2NqTPuW7EO1u6/D1q/iK1+E/9a1zdj0rlD6dudHn5X7XppkF3Xu3K1wdT7+Npn0WY3Nt43Jb3f3zOI3jX1l4DNOm0RtTOHyTbip2N8x9iWBkbQBv3a33/i5zsgtq90pnp4mzLd64llnuIblkc663bTlQNTZqoqzK/y7CV8f+KTORn7SxDG/akFd5Izlg64f+6xmI9bkymEWm+d84OS4z5ldXjZ7HqIttQgk4o8qauDu+yauRYERtNkMtdmZmJVUwBrMCsxJJGwenEl7el7uV2Nfhgm2gYJm5J7H3xFztrJHe6/3ae8NMe0nV/fIAvdi8kTbCoSe5byUH30Gb0Z7JQpzvNYxbsTPXuO/obTcViHmL7sk/wOJeYx5FyW7GiUjlG7exy5qW5Ew+FX7K1F7kZv6qcnYPzD2XpbfasnAyq/6qIuw/83Y+1t+51Nm52ZdGDrPS/4DJq0MyWqT1vnS8js0xi8ZVtszcRbh2/U7MsZvtbWn4KGcluuBi93vIjlbVwaq0G0PJcY+LdI+jL3YtZNn7MGIyBt25U3t7Elzz+Qhqq/ZqvaQp76wh/rCwjvVHqSazF/OUn4tGbtv5jQv7xXfJ0ruT+ka0iFGv5PSVaB06ahwvzThr3V6m2LSofKRkAbXr4hzoKHGio0mHfZA4Zc=
*/