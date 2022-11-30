//  Copyright 2014 Neil Groves
//
//  Copyright (c) 2010 Ilya Murav'jov
// 
//  Use, modification and distribution is subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Credits:
//  My (Neil's) first indexed adaptor was hindered by having the underlying
//  iterator return the same reference as the wrapped iterator. This meant that
//  to obtain the index one had to get to the index_iterator and call the
//  index() function on it. Ilya politely pointed out that this was useless in
//  a number of scenarios since one naturally hides the use of iterators in
//  good range-based code. Ilya provided a new interface (which has remained)
//  and a first implementation. Much of this original implementation has
//  been simplified and now supports more compilers and platforms.
//
#ifndef BOOST_RANGE_ADAPTOR_INDEXED_HPP_INCLUDED
#define BOOST_RANGE_ADAPTOR_INDEXED_HPP_INCLUDED

#include <boost/range/config.hpp>
#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/traversal.hpp>
#include <boost/range/size.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <boost/iterator/iterator_traits.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <boost/tuple/tuple.hpp>

namespace boost
{
    namespace adaptors
    {

struct indexed
{
    explicit indexed(std::ptrdiff_t x = 0)
        : val(x)
    {
    }
    std::ptrdiff_t val;
};

    } // namespace adaptors

    namespace range
    {

// Why yet another "pair" class:
// - std::pair can't store references
// - no need for typing for index type (default to "std::ptrdiff_t"); this is
// useful in BOOST_FOREACH() expressions that have pitfalls with commas
//   ( see http://www.boost.org/doc/libs/1_44_0/doc/html/foreach/pitfalls.html )
// - meaningful access functions index(), value()
template<class T, class Indexable = std::ptrdiff_t>
class index_value
    : public tuple<Indexable, T>
{
    typedef tuple<Indexable, T> base_t;

    template<int N>
    struct iv_types
    {
        typedef typename tuples::element<N, base_t>::type n_type;

        typedef typename tuples::access_traits<n_type>::non_const_type non_const_type;
        typedef typename tuples::access_traits<n_type>::const_type const_type;
    };

public:
    typedef typename iv_types<0>::non_const_type index_type;
    typedef typename iv_types<0>::const_type const_index_type;
    typedef typename iv_types<1>::non_const_type value_type;
    typedef typename iv_types<1>::const_type const_value_type;

    index_value()
    {
    }

    index_value(typename tuples::access_traits<Indexable>::parameter_type t0,
                typename tuples::access_traits<T>::parameter_type t1)
        : base_t(t0, t1)
    {
    }

    // member functions index(), value() (non-const and const)
    index_type index()
    {
        return boost::tuples::get<0>(*this);
    }

    const_index_type index() const
    {
        return boost::tuples::get<0>(*this);
    }

    value_type value()
    {
        return boost::tuples::get<1>(*this);
    }

    const_value_type value() const
    {
        return boost::tuples::get<1>(*this);
    }
};

    } // namespace range

namespace range_detail
{

template<typename Iter>
struct indexed_iterator_value_type
{
    typedef ::boost::range::index_value<
        typename iterator_reference<Iter>::type,
        typename iterator_difference<Iter>::type
    > type;
};

// Meta-function to get the traversal for the range and therefore iterator
// returned by the indexed adaptor for a specified iterator type.
//
// Random access -> Random access
// Bidirectional -> Forward
// Forward -> Forward
// SinglePass -> SinglePass
//
// The rationale for demoting a Bidirectional input to Forward is that the end
// iterator cannot cheaply have an index computed for it. Therefore I chose to
// demote to forward traversal. I can maintain the ability to traverse randomly
// when the input is Random Access since the index for the end iterator is cheap
// to compute.
template<typename Iter>
struct indexed_traversal
{
private:
    typedef typename iterator_traversal<Iter>::type wrapped_traversal;

public:

    typedef typename mpl::if_<
        is_convertible<wrapped_traversal, random_access_traversal_tag>,
        random_access_traversal_tag,
        typename mpl::if_<
            is_convertible<wrapped_traversal, bidirectional_traversal_tag>,
            forward_traversal_tag,
            wrapped_traversal
        >::type
    >::type type;
};

template<typename Iter>
class indexed_iterator
    : public iterator_facade<
            indexed_iterator<Iter>,
            typename indexed_iterator_value_type<Iter>::type,
            typename indexed_traversal<Iter>::type,
            typename indexed_iterator_value_type<Iter>::type,
            typename iterator_difference<Iter>::type
        >
{
public:
    typedef Iter wrapped;

private:
    typedef iterator_facade<
        indexed_iterator<wrapped>,
        typename indexed_iterator_value_type<wrapped>::type,
        typename indexed_traversal<wrapped>::type,
        typename indexed_iterator_value_type<wrapped>::type,
        typename iterator_difference<wrapped>::type
    > base_t;

public:
    typedef typename base_t::difference_type difference_type;
    typedef typename base_t::reference reference;
    typedef typename base_t::difference_type index_type;

    indexed_iterator()
        : m_it()
        , m_index()
    {
    }

    template<typename OtherWrapped>
    indexed_iterator(
        const indexed_iterator<OtherWrapped>& other,
        typename enable_if<is_convertible<OtherWrapped, wrapped> >::type* = 0
    )
        : m_it(other.get())
        , m_index(other.get_index())
    {
    }

    explicit indexed_iterator(wrapped it, index_type index)
        : m_it(it)
        , m_index(index)
    {
    }

    wrapped get() const
    {
        return m_it;
    }

    index_type get_index() const
    {
        return m_index;
    }

 private:
    friend class boost::iterator_core_access;

    reference dereference() const
    {
        return reference(m_index, *m_it);
    }

    bool equal(const indexed_iterator& other) const
    {
        return m_it == other.m_it;
    }

    void increment()
    {
        ++m_index;
        ++m_it;
    }

    void decrement()
    {
        BOOST_ASSERT_MSG(m_index > 0, "indexed Iterator out of bounds");
        --m_index;
        --m_it;
    }

    void advance(index_type n)
    {
        m_index += n;
        BOOST_ASSERT_MSG(m_index >= 0, "indexed Iterator out of bounds");
        m_it += n;
    }

    difference_type distance_to(const indexed_iterator& other) const
    {
        return other.m_it - m_it;
    }

    wrapped m_it;
    index_type m_index;
};

template<typename SinglePassRange>
struct indexed_range
    : iterator_range<
        indexed_iterator<
            typename range_iterator<SinglePassRange>::type
        >
    >
{
    typedef iterator_range<
        indexed_iterator<
            typename range_iterator<SinglePassRange>::type
        >
    > base_t;

    BOOST_RANGE_CONCEPT_ASSERT((
        boost::SinglePassRangeConcept<SinglePassRange>));
public:
    typedef indexed_iterator<
        typename range_iterator<SinglePassRange>::type
    > iterator;

    // Constructor for non-random access iterators.
    // This sets the end iterator index to i despite this being incorrect it
    // is never observable since bidirectional iterators are demoted to
    // forward iterators.
    indexed_range(
        typename base_t::difference_type i,
        SinglePassRange& r,
        single_pass_traversal_tag
        )
        : base_t(iterator(boost::begin(r), i),
                 iterator(boost::end(r), i))
    {
    }

    indexed_range(
        typename base_t::difference_type i,
        SinglePassRange& r,
        random_access_traversal_tag
        )
        : base_t(iterator(boost::begin(r), i),
                 iterator(boost::end(r), i + boost::size(r)))
    {
    }
};

    } // namespace range_detail 

    using range_detail::indexed_range;

    namespace adaptors
    {

template<class SinglePassRange>
inline indexed_range<SinglePassRange>
operator|(SinglePassRange& r, indexed e)
{
    BOOST_RANGE_CONCEPT_ASSERT((
        boost::SinglePassRangeConcept<SinglePassRange>
    ));
    return indexed_range<SinglePassRange>(
                e.val, r,
                typename range_traversal<SinglePassRange>::type());
}

template<class SinglePassRange>
inline indexed_range<const SinglePassRange>
operator|(const SinglePassRange& r, indexed e)
{
    BOOST_RANGE_CONCEPT_ASSERT((
        boost::SinglePassRangeConcept<const SinglePassRange>
    ));
    return indexed_range<const SinglePassRange>(
                e.val, r,
                typename range_traversal<const SinglePassRange>::type());
}

template<class SinglePassRange>
inline indexed_range<SinglePassRange>
index(
    SinglePassRange& rng,
    typename range_difference<SinglePassRange>::type index_value = 0)
{
    BOOST_RANGE_CONCEPT_ASSERT((
        boost::SinglePassRangeConcept<SinglePassRange>
    ));
    return indexed_range<SinglePassRange>(
                index_value, rng,
                typename range_traversal<SinglePassRange>::type());
}

template<class SinglePassRange>
inline indexed_range<const SinglePassRange>
index(
    const SinglePassRange& rng,
    typename range_difference<const SinglePassRange>::type index_value = 0)
{
    BOOST_RANGE_CONCEPT_ASSERT((
        boost::SinglePassRangeConcept<SinglePassRange>
    ));
    return indexed_range<const SinglePassRange>(
                index_value, rng,
                typename range_traversal<const SinglePassRange>::type());
}

    } // namespace adaptors
} // namespace boost

#if !defined(BOOST_NO_CXX11_HDR_TUPLE)

namespace std {

#if defined(BOOST_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmismatched-tags"
#endif

template<size_t N, class T, class Indexable>
struct tuple_element<N, boost::range::index_value<T, Indexable>>:
    boost::tuples::element<N, boost::range::index_value<T, Indexable>> {};

template<class T, class Indexable>
struct tuple_size<boost::range::index_value<T, Indexable>>:
    std::integral_constant<std::size_t, 2> {};

#if defined(BOOST_CLANG)
#pragma clang diagnostic pop
#endif

} // namespace std

#endif // !defined(BOOST_NO_CXX11_HDR_TUPLE)

#endif // include guard

/* indexed.hpp
kXHYT0tcs7r5OtCsTOg6vOTrczUrF1h9vPu6IY48ZDn8ipdOxdn/eV8Psv9NyB4w2JdNprMfH3p46lPEfa+kHYxLqYKM6OCdT3aL8pQUeZ5lMD6FWExZx/b7fhDn6veodOg8y2etbYYpo3surTW7cGKVPUCr19XTJTBS8KNLfqBNzUscwcoRQNrz7WKGRpe+UMEcqcLifnk4GR7Y9ztW02q+Umdz0+yAAl0is+Ovwm04hU+HH3tDx53YHPG2qbgQ1WzqWnGxmJy9UHaRDgKFjzlWE3MjOB5r7bXQQvVegwVIvuXrXnkSB/0L+Xj+gEzUpo5u3BLYweOvsQyPePy2ZNTk23GrPFsvNqKtwcUa/VHYDV1Ouwq6vJijSVPbUOWUM+3KS6EnFAHnnNv+m+zqU4iyYgvW98gZd6tGDwWegOBOV1tlM9AjuBuXG80y6qcyWafL5isBmrvd2fzQ6GkxmbEPKN2bP86o2hJwW1OYHO+CUawxJw3e+cSaYzKAohlkqM9v0HaTJNiNayw+LnSMivsBNqvw2PfXCuvavVqhh+0myeJu01Z3xok0g1sAL9DTdOr4+PU6Tkoqg6qFONx2EbOe/nstWk83iCxYBB26jXk+a2ZR/tLvouhJ7q4VihldE0swquEnOwHrOtaLJFIW7L0lcdydZ5Q8vwnenwjv06J/OFdTO0Ex09QeTY1K44kMyU9eiYpE5fCDXDQJ/eX1+1CRSr6WfJbMZWFzM0mXAn1b3ay5tmjuddrcjY5nScpl+E1gAGqpWpGJ7esowVjuZ2k6p88u9pQAHgPbT4lwO5sxQQZ7LuXukbTjupXb/q9LoCt4Ya6XCwutV5eXntx7gKIEpsgoga28fb6MErgcowRepip+Sw9AuVOGCDz5Hnr5Xkad6DRdbo3pW51waz8ZvsnrHwaV+TM6oAkSDpTk/dhNcGLBJLN0UPr7L7+HYQCd5RiR14cG7rNradnTCbkZuVMNQITfjJga+R4Kf/chaviyoeuhIWdj5WA7jQPxdihA5IsjQ9q5Ddrh9nSdMr3N8PDOB6CuCRfPATWTp/V1wcTZdgBGJuUrnDjhkZsMS8fYgKQp/J0/oyFee1Ip9Bu9IddWHHS+7Xpc52qORwqxB8jVrD9bR8+U8yWyT+MugWurWNIDdx7+Oh9CwpcQUxi+eT0h1zawjbbgKcysGtQ31eaQa5X1790wr2H9Y2TrpAKesjlRtt7fkCzUjaEFqdcLdV3ItVaoW9hhD//ytVPo5mXm4L6k4B6yUjX3ejWDNz0/RDJHmGuzlq0tMfHePHJ310cqQbO1NzQZMwOjbc/nrBxjc1QbLoYJN4xl4ZFi7dZFHdMtPwp55px/MeJH0H6x7iasaz/pbFRGe71+22Ds1oX0oCFfq5t0EWmLI+HvBoS5coPpYrw201/LxaTsJhwhVxM2juq+OHdnKbgboRjU0XzxQQrTzDeg+tpglXY/LOC8mihOSNU0oiF8Qay6Feb9PbDK0WHSCRjaGxL1zysT5RLaqxjvcq6hK5d5i0crbdFKW0XWBPS8rG6HHq4sDfMb086gEKg1og+ESvlbYOVg0beGeNHhVFnrJOELWgwoSS1gFdnqyeE/uqkOKWMk4y0sOjDS1EFkUoZRwX5i5C2gXNmF/X3n3kBqXjPrDw93unqqUvJAvYoyVytYz/qT9/BJFJ9E2REt0OY89WiyNreNUSusue/E2P3BzyYE947BjAnjMZw42DBBc7c7XG1VGTSmS3X5Z28I3+NwtwVmnXS1nyhtP+Fq/2hxW4uqX7emN5+GdXT5pUmGla5w+HLEVcf7gp/oZqoc+sfcYXvDDatxRihpK+l3kHc+PZZ4p67flF0J+o0NKvBpn52r3/wSjb7RV8X1G5lA4Ph2mAkBs1Gdq08DJV2fAhwF+i1ySGibPZCCw6JYmuosOvnDuTCXWn8UZCNad9Qhcv4kj8zCkFWxPcNGM6h+3KNoHK57lIzD+Kl39n2oDt0ZnvJn8zHg4DpDnwjVHUvGku+p5GIqqUjCki4qSaeSTipZSSVgmgt9R6t8BZV0UMkigvMdlRynkjVUp5JK/kklhSYs+ZZKXqMSE0F+hEo2UcmbWGfXN1Di9fHVVDQxBSv9lirdRAhNShkEVEslN2AJvPEw3d2UMtipF37sFdX78qGkRO/UtVCSeAQ42Jk5xMnL6gqhtn2/c69SpLk7YVQ1d48GRgMaDPGzZq7O55ecB4LaFXlewd/V+BIK8Qbst4Qhtm4BLvP6liWgxOyZgseJB9ArO/t86ZWFcfEbYVIsrgHGTpGMeABHBg/t6MEQ2KNsNfalsCmlQRlj+yqZDOtULR3vWN1tKRRMfKdWjwaAY/ccuFcuZ6tvI0xQR9qKQHbgPSEhdmAVPglRqfPItzP0+hk+HyiCE00ICHFXrhnaJZ/PfzHFhcIc/Cc6pKiHUGqTpXVI4oXsUNnzk5LH2OZ3rHq2W+DmOGoZk8aj2yi0GicJdBGIyl9v7haOqcjKrTVjkD1R/7Xd81LiCORAS/OHtKTRA2ovFuC4o9yEdMJQ8sMGDEWDl7KCGEGEkyS0GuEVyzQUHr7xn6eEs0lNB9JkTYDl0oG+qli+Cs0VwaBUDYrK37EBme7/WF/VXAsMOA8rI8UOhFnCL/u/qMAgeUrMQcjhwSg+ASQqHqCOaPUvw7CLyTQv5ESYTHMlG5A78ywGxWKhR/wRFT6Q3iOhN9tgufI/X9ktwsOBk/qN/KmmbsHfH5dgIOmEoAjqW50uM3CZ+q9Ao/g5BYMSzcYDpKI4XXR6kQD0SfLzfAAryRzfEnviHhijNZcNBm48iuepcUkFO2ygngxDVWYlaiurJ8lC/lu6m6jfPQB3odW4dPmyPFiAq3Glg85m5n66RSYDt2l8Pt0ukrepfOTVeIvsBW5TuLgKbyvkrYlH6NYkb5P5r+kWuQrtAd9NtzlG3aU4i263SA+jgd90VV8swmTiZej2vixxQ8mcING3nRyU6LH40ppL9fjSC+UExY1je4NjA1LT+kQDaWM3fwmUvy9Zjyu8ek+XkNMj5IqUf38zjC5uEP9sLShMgQjuC/vH+Xjz5aCt3xkJRlOV4XxKU5fooOQTgCe/qqnrp+ds59unBE7NRnV4bNqGHx26NMnGVSOshTnlVEZ/xVOTTGhE3pFC3vqxYgdNhR3zaDbaYmYkHU48xL3oidVhouGhkMIwpA2jbkej+cGdl2LAjh7JWnIJUgtm7J8e7aa4TeQnYHkmxVZ1fK220lrVXJ2gDFlrJkAFPj5JpyB/Cyl4wxAKBgb4N4+DyfmOxecfBz3kK8bHopQlDbv/CTRsN+o0/BfcwfrDXTUZs6k3iEF/8kA0f1wAmX9PDo58Cygrq5ELAoe37rxzjnXt28UebW6nTGUDViOlZImxRzyqTOzRx+e/0S/ilL2M3TnHbwDT3KzT9ChlA9GZsLTpElnwTgTKX72uF/SATiBTI3khZfIXRIamhOTtrL7dgokWOhF9ipE/iukbJGitxUKdIOQPxxLw6A+jZATfYIqjD6Pnx6KJiZMiD6dN53/EXNbVKioTuuDj3RMB+90LUlB/SdV2I9psNQHdj1zSowPYiLMoEAFb91IfoCczPaVwE+jQPikUfw2A4FElYk5dHjLNZFH8eAH/58UyTOy/F2P+h4t0fuW/wX7SW556C5Bn1HiDvl8Oi0/yMV68tFvs6cwfZZMZKhJYxpSlyAnxNoGtXEqFa6gwznrSqRBvE9hTVAXAC25FwBX0JM7HPlGxeicVxnndfirE2wR+uI1guBDGMXoSZ5z/S9XxVjJWKBzGa6lQvx3OO2A2eELEhflLb3QJKBzBj8lC5CR8rSy08D2yEFcXf/QNSgEC5ekajS4Y/3u2vEUSAkFpdYuwWsVbeFJRwnlAXtPri+B6E+ofGqlZm1DaayT8tQ230V9aUhvm0N9C+ruA/iLrYfu4uHBwu6dY14B+9Ui3Pq8xm5q1ZoExrs/k/idNxn9tr/D+JJNBc+v6cuyWTqAtb6J0Ll9CdcbhojzqA87X8VskKQLr+JKUgQTOAfxHMg/FzdL8qRJQMTssPPewGXNAWeTT8bzmzfDHutM9AIsRl+HGHahLDMBUt5YbHqUj+3oR24PLPDxzT/hmZCPfnyb/R4YvNoZzAAUs+tPfwAJYIZ9/CmBPf0mPrSw/198FQFq2SyA6a8DlD5gdTVjgBn2B47IeGNJTP6ZSoV7y6LJuMX9hmR4VUBzPz2Rv8Hh2oerJvvfq3XcNUPj8BAkvgaPiUWLlIuEakNmC9EKHa6DymL1BjyS273e4LWqqthpb1XXVvYqFLT9mibG6YgRblAAWxuNfP+J54/zw6zErK3oBWFn3IOYnj55tZaV5QD6iH/mvY5Ez3FD/KnKGfRfQQZUNp0HLlV07Wb0b5yrqz+pFXm+ihn280AukoanMP67oFptygRmChHJskFJsgzGOfaO15n08JOZuE9pW1Lh10lcP9ujfzFV8xHfn9Qo+qh8WX76J5S/ALaQNi6gNm1FCx5x95BWZjRhgSS/511vwmHHnbOHJZM3lN80abQMS8KZjMtUSnSB1RRzrVkpPNTE/PPwc72dsdHjgenTcDx3IRmUUy58DMrXJhXLU4Jw2R0kGAMLFHaXtyhvwR/XzR08h/3C38lt3UIQi9DMpNLd1Nh6r8dwD1rRXngzQoaIO7Gr3yPDz2Ni6Imw54ugkSqmp6Pt1tTF3a8wFdfnuLuEo7bTWDseANUusycPbu0T51zdTch8KBXw92iVAHZoH5v8vmaTT3WgmmMGuYPnmeNhcq/OAci1IDz7iUXI7ZuGpTxuwK/7SUfStaTSscqCVHR1j0B1c3qo3Rk2/A73VwQGsz8/ppzexizCg4ngw0Iaxna6WpjpkerSrBp2kLgPx27Q6XA5DJj2/tL9LqkD/2gaNf3irLone76NuYkz3SCqlOtclomStmYUHzUAGCnkmQJ/T5cehOv9DIoDjMQCR7UMADP9pAC0IwJMIoCUG4O9DAew/85MATiAAayKAEzEA/z0UwMqfBvARAjjUmwDgoxiAa4YCmPGTAPAUjAXkJWZt6xexsNq3d+H8jU+51+A2fLdXt13Gv9EtvOWRfHK6/7CTTkdnQFn5Coy4u3UQlwwqibHtDduGoFMPHAwb/70C9ltBnz6Lh70GY9t5czxFFe/+IaFrnbEZN3sorAcob1l81pXLWedNMPFgYQ12p/0N9GNLmwUPkaNf/U2+7wgwQrImQq43Pbq7mZ/acQrUAGCkneHJsaVD0d17Xgc2iyeOE1ulyY2Ho6GVKlIgYN2pTXEeI1Gx7w9GjdZn9xZLhYofq8ekn/+uCio3/NV6mUILEZ31Xq8I3+TVX56LL+u1Zspr1NX4VHmN6hW/Tl6TYTu+noLYYnswX/8W92CWfzPKxt84jMsd+UQO2Dmh+kIA05tmVC1eqc7xr2Gse9NMarZXDyI8sZPgok7G34VrjA6ekYVRYBur0atWbCqpfV+5gk0zA1/JzXs73/4+CMrzat+vmOAszg5cwR7MDN70pEEZdqvzSGWHvaGsEYttbF+TaQ1FU0wzJb9d1sj7j3eJgzKmYpoJ8/M4I79xOh80P/zzvEjFFOeD2YHr2bRMr89+kp3Z+1WS/X3HXIv1icbQgrHCmHMDPh8Fz5ObFs532AJJmo0isPjzCDVmy9aPljs8qaywB9Rz/7Lh5T5D2nJesbNL3Bu8wajO8xsxEg1m7EAXUHAiP3NzkuEuGZHOonxNfZcgr0rDF920q3Ilbs9EsP5BqI9BMnjdvzMeul4Gb7AmdJDw0ZlDzm1OAFy4vUdnd71/h3qqRfwcYeA2thng+o3lN/xuNIxfbXsXHn/Qm/rfQfACLvkbo2U+ElP9sDoAfHQUHaYsMOcVmOwn8/Eg2ZW0jFZ/SVsrlVnOIqR/SaaW89g0Z3NlZ8e7OM7L8MyiauZ/vxMP6GLYF57pEg+bRNYW6RJCx9JzWLWyu0seT77l73pokMEkTyhjPPStnh6hUzGIsqjI5Nz7m/OcBeaHR+XtrXjKWZAdeJwVZYZM1cFcEATYwEY8MQ1a6rXylux2fjkgYt8PjT6xt3a/tWa+IGdvMqgMCDodN3MHTyf/ALJgurM0Yl1VhhLzxVGx87o2PK+7JwPPf4CuZD8J9Ii5LVZ8IHv8VhGGqzi7rTVtBjruEesxytPVGKS5B/vnpSc6qtbaP6KKLMvWQtmWXGUx/1WXTpjLX5GE8UmiHOLXIFVdZjy2WFmOc03Jw3D73QPUqUXwTjHce/jHMjujV4d8hzywT1yhMMKt0Ev5QJIouYgOeY3AHKEADWkCROi0rsKD5+EsObv/d1uX0A9VoP7AH8uI0eYgqogf2jB+zFKoXFSo5mI4U34OTWT+X+tpsYfT688sTrc18oUP4z2flTGY21R3ptcKNdl/w0Ifv2gkLBetbq2Mykjh34Ca6sOESztyoBEqD75j0W5YmJAkeASeGM2/CboxnlESA1iZY5mtGHW/bLEDS/jdADf4Il4a7iob9F3tgl76bXxLOrVKNd/6lsYUAMpXpQ6ZKdszyhBY6FQjsA+KUFXMMlI1nDqbd/wXdbjRb+SfwCXuufS1NOJbm40yaXV+LJTVzDd4sXLccV5cEgJ75Hvmtnj4L6tIx6IzhTZUgQ7pcWam5d1Cz01MoWOWwkIFhd6sEh+fjHuQsCwjLM1ZkKNa2AyTsyCXZOLVIZfF4zf5R/lElvKPDFtvWj4ryFFSgs354eRg2x4tjRXkajNM+ulBiyH4Oh1fbpq2CHd4ldFgmqSUP2iilBlyu6ixY6KCIbEldEQXZzeQM7qVVIQx8KRMJ1c5dDxuoHpZqQUZs7dEcw/w2x6XvcQp4vZZd56pPancuvdb2721veqNBHYF7g5Lv9pLtlxA5DJ/BO4jYAEG26yKVQ99NmPo8whUgge0ikVxo0lP2RmwGGCoYS6doH1qC5DZww2Bf0Ph56p0Ctcf/B1u/PDfxTZ+KG1ERZazGkOGAulMwwhMZqqmeRoA2OT0RLSVGKEoVwT/20PdorHeFJThhWSj2wV/637CID9BytY8hFIWW+Rzmrtl3PuFjnocCiWrL78CKGBULD49Rwxt2okZeIIujiAYoChV7qY92zmEgwR91SDo/iYMbgfg3crPZISuzJpVdQmymQzkisspj57b7Ci0KFnJt0x3UoXKT6GF2F7PDEu4J3a82oar2OL1yV251D9QxyhbF+2VFuQ60hSrR6LiSLPWdlAkgDnlPVzN0WHWFXgwV4yrPeVPtyWQQ/1NHGdXkx74kdmbP8+mjgwSUQxqSnCECD8pgwPX6Eusr6VQSw5Xy8K1sXUXDsuClcZY9vgzwYak8AeydBWUdsyiXF14uw7PEzfL641GmWL4aQw5flGWrcfnX8vrLXi9Go+pfwa2COUWXqoPfUc/HvpriCX4Fn+C/u2H/y/B/7fg/wfw/zv4vxr+V8D/++D/RfB/0JnQ3zdDjvoDSNvJa2HiY36ND9mFEfKCmCkiIeIRR2WezHRMzZEVpTTp6g2YiAAzKU+qfROISC9CXfREDFYfiFc/T4CYCJhNvzkIIti7hDL74jLS04jF6w2jl1YhKsBk3AA+hOBZWrkRucBhGWwf
*/