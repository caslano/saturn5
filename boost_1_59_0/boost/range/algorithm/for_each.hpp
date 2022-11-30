//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_FOR_EACH_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_FOR_EACH_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/ref.hpp>
#include <algorithm>

#if BOOST_WORKAROUND(BOOST_MSVC, == 1600)
#include <xutility>
#endif

namespace boost
{
    namespace range
    {

#if BOOST_WORKAROUND(BOOST_MSVC, == 1600)
        namespace for_each_detail
        {
            template<typename Iterator, typename UnaryFunction>
            inline UnaryFunction
            for_each_impl(Iterator first, Iterator last, UnaryFunction fun,
                          typename ::boost::enable_if<
                            is_reference_wrapper<UnaryFunction>,
                            void
                          >::type* = 0)
            {
                    typedef typename std::_Get_unchecked_type<Iterator>::type
                                unchecked_iterator;

                    unchecked_iterator unchecked_last = std::_Unchecked(last);
                    for (unchecked_iterator unchecked_first = std::_Unchecked(first); first != last; ++first)
                            fun.get()(*unchecked_first);

                    return fun;
            }

            template<typename Iterator, typename UnaryFunction>
            inline UnaryFunction
            for_each_impl(Iterator first, Iterator last, UnaryFunction fn,
                          typename disable_if<
                            is_reference_wrapper<UnaryFunction>,
                            void
                          >::type* = 0)
            {
                return std::for_each<Iterator, UnaryFunction>(first, last, fn);
            }
        }
#endif

/// \brief template function for_each
///
/// range-based version of the for_each std algorithm
///
/// \pre SinglePassRange is a model of the SinglePassRangeConcept
/// \pre UnaryFunction is a model of the UnaryFunctionConcept
template< class SinglePassRange, class UnaryFunction >
inline UnaryFunction for_each(SinglePassRange & rng, UnaryFunction fun)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange> ));
    
#if BOOST_WORKAROUND(BOOST_MSVC, == 1600)
        return for_each_detail::for_each_impl<
                typename range_iterator<SinglePassRange>::type,
                UnaryFunction
        >(boost::begin(rng), boost::end(rng), fun);
#else
    return std::for_each<
        BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type,
        UnaryFunction
    >(boost::begin(rng),boost::end(rng),fun);
#endif    
}

/// \overload
template< class SinglePassRange, class UnaryFunction >
inline UnaryFunction for_each(const SinglePassRange& rng, UnaryFunction fun)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange> ));
    
#if BOOST_WORKAROUND(BOOST_MSVC, == 1600)
        return for_each_detail::for_each_impl<
                typename range_iterator<const SinglePassRange>::type,
                UnaryFunction
        >(boost::begin(rng), boost::end(rng), fun);
#else    
    return std::for_each<
        BOOST_DEDUCED_TYPENAME range_iterator<const SinglePassRange>::type,
        UnaryFunction
    >(boost::begin(rng), boost::end(rng), fun);
#endif    
}

    } // namespace range
    using range::for_each;
} // namespace boost

#endif // include guard

/* for_each.hpp
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
*/