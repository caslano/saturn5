/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ACCUMULATE_09172005_1032)
#define FUSION_ACCUMULATE_09172005_1032

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/accumulate_fwd.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>

namespace boost { namespace fusion
{
    struct void_;

    namespace result_of
    {
        template <typename Sequence, typename State, typename F>
        struct accumulate
            : result_of::fold<Sequence, State, F>
        {};
    }

    template <typename Sequence, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::accumulate<Sequence, State const, F>::type
    accumulate(Sequence& seq, State const& state, F f)
    {
        return fusion::fold(seq, state, f);
    }

    template <typename Sequence, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::accumulate<Sequence const, State const, F>::type
    accumulate(Sequence const& seq, State const& state, F f)
    {
        return fusion::fold(seq, state, f);
    }
}}

#endif


/* accumulate.hpp
EV2p2tKit4fdFONb/gRyjMWZW1vaxto6+Qd4S2PtNfgy9UoL6KNNmIixNj/KWNvjY/tY2/SRc6xVWMearp1F4fpRLEuvUv29ymO8ZdrGlsOWydNuKQNWhsrR2Mqnf6toi9v4/kag7hq/Zlx1dss0tpS+lvQVJKyqc4wtXS9OnxjbdPCpVmvsV+Gfjflqs8XXRPAKj+qHwc23h3xH6PpSRj4v/x7OMWTUbQP1quf3U1Dows02+zldI4x2tVs56bYiV/N96Cdm2ozwOGT4mmsK2YsFg4KrbWzjcVX7kP2J1jtwrTH3fWppH6O7C6YV5JWU7tSzxxvtQmOn1OPZQ7agtnFmTNeOdrP725E9eTNdUz8kcQbfuCe+GqhDCWs23ZNim7sHvW5eT7oeXO9R1S7z9wo9y1h9SZRHjGmNc/P+VqrYKRHXkl/9RxquTvVpTNcX7e1+Det6kX6lwTG1mu+pHekfY659jbqb49qcH5iS7L7s9CzY0Wmj/OYQ8tvSQ3a5gTAzWNAPP2X4uPhs12vJRza5tjJTOzntk9cZ/e1aZny24llOW3GuK3db8dUu/gPeNq4dVz3itxWvHRLdJjncJp3d/YjUbenxi/kRqens7kck+fMeu8WPSHoXdz8iGZ/32KV+RO5HD5sfEe3XV4T1MB9TEvUjkuLiG6Dbcew7u5QRb393Pc69v1e4+AVIIW2dS5mJ9DfzoaO/72igvwd3deqzwVgjfuHUJ14/Iuji6O9KDz8iNS6+CXrQLtkuesQ77roeF33cnSQ9eh3kHHfvGPORVQ89niYy9jQOsPV3jr1NlFPjUk4i4++9Ie7jr283Z39/QNp6l3IT6XPWJ865v4P73L+qm7PPP0SX1C+duiTS7+/FMPdvg76kJjv/Jjv/XWvnf9Whxt97NK+e+Pw+mw8ZddWM9JmvZD4Qv/3/9QH7/7xLXx35SN85I5M6VP70cPefvtkJ+/9a0657VYTdy9E+i/2/0rV0SUfRSqf367B7lPzS3vAud4LVPrqBcsdZ0pU7yvXIr4FyB1vza6DcQVY7Lke57vnVNJDfr810vEv11m+E1U6qgfyGmel4Zyn9ouXXQLmnWu3HGih3tNU+yyzXM798RO/tGKPBdK2M98xK94jseB6FveFjssd9HE6SffE5si9+RnbFf5Zd8eeyJ25Nvs/Kbijdp/dteg+XYthIwaGIT/4AAvd/2Bm+K/ut9+Bw+QMYAzdZ66n8jm9wvCNvKV2U8el3pPMYT450rv3KOxili9Kv2UrXP0o9qhzp3OtR50jnVg9kvdJFqUe2mc6zHn6f9tThOqWz2nfnyR69AI6E58DJcAa8ABbK/utcWAmLZH9eLPtzv8bXefB1WKJxtWUP7XtrP9wo97igHX3g853sAn/SePoZ9pddX7bs+uYZgFfKnu822fNVwRbwQbgnDPjahV/BlrCl7PqOll3fIItd3z5wuuz5roTJcKHs+JbKjm+57PhWyY7vSdgeviR7vjdkz/eR7Pi+lh1fV9nxHSw7vpNhChwLD4bZsufLkz1fiez5ymTPd6ns+RbCw+CDsBd8E/aGXbjvHg77wD4wFR4BT4FHwkx4FMyCqTAXHg2nwX7wKtgfvgkHwHVwEHwHDoZ7NKeP4KFwKDwM/hoeCU+C4+BwOBmOgGfDU9Tf833aU4efaZztC+dqnI2SP5cMOASeDsfCcXAGHA+vgxPg9fAMuAROhEthpvwKTIKPwMlwNfwtrIPZ8COYI3027KG9cO2Ro0/gHexajb+7Nf7u1fi7T+NvOTwb3g/L4APwevgQfBCugG/CR2AX2Vd3h4/Bo+HjcCxcBc+ET8B8+CScA5+Cl8DV8Cb4NLwNPgM=
*/