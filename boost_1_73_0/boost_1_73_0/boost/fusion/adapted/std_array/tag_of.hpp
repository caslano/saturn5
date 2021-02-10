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
cKbXttayactbTlpTI5ov/cth5OT5THPtS9hJ7lefYsbLplkf7dE1bJu7JTraIy5iSHXXYQ/+6F9MhgMvKDOvEbnz5C8PLMBLbnZIvzyzHKILf3t0mu7CBfuGj0tKe7pdIG01ySKA3R5Nf2YoO/DASFPKsbM5GDaaSWTRId6GbUbHna3Off2J7NCujkzQoyf9NqIXHOtQhg3RNryVWbPkTRKTVnuFpF5tVQfUZdGtsZlwldsz9YlyqOyNa3KkA1VWWPrwTCpdsLZboOd+PTR6CSDMXpp5LygnPHfYcNKRprbWkAumTQPUqrZRqn5UQd9+K59KshXjs31ryf9fOZhYsTUlK5CVdfUUsh3eYP7jBRl3oux/7YfD/m/hMIyuvX6aNj9ZmnPCTZgOosvpCGgHLwfeFA0dxNrt8SAen3v/AlBLAwQKAAAACAAtZ0pStwI9p0AFAAC0CwAALgAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfVVBMT0FELjNVVAUAAbZIJGCtVm1zm0YQ/s6v2NIPtT0YWUln0rw0UyLjmIZIGoGSuqMZ5gRHuBpxlDssq03/e3cPkF+aafQh8sigY/fZt2d3cVc2nHyzj+USHHz1k5hvgh+8DkrzRv7B
*/