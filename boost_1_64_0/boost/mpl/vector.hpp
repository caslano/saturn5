
#ifndef BOOST_MPL_VECTOR_HPP_INCLUDED
#define BOOST_MPL_VECTOR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/limits/vector.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_VECTOR_HEADER \
    BOOST_PP_CAT(vector, BOOST_MPL_LIMIT_VECTOR_SIZE).hpp \
    /**/
#else
#   define AUX778076_VECTOR_HEADER \
    BOOST_PP_CAT(vector, BOOST_MPL_LIMIT_VECTOR_SIZE)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/vector/AUX778076_VECTOR_HEADER)
#   undef AUX778076_VECTOR_HEADER
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER vector.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/vector.hpp>

#   define AUX778076_SEQUENCE_NAME vector
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_VECTOR_SIZE
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_VECTOR_HPP_INCLUDED

/* vector.hpp
azfeblC8YjLPxGiLCRrJ/GKxTpteeBtbwJnjcCjmkj4vHieP4Hwb04RxzEWGc3wEoaVsjFr2DBubzo++hRIQuHZomJx5OurKhWiIvjRfL1XvaAVagwLGmLFTx8e/ILvlWH4RVwTThRxGfFK0f8i6Bt1oDFsiWuH8BuR2Yxsjc6vjUWDaDYxg3wOWwDmu/VG1H0H4EA7/DRy2oJ7dRFYa2udNF8lfXq3jEwvSdH6PuTfFC7WbuE2YddP961v4n37z+C96cCbp8uh/7MxedTPhzMBiM8Qcb8N58ilQx7B1au6n/zVpBJ3/EMg6BbnF7R08jZLpv9YohfLYkrDzWt048EwLIrmBiwehyrPrEN+O8oIxohyGuemqoHSoGDQmLyIheSKHdU4c6Un6ObOFnh/4Ktd1fcyDJ+as62dtyaLnAYB5ICR7pihouzdeeoU9/M6rH+asW+zaV+mwYoEc0uVcspQE/kkquH1cIXwHc3gJ7D1gSjVLKxDKcT/AjZLc2EzrEN09lRmdC1UyKpN+2EXCzBrKlfGCVUzUZNG2TYavCD2PD3A70mQ6jj1GIg==
*/