/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Brandon Kohn

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_AT_IMPL_HPP)
#define BOOST_FUSION_MAP_DETAIL_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename
                    mpl::at<typename Sequence::storage_type::types, N>::type
                element;
                typedef typename detail::ref_result<element>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& m)
                {
                    return m.get_data().at_impl(N());
                }
            };

            template <typename Sequence, typename N>
            struct apply<Sequence const, N>
            {
                typedef typename
                    mpl::at<typename Sequence::storage_type::types, N>::type
                element;
                typedef typename detail::cref_result<element>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& m)
                {
                    return m.get_data().at_impl(N());
                }
            };
        };
    }
}}

#endif //BOOST_FUSION_MAP_DETAIL_AT_IMPL_HPP

/* at_impl.hpp
KPd/i1nQ7pb9sVmYdxNNX7grsV+/irtQyBuwmPv+ZbkZGvJhJ3+iQSdNI7+zVbQsRc7xt50Q/NB4C7MYpHGRIoBRvqUIzA1ZvXi4i77RrxZ5mAArxgYFKufJ/SeLfZkFMWf4vcGG7mgGz3Hq7sZcJj5ILcfcqARQGoUTURXcxKpV/OkHcavQXueUUYp2KdxCq+fCk8JEVIuXcjL4VnKv0OMxbPGrwS9bkfiRnC6JdT4vmMok7WuJI6ReeS8ucyR3tY0LP8bCm/Iv17Xi9rwxb4X3n1kdGyzartNr+V8b/6N5EXYa2h1IjfCTwWwtNVmLRirRUnucTwfGLxbQkFUJ+FpjgxnJbXfV7lTsqBUIuHo05NVzn/HCBVU3VqlLySPChHeDaQHiIR111fGoawHR+s3YF6VWwKQV8Msuz65gTml2Avkm6a1uTNhnpDkQ+jwPA8xImFe2W1QReUsyreHwNfKJV9J0g5HQS7GdSyqmdxCl8rJ3rgTEPM+p/7lWhqQ5muDtgCfKJKffSkkZ8TgqfwNKOA5uyt/dvotE0nv5axP6Pg0m19HTILbhx50d1fx3thWXNz8MLOfQBTkIH8zefe2d2X36XHtXSlU/qvfN4ov2/SJtk5bY+MrpnOcVyHkCmxE2VTFbK09ucpNf
*/