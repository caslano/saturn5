/* Copyright 2003-2020 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_AUTO_SPACE_HPP
#define BOOST_MULTI_INDEX_DETAIL_AUTO_SPACE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/multi_index/detail/adl_swap.hpp>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/noncopyable.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <memory>

namespace boost{

namespace multi_index{

namespace detail{

/* auto_space provides uninitialized space suitably to store
 * a given number of elements of a given type.
 */

/* NB: it is not clear whether using an allocator to handle
 * zero-sized arrays of elements is conformant or not. GCC 3.3.1
 * and prior fail here, other stdlibs handle the issue gracefully.
 * To be on the safe side, the case n==0 is given special treatment.
 * References:
 *   GCC Bugzilla, "standard allocator crashes when deallocating segment
 *    "of zero length", http://gcc.gnu.org/bugzilla/show_bug.cgi?id=14176
 *   C++ Standard Library Defect Report List (Revision 28), issue 199
 *     "What does allocate(0) return?",
 *     http://www.open-std.org/jtc1/sc22/wg21/docs/lwg-defects.html#199
 */

template<typename T,typename Allocator=std::allocator<T> >
struct auto_space:private noncopyable
{
  typedef typename rebind_alloc_for<
    Allocator,T>
  ::type                                   allocator;
  typedef allocator_traits<allocator>      alloc_traits;
  typedef typename alloc_traits::pointer   pointer;
  typedef typename alloc_traits::size_type size_type;

  explicit auto_space(const Allocator& al=Allocator(),size_type n=1):
  al_(al),n_(n),data_(n_?alloc_traits::allocate(al_,n_):pointer(0))
  {}

  ~auto_space(){if(n_)alloc_traits::deallocate(al_,data_,n_);}

  Allocator get_allocator()const{return al_;}

  pointer data()const{return data_;}

  void swap(auto_space& x)
  {
    swap(
      x,
      boost::integral_constant<
        bool,alloc_traits::propagate_on_container_swap::value>());
  }

  void swap(auto_space& x,boost::true_type /* swap_allocators */)
  {
    adl_swap(al_,x.al_);
    std::swap(n_,x.n_);
    std::swap(data_,x.data_);
  }
    
  void swap(auto_space& x,boost::false_type /* swap_allocators */)
  {
    std::swap(n_,x.n_);
    std::swap(data_,x.data_);
  }

private:
  allocator al_;
  size_type n_;
  pointer   data_;
};

template<typename T,typename Allocator>
void swap(auto_space<T,Allocator>& x,auto_space<T,Allocator>& y)
{
  x.swap(y);
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* auto_space.hpp
7NDYkpx0oFXJG6aI8ffB3QkaDh5EiT9fxOhU1K+HmZ3DcO4v/F2Mo7oOxr93F8GwZxE/tgzn71BcZpiqfThwwry9cfcAXrsDIG9Z3Ihw8KCLvEdAcOqPOb2xDoe5fZ19v79FsJ7R9i/Yo7FqPdOEk6YGKZOJQwuSPvXEm9S4Xn/q7wYJP0Xq6PE3xfCttfn2Zr00xDr6oonDLNKTL9+TuGdupjlwBZjco+6H9zarcqJMuBcxuBqM4V8h4dTf9pmb63DIoM4/rF11eHdo//sBw4f3v8VbUg7vf99h2GD/W91Hce57+hcMU30TseVbUQzahOSZYcP75fKtkcP6JX7XEYf7+np6IunfRuNb4PBpibbnRcSewnzUh/t1ePUpQX/Yt4VwOZfqmZ2+9YIY+zQ00HfSyxrUF0qY5kmU2rbAlSLz0QIdgfBzkeWJG5ahJ8BmQ7vpqCT6aew9w9KI0zS0Us8SUBLcw5A0DlB+IcqsLOMwLAh/0BfcJM+XH+apm1s+yKg9A/Fbh2fvgsrYjnD80LEDzwMh/tnh/gSPU7lM5KFtyzoAKX0Uy/nLlD/jek5seYHik8hJffUYv7DytLBCW+hJDvloQ0D54KDRi8I4sH0t0YQT8+ZKxyz/WaP8RRynflkmKIdLY94+7+F17RUhOGItUKyzgU667o4+GHkfCOOwCP28klld6coZjdfZVzg/SxzZ0ZwA+PWKgefpO7zPxHlkOa4XC6YlqPVN99H2UlTmwbHtWL6bqVob9Al5xehfWRzbYZoJav2oy6zrd9fLebskiV16RSYMK+aB9r8DyBGfYGkaxH4otLIGfTRp/kHKT4WTBLkXZ3lfYJLX7Qznp4FbpHbgCNTqGGM+pHy4hudlVuQGhD+J+uSH6DHCyu4KL7X8oIyVENwU6bZVrwTrDy07ovPXobIzgWM5ZRZmQn+UNL+r+c9gfD9MfTuPCqE/VgP8F/DyF4EV+FZYDXtqEIh+So12dLzAShKXCjTXZUerExI4TqhcIeB4wCrdGMXk2FqqhSwt80kuUySyKG5cUJmVXi2DY4X1Fy/2nNwPAoEfCtNW+Fu8PaMgsLIidkV1LYDNSZjGT1gahZPmZeqXAg1ETB+tl40+JgseBH6hBOh3BX1AvsKs48jKnDwUtUmbNOKhjSnQBySTs4WfRoEVFzGRo5WA+bsflTvqhklmJ3agLHdpeXo4Zhjf91zLcstS8Wm+0HeXa5SnKNO0zKJCSEPq9mBFC/y2sHScKHLiOAnh2gdry1U9hy1S/oMDz0pzV1YzGG0PzGEdys1FbnvgNi8S1TeVeaGzfP1tYeXIRVB4sorz6oOv+u80/I14JGstgRc1PYZsfUeAxZMILwg9O/Zy0VqTvqO2NrakOEwI0qndJhqFGb4zP0/jKEUoq7OMU6vyMwjW9pXfPl1HbezvVC4TSRkWvmt7Yn5z4yTIdFY6A2PkJ1SmEJmfOE5oO0J/4Gll+fobQWUcR5SBnYdpVgj5UYSyzT8NNhPbVVjfv+iBV/LvchpaReqUKh6YAyAWw2fghq/7KZMthOfZmZ0GJZftbUqPbHIMLqrMwK0/c23weBaPLYI4zRM3siGenvJZCLHB5oeP4+dRuVIERZ7nthMSH35kgiV3M15L5Y7EuV+Edp6JFdk8W10jjbfyNOIoi/M0dUW9jph+yhFwjbj6NNMf3wdZmSJROo6Tyz+iXlBMy6X+1uZ6e1E1zDKUkvXhC0w+EW5WJKEPo7O1uiSfzQTBbfqwpdv2EovDFWWROWnpukJ9QKaHda8FX68nztL+5Ykw8Uo7ipQPQj2GoTlZ+vIvHemCc0k0sJ8eZvHYwi+y0AlTT0WE1pXDIllpLwo=
*/