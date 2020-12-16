// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/associative_container_adaptor.hpp
/// \brief Container adaptor to build a type that is compliant to the concept of an associative container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <utility>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/bimap/container_adaptor/detail/identity_converters.hpp>
#include <boost/bimap/container_adaptor/container_adaptor.hpp>
#include <boost/call_traits.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template
<
    class Base, class Iterator, class ConstIterator, class KeyType,
    class IteratorToBaseConverter, class IteratorFromBaseConverter,
    class ValueToBaseConverter, class ValueFromBaseConverter, class KeyToBaseConverter,
    class FunctorsFromDerivedClasses
>
struct associative_container_adaptor_base
{
    typedef container_adaptor
    <
        Base,

        Iterator, ConstIterator,

        IteratorToBaseConverter, IteratorFromBaseConverter,
        ValueToBaseConverter   , ValueFromBaseConverter,

        BOOST_DEDUCED_TYPENAME mpl::push_front<

            FunctorsFromDerivedClasses,

            BOOST_DEDUCED_TYPENAME mpl::if_< ::boost::mpl::is_na<KeyToBaseConverter>,
            // {
                    detail::key_to_base_identity
                    <
                        BOOST_DEDUCED_TYPENAME Base::key_type, KeyType
                    >,
            // }
            // else
            // {
                    KeyToBaseConverter
            // }

            >::type

        >::type

    > type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES


/// \brief Container adaptor to build a type that is compliant to the concept of an associative container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,

    class KeyType,

    class IteratorToBaseConverter   = ::boost::mpl::na,
    class IteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter      = ::boost::mpl::na,
    class ValueFromBaseConverter    = ::boost::mpl::na,
    class KeyToBaseConverter        = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class associative_container_adaptor :

    public associative_container_adaptor_base
    <
        Base, Iterator, ConstIterator, KeyType,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter, KeyToBaseConverter,
        FunctorsFromDerivedClasses

    >::type
{

    // MetaData -------------------------------------------------------------

    typedef typename associative_container_adaptor_base
    <
        Base, Iterator, ConstIterator, KeyType,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter, KeyToBaseConverter,
        FunctorsFromDerivedClasses

    >::type base_;

    public:

    typedef KeyType key_type;

    protected:

    typedef BOOST_DEDUCED_TYPENAME mpl::if_< ::boost::mpl::is_na<KeyToBaseConverter>,
    // {
            detail::key_to_base_identity
            <
                BOOST_DEDUCED_TYPENAME Base::key_type, KeyType
            >,
    // }
    // else
    // {
            KeyToBaseConverter
    // }

    >::type key_to_base;

    public:

    explicit associative_container_adaptor(Base & c)
        : base_(c) {}

    protected:


    typedef associative_container_adaptor associative_container_adaptor_;

    // Interface --------------------------------------------------------------

    public:

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::size_type erase(const CompatibleKey & k)
    {
        return this->base().erase
        (
            this->template functor<key_to_base>()(k)
        );
    }

    // As we redefine erase, the other overloads need to be manually routed

    BOOST_DEDUCED_TYPENAME base_::iterator erase(
        BOOST_DEDUCED_TYPENAME base_::iterator pos)
    {
        return base_::container_adaptor_::erase(pos);
    }

    BOOST_DEDUCED_TYPENAME base_::iterator erase(
        BOOST_DEDUCED_TYPENAME base_::iterator first,
        BOOST_DEDUCED_TYPENAME base_::iterator last)
    {
        return base_::container_adaptor_::erase(first,last);
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::size_type count(const CompatibleKey & k) const
    {
        return this->base().count(
            this->template functor<key_to_base>()(k)
        );
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::iterator find(const CompatibleKey & k)
    {
        return this->template functor<typename base_::iterator_from_base>()
        (
            this->base().find(
                this->template functor<key_to_base>()(k)
            )
        );
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::const_iterator
        find(const CompatibleKey & k) const
    {
        return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()
        (
            this->base().find(
                this->template functor<key_to_base>()(k)
            )
        );
    }

    template< class CompatibleKey >
    std::pair
    <
        BOOST_DEDUCED_TYPENAME base_::iterator,
        BOOST_DEDUCED_TYPENAME base_::iterator
    >
        equal_range(const CompatibleKey & k)
    {
        std::pair<

            BOOST_DEDUCED_TYPENAME Base::iterator,
            BOOST_DEDUCED_TYPENAME Base::iterator

        > r( this->base().equal_range(
                this->template functor<key_to_base>()(k)
            )
        );

        return std::pair
        <
            BOOST_DEDUCED_TYPENAME base_::iterator,
            BOOST_DEDUCED_TYPENAME base_::iterator
        >(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_from_base
            >()                                         ( r.first ),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_from_base
            >()                                         ( r.second )
        );
    }

    template< class CompatibleKey >
    std::pair
    <
        BOOST_DEDUCED_TYPENAME base_::const_iterator,
        BOOST_DEDUCED_TYPENAME base_::const_iterator
    >
        equal_range(const CompatibleKey & k) const
    {
        std::pair<

            BOOST_DEDUCED_TYPENAME Base::const_iterator,
            BOOST_DEDUCED_TYPENAME Base::const_iterator

        > r( this->base().equal_range(
                this->template functor<key_to_base>()(k)
            )
        );

        return std::pair
        <
            BOOST_DEDUCED_TYPENAME base_::const_iterator,
            BOOST_DEDUCED_TYPENAME base_::const_iterator
        >(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_from_base
            >()                                         ( r.first ),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_from_base
            >()                                         ( r.second )
        );
    }

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP




/* associative_container_adaptor.hpp
HP44981Xvv/yluOzb27Z+IklV1MHF5vlUc/PW3KqTeozP5817LFFm3+/kzpbw7X8kfFzUg/XXLpm/toGFTsfuHU7z06bfE5v2SFmfePlj30ze+PiXTcdG0W/aJaP3Lj28ne//93QIw//+s7aj7S9m7mzYNfyrl3XjPnrH79tMmrf3OhR90Tz0MUJ4n9kmoj72yFbYStsrX53wlbr90vY/fr9KrZKv1/H7tLvg9hv9Psz7BH9fpu6t1K/P+T3Y/r9RCBzqPr9dCC+fj/P70f1ewe/f6/fu/j9uGc7/L5Pv7/j9wb9TgnlfOn3g/z+tX63odM9Bns59I1hfRN5q8ad8SqH9nUdZRGwA2wMO8EervXwGFxmfTPXfMvXpO+CLVTf04V47WASjIe9YRa8CBbDfrBU/iz5c+UvlL9I/k3yl8i/Xf4d8u+Sf7f8B+Svlf+I/Eflb5T/lPwt8p+Tv0P+q/L/IH+3/Lfkvy3/oPxD8j+Rf1j+EfnH5H8r31V4/WGQ0728vtO9PELLI+VHaX1zLW8Nk2ESvBgmwwHafrJD3x2Fv9N5CcKSdF4RyS4LhDXhclgLxhAvGJbDEOjaTlfPtythPdWPQCxW2/k20FHmYgDx68JApYvBUpQuUumcmOdekTIt89S/IsWL9lP/KHOz/ddhI7gLNoOcAyt/K5V+sp/8va30B2EGrIAqH33P0HxT8bTyeS/Ane5DGAo/gvXhx3AZ/Bv05L9C22nmJ/8vOtzl8hIMgy/DhvKPwSEOfWcP7lX6mlhfpV8V6ihz+Q/CenAtNO8ywcbwYfgnWA6PwbgAfbNO383bCgdg0QFqj+y3BUyE7WES7AR7wi6wF0yC3WBv2B32U7wBincJvASO1XbGw0thluJdp3g3aPkv5a+GQ+AT8p9W/Oe035e0/DX5e+GF8Dvtr7bTna96TrcfLr+R/Dby28nvBrvDHvBS2Ed+f9gDDtRy8y08mKblk+RPkX8NHAqL4QXwWjgMzoe94QLFv1Hx7tD6NYr/kJaXwxFwvZZvgpfD/drOQaU7JP8D+R/Dy+A3cCR0ncvRcDgcC6+FV8L5MBWugONhObwaboQp8Gn5z8I01b8mnu866btSW9V2Q9V/s6wsAV4He8IFcCC8AabARXASXAynw5vhfLgU3gJvhavgbXADvAO+DFfACngP/AKuhDWc1HcYA9fA7vBBmAIfgZnwUVgKH4PL4BNwFXwSroeb4G74NHwPboHH4XPQyfE9DxvCF2FbuAMmwlfhYPg6HAt3QZWPvmlkvrd0WvnUdbrbU2OYCGPgRbALTIY3w6HEXQ5dbfNO+Cx8FCa4ruUwsgb5hzlwHLxe/n1wA3wKboEv00E9A0/C3jCkpjt9GHQtHwZfgDvhdvgmfBUu4t7sNXgv3AK3yb8kmHkyOB3+yRUPvgXvh/vhRvg2fA0ehCfgX2DNEPpHeMz0V9IJhcd0nWmErVf/tSHUXT7bYAe4HSbBl2B/uAMOhPvgWPgWnAr3w8fhAXgUHoSu6967sD2sgMnwPTgZfgDnwA/hMsW7T/GegB/BZ+En8E/wb/AQPAx1HZHGIW3Mz3Vkn64Hb8PL4TuqHycd0hWUjuFWXccOK90R1Y8vYQL8Gg6HgdpOF5gKe8H9sJ/q+wDV69FwHxwD+7raOfwFHAdfgn3gQeha/zEcD68g41fBB2AajKjB2Ax2gm1hPzgaDtDyYTAdToGTYBHMgWthPvwjLIBlHF8h/AUs0vFzbqTLQFwdfzPsfR3/VwHu4/87bA2/h4nQGeguhzrwcngBHA2T4Qp4NbzYSb7gz2EOXApz4Z0c5zT4LMyDL8Ai2Ih8FsMYWAJvgzPg8/BauBfOhl/DObA=
*/