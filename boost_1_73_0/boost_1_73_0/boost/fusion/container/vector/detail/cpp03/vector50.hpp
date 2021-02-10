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
5jBzNdxjUpzwVzMLOY2bxmriP+synhxTqJ+lCDOfhzOqwWcuQRBUdvka52synxq2Gmeh6rWfL8Wz+ldmTK11IHmJKJURVAVBWWDtJmRAz7KjZ+Nms0neZQd8Kgek2h3HhIDaMO1KyeWGDp3qb14Z8yPvLsybonlfs7sfteF264NVAR8aiTLiH+rKVnZT3WEWvXeNvbIfqKuQrT3Bzd5hucdK++XvCkKZ+9WasTGwJZzB0WFGN08qxvBuPZ6ok9nBcizPdINiBUYAU8lKlFShMemSOsltwWGeCrV53oDJURzo19TQQJQ6+Fvz4PLwzozUE0DUCAveP3Q8PJjbyj+Iyring894r8DFye9dlyiqZ06F2bWRTnuzPAN372IQtM4BSU4/a/bdNgZ9/3yx4Ynaslpwjj2KOn1fs9oL5J06gLB0kzLTcOsd3/nxDubZOj9/1zox5YrtFckLbT0oXPonY3sDXcOp2AXAsPWGo8kK+lrpjl9N4a6hWAPInEX2umA/Mc7payU2cPTw4kZdi/DQkVG3hvlifsATd2vtTlWU5Kq6p6V0VZ4sOjlUopu5UoVtSJFzv2HThcwnDvzSYYxanbXukVVXzlXmWNgQuVJQpo9mmcw1POIk3hvOyBNyzaOpXHvS3+Bb+tJoDTag
*/