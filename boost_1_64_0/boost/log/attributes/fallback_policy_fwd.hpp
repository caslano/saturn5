/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   fallback_policy_fwd.hpp
 * \author Andrey Semashev
 * \date   18.08.2012
 *
 * The header contains forward declaration of fallback policies when attribute value visitation or extraction fails.
 */

#ifndef BOOST_LOG_ATTRIBUTES_FALLBACK_POLICY_FWD_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_FALLBACK_POLICY_FWD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * The \c fallback_to_none policy results in returning an empty value reference if the attribute value cannot be extracted.
 */
struct fallback_to_none;

/*!
 * The \c fallback_to_throw policy results in throwing an exception if the attribute value cannot be extracted.
 */
struct fallback_to_throw;

/*!
 * The \c fallback_to_default policy results in a default value if the attribute value cannot be extracted.
 */
template< typename DefaultT >
struct fallback_to_default;

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_ATTRIBUTES_FALLBACK_POLICY_FWD_HPP_INCLUDED_

/* fallback_policy_fwd.hpp
Cy/BA+LuBRWeexz7Gp6G38Av4N/hV6L3d3jVcPcD38G68BpMguq8UGjq9YQGnAoD4AIYCBeL/XJYBq6Wa095ZhdTnnukPPdKef5Kz8/l/SnMQOzz853SznbBSnA3rAWfgk3h07Ad3AN7mP7DPvBXcDA8IOX/LBwt17fDZ2C6XF+C6/U7RMpA4hEOV0o8lkk53if16n7xd43UqwelXq2Dv4APwUVwO1wGH4aPwU3wMNwKfwu3wddE7024BX4CfwnPi7mcpy3vryhjiZ/1PO2OEr8kGA47wWjYRfKrO2wDe8ABsKfEfxQcDnvD22AfOBH2k/6oP5wHB8LVcJDUx2T4HBwKXxZ/fgOHwVfhcKmHt8KzcAS8AEfCL0XfU2+Si6k3T0q92SX1ZjeU/lme8VPWDv0zaVHuUmBFOA5GwAzYEo6HcXACjIeZsD3Mht3hNHgTnA4HwlyYCmfADDgLToF58E44R8p7vpT3YngPnCv99kLpXxbBvWKv243c/4Y5pL+PpL8vrAj76fYmz69huIO7EHFXAVaCoZb77dWS34MdxoMD4u45GQ+el/7/BblfeQm2h4dhP/giHCTmEi8C8z0eHBX/j8l4cBzuCzbUeZNbOpc3YvaXU+dY+jq3ci1yBL0CxOjCGX7zA9QZhYkDIeLrrMqLcDLXq5GDSPgg77Mrz5gPoX7BGYiI5xzLCxeDjCSuE9EdYTvTcizm9nMtr8BQ87xK7LYip5CzmDcfTFj8HbrQfe5lHejr7Mue2HnOv8zj73R4kOsCZBPX+5DTyBUkcRF6SINk/EBivgxSZ2V2hRO5XrQIXQ7cPY+sN/3D7BDcjXk2OtZzNIMuctYnjFgsZ2rCsUh+Mn9zfRHmcb2WOK6FnrM2o5mY5sInMFsJT8Ii525ilqfP38TuIvE33S4hLlwfR9YTnyNI6H2B+mzOsdgnwTy4GhnbGb9hHXTO4+Ykf5cb6j63M3opecnfXZHEpeiZ5Q/lLE8mgYSBWM/0PMR1PmF6zva8xnUeupuQnlwfgZexdzrvs8GlICNxGelDxlxU53/S8HFH3JKxz0bWc70a7kPOyLmgY7DPx3w3f1+AVzAPuoe0cN0EXoZBXb3PC03GPB1GDyN82BwmI9azQydyvRWuRfc0cgE5xPX8YZghEcuJg+kfvAxXXiRemI81zeFqeM3UNeMv54tmwzrDiz9ntEDOGj2C+66YRdxCnJDJ/D0Gzke2ILsJ7xw61jNIz6hzSCFyBYlbUXge6YAV7jNJ+5LP8/l7KxJ9K/rQfkZpVzgMKcBuBHZ5uMmDm5CDiK8zSy9gVm4laUL/LNdN+Hs36S83gnqBWTLXDfg7F65EBsj5pnvMa3gaWs863YJZTxh9L/GAcfAkZsNgHnJuBOFD61moe7jeAs9AYyR5CY9wXWcV8eG6J+wLx8p5qblcz+fvTUgB17u5rkM/2BMZi8xH1iMHkbOI0ZU+FUlCxiBzka3ISeQiEt6tvNEGGYHkIeuRg8gZ5DIS0R17ZBiSi6xGdiP53UvPPS39lf5Kf6W/0l/pr/RX+iv9lf5Kf6W/0t+/5/dznP8fn5IzJXvyT3P+/2O8lOssZ+M3kXU5ZSQtwcjnvGjbwrs599n4fXrHT2HxMqFnpJjfIMji9YQ/60pDK581/eGD4QHqfHNZLyvh8m1d9Vtgrq2Ed8Gn0c9n8adav+8Vbmo6geo9aC7LHrRqmJ9TbiYGtiX2ExCndbT4q/fCJbZWZ744rqG16t2m9FL1XoFn1UnK3dGvxOlFwfpM94+UmxG86whyWMfs5GeaUUP8rKf8bOAqy5u4y/hbyRXsuAdD/FB5MDdS79fQcWiv/IkKjJQ4RFjcR9jcl8E=
*/