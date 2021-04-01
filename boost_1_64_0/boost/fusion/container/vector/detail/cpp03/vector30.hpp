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
Ctc/ylGCZc50aq8JJrl5svX6rqCuXTrHvp/z8UWPXBtDdp7PjrYe2a/Eh6p5fy/46OYVwcd/gBgcOvl56SRRZhj7VwzOuFpTwfooooJrzSMS257jS7ChjzEz6X7nNn6k7ETbswSfj+uZUfS13I/DjHD/LN/Pt72gVXv1GXbBC3IqR/Qfz5IlKsYoKM5gbs3LzTI+HeDh0bf7YC61xnuCs+r15/tlm9du1sl4/ReHdaong3TFp3S04/Yz44iyy3Hcs9LceMWvbg1sWgsEEAFmv5OObS1QpBaYS7HNf808NV5nKI/jJdYaExpG+QaGoP5XcQDMXdjHlGxCpTdeTMx+xhHnT2NnniEGu65pKbkn/5Dl8T8F0HPTRyC7jABlcPhztTRNvF3OO/gPxweIJUrKkAuV3VRsAkrDnGZq7KzgyoeUpWP19f1q7b6K/5P0FJI22QOgVoFSr+nZbjqDlvjtmoT1Tkp6Zz16dDwwLo7u2+Dvywui4SCI+Wsz/zhOp+AN5Y2bLiK5C8I9Btq8hCuFZMTaL0PW6e4YpU79u3fhnXrEk7vxT+lc5o41Ow==
*/