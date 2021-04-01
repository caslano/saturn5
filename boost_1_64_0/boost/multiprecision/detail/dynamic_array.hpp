///////////////////////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock.
//  Copyright Christopher Kormanyos 2013. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_DETAIL_DYNAMIC_ARRAY_HPP
#define BOOST_MP_DETAIL_DYNAMIC_ARRAY_HPP

#include <vector>
#include <boost/multiprecision/detail/rebind.hpp>

namespace boost { namespace multiprecision { namespace backends { namespace detail {
template <class value_type, const boost::uint32_t elem_number, class my_allocator>
struct dynamic_array : public std::vector<value_type, typename rebind<value_type, my_allocator>::type>
{
   dynamic_array() : std::vector<value_type, typename rebind<value_type, my_allocator>::type>(static_cast<typename std::vector<value_type, typename rebind<value_type, my_allocator>::type>::size_type>(elem_number), static_cast<value_type>(0))
   {
   }

   value_type*       data() { return &(*(this->begin())); }
   const value_type* data() const { return &(*(this->begin())); }
};
}}}} // namespace boost::multiprecision::backends::detail

#endif // BOOST_MP_DETAIL_DYNAMIC_ARRAY_HPP

/* dynamic_array.hpp
P4j82RqP4wS65RzXGaWbNED1dnQaWtvneyySTbITh85m39bJq+qLz7gj4FjznKoCtTy8hovQKOZ37dAjottu/KebHmSRJYw9M92ZXnnJdB4v8Rn5UWdXqWr9J4B1Uhz9V4NnCIquUrPskcijmiYaiUr4qEjP0vTt+SUMNKYISAuMlHteg1Svn2TTOfTv5z9Enq0jlCmae1j74BKTFqMmTwYrzgNaJwkwiM7K4mkFGRT7H9GHJeAgwLCPmPUTRKEs+/yEYn6hHlWnFIERar1KcRoSILfbwhREDi4RGcxrEgLPh5bhBQGzE8kS2zSdukT74F28WLrRU90PrZ6JRNF+EGAD/u5M0ieagODgidCL9PBETQyoGnV7cqQQQ3oF6sSniqFOt52MOMKAoRJmov9STI/BBj3i3v0tZ+V427UtdIGRGp6DrDirg/lRNrTArpmLpfxMl1C7dxkKb2sGYK41iJr3r/sh/ob0aW41GfCFs5zjVZZrMD1WGvO2Hdgk+bBtb/OtGDjryPFrE6kSU0xGmwPidqyeoVmq18Pii0I/fUpUbg1nqKEpd2R86Q==
*/