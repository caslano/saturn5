//  Boost string_algo library formatter.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_STRING_FORMATTER_DETAIL_HPP
#define BOOST_STRING_FORMATTER_DETAIL_HPP


#include <boost/range/iterator_range_core.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/const_iterator.hpp>

#include <boost/algorithm/string/detail/util.hpp>

//  generic replace functors -----------------------------------------------//

namespace boost {
    namespace algorithm {
        namespace detail {

//  const format functor ----------------------------------------------------//

            // constant format functor
            template<typename RangeT>
            struct const_formatF
            {
            private:
                typedef BOOST_STRING_TYPENAME
                    range_const_iterator<RangeT>::type format_iterator;
                typedef iterator_range<format_iterator> result_type;
            
            public:
                // Construction
                const_formatF(const RangeT& Format) :
                    m_Format(::boost::begin(Format), ::boost::end(Format)) {}

                // Operation
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
                template<typename Range2T>
                result_type& operator()(const Range2T&)
                {
                    return m_Format;
                }
#endif

                template<typename Range2T>
                const result_type& operator()(const Range2T&) const
                {
                    return m_Format;
                }

            private:
                result_type m_Format;
            };

//  identity format functor ----------------------------------------------------//

            // identity format functor
            template<typename RangeT>
            struct identity_formatF
            {
                // Operation
                template< typename Range2T >
                const RangeT& operator()(const Range2T& Replace) const
                {
                    return RangeT(::boost::begin(Replace), ::boost::end(Replace));
                }
            };

//  empty format functor ( used by erase ) ------------------------------------//
        
            // empty format functor
            template< typename CharT >
            struct empty_formatF
            {
                template< typename ReplaceT >
                empty_container<CharT> operator()(const ReplaceT&) const
                {
                    return empty_container<CharT>();
                }
            };

//  dissect format functor ----------------------------------------------------//

            // dissect format functor
            template<typename FinderT>
            struct dissect_formatF
            {
            public:
                // Construction
                dissect_formatF(FinderT Finder) :
                  m_Finder(Finder) {}

                  // Operation
                  template<typename RangeT>
                  inline iterator_range< 
                      BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type>
                  operator()(const RangeT& Replace) const
                  {
                      return m_Finder(::boost::begin(Replace), ::boost::end(Replace));
                  }

            private:
                FinderT m_Finder;
            };


        } // namespace detail
    } // namespace algorithm
} // namespace boost

#endif  // BOOST_STRING_FORMATTER_DETAIL_HPP

/* formatter.hpp
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
*/