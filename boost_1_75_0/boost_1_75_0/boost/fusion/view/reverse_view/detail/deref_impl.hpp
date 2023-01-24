/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07202005_0851)
#define FUSION_DEREF_IMPL_07202005_0851

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<reverse_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<
                        typename result_of::prior<
                            typename Iterator::first_type
                        >::type
                    >::type
                type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return *fusion::prior(i.first);
                }
            };
        };
    }
}}

#endif



/* deref_impl.hpp
KJZKFG9PQfMQBybxIgJpvk2kijZWo3xw3/eGuquP5xQbevC5rHL/TRmIW7n0ETbW5dGcOsMLcKQ3A0haqu7xZS1RmvL/s5595uUOzx7KBH8HaUGgGxnL5D4M2G2NgkN6TLxrSfrY2/sM1cuD4Q9Fz7n7SdVRzDR3P1+VR/VbbJcRc8vq3aprV/3yWjSBhETx2s8cnau5B017wgr6dKfJ6+GjDnFn7qKJmIRtAK5iFPWjXMUzPCOZabdUdXvDZaSXfQt+QTvVuW2eugXG3IuAi3plJ09OK0DjzNVVSulapwxu2wOAuqacUzML+wNNEP2KNZkrd74UE7fvMb5AvSqoaSlgtk4envugpef8UCB1c/aa5a/frM6VNKdWglH/cy0/CnB/fZjLDYkUU9fZ2JGLKobwI/XvF5Nf6R8Sv/a8oteBS7xR9Z8m35DjRWeuXhmEfIPGMTvNg4IibJVvpU5i5GahN/JwyYPXD5p+0rowfHyy3b3TdLD7/OZBnIRjGmvX09M6R2bsJCOl8lKsWU6HX2pn2M2UDv4VSgaGTvfECXo1ehOPJ4xUH6dJ3FPsbAmTbLViQgL39gdKn1g91aROqDIudOgPKSDvtzOIXtCS6rk3d9f/9P34Fs6QfK6jc4Ek7VBr7GFMhu6Z829qOEUebcg2F8HdLOGc0Mq6nGY/xvNZMAA3ynntrnnsf6R3f49cXBAiVM92z6lFGe/o
*/