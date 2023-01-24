/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_20060124_2033)
#define FUSION_DISTANCE_IMPL_20060124_2033

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/algorithm/query/find_if.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion {

    struct zip_view_iterator_tag;

    struct random_access_iterator_tag;

    namespace detail
    {
        template<typename FoundIt, typename SearchIt>
        struct best_distance
        {
            typedef typename result_of::find_if<
                typename SearchIt::iterators, is_same<traits::category_of<mpl::_>, random_access_iterator_tag> > finder;

            BOOST_MPL_ASSERT_NOT((is_same<typename finder::type, result_of::end<typename SearchIt::iterators> >));

            typedef typename result_of::distance<FoundIt, typename finder::type>::type type;
        };

        template<typename It1, typename It2>
        struct default_distance
            : result_of::distance<
            typename result_of::value_at_c<typename It1::iterators, 0>::type,
            typename result_of::value_at_c<typename It2::iterators, 0>::type>
        {};

        template<typename It1, typename It2>
        struct zip_view_iterator_distance
        {
            typedef typename result_of::find_if<
                typename It1::iterators, is_same<traits::category_of<mpl::_>, random_access_iterator_tag> > finder;
                
            typedef typename mpl::eval_if<
                is_same<typename finder::type, typename result_of::end<typename It1::iterators>::type>,
                detail::default_distance<It1, It2> ,
                detail::best_distance<typename finder::type, It2> >::type type;               
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<zip_view_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
                : detail::zip_view_iterator_distance<It1, It2>::type
            {
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static typename detail::zip_view_iterator_distance<It1, It2>::type
                call(It1 const& /*it1*/, It2 const& /*it2*/)
                {
                    return typename detail::zip_view_iterator_distance<It1, It2>::type();
                }                
            };
        };
    }
}}

#endif

/* distance_impl.hpp
eJ5IEWf9slIeag/6MnM+Hup0W+ZlcBK8H7t0xCJvcw9mJzBNkf3P801UCkC1VMoAmRuInIvxpz45+MaL8kST4vD8eUGjl7r7mzJuxjOQz2nDNVyYxszCvAUY0HO9WhmeSbaiDXeON/pbo5TdvwBjFRw4TLZdLus10qaDIqomPM96OdabJemifG2jSAR0a5Wt1+r32nAtZpJXlfMBoI3hc8N3HpWTW+/OM366Ua/GgxiP7vholI7FymzyyXtFXvl+wGR5IlbB0p7zJtzDOyn+AI8CIhrWlbx/FXRNEXRhnlgI408H+UhrOJNq5sE9nXZOQH+Rr1Vkhy6hF8X2vJC/Nsj+EgmTCTAH/xVPQ70Fxj46qsix3HSXWIUuYncvM8GAajiYlVw+oip6nW7KTjTH/tJTsyqHh+1dlaubJG1xtx68kJPuKny8zncWeqfLoW2ZGEM8A0Y/X6+XDjRfC7ejPtZzF0Qv6cmRgX82+9B1PdfUz1nEZ30Bz3I6fP5RWQhqCOA+cn8NJBrZRGtM31XQV8SXnpewKRdBRXTS+1wu6816anJLlawWvmNz3BlPgyKioTqN7s/j6VWeCxkxIrRRmQ7yYa7n4a3TCwbmapbveH1/oBLokQNv5qkBoG+aMAe7Mx2lIlIYvcBwn+vRAwPLbycPag7jc6yfTzbiTfa3Vaalj/KV9YYjD3yTpivD8Yz5QPH0qdQWypjMYRRH
*/