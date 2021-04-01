/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_04052005_1141)
#define FUSION_END_04052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_end.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct end_impl
        {
            template <typename Sequence>
            struct apply
              : mpl::if_<
                    traits::is_segmented<Sequence>
                  , detail::segmented_end<Sequence>
                  , mpl::empty_base
                >::type
            {};
        };

        template <>
        struct end_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template end<Sequence> {};
        };

        template <>
        struct end_impl<boost_tuple_tag>;

        template <>
        struct end_impl<boost_array_tag>;

        template <>
        struct end_impl<mpl_sequence_tag>;

        template <>
        struct end_impl<std_pair_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct end
            : extension::end_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence>
        {};
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::end<Sequence>
        >::type const
    end(Sequence& seq)
    {
        return result_of::end<Sequence>::call(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::end<Sequence const>
        >::type const
    end(Sequence const& seq)
    {
        return result_of::end<Sequence const>::call(seq);
    }
}}

#endif

/* end.hpp
v36gVrAKoBQ0ISVVpygcAcJEvoiP0azI24pfpZsTcyt/3eWaF4xE8Z65zOf0dhkZicDc4s5wFwMGbkoUrVfcyjlGW+tLSkNpx8bd7XjmEGFgCH6PDgrti/AZ5YgCP8D9UZiqUhNa8/1RrwVGshBvmkhKSc4iCZxzXkvxYHLwL5YNkhiW0bXKXypeprt3wdmr4bDBKUNUC8m2QP2g7jR+poJ87AKqJrbGZcD+7o2GflOSPrsbtFO9ifGszXBEU8bkrY3h5w/AkwK3I9oxpeqEu4CX5aiOzFgJuQB+LbEl5WqgW8aB25JdW3dBaLpLcwK1snjLxIRsKKxeKm1Mgr/LlzN2D1O6M2AeqMSvXo3kHSk2VJ/XVNZ6htNOEkM83cj9qAcmoT5JaMrhiPp7CHSueZegwQgt4/TQEtbYqUXamlXl+57Ccb2hv8vEOLXWcY/NeB+7G67nkCFZYmAe3SXGM+68/5fR7Jv627aSCZ9UOm7or2gDalHQEaK1tZKrkQ7PQDF9JqjFMuzxPRmLsntN/PLz8RPfyxuluYF19cQZWbmR2uGWXzpmM6Yegg==
*/