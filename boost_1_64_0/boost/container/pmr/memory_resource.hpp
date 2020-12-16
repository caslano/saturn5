//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_MEMORY_RESOURCE_HPP
#define BOOST_CONTAINER_PMR_MEMORY_RESOURCE_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/container_fwd.hpp>
#include <boost/move/detail/type_traits.hpp>
#include <cstddef>

namespace boost {
namespace container {
namespace pmr {

//! The memory_resource class is an abstract interface to an
//! unbounded set of classes encapsulating memory resources.
class BOOST_CONTAINER_DECL memory_resource
{
   public:
   // For exposition only
   static BOOST_CONSTEXPR_OR_CONST std::size_t max_align =
      boost::move_detail::alignment_of<boost::move_detail::max_align_t>::value;

   //! <b>Effects</b>: Destroys
   //! this memory_resource.
   virtual ~memory_resource(){}

   //! <b>Effects</b>: Equivalent to
   //! `return do_allocate(bytes, alignment);`
   void* allocate(std::size_t bytes, std::size_t alignment = max_align)
   {  return this->do_allocate(bytes, alignment);  }

   //! <b>Effects</b>: Equivalent to
   //! `return do_deallocate(bytes, alignment);`
   void  deallocate(void* p, std::size_t bytes, std::size_t alignment = max_align)
   {  return this->do_deallocate(p, bytes, alignment);  }

   //! <b>Effects</b>: Equivalent to
   //! `return return do_is_equal(other);`
   bool is_equal(const memory_resource& other) const BOOST_NOEXCEPT
   {  return this->do_is_equal(other);  }

   //! <b>Returns</b>:
   //!   `&a == &b || a.is_equal(b)`.
   friend bool operator==(const memory_resource& a, const memory_resource& b) BOOST_NOEXCEPT
   {  return &a == &b || a.is_equal(b);   }

   //! <b>Returns</b>:
   //!   !(a == b).
   friend bool operator!=(const memory_resource& a, const memory_resource& b) BOOST_NOEXCEPT
   {  return !(a == b); }

   protected:
   //! <b>Requires</b>: Alignment shall be a power of two.
   //!
   //! <b>Returns</b>: A derived class shall implement this function to return a pointer
   //!   to allocated storage with a size of at least bytes. The returned storage is
   //!   aligned to the specified alignment, if such alignment is supported; otherwise
   //!   it is aligned to max_align.
   //!
   //! <b>Throws</b>: A derived class implementation shall throw an appropriate exception if
   //!   it is unable to allocate memory with the requested size and alignment.
   virtual void* do_allocate(std::size_t bytes, std::size_t alignment) = 0;

   //! <b>Requires</b>: p shall have been returned from a prior call to
   //!   `allocate(bytes, alignment)` on a memory resource equal to *this, and the storage
   //!   at p shall not yet have been deallocated.
   //!
   //! <b>Effects</b>: A derived class shall implement this function to dispose of allocated storage.
   //!
   //! <b>Throws</b>: Nothing.
   virtual void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) = 0;

   //! <b>Returns</b>: A derived class shall implement this function to return true if memory
   //!   allocated from this can be deallocated from other and vice-versa; otherwise it shall
   //!   return false. <i>[Note: The most-derived type of other might not match the type of this.
   //!   For a derived class, D, a typical implementation of this function will compute
   //!   `dynamic_cast<const D*>(&other)` and go no further (i.e., return false)
   //!   if it returns nullptr. - end note]</i>.
   virtual bool do_is_equal(const memory_resource& other) const BOOST_NOEXCEPT = 0;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_PMR_MEMORY_RESOURCE_HPP

/* memory_resource.hpp
BFgRmc3sqTf3/QyrMDmZ8ZxVjjbBVcP6Hh+bw+b56HfgWHvn0DuFZlnD2kwcTLzn3aVYn2KuS53NS8ZrGXvZ8EthcWReZnyZJSuWQeZjdt2VrWtgecLMGISVKHVWiDqXVC6wYHVKLc1KLV1KLRGlFusy51qCZE61JJE5rfcMxXIVK1KsgsypDzWKNSjWoliHYj2KDSjmudzZfIrFKZZE5mHGt+kUxdIUy1AsS7FsxXIVy1esQLEixUoUK1OsQrEqxWqUddSgxDUp1qJYm2IdSi09ig0o5klVxq5icYolKZamWJZiuYoVpCpjSbESxcoUq1CsSrEaxeoUa1CsSbEWxdoU61CsS7GeVGUMKnGuPzibRzGvo812+ZidG5sXZQHF4hRLUCxJsRTF0shsZuZaG5bN4s7j7yyT5SqWr1iBYkWKlShWpliFYlWK1ShWR2Yz48usRcTdXvHGg7A2JWeHYl2K9SjWp9iAYq4/OptHMa9iPsUCisUplqBYkmIpiqWRWczM9RgsS4nLJrOZHVyxoAlWIOyV517+DFZG5mUW/OdDu2HVSnu1itUr1qhYs2KtirULM/PesE5hZv4M1i2Wy0XZL34OiwgbM/TnfTD7iuhldt7tL3bB4sh43PayS5+ApVyhrHcyH7PNj684BpZDZjFbveaaq2Fh0V7ph3esg5WKnGu/HDEVViP6ULfw2cdhjcKOeyOhD9YWbWx+KcHVzfqXEBse7B9Zr2L9ikUUc6c5m6WY7WhzXH5mY2NzoyyoWLxiiYolK5aqWLpimYqFFMtRLE+xsGKFihUrVqpYuWKVilUrVqtYvTD+bbRGMpvZwFe7smHtZF5mxz3T/Aysh8zH7Lq4U0bD3FdGx/HfpfGROdUZUCxOsQTFkhRLIbOYHT2wcy8sg8zPLHx31yRYvujfzoylQ2HFIqeZk4OVk9nMHgqv/QxWK3Kab1zDmkRO/ptKbaJ//P2ODtHe5sWTG2B9or1g58wpMPfk6LjP46fHwPxkPK7qgYfvhiWIOP9Dy36EpZH5mPUf+VQ/LEfkXPnjE9fACsj8fJm5T+qBVYj2jnT9+TJYnbAJG7Y+CWsR7fnu3/knWKeIG33n6iRYP5nTWIoo5p7iZOe6LGbjYsdGma2YX7GgYvFkFjPzDWhYMpnN7Nutv5TCMoVNfvLMFlieaM+co8DCwsy+B1aoWLFob0p8xkOwStGH3XljT4HVirjnn/r1TFizsAu2jZ4B6yTzMjvrt7VuWJ+I65mzrBjmSY+21JH3NcECZDxnzA2fJcISyZz6kErm1IcQM9mHMJlTH0rInPpQpfShQelDq9KHTqUP/UofrKuc+xAgc+pDEjPZhwwypz7kkPE+5IfzRsDCIs7Ms8NKyJy2sTIyH7PPsmrGwWpFzruWBr88ZPmuJpZzfOz9gznJWhRrU6xDsS7FehTrU2xAMddUZ/Mo5hXG9xM+ZoniXl1AsTjFEhRLUixFsTTFMhTLUixbsVzF8sksZsfmHFMMKyKzmW2655bDYf+j7n7goqzPAIC/d5xywAsccOgpJx6IeirqqWBkNs9EJbOitKJGiYpJxvRUVFTUS8nIqFBJWdGiJKNGhUWFmxVbVKRYzLFFiYrGzIw1WlZs0drz6+7ZPfeb75N/1vaZ53Fw33t+z/P7vb/3z70cd2VgJmLLXot+Aa1aivt8aZQBrYGppYmxFsbaJKNzokOqRZxfQushcclSm4ZrtU1lzMyYlbEExhIZSwIzERPH12hpjGWCqcTE+V20XMYKpFr89tOMFWsavC8qsfHy+6IyVslYNWO1jO1jrIGxJsZaJJsw+ve5aG2SiWN2tA7J6Jh1MvnOMHE9YCqxzZF1jWg=
*/