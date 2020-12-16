
#ifndef BOOST_MPL_LAMBDA_FWD_HPP_INCLUDED
#define BOOST_MPL_LAMBDA_FWD_HPP_INCLUDED

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

#include <boost/mpl/void_fwd.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   include <boost/mpl/int.hpp>
#   include <boost/mpl/aux_/lambda_arity_param.hpp>
#   include <boost/mpl/aux_/template_arity_fwd.hpp>

namespace boost { namespace mpl {

template< 
      typename T = na
    , typename Tag = void_
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(
          typename Arity = int_< aux::template_arity<T>::value >
        )
    >
struct lambda;

}}

#else // BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#   include <boost/mpl/bool.hpp>

namespace boost { namespace mpl {

template< 
      typename T = na
    , typename Tag = void_
    , typename Protect = true_
    > 
struct lambda;

}}

#endif

#endif // BOOST_MPL_LAMBDA_FWD_HPP_INCLUDED

/* lambda_fwd.hpp
S7XoUKFhhI2ZLgLEWBA+4fUMKA2KGUAV6eU875H/1uX8P/7D681gxP94ML49MdxmKIx6dSQ0anEBFbP9LzOVCeAQc+x90q5X3jqttBc8bt1NiCR8dzmGODmV93Cqm6z1NNay5baXrhKeYLAlAiMDW9V9K1DE2KlSsUN3y9QfVSo2sF9ivAkPNg6jAdAuSocsJeRqCec2cBGGMp2rFO3wi/NQRgDhc/KrAy5sYCiJqQn0IBY4pcmkJBW7jT6GV41kbNH9ggYjXaXCEjdJpFI5LpGh8rBhH4k8qq1GjPYjlv8bR7uO1zid1DHcdj+Bu8nMPhKyXbhTjy7wzkWE8OJmNgm3ibuu4nYS1ltxvfkIeL9SfsNmxjh0epN+OYtsUS1riAHEQtw1bXTjmpmKr1fcKF4cl9dsvFbg3PeetV/SKxnsH0uMRKSLKbTonrsUuVxCBDc2+wgi+Pm8XwPBbykBDTER/L0/XUDktyVyEPDa28jDdHfvOSJ2NgVa+KO4CUcStKGQTbn55s/bNVpf/YkmDQSlsYSIEOdJwlUbqTr6/TpbojGNvLoB+phIFW/Uj0ALoYlSbmvw5EKn2GzO7dJQHieoRNvofB9dtCnITEEI8PU73eWfZIjb/0H3OMK7+Nb7ic+LMp3UvykIi16+I4MQcAWZHIFncQAAJ/ucoUdkupejkW10p6VJRJnjCG7j8T7nnt0xi+TfGW5+/+9eu/xC4NVAkFctWjOxWlbyd4QSUrEV2ZZAQ5yOIliE+R1ynVqDdcq4VGh/UCpC+7NepCCCa4QCmCnysT5iRZ2XYzyo1UDD76cRue0WFSb+EsrBVRzWu4SqIjFZIXc9FM+d3H7dpMEgqBEHjYLqliuDK+URqFlRynrKM6iX/zqQ1Y2yIjDhVg7uF7JrOkpQDPQ/yIV9JRCshKIzqCLI/MFcCy7kr+LAahmXoUvYD0eVwfmBTxQLeILMXmgPKbJ08Bks5y6w0RtesicPTJeA5Kg2TgrBu1Yz7iIwbunNqFJRUD/fpkosXIOWrL5c6B5j2RhtPiF+VaAmIUkb7/s3SlJ84r+XmE77AxXRAdc91fOUvam7EISfI5HQN37RR43YD1h3TzPmYOnwUDzoSeJxAX5CwPhYc/BS+q+bOfEmNfT+JG92r0ujsObGeU3ChrO7t7seoZlT+JoByXOqzAVR7oE5mZ+nHF6apdIbbemNg3Ez7DeEF+hATDg6fzdjUUgIMhuZpfsYUwgeqLpZFFBGjtGo6feD/ltvVPR/SjkIXNMtUOwxpjUptOH0g224Wu6Bhz3RaaYRX77WeK8A3qM03grKITqXhgRDwtn5oy52CYql6GKTwsg5Ly45gYJ64wrNHUdYLslLz6KC3SwfXcK23/8hW4x5uqUa6MFABbsXeeKxmBcw4tteLkXoVSD0rKAi9HEV+jF/hv3537mjFK/qbLyqG1xygNFL4cL1faDrrtCFzg0NxeI9EMXp0anBVHsfXeJ6VeL9JarEENS+qVSZ/LwcSyyIIK19HPJy5s/y7Ox/7MeKf3YH61PetFK+VH8yLfGhg+jn/vh5Bv/sQz8z8XMK/cSV+yvoi1jo5yidYH3QrhO0CZ3gCVsibnoB9HZK7fDNZMv/4Xb2f7gD/g9PRNjPbnRZ9rNp1OHmYtXh48NcIA67FWtopKMS/B6un4YyNNwBevEtnbeXTXDy+r/Mvv6bix7hNbKODq03Ldy8S9nBWvS3ev2tapfaaTM0TygSl9rANJ2a1001r+GMblTTnMmM2iRg80p8beSvU/G1eRevcpzHkUnWcg7pt+VrKR2b+Pc9cpt+yWaOShsI1u7inXotZzvlTv3pubxTpyTeqbdxjkGwtOo=
*/