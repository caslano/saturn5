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
1Gk2+WtbeBLInk7FIB+EbMu5nlkNc4RuGeZDdpbd83uYgsaTttJWxd16XXq/i+LBPYyaBNNpfB3d5GXAWrzKb1kDDt5zPb/bTXeLziYzu+3aI3rXOU2ddpes0nx3XogsqeVTUQRtZHtuzgb0c6lMDN3gm/IZ+f520crrKBX/tsd57pUDGMIYL9AedLzA+4Styp93VzTQKL87H/4aXQDGg1DNBXPXKXPCG66z9eCr4hn8bGWc8z6Nn1wOb5O67y4tBzoqX68I47PMRTiF+bmWMD6CagY5DbroyLmDvz3XA7e4HSeWaSfLcf422SMiGzLIzEipotfuDNl67jj1LPFO2eqbvEkwQGucPT+rLPmiG5TPa9uUAajCHcONMlj8bqV4aziyM42iIjAp9IzNl+elg4AOoJtukZHVnv+7xabobg7XGJn1Bl9wLh/eSSH/YNee23/2vGNHIp6SVSjOvfL/0c1AlDwqf+WpR83haaH9PIm6kk+wJq+GOafnep7v6Sp3HVRiiWdsz7egR7vXn8ES4nnsl/M3Bx1UnXYVjnrjucz5M0r7kLUqjjwn/GTdZT1YldwfRT7T9ek+XC9rDmvaKqOJ7qOCma9HRf7kpzHXaXPIPBw6EX75WWeavqQ6y7cTLVFRPSc4e764p7hOinZd7YOLGx8Qe52vR7VxDDPAnfhiMgvOupgPFHwVGCGqDef+utvAzLfOXxXheq3r
*/