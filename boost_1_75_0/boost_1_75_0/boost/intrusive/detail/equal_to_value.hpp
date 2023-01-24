/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_EQUAL_TO_VALUE_HPP
#define BOOST_INTRUSIVE_DETAIL_EQUAL_TO_VALUE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>

namespace boost {
namespace intrusive {
namespace detail {

//This functor compares a stored value
//and the one passed as an argument
template<class ConstReference>
class equal_to_value
{
   ConstReference t_;

   public:
   equal_to_value(ConstReference t)
      :  t_(t)
   {}

   BOOST_INTRUSIVE_FORCEINLINE bool operator()(ConstReference t)const
   {  return t_ == t;   }
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_EQUAL_TO_VALUE_HPP

/* equal_to_value.hpp
pllXkdrHXKbrFBc4AoPod1el78fz+4ejVX9taWENGFAGyblS5lY8d4+rxS2QaVLgnuV+8PzqBG1Xef7J293H3Wd4v5Hz1dW+zdmFq3r9gTNXuxQq+C5zXD5aLidvLPO6Z03rj7S0Jb1Wfadh5WvFnoBeNEw7TPuedNk7lzF6anWQGkFj3KO389Pje+dmnK9/G9N7sJ1uOD/F7wZ7mLAIXI5VLjltQ/H+xyXwiIFIAjjKoEsGKjU+GFCJ281L5YCVNSDtjCPcAAtCNMnn+QWrtYp++q2fv7lX7xR+7VJLp9KD5BdWjjighPPk22R5SryTDY774sun/Cl9EZp5vtO0MH7bTpp579PmMH7L9y5Vy6YlerkhCCV7+eN4S1XBffN++a7rSpIWhUU8LYq+/xy5O2QMXPGuxX7vQfKq4rwnHMTxzIBfX9Ptblq0s5dme3RRBXjCFXbsZJ5vZemGuquD+7rFTuyerNUte0kpqbcUiqZSulVO7LxDVMHjr2H8ZnFI7lNvAyp5AFrwqqUW59sojxFO8b1SLuNlkYhwboEDvcWKzwhR9Bq239uvCpCQED+vadyXqFxQVaeFMDG/GZWSYe4AbhkOMdCftP4PYgFrjFafaY8hO/eT/U6Ws67WKctZ1yo9Jekg2F+ys1QOiE1RhoFCRobY/Jvn2CJFvpIRlc0mT5OmzcsM3HCrB+6IFJy+xL6UFDETyskQIZ+4
*/