/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR10_05042005_0257)
#define FUSION_VECTOR10_05042005_0257

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/vector10_fwd.hpp>
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
#include <boost/mpl/bool.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;
    struct fusion_sequence_tag;
    struct random_access_traversal_tag;

    template <typename Dummy>
    struct vector0 : sequence_base<vector0<Dummy> >
    {
        typedef mpl::vector0<> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<0> size;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector0() BOOST_NOEXCEPT {}

        template<typename Sequence>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector0(Sequence const& /*seq*/) BOOST_NOEXCEPT
        {}
    };
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector10.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector10.hpp")
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
// expand vector1 to vector10
#define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector_n.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, 10)
#include BOOST_PP_ITERATE()
#undef FUSION_HASH
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* vector10.hpp
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
*/