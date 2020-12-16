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

#ifndef BOOST_INTRUSIVE_DETAIL_SIMPLE_DISPOSERS_HPP
#define BOOST_INTRUSIVE_DETAIL_SIMPLE_DISPOSERS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {
namespace detail {

class null_disposer
{
   public:
   template <class Pointer>
   void operator()(Pointer)
   {}
};

template<class NodeAlgorithms>
class init_disposer
{
   typedef typename NodeAlgorithms::node_ptr node_ptr;

   public:
   BOOST_INTRUSIVE_FORCEINLINE void operator()(const node_ptr & p)
   {  NodeAlgorithms::init(p);   }
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_SIMPLE_DISPOSERS_HPP

/* simple_disposers.hpp
SmvRQb7kqFutkL09vT5cyPEFhBEE7125r7sPcmpnMyd3vOlLzCYns7Z6XsN7c47qVugcZ9vnOGyuHkXz2zXtM+dH36wc3x549zb2w7bst21rZIyNMo2Mbzt0G9d5oNGN5/4++iarunzSmtsf1Pev3+VzVnqbuszLfePv5V3gVhM/21VfSSva9+MWd30lbuL3Fy9uqG1ZxjW5k7LMNm1LRvtWtG6pLTJatUnLzXT0jcZ85rvZpFlo9Y81eu9v9B7m+ZXcEuMeZp+PrHytJa7zMYNwkn11/vloeN9P9D2szmlTt/0V13purs/O7nd+y8SZFMix3lv1rRfbJmav0PXSKT+xb7yRthohW43UxXm/1kG8l/Ab5IvzfVvFfi5SWa7Pj1lvSSdxu9lxM1K9NtlRbx1x1SZHt6dW3HYNbaKJ9xbXeahty6VMY/tw/WaRdrt2aS3S1Lbp2N4+3jUxpcnXxB1Gh0Lr+3L4eW7TxOvCPq9+G5ga3i6me/tko47se6uhjTNt2yXoZ66VXvIZoPoxtr8/R8TMOekEzw89D/Yx9aO8qmrF1GkLmOVdFOpv4qVmPen533LMdyH/vjfbyASDzzifoZWm7nvy3VtVtbV8MymXl5WXOesMMv61lprDDpPnCgYtDTfxT+p+pznzq2y/AvOM7F8DX+YNgTicayO/vsy6TleZOL9iHc508w47lutlQz++D2SE7oPVn458h53Cdid9gypBn5uww+cJkwmlbH8DuSc4VgR3sO/jhJf4vYyw0Lpn5iZxz+zZN7IN0Hcr2b+b/f4UYVPud8ZGqTmKL9vZ896Pat77QxpH/iBhcujbT1+/DpTMmjFv1rwZpi74FYFoEd/1jD7Oc09a7v4d1Z1XzfEZzjqArO3zmb/1/nX3c3OsqH6bX4P6mb49jfsy1+ka+1vj/Sb+3YH3UVJXnegMn5UunQLnEId9frqtVPe9etjwHP+2kWlj6tAErqmas2kzzLNUQfR3EMV5njiLzXeQzKjvIN0UJ5Vz8/t04qROSmvbKi04Iq1Nite+1KUTItIcMMDLd13MfOcQ5w+hNFsv8OO84eXLdku2l5DGUoXuVr0NNDLeDDtZz3dWXfXrR+y+s6GqjxvO8X2u+xzdBx1M2tVrN9a7D6kfl8L+YGBFKXtc9U4ywYT9JpAeOpn0TLuJfNgz4UTp+PI50b4isrpyL+nn+YqYXDJveMjJ7LSp9VfMpq0bNgSs89y4Lwe7nd49MDq/h7kADrjz27pR9nmoS1yfFMiH+5ioS0Avz1akLR8T4bapHhSt6xeIW+PU1XeiYfTtkBNfX9Lw7weTOjfuQ6OmX9N9aKBLlA8N8rR8aISfow2Do8vdnTpx2F3urVXrEisz8mo7fX9PvMu4y6u4Ddd+EufTLm+G7adJ+dllXTIkuqyPco6PO8u6bdWGreUJ1Ufk7e+S8gHrLqviNrRhSZTVr7uR4ySUn31/POYo61mhcQ/hZV1YOn1sSekCbpOncb1719ChodF59iDPulh5WvVpQX4jfmgsG49ppD7VnUZ9Qo8oG4+x6pNd3sHDostbRHkD/b3yMhTcexQ9Dft69Te3IDq/qeSX7srPsu3s+LaVfFDPFnFtS9ym23a2w7bkJ9uGvy8fdpS1dR9SbCjrouIVc4tsX0avNVLOvAjdTyWh+2uW7vY5GTw8Ws8gehaE62md/uTPv2eT5x15zSKvwqi8uJXKJjP6xLUJsk2/l5K2bBKu56ERtp4icYsj9DRVNMFzh6zV5xy/jhafRh21zrPV/+yuo/ecG13OCyjnyshymltJYudjZf/E7yUr+zf9XjKjT+P3Eq+O7x0ZXc7LeUao9Ms5Y9q8aQsmz1k=
*/