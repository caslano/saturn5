/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_ITERATOR_RANGE_AT_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_AT_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<iterator_range_tag>
        {
            template <typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::begin_type begin_type;
                typedef typename result_of::advance<begin_type,N>::type pos;
                typedef typename result_of::deref<pos>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Seq& s)
                {
                    return * fusion::advance<N>(s.first);
                }
            };
        };
    }
}}

#endif


/* at_impl.hpp
uq1HvONY6D/xMf/75gXVg+2FRw0sjpdS03MryqVXMO7yF+Uj7v+VlwkDF9gCYc8lRWCZDDhnKZZzHxplcrC6GaWchZ9xWpLaGNZycgXUJepPjQ/BQVnOIEREz6rPIyrx0W3i+ELfYsZJdgrqK/57rsSkCS4/R06SFt2FkEF5ab/MjK9c2+5pq8ZQuLyczBuPqKVqIseBGpm10B+jykUuuI/mAwCsfg8Ieoxo8SKqUCak7/5nFPWoeJ8LKn9WzETBhQXCihMqpmwPdofUWf/OfG+WHJH2/muwaDTzq90Nc9eJOiaw+sQLbAiyoDOLaK+6paihiCJk39XOCMZrWcUnc5kyhE1rqEdNhZjRXrwclSqlHOwhKlHlxTbx1x5B8NAbORI6qre7B1bFU8kRqBh9BOwUmeoHHpmBP3jlnwwO3BL28gO0JbxQDkOkLcmGfShb0nAGpCHCCiESdyVqtpQzsGBgtQCJ7ZZCvllXtbPgLD0uEXwj/ShHKN/QnmmIAKpxn3E2Vg1ZBPyLmeZHPCABVKng7I31kZKsinjYD7Wg0Y3zujYueBoKNG4k2Q==
*/