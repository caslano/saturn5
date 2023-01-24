// Boost.Geometry

// Copyright (c) 2016 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_RESULT_DIRECT_HPP
#define BOOST_GEOMETRY_FORMULAS_RESULT_DIRECT_HPP


namespace boost { namespace geometry { namespace formula
{

template <typename T>
struct result_direct
{
    result_direct()
        : lon2(0)
        , lat2(0)
        , reverse_azimuth(0)
        , reduced_length(0)
        , geodesic_scale(1)
    {}

    T lon2;
    T lat2;
    T reverse_azimuth;
    T reduced_length;
    T geodesic_scale;
};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_RESULT_DIRECT_HPP

/* result_direct.hpp
3UnEKPF5yGPxh3L78h9vdqK6aMUUWP/K7NJZLWGIT62yz/ujrPYbr85lMuMoBrU0hkL/kJmhthuvrmW6Fc7gg3+2llkdOVn86CfGrr26l8ukfDq3QsbIF2FQnYWbhjf7oltcwcexN5UarH0kpbHCyY3/Exk6eLKG2f/lYqDhpvPEQl4ngPa6hT0yf+BpPHZEFWj+WWY2kZwySurgOGbAAv5dHMZvB34joMm89Cwae+GrRW9HsOXYQ0Gltj2YKkrR87VatPmej4wek3mb0Vl4lZed3Ntt6eHTFyt7Umh4luZLervKlbuQk0hOloYTwSoZ1q+WtHtJL81c6zVYSzVYI6WOTSWQpMKCsaobj3lkhX2Wb0dHr4Hbwckypj6NlEz73nO2nUsBRRyROB0l1tJYhIyZTUbLcNfDs73M4a3oan3JBEXJreSXct/SjmT4bF6iZAeEcIdEUrqX8QulVULesP09XNo1cfuB/SFe9x/E/6Q+97uPoRpOz5fR0fxWiXC3oV655+DA52HtGHGmFmcXo57/7djtMSNB8i09/hFOU89rg38Lz97lAFRcHCeWKLV5wj4qWD2cOeWv6jdZ8Giy15yOUlBqYHS0RX2BNVfSDTnfIumWxPGrsye6y5MwhvPkTFk3dVOHTSiwsqLO/2x/ulEGoDUTeLS00tnDdhUXlUMzHF7v6/FrPpJaY/+1zuNK/5sxgmo2zjVCInRk
*/