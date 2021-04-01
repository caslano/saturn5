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
BUib2nLSgqzouh+05xdDOZxfMmPd7NvzbgNDqFiA9GQ13YvJ+n5jSZkBYrzDY7k6eRzP/n90m3gxGEaDC7blVqK4UrVveydxIMM3nREhZkwEcYWVCteW9uNfkon6nqoOTvJMnJTB6JCaMRG9KwU2EZMCFJ1Eea74f9D+4PaTYAv/xul/rKc37+5Lo7hrKgjvmgOI1Z1NxzoukcPT3AexvAHbvFCFXTq5wt5sH80XCjD+ULGiDBYL/PgOqozMjw+WWVlFfe3jop2VAlyunyYHhr7VpTdFzfFky7xGk7OSqjniUshHjJDJ0u5EwW9rSqsFN+1yqPfxaMB9xbQR8oQYih2J9BHft0cz8Wi6UzaAEd8fAs91ZcT0HOjZHwgUQUzTNMKiNBZNxo4uJ4MW9e4+0jGi5nSzpsjChjdLoY7Cd+QSgOM86NtwUBZK00iXWKfU4kxgo55ycq+XUEGbOQjkLwc3yEWIfAXAthZcCu3umn+w112Y1MP/TWfy3OnQ/9SJAbGxSoHZ+rUjlc9scr7ooPGGwUkI85Se/9uTbtW5mziSGQTm0ntP9KyF5w==
*/