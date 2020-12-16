#ifndef BOOST_PP_IS_ITERATING
/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VECTOR40_FWD_HPP_INCLUDED)
#define BOOST_FUSION_VECTOR40_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector40_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector40_fwd.hpp")
#endif

/*=============================================================================
    Copyright (c) 2011 Eric Niebler
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
    // expand vector31 to vector40
    #define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector40_fwd.hpp>
    #define BOOST_PP_ITERATION_LIMITS (31, 40)
    #include BOOST_PP_ITERATE()
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

#else

    template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename T)>
    struct BOOST_PP_CAT(vector, BOOST_PP_ITERATION());

#endif

/* vector40_fwd.hpp
C6h/G9fTIm3tN8n+uJ7UlfWMni/r6Xqhr+ZxopQ/yu1ab9zmu6Usr8l590+k7lb+L0nKYrx4X9KxUdW1u4nsL1KvhuNiorTxT5dyppAukIclWcopFwhf+idwPc9FmVybo43XB8d2TXLkyX7qcvyUm5TxLPMUupbRx3OfWTm1a7Dncn4n5TznUs590rZ/g5TzFlIO29xqcymnj+fDTy/heuvLOXKU9BdgV+aV+v6MvEv15acJpi9l166xructyiTH978dyyeW2uV4PnGN+/3SYuozIcXwTnrc5HExjtOnN/01tJIy5Jr0Lb/cuVzLtYHOv9epfxu3c0ag9Okh78ojSEtYXpFJuagur/ZHq5RJXy97Jf98Pqeve+fflKOOnGvGSHlipE1+mpz3kknLlQUucC9Prk3tdk86+an6eJG+YdzqzHgeVBfn6KPBqp5vqIHKf5L16rnA0Ic/f0sf/vLvExcY653YAV4Jen6nbf5u2ffxAs3fyfv+btn8HbKnd+a+v5M3j33w9I7a9/aY5jERvscg+BoT4WssQIN85fPe67dEPbQ2us+wzKg193co3eY5RsDZPkSeV+FgUqBL+5CH5d38LuyMu3EAPopquzH5/mr5vr7d2D3y/XsxDH+LMbhDF++djg/gYizCZfg7lPLJ8yA0Kd8dFmkvgSG4Bbvr2i/ZlSTfv02+3wiT5fvLJeZgJXbE1dgDb8IxWMD/onANzsJbMA/X4wrcgAW4EdfiJsk32iLPUzBK8r0aR0m+86VekrAdJmMHtGEnXID9MRVH4kLdcgtkuYkmy82S9cmW9bHjIFyE12OurE8exuESdLZLkecPsF2Wq2+X0kuWGyblG4BDcJCULxwX4PWyPSOkPm7AO3AY3o2RuvUokfxiTdYjRvKLle05W/KZg+MxDqfiXJyO89T9Ue7lcaPJ/jhalhuFA3Ac3ojjcS5OxCU4CQtwMq7DKer+KPfb2Npkf+zCfFdhKDbFrtgKu6HExsh9M8uU7+tjY36li4UJwWuxJ16HEdhW1r+dbnl2WV6iyfKG1WJ5GIntcDiOxBE4FkdjHI5BqT/uVz0fz31kef0xDAdgDA7EWAzHdLweF+NgXIZDtPZIco/JsmT5+vZIB+V4fhXb4GsYjK9jDzyEarumiyznsCzniCznTVnOW7Kct9X2jXLfJ/eDgcb2jbTbklgk7IptcRK2k/Vuj5nYUda3k6xvFyzCUPwIu+JZ7IZfYQ+pj55igkXuy3CTlEM/Psc/ZL+4gO3wnzgSK3As/gun4I+Yiz/hUrSw/PUKKOdDueeibk3Oh3Wl/d9VOAAb4Q3YGEdhE5yI16Adm2IeNsft2AJfwpb4J2yF6n4v9wnpJvvpu7J9jmJHPIZR+B5OxOOYgh+gGmN2keWdleWdk+V9Jcs7L8v7Rpb3rXrekPsS3GCy3/9NlncSB+DHeCN+gnPxFC7Gz/Am/BxvwS/U8VfkvgHtJtt3n+yvz2Ib3C/lPoAD8Y84FJ/H+fiClL8E0/FPuvNTQorn6+VCae+XjlbMwO6YqdtORfL94Sb1Oknai07G6zAaO+FUHITTMAKno3pdkd+vaSbXlRvlfDJbyhOHoTgXw3EeRmI8jsL5OA2TMB5tmIwpGMGyiQW8aLxgxHvE+2P/HubxgOWoxP5ZSf1JZnF+UTlafF9srjYWtBbDp8Xu7UaJ2XOL1wslxZC0tjOG2Dzi8pzxeD1IWgyecXzpYyRi7SSuruq2LhJTp4ulM45LnUdS4ubWoj4+7hjJ0k8f/2YcC0Xi3oh5c491CyJpcW0S02Yy1rUWs6bFqhWQCpW/2W4rSdtJxaRSUhkpkB/5oaRRpATSBtJu0iHSKZLlLw0=
*/