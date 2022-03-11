//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_MULTIALLOCATION_CHAIN_HPP
#define BOOST_CONTAINER_DETAIL_MULTIALLOCATION_CHAIN_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
// container
#include <boost/container/container_fwd.hpp>
// container/detail
#include <boost/move/detail/to_raw_pointer.hpp>
#include <boost/container/detail/transform_iterator.hpp>
#include <boost/container/detail/type_traits.hpp>
// intrusive
#include <boost/intrusive/slist.hpp>
#include <boost/intrusive/pointer_traits.hpp>
// move
#include <boost/move/utility_core.hpp>

namespace boost {
namespace container {
namespace dtl {

template<class VoidPointer>
class basic_multiallocation_chain
{
   private:
   typedef bi::slist_base_hook<bi::void_pointer<VoidPointer>
                        ,bi::link_mode<bi::normal_link>
                        > node;

   typedef typename boost::intrusive::pointer_traits
      <VoidPointer>::template rebind_pointer<char>::type    char_ptr;
   typedef typename boost::intrusive::
      pointer_traits<char_ptr>::difference_type             difference_type;

   typedef bi::slist< node
                    , bi::linear<true>
                    , bi::cache_last<true>
                    , bi::size_type<typename boost::container::dtl::make_unsigned<difference_type>::type>
                    > slist_impl_t;
   slist_impl_t slist_impl_;

   typedef typename boost::intrusive::pointer_traits
      <VoidPointer>::template rebind_pointer<node>::type    node_ptr;
   typedef typename boost::intrusive::
      pointer_traits<node_ptr>                              node_ptr_traits;

   static node & to_node(const VoidPointer &p)
   {  return *static_cast<node*>(static_cast<void*>(boost::movelib::to_raw_pointer(p)));  }

   static VoidPointer from_node(node &n)
   {  return node_ptr_traits::pointer_to(n);  }

   static node_ptr to_node_ptr(const VoidPointer &p)
   {  return node_ptr_traits::static_cast_from(p);   }

   BOOST_MOVABLE_BUT_NOT_COPYABLE(basic_multiallocation_chain)

   public:

   typedef VoidPointer                       void_pointer;
   typedef typename slist_impl_t::iterator   iterator;
   typedef typename slist_impl_t::size_type  size_type;

   basic_multiallocation_chain()
      :  slist_impl_()
   {}

   basic_multiallocation_chain(const void_pointer &b, const void_pointer &before_e, size_type n)
      :  slist_impl_(to_node_ptr(b), to_node_ptr(before_e), n)
   {}

   basic_multiallocation_chain(BOOST_RV_REF(basic_multiallocation_chain) other)
      :  slist_impl_(::boost::move(other.slist_impl_))
   {}

   basic_multiallocation_chain& operator=(BOOST_RV_REF(basic_multiallocation_chain) other)
   {
      slist_impl_ = ::boost::move(other.slist_impl_);
      return *this;
   }

   bool empty() const
   {  return slist_impl_.empty(); }

   size_type size() const
   {  return slist_impl_.size();  }

   iterator before_begin()
   {  return slist_impl_.before_begin(); }

   iterator begin()
   {  return slist_impl_.begin(); }

   iterator end()
   {  return slist_impl_.end(); }

   iterator last()
   {  return slist_impl_.last(); }

   void clear()
   {  slist_impl_.clear(); }

   iterator insert_after(iterator it, void_pointer m)
   {  return slist_impl_.insert_after(it, to_node(m));   }

   void push_front(const void_pointer &m)
   {  return slist_impl_.push_front(to_node(m));  }

   void push_back(const void_pointer &m)
   {  return slist_impl_.push_back(to_node(m));   }

   void_pointer pop_front()
   {
      node & n = slist_impl_.front();
      void_pointer ret = from_node(n);
      slist_impl_.pop_front();
      return ret;
   }

   void splice_after(iterator after_this, basic_multiallocation_chain &x, iterator before_b, iterator before_e, size_type n)
   {  slist_impl_.splice_after(after_this, x.slist_impl_, before_b, before_e, n);   }

   void splice_after(iterator after_this, basic_multiallocation_chain &x)
   {  slist_impl_.splice_after(after_this, x.slist_impl_);   }

   void erase_after(iterator before_b, iterator e, size_type n)
   {  slist_impl_.erase_after(before_b, e, n);   }

   void_pointer incorporate_after(iterator after_this, const void_pointer &b, size_type unit_bytes, size_type num_units)
   {
      typedef typename boost::intrusive::pointer_traits<char_ptr> char_pointer_traits;
      char_ptr elem = char_pointer_traits::static_cast_from(b);
      if(num_units){
         char_ptr prev_elem = elem;
         elem += unit_bytes;
         for(size_type i = 0; i != num_units-1; ++i, elem += unit_bytes){
            ::new (boost::movelib::to_raw_pointer(prev_elem)) void_pointer(elem);
            prev_elem = elem;
         }
         slist_impl_.incorporate_after(after_this, to_node_ptr(b), to_node_ptr(prev_elem), num_units);
      }
      return elem;
   }

   void incorporate_after(iterator after_this, void_pointer b, void_pointer before_e, size_type n)
   {  slist_impl_.incorporate_after(after_this, to_node_ptr(b), to_node_ptr(before_e), n);   }

   void swap(basic_multiallocation_chain &x)
   {  slist_impl_.swap(x.slist_impl_);   }

   static iterator iterator_to(const void_pointer &p)
   {  return slist_impl_t::s_iterator_to(to_node(p));   }

   std::pair<void_pointer, void_pointer> extract_data()
   {
      if(BOOST_LIKELY(!slist_impl_.empty())){
         std::pair<void_pointer, void_pointer> ret
            (slist_impl_.begin().operator->()
            ,slist_impl_.last().operator->());
         slist_impl_.clear();
         return ret;
      }
      else {
         return std::pair<void_pointer, void_pointer>();
      }
   }
};

template<class T>
struct cast_functor
{
   typedef typename dtl::add_reference<T>::type result_type;
   template<class U>
   result_type operator()(U &ptr) const
   {  return *static_cast<T*>(static_cast<void*>(&ptr));  }
};

template<class MultiallocationChain, class T>
class transform_multiallocation_chain
   : public MultiallocationChain
{
   private:
   BOOST_MOVABLE_BUT_NOT_COPYABLE(transform_multiallocation_chain)
   //transform_multiallocation_chain(const transform_multiallocation_chain &);
   //transform_multiallocation_chain & operator=(const transform_multiallocation_chain &);

   typedef typename MultiallocationChain::void_pointer   void_pointer;
   typedef typename boost::intrusive::pointer_traits
      <void_pointer>                                     void_pointer_traits;
   typedef typename void_pointer_traits::template
      rebind_pointer<T>::type                            pointer;
   typedef typename boost::intrusive::pointer_traits
      <pointer>                                          pointer_traits;

   static pointer cast(const void_pointer &p)
   {  return pointer_traits::static_cast_from(p);  }

   public:
   typedef transform_iterator
      < typename MultiallocationChain::iterator
      , dtl::cast_functor <T> >             iterator;
   typedef typename MultiallocationChain::size_type      size_type;

   transform_multiallocation_chain()
      : MultiallocationChain()
   {}

   transform_multiallocation_chain(BOOST_RV_REF(transform_multiallocation_chain) other)
      : MultiallocationChain(::boost::move(static_cast<MultiallocationChain&>(other)))
   {}

   transform_multiallocation_chain(BOOST_RV_REF(MultiallocationChain) other)
      : MultiallocationChain(::boost::move(static_cast<MultiallocationChain&>(other)))
   {}

   transform_multiallocation_chain& operator=(BOOST_RV_REF(transform_multiallocation_chain) other)
   {
      return static_cast<MultiallocationChain&>
         (this->MultiallocationChain::operator=(::boost::move(static_cast<MultiallocationChain&>(other))));
   }

   void push_front(const pointer &mem)
   {   this->MultiallocationChain::push_front(mem);  }

   void push_back(const pointer &mem)
   {  return this->MultiallocationChain::push_back(mem);   }

   void swap(transform_multiallocation_chain &other_chain)
   {  this->MultiallocationChain::swap(other_chain); }

   void splice_after(iterator after_this, transform_multiallocation_chain &x, iterator before_b, iterator before_e, size_type n)
   {  this->MultiallocationChain::splice_after(after_this.base(), x, before_b.base(), before_e.base(), n);  }

   void incorporate_after(iterator after_this, pointer b, pointer before_e, size_type n)
   {  this->MultiallocationChain::incorporate_after(after_this.base(), b, before_e, n);  }

   pointer pop_front()
   {  return cast(this->MultiallocationChain::pop_front());  }

   bool empty() const
   {  return this->MultiallocationChain::empty(); }

   iterator before_begin()
   {  return iterator(this->MultiallocationChain::before_begin());   }

   iterator begin()
   {  return iterator(this->MultiallocationChain::begin());   }

   iterator last()
   {  return iterator(this->MultiallocationChain::last());  }

   iterator end()
   {  return iterator(this->MultiallocationChain::end());   }

   size_type size() const
   {  return this->MultiallocationChain::size();  }

   void clear()
   {  this->MultiallocationChain::clear(); }

   iterator insert_after(iterator it, pointer m)
   {  return iterator(this->MultiallocationChain::insert_after(it.base(), m)); }

   static iterator iterator_to(const pointer &p)
   {  return iterator(MultiallocationChain::iterator_to(p));  }

   std::pair<pointer, pointer> extract_data()
   {
      std::pair<void_pointer, void_pointer> data(this->MultiallocationChain::extract_data());
      return std::pair<pointer, pointer>(cast(data.first), cast(data.second));
   }
/*
   MultiallocationChain &extract_multiallocation_chain()
   {  return holder_;  }*/
};

}}}

// namespace dtl {
// namespace container {
// namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_DETAIL_MULTIALLOCATION_CHAIN_HPP

/* multiallocation_chain.hpp
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
*/