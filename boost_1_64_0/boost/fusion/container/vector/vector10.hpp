/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR10_11052014_2316
#define FUSION_VECTOR10_11052014_2316

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   include <boost/fusion/container/vector/detail/cpp03/vector10.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#endif
#endif


/* vector10.hpp
5ji3J689uGyb8vC5jnblsfwdsI5tkueL+XsdIYb529Gorflx5uczfw3Lr8O9hBMEozbo/nyuO49lWLaAz534ezP7HsH8M8wby+ex0ka9gDBf+qTbzN9b8TBq260XM89/vq39ergin+NwPsEnhnVR2659M5+j8AiGxChflo527kG3si7zYjAPC6Tdex6fi2JIszKPz0V8rp3raQoiRBISCIsJGwh7CScJdWd5moIJMYRUQj5hLWEH4TjBNJvrmhBJiCPkEFbNdreHd0/uyT25J/fkntyTe7oW05Vt/5/Kf/FZyVO7hYaGV037/4eamtR+RAKkzOtR6cPsIcLS1koBnvX5PzpG6cItPjQkLDw+tHtIxdqBB+ABW719qr4/qAIX8cWe0sYXFhIeER8WFv774+ODYXwBpWXj69b98uM7g3FV2C9KZdsDXOn6/crWy1e2/v1/tZ59g7U+fdrPC/42be/LncfGvD+n5O3AVZdXnx5gkutSzmdvXX8A7bT9C5xyvVywtl+RUhfLSTn/UulfwDSH51dCDCGdUEDYTDhMuEgImFt+uV9Fx2WPnut5VfsXqOq+Ba7mGAGxcz2v+jgBl9uPwOX2IZDEPi4mrJ3rLu9wT+7JPbkn9+Se3NN/x1SdkHxln/8tWRlV8+y/UjN2/1h5Fl9J8CMsJ2xvTfheno2lq2TrCyLxyTQvqXi7//l84J1v9Z3/OOwn7/wbvMsv75ip75K4n6ndz9Qun6lLrM/UDydNePW2ez6JCfmuTfrovNWzL++ZOsEk57tcB966Pi7rS1uwRhiKvjgO/XACNkELNsU7sBkuQ39cjs0x1vYMXenn42vd794f+bn4aj8TX83nYZ957udg9+Se3JN7ck/uyT25p2s5XYX6f4uj97/fXwawRDM23lopA9iFfrgdX1fq/79T+4gg+hRzhjKAjLn8/lvsfTe8Zuungb4b1L6tZAx9y9Qpslyebqz9pk59AWTnTqHgYYbZMe5Vkvpv8g+aflo2N1Dmz0jSjPel78tB3edgaRMwg9CAkEpYQTpij1j32drnFztNDyWJGbmWirUJiMJlDZ37gwrQ5YO2f4diSUO65HsK3s/6Jbo00A9fJeNPys6ReTHqvOysqTIvWNLEPNJUfjpXVZcxJnjWDxA3sM2iz5zTSRdp5abTy1RXwVTwBeui0gfXdNvfQSNGdQ0xybwYdV5YT/u8Gx3zIuzzDpeo87rZ521zzAu3z1vpmBdmnzfPMS/UPm+qY56alpbqvNAe9nlff67O62qf94pjHuva+kq5V50XwWe2r37u7vKciUHN2HD6vrskrZSnqX3FWdgnOba646g95xezrDIdJAH+uA+fJ+6Co2WOYzy9+JTb16f0WVQm/akY5O2cfos6j+6Xcs3WPlrWcF5NqmF7B/JNWxq0/QZpx8ZSly9k+eHM8z3mWD7G4F4TcoltFEucszTbiLjE8vxp6gN7NMtHXmL5EFm++XGj/vPIE1nei96N3pH9foP0K5/bH3P+PE/3uVj3ufVxx2ftsd4u/Rpuuo5jjc/ieo5TwAmnY51kpnMUs6n8fg2Vc3f9t879/iw0OPb5aOsbihiU4yTfBYH2ebbskjwp21deqtovaFIqnTfJea5ta2V8zJW8zyeOrez3TBI58RtH3idgoDWeicTOvjj1YTWxTB8/UdIf4Rr5bniQcB/xL/zEKe/SMtJyyr3fVeZ7wX7sDkv8G6VMfoOSBtaP+topfuA7uRLl8fo0xBn0zROiy2unfhqlyOlz+b76GJV0lRx3Spe1xoCU/a77hy5dhmNVBhucFyEGvzEiDM6VI+TxEU8Srbx7/iXpR199P2Txah6odRHF17AuorI=
*/