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
2LSeM1NLGK0+NAmTRPdSJa6Si/usTJfmnTlBRuo+m8kylaFcep0FzV8YOVWOXwDZ5H3IPk66R0qLz2rHvrvo2Hfg0igTpMzYy/SGnNCUGWBRdV9DR6oPRepHql/QuW9tt2hKzQz1kIr1bF88aIEZFOcScl/9lCJRuaaPRezT167V8ic+d61mwX1E/Jmh+NifeFnSOO4ifgYeE0kCWhFwLLZ7W4rEETb+lttnYwX1g5foQ8AKt+HVaqkm8J4gWQ/sZUWM0KqOyXncghC4CQ5fGEKQjhSpOTdj6iLoy/08zEwF1/C5MiUsjrzHRRGmxnYAOn/AV35HzRfAd/i5pBOLo9lB3OXACSiBXGJ+R+ZGEYrnymst6HTJBsHKxssSLXhR0wtepORWaAu+YZgIC9HDSQf9RYq3Ny34brMeEwIXvEj59rJoyi6LljNcuTf7hC14hvJkH+OCZ6Ro67kxWVvwt8SfRcoLyRpGrEy2CLumZTikaM7CJc6Hrft1rtEgE6s6duZaw+aHbPpigrU7lxXGbxWh31YYv60wfuPoE8c3Ln/Ld+UK492Qlqqjb65VD7SEw/60NyT2tGQKzMoPOSvYpR25MCr4Whu6rEkWs3Ne1qy9nQS5av6cNpOek++m5xj+ezh/DuXPgfyZfrdBz7MZ48G6apqV9e/I4fJfbMoBHjMuaCFZt1x1S/YN92P6eh/GO+mTcyFC4IbWIrOv
*/