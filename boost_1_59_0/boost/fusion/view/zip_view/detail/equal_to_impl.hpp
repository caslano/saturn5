/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_IMPL_20060128_1423)
#define FUSION_EQUAL_TO_IMPL_20060128_1423

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/mpl.hpp>

#include <boost/mpl/lambda.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/zip_view.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/unpack_args.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/equal_to.hpp>

#include <boost/type_traits/is_same.hpp>

#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion {

    struct zip_view_iterator_tag;

    namespace detail
    {
        template<typename It1, typename It2>
        struct zip_iterators_equal
        {
            typedef mpl::zip_view<mpl::vector2<typename It1::iterators, typename It2::iterators> > zipped;
            typedef mpl::transform_view<zipped, mpl::unpack_args<result_of::equal_to<mpl::_,mpl::_> > > transformed;

            typedef typename mpl::find_if<transformed, mpl::equal_to<mpl::_, mpl::false_> >::type found;

            typedef typename is_same<typename mpl::end<transformed>::type, found>::type type;
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<zip_view_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
                : detail::zip_iterators_equal<It1, It2>::type
            {};
        };
    }
}}

#endif

/* equal_to_impl.hpp
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
*/