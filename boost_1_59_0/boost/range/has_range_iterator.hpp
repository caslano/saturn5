// Boost.Range library
//
//  Copyright Neil Groves 2010. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
// Acknowledgments:
// Ticket #8341: Arno Schoedl - improved handling of has_range_iterator upon
// use-cases where T was const.
#ifndef BOOST_RANGE_HAS_ITERATOR_HPP_INCLUDED
#define BOOST_RANGE_HAS_ITERATOR_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/range/iterator.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost
{
    namespace range_detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(type)

        template<class T, class Enabler = void>
        struct has_range_iterator_impl
            : boost::mpl::false_
        {
        };

        template<class T>
        struct has_range_iterator_impl<
            T,
            BOOST_DEDUCED_TYPENAME ::boost::enable_if<
                BOOST_DEDUCED_TYPENAME mpl::eval_if<is_const<T>,
                    has_type<boost::range_const_iterator<
                                BOOST_DEDUCED_TYPENAME remove_const<T>::type> >,
                    has_type<boost::range_mutable_iterator<T> >
                >::type
            >::type
        >
            : boost::mpl::true_
        {
        };

        template<class T, class Enabler = void>
        struct has_range_const_iterator_impl
            : boost::mpl::false_
        {
        };

        template<class T>
        struct has_range_const_iterator_impl<
            T,
            BOOST_DEDUCED_TYPENAME ::boost::enable_if<
                has_type<boost::range_const_iterator<T> >
            >::type
        >
            : boost::mpl::true_
        {
        };

    } // namespace range_detail

    template<class T>
    struct has_range_iterator
        : range_detail::has_range_iterator_impl<
            BOOST_DEDUCED_TYPENAME remove_reference<T>::type>
    {};

    template<class T>
    struct has_range_const_iterator
        : range_detail::has_range_const_iterator_impl<
            BOOST_DEDUCED_TYPENAME remove_reference<T>::type>
    {};
} // namespace boost

#endif // include guard


/* has_range_iterator.hpp
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
*/