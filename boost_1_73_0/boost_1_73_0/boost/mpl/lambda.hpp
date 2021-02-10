
#ifndef BOOST_MPL_LAMBDA_HPP_INCLUDED
#define BOOST_MPL_LAMBDA_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/lambda_fwd.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
#   include <boost/mpl/aux_/full_lambda.hpp>
#else
#   include <boost/mpl/aux_/lambda_no_ctps.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>
#   define BOOST_MPL_CFG_NO_IMPLICIT_METAFUNCTIONS
#endif

#endif // BOOST_MPL_LAMBDA_HPP_INCLUDED

/* lambda.hpp
q+VcXC2X80WvMvquEXF0b4uj1l08pgWbHZueLVIWseGqbMLxMi8s4eNyphCFQhQybCutLHwTrRQnbhKSRMP+kEaDAd287oiX0vGYljV3afCc3uodLMMBDZ+Nnz0fw+e775cd0eYdk4fQs+EmyuSGO2KqlWPlesumYm+/c1HutmVHvKqVano5y3RMDVt87p3fsFq7fEyDjugA3qm4T6CAFGqTnZD04cD0psiYpErpMt0hXg0r6Yxu9apQViuamtpqoE6lkxNxTXtpaaWNokKFwA1LQ8Ovn466x5OkcI0P8VGbTddfSFprnVImt0XZdOGj63VOSjsBo8ulo0TXyhnYtk0mEcPQigu1xpOZNlysFU7g+63hLasu7XMNMM6VjKiFsY6kE1d1WfaJrhjZ3DEnOEZPaNXQlk2SA2dhuevhlix3PoXOMvI8OSNT9K0sdpwKmTk2ewnJIPIBSGb0FplZJUxAmcuUttKYAjVsEV77skNpoJlL6QpwTHtcCyW3cDoy2kVtaEPzkJSWuodE+BIPGfEVaBeJLIH41JnXhmv3q5JsXtCqdl2P0vNf21qWiGRMXfkqPHNB/j7LTK1LxO6KPbpuGF3YUxv3j99+V7JBxf6WdG0slzuIwVeyNwVYxBl5LPBsVfEiGK0GASLR
*/