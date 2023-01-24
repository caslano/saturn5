
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS_HPP_

#include <boost/local_function/aux_/preprocessor/traits/bind.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/list/transform.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_APPLY_( \
        d, bind_macro, bind_traits) \
    bind_macro(bind_traits)

// PUBLIC //

// Expand: pp-list of const bind-traits.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_CONST_BINDS, \
            decl_traits)

// Expand: pp-list of const bind-this-traits (size <= 1 after validation).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM( \
          BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX \
        , BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_CONST_BIND_THIS_TYPES \
        , decl_traits \
    )

#endif // #include guard


/* decl_const_binds.hpp
w7tLbBYLX3ESX1TT9xwhcscHKlR2SApWlEhMcJmSVd8xbDBZ/NfKK5HJbL0GMn/r/h51EsI3zF5kuA139de9alWI+03XxGlBOMznNYUB17tw03TJfQGkuSuLDaOFOO7N7gokmQVd6KBtEmV8hOTLT3SVXOvBlSK06Njjk0jqkmcGa3bE4AQ7BrUofQlsNrpSmpMoox/KkmPfVwW2Stn8qbyLetnKK4X7jZx7EeWGDFQxRfmq8CvJrTX4iMO3HZkZKSk6OfpF8WgJN2KaLpiXdhJbO4eQbTgxsGoLuFg1WzWbXsdpjFEiNSg16O3OHXsT03qtXiz8zl1A7mo1J+d7d43uRMfl/GVveaw+S0FVpvCDbdc508yq1xCNLMyb7uFDKyBuMtEr9cHD6ZzTT/os26zR4fyzdrBXLhHmmVDxp9V2eT35rsnnOIdzjlxs1pfY93fCEI9NcEQX/arXFE+IV+z3m+fp8kk/mKnK92qVjqx6o/h76a+a+nbFCmeddOvWbtp/6x3Vp/jZaODGn4/0Z+wVXtqZ7/KrvybmPOzwdO1TVr4nF6UHT+F7lUK/PnY6BKj+ViUskBN+J9AmYocxtDaGOTfh/S3aGX5kSkaYde+M/+ihuiDn/O+Provq7YQELsM0vzRopEGnVJKv891g4Sjp2AJox75fB10aepmfqDx9kzkVDrYngY95ZuTLinbE53xE3OWJqSJ4mreN
*/