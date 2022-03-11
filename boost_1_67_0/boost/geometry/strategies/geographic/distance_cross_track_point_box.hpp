// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_POINT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_POINT_BOX_HPP

#include <boost/config.hpp>
#include <boost/concept_check.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_void.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/concepts/distance_concept.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track.hpp>
#include <boost/geometry/strategies/geographic/distance_cross_track.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track_point_box.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/algorithms/detail/assign_box_corners.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace distance
{


/*!
\brief Strategy functor for distance point to box calculation
\ingroup strategies
\details Class which calculates the distance of a point to a box, for
points and boxes on a sphere or globe
\tparam CalculationType \tparam_calculation
\tparam Strategy underlying point-segment distance strategy, defaults
to cross track
\qbk{
[heading See also]
[link geometry.reference.algorithms.distance.distance_3_with_strategy distance (with strategy)]
}
*/
template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class geographic_cross_track_point_box
{
public:
    // point-point strategy getters
    struct distance_ps_strategy
    {
        typedef geographic_cross_track<FormulaPolicy, Spheroid, CalculationType> type;
    };

    template <typename Point, typename Box>
    struct return_type
        : services::return_type<typename distance_ps_strategy::type,
                                Point, typename point_type<Box>::type>
    {};

    //constructor

    explicit geographic_cross_track_point_box(Spheroid const& spheroid = Spheroid())
             : m_spheroid(spheroid)
    {}

    template <typename Point, typename Box>
    inline typename return_type<Point, Box>::type
    apply(Point const& point, Box const& box) const
    {
/*
#if !defined(BOOST_MSVC)
        BOOST_CONCEPT_ASSERT
            (
                (concepts::PointSegmentDistanceStrategy
                    <
                        Strategy, Point, typename point_type<Box>::type
                    >)
            );
#endif
*/

        typedef typename return_type<Point, Box>::type return_type;

        return details::cross_track_point_box_generic
                        <return_type>::apply(point, box,
                                             typename distance_ps_strategy::type(m_spheroid));
    }

private :
    Spheroid m_spheroid;
};



#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename Strategy, typename Spheroid, typename CalculationType>
struct tag<geographic_cross_track_point_box<Strategy, Spheroid, CalculationType> >
{
    typedef strategy_tag_distance_point_box type;
};


template <typename Strategy, typename Spheroid, typename CalculationType, typename P, typename Box>
struct return_type<geographic_cross_track_point_box<Strategy, Spheroid, CalculationType>, P, Box>
    : geographic_cross_track_point_box
        <
            Strategy, Spheroid, CalculationType
        >::template return_type<P, Box>
{};

template <typename Strategy, typename Spheroid, typename P, typename Box>
struct return_type<geographic_cross_track_point_box<Strategy, Spheroid>, P, Box>
    : geographic_cross_track_point_box
        <
            Strategy, Spheroid
        >::template return_type<P, Box>
{};

template <typename Strategy, typename P, typename Box>
struct return_type<geographic_cross_track_point_box<Strategy>, P, Box>
    : geographic_cross_track_point_box
        <
            Strategy
        >::template return_type<P, Box>
{};

template <typename Strategy, typename Spheroid, typename CalculationType>
struct comparable_type<geographic_cross_track_point_box<Strategy, Spheroid, CalculationType> >
{
    typedef geographic_cross_track_point_box
        <
            Strategy, Spheroid, CalculationType
        > type;
};


template <typename Strategy, typename Spheroid, typename CalculationType>
struct get_comparable<geographic_cross_track_point_box<Strategy, Spheroid, CalculationType> >
{
public:
    static inline geographic_cross_track_point_box<Strategy, Spheroid, CalculationType>
    apply(geographic_cross_track_point_box<Strategy, Spheroid, CalculationType> const& str)
    {
        return str;
    }
};


template <typename Strategy, typename Spheroid, typename CalculationType, typename P, typename Box>
struct result_from_distance
    <
        geographic_cross_track_point_box<Strategy, Spheroid, CalculationType>, P, Box
    >
{
private:
    typedef geographic_cross_track_point_box<Strategy, Spheroid, CalculationType> this_strategy;

    typedef typename this_strategy::template return_type
        <
            P, Box
        >::type return_type;

public:
    template <typename T>
    static inline return_type apply(this_strategy const& strategy,
                                    T const& distance)
    {
        result_from_distance
            <
                Strategy, P, typename point_type<Box>::type
            >::apply(strategy, distance);
    }
};

template <typename Point, typename Box>
struct default_strategy
    <
        point_tag, box_tag, Point, Box,
        geographic_tag, geographic_tag
    >
{
    typedef geographic_cross_track_point_box<> type;
};

template <typename Box, typename Point>
struct default_strategy
    <
        box_tag, point_tag, Box, Point,
        geographic_tag, geographic_tag
    >
{
    typedef typename default_strategy
        <
            point_tag, box_tag, Point, Box,
            geographic_tag, geographic_tag
        >::type type;
};

} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_POINT_BOX_HPP

/* distance_cross_track_point_box.hpp
WkOv9tftzwLTEp02YuiBebr9cQAH6H5jIjPIMDqNLhaL+4dj6hs9Gr76A8JYiynVnp7mjxDVnJfO1Vo3Rks1wItB50v+St5HmcPqZ2zDT/PL2k19rDCJxTxHYLo5JKMwzRF0tE+fC04c53BPZGNlEABrT4jwqhlsaO8sGyuNZZXbz1TRFhExpC8qX8dQ3AUNm/vPj5nzneNyPh5XhlfHnHjMXH87gYkQv/uA0eEnpQLNZ6a57SuJgJ4CUKIf4AoFQOrk6L1n7Ks3GHeiXXVYyKLPyg4zDfT5PvkiLL97Ooh9RgRJDIjsgW+4i2roi5S7RlGASrbsRY0+9hfkeQ7+heNjlqyLu8cryW3gtgyRWzYZXQiCrEhQRhO4xAoJudLiDlCteRHXF5Fy5Ffg/6qMxBFuIZTsKLetGsafXO2xScKw7tvKqzhkH12izusVEeknp5BgnbIvsqg/mpF6zZmcy1O+sg2bPSpscSnMNPrpzA2zf2wNxKuXKl1oAm3kU/9LOWOdnapG+t0Guwdzd/I2PN+jDHG9CGicK9Btcehj1AA3kaT1nnrF9WJVzetwgOPNDiYh15FH1hUCEU2ycv/gryTm2CPFjcy5QO7mqNhXZn8Rsn9k+dyd+tEz/a1r+BXLiaUrUovUWT5sVWK9XzE3n0qxU4xKtoBM3vf0nFU9eInrYNvb2OsX4rt4qM8KAb0qzdzmWItJDkHKZrrmaxrXAnGQglomMylgQJQ4XI8R7sWUZccI4OiwNLoZpu6EZGaEP/3MIBbsOp6Ls/3CJSNUY26KtaNYTD/bK9clW2CwwbKMZZHJCr0VxxrZKOSrwufXrDQWDN//ePAEUTKqw1uEY7+a66Xd0LkXM/2sEHpDpxKcq8vK2WDhWe31P1CWNyQ9Vbbrxf9PcizLMhnKnWggwpiC2k5pm9g9OPh8o4nSzUPlptJkkqMDjQ45JyqtU8NzJt4ZTgGC1rftdzdNapHG5IchpZwyyHw85SNpNXhtvZ6Mf9ZYyZFr87dJuYKUsAOwIw609bo0xNalpEfUedPnXX0perAoVzu1bjJnoSMipVkWmltfEmT9+ISvzfKoddDKckY8mJSTFHthsHgr1u+XpPd7fkStstWf09HvarabIKQmLnoAEP25LsdTIOxSo2Zj6ZqFa7d+zqBN7e16ex1N8g6XR2iX0LN521UXR+vTiaw7cdKjfYtGPn4SuaSzGrhgcKovnPbi3mPPGvYi0kM4omO6oulkIZZh9iOYJAIxKWrAEXEAlAxyh9PeP6TvMooYxMU9Zc+rEqU4MnnXbO5Z3gLcMRLRxr7nd97FbuBk2k2gCbIOXH/vZahDieAnJFDtDRmpCGTXLa7hrg+QwTBi6HgFT2QTnBiVTYqV0PPpVa/efncpfP6OvVTFeArFu4ji/IEhr1a1dzvQyQ/O5UrDlH2MByrWFIsPQ+NEQ39SdXry3LFZo1Yu+bE62tE/0Ih+uuZ1RnCne8n6k2agXHpqSUnQXSGVuGMR6I1Fmj9fKAQ+1l+qx30JYKWbaJDM/VfKIvvVCU0sjhAuoV8bHZEWZfd99+zF65XoJ0OD1ytSUl83Vzr966QoCItEq4pDNWOWOyWl64uBntudVAWTdpdGy4L4pH2ia9uoZ1Oxxtd8QH2c9SkUVIRfeTc8Zc5w19VvOcjG8dy13TRMu7Fz+AeN4xjNi4DyhV1t4kX1QkebXbxrZwz3TLVTu8jT8qDd1CuvwbFgL6pA+xlNAK6DD9Pk6v7fttLV7C6bnkWJYdcHDePZ47HJfa1bZasK99f7tbsGr60huXSG8mE8z3+6k1W/g8FxldobGmobZp8Cd5iuDCMjfRKJX7UlTMaJ2pKcMyc5VDm7yhbb3cDdnVCup5NCODOmIXegho/oSDn5ciXgXtxaLarCLcLaMPdILiLce0UYi/KM5O8+6eiekIwgLg5xGj6BmQtLhgDXi/0Ndyl4Y2neryOIgOr9yOc2JxOhEO8pulq9HKHD2qvQJ0OYGfQrnDzI24vKIsGnto2OaKxN6QqcF4puhbvTQSHFM8VRA/WN4fPDFypmDfhIqRWMxLHmp3QYIgjpplds6Ib0FCUBC1fXSgSs0ODiqjm1y09B7WHlxjWl+FPbvdDUrSZj/VvXnQjKsqSexn0pjvGWhnxZ341IOXAuj/98aa/HruMJ+EYmVVKjiVTcv74XWVZVTOdIaqSMDk9XEGN+Rqu1Wm1VetTyrnrOSPIzoTWHUkTC9Vi3+w+4g2w86Ist7PamUBza6stTyRyv+mzb9OK0w/qiesxyAdOzl1Q7C3WVtouStdVU/Sl9/eRgUya1Q6RSo8Y7EI0U73hlUMUPaJBAhdiHXvk4yCfkZg+wc4fx2Ce37ng6NbF09Ul4aGUpcbSMahROpv+pjqF9kk3M3CisJ9EAR8Gp8dMTNtTS+aDhgTyDE6BZhW/IAMCqqqXxYs/2LGD08p2tPz/zz1nHCOsWuNJEAmLIbzuHsjIkc4N8jyDH/EyNBougbKjGOrNjDqVLXfJuy3ZhEHeb3dgyHU64sWs4sLqyk+5bntkyRZZuvHIcEIaswlPFeAkiyFvvgONfBtIbRSRkvQXsfYNx3enOpdqqrgmEZBEB1XeRThUD4iFoesLJb/HfByHGNGUaYCbIxS10MJeGYGwDshW8PAVjOMHso+wvL8QbwnsAxylRT7bkW1rOEj6ijR3FH7T614hOjPEFJxtAg8VueEFcq2i+2r8qGsFD9Tw/FfisB3+QtyCYEdB1MdbHTqz3k7r/NgVLrqQMIl+f5BIjx8VyWHNTveVqD8TGNpUea4mt0fLGLNFcSG98i8UauDovjIEK0h0aacuMal1ZXq0hChbWz2cUW/BuDKnSNOeOtPQo5O19rvqI6duJrD3nFDRpjhAktfUqHdQRaC5gdhw2WS9If4Lc5tr596XbE7+12oWOKL3qqBkeyXkjIpIBTGyWc9J6P7y4tSDhSvhRtZIYmjP3L7c8pFg+w9wx5H2RQNGIB4wMf6xKZ/mD1nS2qNIX7AY9VZXmpfme39rW7Eisijrjvn/ke3uDd/9c5mhVAT9Bz8dtlvBXHbGK1ZZHSSm4AFNAAlziZ4bfcg5EwxlHKVrKJL48Nne7tF5V12KOjMFqoojvSOSPDk/8CMbUOdJVnuCPjE0REwtiIlRyMSiZ0WElzKc7e9nYsXZ3llLSKuwcbTwyuKBl64zv7fEs10oPeMWmHaWwtSMJlkCfrvmzFr2JI5D+6kXXdNE85blvTrxtjwo3WVyBrvBOuoaAuITwFrZyNMe0ZBNBz9MN3U94mGpCwRVinlCHabbxYamuG6jMIksppiFX9O4O2EDN+f5LYGsxemKeq/N93QWb6ZSe7FiDNCO38fOp/8c1aWyiQxWVZgOPDD69dkK3DiL34fHhuh5QLu7HccwAgGOUWSLuIXf3yzYyJtg5cUsn+Okwp+EwSl2aBjH57Umd8GOFDNG/Siia4xnxerrQcr01QYEAzW2sqyQkYwsEhiEOsUw7ZHLbeqFX1apF0EGYGPbS0aEdhkScBaFSipsPNgFq2t5XOPUPbbJdVevwoir58WfrLdm3Qq0cq2QIPqmGU8m/FVVdzafoSJM6BEnLaNn+N1Nv+DL1rZktHsO29SmddaRbKAM1D3RD6M6lW0bBVYBOQgFPeqqNWZCm+TmSdAInqkZRO95AV0uh2kkvFwua/JRsAbgkcxUvAt07bzHqYrNRwEFjrfib3gRlkfg4XjXFfwbPLECextFWiNOmOgpOgKTBuiTC6/cmcfTduMZmTLearkTRnDFAIvyqP2tNI65nAH8STbdASOfpstqz+QN+8cdhXgMxmb1VF8eKKOAm6bw1wtUzG1kw49dZDuT2PEvQaL4PEIZXAK4PfFFDvatur+qK1+uOiDvRNSvhkRVxVnw1dxDWoFIj7iuaSzjO2ujaPfNClHvHDjM5o7yd/2aVNSDq0JSnV9/suZfuXJp7O+zMjDM/z+Nv/iX0LrXuPf48j3Ee+3s3BVtzvIssN/077Gj8jTJ+PSkPAtm8YitlMBZnrFV+c6LMyo+ByaDFsR29R3xjEaLlfcq96f5JrnAA6+XADNwEA7cLMNQdxXr8O4ZhuP9ifD66awVZAbd0Y0HpBaQbRm2P/4U53LTBfEr2e1ErnuV6TyN/rVOu2WhGIFHmGB51XGeK3/F9pJReC++zY5ArG5Eyjfg6GkbtdSa0jLR5U18LIWshcNUXZBM/dOQJH28xaM4z75sEUy39i/hB82b3AV27Maz8FxGjgaHZz70vRpxWcjmdW2inOsKA5NbRURjTjJ1Z3rpWAV3Egeaou8vXUVVjwd9ohu+z/4aCRmCEJEZRlSd6hx0D1eyLACqvNH8gRbz8Yppriy7azMsS3byA4f2DIoJXg3/pKhzYWogjJtT57DXwLef6i7S9KLYfbd68XHaua5kFsK06VZ94c3XkEng7O9kW/j2BSH6BAn7Rlbjc4Jw/w+Hae5fIZaanRC4/qHtqTEahCUi/VNPPGKQ4QCccyxOp8vnKRLR25TNQ6y88zInMq/2ZFSy9Bx0qOlN5oBGncY9+LgnKCN7PqVyx9DkpjiYZY4P6r73objQhWl073RAkVPKcWaBxXxl9CwrEujELFNIjfHSYcv1+TlE36vMkMvq+UMV9m+aZrtYzd3wMeaugqW+OQ9ivSQenaxxqWHoRxrSxP3gMpFIBXHhWScnRQp2wXD295gqP98DEAtk2lw9NUWf3VX5AqEdmu6cuTOO6r8N0FxshcKAACCz30+2gHcC0pyDZYeBddVPQvjf58VeKeAS9l244AfnR22WaUYfEkJt+p/BYa2h8quRHaEKkS9pLK3XEnyZuQq2Pb5iiU15qf/8mTn/bNjJx1AQRO/N8qbQ0b6Hs2ps/EpxI2m0buz73XxcJ5E4gaUckO7qaZmzcAnHFMsGpZsveFNd80h6f4/Q/yM0Dy0ySGwxmAJo3Zb2bdp6Vz9WoBkcIID69KQLn7k+6Ms8ncxQufh0Yc2s+rJAZYWe9K2U3vG4Mnl9HZwr31FWzx/FL5lXoHeZOWG1am2176pPvVNtkRQA1sNJgo2yqaFXpwFeRw0pGm/QOdmRv5R6NGQPNjzKCpWwrxtYjkr2GRKNUtMdsawqbh6U+59nG9Ai9A56W/cDXGBTiU0muOn/L20iLROmaf92Trl2RFl6wGWqQOzBCEOFmn9xUGujM1OJgvhcT9VpqOcqZSleElUsCtxA9bfIstByYZ8JqBJeZh+FY6/ybU16JH0HkjJlFTXuJs+ZKQedPI7s/4C3+gudaplU4X9TzE14HBCX0vcgv2AZYET1usNoMPUitOvObawFaQ8JQrvx9R8L906Qfz9djz8iVcjXDbu5UpXyJsXOE/R6nhVrUUZLC4dfrg2ClU/jtuKYDdY+cSZEVsCJFp0p4i6MnNSjenXYxICSk5hC23aiplweoM4C2S0qbdY+FrKOwW6YM7g84aQNt/AczFTgci3tb9P7zaAPKjGec+Bbhthi/I0LbDHwTHNnaHEcOLNHGyzmINeYiGrje33KmUV9YncZrn7qdqu5M8dLlZUUkltW2tDLQHMcGE24isy3+PsdMV6aMcCvirsz0enIhvMx1qMAbDLuIr9vPhyE6srHaz/30RKpYi7r6yQzLh6Sm31xoad1xTr23nHkkI54zo+2vn7Hh3o/XWEXy6cQ1iGJkvJRaR9AIUWlDFqHAss+lXIfXjgklh3FBH/2G6N4yV7BB13z7NNXYq6cgddYFCRs8IZTySWe7KyS1hWyl5OG9CpEf+ZTUNE+rzhURXPcyl8hg1K0qtAoPncW6NRdwpFvuG2enoFqHlRlwz+swZPotPvQ7OB68pb1rEVByT+LUY1Z766dTCK4XZNf/OuuMkJ+gzYrw1hHYlfexWgLun7d/zCC6EChZFXximMDqjFBjVUfSNRYChdNUTWCU0R7OlDS1cwTJaRMDtrsMCQM8nPCYDQzI+xbOLaJ0TE6HbuYXo1Fo3kBAbLFjBp72spJLv936e1lqDms5Olndy8UXI6MoLz9wqDpcF0pcMV5lirPP+dlGQ7qxaCVtooEnxJads8m0XOSMGlyu9vXhapY0Y/obX2dFIsF+5/T3wpUmbBkBd8E++cpeMNUdL9ywnP7tWB8xdGNds67oswO6C9Yn/Tg5cZUuZTElbTG24/JmOBjSO03cYVpbhOOTUTRdKpgvw1iQm5bg3k11qfFI7FG4/3av9wVgQy2mnIf5zu7NZGeQ2BZHouxCOiTWs+/lx5FXfPJFCVyeKmeK9e4Ur9O6gFnKJpC2HtJf5D2dHrT2E2cRMy2+R2eb4p2A3E58g81Q5pyGPB/iEYn9i+Qs7bgiVP/qJzXsTsHArkh4xUMkn0nfPcXTu20TOG/DfKSH2CnWSrd7hx6obUdXwgLkdhZfGtrqiY0/uCma1stkDjm8qLmKmb9Zs8ZKzr8h/3cYP3M4/2GZPJXJbxeJUjZulBgFaTlCMt+rZPyCi+g9yysxabtwZFheSibbL4qX4T/6Dvkwppwabhc+qkVctuDnZM01kXwTR+5rbi3JQI71CmnbG/5tzRjy04xa2aS1TrOlPY7a2z+PTbW147+oFZWek6YYoAiyTFnzfB/KZfWic5PrKKaclXH1XyWDE+4uEdteHd+m5vfd/NiP9BhYNrGeVr+ViM1kqfMAGzFBIimXJTxDkFzaKvsKJnuROHim9vrvjibuVxLofQueu8TRRflMWe+a5jfZcrvnMLB0O+/aVDiEx1cGqwJWPy9+GTuHqBqHJ34ReLCFujOBFBUoWp/cOpbzaPYDps2zY0bz4UmAIIM07WDxokH2nMIMVE/R9wflB+OpAIs6tA1tVXIyWnbJRDMFqOqVfj0d1pxnEdgxTczsklTtQiX7sUco7N+XKAXlbGGz/X/lzwh4yln9dOGDLvd2mvnES9mTo87BbDYbAt/agkavIs5X4RgkD6R4zWVNa0IDI7svC0RnaIeEWR8EJaKcmup55rWdTKdwbrNE/H6X/v1JL/UaXulx1kh+cekzME2pETjJQHg4iYJO6Tau0imgGaCmJk3CWvp4V5gskE9LyvxpdcxmxFp4JcbCPPOMnJV3r9XHsJe1A7EWpYIvOy6csN8ycjxcepzFvgt+DTBa6DpzrcZJiYPUYeVELuLKMzalpPqrJMt0I2UskaofGmdmoQ565DPxm532c1P7E8TqAk9bIPEWNZZBcvBI+wFJtsG1L/dbApeLsQBf2cB77Cstel1M1wIdKl085Lw7e3xmXnYuW97grM9ktgBo1NMyTsIcrsbdcwPTZPbVk4fckeb/ThrHB3obDmcI+/EMdHroZHiAplETWvPml+YvR//LHBL2CIEhGKJNQVOZr9oOmbelVcU/X0wHLWgLAbVh+XVu1EiS9UzScOJNMwdnqLUQj0zZ6TDseTn90FKjIMPxpcSbcThX7c/ixtlHm54o9xyE6RTtomzUlpmQQUNmZh4Onsow9D6JKWR1aqjf/+Q4GPejtL7Kv7zmlCrigTLT1EIH0OVTCNsfLPVsTDv5sKJKoM0yPdIC2Y3FC/LFI9yIicoWRaE69O+9EIfwws64xWdVcW09KL+r023pU67FNc1cOrOyVJa/tQl0Y1Lp3vzqbUISmuhH89o0YeF9LoI0yzSLRu3yewIYH+lHvfUKbF0xP3IN4w8FzXFUgKTFojntKN9SojqtaHA8KJ82jybPUT+KR5wR1ml7Pe2tswXvywQ8eAdRpCqWOW7awXBNYToY4hDI/+B0Yp2LZQg3LS99cDccSlc6fMgLQN1sOj+dxNNsuQj4tEPB12m/EhswOvgHrkanR0PX6XB8oBKFr01Gp+ViRNKV/tDAFGjhGI6QF+ljyn71AkEb12dpORDT32tf2tInKd2ccZh+FgnrOLZ6/dN2CHM0B6tcfaisLCsi8p5lTRP1sQCnnYSf26Zn8PcbHbPIy2yL7B2ltqC/YztW/MOPLs/i82+PWj0CdQUMnGdW4VZKao3CGCmpHpfUEOT2sm3h28r5OmKYbrAJeOfTF+6FTiZp6o4dsfe/cPOSnbtgnep12LW84j6GCtgXVXVIUlhPzn6rEJuppr+yDcI1B4HlLRfgrOxfOtNvXZNElHbst5q5ORsvDiflHv0QdRLThNwW0nImHa7oTrOMxjFyjmwHtpJARzj2f0IjezorYUe0u5S3jva308t/B8InElnme0nOoYuiwhBccFYwZ5wpuEsE/DrQorUjrEJ1Dnith3cMSkU5K1i1IPtg0yGwHcyV7n2SJ5jWdsoD0bpU/Gdg7Zvr6AYXRqajZAa5s2s6kEbTqJYb+njk3M3omIPSHhvEzM2qe/eSbaQkBSnn8QvmYu6LLlM+dQeXPMps6bxYWkK9JZ1KH0XXBLLibUAvp9jVv5Gxm7ZwlCw9CCLIopOYSeMepiZYwgcnV90NLc5gtY5Oz+44I3iMRbwADgJp5YsC2VJrDUAYYxc7nS+PZW4SGCJBf1jRi4OuMfRhnmmGs+RhAQ9UOvhKD31gGRXC6K7VrbL2mYsik+IJCa5NsCRJrdfSS5rW4jUzz/JSuuh1Wr7uFisSyCCETv0Yu4uXb7MnGaaNpd+fSBxfWaf2so/yqaW0Vp+qanMgWoU2FFCrrtoIWT9neguU2euo2dVUfjFSIK4+BMoOM/YfBKw08+GQFkaMPTa5XCnsTrXd3acnEXaXgJMTemDsAJ88M2XR0br83THikYxXqOe8HCfsgvMtpEMkyMJr0q0+BVqNY7vucUoC76ktns03rwkdVnWNE4KuFfd+xnySHPVHLbRIghq2OeEmJemx3Wqxdx3Z+/6TCPFRVII91eLButImXdwS8o4hKXVAQgRML2i074uQMNKktDHHA1tfxx5ud4hR5JPcidWTNoj0v0NiA02FPpXPj3JYVqxT3bFQ7FwhafNKLtyUjLXa3ndAM6/lWrxyHS5cdSq7JwExUfooYsGIuwzmCORAq6QM9w9bfhFVDubOJ98RQSXFjOZWbVNeA6tCGdOcon2z/EkaBEydQSNMeijM/ITVYUJa56Kp40szbP042hAnq2yWDQ0lDg0calAAloHDbxC32qPZCABceG7u1pDn4zcP9R1S31psHe1PaWQ4rXoBdC7PgoQCMHlNQe1V+41FnfvyPWRNTDpoJXzCYUI=
*/