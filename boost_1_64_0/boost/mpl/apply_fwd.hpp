
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_APPLY_FWD_HPP_INCLUDED
#define BOOST_MPL_APPLY_FWD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/aux_/na.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER apply_fwd.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/default_params.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>

#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/cat.hpp>

// agurt, 15/jan/02: top-level 'apply' template gives an ICE on MSVC
// (for known reasons)
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
#   define BOOST_MPL_CFG_NO_APPLY_TEMPLATE
#endif

namespace boost { namespace mpl {

// local macro, #undef-ined at the end of the header
#   define AUX778076_APPLY_DEF_PARAMS(param, value) \
    BOOST_MPL_PP_DEFAULT_PARAMS( \
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        , value \
        ) \
    /**/

#   define AUX778076_APPLY_N_COMMA_PARAMS(n, param) \
    BOOST_PP_COMMA_IF(n) \
    BOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   if !defined(BOOST_MPL_CFG_NO_APPLY_TEMPLATE)

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
// forward declaration
template<
      typename F, AUX778076_APPLY_DEF_PARAMS(typename T, na)
    >
struct apply;
#else
namespace aux {
template< BOOST_AUX_NTTP_DECL(int, arity_) > struct apply_chooser;
}
#endif

#   endif // BOOST_MPL_CFG_NO_APPLY_TEMPLATE

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/apply_fwd.hpp>))
#include BOOST_PP_ITERATE()


#   undef AUX778076_APPLY_N_COMMA_PARAMS
#   undef AUX778076_APPLY_DEF_PARAMS

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_APPLY_FWD_HPP_INCLUDED

///// iteration

#else
#define i_ BOOST_PP_FRAME_ITERATION(1)

template<
      typename F AUX778076_APPLY_N_COMMA_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply,i_);

#undef i_
#endif // BOOST_PP_IS_ITERATING

/* apply_fwd.hpp
IWYXZ3bidRvT2fWD3aZI0HRJvvEkh0tyaJNit0WxizG7fmaHmgl06+x6wK42EjQ9kvNPcngkh2oVu42KXTez62F24lTerrPrBDvYzpRD8q9OdDgkh6oUuxrFrp3ZdTI71GUgwexoOZoEu7JI0PRHvuNEhz9yqGzqpBjYVUzN7Ae7BLNLMjvxINd0doPMTna60RTuyNNOdLgjYyso3GV7qARoLGCQBYhLea8uoA8C1kBACm/k7ZMc3sjYiSkBJRYBvSygjwWIj3mXLmAHBIhtJoUz8spJDmfkurBFwGqLgC4WsIMFiNN5qy6gDQJWQEAKX+SsSQ5fZKzplYAii4BWFtDGArjSzdEzIRsAc+gcMgMwbmrybA6aMdu2Jo20LQHmcNktGw1zrOwSHuZA2W7jQUxbJcAcIpuFx9F9ydvnZ77/dMKY7z+daLz/9M9e872jF1GNqfi1pPH7XyeM9l9EO1et0jrJO7wY2xyzOXrJIR0ZWw/pyFjmnMHXpZjBFxk9cmeMPbnhkrpzF15Xa9u5G1aDIonlXhKnKLi1kj2QYjErsWtfhti24NoHv8LWM8VKuIoGVlmzrAqWnSlvbqzC8JhDo8kqzOdnksMk8qDO0EDi5Oqgl0+ulBnQ6gG33MD8FpgdwHTbnP7aBPA4AA0ANFoBKJlg6oApAWatjUlcACUALAKg0AZoFcDHAMgFIM8GGBLAuwGI4zwwYXMtLNP9HwHoBKDLCsBMIZi/ZjNmCzD1NswiA/NzYFYDswaYxCil3Sd8DoKPeGnZlVYhTABYYwP06v4vACwAYKEA7BqbD4APAL8N0KKffwIwiHwOST7tGnMB0AZAu60ghab/43GM2QjMJoVxKK0VmCJgwoJx+D8CYFqBSQt2bdwEwBwA5gLQPqoJLQHGA4xXMHaFvAuAfmRDOwCAvQl5AWgBoFUAdoW8fCwDagCoFYC9CT0DwHIAVgjAflz8MADK6oySOvy/AOgEoAuA3lElDQPTBymxA8DYS3oJAE0ANAvAXvVnAlABQJUA7CXNBGApAMusACywBLPLwxhl2QbGXth2ANoAaBeAvbDfBGAjAJsAiNsL8kUA1iEbZQ7fEFVrVwCzCJjCA2M6s8wATFmpRZazRNnAtADT6vCLUYUaOAZtAJha4WMv1HYAigAIA9CqC8oyBN0PTA8wvcC0jMrw7cA0AdOsMI4MfxKYCmCqBGPP7fsBWA7ACgHYc5sLwEwAZo3hY5WYiFoApkxhHDnpAWYpMMuguoxRqmsGZjow5wsfe2buAiADgCwAykYJWgVMPjAFypHEIegSYJJoEi4HRsmaCkwPMOIOsG4Un5EJmNqA6VYYB58XgWkApvFAav/uHwFTAsxaHP4n4ZoRR95cPBtXJhAyCGeNIdD9oDXQfaBjoMVhhJtNhDeIseoonEei8PbFFJxT14WQNtDtoFtAt4JuYhqNSt/uiQsJ5qPqKBxMovUI2Qh6E+ga0LWgK0BXgV4HmhsGvaAQoXW3uJDoTrJrkds1CCkCHQa9HPQK0EtBL0OJGiK0XY+KI8kClEjcTBYiZA7ouaBngp4Fejro80Hngy5A6fojtP2oFEcSH0onbiZ+hHhAe0FngM4CnYQjgwsl6iLvCfkQXLp4JJGzCeoIIf2gNdB9oGOge0D3gt4BGu7noS0RMhlE4U4ShXumOJvQ9Io6At0Kugl0M+gGptG6aFsfCW2qphUIageuHPXI7SaE1ICuBV0Bugr0OtBloEtAczukE1l6eblanErEt5F8k1FHCFkOegXopaCXgV4EGr5pfAJcRftkdSYWe+2XazePs2+Yx365to/PxGJ8JoY2HuxXErTXfkH4wnF2Y8fYLwj3swQ=
*/