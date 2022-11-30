// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2021.
// Modifications copyright (c) 2015-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INTERFACE_HPP


#include <boost/geometry/algorithms/dispatch/envelope.hpp>

#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/envelope/services.hpp>

#include <boost/geometry/util/select_most_precise.hpp>
#include <boost/geometry/util/type_traits_std.hpp>


namespace boost { namespace geometry
{

namespace resolve_strategy
{

template
<
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct envelope
{
    template <typename Geometry, typename Box>
    static inline void apply(Geometry const& geometry,
                             Box& box,
                             Strategy const& strategy)
    {
        dispatch::envelope<Geometry>::apply(geometry, box, strategy);
    }
};

template <typename Strategy>
struct envelope<Strategy, false>
{
    template <typename Geometry, typename Box>
    static inline void apply(Geometry const& geometry,
                             Box& box,
                             Strategy const& strategy)
    {
        using strategies::envelope::services::strategy_converter;
        return dispatch::envelope
            <
                Geometry
            >::apply(geometry, box, strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct envelope<default_strategy, false>
{
    template <typename Geometry, typename Box>
    static inline void apply(Geometry const& geometry,
                             Box& box,
                             default_strategy)
    {
        typedef typename strategies::envelope::services::default_strategy
            <
                Geometry, Box
            >::type strategy_type;

        dispatch::envelope<Geometry>::apply(geometry, box, strategy_type());
    }
};

} // namespace resolve_strategy

namespace resolve_dynamic
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct envelope
{
    template <typename Box, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             Box& box,
                             Strategy const& strategy)
    {
        concepts::check<Geometry const>();
        concepts::check<Box>();

        resolve_strategy::envelope<Strategy>::apply(geometry, box, strategy);
    }
};


template <typename Geometry>
struct envelope<Geometry, dynamic_geometry_tag>
{
    template <typename Box, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             Box& box,
                             Strategy const& strategy)
    {
        traits::visit<Geometry>::apply([&](auto const& g)
        {
            envelope<util::remove_cref_t<decltype(g)>>::apply(g, box, strategy);
        }, geometry);
    }
};

} // namespace resolve_dynamic


/*!
\brief \brief_calc{envelope (with strategy)}
\ingroup envelope
\details \details_calc{envelope,\det_envelope}.
\tparam Geometry \tparam_geometry
\tparam Box \tparam_box
\tparam Strategy \tparam_strategy{Envelope}
\param geometry \param_geometry
\param mbr \param_box \param_set{envelope}
\param strategy \param_strategy{envelope}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/envelope.qbk]}
\qbk{
[heading Example]
[envelope] [envelope_output]
}
*/
template<typename Geometry, typename Box, typename Strategy>
inline void envelope(Geometry const& geometry, Box& mbr, Strategy const& strategy)
{
    resolve_dynamic::envelope<Geometry>::apply(geometry, mbr, strategy);
}

/*!
\brief \brief_calc{envelope}
\ingroup envelope
\details \details_calc{envelope,\det_envelope}.
\tparam Geometry \tparam_geometry
\tparam Box \tparam_box
\param geometry \param_geometry
\param mbr \param_box \param_set{envelope}

\qbk{[include reference/algorithms/envelope.qbk]}
\qbk{
[heading Example]
[envelope] [envelope_output]
}
*/
template<typename Geometry, typename Box>
inline void envelope(Geometry const& geometry, Box& mbr)
{
    resolve_dynamic::envelope<Geometry>::apply(geometry, mbr, default_strategy());
}


/*!
\brief \brief_calc{envelope}
\ingroup envelope
\details \details_calc{return_envelope,\det_envelope}. \details_return{envelope}
\tparam Box \tparam_box
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{Envelope}
\param geometry \param_geometry
\param strategy \param_strategy{envelope}
\return \return_calc{envelope}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/envelope.qbk]}
\qbk{
[heading Example]
[return_envelope] [return_envelope_output]
}
*/
template<typename Box, typename Geometry, typename Strategy>
inline Box return_envelope(Geometry const& geometry, Strategy const& strategy)
{
    Box mbr;
    resolve_dynamic::envelope<Geometry>::apply(geometry, mbr, strategy);
    return mbr;
}

/*!
\brief \brief_calc{envelope}
\ingroup envelope
\details \details_calc{return_envelope,\det_envelope}. \details_return{envelope}
\tparam Box \tparam_box
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_calc{envelope}

\qbk{[include reference/algorithms/envelope.qbk]}
\qbk{
[heading Example]
[return_envelope] [return_envelope_output]
}
*/
template<typename Box, typename Geometry>
inline Box return_envelope(Geometry const& geometry)
{
    Box mbr;
    resolve_dynamic::envelope<Geometry>::apply(geometry, mbr, default_strategy());
    return mbr;
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INTERFACE_HPP

/* interface.hpp
UylFLArtSEzVmga1iJdIQlnKz6V2qxEvlfpEVWhUfi41y6kpxzJ6EnLBym6cBIA98wM/X4GSssA+g/sExkm07cBKRBhYSfFXIXkcnh442r3MZT0h9yrQbJpGTKeW7jjU7tPCJ3CN/BsIoe1r/IRx6RMbTQuxUDox8tT7akLoDnWp+LrJ5bpbeP9oYREvsIdP6g57OA1EVnDnXRwLUZg1d3S2BzM1yGFfVcfDLsgZ9kBm2FRStuFm16oig5p9WDMsWEyu69CKzuYhndY+Pnu3IeeYztT7ycAGsFQD4YFQV6I0N49yrra+imOCpwPrQUYHIoOhntVQNKrMq8unrUddgfWyopOO8IBeJMuaBcNpR3iQnekuExfWDHV+mrOMzTHutLnZ8wLryCHQPsAW4Ii9chdku7J8GYfy46g+gfAJfZTp/ZQnsOIt8cysr2kZMX1ciDUzkpqoONSg9bKIxWqkifWyIycCe9QL1GXO0N5EAQE07a8mP0enFoE9Vpqfl/quIT5Zufvo10nqDG3G5Y6wr+ItRB6iDlI3vY6wX0YfWizO3IBl9n0FrKelh9jgE8+zO+EX7PqCVFhIL7Ai06hscfpSv+KR6D/yiEdW+G0WAZFZv9FQtuwMRYQO7z14GvA8TvRAmmHuh/mdadZ+w/HrVVTSLP5x0RljHc16RWeyvdy+zLOpc/vVncuG4p0Lsod6lKMXsMO/sLviU5pxjkqEoIW3vFYkORZqnIObFg9VcRyqggi8k/4toH8L6d+S3KhzwEsz/o6mZZkFbLKj9YoKp832Cq6mxmZp68KG9fRPHB9z2og2itQMOq6JzF+0SHVoD2K0MA/8g0Q+iqOstJepkPmrbCVoRYGQFr/HWYdnyHxDfb04SMUSY2G6CjMgx85Q15p6mD0QqlHq2fCsne19SvWp8ORDeaszeas5bwksBUNAIzfcI/OW4Tu+eTb8nd1U5qnhoKL+jKqfp2Mufer/LhF8iHgDkaKpuGuRtlfYzfERIrjSul7PXlUx1XJIGt9Dd4s9Jx3sDG1LoCeVR/q0jwODdEdildyUD15o3UcKNtp/13Z4J971lRhr+3St50gf56uX+VAa7zIvZgFfZJmjnwEvOHr66E79TjZUWVBaQi3CeeX0TIvlX9Xi0c9o+y4wy1+L2Wu/wmy9PKf16XjPtF6WbV2/98hBjPjoQTiXmunRJn9pyGBsSyTeNOtbZ7vi85w7x4giSSUGQDsc1DQIe54RN4Ums+p1PNIo7lr7hbFISw8jTb586AujlRA/uiagxnuvyoIii2qU+ovDwl1kLo5//SY2sTdPPx3HSCzFArXG7CXxTfheAaBGW23MPqbXFYy4O8Jp0NwzcIGpfOJrfLo7wAHGYW8ciIpFM9k5zniukd5vnMn33Pk3Sz36fJ5Szn14kczX8Eu/7RfQjCDyJPeKcZxa6jIU99od5VII2iwxsyE8AmYRpF5Dnlh2RCMdYRc6fv7wjrvNjr8TFU9Wy45zQXrfWM0dWrHcL/n7wzzjQAXrN+UmHZijwhuTBW/ngkO0cBNum3nPHEwlUVZLs3/lidEcmm0iVdAo5j8DddnchjE6up4yVOGt8I9/DfvH3x8Vx75Fzfa1bFpGI35T/HI64/9jUC193M4fX6tctKUNRsQPyq+Bxmbx7HRTN6NA/GlrEWitu0qYUNjlgB8Fiy8+GozBxf3fnT0pT5VG+7iV7oCjT1nc/wz7wgMagb4xlWCy8LfMnpS7Vhw1osLQPg69v7ogmHAnCsQK6kHwNQgcFVfwNUhSFT30fvsk+tr+AS0/YWrRCVDUoR4b8WJji4959RBLVnQuUl/LSmCrh61ZZvaYAuqTshjQcrQcNPygTJBTqwRObbcxu8gopCf4DHAYtU56dPLjXBc9uuSje+2HdoJXLG18pnYf+8Us1O6DXAoh/+6DXOqyWpd2Xyk/uNd+DvBWwnQFrfhXv61je7wwWes6rVcmC0fqV5oFC82KUEGpVUFxXgXOZK1z5FAAMTk6r4/I593ES5nbP0JyRCzmRYbfD7P/Kl7YIeyp2I7135XSHPA+TDZ5fKYUp8ijR8p7bFI6oq0/m0RlS45E5ecsUckNEskAHMP+ITg9bwaCPNDaxhpxYVPKKKT0dRyK3/AaQBuW7HuvkTHYWwDO1PcufleK2dUK1CDk93GA9Gfkc4HJJl6cx9VmceWKYfLF5IyVe4+3cXDzZjM2kBKxWM/GxgF51IaMLbC9bjkM0+3vXGPuIt9TVT3HcfufQwTjj77LR8o4lJ3IbOuo8XD9iFy3s63+rQd/dbhN/KwRahmE1rJipzCuSf/ncVCz0RG25OuEJhF4GapyRqF9KN7+hZ8oHLepmjIgHn4ibUBxEwo2hHoqE1msLlo217xEVXz/3NNG8nWvPsmSt4uWp/lDhD/4VOUwEZSt9uZU5DArDd5dUwh1J9oigKConwZzNevuRA7nakCHByDJ/sFTaYMIFDwuweMO8YdGGU/EkXoQm4kuq91YJSO6BEl9nPRCDTMrooRkpF6CqkVzS6eVtLbbNcLkrSkn6PsGwUX2md8XImmQkwbMJFS8AboTDS1ncpOmcS5XOCfpVk7yWUm5xg39o08b5jDpKt7ZX2TJVK0lss2HckT++gTnyfU5xOuzFOuzW1z9XP76fPL4163PDv9XrM8v/XJ9oOJ1rLHRWp73bpDLk5bB03xA2k5lwoewKghRv7tD2+MXaoWNGRlDbWoDz30GqdMrxSh7jnBqChDUzaw5xfg9p6vrWe//xUZLFGtsWSlj1/GqUvvVRC9tyFlVSqpEkovXo9NKMrZITr9cR0qpMrYMypQBM6UagoqRcgn5dcs0mYFXUKbcagbOs1IqDuUu4ZTcJQy9ORRWX3kiA6svPMGwOrmBYTUncG7qNalAkUEerOlxxHST//ekPOKKTBanyXCrivmHicySrwEqbcptLD4ZSX2Rs4CYd1TDuZrXnCd2CQVtTBxvT/3qcyP5mmS4VWhSujJd8gisoDuyV9Fm41EWDG14QfaxQDw/+oyRh3SAJzfxukmZs3tJni4D5MpSrLhq8Rnjv32s55F9Cdd5OEELxF1wJ7VbbLx2km14BGh1rds+XKH7Y2v8483xey1UYoRUYIDMUCK+t8rj1PlVfKF8LPOVa6FcWf3AS23iV1fKI9sMPxTLQXwrDjWmwicymO9ZQ6zcmxM/OA3GSPiEUkAkNKSfja0TwcEhsDzR2NgomeSSWo8HaCYSJw0DZoIXyoXT7M0ED82iXfnC0LyLODrOw1iU5YtNjslHVwN5H+pG+VvXTMJcDCgVWpO7WbuaFYov/pig/gZnRxfH6/HLx3HapC4xMXnMzpReCa0o4uO6hkXm/dlmuEkolCoqtMaz8lDwazRmFElejzYxpr3GDJ7XKqUU2xkLdEWNLXhjfWbJA10+3A6t1Wj5wfWHs2pd/nxdrrJM2FwjOMNLlyn7Qb+kABiNsfFxqv4X4OcqY/MQnMPdRLO6HyH8XvrOLDcmPAe7WYSvEIEN/hy3MN97NG289iBciO+oKa20i1//yc9RsTN+xItFn4/9iMM/BTvs2PXLIhv7hrnmeaq09Scxjga///cbWdv9tj/52XtMTBb+Fy5MgPVIl9ZF6V0o2fpYq80s1MmFgvmFvj+k0ANc6MeZQg9xIWd+oavyC3nWNRrsT8bXujlT8GEu+OYf8wqmxw8peK4ZgzLW+qhVMjV7kOan3CbWPUZnZWauZWxE6GcQQvkTOKaAd1J87ZMr4bXUZUxKAPk25+Y7hlpmlMtQmWXZWujpMfPJZZY4QGmP5pZlerjlpJ32758Dpuczn/y0STY/zlRmG5/c6nZix6H9H+fW0SYzXvAVLcu8B2Re89wrpPSf6CXZ/kOXPbc2mg2XWYdZMguoo7PVm2Iwq0jO4NjXBz4OSuzyQkL56gmKkW6BtujR/DZtR/+5OPPHYGtodm1VCYwhZEgDjixa3AypuDyllYKKT2v1LaYs7aRckIGk8WPPOqiOJo1HPetC/LDZs+4SfnjMsw5mb0njJ56OzRlZkUlxjkJ04ILThj5C2x5l9Fv8YKp0WgSRairjkElGiev4NJ7IRjVj/ytQ4pF+YfFEVS7hfcWZTspGbuLYd9Cu7JURYynt2mzAOQLXDUYG33lOpnR8ZGNOVpRPOPiK6T9k6TjZvoLq6X854yIlbjK/ns3R9ppmSpz/2WZJILGk/esyhdi+yJTTsqXSrXnwNT+Hoq8px7Wz4DOar+sus/zgetb5YTcxFK4nXmbeS+tOf2Egsgua7pNmqjQc5Ba4BYdBx7+qlhCvLFerNIcbZc/RTBjNY/qfmKrteWqSiitGZKS4uvC0oUnF46STj31WP066+BmXdkpjDeukm9lQLLsApzy1HpLaaEpjLeGps0ZABLd2x/3s5fV+C7W/dzNfDmoSv4vz7wio/yXvLrHFC5f2r7t+ki0fncH9JLdgnCPpZZEycwLfvdS0mz4ulw1yThjynOoz8ZNkWw0wi7oaYLzZqrKm1VuX1OVpLbMCEbUccYFBH/aqRI2HfWqtG4HA6I0e/WpteXfh6joEAyuOpdpr1JHqbKc626XOdqeWLVAd6iynOsulznKnaleIcPwzI7WeY5NdT4/JuaX0r4z+TTOS359uM114G+8kv19NuCj9VNqS36+yLe+uLblaRlVYPCR2y39FxXuUjaiY68MZFW/0tsKYDRtCaOXLDqntVeKNVdQ96uY2+hV/C0/OjWKozfXGKoxQb3yiGMClMddLzxairbZ7tbk+/tjLH315H33aXDclTAi+DFaGMiZ4d0kcRn3RFrXdncMTIDw82Wsk2522+BhtrhPLtJp1N5LtLlu8WJvrspJC6TVjcl6Rw0tHPvUK1Zbi3WcjlGyuj98p+2jrmQio7uXLvk5BhsMU8UqAT2WGWwZuMUTpIM9X9zBvYe9I8cM7ZuRkrbZY3IONTeM6/14Z4NxPk7JKVG5m1qfNq5wTTLiVwuDqUn98CZfWap2g28yqLOXuasQDWcBdYi/iMKuRwiooGfSAha64HOizjGQ2ndPKOQ3alNNp5rjl3z36FS0XU8suq+XivJZdX9VyKbdSnGkZijBlnFaSablMO//1yVuk9j3ivUIfwkdzw8B0lfgwwHdgTmfO5xWNUZvV84nmlW7X4BTVLAc4qxD/NqzchdqddLnE2EER2OLDSmY0HtRLz8a5L7GCMS4rJjTwDz8rgg9Y2JhcSOvI9lcniBogwl88+zmvqRp2EeFZIn7wY2tKC4DqexiMU03HrHmaK7NVD8vmQrZ0JptXkhyU+Vyxa6p0JIScbp4Q2P4ZUT+NX0r+ONsz+dl8yCZkNjei4oBrJbofsRoeRfk865IcC1g4r+LTMKSFj4XC6TUOaHmPDIYH2+lpEE8CT0IdqdW6tXtdzEMfcEDie8YRPtGvsRHGiVD4DIqeoRMwGD6JEif5cQCPA/SYU1o4woMOiIePqSP1hrx282sCcLwZ94kdl0lfjdwhWTPWH5/+LfMJPeSWhgUlJWQAp1htcUycPM1Llrxl0Ja85ST4jjvjF4pfbrJmBlFJrYUbzK6IpVxPuSeL6ZdJV7uU1VqSNM91eHD5MmsouDjs0KmwRjPT+ZWdWs6dcg3plH9op1z5nfLldepnZbmd8v1/dirXMzJLnbWD2pxiolaBIqjKZiO6WutpgaWSGtkoqkom29Twk5B7rt0BpoZeuHYHrFRSib5nnqnofEalRbF0EwALLPTTUmHxjHT/FAXyC7ViAew36tMiG1lO/VHYz2zpS+hG6liNu2SWXw0/QNMBpaZecfASE4tZ41cTD3QYig59jefU8PNq+AU1/GIq/BzCHBjxycAmU5HnGphZxtU/FxUbUD1rBnR0to/U0mr4aX2UlnghkHhOTTwt6fqOzjWFWvjFAKrcRC3Q92OBRB99TyY2QVk0fCIQPkzftGtwLLIIfj9zfjHSPoI/fbzZDahWo3OU+Dy0eJTNWmHylntpxdZR3+7N4E5a+N5QOuGg3mjhdcHwJjxugguZJ6XRFZyzRe6P0jyLI9NH2FpXaOlloS/jtNCKo/Xq5eCFT5H4MHxhBGe5Pet+yup+InA5xGZPapH7adZmC8QmYVoN2ggDgS7Pr7sfO/WlfokWOal1gaexP3DA8+ttlKbtoYRtWqM78COXVBMJ9FCn1MhhPSzuylQzCA2InGoGUY34mmoEVRPpw0gjhx2RTa2j1cgJLdLniDytRo4ZE16cjHi0m7VxNNjHIYjsixoPS42gzTSOlNKXSvQgPujba7v2Mc/z8WfUpq1q06tqU6fa9Lo4fN0IW8WnoW1xnzbHG9odX2gom0UpXbz9t4I2meML7VYGtFkuiMEvZiUXaiyVeDoGOUlUVZ42Hl7gQKzGp+Pfo2wE+YbydGiHUp3scoqN3vG0Vk8TQqfXarMQDHP215S/mLJY5QnfQWzGOn0s6qmz6iGs8un+dxgCNuMN/VJcqvJkcJUvPrI7DPQWrjQ8qcjWHBbuOB4H7QJ7c6pp63wLwLdGxS9v8NuCq9zx6bT2V/K1qM1yEyIUOaFGdplnb5ca3qeGX9Wp0DE10pNN3aOGt2pzXKHdng5YfVEj/WwYgb65eLxm37xf3zfv2fs2zuxbJfXtn6eifjcrEWEz7QusZTojvEsNv64XaWECkT1WGgFepzbHSbVOMJTHrYpZY4rWX79AtjgJdE6q6fH5pv7vVpbPEmU4x82Ia0kw8aRZQSzV1JNTQWFM1D/kt6GTADje0RNeZ0iUp9JPZ1LP/zeOI8+6yaw99QBcDo21c9Dt0CnPOgce67xam49O4gmtjkZxlUuSzuZE6ReAUoYhDn2kg6zIJcnMd0B03/IkNd6Tp7HFfiUsLlwy8aQtXs7aW3TnJjbRNGns48BBm2mffhPtQ0fiaZqobOoevVLWgVJUhI6lU+9jnteb86z7HDjxBFL3WKk9POKeqLilmg7Kxe6OQ/GJmDE+qnuYUWFOmhZ5APfL4/Mr3g42PenZtG1+zIguoLzGhBcwc+HNWiQtdRAuuWAoG3O4GZe21Gs6g2qnw2uP3TRhylX5BLYtLSsQoxMoKOF78VnBdm+8JIMm+hng+EJeUOrG5df/pPSTgwVrk/rpviy40jWvK8F2X3wBX5g5VfiyVRCC9OGlcrleMONqOsKIc1Wi7Q3sYUSekGJP6kX6SPguYjD7+5mnUOtCs/azNOuyqucLACN5jJpZzc3EL4Lyj2wCmi5Ap0sCXaFtiSYHYjaX6BHKG+W8CvIWy7zQxnHDVIrzXsZ5i/WLOAAgZyg2++tDTNOEC4qsiKWmzYXblehq7qPWI1q+6ece+TC3BTSbelGw3Rmfgcm6BJM1WU5WY64VGbaafm6w3UX39FyXUSEns9jaZo6sadbEYss0K48BcZBOKghMQrPdhHM3bCac+y4iz0ODhNLOdsU/gjmHQ7vLFW0W78pAB2Nb7ZD1djsl+geX2R52HDdcCwC2ow3OmNbmDB2In9eoLXSF3okXNWu3u0Kn4qNCf40XiPcfLbItW9zxdryIshSEoi5lVPI7Tps606uPTH7HRQ8+tc6/fKgTugojJoOSVctOeWfHpDe2crNb8IdKCT3G/PIcrrgxs1zSoMaN5dpM
*/