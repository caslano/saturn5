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