
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
a2yJXP9flefXhdYlvkMAlpa7NlFjel7dUdU9AfpKTOuEjAs+Ssr2Je610dz3F6aPaBVOd1jRxsw74gcEsMJV9/1XOpfCVOO6lXkd8wWu4S4tMUeshDF4WSnHJsv4hFaR2ojCrm13KKRv7J9brPr486/htrq2PIF+KtW9Bdj+kWGGMI2Laoy6vBZCXvWzACz3MbC+n54sK0ZX8PruuImWbaBT3W8uR+bp6yqwTfykb72b9It2RmWbZL+s2ibjld1alPsWlH3Mbdvvb5O8B4yxty73bVW51WP0p1ht42lW+7ql7LCbUq9ryDHHAE1zvdjRHHNFrdeAHeZ6Fe0YzFM9W8L6WJB6y30KCr9eP8fG/RJjteOMfYE/KvVg/lGXgvUeL/3sZaXvtxQq9c7ZYa43O1NVb68H1PvCK8Wrt/UzNc5b1Vu2A/0YVvdJLOLxcU7mI2Q+W7Vd1J+TiVbbcZL0oUbvLHy73ZDt5if9tm1IzVooQWfzdovj2y8uVl+EsQnKd+IVtnnuaGVZysfa9JpSjhzja8rlSAXHbhyS8Qn35Tsyj3SNZZw1r9/0lV2Ee3uWfeytXdbPSaH+lDhcZ+NeItbXRDzg3p25Vp/BHBufwWAZhxAudRpL+pI6VckoUKeQKF1RrgUx1WMzlY8qpB62ru0w1ttcLumjPyvl6i37OpB0k3KlZJjHgmgTdaYhEg/sq1ePQ6EchY6VsfTV2+qTt9VXbKtv31Yfsq0+fFt9wrb65Ivfx17cPvzi9rEX3odf/LEJNvrqbYxZsN0nn2jsk3/7p+j0+Smdk4duiR67oPWGvbbGVpTc9SZ3jX2ccu6EJ2RceSWcQVKmiqVMfYdOWA0rY12sgk2wKkZgNZyGzjgTq+NsdMFUrIFpWAtfxdr4GrrhUawjfdjppeQcSs6tlPJ483cqKlMbuf+HL7qhHzbEdtgM26M3BmA37I7h2AP12BOTMRA3Yy/cjb3xbeyD72I/zMb+eA0H4lc4CL/FwViKMgVjFRyC9XAoeuAw9MHh2A1H4mAchWE4GqNwDM7AsdKHGYKLMBRXYBimYjiuw/F4AqPxbzgBz+NEzMYYvImTpO8yFmtiHHqgDhtjPLZAA/pjAvbFKTgIp+IwTMQJmIQxOE36LM9q5LwOqR/7ydSX/6bVdT4u6Cx9yh7Sp9wR3XAM1sEIrIuJWA+fwvo4FxvI/mqIa9ADs7ARnpW+5RvoibnYVK57aYae2ByfwBbojY9jG+lz7oDe2BlbSb1SSvGHnA/dlHo9wd/zVGNQnPCk1OuU9KWfxgZ4Blvh37AtvocB+D72wbMYjB/ifDyHi/Ej6UP/GNfjJzJG5VN8BS9In/olPIyX5Ti9gh/gVTyH1/AiXsdbeEuO06/wEfwaa+M3WB/vyHbKke30LbbDu9gFv8OBmIsj8R5G4w9yfObJ8fkjrsGfpK/9Pm7CXzADf8UsVMaqvIFl8B10wPfxEfwYy+EVdMRrWF6+F1iGnHdyPirfC635m3UYp6dkv8yU/TJL9sts2S9zZb/Mk/0yX/bLAtkvC2W/LJH9kiz7Zansl2WyX5bLflkh++U52S/Py355QfZLmuyXVbJfVst+WSP75UXZL+myX17CirgRq+EmrCVjQTxwixynL2MP3IZDcTtG4Q6MwZ2ox1dwFu7CpZiBm3E3vox7cRtm4h7chwdwPx7DA3gGD+I5PISf4WG8jkfwKzyG3+Eb+CseR6WdcCL/vjBy3ot+8vvyCHYgMRmffVMG+2JF7Ic1cQB641Bsg8PMxwHprCzvfiHXbz0hv1ct0Rm9sTa2xg7og13wSYzGNhiLvrgE/XAjtsOD2B7fwg54CTviFeyEt9Afb2MX/AY=
*/