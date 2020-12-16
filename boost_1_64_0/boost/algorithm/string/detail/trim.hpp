//  Boost string_algo library trim.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_TRIM_DETAIL_HPP
#define BOOST_STRING_TRIM_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/detail/iterator.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

//  trim iterator helper -----------------------------------------------//

            template< typename ForwardIteratorT, typename PredicateT >
            inline ForwardIteratorT trim_end_iter_select( 
                ForwardIteratorT InBegin, 
                ForwardIteratorT InEnd, 
                PredicateT IsSpace,
                std::forward_iterator_tag )
            {
                ForwardIteratorT TrimIt=InBegin;

                for( ForwardIteratorT It=InBegin; It!=InEnd; ++It )
                {
                    if ( !IsSpace(*It) ) 
                    {
                        TrimIt=It;
                        ++TrimIt;
                    }
                }

                return TrimIt;
            }

            template< typename ForwardIteratorT, typename PredicateT >
            inline ForwardIteratorT trim_end_iter_select( 
                ForwardIteratorT InBegin, 
                ForwardIteratorT InEnd, 
                PredicateT IsSpace,
                std::bidirectional_iterator_tag )
            {
                for( ForwardIteratorT It=InEnd; It!=InBegin;  )
                {
                    if ( !IsSpace(*(--It)) )
                        return ++It;
                }

                return InBegin;
            }
   // Search for first non matching character from the beginning of the sequence
            template< typename ForwardIteratorT, typename PredicateT >
            inline ForwardIteratorT trim_begin( 
                ForwardIteratorT InBegin, 
                ForwardIteratorT InEnd, 
                PredicateT IsSpace )
            {
                ForwardIteratorT It=InBegin;
                for(; It!=InEnd; ++It )
                {
                    if (!IsSpace(*It))
                        return It;
                }

                return It;
            }

            // Search for first non matching character from the end of the sequence
            template< typename ForwardIteratorT, typename PredicateT >
            inline ForwardIteratorT trim_end( 
                ForwardIteratorT InBegin, 
                ForwardIteratorT InEnd, 
                PredicateT IsSpace )
            {
                typedef BOOST_STRING_TYPENAME boost::detail::
                    iterator_traits<ForwardIteratorT>::iterator_category category;

                return ::boost::algorithm::detail::trim_end_iter_select( InBegin, InEnd, IsSpace, category() );
            }


        } // namespace detail
    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_TRIM_DETAIL_HPP

/* trim.hpp
Wwv/cRr9hLQE0itnuucVpSXxrVU36HGQCtpFcO1Mrcu/bR/8099Pfz/9/fi/I9AnlZxF+qTEZtVJcT+pk45InZR4BOqktsdkwWpxYUmZwtJhBYujqU5KadlK7TbF2v9gyaIZdVLqkaiT0g7bUUevUi2+UTQ7quex66gW39Arc0N/DDuqBStEapxIdVKfY9dRrpasV7ijPEe1o5pXJx01ZaY5o/zHcka1sNJZmUrno9pRh6vUiJatlNlRVx2TjmqiTipomTop8xjnmHZUCx+4mR014Viqkya2bJ3Mjio6hh11cHXSsCk/Sp80/ZjMqJZed3/SJ/3099PfT39H9a95fZLWJsFE/fTsk5PAnXr7jb3QJl0RB1VSIn7bih6k4nN8uGOhFUKIo/BpNwPxnqT1+GlFYBJM4GBwwYC7q6+VmNZQMxlrWBFl7GTtUsWWFNJEcZj1UOs99lWkh0JWzuLggKiQPBlriLnO3koYI5VJYLAPhdeM+ZHKJHwKj42b0yx3zylJOGjuxZG5mTnmlAzA8QWeEUH9U9zOfR5jIz5S8MwIaPME7w22vb8SFQDN7tmLJ+28uc/BdV9SZhNygeKkzt3uOSzVQspBsCwGOVGUL6nYhIVlPXK0hTquYlsKaHDWcoO+zw26eMuWj6a0WIMOSD6yFgVkR+OTiu28PmFMpTjXYzg4G4z9FdvRpGtBHcYFurvXeZ52nqBBP6D/ezepMW70vFMOS7c0acpBm3RtNIZKtKlzN3Kc4rG/TWMARHicHwFvjjlKqdiWa9TUaMoYjVGnyauoS6zYnBKJhgUPp0LGNGrZj2nC1aFV1+TQQA2uqk7uTYTzSN1KX9+7WYOP3N/1tsNSLs2aftBmXRM9x6hV65Ghp8f+FkYBSMAs45G6ThqVCv1xjQrsmWYuzN9ISjGv3WitQ4xZFq9kLvVCiztrjU94/r8PAnOCxrnd+39BlH9J8//tD18/+Xu2KlBcl3t39RG2atZBW/X9KJqr0KpMch8Ppn8dT/8GbtS1Mv1/u2jqhd+/UYHQJdR5jG8PJNBCsq0pE3BjmjedTWhV7ngPdQAmklEHPoXFAjTmBO99c37b+4n2LdSufcBYv3e73juvc+duR9iu3oO0a070aBUeoND/YPnI5scsi16nqMxIApuZwpiXSDP2EZVoFlpajpDK/INQiWkTjQHcVSbVUGn4nTnGWlmuHM7zPOZytZU+vmezAsWpY0fPO0KCRxy0WddGTzFmreh+MChku8pZCyKwGKDrP3/kN7dbBJro3MbHKMljfGSRiyHkBktsQi1x6SMkteBgpEZPKyXTajR1nHOXLFlYby5aWZ0M2mXxoo/v3azGpIfv73qEtI4/siXLWCpSAA0P+wrkm+DcD6ZFO710oQ/EUrFHTiZedKj4NKWi7khH7MQjaVVhBdUAL6JunF2xObN7f1Ds/Jh9DmV8wg4nZtdS9Pds1+hyJOe/2LsS+CiqM55kNmRJIlkgaLgkukGiUI0OahCoGbILs2RXsAJqFWtLW7G1FTWx2IpKozXpc9W2trW1rW3tfZ82xWqziSQhIZAQSUAqqK11ELlEJYCy/X/f93Z2wtFia2/2R5g37/jmu9/3jnmTGqmrZjxx6ZEdH8bqNMAuPsT53Urj4OOj4OO//9mfvF86v5HfVqq9tWRxBs7pimd/8Hf8ViIfqVu+tfEnO5LIXPA9b+bo3+xIHu28lGyBhzZjNaByfWaNfGItVLKUMksptUROEj6hZcexHJEi3wv+9u8ZfhgfExjMXwl+9DFkUOIX3xWsBuJTg/qCT5wqHhWJbX8TiYpLFlzacD/BPEXDVNmB4fpYQCExhjNK42PNCmTSOdGv0Jk=
*/