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
jt2wELtjMfbAF7AXvoe98a/YFz/Hfvgj9se6lGEgNsJBGIiDsQ0Owc4YgWF4A8bgUJyJIzAdR+KdOAq34Fh8CMfhozgZn8cp+AZOw3dwOp7DGLyaOpmBbTEWO+Bsrf9XeW7Ktjbp//WAXCf+iJ3wReyFL+FAfBlj8BWMw4OYiK9iOr6Oa/AQbsQ38C78M27FI/gYvol78S08gG/j8/gOvotHsQzfwwp8H3/A43KcfYiN8AT2wr/hDPwIZ+HfK/t/JZUsM/Z321TZb0kWGasvDO/FEXgfxuL9uByLZH1+h4X4IO7Dh/BNfBj/grvxJ3wM65PP49gGf49D8Qm8EZ/EHbgPi/AZKafVIs8nMcS5no7/biHlvF6dT54pYusq5gtb6d3yErycr1Dm617FfKUyX1eT+cL167FK8q1ivkiZr3UV8yV4ubxCma97FfOVrvJyPVZ7zredfj1kvq4e5guu62x/kvFWA8vmt7xvg/Lf2P7kUtueVLfdyYkOdXxqe7L79vrVbn/ia9uTcx3q/KLtT4rfalDjbVD2nLk8bVAOnrn6irdDOUj9FPL3Caz/dgNLGCmWtJK0k3SEVE4KLm1giSAlkzaTikmlpApS8Dv8GymGlE/aSiomHSGdJtV9lz6KSZGkZNJmUjHpGKmCFHyUfyOlkjaTiknHSOVH/e1i/JN/qs50peL/iXdQGgBcUvy/Erv/TZBFjRcOkvuazqQAUohFYj959qu17XcGPyhrQZP8ytioKuNULqXtuvk7Et/fPZi/I/G9rbv5OxXf31WYv+OpuXczNfVOwvwdie/vKnxt0365264fc7Rdr7ujT/8nZ3ycUjrn3r5/n5t8qHrvSKIscpxgZ5O26y2lL8bW2AyDdON7B2MwhuB1aK9jqXJ8hP+XduHV/W3uy+/y6v4m/39vE345fotf6d/hhfx30DH/713/5J/8k3/yT/7JP1V/ukL3/xlp8y+9/b/Svn8FNybFjvb9lQ3ynU3ubHmpNJ1wtu9/P0jr/4+YBibylXckA0hxSqzubK1dXPLiTHv8/LRsX9pprnJpRxjLZ78J5DPdON5WvMk5H43TjGP0tpC29aulXMtI8/hCoWu5UuyXVKaVTY1lCjNpXxCuln2+Wzm3SjnDlHnlvdAQK3/P0cpJVLXXfSEYy+mxntTtt1naxd9GCpYYvgS+YJ9j6J9BCb+db8upfhm09j4LcrIX213a+0h7U0M7Lpoh5i0mZEjr+7GZ1KsM8+top7Gd+ttQxxnLsd9RZmlj6r7OhvUeJe3yo2T/GEmaTybWOON6S4Pdaq23sf2sLEnKXUiZI+tSn/w9Ok4rt7WKcjeW9vKJsr3iSEl8qcBYbhlM43JvrzpNo1iH+pSpgxKv6MV6qOOHy3psl/W4m2RTvjRXXQ+f23Z7WgdpZyzrgI52g7aMtCybHLNyfNJ2TBe7LcvLcDtmNkgb/Vgp+3TSAspe4lL2mjvnzacEpuU32ddN210b6n6UtOnfKOVfR0pTzjnzjOWvmXMjC7F4U/fKudGs7o3tc5+XsrcmXUVqRVpI2U/qyp7L/i9XL7lwed9/xQpHvsq3jNs8WvokmCJ5jydlKJUcb8w3y1EF3rfT1NrLu657amJuqrNt4vXOPCxftjSW6ZSUKVHKFEcqYx67c/7Jxouv922Jz7uUKcpw7XWW6Q0p0zcuZSps4H7dzbJSLrcypdh9OTbOX4Zrb2MZx7+PXFt6kDpbWYcEKWvlxbea21Opp+cSzLfdZg95l7rm7eiTo/r5f6/mb+xnIU/a2f9T3ut8S7KTf2Ci5G+88MfbLN73aeC6rVJNriV2k2t/vpwftGu8tg3t9aQNv+x/jzrLaSlvKf0=
*/