/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_DETAIL_ASSOCIATED_VALUE_HPP_JOFA_100829
#define BOOST_ICL_DETAIL_ASSOCIATED_VALUE_HPP_JOFA_100829

#include <boost/icl/detail/design_config.hpp>
#include <boost/icl/type_traits/is_combinable.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>

namespace boost{namespace icl
{

template<class Type, class CoType> 
typename enable_if< mpl::and_< is_key_compare_equal<Type,CoType>
                             , mpl::and_<is_map<Type>, is_map<CoType> > >, 
                    bool>::type
co_equal(typename Type::const_iterator left_, typename CoType::const_iterator right_, 
         const Type* = 0, const CoType* = 0)
{
    return co_value<Type>(left_) == co_value<CoType>(right_);
}

template<class Type, class CoType> 
typename enable_if< mpl::and_< is_key_compare_equal<Type,CoType>
                             , mpl::not_<mpl::and_<is_map<Type>, is_map<CoType> > > >,
                  bool>::type
co_equal(typename Type::const_iterator, typename CoType::const_iterator,
         const Type* = 0, const CoType* = 0)
{
    return true;
}


}} // namespace icl boost

#endif


/* associated_value.hpp
Dao3Txjm04pnXmvwRD5qVGmHrVrJq9wvyq7/RKisPrL/y8Lg6rDCOL8j/2EBNHb6XlUYSXaxA5TjL0N1ZIbP5va6EhtVjSyZoHOhIkU8Mw9K8CR3hL4t35g71wBveHojmAwo6kOy8nMzM9vcmdtvalMiHcv7Lz3ZOzivXBrdGHTYCPavf93M++zBlJ/Kx8e+6/2QnAHUANRMmezGACkEHGcTpqkjurfLGOe1T+0chSX/SQ+NhfYkJVHkBVYE8hNPWRsyE5JPSwhLDUTwHFZLTfn6/ZfzJkMRiLuIvP8Cq2HrH/R+YAmnlMkRco0sOjPDetacCev/MFBpMOmtrBcnPawh8nsnjQrPgB7brDo+/8iKc3BvDucCd7ggv1CpgtcjALD6vUOUzjI8pOc7MyZsCU0baxZSBlbLYXj2C55TImMLDoOQf0wTSYLETjvF1DHNmQrDpVZt0rE7z+4d/RulvIDTXlI8fmcItv8MZ/5nYcoBjyKE0a9PG8mWPPZ8vnNHPGEjtTgnsyYCtnoU7V9Om/p8HlCwxM6MEVLLVsoavGOGDMnjHI7SrrvtMQ==
*/