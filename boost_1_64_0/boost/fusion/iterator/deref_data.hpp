/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_DEREF_DATA_HPP
#define BOOST_FUSION_ITERATOR_DEREF_DATA_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_facade_tag;

    namespace extension
    {
        template <typename>
        struct deref_data_impl;

        template <>
        struct deref_data_impl<iterator_facade_tag>
        {
            template <typename It>
            struct apply
              : It::template deref_data<It>
            {};
       };
    }

    namespace result_of
    {
        template <typename It>
        struct deref_data
          : extension::deref_data_impl<typename traits::tag_of<It>::type>::
                template apply<It>
        {};
    }

    template <typename It>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::deref_data<It>::type
    deref_data(It const& it)
    {
        return result_of::deref_data<It>::call(it);
    }
}}

#endif

/* deref_data.hpp
caYXsoeU/TI4XfWZFeWJ8lhZZ+2HXj//dKFg4UYh/0ey137HJ48IBTvK/Bd8D61sMCY61j47HDOpnCdoKtftC1VmRuq3yl9qV7wtQo6TgwvZP/JCwYjURy4UbHFIiykLNXv2UKBD5KPiJk2JLpGPOUeGGiNSH9cWRzSZsVC37wkl+sQ/IRYy1Jkw/0ljoECXyKe0zR5F+iQbFwo2OaZF+NP2VeGAOmMWPyNGyvSJfdb+KxxQZkCyqR2OaDBh7nMXCs4hT4fw5+WVXUr0iH5Bf+xTpkfsVPtkqDNm/otyxwkdQl/SFruc0CXyZW1xQJUhiZa4yHNK6CvaJs1i198nL9sHwfGU/cecN1j4qpxRdlxRVr53/mCkXPyae6gw4eZteaT1fvWUE+a/7l4KdIh9w5xwSIvgm+4jTZUZix3tUGbEwrfEQYPQty8ULJFm3zf+ZeWIhe8YNxWmLHb1ywk94t81Zg4Jv97P6srI94ybLA1mFK/g8+3f1zZ1Zty8J3/UmbH8A/dwSvSHHpOhwZTcec5r30AxUqRDqG8eyFAj9GPtkqVB6Cdi4YBTWgVfF34qVxyy9x5jIf4m15UryrHypGA+32uuPe69xXnH4bfKhTJPgwnJ97nu/LrygLK6RWWHtaJYXZs5jjo/V5ErVh1nlFWGxN6vjTdr/4HG7Lj/ADlWHtFgSPwDYmCPE04Zk/igmMjTZES8qg/2ab1TvTe6zziKhAr6YI8WIf0uskuRfbEti7lETPwHlOmReJvXBk7oEHu7cZOhQ+od2qVIl1BJ7AuhIHH38wTpjHZL8kGZLiGxdV7ivpe6j5VLnM//c+QzPo4HxF7mHMet8wb7yhJDVmyQlzryHKVK6OXmnDwDkq9wjQpTll9prukzf+waJ7QJvcq97FJlxvKrrR9Onx8KWsrgNZ4b7FBhQirvMSWmzL9W7g7dw/qLPC/ZWTxPcETH8Yy5Fxt3PxRkrnyeYMNxVdl4odieZ+0Sfr42su59rjkh/Wxx0mRK6cM+C/Ys5zKu2W9k4HiV3jM9fprznBL4mlZ7xnns029szO5/3qD6zpA9/83hC84brJB5irGwkpZ7CrQJniROtqg+Xr6JP8G6JUfwRNce55j408/js+Zi9TVt53p+n/8Ya4rkY41zPuTvI+T80WdzZg3sygdVZqyoN9hx7yOdJ0/54ebjYZ4rDxXnljmhyICls+cEJyw9UJ5Ovcd3Qe+/OI53jU85eKtxM3ScepD7qd/PfN3OmG5vDBzSYML8HXzN4JhTwqvmnjRl+sTvaD7J0WTK/J3EwgldYndWhyzbK+Io+xq+ed6gsCynBLf2OnrmVnJH8Zb6X5Knm3iNYJ8ibWbM3VRMDIjdTK7Yo3Ejz2/iN9Y/i46b9z1vkLyh80+z1q6vDhOSN3DtSecJ1pWdr3q/7Wvn9rODdufdfw39kqXGmLlrygUn9LM+x6osX027V1X/is5vm2NljVDS/pIcsHw5+WLl2n7nqGwxZTXh3KWtsZeGgn3l/E3OE1SUQdy9lJiRuoxYOLqOvydSntCkGDMOli8p/ovrI2qNkr6Ia5Qi4mbzQvo7n9yeX05oEg2be+rMWLmAeadF5IL6I8cpuT/b94QRib/Yw4UsdUYkpvY0IUudMcm/qkeWCgMSf1OPA8r0SfzdOQ4oMyA+c44DKvSJ/sMeMWSo0Cf+T+dIU2LM4r/sZUKBDonA+Cmw/jx7LSmj5/KcJ02VKYvnNlc0aX/PZ8SVi+dRhxoTlkIeU2FM6rzWAwV6JOV4m8rYXjYj++z8yj5BVLrGxdz37UdEif2evYzY+oGSvR+6h3N+ZAz9C9rH1/hps/4T4yX/U+0NjJO9n13QZzQ=
*/