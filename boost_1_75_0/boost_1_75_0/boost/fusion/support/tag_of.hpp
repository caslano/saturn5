/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_TAG_OF_09232005_0845)
#define FUSION_TAG_OF_09232005_0845

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/fusion/support/tag_of_fwd.hpp>
#include <boost/fusion/support/detail/is_mpl_sequence.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/config/no_tr1/utility.hpp>

namespace boost
{
    template <typename T, std::size_t N>
    class array; // forward

    namespace tuples
    {
        struct null_type;

        template <
            class T0, class T1, class T2, class T3, class T4,
            class T5, class T6, class T7, class T8, class T9
        >
        class tuple;

        template <class Head, class Tail>
        struct cons;
    }
}

namespace boost { namespace fusion
{
    struct non_fusion_tag;
    struct mpl_sequence_tag;

    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(fusion_tag)

        template <typename Sequence, typename Active>
        struct tag_of_impl
          : mpl::if_<fusion::detail::is_mpl_sequence<Sequence>,
              mpl::identity<mpl_sequence_tag>,
              mpl::identity<non_fusion_tag> >::type
        {};

        template <typename Sequence>
        struct tag_of_impl<
            Sequence
          , typename boost::enable_if<detail::has_fusion_tag<Sequence> >::type>
        {
            typedef typename Sequence::fusion_tag type;
        };
    }

    namespace traits
    {
        template <typename Sequence, typename Active>
        struct tag_of
            : boost::fusion::detail::tag_of_impl<Sequence, Active>
        {};
    }

    namespace detail
    {
        template<typename T>
        struct tag_of
            : traits::tag_of<typename remove_const<T>::type>
        {};
    }
}}
#endif

/* tag_of.hpp
XtWdBdxwLeWVCcVUJM1NFrzdRyvfkCiNsoGFbDiTDgA7WpM7TXL7kztJctcmd5zk9iZ3hOT2IHeg5M5/wtz+kvsWuaWL8BzZ5M6XhsILT5RhN5PcgvTM/ic6p6XM3fbzwvhizlwCTEV7PqY4xiZxHBynfP9xlKJMbitD8+MJrkaWsItsHHrzIpTJy6Pl7z+Ok7//2EsxsrCLHjM0Fz26WFxqV1FPSkvOc29x4fYJUX8fKyvkdiH5JX5mLOWUrJDvpkw8P0FRyP9zgTG//wKYf3Y0JvknT0A56TWWZ+L5XixjruxzU8vKE/J42R3j5QFns8jBSmy8lO4jofGy4Vw6SMw0yPu/3pF7Zcx9560mRT5Ho1X7Pj/qqToDsuWknM3PvVg2A8cr2dzxPcvmxe+xs6j1KOz7/D0T2RwdzXcYBdrVZ0D6nnRry1haUFLUERbrHFWpEy03osYvK1uf0omxj2KURhSIRvQMMdiaM/ifKL716cQYzthHL4GxQLZBiGogzOrUgMQq/7mS1Hqi0XqOznZuPfrzT5JG0Ub3H4w1O/903q1gYh7T0H3k+obWALMrK6eizRnQkgt0zh0EmjUUjzVKRXeGZziwVHQfLZ/esdsI61596O5mCzPz/zFPl5TqqyZqB0tXTZSyKFdN2IXMF1XjLZvr1Z11UzXXY8eIJ/dVT//YwdLIJPUXG9hSt+fPD1VebEL38/4clReb
*/