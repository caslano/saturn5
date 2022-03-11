/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INSERT_07222005_0730)
#define FUSION_INSERT_07222005_0730

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/iterator/mpl/convert_iterator.hpp>
#include <boost/fusion/view/joint_view/joint_view.hpp>
#include <boost/fusion/view/single_view/single_view.hpp>
#include <boost/fusion/view/iterator_range/iterator_range.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Position, typename T>
        struct insert
        {
            typedef typename detail::as_fusion_element<T>::type element_type;
            typedef typename convert_iterator<Position>::type pos_type;
            typedef typename result_of::begin<Sequence>::type first_type;
            typedef typename result_of::end<Sequence>::type last_type;

            typedef iterator_range<first_type, pos_type> left_type;
            typedef iterator_range<pos_type, last_type> right_type;
            typedef fusion::single_view<element_type> single_view;
            typedef joint_view<left_type, single_view const> left_insert_type;
            typedef joint_view<left_insert_type, right_type> type;
        };
    }

    template <typename Sequence, typename Position, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::insert<Sequence const, Position, T>
        >::type
    insert(Sequence const& seq, Position const& pos, T const& x)
    {
        typedef result_of::insert<
            Sequence const, Position, T>
        result_of;
        typedef typename result_of::left_type left_type;
        typedef typename result_of::right_type right_type;
        typedef typename result_of::single_view single_view;
        typedef typename result_of::left_insert_type left_insert_type;
        typedef typename result_of::type result;

        left_type left(fusion::begin(seq), convert_iterator<Position>::call(pos));
        right_type right(convert_iterator<Position>::call(pos), fusion::end(seq));
        single_view insert(x);
        left_insert_type left_insert(left, insert);
        return result(left_insert, right);
    }
}}

#endif


/* insert.hpp
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
*/