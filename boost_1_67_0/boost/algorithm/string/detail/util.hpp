//  Boost string_algo library util.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_UTIL_DETAIL_HPP
#define BOOST_STRING_UTIL_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <functional>
#include <boost/range/iterator_range_core.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

//  empty container  -----------------------------------------------//

            //  empty_container 
            /*
                This class represents always empty container,
                containing elements of type CharT.

                It is supposed to be used in a const version only
            */
            template< typename CharT >
            struct empty_container 
            {
                typedef empty_container<CharT> type;        
                typedef CharT value_type;
                typedef std::size_t size_type;
                typedef std::ptrdiff_t difference_type;
                typedef const value_type& reference;
                typedef const value_type& const_reference;
                typedef const value_type* iterator;
                typedef const value_type* const_iterator;

                
                // Operations
                const_iterator begin() const
                {
                    return reinterpret_cast<const_iterator>(0);
                }

                const_iterator end() const
                {
                    return reinterpret_cast<const_iterator>(0);
                }

                bool empty() const
                {
                    return false;
                }

                size_type size() const
                {
                    return 0;
                }
            };
    
//  bounded copy algorithm  -----------------------------------------------//

            // Bounded version of the std::copy algorithm
            template<typename InputIteratorT, typename OutputIteratorT>
            inline OutputIteratorT bounded_copy(
                InputIteratorT First, 
                InputIteratorT Last, 
                OutputIteratorT DestFirst,
                OutputIteratorT DestLast )
            {
                InputIteratorT InputIt=First;
                OutputIteratorT OutputIt=DestFirst;
                for(; InputIt!=Last && OutputIt!=DestLast; InputIt++, OutputIt++ )
                {
                    *OutputIt=*InputIt;
                }

                return OutputIt;
            }

//  iterator range utilities -----------------------------------------//

            // copy range functor
            template< 
                typename SeqT, 
                typename IteratorT=BOOST_STRING_TYPENAME SeqT::const_iterator >
            struct copy_iterator_rangeF
            {
                typedef iterator_range<IteratorT> argument_type;
                typedef SeqT result_type;
                SeqT operator()( const iterator_range<IteratorT>& Range ) const
                {
                    return copy_range<SeqT>(Range);
                }
            };

        } // namespace detail
    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_UTIL_DETAIL_HPP

/* util.hpp
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
*/