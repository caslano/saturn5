//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_DETAIL_RANGE_RETURN_HPP_INCLUDED
#define BOOST_RANGE_DETAIL_RANGE_RETURN_HPP_INCLUDED

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/next_prior.hpp>

namespace boost
{
    enum range_return_value
    {
        // (*) indicates the most common values
        return_found,       // only the found resulting iterator (*)
        return_next,        // next(found) iterator
        return_prior,       // prior(found) iterator
        return_begin_found, // [begin, found) range (*)
        return_begin_next,  // [begin, next(found)) range
        return_begin_prior, // [begin, prior(found)) range
        return_found_end,   // [found, end) range (*)
        return_next_end,    // [next(found), end) range
        return_prior_end,   // [prior(found), end) range
        return_begin_end    // [begin, end) range
    };

    template< class SinglePassRange, range_return_value >
    struct range_return
    {
        typedef boost::iterator_range<
            BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type > type;

        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type found,
                         SinglePassRange& rng)
        {
            return type(found, boost::end(rng));
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_found >
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type type;

        static type pack(type found, SinglePassRange&)
        {
            return found;
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_next >
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type type;

        static type pack(type found, SinglePassRange& rng)
        {
            return found == boost::end(rng)
                ? found
                : boost::next(found);
        }
    };

    template< class BidirectionalRange >
    struct range_return< BidirectionalRange, return_prior >
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<BidirectionalRange>::type type;

        static type pack(type found, BidirectionalRange& rng)
        {
            return found == boost::begin(rng)
                ? found
                : boost::prior(found);
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_begin_found >
    {
        typedef boost::iterator_range<
            BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type > type;

        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type found,
                         SinglePassRange& rng)
        {
            return type(boost::begin(rng), found);
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_begin_next >
    {
        typedef boost::iterator_range<
            BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type > type;

        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type found,
                         SinglePassRange& rng)
        {
            return type( boost::begin(rng), 
                         found == boost::end(rng) ? found : boost::next(found) );
        }
    };

    template< class BidirectionalRange >
    struct range_return< BidirectionalRange, return_begin_prior >
    {
        typedef boost::iterator_range<
            BOOST_DEDUCED_TYPENAME range_iterator<BidirectionalRange>::type > type;

        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<BidirectionalRange>::type found,
                         BidirectionalRange& rng)
        {
            return type( boost::begin(rng),
                         found == boost::begin(rng) ? found : boost::prior(found) );
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_found_end >
    {
        typedef boost::iterator_range<
            BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type > type;

        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type found,
                         SinglePassRange& rng)
        {
            return type(found, boost::end(rng));
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_next_end >
    {
        typedef boost::iterator_range<
            BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type > type;

        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type found,
                         SinglePassRange& rng)
        {
            return type( found == boost::end(rng) ? found : boost::next(found),
                         boost::end(rng) );
        }
    };

    template< class BidirectionalRange >
    struct range_return< BidirectionalRange, return_prior_end >
    {
        typedef boost::iterator_range<
            BOOST_DEDUCED_TYPENAME range_iterator<BidirectionalRange>::type > type;

        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<BidirectionalRange>::type found,
                         BidirectionalRange& rng)
        {
            return type( found == boost::begin(rng) ? found : boost::prior(found),
                         boost::end(rng) );
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_begin_end >
    {
        typedef boost::iterator_range<
            BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type > type;

        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type,
                         SinglePassRange& rng)
        {
            return type(boost::begin(rng), boost::end(rng));
        }
    };

}

#endif // include guard

/* range_return.hpp
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
*/