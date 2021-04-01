/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ANY_05052005_1230)
#define FUSION_ANY_05052005_1230

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/algorithm/query/detail/any.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct any
        {
            typedef bool type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    any(Sequence const& seq, F f)
    {
        return detail::any(seq, f, typename traits::category_of<Sequence>::type());
    }
}}

#endif


/* any.hpp
dxbbTEpKPpyE8J9XzMHaSsEirNveFhpuwPgsf5wfoLULRht7z/zLe/h0wEFs1vPRpAvX9+voxSxaCm+ZGhSdu0sp5ZuzTW3GnMgDr09mn1woA1ebpZxctj2aWw5g+RFySSYryoXxd4MuXAF+wrtHo+RK6g2hV4G4diQHnnJY16f34iBr0gwjXdP/mRArQZrqLgvPXD7h4IqPtGdQ5FQLG9+z6zfjn8CJmI5fpAgMAKysX8rCHq5D8q2zJk79JTuFZ5UMJFfG92q4ygKxDO0td/C0MItO25xTDJghEkq/ZbhJ8ikQs/T7D5+ist+hJnoipadkMyN4sJ4FrX3v+4GGqlL2M7hdD++2PWOQFwMnKh7mZgWU+dHq0WUmy5u8QJuq+WqHt/wpfShJC+KmK+b7Q2jgHxEz9UID5e+hs7XsRm7seyLF7R7vSV3abnF3/ofHkGy9dZUK+vIHf2KqyR5H29jwkjwFJLz70V952dwdHICyDSLOv0jdPbjxSn+GGy/kFvWM1sx82Vao7x36H1DjcjeTdrYdbLlXCqNCp3kLjo9enP9kT2eFWzalMg==
*/