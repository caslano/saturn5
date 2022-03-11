/* Copyright 2016-2020 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_PACKED_SEGMENT_HPP
#define BOOST_POLY_COLLECTION_DETAIL_PACKED_SEGMENT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/detail/workaround.hpp>
#include <boost/poly_collection/detail/segment_backend.hpp>
#include <boost/poly_collection/detail/value_holder.hpp>
#include <memory>
#include <new>
#include <vector>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

/* segment_backend implementation where value_type& and Concrete& actually refer
 * to the same stored entity.
 *
 * Requires:
 *  - [const_]base_iterator is a stride iterator constructible from
 *    {value_type*,sizeof(store_value_type)}.
 *  - Model provides a function value_ptr for
 *    const Concrete* -> const value_type* conversion.
 */

template<typename Model,typename Concrete,typename Allocator>
class packed_segment:public segment_backend<Model,Allocator>
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
    template rebind_alloc<packed_segment>;

public:
  virtual ~packed_segment()=default;

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
    return s==static_cast<const packed_segment&>(x).s;
  }

  virtual Allocator get_allocator()const noexcept{return s.get_allocator();}

  virtual base_iterator begin()const noexcept{return nv_begin();}

  base_iterator nv_begin()const noexcept
  {
    return {value_ptr(s.data()),sizeof(store_value_type)};
  }

  virtual base_iterator end()const noexcept{return nv_end();}

  base_iterator nv_end()const noexcept
  {
    return {value_ptr(s.data()+s.size()),sizeof(store_value_type)};
  }

  virtual bool          empty()const noexcept{return nv_empty();}
  bool                  nv_empty()const noexcept{return s.empty();}
  virtual std::size_t   size()const noexcept{return nv_size();}
  std::size_t           nv_size()const noexcept{return s.size();}
  virtual std::size_t   max_size()const noexcept{return nv_max_size();}
  std::size_t           nv_max_size()const noexcept{return s.max_size();}
  virtual std::size_t   capacity()const noexcept{return nv_capacity();}
  std::size_t           nv_capacity()const noexcept{return s.capacity();}
  virtual base_sentinel reserve(std::size_t n){return nv_reserve(n);}
  base_sentinel         nv_reserve(std::size_t n)
                          {s.reserve(n);return sentinel();}
  virtual base_sentinel shrink_to_fit(){return nv_shrink_to_fit();}
  base_sentinel         nv_shrink_to_fit()
                          {s.shrink_to_fit();return sentinel();}

  template<typename Iterator,typename... Args>
  range nv_emplace(Iterator p,Args&&... args)
  {
    return range_from(
      s.emplace(
        iterator_from(p),
        value_holder_emplacing_ctor,std::forward<Args>(args)...));
  }

  template<typename... Args>
  range nv_emplace_back(Args&&... args)
  {
    s.emplace_back(value_holder_emplacing_ctor,std::forward<Args>(args)...);
    return range_from(s.size()-1);
  }

  virtual range push_back(const_value_pointer x)
  {return nv_push_back(const_concrete_ref(x));}

  range nv_push_back(const Concrete& x)
  {
    s.emplace_back(x);
    return range_from(s.size()-1);
  }

  virtual range push_back_move(value_pointer x)
  {return nv_push_back(std::move(concrete_ref(x)));}

  range nv_push_back(Concrete&& x)
  {
    s.emplace_back(std::move(x));
    return range_from(s.size()-1);
  }

  virtual range insert(const_base_iterator p,const_value_pointer x)
  {return nv_insert(const_iterator(p),const_concrete_ref(x));}

  range nv_insert(const_iterator p,const Concrete& x)
  {
    return range_from(s.emplace(iterator_from(p),x));
  }

  virtual range insert_move(const_base_iterator p,value_pointer x)
  {return nv_insert(const_iterator(p),std::move(concrete_ref(x)));}

  range nv_insert(const_iterator p,Concrete&& x)
  {
    return range_from(s.emplace(iterator_from(p),std::move(x)));
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
#if BOOST_WORKAROUND(BOOST_LIBSTDCXX_VERSION,<40900)
    /* std::vector::insert(pos,first,last) returns void rather than iterator */

    auto n=const_store_value_type_ptr(p)-s.data();
    s.insert(s.begin()+n,first,last);
    return range_from(static_cast<std::size_t>(n)); 
#else
    return range_from(s.insert(iterator_from(p),first,last));
#endif
  }

  virtual range erase(const_base_iterator p)
  {return nv_erase(const_iterator(p));}

  range nv_erase(const_iterator p)
  {
    return range_from(s.erase(iterator_from(p)));
  }
    
  virtual range erase(const_base_iterator first,const_base_iterator last)
  {return nv_erase(const_iterator(first),const_iterator(last));}

  range nv_erase(const_iterator first,const_iterator last)
  {
    return range_from(s.erase(iterator_from(first),iterator_from(last)));
  }

  virtual range erase_till_end(const_base_iterator first)
  {
    return range_from(s.erase(iterator_from(first),s.end()));
  }

  virtual range erase_from_begin(const_base_iterator last)
  {
    return range_from(s.erase(s.begin(),iterator_from(last)));
  }

  virtual base_sentinel clear()noexcept{return nv_clear();}
  base_sentinel         nv_clear()noexcept{s.clear();return sentinel();}

private:
  template<typename... Args>
  static segment_backend_unique_ptr new_(
    segment_allocator_type al,Args&&... args)
  {
    auto p=std::allocator_traits<segment_allocator_type>::allocate(al,1);
    try{
      ::new ((void*)p) packed_segment{std::forward<Args>(args)...};
    }
    catch(...){
      std::allocator_traits<segment_allocator_type>::deallocate(al,p,1);
      throw;
    }
    return {p,&delete_};
  }

  static void delete_(segment_backend* p)
  {
    auto q=static_cast<packed_segment*>(p);
    auto al=segment_allocator_type{q->s.get_allocator()};
    q->~packed_segment();
    std::allocator_traits<segment_allocator_type>::deallocate(al,q,1);
  }

  packed_segment(const Allocator& al):s{typename store::allocator_type{al}}{}
  packed_segment(store&& s):s{std::move(s)}{}

  static Concrete& concrete_ref(value_pointer p)noexcept
  {
    return *static_cast<Concrete*>(p);
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
  
  static value_type* value_ptr(const store_value_type* p)noexcept
  {
    return const_cast<value_type*>(Model::value_ptr(const_concrete_ptr(p)));
  }

  static const store_value_type* const_store_value_type_ptr(
    const Concrete* p)noexcept
  {
    return static_cast<const value_holder<Concrete>*>(
      reinterpret_cast<const value_holder_base<Concrete>*>(p));
  }

  /* It would have sufficed if iterator_from returned const_store_iterator
   * except for the fact that some old versions of libstdc++ claiming to be
   * C++11 compliant do not however provide std::vector modifier ops taking
   * const_iterator's.
   */

  store_iterator iterator_from(const_base_iterator p)
  {
    return iterator_from(static_cast<const_iterator>(p));
  }

  store_iterator iterator_from(const_iterator p)
  {
    return s.begin()+(const_store_value_type_ptr(p)-s.data());
  }

  base_sentinel sentinel()const noexcept
  {
    return base_iterator{
      value_ptr(s.data()+s.size()),
      sizeof(store_value_type)
    };
  }

  range range_from(const_store_iterator it)const
  {
    return {
      {value_ptr(s.data()+(it-s.begin())),sizeof(store_value_type)},
      sentinel()
    };
  }
    
  range range_from(std::size_t n)const
  {
    return {
      {value_ptr(s.data()+n),sizeof(store_value_type)},
      sentinel()
    };
  }

  store s;
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* packed_segment.hpp
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
*/