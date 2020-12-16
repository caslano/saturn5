/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DERIVATION_VALUE_TRAITS_HPP
#define BOOST_INTRUSIVE_DERIVATION_VALUE_TRAITS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/pointer_traits.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//!This value traits template is used to create value traits
//!from user defined node traits where value_traits::value_type will
//!derive from node_traits::node

template<class T, class NodeTraits, link_mode_type LinkMode
   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   = safe_link
   #endif
>
struct derivation_value_traits
{
   public:
   typedef NodeTraits                                                node_traits;
   typedef T                                                         value_type;
   typedef typename node_traits::node                                node;
   typedef typename node_traits::node_ptr                            node_ptr;
   typedef typename node_traits::const_node_ptr                      const_node_ptr;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<value_type>::type                      pointer;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<const value_type>::type                const_pointer;
   typedef typename boost::intrusive::
      pointer_traits<pointer>::reference                             reference;
   typedef typename boost::intrusive::
      pointer_traits<const_pointer>::reference                       const_reference;
   static const link_mode_type link_mode = LinkMode;

   static node_ptr to_node_ptr(reference value)
   { return node_ptr(&value); }

   static const_node_ptr to_node_ptr(const_reference value)
   { return node_ptr(&value); }

   static pointer to_value_ptr(const node_ptr &n)
   {
      return pointer_traits<pointer>::pointer_to(static_cast<reference>(*n));
   }

   static const_pointer to_value_ptr(const const_node_ptr &n)
   {
      return pointer_traits<const_pointer>::pointer_to(static_cast<const_reference>(*n));
   }
};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_DERIVATION_VALUE_TRAITS_HPP

/* derivation_value_traits.hpp
2BXIAM2hRDSraaAd41boPNXtHoNdga6gszkxneurKjYoQpOis7mDdLr2D7rG05kJOlvapjM8uFYmV6ct54nW1w20Zqk1TNu0cjBIjtbDHaTVmbf2ZpppPXYWWrFD2lxR3lC9eVNy9B7rIL3uWJBlpvdEQnq5Rk5yLDjRQTodHjiVlWAdmJBOLgdkHEiO1lMdpNVZs+7Jjqd1IXBbE9KK/dLmuqRobO0gjW7/zzHTaBW2SWNYvWWSbW8VdoxW4VHao7Bi9LvlqLVgYlq3lVaWN5QnSWdmYfLvEonrzm3Lc85tbjO+S9TXv0Fz+xS1UeZapcC1gcNekmUvOk9ttCM3nt6gWlcmohdOpuck6SzuIJ3u+jcvns5ctaZsi05uKZJd/0w5T7SeNNCap9aUiWilsRQZ8uqTo7XkPNEa6hZPaze1pjwrrXU19UnWa9l5onVovrlv1SakFS/xI8v1pGit7SCtUx0eyDfPz6FEtPLFZrK8GjpPdO7oHk9nvlr3noXO0oo1SdHZ3EE6HXnYcer9r/GE341sACxQ614jndWbquPXDq5s/AGJU+YZ4Ukzr3+1eWWuxK9v2FxX5cqfH5bwlZ4LPenGuUaPXyHnCeqEx6w7Scd9XHBly2Y6GwCuwRaLZqNuU5EKHwHJeTf62dZ14nc95r1we1XL/LStVj+PeLQo2q7si+obqSSyu/SghOPNO+ZSNafPQ5qD4OYT3g6kT8AtwO/KnLAcek7w7LoCMyCL/qekbWHR0vb8O1f82C6UQ6u6zmVdO3Lox5Uf61TnpxrNRoHF+9U91N6kj4mfIO/W+qUFWvT6eFbi9Hbr77T6jrEHFEri/X7U3okKYt9gPf0Mrhfos/qa6KM+Yc0Qm877Oq2PSfxu5nVf31h97rAf7qSt6cv0C94Wa6xo0elk7ANIy6xnWeNXn+B8GNSsMfUNpGHU3+vS0SDh14ACH9bwtrHPMI04Xi4gDT0kvNkqAtXQ4WAtsgrddnxUwnzsN67taJf+ORI+GrFy3f62U/zGoL8Ntvqi/dMs6Q9of+kTbt9YKGc053ZuEKUHP66NdFvlrj/7Q7ReYn3vc8xgL6A3/Ir6mfitHnIwWQEkNQdIGmyDJ3m+apnX6cA99/nCGRuQB/WIxNjYol2ArkwoA66PWusmLmNl+aaqpMpYrJXxGsGVqGa9guehjCqPXOahz+d39uGZPc+N8uH6qbWnuYztlmeXkHaD/u3ochJX33P1CCZvB9lQ5ji9D3OdMtMeAKK4ZR+AMtcmLjOXhKX1DeUVGwxld8/+GySNPPNaUauLx8/C17Xnoc0f1/hanyv29Ivpuyx/s7n85yTDbm5HWZv/A2V12no/L/QXkr97sawticsqC9ZqNLasApIsb0s7yiu4PD9uQluU9Of5cZcU2Kc5u372ZM5WtXoxjm3bBsTzwCAlD0xQL+2Rr51w+7G7njXbOulAu2ewfFzDRfH3qoHmsp0yl+3cZIhJlvHUeS6jM243DOJ7SStiq/4ClLE1YRkx75c31jQkyc+t/ZK3kaXjTovYvHTXkH+T8C5c33Ldf45nRSYbWjpfV9I+ga5Pa4hal/Q31wsN+SRVJ0X9k7fjQ1y3L1/ewfLqNn308s6+IIbXWd4p5vK2SwY9Ja68iGse04B77nweVUbmoffn0UPMZSwxl/GcZNgl7WjbkvNW1ngbTesvjJeBD1XyNXNZ2y0DL+ufvAxcx/X6FK5kZNx7lcXw+4rzKC939uuKhlzSoPeB5UPj+/wwtZ4z1xmNWiW3F0EaJptW5jVbTB2UdLDP6/asdB5ZcpF2rs9yD1frt4Tl5b4uSR5p7t8+m0fNMeW+4hzLncjmkd7WO6jLP58=
*/