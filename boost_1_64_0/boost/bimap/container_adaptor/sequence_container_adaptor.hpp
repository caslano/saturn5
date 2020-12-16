// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/sequence_container_adaptor.hpp
/// \brief Container adaptor to build a type that is compliant to the concept of a weak associative container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_SEQUENCE_CONTAINER_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_SEQUENCE_CONTAINER_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <utility>

#include <boost/mpl/if.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/bimap/container_adaptor/detail/identity_converters.hpp>
#include <boost/bimap/container_adaptor/container_adaptor.hpp>
#include <boost/call_traits.hpp>
#include <boost/operators.hpp>

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
    class FunctorsFromDerivedClasses
>
struct sequence_container_adaptor_base
{
    typedef container_adaptor
    <
        Base, Iterator, ConstIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,

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

/// \brief Container adaptor to build a type that is compliant to the concept of a sequence container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,

    class ReverseIterator,
    class ConstReverseIterator,

    class IteratorToBaseConverter           = ::boost::mpl::na,
    class IteratorFromBaseConverter         = ::boost::mpl::na,
    class ReverseIteratorFromBaseConverter  = ::boost::mpl::na,
    class ValueToBaseConverter              = ::boost::mpl::na,
    class ValueFromBaseConverter            = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class sequence_container_adaptor :

    public sequence_container_adaptor_base
    <
        Base, Iterator, ConstIterator,
        ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses

    >::type,

    ::boost::totally_ordered
    <
        sequence_container_adaptor
        <
            Base, Iterator, ConstIterator,
            ReverseIterator, ConstReverseIterator,
            IteratorToBaseConverter, IteratorFromBaseConverter,
            ReverseIteratorFromBaseConverter,
            ValueToBaseConverter, ValueFromBaseConverter,
            FunctorsFromDerivedClasses
        >
    >
{
    typedef BOOST_DEDUCED_TYPENAME sequence_container_adaptor_base
    <
        Base, Iterator, ConstIterator,
        ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses

    >::type base_;

    // MetaData -------------------------------------------------------------

    public:

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

    explicit sequence_container_adaptor(Base & c)
        : base_(c) {}

    protected:


    typedef sequence_container_adaptor sequence_container_adaptor_;

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

    void resize(BOOST_DEDUCED_TYPENAME base_::size_type n,
                BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                    BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x =
                        BOOST_DEDUCED_TYPENAME base_::value_type())
    {
        this->base().resize(n,
            this->template functor<BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x)
        );
    }

    BOOST_DEDUCED_TYPENAME base_::reference front()
    {
        return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::value_from_base>()
        (
            this->base().front()
        );
    }

    BOOST_DEDUCED_TYPENAME base_::reference back()
    {
        return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::value_from_base>()
        (
            this->base().back()
        );
    }

    BOOST_DEDUCED_TYPENAME base_::const_reference front() const
    {
        return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::value_from_base>()
        (
            this->base().front()
        );
    }

    BOOST_DEDUCED_TYPENAME base_::const_reference back() const
    {
        return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::value_from_base>()
        (
            this->base().back()
        );
    }

    void push_front(
        BOOST_DEDUCED_TYPENAME ::boost::call_traits<
            BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x)
    {
        this->base().push_front(
            this->template functor<BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x));
    }

    void pop_front()
    {
        this->base().pop_front();
    }

    void push_back(
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< 
            BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x)
    {
        this->base().push_back(
            this->template functor<BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x));
    }

    void pop_back()
    {
        this->base().pop_back();
    }

    std::pair<BOOST_DEDUCED_TYPENAME base_::iterator,bool>
    insert(BOOST_DEDUCED_TYPENAME base_::iterator position,
           BOOST_DEDUCED_TYPENAME ::boost::call_traits< 
                BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x)
    {
        std::pair< BOOST_DEDUCED_TYPENAME Base::iterator, bool > r(
            this->base().insert(
                this->template functor<
                    BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(position),
                this->template functor<
                    BOOST_DEDUCED_TYPENAME base_::value_to_base   >()(x)
            )
        );

        return std::pair<BOOST_DEDUCED_TYPENAME base_::iterator, bool>(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(r.first),
            r.second
        );
    }

    void insert(BOOST_DEDUCED_TYPENAME base_::iterator position,
                BOOST_DEDUCED_TYPENAME base_::size_type m,
                BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                    BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x)
    {
        this->base().insert(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(position),
            m,
            this->template functor<BOOST_DEDUCED_TYPENAME base_::value_to_base   >()(x)
        );
    }

    template< class InputIterator >
    void insert(BOOST_DEDUCED_TYPENAME base_::iterator position,
                InputIterator first, InputIterator last)
    {
        // This is the same problem found in the insert function 
        // of container_adaptor
        // For now, do the simple thing. This can be optimized

        for( ; first != last ; ++first )
        {
            this->base().insert(
                this->template functor<
                    BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()( position ),
                this->template functor<
                    BOOST_DEDUCED_TYPENAME base_::value_to_base   >()( *first )
            );
        }
    }

    // Totally ordered implementation

    bool operator==(const sequence_container_adaptor & c) const
    {
        return ( this->base() == c.base() );
    }

    bool operator<(const sequence_container_adaptor & c) const
    {
        return ( this->base() < c.base() );
    }
};

} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_SEQUENCE_CONTAINER_ADAPTOR_HPP

/* sequence_container_adaptor.hpp
xI7ro2N6n/F715Y6JzruToT9wfpp0BMzfd00sAQIXYxglxzFxUPpIPOaA3mog90XV7e0ZDYh0t0TMhNJi+c6hszMnV29uEZp4adfi5fROZC+B5lWnjRw50AIG2pu2Nz0wj/Uw+HRHIjUCIPScKTS8O6mOZCDmgNZtMTUH0pafOxfe63edOyJ//jLuN+lNM2BNHYOJOtzzoFE7PdtwH6u7LeR/bawteSVTXMoTXMo/+I5lLZTOG9lStM8StPT9DQ9TU/T0/T8Nz1f0Pi/prb68Kz/j/WM/+mG2LMU0RExE/Gd0Ng3yx371nBqX11k7X+9jf9n1HjuepPZbu6d3eeafJTdYzfV7oZb6t4DPNH0CrnfI0Nj4oj9Lrpvltu7TZ7imU+YP2uW/GsDi0x/gskrXfv5Mh97f20ruNr0MySPdX+npULNXP659+9+yfTPcHI5pzCUt7cxkDgrNGZG3J7T+Lu819s8hdJKY2/SAzXSI+b+PYtfzB2Du5Mce76lfLkScXsBeR6XLyWzaiweX8NWwEHi5gtm4/LlI5NXefNFeSCzyoOxyN83+SLfPGgF95n+DOVBxH6+m8ZTspXGCfJkgumnxZu3sJFuPDPc/Eg1vQqnE/mRGqpr6M9FFCPmIcaRL1UHcd8jaUWaK600z+HNl6K4fPHOFeWnOPZcELm/B3FH6DzN7Ei+cFf+9KqFqjWJ6ozME2Kl90MmP9cZgV9+9eYB059AONoozyJutE+Yxu+afrP4cu7eo/mE6U90hvE/vqxPOIxl3XuneKXurL9J6fcVxF2kX2FOvfRT6XYSlW/sxKbhl0y+wDk1QRqeb/pznFPcO5TlRgNp+LjpZ3vLpZt+1aZXxdxRIGHZHH8Yy6Y739b03dYX9t3WHTZvt2v0af3mfv316muab7/hw1s67040v3j45gv/Xd956Q4pvVPpF/jcIUU5XtkNHg/7wAHwNDgQToQnwmlwEJwOT4Az4UnwPZ1Ru0Puf0vuZ8BJcj9b7reGg2EunALbyN12cD7Mgytge3gF7ACvhB3du/3URsILfO72G4K5TvBU+VcIT4anwbFwODwXjoCT4Ug3/Go34E0+4c+XuwXweNgVjofdlD69lR494CJ4DFwJe8KrpF8cbNz3drHzjv/+Ocd/5Xzj551r/E+dZ/wi5xg3Mr/4U8ROxP6mucamp+k5bM+//Pw/jf+ryusqD9f5f8M6OO696kXaA9AV0RzRAbE3tIiWbn3ymrnly0pCAZhJ6KoXhcebb7XU+na0Py7z2e6969OzDnyuf2T8gHvhNWkn9s73TZqfWIdoibgG8Ud+bEuLC9v8mmVoecJWFtoe4Pb9XzHzi5w5uK3wyo2OHjsLa2cqPmNc/Vy3v/+iyVdxP3fA7GwocHgWEuhoGhxtadCbe1PHZU9CXkb4R5CgzZJzj0hLDSZlHzEytVlSamqwWVrHSDqVkE5R98pc94rQ/Iv5OYc0OSu7sWOxcFoSf6kNctWIX1z6dqDPZwySvmJyK/o3mXHpW1c7D+16eZ8bjrfM7wmMpkSOCMxWegSc0UeE1LM88wh1y2rKw/mCM7J3cqCP80ftF/GzU9MPOHmaa4j4dQ63FicFWjtnBMo0DxFrNynV7PZ3eLqpHEw1u48HNpMG2xH7Ea0Cqc4yxDUI7bOQH3n18qWbysJ5pv+rwI/5vwPh4HcHxCrE1xEDydtm2GqfnVgUZ8XJGzFObOE0A/Qdm+G/5W9Kduvw74KxZ/U7yZFajyNctQERteyoWv+I2jWZrhreahwaVx+1F0RzIsq/mHkS8kfmJkPSHTVL9/DYX2XtzVS1M3jYFmbBNMravmb1y1roshCMJGhrZIfUytPYv0U=
*/