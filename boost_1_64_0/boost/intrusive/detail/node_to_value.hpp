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

#ifndef BOOST_INTRUSIVE_DETAIL_NODE_TO_VALUE_HPP
#define BOOST_INTRUSIVE_DETAIL_NODE_TO_VALUE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/is_stateful_value_traits.hpp>

namespace boost {
namespace intrusive {
namespace detail {

template<class VoidPointer>
struct dummy_constptr
{
   typedef typename boost::intrusive::pointer_traits<VoidPointer>::
      template rebind_pointer<const void>::type ConstVoidPtr;

   explicit dummy_constptr(ConstVoidPtr)
   {}

   dummy_constptr()
   {}

   ConstVoidPtr get_ptr() const
   {  return ConstVoidPtr();  }
};

template<class VoidPointer>
struct constptr
{
   typedef typename boost::intrusive::pointer_traits<VoidPointer>::
      template rebind_pointer<const void>::type ConstVoidPtr;

   constptr()
   {}

   explicit constptr(const ConstVoidPtr &ptr)
      :  const_void_ptr_(ptr)
   {}

   const void *get_ptr() const
   {  return boost::movelib::to_raw_pointer(const_void_ptr_);  }

   ConstVoidPtr const_void_ptr_;
};

template <class VoidPointer, bool store_ptr>
struct select_constptr
{
   typedef typename if_c
      < store_ptr
      , constptr<VoidPointer>
      , dummy_constptr<VoidPointer>
      >::type type;
};


template<class ValueTraits, bool IsConst>
struct node_to_value
   :  public select_constptr
      < typename pointer_traits
            <typename ValueTraits::pointer>::template rebind_pointer<void>::type
      , is_stateful_value_traits<ValueTraits>::value
      >::type
{
   static const bool stateful_value_traits = is_stateful_value_traits<ValueTraits>::value;
   typedef typename select_constptr
      < typename pointer_traits
            <typename ValueTraits::pointer>::
               template rebind_pointer<void>::type
      , stateful_value_traits >::type                 Base;

   typedef ValueTraits                                 value_traits;
   typedef typename value_traits::value_type           value_type;
   typedef typename value_traits::node_traits::node    node;
   typedef typename add_const_if_c
         <value_type, IsConst>::type                   vtype;
   typedef typename add_const_if_c
         <node, IsConst>::type                         ntype;
   typedef typename pointer_traits
      <typename ValueTraits::pointer>::
         template rebind_pointer<ntype>::type          npointer;
   typedef typename pointer_traits<npointer>::
      template rebind_pointer<const ValueTraits>::type const_value_traits_ptr;

   node_to_value(const const_value_traits_ptr &ptr)
      :  Base(ptr)
   {}

   typedef vtype &                                 result_type;
   typedef ntype &                                 first_argument_type;

   const_value_traits_ptr get_value_traits() const
   {  return pointer_traits<const_value_traits_ptr>::static_cast_from(Base::get_ptr());  }

   result_type to_value(first_argument_type arg, false_) const
   {  return *(value_traits::to_value_ptr(pointer_traits<npointer>::pointer_to(arg)));  }

   result_type to_value(first_argument_type arg, true_) const
   {  return *(this->get_value_traits()->to_value_ptr(pointer_traits<npointer>::pointer_to(arg))); }

   result_type operator()(first_argument_type arg) const
   {  return this->to_value(arg, bool_<stateful_value_traits>()); }
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_NODE_TO_VALUE_HPP

/* node_to_value.hpp
wEvh2eqfrH59vuA7pVPekOeLbV69bmESfAEmq78r/C3sA3fCLPg7bR+/h+NV7mz1T1T/TPgyXAxfgdfCP8C18E2tpz/C++Br8FG4Bz4D/wSfh6/DX8E/w1fhXvi6xnsP1kn9oU853/42BRdrOeNwc7Scyfoc2AFmwI5Q3ic0351hEewK58FOcIH6F8I0eLHl1/R2ePRbCXxJ00vFbTWeA8S2M4zXvS2TdI9JS+4RtaFHGaW/3wZHwO1qU28TPBf+VPvFJ+A8SN8h+XgSroI/h3eqngdVz6Oq5zHdE/MpyRftUOVeVLmdKjeiRb3NtsqlPs9NS32N2m5rttv2n7Pbtnmp7z9iu23XUt+/zX7b/qW+I7Lh9v9ivy0R+XA23A4v9R1zO24J3/P9T9hySyef43HluJtwW3B1uJgqnycTl4Orwq3H1eLexyUv4xhuEq4Utwq3AbcD9z4u4RL2tsPl4pbj1uE24/bgDl/SbA+u+a/5r/mv+a/5r/mv+e/f8/dvs/+3pLKktELM/x2V/T/Lfl9vw35ftte0JYRO3EPWHM4BbT1+e0ojR406Z/rIUbNkwtZCScDjX4OxISPsWkDiR7Z3ib1OD12yTs+0bXcgTN42hctbaWlJJHnbdAzytipK86QRWmreat3zVlFcWLaoqKLxvNUeg7xtjdb1nJqvc3EbkdsVmreK4HM6JXzeNL6XMHsdqEY15iruFpkO7mukNH6qM3+NDbA0eXN++F6Rm8D8Sa+z9vPPuo7h0naN28Gy64ayGGs/dS2okWezzg763Ossa6BLnWlbi6TOiB9SZ0QNqLPRyLjWmcR3rzN0BNTZpIHfbZ2RXkidZenee+fomFSO1tkm9zrTayCgzpw5c09JnIkc88q8KNfrNqQuVaWxX+dmrcs2rvPm0OFan4F60uBLIncK83OjvoP61PSC6nNvy9A+5RHipw8iL45tO+lPzKVcUp+54dsg8ZvWp+Rqnk27e5WtQvviR5HLDMmbGkrzNJ6vzGOQr4SY0Hw9hlyWS750oUSj+co6inzZ53J+bOi18Thy2YH5qnA9l0HXxqxBjV8b6HXa9WiJb6g1ro8c5MJeH4aejqpHr48QXWlw4aDQa+TkVF0jE4G9wuD666jXyGjxB6ZpnvMNcbrPDs6LOwn3JHFqg+vW/Zw78xm3i3yGW32iK9hmX/lQgt3qDNlwa8/c54eqvDM3uq/Yd2x838+g+gqy+Sb5C2fzTepvrNbfpPjQa+Zp5D2D7fqbkTMy55wZfitAXDqZhhVorcst4a8f9DTt+tmi5TH3NzwQH9QXah4Tw+fRXsTZaP4SjyJ/zvNfQmgdPoNcetj8ySqHRvOWfhR5s+uutHXo3pDPIpfpljejC7L77NHh84eO4H0wS1yvCZVz5o6Xt4vcZsdoLRN+035NQB+wto2zVxV/6MY9T7xsp4w5M3KkgLLDMVXvL9vYsGXTuHrNfyLXfHGV6zVvyjr1UFpWGG4/y6C6WJ0UeV2MDbrWyRd+8uXsaan1o+mbbbSqrY654uz28Av0VYfWURFvn5XFUk2N11O1e9ndbX0Flf3Woyi7WU6zLYxWbYg7e5otw1MTWk4KKDaqzDLW7xUs8ie4v89qOWQNtjUfmzT7kXpCYmzIHs+R9uNjXfqVusTQfuWXyO0KKYs80xQUsgSooHBZo+dsVxP7lbEuz1rb2rm3pzrXvEV2zdU1oS3VBbWldcewLdl951dq1y9NlcjcKuJ6hoQrY97cZXlTzh4dwXWDjqCyLiopciurIZtUXy8FFZXlZRXufQzygXWTdtR1489bqtnHGHkw66xPcmidvYDO9AbrbOpZEyKos/T6OlNbS/IJzH2dThM=
*/