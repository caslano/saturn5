// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_CONCATENATE_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_CONCATENATE_ITERATOR_HPP

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>


namespace boost { namespace geometry
{



template
<
    typename Iterator1,
    typename Iterator2,
    typename Value,
    typename Reference = Value&
>
class concatenate_iterator
    : public boost::iterator_facade
        <
            concatenate_iterator<Iterator1, Iterator2, Value, Reference>,
            Value,
            boost::bidirectional_traversal_tag,
            Reference
        >
{
private:
    Iterator1 m_it1, m_end1;
    Iterator2 m_begin2, m_it2;

public:
    typedef Iterator1 first_iterator_type;
    typedef Iterator2 second_iterator_type;

    // default constructor
    concatenate_iterator() {}

    // for begin
    concatenate_iterator(Iterator1 it1, Iterator1 end1,
                         Iterator2 begin2, Iterator2 it2)
        : m_it1(it1), m_end1(end1), m_begin2(begin2), m_it2(it2)
    {}

    // for end
    concatenate_iterator(Iterator1 end1, Iterator2 begin2, Iterator2 end2)
        : m_it1(end1), m_end1(end1), m_begin2(begin2), m_it2(end2)
    {}

    template
    <
        typename OtherIt1,
        typename OtherIt2,
        typename OtherValue,
        typename OtherReference
    >
    concatenate_iterator(concatenate_iterator
                         <
                             OtherIt1,
                             OtherIt2,
                             OtherValue,
                             OtherReference
                         > const& other)
        : m_it1(other.m_it1)
        , m_end1(other.m_end1)
        , m_begin2(other.m_begin2)
        , m_it2(other.m_it2)
    {
        static const bool are_conv
            = boost::is_convertible<OtherIt1, Iterator1>::value
           && boost::is_convertible<OtherIt2, Iterator2>::value;

        BOOST_MPL_ASSERT_MSG((are_conv),
                             NOT_CONVERTIBLE,
                             (types<OtherIt1, OtherIt2>));
    }

private:
    friend class boost::iterator_core_access;

    template <typename It1, typename It2, typename V, typename R>
    friend class concatenate_iterator;

    inline Reference dereference() const
    {
        if ( m_it1 == m_end1 )
        {
            return *m_it2;
        }
        return *m_it1;
    }

    template
    <
        typename OtherIt1,
        typename OtherIt2,
        typename OtherValue,
        typename OtherReference
    >
    inline bool equal(concatenate_iterator
                      <
                          OtherIt1,
                          OtherIt2,
                          OtherValue,
                          OtherReference
                      > const& other) const
    {
        return m_it1 == other.m_it1 && m_it2 == other.m_it2;
    }

    inline void increment()
    {
        if ( m_it1 == m_end1 )
        {
            ++m_it2;
        }
        else
        {
            ++m_it1;
        }
    }

    inline void decrement()
    {
        if ( m_it2 == m_begin2 )
        {
            --m_it1;
        }
        else
        {
            --m_it2;
        }
    }
};



}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_CONCATENATE_ITERATOR_HPP

/* concatenate_iterator.hpp
hql3xC7AL/bSEDwLWXWzAOCVIdSiUjcShQY5V+uJruv/bjrB+AYboxcT/jsKmkgObdaq7HZh+iDcQd+Uar/C4DXxGkhY4Z6L2DFGtGB95OdXEeG2ICj0Rrb9WwXjXlYLYCBQSOYQ6TFSyrg16IREOll+5zlYxgDbEwVUi69Kj7bJQ8x7R2OqlhZQk7YsQ0e/vWah9nuwKHI8LL85jwEUKd3fN848942kI6Vz8d/mGqmirxb6tOG8BWD2QRUSRpur52UoZJ3S+mKfNT1pE23wxsydx2fUliZiqHzq3V2ORMo/+YK5QV+IskpBxLKwV2eKi/cTgG2hFAAowWH/vzqKhsyd7wQLk69pchUzPpepVI6x9IOXVcpi0bqGZO63hDQ8W7WqRlIXleuwuOXBa5tAlAs5e3aVRMyEhlb4r9L1lV4wMyqYuTFQ9iuNeiNGVx4GpXIJAxjQC6zyBVJo90wkDk86g2Zz4em3HgLo/MQ+I2f9rVMUM/vWeZMxiIjG1oZH54IYmVWbCoky+Wg2+oxwveQU6VWzpWB1PONfvEgXjfuj3ewM+P7yo8sywg==
*/