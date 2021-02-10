#ifndef BOOST_MOVE_DETAIL_PLACEMENT_NEW_HPP
#define BOOST_MOVE_DETAIL_PLACEMENT_NEW_HPP
///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
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

struct boost_move_new_t{};

//avoid including <new>
inline void *operator new(std::size_t, void *p, boost_move_new_t)
{  return p;  }

inline void operator delete(void *, void *, boost_move_new_t)
{}

#endif   //BOOST_MOVE_DETAIL_PLACEMENT_NEW_HPP

/* placement_new.hpp
lY90lKk6PAK8mxQyTFwog2KB5UZkptpaSVM0R45qxUbO6ZqKNKDfQjXmapGQezb/34WNEosgKTDcTmlRezBHFsfYjgscdYf6hWW3QQ2COcugiu93b98fkc8ETI+ZXGVcvVyvoToX4UuCK3xiyXYRxCLGVGi5BwlC0dq2Y89mg4Gu+h92DVrN45Nmc7SHFj5qYO017Kw94PTQGQztUd+tbeffltyPA8BA/FHPucBwDo2OjCJfHbWe7xPVjurWht37WH/V+92x+0MHvf9lr/Qhz84mrs64lj5AlkV4Ov1Ia4AMda+GU3/ac6/94XSjzkUYRz/U9s6n/pVtT3uj4fXGMirRKlxy5EmMdEGe4cSR0ZZA94iIfYezM8QtpiBgQkiFpFU74iIWXnji5LLIAg7oSJysGvBGFtjbK8h5goc4shg4zjs8pjQCQprRBnj4mrNXU7VEMtsrxELFqEHWDa8jee0MPTODENMAMpA3HxA8lcgfnn0rOpiNzz09bbfiUSHM/8RDBcfu9feD1pKPQXZt+2o/ZC35GGTbcSZOyeM9wL0+yv9Yrm+fzS4e44VR2C/AS0yd7TwGvNT4L3QUxgGLd5yOXw3ClGf6D0KToez43acg4UwU6frTZoaOZ6PRyzVSkQnQQ/nIzNwv5ekF
*/