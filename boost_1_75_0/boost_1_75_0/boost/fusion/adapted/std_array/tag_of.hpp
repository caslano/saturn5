/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_TAG_OF_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_TAG_OF_01062013_1700

#include <boost/fusion/support/tag_of_fwd.hpp>
#include <array>
#include <cstddef>

namespace boost { namespace fusion
{
    struct std_array_tag;
    struct fusion_sequence_tag;

    namespace traits
    {
        template<typename T, std::size_t N>
#if defined(BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS)
        struct tag_of<std::array<T,N>, void >
#else
        struct tag_of<std::array<T,N> >
#endif
        {
            typedef std_array_tag type;
        };
    }
}}

namespace boost { namespace mpl
{
    template<typename>
    struct sequence_tag;

    template<typename T, std::size_t N>
    struct sequence_tag<std::array<T,N> >
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template<typename T, std::size_t N>
    struct sequence_tag<std::array<T,N> const>
    {
        typedef fusion::fusion_sequence_tag type;
    };
}}

#endif

/* tag_of.hpp
LQiqUx3KN5npG+/6EY6tistAJ6kLzpsZYKo3MFu5THkiFjUWd6hZdG9UMhiKoFDP5i6sKKAInAJklmUOOsep1GbP/ibV8WDJMCtLUgbLHfa7F/0+K8uX0U2eXcuGduRQtmrKiZcq5Nj8TMYt52ZKq77IZ4w1yOE5HjM/enPmoLMtzfEO5XO8nN3ZyD4/26GUDIPKVP8Y6dnYBRjCCd0v+0ohNMIq+zJSszxNYe4/WY7nszrCRtD+h0Na2EUp5SRblfrM9CrpgUms5eCKdWfRhCzf2G4OpU5mhMuzW9gUuYPRd6FS3MuT14s1HJUpK48Ps4eDl5cpkkV5CMMcWo0r4oisxF7ondsrM/0TKOKu95Dg5nC6k8gB0M9cYTWQTLcu21Kq8mFB7gjH7VW+NybfmxNumG4ZY3A22XGY7LjWnuyrj8Usz021sP4CXSFYaMKCZBHjEvRRD3syn4Nx3p0LyUgFLY6Gs/ANMlwP1mm20iVWvroAbSIms2NZ0qZYlkS9mP3zCXCX1wO1Sv9MKvmRPX2yJs/+IlVO/0pauhNaJWK3nL5bemBzOF2o2bphlrRWew/31jmRjkpwEcNYwzXs9yyf9/gpbSGMyZ6OByN7l1QVdS8Ll7WN2G/7ssG2dJTGZMjGzXClkodZPMzx16W+Nos87Iss3yLKo6qox4OR3TCLMBms4NQw94/ZTAT5HJBFNWZxJlT2YaiEXL2P
*/