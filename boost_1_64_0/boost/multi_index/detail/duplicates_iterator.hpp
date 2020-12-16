/* Copyright 2003-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_DUPLICATES_ITERATOR_HPP
#define BOOST_MULTI_INDEX_DETAIL_DUPLICATES_ITERATOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <iterator>

namespace boost{

namespace multi_index{

namespace detail{

/* duplicates_operator is given a range of ordered elements and
 * passes only over those which are duplicated.
 */

template<typename Node,typename Predicate>
class duplicates_iterator
{
public:
  typedef typename Node::value_type        value_type;
  typedef typename Node::difference_type   difference_type;
  typedef const typename Node::value_type* pointer;
  typedef const typename Node::value_type& reference;
  typedef std::forward_iterator_tag        iterator_category;

  duplicates_iterator(Node* node_,Node* end_,Predicate pred_):
    node(node_),begin_chunk(0),end(end_),pred(pred_)
  {
    advance();
  }

  duplicates_iterator(Node* end_,Predicate pred_):
    node(end_),begin_chunk(end_),end(end_),pred(pred_)
  {
  }

  reference operator*()const
  {
    return node->value();
  }

  pointer operator->()const
  {
    return &node->value();
  }

  duplicates_iterator& operator++()
  {
    Node::increment(node);
    sync();
    return *this;
  }

  duplicates_iterator operator++(int)
  {
    duplicates_iterator tmp(*this);
    ++(*this);
    return tmp;
  }

  Node* get_node()const{return node;}

private:
  void sync()
  {
    if(node!=end&&pred(begin_chunk->value(),node->value()))advance();
  }

  void advance()
  {
    for(Node* node2=node;node!=end;node=node2){
      Node::increment(node2);
      if(node2!=end&&!pred(node->value(),node2->value()))break;
    }
    begin_chunk=node;
  }

  Node*     node;
  Node*     begin_chunk;
  Node*     end;
  Predicate pred;
};

template<typename Node,typename Predicate>
bool operator==(
  const duplicates_iterator<Node,Predicate>& x,
  const duplicates_iterator<Node,Predicate>& y)
{
  return x.get_node()==y.get_node();
}

template<typename Node,typename Predicate>
bool operator!=(
  const duplicates_iterator<Node,Predicate>& x,
  const duplicates_iterator<Node,Predicate>& y)
{
  return !(x==y);
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* duplicates_iterator.hpp
UEwbjEXHN2iBDucQ2JRwjIHnFPGMTYdjjPqzg/GfnmP5cvoyyqPg0H4X8A1+jfoG1yfjgzrqaZP+WpWu70OtnK2qcnnVjinwRHirQHskAErR8FsMNH3Cu7vX3exRn5M3tixaXS3kzWaQPtjf5LzPn6U05MU5PaZtshA5rpvJKtTjeGz8Vlb7RakbS08euv2WzX40k1eKrFBKFscHvCOn/HDOnAbvTbUHz95902un+6o3WK49GaQ287+aH+En9MADG9o0pVXLQdsrK/i2G94WoTfBpqYe2tBmxmmGHeXPUgy8yVgjkH6E5V+urNZ0zP82jL8sAvLG972fQ9+lhZas4++9VfGBRgEnPEtr3qQF2tspLTiHgfseSnz5ngT6iCFBUPfY/VyOQR1DzPEWwwwmyfmwhUE5ZHzEMwazqVHUP+u6pkEqvLRhv6BL3vOYZTgg41j4zhFG29xW55jq0BV533YbRoeBgrzHb0tp0A7ASd4gH6MPkPbqo4wGcT+QNns7SuOxCK9y2u4+kfl3TtMxtdGn7vaMNmjKivRzd7Dp+7uAwPedj1E6PsON88Bvn235yCRhVcaHdnVgtt2TqT8ivInP7CNO39/RCCzPOVaeQuRB5MdeEBy2QMa2uUblFcJP8qRMo0wMhmvbEEtqtHs8tW3spg9RnoUshPc1C3GxM7jAz+BuUNxiFHhBlbpCe92Y+XbHYD9Dsadizy/LIkjETn8kdsfs7/2IYVPHTZPckWLT8v1wHkHa/Cm6TeFES7nAwel4+2J/Y3+bxQe/9zTgVJib4bp+DID5X7QUDb65XlmExLfAjNm/jdHxo8z8w14xw3DctwvfcwQM9EBTSHC7UA/O0PLsjmEUhMR7u7ult14ShFFaHXpTE88MqLxcxF5aBbIU4JpLtYTZQU8dtTngsMHxDclphYH2bppb102PD0gHFlZ9pH8Y6azqSL88A/TxvkJ/FE7nflTmDGOGvgc42N/d7e7ReeF9T7f9Wj0nkMEh3tap2zcxMX2ezs+gk9Kp8iJWa+nT5n83iGRhvA4wdbQePREam5bJ8oQbJKmfuhmRFRT+gZKEGZN3fwY9g8r83AmdRAy2OmdOzy82YIzxzbAyicrEz4oafHIJw7EuGvxjGR7Wp6ETyRq/eGIe8RgTnOILESrpaZRm4nxfLS5OLpw4ceb06SaXEM+tnsHPTCPPdbJMDC72LnbPLOw+4aLGkzNaindDocZLJiMvFJ3dXbVs6GgtP6EsMzi2e4JqMCvm0VXG78Ohq+9Ii53zOriPzngDkbulX6nWziE80umnd/cGihtMQ9Aj4jODezGU33NEmUmvdNNSePDSy87wzGlwdQMBF9UFiJ46dR6eOTFQPjldmDKzMfv3J6w8icjyMkgL7RVk3sCrp1rP06UZoHuPTkGJp8xeMO+LJApU90mhiqNaZvu8kWXKMXiWiT11zn6L3I+rIokE5rO4Bo/KdvauGBmoz1AuLCBps8SsM6ls1c2VUsEwCgOxutVT7j3wp6Nsb/Vsq+6Fxbq5VJHrB0ahnJ7p+4rKyoRXxEmYhDkOOSwQKYdr9I7yFiILnMoJC0do6GQB2E7oD8baKRPS9fMszPzx/ufdRbrKC41NwGQFws2LKoxh92sRHH1MO+M4oo2sB6CxE1j7BiLL3TTzCknKtNfZGcAj1KeDnfX+RuNfttYZdE+RNzp/xOS4At5hS8KMyPF7g93+oDdsxohyM+msb11UJKie7iezDvsnq1sqyjAJKj+CG1KbavX1H+tH2t4z5bv/M/kbUV4QKpHVQR04qSfP4FvVVFYlUi8IKohZ1VUvcGz3d5X6nQanR1MG5PM5XxIkbibjQkBHA9Ned70=
*/