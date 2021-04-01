
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_FUNCTION_REFERENCE_HPP_INCLUDED
#define BOOST_FT_FUNCTION_REFERENCE_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/function_type.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> struct function_reference
    {
      typedef typename function_types::function_type<Types,Tag>::type & type;

      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,function_reference,(Types,Tag))
    };
  } 
} 

#endif


/* function_reference.hpp
d9XkGXp6gjHnYKIxNkuN7y4mysnHDxK57P/DTbXn83guAVNwM6pCy+piudkrfsg4Zw/TqS4eJ+JLDXPApHfZ873vj8YxYCtj1GRKPcrMxQswabrmuvttHF8kNW5doVLGnkH9J2OeFlSHWO66NE8Tms3i7geFeyU9blWVAz7lwGDjhsxwfBd/g8kCJ7yzkQHJCWppCNF+eFEkP1uqwDG3SfSp7fAgLZQjqqM6cMBLHTxCtl8hDqijNihxxvsdVqhVA9alysuVM/fYQQ8qPpuvgEPPLVIIN4BydwIz+6PmCEZnLqkn5+FsoI6TvsHQbsnZxc6hqA0rQsJTrYQ0SB8WM+BtdD4d8cPXI2YU8vp4neuIRtcJLKg7YB66dxwf8vkwqdxWrRwG0UH7U/8CJJg+649QxiZtG21SNwHJHwLKuuNMfT2MFcZhrUSC1QOR302SG9e5e5V1TR/9M7XksHSVq22m6hBBhIzMnk0ZtdzlqSpeEGCwonIr94mFEFSUa66nqfYcKhMKHHjDkbkmsJLBmo0ZYwB16fQ9GW7b+lD6kdtfvHCoClJTRua+9g==
*/