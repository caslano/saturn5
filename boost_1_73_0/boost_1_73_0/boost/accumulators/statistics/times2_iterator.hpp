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
BccvKgyv7PYXaPzB56KX2UBrq/OnF7DNLj9y0K5We6iMQBQXFnYXvsWwStX1cXVbXnuOc0ZhkwADp3toKEjD6VREVBIeH+SsgQGKoC+FP8osI6MRbCYfFetQCJ2HURSJGpbGlU0aPJ1PN7fkqA7PTk9xLkBPwr/HTejEui3osqZPL/5rA1nPB8N27J8lrxropsmShw3oBPY/4qkrQeEhHzNwHOt5d3/PQKO2wZMGxvmcFInmaYeSSM3zQfb9ceCzyxJBVBal7Xqh6TFnC9FogfOOlrgepVq9J0h960miMoCjmcmgSZmNL3ohgX31I5UgEY4KuCjJCWzERJuEKaBiimr04E51S0Di8QymFogNnpijJX285RhoGwB13fkN4HODQ5uWxN/KMh29hu3YGYSrjah9ceu9CXDG4+bSCsIZgGkuSAsRPeSwJ0ufe+03LZ89ZrWwXCL6grUcZlntcxj3Tpjl3zdL67yfU6i/ypx72apujjE6kzSUFiWHexJ+isah1d+cVtLXnKG4n9EgLWqY455HpziYW7kXHtFZ8orz7On9jQpT/8TH3EaHqxxafVk4amsZJu++YqNa1it2NxjjJRQ5DNZa1/mt79t8GqkfPN0GV2Rt46iIycdosQjZ/qkTEVMfFT2Xs5ERmkRZ
*/