//  Boost string_algo library join.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2006.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_JOIN_HPP
#define BOOST_STRING_JOIN_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/algorithm/string/detail/sequence.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/as_literal.hpp>

/*! \file
    Defines join algorithm. 

    Join algorithm is a counterpart to split algorithms.
    It joins strings from a 'list' by adding user defined separator.
    Additionally there is a version that allows simple filtering
    by providing a predicate.
*/

namespace boost {
    namespace algorithm {

//  join --------------------------------------------------------------//

        //! Join algorithm
        /*!
            This algorithm joins all strings in a 'list' into one long string.
            Segments are concatenated by given separator.

            \param Input A container that holds the input strings. It must be a container-of-containers.
            \param Separator A string that will separate the joined segments.
            \return Concatenated string.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename Range1T>
        inline typename range_value<SequenceSequenceT>::type 
        join(
            const SequenceSequenceT& Input,
            const Range1T& Separator)
        {
            // Define working types
            typedef typename range_value<SequenceSequenceT>::type ResultT;
            typedef typename range_const_iterator<SequenceSequenceT>::type InputIteratorT;

            // Parse input
            InputIteratorT itBegin=::boost::begin(Input);
            InputIteratorT itEnd=::boost::end(Input);

            // Construct container to hold the result
            ResultT Result;
            
            // Append first element
            if(itBegin!=itEnd)
            {
                detail::insert(Result, ::boost::end(Result), *itBegin);
                ++itBegin;
            }

            for(;itBegin!=itEnd; ++itBegin)
            {
                // Add separator
                detail::insert(Result, ::boost::end(Result), ::boost::as_literal(Separator));
                // Add element
                detail::insert(Result, ::boost::end(Result), *itBegin);
            }

            return Result;
        }

// join_if ----------------------------------------------------------//

        //! Conditional join algorithm
        /*!
            This algorithm joins all strings in a 'list' into one long string.
            Segments are concatenated by given separator. Only segments that
            satisfy the predicate will be added to the result.

            \param Input A container that holds the input strings. It must be a container-of-containers.
            \param Separator A string that will separate the joined segments.
            \param Pred A segment selection predicate
            \return Concatenated string.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename Range1T, typename PredicateT>
        inline typename range_value<SequenceSequenceT>::type 
        join_if(
            const SequenceSequenceT& Input,
            const Range1T& Separator,
            PredicateT Pred)
        {
            // Define working types
            typedef typename range_value<SequenceSequenceT>::type ResultT;
            typedef typename range_const_iterator<SequenceSequenceT>::type InputIteratorT;

            // Parse input
            InputIteratorT itBegin=::boost::begin(Input);
            InputIteratorT itEnd=::boost::end(Input);

            // Construct container to hold the result
            ResultT Result;

            // Roll to the first element that will be added
            while(itBegin!=itEnd && !Pred(*itBegin)) ++itBegin;
            // Add this element
            if(itBegin!=itEnd)
            {
                detail::insert(Result, ::boost::end(Result), *itBegin);
                ++itBegin;
            }

            for(;itBegin!=itEnd; ++itBegin)
            {
                if(Pred(*itBegin))
                {
                    // Add separator
                    detail::insert(Result, ::boost::end(Result), ::boost::as_literal(Separator));
                    // Add element
                    detail::insert(Result, ::boost::end(Result), *itBegin);
                }
            }

            return Result;
        }

    } // namespace algorithm

    // pull names to the boost namespace
    using algorithm::join;
    using algorithm::join_if;

} // namespace boost


#endif  // BOOST_STRING_JOIN_HPP


/* join.hpp
ajsLRD5+ywwiN34QvUbdKTPdGJVwVHfwTMYWK2ZBKFwBzfS/T+tR2390C+nnRteoIP61LX9oVvn8wbb8TdXL53ey5SdUUD7eln9HBeV/6hrK/8BbPn+fLX9jtfL5a235UzA75fpvy4+uoH6fLX9phwr6b8u/unEF/bflb6lWQf9t+Uf72PMpwEA1vI2APEcXlfGP9EkXm70BDgTI1Pd2Ftb478jnO3mmuA4k5mbEIMnbiDxJy3Sq+FqiNVgvUXimSzrrAvluEb4v05i+zxZOejQ/HUNgNNxrLCX6m4UW9hOxktyXot3BvblHT8phHaAn4VTs3zh+r+FHn+VRSGtNSHN7Wm5CRySWEQt9zrD30168Q3Z8wvW04x9VP7ckFuH0/DhV9s8c71SMdxa6y2OfmY9ebuPviQjuUPSb/sQyOtsj5RvV/dl72LfYUdUhVSbhEzGeUB091pGu3hogeUWc10cmKAfbkQAnN5EJWnoZFwhN0HJNZeIy+PYIF1epasmF/Nyz+mKGjbO52R+YQPewq+Jo1rplGfeaM5jMM7hdnpUdmEFQNW0v0xmTKW92g3hKllEiC4OH8e/7aIrmyxT5RtAUPaYGtvjDPLid2l/YrsvC+CXcTfZdTOKvQ8/+CjY9p13haH2C/CqN3XodNfZN0r1XTzQPX1MixcudFRfl66wud/FrVJzpfmwxChKeKqxAOdo8Jq4rjwMnxOUyB+Qv9nIWTvniKf0aTxlgHuzfvajt47H+0rLjsbld2HiM0eNxvihKFlxL4/EGxqOWuveCiscjgcajfR0ejwRzPOaiIOFpweMxxhyPvuVxICjZr4dpPBJoPNo3DI3HjHP/uPGwC91Wd7Lr26ddYt0BO2gjsiQk4ecF+oR/GeRcAsGVk4kRBTunqmUpckbSMvt8uTqVna/4tpgvdU5ON3i9x3zdqOdri8yX8xqar9cxXzXV54nlxroXvXsnlzj1NyeN+JsN9AOwdW06zcEN0TsS60m7r+pohUk7lglP3WyiR69iN9H9bWwmBtWVwHxSZ3IYqd5LE1J2VwNL0aV7Ya7u2zjpW9vhtYi9Zu6uaqKcUa/0CXcgJ9ZKMBFRq9ta0/i+l9SIt+hgUo8hA4kbPfJuv/RC/vkyJvMM3xqYHx58lckJX5NiTplXT9kNrUUu2YnEkcmFN+lu7RCSM/hqmrJCth5o31R3x4zoOOJanjW8M/Nhku3N5/et6ezjzBibqKoCNxQ6iEgbH0PQcVUUj2oLWanre5WyRv2nF7HwcYhIeVOiWOzxkUqub41Rf/VRnZABWi+cLvOSxEUiYUIqHOdGxVL//BDdm145Z8SBC+7Bb4KwR+AMt2s5hCJb5DAfhnyrv59If8cMM/v7obq8ifSXekYvd/ae/2EP0fb79Isdyu6vtUnymn+BuJTvk6gfR5EZZ7PD/IIJe2Wu0+XpTRepVMhNs57WHFwiC7SuCGFbaGqz5Tz+Gc/EryJ680TTs0Bv7O+HDySHQhUdpUExvlePYJvkfuvIGZ970pHTsHCsntPOojlUNfBXfKFhc5tPSqJdmTs9MSonPmUDTsqyT3/cnwrSCW1KFGkNEr6++bPioNLQCWhDSpB1L5SnraY0P0ih1ERl4MZACTQM/aGP2TPRKK4IeUsgRwfMWBb7htQS7U71UuOzb7wUQT6U0t5ae+AkO3jo/T+nNXcwuZUswjrS7TT7+10D5BEh+bKyj3T29b7+YrNOcJ4QHz3YQo5tzXHPSqzEirafTxMvLrt/fC3Dzqdb9EJpEC12M4Np86/FkolVPc+t8HwammSeT0PjaP27OzG9aePPvoUQnRfNK64F2ZsDGRgLdaxRGUToSMLZ4RXK9nc=
*/