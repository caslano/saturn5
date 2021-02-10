/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR20_05052005_0205)
#define FUSION_VECTOR20_05052005_0205

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/vector20_fwd.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/container/vector/detail/at_impl.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>
#include <boost/fusion/container/vector/detail/begin_impl.hpp>
#include <boost/fusion/container/vector/detail/end_impl.hpp>

#include <boost/mpl/void.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector/vector20.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector20.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector20.hpp")
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
    struct vector_tag;
    struct fusion_sequence_tag;
    struct random_access_traversal_tag;

#define FUSION_HASH #
// expand vector11 to vector20
#define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector_n.hpp>
#define BOOST_PP_ITERATION_LIMITS (11, 20)
#include BOOST_PP_ITERATE()
#undef FUSION_HASH
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif


/* vector20.hpp
1tR4iHV6tvgvZqJ5ljbCbSQAJsm/HK3+Kvi11x+geKtn4JIIkjA3qxgao65Ncq07pTDLbteJ4PjDoe24wIbDFIRKGEOy1+eEMkKsXMHL1Yt72Vq7qJcrF1U9u/UremDqBdOKJ1AuY85zMJuJ1STxJKAo7y0ndny9wxTb0KHI6OL0Z+s2aEjYg7vQK8FPj+gY8Rd3xEFfG1i6ni0Tu61tVL546gqoBEstfeJky2xbT3dXZTSRnUrFwNPO8coo/h9JPsKC3kvj6+KCKBvVfjGMKMSwLXVY1fHI1MeiOrwrIkz0AS5l6tymsUuRZ7tc98CZmBtxSPKvM+AT7VBPloYfd8ry8WrgxWesL+KpL/9mOvvDhOeg6c/C2gbtrHMX00z8so6M/VzXUTtkj1UyJkF9rGr7iUoFwhXKLCE78yW6oTdB0homxKYLzuN6wVMFUr1qlOl4Y0xMpCDHqa7uxtUftXCXgXg2pml+84p+RllgYIShh1hQP9PxqkoiQFHQNOJA1Q0j6ZR7eboN87tcqE+Q1CrxaJ2s5tWOpDosWm3RpobV1SF1crRu5NU8iwgtT9vvrt63+v325cBBxTceKqI6Y7/7pXSu18sIzsZrKhSHUvu9rfd3m6SzsbiJ5C0ykiEoebYY5UP05MiMxeg4
*/