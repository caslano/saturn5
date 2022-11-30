// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_APPEND_NO_DUPS_OR_SPIKES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_APPEND_NO_DUPS_OR_SPIKES_HPP


#include <type_traits>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/static_assert.hpp>

#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/detail/point_is_spike_or_equal.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>

#include <boost/geometry/core/closure.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

// TODO: move this / rename this
template <typename Point1, typename Point2, typename Strategy, typename RobustPolicy>
inline bool points_equal_or_close(Point1 const& point1,
                                  Point2 const& point2,
                                  Strategy const& strategy,
                                  RobustPolicy const& robust_policy)
{
    if (detail::equals::equals_point_point(point1, point2, strategy))
    {
        return true;
    }

    if (BOOST_GEOMETRY_CONDITION(! RobustPolicy::enabled))
    {
        return false;
    }

    // Try using specified robust policy
    typedef typename geometry::robust_point_type
    <
        Point1,
        RobustPolicy
    >::type robust_point_type;

    robust_point_type point1_rob, point2_rob;
    geometry::recalculate(point1_rob, point1, robust_policy);
    geometry::recalculate(point2_rob, point2, robust_policy);

    // Only if this is the case the same strategy can be used.
    BOOST_STATIC_ASSERT((std::is_same
                            <
                                typename geometry::cs_tag<Point1>::type,
                                typename geometry::cs_tag<robust_point_type>::type
                            >::value));

    return detail::equals::equals_point_point(point1_rob, point2_rob, strategy);
}


template <typename Range, typename Point, typename Strategy, typename RobustPolicy>
inline void append_no_dups_or_spikes(Range& range, Point const& point,
                                     Strategy const& strategy,
                                     RobustPolicy const& robust_policy)
{
#ifdef BOOST_GEOMETRY_DEBUG_INTERSECTION
    std::cout << "  add: ("
        << geometry::get<0>(point) << ", " << geometry::get<1>(point) << ")"
        << std::endl;
#endif
    // The code below this condition checks all spikes/dups
    // for geometries >= 3 points.
    // So we have to check the first potential duplicate differently
    if ( boost::size(range) == 1
      && points_equal_or_close(*(boost::begin(range)), point, strategy,
                               robust_policy) )
    {
        return;
    }

    traits::push_back<Range>::apply(range, point);

    // If a point is equal, or forming a spike, remove the pen-ultimate point
    // because this one caused the spike.
    // If so, the now-new-pen-ultimate point can again cause a spike
    // (possibly at a corner). So keep doing this.
    // Besides spikes it will also avoid adding duplicates.
    while(boost::size(range) >= 3
            && point_is_spike_or_equal(point,
                *(boost::end(range) - 3),
                *(boost::end(range) - 2),
                strategy.side(), // TODO: Pass strategy?
                robust_policy))
    {
        // Use the Concept/traits, so resize and append again
        traits::resize<Range>::apply(range, boost::size(range) - 2);
        traits::push_back<Range>::apply(range, point);
    }
}

template <typename Range, typename Point, typename Strategy, typename RobustPolicy>
inline void append_no_collinear(Range& range, Point const& point,
                                Strategy const& strategy,
                                RobustPolicy const& robust_policy)
{
    // Stricter version, not allowing any point in a linear row
    // (spike, continuation or same point)

    // The code below this condition checks all spikes/dups
    // for geometries >= 3 points.
    // So we have to check the first potential duplicate differently
    if ( boost::size(range) == 1
      && points_equal_or_close(*(boost::begin(range)), point,
                               strategy,
                               robust_policy) )
    {
        return;
    }

    traits::push_back<Range>::apply(range, point);

    // If a point is equal, or forming a spike, remove the pen-ultimate point
    // because this one caused the spike.
    // If so, the now-new-pen-ultimate point can again cause a spike
    // (possibly at a corner). So keep doing this.
    // Besides spikes it will also avoid adding duplicates.
    while(boost::size(range) >= 3
            && point_is_collinear(point,
                *(boost::end(range) - 3),
                *(boost::end(range) - 2),
                strategy.side(), // TODO: Pass strategy?
                robust_policy))
    {
        // Use the Concept/traits, so resize and append again
        traits::resize<Range>::apply(range, boost::size(range) - 2);
        traits::push_back<Range>::apply(range, point);
    }
}

template <typename Range, typename Strategy, typename RobustPolicy>
inline void clean_closing_dups_and_spikes(Range& range,
                                          Strategy const& strategy,
                                          RobustPolicy const& robust_policy)
{
    std::size_t const minsize
        = core_detail::closure::minimum_ring_size
            <
                geometry::closure<Range>::value
            >::value;

    if (boost::size(range) <= minsize)
    {
        return;
    }

    typedef typename boost::range_iterator<Range>::type iterator_type;
    static bool const closed = geometry::closure<Range>::value == geometry::closed;

// TODO: the following algorithm could be rewritten to first look for spikes
// and then erase some number of points from the beginning of the Range

    bool found = false;
    do
    {
        found = false;
        iterator_type first = boost::begin(range);
        iterator_type second = first + 1;
        iterator_type ultimate = boost::end(range) - 1;
        if (BOOST_GEOMETRY_CONDITION(closed))
        {
            ultimate--;
        }

        // Check if closing point is a spike (this is so if the second point is
        // considered as collinear w.r.t. the last segment)
        if (point_is_collinear(*second, *ultimate, *first,
                               strategy.side(), // TODO: Pass strategy?
                               robust_policy))
        {
            range::erase(range, first);
            if (BOOST_GEOMETRY_CONDITION(closed))
            {
                // Remove closing last point
                range::resize(range, boost::size(range) - 1);
                // Add new closing point
                range::push_back(range, range::front(range));
            }
            found = true;
        }
    } while(found && boost::size(range) > minsize);
}


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_APPEND_NO_DUPS_OR_SPIKES_HPP

/* append_no_dups_or_spikes.hpp
zHquDvYvy+7P/kibp0CRFaqYA4uWC+0Pp0JyniW+aT8GkEC9KUBIxIemneZ32JfRyt7E4jKTsjLyuWxA8EVKSqvJ1KLVLN0A6DyeDEerqel8aCBgGvfnCk1xaoNJ/XhBcV6r6f4R9I77sX+ZWfAvMwkL7o62rxy1eLL3VMmpco1FrrHKNclyDTynyTU2uSZdrjGh34IfmTOur1a+UabJ848qMG3zx5UKS0aFyVFr8RplL5wtb5xSNh7InyJuLrPKZafEV3fJJWnID3SnyiUWucTmqE2WYo8PwtPaMqviHe8osStlR2VfutxglUuSHTW2VpOyKxirfJCxa674apnFWGZ21B4FZNULtXmPGndl75FLTJgvAYoHmm9Qg7EZ32S0jIuvtliMLZQ5QZkPmecfNX4j+8yLF8nmu/snGDMXhUkI1NmSnQOK04LhCVAl74/ISivrqqhPBSK+5jwKAkBmj/6W3QLX2Fvmb/koVXzoMWIs96kpBUjqz9/hv3dI8N+7D50axwOdb9y2QJlnkp1HST/TOeoGKhsejbvcymfyfFICKhvnQW3FLc6PuplR2Sm+2qf8ZfUXAPFWPRB7u//dU7dJ8fWmxRnfGD/IVrM/crT0yS2j4tPb5NqjaF7tHb/TrTgHKlTvbuWTQNkouxaRRN1w95YjgAvpJPnG1D1A7imzXraSAGaKW/3EfzmmCRuT9+wPJ+GLoCQicbiovV9KJJ1Yq/9yTNDV2JM7/3TbsI+tSASIMijXjvUaGwAGZx/rLSzIOfh7n9xYJDeWyI2lGKC60S03VsqNNXLjQrlxidy4NLCyTr5JXmGSAXdcYQmQt34ireVG+H+z/Abpzr+B2lmsoOaQKlPI0F6Kftm2FD3vEzt0bd5htdePqkzPQdvyG/uo1AH6lyKqUOwY+Q1GhdFFEPFI/egKhB2Gwj3OU7FyY6rcSBHOAU9vzJQbLTLpWMpvUJA48lktNyY7Zr357X6fNwfuHzdsiKpf4iTx51/iFDpmYYIkAjY/Nbt/jpyI2YNmdoFNFPDdC3iM7D0wTOFQSPlrNODdt2nTJr+Cupiqn0IeqJvqrTVyoTu7i9RYuT4rZgys9G3aVC/etUn2VGZ/JN+RJd+Rr+yUC2tkz0K5cInsWbpJLkyTyUu0XJgOCHpvofUhesmRC3PZkTSAyNvZm5ZokwGg/C84t5Tf3PkcyrF/MhUZRrDxeuNxnQPFBb0wd7rsUDIqBabsftTPIgmtN5Zdfl+CEHgWF4yCf6ICdmFkFmk4u8vx8HNcyRded/kftAteux75bv2zoqCLutromWItMB890wJ+cPNhNbBlNzH8cf1ZXPe4JgljGxy0uAZlZ68RNwz7tAaInoc3aHEJZy84BEeE+Ftsd7wosKenRs0LwFw4jqj56GYJAobNskzS/brjtlDYrNWj2OnoUL5PhEP5nsDQZNl7HIvtcB91Kev4t2h1LYsAKIq0X/GaV/8dtoF6fO+Fx45/cpnXjEHPHbVW7z36zDQ9AzPAo5ykdI1rM8Cm0CPNS/ogEPAS2a0X9BbZ8ztgbtD5FcYwgvqetuNGYw13kRLXlZCcz568QBSC8/OOSDurtAkcIjmc9DbqNaGDZQTwifUxeANZfiHCqls6BZsgOBZnSYmOi9A9uje2U8iCDno8Hk1pNGX9BZt9FPl3u/di/zr7c1qY3XzsFa3KnOoxdQQ9bZIH8/pUjMCkA1zv1cgX4goKZyxsgsLK9pGXofgy/zv2RyCD7f5p6opc1Jhj33MCwoCcY/2buSkWeuu18N6KbbsNpINURNAKUDn4lcLP3dNGbRmU2Xi2PRgIqtRewtJiReR9LZ3QS7FNMmgcrFklkAJPpeTePAvlJDU8APpyuOPryCAavRXnApKRo6ZUWmlybDA5IjpJ5yVHLufdqtS6hdjgQvgt0boVA9lKeJ9qWAdgbhgGGJ2sL6RWc6G2GeHaqvn0jWA4xjqb8J7gQcuRSvjhJBXQGwCxhdgVjJK30J7ZKqHvA3hKb11IA5XsdvgtUVOKINcyf7O9CbXdc7xWx0WpGAnQ7GbLM9GBlcfNhjJgS8BHabpbC2uXDr+lakoDirq4qQyhS83Pq2i+j8MH1Lt5ndajhRSnRut8ePkxEAEMuFJfGmaDgUNCUcfTlMCsfCLsuO3FLW203so8c15fa4zSLRcDSmCV5sL2FtUVJg49qtiY87DKHaB8wP6QRpKxC/Td/5uvkMFr0c7WAw+YhHBnglMQ8dPCg37A5qRh8KJ1VOWeJ+FkXBzYQs7Z2fv0lr2ncGT2t5rcMQJ8dP7vUBh8rI+N5M12xE4EJiiN0oBJixl9esH9AGtDARoW2cV2jwllYuLPumD5Y9mvvw+gdw2HFiXQiWrSM80aUVVP3ZtPb6YIaQAGXoNKWc7oETQ/F9s/Jy9zu2d18gBqaXp6L6UP6OkmPR1datSZkPMIHY7Bc6+msOn8SDxG3l03pKA7d49nK2leIkjEWCD1RvIXAK/Px1A0W/8OO35cb0QnQPggcCCCa5NDnyFxHX7FlgT+dx1WRR4N4OVpk9YVQNZGU1CNKhWzmDALjvzNeYcQIKYBDGsq9XjqjZ56Qx1UtAq9caspWRgHYdyvqtJ1HjgwXTAIjHaQqqbkJ5NLKdjRyU3TdbVbgweF5CP7YnhoPitCwUVZPCafNYsoNiv76Q/R1QgGuzTDSFBdEGFhgLt/is/bLr0OPVseiV8CvLxJ2+2XBB9DHyMBCrDs7nVRmA32zp3cnbia8g708EWDFN/rQi6+IG4psrcCxekfBxo3FrrlH7eJAZSMOS4R245yeJKuwZNM+GXBL8cDh+ll2AEGjsPgTGWymwQCcpUI5G4K9SwFvqXDUXsRN8wmyDLyLMK1eA7xUMDrplOLAMgWNGmQxCa2LeXgbyFMXQ2BvxwMNAHgrygE/pI18GfjNYxcz7tboHW3SIfM0FtsPoYvmd7jItauJvGziWCRwkpAhTPDFYbP7cifo4BgLpUAiExvS0NA0A5dz29tICIcCL3WGgQRGiArDQPBZanKeBgEVrP/upJAYDUbvII8BRMATKPeQhshAMipPYDTzS+qPB6qHd7ym9dTLhpDuO+wk9JW95ICu7Y1CPLE402uzYeBpcAERK5PLLzjZsdOttrun6I25ao3sfm3kDLlhvMxsAO31bz2cVHQ4kjIlzDb46KuWC5fzC5ycyeH6zjkiUBV1hF0yn6Pffl3kUxMzJHWBhy09ZwfEVA0NVotPj3k8lF10GkgNbNiDBYz24wI9NQ609eIWL+MZ682Oe9zaYa/1WxrudVB/Ya5hnF86YBdjqlXOSiYt/c77MMnDqkOX4N0fqewf7+PjX6Nbja8CSifZJshu9yaxmuQpiGpP25qjXW05kimvF5vTPYehewEsrvyPgAgKi9KJzdN99wDcNRVEDYgNGV/lNcrbtiW96n0RWDNEzzuyeRvPYDZbtUw27xeaQuMIYl6a1bI7DYIl5JyEZ4dt0pUg/oxgPXsfrio8rq9aY5EnAix7QAgNtpkvAiTMbIb3h3l+dKtiquyot7g74rBEBQuNzzABhuyUnVIisjxQOTfKsjFJskEcyBWs9s2iIKf5lcIvgDEeHt/a5LitKJ2SKB1iSwGp0I9+BSP7q+gq1DWG+vfqQbjlGeIPGmqVHrVJjd7vIP0kRL8J1XufBlVWxHIJibBbQewJZRzOeT0yK40/bSWF7CBk+hauVIppz77u2MqOCqFsCBAkdhRPeozURTIzzb6XX7QVK02FbGcb5NC+qwUBj1vp9h2N0yIvxSaRPMJZkkSNb9J6edwzEkbkgOuamUQLeTypRmkIm7ik4dqsWY27TGK94Qer/kKfRLpzAzI14B3FEMDdWX3+1fCdAEFdsfSTTBlfThl/ufJpM+xMg1SxlVpDo/eQ5sqcUmCgI01FrHFp+DoUhg7maLgsekiekygkx64o4D9/ZskfEVqXV6ZPuF84JYgD6/RkR2r0SKusu4eQRVwjrXtAYvk0YaX8iYqGsMSS1OVNdhPDMQVS0GS9N2Ysg+yQEllNsJEpU98tczMAWeFlqOp0h2q8FO4VqUF6qw0qGFiBbzoGuHgWYtapYuJK6GUV9b1CB0Am91zKmCDzKlA8zy35sR9MvU1/bYIGJMVDWMKwm5lPRUVyg5kaZkwMoe8FD0ooc4j0SgAGXpQ6Rm+aNcN3Yzwy8Vrh3eSTTnBQzLCvaIfdXf4BspiRvj+JyRIyGdYsz0VsIseuIcMfKfDICq004kGnuyUhbwBzdeuhxy2AFZZQWF4uZsiwLoq8z72otW1UbnTpN1Xd7or6Jpy82tK4fdmuDtYz7RvKLKtDXUapgH2QehaN7TWAWPBF2UMe8fen0vxbEtUuvE/GYfWe+DQFExyNjZxyo1XRRC8qGQSxlj7JpG/+8Lkr9OszEevYpUAceBPvuJMVgblSvsS9HXeYIZzUWgSA99HzdQWO7p9nP0yEGjmBykU0Z1mtNVZYtwGreBuhaHny5wMMBYu9a9ME+QNdorx2EZ0LR7NNykBDfEks//eVMF/r03IPgYIc43Dmy7FOrxp0pWOxnTpUjy6LWkqsXv0rYuQAZZjCfS0JvuYcodZKUyTOeLpP2Hz2vN6JBvsGMK85MY0SJNmOGZZoKw3iR/8YAKa8Aa/BFgA0AFwZYBZRYT6pGFdMNUAQM1wR1e290vGQGMBZM9FGX97vzcOo/MGY/1L7XZUsEmCpCk0ZLg5KTkdEGt0rRdo9ClxPGxXM3qmLCFn97FKoTsYC/dbRlwVobBaYiUAJZclwwUwFZMRME1xNNsLuIE7FFLuqJTf0ecRBwFvxEpaR7OKeaVy6EhOXixCCuk2d4DHvWLlU0VBfZOeYUj5Ab42YWNVyIfMvF4eq6wSCfc7isfU4IXqrA3cunVyGTREvppvA6v3O1A7Ef/aH8xUxJHHtKAJyufCtl6IRabBeqY2T5Vb0mCBFpLD4ha7lICr7DXKLXZHS6rY/jwFuksT25+iByCe/gcjYd5hxpW0OGZb6O79VQxqlmcug6qzOorsN8CBzjbALCyUEp7be/5+H6Y5WtKlJMfKdEj6XEsKFC6BTNBaAKbUij4hKu2liJRiQIO2+BhCh1FwkArTTLEEXu2ut2V/dNsy2MW4FHdRoLUc7UiR6k01TA9+clfDHO6Ah3S+LpgBi33EV2s3/zPE/+zjfw7wP8j/xOhsaspyKxotiW0nTJRSBxO1FGEXwqY6yIk8UrbALCIO3kBAsdkuwQ//NlcD0okZIkgGiZmOEgJeh5wEFviaYOVy2FHiq85kI+xLgmCI2eq3C0el06urYUE3kIUXgjT/24RmeJFDkJnX23ovespYnUCcUThtphLvwWCFuJl4peJm/yb4073fPLUPnl/Qn7WiV6Osh0LTxeR1SwkI1VQ5Jhgj34wf/NtMKgA+WBibd6/GbEBAnEYd6uDqSHXar4R+uON2J9OOy4TlXU6AN17BcXLg62MbjhIW3gAzhJMtsNYjSYJ/Hb0goF2qTzQrL4LNPwcb1iZJ5V74dHrBrc0Te/T/aGKXar8i/FWxW+8+omr9yBTbcZv+G3ONvB764UhwtnEni23/xUnY0t1vw9igZaQ3evkA0A4CKGJvnDIbzzu7P0AktJ22b6U9PVB6fQzsQQqfC1dLoHRaDGxFCiphlTmDU+mT37STuuCjXbR961Xup+BNAikYOQv23Cb25rQjqj5TeJqz1ZEPDfzoLlUowi7g0He5I+EzB6X/+bBpiiPqGfk+NZTmTXK02LwJCA3a9iBxhI4BkpWd7FfHAOWGjpgV/8ta8JuQu4O4OhUVitDRJgKfu1j5OqRAJAl6YYY5q2LLl4/hWqVB//PxzNfdHt8pwDYjvIKwMzjf2t+CAu3fqM5WsXSoQ51lofrSwvXlnrO+Mw68ig39YAxGk+qNhdFK/133HILfXezW/6Mzi7XeDecPaJcWm7ITg+rAHLBNX6MLaC26YsSQ61zxX4TaPueEQxNDh5MEuHOkdAx0hncJ7KtE3FcYQTOChFIbl6qNSyqCF9F9kz3hK/q2hArzq6urtHObRSxDfvm42arL6KKqkTAEZE3Ufc7vb7kwbeTF42g2CmTsPmEiYYsAFQhbywAnbNM1wjZCmyA/7Oghl8IeIV5YHXCmu5VB3eOtdBnc0jaBbnDtYkUfmKUU980WaElHvASLhKOLv0fxc2wBryXQbM/B7/5xo9j2BI8/IypOS4Yz3ejMQuQpmOsfj/FOBRwqw5lldKYH7f5xg7eB3i1KWVZGNyRmlKVz78lOC/lGRfQhB5rPgfpt2LoF0eTcTW70YIOyR/Sygbd7Rh9Qhpcp87My5qfnvSvNxHB3Bme64syCHuT1tQDhCtXLzizFaac+Psv7aFWcORlO9PeRC00VBG/BTkJiZoYzBxILcMKCV2FPf6SU5WB6N1Sdm1GGRQqorwZ4N5YSc7zgX3S1QMGyWldzMuZnal21G5yZvCN6VzNlZ44yi/AlnPFPcLYXGehizdFeKaDNZAywJZ1788jEo4GF4QLMwRIcx4rjU0LmzVrN8MGDeBb1KPsYYR13rXXmAlTNz4DCgB8kcaCF4D5rmYwas3BYMgDmkfoEKvHeqXOb9Ftg3WiSUFWtMe2Jcc/y5x9Rg+X6hVmMYAMnE9cwA84XQcM7FQ9CgVTx1fl4qaQbP72TV4gwIquCDgj+GvBqQ4pijBqOmIH2Y9z3Qg5OONSLECcf2slRGvP938sX6oUKN0U7JI816ezUP8mEZabcmE/+CIq4Au/W3fw05UBXc7O73PC/wEpfwJu+CcBL2iYcFP2j7MSxbWLrjqCrikChT4u1zimanexWAIOENxXmKz3BZyNEdbOeR0BCwjoaDiKQk3weA/kyPOffldcNZh9zNAJiiNrAw36U1w6yCK2UlSt4eHpNlNsImKMqJWryW5kwFKWwRnffgyGAZdzPQJhAEp5uGcBC4UK5sDK7S/ePiwIjOqQwNzxXdv8mlO7esZDzFrKPofpMwI8dd2RJ0x2NyZKvSn1jAw8188t/wPTsZBjU3THLSoJotdHNs7vZfVmw5d/mbL+bHhIF+abA2+vp7Sp6czRmSlPURgvUcDAD6TqYUZluvDMKK7c73kA8VPrCzUZWw/IqRET4Udaet0tsk1C5dzbuoaAZNkIpLNvC7I/yesSfbcv7RGyLRXR7mjLXjLgxpP/lwo+Ofya2ofIWosyYvBDPHtJrKAhD8aW4pd8NgMFWASjDQpkjEOyV2STBnIaSITbwrUal93hRQphMwsnGLGkGZwcO7yd2IDHpUUqJbOGqqiqNP5upphTMJLTCGhbxpXL+N0m8bMhjb5ILzfdPUxuRc5zMjFcJwshJki9CBhQuNqJwcRYXLn6BiIVkt4ptA5yhnUvINNxe8EOCr6iqhxNaEch0PtvCiIZvjuoBSlRWcyGjlW7XT+m67hHbfmCgFSLai9NXxGUvQq0rmK7KCC57D3HZ03j5kRsihQIRmzRCyJgfKRe4hIW47FnUvBsqnBmuMILL3qNz2Wl2SzRIk0lvpRqXHRBJmJzU1hVIKMNTSeviCHFhjs5l53JblDYu8Vods3Rp42kRWe1VbvZDkaSNSziz3a4tZm6I2a7LF0uaN0Yw
*/