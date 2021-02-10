/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_VALUE_OF_PRIOR_IMPL_SEP_24_2009_0158PM)
#define BOOST_FUSION_VALUE_OF_PRIOR_IMPL_SEP_24_2009_0158PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/container/vector.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<nview_iterator_tag>
        {
            template <typename Iterator>
            struct apply 
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef typename result_of::deref<first_type>::type index;
                typedef typename result_of::at<
                    typename sequence_type::sequence_type, index>::type type;
            };
        };
    }

}}

#endif

/* value_of_impl.hpp
5/biI/WdrBHLplY7N5Dvvm97bHO/v1Q6KAm4MM+f5xnIt5Uw8HWvf62NB/xoOntPOi0dgBVJpST4wrTl8jv4xCWvYH8gtgaCy/ElCNwmJ6TY9uvph3b7gnz7rZvlkEonxrgfugmj+QElq1WKOb6E+GelPa3nWUodHu3aFzlShUvJm2vJtReUv05tKV43P1Ftmb9Vp5yaP+/2i4Me/w1A9uV7nsguL+GfXnep0hTvml9uFVVGut2uWPq9zYM3sSN+S3DrYmLqUBU1eqa//B1EdkDFzz4yQ5oybpFdxbZmhqG/qhvvqcrERRv5Tmpb6+Lw4Jn4zVtmj9T9HKE3XgS0bPx5r3QvaJc/UNpE+9uJdtMzrgGogX3FbYUBpMnxXzmVZXV+d1YYSF5TwBhYCrY5hUojA8Fzv6gRPpAuOPdbHmEawiKyk2qTG149ywqmzCQrmDCjokTypmuFRPxy7bZEYlKtRAKEZmXaGGdWKmXARbnS46YKyeRJ17ZsamKtdPrVlToXzHlFbiMzrlOUTrzIqxCNv0DcFozPqS+7NsCu4F9ZucrcsSifgsIVErIUG+ZFlNPqhcyE3KJ/b6lvEwq2JFSxvkpEkW1KZJQT68J32vpZhgVEJyCVCAeFwPH54L9QSwMECgAAAAgALWdK
*/