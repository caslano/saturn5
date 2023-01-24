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
YKgx7+lwY56ITePnABJf2kf7CUFJNxmHXK1eya10USay0q0iKx3TK2YLvULoalePJjZ2OXuyRyd6tKNHAj1ajCYWZ+bP1ePp+QR/BkbR83v+XMzfz+XP3aOQH864NfxsTaer89ZpdJUm4W+hD1YwklqB9/TTrMTVkaQeRC0WSepJNDprSKP7zNbypa6LMNDcPEopAQGCVMetacZ1AwzK7laCDhvGEJ+XRNBS55OZ9L4hmL0YK4hJo6UpJqc67ZgD2y02tptKcQrBkqw6fkzV/PAIJJWjdlYEif3IxlilO7L9luhAC1N2zx32DbYh9g1xJmfP3foR31H23w1S2rOwXT2tmWxQQ5oc1GXGbi8rFUOjzVGyWWwOhQ0xWEht3Kc024a9/F+oJe3ZitB28DTnFdwJyypC20nQ2lkGh59eJnbFe6Zq++BWWDGta9ppwi0aVEHY1i3F9cBJyjbTYUSpce+Uhu6dIs19ocjgAsmmPr9vmNdl774hSwiS+9F/VZUfkmMcxi/hN40Zj9t5+o89oOw/RE/5H03w+OV6ruMw/Dh6/XkIA27jEqOAIowDnDawbXzDGYtxG4en/LhjJG2zSfwZcQuPUzCWx/8dSbk/xuKjP/36hn+8mn7u5T878Tq2jtX3qmZnArPN/rUhLiy4ReuM7lX1fc6RrK6UK4epkj9+/m62zI7x6WThKZmF4pjq+LBPqHfG030ohtZX
*/