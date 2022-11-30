/* Copyright 2016-2020 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_SPLIT_SEGMENT_HPP
#define BOOST_POLY_COLLECTION_DETAIL_SPLIT_SEGMENT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/poly_collection/detail/segment_backend.hpp>
#include <boost/poly_collection/detail/value_holder.hpp>
#include <iterator>
#include <memory>
#include <new>
#include <utility>
#include <vector>

namespace boost{

namespace poly_collection{

namespace detail{

/* segment_backend implementation that maintains two internal vectors, one for
 * value_type's (the index) and another for the concrete elements those refer
 * to (the store).
 *
 * Requires:
 *   - [const_]base_iterator is constructible from value_type*.
 *   - value_type is copy constructible.
 *   - Model::make_value_type(x) returns a value_type created from a reference
 *     to the concrete type.
 *
 * Conversion from base_iterator to local_iterator<Concrete> requires accesing
 * value_type internal info, so the end() base_iterator has to be made to point
 * to a valid element of index, which implies size(index)=size(store)+1. This
 * slightly complicates the memory management.
 */

template<typename Model,typename Concrete,typename Allocator>
class split_segment:public segment_backend<Model,Allocator>
{
  using value_type=typename Model::value_type;
  using store_value_type=value_holder<Concrete>;
  using store=std::vector<
    store_value_type,
    typename std::allocator_traits<Allocator>::
      template rebind_alloc<store_value_type>
  >;
  using store_iterator=typename store::iterator;
  using const_store_iterator=typename store::const_iterator;
  using index=std::vector<
    value_type,
    typename std::allocator_traits<Allocator>::
      template rebind_alloc<value_type>
  >;
  using const_index_iterator=typename index::const_iterator;
  using segment_backend=detail::segment_backend<Model,Allocator>;
  using typename segment_backend::segment_backend_unique_ptr;
  using typename segment_backend::value_pointer;
  using typename segment_backend::const_value_pointer;
  using typename segment_backend::base_iterator;
  using typename segment_backend::const_base_iterator;
  using const_iterator=
    typename segment_backend::template const_iterator<Concrete>;
  using typename segment_backend::base_sentinel;
  using typename segment_backend::range;
  using segment_allocator_type=typename std::allocator_traits<Allocator>::
    template rebind_alloc<split_segment>;

public:
  virtual ~split_segment()=default;

  static segment_backend_unique_ptr make(const segment_allocator_type& al)
  {
    return new_(al,al);
  }

  virtual segment_backend_unique_ptr copy()const
  {
    return new_(s.get_allocator(),store{s});
  }

  virtual segment_backend_unique_ptr copy(const Allocator& al)const
  {
    return new_(al,store{s,al});
  }

  virtual segment_backend_unique_ptr empty_copy(const Allocator& al)const
  {
    return new_(al,al);
  }

  virtual segment_backend_unique_ptr move(const Allocator& al)
  {
    return new_(al,store{std::move(s),al});
  }

  virtual bool equal(const segment_backend& x)const
  {
    return s==static_cast<const split_segment&>(x).s;
  }

  virtual Allocator     get_allocator()const noexcept
                         {return s.get_allocator();}
  virtual base_iterator begin()const noexcept{return nv_begin();}
  base_iterator         nv_begin()const noexcept
                         {return base_iterator{value_ptr(i.data())};}
  virtual base_iterator end()const noexcept{return nv_end();}
  base_iterator         nv_end()const noexcept
                         {return base_iterator{value_ptr(i.data()+s.size())};}
  virtual bool          empty()const noexcept{return nv_empty();}
  bool                  nv_empty()const noexcept{return s.empty();}
  virtual std::size_t   size()const noexcept{return nv_size();}
  std::size_t           nv_size()const noexcept{return s.size();}
  virtual std::size_t   max_size()const noexcept{return nv_max_size();}
  std::size_t           nv_max_size()const noexcept{return s.max_size()-1;}
  virtual std::size_t   capacity()const noexcept{return nv_capacity();}
  std::size_t           nv_capacity()const noexcept{return s.capacity();}

  virtual base_sentinel reserve(std::size_t n){return nv_reserve(n);}

  base_sentinel nv_reserve(std::size_t n)
  {
    bool rebuild=n>s.capacity();
    i.reserve(n+1);
    s.reserve(n);
    if(rebuild)rebuild_index();
    return sentinel();
  };

  virtual base_sentinel shrink_to_fit(){return nv_shrink_to_fit();}

  base_sentinel nv_shrink_to_fit()
  {
    try{
      auto p=s.data();
      if(!s.empty())s.shrink_to_fit();
      else{
        store ss{s.get_allocator()};
        ss.reserve(1); /* --> s.data()!=nullptr */
        s.swap(ss);
      }
      if(p!=s.data()){
        index ii{{},i.get_allocator()};
        ii.reserve(s.capacity()+1);
        i.swap(ii);
        build_index();
      }
    }
    catch(...){
      rebuild_index();
      throw;
    }
    return sentinel();
  }

  template<typename Iterator,typename... Args>
  range nv_emplace(Iterator p,Args&&... args)
  {
    auto q=prereserve(p);
    auto it=s.emplace(
      iterator_from(q),
      value_holder_emplacing_ctor,std::forward<Args>(args)...);
    push_index_entry();
    return range_from(it);
  }

  template<typename... Args>
  range nv_emplace_back(Args&&... args)
  {
    prereserve();
    s.emplace_back(value_holder_emplacing_ctor,std::forward<Args>(args)...);
    push_index_entry();
    return range_from(s.size()-1);
  }

  virtual range push_back(const_value_pointer x)
  {return nv_push_back(const_concrete_ref(x));}

  range nv_push_back(const Concrete& x)
  {
    prereserve();
    s.emplace_back(x);
    push_index_entry();
    return range_from(s.size()-1);
  }

  virtual range push_back_move(value_pointer x)
  {return nv_push_back(std::move(concrete_ref(x)));}

  range nv_push_back(Concrete&& x)
  {
    prereserve();
    s.emplace_back(std::move(x));
    push_index_entry();
    return range_from(s.size()-1);
  }

  virtual range insert(const_base_iterator p,const_value_pointer x)
  {return nv_insert(const_iterator(p),const_concrete_ref(x));}

  range nv_insert(const_iterator p,const Concrete& x)
  {
    p=prereserve(p);
    auto it=s.emplace(iterator_from(p),x);
    push_index_entry();
    return range_from(it);
  }

  virtual range insert_move(const_base_iterator p,value_pointer x)
  {return nv_insert(const_iterator(p),std::move(concrete_ref(x)));}

  range nv_insert(const_iterator p,Concrete&& x)
  {
    p=prereserve(p);
    auto it=s.emplace(iterator_from(p),std::move(x));
    push_index_entry();
    return range_from(it);
  }

  template<typename InputIterator>
  range nv_insert(InputIterator first,InputIterator last)
  {
    return nv_insert(
      const_iterator(concrete_ptr(s.data()+s.size())),first,last);
  }

  template<typename InputIterator>
  range nv_insert(const_iterator p,InputIterator first,InputIterator last)
  {
    return insert(
      p,first,last,
      typename std::iterator_traits<InputIterator>::iterator_category{});
  }

  virtual range erase(const_base_iterator p)
  {return nv_erase(const_iterator(p));}

  range nv_erase(const_iterator p)
  {
    pop_index_entry();
    return range_from(s.erase(iterator_from(p)));
  }
    
  virtual range erase(const_base_iterator first,const_base_iterator last)
  {return nv_erase(const_iterator(first),const_iterator(last));}

  range nv_erase(const_iterator first,const_iterator last)
  {
    std::size_t n=s.size();
    auto it=s.erase(iterator_from(first),iterator_from(last));
    pop_index_entry(n-s.size());
    return range_from(it);
  }

  virtual range erase_till_end(const_base_iterator first)
  {
    std::size_t n=s.size();
    auto it=s.erase(iterator_from(first),s.end());
    pop_index_entry(n-s.size());
    return range_from(it);
  }

  virtual range erase_from_begin(const_base_iterator last)
  {
    std::size_t n=s.size();
    auto it=s.erase(s.begin(),iterator_from(last));
    pop_index_entry(n-s.size());
    return range_from(it);
  }

  base_sentinel clear()noexcept{return nv_clear();}

  base_sentinel nv_clear()noexcept
  {
    s.clear();
    for(std::size_t n=i.size()-1;n--;)i.pop_back();
    return sentinel();
  }

private:
  template<typename... Args>
  static segment_backend_unique_ptr new_(
    segment_allocator_type al,Args&&... args)
  {
    auto p=std::allocator_traits<segment_allocator_type>::allocate(al,1);
    try{
      ::new ((void*)p) split_segment{std::forward<Args>(args)...};
    }
    catch(...){
      std::allocator_traits<segment_allocator_type>::deallocate(al,p,1);
      throw;
    }
    return {p,&delete_};
  }

  static void delete_(segment_backend* p)
  {
    auto q=static_cast<split_segment*>(p);
    auto al=segment_allocator_type{q->s.get_allocator()};
    q->~split_segment();
    std::allocator_traits<segment_allocator_type>::deallocate(al,q,1);
  }

  split_segment(const Allocator& al):
    s{typename store::allocator_type{al}},
    i{{},typename index::allocator_type{al}}
  {
    s.reserve(1); /* --> s.data()!=nullptr */
    build_index();
  }

  split_segment(store&& s_):
    s{std::move(s_)},i{{},typename index::allocator_type{s.get_allocator()}}
  {
    s.reserve(1); /* --> s.data()!=nullptr */
    build_index();
  }

  void prereserve()
  {
    if(s.size()==s.capacity())expand();
  }

  const_base_iterator prereserve(const_base_iterator p)
  {
    if(s.size()==s.capacity()){
      auto n=p-i.data();
      expand();
      return const_base_iterator{i.data()+n};
    }
    else return p;
  }

  const_iterator prereserve(const_iterator p)
  {
    if(s.size()==s.capacity()){
      auto n=p-const_concrete_ptr(s.data());
      expand();
      return const_concrete_ptr(s.data())+n;
    }
    else return p;
  }

  const_iterator prereserve(const_iterator p,std::size_t m)
  {
    if(s.size()+m>s.capacity()){
      auto n=p-const_concrete_ptr(s.data());
      expand(m);
      return const_concrete_ptr(s.data())+n;
    }
    else return p;
  }

  void expand()
  {
    std::size_t c=
      s.size()<=1||(s.max_size()-1-s.size())/2<s.size()?
        s.size()+1:
        s.size()+s.size()/2;
    i.reserve(c+1);
    s.reserve(c);
    rebuild_index();
  }

  void expand(std::size_t m)
  {
    i.reserve(s.size()+m+1);
    s.reserve(s.size()+m);
    rebuild_index();
  }

  void build_index(std::size_t start=0)
  {
    for(std::size_t n=start,m=s.size();n<=m;++n){
      i.push_back(Model::make_value_type(concrete_ref(s.data()[n])));
    };
  }

  void rebuild_index()
  {
    i.clear();
    build_index();
  }

  void push_index_entry()
  {
    build_index(s.size());
  }

  void pop_index_entry(std::size_t n=1)
  {
    while(n--)i.pop_back();
  }

  static Concrete& concrete_ref(value_pointer p)noexcept
  {
    return *static_cast<Concrete*>(p);
  }

  static Concrete& concrete_ref(store_value_type& r)noexcept
  {
    return *concrete_ptr(&r);
  }

  static const Concrete& const_concrete_ref(const_value_pointer p)noexcept
  {
    return *static_cast<const Concrete*>(p);
  }

  static Concrete* concrete_ptr(store_value_type* p)noexcept
  {
    return reinterpret_cast<Concrete*>(
      static_cast<value_holder_base<Concrete>*>(p));
  }

  static const Concrete* const_concrete_ptr(const store_value_type* p)noexcept
  {
    return concrete_ptr(const_cast<store_value_type*>(p));
  }

  static value_type* value_ptr(const value_type* p)noexcept
  {
    return const_cast<value_type*>(p);
  }

  /* It would have sufficed if iterator_from returned const_store_iterator
   * except for the fact that some old versions of libstdc++ claiming to be
   * C++11 compliant do not however provide std::vector modifier ops taking
   * const_iterator's.
   */

  store_iterator iterator_from(const_base_iterator p)
  {
    return s.begin()+(p-i.data());
  }

  store_iterator iterator_from(const_iterator p)
  {
    return s.begin()+(p-const_concrete_ptr(s.data()));
  }

  base_sentinel sentinel()const noexcept
  {
    return base_iterator{value_ptr(i.data()+s.size())};
  }

  range range_from(const_store_iterator it)const
  {
    return {base_iterator{value_ptr(i.data()+(it-s.begin()))},sentinel()};
  }
    
  range range_from(std::size_t n)const
  {
    return {base_iterator{value_ptr(i.data()+n)},sentinel()};
  }

  template<typename InputIterator>
  range insert(
    const_iterator p,InputIterator first,InputIterator last,
    std::input_iterator_tag)
  {
    std::size_t n=0;
    for(;first!=last;++first,++n,++p){
      p=prereserve(p);
      s.emplace(iterator_from(p),*first);
      push_index_entry();
    }
    return range_from(iterator_from(p-n));
  }

  template<typename InputIterator>
  range insert(
    const_iterator p,InputIterator first,InputIterator last,
    std::forward_iterator_tag)
  {
    auto n=s.size();
    auto m=static_cast<std::size_t>(std::distance(first,last));
    if(m){
      p=prereserve(p,m);
      try{
        s.insert(iterator_from(p),first,last);
      }
      catch(...){
        build_index(n+1);
        throw;
      }
      build_index(n+1);
    }
    return range_from(iterator_from(p));
  }

  store s;
  index i;
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* split_segment.hpp
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
*/