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
zieM613qymSsnFDDOnfQR+u/67D9XmO43DMh+5tZRC36D/cKxcso9VuGaz2ynqUtSzJtOXXLbn68anbvhLY9s7+S96nLrVWyrwmzlpO0hj5v8Ai1YJGyXFNluTKNy8XKK8v9ebJPNF22XiXfE2JT3x1GqjN9UL7Xb4CTmYGHi/ouTu0sJ9JS6jWN4v32ybp3ztWitd/DpWy6848wpzKdz9iek8/Q2tCk4vkkSnvWzzvctv59ZJD5x+X66Xy5flpQSd45ar0ZLbbMx2bK9ZsXqljTeupu5JF2VNI1OHlm9M76kPvdbL6viik+5vVi/TSg7FPI6LvK5KetY5vvNbTrqqNkmrpyXdXJtZl2XKc/V3cdpS7MGbmm9zkxhZkWqdPrHuhWT5fudj9s+A5KllN/P0Oi+TvKDffKKcvS+j4Zi9Z4jViW5QtZlhOEh9JnVDUuSyJb190th/R3dsdSbYzHrrZlNy6bTbl9R6uZ1pDngqoTNSi3RzVruXkDJBeIuI0nvJzPJur7K3mmTJYlyqYN7Blt//67R3pRrmrF71cbPHx80NTAMcNHB5X3XZEhuveq6fP0YUdofKdbKNNazPJUXuZWjncghpThXW7F5cgeY7/sNbrzuVaOof6j/ccNDJg6euAof2Xpy16OB+qZv8vWJ9B+2d3Js9A8T2Xpy/W+vwfqlb78xWXZE2j+rlAPt//Mu0K19z2Ota8Db6YNdJBvedtAh9al10GP4jYw1r4OIkmQLmWR9wsyrGD51n+4o7Y/zv79iiub0n/Z5yeveyz7O3s55rJ712NhCe8xPjjOfj1MUxJVN5al/O0wvBzbYa/x9usgVflO27Yc4/wnjhnpP7h862F+D/M2eHC8/bI/xrQW0zzLv/zze5R9+QOC7NvEdBJk25RFXgc7lXdklqMcuv2S4RoR8zGcf+YE2a+HXM4DigzlmGMpe/4nmkr+hrw8J9jn9WlTUtfQ51W+9q8tq2EbT5tg/+7lDPIKtMlLe+Nyqfnpl+OyyXKcZN4Wm3mXr806qrPgifZ5DSFBpm1elvhyrB9HdVY40b5NPke5CmzyKn8f9S+TPmpDbUMfpVvm0En25VhLOdxr2paDV9DeVRlK2yauk7/x+doYEgTa5s+F47urc4fPROvLZLy/Mti+7zpFnaTblKn8fdaJpqX3WcX9Z1GwfVucRYICKYN6g2dSbCKXcbheEFneY4eZvcz77dTJ9sserxTU3Tzf8h47zCzDfqtdcR1IWZpLHTxIjKrDfkstC/f7ln27GFlHyWNqEGms5zmTrPOgndWxXfdZU9TU66TuM4jZFNKiTq891Kuc6tztuA+Ge2HkXMj++6xgw/1WSrmdazUzvYfH5yEZl0XWm7eT3DdRy1juhNiyXPso/RnwO2UKsy2TbNtyY5/13WSkxSOoXA9Isy0TV3bu7r4bufdEVx6T60lSxla11TK6yTn7XsPvPvc3Mx0LOVeW4TH+2BhTcCQFzbv/zjuKtWsT1se1y34v8t20ibLc735dycnF0ft6Hb3n2NH7gx29x/fPe2+x+fuGy/+e3fK+37e87+U1f8+xo/cEO3pfr6P3Hzt6L/V//r3Ijt5vfdXTWm9vVH63db8V/+z+vOvOyUHrj/95771+3PqeY9dNGZ7Bfq6DP6zk1ypr3riajt5X7eg9x47fY219b5mzjF8v49pnUgd91PfWWn8yqqjvVXsW2+Ea7IbrcBKuxwW4ARfiJtyOm/EYZuInuBUrMs9t2AZfxM6YhaPxJUzAlzEFd+FafAVz8VV8H1/HS/gG1qCsu7EuvoXjMAfn4jv4KObiEtyHW/BvuAPz8BDuV8qJ7+MFPIhX8BAq7y89jO54DH0=
*/