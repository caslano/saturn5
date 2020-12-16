/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_TUPLE_FORWARD_10032005_0956)
#define FUSION_TUPLE_FORWARD_10032005_0956

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/limits.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/tuple/detail/preprocessed/tuple_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/tuple" FUSION_MAX_VECTOR_SIZE_STR "_fwd.hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    struct void_;

    template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
            FUSION_MAX_VECTOR_SIZE, typename T, void_)
    >
    struct tuple;
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif


/* tuple_fwd.hpp
jorjGqQf2GfSsd/AcfPXCF2aWXscM95uv4nBjmXTPCd1Q2F29TGQ53juxMa1fZEh99sUb/sZlHv0vveGQ7k4TryCeKMdGmPRPxM6aacoo7wfxajeyZAxfaBN14bgmBgxpl9q0n+N0KnfImPn+yPOrst4pud9u2Na+X7TxtKWjvm++IB7w6HYJj0W3vZwWJ4PvDdcW+4VG0+9CMr9x73i2nLPHqR46j17mLffs3Ft/4nYmQdR7IUBzgvU1dI9Q+41C9s1UpmtsezQLbE6gVhvvkZ4SJ+MNjzkwbth2vLe3MJilcY8/TXF2P0rlpX3kBauc6D2XJ2W28IbZazPUz+U8JE5GllPojjiCbFsH7YrRoeGY9v/KmKb/sHUt//hSKf9R913vAxiACLPd/qJ//L+aS587yWpD3xVPERNi/JFO07y4oSkyB1LDBGD4TliIHaGYAYbiGn2LC9PSsxw4yI47YElf6fihSj1584ZIXbNPccb5pqkFwZRlvH6jpujPIJJD74EQGKEtiu5cM1cI/WRuK+P9M2RihmhNo0r2rJlE5G/VWPOLRvyMeYc6UjL9f4qmVNFjEdJ6hVOeLtzKnnvMes1ezbvI/LUHqB63KZ7rfS1ap0007sWmH8yNI2puvA4GGOIzOE6duWQkebXT0hKk85fTMhvGq3C75G2NkloagcfY+AJrYokMs/fp1OELnflkfcqpW0NoNaRGItpQldRYGtLF8idCNcQQ+Jw6reokFbF4eA+P/kOSziNvFftQ1oTo6PHXA1NZjK251ftl99lacoTC8aZZb1evi7LVdK71x+PkHLPmJ+EoedG/E7rUbX2t7u+Rxrr46PKXnntDdiMvgnOrNs05YOQd25S0qGq9Xfq7DHWARVNqZQC2uuAU5QuKxm5O2Ga0u11wn9Qeuc64ZU9FCONV3RcQ6d0+MsFeaAP72B9nbmW7TPXcf3QyQNWQP7DMPjkfHVJrszTzWqvA8v5d6/DfF8abxzT+R7keg95jZZzmQjhOJ74f8r5JQ/u1meX8+aETmbVbvEs+QTSZGa08voPFn0EB0iGy+oMMvYFK5OIIe3huvq+ubZSZTH0NbAfZ5bRFKEPNio6tocrZhnwkEWZn0dFettrVXJJVq9V/f3p0Df/TM7H6oVamT96zcn8Xi074fzxqYRW1SJcY1I0OIdvkskaAZyZAr3+mT530tR1eKJitf5Jv51W+W3cibCh4xvhPK2WbWI+OWlgZGkaIIwLnerA1DcU4BmpaQMDHhvFGGOjdE8LQy47wDHDXgMHgC67v73PwIyJPqyrq/slpvYY0BX3jP3dnyjaLdfesX5dvo/EW+Vj1O1fEzopP6zb7L4Ks7O+fpcsjmYP7n74XYeyIc8NgwZZgTzfPiC/y0yEOUFVz3BM7N0faPJcvFEx8LC+YfM9Hbj6Hg+U9egHtDF4YN+Q9dUOnD6wj2cdHtiBwf65bucdmPpQP6b9zMEac3FzuFIZguX0PULDRCPvkQcRukws0j5EaMp4pB04ZNLAaIPvbkKrjMXxHPE7MSsKryiz5LbvY4EdFdgHpGPL9Qn/pWW/dOGeCBx7Pl2nYVLSYU9wvDQ7AydEN7fA2urVmWX1wItRp+emJLaS4coqlA1lM2zq5XRDP1UoIvZL12K5x7jcHg/oWIFrkr6yalBXNe13Ne1SQ0S+0XVFGy910K7/dRJoA1Mjxk7M/KeiXZqdnz92YpcxESmLjHm5cNMgce+8LNSYaPc8qOntPEBaVx4gjeYBpXXngaTtngd6XfRDTwebflavaTfkzZVxRf8w0K+fr/ZTwKssba0YdGNvfK2qfzBTlGPoqpt/Ap6Ls+k4pEIZv5hsYVaqsS0=
*/