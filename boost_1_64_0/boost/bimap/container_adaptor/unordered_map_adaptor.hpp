// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/unordered_map_adaptor.hpp
/// \brief Container adaptor to easily build a std::unordered_map signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MAP_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MAP_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/unordered_associative_container_adaptor.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/call_traits.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::unordered_map signature compatible container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,
    class LocalIterator,
    class ConstLocalIterator,

    class IteratorToBaseConverter        = ::boost::mpl::na,
    class IteratorFromBaseConverter      = ::boost::mpl::na,
    class LocalIteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter           = ::boost::mpl::na,
    class ValueFromBaseConverter         = ::boost::mpl::na,
    class KeyToBaseConverter             = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class unordered_map_adaptor :

    public ::boost::bimaps::container_adaptor::
                unordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, LocalIterator, ConstLocalIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type::first_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        LocalIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses
    >
{

    typedef ::boost::bimaps::container_adaptor::
                unordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, LocalIterator, ConstLocalIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type::first_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        LocalIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // MetaData -------------------------------------------------------------

    public:

    typedef BOOST_DEDUCED_TYPENAME Iterator::value_type::second_type data_type;
    typedef data_type mapped_type;

    // Access -----------------------------------------------------------------

    public:

    explicit unordered_map_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef unordered_map_adaptor unordered_map_adaptor_;

    // Interface --------------------------------------------------------------

    public:

    template< class CompatibleKey >
    data_type& operator[](const CompatibleKey & k)
    {
        return this->base()
            [this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k)];
    }

    template< class CompatibleKey >
    data_type& at(const CompatibleKey & k)
    {
        return this->base().
            at(this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k));
    }

    template< class CompatibleKey >
    const data_type& at(const CompatibleKey & k) const
    {
        return this->base().
            at(this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k));
    }

};



} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MAP_ADAPTOR_HPP


/* unordered_map_adaptor.hpp
bbVhaof0vp9DGzVN7dhctVlDoNpA+71ZbdgO2Ym0WYUHqBM1PucbLU1wvtFKn/ONVnvPN5K5tT79i3Wx/Qtrq95I0fcfaquGqi6O1p6JzmqrOuosKYd3TL26WFLNrV6zK8oXJmwjZK9jg3VNZhKeKSX9hGdKSd9tG0/WfqFBjVi3jU//0QnSv8gn/SfHpn/T923/hvXZl5fY+uPWP2+Y2erNHrkf/+a1P17396/8b3/f1tfR+BWma10iCRaogOPVyhD7wDR4XOQcqcg4T+NW7Jmd3jD09MdcD3g8RDgnwiFwEBwKB8PT4RB4FjwFlsJC+GU4El4OT4fXwdHwRngG3ADPhPfCcfAn8Cz4KBwPfw8nab1uKsyF58PesASOhdPhTDgT1sEyuBrOgrfDKvgwHA9/ByfAt+Aw+CdYBzOJ9yKYAxfDVnAp7ACXwQJ4AewNL4QD4Qql38rIOEPjLNKPtMZdpd/rGDkKvgk7w7eVnr+HZ8C9cCF8H14CP4DfhR/CO+HpNLDPwI+R/wbuh6/BT5Q+n8J34F9hS/z8OzwW2sYhmALvgi3gkzAHPg3bwQ9gR9iS+BwNT4QF8BTYFU6C3eE02AtOh73hN+Fx8GbYF26HA+EbcAj8FJ4K/w4LYack0ht2g6fBPnA4HAhHwMlwJJwG02AJTIfTIXFbuRzug6vgHvht+CG8FZI+Og9N/WGY77Mf4GzMNYdFMBeOh+3hBI/9HbKf6WP/DMyFeCZMhmNgBhwbse/218h7n3q0Wuv5V8Gu8GqVg2tUf76qevM1WA5vgHPgjXAJ3Kl685LKxctwM/wtfAjugo/AV+DTcD18Hd4KkwjD7TAH3gE7wbvgMfBueBy8R/XpAdWnB+EF8CH4Ffgz+A34KHwcPgGfhE/CvfCXqkfPwO7wWXgifA6eDF+AI+G1sBxeByvgK1Dtl97Z9DN82q9V2s9xMewIL4Ersb+zOKNR66RNZ9kd3PelTWfZRb8z3U8ZazUtw+mLGIuoRKxEbJjWtP7X9DQ9TU/T0/Q0PU3P/87zBa3/hxboD3n9P7S+396zvr9GY66n9O3jw4glDCQ2fZyu9X3zt6RM3/0fXaA5yip3jlJmc6Pnipn8fmehvntcrPVs7/f4u8zMOmcyIbLvXfUt5xZCNT2rcd9CR+Ygjy7QHGRV7FltY3V2wAhES3FZKG77Y+M2q7a8HC2F1RM/hfUJM3+s4huxnyt5wHnf5AF9+2LhRzT+7LTFceEfqvC/qfCneMrZBZjN+iQ2/BXldX1LptfUlJRNr6MQJMon2Utp9HpTXLq6Z7gtTVJ4ZCkkvRCz+X7hqp5eVZ44TLKT/LnDpLRiPq9+Wi3HbN/6YSqZUV1SNb+spHxpTeJw9T1MabXRJ1wrMFvoEy4tYiYMU+FhCtOglPr592XMFvmFad70ioW+dUP3fh5k/i1OEKanUvzTqdQnTPquPGE6lR6mdCpN9Q9TjU+Y9G14wjDVHKYwfeATposwu9InTCrkCcO08hDDFKl7a9Lqh2klZtf6hCnuW3DfcK09xHBF0io/vX64VmF2g0+49A1zwjBtOMQwRdJqq0+YLsbspgRh0qJ94nfvIYYrklZjM+qH6xLMbvMJl3ZBJQzTtkMMU6RvUqONFffqrNANiEsxuyMuTNXlSzzndYRfOAqLzB7trlu/a/Kr7ZzV6Fp/uJXTPkHZydPeI84bMvmNTpG3P6M4R/ozSZ+GzNTSSzjC7c+88zn7M+FzOSwecWevWDhjytOII+rvQbk8VJ4+jU2jhXF9BP/2XPZwLcc9P8e1pPVmM3NQ+1a8bX4ualjSGTGu2zFlcZ72s1ytfttKxOpQWawfp37qX8THx82Xl8w=
*/