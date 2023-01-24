/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<filter_view_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::deref_data<typename It::first_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return fusion::deref_data(it.first);
            }
        };
    };
}}}

#endif

/* deref_data_impl.hpp
rkmlhntEG+M5kHpomfxWVQbtnqkyyUTjbCX9g5G6gWlN7sGlDrawNVv2mXXSu7oF2ScZAa3sFFJ/2jrHoSIKtw1Ics6XbiDObxiSqHl8tcykM8vC+YFztN2nsGOcho/K1FNOq7IsNZrVS16sI5TKO2FUkxc41hgJZw3Yk+bAGpxoYZFB4zsj7CemOjLFp4Ty/sqJnYi4Si1nN5BdF4LTudKWQE0+bmeiYbs+iDF/psOr84/0eJJ5krZflB3uHdnBrekIeu1zeN47YKj6NiW7Cy645JwdFoZ6BSScpOqT3bf3zstobUhYmFyKnDQzaEBXTA32fEKRx6YbbzT9arui611MTD5p5bLdEsS2xAACY0bCJaaZ19t/c7ZgH+WnhZ1ka8S3MZy/1JD/Miwu1dVWHMMb7MDL1z57/agA4Kd+HPxwNoUiCjwRYltHIP7tvzA1AcIUmJPGdvAWloeHsKXMMmIyf5DV+UtgdjWSg4UerQiF3FtN8A+hOTe2CasyllgN5xrWOdNV/FRodGzw8JmTw+Jbamek3C64NLpUpR1/dMxFufJMiNDvRuJZ1gY7Bfz8LZKuS5OWt2U8tb9aqYeAdCXamnZAhA2LPn3CkoH6OncxKHwtEJzkxbUy5p7uyA94576lf69mQd5FyzkwQge0ga7le6nvNfCabJRAa4MhP7cIbd1TItF/J3XRrmTsVsUG8BD/pDowjYAk/0Z1
*/