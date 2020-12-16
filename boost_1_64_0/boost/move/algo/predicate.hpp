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
BZPLpPY/bZLdxtVKrr+LWW6A0KBdKLWg0n29BOcNlZnxU5UJA1gvMR8bK822nj7eefUhNp1IUXXTCFdsKkhLLMtDTIuIVTyC2kIbX5hTgNU0D866AiG7eMQlm51l5ueJdURqNIneKMH+GClJqpNJMuu/bzlx5rmD5EssSn3IFzuFnhNiAylwGQInsVNa+vVz/DqfXo700stMK2741dTzbZE5K0YaIcW7SkSodb0R3izpM04GzTDyVdphMqjEGKEShmXQOGOMSuiWQceLbatsJyvPKFZ43j+KIeR1htSk/fok4WtzUmD7/yQ1cfMnFZCK7ZmdJm/sb4DaSuT4hhi0GReoXcQNWuT4xJFK5Bh1aaYQn5ZmfPdw43aN7BqFbM35jMwhifRfaksiP7/FlkRGLjlkSWSL+t5L61zmYyEXLbUWMjPIswWQG7/NxbZlrmcqAvxGlNl3viJAVDDBfeK66yMncUJZF5BlPJdZbORGiroQNbg6lTNEdfgciv0p+ePvWGGlAQ3JrXnBqV/OA2mr+jusdpz7eZ602kGKmwjEJf+JKjDMZlc8heWBOeCyl5HoLfS66NrOW1Znai/tMIjvSYsbKdMQCLVlcnJOenQ266RauVZWh4qKHemrbqMGg2DMyTj3aTHZ9UaxVzEh9MrJVzJR1a0uOqQnSGb1TQ79U3HhiQSWoymIjiBZRa6B7mPNQA2wiIrlwS5Lc09DBBAApVlY0lDtt57HIp5UO6aqjEEi83VDZgxhF9TeIsZ5CiDqN8++3NHtEH1sDauDSxtl9cJGmb5wMyekLNvo84rJxqU6Q8gtPhQn6ca3dSjmuh0ydKYORXdcf+a/3HehHn9H0AgXqqpjoYYO84tw9z1euBofxwx1n9vpWpgaDtAc08QxehqHwlmTlcdY5H0k/DV/0JTXOTOrrfUvKy6R908adK/ivLT/d09Xpr1sKt6gMhXFJqLrwdh3Zf3HmcY9dmP4UfqRZ4hGWqrClU/rXiJCXnWJhY2GBrfWlDxDZG38TKdCgf7wzc6ZuLXXfzMc46nBMaxQXBIQHmEXljJtvIzRK9kTdliXsu5cAzSos51+9PSIgv6vsJnTckQ1OUcUOOXCkiaMKDmUh+usISq46TLHiMJQfoAKyTclKGOt5qotGowW2r9idEfSM0ZJnBlD4bap2mM9bxynx2jAXHmpg3eg5U6igQZleEiShU0Yo+5jd8hcFpCyX5MkjmzlhCTOJlJkECSN1PEKK7iKOaFYNPfJaSP1KBl6ig6FgDJc/C8fqZ376PFcctG/YTyvbzyU8Rzg+x/T5Xhu1AO5UfPRt3NajeUeTj57Ym4nhzPyM+5vMY6vOE004QMtx/FZMuLBtKE6BqEYqu3ar/Lh/seF6fYt6uT5G53j6bcd8s0I1VN3/F62FFfu4lNAPMVI7U/4Wp1lrpPrtgXbGZqeOGDczDYjkBepeCqHxsHVizKQkAbPTD2aApv5aNKLds0R724u1B5ZKHFCmOBTRZGxOIa1gi2O/2oYZKFHHF/qU8TgfCiGyZPBqr1dgvNv4N8MVdWUE5x/uUcdRyaSOxkRnrgSQC+oFJ4ZwdvGAm4BfsBE1yfukMyj6rNx8ZNE0bFMEeWgizbqMHFCjiQoquQoNGJTe9yOwhUGF/zYhUwYA73IY+X9okkiNbVAUWbO2SsupFMbonx4gqOdhwJyGB1I7+KUe7Jsm3bjPChcPVMTTaO6gKa2zhobRy68o3EG6toOj/fCWTXQ7NAwmdi59HY7KHskWVxMAiDBtE3tdTlqerKimK+t+nbNdlAM9JSGIJhiT7kcmRTGp9plFLTFnSaGJH1tv6QbEIEodYz+409AvoCj1ulZWOM=
*/