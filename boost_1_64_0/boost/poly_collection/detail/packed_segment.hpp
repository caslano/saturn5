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
Sf3qGfwNuJlYeKMi9QK94aFwT3mWAycMljVY4wIHjrwZa+CDCJe6cBsrAqN4XZsmG93Hkbz+YODmEE18aYFCmq9LTGXkh7LhPgHd31SYpxsYXLxzYE5yTC2HBGnMvIGBP6CDz6KBOePE3M58VyWL5ftyDHP6pI3pY6IbDzhmh81HvWijMcNJPqtwFJ2dWz+j2mN9AgO5gXvRSn2JXOHOTuBGHKfa7fPap695lFO+DgJx9hHmZSf5XXXkZ19Vn8UF33oF0z6LF3maxmFzdH+iPfKZjEY+viI/KdMbmrQwXNUxfpsuDh94/v7dJRND3RsgYGQ+73bw4W+qfNDFg8Vg9FTMTnq5FnOqCsiJpiikDv0W8xyogKKfYm940/6L4Mn9F3ftMdbfNEvgyYGjRDTLAh7vHNvr71NkureavoIJXoer4G/Q+AmQjwUm8/ZRXMebCY8eI5VIvNv1I/gG4vEY8V7UC1fxVMvd8e0H+DaT5GF5fGa2TiTmWHz/Cb6zjhXAuJLNRscLv320C0hL8Pvi3VCR+/qSX53uZ0hHjY6kuDKfhMVMc7u9mjlKd/9oPbizcf8bo6DF/Ly3gD7l/vfXicbv9vK5+uG3EHQ0edOrmPOJ9kv5vsZQz+M4zWt4S8JR7+Mgyeu6hbGZSV5ntwocKOLdTUycvKNJXve8FcM0zsUSNQJZ+0MbOIxX+6Ih47n/1ja2uQlAzvV6jZ7A0euMjNd9b8MxqHzo+KoYDHeZ42qAYIg/JBzhEH/IicPCARwr7+ucOBLAKm/rthPYkSvviw6cK+9tt3PgeN4Me8nCutrlsSw+/HQs3hKAizjHf2ISv7r6/KWBjJ5qy7JnuxtPjt1A67r4qoWd1ke8O9g46iNMl7pKGDUCSI+QeWV3tOlomj10qZa1z7fcuEVcUxU6tyrnoTs5cUt9lBfbmbP8/sm33FgR51qPlx1ODF10ZHcxXDj1cjXyZ2UJ7uzCki7C5Pu+CwdWvB/Ed3FhpN6t34jeR/jvuPBUnFnpZzsrfIDZ3ZG7OtMAyO6l2pgpc8bDd9o4bFN0dSJPelvBxjUXrDFRghdh7ns3F4bGIuuDl20c6dmyfNvvbtPRl/eioln7XnZiWL/i7XuPCayzfX/pwNn1euKeLgzVK+P16wkc6XWsHk7eizBNtHmaqTX915yuyJoe35vooGk6W0dddPxcWG9mW1mX4/u4cNQHm6pU2Hved3Ms+OoYQDW2PzitJ0FKgHZifevU/QRuuMgXZqnC7yPM7xwYUs9tFQmy0r3f+0+msdR1/TaEC0tbDVmeCw9wYOQ2guW7dZcDN3Ln+6Yaa67VtJ1UOlX2QGA2ian19Uk6zeosjt+DgHG85yD765WG7lS1JWb3gwkzEUJf8QGIMCyEvt2vH/1QwhjPHep7WldruhhTLD7kw+gbxhmt1eBH9kd+Rxub/5XmiXd1R+vfz27udh9rN4WmPRIGoPyuBueapN1a0ejNdxZjejto9NYj6BWi46Nrw027lokwH272tnAGal7Coat95ySPX5ww6UN4exNI8dj1DPNdShJyXe3jtBxMCE0/SHtAfxapoS5g7OOp6Na6LOMRlb7pFdCN1f61M6WMABkxgWKNs0GrktfDn633uPR6aQMVnuagS3mKhhdX/FU+PzgxQasZgjSQ+cycdGNm28dP1PMC4Z7lwNkNKXmecmA1UN/Nu/x+9u4mD/ElfxcqmyijPBd4i+mXl3QCWImrm4x9glzwcAffs14DP27v93M/C3sp/PzCo+JxuSIqn3oA0YXJlwHl07a/uyidEZZiVjo+7+/fMh1X794ZductpmPp/qTKf9stLazVEo+V+owbZ4ug8Be2boYnMZg=
*/