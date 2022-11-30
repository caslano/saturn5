/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR30_05052005_0206)
#define FUSION_VECTOR30_05052005_0206

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/vector30_fwd.hpp>
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
#include <boost/mpl/vector/vector30.hpp>
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
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector30.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector30.hpp")
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
// expand vector21 to vector30
#define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector_n.hpp>
#define BOOST_PP_ITERATION_LIMITS (21, 30)
#include BOOST_PP_ITERATE()
#undef FUSION_HASH
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif


/* vector30.hpp
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
*/