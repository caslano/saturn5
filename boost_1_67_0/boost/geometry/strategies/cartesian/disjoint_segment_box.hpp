// Boost.Geometry

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2019.
// Modifications copyright (c) 2013-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISJOINT_SEGMENT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISJOINT_SEGMENT_BOX_HPP


#include <cstddef>
#include <utility>

#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/calculation_type.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>

#include <boost/geometry/strategies/cartesian/point_in_box.hpp>
#include <boost/geometry/strategies/disjoint.hpp>


namespace boost { namespace geometry { namespace strategy { namespace disjoint
{

namespace detail
{

template <std::size_t I>
struct compute_tmin_tmax_per_dim
{
    template <typename SegmentPoint, typename Box, typename RelativeDistance>
    static inline void apply(SegmentPoint const& p0,
                             SegmentPoint const& p1,
                             Box const& box,
                             RelativeDistance& ti_min,
                             RelativeDistance& ti_max,
                             RelativeDistance& diff)
    {
        typedef typename coordinate_type<Box>::type box_coordinate_type;
        typedef typename coordinate_type
            <
                SegmentPoint
            >::type point_coordinate_type;

        RelativeDistance c_p0 = boost::numeric_cast
            <
                point_coordinate_type
            >( geometry::get<I>(p0) );

        RelativeDistance c_p1 = boost::numeric_cast
            <
                point_coordinate_type
            >( geometry::get<I>(p1) );

        RelativeDistance c_b_min = boost::numeric_cast
            <
                box_coordinate_type
            >( geometry::get<geometry::min_corner, I>(box) );

        RelativeDistance c_b_max = boost::numeric_cast
            <
                box_coordinate_type
            >( geometry::get<geometry::max_corner, I>(box) );

        if ( geometry::get<I>(p1) >= geometry::get<I>(p0) )
        {
            diff = c_p1 - c_p0;
            ti_min = c_b_min - c_p0;
            ti_max = c_b_max - c_p0;
        }
        else
        {
            diff = c_p0 - c_p1;
            ti_min = c_p0 - c_b_max;
            ti_max = c_p0 - c_b_min;
        }
    }
};


template
<
    typename RelativeDistance,
    typename SegmentPoint,
    typename Box,
    std::size_t I,
    std::size_t Dimension
>
struct disjoint_segment_box_impl
{
    template <typename RelativeDistancePair>
    static inline bool apply(SegmentPoint const& p0,
                             SegmentPoint const& p1,
                             Box const& box,
                             RelativeDistancePair& t_min,
                             RelativeDistancePair& t_max)
    {
        RelativeDistance ti_min, ti_max, diff;

        compute_tmin_tmax_per_dim<I>::apply(p0, p1, box, ti_min, ti_max, diff);

        if ( geometry::math::equals(diff, 0) )
        {
            if ( (geometry::math::equals(t_min.second, 0)
                  && t_min.first > ti_max)
                 ||
                 (geometry::math::equals(t_max.second, 0)
                  && t_max.first < ti_min)
                 ||
                 (math::sign(ti_min) * math::sign(ti_max) > 0) )
            {
                return true;
            }
        }

        RelativeDistance t_min_x_diff = t_min.first * diff;
        RelativeDistance t_max_x_diff = t_max.first * diff;

        if ( t_min_x_diff > ti_max * t_min.second
             || t_max_x_diff < ti_min * t_max.second )
        {
            return true;
        }

        if ( ti_min * t_min.second > t_min_x_diff )
        {
            t_min.first = ti_min;
            t_min.second = diff;
        }
        if ( ti_max * t_max.second < t_max_x_diff )
        {
            t_max.first = ti_max;
            t_max.second = diff;
        }

        if ( t_min.first > t_min.second || t_max.first < 0 )
        {
            return true;
        }

        return disjoint_segment_box_impl
            <
                RelativeDistance,
                SegmentPoint,
                Box, 
                I + 1,
                Dimension
            >::apply(p0, p1, box, t_min, t_max);
    }
};


template
<
    typename RelativeDistance,
    typename SegmentPoint,
    typename Box,
    std::size_t Dimension
>
struct disjoint_segment_box_impl
    <
        RelativeDistance, SegmentPoint, Box, 0, Dimension
    >
{
    static inline bool apply(SegmentPoint const& p0,
                             SegmentPoint const& p1,
                             Box const& box)
    {
        std::pair<RelativeDistance, RelativeDistance> t_min, t_max;
        RelativeDistance diff;

        compute_tmin_tmax_per_dim<0>::apply(p0, p1, box,
                                            t_min.first, t_max.first, diff);

        if ( geometry::math::equals(diff, 0) )
        {
            if ( geometry::math::equals(t_min.first, 0) ) { t_min.first = -1; }
            if ( geometry::math::equals(t_max.first, 0) ) { t_max.first = 1; }

            if (math::sign(t_min.first) * math::sign(t_max.first) > 0)
            {
                return true;
            }
        }

        if ( t_min.first > diff || t_max.first < 0 )
        {
            return true;
        }

        t_min.second = t_max.second = diff;

        return disjoint_segment_box_impl
            <
                RelativeDistance, SegmentPoint, Box, 1, Dimension
            >::apply(p0, p1, box, t_min, t_max);
    }
};


template
<
    typename RelativeDistance,
    typename SegmentPoint,
    typename Box,
    std::size_t Dimension
>
struct disjoint_segment_box_impl
    <
        RelativeDistance, SegmentPoint, Box, Dimension, Dimension
    >
{
    template <typename RelativeDistancePair>
    static inline bool apply(SegmentPoint const&, SegmentPoint const&,
                             Box const&,
                             RelativeDistancePair&, RelativeDistancePair&)
    {
        return false;
    }
};

} // namespace detail

// NOTE: This may be temporary place for this or corresponding strategy
// It seems to be more appropriate to implement the opposite of it
// e.g. intersection::segment_box because in disjoint() algorithm
// other strategies that are used are intersection and covered_by strategies.
struct segment_box
{
    typedef covered_by::cartesian_point_box disjoint_point_box_strategy_type;

    static inline disjoint_point_box_strategy_type get_disjoint_point_box_strategy()
    {
        return disjoint_point_box_strategy_type();
    }

    template <typename Segment, typename Box>
    static inline bool apply(Segment const& segment, Box const& box)
    {
        assert_dimension_equal<Segment, Box>();

        typedef typename util::calculation_type::geometric::binary
            <
                Segment, Box, void
            >::type relative_distance_type;

        typedef typename point_type<Segment>::type segment_point_type;
        segment_point_type p0, p1;
        geometry::detail::assign_point_from_index<0>(segment, p0);
        geometry::detail::assign_point_from_index<1>(segment, p1);

        return detail::disjoint_segment_box_impl
            <
                relative_distance_type, segment_point_type, Box,
                0, dimension<Box>::value
            >::apply(p0, p1, box);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


namespace services
{

template <typename Linear, typename Box, typename LinearTag>
struct default_strategy<Linear, Box, LinearTag, box_tag, 1, 2, cartesian_tag, cartesian_tag>
{
    typedef disjoint::segment_box type;
};

template <typename Box, typename Linear, typename LinearTag>
struct default_strategy<Box, Linear, box_tag, LinearTag, 2, 1, cartesian_tag, cartesian_tag>
{
    typedef disjoint::segment_box type;
};


} // namespace services


#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}}}} // namespace boost::geometry::strategy::disjoint


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISJOINT_SEGMENT_BOX_HPP

/* disjoint_segment_box.hpp
+Ij+0q5Ay3h9wel2oWBrHbmsmc0JDmcFnpx8F8zcbmFXIVzoi342nVV0ByzegRXfYGtFAR1EQJksAEiI4bKAMo+AUiYA7rDVWwxAcmIOKVznUq2KgrEMkSPKVol3L8DgsVsjyEUNl78Rfd844Vbx26WkQD69ikMgAR58XnQj916dchcZ9wTYloXcNf+f3DWI7TLJGpw7odhARfHsEgkbXGDYWhk2uIM83MsSQR6+RqrodM3sAaR6CuIm6TF+On3GnE4eMAsE8iSAfGouQo5lkMfTvXEU8rZ5FHIqakLkOeE28XkikrZ/vviCgTShqJaxVxB3FojYd2sHNACTLl3LLSEv0luLAtjj5ixxFKpTT3JRJBf+8jyai4wsWz1XmI5D0aXTmUKrTrm9peXIWOAWseYdFIgjN1s9nsThbCPUGEZBVm8Qykwrxfh10wMCSi4lB2usr7EWOyq73Q0N1voy2C1B2VkZFXYr0Mts9aGF7FvCgj1UMvxc+eR+0sBNgwO3zDiNpW+LEw5m15MXBLUU9ZHvEHR8I7c4Hx1goU7vzIVo0tYZ/wcaccaC79zoB7dUnPk+1IYM+Y6M0hbaTMwwYtLAcEtw8JsFZy+9AIE6nJK1n+o9xvRr7b3GmObSzjsXj76kccSpraPxAB6horO0S2Z2thXNrCQIzP4TGH4jTdL0ANM0CQaI3KZqojAK5vgqO/kF7uLyzyDy3S07r0FYBFIkttM0plse7t+rYm+MNlcbi36dJ7ZtaJOUOGuRbT2MttE/Oe+co0IkyQxJTJf7WYijpOz3sjXgBkKgXphg8LOXvLJhepY7IfnRc2Qcz0uaWAqwo3JxbLRJBpo45MTRJjYP+pIDL6om9RkTeZN+kbft5grBu1QLfwH9Qbx6typArAuFsHpwSYdt0dxIN+zG7ecW1SKkjCrBkVZFxsAiGexCdTkKcS/Y/zsIegELDirKW56qvXkOU9U6x6Cs3v/WeARGiFJ1GQ6pDJoNIep4EfQGLWGg/QwEXFH8dp22cXXWVN52yZIB79wPEJP0NJyiRs8Uvu/c002OnYpX7rvX4lkQ8i+eUMGhQ+gZt9vlaV2t4qB3WZ2dtWwLmD6jPSPYbM/QZvJwgsyZ1mp0fC8as2lYdC2NId4q/vMNfPnWYqR1Tabd2gqBPejVKrHmDQD7V2IOYfoE5mVmlOB8DEyzdBpk3CderbNUpPMyjTSwirQYDx7BF7b3YnMzVehwWjThlIk9rQSPPm8EZwBEqTyuvFBA59vo/21rOv4Mp8HsZFwV3UzMLqlHlmEki8tE1fesTQknoTTOEzLLXHfgBM6pfezS4UbpUpHoXNfmJsWRGJWJXgfQER/1UWyQzvjIQZkT6WTWu6vREKSDG8DnBpJRg9HRx4hTKu876qKPRh6FmSSD45pJl6vNDuUdu0yRKVqjuwILMBbmTH8QnyPDgZYP6Qt2OgGehe/e6Xmx5JV88XU/G2LDFlikVLRETiNpHfJ18p8jW2uMvFzcP+9KriVRj84UbLsXPCRw27YLcTvnRAiR58moEzySs5OsJ09DcKDfqPR5cQFGbnI9PmrdCw2ajEKb6YlTax4pMIH2or9NJIB+G2WkU1Pkc78hdiX03Jb73akkt0+HR0FVJuyWlmJj3C/+qkHu7KPEAxbyxTXanZrY6b2X+nd47l1poQODCqlnx/Gb+KvfQw0qXMZ6dj662mRfWkI796XQyV+aEKyx6BRSK9IxrAGR6sSJRlPngi84UBpfvMfo2GF27NBvAYBJxaZeUXlXwiwpeVfCLbq8K5GWB/OuzLX0zbuSYxnnShQcT2qNcbXZ/Y2OH4TIPUb1XgjCuscQd1C49YCg3uEaIaj5RFewoMZ+mDRVdSXPbdpNTIKa5/i9ZnUl+bfX7PdMjswIc2Hzgn6muMa5vU2RjS612XHS8UzwwqYKOF17LdFior45rL1JRbc+que0fAB3nyE8izxmGcWVW0h/47jGldfQBailM4lxijxtPcdFGGBCjzQVkr2Lei6XJ63spBn8hNTDfGcWhCWoTio2xEfBFKIjkE4hjgmkU4jw6ipNIb5Pfms5Dn43TOEQ13qqUJBLF1RCYb2kgenEn4e6CIti99FqyJXfSsr0vKiaCRvgKgONkT9bXVwE3DePzlTgvERWyzz0uEWedZAqe4FbvAEfJhYQrFbly+1us2MEKVO9ewqxxFXw41ryI0l2Fkl2VhXW2MhpWstdUrpoPIkJW0xuM0Yes57lImZVYYJAYlaATwaIkBWd6r5C5F/20h3uk3RnojAHFRi8rFMqZaQBekstE//+395Eyryl8gFSg5fyuw0fYPI5kP8Dei5yDteT/gOcSagrhMg6Kc0KcGy6m7MtJxZXmXKFaPVJuQL9FJp0aYncomvU+EQR4yLgIC4K5V0kCjVy5SQxc6M4ljxPMDTSzLd8h4/gMJu0LWie8CB+l3QhhDaWMNe2tgE+CgWIzS95K0RqWrvbLSesxRqO1dusFctfwtS1NHVSf1298brA2ki83DymQ/MI/4amVMP2oL6kaBvTpbZBWgVljrbepG41Frh7cfkNbfDSZiUmqxUWN1OI1ZXBwH+VgZ60eNKBuvdbhmGeICVOztRl6xlMjSYBbe4SGTzmmexZEd66DvdkFCR8/yKp9QpdM0oIDbXEGO0XmrWHSI+xjS4pbMRD6vaNzCxupIVCNMb+PErssxi7VMFkt4JBt0ZhJ4IX08WWRdhFZ9HoFtYXDUXWdFrhyJiJE/fAZXt2sMmerSXPjsc1UXw3h3GBqYiu18QG4vgAuvvOQjHffK1/2Aa61j/xLs9af+5Qn7X+S+txrf+FoXSt3x1G1/ovh7G1/klDpbX+XhtwrT9haBfX+nO+6M5a/4QmxR6Kp+bJa/2rOFzrD/1GWuu3FirW+rNGetb671/vd63fuJ6u9c/aIK/1j1vf4z0UlWWU67UwD9f3hvhw/bAMueYOoVz/FEq5/m8o45o5ROK6ugy5pg3pItewDd3h2kfJVfW6zHXSIOS6a6vENcSm4BoW5uF6aJ1frhfWUa5D1stcj6/zu4eCjGfl0SwGHUwlbaROETwc/SQYHRfMjkYDONa4EO22z481QDDh04GcrQOdPJD3HGiazslRolAoOwfTkUchivuoW6nvL7Cuj64BVYjgiYSSAJ/BSMyeHCY2rcLjixHYuZgcvcePUIZ7jxUb1mLxhY2gxSeG0OJrDGHF13cEhgmPFc+thSFw78shnnDvrhBluPdY8R0q61AIlfVHJmuJJGtLCJP18Vp0Dfd5CA33Xv63NhbuHY71f/QaeDZvLzit4WxHWSz7HDjNmWSTKdwhjMwCCiND6CHN9pWeQ5pEyeLBNJPxTLGrAKggYTb5GTULZJpdHc40e2ow00xDc2kc7MllwmDvXK4BYbqQewfTXG4aTmWtlWQNlGR9jcUS0h5Ec9m7pF2Ryy2vut2Fbs62X6XI4fSC63K4bjjN4TDvHFYEeecwmOawNIjlMIxpFSxp9WYQ0+reNZjD3CBPDucEeedw72rM4dNBNIeHhlFZ+4YxWcmSrKOrMYfRLIfDHMocHsmhOfwJppfA2SFXWMzqc04+2zXNV0FeQ1md/mQk5hXDSdZAc9sjkDd+qeamBXnX3HtQy4RHmJYPMi3vlbS8R9IyZjXmeAjNMaj2CFHN9RTRXPWv9q48rqkrbSeQsEMCiEI7OozFjmvFrcVBgUAiNxKQ6ig6FkXQqC0qYAJapaDoD5JMpK0dVxRRK1q17qK2RXBBrFZEP7fWtjpfq6kp1WpVVEK+s93k3iRgWLR+/fUPMbnJfe7znO2eN/c577FQXrsVYd4SYsyvX8KY514imLVCgnltK1JeKcTK+zk0EuX64gFGmGhRNwGtp6hG04Pz12rrRYuPW7TnjAWM2sYlkD4S1/agElLbRPsuAVt7D8xzlQDz7E949qR5LhAQniFbkfZ0gbm2pwjYmr/9BGHFEawbARjruwCCNYjG+vkTpLmbAGueUm9k1LY+E/TaB8dBTFBLNM6CK9+X5Jo0ConGfW9iRzuR1ujFlhaH6dz0wnQSCJ0RNJ0zXoRO4idIWrmXWdpuL7Y0B4y1mmC5EyxHGmshjeWNpWV4YWnDjzClCTPJgMSzqMBdOVbdlYPF6VJLWN21nxe7u07fgrprgBfprun+mNl0f8KMQzPL2oJU3vE0q/zBk63yL1tQd/3KE6vsRrA601h7PQlWry1I5UZPrPJzlsqeStxdv3ZgKKx5z0phWDxWqF7HUnjbk60wfzNSeMmTKCzsRNb/dqLX/9Ks/rMZKfyUoXC9hcJ/bEYKNURhFMEKpbEyaCzpZqQwmSjsf5SpkFJghfV4yMU/dsNFHD9ls4ajPkSpYgRSCtdlmIekvgfxugznUaZ1GYB8pQdbvaoUqd/iQdR/0BEzVnUkjN/3IIyXlyL1uR5m9QoPtvohpUh9ogdWLyFYQ2ksMY0VU4rUD/TA6gPPMNUPn43VPzYPx3h6AfTPt9CPO6oiDkmsihJzGfoPYP35I1m9uMCd3YsLNqGel+6OOX/gR/T7Ec5j3Wn9m5B+yt00OJdkkMF5oDu7HAZizM4EcyjBHERj8mjMqE2oHH5zw+WQZioHODiL8n4UChZdJ/04RxsXrPtpHkv/X4h+8UtIIhHe5V3GveiRG1vuyo8Rtf+6YWrrO2BqqzoQaifdCLXNHyO5B93M1b3djS0zFmMtI1hjCFYcjZVNY731MZI5g8i8zqru8elGowS6bh3o1l6EWnug7sm7pj49lCh93BFPJlXzhLrdRahf+6PNpwGsz/IG0+RSFQJ/4jX6/cuRy6GLItOVXRRLNuJ11K6Y/nJfTL/Ql15H7Uror9mIiuJ1V3NR9HRlF0UkxvIlWDEEK4rGeuxCsN7ciIrilgsuig8rmEURnwaLwmgxeP821+ru6+uKh7Ydq9l3X70PW+LWDXieS2aAe30wrW0+9DyXngEe2oAkbmXMJostZpMTMVYBwZpGsJJorFk01swNSOJEHyxxvJopccYs+OMszlcbjBMfzaMYyY8SmZ7Z9o1Nts2xik2eOJljkw3rmo5NolexY5OlFjO8qPWobOaTGZ7MG5eN2JuUTQo9wxu5HpXzKMacNtpiZvewBGEFEywOwaoXEqxONJbTelTOzmROO7uWGZvwZzYRm2zKsrpRSrxxa5q0knWj/M6JfauYUIJuFVVO5FYhF2JmE2hm250IMzinAABrnMwqP3Biq/RGKju/64RVvkSwfGisSTRWYAlS+aYTVlm5iDlz/+sMG7HJsUwrheeFWGHOCpbCf/LZCuevQwqH8InCRQLMar6AsHqFT1jBOQUA8OWbFTrz2Qr7rkMK7/CwwhCCFUxjXeIRrDDU8Dqf4GGFl3KYCoemNhmbXFXajE3C/Sxik9eGMO4Hc3nslqsqRq0tmbD80AuzVHsRllKa5YpipHgwz3T7W/8Ouf1147GVD8KYXgQzjGC+TmPedySY4mKk/EdHrLzugcEyNvm69mmxyUWF1ej4xTBc2ys/Yo+Oix3Z2rVrEc+ZjpjnMk/Mc4kn4Tma5lm0FmmXOJpre7AjW7MIY3UlWMMJViSN5Upjxa9Fmh85YM1/q2OOjiPethmb3J1tFZtwh7FmNSMd2NJ2r0F0Qh0wnc88MJ09HoROVwdCp3INkubjYJbm5MCWJsdYt7kYaxbBmkpjXeQSLOUaJK2Ki6V5fcaUppjeRGziN9uqu8okuALPfsTqrtu57O76VRHqrv/hku56wR0z+8qdMJtPM/umCKlM5ZpVJnHZKnOLUHeVEpUqgrWAxgqmsQqLkMpAojKXpXLJNBuxyYAMK4VqMVb4y1KWwg0ctkL9aqRQwyEK77mR9Z9udDzBIawerUYKkzlmhWM4bIVrVyOF4Rzy+yfBKqaxXqWxtq9GCjtysMIHLIXbpjYRm8Sm24xNqqNsxCZLt+G5+TvRzNhEYqG+bhVS34dWf98VM65zJYw70IyfrELqeQz19UYeS/26VUj9dXAYYm0hWCU0VjX8PvzijlVI/QH4Hqj/93Gm+k/lTcYmsWk2Y5PqSBuxydKtWL+e3YuHgGsye/HPK1HP60Y433ch+l0IZw+a85OVSH9DI48enPlyMjjrGtnlsAJj1jZizBKCuZLGPNBIMEtXonLY3IjL4erxp8QmsbNsxib1nszYZOEMxr2ocyNbrmEFouZEqDkRao3OhFqdgVDzwHK/NfBM1V1rYMvchbEOGTDWIWeMtZvGKqGxKlYgmR8YsMzYKmZ1H57cVGwycaZVbJLpZo5NOr7Pjk0y1daxSfkDjik2STawi+LuckQ/htB/4oTp33Mi9PvT9LkrUFF0ZRRFR4ui2ISxjA0YawfBKqWxbjQQrH3LUVFcbMBFMeYgsyj2ptiKTcbOsLr7nmjgoKHNt5B99w13Yt+iBJhWdzID9Ce0hDQtAT0D7LIcSTQy5lr3LOZaR5chrKt8jHWaj7GO8QnWUXredm4ZkriHj4e20nSmxNpk+2MTShUvJJuTRDBXrsEE0zAowdusSwb8IFYl+dPrE2WqZPh0seuJCH8usnFUwmWotfWKdyjtXLRyMTRKmOUlRbtHntUFpBuMegFcIdIL7u57VleUCVffshd7akYJLZaRUtoO8dBDFCjTnJFpjuvipkHrWZQw0x2m/V6JruFNrgH75O40cBkf82Xgsf6ZjfQzI7Rf7hy8eyljXxGLNWqpQY+oBT8fQOv4JMVkgdr8y8QEJXko1VxBG5L+F+7Pq5FkUZrsHJlmXz69+4laMqtADJfUjS7VGarR07zz0BhwXAaNX8ZFFQrHPAFXNji7TOmSJ3D4KQ4UYBUoduhtys4H/wop7TDa2RRbaDY2BYN6z9eV58OdOCQ38ePf7O/FBdk1lGZ0GZX3WKDoJtrJBd+q0e11hNZRhR/8BqWV1FB52TeRS6lGXBAi1cBjpeCsUplGcph2vwnKlPnywcEZAfBD88EzyNjPCa3O7iLa2QdvnAQvcZ9vMCILDsSAWFRoYtnsEObJYjVvrLhnlSi3Ith83hd8vDgIftuNPldfTWkTTSwTa0AxaIB6DaxL7ejlsCJrUdSeuFzhKR6crVE63xUJvJ30oCwd0Gno6XiN7tRU4meAj/F5QeCjw/ipeqlu51QO3hU89iF8FC6ajh6Bw4q2aZE7HYHT8tMJaoJJU0i/yKP34E4CbQF1j7tw61rksNB8HnQWlcnGoMumFrEoqAIvKQpEbkHdjSrcLOByzk+HG+g2QeXND6I4Sj6QpO9AL0nWInPNaV1cRqORWC2c4BfjXTLc4M7eIbrLcngAIyzc090q+CYJCps2DeelYSWdt+H5m3YAtHMhNvzlMparvn+Bbusc6JyWQb9fkkxzC25VkCbTPAKNPg3qmgPGBIn6N7kgoeKuQIgN3IK+RzPdRfu54GDn4HuwvK/CnPLf9uFy9H7UgicFvhzObJ+7ggmdz/WBS8GPuoFTLs/+EVCoJha2Cmhh2ymXCt67ItPyvxFxOYe647Zz2einqIOYDVTKncUV7yXGaqcKJQPq1OKhl0HhQqtEahAF/8TLVJOxMTDewhhI6bIXIZemmJhgkcvHExQuZTxBhTbO3w29PWlAmtlvSME/8VJttNlvaA37qgkWViwEPZDeCHvqOqJrBdRVYKrW0TuRszErDT7FAmMTaLS9QN3CBUtaSQG8UIi4QBEULCiTzJGjhcDIfgoJiNWwVrSo/V2Qamp0r13EdtFq3NR36o5PJobQWOT6GCPHrg/kp19wTGjb9WHVPg6C9nEWj4OXGO0j7TzdPpzFBbH5sZp6GfrRCrSLWeAg6KyJOajwBjyQq5QalbIQ3RPQOA4GNLF2GJeUGxhHby80khsBGPBfFqtvwDP7gPMKVcql9DlLWaUdW6g7uBAVdmKhXDz4ZaWzaC8Xu8MbBWXuYBjTyEN/zQoQlF3MOwKGrsrQIzkecBORMo954IPMOqDnIawUUA0qyW25SgJu6idwrX2v669oNL4PLQ9GJfRwVmlHcdHxW7NQbZ7ADp7Ew3JV4g5zZYIBNXaH7pOZjdAP1RfU44xiUI07SDVORtWYRaoRlBCuxdh8mVZSTLaqfvt/cB0+xHX4vY6bQtehM6zDDyfjOgzEdXiWY1cdNuPr3VLb/r7eHiXEvDvnkKWv14v+iH/Q7Ovdl9diX295rtnXq75uaJWvV/357+vrdfv82ft6M/YwfL2PqGZ9vV2uGczf/Yqyab/NSGqpr1fXm+3rVdgGDkj6Y/l6v4h48Xy9PSLa4uvVh9vw9V4Mt8vXuyO8rb7eGeHPwtfbKbyFvt4bYe3k610T1jZfb2JYO/t6PcJa4Ov9fmhbfL0lQ5+Xr/eNoW319d4fYp+vd9x4u329r41vxtfrPb5ZX+/dfzXn61W8ZZ+vlx3vM7feHesihVuOPSXQj+1VLa19pJgjhWHAKVloDAnypZpa3cBJJMiX9YoRwgNlcruD/F61VO1jKvRxllCm9QinHM/JNFVGvy7XYSRVQ4XOE2by4YxMY3XRw0kWF42Um+L9eLwRFSPUtzsG+nd1+8RAvW+YYqArgVYx0JlAu2KgSwNZMVDatTbHQHOzrGMg1yltjoG6ZlnGQHsn2xEDzU5phxjI4b5FDFSZwIqBRo5rzxgotaodYyC9sjUx0D7lM4uBXptqOwa6kfz0GGjTpNbHQGH3LGIgw2hWDLQkwZ4YyM6cU1uO8dop59SAj0hos3C7zZxTvvTnbtssck7ty/xD5ZzqOtucc+qX84bnlnPq7Tf+zDnV2pxTPhP/GDmn5Lcb6JxTnQYyck7FDfp/nXPqSbxVzildfAtyTn0W38KcU10G/plzqumcUz+Mxzmn9vYz5Ryq69+SnFOH+/8+Oacc+/2Zc6qtOadujjPlnNrb11z/wc8k59S7456Sc+q6jJ1zakpwUzmnwk8b7Mg5FXDa8ELnnPo1po05p3bG2Jlz6lIfVs4pzimDOR3SjgFN5pyKj7HIOXV7jT05p06uebFzTs0d3qqcU5HDm885ldGblXPqaBEj59Tw/jZzTt2WNptzauxJQ9M5p/ZIW5hzqn9R8zmnkqUtzDl1xc8y59Se3i9ezqm/9v5dck7Vx73QOaeO9zAlWWrs+RxyTl1fTCLGaevNOacKpplyTs3t+bvmnNrf3VQct3u0Z84p/hU=
*/