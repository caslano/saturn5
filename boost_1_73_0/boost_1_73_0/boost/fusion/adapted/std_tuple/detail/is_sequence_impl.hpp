/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_09242011_1744)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<std_tuple_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
M2BfgX0DltdOsW7tFLNPZ5g4j2EOLR2yRXq/pL9hjkiviybfeuc/bzzSq6mO8GvAk0OTJ4+dcFfk3rqqKk7QTq+WcHRSU53wKEDVRhcC6SaD4dce/aYL5kNN0Guq4/33+ZYt+bpu10Vvjphjkf+VmdO6dM1QJaKrUGIW2FywTWCbwdwo9ppNsYN8FWkU86RUbFFVk4hJDgjBqu9dlKAYr90n1laYa8cl0fNioDU91QS4B4SefCb1Aex9gvDRVR0=
*/