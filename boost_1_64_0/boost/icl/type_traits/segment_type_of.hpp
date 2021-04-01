/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_SEGMENT_TYPE_OF_HPP_JOFA_100902
#define BOOST_ICL_TYPE_TRAITS_SEGMENT_TYPE_OF_HPP_JOFA_100902

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(segment_type)
    }

    template <class Type>
    struct has_segment_type 
      : mpl::bool_<detail::has_segment_type<Type>::value>
    {};

    template <class Type, bool has_segment_type> 
    struct get_segment_type;

    template <class Type>
    struct get_segment_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_segment_type<Type, true>
    {
        typedef typename Type::segment_type type;
    };

    template <class Type>
    struct segment_type_of
    {
        typedef typename 
            get_segment_type<Type, has_segment_type<Type>::value>::type type;
    };

}} // namespace boost icl

#endif



/* segment_type_of.hpp
nDLNn3w0i+4g13iGckUC/HxTHt2Qj1mKyLB//yJQoTLOcNGOET+OQyNkJ/7DHYBGjkG+E8yFGkYuvORvX55jO0GhU2fDSZiJisQqahqDIYEeiLZmcY/L4K6lvdCML9wSxsUq1uodCaVyJfHLCKhJWs/hN4ZIcDXuiicE6ttzhKReaVLg1mBTGGart7xjL8SqOIZa3+MOZtDcnNpM8gygJww7vQgCw8O2zcdY9TDRlRyQTAvoR4x7fK1X8xXuRuTwnD8w4gCaaMZ3qzWPo3fMEMD14jNnrgEpQrwZKzPgm3AxjGxfsZ5KXcDbxcN4btRViFDolnfGEaNx6Sc16Qd/DzzIEh6xs7ikunXIlt7Si09ygj09Yd+d2U95YjcNFczz02hnGidUAo1xmuz+HbWMs5t83KXRi6Bfr6YUjAXHgkeHsLoCEMhRxMfI8gNTXN7D5yOOywtatUqxzpThPl9JE8eaRdORJTF/f75+8nBFgl6CYfqjAxtmUfAKJfBGnL3hZuwAmQ8OJeeBAbL53CvAy8xHafaT7zVwitu/5Zq/TgYI7aHNvyS3pt9GnQ==
*/