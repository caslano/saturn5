// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_NUM_SEGMENTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_NUM_SEGMENTS_HPP

#include <cstddef>

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/times.hpp>

#include <boost/range.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/range.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/algorithms/detail/counting.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace num_segments
{


struct range_count
{
    template <typename Range>
    static inline std::size_t apply(Range const& range)
    {
        std::size_t n = boost::size(range);
        if ( n <= 1 )
        {
            return 0;
        }

        return
            geometry::closure<Range>::value == open
            ?
            n
            :
            static_cast<std::size_t>(n - 1);
    }
};

}} // namespace detail::num_segments
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct num_segments
    : not_implemented<Tag>
{};

template <typename Geometry>
struct num_segments<Geometry, point_tag>
    : detail::counting::other_count<0>
{};

// the number of segments (1-dimensional faces) of the hypercube is
// given by the formula: d * 2^(d-1), where d is the dimension of the
// hypercube; see also:
//            http://en.wikipedia.org/wiki/Hypercube
template <typename Geometry>
struct num_segments<Geometry, box_tag>
    : detail::counting::other_count
        <
            geometry::dimension<Geometry>::value
            * (1 << (geometry::dimension<Geometry>::value - 1))
        >
{};

template <typename Geometry>
struct num_segments<Geometry, segment_tag>
    : detail::counting::other_count<1>
{};

template <typename Geometry>
struct num_segments<Geometry, linestring_tag>
    : detail::num_segments::range_count
{};

template <typename Geometry>
struct num_segments<Geometry, ring_tag>
    : detail::num_segments::range_count
{};

template <typename Geometry>
struct num_segments<Geometry, polygon_tag>
    : detail::counting::polygon_count<detail::num_segments::range_count>
{};

template <typename Geometry>
struct num_segments<Geometry, multi_point_tag>
    : detail::counting::other_count<0>
{};

template <typename Geometry>
struct num_segments<Geometry, multi_linestring_tag>
    : detail::counting::multi_count
        <
            num_segments< typename boost::range_value<Geometry>::type>
        >
{};

template <typename Geometry>
struct num_segments<Geometry, multi_polygon_tag>
    : detail::counting::multi_count
        <
            num_segments< typename boost::range_value<Geometry>::type>
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH



namespace resolve_variant
{


template <typename Geometry>
struct num_segments
{
    static inline std::size_t apply(Geometry const& geometry)
    {
        concepts::check<Geometry const>();

        return dispatch::num_segments<Geometry>::apply(geometry);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct num_segments<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    struct visitor: boost::static_visitor<std::size_t>
    {
        template <typename Geometry>
        inline std::size_t operator()(Geometry const& geometry) const
        {
            return num_segments<Geometry>::apply(geometry);
        }
    };

    static inline std::size_t
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry)
    {
        return boost::apply_visitor(visitor(), geometry);
    }
};


} // namespace resolve_variant



/*!
\brief \brief_calc{number of segments}
\ingroup num_segments
\details \details_calc{num_segments, number of segments}.
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_calc{number of segments}

\qbk{[include reference/algorithms/num_segments.qbk]}
*/
template <typename Geometry>
inline std::size_t num_segments(Geometry const& geometry)
{
    return resolve_variant::num_segments<Geometry>::apply(geometry);
}



}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_NUM_SEGMENTS_HPP

/* num_segments.hpp
Nop/EXe5p9Rx8m4Z8iz0BEbLLzp88QHP7GQBTE+YTKYncVJsdOqEtng4GGSILZnRMBhhExBT0Q7xgUeMDkZgE0b7w1ApI4PRyDTycgfDkD8h2H910f+iaHSamfDhYOifkPK/K8X+i4JHXz3laN08v5HaLiRcLUaz/0ZfwCYYiz3/0Z1sgId6Zd43h6hv9KKk9ZUvK2Nua6PBc7ySpFHfpimHV3GvN0oq+5aKKzUftWiRWbBbsOPiYtr8ekxPiqcgSOHmI6EVPJCJYOwCCWu7/TgSXT2gUftHz+yXf5IWfmtH5fU8ukq6WAbjMbgM37NsiRdRtbIphHTvV1Jy0r15AIA5AAgyk5joWvoZZPFXaYa5+AR9qsC0z6sY45+8J460Mzy8UtdHWET/TZHWFF1UqeU7Is1gNViXxq6U9/HCji/TjZq5M+pLLOcplYtZelQbkhcmjGaVZZYlgdu+p7gkyZE0El+QMVvQhyIfaGXZDvTdfhIkA3/42Ch0OSsDlBFJn8je5lxU6EbZvQDPzmTl/hMMBEwrTE1FjbSkSHPIebt/irt/ckQlBcymx2trioUvr0wphrWQcUtgZ5rVqX66BA74U4Gd9/yt4t/WNVE4Uh9rekQMcKzb6ifUk3nBz6zWvytmkKnQ6uS6L0w3AWi/zYGcOcBDBjJmwFfcC+l2WN1dP4HNlfoupNRflbrYCd4ajIKa1IZNFZJZ6HCUavy9YU/6S0DmY56BZZ0RQnwiOtXl/2CiQe6O1MjIjC7RMNcbHW5EE51UPKcebx4NcXx67uU6A8rZm2OqKWAtg+gqY3x/WLi0mr82taEK4pwikCoptcoll3ZXr621TEVE311pkloy5Mn2zoU/MqIdt09HBVCwkvwa47o7F0jpxx4PnES7pKahFyvkWZTLwb6KemlBypMG5ZKv1yYkgBmfsXWMaqZIjF2GMrUHAVxW+TRlFCNdU8cgUO+SADkXZiBM91Ay32BJsSmE7dDDzPis6s1R+VRiYCsVn11oXsXOI58qgn0qHAtcFph+USwVJjyQZwh/dpUmUOsKfVFE9lEd3f+xokZh28bZj417ziv924SqZgca7cn8IP3QFvbvvFvIim4+J7Rf+akFZF3KUSvIDY8L4cq/VYFH719Mcv8XtltcddK1Gn1Tj1jIspb/cvb818SFrKZwfwp/4Dxb7dHK73x+lmnxBkQf2OKeg6EqFBYfpvN/58EpnUiA9HmHB+UNqPDgdT6ypSu7krmv12K2bdHf1jDqfetEoktfafzCNW1Miu+njcTNj/Av77pTPnqh/tPWUJ7u7SHfUtVZ8XHV1JNtUZf/ukLg5/O0hu+VJM7smyWgADSKU4khenrL+NrD948CAzX0C9MT6rxff4TpPtwvaJpw5SAkTRtX2A/u2JAf1Dsz0yk3lCLxnwyBNeTGLbot8ZtezFLmPKkFdgx8bk0pHyfzNegTAAAs/9NX3hQSyl+Tkx9yfhOMMinsnrKqpHVelzSqnoszGoGwfhe/joxF/CGbiohIXsBV0f25DRxml08dZ1j7g86/b8u68h6G9x2YGTmlVwpZF06kUe98iA8ShTOcBH3SAtdREiS0iWPUVkOH6l902H66wlhLZkeJaxV8uZR6388AmiB2cuus2oLADbu55lKZC6lABflB4ZsPKC6AnUfxyZMD+mqntL/iKj5xn4eybpQECrdbBlXpX8wSTLKiYEzqE8pcKtaX6NczzV4ZC5GcurPHwkWLR+no5Cphlwr8w40jl/GOZm/FumYIT7lr9l+pgbyaQE6DThkzNLSFitB3iUTbEUn1D4pOsa2WPgbFcwQe0n7TGLml4CyZpe4XHskEetS1J4Mf1m7HR0SH7B4Y0ie/PGCR7jJ5olMhdsqP908E1ukKuv2X3qXeBEaODtTbuJDtOke1qI5zOdKrUuP89o2jPXlHCbA0U/y+uipNDL+yEi0+22HenOTIkHi6YVGikt3NCjPYiXKnxxhwYtHvzrImmzEOFjT4DWYHD4lnTE2m802gAc7Hj++M6mVsL/KTp2tGAtx/jtSwJhCfK7xh7UFVfJPncotueXxgTUcCNH2Tm1xamnUZ5+MOAofaVSp1ifo9h4DOM/NNrJrhbZ6lrOyB1QVEiZt/nwtaYS6ckm+tZmItyPBxpO6jnHvvuZCWNAW1wSxk3M4bQouTlqi9ACCrFmXaplmqKDObvUQq6mQ0AgIvFEDjcCtvLFXJMSEI/jCxtxWlXKSy1fAqvfzRfGEFcWUbGOAYD+KcAE3UEoB0jGW/2tOsocnFOZGKZ5Mo9lCv9ViN7eI38bpfSLscIkl6MGIsBcS3SVri6Ds3aMfFCu0uRKnXe+Q1qg+nHhkBXNbEmbpzeqgkteZbP1FMs1kF7pGCM75IdhpDHWVZxRz4RrCwpDErsLN3cK4VzwasjBktThY+Ps7hB8H7Wy0PgrRHYroxqawjt4lsKLM9c0VfcXfhz0TP1uc/tIX7SYJ94ncC5oKd2fg2PYBHemqAaN+gWEnwfNJSqiYH+OaeiabnhhXWn5Oa5cXkZNiPEn4V4ZELcKfPj1PanK2SA3CvMIHXFaU2AuaZ3BAdniPItpikXlIeOofOHwp7RkWhHUwqtjaKdSe/MqIuScxG7QkurTr3cK7sIsvDeDr1pN+1RwJbuwz4LykmN2ztOGJ5oH1i7yZ8WrcSjjvgkcuSiqd+aQpXMStffZQAyyLMR5wrlMRkeFgHuJNsdw5xy5OTd6p/IvQUG4MG25BXjqI2IxTNynUpe9y5Qbc2cGh7laCQVmW6rQ4irgyRBIWhT9Hk1REFJJFRU3c0cvLTsr4CqkQ0y4Zikw7IwdanBYZm9qSm1lrVpy/tnv3XakgYSQe8F53M9FyncYAchmcJ+vhQzjTZMVjM4VeBPB7Z5BeR0itZw33XFZxql4siQkHwEegrjmPXkQu7mhUfGIPvkQhHR1DHxUd7psTBYmPlk2AxAkBsFOQ8MKlGB7THhU97xgYwT2OfqfCdI9Me8mZNeQ5rPxlF/EM5rf3+fm7woN66/zP9ubgXdAHDN5CHwYfxfOc4P3BkIH0NFoEP5Kdhj35UmPPI4HHnKIBdFUa5Xdi8MkPQ2565q29oxt+dOoxAcoRyHMWPYN+5zpOAQtsxWmhxaGoFHfk5KkAgMireW3Df+2s5QtZF1Qb+Y/DV3uxDhKSbFIdA+uCJerEjS0aLA0g85qa2Gkt8BtsUqtqqnCjWIU68AKEltqB5qxNsGXmGqCafEOKj6ZeZ2btEEYhrs2fX8GqbamV2pGtmM5/ptNxcd7LUm5KWv9bJQXXQM1duRRDwE2dpF5tSC6gbPirs8mnobA4b30cTOAkGPdE06v76XPN1SZPadDLKBHWpibVggil12UR4yVHjCs1IJCV5RgrK1YBethNA/vgo9mse/3AixfFEcN1EpsDEGZHGCJmWZEzcCSIvxmcmtI7Al3DxE7INzecfyM3B4TJe/8WJ5ZNuKROjTo2lAuw49PW1PZc/INtsJZyMsMupr+RwI0ZbqwYUq+8zB5ngmDcJQ6mpyihmOmc++Y3hpqkTsW5rOSDEzWcAn8qsgWwA03mpVrTpwWC/yQaXPtrujsOroy14aozz4awfWdIrfJSnxlINdBufaV1mykSti30OxHzomaz99t6imz0+bz3UFbz9StMLRWaLXWD78/YjvdnFxVwRknzD0TO6gMwGvxhNC8bJ63mFcsZrrBSEyT47K2Sz6b2yrUuPMDxYm0NjLmai0KG4k+Ppa3vG2aZ5JlQjPR/9rqAlzpGLjudeMc1zR9fGwsnmDZcFZKXk3zdW12nZ0ID5PewxLXN9bkqQz1RV+hL2X62aJn15MGdlx7tj3gpWu9mr8wY0noNnFB6tNbi6ip1Ws6aAYitgZ19iL9UDD+9OHz9I+dtlfx7oK4SrkE7Vz6nP/K28CdXwS4QrMhOWHvafZvAIifhPIhe8lX7sj62XhUfBB/Twy9KzRHoPD6irOx/pj99iBV7em+9Qb4fAeEZ2G6n3ZmfbzfSsOKdinSZ6EYU2lAb3xo+E1XWsJwDAH798j5zuDoQrZFgmdNh5JBnMg4lJiAmuuOCTa9BAwEf6e57KQDb8g9odOt/UTMqt2dlAl97cxycmNcHVC7nmq3kPnsEVyRe4CKPFGbMdoCxsijkU9a5JoVqOwPIzRNBn9tuGggeu8MvKqExP89Ewske4PrQmDUWV5PTA9cYprqNKRyzD51iWToIRbFyQrclVibCFxTPgigGSNOgRRVHYArUo9tyPR+FPRT3ark/ZSwhNXKFMrUAyELmQ5Ud0kWMy3J07pS3TU3PE4ppAtB/WWKbITqlMMEd4+SVROco8S56KElKO2uFd0gaPP6UAbemzJ3KRZFBCrTZnoxIyLZaPCtmsWRYJrftRVD6flpM74KCLSO7xGpFcU02t172XeX3O1pk21At1la2NhdbTeHp3KWMvts1nEKPxjSIZwdTbbAdrHhxEB1o22CYezCakSSYAvXfmlp/4vmfOVg4xaDsJiyDg3NvRHNIqiqcA40ZEVWwkHr5XmGEKbyeiH2028/0SZdQKVof/UKH6SFnz/h/EnCTLcjDF6styrU2gOt/8avPeOtdD9ro55BWB7Fej15mND8vf8zrGRTVXJ4thOwT731EFtOlQAFNzCeIoFI3oKCz6h5SRGDYqHTZBsa77Pb54pKc3/3dRx4JnpgJhz5LdNlbhUr29OEOpJ/TuqYALqsdLcxFarsHT+sUPHfKpXPy1oQ7JLxt+n/rfAwxDHmfHUoXjkg6KwUQWvGRtyJ+/+SUpJmKhM9JCchKwCCL0ZvSyLLgBhuDXNwUziWzJ78N66lOv+GyEwYDs+9kbSw2+4xBOOJ1KSFaVEtrpGeqJEbSRzA/wC5RHLo+8PBq/tV8LCqcW2NL9bEW+WmsM11VMBkqKivkEwaUtYV7axGY+vbl4vJjWyEU++E6W640WogDYLqI+9AusOd7ACQyHyYcySGuzR5nJ5CCvfo5vIlnoSfbNNRYlZh3L2FaRqGLfhm9cHPWYK+WUGbvYmCJGTwukaYtX/GtndZg9rMIxq0RDq+KsJ0g6iJw4aDOYpLD5sCbKEEreMOU5bE+shYLOpKMHJwGuR6yqaeAzrfjmyOigeOFHqGkJTE9cRo8rAmN+NkY8JwbF6TB2FSqhYmgINJeToT7RiFmLSB3ivJX+nFAGUudirl58GnkXOXXoEs864rYiGdEgXVwsuzpZQK6o4bdm2Tq95VHY3T+9r9KGi2iLe8gD8vsWVMRvf6bUZMxww7gYhEiH8V+s539brjZA6kGWUpoJwwLn42Bxzc1ecdoR/9aK8NMa3U0gN6Qh9aSdPQeYkEW2TsrWmzAzJrQGGy9cBm19XnvU2AUE2v5O8rrJ8bq+bju5eeLFj41DOEU6HLS1LtwCXUyZDaKzxzAFpgEbh5Obc55TdaC8w/1nDXvTXATAofJz5j3td7sBn4POUOJ1MA9pLQPeVJb+iAQYgo0mw1/nddu9vCjR6cdIH48O0SHKY5I8kMs4nsw5roZYHyUshFhnn0DMBO3Uk3RaIJc+j4J9Fzfk1wsAFxtH76iqSlfsUOzWFTocDz0G1MRiAYNgVdcqroEWSuv2Xpa+E1XEia1WBF0ifvP2tvX3xfHj88bAfh9q2CKEvXdAXG/AUB9nub+rLU9xdjX3R1wDl2/UnW5goTS4tn0U8/lM1d2eOFrK49+cUT9v28ahwoD3zsRpZFvGKWbMOPMXaEreANZ1BnQztau+lkWhU6NYD+xe88nh2QkhaO5zQPkdWrpP8maUR/7wHwl/GJ2SrOSBtoNxWuRZ5DXkgAcGaOGpcWtrww/QJljmQU2tYebUdC1HypAoQd+NhEAG//7lWjEL4WnShtFfbRLgipcanvwWZTCf0AgyT+Y/f0cL0ZS1LaOft8BJ30idzB2XvpxFOY58kgdaTKzLVR4VBQ76q4cJdm9s17OtlB6bbkkqPbg8690GE6WO/0MTL1djQPW3bTANLrNCr3vGKaUsD+999x4ED8uGq2BAvEJbxpigPJ5rBAPBfg4AafqgnhUbWd2Zi7RujTpnQkMF/MoucFYd/A5LJ6QrqyYYnMnCxnjgfBiinM2pzBL1G2J60AQ6fXQaquvfPfmgKnjIi7w9O9lZP4asV9CumHFLpWP1nvptEqm3yyneoVgBdqDEwTaM9wTb3pZ7K7nZPI3+ZZfcIWYf2iBcOiw5ENdIHpg3J6e3tYCjTD0ZEjI0dpQU1DMevIUNEYbDsQuSFXXbW+p4GbMi9bHaiXKiTDEN5ovyqRf7G5lOHOsMqHtQiPGD0ozWud34FHwbVT1sreWckbYz+hsFkx9Vo6aYCLWIcH70b5Z0m2r5qviDPvAaPRGYhJzjGC8Uz23bAgkxmVHVjebniFn7HcerVHGyrEVb7UX4KcEGTepOskZfjqK/v/82VbQexzONeuw7UCgU+3zevKeR2QsL7w4TP0Kt6Rkr+zU5LICheoKAMgAHDRqEmZulY+F2oE1RK6LE58jF9okuV58Nd+Twh6be25avzqDS5foFf6nmzRikB+jxZbJ8bw0SIXjN1VP9ZbusYsy60UN7GxHrPpPytcbtsGJ16VrcMkk3fO7AOuMCfSE2GDIwSeTpcbINNmGqFWl6XfQPFj+3aclws0ryXJPvvJ1zY91sGWF883alWoufjrPKotS4zjpXvkjMwUJjY/7nUeyxifKuLsiJKcD7uNZFNgp6GJMXmJ/TPdP1aEpsTkf72/DXYbHPDDZsb0mgn4EDv5NOE+hFf11tNe8mMZ/tNIcB7MDCJaSPEsJqsP3w7eEdd/XhnfOOMoQlPRdzW3fPIvtJpV27ZW51icfEl8W4EOwtRLRBVMx8JmvF563NwWTm2nw8LLGQJoun21YabnptF9mlfOX2rVea3+xQ0iZZF8L6LL3Gw59s7Y5Ct6uErfYyD8dwmW3SpjAe7Wg2T8cw8nGupRiUkLtJMPmQUSVB5S1LfDOSenZ766tN3SykXO6mddr1Kt12t2yCspUGlf0yZtMszOxoJkHvA1NVYJSZohg9AHnw2bbVoxu62N7MEWVDMjKCZuzdMqyDeIbn0P2d4hAtxGSdwBlPrMQgoSVTm6j76sa9oO3FTOE8NH313NdG0LFDXKmMlcT8o3QAWeHEJ2Yj5j5KrMZQplgqTT66uXTSgXh398cgvKyT8Wtz4ggxemJYQlEyqIwwfXTAKwafofxOg+epamPfybSxmnbsx/XXxfLaeDvjvP9iyExAeRVVZfzjRMPm4Bll1s4trAWEdvNsT5iiRK4BS70bi/yqfBf/rqbOXh2LSROB3x6rBM1YfHJ8CxbsoSM+d6/UUPpyXzgWmmYAMYHSosaKhcOySnl2WSOUPGiaozy88l2a3Cr4qZlITF+vL45tp3QnB9oa1txMMV+EB3slgy3vSKzDdASLqvpW1sTO+MmklrQP5gDqEg7jfnWKLPnB5M1gL1SPUDUoc7eqGnu3SrE6irb4qlRa8oYHRmi9+Uk61Y1K/8S76KbK5HOEEzmOXlBkS8qtZ2rYmD2+5rAHXN1V9zdv9+BH+cHG0OuR5i+96aNa7UmB7u/QT/OHyX+1p7U/a3afXSHYgXiyI5oZKAT6LKbvAYKrUhQgsXiL4jj9xbeeBBucPDzOJGsMDeqC3otIM8c+RSsQ+PZovDV60zeFDQL0Nt5eDszcUvJ3xNNxh90sJVQq7b7eveNoC6MF3zkehju9Z1ZB3Aqbl6hY8BztQ9Mt56SKz3RoVxy0jmcY90odVnKr5VFbad1riSPMtb5pm0I/t+n8+5jxjM9TNr1WR9KIPtAsJyvAVw1MbjhOx6EbnXneDrkaIwNkJ9Jsbe8uyb4z+FLHBuIiPdPP1t5HDaEzD+6fg78TivMV/oWaq4h0jdUnYnTWLu+hRUvsyq7M6LBNtJpEa+WU0v0nauTx7SqUUVk8Rc6/YA2ixN0nIqUmnr57F8nsBgtJehGpRrcwr71MaZu0Ev8RholVEqTSOPCj9f5QCZ3SXeyXmphk3k73VSH8TJuVj6568Bd1xcNlSLmb57UDrO1/H83vjbFSYY37TS0M9Uu/qv6uGz/vXza79v4CzZRLiTaroKy0vRxa8wOmT+X0PqL/35EhXhh1WY2N982LrGvWsjghaB3XNmXihAyyLDrypIKsg6IkqXNUuTNHqiRt4t9SIenx0gcpWixRE3GjoQ49UTvek7CmhsRkn+86F5fTnJIfMw/fOzw7394jD6c6N54v61Y1Ex3bG5rSKCN+sdA5aM6CUO452E12k1OwtHBcvb1qAtDPrQzhxmMXhmzrktgN6p3owrWxQVt1HUmReTAFsFjuvh4iLo0cdCCiL/v0hU6teIi76UkiRrkDv5fHa5IYwx3PkpnQwQb0gJvm0fOWtB8mQcy1Zo0giCHl4DBXiVhXKdU8OvGDSO15E+SBYDSZfCLZXh14ktwcg0wjDWofI5NrUbNrYvbUnZ3YQxYQdasXFy3SxbtEtCPOh6+nOR1BCmqzZ6MOJSfNFkz+9YCtRNAdfOK2KUbk58oqVdBWc35evnMSpK6mmV8yUdD1KvqSSwP4yMq51R0J92GsbaNcZH45/cmdxfTn/EdvDttbvgb8fg08IPiMAVEkb+EioWhHlhp8k+H8UIiNrGa0UsXGhZZXsaDV/v10HteYJ9aIhtUo6183xMGyaRsh11GW1uwa6Cu1sSKAf3YuOfsnvgvOgXDB1qJvWV7rsKq/vRD8Y4D0RI3K+A/EZBXfJp+N4Jmix2gNcVEVsgoUCiiHZQ4iG2MDi44nR1lxkvQhrRcKC+mmaKu+4Bg2XR+cTgY04h8LK3dumaGzeTOmGEfavxkWZUfvQ73j46JfMOvEhbL+LFUWO7sUlHk6KkdG8JnNphvObIIb1Fwn/Rtt2KyBd383ZomjpPXH8N59WiVu9kfAUgKfQoPGcUUsPFOZG6FqSTnzT3qJAy7+9kA5vuLZ+d+0IZfiANsMlP5OVy5GQJYaZsnYQeiqvkfoC8PF+lcQl/QMGdKEo4V9WeJPp6fdzg9vSOSfEjnMQMt8UdgCBJ6DgwPXTifx7UzJNa6o7wICg26Gpxcmfa7NF4VGEYqP8ajlW9z4560DeITEFIKAFps2tMafcUDsAZ0wRhHnbwqy82pXnhi0houzOYc=
*/