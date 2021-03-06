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
/78hhxMuNWugDqZill3GkqZV+Q7mTe4fo8PAkrAllK6DBK8uzE9l1A2qDSICLuvgTo8EEXmMbNW1cZY7KVbVk49++H0mEfpZv5hDiEd52p0OEX/F++mVxPA1FcKJFucIHO5j9v6a+/SA0HYWuay4JUGYhmNCGQM8PQgBFuj27ZDnsnPE9jHMDALPTSBlELPmhrOPVT1g2dm+pNRVpwK/Awf5CDYWyVGK3bxXI7HpwP6BaMe9fT+pIfXgRz1VKFUBgXpqHNtVpmjzgZB5ZjlBRPYMMC7m2EyM3EEZtengbiM8OnysD0Osn27arERfMVOAjY8HJBWz5QJMZRvnWTdz6XfgKVFfyx52HoX0AsgSZZdlRhklT6fDrqZAey5ehkVLP0OBsXqF5VOx2OZ/yR3sr1vcML63r4dJx8HMP/kXPwOUsKbzeMgz1Zs3JP9KUnmXf0CMqVc/sOwz28RzW4FuxeN9zhEUXD72qvS2UBGNeRQOzc1yJoLzHUir/4r8Aag46DAD35d2l4RHS0TRIpwMx7wwOAqxj9xpqSIF54GL9JtM3+HbmkKNqdX1/Q==
*/