//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_ITERATOR_HPP
#define BOOST_CONTAINER_DETAIL_ITERATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/iterator.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/container/detail/mpl.hpp>

namespace boost {
namespace container {

using ::boost::intrusive::iterator_traits;
using ::boost::intrusive::iterator_distance;
using ::boost::intrusive::iterator_advance;
using ::boost::intrusive::iterator;
using ::boost::intrusive::iterator_enable_if_tag;
using ::boost::intrusive::iterator_disable_if_tag;
using ::boost::intrusive::iterator_arrow_result;

template <class Container>
class back_emplacer
{
   private:
   Container& container;

   public:
   typedef std::output_iterator_tag iterator_category;
   typedef void                     value_type;
   typedef void                     difference_type;
   typedef void                     pointer;
   typedef void                     reference;

   back_emplacer(Container& x)
      : container(x)
   {}

   template<class U>
   back_emplacer& operator=(BOOST_FWD_REF(U) value)
   {
      container.emplace_back(boost::forward<U>(value));
      return *this;
   }
   back_emplacer& operator*()    { return *this; }
   back_emplacer& operator++()   { return *this; }
   back_emplacer& operator++(int){ return *this; }
};

#ifndef BOOST_CONTAINER_NO_CXX17_CTAD

template<class InputIterator>
using it_based_non_const_first_type_t = typename dtl::remove_const<typename iterator_traits<InputIterator>::value_type::first_type>::type;

template<class InputIterator>
using it_based_const_first_type_t = const typename dtl::remove_const<typename iterator_traits<InputIterator>::value_type::first_type>::type;

template<class InputIterator>
using it_based_second_type_t = typename iterator_traits<InputIterator>::value_type::second_type;

template<class InputIterator>
using it_based_value_type_t = typename iterator_traits<InputIterator>::value_type;

#endif

}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ITERATORS_HPP

/* iterator.hpp
nqoycUI3f2ETXyhk1iT35e+s+W39eC7/rF9WVPF4CeqzvBUPQF/+hjXd2s/6RYnF4rDi0NZW3sr+kr9Fllc95vdt5/G2tbe3VzFbk5GhYR9++R51ZpV3tnNCGxFU+L6T4u8OhL81haMOpX5TJ2bDPYkH7d379++ZnVnIiC8MDQ0NfZPNqf8XHGaR2fCu9H19fT2xA8xW/IDbl/9VLucWX7jLOz+3rKGhgTIDTNRvIPw1e62zcj811NbW4mWqN98dy+De/HhX35rbwKZE47J9agu4c9uyd05kZGQHFXBnjRw5sg9/YODte1/wd3ful/wowAv9Lf4vwp/yB4f8Lf7qAK/gv8OPKrxefsn/+k/0/9iXHb1+HdXNz9//H79k5fBHRUdxQmQEP3/1V/i72TF/eHh4/0x8Ifov+b9/b8V3/V//3or7nMr/foTvOfX7736+/+7n++9+/t/83U93oLxqf2W7gJCkpLSopORwya9wSEpL/yAuOhwzDO+XQVJaRlpcXFzih+HDJaSFFKTJ8QrS5EfHHG5phaUy0gtHi4tKSohKKIgY0akfsJIgyaHTFJcuHD16tIyoqLioNI0c5GBMIz8SNpbg0FUUFy5e/COuQ3xAgQTdiJTFFeB/3PIiQouXLVmqIIPrEBcSoTFE2JkibIYIjVMc05WVlh2iLV2yBDNIKkgrSEsKEf24ZCxf9YapqSptKa5AnEbUE6HR
*/