// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/vector_adaptor.hpp
/// \brief Container adaptor to easily build a std::vector signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_VECTOR_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_VECTOR_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/sequence_container_adaptor.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/vector.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::vector signature compatible container.

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
class vector_adaptor :

    public ::boost::bimaps::container_adaptor::sequence_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses
    >
{

    typedef ::boost::bimaps::container_adaptor::sequence_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // Access -----------------------------------------------------------------

    public:

    vector_adaptor() {}

    explicit vector_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef vector_adaptor vector_adaptor_;

    // Interface --------------------------------------------------------------

    public:

    BOOST_DEDUCED_TYPENAME base_::size_type capacity() const
    {
        return this->base().capacity();
    }

    void reserve(BOOST_DEDUCED_TYPENAME base_::size_type m)
    {
        this->base().resize(m);
    }

    void resize(BOOST_DEDUCED_TYPENAME base_::size_type n,
                BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                    BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x =
                        BOOST_DEDUCED_TYPENAME base_::value_type())
    {
        this->base().resize(n,
            this->template functor<BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x)
        );
    }

    BOOST_DEDUCED_TYPENAME base_::const_reference
        operator[](BOOST_DEDUCED_TYPENAME base_::size_type n) const
    {
        return this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()(
            this->base().operator[](n)
        );
    }

    BOOST_DEDUCED_TYPENAME base_::const_reference
        at(BOOST_DEDUCED_TYPENAME base_::size_type n) const
    {
        return this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()(
            this->base().at(n)
        );
    }

    BOOST_DEDUCED_TYPENAME base_::reference
        operator[](BOOST_DEDUCED_TYPENAME base_::size_type n)
    {
        return this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()(
            this->base().operator[](n)
        );
    }

    BOOST_DEDUCED_TYPENAME base_::reference
        at(BOOST_DEDUCED_TYPENAME base_::size_type n)
    {
        return this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()(
            this->base().at(n)
        );
    }
};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_VECTOR_ADAPTOR_HPP



/* vector_adaptor.hpp
e+DJ8HE4GP4aDoHPwVPhTnga3AVHwD/BUfBdOBp+As+AGYT/TJgNx8B2cCzsAMfByqDT8L0PiMea7n9ouv/hEO5/2MXc3mdN83tNT9PT9DQ9Tc//wfMFjf8Z0B6e8f8/2tOf1Pj/Uo2pP0R0QryGGBQa/z9Xf/xvp9qV15XXLuQ7BO/YWvuuNbaW3V7uGPYBkz/q2Vsc/mJJe4tlvo87Ln7I5D90ctx7fBeWl5dxnGT0WwXZ6erez3u/yZ/R/eoRO7pfXWPlrWbmEZPPdt3owVgAO/Y9xMz5i6qJX4nFx3NPsMzy572HuLPZqTTT7j3AcWZXy2x2R3N/BlLX7KA4s2tltgtkZ5ElUiS+XZ8PmRtp+rvsHMHyxTVV7K/W/v5M02/OODzFndNoY2qT3fOIf5TH7EE7yir5f5e+ES9yfB93fqbUHecrTWLu27cg2jdNNe69ucqr6H28MhvNjzzdx0uaox6X5rqXt7PpKW11Ly9piBppqHmi9y3t2OMV9+1cob5Dez+N8ZfYEjM7no+fJ3KPjqxflkmCTXDICyE7V6RFymbBrpD8FpX1iJsL9Q0btzqb+fJAJ6dtQHnpKe+nWbxvNjPd0sJ2SF+TXxD4npMfdXdnSO0Ic3eM68/fkic7tyRHysR9L9qefB+/j4v6HVuO5M4wk09Cnm12mrvlKqByRVgtzUeZ/vK0yHckw14Kn6edp7p9tOk/mHIvYd8TOM65L+mvAX3zJb/G63u7aPg6sgvMv26fZuVlrJlbkhY5c6GFyYOBx/EjWiflvurODtRyFGdv3c9RvO80N6YyTu8eratxbuyUG/mprhvzF9WFw7Uds13NjW+lRepcssnvSevlzFH6MAP4G31vGanjcX7sRs23vVH8t8Iic3ehm+ZftjLX2i0bw01/sPstz9dNP9n1szDOzz2Beu2V+bUNc8ebW2tdv44zeYb7ndFV5vZRkteP3+g4v/YF4to7xasUnmNuV7t+fe1lfWupevA7kw8L5KlNb2vmn0h5gHx/l7L1YtLbAb96ZmeceNTasHswEr6iuPDtR829z5y2MYewsVdOdvel5jtXeb4lqXW/F7pup7kd7OQkB/NCash2WP0bHWzn5OPPs4GBwfT688eKa7eXdaa46k3X31pZCkS+jc4z/zsFXyAfewaet2+hz0F9hPmxPvlxdgZuDL4bMPtuPhyJe5hz5ZkWn9Ex8enriW+F6dfE6FPXXf26cu99+d95Ue9ltRXNLcw/JMzxefAa+6r76z76qHp7dneG/FsX49/d5t+DlkZV86vxL1KfFpv7S52OlO1c1f0sC8N9qesJZ4/AJSk2H+/60driM8jrvr5v/GonfafVP/z9Vt+YfJ9p9u6IsXeDR3+B6RfF6K+oN/efp7v108zMT9PectLYP/uM0y94eUrkG6Sppjc7Lep2jdtnSbX4PuhffrFfGeP/rZ540UDzWLsHY+Ir9X0wmq+1oaBEvwG3NF2e+msn31PW51q4WoXiZW38ZsyH5HF1zTWvtivkrtJhT6iOUEvfDYT7IFWecumG0drVcBizYvLkPPc78J3hd1/wNMKQsKyRPqtj0qfGE5cqa3MK+VVi+mVpea7eooXlJbXTq8vmV5WEg+LG+zcvht+5H9FfGoKcvpKdE3B/bnhd5WrEZQcQP0HcjJjYhnTO4Qwbfl+M+CniyqyweBRxo8xExHuuXtj+EEQ26ufp9/OIm+R+ocTTCLkjdTNjbv0QbkZskZ0hkmPWu/7jPVvI+oM66yv+GU4bSPqebO/SswMBWxN69WWtCVWXmTx/V+wa0SYk8X3HrfqOQH1HU9vmqllfxdS2o0Z/BLVwf4S+JO94/z7mTtn39jE=
*/