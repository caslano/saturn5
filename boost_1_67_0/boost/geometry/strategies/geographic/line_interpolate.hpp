// Boost.Geometry

// Copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_LINE_INTERPOLATE_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_LINE_INTERPOLATE_HPP

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/srs/spheroid.hpp>
#include <boost/geometry/strategies/line_interpolate.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace line_interpolate
{


/*!
\brief Interpolate point on a geographic segment.
\ingroup strategies
\tparam FormulaPolicy The geodesic formulas used internally.
\tparam Spheroid The spheroid model.
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
\* [link geometry.reference.algorithms.line_interpolate.line_interpolate_4_with_strategy line_interpolate (with strategy)]
\* [link geometry.reference.srs.srs_spheroid srs::spheroid]
}
 */
template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class geographic
{
public:
    geographic()
        : m_spheroid()
    {}

    explicit geographic(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    // point-point strategy getters
    struct distance_pp_strategy
    {
        typedef distance::geographic<FormulaPolicy, Spheroid, CalculationType> type;
    };

    inline typename distance_pp_strategy::type get_distance_pp_strategy() const
    {
        typedef typename distance_pp_strategy::type distance_type;
        return distance_type(m_spheroid);
    }

    template <typename Point, typename Fraction, typename Distance>
    inline void apply(Point const& p0,
                      Point const& p1,
                      Fraction const& fraction, //fraction of segment
                      Point & p,
                      Distance const& distance) const
    {
        typedef typename select_calculation_type_alt
            <
                CalculationType,
                Point
            >::type calc_t;

        typedef typename FormulaPolicy::template inverse
                <calc_t, false, true, false, false, false> inverse_t;

        calc_t azimuth = inverse_t::apply(get_as_radian<0>(p0), get_as_radian<1>(p0),
                                          get_as_radian<0>(p1), get_as_radian<1>(p1),
                                          m_spheroid).azimuth;

        typedef typename FormulaPolicy::template direct
                <calc_t, true, false, false, false> direct_t;

        typename direct_t::result_type
        dir_r = direct_t::apply(get_as_radian<0>(p0), get_as_radian<1>(p0),
                                distance * fraction, azimuth,
                                m_spheroid);

        set_from_radian<0>(p, dir_r.lon2);
        set_from_radian<1>(p, dir_r.lat2);
    }

private:
    Spheroid m_spheroid;
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <>
struct default_strategy<geographic_tag>
{
    typedef strategy::line_interpolate::geographic<> type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::line_interpolate


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_LINE_INTERPOLATE_HPP

/* line_interpolate.hpp
Aj2xr+zqkuf7utFFjU1ghLes2aFEwVFCP3dPogF4QpEBDFdBTY+PNrmlNj1ABSQ8FI9PmQddEdRyAXIHijOfrnebAcCRMlfHoTzgxL2+bk4/lkfAKUpEgsiOzARzFzl6qmJfqcx/czECmh6fkM9PGUGVRxOp1dpdzk/s12Ubdj0AAiz909kdVbi7rCC1Wo4Hub01zW6X0TFZW/zRNJACkZV/ZtLyfUV3FzPmT3H/Fd/Od8LX5Xzqm4YpyUskG1+RdtXkXZsTmi1FNA1wyER2mcwu6MuHkDKriu4TCehMx7dKsjchLqFKwPoxBLrumcxiGhaM6O4SiAFOEJ/sq12O+ot38pwxGhvfalGtCix7+GG/VuHvaR1Jcbuw/av0+4Q7AO/RLMoMd4YOTRHkC7imaO6IvBSBJBaxqutqHb2mbUHfuWZJ3dhqufhbxNHAfS8o7X4pAhdLhtgDt2huWOWlYHXkwTwg5rdWsZoU0Cpc17JcnrVZszMWLKAcDLHgUbjpIH2tisiSlcL0lprdhjcjafxGuuvGJ5/exwnL7ywDBPt0Hb0ydolgmF+6bShEV7E9Ykdh8mHOBJpZxNs7IXTLCVQKGcWG1M1ygI2SV4HuufuGH7DVFxHV3ic3TZJ+VtrlHMXC8xnIFn/AGKSVjbg+w4wS9yUQ5jQn4NMN3nOy4ATjY4DcshiA64xhaw3YpVpKdlRemOdez05tRgjD6bg82pgIGpvlDiD+4IYQSb0vAOvyjwN8pORF6wRZfcocbsdGQpevMe+tG3YOb62P2VlWnxXiKBVW36nFIAIe1ERbFsk2kzBoGiHBFCLQLMwCjyMUsXNhS8x+Ve42EFSFNzTZ8/OI7m0CvuHeWPU7rIcbf+JhPg1KexZ85nlQLnsTHIghlsP7udFCmwhaRR8UyQ7RvfYUZ2SFy2lMjv9M53h0jcldjdazBnO0y0l5LgOCg6Y1HZSYiHggMwhsZnvq/COatX+bmb44enjk0oPkiHIqgv/rwlyV/8En0k4aO+6BDcmJrLuuye1tvs5IjdbbuU/SQAWo9AS9SrPJXCeA9lyapJIO2ywT91DgElwMwrHGGSFfSwzabdAMMNm4RqLFb71jXQOAeqoXCC525ZTnmQdu+SoniU2cZgSrDgb/mcf28/0c0BQoJ4nJ1hNWYyvYG2fJpmZgBf2ba3XEMDV2yKVeyIghq271qFmN6nmLM9Ky5YsZc0pdmQmtdG3y1AmMDtzC9iJqIH1Xooxkp58Riv0rbx+a0AznNFtXba3Yc8PBvhdsyUAWg8zFQdRoLLR3lANO6ad/bBkPsIo52QmMteig4Pao1mOWlZog38w+YG5Rsu3JpnyGacOfawtgmkmjAe741JZutiTSwY98Sz1PJ2EfXovZo8wCrOeJ6zll3Xi7cLdOWekzxESQKMxN3hJryK4vUaHs7PrzWxEZxBo0CsNrFqON4S+6qkCKUNU27pWfM5kPKWOcmI60AWwNVWW/uGS6TqRMeJ7dnhlmxjD0naISUY8JRIUFUc/Q5GDa4MTWGp3qoTJfLbRv4ZCA6MCfEp1+cFGM0usnNpAdBkjBn3nmjNSZ/Rc2JxCcQ1TFBWqfC1SYxUxF95meWrjzXR1QgPTxDtN+ab7k1B+TW7aKEIlN8RL/Qem3oc1VxjouJs+gn27AkENZ7ic+bSADLr1HCC0K0Lt5JK8Jh6jPfQ4b0vNzo178Y2ZXapaYY51ka2/H0FktyjdBS+Z7bDKidDSyzdAXkctoWy6FSxpbLwM0rpS4I32JXYZLcBzrQWkYcCHgiXUwnYnx0rMjuwaOAJj5iZW3cbuFCb2geyRwhvMjzG5HqpTY21VXoTcqBOooKKOXGqoxHt4o6NpuVzgjSgJjAv6zDTcAKz7g1bqK1bzxUX3HlTweZIScxYxVKcfXSPrnSHrdNDpALTdIt74FrsLE4ZkAlDK8D6Xee3HaOE2Czt4ZmJLFjiu1PryP+tgiSB7gfOhhmmvydjdc6JLGo+ZgbqBPC/KcNOYpXV9JS8mDFhwDtJwcX2XL8d2Wzj5H6EHvq5C+oCe7AYTRGyIWkqOXpIzrjVqZVFoHNHVmrgTIQwVIQ6kKu25cOjgTpzWtWEvarLjYTC3gRAf8qpcuHu5nS/A3w2T4M3y/pIaLrGOfngEAsuBToU+irawLfKF/+O/SkeuEfCboPjjF8a42OtB7ZpLQH8ZZIGelBX2XU7c9Po8dbUu3vvCf+GDx9vI4EAZ5runfrM0yMVWGGWENvfMG/dJykrhtRiytZzX5SkX1eNc+lZCESFaSaYo3dSvso33VuDov2bwrOkK2jc2W1Z6npy7V2Kv9n7jXBKkZd4khYYmKqQ0dx9naigtRICxwXvjox93If+rT22ZS7XZ9aLpjwFhLuPaxainu0aAZLW9DU0a//ITtRHwzFXG1GF+lZA70na5RBDuAcY7/BdPHBN/6v5nySMIHjLF192BMB+ByPUJ9IZcUMXttMJJhHhB5baz5hZx5ZwVrBAquTiLEAGls7mF8Cv5xwsgbE/wxzseubAoFnMli6/YlS30eXIxMO7ec0yVTyQhjgVdjseb1Pv9wTTPq/AKzOuojfYaka+lSqNMbSsXqgTe46z7GcIQCzExLI6VuZAkamoceEkvlaTe8KpzTiFSLHGgtrcdDxQ8fbnMd2j+KVK0Z/lOUyktpXDWu28hOlXHBbLt/mmxicy5twwuve5M5YwHLn2w7KUClNPWIYToR4ujNPg02UfKII68MvO06p//iuGW/8W86aOzaDYgTl0FWKKcKMmk88fF9LEQx0F6OgmGvn781myN/O6EkEhjOGSP5UA9WGrEDuy4ePG3hFYQTQWwKEDxfjtFaPo1mZRLXmOqBDy8EbrJjfGIYZ/EWMIpbBPpBm0J1SiOFnWBYKPXtFLkSGt988KYGODUTe27d7074dGNglFaoG/oIdeSNwk6ort3KcGtwkNJhA578uZCj5jMkG1zQRxAMS2Mr6sxsxYDf7kfmQj1Sl3+YOrQXR8Ps9W9fB2mlqBZlsSlPrJEM7ckRYsVfF3KAhYmFlTQAOl07MoCU2vWHdWebZHob3CGN+URFQeuwbKDewuskTTYfGkRl4w9V9cgutAAd1EmH1UVJda544UYWT5IDxwAHg11E3ltAsG9hcFf4PikAhW3AXru0XD2E2w6JkX/wptl+RU9Rj+W6tza104j79cjseouD5Y/hl6zJXvXiDxFLxtdYadrbk8v1TcZYpjMmFwv+21jfBovz187gbe4cHwycrOZ6xhm+mVkL7dQd+cnRXIdIwBZbCiJ5baI8UYUVKd9Qln3AmQ1ZprM+S9wxuL2taGfaJtFWILz2isA6OsLI/rQcktVNp11C8kfsDvj6tN8DVpzPgLiZT5oiUie6FWZdpMDNLy5tAmnbAlXhlTiHYxo1E/NFa0EXmp6Ztw566/PnLaPqhxgpDYotEoCF9DC+/nklXagzKsDM5yq3xVu1Ss3Uz0+CbQBdt8asH/KUxzM6IqI04A6u8GwevMJf3iyvxnuwm51Innm4BVpnkXB0gd1rk7bho5nA5lQGpD9wy4MXT5+CBJn5wWw3mWs1AHnefll/WyWNBHmXNjVskqVtFmrOB2KCyUgOHdT7Z7k0kg35jO24KFweJB5J1xcUk7tu5lQosLUZkFwh75zqhRTAPgH+Fmj3cwcokgbBDMUNWOFow50K3R4Q6aF+R9nSHWdemH1kZYSd3iPmS00z/8upbwXaKaZGFvSOClxvuJp0MOeKCUafTWw+wUpABtXuYvqpUY+5HK33FEvxguOoSe+fV/30IKhH8wzAkrwZ4hHZfsIOwrxUm/3usuVcYReTsJgjC1xVWne+3Yy/2HkqS4gFvEhCA3GxA0cJYaADXT7GryP+Nn7uPIHyoDl9kPvXpaHC0tiCa+xOqIk42UbRtAt8avMayWpyT0HoZi8i7S72F2LvKhRu9Dn3Tr8VuvAHF+9mXKdgyhcm1buIzVMi89xOcMq9CnJNTR35+3VgBWRLZegAvasJ7pOLYfjUxEBI0lCO5E9AQhLxtrzwo4Hzi5oKrMpcKjDrc+4bqvln5WoiIuCf7Zl78trH6deXTzf0j30mJgiyFXlVxlDf6kHsiOa9kVvv5kQG7rwK4i/4kpjcC64yYgMHLU8x6hkLuU4psm4NYp8GJgdpz0M158OdC0xHWt7LXPJTynNzDH3TI8HDB/PHPInAgrY2QThhqXQjBlJNCt5Gr7P9OmpezTbL4Lgm9VFNoLXkipRqjT/GdQEsUmqQ+wVHMGb5cU+j40fySF2a6n+odXC6jONryd/jK8XwxjVRu/5YNdVKalNXqqNmJzZ5mSyXG2z+RPS4DRX6EvZyptSowyy9QdR/o5nNIZW2YvnJ2cvRaAPPkEip1VjnTo97A93Jn3LnjWKjTaHCmXzU8+3rG95A2QA5wZj4w4lKsLw7FqLFxoLTLO9bKHaI70hM3oJZTRQGsMuyn30hH8wTwtcdBXo2esak6/qIb+T27XCaTEBP0yy3MRl8OVHUfisMcpIktg5V2GpXc7/G6Up5MUEXKtFSjtFXrVwseOLWBmg09nODCNkrDvdXc6J9Hggi8fn6V0S2pd6+OFgmTWpaeohn9nf0N9yy0wbm4a1D2Zx6oCltCvm2ZPusCGVoPNxPifumpHYQ/6kIoZosP2JX0YtY5BBf43Yh2Qmgo1EJ92ySSb7BC9Y4RFpEXKHDU3u972gFaAP0nV/9ntGOBXcFHbOgY5p26rF6sKWX7qg1JR+/lIQGZEt3baot7M8MfnODfGWcUJ8PynyUEdrZ3o38fwBhgJ5/IjhA+tgNnKRfcTgzcaWOK+UJEFRpRwxkyWXtskElkVayUPdh/F1Ce1cDnYBkEwwFcQvE+wvWGceLdtanafpOJ/ApgBW3Y2mbTn/77+3XN75e5OWdsETR1lX0FUjqm9LkgwXarhdxOBfiePzpAmsyuahHPo0Y+QyDZRRYD/n8T6ahF3G7ir4OXJyJOWz7HQK/iEusDNZGAlvkFZHuvzNWOy5qa6NgXBolmZWwKFyxx4dCGIdy4KI6BvjSLpALLO8egZx/eYcum85tYhWU+JZ3B9jyrpJYH2EKm9TEaht1scPy7hZstRjlseP+ewRbnZJk1HDKaelohO1L3jWllS3LcBydoRMhIGfB/kmCax3tSBimlhHQAIzaT7tnw1L2DDkK04UzlFQsQK2bge0nUEbx7UJnKMXDgw5MECDjW0l2gkxq3HlsBbwBmXQhT/qZ7GGD43EcNHEofx6OJe8GwJnvw4HF8ipsYV6d9+FOC7T0UtKNLdCmg8D36AJfdc+G9Wgj6YF1WUgvf127cNOdhGNd2tC9iB+p7gE4V+b76rpIgi/6jEY3pCFi/w7qPOEgTXiFJeUEfmKxShys6MflMH1N4Lcf4Q+fuU/6OUY60ivmrDL7IjW2+LVdTU9DBuYGTSf2GvIoThwwxOyn8ee/7Gc033Sa3HZB30O4yqLfRjqUcSFaj+SxHrnzj3b7DO1cTT3VeV5lPBvpH83s2zKc0OuvbiUJ+BaM4wT2Q9Ue+1Hd1FJ2kSRtWJxk3I4ybrAOatS1wr7rIwzAjWjsRdK3oZXt0L1G/eq96u2PDNFkd5EMJzNZqRM3bz8fP6E/8iKnIf7HCP4qMS81c/p2pqtE5JHNVbIVd8pubfZ1EcQfrr64MTMYN1Khibx8EztnuerwS7ZwNbgiqNrSTjLUipFt30CV41drK/Wr5OkccJIXmNPSlRF3+R2mjHjKlHGUdBSflt9gP492lC19d5F/nNfGvw8NerVS6zLorycvs9G8h3Xw44BCW/H96GDkVorMXkFmtDqVfdQfz9hfAkB8XpS4TBGt8eOEB68nmfH+iDhBsUfGxwljHQH9NuUw/Q7+25otWDNba5wmBsDwDknTNlFKnWwTxRupMTQ5vL9p08X/5Gh78MNAgqfWrIDgYOnyrGhO20wzsu97LXtQc6Pg/l65rIXoPQhr/ku/aR/qsV+lDphOXh0CNNrevzhX+0KdetcQ5kMbyQuoB8SCOGBSGoQyqhiJ8ErkYbcqYkR8lNArvr8Q6mt8KDs56PobOkshNA0zbedb2bkPNqn7KraAO9yAP1yLhT8+bPYxvQVHDKjSR1cOdOlKXkT8AKE3ANnBRiM5C048HRNvnWefsNMHbwuEHAvoUuCbs5m5e8BkQvCuZ663qhrtS0BLJciOLeNdX7PPWHXa+h0G/iWmTFgskQnCfcnCmGSxRrPlgSktqewEOXYo+nqS5oBggCwDXqxdP1/A6bIvrfP6jN9pYD/p0R1XzI9rIAaIeAys+GNAS/NmSOQBYWSyMCCZl1fhmzQpFv2cdeEf7+SSxdBA+qyfIZ0BKP7GtZ7XGvfU/Da9caUgOi2cr/34CLOfwhztjH4G68DVwpKxYx8Vly9fKaxaIHD+Q76WX4Gu39w2Xx95UurBxKZkm7n/DxRYiqOuQwCAQ0vdvQ9cVFX6P36HGXBEdEbFoqKcklpb1CiwoNEC+WsCjoIg/kERRgERCGZ0LFFsmPJ6m6Ld2rXNNmurdcvA2ij6D9IHsMx/+d1oNaP9WN3bWGGSUgLzfT/n3hlmCNrPa3+v3+v7/f2sw7nnPH/Oc57znOf8mXvPkTjkxgWGOjAjuf+FK8hKp+zRv2Bz3s8ONlUAf7xCfhX9YcQe5IoZoyCvmCEjZyOOS6ZzeJYMUT21ZBSqB5fIVHWIxbCjKrqH/erDKuUe9sQHBtk97KUh+XGB+5Y02Sz6LPGzNhX7XCJEcuno/uMpdIih+BKLJI1+wJ0lvkko4p+m+Fze/r2O3nZ7YAp9FOC5sjKlmb5nCsqXPpowwN74vU9mrXPURA24LwRGQETVe2H4++7Zjhdt1hn28SyLznjsNwlHOpL7s1+HnqU22Gbn2CYbP5uQRdNx8M2lX3amfQTIjk55i5i39oif/n7QfYiudK/7+SYIfzF0gH1K9S0lvgkls+/ntdJpSp4M9b5TG/e2Rjl8vz3Up05XZctifzOeblhvkfZmDbhTJHsW6Z1pa16O2HhAqdJyZLuuyBH/TBniVl8+FQCJZaG+qol8nanG9YWY7Zc/Wc6XbieSOB8mK9tSJBHatc+lkjnLtBwxxlP0UdJ6Mt1fGeQt8zTlZejpU52PqZ1U7FOMzimyORxsAfS0lJo46H4vKRVdLr7UIB67UTklcYk90JLZZDM4d9CuAz/G2Fp9s70l0J52yW1freZqV0+tta+O5tZ2xLu5YPw1BAe3x9/ECTp7S7z6sNN0yXis6ri9QxN3NbHROc/Og5ntFlhK+hyJ2kxNvDQRMsjVFvqk2FfoGvkfmiABybcISfFjpDCci7dM9t68BdDrr8i54d5c8Z43NZzrv8XgITy6RGbbK/LNGS/QYaorT7Qnu/XS92+A771NdIadfYJb7JrkeeH5tjfZW9Utbw245f2Km9h2hK5OOjXgNh6wGMRkL9UzXiqVTMW/RW/piuyz58lv0nMPe74Cz9szevCo2Z7RS69E2TPOaqRgb7bWB0UvjcezePpVVj3+GtE4yXNDghg1ib1Vfe1bdOSiHtPQ3ZBqu7mXXhCnk1p7MHtzW0X4oLNuay+dRfWJNAcowq1Ce2tfoKBhl5zYv5ra+lUQXa1ZaxhUNN+TI9agxDy3tds9JZ3urbmgc6wFqfj2RO812TlI12a446Vjb7AHrdT5Bl36l+W+Vbzu6kH5TkzjJetlogG8tsfa6Y1KR8dJeMd7PkZ1zF0cdekuums171XP963XrLXXdF1pvVzoeHwxQazPMZ9LB+w9eJIuskXNbhUPhA8qx5g7ZoGXdPdJaiEsLi3XzeXiEV01ly5esIxDim5HSfiYFluDKilWfgiQbsID/V5S9QabaRo7dPevw6O9L2DjBHufZmMk/WTsyEaW7t3kwWhaCzawt0cd8W/IF38MYi0QINHrt6UBubkQ6uaH2FvE4w5YDuWyDMNDynVtJOfPx+nr1X8qclxq9hbb0ywX+0cUu4lXeH3p9PCqlXmdkDOmHSBN3Ac2UjPoADjSQAe+RegV6+OtfVLIG0ybrhMQ8/u33uNK1cuFtsgOkzNpLrvZdmEvg7MDX24DK3Wf8fNtn9k/dEtFJFaQ5+wwIYQdHNbaDfPQamq1BmkPlekxCo+NlarJxDD/uZ4sjx16NmXOJDo40hrj8WCzXvkVxrC7W8W7XqKX7Ll/Mvs8PIQk2yevmSDNRuHygfUZr2k8R3s/+hrrbLvQD+m2qTDpB5iS2PCy7A7G63ydRBDdNPB7uh4nTDw/wesoFr0mf7r/FbkXiww+4QW7rhIOyKu8T6LgsEIBfH2Cd4yYAlrXrcKBYyKfoTe2Vqn5ZL3bqhf3T2R3v/MrexwnrdeIjgne64Anvzzgc73y3a/QxI1ZNYaU7wVURscnTZhOr2FlT5ghfQ3snfMDa38K1tW5qFLsMN4v8OTO0NfWDHI7xgk6Z6JKuXekPWlCIDBb6Xog3c70Cdczwle8hHvxtEMr6OJlaiILkMmuD9Y5dnrIbmBk93rJ7vYhA4laJrkhWFoKQK1WI807Qebcm2bsrA5jexnB1nF0a2SGvl0d7NoMpbjudifrSzn53F5aXgpj3DFB7inh8nnNwbKh0CXE9hqRsyQKYy4kBWnSLKG1Ne5gyxvt6vHCmJ0Z7h3pQYGuG40re6xBDLAHynPLHw69spP1EMrW1X1O/Vw9PlH6Bx6EMeTeLnDxVm2tNkD6EFk7VTvUiVLrx/JE4MT+AfeCnePqDtqCEqX72VAZr3vtoEuHLrltMkqrmrBA99q4+No3lq6hYVbcOVn32ge6d3lKYlE8Xnw2xPOxi+ueBGOnVaPucsULugtJN6MO1yfuyL45EH18y9idkwXdjuwJ1yfa+9RWT+qGxMgu16SLXY+Xqhaz2e/XPKuKkHwmcmXPMfLgIVnoa6VcsTRAB2ceYmfV9kJb13k62EfkBjCQuKUxqIxJTA+k7kTPaBfh8uiD8BuPtapbQManXxYlfdEot9zYmEEs0fUS3RpsT9YHKE0UQJPX0ZqolDVRkaeJboLL7oPOI8CqdPzStbyamqqPmooefsLD9cKY9qQgGEwQcKj1xik0PdF0gyKacJDZP3sJVq/A9hBsvHQkmk5cdFomaC4EUQtOCJAeiqZDXjnlLKdawgvMN7Y=
*/