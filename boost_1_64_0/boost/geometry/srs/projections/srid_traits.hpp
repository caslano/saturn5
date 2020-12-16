// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_SRID_TRAITS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_SRID_TRAITS_HPP


#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_SRID_TRAITS_BEG(AUTH, CODE) \
template<> \
struct AUTH##_traits<CODE> \
{ \
    typedef \

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_SRID_TRAITS_MID() \
    parameters_type; \
    static inline parameters_type parameters() \
    { \
        return parameters_type \

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_SRID_TRAITS_END() \
        ; \
    } \
}; \


#endif // BOOST_GEOMETRY_PROJECTIONS_SRID_TRAITS_HPP


/* srid_traits.hpp
6CHaLcd8rNUSb7rEZehaa8NAWqeL/dsCEStkGCAyRg1iQn3nGCdJPR+3uq6q7R5ijBU2Kyqbifv7q/sW2Fr0kLvjGfbCpezt2gH9Vdl7mtqmbpXgc1dgWyPW6W1V5XFzLtMTicyEoyViIC7TIaPNhRx1i7xt/mglw2OY/HF1v726PcroKllh57jKEpFWmQUmn7wb88nDgXO4mzFUmqG2oUfi9UTG60mK1zrotxjUT8Dzk5mtcUFfU+fF1lOUzk9V9JdEpZ87MYFHw4J/ZS5PTcZL2YL2+4OAxRQML4NZui+0aliiXMpblTlpjfQftyNoHjPg0WYJD3JoLbA14mZZOHwd0ClhccxqVK43IsKvurUtKjvkgcu5RNPsjyQzaTtX0lhexwGNY5QC9yjIOBmRmWDV6AoaZ9A9FnQzEaEzrKNkEPY/rGFxBMYV/HEoeyTironk8MvgRyNiATR+SCKkno8H/Gohr/AylNWwYxFkQTLY0wC7LoL1KKrj49VxAcN0OW1nLC3XCQEDrS5XAOxkpOBMxdMpmEVEUyeRN0ntfGOkaCPRC3llbluRfqciGbybbrnr3/PQsY6wse5mqTsbPqRHi/7eBryw53pEmfgzfvuMRzoHrzI5eyDgK/rJlayfPIv6c+C6V+ypuvuGenuGafVrwNUa+NmKX/WxWb7eDpPGxWxAWptQ8Bqr0/OL1gttLoZui88x2YRTgmboLXotLHDPEH2T4fg6cCvWTo7ggzbkNM8EzQMZjtOMWg4KY7DRBMBpmgMaZ1V85LA120c07ogHZ5EuR61cvoRVmFPOJsYytqX3D1dbBdsuVspdg2do5U6ueu9wTMLczsL3Xtdaqp8ItpmKn77bYn7Kyl9nqUWuVYHd4MIsssVxS7zNA4YOhnJlu6sgwwlLehn40Rr0pIJBXbfcUZS7UcEcVcdzADtlqaZXsAcDdrOFSqYter7FyolOTDa+Vcx1YkKZzDulXAIi0vgD51Y4O1nIw/jj+SISXzJp+KtsQDb+NfqWtYhfjMpkMmnk2ySTZWzBqvNr9S1rUZk2XQboKSZ3O4eDM7fleo5Dkuu4LdrF61tbMdYVsNkWuTq8zToj7hRD41qvGo/EGgL1Rp/LxqOhiH7llS2eGEjPt1XXHyHXbWIMej4bg17A1qIvNNYlL4rhMtaiV6s5+sWqrN4/3T2mxgo9Ruh9n0zkz5eQFwSPZ/smBkfqUhm21LiYNXaIgKwdVnpoqL8QvtXKYNxxEe46BuaOvpTZt81SnxLR9qFHsk1LBOUKal1Sp76q9nKl8yuUztXtz9KNNX8G0nWIueQatZbEIOrTlizhmXgxEOP1as2r0TtPRY15q954bsTzTt99tK4IGc0VbWYh+Jr2DfoMJ+rxB4t8QZ4bJCbxL5/74Qd6z0t9Jib8poh3q+AwtH8WsIMVGGyI9i7CuNKnXoXnrdZBen6NeK4vQtxK39/aJD9mwevqlDAaTTR8R9NBVChpXwtevU3u+UVc7OyzmEA4j34DJ3hp/OtAO9QkXmDGumzKrko/YuCJByuzv8nOFkqHtP113yA7jjYdRF43DmbylbnmgIZhwuJlUxIOXrJsO2ScVDAY0IW9HrBCk9tmOPAoi/mK4DNN8qyHEEzOw0045xhPo1GVqFYF92RlJyG87rfHwO9IU8rtU+fCbd/I+uvRpmpuyGFznguIwVgTEoD77ZuV3+q+/5aYt++/VfX9t4U7o5zOY74VlXkgan12Le0/ZR95h+wjU/pMDPVH38nPZ2tYs+n1pB7L322M5e+J4TLG8vcq3d4XdK6BMXMCPUHXTU+oc2fQOQjKoX34ucwsBG+HD1TaAfeV+ekGo30+qHS4PiY=
*/