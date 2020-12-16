///////////////////////////////////////////////////////////////////////////////
// times2_iterator.hpp
//
//  Copyright 2006 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_TIMES2_ITERATOR_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_TIMES2_ITERATOR_HPP_DE_01_01_2006

#include <functional>
#include <boost/detail/workaround.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/permutation_iterator.hpp>

namespace boost { namespace accumulators
{

namespace detail
{
    typedef transform_iterator<
#ifdef BOOST_NO_CXX98_BINDERS
        decltype(std::bind(std::multiplies<std::size_t>(), 2, std::placeholders::_1))
#else
        std::binder1st<std::multiplies<std::size_t> >
#endif
      , counting_iterator<std::size_t>
    > times2_iterator;

    inline times2_iterator make_times2_iterator(std::size_t i)
    {
        return make_transform_iterator(
            make_counting_iterator(i)
#ifdef BOOST_NO_CXX98_BINDERS
          , std::bind(std::multiplies<std::size_t>(), 2, std::placeholders::_1)
#else
          , std::bind1st(std::multiplies<std::size_t>(), 2)
#endif
        );
    }

    ///////////////////////////////////////////////////////////////////////////////
    // lvalue_index_iterator
    template<typename Base>
    struct lvalue_index_iterator
      : Base
    {
        lvalue_index_iterator()
          : Base()
        {}

        lvalue_index_iterator(Base base)
          : Base(base)
        {
        }

        typename Base::reference operator [](typename Base::difference_type n) const
        {
            return *(*this + n);
        }
    };
} // namespace detail

}}

#endif

/* times2_iterator.hpp
TiPsxxQy5IiwoNqdhRJxMojt32fKvaTDKtxK+iuf1Kn6/G7uxKikPqgccpfNEeR2+iPZDlrdfmXzZisc+PIUpLnI4aCxtaBLCuCikoSi3faCLu2QqqBHe8KryrmVEdgCALtnttajLB/voTmlxck4CSPKEVn5HfBGBinmhl+0oodsk3ODx7HQbfWGNuA/w4Kf7rHeot2xuLNu4EzHQoungMJWwNKtKN2xkCJtZTO7bzwFbqunIMNS4JYjcWdHv03ywvSbsD1Kv7R98vxA7UJpUEsihNsfYRRDeaR2/oFnIV/2PrUbgqbRMC0Yf62ztx0d4vrAMY0MyWUmonRt7hF5S/wW4j6pYG/Q6FZsG4B7wJpRtf68VgyJQtc7FvawZsB6CE1Lo7Z2QftL0P4iar+1oB5a7AYG0oEBvF3HNn7fFfSwoo8tBWmxXstIZF47cFcdcv+JrTPz8PaktMmFHTpGTf1BiCC2UqjdqN7cy+MiAwphz3TnsMHsKyrYDbXdyO/INO7hz2hEuckO1JbsmF1EN2T5j1py4c23hicwsq3PhUtgqYmQ/tBKSh6q37U4UZp+eQ09BEfaSy9A9Mbm0UaLkXk3lhttXYP/ktF29p9T+4f4YFz4/meVfbceo6NIy64umK0JSKk5PHlt8YKAXoZcCuohFW/2BzT08n6i/WXHlBdjNBVtp8SliBa+31dUKR0HyQ1p+QghvofewTqLzB0//3stDgEBIkQ9fRyijyUZpDF0QB1YD5BdQyXOL6SROUCTBhXZtyeTQUsTW0DopG4ceh7lqFlCxU78xFPFffC/7XFG7f99LONe/QkMjZWWWJmrQXcLsI2AJzSwloCTqQIsJuC9HAFeI2DnDQLMI+AbDTxEwGPDBMjnaNMFGEXAQzq3IQS8nC9APwAQGK7pD4EhdgIfIKZndaAPh19sCm9O4Z8gXD2vy2giiRNNkehZLZDEMaZwG4U/SYnf1nX6xgDQQ9dph8EpvusXTbEbz2qI5PS+KfwTCu9BOXXW1XiMcuqlgaDktNSUYgWlaCI5PW8KL6TwmpRTn2xJnCWJ3zRFmk+RvunN4XNM4a9S+CaEqy4a/fUk8bOmSAsp0l8o0j96SKQfpgIYPUOALwmYonviIwLazhagmIAWfQRYQsDl+s3rBDTUwNMAUGR/U5H0rNpKfW8yhXej8IuoKot7SuJsyqnJGAF6EfCMrmQGAQt0tA5SxoWmvOhZbe3F4VYzrk7G4/QWwlXwD5I4FDDR2gEC6g0V4FsCrtbRdhJQmC7ARgKe0cCyAJeyoG+0FHpWN0vpT5rCn6Hw9hKebwp/kMKbSvjDpvBHKbzWKcIPoPXqySlSiXZUo2F3CtAKAGovwKUEbJoswHlS1ztNefWlvF7syeEZpnB6VtMlvI0p/BoKH0Fltxssmb5XACC1lwBvETBYv3mOgEc18EgB51XNlBc9qyukjD13RMMP4VmdJ+HbTeElFP7TLRz+nin8Swr/CuGq2C+FXU4lP6GBiwiYrQEHAfOGCBBLwGoNHAIulU23QxEQM0mATwn4VFPb+wQc1kARAe1vE+AdAv6gy/kLAYPy9fifIvg11bkn1fkqqvN9EyVSrkTymSJlUaSa0uC2pvBUCt/fA4mv1HwhhYprpwEnAbP0oL+EgKv0IKpLQA8N2Ah44C4BjkwG0FUDuwlooXP7BwF36jdbCTipgVUEvDhBgIUAUM3Xb49WczGeVWeq5jMFEulBifSWKdI7FKl5Dw6fawp/nsJrU+Lf6+JuoeKOaSK/iYDkfgK0J8CbJcCVBIzUQGMC9uo09Qjor3OrTkBvDRzNB7BKR/uegEka+JyAlRr4kIDqNwuwJp/rbDPVOYE=
*/