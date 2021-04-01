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
FII00O++/5SfdDKdxLSaJZm6PgRn/XQHhG0/xYpD3CG5OicIOEBhsonsDOaTXrSQIC7P+maoqJrILtGJKRZ+LkihBqOaPqcjVx9G24lbl53OHnxbQqzE6xNak7NXR5d1cbVpivaLbM38zbJ9Hoq/IgyTriCBhKnMKIsAztWN/ZaJ9ONR/6KW2Idb/GJ56wbYg/PKvdNGuNmHg/CEYXRtSxAuWDlJr8UYlhChkFsuONU/nVf8ABqDNtAWYyuyXLoakIRwFp1P342GyKdCg9g+DnA3MggZ+FBwzX2uU0MOzYUqlyn9MIx8apDIi9g4eIEBdd9OXAc5zspu5Oc5teffYztMoQkV2UMdSwUfL9rofuE0Whe+N78fk+kdaZBdI6q8vImkAUgxmzd233eXJzQwH1cEsDiRb/c/pKLwQLi1iOaJqg1NeB/fm5PvPt5pXkt1abFKZyC1/L2Cnm4Oei4Sm3XRT3VH/u6Bqcr8xvpjzDo6sZz21RL55Wh0KzN7XxdeeR9EmSdmlMEGZ4U1BjKcWkpZJCb5GsAu1NXdgnMcqUuAscUUKflJw6lpIQ==
*/