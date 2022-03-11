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
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
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