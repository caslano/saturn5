
#ifndef BOOST_MPL_AUX_CONFIG_ADL_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_ADL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/intel.hpp>
#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// agurt, 25/apr/04: technically, the ADL workaround is only needed for GCC,
// but putting everything expect public, user-specializable metafunctions into
// a separate global namespace has a nice side effect of reducing the length 
// of template instantiation symbols, so we apply the workaround on all 
// platforms that can handle it

#if !defined(BOOST_MPL_CFG_NO_ADL_BARRIER_NAMESPACE) \
    && (   BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840)) \
        || BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3202)) \
        || BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, BOOST_TESTED_AT(810)) \
        )

#   define BOOST_MPL_CFG_NO_ADL_BARRIER_NAMESPACE

#endif

#endif // BOOST_MPL_AUX_CONFIG_ADL_HPP_INCLUDED

/* adl.hpp
nPGn9+0vcTuS9ldfJwDAQWb/9zk/MftYf7DzWsa/jsOpb/6d/kHnOSanrfZnjnyLw4mcWYzdv+RbRebacPD+rC98iiCT+/dz5P8q/pSrjLZsWAcANtLMIsMssgDbFYyWyRjpqGvrqWhv2rhBRQv+DAcJe2crC8fvbTtVEydrpz+1nR3+2nb4S3sffNe1Zr2KrsoaPXXdDVv0Nqwx0tPfBH/RyUyN+yy+tc2sTByNnA/YAwAAWFpb2JrruTlY/EXP2g3qWmob1P6qd6vuNvW/yv6pB8DMxdHVAgBMTZwsAADsHc3/ZLWZvaWJmbO9459912GatFGdadMWAABXE1sXCwk7ZtY2N/o+/q+8w1/y+V85a+axZm1m7WzrtkYF4JtOzZ+1Avwx8Zs4W2hauAEAAPxV0/cxRjq6G7ap6Klrqu/4984cJztpCbP/7Jwys7Iws/lpkKq49DLZP9Uyst9q+T/XclIKf6qXLpcGAM1vcprf5DS/yWl+k9P8JqcjLq0g86daRkbuz/XSZX+qZeX//LxURhr+jAjyLZ9823tS6qn25aqS5j36ZxbXec191zwvogF/Bv3e+Af8mPm88QJt5zw7piR1pTgulNpAc5ve316bd4M/8MrkdKmQz0eK53avifeFAeT8egwZPOwComew/PlBMwZ3j83CqganLwfiZ7ut58YfEN00vGyazYMbNx8vlv7R7lnf7C7cL7cuuuH+2Ev1rAuJeSnBe8MD7uEv+PGz8J/4RG+O5zzJxZqZMqgis01HLT3nSfHTW8ITFdYs2Io3cyZzFdrcLD4qMzUkT4Pldt22Uu75cjKejdwGgvMKl5v5Zg0tGNWa/7q9ao1L3E72deZqDV7RJ8FDDn8Cb8Kb3E9KU1+JqBsYLFn1oz9S3/xJXBq6N1Eg4ZAg+O3d43Tx2KGqa074z0F/9BH/NX6VH8uUlkx6q9TRGhU03qZlWFyAX/CcHfVS4WGZNiFYZ6rPzrJtCoH+ErXnl5ws76l7v+TjVZ+K+UUB45cH3bg/u3/udWc7wZWmAUlno3YMqbw5prdEfuu4vt3FW0VsV+gZyju6cuYs42vSiFgkZr87Nqo4NPSlyPCAYOHimGlHup5LT836lFvCaXyjWtDD6/yhNYJHQt5NNsJ/gPtmG70Glou/3j5jUsb69KRD798L7K28J+L0YxxVv8WxJtYXRGblbomo3MOnIHPiatxz81sE/1v81xrGYPMZpTyToFkxc0Jj5sVln1z9IeG5467ozOn9uTf9Tgf1cjRvE1DY/N4j7DCvbknhyhvF7EudXvuuEpPr/ag+p95GRxmg7GQQWw4ra1dVrNJDywVnbqqeM/dSGK+cNW94cZqxzcZVt+I1DQ987NixmAreFk7AK02y6zNvn9yrevaLh4d0aVuhJeFXENl7MGZlCauBv9FNMfeZz6IG1Tbon1Wz4ksr5BNWshSL/OAYbTiwaPU9nTyifJ3dZKmig3eCY+lq36Jw1wu1ljr/Mg4jm719jhdLRtgcrSTrhzgu1azMepDrd25dar59zuzT8uYcv+Yf6WSJt+Mu1E4KmcmtFM3O+PR4Rln2f5p/Kuc3vs4zsBFqPTfJzPxiWxSXwooEXqtnWz4k3Opo3nBQta/pgPWjrgd+JY7Xre3Xs2hYONcKWme/P7RHNHfJhFV9fekn3LscMpqm/6jb6EbSwpeeKt7rn76S/nt58661ldrSpsyDd7MNknfMXqJvNj5G4j+1ez7PqlKFneMrklRXpVY+WGecVG8qZNNgzesucsALynYKxh9czrs9sFo0QOND0Pxg/gj55CnzzZyWy2pueJm9d1/5l0j/Ctf1yWvS8QccMq2RLldWDf+8+v0=
*/