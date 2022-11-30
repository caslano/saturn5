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
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
*/