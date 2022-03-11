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