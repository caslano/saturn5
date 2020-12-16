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
rKu7lSQnF6D5eyCPH+GJ7tJcXqRel57ApLpulcWF28niI1y49ha/pgVHy1oR5BMdg40I/jO38sxRWLzYmSt7nsB6nLjFOutxe3pnkn1IfiK0riTTjFc/H8vb//jgRJs4VBkOXKIjL9OPwM64jHjCfPXgTiBCJ6VBNnQvuko6rwCJ+l2lzY3U/6gT4UY1o6p+NJVPzZoerm2lj8xelv7bhvkEOH7KAL9Zxn4fH2Llj8iTFyqkR/2WdzF36N0a8WoLDVzxntsC58H+O63o9OCldr2uolUWgFO2Qxvd/3McK932NfV4zR+Q8hr5SsaNclH/Loe9JXcHTZQsNcGmH+KiTS+6BWYFDSR0b4Vqq1glYe/RrSyg+fJo6YNzgV9K26eSUExtBlQ8ZtfL28TomdRPeQg4TKe0LNWW2LBGoKfqLqVLnBP1bcAsaEuNJf8W88WD+Ks9P153ELiIz+iHrhhRkIctTAKo8PpCn5OOz898kbggiZfpEC/D2+BTkg7vyfbA8zh2UFMWZz4qQOgyTR9+I9xGNatnfXR684G6cy8NaPoukX2S16CztkCPsgd07/TU5zT54Z3h5+rGeh4GC6ikNh3kHD8NUDcBijKdiwTGIAy1SF3EGWqvtfyaElVeUnrLoMFXPtNY4k0kOsezuMZjCaOWrxVzJHpQ3b0b/VpNAtlU1kCTnKxtVUuS/EHZzvigmMb9shTcLzsaXR1xPhB9C7afXbf7C6xAcJbDmRDrZ1ZRF6PVufWhh8DVfg/WuQ3oJ+wRTYUFNn1FdLaUNkQacg415P3s4DAPvm9zblf1ddz0f2YnDCX6Hg498bNjcBKfjMdXC3PVTnQ/GCyYDI3J0gX8AYhqesSGt+rQAZF0I9zX4rkXsY2noo3/d7zHCN2GkyUWf9OKehDYb4SdRojzY1EmyqLmoELetMmrZGfhEYvXCKmjfSt5vGJwMo5vS3IhbWtny0tjiKvUPGSjrXda0RmERV5yFcxtB4eH4dfqi23APpbVkmn6NjutLgXxfNbVyyZZ/0gY6ZwBtF8TuKV4//GBG2b1jQuMmXWnLTlwDVF2Gt7IiDWJCI7aDgJBSjJlbM2kJIsYXMpVLab4ZCD0Ga282QNiA+2IzyLUBvdVNb3/IJgtEJUJ/aW06L1/3HbRzYGDWfuP5bLyBWoqAEqp27bRWYff+Bb+Gydzmau5zAWE71EA+TN2+u0NYI20oucYSyOYbsM+JJOCkR6h8xfC26gne3PgQr73v458L3iv4ZXwdKKpM/sLWEuybRdEWz1QksJdVNuRyv7QtNP0GMDm3OgrfA9s9h4/sdmtSCOk7zSgPtpVFRJv4MRazYNfpkReMCtlrcS80CKPyxSaj+a6+Z/yd+B9tc6humbuq51XdrMeQCky4C8blATRaXFw4C/Vrq11h7uultT0uto8VWdeVxsTvq6Wed9B76sN5wwzB0ffV/Musus/OgYsSaKBExzUuqp/Yoz69Kp/++01Uz/zPlZ4duH4gd94x128p82Mn6HJUgcKx+vLMv1F8vbAhepVqLasq2O4pdYbWh3H3I7EPWZlxfqC+TjSbHXALbUTzP10rJfvwrXiy2r12Sscc0hzi7tkjvlPIQClXwNzhHKGn9Un2R5oi9s/XvyHQ5jpdW46iukJDfskFkFZtHqATm5A8c0+iFYngr7mbp25szfi2tltelhcrfU0yCH596mP0WUHXjtbrrwjo++cWTiGCI7dXhNHSP06EocAR1/5W2EB71E3qbp/9wW14hpXUfrsmoJYsuUvrrEVOYr32IriQEVl6fl0Lbr0Av63F//rpH8Peh/2cSjQ+BUQugybsRae9aaSU62uXhk2p8mTG2IpfIk=
*/