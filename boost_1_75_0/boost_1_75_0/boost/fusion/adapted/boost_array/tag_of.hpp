/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SEQUENCE_TAG_OF_27122005_1030)
#define FUSION_SEQUENCE_TAG_OF_27122005_1030

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of_fwd.hpp>

#include <cstddef>

namespace boost 
{ 
    template<typename T, std::size_t N>
    class array;
}

namespace boost { namespace fusion 
{
    struct boost_array_tag;
    struct fusion_sequence_tag;

    namespace traits
    {
        template<typename T, std::size_t N>
#if defined(BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS)
        struct tag_of<boost::array<T,N>, void >
#else
        struct tag_of<boost::array<T,N> >
#endif
        {
            typedef boost_array_tag type;
        };
    }
}}

namespace boost { namespace mpl
{
    template<typename>
    struct sequence_tag;

    template<typename T, std::size_t N>
    struct sequence_tag<array<T,N> >
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template<typename T, std::size_t N>
    struct sequence_tag<array<T,N> const>
    {
        typedef fusion::fusion_sequence_tag type;
    };
}}

#endif

/* tag_of.hpp
fRkYmRxi+xknS+e+CN0/rALmeDsCj4l+347HRJt24DHRd68gYMEqtflidJmzSrOddRm50VmlamcAau/tBwib4oBxQv8XgT/UsL+9BGSwiv3cLVyYHWZFauBOULNdkcoyw6OhcxESAg3E3WfgHD55t4ER/5aIRU9naPxsnJpKpe/R9XhRHCtmlX7Tw7I4jIRe+C1YdGGBH40AqTRjFVn91ggABKnsIizBeYBPlc4afVfyB58mx9hN8jrWYj69vjDMOH/epqZ8S6K6Nz+95hkkQwbm/Qh9lV1jfPnZHvrySxQdZLcO8BR7xcYQiN6LROP57iuQQ9rte6XSx6jjXxmOHVpB2ToPrBsLRPuyK9S+KZIFQPO8zjpZmVzBwjaoV93ImCpb6QOe89A4Dqj880zIiSBuRA3BQK+SLBQZnXUObVIq8FT2BiRQs2VfBvbDt28Aa2vy+8tKbOyDLFODKzQL4vMPpnQ1TUdOappugLqeldA8FPoPgFs4w+iGxrsF8MRuIYixI3+/lFzaBUYHWD/vFUn2GtbMNZzyxy4lioS9Pvg/vBRYJFtC/ccTEt7dWUlnwR+2E5ErjubSwPyNP6+ayOXKRLJjvpC/78glc6ABE+nZe2K7ez3Pr7mAd7vKMDVwShX7nEqbi1yoCQRZMrEVl7b7LzGrf2aA+ufCHDarvIxSm42rV5AxprKZdmeRi0NL4j3qjY/rZo6s3nZY
*/