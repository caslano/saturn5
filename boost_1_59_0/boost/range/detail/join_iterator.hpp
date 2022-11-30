// Boost.Range library
//
//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Acknowledgements:
// aschoedl contributed an improvement to the determination
// of the Reference type parameter.
//
// Leonid Gershanovich reported Trac ticket 7376 about the dereference operator
// requiring identical reference types due to using the ternary if.
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_DETAIL_JOIN_ITERATOR_HPP_INCLUDED
#define BOOST_RANGE_DETAIL_JOIN_ITERATOR_HPP_INCLUDED

#include <iterator>
#include <boost/assert.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/detail/demote_iterator_traversal_tag.hpp>
#include <boost/range/value_type.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/next_prior.hpp>

namespace boost
{
    namespace range_detail
    {

template<typename Iterator1, typename Iterator2>
struct join_iterator_link
{
public:
    join_iterator_link(Iterator1 last1, Iterator2 first2)
        :    last1(last1)
        ,    first2(first2)
    {
    }

    Iterator1 last1;
    Iterator2 first2;

private:
    join_iterator_link() /* = delete */ ;
};

class join_iterator_begin_tag {};
class join_iterator_end_tag {};

template<typename Iterator1
       , typename Iterator2
       , typename Reference
>
class join_iterator_union
{
public:
    typedef Iterator1 iterator1_t;
    typedef Iterator2 iterator2_t;

    join_iterator_union() {}
    join_iterator_union(unsigned int /*selected*/, const iterator1_t& it1, const iterator2_t& it2) : m_it1(it1), m_it2(it2) {}

    iterator1_t& it1() { return m_it1; }
    const iterator1_t& it1() const { return m_it1; }

    iterator2_t& it2() { return m_it2; }
    const iterator2_t& it2() const { return m_it2; }

    Reference dereference(unsigned int selected) const
    {
        if (selected)
            return *m_it2;
        return *m_it1;
    }

    bool equal(const join_iterator_union& other, unsigned int selected) const
    {
        return selected
            ? m_it2 == other.m_it2
            : m_it1 == other.m_it1;
    }

private:
    iterator1_t m_it1;
    iterator2_t m_it2;
};

template<class Iterator, class Reference>
class join_iterator_union<Iterator, Iterator, Reference>
{
public:
    typedef Iterator iterator1_t;
    typedef Iterator iterator2_t;

    join_iterator_union() {}

    join_iterator_union(unsigned int selected, const iterator1_t& it1, const iterator2_t& it2)
        : m_it(selected ? it2 : it1)
    {
    }

    iterator1_t& it1() { return m_it; }
    const iterator1_t& it1() const { return m_it; }

    iterator2_t& it2() { return m_it; }
    const iterator2_t& it2() const { return m_it; }

    Reference dereference(unsigned int) const
    {
        return *m_it;
    }

    bool equal(const join_iterator_union& other,
               unsigned int /*selected*/) const
    {
        return m_it == other.m_it;
    }

private:
    iterator1_t m_it;
};

template<typename Iterator1
       , typename Iterator2
       , typename ValueType = typename iterator_value<Iterator1>::type
       // find least demanding, commonly supported reference type, in the order &, const&, and by-value:
       , typename Reference = typename mpl::if_c<
                !is_reference<typename iterator_reference<Iterator1>::type>::value
             || !is_reference<typename iterator_reference<Iterator2>::type>::value,
                        typename remove_const<
                            typename remove_reference<
                                typename iterator_reference<Iterator1>::type
                            >::type
                        >::type,
                        typename mpl::if_c<
                            is_const<
                                typename remove_reference<
                                    typename iterator_reference<Iterator1>::type
                                >::type
                            >::value
                            || is_const<
                                typename remove_reference<
                                    typename iterator_reference<Iterator2>::type
                                >::type
                            >::value,
                            typename add_reference<
                                typename add_const<
                                    typename remove_reference<
                                        typename iterator_reference<Iterator1>::type
                                    >::type
                                >::type
                            >::type,
                            typename iterator_reference<Iterator1>::type
                        >::type
                    >::type
       , typename Traversal = typename demote_iterator_traversal_tag<
                                  typename iterator_traversal<Iterator1>::type
                                , typename iterator_traversal<Iterator2>::type>::type
>
class join_iterator
    : public iterator_facade<join_iterator<Iterator1,Iterator2,ValueType,Reference,Traversal>, ValueType, Traversal, Reference>
{
    typedef join_iterator_link<Iterator1, Iterator2> link_t;
    typedef join_iterator_union<Iterator1, Iterator2, Reference> iterator_union;
public:
    typedef Iterator1 iterator1_t;
    typedef Iterator2 iterator2_t;

    join_iterator()
        : m_section(0u)
        , m_it(0u, iterator1_t(), iterator2_t())
        , m_link(link_t(iterator1_t(), iterator2_t()))
    {}

    join_iterator(unsigned int section, Iterator1 current1, Iterator1 last1, Iterator2 first2, Iterator2 current2)
        : m_section(section)
        , m_it(section, current1, current2)
        , m_link(link_t(last1, first2))
        {
        }

    template<typename Range1, typename Range2>
    join_iterator(Range1& r1, Range2& r2, join_iterator_begin_tag)
        : m_section(boost::empty(r1) ? 1u : 0u)
        , m_it(boost::empty(r1) ? 1u : 0u, boost::begin(r1), boost::begin(r2))
        , m_link(link_t(boost::end(r1), boost::begin(r2)))
    {
    }

    template<typename Range1, typename Range2>
    join_iterator(const Range1& r1, const Range2& r2, join_iterator_begin_tag)
        : m_section(boost::empty(r1) ? 1u : 0u)
        , m_it(boost::empty(r1) ? 1u : 0u, boost::const_begin(r1), boost::const_begin(r2))
        , m_link(link_t(boost::const_end(r1), boost::const_begin(r2)))
    {
    }

    template<typename Range1, typename Range2>
    join_iterator(Range1& r1, Range2& r2, join_iterator_end_tag)
        : m_section(1u)
        , m_it(1u, boost::end(r1), boost::end(r2))
        , m_link(link_t(boost::end(r1), boost::begin(r2)))
    {
    }

    template<typename Range1, typename Range2>
    join_iterator(const Range1& r1, const Range2& r2, join_iterator_end_tag)
        : m_section(1u)
        , m_it(1u, boost::const_end(r1), boost::const_end(r2))
        , m_link(link_t(boost::const_end(r1), boost::const_begin(r2)))
    {
    }

private:
    void increment()
    {
        if (m_section)
            ++m_it.it2();
        else
        {
            ++m_it.it1();
            if (m_it.it1() == m_link.last1)
            {
                m_it.it2() = m_link.first2;
                m_section = 1u;
            }
        }
    }

    void decrement()
    {
        if (m_section)
        {
            if (m_it.it2() == m_link.first2)
            {
                m_it.it1() = boost::prior(m_link.last1);
                m_section = 0u;
            }
            else
                --m_it.it2();
        }
        else
            --m_it.it1();
    }

    typename join_iterator::reference dereference() const
    {
        return m_it.dereference(m_section);
    }

    bool equal(const join_iterator& other) const
    {
        return m_section == other.m_section
            && m_it.equal(other.m_it, m_section);
    }

    void advance(typename join_iterator::difference_type offset)
    {
        if (m_section)
            advance_from_range2(offset);
        else
            advance_from_range1(offset);
    }

    typename join_iterator::difference_type distance_to(const join_iterator& other) const
    {
        typename join_iterator::difference_type result;
        if (m_section)
        {
            if (other.m_section)
                result = other.m_it.it2() - m_it.it2();
            else
            {
                result = (m_link.first2 - m_it.it2())
                       + (other.m_it.it1() - m_link.last1);

                BOOST_ASSERT( result <= 0 );
            }
        }
        else
        {
            if (other.m_section)
            {
                result = (m_link.last1 - m_it.it1())
                       + (other.m_it.it2() - m_link.first2);
            }
            else
                result = other.m_it.it1() - m_it.it1();
        }
        return result;
    }

    void advance_from_range2(typename join_iterator::difference_type offset)
    {
        typedef typename join_iterator::difference_type difference_t;
        BOOST_ASSERT( m_section == 1u );
        if (offset < 0)
        {
            difference_t r2_dist = m_link.first2 - m_it.it2();
            BOOST_ASSERT( r2_dist <= 0 );
            if (offset >= r2_dist)
                std::advance(m_it.it2(), offset);
            else
            {
                difference_t r1_dist = offset - r2_dist;
                BOOST_ASSERT( r1_dist <= 0 );
                m_it.it1() = m_link.last1 + r1_dist;
                m_section = 0u;
            }
        }
        else
            std::advance(m_it.it2(), offset);
    }

    void advance_from_range1(typename join_iterator::difference_type offset)
    {
        typedef typename join_iterator::difference_type difference_t;
        BOOST_ASSERT( m_section == 0u );
        if (offset > 0)
        {
            difference_t r1_dist = m_link.last1 - m_it.it1();
            BOOST_ASSERT( r1_dist >= 0 );
            if (offset < r1_dist)
                std::advance(m_it.it1(), offset);
            else
            {
                difference_t r2_dist = offset - r1_dist;
                BOOST_ASSERT( r2_dist >= 0 );
                m_it.it2() = m_link.first2 + r2_dist;
                m_section = 1u;
            }
        }
        else
            std::advance(m_it.it1(), offset);
    }

    unsigned int m_section;
    iterator_union m_it;
    link_t m_link;

    friend class ::boost::iterator_core_access;
};

    } // namespace range_detail

} // namespace boost

#endif // include guard

/* join_iterator.hpp
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
*/