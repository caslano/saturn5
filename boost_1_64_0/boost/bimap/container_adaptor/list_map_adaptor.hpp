 // Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/list_map_adaptor.hpp
/// \brief Container adaptor.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_LIST_MAP_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_LIST_MAP_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/list.hpp>
#include <boost/mpl/push_front.hpp>

#include <boost/bimap/container_adaptor/list_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/identity_converters.hpp>
#include <boost/bimap/container_adaptor/detail/key_extractor.hpp>
#include <boost/bimap/container_adaptor/detail/comparison_adaptor.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/if.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template
<
    class Base, class Iterator, class ConstIterator,
    class ReverseIterator, class ConstReverseIterator,
    class IteratorToBaseConverter, class IteratorFromBaseConverter,
    class ReverseIteratorFromBaseConverter,
    class ValueToBaseConverter, class ValueFromBaseConverter,
    class KeyFromBaseValueConverter,
    class FunctorsFromDerivedClasses
>
struct list_map_adaptor_base
{
    typedef list_adaptor
    <
        Base,

        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,

        IteratorToBaseConverter, IteratorFromBaseConverter,

        ReverseIteratorFromBaseConverter,

        ValueToBaseConverter, ValueFromBaseConverter,

        BOOST_DEDUCED_TYPENAME mpl::push_front<

            FunctorsFromDerivedClasses,

            BOOST_DEDUCED_TYPENAME mpl::if_< ::boost::mpl::is_na<KeyFromBaseValueConverter>,
            // {
                    detail::key_from_pair_extractor
                    <
                        BOOST_DEDUCED_TYPENAME Iterator::value_type 
                    >,
            // }
            // else
            // {
                    KeyFromBaseValueConverter
            // }

            >::type

        >::type

    > type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief Container adaptor to easily build a list map container

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
    class KeyFromBaseValueConverter        = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class list_map_adaptor :

    public list_map_adaptor_base
    <
        Base, Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyFromBaseValueConverter,
        FunctorsFromDerivedClasses

    >::type
{
    typedef BOOST_DEDUCED_TYPENAME list_map_adaptor_base
    <
        Base, Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyFromBaseValueConverter,
        FunctorsFromDerivedClasses

    >::type base_;

    // MetaData -------------------------------------------------------------

    public:

    typedef BOOST_DEDUCED_TYPENAME Iterator::value_type::first_type  key_type;
    typedef BOOST_DEDUCED_TYPENAME Iterator::value_type::second_type data_type;
    typedef data_type mapped_type;

    protected:

    typedef BOOST_DEDUCED_TYPENAME mpl::if_< ::boost::mpl::is_na<KeyFromBaseValueConverter>,
    // {
            detail::key_from_pair_extractor< BOOST_DEDUCED_TYPENAME Iterator::value_type >,
    // }
    // else
    // {
            KeyFromBaseValueConverter
    // }

    >::type key_from_base_value;

    // Access -----------------------------------------------------------------

    public:

    explicit list_map_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef list_map_adaptor list_map_adaptor_;

    // Functions -------------------------------------------------------------

    public:

    // The following functions are overwritten in order to work 
    // with key_type instead of value_type

    template< class Predicate >
    void remove_if(Predicate pred)
    {
        this->base().remove_if(
            ::boost::bimaps::container_adaptor::detail::unary_check_adaptor
            <
                Predicate,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                key_from_base_value

            >( pred, this->template functor<key_from_base_value>() )
        );
    }

    void unique()
    {
        this->base().unique(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::equal_to<key_type>,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                key_from_base_value

            >(
                std::equal_to<key_type>(),
                this->template functor<key_from_base_value>()
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
                key_from_base_value

            >( binary_pred, this->template functor<key_from_base_value>() )
        );
    }

    void merge(list_map_adaptor & x)
    {
        this->base().merge(x.base(),
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::less<key_type>,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                key_from_base_value

            >(
                std::less<key_type>(),
                this->template functor<key_from_base_value>()
            )
        );
    }

    template< class Compare >
    void merge(list_map_adaptor & x, Compare comp)
    {
        this->base().merge(x.base(),
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                Compare,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                key_from_base_value

            >( comp, this->template functor<key_from_base_value>() )
        );
    }

    void sort()
    {
        this->base().sort(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::less<key_type>,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                key_from_base_value

            >(
                std::less<key_type>(),
                this->template functor<key_from_base_value>()
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
                key_from_base_value

            >( comp, this->template functor<key_from_base_value>() )
        );
    }

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_LIST_MAP_ADAPTOR_HPP


/* list_map_adaptor.hpp
zE1zrqsfr1l6n5Q555Qy91yHreuFylTnuaM5Np7TbF1VJ3VqPfdGP2Rla/gHuCWWko3zOs9T8gonZ+TlFRZeM6OoypjP7EDn1ZOmrTWGut34SU63j7pbB6Pt5Ygk/T5zPvILs2agE52TW1xSWvmt0dEm3kz5nnTZZr+fmHTF2d5t85BZ31d1zhM/n2tsX5Pmq1amx8jL8/q+6xqTt1in8a00N56et4LsWaVe36ecaOJdI9+TbqxJF1jTlOhlJuHogowir3FfjomXKd+TboJJ94bZX2ZxdkYpmtlKp2M7bPL5TrXHtsud1+zuidKdxPOqT5aZ72meRY++KKBS32ZlgKcemXNs9dXsj2Vmf6ZerTD5o+21dvvvyW8o/7j8T2PdfnKHqutH+/gZ8t9Q/MIOVdOXy98nf4P8MVFu/zmf+Pt8tv+ZT/qTPumdHaumr9Ox6vqG1vqqY4Y7zV+jd2D6y13wGHEq4r3a0TTkf7KLffpK6zvXirvf0ZMlT2P6hpSpI0fNNTkn16WqXpSXW2pp6lrpmjiiVNdOGn93QHf+bsTqOp1Wm3UwHs4oLrXawfLOpo90Rlj6SoU5OSU0L+UrHH5k4rxOfuY6fo7qSTt9A/Qbs591AfGsWYfVdNZ0zMM+wwoDalr9wEyTPlj3OD46+mpXuxJccY47O+p7s6Wee0avfHxp9veMwxXnUazymLILslzx1EZWmv3Vd9ZyxPE+ZpZvPKsttepidHwdxDP68Hn16M+JN8+tg769TggSZIGhocwneI/trbb5oNlPXLX7NddsbfeAtd0Fg8+23bguZrt+82l9q8urfaf/gGtGlK4ZR0279qlf1Pdu5ph4f0ftIc/HP+jjp3ep6t9l+T5j/wbSo2Zlc5gI95Ov3S292ovrCw0O37GFdb1R3HZWPTth/EhnbfX5wV7f1omJca37sIr+5hETv5s0o51m2UMm3kTelwyprK+m3elapzb2nUnbhH1ZYxGrTX1h1rVwuq79KzjatcydXOc696Flz3iP972/JZIVreu/1/nMcNk5nNd6jqDwZ0y+HbHZxcWnn2edy8YmDuWkc3Mkxn9fNsvVuI02hfuesghuJE5yW69zk59dPCW7uLpzo7idHZE6NwXGbxRQSB3ei2JAhMYEV7RzLc91tnQkO63xoCnvkqLszG7q4zzb62SNB68xfpOAls4Q65p6Q3v395JO306iNR6datI1C1jucKdLsbYdp7ri2U6i1/k3B5tlvoOi43nHpHnTGefoz71KS97DPur3mKJcdZGyC648JquBRbjri+IXEL+zpR1qeiuzj+GUIctUP9eZZfUDPnN84PBs21F5nGbb3uOV6Sb++ABXP9SLNlfaiHcXw4wO5OsoPHbSdw2qncdrYPLWodp5vDCzPtpdl7WPA9Y+sth8UFCdWnXan20/D5l8xle7nwfM+pbSMLwqvI5DfZ9Xe7kp2pjVdhZFn3sbOvt42jp/us/yXZ5YZVy9sIl74yEcWxP4Hbaec3W0jVcbcnUp6ZmFBTOzi0urb0tKM8AaD1j126dfGm7FbW61k7qx+KgrbOZv5TW+tDijoCSH+0BXPFPfapt4hxxPsZdI1XvFy8soNXXfakPLTdx0rsN1fK/V1ve3e5o4E823oeZFkq/GnjrRJDQgqE5b6kPtUFelaOinTuj+LMJso6PfOtEQ1jfr23vfQ1l14froH+ucq3zpL93HxLhH/edwH3+S5Ve9lz4VJS0F1YUD8GviLOtq1QU1XFct8H8vTT1Q/HxGYM3OWBeidJ4eNfGXOBM4T5nOIMeNmOqJttXC6vMuTnRrbbew5ncySkpmUD3zMkpK03NL0rNyiz11IBI+YtK/5uw=
*/