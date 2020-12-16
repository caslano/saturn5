// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/ordered_associative_container_adaptor.hpp
/// \brief Container adaptor to build a type that is compliant to the concept of an ordered associative container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_ORDERED_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_ORDERED_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/associative_container_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/comparison_adaptor.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/operators.hpp>
#include <boost/call_traits.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template
<
    class Base, class Iterator, class ConstIterator,
    class ReverseIterator, class ConstReverseIterator, class KeyType,
    class IteratorToBaseConverter, class IteratorFromBaseConverter,
    class ReverseIteratorFromBaseConverter,
    class ValueToBaseConverter, class ValueFromBaseConverter, 
    class KeyToBaseConverter,
    class FunctorsFromDerivedClasses
>
struct ordered_associative_container_adaptor_base
{
    typedef associative_container_adaptor<
        Base, Iterator, ConstIterator, KeyType,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter, KeyToBaseConverter,

        BOOST_DEDUCED_TYPENAME mpl::push_front<

            FunctorsFromDerivedClasses,

            BOOST_DEDUCED_TYPENAME mpl::if_<
                ::boost::mpl::is_na<ReverseIteratorFromBaseConverter>,
            // {
                    detail::iterator_from_base_identity
                    <
                        BOOST_DEDUCED_TYPENAME Base::reverse_iterator,
                        ReverseIterator,
                        BOOST_DEDUCED_TYPENAME Base::const_reverse_iterator,
                        ConstReverseIterator
                    >,
            // }
            // else
            // {
                    ReverseIteratorFromBaseConverter
            // }

            >::type

        >::type

    > type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief Container adaptor to build a type that is compliant to the concept of an ordered associative container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,
    class ReverseIterator,
    class ConstReverseIterator,

    class KeyType,

    class IteratorToBaseConverter          = ::boost::mpl::na,
    class IteratorFromBaseConverter        = ::boost::mpl::na,
    class ReverseIteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter             = ::boost::mpl::na,
    class ValueFromBaseConverter           = ::boost::mpl::na,
    class KeyToBaseConverter               = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class ordered_associative_container_adaptor :

    public ordered_associative_container_adaptor_base
    <
        Base, Iterator, ConstIterator,
        ReverseIterator, ConstReverseIterator, KeyType,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter, KeyToBaseConverter,
        FunctorsFromDerivedClasses

    >::type,

    ::boost::totally_ordered
    <
        ordered_associative_container_adaptor
        <
            Base, Iterator, ConstIterator,
            ReverseIterator, ConstReverseIterator,
            KeyType, IteratorToBaseConverter, IteratorFromBaseConverter,
            ReverseIteratorFromBaseConverter,
            ValueToBaseConverter, ValueFromBaseConverter,
            KeyToBaseConverter, FunctorsFromDerivedClasses
        >
    >
{
    // MetaData -------------------------------------------------------------

    typedef BOOST_DEDUCED_TYPENAME ordered_associative_container_adaptor_base
    <
        Base, Iterator, ConstIterator,
        ReverseIterator, ConstReverseIterator, KeyType,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter, KeyToBaseConverter,
        FunctorsFromDerivedClasses

    >::type base_;

    public:

    typedef detail::compatible_comparison_adaptor
    <
        BOOST_DEDUCED_TYPENAME Base::key_compare,
        BOOST_DEDUCED_TYPENAME base_::key_type,
        BOOST_DEDUCED_TYPENAME base_::key_to_base

    > key_compare;

    typedef detail::comparison_adaptor
    <
        BOOST_DEDUCED_TYPENAME Base::value_compare,
        BOOST_DEDUCED_TYPENAME base_::value_type,
        BOOST_DEDUCED_TYPENAME base_::value_to_base

    > value_compare;

    typedef ReverseIterator      reverse_iterator;
    typedef ConstReverseIterator const_reverse_iterator;

    protected:

    typedef BOOST_DEDUCED_TYPENAME mpl::if_<
        ::boost::mpl::is_na<ReverseIteratorFromBaseConverter>,
        // {
                detail::iterator_from_base_identity
                <
                    BOOST_DEDUCED_TYPENAME Base::reverse_iterator,
                    reverse_iterator,
                    BOOST_DEDUCED_TYPENAME Base::const_reverse_iterator,
                    const_reverse_iterator
                >,
        // }
        // else
        // {
                ReverseIteratorFromBaseConverter
        // }

        >::type reverse_iterator_from_base;

    // Access -----------------------------------------------------------------

    public:

    explicit ordered_associative_container_adaptor(Base & c)
        : base_(c) {}

    protected:

    typedef ordered_associative_container_adaptor
                ordered_associative_container_adaptor_;

    // Interface --------------------------------------------------------------

    public:

    reverse_iterator rbegin()
    {
        return this->template functor<
            reverse_iterator_from_base
        >()                            ( this->base().rbegin() );

    }

    reverse_iterator rend()
    {
        return this->template functor<
            reverse_iterator_from_base
        >()                            ( this->base().rend() );
    }

    const_reverse_iterator rbegin() const
    {
        return this->template functor<
            reverse_iterator_from_base
        >()                            ( this->base().rbegin() );
    }

    const_reverse_iterator rend() const
    {
        return this->template functor<
            reverse_iterator_from_base
        >()                            ( this->base().rend() );
    }

    key_compare key_comp() const
    {
        typedef BOOST_DEDUCED_TYPENAME base_::key_to_base key_to_base_;

        return key_compare(
            this->base().key_comp(),
            this->template functor<key_to_base_>()
        );
    }

    value_compare value_comp() const
    {
        typedef BOOST_DEDUCED_TYPENAME base_::value_to_base value_to_base_;

        return value_compare(
            this->base().value_comp(),
            this->template functor<value_to_base_>()
        );
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::iterator lower_bound(const CompatibleKey & k)
    {
       return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(
                this->base().lower_bound(
                    this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k)
                )
            );
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::const_iterator lower_bound(const CompatibleKey & k) const
    {
       return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(
                this->base().lower_bound(
                    this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k)
                )
            );
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::iterator upper_bound(const CompatibleKey & k)
    {
       return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(
                this->base().upper_bound(
                    this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k)
                )
            );
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::const_iterator upper_bound(const CompatibleKey & k) const
    {
        return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(
                this->base().upper_bound(
                    this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k)
                )
            );
    }

    // Totally ordered implementation

    bool operator==(const ordered_associative_container_adaptor & c) const
    {
        return ( this->base() == c.base() );
    }

    bool operator<(const ordered_associative_container_adaptor & c) const
    {
        return ( this->base() < c.base() );
    }
};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_ORDERED_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP

/* ordered_associative_container_adaptor.hpp
BsMwWBtGwXowBtaHHWAY7AQj1L81UvsLh/21fDBsCIdo/WWwDsyHobDQLPdoZemeVPc9U320snqrvl0I68M+sIHxpT2CrVT6OJ3fZq5+ROnrK12ENLOawLYwCvaDzeBAGA0zYHOYCXvCXNgSFsMYeC1srfPYBj4MY2G54j8O2+k8tpc2SRzcCTvAN2BHaWh1gidhvDRIEqDrILrCRrAbbA4TYUvYA7aGPa32pPsteJOf9tRTmjAXwDjYS1pqvWEivFD9ZB94NewLJ8L+ut70g9fKXyT/mNEC0z0J/Er7jYArtN+juq58AdubOO56chJeLq2VFFhDWi+npH30d/Vz38G74ffwXsVbA51wMwyAz8FA+IrW74LHVa5fws+1XFp0uregbPxo0eXoepirfE/T9fAajR9K4YWwQFpNJTBdy6UJx9j+7JpwrnjrzhKvobRIkoafmxZJStF/1nPFlboj56438mM9X/yfqjUyhnNZhC3HyrEdWAV2EmsyIsTRC0vBpmJl2EpsK1aBncKaXGZrjdjBDnawgx3sYAc72MEOdrCDHf4zw0/0/D+PPv04z/8/6npu5ULX8//m3/2lxebp/dISsm/WL2nF3Glf7/XFZKuwgAjm/YCJ0Q7rGcEspz7qidU18/2sY2KpyP1+wOBRo8xzc+naEnkpsb4Xuo0tvGDs3J7FOQ6Dnef//1P//++r/v964de6lg+N7LMyc2LiDf1Xfbl44LSBXav7f2J1/wes7v+wP97/T/WNDJW1OQdUi6rfyBij+eRxmvdPhZ30f5LeME3zwhOkxT41NcSxGPN+h38fNsRnDm2M5sniNC+2D/Oe88rSnNZxzHv+SnNS1lxUE803+c4zrU2154HsYAc72MEOdrCDHexgBzv854WfSP8vKy8ns8A9A/DD5gBc9/Bptv7fT/6883/7c822/t+5P59j6//ZwQ52sIMd7GAHO9jBDv+b4Sf6/3+Wkf7/Ee79r7Lv/e17f/ve3773t4Md7GAHO9jBDnawgx3scN7hX37/n+Gy9JnFOT/8+X/X/X+ql77/cad0m/X8vmthgksr3aPvf3F6VmE6uvS5ObM9+qY1woye3ZSSUkvvTfGbSiPWsz4d+TyPXroVx2yjbazRjMud4rB0bausj2voWs9ha/0VlevP+q6AR0euhtHwc+czsoqWtpU3SxuP/LCc/HhppJMHlnny0Ds8W8/Z/y628n2E1IDq5iaqm1upbm6iujmI83+PoHYN1/JHxs9JPVxz6Zr5axtU7Hzg1u3/vjmLgeZ9innPPDRl1qZ7P1j+eb3jX+y5+Lvq5mKqm7Oobo6jujmR85978j/ndf5zJec7R1bdnJfRC/K0G7XRGB+9oHC93xEBw2ED2Eh+FvljTuas8zZr+zIHgR3AqtNZGXGRex5nOSzHdmJhCWwTeuZ10vr5n9tZyPLVmDXH08//PE95/8q5np2pIX7newYlkwZmwTFwLfQ/94P9g70zgY+iuuP47OaOgEmAAOEwQjgEREBEFMQgICig4VABQxMgIeFICCFcChU8UVFpa5VSrbSiVastKLa0VsV60dYq9SpaVLRqaUsr3mjt8d3//nZ2djMbglB7ZfJ5+e677zfvmvcKo/M/S4fFzgHtxH3vPFDb08JzQYVwLyyDGxF+80J7J2d8rrmhvcNJsxGkR0gN1iFuQvwU4Z0z2oU8a2R47qgIxs8fPT/Sfw6p1enhs116w9EIvzmlvajHzyt1GEV+jWr8/FLx6Ogc02dN3+k0PU1P09P0ND1NT9Pzf/h8QeN/Bqe2/f+Qx//ndHDcs+y3+Iz/uxcwHvGO/83rRGN/mdW4XWP/mHF/VgPj+qKQ/UMY1+c=
*/