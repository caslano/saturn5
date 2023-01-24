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
/OshyparKf48jXYtxAX1yg6pgJ1Rf/mqPpmC2TJHm4/fC9DNsxdtNG9PaJoueOu6ZfsiQJibxmknfn053L14DqK0PulmQogC3KRcDhmxkW/RYq+kwRndaCjmYNjJ23grogsBMijeIWY2XBbw7HzSnibcdsIRiyItRdh3Wm9wahR/NT1c22WqnVSOG72GZRf0WE7R1XwSaqoazCeyqYvTDwsTISPSffPj5XaphouPv7FPSw0TKzJN++Xb9+edEy9GXnmiIGGtnJDWFNno0ro8VCoCIUUJJ4mIX6g/OvofJGoQ943gJ64p/nMWe6f6lcVii+NHBW+dO1Tmy8cbXH7bZGJEHUuAYsjNFNVNjZrUOzKjuqdqc5vIPDJHjGwKrr+AWdwFBr28g5KVry2s9Fnm2lELDplq5Y6FbPerXHmOUznbun/Isid/22Gta4ncr/cQ39FqA9bUc9FGK5YLwUeLBbn+7520u4DPrU9whIiuaoW6x9jpif4mtfpkNzLUG0/uOfgNLrF87+4HrWYVlFZ9MmVSgRnaHwWpP7knBnZRhv1WcV3mvJk3RTpoTHpjcqw77lDCPnlEFKp5enNFoQocrELmCQOIMnshHbiicAhvj+lhQnnB84SIUMKK8TRfzaesnAfLXGvi21bOyEC6iGN5JsLgt8wJ9mi9WT0gaLsFpdnGd8MOYZcAqrbWNDto6/xRBDixrlbZ+aDgdT1j
*/