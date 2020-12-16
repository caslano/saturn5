
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

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/preprocessor.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
#   define AUX778076_INCLUDE_DIR typeof_based
#elif defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#   define AUX778076_INCLUDE_DIR no_ctps
#else
#   define AUX778076_INCLUDE_DIR plain
#endif

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_HEADER \
    AUX778076_INCLUDE_DIR/BOOST_MPL_PREPROCESSED_HEADER \
/**/
#else
#   define AUX778076_HEADER \
    BOOST_PP_CAT(AUX778076_INCLUDE_DIR,/)##BOOST_MPL_PREPROCESSED_HEADER \
/**/
#endif

#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING BOOST_PP_STRINGIZE(boost/mpl/map/aux_/preprocessed/AUX778076_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include BOOST_PP_STRINGIZE(boost/mpl/map/aux_/preprocessed/AUX778076_HEADER)
#endif

#   undef AUX778076_HEADER
#   undef AUX778076_INCLUDE_DIR

#undef BOOST_MPL_PREPROCESSED_HEADER

/* include_preprocessed.hpp
PMHzIXeXAEIfQjIhh7CHcJxQQvCaWt7Wu/xT/rnZn7+g/X90umFCkqn1/59r/6+081+j6v8/V+47z2I1PINVQ1y47hnrGAf2jBjSo1t4z+gh4ff1peWp0nrOif7vTXWMEz2N/dNY2gQOpQGAsh8uqjZ0ATVM01KT4m3aMKU4ap8sdegGElzdF839rMMwIeEhS3tkaf8Xl2hsM6DqA0OvzlGvrk2/b4ZeHsr0kF/8m0Vcmvbott4jvc/fvnCGft8MXxjrKDPqzb848/4nRs5pPnyDZ3CVc3p1l3p9KujVsZa9b4/njPFmP7v246/fCQyc+c6QzKTFz5wve51vWetqHfelUfY+PxzXKZe9TvZRY93r3ArJv3s+0LPJ9KA7ds0cNfaCXl8gN6/PDHkXXc4z4/nHM4Ptu+i1pAytvtTh+kgZWQMpI2uIU9FXysIa42PYBJ9BP9yLTfFtbIYfoj+exLvxn9hc+hFugW3xXuyGLXEABuI4bIVTMAjnY2t8C9vg37EtnsB2eAbZVuoOnHuHMpl7ykWEQ4RCgvke028g95kE7jE195fMf533JwMwlFDC3zGDnHuH8jx/e4WzvYRMQi7T1mEebkPV+5Tcl7IvhGD+duN+NAL90PxOZf/79d+r3KZ6t9ITC/EywdH7lSHyjmUUZhDkPUu7dyy3Ma2AEMXfJah919J/m6vlPctNcg9cRPCIML1zeZAQwN+lvWvZP4L1YQxmE7hf5p1LjDDfM7OuCLaRYH7/sijCeg/tw/cILO3dS69h5vcvmYbmdzBzcAfhOEH9DqbH8LK9h7mIadsIBYTzBEfvZRYSfJlWgiEYSchS5iHkE7wpOFffox+PtL6feU35/xH272kGM+0ERuE0wgp5Z3MHFhAu98CHy+/Ryz/ln/JP+af8U/75b/j8Fc//yvPtzXr+f0L1nv8Jef7n1tn4/N8PPZT23SHWd8THpJif/J15L7FSDc+umvcIpCxgjMH6fqDS0Jsm2WPYJMu7BOubGKdZ3yUgYZPGpdj2X0uns2yJzXsa6neYjOtNGCf9dZvfi5eyBE3fyJetffva9IfL/9PU3HH/AV9LO/izSpxKW+yu1nRiOVNCSTqx306VkSjpUl313iTrsbSFn2zZHuknWZsOqnf4klRlHaE3sazDcZnGv6/s4v+tjOJVYxlFXsKY2ytEvt/prbO7g73PXmnx15RR+FaQa4FcIw5p2tW2lDKKQPTCIGyCbdAf22IQtsNIbI+TsANmYkech53wSQyR9jyd8WUMxQ+wByrbEobNsCe2wj44CPviBOyHk/A+Kavoj3NwIL6Ng/AQhuPnOBhLcIi01xkq7XWGK/FgJN6NIzAQR2FvjMJ+SFt56W9PrgVyjSAOm/72aks61cUWWA87YX0chj44Wsp2pqjKdpriHvwb7pMynAPojyekDOe0lOGcRdZNf2HOlbloylqkjMX5/qnK0i9VLuYRbMtPyt4PlX4fVPrlIlEEbVmItr8pyj6c6mPKvn8pddlG2fqUupn9SFFeIWUVN95v1LVp9BE1vbz84V/s3QlcFFUcwPE16MQKAoUEAxEBDQWVjBQLFRCNCAWLylxuRRE22MzKCo3SEsvUysqKysrKysoKy8rSysrKbrup7LaistuO3yz/3Z09Zg8Eu2Y+vb672zDvzczuNO//3rynL/qiL/qiL/riy7In6v+M0VZvVgIAnVD/X8HN6Gip1zbKffytUq+9iaRMSBMzwl6vHT2u0FhQOHFc3lhjTcnMig7VcekHYKvjJpNzab293r8jXBlHp9pN/dbexq+sU0ruBqdn9Cur6hglQcbSkn2Kkbp6hexTifI37FObxj6dPtNYUl/mfVw=
*/