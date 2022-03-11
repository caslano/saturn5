// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_NUM_POINTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_NUM_POINTS_HPP

#include <cstddef>

#include <boost/mpl/size_t.hpp>

#include <boost/range.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/algorithms/detail/counting.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>


namespace boost { namespace geometry
{

// Silence warning C4127: conditional expression is constant
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4127)
#endif


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace num_points
{


template <bool AddForOpen>
struct range_count
{
    template <typename Range>
    static inline std::size_t apply(Range const& range)
    {
        std::size_t n = boost::size(range);
        if (AddForOpen
            && n > 0
            && geometry::closure<Range>::value == open
            )
        {
            return n + 1;
        }
        return n;
    }
};

}} // namespace detail::num_points
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry,
    bool AddForOpen,
    typename Tag = typename tag_cast
        <
            typename tag<Geometry>::type, multi_tag
        >::type
>
struct num_points: not_implemented<Tag>
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, point_tag>
    : detail::counting::other_count<1>
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, box_tag>
    : detail::counting::other_count<(1 << geometry::dimension<Geometry>::value)>
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, segment_tag>
    : detail::counting::other_count<2>
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, linestring_tag>
    : detail::num_points::range_count<AddForOpen>
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, ring_tag>
    : detail::num_points::range_count<AddForOpen>
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, polygon_tag>
    : detail::counting::polygon_count
        <
            detail::num_points::range_count<AddForOpen>
        >
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, multi_tag>
    : detail::counting::multi_count
        <
            num_points<typename boost::range_value<Geometry>::type, AddForOpen>
        >
{};

} // namespace dispatch
#endif


namespace resolve_variant
{

template <typename Geometry>
struct num_points
{
    static inline std::size_t apply(Geometry const& geometry,
                                    bool add_for_open)
    {
        concepts::check<Geometry const>();

        return add_for_open
            ? dispatch::num_points<Geometry, true>::apply(geometry)
            : dispatch::num_points<Geometry, false>::apply(geometry);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct num_points<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    struct visitor: boost::static_visitor<std::size_t>
    {
        bool m_add_for_open;

        visitor(bool add_for_open): m_add_for_open(add_for_open) {}

        template <typename Geometry>
        inline std::size_t operator()(Geometry const& geometry) const
        {
            return num_points<Geometry>::apply(geometry, m_add_for_open);
        }
    };

    static inline std::size_t
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
          bool add_for_open)
    {
        return boost::apply_visitor(visitor(add_for_open), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_calc{number of points}
\ingroup num_points
\details \details_calc{num_points, number of points}.
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\param add_for_open add one for open geometries (i.e. polygon types which are not closed)
\return \return_calc{number of points}

\qbk{[include reference/algorithms/num_points.qbk]}
*/
template <typename Geometry>
inline std::size_t num_points(Geometry const& geometry, bool add_for_open = false)
{
    return resolve_variant::num_points<Geometry>::apply(geometry, add_for_open);
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_NUM_POINTS_HPP

/* num_points.hpp
CmWyWAFwqhphA1zu/VLN1JUVR0X+1c8oBmjqKbGLzX83MAzuzbY7xWCP+8zZvXHC144ATjnpCQ05y79oI+8IeMtfRYmuLUX7LYFfogoECw34PBVw6Tk6KISw8G3WWoYKAg9UDbXOFCrU8M4zF43IMBIUeEOyJMLf4Fjw3i6RiIrrbjEutSj7avKLH6N18d6ihxap8N7ghhbLGe4ZYHd2FWqOE/PgEpSpPcmUR7uvpi4JdrkLtHlQqH6bCzuWkoZ3boGSKUuUDB+8C2/SQXQXlm6v9c5uPKNO5sGzISEM+CoYvk+sbZ+XDeL36ihak3u55oqBF46QBXZPCGj1pWmOpe63hPDBZmIlpcXYpHAiqcGrU0M5aNIV26nBVHGlfQ3rSB5f9QqKSInHRO3ijKYpSb8NPnFdIQR/ruY4fyPKw9uL8BbrIUigxQ/e+R3xH3cyNejrGEuCSSGRvFwdrW7jHQblD9W91LJuIF9f5adGPhVcJtEhNc/Kny++Pje7Wn6sdQpzFenPTxMEX0XZeXTxoimWTyTMb1s+wZ/dXkDj1gXtGBCMZtzuBOqTKlkU0UycXNcYvTaTbh/eEx8PsjJmJ2KJq3+vnhhcJB8d8PRtzQon6U0J2E7cE4TglfW+voleDKR1eLZqoRRFaMSXSGUSNk78Wb/NSo5fK1NRDG4X4xhGWZiz9Up9Y7BbLQp9D9anFHuUzMXVMuXNhjpIZGzidbiJ6XMg8nF0H35FBQ+VfzucTnpVJ4uSfxtklLWjQRkm97HUYzbwni9Vpf9fpemngpzLu4oTrf/MUKJHzHiCvelmsa3MvMsTTA1BGcDpU5cUBdsFnVHXg/yC6aBt1X1nVeRw4QjDlbgv2cjMGzDMaPPbf8HsJp3NMJ/PK7cRCSb6DFu3q/vkGc/lLHtO7LGGrgtjPewLzdcvcE7IfTuGOSRKPeaNFftF+PbMAZPvbA4NXvwuZqtak79MvPxZjTCqK/ACupr1iYK9jEhQQd0Pay9HpjeBbLzX8VgVuZr8ltfcqABjHcyw8c7Tubj3zI7OGCuYSDj6Bi3zZp7JDMac8Qxp8WaTnR22h8POcccf8996dCLsVEtj+kIke9eKjciNLxaBqdxO+LEfmmHeev7em4oUo+LphKCkoucE0TS5Z/6EqnMmH6Sj4XDFcYvJmzP8AOPM4kLeWou5ZRRSpGBZ3k3zLCtOaXiJ6t4/dn0HOqqoEhYDi5LLDeQ0qtrNw6dDRJdRIbQTCqG+y5fYGOI6Rcec64mtjDCv4XjlAzHhzIKjgHnCwmYIvi5JkKmd+6dsj4Y3q2EcBbw8yKVB7MQGTdqrfyK0BlSrMDIbF3Vu/gzFZ8imS1zIwyM7OErfL+8vfoviZcpSqMVVXUvbrsVLxVU6wEe/kyX+RepPIzUSJ9+8tnlmEWvPZYYyqjkvxcdZAoZjhq4MKPZ7CBlE7pjTYT1RM0X4dfGKao+OKBu2Ma7w5+vq7SoezAbMYqI3rt2+/OVsXMqSIwuU0UsplqAql+OlihRJSq9SVgL1xLv8ymOkt4A5xh3Pik/73GtbHrKTWFm5aUlZ1WxzZ4Wv9/fm5KvPClbDnXStaY47V1M8dVLPGs0LYxCyWSjVrrNTM7kouWndyguMrJRE+YM7qD88Oyi0R5rYXByC83AI99ivCZx3qiiSVy04+5cpk9OEb6Siik7Nfb4XC6TnvD54mp8Bq0fjDdW2AyWLXaeN11Y9Ywgz7+zaad8mnvrmH4kq8/TiywgT9tdMFGe3a9Pv0aDPM5Md127mG8QNu0Y6Xqyq3xONTqUP2zo5IzVvzVU7ENKhbpouprENW6kDeDDkOrZrdd/eCDCxF6GePJLXNxQOPp/lXr0p8sy/nVa6OWq5DUzPGv6dJ9SvwVhhW6XavC37SN9eLm+dUNVQ5yQEyMfw46jfD2W9Y+ETcD15tK9YlCoofHiBjVlVOMqcXFp/nNd9NBBWgEGV4tJ1vDX52Nu/Rnz1GdhMk4XKbDUbXYczBi2ngqeanV87cjN1TeTPHgZUJJV6TZ1ma7Ap33y0Ow2cSDCfxE25OPnBJga6S7El86glfVAeVuqKK9Qj1SFrjFmKjo0bRo46aSAs1K+4wKcbdHkd9q+Ushl/vxxVLWbhEj2Aw1K08PCfWvR3EXShHo8awYQfNsmo5YMKzAEjmdarMl0s4E0fJ1aOZsdWexdr4zENWizE/d1BG8a0oUvsY8gYwOHiokBaaPFjMnJvGW7IpXZiD3GbuUpvMZueuAqYgB4d5Sa/aW5LcZ20NtozKru5S3SSZw/O5mv/mk2T7CGHBZhDetTuD55HXllFr7Sw6jwPJMdwe6LydvaQnhyIsvOgw1dm3La9D96Mu7n6Ag6ypS1CbpIJPF0icS8fXmf6zdBV5drdvCrVzxNt+T163gsy30p2REpzOJUvs3M6n3a/gmDes6wX6yiynkfc2H18s77Ol6ti9Xg/7wrOciqlpW0hrpx21E/dDXaX+IbvPosupMmcq92xk2v/mW4KxhLsH8fSNZx9in+XnysmRtc9PHNc7tz2lV2pHb7DU69Pp2hlPn/wPIa/TGEOXZE+WzjFGn8+vg5cmUX61D9MCYzIgOKhzJyn3SVsWf0ztC47ov3IxV3CK2txUlP7w2zbpaMefFACTSVl+inuzlwcCFpAjYOFijsefxEW16Py4s3A2TJVVmGVncsvZa7VabF3gaLRIMMGewX4ALRmNJBMITz1GHqJvRgq7O3Kqx25PXWq4v3+Jn332hnr6Z6u9W3utnZbaQut5I/+KtALXqi7ajggm6E7+9KwyzbjpqNN5ltlX1f0tFy+LBU3JY+y07Lpev58svpEeVvSgsd8d/HnqVzKLR3Q461q4Gyb4R9o7FN6uUx5bpnw6+m+Ml+uHH2Ijg6yorfz9UMZ21R1PA4otRbfuiWFp7Xdvptmp0kxLhp9aV+ElfqentBfHqIZAhnq6U7zmwb0BXMG2Qz7/Enl6sgvuOXN3ktH6r73bzqq6b7b2EGkSMQcyd1yr/mcr6afuWLi3m6siZx6xAhOLUg6UbqubS+VVLgPrb1WiN2fWMOQSx8c0d1J6uBbrhz3sjKG2bFtfOdKO/gXGlCpJ/MkFjpdzxahOtQ/4AuJ7JwAp/yo5q78UuGaucDNys4+sbDGScQ9YEG8EioHlUjGZVZcSrTMSe2laKgrZBvTYIcJmYOShwqMG4ocbu3fr7Q3HYw2zwlvHaJUIoM0zkCZmapUvexfsE5OV+3lk2+YtvTnxhfU8P75qzP+sQn2nwOknpKKu1/iUkg5hM1zpTeXg0FXf8kn/MYvu+9i/svGOoKfNTZ+5V/rwl3uDoD6amA1feTYNt1I8XVOHklUbYJejnJ2a/7I2DCRyfgb8T2YDb4Q9rIh1sWSeXZPa95HMfKBIMquE/XGI4zCJVutGPUzYZe7tWcM4+GxdIvqluvDqG+t7T7aht0b/+X9LVa48L5Kr5l69pOIiL7r8Ej7G4+bWAhBnr+z4eqYtAMnGs+Ugqa6Peq1wHpzkn9FHW2zjZHEtuPMITVGvkENQQqw/BnwrhHryqn2rnf9cFB5s5zTxnoTMlUhErSaLZ9tqdNxXOri4+0QoHVCX+OKB7J+4jPL14B1ZcTY567yB++sfeu+XK/01oISp8lllt/o4lHFvfVRpZXi7fEstHwENPDbv4qZysZQUe76NVzjxvJC+yIVYHgClbuXuJHFgcNAUXkNcL0Aha+GqAoUkp9s5//3cmRAJ3350pXq3qBkvxZQSDI9s2jjmfYy1FnTovvxm5a6Lc/LcaD7E8HMz/W4rzlVNTOa5NKTw+/CxSOqUuerFAWFHJ7A5emtECd0Zeat/XUkPWDed+Lrn5YZQ4nR+Sxz6sV9YVbks0vyFR4KZ75P/8V+PzAC3Xh7zGNaQgWBD0u5rxx/aKfdpO/FqYF62vf5Z9SkBfsNnGaj45Zxw2qOoM3+gfaKD7v02gQd1ZLdNtwJU+Tu1gxfk0bcXd5FBrpsKY1vms1zEQt/6c3d0QJbTsxCR6kWc+nLV4lJvMm2yV5DqsmysyMkB69F1c0UFBxzB62M2aPszx5YsygybpjxdcfgSv0Uqx4mKgWZxQBSXkHO8g+8LkAj94rkmObN+8qO4OXlmddXbk41uVeTivnMXKRfAr9SyDu8pYR0cTIK+c+fCTHNdlxaWD7zNvsBd5/wtQ+aHjAEJzE8bOt/F6/tbL+tXd/f8W+udliGX4c/fD43sv3u7kJ3LnfQDDdsEwTXo5yzo12/Xpif5WgaK56+uy/vQB7oH6nf8du4D+RUG3feSHey+bx8DLaqBnhnULffj1FWIp34uZNvVXYebKwRTnZOezzlO7Jcmo+evF40ozO+ja/mivYqrjqqoitYbr5dIosC/YN2rtOOsJRRCHyFHU5ixEM30KLVeKRymmqzc9Wz8si15lo1zy94tno+eq3OjorMBuy058Z02sXZFw4f31cuRzDAeSy7lueXddZ9r0c8R1Rbl7/2XXisd/NjqWxZfr9o3Q7aDq0vsCqJBbvrjuPXdzwo/fmzISBIuzdJshU9WWED/p3lsSiDlBfjqPbo5AK6dLi/H8JVzo7i3JdXYDzjN8BzXn06/ovb9K3EpJjMZCL0L2Dssz8p59pW2JP7WbUVwNUOeH3rcFZxNj1f1G2QizFQp/RQV3T11RSa11rauGEa2aI+t5ZSbL8+R+8pHQpriAB1Ub32S/79NPddfnNNVyb/ZOLyRp176cfSZdQZ9H2ElCn8dvnNd/DV+uVlZoPJNTvfO0a7dbNSCHosnVhM0CTZwf3h6xYKAVoiYtsd12Q5uMoU6cSNl0nF9fGmFdv1/eaarfsRulYY88z/dbW7rsW6h47V4307kCr+8IbnyfSuKhnk49MhHp3LQ7XlfAaRHX2hldKF+er9XuVTTV5eHB7r52OzYFMvqG4ibXHwMyEHpMj9Xu1DrfruCJg0wdZIq6IIzn42JA/Tay/NxnjznC7F2yov6jVDuu/LOs5piXXfyjArBWAjZt7z62tPNYdBeJYfYuxX7tdpTNTFI/P1N8M2p5PspYvQ+QZHC/wE036PVutXYcpHuSrJC9U1DvO1Sb9Yh78ji5MyE5MZvn6CwaMk6spK1kv+Li4iGxMud6lLL9Du116bBxWdrXo5I2yC6vX7pj6QE14zcPlujlJ7qdILN60bPmX397VyMZIef7xliAVcbIjiwVhLb4aGjiPkWC8z+hmVlG8s9saHx2vaLthlAjaX+OTljitmDenu3JYq/Y86+YmuHYLFF83X42srnhrc+cjm7foNntvRfuAH7AM1VtKdntfWLp/oi6VEupDcnlrpJwTvL5+YrR5PmkYS+mHc5feiovajAL6ZSwxXbPyajvz92IR8N5kd5leizu+CmLMQC4IlMNQYOjxc6U2flfNsfO0bbw6KEfvdCVBG+e7ulRvz/dfzeAxw0+yYSgsFx8N+MoxM4fBUVW92G/sZiW+GAWAz5xy4GMJS6v7hjqTxkqDhDOJkCVRSp+8+0sxhIcWuJRWdejAz8uYNWBdtmdcNiz/VXMaXhiW7I82/qvKlKJyAFRA4Do5bj2v4L0i0lpy/pu2HZexK+UMoPzwkZbQ30XwqNjA2ZlsmUFY3jJElqMby7TrM4qLgGIjVxxbjpGinSKiT405R3J5iNrybureGBBoi3k2q6Gw2vQpHXj493d7Oxm/zdvYxdLee+oQW1MZwuPzaG1dWB1xtMA4v11grNsZVNmI+lyYWT+x1I8sjVpitL3CPf3nynKUsi2o27yUivbCT00g/vd+L0r+fsXWFyju8Hs22UUt/6JW+xHbNx3G4mTyerg3r2a2/j81ya42m6GB466WbdPo+VcpGOUmJdKyo8E/nICNhxSkTWDg3Vps7VivmYKzePaM5Mo18O3b8LuWrS13YSlA9v07Ibdvd+z6IDug7g5B/VXlbuWnza2EYqfe+ikd/0XGlCScK0KNzn7VxGg5PI9b4ujUS5/Gq8uyRsBM6kXY6jkl7Wiw8T5wSh/ebPcu8C2JLkuKmlCq+WuzKO1GkYgVO6vPT2WwsFYgO18hFazk3F8XprsSqeHEj/VNCJbYylHVN/xj8fW0bsX19kBGu+dg93vzAZ9faMmribWC88srKRvAyvzTPT0HMj8FJvaNl4PhQuQITmjWqu5b5smkxemm19J6qdMGng/uutGG5olRhXJW7VEndeK/R8vKQC5eCrVfP/7pS7WVUJI/Bm8Z5Oz4RDO920qFt9/rsswKRLU9n0UEiMtNTbVbyPr8bKX1ptxJ6uQxw3AhwjTRdC+VxjOAk0H8FMI8EneS0Vb9bBOlZBhSO8GZLO5X2vHUn0xQeFGLSO937nCsd8KbzPmu+8bU/AI4QzFqgfVetorZYZx4JGjpju8JcOr4Xtv7m6ZJf+3IazTbDXrjSV8H6evHMn65LA3ZP18SjpRN72ueupU7Snldm1mai0njlHYd9jHLPWhT5Iq/POoxGS/GuEPhiJNvdHMVzgztci96uHrPWYW5ssFvStutoC33LZyFyz30nWr7Ob7s65SAmR3UHmJubEnqZmwsVFxwPGRaKjGNzKeQxc9OhUhy9E3i46ZVyUigJkFHJciEjRsYWF8Mehj6n2E/o6Vc9WxPee/qrrI68oa8oYGWlJUQ7Tz38CYgCGBKLtq1xx/Zskbm1jKCcDmi6/CNPZPy/yH0KKZP2Ler+bstWTHD66U3ugiqRztLptrMEgGWuCmVH90KcF8XcCPDm8la8Inxm1TvV3/nya5aAaclXRe52blfhsE5PK8BvQlEum9AR04nxG18jC33SjrtI3N1ggv+7mrpeERTYgd2JYQHiQ7t1A0IHTYInK4LOg9WHE9DxJwc6B+6E+kOgjyIA6o/OpGgNOYufl8yuDK5PTiDUDzwObAr8CK4OPwuhzyqg598ENALEA8EAqg/aG83X6DnUAdwM3IqRB5JX5B8H5K/o7wDkAoQOxALainlghliPdgC8bMDT66lz5flM7qaP+An/ugOEfRq/3wF0BEQA4gzxyq3rDIl4LqYI3D2bH61lDQOnC4Z4LmEJ9AzkDqIv788OzAVkDXIKOSuUi8oN3AhBwRj0DGQOxYCbh9ZL408LlALaCK4OV0vaq+lfBZQDuoqtDyqgxewpomMNUQsngOEP7Z8IDA5EA4wJccvrDwZEAKwNW4u0q+pfA7QM/AsmdxE0CeQDLw9eAFT4VM3f0T8EaAsYGxgW/KcHtJ8eDH96UAX+6QG0lrYX5b8DqL9W4fVRep+BaKMkHCD8n4G8gB5BVlH0OQQg/DWAsoFTQDvBarF35YGsgLfB3eF3Z4BwgL4M5fT6abtBa+F6O4DQgG6AYYHcCfSzHJw4xWkVCP3FAeo0/qmCfjastsf0f/etRG/JRW6fiF/BkbwTIbd7RTB3xH7Z0Qe6YfRBhO0OiN6WEb+CIHm3QXZL/epR+aVHHchPFFiD0ccetpspcgteQnxFH9iC0dcRuQsqcrtH/KqM5B0A2a39S480cIcqsAatLxexbyVyF0fkVpbYHZQ5/hmjb+Nnxyl6C0z8ao/kXQ7ZLfBLjy6wBrnPDq1vJWJXPmz3QvQWjviVDKkzoE3iPXL3SvT2mvgVCMm7FZLvJwHCQHqMPrXw3ZaI3f+fu1DRp+jtM7G7G5K3PySf9q9cqkB6xL7UyN0KkVst0dsm4lcU4ldPJO8gyG7JX3b6lPNfxO5evfTwvw+R/bZAK07IdDl6g+MskF1am8mJINzvwGpXmecUQiey83J43lCqZ307n4SzcIgm3O9kfaAAgRh6F4KjQLocFeRvIvtzL+RF8am+F4hCUh57OxDIhiMwLVhRX3Iej4jbowfsq6lxf/C7+glUHTrtz/90gqa5mXH83bh93eCKist1N6DXEqq+3ZiJiXPX9WXNhnI4Cj5yzQDsXIpJsNH3gId5jxci3AR0K7oDZAN8D4dWBt6Ig/Ry0zOuMBii4zg7X50WoC42MgEqGEL4H1/Bjx84qdARkGvDMBtBPuN+Aa2mJabeuOrVHwgUcFJ31V66fsIfap32DlCjiHrKB2EhO4CM8L+rt0dWyNUTHlfsWMYhGPJkVs8jbTKygO0MMJtxhJPdrq3O59BbZD6/WvyYgyM9+KedUTM34rfcozG1GNMv9gfItUmY1BOrEjUZokdbKxUPpVlyBHofhi2QPxPCYabeHpDbeNPSBIVrfA51p7mhGODHcvctOEKsI3a96kKad/3XRpCM+8EwBbfNHjkfwUhMMfQ98acwwWo9kEIxDyPfHJgNH88R87gIurPfO3f3VokCo2Bf7vK/BxPpZ+K+jLo/hPdGAG8kGkp8LSUCfrenQQuQd3tDasUW43o+GSU8S3KEh2pfr5LkReS5ubCPgr0L5CR3Mb663wG+VqS1RvdoF6nCqZjIOPW5r0qXnUeskhNkv/7sDLBKRhA3HMJUYDWnu826jDkn80PEpDyoE5mxfoOnLGehImEkSGS821f6q3sl1/SATnmvKMcts+hOruiBnYkeYPUEb1BNJYB9oqM76YH8u1ip1J2Fj9IjItkdi/CWGoaelVT3Q/MUybVWWSKwq7TCGwf0JJSbayLaocE5eYU371wQ5oWDZdi56wounXHfzUuXH2p2FwQS4i/koMtsRKayUdM08bgKPTx2mb8lBp6938276X4I9k/VTS28FJ7JW7izmLyB3fChXLN7InRjPKjAfw1L0Px6D3qIJSOVG/w7amvEtzosxL7B0FhNU/XIdqAWTkGqkrGtiNXuniJ3wnZQGl6IUyja8rc4cdP22u2EAqdU+uCWGqPbD45Vh0S6VPwsyzRNHOodvymRwfnvvI6Wbp32Ru6/9i2ZPT29tHRmsA3Z8vup48Lznqh/1w4lhdolFp5Je97976AuxFhS2M4Z7zZzwIAo5SNmNsdtddkbeqLhZhodiDwcyetTSICHreAmy/0pT1/WG0jknwfD3sNEaMDu1mQP1OED0aFRzThEj8vS4y0Fa6PJGZe/rhuJm4fHaYNHUT9sc1yjwc9O4XeV7F53jPGbAXGyF4mjfOibAZystkNx2A1nWuHG2PxWqfOEESZVUw29i4dwfiedtYeebO6Ib4WiUFEjPbNgirQgNf9sH5fFzknx2s0yy6M2qzjkC/fzUcdTB/yoArGEYpLMvx3u23sPBY4=
*/