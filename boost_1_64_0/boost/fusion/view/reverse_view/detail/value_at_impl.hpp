/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_VALUE_AT_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_VALUE_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_at_impl;

    template <>
    struct value_at_impl<reverse_view_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : result_of::value_at<
                typename Seq::seq_type
              , mpl::minus<typename Seq::size, mpl::int_<1>, N>
            >
        {};
    };
}}}

#endif

/* value_at_impl.hpp
8SEPiObXRroO5tqJVXH9fy2gCi5AQLGFSyAiUGhsXCnhnoqX9BdYAUM//VZKLeEykKscce01BmYf1ZvuNOLlDnTEV1nyhe1D4fQoKqfcMoqr8YBxz0ttFU/osUljSSfrjZcpEQpyOQ9e7H2Dq3VZqdDiOWTUls8M9+PrmqMkrSxMafrpY7aL9fFwZg8ZCRAINnpAa744qp8J35CXT/Ray0HeVrQCV6/OTOR8pXDRFn0khDsMKWER2u18OiA9NOWwDwPv529/UHRQeovIMtmkbta3YjvL8OkDOqeVcyKCoArxuGEeKPVqiUwsvUhftlUjoKVgZ4XJr6n96A7rEOrG9utMKtIGr6bkNQFqi6F+poxu9zh51hsJDfY2YWsObxrZFUDSXKEybRmZ4P1+6fjAvEmtwuYUkaoDmi0/NcpU0RtpO/i6AVUdew+TQZp9kWBDhDicc3+8I+jLD+9zh8bxsGs2luGzBp4Ny1oMr7WmGFKdSC9K6fnTEh0c/iFSZOfQSATU7pGvzIw+PHer3PUZYUESSoANYjAqbv12kJDCWX+VFj69Igl72oUnGg==
*/