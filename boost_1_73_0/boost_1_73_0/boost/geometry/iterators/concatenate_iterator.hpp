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
U06g0mO+vHN8tvBc526Twkisy0DESEGg5XoeFo0VEGR7Mx5gpRM/kDljDWFmBAt9foclOxb5a3S7sITSkQy56/k08uqvEapZAPXa4w9utBgQqlUAdQQBsy0jL95BuK0CuI6wg4gnzgjbLoDqWtOI5THtGgVAx+5j4Lmx2SLciwK4E9eeRJsjAu0WAL2BCbIjY0GovQKoHmQyPDKK1bcAB4mQhFBb0hyrEJ9jAmDso4LTJQHPQsuiiH4EQTxEtpAn2K7FbTWNQSImfgd0G/UC/u+kHenldJXqKnmgUzmLNHy2SuWZPNCZvI/Y9XG41SJSkMmJ2Sh23ucEWUTv3Ld4BHZBYEVmcgGOz0D9SlBFRvJrKEbCMnCXBFdkJpcQN0T6GBBYkaEMpPC8iC1FIdUiQ7nizl1E7prAikwF8hIsnhrA3wiwyFp+k1bgxtkEbXtFs3ozlf69eDKA7wmwaDreVz0egd2qbbQA7JY79yKa3Q9FWRLBfQjtsMI+C8/FkwgJpu1UGN+83+SbDNKyRFrrRQUrMhTHZapICsnUjLJxVoUl6qvaaaYKZE2Fhel7qghEjRXwZ5+xCmQLp7zyRafZ8oBKgrkqwPpiygPsG7muDaktMGMv2XH7dNClDH1SAjLsFWuVaUEhNPSvmeJB
*/