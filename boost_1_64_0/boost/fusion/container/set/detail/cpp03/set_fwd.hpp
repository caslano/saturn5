/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SET_FORWARD_09162005_1102)
#define FUSION_SET_FORWARD_09162005_1102

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/cpp03/limits.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/set/detail/cpp03/preprocessed/set_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/set" FUSION_MAX_SET_SIZE_STR "_fwd.hpp")
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
    struct set_tag;
    struct set_iterator_tag;

    template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
            FUSION_MAX_SET_SIZE, typename T, void_)
    >
    struct set;
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* set_fwd.hpp
uAO1vqQ7sT2+iZH4Fo7FtzER38FMfBcX4G58GN/DFfg+7sA9uA8/wGO4F7Xy6UO8Hj/FW/CvOBj34RjcjzPxM5yLn+MCPIgv4he4FQ/ha/glHsXD+Ct+jdeQH45gWzyK7fFbDMHvMBq/x/74Aw7BExiHJzEVf8JcPIWT8Gc53hVeUg+R+ol2TELs4/wx8X/Jd6GS78IxGKMwAjtjT+yCo7ArpmA3nIg9JB/2wsewN76EffAN7IufYj/8BmPwBN6Gp3EA3khcBuLNOAjb4+04DgdjEsZiOg6R/HgHrsCh+DkOw8M4HH/HEehDPhmJTTAOm+MoHICjcRiOw3wcj0UYjysxER/FJMl/Kfg2puEJTEd/0jMD22ImRuAEHIwTcQjm4iy04hzMw/lYiMtxMj6BU3ANFuGdyn3sw09Xs42VFVhezXNP23NP+6rd0w6M5l40oTjac8/ZM3kmz+SZPJNn8kyeyTN5Js/kmTyTZ7JY/rPj/zHOQ8GfNf7fqsYWZ5/x9nL/r7n0GW8iY8lYa+ueWWYkTk6N51FlMuspLEjVolP5d5Ebx5HpL+93dbwrbKI8307GCpYt0287OzenID03OzVvqvSf1jaeac2aaqnkmICn6l3ZmIAN+FzmfEaan5yYleh81365/pm427YIscbxAfXPMZ3j8hUZnqdq2+4t8yR+9BW3Gp6VT+FZMfumf1e0oe91dmL+RIvh+fk0iYtu7IEgx/gfa3z1z0kPOD/r2yVYpV1CO+nz3oYwV8szN6jHzZBdruAd2SHGfu669NWPm1dfnrnnyDP3TJzF9ytuMHvmTjwq+Wz9l0aVG2tQzTOlbvLMcpP+8GU409AfvoHkr7tbuNbBH9zmsWg0jmUSp7SLkHwocUxMpk+SYfw/q3mbCMkPixpKv3vJD+/L5/XyeX4j/d/fauT8u+4916Uy7t7X/LE5HsKNLGO5ybZ8ehoHaJA2xGclx4N5v/Elx4MxjOtQJOfOH8fJLDI5H4vxiOG8LcEjhvOntBLjROjHkSxwbiPSNc859s7am/RtEr4xfG7WWP95QmP9ufqY8+/6tN91rYwJImm/BDezTEITJe1TcguTslIrNe7G0aaXHHfD0F6jyDDOybRKj8dnSCdnGbW7iX6/zxg+t2uqT6cRTfV/n2X4vKmpPt06Srp9Ire/35C2ca/hFi3dblbSrWhqpfJrrZZXll+1z1bDuCRFJvm32CT/lphcd0r15b/bcVBjXOkdZvlj/g2xVO5YhTqO1YZm+mNxyvB5qJ/+80LD538YPrdsrj92Rc31f99r+Fythf5ztOHzdMPnzxyfPeOMeMYZoSHApixt/rLv+heHh62q3Thw+oD+C7Nr/uvjjNjq1NjcpJ/qo9Kv7DFsgmV4SvJfmXxvorQX6SNj2Vmk/3Nz/AoD8Ch2xmMYj99gGn6Pa/DvuB1/wj14Cj/FX/ArPIun8RxeI++nq42/YT28gK3wIobJ++n6ow8+iFVxBV6LO7EavoPV8SDWwL/hdfIe55p4A9bC3lgbb8PrMQN9MRvrYTHWx0V4Az6LDXAbNsQ92Ag/x5vwa2yMf8cmeB6bYT0S3g87YnO8FVtgIrbEEmyFe7E1fopt8CzeghfQH1uRDwJwALbFOGyH47A9ZmEHnISB+C4G4YcYjJ9iCB7EUPwHhuEvGI7nMALrcdwj8QaMwlbYFSOwG/bHaLwDe2E89sZk7IOS/6R+ThxN8t/D0l/vEWyDHEN5n77UpaWOzfd079OPlX6JQ7At3oHBOAw743DsjSNxMMZhGo7CSTgaizAFN2Kq9M9MwxqYia1wAgbgROyFWRiDOTgeczEZJ2Ee5uEzWIAvYCFuw8n4LU7BH7E=
*/