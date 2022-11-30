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

   node_to_value(const_value_traits_ptr ptr)
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
o4WDvaU+kXdG9WxStErK9P/h+i3iVbXMN86Ud8DrzGzoTBLtAdiSgNqKXRYY1d6veTmfCnT8paM+ZxJ0Fg82BAY+EyoKyoYy7tuFNflgMUuNXm5Iv3Pfr+arni60YO8WNzNT4a7Ieye8MGxQccUGtk++Ec1sCdOOna9w1q5jJpSRS6r6VERmijT+c0cVVnWV+PfkpHFropXoQL2UOz0hK7NIrp+Y2xLvJpBHd5/skPjA1uEtwJuamlIFUgF4J4pMvl8DpWKjuNT4wWC08MtX44NpI8kQnttDwbgscXSVDkIWC/UOlTqWy5/uZvYuCvyHza11Jpd3o2739cBWd7riLMvLuXaoy5bR++uUN6Vv72+T9Q3xiI/digtL60ixQG5ba1IbmiiNckTSdbBXcipJmRpE6iP/u7yOr009cmX87jW8xh4VXIgo26B9+tYuKRsAJUhs3MYwDWuvfFLPMiemwsDj1wQOL26pGd51ntddHl4CfMFfkWzqSXdQRV2IiODhBBdTczPBCqKDUv9ZXLu3bww2EQdvmFcK5wPmvRaR+zsR9wInyBKpkkohSw0fCX73kXukQ4s7jYsNHL+z5M1CNoLN6QJHVKOxp6/jtj8FvfLO1/uY3ifMNcHegFemXd6fqXMoJAx+5jvI5AVKrxPsy/h2WDmI1BNuqZ1GMOiHI+4GZRGSUHTxP8SUthGX+vKFsM1ZlQlhcUmmZjg+WiULnxXN7k473JZA45/dD+0Z20i3p4AymRLlhyHzRTCNA++MoTxv8eGuCLRihcAeFN7MufJHEcCv4ggUCmG3iSr42i8pFzblYLBHk0H9KKYgUjqD9smuj2mu+WPXFDP/rvVaRbGe10f9wMVWUfOqTr3/EWF++vzLLDp+X4aCjyBbgEnaB6RnpDWOaplv4I5MO62EMI+RLplLU55+gzXFTsd24AmEehFuPVCKvausB2tPqjjkImccMXMrdouZKsZd0DCFJsD+RBpnS4+TyN2Je1XjOnz7qgsq4dYwL0KAZvkLiE0QRvoB97QnkI2usCS1sYijcJ34koSa0gGsEgsSpapN+5c7MOVcHJRuK5qFNMHTILyFlJVk8J37ZnKCpVwWTT2rTI9nZkoWwKTs7zbWzFDCAsiq+jxHKm2f5JKyPua14ufkYyLBcWJKdK6MzytfjRSmqjeKynN1nXgvd6KLjoFMarJ5+fA/QELq7hD4T2MCthStsw4rbs4h7beQPRFYjkTKphjDk55CSZVogqCcV5aZ/QjddsxR8E2iofAbHYG53esUjqb1DguKEa9LWw8B+wVujn492OSF+/5PlkPf+34v3XRmWS/5rBetu8kganmGRadrG2MUwFMjkXCetLWbhtmcukf0L0xjXsChsEhCZ/P4MTr7P2di6F+OM/sj7rhDiOdJJL3zIs4jQzBzXebS7DQEV04jq2Ctk1sHGfCtphH/ovJFnYq10W4w8rvAQQyv5sjH42/RobsXP6roJZabUPhGBApNHUUIlHZSG7EFQpNPR0PjO09kzbOzEUpGJDKsQR1fmCuoQMV8bf1QhzW09PArPsrdpxEleicQMgb2whec7dhgcgs8PZlL6g/5Cexo8YbcOFOBFHvt/2C+8Y7naXtpQoSJaQzpnhZorwmUkWFCXdTX+ywjn+JFh95RMTvAW3U6YeshQsRMn0JtWzZZSB2Z6EgFMM2h7owxR22SR5d6Ces4KfYqo9rzjDOvUnceqmzIs/jVWDIjQXSA1N8D2PhBwk+k+kGYJzgT6T199E2GojePK4CKpA7Kde4hDg+kYdPmCQ6Rcu+QrsJJhTggHcm0mE1UtFHyJFq9zj04Ot3yqlJWMB/0WYoKQKODGgU/jLYd5GlaxrK2C4JhkIG3T1/frrmTfeSIlGRIN2y0wle/Evfc0aMmtALQe7kBRfDOFRuHaLI/Bz+I2qumcztB1gIRWFUJdkZnflk1Pw0c1wVlxbp+Cbalt/LFkEqbiegEmD4M9+iuWdaawCoDRpq2YEKmmRzU6eVjzY22IbQRcMWSqZELsjX/ECvMji28whVgb0eA2ZK1owaQT+O/2Pf/sWtDZAtGy6O7RF+C4yb0/SaMoNHmSpXsB5Nfwn1ouqAQ/RmDBVGpKqSYCBtzqla0275je4KfYDnZsjrSOrJAK1sJCl/Dlr5TfbDJKwLDV5tZKNQj5hJlRuGaMgig6BTud0Nq7Ibl33Xb8ZWQY8sVCdnrDD7/RvqTbEZ94wKYtHwMrWsmGooojpi6Z3m7pkXMhbWjJ8En5ib0OmOqZnZMQpmpAmvbDDBK3dQJ7+ZKMEFzyJLtWRgGcq6TTjSz66HCVapoZ/zNbclgdrdkft9ecysCMabTwss4g2ofo7nIKILbYqcMt6dbrLAw5o0o8uJ0dln6l8VKsF6Oyij68WvxcnmG3+rAzNMBv3OX0ps+KCaL5+c4nwhAolmIjove3pLkhqVG6s0HtjfmnKiLcMA1l4wMxZlfzjxT6LtcDNDmFAWkr640bwZMY9INvaaH96Z1EFpsUrVaOMBXLtRjLaU+HuRjjYTUjNzkRJQY7iwHc/oI17A2jpuXQqYUumChQaS2QafxbWwfhSPw3EsCsur1+j54/AEO6ka7olL3XMupN0QpAT5vilGIN1UQMfBu+H7/8QaEiSW2TY3+AEFinzc6bBzDcf6Rc7coJL6yTw86s2X46/RLBfoNGYzs7XkRlnRZskCsjA7CmqyFiKQ0deBd1t6gqyJih8JMxoU596huztkAAyz804GhpDNA9ofYfxnxifnBJa0eD4vvBMTGYd8YFq3r3zwAmQ66MboVzrckBpfyDRATFHsFdHEiXkFfl7cuWUHymYZ1JKgL8CDTlzJQOPmCoNe5giFVDRfh0t8GhQjbi67+1UwnomNASAt3mLf7ZJtmRLg6AxmKA6JOPnnMHU0bu+RVhFJBd0BSG/y1henHRXn5uQww9HNiXXzcRVZwotsq7PRQofveyOky3EtB0A/v4xkc37xtjpolRFPaW9cdhMoJsd31IHOEMdb8vPU88+6tecbR9PC4mWNMXMhn0mvLsoRekzG8SXr9PjWkSsvAfizmpcod2P2u4+22Lrd/JtOdSoZDGgf5gBNcpHgiNSp+EhxQ7MKuiAyhNybhoXxzghgZm6EdPJRzoV4N94PbuFoelJadO0TUUMGBibgIkQNOrOzPNWW5yEsqOeKo2rtPlzupQvtQyK0+dRtchGoSZsmZFfSgSxfnUaHOmX3fCySXNjei6zASMrsz+aM7tJlXvbYCSOVZOhOjP9B857oJOJWYGLuZPYz0VUosZDK5hv+oYlDVHSpd+BZFXOzGSXTZ+N5S5OxbQo8bgeff+XyhWq9KNg+W6faeOraNpMfKURvlK5kC7x43obNl14i5qTU2Ejkn9lvf2Il6SsEPLlcoHvjRg6D8/tuJnhMNbZAvLK4AmX2bUmyhwCLMokGNosbf3h6Q8Il3bnTZzSZZ8BZhe6W229yLhB6811oz4pglN+GwFTGS1eNiUaJPRhYCmIjDnVRo7RwMPb+J/DeyZdvfjZMqiYeb+oY70Q3vr8ye/U2um2bRjRTTXGw7yVgS7UdWM6FLT3qXWWRdpm6NCuLeEjO7WzuSNTcM29h0FOfI6BUUP9bT3Hslc8QEbe7ad1w3fIpWvh7y0Vee8aFN/eHIVvDZFaqWZdMPMqCmuG/RTaBGKHVg26Q6kqfdFBpTsZviHib0pyB3Tq33gS44xH5kwY0p3BuAHFf0bl9LQlSKnSqhkR9KypVMe3z97kj+zUnaYtkaZViao+Em1YmpjHNhhvbZUSLNLYZzNCHWxZr3ExQAlOl/2wT/dWAPCtEH8YPKglFHCgLyI+hdagp+RovrPVh+a2fHo+biWeVm81WbnCx7ZFD0tuKmH52hsvn1k1L+pGvPoQNOIU1llqwuq0z3tnt0rYk3KLx045GE0lDOzy/m6wctYD4PtiRzBMtwgfdwU4UFSLZXB5v31mXpV7Pj1XHN2yM3mUCwVwFK1foPcDdhKZJHzxZDZrNAXk1Mi5ez4EKqzETuGiJiX8OzjTrxrztx+qOUDHg9GVn1F1urqNuYTVreHavjAKG3YFQHbG3tYFvDnIqVTAi6TDIUW7ZTxj3S9uY+eg5E8qdkNhsJRQbNygOBG6AsLgh1d6UT33/yrAJSAzVm+fdxUIreREPXobdy2MLuALBHcwVfNPGotXtZmu36KA2iMn0WkqH+fYmsvHpxWft4RtbzAb9U4dQtT/Z/+/+mVHCSEmGtp9y1hIXhb2tfj6dw6BihNIwi3zgFMomxdDy87y8xUjNGEMxANwu0BeNIj7fPrRHgqdpIWtAtnA+ybM07AuLacMLDqVt8T6cVWhGyRVB6/rlKwCBsILXo7u1dPhMAcFYGSxDwZ5RdIMamxlGXMHqBu2XoQlRNGEop8EDdEML5u07RPLOv5SwsXXW/C89YhHU2BeBWIbVi7yy9uebV8fymlsA7HVDbkfNN5aZdkKxyNfFskVJtXbmm2tX1dnCrdNxbtddwxK/LaqIHpBtJJgq7uFqSzv1U0VAV2I75g1udTobgE3aJdgPDe7E4dNVEzbmbxCMTe3bbQXUbRtQ71vd2u+qr9c8PesnRwa0QiTyXWkstr/Kqfdizp06/wcd7f/7+09RD8f++02QkwhoSoBOTGD6ma1xVSJsnUwtDS0JQZWT1gh/HcWlRtPZeDK8t4gJNRF+0btU2rLRHvpdZiWkW0v9UUHn+U7HJIAj2bLc2QlbCopH1s6BR3Vy3Y2VsfipWoGrJezMRW0ErGQ3mZf9R8TDyJyQ3j2sxkWhagU8i3S20s5zUDIIvrUREsJ2CMmocIgJ/rZsiD5OHZN42lPFgQzVmnmBEGhKn4P8nBFPa5U5kUzG6cFEoXa8xoyWnsITmRZXiH3leXoQCTkiVL7pK0IHsNkjBDC0CC9oD2OknJQmcDvhC3nWnR89LACMtXBN4Ij3BkPA9xw1Kn2yfYBWIlWHsex2cxtR72HBq2EroDDKcTwUfoi+o3iJh4DwHcArcyUfWVNYstd0kNLYzZUqK5FvWYWtM+c+CNCJiWpKQtO1kYoPojTNiAlxK+1XkDiFcTI4qJ0vninsSgyza4oAunx60z+kIhNDnN9FfNQlThGFLlVTjE2UEmkYiSfoA653sq5iBNE7X8c8YQKu+mwhPiQVJHERHLDt5pmXrRzv5l6LpzEz2TmP6dVX/nLIzO3Cc0C91iq0phn18DqKpQR5ZicdbjULLQR8//7L4WBTwQX2ess7owdY0zpVp3WYFQ7Jif1LR6f4habRLyHOo9HuRkkV/X6cwzijMkLxtLj37O4bJVOeXMaRpVkdVTh/mBYeTskdTyec47Z6NsUHr281eJxlMgGR75XmkUQJgdY2UdgqRDrF80wbDvvIMiyR6W7/Ini4+CcDaJht4snTdFjsd1vgnLbFyRgdfyi9vmZSQWRICgD1kOF6WAcC9WZAtqpAUgi75sKa1FWhIIYwY+gLP9N9tbj8iSSWeq8Gu513dhyWa570CJhPnn8n2SjWidRGmzmavbPjOEKvCYubs4cqBcTs/ANXQ33yD/uab4jffV6oDTtO7W/c3DK8aMtaYxo36VZFl8Vt+eV5gDcITy68egtvAaoZKci7KVEx2Iw9UpBRKELUMZv5qj0toqwI3jHtYXWY1a0UaHEPgNu/DmFShSj1w3xL/wqiPFO6lkkG8SViY9pxCgMdf3UJbvQC4xFVHSvgwYuw6aA4UmeGnA2kJraKdvHdY1bHcdRveFvGXanKr/NpQlNj5D95uzNW/Jd97l4hQkapXTu/FQzWApAPsVLzRB+GrR8v5xB2m6pTucjdNqpJi2o6nmx+q1bnKwIXd9xampM59yTW0V1nwyN8RvrS6aHhQdsXea70tmgJvV0eeTACV81MevGfnVtn/+wyYkQ5hCCkA82QeUPzgpobiAoZZL6saVv4nEO8M/VX3rOb+5fyt9bG5g7HB6N5nI3zXzMQ5j8AZDYKdbTInUyHujclg5VOeRU3WIP5wG6gU0K7sTLPjBUg44d8W0r5guFFFuxwQ2mZmbd4uY5y3J2iKwEpK2NAB2NbTSxpOlEMR5GO8OZCKEgLAbs90nmBIZqK6lObRIp9Oj9F+QBLREbyAKogwiwoPsWVqfKa6HxAM9My0P/nXx0Qk0dnWzdyhURZFh1VaubRP2DmFeUW8cv5ivFUiDhATlXciPilLdNSeYFnfAD6jUARoAJqcDUDqhNXb6bIIDaHmHxcmXoD5fsdQliPzRgCxKzOFYFvGpW1fO7rw2tauP2Vf/JhYLz0UXQWXFo8508J2UdDac1pkaPpIzcpjFlrO6F49/9WuJBLUKB9UwAQNXFG5Uj0GYNZULmGUdMbhH0+R44nBERZlX8VJ2ICY19mqG90QcOPiuA/6udg7pH9C+z/QWkcRhkQj6Im49FtLlyFFzuAOJtsUuH9AjQfeESyXNQi1EPP9PeKhcqR96G8WUv7ASJKcK4LtQOceXH8L7GA8e/Y82BPJlfJtzy/Si6hWb40mnOhsdjSlQI5cWiq+kNxMi9GyqsCs3XYoGDgakFSnRgD2LUJvaEkyKz34UYoRnfGpKIF2/d2OAICV4sQUT2h0W1zRh4vYYm+CR0Z0l3Keo9E6P1BeVbbmVnsDQNmPlrqD77AvrtVbCFS6h21Ji10YYsyjIxQoAdDyiZ/6Jo079VQT6nOtg3Agjc/Qj5UBUgZAjEj8mlApj/lr4AAAAD5/80bzm7frnqD1IRlRQgDS3dminK8HT2jToiHWYA6x3Yq8oh3vg0zf9uJ3gbf7XkfbB+6qeqyvTixbU3z9wFMCDdvt3oTbi6H9T0UBq7KnLJ83iSLzNjqdiscUgfVru3AV3dqgJScXD4gZZcwgI8vIiL/OyFBGW/oJ3ITuvIoaiNEPbOYx5mmMaYbDSXlti/0F5RFTTsfde8LQKxs72sTw2njEdX5lOgiJH1MNkBEnUMOpK3+WDARJSSh8H0MDhZvz5klP5QXWSbyVh+OUoJTXJpnr0RL49jLUsMft+tnfQ/EVZ/GhhG14fZ7h9eoAUz3frGwd+eOF8cxO+H9bpboiHFoQ0o8aw4NYnRaKhpqsQRDvphVHGKdSvXSm1Svx7wUZS6Ie0+IrPmd7BLbiiYOBablkGrZ70nHnGpWL9hgsJkMsUPEfmCtQ6KUwG3N+D4qlWaS0v+XSEbfuCwiCybJo4xEVge1YNNfpm6bV0Ol7zMTsNHFFu1rJEic+PVpP/WwMmGdaxMv3iQS2hQarYezPi/1rJ0sB7OddEdLLGZLb47LBRmYU3NHSVgRnqYw2lHkENu4Wrw/10wOOu1RcKIp2gMzBBPxBQhLa4n5/jIjtIJuyjpDBpOw6TeC/KvaTfdzmwvx6E9ZrXxQ99k3KEfWU0pmgqpuhb2aDVG80lYVkQDyun0tZqE6Vj9H/NVFO1nuKiGcAUKLf0PaaGUZIshNxIAQRUwqGaZqkVimvgl8YxeWk/pZtqiQa1Cgv2mrMIVIYAqi/4J/ftHhas+39NTc8DwRLjJ31YznemDw5G40ofSjoPxDPM2AR5aWuzDyFnO2szgcvyToat+sFRtABGg/lgD2ZDINV9SOvJFQLJN01Kene
*/