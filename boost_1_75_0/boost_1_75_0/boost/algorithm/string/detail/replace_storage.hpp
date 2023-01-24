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
Cim/iBu2+p+o0IBTpFrIUM3FRjhXWKKPE4ad9XgCXt/1buoxz8Q3R8tvpZhWcFZcz6ZdtIH4jmHZw7r5XAbCEbjw53k+P11LPUhGEa62+ILIjrYrtd36i9H0nXNy309EcHMwstuX7gxJTrbb2n1BC9J8rLrgGqAviUz2s6wLnLCCY3r3nXBL3eOyC6ooHH5K4dKeP3obz5TzpbDO2lucvrzev09hxsvpr6V5qYjqT1v5TptLgHznr0ug7looGCC/bv+fzWp/ImOyh/2m4dLE+Mmtyc0pPPrGnep5sQa09UanF7C5FNbeGrJNPNx8WLiL032fuJsOWkYsc29P5ba9vE59LgM2dQ1FAk28QTwPQDtvbrCF91c3WBFcL9eHMV9HovRuHY+tcHE9Knldmepy9Nr7FFUVDal3+NUuuPW8u0H0umONgg2SzRpUimqogi61t7SwqrsryWHa3/6EfpCIE3J73JIZbmrrNs9555ed4/Upmvjk/JIUOqnVFJDqhf99rlPAL47QkxcZbZmmFQFFAb4OMeXfAc8I6N3OXnKoVAhRnIKhc46tfRSuF2BZlqYe5a54Xj6NVx9xhCOhlhHE7MKeeEa3X0pKv+Agtj96eBQjrsnw1pW8F+1VbFJQh3vCZ/T2mIChpwZOPMLf/d23vF6E5OZybF4gytLTHlKvIu5+hjlQNZn2kU5I6xYYJHh8zFe40KPhaNeqwmnU
*/