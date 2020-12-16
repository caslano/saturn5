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
bfloxDwmv7nLPXp2JD9Nvkc78lON8RoSTSOuz36X/KTq/DT6fu64PtVhez7cr09hqss9X6ff5Hu+oz4MuT7OaNz78dsu+cnV+WnS/MDRj/NaSl5iDmfOeURhmss8QuejUfMIlX67SPrNdPqOhB3ld0k3X6fbpHmGcxzDQvouw5h9n2LTv5VxvL59EXtfoNt+u6Z/ayX2PkW3/XBu+wKbvu8t9r5Gt/18bvsI3fcLfk+dt35t9IiKDWMHXXXFbc3nrw0/eLbbfke3fZ9u+wjd9gW67e903296vPa5NnV/aux9t+77Gq39XLJeKP2x1r6fS/T/m7wZBsUekctpQG6ZyFWKHHaRwzQg922Ru0rksGu5vAbkDovcxyL3iU0uvwG5d0TuXZF7zyZX2IDcByJ3SOT+Zt/n5yYn+vlNBmAQBqH+7kcDcp9Jep9Lel/Y0qtxl1MDqoKk57Wlt7UBuUmS3nhJD7uWq21ArqXIpYscdi23twG5XJHrKXLYtdz+BuSeELknRe4pm9zBBuQeFLmHRO7HNrlDDcjtEblHRe4xLcdvlpscdpG7R+Tuhbr/NSB3u8j9SOS22/tfA3I7RW6XyN1p738NyP1C5H4pcgfs/a8BuWdF7jmRe97e/xqQe0HkXhS5n9v7XwNy14vcJpHDHu1/DcjdJHI3iBz2aP9rQG6JyC0SOezR/teA3BUit1rksEf7XwNy14lcjchhj/a/BuTmi1ypyGGP9r8G5C4XuUtFDnu0/zUgN0PkzhY57NH+14Bcjsi1Fbkce/9rQG6IyA0SOezR/jfbXW6KyJ0pctij/a8BuWyRayVy2fb+14DcKSLXV+SwR/tfA3IXitz5Ioc92v8akOsicp1EDnu0/zUgN0LkhsGg2GsboZfDWEH5MXmYiVd6jQWYWLo69kyydDtcKroLckTHADo8OPt/bHo8/hd0eHxT9Xcci+6Opu69TjiLMF9x7/XB6m+u7o7/1H7sr2sv9nr6ei1mH+YQJusqrzEIU4hZi9mKeRrzJsZYx7iAGY0pxqzD7MLswxzCZPABoVzMNEw1ZjvmWcwhTMa38cNMw6zAbMbswRzEmB8c6owZiyn+TnzPd/wX/8V/8V/8F//Ff/Ff/Bf/xX/xX/zXuN+/c/9/Ma+iK6q+us5/c9/DQxkRvUpmlAXzFy1evqigvGLxHELwrk2dEfgsFX0Xomf9admb317K2Q5TkGGtkXhQfTFi1ITTpxXMWjoHXWVloj/qAvzRLTS/KqpbSMK3t+lWR0brVnf6swbJ/wtKFol/vs3f/T1+jkOn0wVKvxR5qKfXnHTFTfSm4EZassdCys33g+vrU6ogzlxHuecsrlheVFFsuJZbwreJWa4JNv9MY1Las9hnkO4O8hkKB7zhoI88TU77KmXW5aujP3+rT/TIRGLCFCFf6Cjf3JKqgj5uZZOwHazvCWhdilK2qL8qm/kt+/4+q2y+TMqWYJUtW/ym4bfTLLcRCISDwbAvbHzlsi/VOhSd13Zrgl5jV7/+UvaaemVfhOnrVn4Jf4pr+cVflX+bj3QSpPzdKb8/wSq/+E3Dr1aVPzQX38Rm4UDK8S7/MCl/huwhH24Bd9YmkT9Yr/x8Q6GgvGj2fFS9xWjj6REdZkpuiDGIv1I3EpePMBEZ4lJiUj86zHDXPi/+Vv0lkEe/1F/vaPuJ+NXid79Zfz7aT8eAYdbrCtx2Ybab7kmh3qHRgYRwUkDJHWvdis5JcZMyNWI8+XWgvg6+uRnWOrKuc6XXjg4ndV1Sv81J+FS3Nif+WY0eJ0sa0W5OlTLUyr76kyWmk6QM+fXKIB3HvRwik+NWDvFP1G1hhrJ3Oq7livSH12QjWXeJqRs=
*/