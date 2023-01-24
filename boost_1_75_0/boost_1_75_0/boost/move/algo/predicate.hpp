//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_MOVE_ALGO_PREDICATE_HPP
#define BOOST_MOVE_ALGO_PREDICATE_HPP

#include <boost/move/algo/move.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <boost/move/algo/detail/basic_op.hpp>
#include <boost/move/detail/iterator_traits.hpp>
#include <boost/move/detail/destruct_n.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace movelib {

template<class Comp>
struct antistable
{
   explicit antistable(Comp &comp)
      : m_comp(comp)
   {}

   antistable(const antistable & other)
      : m_comp(other.m_comp)
   {}

   template<class U, class V>
   bool operator()(const U &u, const V & v)
   {  return !m_comp(v, u);  }

   const Comp &get() const
   {  return m_comp; }

   private:
   antistable & operator=(const antistable &);
   Comp &m_comp;
};

template<class Comp>
Comp unantistable(Comp comp)
{   return comp;  }

template<class Comp>
Comp unantistable(antistable<Comp> comp)
{   return comp.get();  }

template <class Comp>
class negate
{
   public:
   negate()
   {}

   explicit negate(Comp comp)
      : m_comp(comp)
   {}

   template <class T1, class T2>
   bool operator()(const T1& l, const T2& r)
   {
      return !m_comp(l, r);
   }

   private:
   Comp m_comp;
};


template <class Comp>
class inverse
{
   public:
   inverse()
   {}

   explicit inverse(Comp comp)
      : m_comp(comp)
   {}

   template <class T1, class T2>
   bool operator()(const T1& l, const T2& r)
   {
      return m_comp(r, l);
   }

   private:
   Comp m_comp;
};

}  //namespace movelib {
}  //namespace boost {

#endif   //#define BOOST_MOVE_ALGO_PREDICATE_HPP

/* predicate.hpp
9jJZP/Og0T9j387+mfPbOeTb3MaX2EeDnJx7QR1Q+uU+qZfR46qfcb/eKQD8CNL9P6N2XnQ3YepTugh77byzi5p5/bP1NWqLmC8FzmNxo9yhzJF0sV7wSdOEdtRI+pGSgIxyxZGf8bF6BYA3IQ38LG3L1kZts963PlOxFFbbmWFqD94ofCrQrYb6/3wLtv3EGJRL9Fxm6zgvGtnI1/YEAJogtW9M26E6HNZoKyelFV5U34PXUVPUlo2WTPNHqMENsgHSVZlYJTcoB9XHsdIu14KcMA3NwD5oaVyNmLR7NNBu3ZTZ07T7AOB7jNTpKADDHgWB4lF6hmGROe6Ay3RUrE79pl7Sdm5hZ9vZGcaIR60xmQLL/+bhRV/hUhBeq5VtarXW7V2s3+sr8IbVsJKU41KlUAlEqIlXW9PKdOojGhWBh8xB/vWMjlD571FOjxYCsPZRkz/l+lObSJXytWKiL1kEknSxaOAImkE2Akz1ydSemcm/gCJ2CB6vE1zqTqhr4QHyeIk83oAHXi9dZX1fetRmK5+1Ceb/Jj7/N1kD9RGgOI+ll/FOmP+a4zw9sYn4/5J3C5BdX5XaZOf/INPO8d6+ybmu1uN9lC4Msi3tspd/HDJ7efkdg8qvwrstuuK0aX/VjuMMZL7gOD4ehONt/I2FYwTgUAkNZvTvMU53xwFQCKnqMbqmjnzi4vaOJY9Zqg9iF7YLyx8Jc0Bg
*/