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
#include <boost/container/detail/placement_new.hpp>
// intrusive
#include <boost/intrusive/slist.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/twin.hpp>
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
   typedef boost::intrusive::twin<void_pointer> pointer_pair;

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
         elem += difference_type(unit_bytes);
         for(size_type i = 0; i != num_units-1u; ++i, elem += difference_type(unit_bytes)){
            ::new (boost::movelib::to_raw_pointer(prev_elem), boost_container_new_t()) void_pointer(elem);
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

   pointer_pair extract_data()
   {
      if(BOOST_LIKELY(!slist_impl_.empty())){
         pointer_pair ret
            (slist_impl_.begin().operator->()
            ,slist_impl_.last().operator->());
         slist_impl_.clear();
         return ret;
      }
      else {
         return pointer_pair();
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
      , dtl::cast_functor <T> >                          iterator;
   typedef typename MultiallocationChain::size_type      size_type;
   typedef boost::intrusive::twin<pointer>               pointer_pair;

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

   pointer_pair extract_data()
   {
      typename MultiallocationChain::pointer_pair data(this->MultiallocationChain::extract_data());
      return pointer_pair(cast(data.first), cast(data.second));
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