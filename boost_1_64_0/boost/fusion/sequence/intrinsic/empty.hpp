/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EMPTY_09162005_0335)
#define FUSION_EMPTY_09162005_0335

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct mpl_sequence_tag; // mpl sequence tag

    namespace extension
    {
        template <typename Tag>
        struct empty_impl
        {
            template <typename Sequence>
            struct apply 
                : mpl::bool_<(result_of::size<Sequence>::value == 0)>
            {};
        };

        template <>
        struct empty_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template empty<Sequence> {};
        };

        template <>
        struct empty_impl<mpl_sequence_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct empty 
            : extension::empty_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence>
        {};
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::empty<Sequence>::type
    empty(Sequence const&)
    {
        typedef typename result_of::empty<Sequence>::type result;
        return result();
    }
}}

#endif

/* empty.hpp
KwGkPoXZcNXSKNX+Q6PLYK4WL0cDPgGEmvXXD6i28Vf/9D+Ln27XUFoaWM/ff6jsli4elUZ9Dfe1DHpWRqaiHGz1LEJaXljm8xN6p++jPICyFVRD6/h9jbi8BZBC6UCTTNJ0vk3SFvnTFbDOLc7gjA3gU5PuD4gPapsjJugPqaAVkGJdp8wYyqpql5N40H5Q2vm/hzX0UR+p+Cw0Ibnm+0VUPRVfTEvxRSBUeXQkuERLWD6MUjivoLeaIW6Kzp8QWbesBtvSdWPtDobiGX+RWzTGbIh4iWoj3j43xaj8z2nlMdCp/ztyno5spKuOv4oKChm+ZR5Po0OHa62XZ0PQoXwlWerlunPavKLseEtaGX3HE+CSrFcsojvdIbIOpYgrXaD/E6idkEKZiWTlQm3PTAyGTuyd76bfeaiH4AUViHJnKObdqIt26FUDzBwvBXBXlEyAil1zL3hAMlNHyq7m1t2NO7aAHkblK2bq0x4mEsXrkao9+ZzSYoJ+tpaMI/9gaqTHVHitXWkGATdSuX0h7L0eu8AI9vJnojnCE+G2gPV+CDCPqt4rKRIBuQ==
*/