////////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_FLAT_TREE_HPP
#define BOOST_CONTAINER_FLAT_TREE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#include <boost/container/container_fwd.hpp>

#include <boost/move/utility_core.hpp>

#include <boost/container/detail/pair.hpp>
#include <boost/container/vector.hpp>
#include <boost/container/allocator_traits.hpp>

#include <boost/container/detail/value_init.hpp>
#include <boost/container/detail/destroyers.hpp>
#include <boost/container/detail/algorithm.hpp> //algo_equal(), algo_lexicographical_compare
#include <boost/container/detail/iterator.hpp>
#include <boost/container/detail/is_sorted.hpp>
#include <boost/container/detail/type_traits.hpp>
#include <boost/container/detail/iterators.hpp>
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/is_contiguous_container.hpp>
#include <boost/container/detail/is_container.hpp>

#include <boost/intrusive/detail/minimal_pair_header.hpp>      //pair

#include <boost/move/make_unique.hpp>
#include <boost/move/iterator.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <boost/move/algo/adaptive_sort.hpp>
#include <boost/move/algo/detail/pdqsort.hpp>

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#endif

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//merge_unique
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME merge_unique
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG namespace boost { namespace container { namespace dtl {
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END   }}}
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN 3
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX 3
#include <boost/intrusive/detail/has_member_function_callable_with.hpp>

//merge_equal
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME merge
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG namespace boost { namespace container { namespace dtl {
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END   }}}
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN 3
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX 3
#include <boost/intrusive/detail/has_member_function_callable_with.hpp>

//index_of
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME index_of
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG namespace boost { namespace container { namespace dtl {
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END   }}}
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN 1
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX 1
#include <boost/intrusive/detail/has_member_function_callable_with.hpp>

//nth
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME nth
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG namespace boost { namespace container { namespace dtl {
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END   }}}
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN 1
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX 1
#include <boost/intrusive/detail/has_member_function_callable_with.hpp>

//reserve
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME reserve
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG namespace boost { namespace container { namespace dtl {
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END   }}}
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN 1
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX 1
#include <boost/intrusive/detail/has_member_function_callable_with.hpp>

//capacity
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME capacity
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG namespace boost { namespace container { namespace dtl {
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END   }}}
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN 0
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX 0
#include <boost/intrusive/detail/has_member_function_callable_with.hpp>

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

namespace boost {
namespace container {
namespace dtl {

///////////////////////////////////////
//
// Helper functions to merge elements
//
///////////////////////////////////////

BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(stored_allocator_type)

///////////////////////////////////////
//
//  flat_tree_container_inplace_merge
//
///////////////////////////////////////
template<class SequenceContainer, class Compare>
void flat_tree_container_inplace_merge //is_contiguous_container == true
   (SequenceContainer& dest, typename SequenceContainer::iterator it, Compare comp , dtl::true_)
{
   typedef typename SequenceContainer::value_type  value_type;
   value_type *const braw = boost::movelib::iterator_to_raw_pointer(dest.begin());
   value_type *const iraw = boost::movelib::iterator_to_raw_pointer(it);
   value_type *const eraw = boost::movelib::iterator_to_raw_pointer(dest.end());
   boost::movelib::adaptive_merge(braw, iraw, eraw, comp, eraw, dest.capacity()- dest.size());
}

template<class SequenceContainer, class Compare>
void flat_tree_container_inplace_merge //is_contiguous_container == false
   (SequenceContainer& dest, typename SequenceContainer::iterator it, Compare comp, dtl::false_)
{
   boost::movelib::adaptive_merge(dest.begin(), it, dest.end(), comp);
}

///////////////////////////////////////
//
//  flat_tree_container_inplace_sort_ending
//
///////////////////////////////////////
template<class SequenceContainer, class Compare>
void flat_tree_container_inplace_sort_ending //is_contiguous_container == true
   (SequenceContainer& dest, typename SequenceContainer::iterator it, Compare comp, dtl::true_)
{
   typedef typename SequenceContainer::value_type  value_type;
   value_type *const iraw = boost::movelib::iterator_to_raw_pointer(it);
   value_type *const eraw = boost::movelib::iterator_to_raw_pointer(dest.end());
   boost::movelib::adaptive_sort(iraw, eraw, comp, eraw, dest.capacity()- dest.size());
}

template<class SequenceContainer, class Compare>
void flat_tree_container_inplace_sort_ending //is_contiguous_container == false
   (SequenceContainer& dest, typename SequenceContainer::iterator it, Compare comp , dtl::false_)
{
   boost::movelib::adaptive_sort(it, dest.end(), comp);
}

///////////////////////////////////////
//
//          flat_tree_merge
//
///////////////////////////////////////
template<class SequenceContainer, class Iterator, class Compare>
BOOST_CONTAINER_FORCEINLINE void flat_tree_merge_equal
   (SequenceContainer& dest, Iterator first, Iterator last, Compare comp, dtl::true_)
{
   dest.merge(first, last, comp);
}

template<class SequenceContainer, class Iterator, class Compare>
BOOST_CONTAINER_FORCEINLINE void flat_tree_merge_equal   //has_merge_unique == false
   (SequenceContainer& dest, Iterator first, Iterator last, Compare comp, dtl::false_)
{
   typedef typename SequenceContainer::iterator    iterator;
   iterator const it = dest.insert( dest.end(), first, last );
   dtl::bool_<is_contiguous_container<SequenceContainer>::value> contiguous_tag;
   (flat_tree_container_inplace_merge)(dest, it, comp, contiguous_tag);
}

///////////////////////////////////////
//
//       flat_tree_merge_unique
//
///////////////////////////////////////
template<class SequenceContainer, class Iterator, class Compare>
BOOST_CONTAINER_FORCEINLINE void flat_tree_merge_unique  //has_merge_unique == true
   (SequenceContainer& dest, Iterator first, Iterator last, Compare comp, dtl::true_)
{
   dest.merge_unique(first, last, comp);
}

template<class SequenceContainer, class Iterator, class Compare>
BOOST_CONTAINER_FORCEINLINE void flat_tree_merge_unique  //has_merge_unique == false
   (SequenceContainer& dest, Iterator first, Iterator last, Compare comp, dtl::false_)
{
   typedef typename SequenceContainer::iterator    iterator;
   typedef typename SequenceContainer::size_type   size_type;

   size_type const old_sz = dest.size();
   iterator const first_new = dest.insert(dest.cend(), first, last );
   iterator e = boost::movelib::inplace_set_unique_difference(first_new, dest.end(), dest.begin(), first_new, comp);
   dest.erase(e, dest.end());
   dtl::bool_<is_contiguous_container<SequenceContainer>::value> contiguous_tag;
   (flat_tree_container_inplace_merge)(dest, dest.begin()+old_sz, comp, contiguous_tag);
}

///////////////////////////////////////
//
//         flat_tree_index_of
//
///////////////////////////////////////
template<class SequenceContainer, class Iterator>
BOOST_CONTAINER_FORCEINLINE typename SequenceContainer::size_type
   flat_tree_index_of   // has_index_of == true
      (SequenceContainer& cont, Iterator p, dtl::true_)
{
   return cont.index_of(p);
}

template<class SequenceContainer, class Iterator>
BOOST_CONTAINER_FORCEINLINE typename SequenceContainer::size_type
   flat_tree_index_of   // has_index_of == false
      (SequenceContainer& cont, Iterator p, dtl::false_)
{
   typedef typename SequenceContainer::size_type size_type;
   return static_cast<size_type>(p - cont.begin());
}

///////////////////////////////////////
//
//         flat_tree_nth
//
///////////////////////////////////////
template<class Iterator, class SequenceContainer>
BOOST_CONTAINER_FORCEINLINE Iterator
   flat_tree_nth  // has_nth == true
      (SequenceContainer& cont, typename SequenceContainer::size_type n, dtl::true_)
{
   return cont.nth(n);
}

template<class Iterator, class SequenceContainer>
BOOST_CONTAINER_FORCEINLINE Iterator
   flat_tree_nth  // has_nth == false
      (SequenceContainer& cont, typename SequenceContainer::size_type n, dtl::false_)
{
   return cont.begin()+ n;
}

///////////////////////////////////////
//
//    flat_tree_get_stored_allocator
//
///////////////////////////////////////
template<class SequenceContainer>
BOOST_CONTAINER_FORCEINLINE typename SequenceContainer::stored_allocator_type &
   flat_tree_get_stored_allocator   // has_get_stored_allocator == true
      (SequenceContainer& cont, dtl::true_)
{
   return cont.get_stored_allocator();
}

template<class SequenceContainer>
BOOST_CONTAINER_FORCEINLINE const typename SequenceContainer::stored_allocator_type &
   flat_tree_get_stored_allocator   // has_get_stored_allocator == true
      (const SequenceContainer& cont, dtl::true_)
{
   return cont.get_stored_allocator();
}

template<class SequenceContainer>
BOOST_CONTAINER_FORCEINLINE typename SequenceContainer::allocator_type
   flat_tree_get_stored_allocator   // has_get_stored_allocator == false
      (SequenceContainer& cont, dtl::false_)
{
   return cont.get_allocator();
}

///////////////////////////////////////
//
//    flat_tree_adopt_sequence_equal
//
///////////////////////////////////////
template<class SequenceContainer, class Compare>
void flat_tree_sort_contiguous_to_adopt // is_contiguous_container == true
   (SequenceContainer &tseq, BOOST_RV_REF(SequenceContainer) seq, Compare comp)
{
   if(tseq.capacity() >= (seq.capacity() - seq.size())) {
      tseq.clear();
      boost::movelib::adaptive_sort
      (boost::movelib::iterator_to_raw_pointer(seq.begin())
         , boost::movelib::iterator_to_raw_pointer(seq.end())
         , comp
         , boost::movelib::iterator_to_raw_pointer(tseq.begin())
         , tseq.capacity());
   }
   else{
      boost::movelib::adaptive_sort
      (boost::movelib::iterator_to_raw_pointer(seq.begin())
         , boost::movelib::iterator_to_raw_pointer(seq.end())
         , comp
         , boost::movelib::iterator_to_raw_pointer(seq.end())
         , seq.capacity() - seq.size());
   }
}

template<class SequenceContainer, class Compare>
void flat_tree_adopt_sequence_equal // is_contiguous_container == true
   (SequenceContainer &tseq, BOOST_RV_REF(SequenceContainer) seq, Compare comp, dtl::true_)
{
   flat_tree_sort_contiguous_to_adopt(tseq, boost::move(seq), comp);
   tseq = boost::move(seq);
}

template<class SequenceContainer, class Compare>
void flat_tree_adopt_sequence_equal // is_contiguous_container == false
   (SequenceContainer &tseq, BOOST_RV_REF(SequenceContainer) seq, Compare comp, dtl::false_)
{
   boost::movelib::adaptive_sort(seq.begin(), seq.end(), comp);
   tseq = boost::move(seq);
}

///////////////////////////////////////
//
//    flat_tree_adopt_sequence_unique
//
///////////////////////////////////////
template<class SequenceContainer, class Compare>
void flat_tree_adopt_sequence_unique// is_contiguous_container == true
   (SequenceContainer &tseq, BOOST_RV_REF(SequenceContainer) seq, Compare comp, dtl::true_)
{
   boost::movelib::pdqsort
      ( boost::movelib::iterator_to_raw_pointer(seq.begin())
      , boost::movelib::iterator_to_raw_pointer(seq.end())
      , comp);
   seq.erase(boost::movelib::unique
      (seq.begin(), seq.end(), boost::movelib::negate<Compare>(comp)), seq.cend());
   tseq = boost::move(seq);
}

template<class SequenceContainer, class Compare>
void flat_tree_adopt_sequence_unique// is_contiguous_container == false
   (SequenceContainer &tseq, BOOST_RV_REF(SequenceContainer) seq, Compare comp, dtl::false_)
{
   boost::movelib::pdqsort(seq.begin(), seq.end(), comp);
   seq.erase(boost::movelib::unique
      (seq.begin(), seq.end(), boost::movelib::negate<Compare>(comp)), seq.cend());
   tseq = boost::move(seq);
}

///////////////////////////////////////
//
//       flat_tree_reserve
//
///////////////////////////////////////
template<class SequenceContainer>
BOOST_CONTAINER_FORCEINLINE void // has_reserve == true
   flat_tree_reserve(SequenceContainer &tseq, typename SequenceContainer::size_type cap, dtl::true_)
{
   tseq.reserve(cap);
}

template<class SequenceContainer>
BOOST_CONTAINER_FORCEINLINE void // has_reserve == false
   flat_tree_reserve(SequenceContainer &, typename SequenceContainer::size_type, dtl::false_)
{
}

///////////////////////////////////////
//
//       flat_tree_capacity
//
///////////////////////////////////////
template<class SequenceContainer>   // has_capacity == true
BOOST_CONTAINER_FORCEINLINE typename SequenceContainer::size_type
   flat_tree_capacity(const SequenceContainer &tseq, dtl::true_)
{
   return tseq.capacity();
}

template<class SequenceContainer>   // has_capacity == false
BOOST_CONTAINER_FORCEINLINE typename SequenceContainer::size_type
   flat_tree_capacity(const SequenceContainer &tseq, dtl::false_)
{
   return tseq.size();
}

///////////////////////////////////////
//
//       flat_tree_value_compare
//
///////////////////////////////////////

template<class Compare, class Value, class KeyOfValue>
class flat_tree_value_compare
   : private Compare
{
   typedef Value              first_argument_type;
   typedef Value              second_argument_type;
   typedef bool               return_type;
   public:
   flat_tree_value_compare()
      : Compare()
   {}

   flat_tree_value_compare(const Compare &pred)
      : Compare(pred)
   {}

   bool operator()(const Value& lhs, const Value& rhs) const
   {
      KeyOfValue key_extract;
      return Compare::operator()(key_extract(lhs), key_extract(rhs));
   }

   const Compare &get_comp() const
      {  return *this;  }

   Compare &get_comp()
      {  return *this;  }
};


///////////////////////////////////////
//
//       select_container_type
//
///////////////////////////////////////
template < class Value, class AllocatorOrContainer
         , bool = boost::container::dtl::is_container<AllocatorOrContainer>::value
         >
struct select_container_type
{
   typedef AllocatorOrContainer type;
};

template <class Value, class AllocatorOrContainer>
struct select_container_type<Value, AllocatorOrContainer, false>
{
   typedef boost::container::vector<Value, typename real_allocator<Value, AllocatorOrContainer>::type> type;
};


///////////////////////////////////////
//
//          flat_tree
//
///////////////////////////////////////
template <class Value, class KeyOfValue,
          class Compare, class AllocatorOrContainer>
class flat_tree
{
   public:
   typedef typename select_container_type<Value, AllocatorOrContainer>::type container_type;
   typedef container_type sequence_type;  //For backwards compatibility

   private:
   typedef typename container_type::allocator_type        allocator_t;
   typedef allocator_traits<allocator_t>                 allocator_traits_type;

   public:
   typedef flat_tree_value_compare<Compare, Value, KeyOfValue> value_compare;

   private:
   
   struct Data
      //Inherit from value_compare to do EBO
      : public value_compare
   {
      BOOST_COPYABLE_AND_MOVABLE(Data)

      public:
      Data()
         : value_compare(), m_seq()
      {}

      explicit Data(const allocator_t &alloc)
         : value_compare(), m_seq(alloc)
      {}

      explicit Data(const Compare &comp)
         : value_compare(comp), m_seq()
      {}

      Data(const Compare &comp, const allocator_t &alloc)
         : value_compare(comp), m_seq(alloc)
      {}

      explicit Data(const Data &d)
         : value_compare(static_cast<const value_compare&>(d)), m_seq(d.m_seq)
      {}

      Data(BOOST_RV_REF(Data) d)
         : value_compare(boost::move(static_cast<value_compare&>(d))), m_seq(boost::move(d.m_seq))
      {}

      Data(const Data &d, const allocator_t &a)
         : value_compare(static_cast<const value_compare&>(d)), m_seq(d.m_seq, a)
      {}

      Data(BOOST_RV_REF(Data) d, const allocator_t &a)
         : value_compare(boost::move(static_cast<value_compare&>(d))), m_seq(boost::move(d.m_seq), a)
      {}

      Data& operator=(BOOST_COPY_ASSIGN_REF(Data) d)
      {
         this->value_compare::operator=(d);
         m_seq = d.m_seq;
         return *this;
      }

      Data& operator=(BOOST_RV_REF(Data) d)
      {
         this->value_compare::operator=(boost::move(static_cast<value_compare &>(d)));
         m_seq = boost::move(d.m_seq);
         return *this;
      }

      void swap(Data &d)
      {
         value_compare& mycomp    = *this, & othercomp = d;
         boost::adl_move_swap(mycomp, othercomp);
         this->m_seq.swap(d.m_seq);
      }

      container_type m_seq;
   };

   Data m_data;
   BOOST_COPYABLE_AND_MOVABLE(flat_tree)

   public:

   typedef typename container_type::value_type               value_type;
   typedef typename container_type::pointer                  pointer;
   typedef typename container_type::const_pointer            const_pointer;
   typedef typename container_type::reference                reference;
   typedef typename container_type::const_reference          const_reference;
   typedef typename KeyOfValue::type                        key_type;
   typedef Compare                                          key_compare;
   typedef typename container_type::allocator_type           allocator_type;
   typedef typename container_type::size_type                size_type;
   typedef typename container_type::difference_type          difference_type;
   typedef typename container_type::iterator                 iterator;
   typedef typename container_type::const_iterator           const_iterator;
   typedef typename container_type::reverse_iterator         reverse_iterator;
   typedef typename container_type::const_reverse_iterator   const_reverse_iterator;

   //!Standard extension
   typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT
      (boost::container::dtl::, container_type
      ,stored_allocator_type, allocator_type)               stored_allocator_type;

   static const bool has_stored_allocator_type =
      BOOST_INTRUSIVE_HAS_TYPE(boost::container::dtl::, container_type, stored_allocator_type);

   private:
   typedef allocator_traits<stored_allocator_type> stored_allocator_traits;

   public:
   typedef typename dtl::if_c
      <has_stored_allocator_type, const stored_allocator_type &, allocator_type>::type get_stored_allocator_const_return_t;

   typedef typename dtl::if_c
      <has_stored_allocator_type, stored_allocator_type &, allocator_type>::type get_stored_allocator_noconst_return_t;

   BOOST_CONTAINER_FORCEINLINE flat_tree()
      : m_data()
   { }

   BOOST_CONTAINER_FORCEINLINE explicit flat_tree(const Compare& comp)
      : m_data(comp)
   { }

   BOOST_CONTAINER_FORCEINLINE explicit flat_tree(const allocator_type& a)
      : m_data(a)
   { }

   BOOST_CONTAINER_FORCEINLINE flat_tree(const Compare& comp, const allocator_type& a)
      : m_data(comp, a)
   { }

   BOOST_CONTAINER_FORCEINLINE flat_tree(const flat_tree& x)
      :  m_data(x.m_data)
   { }

   BOOST_CONTAINER_FORCEINLINE flat_tree(BOOST_RV_REF(flat_tree) x)
      BOOST_NOEXCEPT_IF(boost::container::dtl::is_nothrow_move_constructible<Compare>::value)
      :  m_data(boost::move(x.m_data))
   { }

   BOOST_CONTAINER_FORCEINLINE flat_tree(const flat_tree& x, const allocator_type &a)
      :  m_data(x.m_data, a)
   { }

   BOOST_CONTAINER_FORCEINLINE flat_tree(BOOST_RV_REF(flat_tree) x, const allocator_type &a)
      :  m_data(boost::move(x.m_data), a)
   { }

   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_tree( ordered_range_t, InputIterator first, InputIterator last)
      : m_data()
   {
      this->m_data.m_seq.insert(this->m_data.m_seq.end(), first, last);
      BOOST_ASSERT((is_sorted)(this->m_data.m_seq.cbegin(), this->m_data.m_seq.cend(), this->priv_value_comp()));
   }

   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_tree( ordered_range_t, InputIterator first, InputIterator last, const Compare& comp)
      : m_data(comp)
   {
      this->m_data.m_seq.insert(this->m_data.m_seq.end(), first, last);
      BOOST_ASSERT((is_sorted)(this->m_data.m_seq.cbegin(), this->m_data.m_seq.cend(), this->priv_value_comp()));
   }

   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_tree( ordered_range_t, InputIterator first, InputIterator last, const Compare& comp, const allocator_type& a)
      : m_data(comp, a)
   {
      this->m_data.m_seq.insert(this->m_data.m_seq.end(), first, last);
      BOOST_ASSERT((is_sorted)(this->m_data.m_seq.cbegin(), this->m_data.m_seq.cend(), this->priv_value_comp()));
   }

   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_tree( ordered_unique_range_t, InputIterator first, InputIterator last)
      : m_data()
   {
      this->m_data.m_seq.insert(this->m_data.m_seq.end(), first, last);
      BOOST_ASSERT((is_sorted_and_unique)(this->m_data.m_seq.cbegin(), this->m_data.m_seq.cend(), this->priv_value_comp()));
   }

   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_tree( ordered_unique_range_t, InputIterator first, InputIterator last, const Compare& comp)
      : m_data(comp)
   {
      this->m_data.m_seq.insert(this->m_data.m_seq.end(), first, last);
      BOOST_ASSERT((is_sorted_and_unique)(this->m_data.m_seq.cbegin(), this->m_data.m_seq.cend(), this->priv_value_comp()));
   }

   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_tree( ordered_unique_range_t, InputIterator first, InputIterator last, const Compare& comp, const allocator_type& a)
      : m_data(comp, a)
   {
      this->m_data.m_seq.insert(this->m_data.m_seq.end(), first, last);
      BOOST_ASSERT((is_sorted_and_unique)(this->m_data.m_seq.cbegin(), this->m_data.m_seq.cend(), this->priv_value_comp()));
   }

   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_tree( bool unique_insertion, InputIterator first, InputIterator last)
      : m_data()
   {
      this->priv_range_insertion_construct(unique_insertion, first, last);
   }

   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_tree( bool unique_insertion, InputIterator first, InputIterator last
            , const Compare& comp)
      : m_data(comp)
   {
      this->priv_range_insertion_construct(unique_insertion, first, last);
   }

   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_tree( bool unique_insertion, InputIterator first, InputIterator last
            , const allocator_type& a)
      : m_data(a)
   {
      this->priv_range_insertion_construct(unique_insertion, first, last);
   }

   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_tree( bool unique_insertion, InputIterator first, InputIterator last
            , const Compare& comp, const allocator_type& a)
      : m_data(comp, a)
   {
      this->priv_range_insertion_construct(unique_insertion, first, last);
   }

   BOOST_CONTAINER_FORCEINLINE ~flat_tree()
   {}

   BOOST_CONTAINER_FORCEINLINE flat_tree&  operator=(BOOST_COPY_ASSIGN_REF(flat_tree) x)
   {  m_data = x.m_data;   return *this;  }

   BOOST_CONTAINER_FORCEINLINE flat_tree&  operator=(BOOST_RV_REF(flat_tree) x)
      BOOST_NOEXCEPT_IF( (allocator_traits_type::propagate_on_container_move_assignment::value ||
                          allocator_traits_type::is_always_equal::value) &&
                           boost::container::dtl::is_nothrow_move_assignable<Compare>::value)
   {  m_data = boost::move(x.m_data); return *this;  }

   BOOST_CONTAINER_FORCEINLINE const value_compare &priv_value_comp() const
   { return static_cast<const value_compare &>(this->m_data); }

   BOOST_CONTAINER_FORCEINLINE value_compare &priv_value_comp()
   { return static_cast<value_compare &>(this->m_data); }

   BOOST_CONTAINER_FORCEINLINE const key_compare &priv_key_comp() const
   { return this->priv_value_comp().get_comp(); }

   BOOST_CONTAINER_FORCEINLINE key_compare &priv_key_comp()
   { return this->priv_value_comp().get_comp(); }

   struct insert_commit_data
   {
      const_iterator position;
   };

   public:
   // accessors:
   BOOST_CONTAINER_FORCEINLINE Compare key_comp() const
   { return this->m_data.get_comp(); }

   BOOST_CONTAINER_FORCEINLINE value_compare value_comp() const
   { return this->m_data; }

   BOOST_CONTAINER_FORCEINLINE allocator_type get_allocator() const
   { return this->m_data.m_seq.get_allocator(); }

   BOOST_CONTAINER_FORCEINLINE get_stored_allocator_const_return_t get_stored_allocator() const
   {
      return flat_tree_get_stored_allocator(this->m_data.m_seq, dtl::bool_<has_stored_allocator_type>());
   }

   BOOST_CONTAINER_FORCEINLINE get_stored_allocator_noconst_return_t get_stored_allocator()
   {
      return flat_tree_get_stored_allocator(this->m_data.m_seq, dtl::bool_<has_stored_allocator_type>());
   }

   BOOST_CONTAINER_FORCEINLINE iterator begin()
   { return this->m_data.m_seq.begin(); }

   BOOST_CONTAINER_FORCEINLINE const_iterator begin() const
   { return this->cbegin(); }

   BOOST_CONTAINER_FORCEINLINE const_iterator cbegin() const
   { return this->m_data.m_seq.begin(); }

   BOOST_CONTAINER_FORCEINLINE iterator end()
   { return this->m_data.m_seq.end(); }

   BOOST_CONTAINER_FORCEINLINE const_iterator end() const
   { return this->cend(); }

   BOOST_CONTAINER_FORCEINLINE const_iterator cend() const
   { return this->m_data.m_seq.end(); }

   BOOST_CONTAINER_FORCEINLINE reverse_iterator rbegin()
   { return reverse_iterator(this->end()); }

   BOOST_CONTAINER_FORCEINLINE const_reverse_iterator rbegin() const
   {  return this->crbegin();  }

   BOOST_CONTAINER_FORCEINLINE const_reverse_iterator crbegin() const
   {  return const_reverse_iterator(this->cend());  }

   BOOST_CONTAINER_FORCEINLINE reverse_iterator rend()
   { return reverse_iterator(this->begin()); }

   BOOST_CONTAINER_FORCEINLINE const_reverse_iterator rend() const
   { return this->crend(); }

   BOOST_CONTAINER_FORCEINLINE const_reverse_iterator crend() const
   { return const_reverse_iterator(this->cbegin()); }

   BOOST_CONTAINER_FORCEINLINE bool empty() const
   { return this->m_data.m_seq.empty(); }

   BOOST_CONTAINER_FORCEINLINE size_type size() const
   { return this->m_data.m_seq.size(); }

   BOOST_CONTAINER_FORCEINLINE size_type max_size() const
   { return this->m_data.m_seq.max_size(); }

   BOOST_CONTAINER_FORCEINLINE void swap(flat_tree& other)
      BOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && boost::container::dtl::is_nothrow_swappable<Compare>::value )
   {  this->m_data.swap(other.m_data);  }

   public:
   // insert/erase
   std::pair<iterator,bool> insert_unique(const value_type& val)
   {
      std::pair<iterator,bool> ret;
      insert_commit_data data;
      ret.second = this->priv_insert_unique_prepare(KeyOfValue()(val), data);
      ret.first = ret.second ? this->priv_insert_commit(data, val)
                             : this->begin() + (data.position - this->cbegin());
                             //: iterator(vector_iterator_get_ptr(data.position));
      return ret;
   }

   std::pair<iterator,bool> insert_unique(BOOST_RV_REF(value_type) val)
   {
      std::pair<iterator,bool> ret;
      insert_commit_data data;
      ret.second = this->priv_insert_unique_prepare(KeyOfValue()(val), data);
      ret.first = ret.second ? this->priv_insert_commit(data, boost::move(val))
                             : this->begin() + (data.position - this->cbegin());
                             //: iterator(vector_iterator_get_ptr(data.position));
      return ret;
   }

   iterator insert_equal(const value_type& val)
   {
      iterator i = this->upper_bound(KeyOfValue()(val));
      i = this->m_data.m_seq.insert(i, val);
      return i;
   }

   iterator insert_equal(BOOST_RV_REF(value_type) mval)
   {
      iterator i = this->upper_bound(KeyOfValue()(mval));
      i = this->m_data.m_seq.insert(i, boost::move(mval));
      return i;
   }

   iterator insert_unique(const_iterator hint, const value_type& val)
   {
      BOOST_ASSERT(this->priv_in_range_or_end(hint));
      insert_commit_data data;
      return this->priv_insert_unique_prepare(hint, KeyOfValue()(val), data)
            ? this->priv_insert_commit(data, val)
            : this->begin() + (data.position - this->cbegin());
            //: iterator(vector_iterator_get_ptr(data.position));
   }

   iterator insert_unique(const_iterator hint, BOOST_RV_REF(value_type) val)
   {
      BOOST_ASSERT(this->priv_in_range_or_end(hint));
      insert_commit_data data;
      return this->priv_insert_unique_prepare(hint, KeyOfValue()(val), data)
         ? this->priv_insert_commit(data, boost::move(val))
         : this->begin() + (data.position - this->cbegin());
         //: iterator(vector_iterator_get_ptr(data.position));
   }

   iterator insert_equal(const_iterator hint, const value_type& val)
   {
      BOOST_ASSERT(this->priv_in_range_or_end(hint));
      insert_commit_data data;
      this->priv_insert_equal_prepare(hint, val, data);
      return this->priv_insert_commit(data, val);
   }

   iterator insert_equal(const_iterator hint, BOOST_RV_REF(value_type) mval)
   {
      BOOST_ASSERT(this->priv_in_range_or_end(hint));
      insert_commit_data data;
      this->priv_insert_equal_prepare(hint, mval, data);
      return this->priv_insert_commit(data, boost::move(mval));
   }

   template <class InIt>
   void insert_unique(InIt first, InIt last)
   {
      dtl::bool_<is_contiguous_container<container_type>::value> contiguous_tag;
      container_type &seq = this->m_data.m_seq;
      value_compare &val_cmp = this->priv_value_comp();

      //Step 1: put new elements in the back
      typename container_type::iterator const it = seq.insert(seq.cend(), first, last);

      //Step 2: sort them
      boost::movelib::pdqsort(it, seq.end(), val_cmp);

      //Step 3: only left unique values from the back not already present in the original range
      typename container_type::iterator const e = boost::movelib::inplace_set_unique_difference
         (it, seq.end(), seq.begin(), it, val_cmp);

      seq.erase(e, seq.cend());
      //it might be invalidated by erasing [e, seq.end) if e == it
      if (it != e)
      {
         //Step 4: merge both ranges
         (flat_tree_container_inplace_merge)(seq, it, this->priv_value_comp(), contiguous_tag);
      }
   }

   template <class InIt>
   void insert_equal(InIt first, InIt last)
   {
      dtl::bool_<is_contiguous_container<container_type>::value> contiguous_tag;
      container_type &seq = this->m_data.m_seq;
      typename container_type::iterator const it = seq.insert(seq.cend(), first, last);
      (flat_tree_container_inplace_sort_ending)(seq, it, this->priv_value_comp(), contiguous_tag);
      (flat_tree_container_inplace_merge)      (seq, it, this->priv_value_comp(), contiguous_tag);
   }

   //Ordered

   template <class InIt>
   void insert_equal(ordered_range_t, InIt first, InIt last)
   {
      const bool value = boost::container::dtl::
         has_member_function_callable_with_merge_unique<container_type, InIt, InIt, value_compare>::value;
      (flat_tree_merge_equal)(this->m_data.m_seq, first, last, this->priv_value_comp(), dtl::bool_<value>());
   }

   template <class InIt>
   void insert_unique(ordered_unique_range_t, InIt first, InIt last)
   {
      const bool value = boost::container::dtl::
         has_member_function_callable_with_merge_unique<container_type, InIt, InIt, value_compare>::value;
      (flat_tree_merge_unique)(this->m_data.m_seq, first, last, this->priv_value_comp(), dtl::bool_<value>());
   }

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   template <class... Args>
   std::pair<iterator, bool> emplace_unique(BOOST_FWD_REF(Args)... args)
   {
      typename dtl::aligned_storage<sizeof(value_type), dtl::alignment_of<value_type>::value>::type v;
      value_type *pval = reinterpret_cast<value_type *>(v.data);
      get_stored_allocator_noconst_return_t a = this->get_stored_allocator();
      stored_allocator_traits::construct(a, pval, ::boost::forward<Args>(args)... );
      value_destructor<stored_allocator_type, value_type> d(a, *pval);
      return this->insert_unique(::boost::move(*pval));
   }

   template <class... Args>
   iterator emplace_hint_unique(const_iterator hint, BOOST_FWD_REF(Args)... args)
   {
      //hint checked in insert_unique
      typename dtl::aligned_storage<sizeof(value_type), dtl::alignment_of<value_type>::value>::type v;
      value_type *pval = reinterpret_cast<value_type *>(v.data);
      get_stored_allocator_noconst_return_t a = this->get_stored_allocator();
      stored_allocator_traits::construct(a, pval, ::boost::forward<Args>(args)... );
      value_destructor<stored_allocator_type, value_type> d(a, *pval);
      return this->insert_unique(hint, ::boost::move(*pval));
   }

   template <class... Args>
   iterator emplace_equal(BOOST_FWD_REF(Args)... args)
   {
      typename dtl::aligned_storage<sizeof(value_type), dtl::alignment_of<value_type>::value>::type v;
      value_type *pval = reinterpret_cast<value_type *>(v.data);
      get_stored_allocator_noconst_return_t a = this->get_stored_allocator();
      stored_allocator_traits::construct(a, pval, ::boost::forward<Args>(args)... );
      value_destructor<stored_allocator_type, value_type> d(a, *pval);
      return this->insert_equal(::boost::move(*pval));
   }

   template <class... Args>
   iterator emplace_hint_equal(const_iterator hint, BOOST_FWD_REF(Args)... args)
   {
      //hint checked in insert_equal
      typename dtl::aligned_storage<sizeof(value_type), dtl::alignment_of<value_type>::value>::type v;
      value_type *pval = reinterpret_cast<value_type *>(v.data);
      get_stored_allocator_noconst_return_t a = this->get_stored_allocator();
      stored_allocator_traits::construct(a, pval, ::boost::forward<Args>(args)... );
      value_destructor<stored_allocator_type, value_type> d(a, *pval);
      return this->insert_equal(hint, ::boost::move(*pval));
   }

   template <class KeyType, class... Args>
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, bool> try_emplace
      (const_iterator hint, BOOST_FWD_REF(KeyType) key, BOOST_FWD_REF(Args)... args)
   {
      std::pair<iterator,bool> ret;
      insert_commit_data data;
      const key_type & k = key;
      ret.second = hint == const_iterator()
         ? this->priv_insert_unique_prepare(k, data)
         : this->priv_insert_unique_prepare(hint, k, data);

      if(!ret.second){
         ret.first  = this->nth(data.position - this->cbegin());
      }
      else{
         typedef typename emplace_functor_type<try_emplace_t, KeyType, Args...>::type func_t;
         typedef emplace_iterator<value_type, func_t, difference_type> it_t;
         func_t func(try_emplace_t(), ::boost::forward<KeyType>(key), ::boost::forward<Args>(args)...);
         ret.first = this->m_data.m_seq.insert(data.position, it_t(func), it_t());
      }
      return ret;
   }

   #else // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #define BOOST_CONTAINER_FLAT_TREE_EMPLACE_CODE(N) \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   std::pair<iterator, bool> emplace_unique(BOOST_MOVE_UREF##N)\
   {\
      typename dtl::aligned_storage<sizeof(value_type), dtl::alignment_of<value_type>::value>::type v;\
      value_type *pval = reinterpret_cast<value_type *>(v.data);\
      get_stored_allocator_noconst_return_t a = this->get_stored_allocator();\
      stored_allocator_traits::construct(a, pval BOOST_MOVE_I##N BOOST_MOVE_FWD##N);\
      value_destructor<stored_allocator_type, value_type> d(a, *pval);\
      return this->insert_unique(::boost::move(*pval));\
   }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   iterator emplace_hint_unique(const_iterator hint BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {\
      typename dtl::aligned_storage<sizeof(value_type), dtl::alignment_of<value_type>::value>::type v;\
      value_type *pval = reinterpret_cast<value_type *>(v.data);\
      get_stored_allocator_noconst_return_t a = this->get_stored_allocator();\
      stored_allocator_traits::construct(a, pval BOOST_MOVE_I##N BOOST_MOVE_FWD##N);\
      value_destructor<stored_allocator_type, value_type> d(a, *pval);\
      return this->insert_unique(hint, ::boost::move(*pval));\
   }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   iterator emplace_equal(BOOST_MOVE_UREF##N)\
   {\
      typename dtl::aligned_storage<sizeof(value_type), dtl::alignment_of<value_type>::value>::type v;\
      value_type *pval = reinterpret_cast<value_type *>(v.data);\
      get_stored_allocator_noconst_return_t a = this->get_stored_allocator();\
      stored_allocator_traits::construct(a, pval BOOST_MOVE_I##N BOOST_MOVE_FWD##N);\
      value_destructor<stored_allocator_type, value_type> d(a, *pval);\
      return this->insert_equal(::boost::move(*pval));\
   }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   iterator emplace_hint_equal(const_iterator hint BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {\
      typename dtl::aligned_storage <sizeof(value_type), dtl::alignment_of<value_type>::value>::type v;\
      value_type *pval = reinterpret_cast<value_type *>(v.data);\
      get_stored_allocator_noconst_return_t a = this->get_stored_allocator();\
      stored_allocator_traits::construct(a, pval BOOST_MOVE_I##N BOOST_MOVE_FWD##N);\
      value_destructor<stored_allocator_type, value_type> d(a, *pval);\
      return this->insert_equal(hint, ::boost::move(*pval));\
   }\
   template <class KeyType BOOST_MOVE_I##N BOOST_MOVE_CLASS##N>\
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, bool>\
      try_emplace(const_iterator hint, BOOST_FWD_REF(KeyType) key BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {\
      std::pair<iterator,bool> ret;\
      insert_commit_data data;\
      const key_type & k = key;\
      ret.second = hint == const_iterator()\
         ? this->priv_insert_unique_prepare(k, data)\
         : this->priv_insert_unique_prepare(hint, k, data);\
      \
      if(!ret.second){\
         ret.first  = this->nth(data.position - this->cbegin());\
      }\
      else{\
         typedef typename emplace_functor_type<try_emplace_t, KeyType BOOST_MOVE_I##N BOOST_MOVE_TARG##N>::type func_t;\
         typedef emplace_iterator<value_type, func_t, difference_type> it_t;\
         func_t func(try_emplace_t(), ::boost::forward<KeyType>(key) BOOST_MOVE_I##N BOOST_MOVE_FWD##N);\
         ret.first = this->m_data.m_seq.insert(data.position, it_t(func), it_t());\
      }\
      return ret;\
   }\
   //
   BOOST_MOVE_ITERATE_0TO7(BOOST_CONTAINER_FLAT_TREE_EMPLACE_CODE)
   #undef BOOST_CONTAINER_FLAT_TREE_EMPLACE_CODE

   #endif   // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   template<class KeyType, class M>
   std::pair<iterator, bool> insert_or_assign(const_iterator hint, BOOST_FWD_REF(KeyType) key, BOOST_FWD_REF(M) obj)
   {
      const key_type& k = key;
      std::pair<iterator,bool> ret;
      insert_commit_data data;
      ret.second = hint == const_iterator()
         ? this->priv_insert_unique_prepare(k, data)
         : this->priv_insert_unique_prepare(hint, k, data);
      if(!ret.second){
         ret.first  = this->nth(data.position - this->cbegin());
         ret.first->second = boost::forward<M>(obj);
      }
      else{
         typedef typename emplace_functor_type<KeyType, M>::type func_t;
         typedef emplace_iterator<value_type, func_t, difference_type> it_t;
         func_t func(boost::forward<KeyType>(key), boost::forward<M>(obj));
         ret.first = this->m_data.m_seq.insert(data.position, it_t(func), it_t());
      }
      return ret;
   }

   BOOST_CONTAINER_FORCEINLINE iterator erase(const_iterator position)
   {  return this->m_data.m_seq.erase(position);  }

   size_type erase(const key_type& k)
   {
      std::pair<iterator,iterator > itp = this->equal_range(k);
      size_type ret = static_cast<size_type>(itp.second-itp.first);
      if (ret){
         this->m_data.m_seq.erase(itp.first, itp.second);
      }
      return ret;
   }

   BOOST_CONTAINER_FORCEINLINE iterator erase(const_iterator first, const_iterator last)
   {  return this->m_data.m_seq.erase(first, last);  }

   BOOST_CONTAINER_FORCEINLINE void clear()
   {  this->m_data.m_seq.clear();  }

   //! <b>Effects</b>: Tries to deallocate the excess of memory created
   //    with previous allocations. The size of the vector is unchanged
   //!
   //! <b>Throws</b>: If memory allocation throws, or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to size().
   BOOST_CONTAINER_FORCEINLINE void shrink_to_fit()
   {  this->m_data.m_seq.shrink_to_fit();  }

   BOOST_CONTAINER_FORCEINLINE iterator nth(size_type n) BOOST_NOEXCEPT_OR_NOTHROW
   {
      const bool value = boost::container::dtl::
         has_member_function_callable_with_nth<container_type, size_type>::value;
      return flat_tree_nth<iterator>(this->m_data.m_seq, n, dtl::bool_<value>());
   }

   BOOST_CONTAINER_FORCEINLINE const_iterator nth(size_type n) const BOOST_NOEXCEPT_OR_NOTHROW
   {
      const bool value = boost::container::dtl::
         has_member_function_callable_with_nth<container_type, size_type>::value;
      return flat_tree_nth<const_iterator>(this->m_data.m_seq, n, dtl::bool_<value>());
   }

   BOOST_CONTAINER_FORCEINLINE size_type index_of(iterator p) BOOST_NOEXCEPT_OR_NOTHROW
   {
      const bool value = boost::container::dtl::
         has_member_function_callable_with_index_of<container_type, iterator>::value;
      return flat_tree_index_of(this->m_data.m_seq, p, dtl::bool_<value>());
   }

   BOOST_CONTAINER_FORCEINLINE size_type index_of(const_iterator p) const BOOST_NOEXCEPT_OR_NOTHROW
   {
      const bool value = boost::container::dtl::
         has_member_function_callable_with_index_of<container_type, const_iterator>::value;
      return flat_tree_index_of(this->m_data.m_seq, p, dtl::bool_<value>());
   }

   // set operations:
   iterator find(const key_type& k)
   {
      iterator i = this->lower_bound(k);
      iterator end_it = this->end();
      if (i != end_it && this->m_data.get_comp()(k, KeyOfValue()(*i))){
         i = end_it;
      }
      return i;
   }

   const_iterator find(const key_type& k) const
   {
      const_iterator i = this->lower_bound(k);

      const_iterator end_it = this->cend();
      if (i != end_it && this->m_data.get_comp()(k, KeyOfValue()(*i))){
         i = end_it;
      }
      return i;
   }

   template<class K>
   typename dtl::enable_if_transparent<key_compare, K, iterator>::type
      find(const K& k)
   {
      iterator i = this->lower_bound(k);
      iterator end_it = this->end();
      if (i != end_it && this->m_data.get_comp()(k, KeyOfValue()(*i))){
         i = end_it;
      }
      return i;
   }

   template<class K>
   typename dtl::enable_if_transparent<key_compare, K, const_iterator>::type
      find(const K& k) const
   {
      const_iterator i = this->lower_bound(k);

      const_iterator end_it = this->cend();
      if (i != end_it && this->m_data.get_comp()(k, KeyOfValue()(*i))){
         i = end_it;
      }
      return i;
   }

   size_type count(const key_type& k) const
   {
      std::pair<const_iterator, const_iterator> p = this->equal_range(k);
      size_type n = p.second - p.first;
      return n;
   }

   template<class K>
   typename dtl::enable_if_transparent<key_compare, K, size_type>::type
      count(const K& k) const
   {
      std::pair<const_iterator, const_iterator> p = this->equal_range(k);
      size_type n = p.second - p.first;
      return n;
   }

   BOOST_CONTAINER_FORCEINLINE bool contains(const key_type& x) const
   {  return this->find(x) != this->cend();  }

   template<typename K>
   BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, bool>::type
         contains(const K& x) const
   {  return this->find(x) != this->cend();  }

   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge_unique(flat_tree<Value, KeyOfValue, C2, AllocatorOrContainer>& source)
   {
      this->insert_unique( boost::make_move_iterator(source.begin())
                         , boost::make_move_iterator(source.end()));
   }

   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge_equal(flat_tree<Value, KeyOfValue, C2, AllocatorOrContainer>& source)
   {
      this->insert_equal( boost::make_move_iterator(source.begin())
                        , boost::make_move_iterator(source.end()));
   }

   BOOST_CONTAINER_FORCEINLINE void merge_unique(flat_tree& source)
   {
      const bool value = boost::container::dtl::
         has_member_function_callable_with_merge_unique<container_type, iterator, iterator, value_compare>::value;
      (flat_tree_merge_unique)
         ( this->m_data.m_seq
         , boost::make_move_iterator(source.m_data.m_seq.begin())
         , boost::make_move_iterator(source.m_data.m_seq.end())
         , this->priv_value_comp()
         , dtl::bool_<value>());
   }

   BOOST_CONTAINER_FORCEINLINE void merge_equal(flat_tree& source)
   {
      const bool value = boost::container::dtl::
         has_member_function_callable_with_merge<container_type, iterator, iterator, value_compare>::value;
      (flat_tree_merge_equal)
         ( this->m_data.m_seq
         , boost::make_move_iterator(source.m_data.m_seq.begin())
         , boost::make_move_iterator(source.m_data.m_seq.end())
         , this->priv_value_comp()
         , dtl::bool_<value>());
   }

   BOOST_CONTAINER_FORCEINLINE iterator lower_bound(const key_type& k)
   {  return this->priv_lower_bound(this->begin(), this->end(), k);  }

   BOOST_CONTAINER_FORCEINLINE const_iterator lower_bound(const key_type& k) const
   {  return this->priv_lower_bound(this->cbegin(), this->cend(), k);  }

   template<class K>
   BOOST_CONTAINER_FORCEINLINE 
      typename dtl::enable_if_transparent<key_compare, K, iterator>::type
         lower_bound(const K& k)
   {  return this->priv_lower_bound(this->begin(), this->end(), k);  }

   template<class K>
   BOOST_CONTAINER_FORCEINLINE 
      typename dtl::enable_if_transparent<key_compare, K, const_iterator>::type
         lower_bound(const K& k) const
   {  return this->priv_lower_bound(this->cbegin(), this->cend(), k);  }

   BOOST_CONTAINER_FORCEINLINE iterator upper_bound(const key_type& k)
   {  return this->priv_upper_bound(this->begin(), this->end(), k);  }

   BOOST_CONTAINER_FORCEINLINE const_iterator upper_bound(const key_type& k) const
   {  return this->priv_upper_bound(this->cbegin(), this->cend(), k);  }

   template<class K>
   BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K,iterator>::type
   upper_bound(const K& k)
   {  return this->priv_upper_bound(this->begin(), this->end(), k);  }

   template<class K>
   BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K,const_iterator>::type
         upper_bound(const K& k) const
   {  return this->priv_upper_bound(this->cbegin(), this->cend(), k);  }

   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,iterator> equal_range(const key_type& k)
   {  return this->priv_equal_range(this->begin(), this->end(), k);  }

   BOOST_CONTAINER_FORCEINLINE std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
   {  return this->priv_equal_range(this->cbegin(), this->cend(), k);  }

   template<class K>
   BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K,std::pair<iterator,iterator> >::type
         equal_range(const K& k)
   {  return this->priv_equal_range(this->begin(), this->end(), k);  }

   template<class K>
   BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K,std::pair<const_iterator,const_iterator> >::type
         equal_range(const K& k) const
   {  return this->priv_equal_range(this->cbegin(), this->cend(), k);  }


   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, iterator> lower_bound_range(const key_type& k)
   {  return this->priv_lower_bound_range(this->begin(), this->end(), k);  }

   BOOST_CONTAINER_FORCEINLINE std::pair<const_iterator, const_iterator> lower_bound_range(const key_type& k) const
   {  return this->priv_lower_bound_range(this->cbegin(), this->cend(), k);  }

   template<class K>
   BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K,std::pair<iterator,iterator> >::type
         lower_bound_range(const K& k)
   {  return this->priv_lower_bound_range(this->begin(), this->end(), k);  }

   template<class K>
   BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K,std::pair<const_iterator,const_iterator> >::type
         lower_bound_range(const K& k) const
   {  return this->priv_lower_bound_range(this->cbegin(), this->cend(), k);  }

   BOOST_CONTAINER_FORCEINLINE size_type capacity() const
   {
      const bool value = boost::container::dtl::
         has_member_function_callable_with_capacity<container_type>::value;
      return (flat_tree_capacity)(this->m_data.m_seq, dtl::bool_<value>());
   }

   BOOST_CONTAINER_FORCEINLINE void reserve(size_type cnt)
   {
      const bool value = boost::container::dtl::
         has_member_function_callable_with_reserve<container_type, size_type>::value;
      (flat_tree_reserve)(this->m_data.m_seq, cnt, dtl::bool_<value>());
   }

   BOOST_CONTAINER_FORCEINLINE container_type extract_sequence()
   {
      return boost::move(m_data.m_seq);
   }

   BOOST_CONTAINER_FORCEINLINE container_type &get_sequence_ref()
   {
      return m_data.m_seq;
   }

   BOOST_CONTAINER_FORCEINLINE void adopt_sequence_equal(BOOST_RV_REF(container_type) seq)
   {
      (flat_tree_adopt_sequence_equal)( m_data.m_seq, boost::move(seq), this->priv_value_comp()
         , dtl::bool_<is_contiguous_container<container_type>::value>());
   }

   BOOST_CONTAINER_FORCEINLINE void adopt_sequence_unique(BOOST_RV_REF(container_type) seq)
   {
      (flat_tree_adopt_sequence_unique)(m_data.m_seq, boost::move(seq), this->priv_value_comp()
         , dtl::bool_<is_contiguous_container<container_type>::value>());
   }

   void adopt_sequence_equal(ordered_range_t, BOOST_RV_REF(container_type) seq)
   {
      BOOST_ASSERT((is_sorted)(seq.cbegin(), seq.cend(), this->priv_value_comp()));
      m_data.m_seq = boost::move(seq);
   }

   void adopt_sequence_unique(ordered_unique_range_t, BOOST_RV_REF(container_type) seq)
   {
      BOOST_ASSERT((is_sorted_and_unique)(seq.cbegin(), seq.cend(), this->priv_value_comp()));
      m_data.m_seq = boost::move(seq);
   }

   BOOST_CONTAINER_FORCEINLINE friend bool operator==(const flat_tree& x, const flat_tree& y)
   {
      return x.size() == y.size() && ::boost::container::algo_equal(x.begin(), x.end(), y.begin());
   }

   BOOST_CONTAINER_FORCEINLINE friend bool operator<(const flat_tree& x, const flat_tree& y)
   {
      return ::boost::container::algo_lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
   }

   BOOST_CONTAINER_FORCEINLINE friend bool operator!=(const flat_tree& x, const flat_tree& y)
      {  return !(x == y); }

   BOOST_CONTAINER_FORCEINLINE friend bool operator>(const flat_tree& x, const flat_tree& y)
      {  return y < x;  }

   BOOST_CONTAINER_FORCEINLINE friend bool operator<=(const flat_tree& x, const flat_tree& y)
      {  return !(y < x);  }

   BOOST_CONTAINER_FORCEINLINE friend bool operator>=(const flat_tree& x, const flat_tree& y)
      {  return !(x < y);  }

   BOOST_CONTAINER_FORCEINLINE friend void swap(flat_tree& x, flat_tree& y)
      {  x.swap(y);  }

   private:

   template <class InputIterator>
   void priv_range_insertion_construct( bool unique_insertion, InputIterator first, InputIterator last)
   {
      //Use cend() as hint to achieve linear time for
      //ordered ranges as required by the standard
      //for the constructor
      //Call end() every iteration as reallocation might have invalidated iterators
      if(unique_insertion){
         this->insert_unique(first, last);
      }
      else{
         this->insert_equal (first, last);
      }
   }

   BOOST_CONTAINER_FORCEINLINE bool priv_in_range_or_end(const_iterator pos) const
   {
      return (this->begin() <= pos) && (pos <= this->end());
   }

   // insert/erase
   void priv_insert_equal_prepare
      (const_iterator pos, const value_type& val, insert_commit_data &data)
   {
      // N1780
      //   To insert val at pos:
      //   if pos == end || val <= *pos
      //      if pos == begin || val >= *(pos-1)
      //         insert val before pos
      //      else
      //         insert val before upper_bound(val)
      //   else
      //      insert val before lower_bound(val)
      const value_compare &val_cmp = this->m_data;

      if(pos == this->cend() || !val_cmp(*pos, val)){
         if (pos == this->cbegin() || !val_cmp(val, pos[-1])){
            data.position = pos;
         }
         else{
            data.position =
               this->priv_upper_bound(this->cbegin(), pos, KeyOfValue()(val));
         }
      }
      else{
         data.position =
            this->priv_lower_bound(pos, this->cend(), KeyOfValue()(val));
      }
   }

   bool priv_insert_unique_prepare
      (const_iterator b, const_iterator e, const key_type& k, insert_commit_data &commit_data)
   {
      const key_compare &key_cmp  = this->priv_key_comp();
      commit_data.position = this->priv_lower_bound(b, e, k);
      return commit_data.position == e || key_cmp(k, KeyOfValue()(*commit_data.position));
   }

   BOOST_CONTAINER_FORCEINLINE bool priv_insert_unique_prepare
      (const key_type& k, insert_commit_data &commit_data)
   {  return this->priv_insert_unique_prepare(this->cbegin(), this->cend(), k, commit_data);   }

   bool priv_insert_unique_prepare
      (const_iterator pos, const key_type& k, insert_commit_data &commit_data)
   {
      //N1780. Props to Howard Hinnant!
      //To insert k at pos:
      //if pos == end || k <= *pos
      //   if pos == begin || k >= *(pos-1)
      //      insert k before pos
      //   else
      //      insert k before upper_bound(k)
      //else if pos+1 == end || k <= *(pos+1)
      //   insert k after pos
      //else
      //   insert k before lower_bound(k)
      const key_compare &key_cmp = this->priv_key_comp();
      const const_iterator cend_it = this->cend();
      if(pos == cend_it || key_cmp(k, KeyOfValue()(*pos))){ //Check if k should go before end
         const const_iterator cbeg = this->cbegin();
         commit_data.position = pos;
         if(pos == cbeg){  //If container is empty then insert it in the beginning
            return true;
         }
         const_iterator prev(pos);
         --prev;
         if(key_cmp(KeyOfValue()(*prev), k)){   //If previous element was less, then it should go between prev and pos
            return true;
         }
         else if(!key_cmp(k, KeyOfValue()(*prev))){   //If previous was equal then insertion should fail
            commit_data.position = prev;
            return false;
         }
         else{ //Previous was bigger so insertion hint was pointless, dispatch to hintless insertion
               //but reduce the search between beg and prev as prev is bigger than k
            return this->priv_insert_unique_prepare(cbeg, prev, k, commit_data);
         }
      }
      else{
         //The hint is before the insertion position, so insert it
         //in the remaining range [pos, end)
         return this->priv_insert_unique_prepare(pos, cend_it, k, commit_data);
      }
   }

   template<class Convertible>
   BOOST_CONTAINER_FORCEINLINE iterator priv_insert_commit
      (insert_commit_data &commit_data, BOOST_FWD_REF(Convertible) convertible)
   {
      return this->m_data.m_seq.insert
         ( commit_data.position
         , boost::forward<Convertible>(convertible));
   }

   template <class RanIt, class K>
   RanIt priv_lower_bound(RanIt first, const RanIt last,
                          const K & key) const
   {
      const Compare &key_cmp = this->m_data.get_comp();
      KeyOfValue key_extract;
      size_type len = static_cast<size_type>(last - first);
      RanIt middle;

      while (len) {
         size_type step = len >> 1;
         middle = first;
         middle += step;

         if (key_cmp(key_extract(*middle), key)) {
            first = ++middle;
            len -= step + 1;
         }
         else{
            len = step;
         }
      }
      return first;
   }

   template <class RanIt, class K>
   RanIt priv_upper_bound
      (RanIt first, const RanIt last,const K & key) const
   {
      const Compare &key_cmp = this->m_data.get_comp();
      KeyOfValue key_extract;
      size_type len = static_cast<size_type>(last - first);
      RanIt middle;

      while (len) {
         size_type step = len >> 1;
         middle = first;
         middle += step;

         if (key_cmp(key, key_extract(*middle))) {
            len = step;
         }
         else{
            first = ++middle;
            len -= step + 1;
         }
      }
      return first;
   }

   template <class RanIt, class K>
   std::pair<RanIt, RanIt>
      priv_equal_range(RanIt first, RanIt last, const K& key) const
   {
      const Compare &key_cmp = this->m_data.get_comp();
      KeyOfValue key_extract;
      size_type len = static_cast<size_type>(last - first);
      RanIt middle;

      while (len) {
         size_type step = len >> 1;
         middle = first;
         middle += step;

         if (key_cmp(key_extract(*middle), key)){
            first = ++middle;
            len -= step + 1;
         }
         else if (key_cmp(key, key_extract(*middle))){
            len = step;
         }
         else {
            //Middle is equal to key
            last = first;
            last += len;
            RanIt const first_ret = this->priv_lower_bound(first, middle, key);
            return std::pair<RanIt, RanIt>
               ( first_ret, this->priv_upper_bound(++middle, last, key));
         }
      }
      return std::pair<RanIt, RanIt>(first, first);
   }

   template<class RanIt, class K>
   std::pair<RanIt, RanIt> priv_lower_bound_range(RanIt first, RanIt last, const K& k) const
   {
      const Compare &key_cmp = this->m_data.get_comp();
      KeyOfValue key_extract;
      RanIt lb(this->priv_lower_bound(first, last, k)), ub(lb);
      if(lb != last && !key_cmp(k, key_extract(*lb))){
         ++ub;
      }
      return std::pair<RanIt, RanIt>(lb, ub);
   }
};

}  //namespace dtl {

}  //namespace container {

//!has_trivial_destructor_after_move<> == true_type
//!specialization for optimizations
template <class T, class KeyOfValue,
class Compare, class AllocatorOrContainer>
struct has_trivial_destructor_after_move<boost::container::dtl::flat_tree<T, KeyOfValue, Compare, AllocatorOrContainer> >
{
   typedef boost::container::dtl::flat_tree<T, KeyOfValue, Compare, AllocatorOrContainer> flat_tree;
   typedef typename flat_tree::container_type container_type;
   typedef typename flat_tree::key_compare key_compare;
   static const bool value = ::boost::has_trivial_destructor_after_move<container_type>::value &&
                             ::boost::has_trivial_destructor_after_move<key_compare>::value;
};

}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif // BOOST_CONTAINER_FLAT_TREE_HPP

/* flat_tree.hpp
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
*/