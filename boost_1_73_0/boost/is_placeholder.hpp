#ifndef BOOST_IS_PLACEHOLDER_HPP_INCLUDED
#define BOOST_IS_PLACEHOLDER_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined( _MSC_VER ) && ( _MSC_VER >= 1020 )
# pragma once
#endif


//  is_placeholder.hpp - TR1 is_placeholder metafunction
//
//  Copyright (c) 2006 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt


namespace boost
{

template< class T > struct is_placeholder
{
    enum _vt { value = 0 };
};

} // namespace boost

#endif // #ifndef BOOST_IS_PLACEHOLDER_HPP_INCLUDED

/* is_placeholder.hpp
ndw7sjs+Ubn4TkUeP26hEhq2lf2upmn8RQzEZfk21DF0OO4rSuiviAR2y1YxEYuPz/6MyTGFWWbm2fugdn/0Lsz/rsz8ZyZxoYwnvtUNLHQ3iNnf/1tFareNLwyf3YYjTe1T5PFT5XBhtNMCooGZDpLYBxvvklsYfeyelQUv8+tfRkNxasfh5zX2Sp64njoz2ZFLHD0ZYV68BN/16xPTdcMvs1vTPdlu61PFewZ2T6K8P/9d
*/