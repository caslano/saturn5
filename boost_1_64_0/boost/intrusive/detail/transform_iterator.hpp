/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_TRANSFORM_ITERATOR_HPP
#define BOOST_INTRUSIVE_DETAIL_TRANSFORM_ITERATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/iterator.hpp>

namespace boost {
namespace intrusive {
namespace detail {

template <class PseudoReference>
struct operator_arrow_proxy
{
   BOOST_INTRUSIVE_FORCEINLINE operator_arrow_proxy(const PseudoReference &px)
      :  m_value(px)
   {}

   BOOST_INTRUSIVE_FORCEINLINE PseudoReference* operator->() const { return &m_value; }
   // This function is needed for MWCW and BCC, which won't call operator->
   // again automatically per 13.3.1.2 para 8
//   operator T*() const { return &m_value; }
   mutable PseudoReference m_value;
};

template <class T>
struct operator_arrow_proxy<T&>
{
   BOOST_INTRUSIVE_FORCEINLINE operator_arrow_proxy(T &px)
      :  m_value(px)
   {}

   BOOST_INTRUSIVE_FORCEINLINE T* operator->() const { return &m_value; }
   // This function is needed for MWCW and BCC, which won't call operator->
   // again automatically per 13.3.1.2 para 8
//   operator T*() const { return &m_value; }
   T &m_value;
};

template <class Iterator, class UnaryFunction>
class transform_iterator
{
   public:
   typedef typename Iterator::iterator_category                                           iterator_category;
   typedef typename detail::remove_reference<typename UnaryFunction::result_type>::type   value_type;
   typedef typename Iterator::difference_type                                             difference_type;
   typedef operator_arrow_proxy<typename UnaryFunction::result_type>                      pointer;
   typedef typename UnaryFunction::result_type                                            reference;
   
   explicit transform_iterator(const Iterator &it, const UnaryFunction &f = UnaryFunction())
      :  members_(it, f)
   {}

   explicit transform_iterator()
      :  members_()
   {}

   BOOST_INTRUSIVE_FORCEINLINE Iterator get_it() const
   {  return members_.m_it;   }

   //Constructors
   BOOST_INTRUSIVE_FORCEINLINE transform_iterator& operator++()
   { increment();   return *this;   }

   BOOST_INTRUSIVE_FORCEINLINE transform_iterator operator++(int)
   {
      transform_iterator result (*this);
      increment();
      return result;
   }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator== (const transform_iterator& i, const transform_iterator& i2)
   { return i.equal(i2); }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator!= (const transform_iterator& i, const transform_iterator& i2)
   { return !(i == i2); }

   BOOST_INTRUSIVE_FORCEINLINE friend typename Iterator::difference_type operator- (const transform_iterator& i, const transform_iterator& i2)
   { return i2.distance_to(i); }

   //Arithmetic
   transform_iterator& operator+=(typename Iterator::difference_type off)
   {  this->advance(off); return *this;   }

   BOOST_INTRUSIVE_FORCEINLINE transform_iterator operator+(typename Iterator::difference_type off) const
   {
      transform_iterator other(*this);
      other.advance(off);
      return other;
   }

   BOOST_INTRUSIVE_FORCEINLINE friend transform_iterator operator+(typename Iterator::difference_type off, const transform_iterator& right)
   {  return right + off; }

   BOOST_INTRUSIVE_FORCEINLINE transform_iterator& operator-=(typename Iterator::difference_type off)
   {  this->advance(-off); return *this;   }

   BOOST_INTRUSIVE_FORCEINLINE transform_iterator operator-(typename Iterator::difference_type off) const
   {  return *this + (-off);  }

   BOOST_INTRUSIVE_FORCEINLINE typename UnaryFunction::result_type operator*() const
   { return dereference(); }

   BOOST_INTRUSIVE_FORCEINLINE operator_arrow_proxy<typename UnaryFunction::result_type>
      operator->() const
   { return operator_arrow_proxy<typename UnaryFunction::result_type>(dereference());  }

   private:
   struct members
      :  UnaryFunction
   {
      BOOST_INTRUSIVE_FORCEINLINE members(const Iterator &it, const UnaryFunction &f)
         :  UnaryFunction(f), m_it(it)
      {}

      BOOST_INTRUSIVE_FORCEINLINE members()
      {}

      Iterator m_it;
   } members_;


   BOOST_INTRUSIVE_FORCEINLINE void increment()
   { ++members_.m_it; }

   BOOST_INTRUSIVE_FORCEINLINE void decrement()
   { --members_.m_it; }

   BOOST_INTRUSIVE_FORCEINLINE bool equal(const transform_iterator &other) const
   {  return members_.m_it == other.members_.m_it;   }

   BOOST_INTRUSIVE_FORCEINLINE bool less(const transform_iterator &other) const
   {  return other.members_.m_it < members_.m_it;   }

   typename UnaryFunction::result_type dereference() const
   { return members_(*members_.m_it); }

   void advance(typename Iterator::difference_type n)
   {  boost::intrusive::iterator_advance(members_.m_it, n); }

   typename Iterator::difference_type distance_to(const transform_iterator &other)const
   {  return boost::intrusive::iterator_distance(other.members_.m_it, members_.m_it); }
};

} //namespace detail
} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_DETAIL_TRANSFORM_ITERATOR_HPP

/* transform_iterator.hpp
Am8bmZkcCwZGElw6k67/nX+06R8gPatf/pQ53oXjKe4+GMk3+LANLeLQkEYu7NCh3qdfL9Lw+gveJIHqdHTMbrxPJsJefp8d+bFt8gqzYXGq5j8rkS6E7dhwZQenDRM+v8j7fSl59WsiumxCvMh+zA3lm9zrIRLX7tMz680lXX+8vhN0YrtM6wmqT9PkLf/Rsk+lOjN7KdGehCuxT3WHhrE5F65YVVYWcuEnuwyNbRfkotc4jeUftTraNhWx1oqsjrDNnozEbTNUtolch5SfkfYhf/nSlH1K1SefpYQzCTtDfXph9imjYd1SbkyUgI1q3OV299lFlPtjp1Fuu4x2Heihhjlf3097E/qG2uewMlI4dWirfGH9ji+YuD1c5VU6QTOOYwn2PEkYSs5p6W0DkeM4Gl8vNbxs9rl6ROXoYI3HuKpPSMgqh2nDzRqJ3PHqyzK3T8xzhWxy7ThpGb1s+97exl2H0iP1SvAaS++YeP1RXN/O+85g/fHa2CNto9vYqylfgat8K1a/d8W8WUWJXCcFUeXctL4sRjkVl32+TVZVbamsqIrRnhRE2CX3tO1Sr1uO3Z5YOtj2OtUu2l67sFdxLHuxwloi9iq27DXftL08ysVa8ydJexVH2Oujp2EvdGMb3Rqx1xTZa0Cau35VxrLXms3rt6xfs2pDAjarjKpjIeEYa+okabPKyDqW3XSbGfsY3WLbzG4Lj8lmXmadCNeE/KI7bbamYuumLY3aam9Eebo2oTyWjlyDJp4/x7074brQvdWpY9mI9Qmcz5ok2oywuKneuXecy+i4Go/mXqu6JsJOw5N4jovZttjPKql+XTD70v196BRxbz/SMfr95vrQ+43LxlWN27c2yfvhUMd7zcpO0TrdEHqvidKpYW2NRO6Ldaehm2evUw7dbuwTuoAidTO+8Bt/fuiUnE6kFXWd7EmP1mk38dJtnSx37qz90ait0pPUy3n9dlbbUg/i0rajV16UXtvKN4ecfwcaf95CNuzauSyJa8dlu/QMv23x18m5iXiFYTpWWc+EjdczZCPuA56su50pbKKtc+w2wMrDvpZKM+U/idAytE14f+jeGF6+pK+lSumc478HW/LWN4EtJl4udcDxTcBKp5tJx/smEJ1WLrzFxB0V9m2gQL6hhyfk0zjcflozXe/GVp4RbeT2rGgbfiDURkbYUNd8o7ZDTvcKb5ylkfNt9lojNkPeXjdENlMastXfHbZ6Sf79d3RO3la632iMpckr7Dp6IDvaRreGnlnTw2yUVBuErF/O+fZ6Klb9Kk2PbyvS8OvpSN9W4enkhvamR9trema9vb7fBHvl2M+ylt62zfblNLzvGV0It2Gzw1E2U/uYwHV52LIZ6fHLl3XZh/jh7WllEu2pVValy7aVn70exO1dosbGm7lTtenudRUjx8efym5kfLxV7mUJrOdXm9708fHoEjU+fln4en7vijHI5xwI7W/desi4e+5t/ere6T8t6d7h1j81j0F+N4xB1oXCdzrjs8b4Hzf+kb1+Fz2HnojwjzxZ/l6nwFZwKvTkaiXXxiF3geTmwNZwruU3sk5yCyRn+40cLrmRMLR/FMyEE2E2HA3z4BjYF46F4+A4eL7iEYy/yplwApwNz4cXmuPS3/s+D3Md+k+XHjNgFzjTkquWXC+HXI3kHoY94ectuRrJZdlyDr+6mfBzkiv0vrfCfMnZftxu1tjS98O28AOwK7wF9oa3+vnr2yfo4Mi/WvnvgmnwGksuvWNsve+V3Gek90FfjtAxtn0/Krl9su/HLLniOHL7JfcJyd1pyVXGkbtLcndL7lOW3F7JpTvkPii5D8FO8Hb7fEquh0PuUck9BrvDL9o=
*/