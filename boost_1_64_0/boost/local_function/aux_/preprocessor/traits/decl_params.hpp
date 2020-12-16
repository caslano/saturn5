
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/local_function/aux_/preprocessor/traits/param.hpp>
#include <boost/local_function/detail/preprocessor/keyword/default.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/list/fold_left.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS_DEFAULT_OP_(s, \
        default_count, param_traits) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
            BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_DEFAULT(param_traits)), \
        BOOST_PP_TUPLE_REM(1) \
    , \
        BOOST_PP_INC \
    )(default_count)

// Precondition: params is a pp-list which is not nil.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS_DEFAULT_COUNT_(params) \
    BOOST_PP_LIST_FOLD_LEFT( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS_DEFAULT_OP_, \
            0 /* start with defaults_count to 0 */, params)

// PUBLIC //

// Expand: pp-list of param-traits (no bound variables).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_PARAMS, decl_traits)

// Expand: number of parameters with default values (0 if no default).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS_DEFAULT_COUNT( \
        decl_traits) \
    BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits)), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS_DEFAULT_COUNT_ \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    )(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits))

#endif // #include guard


/* decl_params.hpp
WtrNzNknlotqqIfZXjzHuvV9gcR1hD2GVnIKP2ubTh4cKpu3geQHyya2SCKiZZ8B9wkzZ56s1+FHKKPaM0D4Wb9v84b4ArugGNGjnMjAvrBNxurymhDbGJkvVjd08hE/sB+Td7quPzXD6uYz3crvEG0flwEepfwnddjHWdrYWGu5kA95Dwb3ceZ70DxrpmlIkK5H3oPNAWWlXoK23/dvqbCZ6hvS/KYIQ19jrbPcYT6PsyTAXNE5GSebcpwwy6p1Cn4HWspvjIozWFeH8NPqocy62U/576KtU4mrxkIrhlAnQxnDe/uUrhOS2QDczPs66VdC9crh9S2p4K4qrX3Q0fTq8ByKSPRe+4nNW6uU9zxhdJ7YxizxlbcynHSGmOrp7X8+UnEmG2LbI3mF+nuxYzsZ79lIuV77QASP9crqK5KaUtypYu9XLDaGx9YEnmlUIYq7gcJwW2m/rlNUPjTGhOa7TOnDe7W/R9JYfzsdJenR1XMRVwIMknKrl/TsjBcN0R1WIu8H0I3q+z0JMys+2Y0QmcIeJ/uf4wqRazsJMFDkavLJhVDK1mnWCZ62tIYzRu0exh5R1v7fyGlLx2FJp6UtHTfWtDWa/t86d2E+b60qXqZ/DoZ+Q+Yrwpyn8O+l4xa5/BF6+nXmp4pcpqFo23Na0De8uve3tXU5Qfv1SN7zrWkE1rn6/qgg3gqo0dtX9LSmH349Sz/JxsAy/yUBDhUZXKYMykrVumBYybCe9McQ9yavDEnDTBk+seurwtjjB7lMG9qCnX0eJ0uAWmgn6rupTS5r723bd3eZY9t3w6v9vvu3U+37buKafffZlEPRTuxPqeojIzm2V1udrJXy8IdbSrhbVB9fGNDHf0g45KAvV3mosI55v1RpdTfPDvlJuUfSN6Up3r7nL/J3wuuKz1Fe3U2nvhP87TstV/bptvTTe3DPNcdfh1J96qPJWTbT43sfDFJlUKqrM4nrsISbpqsfwoX37ef/joYXeShV7gTTPS0gP+slP3tBXaA8aDfuebT5UcXdYX58cR1afUkf8GTlv7MRS+8ebHfnFeok5d+nw74tOJ/WZ+333XwBD3cgJziOfzsQrsmXrzb7jBNLK08orw44T6LM0p5eUuFTHeuNAfrnTfLaFr9mtseiO2xW/vNpJ/tgMx+jrVfhEaqPFR4fKP+78K/S6hmIr9fhSfyv8MfX1Ee5T/O6x+v0EPDS6/QyhVer8u/l6MFX0ROUyQYk0Ogo4KPV7Zl5ilcyrOcd9JYp16/c89uOZFj4ZVj46Ww70sEDVdznKOlY4+5A2w7zrI5sFeZL2nkceY1X9h3NGhsPwqv0V6o0RznG8t8FJTiYn3B0rMOyOMaG9jO0rxC9Cm1G7iVrdHkpGl1emkaXl6HT5cnzkLK7oa59IAe0NzTE+5yfrp4H6VCVLQWnuMy0PONuXbuXeA6tjuNk5beLeqcawykjSOkVumeG6DPadBXh9fP+Nn2WSqNXe33E2NA+wh3wnfq7lEkXyI/DCNfkK5PKCqdvWcv4g8cd5CwYOXGkfLYRLPi9pu8bpIwsZal//iWcdWxk38dnWdoUqPKlZAjq590BY5nFe4TmdVfCNdvlVX0ihZfP5iD5P9lE+a1107BnqLz7EHaNnbx8xVWXV9WEWzdrgtqvvm6s4eSbZhPz1sP8rgitm3l5oXndi7gttnnlWETJ53CVz4rps7T5FB7Sb+6pwpZJWM2ah6C8ro0gr8NVXpHD0rftqe6RXlDd1uylf+6MM+zyS1/PqrQTw2yPxhnhPXcSrq1PiiC/HTx3sr+P3d6Zke/BGeken1epfWqm5dx39burVwxe8OGUO0cfnvBz5+3Bqd/7M7o=
*/