// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2015, 2016, 2019.
// Modifications copyright (c) 2013-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_RANGE_HPP
#define BOOST_GEOMETRY_UTIL_RANGE_HPP

#include <algorithm>
#include <iterator>

#include <boost/concept_check.hpp>
#include <boost/config.hpp>
#include <boost/core/addressof.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/rbegin.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/mutable_range.hpp>

namespace boost { namespace geometry { namespace range {

namespace detail {

// NOTE: For SinglePassRanges pos could iterate over all elements until the i-th element was met.

template <typename RandomAccessRange>
struct pos
{
    typedef typename boost::range_iterator<RandomAccessRange>::type iterator;
    typedef typename boost::range_size<RandomAccessRange>::type size_type;
    typedef typename boost::range_difference<RandomAccessRange>::type difference_type;

    static inline iterator apply(RandomAccessRange & rng, size_type i)
    {
        BOOST_RANGE_CONCEPT_ASSERT(( boost::RandomAccessRangeConcept<RandomAccessRange> ));
        return boost::begin(rng) + static_cast<difference_type>(i);
    }
};

} // namespace detail

/*!
\brief Short utility to conveniently return an iterator of a RandomAccessRange.
\ingroup utility
*/
template <typename RandomAccessRange>
inline typename boost::range_iterator<RandomAccessRange const>::type
pos(RandomAccessRange const& rng,
    typename boost::range_size<RandomAccessRange const>::type i)
{
    BOOST_GEOMETRY_ASSERT(i <= boost::size(rng));
    return detail::pos<RandomAccessRange const>::apply(rng, i);
}

/*!
\brief Short utility to conveniently return an iterator of a RandomAccessRange.
\ingroup utility
*/
template <typename RandomAccessRange>
inline typename boost::range_iterator<RandomAccessRange>::type
pos(RandomAccessRange & rng,
    typename boost::range_size<RandomAccessRange>::type i)
{
    BOOST_GEOMETRY_ASSERT(i <= boost::size(rng));
    return detail::pos<RandomAccessRange>::apply(rng, i);
}

/*!
\brief Short utility to conveniently return an element of a RandomAccessRange.
\ingroup utility
*/
template <typename RandomAccessRange>
inline typename boost::range_reference<RandomAccessRange const>::type
at(RandomAccessRange const& rng,
   typename boost::range_size<RandomAccessRange const>::type i)
{
    BOOST_GEOMETRY_ASSERT(i < boost::size(rng));
    return * detail::pos<RandomAccessRange const>::apply(rng, i);
}

/*!
\brief Short utility to conveniently return an element of a RandomAccessRange.
\ingroup utility
*/
template <typename RandomAccessRange>
inline typename boost::range_reference<RandomAccessRange>::type
at(RandomAccessRange & rng,
   typename boost::range_size<RandomAccessRange>::type i)
{
    BOOST_GEOMETRY_ASSERT(i < boost::size(rng));
    return * detail::pos<RandomAccessRange>::apply(rng, i);
}

/*!
\brief Short utility to conveniently return the front element of a Range.
\ingroup utility
*/
template <typename Range>
inline typename boost::range_reference<Range const>::type
front(Range const& rng)
{
    BOOST_GEOMETRY_ASSERT(!boost::empty(rng));
    return *boost::begin(rng);
}

/*!
\brief Short utility to conveniently return the front element of a Range.
\ingroup utility
*/
template <typename Range>
inline typename boost::range_reference<Range>::type
front(Range & rng)
{
    BOOST_GEOMETRY_ASSERT(!boost::empty(rng));
    return *boost::begin(rng);
}

// NOTE: For SinglePassRanges back() could iterate over all elements until the last element is met.

/*!
\brief Short utility to conveniently return the back element of a BidirectionalRange.
\ingroup utility
*/
template <typename BidirectionalRange>
inline typename boost::range_reference<BidirectionalRange const>::type
back(BidirectionalRange const& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( boost::BidirectionalRangeConcept<BidirectionalRange const> ));
    BOOST_GEOMETRY_ASSERT(!boost::empty(rng));
    return *(boost::rbegin(rng));
}

/*!
\brief Short utility to conveniently return the back element of a BidirectionalRange.
\ingroup utility
*/
template <typename BidirectionalRange>
inline typename boost::range_reference<BidirectionalRange>::type
back(BidirectionalRange & rng)
{
    BOOST_RANGE_CONCEPT_ASSERT((boost::BidirectionalRangeConcept<BidirectionalRange>));
    BOOST_GEOMETRY_ASSERT(!boost::empty(rng));
    return *(boost::rbegin(rng));
}


/*!
\brief Short utility to conveniently clear a mutable range.
       It uses traits::clear<>.
\ingroup utility
*/
template <typename Range>
inline void clear(Range & rng)
{
    // NOTE: this trait is probably not needed since it could be implemented using resize()
    geometry::traits::clear<Range>::apply(rng);
}

/*!
\brief Short utility to conveniently insert a new element at the end of a mutable range.
       It uses boost::geometry::traits::push_back<>.
\ingroup utility
*/
template <typename Range>
inline void push_back(Range & rng,
                      typename boost::range_value<Range>::type const& value)
{
    geometry::traits::push_back<Range>::apply(rng, value);
}

/*!
\brief Short utility to conveniently resize a mutable range.
       It uses boost::geometry::traits::resize<>.
\ingroup utility
*/
template <typename Range>
inline void resize(Range & rng,
                   typename boost::range_size<Range>::type new_size)
{
    geometry::traits::resize<Range>::apply(rng, new_size);
}


/*!
\brief Short utility to conveniently remove an element from the back of a mutable range.
       It uses resize().
\ingroup utility
*/
template <typename Range>
inline void pop_back(Range & rng)
{
    BOOST_GEOMETRY_ASSERT(!boost::empty(rng));
    range::resize(rng, boost::size(rng) - 1);
}

namespace detail {

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES

template <typename It,
          typename OutIt,
          bool UseMove = boost::is_convertible
                            <
                                typename std::iterator_traits<It>::value_type &&,
                                typename std::iterator_traits<OutIt>::value_type
                            >::value>
struct copy_or_move_impl
{
    static inline OutIt apply(It first, It last, OutIt out)
    {
        return std::move(first, last, out);
    }
};

template <typename It, typename OutIt>
struct copy_or_move_impl<It, OutIt, false>
{
    static inline OutIt apply(It first, It last, OutIt out)
    {
        return std::copy(first, last, out);
    }
};

template <typename It, typename OutIt>
inline OutIt copy_or_move(It first, It last, OutIt out)
{
    return copy_or_move_impl<It, OutIt>::apply(first, last, out);
}

#else

template <typename It, typename OutIt>
inline OutIt copy_or_move(It first, It last, OutIt out)
{
    return std::copy(first, last, out);
}

#endif

} // namespace detail

/*!
\brief Short utility to conveniently remove an element from a mutable range.
       It uses std::copy() and resize(). Version taking mutable iterators.
\ingroup utility
*/
template <typename Range>
inline typename boost::range_iterator<Range>::type
erase(Range & rng,
      typename boost::range_iterator<Range>::type it)
{
    BOOST_GEOMETRY_ASSERT(!boost::empty(rng));
    BOOST_GEOMETRY_ASSERT(it != boost::end(rng));

    typename boost::range_difference<Range>::type const
        d = std::distance(boost::begin(rng), it);

    typename boost::range_iterator<Range>::type
        next = it;
    ++next;

    detail::copy_or_move(next, boost::end(rng), it);
    range::resize(rng, boost::size(rng) - 1);

    // NOTE: In general this should be sufficient:
    //    return it;
    // But in MSVC using the returned iterator causes
    // assertion failures when iterator debugging is enabled
    // Furthermore the code below should work in the case if resize()
    // invalidates iterators when the container is resized down.
    return boost::begin(rng) + d;
}

/*!
\brief Short utility to conveniently remove an element from a mutable range.
       It uses std::copy() and resize(). Version taking non-mutable iterators.
\ingroup utility
*/
template <typename Range>
inline typename boost::range_iterator<Range>::type
erase(Range & rng,
      typename boost::range_iterator<Range const>::type cit)
{
    BOOST_RANGE_CONCEPT_ASSERT(( boost::RandomAccessRangeConcept<Range> ));

    typename boost::range_iterator<Range>::type
        it = boost::begin(rng)
                + std::distance(boost::const_begin(rng), cit);

    return range::erase(rng, it);
}

/*!
\brief Short utility to conveniently remove a range of elements from a mutable range.
       It uses std::copy() and resize(). Version taking mutable iterators.
\ingroup utility
*/
template <typename Range>
inline typename boost::range_iterator<Range>::type
erase(Range & rng,
      typename boost::range_iterator<Range>::type first,
      typename boost::range_iterator<Range>::type last)
{
    typename boost::range_difference<Range>::type const
        diff = std::distance(first, last);
    BOOST_GEOMETRY_ASSERT(diff >= 0);

    std::size_t const count = static_cast<std::size_t>(diff);
    BOOST_GEOMETRY_ASSERT(count <= boost::size(rng));
    
    if ( count > 0 )
    {
        typename boost::range_difference<Range>::type const
            d = std::distance(boost::begin(rng), first);

        detail::copy_or_move(last, boost::end(rng), first);
        range::resize(rng, boost::size(rng) - count);

        // NOTE: In general this should be sufficient:
        //    return first;
        // But in MSVC using the returned iterator causes
        // assertion failures when iterator debugging is enabled
        // Furthermore the code below should work in the case if resize()
        // invalidates iterators when the container is resized down.
        return boost::begin(rng) + d;
    }

    return first;
}

/*!
\brief Short utility to conveniently remove a range of elements from a mutable range.
       It uses std::copy() and resize(). Version taking non-mutable iterators.
\ingroup utility
*/
template <typename Range>
inline typename boost::range_iterator<Range>::type
erase(Range & rng,
      typename boost::range_iterator<Range const>::type cfirst,
      typename boost::range_iterator<Range const>::type clast)
{
    BOOST_RANGE_CONCEPT_ASSERT(( boost::RandomAccessRangeConcept<Range> ));

    typename boost::range_iterator<Range>::type
        first = boost::begin(rng)
                    + std::distance(boost::const_begin(rng), cfirst);
    typename boost::range_iterator<Range>::type
        last = boost::begin(rng)
                    + std::distance(boost::const_begin(rng), clast);

    return range::erase(rng, first, last);
}

// back_inserter

template <class Container>
class back_insert_iterator
{
public:
    typedef std::output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    typedef Container container_type;

    explicit back_insert_iterator(Container & c)
        : container(boost::addressof(c))
    {}

    back_insert_iterator & operator=(typename Container::value_type const& value)
    {
        range::push_back(*container, value);
        return *this;
    }

    back_insert_iterator & operator* ()
    {
        return *this;
    }

    back_insert_iterator & operator++ ()
    {
        return *this;
    }

    back_insert_iterator operator++(int)
    {
        return *this;
    }

private:
    Container * container;
};

template <typename Range>
inline back_insert_iterator<Range> back_inserter(Range & rng)
{
    return back_insert_iterator<Range>(rng);
}

}}} // namespace boost::geometry::range

#endif // BOOST_GEOMETRY_UTIL_RANGE_HPP

/* range.hpp
bzoh/TXi5J+l3XBd9hfJ95Jx/ydzxkO3/TnIIl8x3v8T29+mj/k/xDfqjPs/aeMFvb6r4mvxelnPfpgfxrskt0DWasShvpCZPukHma/xXsZAyCKv6rK7pI0GXRYoMmPMR96kjdGS72nj/k/acOpjGS75zup9mwSZ9VndBt+DLCxNLzsdskBjfsRIWeOeOl7y9ddj8VyxwTvG+3+SL8e4/4PMaZwb7aJzrq7fErG9ccf4CGSdxj7WKe3+Te9vnvTtbT3fE9KG8XdKqyCzGHeCRZBVG21sEJ3f1cs+I3Z5RbfB86Kf4ffloosxZ3ZA1misCz+SfCOM9//EBkV62T2QVYzXZXul7Kd62Z9LWWM/+bbITuvt1kl9nxj3f9K3GF32W/HJvxn3f5DZtuj1NYn9DL86CZnrXV2/D0WXYuP+T/w5x7j/g8w8V5wXnY13YT+TfMb9+BcyHkHG/Z+0a8Rdj9ugsxGfe0NW+h19zL8Bme854/4PMouxzgyALGy0LhsCWadxhrgbsoqhxvt/km+03t8QyTdG97WxorPxd3wTRBaktxEBmTXLeP9P+las1zcNskiXnu9+yAKNGBYnMmMuJEh9+fr4LoDM1aDne1DsYtyf2iCzdegyB2R139BlD0sbxnuRj4rOq3Sdc6W/S3VZgYzR+8b9n7RxVpetFVmXLiuWNhL0djdfk+n9fU7GyNg7vgiZ05gL20W/BXp9O8Wmxu/iPxa7GO/4/0zaNX4jqBafPKbXt0/yGb/lvyW2n6fr9yvIGo366qW+D437P8ha++pt/E7G403j/k9sYMyPZrH9D3TZKanPiJMfSbtf6bKzYoNCvY0OKWv8TdcFmTMdxv2f6LJDr++fks/Yx1puR7vGPtsbsshOD012K2SloXq+20W2SZf1h8xq3FEMhsxi/B4wTMrW6GW/KfmMd8aCReaj6zJGyh7S6xsPWcVtxv0fZI3GvcpkyFzGGE29/esxdgZkgYeM+z/I6qbrfm+FzDZYr28+ZGHDdNkDYpendZ1TIatO0GXpoou/LsuU/hpnumWQOVP0GLZC2jDeXc2Xskv0fqyU8T2p23SN6Gy84/C06PeeXrZE7PyGXnaLlP2Vcf8nMoue7wdie+NvhyvEfvXG/Z/IfqPn+6mMh7/e39elvg7j/u/2r98FHZB+1Or1/VLsYjXe/5N8X+myI1Kf8Tdsx6Rvxn3x70X2mG6/P8ncMt7paBHbv2K8/yf9cOj6fSL9Nd7P/lTq26vLOqXdAF12Sfw0RZd9KTY19gxfiQ9FGe//+cIuxm/5fSCrNuLVbZB1ztbbuFPyGWdnf1+JxXq7QyFrNPbZIyCzHjHe/4PMN924/4PMuUJvdxxkreuN9/+krPGb4XchCzPWqEiRBah2h1ju8/OwyKFR/mcLt1gCYbKx+Bepcy0WPPu2X+toJcNX5L72JCh7Gf6tZTwLRBl5hjw3PAsKC2NZC1q7Vva715/n45m06Slt2m6xJE/ysETCXGNz0u25dlXO1wMC+Q8fT8vY6XMTg5KmT9WfIb3+7AH9WaDn9WexRrmwXjc8M8pFel1/ZjXKWb1veGaUs/W+/izRKOe85YZnLBfwjnrm8rn2jD1XNq1kue2/vf4s6IknnkhfvFTXtUE9z00Lip1q6nrs+rMHTF1/1/0s0SznfP/6M3e5sHupa+O1Z/nU9dqz3VPUs+p/XnvmuPaM49tLxrfCx3LBfi1P3Vg+HIhyjUlKJnl7WdQTkQ+X3wMhx3OR41/qUHV5oS750b1mkmpvrPO6r7hl6t9X4RPq4C3lrH0sva3UIfMGH7vzug7eFvUkaKJ6huzXniHP9Wfj1TN/PrPd+GyCXmf+jc/C1bM=
*/