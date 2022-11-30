/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR40_05052005_0208)
#define FUSION_VECTOR40_05052005_0208

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/vector40_fwd.hpp>
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
#include <boost/mpl/vector/vector40.hpp>
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
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector40.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector40.hpp")
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
// expand vector31 to vector40
#define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector_n.hpp>
#define BOOST_PP_ITERATION_LIMITS (31, 40)
#include BOOST_PP_ITERATE()
#undef FUSION_HASH
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif


/* vector40.hpp
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
*/