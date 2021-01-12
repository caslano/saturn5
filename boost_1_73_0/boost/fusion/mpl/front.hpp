/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FRONT_10022005_1618)
#define FUSION_FRONT_10022005_1618

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/front.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct front_impl;

    template <>
    struct front_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : 
            fusion::result_of::value_of<typename fusion::result_of::begin<Sequence>::type> {};
    };
}}

#endif

/* front.hpp
h0GMYOoXmFNIQioykI0w8lGMMlSiBk1oRTu60IthxKTQfiQiBenIQg6KUIoKVKMOjWhDJ3owhFEkXEj8IhMh5KIQJShHFRrQjAg60IdBBC/ifhCPJKQiA9kIoxhlqEQ92tGLYcRcTPuRiHTkIA9FKEUF6tCINnSiH0MYRXQq/Y8EJCMNIRSiHLVoQDMi6EA3+jCIEQTn0H6kIgPZCCMfxShDJWrQinb0Yhgxl9B2pKMIpahA
*/