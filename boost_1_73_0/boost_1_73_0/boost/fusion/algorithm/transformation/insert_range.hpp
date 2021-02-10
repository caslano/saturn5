/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INSERT_RANGE_009172005_1147)
#define FUSION_INSERT_RANGE_009172005_1147

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/mpl/convert_iterator.hpp>
#include <boost/fusion/view/joint_view/joint_view.hpp>
#include <boost/fusion/view/iterator_range/iterator_range.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Position, typename Range>
        struct insert_range
        {
            typedef typename convert_iterator<Position>::type pos_type;
            typedef typename result_of::begin<Sequence>::type first_type;
            typedef typename result_of::end<Sequence>::type last_type;

            typedef iterator_range<first_type, pos_type> left_type;
            typedef iterator_range<pos_type, last_type> right_type;
            typedef joint_view<left_type, Range> left_insert_type;
            typedef joint_view<left_insert_type, right_type> type;
        };
    }

    template <typename Sequence, typename Position, typename Range>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::insert_range<Sequence const, Position, Range const>::type
    insert_range(Sequence const& seq, Position const& pos, Range const& range)
    {
        typedef result_of::insert_range<Sequence const, Position, Range const> result_of;
        typedef typename result_of::left_type left_type;
        typedef typename result_of::right_type right_type;
        typedef typename result_of::left_insert_type left_insert_type;
        typedef typename result_of::type result;

        left_type left(fusion::begin(seq), convert_iterator<Position>::call(pos));
        right_type right(convert_iterator<Position>::call(pos), fusion::end(seq));
        left_insert_type left_insert(left, range);
        return result(left_insert, right);
    }
}}

#endif


/* insert_range.hpp
jHYScJUHgjiEvOgLIG/56Kzuo4TZeX2+nYCUvqjdGX0i3qCbwdrXOIOsl7hBytrvdJqDaVgxoE63639odvPr/BpnqDOfh7dEVtDQZZlTINQF3Mkh7+sGH0NlhdRK6k7bMRVmBv2vnZHNBbzGGbrAwuo0k5xBMnFszOiq9ZHOUZb/fc1MTwzz6Z2ojjNavN5nh3woH54ySTSyVRHT+euh/+e2YytfMwcML9yVVure0rAl0YMCuRV+pg6FktNhqnPeTejuRKJl4Ty2uzGNTzXPe9i/nBCbg5SEhrvcTgWSgTPuF6HohBK/MKKr8cWbjKt35v5q4kIE3bcUJVju1/r+4vPHYoa0VVEwfKS2TMgCNzEWg8R+VYapGf4fYwAJgIJ/HeYpQWYWH11KL4GA8y9MmfECovai6qqx9P/whCuG+bkNF3RrTpHelJ1HGeo9MdFIUqhj++KbrWBpb2yLkYR/3l2wXIYL5Vds79Lo49W4zdFc1tGCvptFckNgkzuiUDOmCzzR7nYHwuG1RbLUh2bO6JAu6xtQMeXEZdTVoCQc40yX4SExCT+2w/yHIIIeg5YvWr9KFBxcHfCGDW5ht9nhTBRbLqy47DR2C4g+7OawXM2l4UB04kgyWO5tqTnPYPmOlUCj/vbgqDCkzmh0
*/