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
2UVQAT5a92OmqbynB0GnAZ+locLrXUiPgirl48ZCLCnZ0hmxFu+roR6asqbRS9pPqLdLaj8ORce/K3MxjBh54kTMfVsuXrt8/GvN3u6jPhnAAxvEurbOvG7GV5FrH16ypcuh/Y/cuYe/yhPrumr39Ztj3+v+6OSbP//J/JMzNvJo37GupKSHyz878EPPsg+u71P2YJ+9jNIKxLo2v9c5Y0V40T/yLuz83O8v/HgfD4Uc65qQUHPixllzh4cvmNs=
*/