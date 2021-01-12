//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_INTERPROCESS_TESTER_HPP
#define BOOST_INTERPROCESS_DETAIL_INTERPROCESS_TESTER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost{
namespace interprocess{
namespace ipcdetail{

class interprocess_tester
{
   public:
   template<class T>
   static void dont_close_on_destruction(T &t)
   {  t.dont_close_on_destruction(); }
};

}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_INTERPROCESS_TESTER_HPP


/* interprocess_tester.hpp
rYE2GoHobkooWvrAAr2mlFLYrbTySAhpsyyrUIlFRaWKioqKbW0D0hoqJlRR00qVampjjXrTpBoxlbRF43/+mbv3bkgQ9fPxaS7czdyZMzNnzpw5M3PmzIwzpcnz5r3lUsf3lHkFqVm9deq8edOmv23evMukCcwrVL6zrpw3Dw1g3rzZ/EQ74N9iHekd8+a9E39K8L5r3lzwfClo9Uu08w3g0Vq8t6NOXsL7VtTXU3iXnAY/
*/