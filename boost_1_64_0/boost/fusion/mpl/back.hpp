/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BACK_10022005_1620)
#define FUSION_BACK_10022005_1620

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/back.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct back_impl;

    template <>
    struct back_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : 
            fusion::result_of::value_of<
                typename fusion::result_of::prior<
                    typename fusion::result_of::end<Sequence>::type
                >::type> {};
    };
}}

#endif

/* back.hpp
SxyWchAxRiJ3CMEEZK3AUa66Ok3jpzP1PdYXF6K/ZTVJz0LSY+2SVFGgXPnXgQWHJ/8T2G4vZDxaLT7uLnoap1VQXqxbxfQrmz8odAmActiYVMByT5kOcSqcs7lYYsQFJdp5X0UBeDjPolWMvzMs8Sqsw0+k6LVN4O/LumGDKTbee59xFit1dBzusKEHPA/2MthWV1edw1Lwu+y9pUlpAOb8iidZf4YRPDL8hjmnktYnx7RamkEwrG5CN7HdTS8xHnNi03fSQPgTlAOaa0zgy6MSGxbXKJMGlSFVR99QR19jZuRlkkWeSXDp/DZPnejY2gEstaWbEfndkLA020uzhOoJEdbfzA9vR4DYtQuOdzwk5EfmcSPd/kV+ZJUgR4gU+VEJ95LsOLfj8p2xwtOXa+Wi1/OHvra65h1Y6cYIGKnZqmjn1MSgGLx8zWVwaoqnEmrYLvnTgqSJf8O4hnuwAeQpkiE2Hlof0tLT8tRzlytWY3sWz9LxY5TowiH4kVBAnU6KMQ0UQVgLecd9TFkIt1RlhTWiymEy8s12DEWaPWOdczm7Em8NHWUGbw==
*/