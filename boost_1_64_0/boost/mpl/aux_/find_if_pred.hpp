
#ifndef BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED
#define BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Eric Friedman 2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include <boost/mpl/aux_/iter_apply.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename Predicate >
struct find_if_pred
{
    template< typename Iterator >
    struct apply
    {
        typedef not_< aux::iter_apply1<Predicate,Iterator> > type;
    };
};

}}}

#endif // BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED

/* find_if_pred.hpp
EXXoj3haV9t0FzNflTLfS9mmObSYigC3ZjqCpwekY6+DbPqcidEp62rtNvo8qY2+zy3tjEwepu8sNjkbiTEOotA3NBtkRbU6iFqF9Ke93Q+1FmBA/NGLFUnZnnuQGLPQPm7PhCqa9yjBnSeyKw/0XP4wlpgmS8iQSqHoyf0dO/76jv60fuK3RGPK4PvPsYDWbkg30Np6Xpae3dpB7SbQi8fi0nO3KurR/VVQf+yiJZTtlIZHPuz7sgQV9DJbO7wFKYbtfhIGxyUv1CW7WN5T3/8K92RjBQeWaiZYHuReUQZP6U3088Zw9APVBUeJzZPrU8O1N37o16Zp2kDR2iny8kXxM3g44bFMOVCuXUd/sMztzbe89tKfrs7H6TwMDJP9wTJq/BL1Qr2/n6hJTdgb7iUuNWihyS7lJJXNCBEZD55TjrU5001l/WS2hR4mSZJUevSU5aY2VjdEw585LW0+P8edZx2EBqelCp9K9l6SQE8Fgc7wyEAXPhoUeQQFMcV6SxkWRq1jiM9MwfIhe39XZDPVyA7pZ13J8aHruY968lFIKai5jvn01Ic4EdfSHIULdOAWZew2r53yV3+SGiTFnrGNcy7aYEcIKf3QO9+kXV0YVsCp15g02mps/SWF3jj0HepRx/un7tcnR7Z+v/5+VMv3Z78fNa8/My2O9msUtdGk/ydCQLQW/RyOZAedxQWEuYihfU1P+SV4CRTnjsJPpyPINw5+JTiCF4eLCcQlpcXpChlA1X7Gq1LPacNQRgZp1tYLUh5G9SDnMQM1OxARez/qcXS3fF33pnryUvUybviJA1W/y1gE0l/DpNl0LQaT8ZacW1rlAhLPZ9dqMADYyIop4ZNRZDYVCXaFmk5wwX4BGVQ4RjXlCXZBuaJ+85EXvyV/0+PpgibOso1nuBxPthqPh0qL8RSV7h8XPRiXHEyw38NtHIx9v3QiwXXUMuVHoky722Fw4Ij0tHpO5p5LqzLQb0Kr3pt0f/cOtvoz27H2TxN9ZTSxHkLAE2d3Vn+D7f3d3rm5/npa/SVzf6X7451bVH8vkFwYzWbgnl3pxXpyjy4Yyof7hUW7vdHN7NL91CMAGyTAFrrjDMlh+X9U/XVBf8O5v5CQSFsd9OYOFuw7hRa3sJPcNhqe56uS7mAHsGTmjoNbwpxAJFACwK0YZvcYUXSsDr04LEGFQuYwRF5psRT3ROK35+ZTgl6nsC1P8/sd/KvZx6c18v/RRfr/aJ7+G4j9Ulp1qCwHkR63ucpyGfstYv8JyonBGYhJb9S9RhyCdJwjm0+NPsZDOnM8ou4K/x+9tccmfqSQuA3oMhnAM05RjhuYChKb8UTjcdUO09D55pJuLL9frTJAd/sp3JHMeFJmgPwwd7F4Tzg0Gu8z1lh56fnmU7Y8P+h4YQ0O+s0vXCY93XgOC3vxQ0UQjUzfle53Co/reR7+2bHAp35qZyEEfzhAJALHXzbBi5yMsqmpgGNh6dgGeI0YaQwdk+Yzd3VmxysiUWX1NLY0HsrXPflCycZbppMoSY/bztptlfFa4zqbuI4S9OVhBJOMN1VJQN5Hjhq6MizfioK+P9/sKjN2qwzY2x/sgtR/N65N9HnII+gub4B/lMc6Sf8oDc37R9H+P46lbx2KO16W40lPzFvS1xfuLkzPzA4a5vdza63gK3gVBQPF9htH0c4/KD4W8ZicRZ1Fr/M86Mop1hgqmNgP0lnFsbCeThEpZK/gtaH2CBdoB4XsDvGsiXX++zcVz8O8lo63MEwZzPETsxUm4BBCDTh/d76gth6ulMTw+vhDC1D/am7t13ZA0Ay5VPsZ19E80FA0PLFudniCcrToReiHIdZxhJjBv8CGZW8=
*/