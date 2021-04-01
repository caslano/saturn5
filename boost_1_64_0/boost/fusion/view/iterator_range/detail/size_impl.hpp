/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_ITERATOR_RANGE_SIZE_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_SIZE_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl;

        template <>
        struct size_impl<iterator_range_tag>
        {
            template <typename Seq>
            struct apply
              : result_of::distance<
                    typename Seq::begin_type,
                    typename Seq::end_type
                >
            {};
        };
    }
}}

#endif


/* size_impl.hpp
IJWrNQZLp8/Mwxv3fXcP7rKisExPdYnbdzVA7FjVp1PrBj4Iy2RWaJkR8s6HLZ9vCt1i+soB5taF4waqJlM4u4fS3lwZ3VIe8N+MeCJzDP4kI166nvVXOrZUpJWubZZw/R3YYiWIbrTAsTHMr8r0IIdIBsEaQHCTX4MlwASQ7vIPmDk2h9W7KyiVnLud5Z6ToHWUSuHAk3ASqVxJkEKSLOg00D3o6ZUcu5yj+rYQRWrGjnmQFUqfzuFeLgcwJzEXi7kq1hoT3CmqJBHO2v2Xlqw9qZfYG4Ogr1afKWdIriMJqMeMyEO99NKWHHe67YU54oCIv4pQHHCv25dqFHCp3s+3jTM4q3Y2JOAP0NabyJLYTlcmKtF0zsfnvzBrtE3fLc4aLq7mE4U9v99pQxnDwAAyGgz8AVhTcJn5fzvdP4Fl9WAGqMuB9I5Dv2Toz9vRpWA8JFWCOyimZH2L5INtpr40tnSZBQMXUXROd6zXtqxDjhzI0y5FmZI3//ggMiwA3rajr9FesRoO/JtWtZuWTJvv4G7J6sbrAd9JBEviG6VZBLu87PZ2OnOYLg==
*/