// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PP_IMPL_ARGUMENT_PACK_HPP
#define BOOST_PARAMETER_AUX_PP_IMPL_ARGUMENT_PACK_HPP

#include <boost/parameter/aux_/pack/tag_keyword_arg.hpp>
#include <boost/parameter/aux_/pack/make_arg_list.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <boost/parameter/aux_/pack/make_parameter_spec_items.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/list.hpp>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/pair.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename Parameters, typename ...Args>
    struct argument_pack
    {
        typedef typename ::boost::parameter::aux::make_arg_list<
            typename ::boost::parameter::aux::make_parameter_spec_items<
                typename Parameters::parameter_spec
              , Args...
            >::type
          , typename Parameters::deduced_list
          , ::boost::parameter::aux::tag_keyword_arg
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
          , ::boost::mp11::mp_false
#else
          , ::boost::mpl::false_
#endif
        >::type result;
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_at_c<result,0>;
#else
        typedef typename ::boost::mpl::first<result>::type type;
#endif
    };
}}} // namespace boost::parameter::aux

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/pack/make_items.hpp>
#include <boost/parameter/aux_/preprocessor/no_perfect_forwarding_begin.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/pair.hpp>

namespace boost { namespace parameter { namespace aux {

    template <
        typename Parameters
        BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(
            BOOST_PARAMETER_MAX_ARITY
          , typename A
          , = ::boost::parameter::void_ BOOST_PP_INTERCEPT
        )
    >
    struct argument_pack
    {
        typedef typename ::boost::parameter::aux::make_arg_list<
            typename BOOST_PARAMETER_build_arg_list(
                BOOST_PARAMETER_MAX_ARITY
              , ::boost::parameter::aux::make_items
              , typename Parameters::parameter_spec
              , A
            )::type
          , typename Parameters::deduced_list
          , ::boost::parameter::aux::tag_keyword_arg
          , ::boost::mpl::false_
        >::type result;
        typedef typename ::boost::mpl::first<result>::type type;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/preprocessor/no_perfect_forwarding_end.hpp>

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // include guard


/* argument_pack.hpp
cxp3O6fxvq3jknuPA24dpzvn8b5zGs/9nx3v3jrO/n9eHHzPeOgxpnjoMaZ46DGmeOgxpnjoMRIP/SWZZrXEQ4+ReOjbZfhOiY0eI7HRJc4sMSbc8Ry2aFnjzJZjcTpWwhCsjKFYFctgNayBUXgTm7o6Sa+WpOegqy3p1ZL06mIw1sNSWB9rYgNTfNg0SSdU0jHiw0r8WZeNsQA2MccVl/kK08XkJL77feZbJfOtlvmeNsd3l/mKu+bLSXz3Z03z5SS++7PuconJSXx3mS/CNV9O4rvLfHlc8+UkvrvMV8A1X07iu99nvj/KfDtlvpdkvgG6fK8o30duwYp03aSOzn6HlmbDd9AX38NIPI0N8Sx2w/M4HD/F0XgJp+LXuByv4+8xHXfgDdyFN3EPfo+v4y08iXfwMv6EP+Av+DP+ig6da4eT7YT5sQSGY3WMwMYYiS2xOg7EKIzHxpiCrXECxmAadsansRvuxvdZzl6Mo38f9sVj2A9PYX/8BF3lcV2mvynT/4gf0P+T9LvKeZie+Z2b+jZPlXMlur5Szg6md/WXlvIsi4OxHA7DSjgCK2MiVsU5WBvnY118CrfiJmyJ72FbKcd26Fp4V6yFfbEzxuEgjMd4HIJDcSQmYRLOwWTciCn4Aqbiazge38Q0fBen4RmcgZ/jLPwCe+FfsLeUyxz0pxzmYWF8AsNxEZbGxVgTn8R60t8Sf4ddcCv2wI2Yis/hBPw9usr7Tub3Q3hZyrsY3XVN6uzZtbSC+BjWwBFYF0diNCZiSxyNfTAVR+EYHIfjcQ5OwvdxIX6GT+ItXIx/xSX4Cy5FG5lZi91xHfbBDTgQN+FwfB4TcDcuId+v4nLcixtxP76AB/BlPIiH8WV8T/pZf1ZcvmeQbz62yPnyB02Oa5+M4/gYRuFJjMYzOAA/xMl4Adfjp/h7vIQH8M94Ar/AL/Bz/Aov41Xp/0b6b0j/L9Lvp2fMlx9d/QWkPwy/wuJ4BUvgVayI17AOfo398AYOxe9xFP6A4/BHXII22Q/2GHWe2cflehhKt03KoTXTu2yLTuyEIRiDYdgLC2EXLIZdMUL6S0t/eeyO0dLfSvrbSH9b6Y/BHtgFe2Jv6X9U+mOlP04tV87PRn1Xrt2Sf3Pcdh7YqPxXwrJYFStiNayCdbAqRmEU1sS6WBsbyfibON6oN8qxIcsJoFOVRSTOu7q2YF4MleUVkuUUxupYWpYTjh2xGHbBEtgdI/FRLIUDsbQsv74udR2lfugWuXZV0eUFkKxnB/TFjuiPMzAPdsJgjMHi2B1LYA/JZ08pl15SHn2kHPpJvgZibxyEQ3Aojsch+Lj0z8RRuAaTcAOOxp2Yiq/iGDyGY/GE5O89nIif4yS8JsO/xin4M07Fgjr3K1gS0zAKXdPVwP4YjbHYAadjD9d4Kb8rdqm3J3UDt+BEugsM1+Q+qBQ+gWVwCTbCpdgVV2KC3J/NwXX4JP4OX5X7h4Ny//AO7sKz+DJexdflfmI/3sYDGKJzPsJCeAgj8DDWwqP4EB7Dh/FdbIbHsQ2ewE74Hg7BUzgJr+KT6OTB13MYhluwEP4Bi+FLWALfxEg8hlXxc6yOX2AUXkGWqa5LrfEudsT8Nu4HsDB2wVLYG0dgLM7FQbgO4/B5HIE7MAFfw2R8C1PwU0zFX2W6YDvbHavjTKyHs7EPUtZpE/E1fBxP49N4Bt/AD/E9/BxP4hf4IX6J53Gsa31wPP6CI9Huw/UM/XAU5sMhWB2XYwKuwemo2jfBZ3A3bsYr+CI6HWxvDMdXsBjuwQg8gGXxTWyCh7APHsbB+DYuwZ9wKW7FVfh7XIcv4A58F3fhGTyL5/DP+Al+jRfwNl7CACc=
*/