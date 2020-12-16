/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_ITERATOR_TRAITS_HPP
#define BOOST_POLY_COLLECTION_DETAIL_ITERATOR_TRAITS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <iterator>
#include <type_traits>

namespace boost{

namespace poly_collection{

namespace common_impl{

template<typename Model,typename Allocator>
class poly_collection;

}

namespace detail{

/* (Internal) bunch of traits-grouped functions for const-preserving
 * interoperatibility between iterators and local iterators of a
 * poly_collection.
 */

template<typename Iterator>
struct poly_collection_of /* to be specialized for iterator impls */
{
 using type=void;
};

template<typename PolyCollection>
struct model_of;

template<typename Model,typename Allocator>
struct model_of<common_impl::poly_collection<Model,Allocator>>
{
  using type=Model;
};

template<typename Iterator>
struct iterator_traits
{
  using container_type=typename poly_collection_of<Iterator>::type;
  using is_const_iterator=typename std::is_const<
    typename std::remove_reference<
      typename std::iterator_traits<Iterator>::reference
    >::type
  >::type;
  using iterator=typename std::conditional<
    is_const_iterator::value,
    typename container_type::const_iterator,   
    typename container_type::iterator
  >::type;
  using base_segment_info_iterator=typename std::conditional<
    is_const_iterator::value,
    typename container_type::const_base_segment_info_iterator,   
    typename container_type::base_segment_info_iterator
  >::type;
  using local_base_iterator=typename std::conditional<
    is_const_iterator::value,
    typename container_type::const_local_base_iterator,   
    typename container_type::local_base_iterator
  >::type;
  template<typename T>
  using local_iterator=typename std::conditional<
    is_const_iterator::value,
    typename container_type::template const_local_iterator<T>,   
    typename container_type::template local_iterator<T>
  >::type;

  static base_segment_info_iterator
  base_segment_info_iterator_from(iterator it)noexcept{return it.mapit;} 

  static base_segment_info_iterator
  base_segment_info_iterator_from(local_base_iterator it)noexcept
    {return it.mapit;}

  static base_segment_info_iterator
  end_base_segment_info_iterator_from(iterator it)noexcept{return it.mapend;} 

  static local_base_iterator
  local_base_iterator_from(iterator it)noexcept
  {
    return {
      it.mapit,
      model_of<container_type>::type::nonconst_iterator(it.segpos)
    };
  }

  static iterator 
  iterator_from(
    local_base_iterator lbit,base_segment_info_iterator mapend)noexcept
  {
    return {lbit.mapit,mapend.base(),lbit.base()};
  }
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* iterator_traits.hpp
CwJgHXy/bJQN4XCEsUr03XiyHb5uYIsqgGkrEv3G0ce+Y2CrMC/bQUf0R0cf+6E53uOgByVKNJqjj/3MKFucdZOY5obJdvu1WbYkF5Y7wdfRx35nYeMszLFVAt9gAvsXqz+gM6JH1G0xgf2HIW8ZpB3cQq3rjORlffc/Zt+FugQHawF9ujXvvovzRAymMsqq0AvQDoTU+W83sFDi4J6cAPsMB3Ynxx7M2lEUxb2ud7zoPaOw55v7cuwT8GIJgih1Mw/uZsKP0cQ+3JAhQsSoqEw73mkcQg3tOthDWLLdZEXuw/TlPYNwbYnbb+CwXKErJoEX2bhDBi5OSyiPMAEft3FHOG5fJ0+hrVZQg2jAKJxn4PxKxCSE5et4buECAxfAxBmWbWyfbFxs4IpOu8TuHKt3ZOEyE5fATuljPMU2rjJwPbEJ7ZUdr/At3IyBw9QbdoME5k8bd8LAZR2oqN247R23cScNXIU1AnsGbEGOWrhTJq5C9K0ygNoaWri+mW/UK7O8G3n+cQu3aODyKCwxjXa9pLJwQ7O8WBY6FSwggV2ONbMfJN04qarUO1pauLGBS7N2u5sFbajNFu6sgSujKggzbKPbgYU7b9WfH2RY7r3ArpcLpnyIl4ZpOPX8Z1q4iya/sgsVptP2Qrs9XmfgknYZVD7W4erpFu5NZjnKbpCWMJcnxyzcJQMH607mZyVCgdrleKeJyyLc9/cxLm1+77X4BXGWVujPdjk+aMoX53HcqTB32fleNnCYMsJuJnaV9nzwCQMXBkEvCQpMhTbuM1Y5sKtspxhHtnyfN/mhv2S9EHp2bOGumOMc9/fTGPV33O7PXzZwcRqGUR4n3vEe4fYR7qscV2AbnsN+gz3HwnB1JMyGq2NsCKhQB6UdgaeB6RgOvmknzLEXIBdwdfe3SSjTXePpKjy1H/pBgKOGebGdqWMg4SeOlik7ddb1D54Ok1ovLoMcWz2vjzR0NiHfGthYV3vpgbS/73i3eVbW63QK9LrKU+f5E2k9KfPDKS3JXHR6aZ6Dx8oq38VNpjti5ImBVaXtIsRMhsI6UnqyrJWRLvGqDMp8O+ygcuWDRo70uqxDI33oQXHudnPM8Nbm/oWrz5dWmbZMe9FOG+VpD2dvZlp6y8RK+0ErbQdqWruD8hppabdopf2y1T4YTFXl4+AIAZoGZ6ADHFA3oKmeddq/PNdMG8O4UeTQfClIGH+EQqaVbfRDq42ybhEEEexYsi+uYj98Gk4w1Eb7ZD/m6TIvS/2gHfiZ3gvLWb6lx9l1SkP75yLGSWQa4+mN2gIO+8ZgZUmKKNO03sPHJtbyEJpk1nT7PmqTny7INDsoDeWT9BC9Mg9lbZhpZB3uQho+nsNuDrMgUjXRJkV3Ef4QC8ruz+rwEE8LxQnaK0yT2FmuKT8EVOJknM4M6fiYxoZU2Fwqbwn9/DT6S2NnkRf91ZiW+S5SehqXGY7lukXcQXL0EtzqN0vaeqqsn/Nm/URFVoiknjgExriaQ6hW1VVkXjuWzTLGYYwaiop6EtAuPBNlfJNVxm6c5fBQyM2xrOI8qzLK9J8x0qd4XyWDZR1zgTWmVufHuB6E1/JoMpDt+v33WGMDfaHXSXzkL3r4mRVco4EA4ux74tz72nusc8IIeif+w/zlPJYa1b1kDX7jg4nzpW3vNc8I4iqFSStKHLxEtFn0GHEdwqzLh3MemBqyOO2WcagGne0SIMsj0wdIz+dVeCoEYbud1G0Il7chBGgmC+q4tPN4EDtL3CHOASmUa38wWiAvIX1H6JZTMbg9CyD+k/zGt2ZYegzQ5veX6Rjip33zFm8jsaI5JEzn17+dg05s7k11tP22zE97bh79U/s=
*/