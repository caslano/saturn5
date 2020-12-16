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
DsWRgvAG5+sP7EjqD5ydhXcGuQAnOjjjP0f8nUc3HU7XIzuSK64GHC52ln0WZapZjsmR88puWL2DzisjLN5z1Vt8yS59vgxNDRSlPtox7wkmRr37Sjt+45gof/mwxWfeQacP1B4ov3m81VDBKOWb0YnN5jpnxZjsDHMTjvLB64+heGWmU2vQ6RblAyp9HpXglWeOtviF6LqZ5WhAGaPQqm7mFEqOrJt5AV2L6mZOpetJdTOn0fXEupnT6TqibuY76VpYN/NC52Q8ZAUhYrXOxKFO8mrsFZ+hE92GcEdRl8PdRN2sTO4l6mZl1c0xLHWRT0pn+XRxti4eVDcnB8V+XezXxYN1cW7dnDwU5+vifF18gi4eUjenwMIGDtWe2FpUN4evgbo5Q1U7v9jMRPPsamKrv27OsLpLh/MM69v7BZHVq4/l/OWbfifvI67Du/AV2Erk7BulT3toNTKD4WtaK331P+zc2VrpP/iHFQ+2VubfPO+cQGtlYNdz65rlzOW/Zo8jBDpgb2QrvBmADz0vQx/F/NJjXDWi+uXrMPxpfQclyiqcEc9vxMccjOTMIpxjWH9RobroSjvhjM3EPb04GAUcerURL8HGbx5j1yYrbho1O+7LxMEMFTcFIgbOggVVmbdduTVO51qxxk7ciHx6eT8LRaKH+rSUbiRTamRssyceMBtxHj19oQZ/AfwV4a8Yf6X4K8MftHeLndg2yKbDawESr/wTHD67J/HHQQKEPkA3DAfGjqm/7Uocv4M6Tt1IOhaA8Cdd4C/JuKphv7Xjo//mT7/KHi3xD3iV/TJi/fUr9CkbEewee0lZCKI2hnCcvdqgzlbX+kJoZYfQPgp7i2WGVRdOGAhnWBgS4d5n9iSeCwTXW2aPlXi2KJSXoMiQamYlnvPjNrHyZLozkKRrNmqH8lYRvBDdD+JaqyiZg6tak0hkW0YbPbTc6A7HP/mlWz75biodHDKa8MD5fkUPNNcHe63E83hed6KFH5BLiPhxTzd5dFVtDAvPmldSSrBUCtYJIaMdsBbmq/UEC5AQbwa7QnkbrUQjQxtiosSPDLopoKtaxdDaQ/TSqtEdin9OQ1uIiH8dVRsKKLguK7RUF4PN24i5QioZZgW7AQ45eECCHzB8eRO1J8DtABwyNgJuCZWMCBlPozmA5O2zTCbnRCu4Du0tk7ISTQzgJA1gX8h4Bi4b840dgGMwwiPR3njawKCUmtdgiLLOCvZgrJK320o0c/NRAA2QGshuyhqdt1tg7IM9Md5jjf2W0Q9gJHHMaK0jEUPSkGWwhyqcDMgiZrobh6taSxB2k3ypVU2xPIGKTzFeQc4HJlnGbtKcUoslCXygOsAtBCy06pwa7GNye5CXaGV8g2obV/hTkbkzBPx8wR2sK+a25Ql6ALQAakN4lhjdQJPhjIdk8AjVC8TMPso5TThp9iEnjdkE3IkcBBhh77eMNcRrYyvVOJ0kYmzTmnpGWmknktJ2sgQTpLTFlPkO6CrpudEcynuOMs5EA508C9cQzjrIJwUss9TTuC6brHrBSVJDWBKUxuyF2ZjPaBUOboAWk2aS2t2XQvpsy3ya1K0cykzYCTkhV+nOUetFZ5AF/aMs01wvquxSSto8xjJWk1qK7pwLWNAciG5aCNqGnPMABkmIiO7OR1J1iMqG6L1vypwiOos9m3n74CAo64IwK1go2IOmonNTw6zA3Foej5Mz+MgtY23IYAynhwwyybzdy1tTdL4TWsy2DfGL1l0I3RVNjtSurKifXBKtl9PYRIZhtRPTB+aOkHkd2T1dQhAITlGWh2Fqyawu8Zt8qYBC0LXc7FneTI9k+8KsTPdKy9xvdbdYwf4QOqvJmI0=
*/