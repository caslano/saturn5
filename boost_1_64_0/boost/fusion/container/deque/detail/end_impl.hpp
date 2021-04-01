/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_END_IMPL_09122006_2034)
#define BOOST_FUSION_DEQUE_END_IMPL_09122006_2034

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque_iterator.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct end_impl;

        template<>
        struct end_impl<deque_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef
                    deque_iterator<Sequence, Sequence::next_up::value>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
vGW/jrR0ue/MdpEAb3mVMl8rP0eQ/h+3Dm7EcManpobVi6WcCe4MncC6EuYLhTWaNf4UIqH0HVRivZjEfHEh85hm1EHS0VgI6tD5FoYuXbytH7UideyB11FiuYd2AP5cqngUf02uFXu+kx0ztrDoIzbGbnDKzlMQe+yLiXmoCQddg0BcfYM8GgsV9ak4/Q67XZ7VRoWIhMq3iE0fAHhwlXqdqRsdEMLlMn6JQx5RDrlI3SHIGzUr2SBkF8/nKVJlehk9+AwISYqgt9gL7LZMuuwb5+Q8lAVDzOgPdl9sE4Fdk4w7a0kA6uNr0oj1SXVakYVd42+mAGQsrfCCmQXfnSZq9uZwhMQKz+mA7PwWXSYmqXJPCAAlZcrEuzO/B6H45T1Ww757vhZZMICJ2lkdemCD7ZTOGcftL4P9UMfw67a32u7FQQ9OJYHpsxWLLh0g3OIjBLCgmqKy5nu5aFes4PYjw/2bUqUAiQ9DRxjGsYCwcd26v8jeOz25spuowFM5SUi428cFz39aPuq7A9cjJEc2NK/m5sM6uWHe9KO4DsaYrsmgIj7MrtAMqw==
*/