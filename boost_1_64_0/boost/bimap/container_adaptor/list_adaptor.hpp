// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/list_adaptor.hpp
/// \brief Container adaptor to easily build a std::list signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_LIST_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_LIST_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/sequence_container_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/comparison_adaptor.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/call_traits.hpp>
#include <functional>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::list signature compatible container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,
    class ReverseIterator,
    class ConstReverseIterator,

    class IteratorToBaseConverter          = ::boost::mpl::na,
    class IteratorFromBaseConverter        = ::boost::mpl::na,
    class ReverseIteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter             = ::boost::mpl::na,
    class ValueFromBaseConverter           = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class list_adaptor :

    public ::boost::bimaps::container_adaptor::sequence_container_adaptor
    <
        Base, Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses
    >
{
    typedef ::boost::bimaps::container_adaptor::sequence_container_adaptor
    <
        Base, Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // Access -----------------------------------------------------------------

    public:

    explicit list_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef list_adaptor list_adaptor_;

    // Interface -------------------------------------------------------------

    public:

    void splice(Iterator position, list_adaptor & x)
    {
        this->base().splice(
            this->template functor<BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()
                (position),
            x.base()
        );
    }

    void splice(Iterator position, list_adaptor & x, Iterator i)
    {
        this->base().splice(
            this->template functor<BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()
                (position),
            x.base(),
            this->template functor<BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(i)
        );
    }

    void splice(Iterator position, list_adaptor & x, 
                Iterator first, Iterator last)
    {
        this->base().splice(
            this->template functor<BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()
                (position),
            x.base(),
            this->template functor<BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(first),
            this->template functor<BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(last)
        );
    }

    void remove(
        BOOST_DEDUCED_TYPENAME ::boost::call_traits<
            BOOST_DEDUCED_TYPENAME base_::value_type
        >::param_type value
    )
    {
        this->base().remove(
            this->template functor<BOOST_DEDUCED_TYPENAME base_::value_to_base>()(value)
        );
    }

    template< class Predicate >
    void remove_if(Predicate pred)
    {
        this->base().remove_if(
            ::boost::bimaps::container_adaptor::detail::unary_check_adaptor
            <
                Predicate,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( pred, this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>() )
        );
    }

    void unique()
    {
        this->base().unique(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::equal_to<BOOST_DEDUCED_TYPENAME base_::value_type>,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >(
                std::equal_to<BOOST_DEDUCED_TYPENAME base_::value_type>(),
                this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()
            )
        );
    }

    template< class BinaryPredicate >
    void unique(BinaryPredicate binary_pred)
    {
        this->base().unique(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                BinaryPredicate,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( binary_pred,
               this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>() )
        );
    }

    void merge(list_adaptor & x)
    {
        this->base().merge(x.base(),
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::less<BOOST_DEDUCED_TYPENAME base_::value_type>,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >(
                std::less<BOOST_DEDUCED_TYPENAME base_::value_type>(),
                this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()
            )
        );
    }

    template< class Compare >
    void merge(list_adaptor & x, Compare comp)
    {
        this->base().merge(x.base(),
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                Compare,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( comp, this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>() )
        );
    }

    void sort()
    {
        this->base().sort(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::less<BOOST_DEDUCED_TYPENAME base_::value_type>,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >(
                std::less<BOOST_DEDUCED_TYPENAME base_::value_type>(),
                this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()
            )
        );
    }

    template< class Compare >
    void sort(Compare comp)
    {
        this->base().sort(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                Compare,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( comp, this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>() )
        );
    }

    void reverse()
    {
        this->base().reverse();
    }

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_SET_ADAPTOR_HPP



/* list_adaptor.hpp
yrDV2FasCTfXe2AyPAyz4GrsFL9Du7E/bAw2D1uCbccOPxvo2APfx45jNRLJHxaL9cVSsVLs8EDKahBl4FoGS7EV2BZsJcvWYduxA/hhg8kHv1Ogozvbw2Kxvtgels2D5dhW17pLAhzx2BBsN34FdhwLTuJ4sMMs7wvzsGVY9KUcM7YlifLBPsJOYmE9OIdYV2wSVoSFrqWchhC/B2mx5ZzTcmwfdhhzfQe6IRaHJWOpWBG2GFuNbcH2YEexYL7TE40lYSOwqVgZtgLbhO3GPsIcA4mH9cLSsFJsCbYa24q9j9nBDnawgx3sYAc72MEO/4+hBpbjcIYDx6AL0wqLsgtKCmcUZ2a7f5bkJUyekZuXldCtc7fOXXMSZpYkdu12gbVuVs+khJKpGcXZWQnFvL+OXIsnRmbx7KLSwrTsyZlZuZmdCydPM89b9A13THI9X9PAURuVRYfFy3IziwtLCnNKY+JGdYgZWVSam587J7dgSsxA1G1y87Jd75KEhgfW5J67v2tuKGtGfv5s5nxHhC+NNsfAfZE9preDHexgBzvYwQ52sIMd7GAHO9jhTPf/Bf+6+/+sEmPp1+YWdE800wA/cB6gBfMAz8XyfF4/Mw/ApvOzS6e6t8+mzZzAnGjXPsLMMSXp2cxgR6U+4Muk393RaDkNGj0y/bLBY4aMHJSuY2L9mb8hUlWjt0Lbj1aEZtiRCJa7t59eUlqcl13QvZtD793HGR0nllqaWYrLFirfpSeJ1ofDv5j1Tc+Qr5gqGolx5v1Z9uHJq8piR2ClZnhzfdtnP2UR1smd15klRcW8c5uTToQI8tKitSuv6QNm5ORke+VX8TtY+vi9jd/ZpGkTZtJcUlicn1GqNMOtNO0sLfiexu9l0rRy72dEIW8CZ3t9W627iTPE+CnWNtqYNEU1TZqLi6eMyC0prfzOUtdOXt9VstLEGM2A9/GTAtkuD42FduhQMzg0oDMvl1s6Y0lR7uOua0o5fZQELK3zMFnb9mggdz3DuYiUxhhlyLlQGWr5ENjGnCOVk5anwFYmvspCy1Mhx8ty7+PtHZ5m8sN7SaTx/gZCjSB3Tkyl0/NVB1xtxn2eVdFdVbMgc2oxx+xdL2ltXrqeShOmbwI4HeuM38oRbr5F49GfzJRGgyd+N3zqglmnuqxz6FlfW/vkyKx9PW/Whfjb11n1NyN96r51HCwPszT0Mk0baeIqf+OTN5/2vCLodC28iljMXXYl16TPLMzNSi+Yke9uzwdjTbld41VmxK2qX/douLd+XfVttytke+SL7fnkK6nm6fk6RFxHfJV8FRUWufP1lya++VJcr3xNaHDu+WJ7fvPlqHV6vt6LJbVPvmaUTK0uX4obadYHmnZdVFrsrYPnk+/U8yhPK99a1gsGmrZk9lGl3ez2cywfcCzJVY9lZkbeDJpm9ec/2XM8VvvIzZrlpc+a7HM8l53H8bA/3+NR3WYfHk1c9fe9NCWehbXE0rAPST/JfTzq7c/Y1ytuR6tP/oXxL/Df16sPXmDiNNX582yjtcNoeTnc+tZ7KOs9NNi5Ll2LxI5Gu78Uf3ewu38O7Ej3HJRwzn3zRrOPuqZvPkv/PCDc6m/998+pp/fPpr99LN5/fxtTx73lb7AG2BHs81Y8Y9zalLMZm6RPzi3ISs+ZUZDprjcbWO90jV8cld8ef8XEf9tRzrZV/tpGU+8+enZ+QUZ+tqd9WHEirW//vmT893j/xWn29VEskb3a1BDihLcx3xuU73TcZPyGJv7HJj778Yrf1axvY8W/1/h1zLnsG8I5rs17Qa5zGdKpSr9nNFYUZzFxyoyOytjQIM6/Vf8Vz7OtcmtbI3y3ZX03KY2yeDs=
*/