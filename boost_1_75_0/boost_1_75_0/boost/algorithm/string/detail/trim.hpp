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
fVD2NIsEDJ4KtjCsBkYS/Nu4Q+hB35TTSE9cNT5fnc4NIb3xT6GyqNcUgH+xqVLV64Q+67ztZHUVRfOiet8bKr+sEx7+3crK8wea1CMRXtg+8DBmu6bpXRGNRWEe3WgR5pwoKU2jfwxycsKoo7i07/MqJ5snDPKyNRTRosJNOzfS/tf05Qxs4lPH/rN7/6ejrxHwy6h9R4V8ZIyD6IwqIFXMWpq5LDlVfaEx7GkFqvFwPtM7X/mwBO8yAUrBcZDpe6kAOb+UqqMdYxNZ9HGDR94M9Pvv2o1tLuw1IoUoQVmyewh6hiTtOQHkp4i01jyZI+iBPctflMr976/XuVogwWs6/b4Yktg8r7rosRhGXMPfcoy7okd8hk04O5L/+IcEtM2nYnSzKUnd/AZjjkm8WKXD8TPowwQIGvPwXVG85qofqdDnHe4LlywMzcpuTZXsIdH5tvaGqvm96rUi8LtBh/fk7EH4URCGFwbDMVt/veYuXUnRNQWPhvbEu9qMCQHDP25NcS7yQPtzOIZu/BMxLeterKQ3psmMACxFXgHt7MkYdkrvxKO+GAdk78TisZhjRMMqn8ypkEmDrrKKqZiqNXSBE68U/CjOLgLWOPxH5EavBPc4fKZLr3obRgBfwPRBX1xW10lLEn4UfdfohfdMCMw5vuoTL+raMY1VecuGoUETpmLuZ0t5TlQAiic0HVyYZveoCY6jhXSOvNUC
*/