// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_NORMALIZE_HPP
#define BOOST_GEOMETRY_STRATEGIES_NORMALIZE_HPP

#include <cstddef>

#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>
#include <boost/geometry/util/normalize_spheroidal_box_coordinates.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace normalize
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct do_nothing
{
    template <typename GeometryIn, typename GeometryOut>
    static inline void apply(GeometryIn const&, GeometryOut&)
    {
    }
};


template <std::size_t Dimension, std::size_t DimensionCount>
struct assign_loop
{
    template <typename CoordinateType, typename PointIn, typename PointOut>
    static inline void apply(CoordinateType const& longitude,
                             CoordinateType const& latitude,
                             PointIn const& point_in,
                             PointOut& point_out)
    {
        geometry::set<Dimension>(point_out, boost::numeric_cast
            <
                typename coordinate_type<PointOut>::type
            >(geometry::get<Dimension>(point_in)));

        assign_loop
            <
                Dimension + 1, DimensionCount
            >::apply(longitude, latitude, point_in, point_out);
    }
};

template <std::size_t DimensionCount>
struct assign_loop<DimensionCount, DimensionCount>
{
    template <typename CoordinateType, typename PointIn, typename PointOut>
    static inline void apply(CoordinateType const&,
                             CoordinateType const&,
                             PointIn const&,
                             PointOut&)
    {
    }
};

template <std::size_t DimensionCount>
struct assign_loop<0, DimensionCount>
{
    template <typename CoordinateType, typename PointIn, typename PointOut>
    static inline void apply(CoordinateType const& longitude,
                             CoordinateType const& latitude,
                             PointIn const& point_in,
                             PointOut& point_out)
    {
        geometry::set<0>(point_out, boost::numeric_cast
            <
                typename coordinate_type<PointOut>::type
            >(longitude));

        assign_loop
            <
                1, DimensionCount
            >::apply(longitude, latitude, point_in, point_out);
    }
};

template <std::size_t DimensionCount>
struct assign_loop<1, DimensionCount>
{
    template <typename CoordinateType, typename PointIn, typename PointOut>
    static inline void apply(CoordinateType const& longitude,
                             CoordinateType const& latitude,
                             PointIn const& point_in,
                             PointOut& point_out)
    {
        geometry::set<1>(point_out, boost::numeric_cast
            <
                typename coordinate_type<PointOut>::type
            >(latitude));

        assign_loop
            <
                2, DimensionCount
            >::apply(longitude, latitude, point_in, point_out);
    }
};


template <typename PointIn, typename PointOut, bool IsEquatorial = true>
struct normalize_point
{
    static inline void apply(PointIn const& point_in, PointOut& point_out)
    {
        typedef typename coordinate_type<PointIn>::type in_coordinate_type;

        in_coordinate_type longitude = geometry::get<0>(point_in);
        in_coordinate_type latitude = geometry::get<1>(point_in);

        math::normalize_spheroidal_coordinates
            <
                typename geometry::detail::cs_angular_units<PointIn>::type,
                IsEquatorial,
                in_coordinate_type
            >(longitude, latitude);

        assign_loop
            <
                0, dimension<PointIn>::value
            >::apply(longitude, latitude, point_in, point_out);
    }
};


template <typename BoxIn, typename BoxOut, bool IsEquatorial = true>
class normalize_box
{
    template <typename UnitsIn, typename UnitsOut, typename CoordinateInType>
    static inline void apply_to_coordinates(CoordinateInType& lon_min,
                                            CoordinateInType& lat_min,
                                            CoordinateInType& lon_max,
                                            CoordinateInType& lat_max,
                                            BoxIn const& box_in,
                                            BoxOut& box_out)
    {
        geometry::detail::indexed_point_view<BoxOut, min_corner> p_min_out(box_out);
        assign_loop
            <
                0, dimension<BoxIn>::value
            >::apply(lon_min,
                     lat_min,
                     geometry::detail::indexed_point_view
                         <
                             BoxIn const, min_corner
                         >(box_in),
                     p_min_out);

        geometry::detail::indexed_point_view<BoxOut, max_corner> p_max_out(box_out);
        assign_loop
            <
                0, dimension<BoxIn>::value
            >::apply(lon_max,
                     lat_max,
                     geometry::detail::indexed_point_view
                         <
                             BoxIn const, max_corner
                         >(box_in),
                     p_max_out);
    }

public:
    static inline void apply(BoxIn const& box_in, BoxOut& box_out)
    {
        typedef typename coordinate_type<BoxIn>::type in_coordinate_type;

        in_coordinate_type lon_min = geometry::get<min_corner, 0>(box_in);
        in_coordinate_type lat_min = geometry::get<min_corner, 1>(box_in);
        in_coordinate_type lon_max = geometry::get<max_corner, 0>(box_in);
        in_coordinate_type lat_max = geometry::get<max_corner, 1>(box_in);

        math::normalize_spheroidal_box_coordinates
            <
                typename geometry::detail::cs_angular_units<BoxIn>::type,
                IsEquatorial,
                in_coordinate_type
            >(lon_min, lat_min, lon_max, lat_max);

        apply_to_coordinates
            <
                typename geometry::detail::cs_angular_units<BoxIn>::type,
                typename geometry::detail::cs_angular_units<BoxOut>::type
            >(lon_min, lat_min, lon_max, lat_max, box_in, box_out);
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

struct cartesian_point
    : detail::do_nothing
{};

struct cartesian_box
    : detail::do_nothing
{};

struct spherical_point
{
    template <typename PointIn, typename PointOut>
    static inline void apply(PointIn const& point_in, PointOut& point_out)
    {
        detail::normalize_point
            <
                PointIn, PointOut,
                boost::mpl::not_
                    <
                        boost::is_same
                            <
                                typename cs_tag<PointIn>::type,
                                spherical_polar_tag
                            >
                    >::value
            >::apply(point_in, point_out);
    }
};

struct spherical_box
{
    template <typename BoxIn, typename BoxOut>
    static inline void apply(BoxIn const& box_in, BoxOut& box_out)
    {
        detail::normalize_box
            <
                BoxIn, BoxOut,
                boost::mpl::not_
                    <
                        boost::is_same
                            <
                                typename cs_tag<BoxIn>::type,
                                spherical_polar_tag
                            >
                    >::value
            >::apply(box_in, box_out);
    }
};

}} // namespace strategy::normalize

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_NORMALIZE_HPP

/* normalize.hpp
2nRq2DA0OcQmZDmemA1fRWBrG3usHyAtVNNRDbsLFKYzKkxkYi1aqhJ3FGlcuGbxHAr7KgINyv9ur7Swro656REv86Gr0BNgC97rpxaKWYpvLSND9iHcI7ldLuk/KwDbCnOUmGgz1v8jdmNhJW71haJsFqMNlj/K3YiZ1WwN3xteXvGNlKT4OjV0m0d7/3MraScdWGviIiolDmA1U7XOgM7WeGPM9SgE+IqGlPy0aFYBrCZQKCadrljLwUa4PzbIUQmBP4tEwGO2qMKLJxpRFsF4k2vuyQ+VQDfMORisQjNEVMgyrzxY2Bxhbo2yiVZ4mLYuv6iKGW5lkhH7F8yUvOgRwq1TRr9GG8yvMRAVkcJs2PBoecApuxlxKXSrOTk6KVIF3QbdqNKJjPu4RW+gu/Ib5sBZ4SiP0ph52TujdG3+fleDTv6v81vEbXp27LUhni2qHZJvguwVqQfcBvo5Gq+VpCUtWiVKHp2GNBoe0q0ufbIktm0YJLhNaOzFmEldBD8ZrYWfThgi3skHsAXCTQCMRWEkFCUhkSSY6UxTiIwJnZbapDh02KoTcJpI4SGxLpx2hGQxVeRgKBtmJCVezggOoYiu/rLpGGCaTRq5uTIbwrdYWvl9QblBnVF4W+UztvJVntmq/3EiEFYaykbVo6eEFB4x8TmbUvffEavRpq3n9cFlUEEQr2W5SyQ4STCdUvflBHTTkDpxCPfabE0uSZaSYLJdLZ4NUvM1soR/jxmw1H3edV/UtYpWrRVC+t9BifKYo8mx/vLJwfbUoQyIgyTGOblX8wYEJIkzchiIaqj2un72ZtXWviOo9m1asa9I9gxilLK+EPmg7JkQs8lUvoVtDcaEoL3ykqf0hjvn9fv3LaBAg07ibLdhG4+0ybaEYJ3z/wbGMb75U6XNVqTXLKM+HrfUED3I27ZgAJwzsfeJ142S+mF8U45RiZ8jW7uOR+p2zp7F1t72A/y5xYhAB4VOrqTBhluLcKKb8gistPB07UNItRnHuoz2GhDJiLsG4+Q+8lTY3KqEhLP1UuKpeSQGiY9ySLREOcJ1/wjqkPqaA9oylIdtmWxxiwM0w344nXdWiBVOnkEi52P0M+LsHnxn/bsW9KpX6CydMvnGJ3I1xeQl/M9ub5DH2kpLzEFKEQ3feIzEeEgBqe14i6Js99UzUVhjUUBGPKxQPCz+TFjCKwgwmCiHmhVlLDaRhgwumqiGH+rQF4DmvcAOEP0WHl0GEB3Cjnb3R8Tv+ywGKCSfHKiRD6qR/+dQHl3eb9q7e+sFrweJs4m6m63hfz2YGjpi3HFb1ZlW8qpo0ENecULad5rmdppXRX92MK7vyXMtpppPqHhyDrGDYzwRR+AGkMsWqi9re4JmLyJNMaBn9k686IRn8mxmop0h8bEDvngCCK2HO8kfcNOVva5MMvDemrdW8c8J485mtGH23q5nb11KpfthSzqghbY/1XH2FzZcbKkxKRfQE6R7dkcoaKCz92SfaC+vYvS6ZwIKDVjWh77UVzYDLv2snXaAtC6fQTo+xcrdj9mFOIH/MfS5nir0X56H7EpeZV/VURe117gHE824sm/jL4+XPCgpdXWrW37w6CwUJxcqP3l+bly7rzPUagx9+WTCwjcYKMXb9mzqXd7qp5/Bh8AdFSpvyW7Ld5/snH1kC/EAsEZdvWC6BS+XjxWt8XnOHzD8oKO8ddzd3Mwsd6VedUxvFqVkU2lffQeLvTREoL9EutfwOb8KArvVDOtttm85zfJ1Oi7lXRYG9nz5zc/24HTNspA1bsjFeIfYwHhcXjE27nnBWsx5m95uuL57rPZgzF8LvPA56Reg3lWHWH5AS028FcneuKtrr2pB6Uyc1JisMJ1J8qZV4Je+UtqsuQW8xetCBKldbi9Y0pzfjjulTYfzWOEsoG9cXx29HD8NVbz9Q+7M7R+6z1JcC+Rib6/CV1PZFKMUl3KEDno7+kJwQjbeoTkZJ/dwrHHDNjZyb1PkEl7bWbBETZRJelFwAU8ZrnBOlAF64WpDGu9emAUc9lR1+Nh7e9PPlrLshaaklqCyi28EeomDqp8PSiryJG8NLJKRn0PSngdB5RYYlJYfq4cksvUfzSH4IjaqCBkg5GnsDWLZBUVNDkRll1D3+xAHNTe3szcvQ5hGr601JxJLH002qS9qOzQn0k0fzykuiCXtKqDrSNXTnih02S+TzuzcbjHxDhn+3HenRJQqaWYTf9Ox/Gdo6kWDK/NH/N+0YndjW5qE9U2lDtvrjUZYM5tR2ODzcvRcKOzcuos7VVdDNqtmPaGkSfWIa3Mz69F1ZUmV00Xa05Sbu7XUdTKujomlJfCq9cRWQ56WbFG1LVlLAfayS5Ugra1YwcbYU5Sz5QHr4FhVlrKn5Ue7ClAahlzPZtMfL2O8Y27pXCKPCaV89bLzS+shvgiT/BvjCNRPrGdxE5qPjjES74bJqKbD9LA+gyL5mw5v0vCbqEP52rN70oujzm6cTLrVnobM7mBjTGq69jqwZFfl71rtNi3VnSukGFtbUWQKjF5LyT4XkizZamMkrrtQN42HjQhbOgUiMz0+m1q2p0NnL45C1/vtvSLLvFlPdnLd4oilugBbqiYPbUKE9ES1o/vGjVJq3QcjLRbjUhnls/xmbQNzHzqnqor1alvRFTaX+DjRIuW2ihWUI2oypAt6PtZqoTOFJkrJu50YLc016OAU1WpWB499XO4ylFVzRmeeeCoBHGV1mqL8u6q/lO3AxksBmZrNbbgTg8hcWnGebQpUZcYrRlwrSmFXToXynTpWpcZaFxn0E0plo1ea1e76FnQNmDOFCWehTVpSZVMY187UilWoEybZKyus8WFTUxCQB6Qa81xlTpztaGVqhGEKEy77F1oZc1dPoZXkmi7WNOkSNiRIWnFGbci5IjrwtCcDVB7CEWuV3tpWf6Vi0/9eIJQ2tFmwaJXiHIfvBjX8JjBn2d4d6snQozCaGml6kFdXOiyOCEuPDnlSf9Ke8rwITQBEXr8U8EXzo9hz519dnLuWxXFVpd7zdG0Obw/DzqK065R9InrOrkh1M5cfv6y6HZRtYBRTeogr7awNvDE/ged0dIaSAMfkP/r6tz/DvZ+sJUd0k5dKcW5SsNyA/jBZMsSSIUdthdowyqFpMS2BqrGrTw3Nepr9gdEQOKJNMpKArzqdoKcDJW10sLb9x9EoyLB2ac/7waA9PnvE5f4sy6tX3pcrwKpZk2huD6cXfthfeh6lXWWvPLQSLCvF15y8P8dQG6QIGcN6Iq1b51ZTbhpx9AU1dViz74pFDFPgWbQJoBayqgu8PncB2+VLoDM9v8H+El1qEzBhwuCCHw8hPuxCdcOqb7gliu1+8L59c/EmSr0ySqi4ri9S4dH2GWIHXK9m8a5l4m3CrklO4ngkKFGT55qnKmHr24Rg5F2jXX4IFeri1aHITnl2k1Rkhd4Xi3e2Rq25Nb10Dt42717kfkMDOJSbpwmKUGfYpVl2YdbhILbTl96ro8dXvtTLbi+2vzt3ygloHE3AJLdk9O59XboYqlqhjNQWHCiBKl8tP0o5byhcrDoWUH/n1PvpamCG1DROeEUqmXSjzLuo8Fm73hrCyNKVXnHG0FW4M3wws/sk2RadQmncdQsnres7ey1Q5aBWSqNQ9meHQRSwd9GDmd0wqDsGNUDqTMYfBh49KFyX9oLFCIE+PCSGPVUKFnGPasnqs1WT8njPuyW+DEViLrlareBPrRDKkD34HwtO4/aMir4gdcQOmaQHln0QeekT19lzgWoY2Co1OHs90MgQf6nB9XKq0SdJATHL1TQ/xkdtwvaemKk9vFBteoPabqUj0WIF4L412DjWNgHdALHA45ebU0lEBTAGtk13IHBoISKCajVJ10frLnt5g2SqJf3QgfesTwP20Ro1g36i15XPDnKoXEZ/9misWw0AcbERcvgclV4UBVBJ4Nu0kBxi5QB8SVDHyMXSPi9g3F4dAIteGLEQeVWhF067/kaOVxh+CTj2ZUy+aSPcLkg+wF1FwE9ESkTqSG7Pa6EoIn12bf8ZHHkdESOILOroPDl5BK9wbyiRnNx/rdhCfKR8gI+0yn2GLOKmzx8oycvDnugoNvbkNJ5Uslsk5zwwwdwROodnOTEH89HC2C3y+R4dOiFB8BD4gv/kgQLhLMFMmPhdxX1e1GUiaeJdHHwp8mPCFGZVx+xYf/Y7mL1+c17MPyaRXG6jnKJDeSyVhqfxNGi7jjnq5mEwSnDsyoBahAE6h/lwChLGxcFcXxRnCXtNkVGtgsE9cHxejV8Pe03WS5Z8YPdiA8gAXE0bAHtp8glY/dqU4RFcQJV9ImTAKsHznKjnV7Z0yGXwP9XfT1l8Hwk73BI/54+u37t82z8Z7PPeT3dVL3qQXl8hSlI+T0F0PymmESddPx4HMz/OTzc/Hm963mU8/7g+HH/4or+cxt/0fDLejvhwtlY++/i+Sh6g53KW8D10IDiYDyEy5zq/7+w9D9xg6QEiiULQvUUR7jm5RyFBE9hIbSOR4h2xBDIzOvdIbwtly8HSydJXLuCRguFa/cYTxBICn1lKiBHIQHofYQT9mGTvzwhwWGY4PPtkPEZH2EHjgH/c6QkFjMoTV/ChtGG0A6GTRB/20XI388wPHyoBLU/mMKmldvMjfty5HRPbMK2HOgUhcFXhZkEo+nBnW7/nT+KgbXIT8Gr4hJZSwfDHP6I+Eh3k52yjiUqMTOrZ4dCD0zr73F0TCDHcIvxbDs9b7FL4WManBfY4HPBbT3tA+xnaj0+QR89QfcWCu28nCdC7HTAwGNH8PIjXQQlY0PtV9r+GSBzkDbcdHqDZ8Chr+ESDB/1UBJKYRZ0DEU9qk2/JAwjdOuGqCVpxQbUe2Hy88KKAAFGAokakSrkVG2KiPhIwZxG77eQp05OvvRR75Ez+0mRKS1XKASGP7h1mEcaSColW+WpbPpOJM52aCChhqUArTZfogrV30sK0Wp2FGStotg4laai05jKhvV+D+EWEQ+AV6TVI9pgceU+Nf6UrHWZebNK1rEQBttB0Yf8oarqy1Z24P1lWq/UcJ3pPjX2lJ3w4i9C2EaWA1NUwTr6RQABkk4TH5YB0Cfri5yNa5hHik34ici5EDD4gSUMqNdz+PF2zaByxzZrhK4dPgfPoHjI+omE5S3BCdEm+HzKGB11gew1pM49PTBOWBLro8NMiwwN9oFAy9pp8BaEctXrrz/mF9TrqLulACKWI02TQ2j0QcV5oV5tRFVpQcZ8nN6IWrztgD20etjUX5ivogq3Hz9qU06SB591TKDevQ1GN22k1GRPRW1Jdoq3Xn/nnV00fhTf3A7Sx15ZzJHG0UZrbqFQ3QQHmgETKSdDgg9Gy+AD30nxWILLtcBsj7j7+QWoFGc3sQwlTJ70slDwHXARNihZpVqIYzJRduLX4w2lL0coGRKovd3nXGaltEYewFGjqsIbY89fk5m7WO62OjpBsTuMBuw/g+iuQCt9J2gx2o4ReEg/4Phyx0B9TAqo3F1CG6E8krbg3llS/+5kQMZzIKWQaAytKiW8mQYnSVav01WBZziY0fv7wPWBDLjzJAqU4qfpspqKESnsP3RZ+5INuH4/sNciuEK19zMbKp5mwgFujRFAgiVyspOLDVxB570ssmAVWK2gG4yt8Wzl0gKTjSdB1nu/qUpgcUifDdBbIZsefPmw7OqhpTCTWTtrRFDGS2YK3Q8Nbf9U7bJ1BW7u7L+HP4MVYEs8B0ddiEk8ltG4KyJ3EQFv3rfpbAMp+tjqleqidSyJPJdRuChYSyJ3D/gneC+ChG1SU0kJ+FVBO1dwPqESFXGDQdZXcYKAt5VzS6YhBzb1DYFBKitk6IGMUMzU/G8mE8vCvdt9rS9nLWiVDJN+t99F1kUk1epNIeqK+Pg5tIYzSiGpn7X4X5fNgwS0nJQvAjNKMGqScn8y28BMikHc53gwiG6En7xm9/eoQ/kkPvhxR2rUsw002jPnPSbkIsEYKuzlTt+vxrh0O/8DMHaHlSJRAZcwAG27dxnBwn0wmK+slH6S5W0qodYwMfTb54KsUgf3hMwMqa4jcT1qX5Or9sXqpdKsfif4DSHyEZCRxkNftgeuS0/bxkRU5evTQb5PAeC+EAVE72jFHyd5oTh4jtzFRCT2TvVB7wjt8ob/mo4ZIvT14JfSgn/m3RAORdd3+uEp5qety2UqAwgC9qseLhXBZsvF4OQ6xLMNTj8rPDyVoNfbrQ5aZ6x6XSg0jvE0P2CUI6FG3woXFDSIOX40lJaJiwqDz0D7QWUdU+JHxmo/vWsRS85yVLPP/toppm2GmmhKD0E9m7Y1FISqpmOYOlkNHGqspY09pOVICKOp9Him0vumrJMSXwVjwiQhNrVfFgrGEg7mYLBCEk2hYp2mmAoihTY7QnjloD/uXRiSAa9cPqcSgQkS8qaJsUyFZGPumlmVk0IQOl+mfI2yW0mPK9A+ka+0pPxleJlZrxpY37xEtbd7YRyvXpgxaEJm0eBtYkO/hlqUnqBkQZm3Mgxs9RXsEICp0WjzrdXbI7h07bLDqNglf+mot1/F9LMdrL5JnqJpCQwQ1ELbYNuSRB1MILi2MK6A21FE3lAAKGWjZzvg3Dw1i4EBQPdMlmGSsDVUv0+XZSVQj46MCqVn3Ga0GjesRUyyI/6xTb2xbTMnPSXLHH4iXrYr7rov7BpBiQ46yItWuiudGRIFYJXDzd/zFhhT/rWmI87UiViHia4kLjqvkPOT9rctlZaRaE+evR9TmrrBiUJ5inZe3KvQraLCCI+TCTmtaH6XFDdXJJp/zy/VnGplLL7BcnnnbpnJlsxoa3oTVHYUIkk7YGksJCxbRPjoGdqsjf44rHR90jyJBk89QsghEpSDeWyRElT1IspZMjijiykmw1giJ7R/pQ4yiE9KpfCFGcukX7+rdkCxulWyf0zzKPR3OGJXhnAsPfa0LJ3zPsQHY9Q1YyAA02wKeda9+los4GdA/DHi0swJYbwCejYbn52JQfyGtfpS7TkKaVY3UFI4M6CcymSM3xkCBMcLohxi/2g59aPkg6DdaItPRi4p+EnJqxs8P4x06j4CrhSufIFkwVjxVnHdFoouILKxIanQnyAUMvUfCTNr9w3WtAhpOIR8fzGdU7bHNX5D+F4fZ+u/wXLjZpmMXLVkcGiPLHrLJQZoosW6bHgPd1vGyd+Tw+xzutCzPa+NMMOxGd9oB6XYS8u0bYEQea2Bl0c65tACaT6GjIU7RYB/GIi3YMFbffmkArsGHkVV8f9KVNiNp478xTSJkMGDfw0WPJVr8mDXCttFuc5wE5n/Ma+Wv3LoWSvsQPboEcSI4KvR4B4ebqfkc5yrSZyrTsm5xncFs6gsBlp7B4kyN5njmRTJ9qkqsx8XcQd6EKZ+CtHEzKlo5E398Lv8gqvpmMx0WKhWAF5AtPA7ieIimy+hnxmlIR0Wg8jF4hSDdDxH5iG7KePwLPWmekjps4kGKwC2kdok1psM4KZuP/grV4/2AiAb6g6kVIlMv8DUKvHwH7sJ75sd4hF8KbjB8EqP+TvGvHHy4m/4rE1ALwMd2JjL8PrbpfVY2MQT9bZiw+iv2Zs1x6SdWhlMiMATD/zA1IVwGW7F0jhWf4Tnmct3zEbkwzeiEmNiFk6bu+RzgsT+Bz6SKpxl5ry7K1mOyM0wJUkTtnehvey6NzxjW23z1EV3RBxmp69MgKSvP3XwA5JTk0rt0sYWXqNZPOMPPePVTDfmUEhhvU8E/KMU3LT2IbTk6LaWsEpey6BW93MscBtmZy1U+5AJzs8c0Gd979NKVBJ1J4D/7vMq5YlCP6n7dyrlkUI9JQDwquabUjGFrk/oMRRjUk1uOa5wGeHUD9IggqVuz5f3SPGqV7nWa6QseZW98h3bjFFpYEuC5pp0hgneykuSR/pDUMPxwTf1YtGNhE0p/zOdG+ZHxDBON8QxHNQ5ZmkNKUtkC7GS4QNljQCXgJ7Ud9Lhlw3pOMXXUJDdnRknosQna4gLugTvEv2bh3kbh3lbh3opw76m4DpW4DpmMJK7yPQ5pY2KCPNBjTnH2WJGACEjFHmlBRabzQJdAh+N58HPztz4JMgvODLWsDsUjrFM6Ic36QyY9uGDwWW+g5wMw7Cfz+GXOGVcNaLSttYfZDC0+G+gnbOkDEf+atJKEEKp4yqbxneQ6v3016b/iCD36hBy52mq+ADQO33ewVdV/Xkd4xuJFw/J7uACs3wGakYFdZCMmeyRQTdii5ctxkFP7m3LGh2WVkx57dpFB4pV0l76b2VSyja1tkyB7hS2AJ6nbtJhfR9Ysl62L0rcNTRthayCns+ZTYA21iP31zDCptG5OWF6+1JyllRxz1ErIER/qSVEXjmO3xNg/WrDot6LPlWkIgGhdZ+ahJZvIHEynlpKJMRInmbhC5NCwiVn42zYFB7TO28HqRaSBlrz9jJm8/UfjOkDXzDO8idWYrH8R27Me8sJMjuHCTlLUqQ2esRh8nVIrpLnkSjMpW9t6hlyVxchIhQm30gJMyOHdapF13lR6aP6EdcPeFvzyL5Q8Fhr5RoMLc4PF+2Z2l5W9Cr/RQTmBV/Lq5FzxMbsZrM4P7eqUQej3DUK7+0I7eC6LoJqt5h+nJxFecfgRsFweLoCrV4BG5ADnGQidrrGj2aVuQZp9KPCqvIsdkAGq38tY/5R1YHU0ieTpueiSmKNRl8T0M2naqVQmb2nk7JDL17pARxh25u6If6rY7PAYCCoZcvzdFYK131H3Va0OtMEfJ8yZ0Xo9xHZBJFj+zk2cdhDgdeYNN5uadZau8sDqpei8CTN3VCHRUyiKPMukINrmmvXo1SZMxLyJ2sdQgzMdQTX8R8EDK6lO3AZkQlLBFANcBhNc2bFQ2heB4Ud+LWOPJesOphAXxXY5KtWk5rpyJ/AKSSNxSB3zjNkkVkF0j0PgalZGY3JYrsqgCtipagqnK93m9nIdLrUhV+/1y3+Areu1PRTJ9sHJtprF5VvdM2zj1ZOOoJxJeayKBDJ+w6ijJfxKUMxV/ONqxuuAoOkquRyg7fn8AqBQVLEO1YvR5LEO44uylPKafokjpBvjAfFXGXjPnXgLPNpbTthilZ1H1jh1MCXMhoBV2eY86CEqegtyH0w00GnuxX+WDZOZqpS8i59I+RbOm7k=
*/