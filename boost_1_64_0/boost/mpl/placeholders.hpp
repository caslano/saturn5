
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_PLACEHOLDERS_HPP_INCLUDED
#define BOOST_MPL_PLACEHOLDERS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright Peter Dimov 2001-2003
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
#   include <boost/mpl/arg.hpp>
#   include <boost/mpl/aux_/adl_barrier.hpp>

#   if !defined(BOOST_MPL_CFG_NO_ADL_BARRIER_NAMESPACE)
#       define BOOST_MPL_AUX_ARG_ADL_BARRIER_DECL(type) \
        using ::BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::type; \
        /**/
#   else
#       define BOOST_MPL_AUX_ARG_ADL_BARRIER_DECL(type) /**/
#   endif

#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
 && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER placeholders.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/limits/arity.hpp>
#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/cat.hpp>

// watch out for GNU gettext users, who #define _(x)
#if !defined(_) || defined(BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT)
BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
typedef arg<-1> _;
BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

namespace boost { namespace mpl { 

BOOST_MPL_AUX_ARG_ADL_BARRIER_DECL(_)

namespace placeholders {
using BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::_;
}

}}
#endif

/// agurt, 17/mar/02: one more placeholder for the last 'apply#' 
/// specialization
#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(1, BOOST_MPL_LIMIT_METAFUNCTION_ARITY + 1, <boost/mpl/placeholders.hpp>))
#include BOOST_PP_ITERATE()

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_PLACEHOLDERS_HPP_INCLUDED

///// iteration

#else
#define i_ BOOST_PP_FRAME_ITERATION(1)

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

typedef arg<i_> BOOST_PP_CAT(_,i_);

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

namespace boost { namespace mpl { 

BOOST_MPL_AUX_ARG_ADL_BARRIER_DECL(BOOST_PP_CAT(_,i_))

namespace placeholders {
using BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::BOOST_PP_CAT(_,i_);
}

}}

#undef i_
#endif // BOOST_PP_IS_ITERATING

/* placeholders.hpp
tOd/G2+MJrrL1eBpp0668W18SaOn2vn112JWe5W2qafGAJUPUW0H48TvzOza8q62A9EkgKPZkbh0/vcn2F+WPFhVhsVUESU3G1QNYWmMUB0FT3Ngpo3PkrokzLI86JYeAvKJopC1CApIDYd08c/Ti629uP7dfUmGBbRLXWFC8zF1qU7+NKwH4GUSrEKqn0J2mnLqKtzJbzs7CR6V6AIv8Q2r0EtEhZErl/Rm/1PhomTS8oMyuxCFUyjFA6OzhO2Ef3Xv6M/QSTnKwfcsh11ZSLdOcaAeh59bBxF1Nn8bxWP7geuV3skCuW+ALVIHMn9H0tbGNL4sM9SbErJW9A1RhY6Yjm0QSE9p2LnIzl5e3OZzY9Ur8rZf+gn19GcGNNJ+2iNzGz4pPF8S8ySW/wZXqqHJTHnFhbdwS/vgfE6s0090axuY+80tGAkbmWfKiLj7kuM1njmbQlaQmBvGg1+jbWXhSCrp0TGleI1olEfVNrOHjVebGHR8qqA8yD32Ex0Ud493u9yUlhXg66QgpiQp5WrCNaIrkxs2Oy0bTLyBguWs0CPHLuyGw7Co4g==
*/