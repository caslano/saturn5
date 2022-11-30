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
K2OAl8yVhGQ8v8c85CLiSR8rqudIIM92orgW3nqdN9lUDpUOtXz1sp79JUN500Tlyo3ysl+5mJeht2J+mBqb+RvMJSLKVqqOfgLq2u96S31JdThQO8S1U1Og2JkeRRDRgNINaPOZ5O2dWUg11DWOVKRS/6JC81RlzstmKC9C5YL320//wThXie+3v/Xv4qbLpJc8k+x7PX/pYt5eagXvHtWOlTINgvA83oreHrY10H4H/Lm5avmb3BCGpLQhYH02mVMAyaCUOihwess+y617Dbf2dwrtk6FfQm8VDNr9NpQ3xGd+V36zmQfrtiSzM0fs6GTkGFV+CXtmR8Z4hpTev2geXcxJaWZfmpOqL3aF1H3K8mJr7HShHQ9LbTgcZMwxZ758PbPjW8wPmH5feuKi71wZy+hWavq70rpV7ULqa9vbX8P0HYA0unChN45i+KdaGeMUNJ4TLUXwQpAf/455OJJIorGK7iYAkYxvCoN9fZ/8wVSswm3+ACcsvMcayMspNDVb8aP/Bw1b2m+n3aUou/EmSfczUtXN+jRx/7fn5aNECoVgDoivTQMj8DDddTDGha+V50gvK3llfHIvdUbWOUtyszUIFli/dCjSKpna2gfObrmfxEgpJmVwsLnb1uu5cRwoagbwEUDoXfC4jNj8Jmy0Riqqmhi7H+8MS0WoVlqlXgy1fiq4vHq7g37/QNz1fRp0vwZ59ZZIjJLMkZSNZmnUN1sFtL8AMVxYdw/23C7oBb792pC17XN3q2WR99u41eT3iftB/fDyCycGvZjJuOfe70Cz1jdr0fL5gackeSqRlKjXTZSAw42tPMFGkLSAxzKv6IHAuY/W+PeR4bmZTKscEm8WhJiph0IjO3FMLBToN0pQtYnrZJQV5Fa6/Wr6+4cyZuTU8YsAjQBPd/fD8pXtmfQ0SX9RIKx+yf+8h1Mt5utvRz3XmbdH5rCHknFNY7Ursu+3Ukr8M9QJVZURF7++OOB/mEg89MwXa7RTawYeTISipK0XrVz3o/3FuYynlSTsDh8qJXNr33TbFjtRupS9Zc+ZA53OTzBmEJKmEotTmtMCj9S89oQDcYfOBI9sCBVOq0yWOkHj/uBQO0irfrNt9ofSecH2uUabpaAjc5WILcYqsaU8z42b/uIEPhZpZj0zKK33Tm+/J5lukkpO4/XZS13oxI1oVuxRWeR3+TCzz6Dn57orZd9vRo23NqD+NbfTn1Fh0grRQW5fNQd8QtPv9qYqB7XmluzT0HYcW5UhUCH5LYGutcwxriOXG4rIppbbFAedxi/1l7u/RXfrby/0wSM5bddsfmaiakm57ohRu+l13SBDcrQDrPz7d8dL/DZaup3DeAqq+MREGuWELbl4JtlnA1ivLIKxPmF91WhRMTIqUGl5e4/2FR3uTjhWSX527Yw4ur6jHpUKMxnubV1GHkYFIqUgCGNJ+PDwfLmm92tLqnYZmH+Qa3roE9O1yi+QUJzuoIgqp8519w+IH7O0BLQorK5iwfidxbggwLv4s1iqSsmYr9lR1o76VUH9wkOPRy73pC/LilMdovditLlsKjJnpWePzPpi9i5ECkULU0TTAE5zF84l8Nre8hob5cd2ZMYBF9tVY5TfBE5refA7KtNchselkO/ufEVji88JbY6ATGfKF955/ajDzdb6Jv+GI910NOD3N4L37y5HZWiymiMe3yORNe0Qj8zT6IxT+kJLzEK00P9VLz7BUOuTWXkWdWludu6VAC2vJx/+EO22PLYamwhbQv5AvrgSQsndebT6Ngp+QVIUuZOtLr1fgeTrkechixltkGiza/v94XTr2XtQtxiOq8nvHD1GpLCWz0MwFbV3WERGgJsLC68QMkpU3PmQ3h4nmI/vzi+5Oyvnu7MdeHfMQJm2jKcq+olYwZ3wCt1GiTv3Sxx/hJCYByDfhXCOPC+q9Umpn0x/z77NY04ddyZ9s+Mm0maCT8JZnUXHdfJM7rArGs/wXNySc0c8z8tSxvulzZSSZnznEMVAxT4n80dJ3NUSmu3RfYuI4bZhWmJPxVbX+KSXhjTrrtQ+Mwj47xSA5NF3nQXD16x5a7e0iQ7AiWls02S7af5vXg3LibIkX/FNTEa53jMq7sjg2TgTb0QqhoaWXdTKTLd5GfuJTOdTb+I5rQUMHnPsxo7odVfOZT3tifyC3fQhQC3GvKR7ip3jrktabyJXehZTjcG089McexN3nP2616t8NS5j1hXqT/OrvNjBTFbj7L5xScniW5vRpLaQhf5zrYiOzTn8u0iYh+VAgldjQa3SnOXwtI/mAgHxUxxmcTjb8U1uxQ55cnksYXh6watWteXnl8HY8x2jUlchYxRt2k2PH4xKbLI3P/sWGDoTNjxQZ3Q21meq8MiN73qhBN727s26ZycDwOZG8txpi1uCpr7XjJXR20Cpq9AvHisy8lW/TmHmNl+XixLsRIGk9IvqZ5+54qqUR8mylUkE9OKGjvan1vfdCfI983xNAo8SrTu4MPv5KopG7gv6vtbp58HYteVU6len1idJproEB5TyCi9H775YmXbJTirWXprzqTgiX0z9UlNr0Wj9RMH0w/x+zNxW9mF3Shf3b5XC6qF2VD42tMTm98+YsEcD3uLfmr6FbOSFCEcEiU6vA0C+xMJ9s6CPKYiSfbkBkctvTWJNdTaNOBARMtl811uhjqbnaqtGOpteOA33IlRVzk0/yn0hkJw8OqnImQ0Jla9HMMEWFmpjiSs7dLQL7TP5y88nggycX+Tm7/Yvvq6t2w29CRjSNKaYXsE2hcv6cUTKedIfAAD1DAdSRUTjrO4xTOxn6wSkjmS17FgRqXV+p3TSKccTvugQTQFzBPkzHqIQWL56nt+yiZ0mpaR58vksgXq7xuKo8ZvdCvuPJJ0/FdnU9b8oQ5PZekrHVEuS1ocmA2n1VtjuedE+Ri3HHgqAHXRETKiOerRttFXqZ1Un33Rwa6xM4A1dPVRak6HW4FzrhT+U84CtxGMTklQ8nLTS7zT7GqbiUtfQ17th5NYYlQP2xe24R9iwZXYYU/Dw61Cm9ZfLgdf49guvww5X8SpipQQ9afmf7PGymJjZ6cYRMLYodG2s8OMsAisPL/nl8SlQBT2b8vK7BrHQSaVaCTNOCnWGgP6PRCNvS+/bmTyrNVarc9XW4rZ+vIXl65LoWWOTxF/MrPpsuy2hZM7LFllT0/Z0aXl2DFzCkPS2d/RaV/QTAcI2bNHGsI7wJF+Iny+huSpQHRqSPhQ2yGS4LEi4XHjhR6mlpHIorLFqrZzKWKJR2C6E6P64GOKcb3I170N7/8FO/5o/V2LexQ9Ul6SwO/b+tPHVlyCLQqeeOiDds92f6Ip73A46NStdb7QN4Pe10scq8Rq5r9sOrraVEvWVLh//DDVfoYupuX7KGAoGWwxORO++euultO4ntSdiQmb/wtuuCJfHr6Hfs+aOpa4vtWnHUxrtGR2zW56fCfrKtzRf3vtyaLU916uf0D70xNFoIo0d7U+T37hew/Zup77Q9DYxFWxwmd2LdjkStb2ijlyZqwebMHYIpNzAl4GAmMeC2DXI2959rlS9uIOq/pmTgqR6h15qfZbepG+uZoO2zRKzdeZ2W3B+0pLV2dWV2NeCpMHJvR9CSDXOPAOk3h83mrK/EXq8rlRbnPR2kvuTM6rgxZwT8dHLJKbZWVFZe6BHg2Lh/PAlQfNrJwcL4vLPHeROTIdfL9X8ij8+FrQwCVlYn3L5VNRh4+UswWbYMmt6PtAZfdlZ4cPsQqyQOmdYd6EzU+TYgCMQ+F3984dA3jKYjB4jQHGzvOx4Nc0jARC+YSI5Il3n7OJhn61bJHirBdvTknq6UPle+ym+Y+CvJyLCzex00vGXJoeWyvp0azxWkY/0hL0MHwlrBoxKG+u2hD8fVb8Wni2ASRoInOBPf3jSl6gVGi5lD6TgSNDfDRTV4ilmKW/kyKKg0vxGQYVVEsR0gvOa+KGlCuqjAMH42AYbGESSvSNY0847sm2D+Bj9579AjLkjRxiCiu/P3AjULDhp+NnHViENMsPgQXSTTRKf4zPi/efG6Rqa+Ip9sSefq4QbMinzwLqwHCxIfnUyRthPr4jzL68hCX2teDJ5RRmmCVNfK79ryX6fnh67UCmPGv3mwfOEMUXBi33msWZJn1Q7p+sF4kLruJ+9CQCPGx4QZ7O6fFfKOvG+Ie/4ZemrJ6pMj9enOGGGn91wYsQZSt+YPW/7VhsvHeAveOwxTTeZv/1I9pXF/NELi6SGpv2+OrqR/LYVIfPekcAvaYcMbyS+ldfkN/nDPduKRNPXVVs+2RPv3HkDKb45ZdvyP3F6LbsyLWA1UajRxpMKvt1dmUrDEbSfLWKtN33kp5v0tOthk0/sk7tqZu9yFdXZDa5+6yYfaHj+7IBdHf86szVdzYscWv8WZJ0V+7xorpbyomXmzCx+emz5Q/qJM2idLXyytvzOg6Aybb8FwciL5z8vagooPKMZQdPseEcL+pIfWxccJO8/WpPDCevGlFM7BEA0HzTcnvhiqe2xBEc8Eu/PqwKn4J7eSXo/+45VlBn2gf2Xs3q5vMZ9QBjBvczfqatsBwObwZ3faA2KHs7BfiTtcDyXI8ryd3lgg3taIHA67EgXVBZXdrT6hMMNFM1PLDy7wB9BE0Tg/+znz1binwdtrwUfmDH0RHz5bjHhgbBeEvXOFNxouzjp0xs1nhUybs1d/tTnafeCpPFzryRT8cPLIXWYsC0TlRTevbKtJFbiXUc4IfUxuiXJvLk76pqxR2jqvc5Q8uNOP4tpkIN1EQgxlyOicKEdj4Q6R7ftXXYpNSmNhjhbz4mE/y+XC3MH69wJYEPNyIalotFzZ/sMxZLF7M8rX38RPDJwUfvlBdVy0KdSGBgPgpiu+D2NktEk12+XTF74LmBGpT6YnhP2+O3r5Jy3JrdRn/B82lQP8kDomzfWQT4NZzsQOOl7418jn7Efk7D3EkHoYGzE/rnL71kGf/6WD3q8++Nhuzzg5gJHnXTDXjI2jBlt5SQSp+pU9Ph4eoI4iHuxJ5yDQSvON0x2mnVWvL3qhzSu/1Q6MdL2ZcV8u5sIx8TodCA+pSgBcYrLG5eexfs1dV4GbDsL3rAauSbGrQe4Mk10zyFsbFSL7TQemuFkCNA9rvz5p3khn+RP6Qg9nS7wkvS3dVd/P9QKmouDSfJKueXC2R1Rq0PU6lY0UMWsSBZESSg38wZVbvh3pUTcBNpf4gZxAdCKQ6xT58YcGSF6+0bKtHgIXRHY+X3MG+Jl1poP/iTJ/e6yzy4SH3KJBbaJzlF/45hiQdRaeH3mC2Bce/0taPupA7sRo/P5VyJpzgfa2TYnO78TWLgqVPMfdPG9m+HYTM+GfTZ5cz6sl5BvUzVtka9cvNg67cxKrJXSLKBWpWHLijdK4+RY+pQ+8qGp+xXXZBaMwbAPOZmtWi6Q4x+ii14uTg6/tIvnS+dXeCT44Wu4Ep5ZHXkrC7S2+o39kF3o16As7qqjeJvvxFN9Vn7gwIWPJvg1y25zKRM3pn3W7idkU+9FVQq6ju++rP8pukNd8sr8cFeJmn8+zPbrZharntZb7Tjp6Onna/xvwlOoKPJ6Yju/EgAsRo4KKeKVDY/AuJ7DEYoJrtbfKIBTso31JJIIvNgDWYBW20QhLeV6kkn5GodKZjly6ElHrcllgkHd1xOL+cXBGNdGrwfEyZJfDtIW9GRGnZpFBPo4IW4ylBpHlow339o330NCmdsbf9ZTvPZZxach4FCb1uEFItRxEfToG+nBkEswKPJSAAdlLfLx5rKLNoNEDHxDPQOqRoXB+cqBlkiiPXMDdNcfEYoLhfsZNQnSwS/tnxd3aFV4fmPZPB9awcyQJkLsNph1w7qwTWMqvx8WyvRCVlFNezLyhUg4jb720LdDtNmrWxJ8NEqqm5kU5cMb2ufxPCW0hiF604Ib31qcZqjTgPQfIrS3GE3EmfnlfW3d9FxwdLu/pKPf40yJWcNOdy2SUhFX52xfqe64e3oJRmEdT6pYCPHIWE6Vnc+FxcP4tXx0Zgt3TtjEvbfZRo3xvdPfhn2QIIClBBqRjplBCp8EBtxKMuNtkJUMSBO8OnFVbjJetK0gQD6bli0IkkzbFb4bl3ECyUfldIta2Gr2qTQQeT2v+hH/sU7BikKlfUwTsKdqqu2kLzYLx93pJhcZVlzcoIq1b6UiD3WO5X7SvJo14cPTmvTJseqK/acdfuQrVjniXrOTTHmuM88xo6djPyBY6B0mLUE1T88JtTc4FjrJ+EzvQzlVp9wBOvfUR9QCP92UqUxjFVsR3tNkU3vINtiUC0XIv+gj2L4ABSz60yQrc8NKMcwvx9pjQKGBqG14Ve9JBIK11wdcsxi3GcR9ad3MPIQ0OAR7AFIQf0Qo9OPDCHQUAjAE1Z/B73ro9cWc/r1D8N0XXpkXkNcGwwYtZWJM8dUvFVum79E2cbre4tgRYZXcUvzjfzaWvDR0kKBfJ6yfWF8pv/himmKULq9cwnr36Vde2x0XLM0XLZJ3cagKXvkpOcQHfZbHlZX4VFgoyRt30+p5NJx1Yn40/G01IGKzmlvw9izoRBxaO7swnnzPWJLTRPOtFa3v9YJm50jzOcdhHM9ydNLMWsBcjCpfn4zpnlTkPWe5pcP9nkWP4cj+vdN0PxXY59Fhk8YW/vmWpJMP2gGeEz/L8lseZs8M6YuxFi7vnbU9uk8sf9/kzLji+HHy6bFXfTkSu+H7SduzZ8IGrtAcqx63E2tzjk0hco/dzWLi6TyHOruLQ7OBk4apNk+DI5udi08J7vWtAfzu/UO0kHvCuHaRgzkGtd5AlzmLG1UG/c39zVetB19i8NW/f6hpgO4cc6wxrwfK9XHM5G2mRWnbgyKeFFhyG5sJPYRkBdHUZwxQna+cv9bNAZCoijawk1o/5pVxO9f7PSLbNP2lxl1v6vgL+I2E9aonYlOaJl/I5EPBna+xmVRvguOoP585OZ+IyhIGB1WC1JAQ19cSNweRTsauxPaLiaV39O9U3jHBasJ2w10h/PUgmOuP4Aq4H7mI3neK1+kStt1+re4YPijP4k7+USSBqLlwe1A1dTr31eJzvMt0aGXa0dX8+AVqi8ugKSCAK5yVw+dGF3T3iBP19epSDpyYbf0OttiQo9ZxzNGZQJHqLMbNlYG/B7ANnJw/+OIgvsf9vZgNTDkAjbRqfxxPbz7FmmjIroY7IDN3Z+94dx0kpG1L6thO/8Ww+ADGt3US8GAlHX47lGlSlSrczfZuu4VlCPHO9betMEsgn9E85dXVhvGBn3yY5PAkYrhE2jOKTb9hSWOVqNhQU5rrnLpKt0buw1RuFrr0vKg8crh6dovo9VNaAvvn8B82g/EsiJ58mxqqT8MDVdd0uquXY6V7j+GR7SUGCOpGp+vwkUGr8jC1SDn6C+EmvJq3TKLUij5XWeYVUwA82SFHN7GU9KJDN7wD4M6zQBkl1TsdM96QVdalmQcEzjYRjKZjus1kX0yh7sYL/UeeilKWH3IRNDdO409k0L+seF+WKn5ZJhGW//iYpNP9R1zkreBgNR9skXyjt5w5Y4DgJe7dEJw0PpkL0ntBOyxnKr2Pu8X9j9ETYLQlWXpUKLJYOh1x
*/