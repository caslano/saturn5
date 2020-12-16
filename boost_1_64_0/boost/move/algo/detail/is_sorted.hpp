#ifndef BOOST_MOVE_DETAIL_IS_SORTED_HPP
#define BOOST_MOVE_DETAIL_IS_SORTED_HPP
///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2018. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace movelib {

template<class ForwardIt, class Pred>
bool is_sorted(ForwardIt const first, ForwardIt last, Pred pred)
{
   if (first != last) {
      ForwardIt next = first, cur(first);
      while (++next != last) {
         if (pred(*next, *cur))
            return false;
         cur = next;
      }
   }
   return true;
}

template<class ForwardIt, class Pred>
bool is_sorted_and_unique(ForwardIt first, ForwardIt last, Pred pred)
{
   if (first != last) {
      ForwardIt next = first;
      while (++next != last) {
         if (!pred(*first, *next))
            return false;
         first = next;
      }
   }
   return true;
}

}  //namespace movelib {
}  //namespace boost {

#endif   //BOOST_MOVE_DETAIL_IS_SORTED_HPP

/* is_sorted.hpp
9KvG6eKvo6CLR76fSBe/ykqmi/DVk5GO0yO9IIVHypl9npUiHNz8xR3cHA/+rs/j6OKrHf6D6WKz9gF8/2sbv58fk627Wv6sNYzoRamMLMJ4f6tK49UqxScUCafbbRuY66n6vUd0+/Yqto6ZLCu5jBK4lqxNKc62vjCzcpku+toBKTpXB1tI/1Qts8eQ+HUeWcVMocSv5YWwz1xSYF+2X63lSM/y/MeGb6ccspSCvTxvyei8lXArXjY6/9pIttVgWlqgW7pAtdSeW1orVrKrCu1sU+NP+LGfHt9FElXzeBI/DtDjBwvtL2r14xHm7Cp6eArywEoe+bvo8x2cudmcXd3fMmeX1cajEfgbFwJfrOe+RSNoysseyTfIR/p0U3nRYzT49SonyMOFkl/8PmrkLvp8B31eRZ9vos83ODvuvjd1o95ob+zLcIqpAwdVgLUHlAh/dWnJY/DMVo3YV+/mERLSKcWVYlHzVsuGeKrdd39DxMvvZqQ1dt8L/Lkx+V3/Xk3Jb8D8MWOtOcqBLxsJCcJtqlRiYBQDgFWkVYsW9lbqMwtqYEUY+2CaGIB5vxGfOLxfGsGoHJ1GoFKRecDUAWmRopKGqZtt3kuAD0NN2fKU8hy43l+jGNsrhtnzXgExqysbL17HQQ7wQczq8O1TCrkoaaJSXFeRKfYfXtScM2DHW6+kEj4W1ihaAKceKJZ9IrC6/gAQu+AdN6sH9u3HfzMS7qOsna7D2lbx/5l1FPe8IxQsJCO9XvuXs3qO/DON5Z/e4iFa/qnCHtBRxKEVkHueP3D4kx+8Wd8qnzusvw7vaHnHGm9j63Xsjvj1+u5ukMLLuzexXnFDT7CpL32G1kAnMEUsPmwyur6JPx5pz7lefFByeNQtZjDRdR5b+z7cskqVl8UL8BChnez5AdYHEapCUkdZ21b6Ljn2v+VjAwB3/KkW9pCjDVi2T32Jcav8A/LUeLUshq9In28GSFCB9COxQEqkm8OfyBzNZNofOIjeCf6nvZ0k/0prjj8/AvCO/CurBX5bxf8gurspr8Fjpd8HmWiowHpsh1L3/TmVWxNbSZUAJiA+1jDLjExgf24hBH/cqSnWUARPI91eRyui859P3sQvVXpCfnSsPKKWU6IPIFO6NDlgU+uWc9P7Z4yX7S+dKOwBvYWox0ejbR05qGqVCgwU6WYe+0i4oh8XZ2CfkSFG9ImW1UWO/aNH2T8CKyuxO+Pjew/iZY8LueNR/vl7+uQCRFprRs/xW9n+k9oz1yMjj9AyBeUhmuUVubn9bEfFZSH4eTVMiNg5A3OPCPL5MaSwVlQB+a8MGwy18HaqizN1HPmqvn4chs1gbdihJvpuj85jDfh7TMTUVbrk8V9yydINGT8v3ZuRuvGZ2lRyZ1n8E5Z07JLYWOuAx5nbUsp9QTaj4Hfrm3iH5jfr5vtx871U8/1N89118899kdw8zJz2kVy8ErVAnHV8qhOYptaQXw4LsM6jmidbT1/Q9ZUi6QWCpfsPh/GMHXpd0GozWotsPh2tnNfVGl+IK4LyH7QkQ4GkcAkeUKulxjGxrIOJpeQsb0fCH7bmqInTsWcJGaxh9QOj4bZKdSghO4cyOwqfyQPE/YNJ4y02w9Dd5KC22b/tx5xXZxOSkgMvcazAYGYpLD/o4fDt6zJhY/A5nUPHYf6u6MVnDB+izzzDaFarZJmTaD4ku3F3pXs3XkjLj2x8RxXVYW5rMaWcL2AqqpOIiKmc2WGKtVavw9swkSZL2ICqImL8wh7nlHsGpxxvk1bv9y2twI/E/yFm2hryOvfELCn2MaGjWq4KFRDOztwgvA8FYbOrSajmuNpjnLGxWMOZzBnd8ap6G8OOs34=
*/