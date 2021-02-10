/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename result_of::value_of<It>::type::second_type data;

            typedef typename
                mpl::if_<
                    is_const<typename It::seq_type>
                  , typename detail::cref_result<data>::type
                  , typename detail::ref_result<data>::type
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return fusion::deref(it).second;
            }
        };
    };
}}}

#endif

/* deref_data_impl.hpp
7SiulZPXTUoJkKKnCD9qbH8k/r6DrH2fxPLEQNekhKlkCI/U6J2caMH8bDqEwCDtQA7FoLDgkhSjMM4YEQxVo2HM3VCcTAlQLXaKiaEJ634bkYDcUq1IkAR35PptOZOtX3rd/d802ZDpg4A8Xoe5w7s6JPv5tZNcjEmYnyCnYyY4jHlyCoJIK01JPAZrUIosiggGDh0+CjlXZkFkJWM/cTlUVNPJ1G+mWrFcEdZ3eqxUrh+x8TOzJ1NWqVji27PSdrck1ku44vUfeVkYpjaKZhMu0RZkU6xTIxS0IPEYNTLQ04T/NYXy/k3sluziY/d071Mxz0Ony0wP+Ez8Uatd/HiJlV9eb22VeQslGQ0bbOL64spCHHW2yUaWldCpljuYETEYAwk9qCXCmS+0K6qQYvrwKMSNTRehZnNi3TftYObHMAZ808ZsNqmUWWwB51G6MmYUIxgAvTxuEeC0wdtiGHUuy8wINorYbLN2g7oC+7Yuy3mo81E3TtP9LBuHYo7FfTxvHqVvYFwpfesdpsGZf5FK2zIbOWBULzT/EDyJueWYEtMp18Hhc3sYe/riDqh4DsPNuZH8hR5QZwo1YJSwYoqQhAZLpIQfpRd6lZqZpTc+1aTqrHT/YiNJJpIk18oKBlKx6FZW0YzeUxXb
*/