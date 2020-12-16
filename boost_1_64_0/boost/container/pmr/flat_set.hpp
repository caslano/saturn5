//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_SET_HPP
#define BOOST_CONTAINER_PMR_SET_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/flat_set.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class Key
         ,class Compare = std::less<Key> >
using flat_set = boost::container::flat_set<Key, Compare, polymorphic_allocator<Key> >;

template <class Key
         ,class Compare = std::less<Key> >
using flat_multiset = boost::container::flat_multiset<Key, Compare, polymorphic_allocator<Key> >;

#endif

//! A portable metafunction to obtain a flat_set
//! that uses a polymorphic allocator
template <class Key
         ,class Compare = std::less<Key> >
struct flat_set_of
{
   typedef boost::container::flat_set<Key, Compare, polymorphic_allocator<Key> > type;
};

//! A portable metafunction to obtain a flat_multiset
//! that uses a polymorphic allocator
template <class Key
         ,class Compare = std::less<Key> >
struct flat_multiset_of
{
   typedef boost::container::flat_multiset<Key, Compare, polymorphic_allocator<Key> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_SET_HPP

/* flat_set.hpp
WgtrI/Mx2/168q+wXpFz5wN33gtzxXhcAWbzql73w4Ixzv2LVyyRzGI2seuTq2GpZLwPn/89cCosR9gVz3/8HqyYzMvsjpSXHoVViLjrnrthM6yBzGbWEWNNgLWJnPeVb/8Y1i3izPNZsIjSd3es8/i0yXzMVl29cCMsgYznnLXj2VmwJBHXdOv5dbBMYR/PPflqWD6ZzWxgR9P9sBIR98TFZz8CqxZxa78tzoA1knmZjZ+YsgjWRua0/XWIODN3COsVy8y8qweLiFrMdSrMPizazLUoLF6xVDJey/Gtbz+J40oWGWo5QMcVs/5guWQemDgPyRdm+g4rEDn333//x7ASMptZ7IGnV8OqhD232NsIayDzMjvp4gmfwFqFlXx0+WJYl6jl5aPPeBTWJ9or2BpKgXnctI0x21G2/BVYnLBPpm9fCksj47Vk/fW3FFiIjLf3+Km+F2FhYWdf9cEuWKnIGRO3qQxWReaBieviGpHzofaHV8KaRM6SJauvh7W7ncdEt9t5TPQq1q9YRDH34dG1HBb6w3Ewm8wpzs9Mjs8gM7nM4slsZqNaeg7AUoUtqrjoHVhIaS9H9CH/w0lthyzPFWZxv9P8i6kFVijM9A9WrFipYuXCTJ2wSlMnM7PeYbVKnfVKe42KNSvWqlg7s4MxY6OsU7FuxXoV61csopj7CGezFLMV8ysWVCxesUTFkhVLVSxdsUzFQorlKJanWFixQsWKhZn7Y7BSJa5csUrFqhWrVaxesUbFmhVrVaxdsU7FuhXrVaxfsYhi7iOdzVLMVsyvWFCxeMUSFUtWLFWxdMUyFQsplqNYnmJhxQoVK1asVLFyxSoVq1asVrF6xRoVa2Ym9y+tjnF0n4uZKzY1yjoV61asV7F+xSKKuT3OZilmK+Yns5iZZ+9g8WQ2s0WvDM+EpQpLenLRTFiIzMvs62tuehOWL8w86wArFnXy+42lor3b9967A1YtcvY2Ld8Ca1DaaxXtmfECaxdxuU1XrYf1iFrM8xMw11HRceY6FWaTOcXFkznVmaLEZYm485644CFYHpmP2fUvuNfCSkTcy7Njn4RVirinrlrSC2sQtZh5aFibsH/e+0w+rEe0V3P8lodhERF37OkpiTB7SLT9ff3mT2DxZLzON4Z8czQsjYy3t/CWBdNgIRE384s/h2AFZE7roZTMaXyWK1apWDWZ0/ZXr1gzmdM462DtxcSGoudi2fKMjb1v8PkesgFh5nvGMO/RtMyYmW8XweLJPMzMtQwskczLjM/bpJGhf4fF8uvifFcWy+mOnTDYB7JsxXIVyxdmtndYAZnNbPKSyNuwMmHfbjpvP6xGyVkn4l5cOicB1iLs8A+rwrAupQ89Snt9Sh88lnMfApZzzjjLOWeKkjNL5DTXxbBsS1l/iuUrVqBYkWIlipUpVuFo9Hwds8Njz42yGsXqFGsgs5iZbQXWQuZjZt7jg3WLuC8/u/l+WD+Zzaxp908NMOsY2m6ZFUx64zhYgIzHmX0ILOkYpzrpXQwy9O+I2HOi38VQLEuxbMVyFctXrECxIsVKFCtTrEKxKsVqFKtTrEGxJsVaFGtTrEOxLsV6FOtTbECY2Z/BXMdGG3/PxkNmMePvA/mE8XEdp8QlKZZG5mVmzjVgISUuj8zHzLwnDCsRZt4vhlWL9vi7SQ1Key0irvXAUc/COslsZmuf/MN2WL+IWzjk2aUwz3HKsibjcVW7C3ph8WQeZuZcA5aoWDKZn9nkBQOjYSEym5k5p4WFhaUe1fwTrFTUOfXOJ1ywKjIfs8au7ZNhjSInfw+sncxp/fWROY0Xtze6fwfOmf4OLOh1Xu9JZLwW8y09WAYZr+XT/Fsuh+U=
*/