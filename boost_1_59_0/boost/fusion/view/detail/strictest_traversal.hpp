/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_STRICTEST_TRAVERSAL_20060123_2101)
#define FUSION_STRICTEST_TRAVERSAL_20060123_2101

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/if.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/mpl.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace fusion
{
    struct forward_traversal_tag;
    struct bidirectional_traversal_tag;
    struct random_access_traversal_tag;

    namespace detail
    {
        template<typename Tag1, typename Tag2,
            bool Tag1Stricter = boost::is_convertible<Tag2,Tag1>::value>
        struct stricter_traversal
        {
            typedef Tag1 type;
        };

        template<typename Tag1, typename Tag2>
        struct stricter_traversal<Tag1,Tag2,false>
        {
            typedef Tag2 type;
        };

        struct strictest_traversal_impl
        {
            template<typename Sig>
            struct result;

            template<typename StrictestSoFar, typename Next>
            struct result<strictest_traversal_impl(StrictestSoFar, Next)>
            {
                typedef typename remove_reference<Next>::type next_value;
                typedef typename remove_reference<StrictestSoFar>::type strictest_so_far;

                typedef strictest_so_far tag1;
                typedef typename traits::category_of<next_value>::type tag2;

                typedef typename stricter_traversal<tag1,tag2>::type type;
            };

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template<typename StrictestSoFar, typename Next>
            BOOST_FUSION_GPU_ENABLED
            typename result<strictest_traversal_impl(StrictestSoFar, Next)>::type
            operator()(StrictestSoFar&&, Next&&) const;
#endif
        };

        template<typename Sequence>
        struct strictest_traversal
            : result_of::fold<
            Sequence, fusion::random_access_traversal_tag,
            strictest_traversal_impl>
        {};

    }
}}

#endif

/* strictest_traversal.hpp
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
*/