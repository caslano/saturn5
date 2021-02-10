/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_ITERATOR_EQUAL_TO_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_ITERATOR_EQUAL_TO_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    namespace detail
    {
        template <typename Stack1, typename Stack2>
        struct segmented_equal_to
          : mpl::and_<
                segmented_equal_to<
                    typename Stack1::cdr_type,
                    typename Stack2::cdr_type
                >
              , result_of::equal_to<
                    typename Stack1::car_type::begin_type,
                    typename Stack2::car_type::begin_type
                >
            >
        {};

        template <>
        struct segmented_equal_to<fusion::nil_, fusion::nil_>
          : mpl::true_
        {};
    }
}}

#endif

/* segmented_equal_to.hpp
6E78MR7zSJeVXuJ3UiOOQhtpQWeuwURv1D5U8C4puguLD0RQv/pEA+qu3lnvQpsrdOc7cqVWChz4G3D8lvKNkZmpSp9OgWOENU5ALxiRovA19U4EnrRyGJvsmBANlnV8/gTbwHcnKRvJosc4lnhpP+IXYc6yuhhLMZxtGJBQ1C6o2gbNkNA4ALj7ptbeS2tVWoxpoXmsece9pjv2XHUHl8/HQtKZtM8aZJeFT1v3EaWEqCe2RCTrvmwEhMlIgsdAddUYd/3zbfLiQfeTkTUMooCJ8lXUIYJRAoq5lM+yJJ2ckxTFmjFL36pN4Op/kMLVlSSuFpO4SqOvLiJydZ7I1QIqayhL6awrbUzpjPbZSsWGkhZpQCJ7B8y88aalIsOft4K+W5EB9fR404iAbdghBY4onJXb9cym9JoLojJO9q/bNXDf0DzIXBc/t/9Mp3hm04ItaCuWoLc01/SqjOtEufUZ30m7TlvGvNPHvhw/dtRxs8EPHgGzWwFVHDUSuuGy8NSWZbsOVl0vSFD0bOOiU/kBlLAchIJvBI9lZgM1m/NTaD9YlVeeu6EjDOLRI6bDOm2q6thD0VVlp3QtF14uA433FO3R/90250yAKeW+i2fL9o1BfWwPKT2ppo5e0d0Iv/JIT9uX5/UWnqvl
*/