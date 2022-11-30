//  Boost string_algo library replace_storage.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_REPLACE_STORAGE_DETAIL_HPP
#define BOOST_STRING_REPLACE_STORAGE_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <algorithm>
#include <boost/mpl/bool.hpp>
#include <boost/algorithm/string/sequence_traits.hpp>
#include <boost/algorithm/string/detail/sequence.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

//  storage handling routines -----------------------------------------------//
            
            template< typename StorageT, typename OutputIteratorT >
            inline OutputIteratorT move_from_storage(
                StorageT& Storage,
                OutputIteratorT DestBegin,
                OutputIteratorT DestEnd )
            {
                OutputIteratorT OutputIt=DestBegin;
                
                while( !Storage.empty() && OutputIt!=DestEnd )
                {
                    *OutputIt=Storage.front();
                    Storage.pop_front();
                    ++OutputIt;
                }

                return OutputIt;
            }

            template< typename StorageT, typename WhatT >
            inline void copy_to_storage(
                StorageT& Storage,
                const WhatT& What )
            {
                Storage.insert( Storage.end(), ::boost::begin(What), ::boost::end(What) );
            }


//  process segment routine -----------------------------------------------//

            template< bool HasStableIterators >
            struct process_segment_helper
            {
                // Optimized version of process_segment for generic sequence
                template< 
                    typename StorageT,
                    typename InputT,
                    typename ForwardIteratorT >
                ForwardIteratorT operator()(
                    StorageT& Storage,
                    InputT& /*Input*/,
                    ForwardIteratorT InsertIt,
                    ForwardIteratorT SegmentBegin,
                    ForwardIteratorT SegmentEnd )
                {
                    // Copy data from the storage until the beginning of the segment
                    ForwardIteratorT It=::boost::algorithm::detail::move_from_storage( Storage, InsertIt, SegmentBegin );

                    // 3 cases are possible :
                    //   a) Storage is empty, It==SegmentBegin
                    //   b) Storage is empty, It!=SegmentBegin
                    //   c) Storage is not empty

                    if( Storage.empty() )
                    {
                        if( It==SegmentBegin )
                        {
                            // Case a) everything is grand, just return end of segment
                            return SegmentEnd;
                        }
                        else
                        {
                            // Case b) move the segment backwards
                            return std::copy( SegmentBegin, SegmentEnd, It );
                        }
                    }
                    else
                    {
                        // Case c) -> shift the segment to the left and keep the overlap in the storage
                        while( It!=SegmentEnd )
                        {
                            // Store value into storage
                            Storage.push_back( *It );
                            // Get the top from the storage and put it here
                            *It=Storage.front();
                            Storage.pop_front();

                            // Advance
                            ++It;
                        }

                        return It;
                    }
                }
            };

            template<>
            struct process_segment_helper< true >
            {
                // Optimized version of process_segment for list-like sequence
                template< 
                    typename StorageT,
                    typename InputT,
                    typename ForwardIteratorT >
                ForwardIteratorT operator()(
                    StorageT& Storage,
                    InputT& Input,
                    ForwardIteratorT InsertIt,
                    ForwardIteratorT SegmentBegin,
                    ForwardIteratorT SegmentEnd )

                {
                    // Call replace to do the job
                    ::boost::algorithm::detail::replace( Input, InsertIt, SegmentBegin, Storage );
                    // Empty the storage
                    Storage.clear();
                    // Iterators were not changed, simply return the end of segment
                    return SegmentEnd;
                }
            };

            // Process one segment in the replace_all algorithm
            template< 
                typename StorageT,
                typename InputT,
                typename ForwardIteratorT >
            inline ForwardIteratorT process_segment(
                StorageT& Storage,
                InputT& Input,
                ForwardIteratorT InsertIt,
                ForwardIteratorT SegmentBegin,
                ForwardIteratorT SegmentEnd )
            {
                return 
                    process_segment_helper< 
                        has_stable_iterators<InputT>::value>()(
                                Storage, Input, InsertIt, SegmentBegin, SegmentEnd );
            }
            

        } // namespace detail
    } // namespace algorithm
} // namespace boost

#endif  // BOOST_STRING_REPLACE_STORAGE_DETAIL_HPP

/* replace_storage.hpp
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
*/