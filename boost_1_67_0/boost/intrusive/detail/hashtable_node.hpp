/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2007-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_HASHTABLE_NODE_HPP
#define BOOST_INTRUSIVE_HASHTABLE_NODE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/detail/assert.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/trivial_value_traits.hpp>
#include <boost/intrusive/slist.hpp> //make_slist
#include <cstddef>
#include <climits>
#include <boost/move/core.hpp>


namespace boost {
namespace intrusive {

template <class Slist>
struct bucket_impl : public Slist
{
   typedef Slist slist_type;
   BOOST_INTRUSIVE_FORCEINLINE bucket_impl()
   {}

   BOOST_INTRUSIVE_FORCEINLINE bucket_impl(const bucket_impl &)
   {}

   BOOST_INTRUSIVE_FORCEINLINE ~bucket_impl()
   {
      //This bucket is still being used!
      BOOST_INTRUSIVE_INVARIANT_ASSERT(Slist::empty());
   }

   BOOST_INTRUSIVE_FORCEINLINE bucket_impl &operator=(const bucket_impl&)
   {
      //This bucket is still in use!
      BOOST_INTRUSIVE_INVARIANT_ASSERT(Slist::empty());
      return *this;
   }
};

template<class Slist>
struct bucket_traits_impl
{
   private:
   BOOST_COPYABLE_AND_MOVABLE(bucket_traits_impl)

   public:
   /// @cond

   typedef typename pointer_traits
      <typename Slist::pointer>::template rebind_pointer
         < bucket_impl<Slist> >::type                                bucket_ptr;
   typedef Slist slist;
   typedef typename Slist::size_type size_type;
   /// @endcond

   BOOST_INTRUSIVE_FORCEINLINE bucket_traits_impl(bucket_ptr buckets, size_type len)
      :  buckets_(buckets), buckets_len_(len)
   {}

   BOOST_INTRUSIVE_FORCEINLINE bucket_traits_impl(const bucket_traits_impl &x)
      : buckets_(x.buckets_), buckets_len_(x.buckets_len_)
   {}

   BOOST_INTRUSIVE_FORCEINLINE bucket_traits_impl(BOOST_RV_REF(bucket_traits_impl) x)
      : buckets_(x.buckets_), buckets_len_(x.buckets_len_)
   {  x.buckets_ = bucket_ptr();   x.buckets_len_ = 0;  }

   BOOST_INTRUSIVE_FORCEINLINE bucket_traits_impl& operator=(BOOST_RV_REF(bucket_traits_impl) x)
   {
      buckets_ = x.buckets_; buckets_len_ = x.buckets_len_;
      x.buckets_ = bucket_ptr();   x.buckets_len_ = 0; return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE bucket_traits_impl& operator=(BOOST_COPY_ASSIGN_REF(bucket_traits_impl) x)
   {
      buckets_ = x.buckets_;  buckets_len_ = x.buckets_len_; return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE const bucket_ptr &bucket_begin() const
   {  return buckets_;  }

   BOOST_INTRUSIVE_FORCEINLINE size_type  bucket_count() const
   {  return buckets_len_;  }

   private:
   bucket_ptr  buckets_;
   size_type   buckets_len_;
};

template <class NodeTraits>
struct hash_reduced_slist_node_traits
{
   template <class U> static detail::no_type test(...);
   template <class U> static detail::yes_type test(typename U::reduced_slist_node_traits*);
   static const bool value = sizeof(test<NodeTraits>(0)) == sizeof(detail::yes_type);
};

template <class NodeTraits>
struct apply_reduced_slist_node_traits
{
   typedef typename NodeTraits::reduced_slist_node_traits type;
};

template <class NodeTraits>
struct reduced_slist_node_traits
{
   typedef typename detail::eval_if_c
      < hash_reduced_slist_node_traits<NodeTraits>::value
      , apply_reduced_slist_node_traits<NodeTraits>
      , detail::identity<NodeTraits>
      >::type type;
};

template<class NodeTraits>
struct get_slist_impl
{
   typedef trivial_value_traits<NodeTraits, normal_link> trivial_traits;

   //Reducing symbol length
   struct type : make_slist
      < typename NodeTraits::node
      , boost::intrusive::value_traits<trivial_traits>
      , boost::intrusive::constant_time_size<false>
      , boost::intrusive::size_type<std::size_t>
      >::type
   {};
};

template<class BucketValueTraits, bool IsConst>
class hashtable_iterator
{
   typedef typename BucketValueTraits::value_traits            value_traits;
   typedef typename BucketValueTraits::bucket_traits           bucket_traits;

   typedef iiterator< value_traits, IsConst
                    , std::forward_iterator_tag>   types_t;
   public:
   typedef typename types_t::iterator_type::difference_type    difference_type;
   typedef typename types_t::iterator_type::value_type         value_type;
   typedef typename types_t::iterator_type::pointer            pointer;
   typedef typename types_t::iterator_type::reference          reference;
   typedef typename types_t::iterator_type::iterator_category  iterator_category;

   private:
   typedef typename value_traits::node_traits                  node_traits;
   typedef typename node_traits::node_ptr                      node_ptr;
   typedef typename get_slist_impl
      < typename reduced_slist_node_traits
         <node_traits>::type >::type                           slist_impl;
   typedef typename slist_impl::iterator                       siterator;
   typedef typename slist_impl::const_iterator                 const_siterator;
   typedef bucket_impl<slist_impl>                             bucket_type;

   typedef typename pointer_traits
      <pointer>::template rebind_pointer
         < const BucketValueTraits >::type                     const_bucketvaltraits_ptr;
   typedef typename slist_impl::size_type                      size_type;
   class nat;
   typedef typename
      detail::if_c< IsConst
                  , hashtable_iterator<BucketValueTraits, false>
                  , nat>::type                                 nonconst_iterator;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr downcast_bucket(typename bucket_type::node_ptr p)
   {
      return pointer_traits<node_ptr>::
         pointer_to(static_cast<typename node_traits::node&>(*p));
   }

   public:

   BOOST_INTRUSIVE_FORCEINLINE hashtable_iterator ()
      : slist_it_()  //Value initialization to achieve "null iterators" (N3644)
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit hashtable_iterator(siterator ptr, const BucketValueTraits *cont)
      : slist_it_ (ptr)
      , traitsptr_ (cont ? pointer_traits<const_bucketvaltraits_ptr>::pointer_to(*cont) : const_bucketvaltraits_ptr() )
   {}

   BOOST_INTRUSIVE_FORCEINLINE hashtable_iterator(const hashtable_iterator &other)
      :  slist_it_(other.slist_it()), traitsptr_(other.get_bucket_value_traits())
   {}

   BOOST_INTRUSIVE_FORCEINLINE hashtable_iterator(const nonconst_iterator &other)
      :  slist_it_(other.slist_it()), traitsptr_(other.get_bucket_value_traits())
   {}

   BOOST_INTRUSIVE_FORCEINLINE const siterator &slist_it() const
   { return slist_it_; }

   BOOST_INTRUSIVE_FORCEINLINE hashtable_iterator<BucketValueTraits, false> unconst() const
   {  return hashtable_iterator<BucketValueTraits, false>(this->slist_it(), this->get_bucket_value_traits());   }

   BOOST_INTRUSIVE_FORCEINLINE hashtable_iterator& operator++()
   {  this->increment();   return *this;   }

   BOOST_INTRUSIVE_FORCEINLINE hashtable_iterator &operator=(const hashtable_iterator &other)
   {  slist_it_ = other.slist_it(); traitsptr_ = other.get_bucket_value_traits();   return *this;  }

   BOOST_INTRUSIVE_FORCEINLINE hashtable_iterator operator++(int)
   {
      hashtable_iterator result (*this);
      this->increment();
      return result;
   }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator== (const hashtable_iterator& i, const hashtable_iterator& i2)
   { return i.slist_it_ == i2.slist_it_; }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator!= (const hashtable_iterator& i, const hashtable_iterator& i2)
   { return !(i == i2); }

   BOOST_INTRUSIVE_FORCEINLINE reference operator*() const
   { return *this->operator ->(); }

   BOOST_INTRUSIVE_FORCEINLINE pointer operator->() const
   {
      return this->priv_value_traits().to_value_ptr
         (downcast_bucket(slist_it_.pointed_node()));
   }

   BOOST_INTRUSIVE_FORCEINLINE const const_bucketvaltraits_ptr &get_bucket_value_traits() const
   {  return traitsptr_;  }

   BOOST_INTRUSIVE_FORCEINLINE const value_traits &priv_value_traits() const
   {  return traitsptr_->priv_value_traits();  }

   BOOST_INTRUSIVE_FORCEINLINE const bucket_traits &priv_bucket_traits() const
   {  return traitsptr_->priv_bucket_traits();  }

   private:
   void increment()
   {
      const bucket_traits &rbuck_traits = this->priv_bucket_traits();
      bucket_type* const buckets = boost::movelib::to_raw_pointer(rbuck_traits.bucket_begin());
      const size_type buckets_len = rbuck_traits.bucket_count();

      ++slist_it_;
      const typename slist_impl::node_ptr n = slist_it_.pointed_node();
      const siterator first_bucket_bbegin = buckets->end();
      if(first_bucket_bbegin.pointed_node() <= n && n <= buckets[buckets_len-1].cend().pointed_node()){
         //If one-past the node is inside the bucket then look for the next non-empty bucket
         //1. get the bucket_impl from the iterator
         const bucket_type &b = static_cast<const bucket_type&>
            (bucket_type::slist_type::container_from_end_iterator(slist_it_));

         //2. Now just calculate the index b has in the bucket array
         size_type n_bucket = static_cast<size_type>(&b - buckets);

         //3. Iterate until a non-empty bucket is found
         do{
            if (++n_bucket >= buckets_len){  //bucket overflow, return end() iterator
               slist_it_ = buckets->before_begin();
               return;
            }
         }
         while (buckets[n_bucket].empty());
         slist_it_ = buckets[n_bucket].begin();
      }
      else{
         //++slist_it_ yield to a valid object
      }
   }

   siterator                  slist_it_;
   const_bucketvaltraits_ptr  traitsptr_;
};

}  //namespace intrusive {
}  //namespace boost {

#endif

/* hashtable_node.hpp
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
*/