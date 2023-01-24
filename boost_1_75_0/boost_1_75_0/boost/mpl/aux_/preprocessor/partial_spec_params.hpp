
#ifndef BOOST_MPL_AUX_PREPROCESSOR_PARTIAL_SPEC_PARAMS_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_PARTIAL_SPEC_PARAMS_HPP_INCLUDED

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

#include <boost/mpl/limits/arity.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/preprocessor/enum.hpp>
#include <boost/mpl/aux_/preprocessor/sub.hpp>
#include <boost/preprocessor/comma_if.hpp>

#define BOOST_MPL_PP_PARTIAL_SPEC_PARAMS(n, param, def) \
BOOST_MPL_PP_PARAMS(n, param) \
BOOST_PP_COMMA_IF(BOOST_MPL_PP_SUB(BOOST_MPL_LIMIT_METAFUNCTION_ARITY,n)) \
BOOST_MPL_PP_ENUM( \
      BOOST_MPL_PP_SUB(BOOST_MPL_LIMIT_METAFUNCTION_ARITY,n) \
    , def \
    ) \
/**/

#endif // BOOST_MPL_AUX_PREPROCESSOR_PARTIAL_SPEC_PARAMS_HPP_INCLUDED

/* partial_spec_params.hpp
3x8DPqaP+Uy0gdJAZZcBecE+lfNXh0NZ0I53+qjsGJzoaSjkKOT24HKlBTxIoGGg+NjXaDRiSy2mgXNPW8tLXW4Lgz8jnjNt6HzqzJMcgKYBZ6xF1cLPBxsQV7O3kvNraeWCAA/t5PBXRCN+dEXC2FHUK8l/orpZxnsWSnFZyOWjyjAK5givaP0OaWntDlCoYxH3y8Edo+dFtx8/sWx5dsaq+ZiA3FzUEzWUVveYzEJm30Ckvz/CN/wq+CjBTy2lMmIHX0NxDqf8Bo3vubBMb1V3IL5tV4MPF6BGRHItZBc5OV1SQ9OrEKr+3RNjqRlYbXGVXaSP8uIDZC9dmQLyaSKMb+5rYb/E3Nuu3KHrv0g+T8ggS1AR/oGNbOcGk9q8WS8gDxNpXvS8YinT0R9aZM3I2h6/j99Ivwl8wz/H1JLsJvhF+wvFFlUItTJY4O8WWPvgrMilFkq4dUcraivKSdBasNjftu9USWbhGd+EbG/fDAnK+gU79nh+ebOc/3TFe5rJv4iEunLzWt7IqslWo10gLOdxVpJs/fNsLJePIxVSZOoT929Fbr/9jh9afbpfIUq4WTMW2euP4GDicV2igjc9kYR+HaN9p9LERBwfQJ9Rt0574l4wFv0hOX7BL2LOWcTT4U+2Q/STw0mf+KNmIsJ3edjSDh29MJNlyj4V+F91IfwFLMV0zejPYq+7JilF3iriSYeFkSSwavrd
*/