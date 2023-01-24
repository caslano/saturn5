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
EzaY924z8PaQsdxV1exYlmU1MZZVYWPJ18ayqtFYVjU1luQLGsu7MU2O5dcCPT8Mt/dBENsXt2kDKaLkJmR80V0GdmQ2NkZjoGBMTYtKlD+3XlAm7iR7MfkmjL6BFD+MJyuRNPp3Ekij7B3PWwXvul9NMW6WdqEYNyh/9yKB+QvEb3Q6yOyWL0sNkbsxfq6cW4L+ySRniuioHZyeU8EIeWdkFSt9MyuUr2R9hYENEnPkvc7KCBOdcPHb20cSLBRUf55GHj8erDnSTLzcYjBQW1XHy4NDbIeNrdBFsALJLUKy1Baj7ZDozm0TSWocy5//TqH7PxNhcUJj3RKTi9qqM7kcuU7wOQpKKbIvdB5sTC5QS8kFKBeMlVs2RESOn8EVHFAlB5gUHBowJnXY5R/dgEr2bqnrx6509uU0zvp3ZC8D9ukiaxvoSKlvxPJURmBwa6fNRAce5w1oR9BOx4EaPDe3JZC5zW0DYxt6qjNGNIuS0oAOCGgCugB2Fv3BEXOaUkalMBtiAr30gYGNFbbzSrkyqmsZgTOsC2IOSGdlE2SGEeUlaHNTfhAZeG4xBNV4aDrwXz3nhNFFKce3sMDln1DE0yDHS5AAGT/I7INspSyDH+5qgRcN+Sl9KT8HweXLd3IdLFVTjYRBG3d7Y3vhTo0vfxhNuLaGcK1AC/PJsGrVJLIYrpxEyPYAQzbuU3RkHOLdvClGvBvNiduK
*/