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
+sVUulgykp3If1Nn+tTAKMD1g+mQxYG9yqMtsTGqsfGT0zOtYM40+rNsjm+XWA6d1ZGFkn/6UY6xijbKNDrsJKAc7wdFWHk0OgLPA31YrdXEc1k918b7sK8kwVquCzDDaJoV8TRztbz3o+b9lctx7fazrBb2oYX5ymlEC/8SMHJf8xxqaLWordmkF06xmrT+63CTJtIcICs5ahm4IaKdnW4Js4WoNdRbtGdZjcW7kJrfYywnQL0HcpntniXtnmm2ezo9M6ueh8hVexq1MlZ6jRslmQ2tJiWGW7lVs60MSWAKOR8+Sv63m78fM7dnREvv8dGRS83sveSp2bGggRjnHPJBEVpevLft7QVe+NX8BK1auNiYM/vN7u0h71WENumjlJ6d+N2NCXTJVMx4z6cWwy16+TqjbIFu7u/Ed7YxOWyTFa+ScDjMz102e6cmmIsDqPjbc+k4CuJTObxX6+e/Vxc3tgq02pWTmlLbtrgxLtC5ISc1hrx/n6Rvxqr3zxT/NrgOK5Q8ZlFiCCW2CEpsNbeCiOBdjdtDKLKN455xRNPDqPrIj+tCqPdus94YjW5duZoBIUBPS2lV1M3CvVBwPxMI47bXdALc7L30xEogGUoHK38C5W9sdMzfgybADWOJ3dEI6MYYLGAzwnifErx5EXhrav5B2ZySi7xj0j7lHOqVbDAW9Ep3CqdyOHAiPd+mrj2Nd4lye7bmHuSxSnheSqgtCpewtmZkI9cwrogNVP4OEMAzXGUEXGONk2jem0QDaO4O+LOMHAM1qUikSazi/oikUERrrZQyb4/AdVzNl/sJVyK11kk0Iflx3CiEbwMCFUiXr4r9mkZW039gQ9RwHlGD6ILtyUXEG0iNrIJ95X2kEyDIH4/8Lt0Sk7w1M4DDWU5+jPC/V/BeH4W3hvCGGgWvr6Q12EHNAEDApn9RavuYT/H/6K7h/+3W74HxawBbgd8Tu7WPycP/Cv//Fd+I4/BT+H9Ad/l9vHv7Fn/j9b/p74D7rsvP0KqA9XxHfAfpJTLpve7bRISkM+VgfoFc7CtUz3WQrV/01VaMi2zA89Njd8fHkMXxn8haLYSELQtbxxhva/mP7mskeUMVF3na0LtHxXtaBbYt4tFxitwfQ4Z4YBp7MPgEwJMoys4WBb7rla0ODh8PeDvBv27B/+nWpEPDxxH8fAt+7sHgj4uAr71GgAsALPc/DoRPFPjaXtDvEN51bWSWanjL3tnuC5X3u8gTGwr09mND+RW/p8xvkNHrifR2s7wCANmfnx67iZUg0T1SRloSOY9nljB6It8U3aJq2usVopk+fHGi9OHv5lAfBnqTF4BObW7pgI6URwSYABRL6zFeXcSmIkVt77O9OVzTNK7LI3G9cbPgsjeLK0491TyuARpXa8F1LY0rfn5sDSHJV5dcrD0vM6fEkS3wsUxBSN2L4lAa4PhSoLuPfqO/DZ8RqidSSMJvpszaW6TMhcVc5iTSSbSOl+PHXtSwpN5HK3PrtgKwxXDV3cnNzREQDZL0MwuRz1m+BWrVH7ObrXlAU+EQKvxERbF5CEpUkDFATQDdaaFvbaGPCaMf2Dz6n2n0f7lLJi25TuYbR6y36xN+pbD1dyHBz+9FUBPLi5tSCBK4cb+4CI25G43byV06FISRP4ab5K77tb01AcbSFrrJ/v/5F6m/E11s627at8at6Szf7/AVz0yMCZynNkEo9ZXkJtIxRXvo1Wx8QlHaiw8xOoj+TsaDfq9GXgs+u67O9HIQ8BbPzOKJmlX0M/VeJ8sBQFvq0gWQ1SE6DoJ8zohPhOgeC/2GkUu+Z93GCfyO2BeE7W0cTr6GPRwJCtB8Ws/CNp6NPIkE1w/ISOc=
*/