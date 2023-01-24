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
Xe9Yp//RqKPycmTcqlkv10f55nhOFFdZRB5WwUy43yVJ+tnqZ8ARt6hOGpdTVPFz1SpZ5vutJg4CoJOzQKk0Ig+o2DcvpDdt1ZAlN6dq7dsdZ+fjWhAneJmC1ZWvbRMcKBPdpbUHmA1rx6pytr8gQnwoE0b/E72O7hnEZ7Do8jc9jY3JN+Ixq40ks/n+7FqVTrF7ONruKTMCTbqI47k5LNDGp3lbePSx6l9ff18rmTMDil7j+njp0Vlqsf2sO3rxLGLUcioXEDbR5QdrM1/Ze7a2d2ZIDipclNV37l7G1VUiBEhlVgLL/uIS8bMQV5l16/Iy4vsrgyVygWga4xmX/pTnUwhxDwWedT/CcR0p6cT+X7xavVwEZR1J1DOFsLxeB1ZhbZlINtQjPsHuM+n/3HyrlhS7aGlqPVyppHPx2nKjJTVJiEshNUHEzn9yhYpmpVEtz76H1E6xJOnzylA1f9Us5voOyyiL0v9ZhM4dlKf8/yDafSXTfTGetUuag+eP51giSpZV61MVSN/IS1JvkUvw7A0OuXneqHPedDFQC93x84+/texHOGw60zx07K7dz8mbZ3YYWX4uNp/0xe0hMJqrp/zPzTW0aMNTWxHvWJGz7ji0lITtVU3fuzkax6gOo5DJ07ivf+beWXaKlrR0iUea8GS/Qt185IMj+eT9dbw5rGTNr1DQ6Y/yqN+doD7lC/jwiDkw6oPtJ0QC
*/