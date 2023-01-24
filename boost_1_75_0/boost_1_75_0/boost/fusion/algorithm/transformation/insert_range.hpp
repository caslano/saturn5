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
Cm7xHC6/wlkz+Dn9bAR+ePZZzg/rgqQ0oB8+w9hsmH0PGRVwDSbPeiXbHex/F9H+lw5ZbxDdZyyio4Uu91wkbElKpvmB52KFLSkhU/oGDEmQjNFa3AHSULAtBpN0xzGoNuIWYyK3D0oBWBKOfbmWXZuz77WTcoLYk6CwOORYtzqaK4YS6A8uU+VWspEkwOusuVvkJacalqqnJL8DPaZ2y88vxJnLa93FWWbawSm2hoJcCzuTdfUgWFcPY84X1boa3EaxroJBdTTWrkzcx/iwqWkRYBXYcRHgkR2Q5ziKquhsAR3Ir6uIxOvgHq9HG8rmoyTgsDD+HRz5Aey8i0jw2WR1DCpg/+1Wx3yYWdstVETHMX8PHag603yyFcynTc98SpA+n6ozzQcZtmw+sGDHfPjMW/S1fRSHG2vxcipUKWruhGpaQnUtBk2LQdcilETQAr/VlhpNS42uZY+mZY+mxdk/V/7p3HkmeUqAupnPxhtsEdss8Wzler4QqFytCanEKecy4tt3ViE+Jt0eZvt6Gyh+bfextm1PkmUZVRLdcGmM2hffHCy8rX8BG4j5ll+a8djNnk9FknHOZX7SJkoyy5k5aKR9qYavaQlydSkmgJXENhvyLMJaWokvVnyPwVR6wUAbYNgNXr4cwxUg8rK688jxMZsmGytJHv0je18AGCzn08r5HkI8gEHWCkQrqSWK6TmKnZIbC7HgkBX8
*/