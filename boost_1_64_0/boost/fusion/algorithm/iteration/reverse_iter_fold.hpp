/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_ITER_FOLD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_ITER_FOLD_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/reverse_iter_fold_fwd.hpp>
#include <boost/config.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/add_reference.hpp>

#define BOOST_FUSION_REVERSE_FOLD
#define BOOST_FUSION_ITER_FOLD

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/algorithm/iteration/detail/preprocessed/reverse_iter_fold.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/preprocessed/reverse_iter_fold.hpp")
#endif

/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#include <boost/fusion/algorithm/iteration/detail/fold.hpp>

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#undef BOOST_FUSION_REVERSE_FOLD
#undef BOOST_FUSION_ITER_FOLD

#endif

/* reverse_iter_fold.hpp
AR/GRMzHifgCTsKPMRmPYgp+j6l4EdNQ6UNhxo7S5jkc03EUZuC9OA0fwOm4Eu/FzTgD38ZsPIL34RW8H7057/6OdXEW3iBtmJtLG+Yx0ob5PpwvbZ8X4jxchCtwMT6LS3AjLsXtuAz34iP4ET6KR/BxPIFP4A+4Ei/gKlTmhnkSq+NTeD3m4WEP32kWnyx/n/lXvs/8d7cXLH+neW3faZa3Ifxz3mvWYVDvUEI0IZuQR9hHOD24/P1m+af8U/4p/5R/yj/ln/JP+af8U/4p/5R/yj9l/fxVv/8nJKRf9e//zWn/nsgL86AqSvv3AVG92WhiRkbfpLTkCYkxE5KUpv83yzp56nVui5uanDLd0T/Asq1QXqT7VXWs14cm9VMyaFKfONWyluyPwVpU2xoWlzopUTZl359Zvc7QdMtaEinpj3Cgrck+Hl6xQf+As5ea8R7fNUKe9w0IqmrcNyCqgrYPxDx+F/av0Zx9ajK0VH0gdtfV9oHYV0E/jTleevsrXR8IcxXjdAZ6a/tAzCedsbrpLE0fCOuxuyDb3y6/32wmhNB+IVe271LoJkw1u593wjamaDDbIR9jTLIs2r4s3rJM5mtgtG3LMss6Afbfr9mV/ZjIOtJvoY2so9d3IslHWy5eUo6Tn156SlcuttXRlotiH/1ykeult7/SlYviEspFWEVtuVig9I3RTWfpy8VYGfP/MzbWGvfjIrZ/VravqRw4Wpo5ELTjqlMGZFx1aW/wgJxryt9Z9r/jZd4D0uYnx3lSJpt2Hdsy3d6WqcCyHlUzA5E6xiJWLecnOfJJNa63OT1xYnIWW4+Jl38L0P4bG5T2N5L3RZW0ZSyQch1VWy9vpPIxuc9/W9pydOqfiMr65czspbvPUtWzphLKWUFlbTl7mHKQa5BWCprbdCrb72Mbh1nG7ld+qwzETbhYKcf628+ImRCXmpaafG+i5Oc+N+WtUMqbUm8UKW27rHmbli5joB42obWMTEyWYxDgMqcM8ZK/J6vmLXCUS+vYqevJq1DSs5GIB9dxjJ1qlnKo1HtT47JkDGB72bQvi3JeLzlVxvV1Wo9lMia/lJF4qUMdZUaJRzaFJKSKdS6alLrEw6nNX46MMZw+KTHBJMeCIPFnX1WsaftNvidlUrX97qyzmhCptA2o50hnrk6a8lziL/tTlbHGVbXn01Klv1t9dRlwnE2en0tHdM6lZVX1z6VYl3PJfiaVos4Oq2Z8Lp2rqj2XlpHOHE065UzyoM5wrpdWV5P5gQmNCEcIy9l+oXX70dzByu2r8p+Y5NQkmnllum9Hau+v2MBWl0obMvW5Yy/Dfa3zIrFQ5lGwXzsnOuLrNOb+HIK/zAWxgvgWNdCNr7VCNl37+HKNkvks4qQNnVyHHNcEaROrrU8C7ecKy1yOz0oZi3+VpHcF4XHl+DfUTW86xYCS7vn9lmt6o3XSG+uSXmlbKOnlDHWqs2QZZ7KkTSe9Qer0GtSP6vMgUsbePybn+2HCSvIh6gZNPthq+zIdc9c5PJS6K49jEMH++yvjtFn3J3W8qoyq+wlLfO+X+N5LWEV8zY008Z2UmBlDvsocYobxdcStdz3tebFa5gNYJuXkYcJT7M+vsd7+rOXEk3lSJI9Ux8v4vNCWiWh1mVCfG3KstfdYbDNGvxyMkBo1Q/I1VcpBkTadUldleJxGd+WggDyOYv+Byro3GpYDOS4S31oyfrG39Rq1G5X4xt6oja/tRoXrgEf3KdtV9ynac7lA5x4iSOd8nKtzDc5S31e4vceRds+a+w7Hc9cUSx5G+1FWScBAlr3ulIexUq5t9ydJ8rdch+3fjSI/j3G/16UJ3zWuO+Sex3FcLMeP/fo=
*/