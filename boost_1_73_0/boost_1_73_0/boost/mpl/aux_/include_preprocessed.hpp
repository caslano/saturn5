
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2000-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/compiler.hpp>
#include <boost/mpl/aux_/config/preprocessor.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_PREPROCESSED_HEADER \
    BOOST_MPL_CFG_COMPILER_DIR/BOOST_MPL_PREPROCESSED_HEADER \
/**/
#else
#   define AUX778076_PREPROCESSED_HEADER \
    BOOST_PP_CAT(BOOST_MPL_CFG_COMPILER_DIR,/)##BOOST_MPL_PREPROCESSED_HEADER \
/**/
#endif

#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING BOOST_PP_STRINGIZE(boost/mpl/aux_/preprocessed/AUX778076_PREPROCESSED_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include BOOST_PP_STRINGIZE(boost/mpl/aux_/preprocessed/AUX778076_PREPROCESSED_HEADER)
#endif

#   undef AUX778076_PREPROCESSED_HEADER

#undef BOOST_MPL_PREPROCESSED_HEADER

/* include_preprocessed.hpp
rbTN2yNpXqCSJU75QUzO3kOcSWPRTdNaqc170BV7Tq0zUq3Q+8zWXoYymQBlSD+Pc5LgMunAZrouEtLAwRIhwSIn7phAanQJUkEjrEGraxOTcIIVY2U7BRtpL4qcabbSxs2CXFoZZl7mXEUHtssoRelqQpx5nMq+jpHY70DE2e2LDIWOZQF/3Vw3+R+DdA7LysEfKn+GTJcIlXQZUMoUxMqCEEQLEcW6LKVKtrL4Svd07araHdNXruKiTpDK3uuV22AcYiLEwd3jXBR6JbiqrHS/3HPtUGeUfsvt1WlYm5wYKtI01QabvoAtEVMrSzKwW1NI/z9jEKXow3NZACfUEA/6Ax9QxTrJ1Wrq1y7tnfsfyG0Xeud6wq50WNmpz/pTNuv1eoeNpq/NSvgsNPNgxeElo+8i0WtVaJkwJ/ajfULP0zyWLGNjgSiTlkSntp36NpPh6cifxWfJ4CTBJY4HsQzHw3EYDk5QjsMgORuNh0Eqx+ej4SBOT5Znw2EaymAUj5en58PRKcrleRgJBm0jin+FjLataKGUz/FulCjPwO9I1aboOHHqPlQGU+ppFZNlPPBnnSAHX24fFld3kwNu8bvb+4XgXCNBx7vou1iNPIL1YcVEJ1kktnryd7sb0aC65jqZeRUSkYOH+4v5
*/