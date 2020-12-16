
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_sign_/validate_/defaults.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_sign_/validate_/this.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_1_(sign, error) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY(error(/* expand empty */)), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS \
    , \
        error BOOST_PP_TUPLE_EAT(1) \
    )(sign)

// PUBLIC //

// Validate params before starting to parse it.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE(sign) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_1_(sign, \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS(sign))

#endif // #include guard


/* validate.hpp
rfMkFmH/HsjrkJ8hCfnI4xzoQuxrJc6ZY503cSv27XMn0ufCduzvAiyFqPMoZmP/Aoh9PsWNCFsAXAq0z6tYOTd8bkXmaeHzK0oRtgtwNrAJUorfNwJXHoh0geqci8x5HfMuRuH3FIg5/6IRvxdCzHkYD8/rmIvx+zx38zFGnY68QxZgvxFozstYeHr43IxWhN0KXAUU6z6egfxifzMg5mlgvoZ1rkb+GR3zNQJA/TwN/IbePZDXIasg9vka6fORh2CaQHPORmkwDNg0P/q5G0vmdz5/YwWOYw6H4/yNnDM75nDk4XcFpBFyLSRzMnSBunkcbWdGN5cjeUFoPsdmwOQp8B1wKDAAXAAx53e0BPeBrzvM8cg8C+cF5gCXTkFegLMhK/B7IVCd99GC/WbgcqBRCH8Bl2A/+2zkA/vjgOpckAD2zfkgN05MEHNCbkXYSrRJCTOxHjQkF1IFaYQ0Q5ZA2iAJs9BuQcZBKiALILdCXoesgaQfnWyMhBRAApCmo2PzSGJbbIttsS22xba1sa2/9f9qwNHu/vp/4P4LLtcFh3Zw+0XSYG+XVRjy+MKw44Gy6poQVx8kQMnVX8m1+S7hO+9C8hyzR6lrtpRVVFjXEZP8vGFC73zBzZul54YzLY/C1Q3UBT9RPLO+VqSTiZAthc4CYxDeeOsg9vWS0gYq6yW54GhpeIzS5hZy4f/0wBbgH/hzMzok2yw2Hy4oXBtKPhx2yKdNB34qdH/2DMLfQsizHr3tSFOdV4BNUPMqqhWOSeZo6KA2bEhfDBL7pyMO9vHrBrE/EpKIMJPbXR2orC8L1NV38PMm7RzUm+8p9MQpHPByP/7ItK8ROhn4F0r7YbE/yFOO861C+oK/T79nZXb43wPpPTDk/8sz0Lc2MFziWTYXasrHax/nAxv+NmGXUVsXmIbxuwqO/ZkcOvib49RpQg9d1D6Oh7Icx3HQ7EiI8Ah58aVjoK+u2YiB6vqGgJ0XL8f5bhf6/cg7s9p9hWuufihPyx3y1B6Wp5oyZMkxT7vtsvbytJjzByZDPJBDIMflIL1d7HmqrZxtXS9O8irnCt0DjUH6a5xpeRztuUccH0x7LLag3nTtejbtW5ikt689zD5/feUsvX0/RLCvPYJ9Q3ddd/b5MXYmkG10Hdvo0l0V+9CgzqgLfvE9Mu8a8ZzaY9mWTBc6FWKuSBZsSlRs2li0xRHr4YRIdlXQCeMZYRztalftApkBeZtms0vyG9cI3W3QR5qEsD1xLsZH7202wixlSLtTpN3VMo5vt+CxYYiREeIs0N609MicBbuN3Jfff1d5CcWcV9DABOohK1FX83dT5/KU+wVfWdobHNbv4N1OEbrTdWWLdFhP5Vq0DfWC70POaIE4XqfjdyCuu3XSLPxn5o0cDa5Zi3PauCtPpXAsg9foapZ1G+1WHlTwsKFfs/JTofs18ucxLoc8pr9Wkaa9fpfX1U7DeqjYGUgffi50XkFp9zC2xajBBfDAfRDhYxx5aPfg8Uzd/VY+s6QKnQfw3IN+JIhy7UvJEPyLg0QaDUWwPCnsmUw+BxSI9DbuUlthckUWp7ItZFtxCLkivrFhfi7HA2vtTL+hs1G2a5ki3v7I0369lqIMS5F+H9iU6k3dMnWrpCRvaqY3HunTdnv7wDknevv5zMprGfHEuSZhfwdX9zfT5jV8uGimwpXm3MYwm9lIap5lUSfQLxt6ls1A2vtCNHWLaXp0PpN23Ch0RovWJIvc9k9F2HY4bzzKLBHHEjnnqaOuZMJvbnyFw8b1Ir1CY7iRFNFXtvryr1i/cNciD8KHHL3RsY9tdPgDj0869bLGx3fbMbZ+4d/sXQl8FNUdns3mIrs=
*/