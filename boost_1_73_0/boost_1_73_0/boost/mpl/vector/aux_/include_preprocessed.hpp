
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2000-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/preprocessor.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
#   define AUX778076_INCLUDE_DIR typeof_based
#elif defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
   || defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)
#   define AUX778076_INCLUDE_DIR no_ctps
#else
#   define AUX778076_INCLUDE_DIR plain
#endif

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_HEADER \
    AUX778076_INCLUDE_DIR/BOOST_MPL_PREPROCESSED_HEADER \
/**/
#else
#   define AUX778076_HEADER \
    BOOST_PP_CAT(AUX778076_INCLUDE_DIR,/)##BOOST_MPL_PREPROCESSED_HEADER \
/**/
#endif


#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING BOOST_PP_STRINGIZE(boost/mpl/vector/aux_/preprocessed/AUX778076_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include BOOST_PP_STRINGIZE(boost/mpl/vector/aux_/preprocessed/AUX778076_HEADER)
#endif

#   undef AUX778076_HEADER
#   undef AUX778076_INCLUDE_DIR

#undef BOOST_MPL_PREPROCESSED_HEADER

/* include_preprocessed.hpp
2qd76huDnd+bZvmQ9LrS772HC3Pw5pn3YZbPoheFW2c+2HnRKlmZs8Ny4SaeUcnWsODR3fsfbOcYs8pyXt57vWm6NBrSOVTN1fxdOHOZemaQOkZjv5pXk1Wn/OYZ1QjPg7IfdXU8b6T9WP8U/tJsItV2XdRO5YbEkvpYUhajNaYhCcCcL81b2smR3KpOSKH+ZJWfD85etZSEJeZ5dUtBVowjctw78A+4kFHS0bcvVn7POVNOEBbIZyAlTo9a9hTKaUwlxSHiRCQsFgQgtSMmsnwWRTgOjqx3mlZ8HI4n/dFdMaMbDd2JdtvQkZqiFPQgVWUYBBiqRzCHcdR9bZTuq2u1Uio//XmGvMAiVCkH/WdkeD21mDc/I5yuDyjAEiO8loAC7qHs1KINyPcIiVFBbJgsKNYur23BqlodqagzdR371Rn2+oPXB3vQtx8Ui3DOuM8C6KZWB64v44xtAthRGkoKLgDXGvskcyiznguEkcfZNiPsDAcDuzMpZA5ilHASYQmGhodTBUBJjmOxBr3QFRKpv4FCgIqJf7I6DFHMJPpNJGQKL9P+BFpIOJPMZ2FL6bRH7at/PgNU9GqVn/ENbmYO3xT18oYJ2Swb9ZIOVxkmEsZl87whMJHtQfP+v1sAWbh/AWYRuOCIXoEn
*/