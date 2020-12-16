/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR20_05052005_0205)
#define FUSION_VECTOR20_05052005_0205

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/vector20_fwd.hpp>
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
#include <boost/mpl/vector/vector20.hpp>
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
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector20.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector20.hpp")
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
// expand vector11 to vector20
#define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector_n.hpp>
#define BOOST_PP_ITERATION_LIMITS (11, 20)
#include BOOST_PP_ITERATE()
#undef FUSION_HASH
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif


/* vector20.hpp
5vpvMo9HC/z+3pAFrvi4L/fFvdf+bMOZpRu3LV3zJgEO7rgpOVfKOfQMSR83dZfEcdyN7XEVxuE9OBjX4G24FvPxXnRiOS7GB/BxXIe7cAPuw4fwKG7EP+Am/BM+jCGU4RFsiI9hO9yC3fFx7ItbcQDuwCG4U+tnRM57fE5N+hlJYDkrDsbOOAR74VCMxxE4DEdiDiZiIY7DlZiMe3A8PoMpWIGT8Bc4GT/BKViJU/FG8p6GoTgdb8WZsj23Yx+04TRMQxvOwvmYgcswCzdgNm7G2ViBOfg6zsXjmId/wXz8GAvQIuPiheA8DEcHdkYnRuF87IULcRQuwhRcjJNxiT7u5X6pXzle9HEvt0rcUXPsgBHYHX+EsdgKh6IVR2FbTMd2WIrtsQw74NPYEfdjZ3xDN+5cFF7ErvgF9sAWlKUntsde2BF7Ywz2wX4Yh+OxL07Gfri5jiXYF0ewL45gXxw/oL44LnPv3Po6cR+vB++hB6fgdK2na3v9r5CXO6sGxv5Trv876dr/r6yljbUeQdpIOmElLXNf/0+Ympwyzkbrt4x8eyDtA9+2uq+VbOly/aSfN4t5hn6Xtb7Z62vXWa7XFvWaucT1Opy/f+1azyzX61D1dbrhmv6cbBeoUxixCVtL2S4WTx4+duLEJFuGvZgLbob7KrZX385X36Z3s7TrnyD1NoZ0knLsM64/M9eP8Q+bGtp1ciXvSJ/N26TevNvGJ2jtDHMLmKe07b/gztcSerP79Zfy+uYWcq/Dox38c/xnG9yKSsyGdbmh3Az2llU0PzdDbUeXht5TrTubyDjsVhxbq7a6D39qVV7nkEeDxu/x96mDSkyJzXT9TWQ/zqvHe3TtlJnF+5mn9tVdp/FW6r28jrudTpJSZnl/ONZxvT+/MFP2lVIPY2WZ963uepkjr0/L64fk9c/l9TZ5/Ud5fVJefyiv/yivR7Zwv85eYfz/p+T1Oaux3utLu+o21H+c+GeWSbjTUO+OnMIF2enOdLUt5onaV653fkpLvTdw38ta5VqfvGZSXktb1hfvct8rSRrbs49F5u3U5vWumleuzYupmrdEm9eral6ONq9n1X4spzwcr5QpO98pn/1IdxtV5qXb1b7V1f2Vox7nw6vep7sX+BfXccQNGtn/4dTbzuu4n6N8Bt11J/d95FjRjc8Rhk5lnjaugbqOUPL+OW+OWKmtw4ptq5a3Rcv5p2pertrOf149KecC92c3XM1nblaWfXYhJ1xDXk6WL1Gude8mL/X+k7r9w+dzay+J26PK8mHMs5OUNkMFd2tlS1Xrx57vmO3aFvUYv0Pq4WM5BtfJ60/k9T/l9d/l9aOyzZ/K65mSzz/l9bPy+kt5/bK8/kpeH5XXhbe6X38ory9bjWNolssxX9+N5XrS1yxjL1OWT7BxTzgjPY/YsMzcQpudADFntq3Q1aDd4ftcLO1VlVi1tnjpY/d5xf22iTTw5tzp0U45VAowntSElER6gz9KXeWwUIAidnivHlWfuXDf+Xr0rcI7ZR7Q9s98vJTjkv9IUmvSEJLyR6XkP99R4N56yT/OZ/7asfON6zvPNqQ4OzurSO4jJ+IdLXTzhxYWFzi1fglaucpsG1FYlJ/ulHWlymeT+YOLZicxJoSx7Mfk8mGZlH0RqQ5/JN/jUXZbnrThv3LZk32UPfUKZU/zUfYcrEVZmJ+kHElZMt/utU3ad2xD93omZDmK85jtOn53uLfFUq+1cdtX3uC93+or+03b9gXujfd/v3HuMN1vbUm+9tvwAPab+rvuRu/91oA/kld7lt2mfNf4ve9CWge+725ofQ33ndx7vUn23UVpm2beBrrmYj5rqs367puU+fcej18=
*/