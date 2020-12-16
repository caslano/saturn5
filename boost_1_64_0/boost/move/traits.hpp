//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2009-2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_TRAITS_HPP
#define BOOST_MOVE_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
#include <boost/move/core.hpp>
#endif
#include <boost/move/detail/meta_utils.hpp>
#include <boost/move/detail/type_traits.hpp>

namespace boost {

//! If this trait yields to true
//! (<i>has_trivial_destructor_after_move &lt;T&gt;::value == true</i>)
//! means that if T is used as argument of a move construction/assignment,
//! there is no need to call T's destructor.
//! This optimization tipically is used to improve containers' performance.
//!
//! By default this trait is true if the type has trivial destructor,
//! every class should specialize this trait if it wants to improve performance
//! when inserted in containers.
template <class T>
struct has_trivial_destructor_after_move
   : ::boost::move_detail::is_trivially_destructible<T>
{};

//! By default this traits returns
//! <pre>boost::is_nothrow_move_constructible<T>::value && boost::is_nothrow_move_assignable<T>::value </pre>.
//! Classes with non-throwing move constructor
//! and assignment can specialize this trait to obtain some performance improvements.
template <class T>
struct has_nothrow_move
{
   static const bool value = boost::move_detail::is_nothrow_move_constructible<T>::value &&
                             boost::move_detail::is_nothrow_move_assignable<T>::value;
};

namespace move_detail {

template <class T>
struct is_nothrow_move_constructible_or_uncopyable
{
   //The standard requires is_nothrow_move_constructible for move_if_noexcept
   //but a user (usually in C++03) might specialize has_nothrow_move which includes it
   static const bool value = is_nothrow_move_constructible<T>::value ||
                             has_nothrow_move<T>::value ||
                            !is_copy_constructible<T>::value;
};

}  //move_detail {
}  //namespace boost {

#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_TRAITS_HPP

/* traits.hpp
fGTHmPIudIYIlC6+dsrQzLayyUrLZpfE6m0La3Ya1jrme4HZt3AdCMr2PTn7ihZuL0G6cySWXFkKeMM7VabN1WnHzi3ovMvMPRDc83UL5TDSFMdxJlad0hkspJa43iHUg6ER3aDdRY5fKfctZ+xgVnFAd5HfWbr/v9ldZFv7rfK6Tuy3Suh4CXsq7f/RaMP/Yxdz/4H8P67c39r/Y+8v7/9xBPO/N/Y3y+U3yzSn2/4fzdb+H81cGj9jvJKJYLw7lEobMoNJ6PvTW8bB+X/U2qbp/h+P6cj/4+Oelv4fG9P9P5oElPB04P/RYP+PjS19+zWma5MA1SlAxU7/yMXf0keE/8cGGi2F4eRa+kkghyv/j9+lagnhf8aN3xb+H13z3CFmYblsbHgmsQErk5DhNgYWhXWJUnL/CPZmuvm2Xgh2Of2AmAT3j4DBFQCrh3QJU+yz/BLAk7qOZhpdT/DmrroCKcOdRgNyzOigATlmLE6n9NHpLgSFsG8XKbjKmcRBZNxtFHQe4OZukcndQh2DolvQddWXXR205B5X+y15QI+OWAldVdKYo4IlK248YDN5IKGDV0Z0WvLKWNTIXhmL6q0QhWTFcwjjeC/rwOpSpI4kKjDLJBFoffCJoh20umDWZt7hHJ/92QmjCQruFBTUVwZ3qpF6+eLPKshW5hx36Ej6jqbvqfQ9Y87XW0f0q/zo/czRWDTixjmYz5V08UibNCRdc3GAHh+ACW61n8wAES/SDSIPrVNHIhEASC8Vi5jKzzbQM7hgPj0Js0ecTXfN0JM+oIVngg0MjjxiOWu+oPZN/dnHvZvV2PpvrMukhYy+cKvCT80tanKGV1Y0AcX1OWv2AcX9hILK5kHZkhrdEPDLk+u4ZM+JknlFyWIE41zuwArLBgBz3fuoRY4zxlniEyi5oFbV7uDG3bAGp8e9Cj914+5MsmLeZlR6OCrj8tuVecfLlfGiMhvoqdqlCZTb28DV+auojk9U5wGCanE3unL3BgbnCp2kb0m3jjtcrnK87db2dK9d26yNu7u3U9sA1eorIITLrQnxKw8TwgdCPOexCbGPS9/EhBgmpJEZghBLPQcmRNkBCHFiO4QAjWRf8bRLo0Eem0bejbvz2iFEd6rwv5h8+Zp8t7uZfBkg3yy3Tb79XOd9TL7zBPkyBfmmuw9Mvu8egHzntE++Me2SL36EPg9unz9sdtn8wb2xrl+b/IGMeYJFtB3Vvf2oQPtRmRTVSV5EJfRdn8VktyC35wlZ7kNp4RFiI0Wd8an4/89X95H6OFgVBLhBuvKkxz39Qw+bg+U5JE/blFpYEqr2C834VwUA8+Up9pT2lFpqHkOtuvHDzKrd/StfQ5el1NUhhxnYEA1PMmunYoSufEwiBY+70p6NpiukZ8LQf4qU/oOVr9YJCWZ1jm3MFpGZVR+cWvnqvLYi02PW8PzhUTnmu4JV30+bNP7slrnOpB3WRrN7VV1WlwYhQKt22yZ4ERegTt9lXttxme3GpUWsYS5+vVsWx+ULVj3kcrLuabI4wfkLkAbUzSNeWvlaU2vqIrK7IHDbkYEDRWaKyE40GrPOF11OFvmkSxUTVyC4SfqR/kLlq/vabq+89toLkd0PFBkQkV+2G2R2qLf23/LR+mDfeQn7+yaHfE2f7uThwvslxoUr2bfkK0KMu2c1Cw3QfFt59xqirbc3fgwRi4SztKiJDYpezmnY5INK9pidrJaSmZkkYVTSeZgN5UwmKui5Ajp1AYHC8po4nIWpDnPZEmmk5IcJuWuhQl4nMtzsyHC8RJHnkUYN4lDHu4nPqsrzcMd8loH6zWqd1C2T4koTJXJoKoQh0GB1DAqn6tZMMpq3wzI=
*/