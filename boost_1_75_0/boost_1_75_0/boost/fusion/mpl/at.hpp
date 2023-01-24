/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AT_10022005_1616)
#define FUSION_AT_10022005_1616

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { 
namespace fusion
{
    struct fusion_sequence_tag;
}

namespace mpl
{
    template <typename Tag>
    struct at_impl;

    template <>
    struct at_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename N>
        struct apply : fusion::result_of::value_at<Sequence, N> {};
    };
}}

#endif


/* at.hpp
0C4LiG2hWkv0M7fji5VzfZGV2XlKCxSSIq5mLLO8e1lYomNRdAjHUGdMuY5Se3kXvueFXVA9iYpvUjxa2zGRkRw6bQ6+5c79wvoRULjlU865J0WKzIa3SvU/u3AbNcavq7XnmguC29voVe9HHcgxj3LUJXkukEoXgdZ9C8+j8IpKKZdyPvQ98OTqQ9Lj7+Nv6Y1BXq2+6jjjp8C9yCRNcm9XDlRerFzah9TjzxE5w4MXt2AkACKWpCFM4xF8fEOuG07nUANcdkvuxg312c3jmoM+EIe1QDcPtODxf1K5PlAGQyKynZWfT5Rq6svqmlNgqTilN96FQZHe2F5W90kKDg8IvIvxaTi5aC7JfTA6FB8bWPnZEHryjb1YEB7baRRWDsraLhcMlaNNeuxKIIPbcXRVsqf60Jpk6E/Qhs9n4LU078LtZZ7wOCcUxuWR5cJDFJmSA6iDwIyUQGxq58dQsCB6DHVCSh1a98lNL9ozEadBzbYKW7GyA23KZNG5hRl0iy+yOMerh2uon34Gh2Pg33k+ZZ8IikVudlgWtmzNthI4ObBpqFiu012rULPvi+HecRRyAdYaWYTaUqp63WdodF1E1nGRS4GrxlqvTKy1gOs0fNfz8BTJVo7k+58h1ZMcuTWNfWDQYR0VRpQVT93xL7QXwf9OuO3MLGtwZpnNhEp7R1an8sVY/ukfK4+Nm6fvtu9cJqfnGHJ6jpDT
*/