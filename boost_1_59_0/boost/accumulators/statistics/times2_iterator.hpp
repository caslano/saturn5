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
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
*/