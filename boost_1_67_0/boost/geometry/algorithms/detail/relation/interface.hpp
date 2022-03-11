// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2015, 2017.
// Modifications copyright (c) 2013-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATION_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATION_INTERFACE_HPP


#include <boost/geometry/algorithms/detail/relate/interface.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate
{

template <typename Geometry1, typename Geometry2>
struct result_handler_type<Geometry1, Geometry2, geometry::de9im::matrix, false>
{
    typedef matrix_handler<geometry::de9im::matrix> type;
};


}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

namespace resolve_variant
{

template <typename Geometry1, typename Geometry2>
struct relation
{
    template <typename Matrix, typename Strategy>
    static inline Matrix apply(Geometry1 const& geometry1,
                               Geometry2 const& geometry2,
                               Strategy const& strategy)
    {
        concepts::check<Geometry1 const>();
        concepts::check<Geometry2 const>();
        assert_dimension_equal<Geometry1, Geometry2>();

        typename detail::relate::result_handler_type
            <
                Geometry1,
                Geometry2,
                Matrix
            >::type handler;

        resolve_strategy::relate::apply(geometry1, geometry2, handler, strategy);

        return handler.result();
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct relation<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    template <typename Matrix, typename Strategy>
    struct visitor : boost::static_visitor<Matrix>
    {
        Geometry2 const& m_geometry2;
        Strategy const& m_strategy;

        visitor(Geometry2 const& geometry2, Strategy const& strategy)
            : m_geometry2(geometry2), m_strategy(strategy) {}

        template <typename Geometry1>
        Matrix operator()(Geometry1 const& geometry1) const
        {
            return relation<Geometry1, Geometry2>
                   ::template apply<Matrix>(geometry1, m_geometry2, m_strategy);
        }
    };

    template <typename Matrix, typename Strategy>
    static inline Matrix
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
          Geometry2 const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Matrix, Strategy>(geometry2, strategy), geometry1);
    }
};

template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct relation<Geometry1, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Matrix, typename Strategy>
    struct visitor : boost::static_visitor<Matrix>
    {
        Geometry1 const& m_geometry1;
        Strategy const& m_strategy;

        visitor(Geometry1 const& geometry1, Strategy const& strategy)
            : m_geometry1(geometry1), m_strategy(strategy) {}

        template <typename Geometry2>
        Matrix operator()(Geometry2 const& geometry2) const
        {
            return relation<Geometry1, Geometry2>
                   ::template apply<Matrix>(m_geometry1, geometry2, m_strategy);
        }
    };

    template <typename Matrix, typename Strategy>
    static inline Matrix
    apply(Geometry1 const& geometry1,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Matrix, Strategy>(geometry1, strategy), geometry2);
    }
};

template
<
    BOOST_VARIANT_ENUM_PARAMS(typename T1),
    BOOST_VARIANT_ENUM_PARAMS(typename T2)
>
struct relation
    <
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)>,
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)>
    >
{
    template <typename Matrix, typename Strategy>
    struct visitor : boost::static_visitor<Matrix>
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy)
            : m_strategy(strategy) {}

        template <typename Geometry1, typename Geometry2>
        Matrix operator()(Geometry1 const& geometry1,
                          Geometry2 const& geometry2) const
        {
            return relation<Geometry1, Geometry2>
                   ::template apply<Matrix>(geometry1, geometry2, m_strategy);
        }
    };

    template <typename Matrix, typename Strategy>
    static inline Matrix
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Matrix, Strategy>(strategy), geometry1, geometry2);
    }
};

} // namespace resolve_variant


/*!
\brief Calculates the relation between a pair of geometries as defined in DE-9IM.
\ingroup relation
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Strategy \tparam_strategy{Relation}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param strategy \param_strategy{relation}
\return The DE-9IM matrix expressing the relation between geometries.

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/relation.qbk]}
 */
template <typename Geometry1, typename Geometry2, typename Strategy>
inline de9im::matrix relation(Geometry1 const& geometry1,
                              Geometry2 const& geometry2,
                              Strategy const& strategy)
{
    return resolve_variant::relation
        <
            Geometry1,
            Geometry2
        >::template apply<de9im::matrix>(geometry1, geometry2, strategy);
}


/*!
\brief Calculates the relation between a pair of geometries as defined in DE-9IM.
\ingroup relation
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\return The DE-9IM matrix expressing the relation between geometries.

\qbk{[include reference/algorithms/relation.qbk]}
 */
template <typename Geometry1, typename Geometry2>
inline de9im::matrix relation(Geometry1 const& geometry1,
                              Geometry2 const& geometry2)
{
    return resolve_variant::relation
        <
            Geometry1,
            Geometry2
        >::template apply<de9im::matrix>(geometry1, geometry2, default_strategy());
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_INTERFACE_HPP

/* interface.hpp
Jrumqtk5Qr/RxSgu6IMZWGXnQBhiYqJhzM/DMbLUB6acZRhQfsqpCB/F9DIfwlpQ3BTC3iN44LsDKBfsBbEIu/iikgK1NqVgBVaTG43+BdMz63Bm9TrOI7xwJtIl4Tuq9MfD3lp2XGd5sci2VknKARzKgwy35cFcbrR/zkg8Cw9K89cVa+hqvDW4iq4tPjYbD067bCBfxpzhgX01o0G6XjTDJlkFc0LDzO0lMGHxTtQLml5azM5HjGFYB/HM9ThbZACqYnYkI7qE4jnlDjnmnMqrrcClB7/OepD4rBXnmfWSzDE0CYpwFlYll5FWzXY3v2PCd6OP3ODBqoJyC/gQERYkiflyzT/yV97eryYe/+2dTu9zZWI7GZ93oqJtmk5tBoKLAoqSaXSe92yUiJYdMbF8tSL4IlqWWKY/pjGV2HOKcIzTR+Y+u14aVCYC0uhsphoUPQ05U2S/fiPN7MXKwSKkqKo8oEDC1kArEE3fOKQ/Y4lw5X8vjzeIzSI/GVDT7RZC7MCPcdI2yj7wybxV/5QFP73polDlv+qi7/JalKCL0m7VW9Hh9rXRqIRflnfy4nxa9423/3y1JEb2frffeHPAqyZbU2No8H0J9BdkilPo3UJ34+U8Rqm/R5M4WBQNuc2dOauJabbfkkiZHUuI4A8Lhsg0oDUWuQy6LsAUYIrOlcXzV5SBLF/b2aQWvLQVpv4SS1exYfvqR7qtGTYO5zvEJlfnIFl9rRkAN2VW96kZuxeyyPjjK9CN3+JlV+ygfaUQ/lrpgshFWNrxQaBo/IGN6o85iT8zO3FSziM1fVhrDQ/+kzkhJIAnOnVoaDvbJ8t+kAh4kYJlQJvpDSWrqEDGtCzdkCzXkaIuY3gxbDX2Eeaf8O/FsYk5A/mPoglUqmfhx5cW84lS4klNTlXkPmmw3hiRfNcYuROoTXGfhIRg11ldpirOihprqcHCeexxhC7RtiSpnKEFbEoCqgWEuKaDhFeT7yV3DnNxVqw6i0XHlhqj0KoxHQYrJisU6zqJ0IPRAo2ICwfehTsgMlslyyzwArW4NJg8IiohDCkaMRnpkg+mQIl0oYq0uYzxsw11ljkB7WHDKqbuVKACqw6NDEOVSVmtBKsyROJ2u7V5vZn89zXXFqEH9vzrTErYwidHhkwzadVZFWP6U2AnUHnjQYxUUikReXN9t3Wns2l0rAbs0j/Eymg3Am0BZmQVJoyI0Ard7rJjLRcJiNDZTFtr25dRIP/YMR+gDAhWb6Zi+T8pqteHX8KROLpZ5dHYCR/OH5FbEGa2SxBLUTDrX8ULl9cnxGHfL2qUOy9IjfPRUSUqVk2X9jHfs0DWUnHPsIV36Wm5f94AqXZOTDz5yKOoS3ft9CDhfVdetmrtveKDuSv3xjDZ89hyV9z9u+F8pPYOlm1jr8St7SxnwVpTnye0aw/3NCKXcpnqZHXrWuDlQ3gd0dJ1bSU9bV8TDOpDNNnVtnTlLD7wa8eGmCAE1OVdy4UunpxigVJl0TbhYoLIvwGpN6/BsFMD7H7WOmjz9HjUEpxkO3wElY0FsLufupIohk6xy76g4Vbeg6AGfcAq2+NBBtJxB/Cc9eGzr56PYewgmwweikyb/aTGV+fAxy7QEs5qFvZbqiMieNfV6oHsSOVPxMkdu7JjcziHWGP0wOh54eh3H2g9F4b6OtLtnoxGGHPMO+S6pYeHEOeiqBOBd8AfPtyE/jS58wUdJ71RhUqqHB7UrjhjQlSbrJc/jv6AtqQZW/PZ/e+q+NWXs0vxRAt4QM3qeJTtRstcve3G6erlqpk4rrvNRguX5Oi5Br13nvPNoIf35sNIp/82q1i1aiWfii8y68lNVujLbFAZgeJqMhqMzwRrfNJgLVgkGadXdfLBH7O5gk7vnQnjRrVT7Nnck+nSJZvsNr9lOHSEHD2duVOjSJICCv2PhXC776HbeshcoPTOEHfi4Y1ssk4cwGEAAKBfwL9AfoH+AvsF/gviF+QvqF/Qv2B+wf6C+wX/C+EX4i+kX8i/UH6h/kL7hf4L4xfmL6xf2L9wfuH+wvuF/4vgF+Evol/Ev0h+kf4i+0X+i+IX5S+qX9S/aH7R/qL7Rf+L4RfjL6ZfzL9YfrH+YvvF/ovjF+cvrl/cv3h+8f7i+8X/S+CX4C+hX8K/RH6J/hL7Jf5L4pfkL6lf0r9kfsn+kvsl/0vhl+IvpV/Kv1R+qf5S+6X+S+OX5i+tX9q/dH7p/tL7pf/L4JfhL6Nfxr9Mfpn+Mvtl/svil+Uvq1/Wv2x+2f6y+2X/y+GX4y+nX86/XH65/nL75f7L45fnL69f3r98fvn+8vvl/yvw17blZdRtUjMntyDT1r0AOepJHktLqaid5bFE9QJPgkv2UqOeSalqBKUsqWNFp9jYInj7WZnoBwnAFDPNcZknBx0iDHtf21/CiCb+6vKOMKkwEOw7I8WKgmiFYVBXKL788IF/EN3Jd19booYLzjmucso0w0xUH52mT95wXHS2aMoj8nzUGUgWcy6glNMj3FcozfjuyY+SvE/re3T6X0SkrdkybIxyROHWFbtWjr5PQNNXU0B2T4+M7tfT2hxeIxbtMLewVw7+Oj43VgMdkCvpWkEWhlqWwAZObFuDz7GADk8M7mNq/G1eFBVcQ45LpnMLx1ef238g7FHZgHmOoSQtZX/CXXsKfrxzbhL7yPL8scIHb2s9vkyk7FFyOBR0BGWEbDVTW0DH2tmLdzPUQcNjsn1IiKvK6t0Fu9hRpECxuV250Jyl5mePYT2r6OYmEFQVtwJjY69EmFqPvgTPm6wT58RQE80OqkxOKezKAp7Tg77jMA89v9hywOZWWeC4jIDfW2DWp2eDgJZ0NSq77Z6ld+/OIZeOvCx8tRZKcgfHldbFSE5JMST2VyqYsZJgqkTRxYivohclSK0EGhZBTSK+WQJo89K+UsNSbXgc/BINyjB3mDHr3yrz7DkSALOZg7hsxCmRUinBOjxbmcH7r6LbRaOw4wJuUr7VSaCD/uZp5cKnBEU99Ok36k+KmEpMUjaaNaWMgF5rPSZwdosb3MCgByFXuJwfWrE7bK5y59tH3+2Ji/shEDqzhfuBqolhTzQii5/7aSNvcERbwliwc5kAqVcUNoVilpiPKDPOCnDuvPW/0uY0gPstUlEKpcZQWaIHkVjpcXrGQf0dyrmHdgZf+fp742NG6IkZg3mwp1PY4DF6cODmhy2OO8oOnTQ2c73uzTqwq6SLqZ+xmmHjaBTK6BLK6GBwEubBKPFtd4r+on5d0/9gxePVc7PubeQuDP2Fx0ll3+cWol8WHeBFsWThH9np56Q56A6f2Eo5CR6NCC5XrsgPncPDo4Dic2Mmz25Vf4HQRBwLXhxJchh2WofYFbbnbnoQkx4xlCrRAoLRSX8G/KcEuMO2AMdHiHPZoLwysRKUwC7TtdvIYCcW/BbFtaVYQ5J0fDLGMLxz2+3oQIPXWR0/b7TUufh6H88K6diPPWfWeiqfphgum8ulHfVB4jrKoIXgq2OcL5F4/vPaZnLf7T7C+0cpKedba+2Ze0wjPjLCn7LJ/14GBhtFHZkelqMeu5CY0+RC6efOoacus2ftmekQDZoqYWNu2CZtianro1nmdvD7mXVEiyK4VtDEaNnaSMivICZtlfdMkMDYaeiztIpV1BCJy2gLhN956atDVudGqztYWiwwE6khi1b7FT2lz+VfoRpyFGRyWIi5s2YRIFiuZhT1oX3DpJUo7RidhiHoMTfJK4c9oFy2efFGSr0JnNfzB8kQUM9NUbDSDQMOqtkc4DWh1o81B9LjDoeSdk2SDrDuzPG8qN/D0VpsQDs7XlkIU7x8AzlI02k1cjEM0AfEIz7hJiEwOjDpXjugMHD4PqcYy7CFiEenXeeSf1mVRd/Mc3XCzuJacpiOSDtST+Xj9nXTmCWCzrK+D2/ZHbNme+HmLY/o6qlHYZlo6rAVw4Dwqb0gAuXBJgYyMLpU87iQ7+UCYOCxhz/S5RsBwfqta4yNuFEb3lVMCzCH82fDMJRzRfKRRImrQJlroT4w1nXR9KySfhYj3Upl8zsufK6XX8lo/ZIxnEDjLvWj+fuXKDtWwo1/zQkUNiBCWBqiKLIospA6iCD0hieFp+YUWoDMaA07w96tZ/fIjUeWTtiVoQCnCX0eHDDkBpLsxfmGL/WlhqGic8a9i+l2Bj4boOUZkDOfSGULquRvSpUqXzsMbnFcHZSdSFDBqIYpI5PP8ZNk1v5osAT3XCfXZMLAJh2a25EfXmeGqnk14Krl95uDUDrzJwnectgEQR8iaMbHAUUYN7GZjQqX1ipA9Dr4K6QHoNj9JhwjBI2B1tQ+FFsXpoosGYjQYKMQGKgHyiQ/LATh0WaZHyFQfDDVRJsxwQO7TE6SGJ9sjpcpHTSKHD1JUSfAyUZSp64tO93jFQzwub3xFSraX14QGRokKjKMQqgUAAX2VNLFEGX92XaWRVEZtklGm+0txYFbcfvZsIuaIMoqsoqxSwEoEBIVwFSwb/JC8XxDNk++joPkvYLQN8BTYIB0C4BJlgyh0J5/GLFjyTIG7QEYnCho9mTmS3OXROJZdkSXjOclaIJg9cZJchj8nDS8C7w7PGs0ZJO70qokiSLMBEGTicKu5E9ULCb4jhExLtQfym4Rqzi9GZzUX0yYrpi8+zdJ8EGwYP4EkzbCIUPmY1gyOZ4obVrx4/DBNGoDR7oYiQioGKhYYLhDENg9HbOPFpxQC7/eZ6mxQIIAL0Re4vgQ2iD6LlFypFISedYPHHGQRKI9CC0ayCpEloKkryfoNgFbPtMPmJIcNZqPiZAJzUo2NckR1Ro0jQkU0Ww5vUv2lPFScj5lhqZkLBkmkCwpkYhIWi+1nYV81w2IVFJn+d3La/MsMDQgVMAZ8XL2y1IiQkHcYIFSlfYjmcX7Ldvf4Y4HFQ10dJUd0FTMn5byZQurwHjZRWTmJ0kFssY0KglJKzlDINQMGBxxYZZOEnFwStHb1/n11PPUr8yKFRjW9ZvY6km2H+TrWYX7sSvGd2/AeWkIxxeg1Enckg+e4U53x100Towill4qNy0QqgTFv3ykIxBafMf1KPzKFXUwkhayP+e5erv6iMZzxlWfK6CSsOJpbO3Um3jYRZmbP72AseM2Fp5iMK3SU9bh7xIgJjgstawjR6G+t91VWgxNFRNCpqiJbGo8XRm+D2NozyUBP3lJPrFHva3vR1e+nyZCiLx6ec81pc9jqhWICEIoYIJwtXChyFAk9sbKymcc2aTiR6qgHnwU1OSFu9tLqxa3dtV5I9R8sRGx0l0iJsZAksCSZhcEdFxfWZ/0CgzJv9Cgoi6b10fupD1bjRiCQB5e9x6iukKGlDeB1YFw0NTC4aD9rHJYNEaxmU77VRHi3b6Oq6SeullBGSwLJFHiS/ULbt0GovfTbBRptnVRWWW04lyxbmI3IVGrpht/P0/UovxHzs6SdJfS4EvhwawAkXzs4wLF8znMdLSQomVSKn9B/lMSKsykYeuqh30GtyH/4SwqBZfbRBQ+0SollKz+QwD2ziWtYx3CiVG8oBXbo34UXgTwJ0+OrWrX4R/OsXo/OVjEv/dzQXXG3D6LwgfuzHkvam5vQMXATktvBKtE6Z3jL/fU46ZeR5FDcI5NYxN0xi6Sz2vZ/0BZACwG2KdXEbUXUPU7kqJqWtELxF46PkIbE49PR+xzi1Mq5NxTmdB4+qVkzUmgWAO0IZzNyBw7EsopMX1jTdlayZGbNeq9harvdv/Fh22E+bMq/dlSzoz1P6gpOAkBpmRKXQFeBANnLFjUbOEKjnoowJvy1N0KcwMEEkBnF0JAC1VSgY8Qt9diq70DcO4J4A7HdGqgAUMmNPqn8DrOzgnOFzE1SnwiDX1qKKQik5mlmhI5N+7xyaZXKV6zI2Lmfs2LW/P83gNCCEZHBBevY6gWk+tgUy0aICKq8LTk8e/tmfpeI0JgNidqI2ScUSMUQ8FFkepfnxu7teqS9WQu66rMHjkC13nxCR0QbR3H36A2GQ6WnWD11wngC3jmR4YzeQ3yH500029o2KBMKc0UmG6aJT1d2iczXYnA6qllwalrL4q1I4+OkHnjRwyyggQQJR6qsklGg6uKBYO1TkpGT59NEsBqvKEQ32eNzGO+lCF5GF8CgQ6lHKwnbpczYNneYujyuE4uCZhn+3GsO3ReKo7DiCBUPjzhxz2DU4Kn/Fy18xEh85h0PTJlRcHsPNb7a84RRY5sfaiy7ebRj9P+f084MVCme7KTQcN+vV0v+6l8MonJJIN9UY5nX/fl7Z2LvjdVEk6QTiFPAFd3PY/uKDj3Nkm5O35fChsAACz/069ew0mrLIoMSQPrCT1YA2FXg62zVt7zpKHuzcmqwZJvdxg91SkO+OhxBPn7pgys219+dg68T7LANeaOxx8eg6abN8EUNEd9dWvf/E+eSSBLyO8ODHo0RdZPsr2E224A6VDrADmaHY24TF7c1Zq4XboX1Cetxpm5b7a4PWO1CbySfkYyVT58HUmiTG1oe1PsyuJD7ydR7sMLs+UQ4paFolS5EdPtYcaU6UAq2DYxnhOYjwHnJxiDiDXXaAqZUi8ojOckT3vzIsC45ik0/qCARB4kA+EKiyB3BCZWae/rMUdZngjanz4DVAA+/C5EyHchZpqXi7ASwqb+bnqyUKSJtOrc6al+9RbR5BPTKuyE70bKyhtrwV5z7+5PqFhfSXBNpdmdcyRljiS+Eh9TavUQhgYOVM8Nb5k4mc1/lwxAQ8unZxMTxf4+bliv8JzKjE/3EYkG0slMAQuqS3WjgMAPtx39hQ655mqWUFFJ0mvx1owgSACrF7uRPq44WfGJD7TYcNefRIVPCDot89TPtB5J6pCa8YNd4zSEOK3PghSGKEzbsalfxcILlLwXMDWIgLUWCMVRmnWHdrNtUSaEASDlkBw8PMQ2l0lHXKC2in/MuZV6M22GOWy9j5vbw+UMlpC1h5PJrOanzcED9KIgfAMGOgU0NexjLEc6sI8fqInoM7EAAoBcjGTHALgVAqVtCO88u7h5yKKj2FikUYgI5XgdvJ4hs5UTWgcmhWNtgxj7Z/NnsHFaG2tkgB08bssmOLs7OXN62vm0U97TIqwvSWN0jPwwwKa/3RKIgod7DcRH2cHm8FoT6XUrpqyByYRHaTirBc5rpDOyvpFsh4agK6heOVsFdKCfccLgBPmwM9CUI6bvHeUdfP3HN+/2n4Fvv+nc0W3kmT/oTP0neu6faDJk8LAj0SEVFXMKXURPINxt4e3l7sCxAS0omNxMKMH0feA5hZUPbuIGrGNcEJoUW7SIz6aUsMLGEPlrPqAxtZCeWkxa9acGLwtg+4wOCw2foeZsi/gykDyP67tulyzA6XU6WCI9wON4wM0MVfqKDVTSzA5Z70kwU700816/0UG6CyUyvVQzNUzfgWlQVYmhlmCxe5i2iGoKB4YBx9ooHcUhPglK26A2WesYaByccCFNRqgM5mzDoVNrYEUDtPurWrdg+/4T2DZgC6+3PwrJgWJGuXBYQVNeJoGVlSWVNwsPEtpJabhcyemyWrk37p9MgRTEKxHGhuNGLm91WgXLXcEyJHMpbMQJ7rPuqSUni1oR3e6xVFiutnH6VA6mEq59RKyVzptzUkTPJXL3c029rGJWRFJtHE5yu/Vx+e3tluCtJmboqnj16kPKeS4dLg5YxHATUoltHicTYYZ+tOqUh1K5C/Ws8mzPLlza9j81z5BnRKrB9+hRqomtvju4KE86Es3+ddLi1wtd7hwwCGx5I2b0ycYYmfazoS0WgUQiKSGVA3c0+3B+qNYwFogS25935NtYZjOMs1pcryJKi6CgPUbreZUq3lutAm13U3/3p2SPr1wdkddzy8AYU4tTsK3TbIoj6SfvaBo4ZUGuUHgJHYWJgyjnokNFwphpjYdz5CJ5XFmMXBAqba3vYkSU1OWMhLo00peYDtAFmMcmfeE5lHd6w4/CXrrVWcX+CC2EMYLFxLLMfiIvv/HylW/k4tMtqrHqyKuVcEpsMXrpjMzIZowgnT1Wk3rxdRFKdv0kRg7Pw3khdhD0oH9hryyJ/4jIJkxHt2T19qVz0YREO12wukwHQ9fqxJoAsp9NLYfyuVxm4RQ2ovf0Xq4f9ttquO/4afSte3J3fbht9vk067zqSHrEdbVNFyZUivpAHMrl5cOrR138sPaRTwpmsk4o5SLaxH5GnnPxK27VyU6RV1Db5qSXU0TvCmaI5CqTcuE0b2rVLESxbqwns//jrB/JaG9li6UaxfxM3Z4BmYEL8+QZXFQ0C9j8qllOX1RUvaXlOrwzQ0D+8xypXPxv6hwGtfLAf7b3Z9D5J/zkG37mCz/3g5/nxd/j+ud282ev/f8PP/3ODD+xJxSi7KLf/Xkg6O8vPSzlC4qvVn2E/s3EK1fRMRIi1TCDgfYkvSdKHpxXw2CBRmMrEB3x+eg9Cp5CXkoW3QKwEg2Ed+lEIg4KSLcGGGrHJPbRbKHJFoGtReX694xdbTDFcPB4qKhbqKzkxOniW3LnHfDoJ1m58JzZYBhVYAwzbvQ8QR3Vtoet9jW7Jvn5FgXTNwcORnp3DHujyiq+xvrbiP865rYf7nl38DzeiEyAaZw81YBXOCr6boRIrAY3XA+9YyoOCGogQ+0A7jzm1Qv/CppKJqNHzLJZDWhhfOxkHVoEb+SeYOpzY3HPdeblvYwA8WzSX3Lzt2gxGpM/PbKgAMQUkapeaJ89oKRKQkY2mgzegjSl19p9WP/Jhfeb00vnF3Ty6ktUv7SQW/eYTZMnptn3bO8iK9JKBOuZm707eCqkuj+AuvDk9TqmtY466NxhfBc5F4tAj/hXGKRBUTJsVM65UA8hSRNedBeZzpf0/k/ss4HCyp/deffBewc+KgU4eMeBSMcMtbARworl70uXoI6g2XKMtg3zJ9sM4T6sxj7hgmfufFVgBgxNtqqS8ra5d2TxkG6kYyXW6hunNatB+TIyEpNyV7E60HRuBjyuqpkTIWrCJhiLYnAcVchWdBQDpioUDBwqkPMAAX4JjVpcEz4CIERwhoV1OJBwwK4D06yh5ttAlYpKlZ2iCXSBt50R1Dhi15NsGP1C8J9ce9/lWGTxOU24LfeZUbLof+XB4cJF4srG4Cddut/c5tnCA2xnXU7Tkd3Hm2jijmB4H5w=
*/