
#ifndef BOOST_MPL_AUX_FOLD_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_FOLD_IMPL_HPP_INCLUDED

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
#   include <boost/mpl/next_prior.hpp>
#   include <boost/mpl/apply.hpp>
#   include <boost/mpl/deref.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#       include <boost/mpl/if.hpp>
#       include <boost/type_traits/is_same.hpp>
#   endif
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER fold_impl.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   define AUX778076_FOLD_IMPL_OP(iter) typename deref<iter>::type
#   define AUX778076_FOLD_IMPL_NAME_PREFIX fold
#   include <boost/mpl/aux_/fold_impl_body.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_FOLD_IMPL_HPP_INCLUDED

/* fold_impl.hpp
rWI7ukHavyYQsTY2AFK+gWUyOVLEMS7boJXGTntbsExSjztHoPtX3DRw5k8CtWcRT/13pw/qI/qHyvrTab899CVQLK3BiQQdfGvy9DENKK/MXtOWfXOy1F58fqEiM3IKE8xW/oMTeltssR593QNftwgaaP0HTSDkBjvor+28j2XkwVw+PsSZEOlAYlPkjx70OVNPe+TCTeaur+lOXQbfDFZlyBUWXMT9qiicUJqqRYspvBR55kY2WwTRATmlDySUPHRNlR2LnyRO+KoYiV7yFj2rRPdC8ch4uUM98EQTbMyg38EdTmM0QM47T3S300t8cktSnH2ait0gWVkgQJJbNKLpFsvrfs/i0QcNTwRUQnBQHEWD21N+BEDR+huw0102G5IGSgu+iPXCXPNi2iiI2A4XH6xYS6vkndNBfkyLK4VGfnR1SlINsEJGXrClDXaV+z0pTz44r+JxhGbFJj39AvezWIbzQ94SNIHRqN6xCpZbnQilp1HR1k1Hln2eEYsQV3LySddx74UsOSzY60Aoq3GlzqylS4rFJiZNEMUCBbdwztO547L9x3cQTCI6L3JNM5RE9x0NflxEcK2QWvbXLn/SOR3nCaDhFLPWxDfs9QCnf7qdI57jAnn6e3OlqwccJ8Xx5iMQJWRQmgD7CB/HSpbJNhHcMCjXp0kD1JX3jiFuVPgBOXTEBB89/4E0ZorPShOXw+UjEKLqmStD
*/