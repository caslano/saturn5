/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR50_05052005_0207)
#define FUSION_VECTOR50_05052005_0207

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/vector50_fwd.hpp>
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
#include <boost/mpl/vector/vector50.hpp>
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
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector50.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector50.hpp")
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
// expand vector41 to vector50
#define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector_n.hpp>
#define BOOST_PP_ITERATION_LIMITS (41, 50)
#include BOOST_PP_ITERATE()
#undef FUSION_HASH
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif


/* vector50.hpp
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
*/