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
oyXi2Cn1qEZDoaTxBWkdP/5zQunMKzedeEInxr1kOL5iZ8+0n7KcMGfS7si5uN7jChl86qS7FKI348ubP145GBKyrHC8xBLjDgGcoI0oCjKdEtMAd4PCdS7JDh/ptv/OiprGp+Ak+N7qFAcYj+AuPM6tOOKtSBAFN8cFv8HZ/RDlYXA5RrNQkw83yTKq0olvVm6GpsEZb4PMmhWATyNoMt0N3Y2Fx25Qwv6cIY+0JKulq2Bb5IUOTsH4XybKlPVj1bEVa951yjAmGCPqFl64IQE42rnWkTVNxzjQvh8w78Ti/2J3fSXorIUEzzL0fg4zDi7CfwKMX2LobZiwpYf9OuPO+DqQuuWdx5XGMK8NvARXIX5movJsz5IUwf8AUEsDBAoAAAAIAC1nSlIjbCa2KgcAADMTAAAbAAkAY3VybC1tYXN0ZXIvbGliL2hvc3RjaGVjay5jVVQFAAG2SCRgtVdtc9NGEP7uX7GYGYhdRSaUZtoEaF1jGk9TJ4NNGaZ0NLJ0sq7IOld3wkmB/95nT++JafqhNTi273affXt27zQa/nevHg3pzpdn3x5e+LQal5n6QwRmv7TnfaLiH7Te4fMuIyNqVD55A7pb5RMdWBWvtPKUv3veXYbesW/8Z8Sa7zz+ihWoseZEba8z
*/