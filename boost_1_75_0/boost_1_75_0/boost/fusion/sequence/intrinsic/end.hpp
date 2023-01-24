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
kHVu3E23F+dBi3si+7aC8oOjM5en5211RhsPcGj26EJqq9GDCzQtoWeulP+Vr7s7m1I0T+UVq3YT1CupVZF/R0y4/VoIeniWm03P0bZdY84+QANT0yVNQdLbyfHqm+9aO8UNS4v3u6GlPtQCLP3sL+ci6JKFMCqExhCarMg/OSqxGQ5zeJPhg6dU1Zhr4Voz4Ov7Il4mwlS1zc12KynIg4ZOTnR3sTQ8wh843OxhteIJU7yH7fZdIrICm3dSYXzTfo9ltzSpxpOx2z2pajTrmop5gjH7MhthO+E0WwRfkvAx/A00NHosNR4HNFN7Z/ixJoDorDZuN7sdADpGHREGsIC1MIq3PCJeeQizwLjiM0tP7Cc4XT0qxab9Tkuls3xEvA9m5TpyaEXbt7Ij3vDV6tCSzWMxcq8HEIHW394B+fDJoNe+vuoPOOXmV/l9UmByGpp/01T71quR6V3o1ZOq2guvAaWuUroWr3fwa9mbzu9fx3sXSBlYloUa0iWHC//DEi0kbeDhkKH2DLhxRJsCUR8CCTEbQQCQJampHm5/h7cA7cQqEAATUYiofW++BoPGwL0X7sOZ8ZpeMe4qlAy2TOXy4ghexHEKggb3qyvZVBXoexUUN2nxJdBoX3CKjPaVVpz7NRH3zdUk4uLZ9p1XbsAMrsrnmKcDrUiNYkU9xmP7ExnXvY2qvYw65GXKKSav2k+dvZ2kzoNX61ur
*/