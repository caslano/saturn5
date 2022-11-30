// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_PERIMETER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_PERIMETER_HPP

#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/length.hpp>
#include <boost/geometry/algorithms/detail/calculate_null.hpp>
#include <boost/geometry/algorithms/detail/calculate_sum.hpp>
#include <boost/geometry/algorithms/detail/multi_sum.hpp>
// #include <boost/geometry/algorithms/detail/throw_on_empty_input.hpp>
#include <boost/geometry/algorithms/detail/visit.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/default_length_result.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/length/cartesian.hpp>
#include <boost/geometry/strategies/length/geographic.hpp>
#include <boost/geometry/strategies/length/spherical.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

// Default perimeter is 0.0, specializations implement calculated values
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct perimeter : detail::calculate_null
{
    typedef typename default_length_result<Geometry>::type return_type;

    template <typename Strategy>
    static inline return_type apply(Geometry const& geometry, Strategy const& strategy)
    {
        return calculate_null::apply<return_type>(geometry, strategy);
    }
};

template <typename Geometry>
struct perimeter<Geometry, ring_tag>
    : detail::length::range_length
        <
            Geometry,
            closure<Geometry>::value
        >
{};

template <typename Polygon>
struct perimeter<Polygon, polygon_tag> : detail::calculate_polygon_sum
{
    typedef typename default_length_result<Polygon>::type return_type;
    typedef detail::length::range_length
                <
                    typename ring_type<Polygon>::type,
                    closure<Polygon>::value
                > policy;

    template <typename Strategy>
    static inline return_type apply(Polygon const& polygon, Strategy const& strategy)
    {
        return calculate_polygon_sum::apply<return_type, policy>(polygon, strategy);
    }
};

template <typename MultiPolygon>
struct perimeter<MultiPolygon, multi_polygon_tag> : detail::multi_sum
{
    typedef typename default_length_result<MultiPolygon>::type return_type;

    template <typename Strategy>
    static inline return_type apply(MultiPolygon const& multi, Strategy const& strategy)
    {
        return multi_sum::apply
               <
                   return_type,
                   perimeter<typename boost::range_value<MultiPolygon>::type>
               >(multi, strategy);
    }
};


// box,n-sphere: to be implemented

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy {

template
<
    typename Strategies,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategies>::value
>
struct perimeter
{
    template <typename Geometry>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, Strategies const& strategies)
    {
        return dispatch::perimeter<Geometry>::apply(geometry, strategies);
    }
};

template <typename Strategy>
struct perimeter<Strategy, false>
{
    template <typename Geometry>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, Strategy const& strategy)
    {
        using strategies::length::services::strategy_converter;
        return dispatch::perimeter<Geometry>::apply(
                geometry, strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct perimeter<default_strategy, false>
{
    template <typename Geometry>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, default_strategy const&)
    {
        typedef typename strategies::length::services::default_strategy
            <
                Geometry
            >::type strategies_type;

        return dispatch::perimeter<Geometry>::apply(geometry, strategies_type());
    }
};

} // namespace resolve_strategy


namespace resolve_dynamic {

template <typename Geometry, typename Tag = typename geometry::tag<Geometry>::type>
struct perimeter
{
    template <typename Strategy>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, Strategy const& strategy)
    {
        concepts::check<Geometry const>();
        return resolve_strategy::perimeter<Strategy>::apply(geometry, strategy);
    }
};

template <typename Geometry>
struct perimeter<Geometry, dynamic_geometry_tag>
{
    template <typename Strategy>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, Strategy const& strategy)
    {
        typename default_length_result<Geometry>::type result = 0;
        traits::visit<Geometry>::apply([&](auto const& g)
        {
            result = perimeter<util::remove_cref_t<decltype(g)>>::apply(g, strategy);
        }, geometry);
        return result;
    }
};

template <typename Geometry>
struct perimeter<Geometry, geometry_collection_tag>
{
    template <typename Strategy>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, Strategy const& strategy)
    {
        typename default_length_result<Geometry>::type result = 0;
        detail::visit_breadth_first([&](auto const& g)
        {
            result += perimeter<util::remove_cref_t<decltype(g)>>::apply(g, strategy);
            return true;
        }, geometry);
        return result;
    }
};

} // namespace resolve_dynamic


/*!
\brief \brief_calc{perimeter}
\ingroup perimeter
\details The function perimeter returns the perimeter of a geometry,
    using the default distance-calculation-strategy
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_calc{perimeter}

\qbk{[include reference/algorithms/perimeter.qbk]}
\qbk{
[heading Example]
[perimeter]
[perimeter_output]
}
 */
template<typename Geometry>
inline typename default_length_result<Geometry>::type perimeter(
        Geometry const& geometry)
{
    // detail::throw_on_empty_input(geometry);
    return resolve_dynamic::perimeter<Geometry>::apply(geometry, default_strategy());
}

/*!
\brief \brief_calc{perimeter} \brief_strategy
\ingroup perimeter
\details The function perimeter returns the perimeter of a geometry,
    using specified strategy
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{distance}
\param geometry \param_geometry
\param strategy strategy to be used for distance calculations.
\return \return_calc{perimeter}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/perimeter.qbk]}
 */
template<typename Geometry, typename Strategy>
inline typename default_length_result<Geometry>::type perimeter(
        Geometry const& geometry, Strategy const& strategy)
{
    // detail::throw_on_empty_input(geometry);
    return resolve_dynamic::perimeter<Geometry>::apply(geometry, strategy);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_PERIMETER_HPP


/* perimeter.hpp
VrI1MSzZyiDJ1j/XRCRbGSjZyqS7w28fIFMms4su3k0A/R/XREyZstCUKZsKNj4Q679VDBA2rtgyjbBl3F22JrFnGuVRuGU+WRXeMo2wZWyNDr5hlRIvDStJUIlkZjWimiSnK/G/Uf4VqSyh/Ety8tZVGvmXTxftryNCfi9eI2hvhvZ8MPGxJ1S6u69yXqdCdMU0O6GBpSWB20tEAGcjmXTjHkMZFb/0SNi0O9pR9NjrYk27r+tU10vWZ2coz9y2XKyXD8Lrxd8swWLxN9fCovA3N8KCoBWULeafL/ari2OKwqjVMfEXlwgui43Ep0U+8G30cj6d3POteweVe/rWaOzXyj+Liu/tjheQHOXqDh4800FlKYN6ok0d1KRTDyo6bHllJBJ4Nt6W09AJCt8fiNyU01zhqOWv3afXadYvwiZOL1qNlELCT2xvWpAEgJzuFvS/TV2PxMnyBisFgA5+8B6dGhL8i+W0Kk+xnm6T+Z7v4qynrjLtevLrFXtT77nxmXh57Go2C8OUGF0OpQ8UOvE74vVxU0wfA+ujnI7/Il79C8oGWfNxx4tCLH7w2zht7Sj9D+yfNXeJpVbRpFlqyoZpruX5d2tUAmqQlNYIlQAc5um3xm/ZoFtDCkTRwx+9P7bEBToLgV7dqgJ9vgboM1n6h1cNuvTfWD2QfmPfKOIgUlxDV55aQYdr5DQ3LvkxrWESXANPPoDCwfWt4cV+5K6wP9b46x3W0sFD8ea/+HRrEXmW/OV49R89bX2UZPJF8eq7i+Osv1OMZ+ESfl689lKKY/fvi/E2KQ3sk2/iNPS26wwGVs0fjle/+bT1UUDIS+PVv9oVBzEfnGa+UejJ+w/GafYr54/GNzwa+Mvx2nvUebphIgOfL4pX3+2MnS9BZs9SyexwhcyaWuiYGNg8gmeK13yf43Tg4ZOKf3QgTv03Yuovz818JC7Nl2/id8draPFpAcFHHrfFq3/ZaeujSIUnx6v/zdzT1cd3I9+4P079V+aeejnGXz+0zRbFa9d9WrhQWMIvjVd/bDy4itl18JpG/a9Lykifq8HYekSmt1cavr1yUaJBVlWfH6a37gnvrnnwNL++M8IfTT+s5X8ui+Ivxh0vGlfx5mAceG8pOu081C1YyK+OV/9nRXHGi/yDZBTgwbHB3AY0493Kj34dp5l9157OIxLphjiEiyV05dIITaLHwafjNRlQm0xRg6/BKY5KqEIzk/Q7tPxma3N0fCRWYTGWst4y5hX8llHI8bT9MxSydsoWwfGEB2WaTjaxmTrmqC3GR2Rr+1Izqb9tMOrm3cA68C+bWe2Gp0cea3Tg3NQ6hOIp4APe+Rb+RW+cAXxQGD01+PZdvzMU8ugwVYFPZrH72SF5HKylc5FPN5JNd6AlJCtqYrMjP5GJHM3xQn6Xb7+x1KN3cHNIWAd6hwZmfnEDymjToY8bmticamI7Wdz8w+f6Q2hmwOZI7jI+bZcQVg9Dg81+NIT0Du3m7Nqq7uuagsbug6y0qvuXTWyGhG8tZKTeLjHB+MtyCd9YP7xFHIBMbOU91EdI2gdUtbu9+6CieXHnPFIPkcd3N1kyUJSeoQrSLd01Fouq6+B31sLPDKU6ytO3ximMYuRu1Gfc4EC78907AYqxDnTwBomtc4VA2zs8MOuLynnXK0hgszLYnCp/voQrbZUDHSW4s9jMKv+ap0VU60tgpBQyZtVacsKrVhT4Rdyu+wFR5TXS4xLtoOxNzCmVsTpUIb7U11yjk7NYkQwjPZ/vfACXQg0/9D4ADSzy0/EdUiHt4Bf8FjMbNZoyqcj3Nbv4kB39IeTdpar6k9hfQVR/6TpfY5VO/pY5mnx3QKKXVDdg/5SxQ8MOy7ebnu5IBKwZE9vxP2LJdFwIFZchAwiDdOmWIzqNe2vIuUm6EjBFB0shg7kkzFYxncGmS937yvZ07IIrOCJ6bxNFSUt3wiJA3RE+ZLuAN10L70MntfBOVPDDrsG5D6KyNrJqRinHsDxEqOc4gsm7AeseHV2d0b4bSNYkF6DFIkJhklM7/J2tSbn40R7q4wNN/2knB5ufSP/I0jJC1cK99DmaX4zc77+fGIxjjG1gnE75axi9wjqeXYRGF0Lx0ju0Mlzc3ygRD3YAPxqbl0/EwOdAPVqjf9XTgv+fWsZqq/xCmyevCcUdedI86PcjF+KdJxWh7ATqwXvk089Oyx8FEjKI7woM5iWhV244kQ1LVVmhOeyaKhLPy8bClswZ4Xhe6Wo8r1h+aHQ4r52tPUvnDlKK398Y1aU2Ppp/YHfy/ZH4XjvxIYWbv9muifFXZOeL/oWbapBAX+5ZMYG+OuPwcc8Un9WDuNih4GhVgMzXG06FzLMXhf7zyCxoiIfMr2tCp0Nm9aDIPP+LOMgcajtDZAp8PhL1Xo7RwLCoGhi+OwuEWx/5Bt6wRB1MJvIlw/ibQ/i77oAYEOP4kQzrazA0rKqR8RuUBs7RYM1PoTyXzuq9G23szoluXIOpifsHb1j+QxhbxEAXRCtQL5la1gg3QpP03pt8dxbqvBeRFxy4AtRY0vm2IyRbTAvMsbso4x3I6CWzphl2tLMTZj1b/SXkaCeT//qI8KNGjQhFAajLd2I1tEciFzjUuIXn3EqNZyqNW/hPIaN3pXi80F0xU1xGaizZvOyzOJeRaQUx90QAzG6gKChO7JviuRagQR62MGeQxfDDDIraWUiS7nwDhoZPQIyE5KFwopLpql3y3Vmjh0vwWSzBP0NWwmxaovVTMsTN8Az3370tFLwYbm/qFgzz8oiqPSao2qXyqTZinkun+49vxDfr423E+c6B3UVvRMH1H2wvPrw3zl5snn7me/FH0DfyThKN3zYNfj0SIPfjulMhd0b3/wGVm1cXD7nrdp6OyglhymDInbwnDnLPz/9xyP0R+F09AL+rY/F7++2nwu+DO/4P8NtfGw+/hh2nxe/qePjduSsOfjum/Wj8kr4O19o/1f6n48NKqDci38QPLz5ViNMZkSvR/z7E6b2L44U4TVvV/6NCnMo9cXB8w9X/09u5hUQRhXF8HyJfCrIkRUKCtuyG3SwzKTMVlzYq72vatuZlx3W1hcZ2y90uLFG2bVGQRlQUBEH0EhRBUF5ryzTTyKwerCgbicAHIerFzszouDN7vrMz20yvw7Jn5vddzvf9z5w5io44lc3P7jfbgfNhKQTvfj0J3mCPCufD5taD5+v2KDsfNuUDAG/hZs3O13X4zQ6AnwXxo+tI/Oa/VIFfdB3Er6VbGb9fQwC/T2kR8JNVf7vF9bdbgOdCmTPFTsqcqSMaZM6uWihzxn8LW3+7sWnz5juA6plNiupvWf7ITUj+65PTEi4rXuaz4kcbyTF/GoQaJ3LHdNkgx0zA/D3JMc2DAMKcVJmOKcsff3uPccdiW5nHNXjP28XRaa2UuMIYohMPeB77yv4uqe9ljDaxa+hFNZC33a0IHYK+FuRtqAhnz6rIi9vNytNNtF7vdxqmWgY9r+IlvgXahTkbJe1CJ/a+I4hnSJ+wmVA8WylSPP82aBDP41awn84JG894caL/DeCMjzbIj2eu/vkSXP9YpfXPv+lBx/nOabyahLxZCz3oRDWEPHAmQj3IPADF//r/pQex/nu7iqgHndcAZnIVBPPIubAw8XpQdD8A8886RfORLJ6UmCcl8HQgnsWVxPm9U4N88LUC4nmlI2w+oLA82/sAnnfWqj+/k+p1E5rWZ1SQpvVDZ1Vodm7uh6b17z5lzc6pVwA5xxpt6vX3PqPFXyvOmdl8t96IABpoJ9NZjgfIa5aLmyVPOEYGKJEvY062Hc7D/ZDZUQ5BvXgpdEjaH6xkxjQ16HyNLNdCxNVoYFb1AiJf3Gpe5BO4GrMQi1xvI6WjjexqZMzEa27zfUMU9zHbH0noF0HXD6Lr7HLij/ni6/UNs9lvxR7wGSmmo51/K5dsMdn2EieQTGrKWHx372TmWUj2etAm6YAYlex1dR9kr4HW0CGl9qqlvB6EfK7XY9fRs7weWkfP9HrcOnRr36Fb4wzsz6R28zY2vgRsnJwktTHr7wUsM3onYGMLYGOLyMZzeBv3MsOtk++Hw2aWnc8q/eZKgv6QbCb2z09U6J/794L982Nl/fPDF0A+u7FSM/0B1r+4+WC8jMTv2RYV+F0oA+cDkzJ+zucAP8sKrfQHqD6ZWnm4X0oqUUbSNShRMkqhEqVlS4QlSkIAABu1XOX62S7maRfVe9Y9JJjLjmnR/5VAMPccDQvTju//nkL931L162cX5ngIQR+LLSH201o45y0TxHN7elieLizPE10AT1ui+jxpMU9aiPfTfLx3FRPjfasGSHOLIaQp4ZHSWKRJnQDS2CUqxzuo37LvTziLSDBHt2kAc0YRBLM7I0L99nM7ALNbr7p/clta1k2k9U1P6E3c5hWbI/VoFkKqLxSeD93sAm57N49zU7b4+fhNOWkB2UjThj35OKT3CkKQsp+vR0PGZuGHDCp3fUM8T37nzTRV7psRp9qg/m+R0gVFuf7qwBwZI6zUBvKJeoQW/lqQD+oR4f3VMe2vfwFxULY65zsAgENLtD1tcFPXlZL8wA+sWM8b2SixADk8FiU4iUBOLOcRKhsjC3BsycIShCBlE5LVOB819ntgwHGgwhNubt2lWZofyzb71TbbabrbNDu0acNg7MUepiyQtNOBId5kk2b3USUp2Q7EFIL2nPuePm2Bh00GRr7v3nPPPefce879eO+ekzNelx0pItXb7/jyx+v+Ke+/9+e+/0YrsLXjelJdtPqreP8dLPr+u/mG77/3F33/fbjY+2/HV/R9QUaGdwevJ8MjR76Ck8dfBIrJ0HHkRieP00nvb94qIr3EwhlID+T1/Ac535+1Zr3t+/OF94gmPPc5ehmdUncFGmLNcr+abNfdeuCVXyjYMnhJXkpbWABBu/rjJQbNfwfzKk5PjjWLcSPzcn3r29dS9AKwewnY3YLsXho1ynMQWK13gkwu5XkQqqItXpAteynDZLsyuUv9envuDmlLSVaUg6czotySOdz5Sa4oZVHQXuxkhElPqm2/LPJip37BNC92HskNy9gq+t0n1LaF6Pt2Q973ArVZ+eZLVMioO+zj3OeYWyrL4FwMZrmhIdosb1G/1Zb5Fg8vx+cMTa4vw6AtEzot+65MyOtmM/OhXTg6m84zn/p3teV+72fLGY/d26dpQ/7b3DlI+/TeFkfS8ev7R+Pon0t9eSd0LgxUKG7RvpYLkFbRycbr798sMl5/bc8fr+ffxFv+eO/EMvgvGE5IMBkMKJd2ddtDeTSb0mobbsYobR4uVUA3i9b4Pvq6niKFVclOdUk+upxx9EnvtKhY1K9cMWxBJoFFB3DYof4MlrNshEzthpvRt89Q37RXUjkR5h4FDYw2a/ex1CdaMa4D8tCv6QKzZCnQRJ+uiYvEPE08ldXE4yPpYJBTNfHHIqJJayI606fzqE/TxFMZTXxO/WhdMU1cN1KgiZOFmljk3dTIz4qMkx/dPo1dm0YXR6oLdFHXx5u0d92avbuy9nr27vAdxexd6KepovauZdHM7N3za4tJ+djrqZuxd9FDRexdy20zs3fR26fau5uUb1yT78E115Pv5ppi8h09UFy+/1MzM/kuXFNMvosP3JR8r/1bsfuf82Ym32u2L0G+uv3Ykm8/tuTaj8X+G9mPDxcWsx8/PFzcfjzjmJn9+H5LMckvPXxD+zH969hvvFHEfjxVNTP78Y15X5L9KGa/41n5f993I/k/vqCY/C9fR/6fLJiZ/Bf7isn/qRvLf3r7bfppEfknrTOTv6nqS7XffZp9kVZfz758YS9mX9zfLm5fXpg/M/typLmYlL+z/6bsyys/KWJfXrh1ZvblFWuBjPH+VWc40mUM0PPulPrJMf2WV1ksyrjbzO555Vy43NavHfa/R7ehKM/gBVLbniv4Rkvm2d9eparLEMc3Xeq1f0ylQvQknVTl7mtsD4X+hs68kkptQs/Vm6e4E0v7O38CHbv3oTv8afyIq/V/ZDk58E8+I89jV4uz8KpxUvu741IGWofHu74Aj1eGc+CXXdb+kj8VwqMTKoBnDqiy8H/xhfb37JUCeBrg8O6aFOTQVRw1SMZenrnDBnbdw1Pvv1E/v3tHjUEpx3gZR/Un+aIWb+EohcdKgzybruEJP0ordu+sNCjz6FqWrbjo23pSvkhgTxrkWHkF5aW5ShnBtS9myH/Q0Cgmkr+DxiAG1BSm3TxZDj+7BwCmhIQ52sORbo6u4aLAhmImjRwJ8KSJw45Yy0lBHvP4TB4xZpKF8RX4BzGiRs88djNVfauRqUScN5UK6tuC0eANAR4sYxE6yGoOWFh+ThpRBNKFaXIXhbbjfLLGA1ot30KckCmZlD8jdyXLIR+fmniguYunnRw95nnYahk8gF7EIuz+eQBZkaosg0dRTbfxnqhVsY81WY1jPqsRSzu4fQ9bqZeD/ywyK2J7gI7QAE+Xk2748UQrAb2Po90c6eHoVk7yccoskFGyHLKk2QpHqpIgM56YSAA7H7FnMbMEXU4HePIA/HhiiC3C0Z0cGeDoDk6KcNBR2zlAcP5XSONOyOIxi8csjKlK6jGFeyJ6/3Xp/xYeG5qUFUC+QHt44oKf4uRbkHwfjw980kSqSBNfnIEenq4kO+FnWgZmAQMgDiB9HoijHsQB1FdhewEOe2SvfA19TkFXgnnC66bEuXms0WrcNCLkDxg0J+ZOep4+xAHw7r4aA3q4et24D+yu8jDtFWjIurtftMPsKf95Q8C6vbxnVkO30FvKgoNg1OK9xy0HjiL43uOygxqSCyWAquiZJQHUXGrQUCXnLD+Of6mXxzbk1+jnYHHtUKUeRpH0gLIoBDaR3TgDg1VvAePF6yGlCD/m5YBw5qjUrj5Vzm6M22nYKoWs220gJ58grRJ60R++LRQJoj/ZjuSbIfXoSuYZ2YZ+vIgruhnQGDYVxk8q5L8SIzS8boww/u+lIbPG/AWZbwiYLX99NDlbgr8vpRnmgOESxhTo/G/oNTzbhmw3XY2ziF1yKQtD4S4jWuHHrrI9rc6UkGZKffEKi7lnpy3mkLTK3LsYb7KFNTag2lKsNlUW6ocPZrgjnlgR7k6cCIK+0ibWsciqoNR2hqk7Qndxmv+zhj7rdrPWpbOAjyRHT1MD66KPACmagvWiIJ2W76DrOGmttef27aW0TFor9ODlQYHxYybCpo143xhM6xCa19zMTPuVBnZdWbGFaX1DtzmvNZDdx9FsWzZqkdaa81uITdcCyyyMb8OzGbKTBQKBudTHRYaeEpTbQ9C6A6bUiHrWrMVx0IKVmTEkokPyKPfDEJDarZYX3DCye8y00yBFBEsCI+6FmLcCqAtLgoMFtaVJZRnt4zuHWsDaPnsZ/dNb9l4wZCoZsNKTBZUQuFP1Mmj5cXQ/DQNHVP+qjE3aYuKo0BmEags1gCb2xXSA370TO/GkfJvGiiGilhfgTdOpXizLL2DkAcb/mGQYQ5kmT8y9hl89iWCkZGtiWGBxF1/VoO5m7baz6RHatex9E4xKmiv1pYImugwhdF6NnnVfvaKPWTsbszpATryMdM/guFdsLLQs65qVl5lHfz12K3akvVOyKU7abpbWmS2JKyBX
*/