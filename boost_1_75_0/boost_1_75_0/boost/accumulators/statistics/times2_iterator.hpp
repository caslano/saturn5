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
Jpi5a4qLKeTa/biJKgFVuVso2coSkrXmIvrQZzYXEZX8EutAUr6+d4X1p1uRfiekacLazym9PWE2cQnKvbjKWt3EdhVCWeYuObta9u2pUOzyTixYR2dxgSQUSOM6SDkmaWlsuzvJpWltduf/v7Y3X8J4tM325k1jO9sbeITUbW+Gw/ZmCBTxUmF7c8dvbG8OnruS9U3dqIvWN5UR65td/8H6Zuoo3fpm7X0QZ8Z6rC5F6xnh1G6/aGkT/x8tbeZxo7gS3tFmblOitYWGJU4JAaZZRBxll878Ha06xxHDCJ5p+Djc2pmdHM+wfsLlfNKd4yJ8kuZLoLnUeRyXlm0lNmn2rAj3086v0fLdJruySmvv18hlvtzFD/v3YcFDMJiGJTkj7ezFXnP66Q5+EIsraGuFctTxlohfo81HW9jtD//W4nfrUN35j5gpmwxqsmxi5wH95YhDtXfgmbJ+BHx8olpsDoO8t2TzSHa4k8y/8fgNKlSSCbHDHeFIbBc33wzYDpZzGjSB+oZuvLpdVzmCQDxf/asF5nPyzgR2toMx3DNF2sx1b45vjQTgzMsr3nlNK/vPmgta51ibyy0DPJsG6jcQC7hzCErI3C9BTFxLgxDRL//Olhb+NGcDPHslYSSbMfDSIAYSKJdFK9eCqqVkfazhCn+5qYQL6HMa6XSVIPpBg2zmCeH589yYx9fWZR24Zzsxs0YhsBnBWHYe
*/