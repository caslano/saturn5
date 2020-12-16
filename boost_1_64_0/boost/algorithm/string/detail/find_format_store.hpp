//  Boost string_algo library find_format_store.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FIND_FORMAT_STORE_DETAIL_HPP
#define BOOST_STRING_FIND_FORMAT_STORE_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/range/iterator_range_core.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

//  temporary format and find result storage --------------------------------//

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif
            template< 
                typename ForwardIteratorT,
                typename FormatterT,
                typename FormatResultT >
            class find_format_store : 
                public iterator_range<ForwardIteratorT>
            {
            public:
                // typedefs
                typedef iterator_range<ForwardIteratorT> base_type;
                typedef FormatterT  formatter_type;
                typedef FormatResultT format_result_type;
                
            public:
                // Construction
                find_format_store( 
                        const base_type& FindResult,
                        const format_result_type& FormatResult,
                        const formatter_type& Formatter ) :
                    base_type(FindResult),
                    m_FormatResult(FormatResult),
                    m_Formatter(Formatter) {}

                // Assignment
                template< typename FindResultT >
                find_format_store& operator=( FindResultT FindResult )
                {
                    iterator_range<ForwardIteratorT>::operator=(FindResult);
                    if( !this->empty() ) {
                        m_FormatResult=m_Formatter(FindResult);
                    }
                    
                    return *this;
                }

                // Retrieve format result
                const format_result_type& format_result()
                {   
                    return m_FormatResult;
                }

            private:
                format_result_type m_FormatResult;
                const formatter_type& m_Formatter;
            };

            template<typename InputT, typename FindResultT>
            bool check_find_result(InputT&, FindResultT& FindResult)
            {
                typedef BOOST_STRING_TYPENAME 
                    range_const_iterator<InputT>::type input_iterator_type; 
                iterator_range<input_iterator_type> ResultRange(FindResult);
                return !ResultRange.empty();
            }

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif
        } // namespace detail
    } // namespace algorithm
} // namespace boost

#endif  // BOOST_STRING_FIND_FORMAT_STORE_DETAIL_HPP

/* find_format_store.hpp
XIS8mCc6Y0c9wNNiwzNlem54phxvs2bKNhvPlFmB2/LI3/pQcd3xq+Nl8+AS/bochXe28VG4p2YRAmzkEuhCLZebIrJzFlvDEyRpWWqC5q4ec47twti70E3txRlViZSb6pj7N9YHT8uMKUrlw9qizvhxxRQdz0fQRUl8+uyYa3B/D0VLC0nHUUGZVFCaLdLgi+9JoeV4+vdoZvp3Og7kEgKCPA8iQ81+zQewMRc+8B7xAcy0KDYAcHCCVSrUB51wMuATuWKVAAdoKD+dqsWVMajhAAugoWb1ad7OGigSYJCGwus8IuIDqdRBkNipj34BjbmgU89cRrA+x5Cv6KtjjrCe+zTrQRwPRWMtcZ/VEMyJ9Sz2HsB6jLra06mhdoU5z1jhPEX3E+f5rboBSknMEerIdidS68q8oO8OV5n8ZwCA3YtomaDx9ce+Tc3QvDBDE6nq/84Mjf0XkPsCyCSsxXax/n8AMyYSRpy7PAbxJ+yFiRf5+pvySE/i/wtEHvnaRvLIOFMeef889OQSunVFbRoljbzcj6WRs03/B2XjtJ5xAfXnY2z0+csDsnPWt/pFyyJv4NuSRWhDVvs3uhCQpTp2QgdrB5BJxEPY0pn5ptwcnXWNXD4b1JF/aQft6qjFEYTH9NNMs3VsBNOMXRDJNNOTmCfzfptVBRQYZwoiVyNAeuDsqpnMsTrG0vidQBzrUiTxHX5igqvVbIdmdnk2YXbEZRa4w8zu1FiL2Z1gO5hYgLrsTxRE+uCgP9LW+eHQAfM+Sixgbwju0M8z2UwZmc15GYoPnEk8ZRDkBMcribM+dcza07boRKIJnIVSnvMKA3hSTFwpql0Ommq7rSi3eHtsUUZxKFY8/vSJNZeF2tEeo1publYJe69qBwZ0ZtPY5ym2Y9PYlA7iOXDqeYTVxVhvI6zt6Bt9K1zBGkVXB3kUqaGZ0sH7jtd3CE3BhyOHm3zhnCDxhdxY4Rf3ZxMwBlB47P3vSSUshViTng+vWB4hgU6166/Vcpjvxm5AQgKpZ6WWx9hEGxK1qH34roDHLsdQpTGWuF+gTr9KbH3rk/mXpPvNyVoe0do0Fd9Xz69ptoj59aSh59dumgLVCTy/WL5/2hRKfsMBfRRgiMoie+lMXrTvIbUFNDYTaoq1m9tneWYswSQ7pa2eG9O1REFj68xLwpPs/rBEkROrJYqb/CxRiGfTnDbsU9YSJh42hYkTYlmYcEGYoGrvcWgtoCVMPE5r/Fb8I4oWESbkGlFqaxEmtljCRNmRCRMPshNJP5/sWMLEX6ig2VHCBDvf7HYQYQKkqOo4LUwQ5GYspTVXau6BJV24x/vEPVgZxOwDcqmwD+SAjLBcvdhLbqXli1DBFaxEtrBQkcDs8QuWJ7gF9I4os5+wky+FnVDUP13bQxA2y7WwOZP+uZr+ucTawG0IS5x0EuNcBp5BB18k/+E33VhHfU+Kd3I1pV7pBL4yxIwCLOAoAUcYWW1ok9ds0h29kdS52aSH2sk5rOZJH9miedIMm8WTxghPWj6PeNLjqjxDZsa4drJHghmUzB2OvIx40jrwpN/MI570uU140v4LzI35eBJQ/m3HnP+xf2JPYfkDZE5mKftFePFeopX9NeiQTHGwvMxH16TWq7uHSydcShxBtku5ZlCp7LbiSWKXV+7E1XnNu3C4rWEq1X+PgHmHQjqp7DS5QyExxL2ePY0nXVzRJXqyYd5N5JFfpYbaNDMaRYis5ClIptsX55vJl9gF++Bz5RJuLn5l9W9mIodidK4U5FIXCN0ckcClwBNS+M5Hm9Ooergvwzf2zEsjTr26vxVLD+IMCG85/yFM0xtGsOxUwt9/CqojTOI9QgemGs0=
*/