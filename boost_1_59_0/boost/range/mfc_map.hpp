// Boost.Range library
//
//  Copyright Adam D. Walling 2012. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ADAPTOR_MFC_MAP_HPP
#define BOOST_RANGE_ADAPTOR_MFC_MAP_HPP

#if !defined(BOOST_RANGE_MFC_NO_CPAIR)

#include <boost/range/mfc.hpp>
#include <boost/range/adaptor/map.hpp>

namespace boost
{
    namespace range_detail
    {
        // CMap and CMapStringToString range iterators return CPair,
        // which has a key and value member. Other MFC range iterators
        // already return adapted std::pair objects. This allows usage
        // of the map_keys and map_values range adaptors with CMap 
        // and CMapStringToString
        
        // CPair has a VALUE value member, and a KEY key member; we will
        // use VALUE& as the result_type consistent with CMap::operator[]
        
        // specialization for CMap 
        template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
        struct select_first< CMap<KEY, ARG_KEY, VALUE, ARG_VALUE> >
        {
            typedef BOOST_DEDUCED_TYPENAME CMap<KEY, ARG_KEY, VALUE, ARG_VALUE> map_type;
            typedef BOOST_DEDUCED_TYPENAME range_reference<const map_type>::type argument_type;
            typedef BOOST_DEDUCED_TYPENAME const KEY& result_type;

            result_type operator()( argument_type r ) const
            {
                return r.key;
            }
        };

        template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
        struct select_second_mutable< CMap<KEY, ARG_KEY, VALUE, ARG_VALUE> >
        {
            typedef BOOST_DEDUCED_TYPENAME CMap<KEY, ARG_KEY, VALUE, ARG_VALUE> map_type;
            typedef BOOST_DEDUCED_TYPENAME range_reference<map_type>::type argument_type;
            typedef BOOST_DEDUCED_TYPENAME VALUE& result_type;

            result_type operator()( argument_type r ) const
            {
                return r.value;
            }
        };

        template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
        struct select_second_const< CMap<KEY, ARG_KEY, VALUE, ARG_VALUE> >
        {
            typedef BOOST_DEDUCED_TYPENAME CMap<KEY, ARG_KEY, VALUE, ARG_VALUE> map_type;
            typedef BOOST_DEDUCED_TYPENAME range_reference<const map_type>::type argument_type;
            typedef BOOST_DEDUCED_TYPENAME const VALUE& result_type;

            result_type operator()( argument_type r ) const
            {
                return r.value;
            }
        };


        // specialization for CMapStringToString
        template<>
        struct select_first< CMapStringToString >
        {
            typedef range_reference<const CMapStringToString>::type argument_type;
            typedef const CString& result_type;

            result_type operator()( argument_type r ) const
            {
                return r.key;
            }
        };

        template<>
        struct select_second_mutable< CMapStringToString >
        {
            typedef range_reference<CMapStringToString>::type argument_type;
            typedef CString& result_type;

            result_type operator()( argument_type r ) const
            {
                return r.value;
            }
        };

        template<>
        struct select_second_const< CMapStringToString >
        {
            typedef range_reference<const CMapStringToString>::type argument_type;
            typedef const CString& result_type;

            result_type operator()( argument_type r ) const
            {
                return r.value;
            }
        };
    } // 'range_detail'
} // 'boost'

#endif // !defined(BOOST_RANGE_MFC_NO_CPAIR)

#endif

/* mfc_map.hpp
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
*/