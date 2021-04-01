
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2001-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/preprocessor.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_HEADER \
    plain/BOOST_MPL_PREPROCESSED_HEADER \
/**/
#else
#   define AUX778076_HEADER \
    BOOST_PP_CAT(plain,/)##BOOST_MPL_PREPROCESSED_HEADER \
/**/
#endif

#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING BOOST_PP_STRINGIZE(boost/mpl/set/aux_/preprocessed/AUX778076_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include BOOST_PP_STRINGIZE(boost/mpl/set/aux_/preprocessed/AUX778076_HEADER)
#endif

#   undef AUX778076_HEADER

#undef BOOST_MPL_PREPROCESSED_HEADER

/* include_preprocessed.hpp
3gkK4zQTbQe0ntBgUXQf/DW8MNRkpTshXPm4b0PdHbl/Latlvmml4Ig4sChpPDG6h3lXu0ZiCAenAMgxusXrjr6Z8/gzzaFOa6vKAJiQHS8G0DUqWQVSSenTJg4RgLqgEdDI1dGqF8um9zi9RDCTD1lq+uAGz8Ul+NQ9PR1VRD3CdRzVx1PkhYBPxi+6SMxoNvx0z2JvoXufnsXrDdsY0MnrG2jfmRxjM5aIE+RaUEni7R0cWjmQ3Yp81UV9hb4D/jRpBEjP54IgZMDwgYivFRcqUUV48c4DqEz3b9mP4/qHMw0ufFGxdHJoF3m0OqFclzz+w+aptYhKR4MpCxtzmYlWlt3xVKu5xhBNk59xVw6M4d0C5a0JITrZS6j0eLd+L1T41vl3UGQL1kVhlZLWGssuQcqKnVpMAcDO3EGL+ixDLTxx1yyndzh8M1c93TSG5cwXSsHv1qHuw+/2AfEqBtTLaNJKEjJzu9qeQxUmINBEXWW84nCPEjDYH2Eu28Xs4ZKmc216wyGEy+CukpzJ7WI+uEbKW6Ki8RA/k0Wt+JhG+oXx3jov39CYXg==
*/