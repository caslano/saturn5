/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_31122005_1621)
#define BOOST_FUSION_VALUE_AT_IMPL_31122005_1621

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<mpl_sequence_tag>
        {
            template <typename Sequence, typename N>
            struct apply : mpl::at<Sequence, N> {};
        };
    }
}}

#endif

/* value_at_impl.hpp
ZaugKDfY3ngdMS1a3B1PAxhTlp1rLkY8DMdsN9kt65Kw3beqn11LGkjJSg2dv52+vKPV7cp7tVov79Ryv/IeW9a+vMnBykvUVRvZ9Bd1YVddFSvZAZ53PxdrBBlwmkp3uiU8/1smYBVHk7NiWQmHxR3bJtm6nwt3MFv4ZXc0zB5Jzd1RHQASeKP5qSl9BtzuORXmtnIAxVgCUCyKLN1TzFqhhhS4wP73miDa8axOq+IsRj9lgLI+Y6S4HWyCV74lO8+0qHr25u7tUL6QfXHPsd/qwndh/o5baaWD0kzQkYTRl6lsQuDB3ZlShQvmCNRI4zsXMkkwlCmToEIERe7QJuUKfCVGFyvmUpZ1U/83WjW6+8xSvindWRRd2d0Svqh5LABURlfCcq45nZFxFksLGJ9bgMZ69nGbxGjc8w7SGAk0eln7xR2XiNoYOjthX3BYpQBsITNG2/TozmK0rVsKGG3zlwmMtpeeFBht1qH/R4y2w/DhuoctJoy2K5YBUFnv6GAYbXaMC3+wPUab6j09RttPPvj2Q+//a4y257wCo63vCijhAy9itF26QsdoO28FYrSdeAGifV4TRltjkh9GmwNJPKeLgdFWU/7PMNruzOksRpt3OO0jLnqXrg+GvguXOulMsKmvXdyqqS9ejHuGHu+SxOv2rjjzN+QBa9uoAVE69yQZ8kCIgdQHDTFAAsBOdWfc8+dZAWLADmIA
*/