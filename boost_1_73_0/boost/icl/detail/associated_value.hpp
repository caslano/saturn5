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
XIbwkIYVsgY9F4i9IYlHftr79ly07xXSw/PKDPr6QZU8MmB/LZQp8/h0b3ZCDe+uZsFrWPDRnFg/MtQMHWOyMk8EkOBQSzhukOSA0I+4bjjpwZ3vbLnO20cfeMl0+sm3AN471jddgL54L8hvj/V/Ag/ZO4ADSLT3IocRhnnv98+fuSDjKc9rvj857a7H0N4uPnp6hh677GM5g9NHQCEPb8MAfBhNSa8m7YmJAA4FRemIh2bv
*/