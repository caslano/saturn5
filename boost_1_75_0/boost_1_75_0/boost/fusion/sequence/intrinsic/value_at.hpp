/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_05052005_0229)
#define FUSION_VALUE_AT_05052005_0229

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/category_of.hpp>

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
        struct value_at_impl
        {
            template <typename Sequence, typename N>
            struct apply;
        };

        template <>
        struct value_at_impl<sequence_facade_tag>
        {
            template <typename Sequence, typename N>
            struct apply : Sequence::template value_at<Sequence, N> {};
        };

        template <>
        struct value_at_impl<boost_tuple_tag>;

        template <>
        struct value_at_impl<boost_array_tag>;

        template <>
        struct value_at_impl<mpl_sequence_tag>;

        template <>
        struct value_at_impl<std_pair_tag>;
    }

    namespace detail
    {
        template <typename Sequence, typename N, typename Tag>
        struct value_at_impl
            : mpl::if_<
                  mpl::or_<
                      mpl::less<N, typename extension::size_impl<Tag>::template apply<Sequence>::type>
                    , traits::is_unbounded<Sequence>
                  >
                , typename extension::value_at_impl<Tag>::template apply<Sequence, N>
                , mpl::empty_base
              >::type
        {};
    }

    namespace result_of
    {
        template <typename Sequence, typename N>
        struct value_at
            : detail::value_at_impl<Sequence, N, typename detail::tag_of<Sequence>::type>
        {};

        template <typename Sequence, int N>
        struct value_at_c
            : fusion::result_of::value_at<Sequence, mpl::int_<N> >
        {};
    }
}}

#endif


/* value_at.hpp
+bLI6xUlfbQ+zavop136bWJFLbqa+isGxDx6EEH7XUW2/miCWIEwRcZWTNXrcGJDqZFhInpWyCmW64+o2DVTm7FrsisjmRppfT0qVl7Ov5mRDCCVHEKQimfGl6LTODBMlTZm9PGSSONFMfPx8rQ+TPbpXfHnVuPlmbONl4Wz8E2hcXsYO38d9Hl49FnGS8F1Bj/VnNTGC3JrGIdadACkydIfZHE8XIdKRcFVCeBXhpMoSUnK6SHawPkcOCS8A8XZswa/H+FcdGCIxkX1wLRc5FXqrBkI4u3ZGP7VIQaAU1s0hkeu5uJMY3g3MvwcfDov5uk4fFqKT1fFsva94Vvx2SZjaIzgQyM3fAMHdmAssEjXcB/O6PcKCy/lV48Li5cg1A0aY09PkaUvK16C7grvh7VpRZPB8N9jMVW79RdBO7PDezijvsqHgChL9dCpo2qQJ8If82HgexzJ7UX2z0X2z9DZ/zn+7Sad/RcTGNBA5AF4nMN5H6r8PvIO3K/4Cu8FuG+M/LHi772j3P4HHAAejZFvGMwZuQFYIHKFeKLS7Lu2YlUsB9+jcXBSBVrdUQ5EBJruqL54QGsL8TWPpWLtvjLJROd1cnub2/gYpVEOA1HbBcPVuL+XcbqFIkPNwW0un3G6RaquQlt/jP+FfKe5NDD0dpP/VzxXCXXmUjohSg1GzstOeYyZjBNoeXm4Gyb8bUTvfvQ5ue57tEE3
*/