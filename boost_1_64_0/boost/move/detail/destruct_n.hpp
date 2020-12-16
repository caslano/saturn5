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

//! \file

#ifndef BOOST_MOVE_DETAIL_DESTRUCT_N_HPP
#define BOOST_MOVE_DETAIL_DESTRUCT_N_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <cstddef>

namespace boost {
namespace movelib{

template<class T, class RandItUninit>
class destruct_n
{
   public:
   explicit destruct_n(RandItUninit raw)
      : m_ptr(raw), m_size()
   {}

   void incr()
   {
      ++m_size;
   }

   void incr(std::size_t n)
   {
      m_size += n;
   }

   void release()
   {
      m_size = 0u;
   }

   ~destruct_n()
   {
      while(m_size--){
         m_ptr[m_size].~T();
      }
   }
   private:
   RandItUninit m_ptr;
   std::size_t m_size;
};

}} //namespace boost {  namespace movelib{

#endif //#ifndef BOOST_MOVE_DETAIL_DESTRUCT_N_HPP

/* destruct_n.hpp
/lb+mPm+816hB0aEaF9nODdDpUeYSQ7pbps9at1IZflWxdKGq67VIZ4w9y3MN5kbpxYPkFDHFAB9irVK8wAf3etGXEFU7Wu2/5jhxtxRcltYNNgwLziv3DL+8st19Ot/AJucr5fv//e44w0zIzVmvkoC7Y0oQvJgacmDfCN7EGxS2IOlGS6ooJQ59vvzuDcVeQ9TVx8stK7VJOYv9yR3UwIRj7n/IAIRJ8aHe+puvp8xseTFLsHbg9rZrnwsoiKwe6eIlbIgcxjL9l94oAJQiqlIzDFPg1dJBYy2AvSYDcMWaBF4CW80mH5N5HdepsVbN8qhUbOBPkidbB2kEj0EC6yhegN8fDdQkaXI5Cngrg8Fm++AnqBB/8SgIVeIfcUvVDcWNLua4kN5jBrvEvbUcd2Cjp7uJs87NRVFsYUoxiYNbJbE0RSNv6JaehU6NMZ7xmUT9VyHQ2SuigxVPEAPAiWsAj2Or+9yz/40dSxpRhsHjxXQK+XlONhhIi3K5X6lGJsw47bpdu06kTrWuvv9v/rH2P880LJ+svj+xvWTg6y1+vioW9GEvGnw2c9+U/mTyFtmk4w33JNbCg+xs+5LkC/1kTfjrHdEvvTBT5V8SdlG+csm5LRG5uaS/6DLje/vt0yob4O//EuaxN/arW/HwYdTKexJ49BOffUXN13fljfj6+tj/7a5+tY+3Eh/72ym/scS+tvWntxs/fsaqX9MM/XPS+h/lv1ZpAV8gK1osr6xCfX1tH/ZYn13NlNfTkJ9Xe3JLdaX30x9qxLw6bUbLm+mPvusJTo/U1dYySblZ7Lj+2cPAbz9ZwgkG88HHz8/a1PeTp6villN939hQv999nFN9t/MfzP1Ve+Kr6+z/dllzeHjV/M1PtJXNYaPqfHjs+cC3n720abwMVSNx9iDJ+Dn3EbwM3tm0+PxJ6yXkN23ufGs3ZzQ39cvMPn/b21kfPbjeG9/+UgT4+GSr4Sb7t/qhP71shdf2tL8lTRT31kJ9XWzj2yxvsObqa86YX0F7PfmtFTfOxc1Xd9NCf3rYV/fXH32O9NM/vebG1tfNyTM1yOAt89/uIn5sL9/h67vtEbriyTUlw54u3OT9d18SVL+L5wLTeb/uvC2pPy/zcL/9N5EeH+z8G+WJ8LvWtUc/EsPJMI/2Cz8ytmJ8POahZ/7YCL8hGbh665MhM9qFn5PaSK8fWtz8F9HEuHXNgt/6LRE+JXNwg/8ZSL81Gbhp01PhB/cLPwTsxLha29pDr7LeYnwm5uFPyxpva1qFv6i4qT13yz86B8nrf9m4c++Pmn9Nwv/SFL9u25udr5WJa3/ZuHvnwl4Y4HzoIulbnz93+KGv65F+Ht+6Yaf1iJ81Qo3/BEtwr91jxv+wK9agl91kRv+1RbhV9znhv9Fi/CBuW74i1uE/3yxG/4HLcJnXOqG79Ai/Kgfu+HffaAl+O/f7oZ/tEX4i891wy9qEf4Fyw1/SovwA852w/dpEf6YuPX26f0twc+Pw+fTLcJPOi1u/bcIP7s8bv23CP9UXP1HtAj//Zvi1v99LcCLfUvF9cZeGlYpxTBjqeqr5CowlC/ja2w5/IxTC9g/KD8GR5fubImbBXvEV0TPQKKlqg8cIxeWu3aGLz1k/TN0IjTkxo2xaXmRfsS2936yXEMQUUkuC7MuH4cNQuBwa8O7FGgK4QXCF9Mle0mpvmTPZ30CpNda+9PJZClkb1ekVqEa6eHoCcGSEHs0jc5DaiXO3xsdGX2NWw/BM8PPtYWi/Vm029P6NLnpNGn6Ww/+ZObnE7Kl1uo0ygYisYBKa9NZyv1ZihPlplYk9zQujpTrKQbAq8oezUvGQaxVr3G+iRQjgJQ=
*/