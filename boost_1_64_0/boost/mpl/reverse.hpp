
#ifndef BOOST_MPL_REVERSE_HPP_INCLUDED
#define BOOST_MPL_REVERSE_HPP_INCLUDED

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

#include <boost/mpl/copy.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Inserter)
    >
struct reverse
    : reverse_copy<
          Sequence
        , Inserter
        >
{
};

BOOST_MPL_AUX_NA_SPEC(1, reverse)

}}

#endif // BOOST_MPL_REVERSE_HPP_INCLUDED

/* reverse.hpp
+DW/dboMz9WJRNVfElV/RLf1538WWT/8drf090fW39pt/cKo+qu6qy+ja9/FI5M8vkFXJHm0i//Uu/qLHuqOn/EHI/lxJcRPSinR33ES0X/qj72r/1F9d/zkRvEz/61E6G/7NtHPHUf0RyfEj1H/W93y07Avkh/tze7qj4jiv+HNRPg5q5D4+S7r57rHe1f/1w92x88q8C/naNd19DAf1i6z1D+vx/qFYXP9zB7rX/apuf4bH/dUP9dS/+Ge6iv9eM4g1SxdL6vHLp/+gCpX/XfAIn/Cz3v6UqI3KP7zUL7r9z0874WPEn3erZOIXv0fZPXY5VdHP0/rMD/vSjyv2/6y8Df6o0T5++mV9Hx3fP5QvrlOlVvXv3eLeA7bR0b9BmMBBVeYpDtpq/8ieXZmJP1ro2CtRgVLVfzrFyJYer1JBmscdclX9xduAj25eFC7QSRLeflaLpSc5FuhKN5uohiQFENnhkaDgxTmgOqvUvUXmep/XdTvzSSh+3gLKwun+7bygxZO1Y+Q/mO7PoF1o7ifUaz5se2c5IKS467/vxaMuF/CN6nPIEF82KsYto3Vzf5lCJkxD15cZ1kuHkhL/sv52X4msVro4NIdXEdMnPq8HOzF1Q7G/TcU9UZefNNhZfNWrJSqzQficgLtHDq5YHB+veAc14fMC+qcd6hXZuqlOB8E036VqW9mCleOVzegbEMmYm06mjgeb2rb5DaRg6KQcsT+v9DD9FxWSrFJKb8USpn2ApTiu/irSR5QLhaN+SIc7b1dvb0pKLE/Y/3r1fj9feYrEf19HI9krDf04B3vRPT4VUK4O5jI3UK47zwP4aCUgbt60+PR/Oah/6lz1S0crZaLddrMQvjYIqSv2vwcrELeIjMSt8R8VRyQk+wPUE20LNEBweNtQJdcBOzAImAH7jEZ5dYh0ZFV87y6PiVMm5XUMUDf3POxdI9N40uvk3vchvA6zs38QgdlWCOhlVZw0hq6zVdOreQbr0tMragT5nMrlLlmmVppoQt8C6kVVYEbyzNa4TUxWoklDFOrtlA2JMbO5cHiiGbo1GB/CrrFZTzi1g1sB5r4rHFVTypp38Ya/viCJA9EnpKh47Wl9/36Rf0Z+5/JrQADyj/gZpY83/KmgQYg/rBFB4SHSrGqjO/NXHovIGEAfrDYu5hDh5QRH7ikCsJQwYCZSeLlzPvpUEHi0Fb83vNSJL819EjfUupPFTae+zepfrnyyuwt4PEm5dZs1AVuLxUdQVyTQ4ZAb2+XXKsdqo7EmYy1Xvo+GbFZsbm+5mkmS/vas2bFlueDi+XC0vjSH1Vbe0CoDIvJtp43oMbT3xW7ovsbbI0/38TWM3+19Hc2SoH8G3U2vlImbtFYscrk82RNbJzfn6ZrV95kpR16IxoTGAuffPfwPV3k+9+/R/lnbZo+2J9dphu6/JrCfWCA5F17fwSQv+LroFZAk021ysEgaCu7Gu553a/EOMQHmMQp499FiwdXOdr3GP2Esy+7zfcz4el/tAXN+RG+Ti6xa9NFDAzqY+/9vCqJPR5cQRt2rfcQ+K4y9/xzz5hcP3l5lKLnyQfDy7N/x1g7bYdJaagqu/5Qqqj6HFWFvZ+WIld9UUsgulnUirP5Bu0+SVaRxM2kCrHZNM84ZVLaAXedQcMJHxIvaiMCvKTH/po/VVHUgjsRzvwtOJX3tGUbPMwWPIROYv8N4+usN3rRHfx+VxerSzlw9M1t4Io/VPOF9E0if4j/+aWjb4PZ070DTnLARMz6dl/5VFP9x2X9uPg4tykKHzPM+Pj9JuBDXlU4ElfTjX/eigTVROsQqgo+Hr+P+zplH2fV4Iou2c/jnXH7WTP6WaOeo34=
*/