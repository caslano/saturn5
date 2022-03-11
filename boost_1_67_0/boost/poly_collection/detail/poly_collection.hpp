/* Copyright 2016-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_POLY_COLLECTION_HPP
#define BOOST_POLY_COLLECTION_DETAIL_POLY_COLLECTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <algorithm>
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/poly_collection/detail/allocator_adaptor.hpp>
#include <boost/poly_collection/detail/iterator_impl.hpp>
#include <boost/poly_collection/detail/is_acceptable.hpp>
#include <boost/poly_collection/detail/is_constructible.hpp>
#include <boost/poly_collection/detail/is_final.hpp>
#include <boost/poly_collection/detail/segment.hpp>
#include <boost/poly_collection/detail/type_info_map.hpp>
#include <boost/poly_collection/exception.hpp>
#include <iterator>
#include <type_traits>
#include <typeinfo>
#include <utility>

namespace boost{

namespace poly_collection{

namespace common_impl{

/* common implementation for all polymorphic collections */

using namespace detail;

template<typename Model,typename Allocator>
class poly_collection
{
  template<typename T>
  static const std::type_info& subtypeid(const T& x)
    {return Model::subtypeid(x);}
  template<typename...>
  struct for_all_types{using type=void*;};
  template<typename... T>
  using for_all=typename for_all_types<T...>::type;
  template<typename T>
  struct is_implementation: /* using makes VS2015 choke, hence we derive */
    Model::template is_implementation<typename std::decay<T>::type>{};
  template<typename T>
  using enable_if_implementation=
    typename std::enable_if<is_implementation<T>::value>::type*;
  template<typename T>
  using enable_if_not_implementation=
    typename std::enable_if<!is_implementation<T>::value>::type*;
  template<typename T>
  using is_acceptable=
    detail::is_acceptable<typename std::decay<T>::type,Model>;
  template<typename T>
  using enable_if_acceptable=
    typename std::enable_if<is_acceptable<T>::value>::type*;
  template<typename T>
  using enable_if_not_acceptable=
    typename std::enable_if<!is_acceptable<T>::value>::type*;
  template<typename InputIterator>
  using enable_if_derefs_to_implementation=enable_if_implementation<
    typename std::iterator_traits<InputIterator>::value_type
  >;
  template<typename T>
  using is_terminal=
    typename Model::template is_terminal<typename std::decay<T>::type>;
  template<typename T>
  using enable_if_terminal=
    typename std::enable_if<is_terminal<T>::value>::type*;
  template<typename T>
  using enable_if_not_terminal=
    typename std::enable_if<!is_terminal<T>::value>::type*;
  template<typename InputIterator>
  using derefs_to_terminal=is_terminal< 
    typename std::iterator_traits<InputIterator>::value_type
  >;
  template<typename InputIterator>
  using enable_if_derefs_to_terminal=
    typename std::enable_if<derefs_to_terminal<InputIterator>::value>::type*;
  template<typename InputIterator>
  using enable_if_derefs_to_not_terminal=
    typename std::enable_if<!derefs_to_terminal<InputIterator>::value>::type*;
  template<typename T,typename U>
  using enable_if_not_same=typename std::enable_if<
    !std::is_same<
      typename std::decay<T>::type,typename std::decay<U>::type
    >::value
  >::type*;
  template<typename T,typename U>
  using enable_if_constructible=
    typename std::enable_if<is_constructible<T,U>::value>::type*;
  template<typename T,typename U>
  using enable_if_not_constructible=
    typename std::enable_if<!is_constructible<T,U>::value>::type*;

  using segment_allocator_type=allocator_adaptor<Allocator>;
  using segment_type=detail::segment<Model,segment_allocator_type>;
  using segment_base_iterator=typename segment_type::base_iterator;
  using const_segment_base_iterator=
    typename segment_type::const_base_iterator;
  using segment_base_sentinel=typename segment_type::base_sentinel;
  using const_segment_base_sentinel=
    typename segment_type::const_base_sentinel;
  template<typename T>
  using segment_iterator=typename segment_type::template iterator<T>;
  template<typename T>
  using const_segment_iterator=
    typename segment_type::template const_iterator<T>;
  using segment_map=type_info_map<
    segment_type,
    typename std::allocator_traits<segment_allocator_type>::template
      rebind_alloc<segment_type>
  >;
  using segment_map_allocator_type=typename segment_map::allocator_type;
  using segment_map_iterator=typename segment_map::iterator;
  using const_segment_map_iterator=typename segment_map::const_iterator;

public:
  /* types */

  using value_type=typename segment_type::value_type;
  using allocator_type=Allocator;
  using size_type=std::size_t;
  using difference_type=std::ptrdiff_t;
  using reference=value_type&;
  using const_reference=const value_type&;
  using pointer=typename std::allocator_traits<Allocator>::pointer;
  using const_pointer=typename std::allocator_traits<Allocator>::const_pointer;

private:
  template<typename,bool>
  friend class detail::iterator_impl;
  template<typename,typename>
  friend class detail::local_iterator_impl;
  template<bool Const>
  using iterator_impl=detail::iterator_impl<poly_collection,Const>;
  template<typename BaseIterator>
  using local_iterator_impl=
    detail::local_iterator_impl<poly_collection,BaseIterator>;

public:
  using iterator=iterator_impl<false>;
  using const_iterator=iterator_impl<true>;
  using local_base_iterator=local_iterator_impl<segment_base_iterator>;
  using const_local_base_iterator=
    local_iterator_impl<const_segment_base_iterator>;
  template<typename T>
  using local_iterator=local_iterator_impl<segment_iterator<T>>;
  template<typename T>
  using const_local_iterator=local_iterator_impl<const_segment_iterator<T>>;

  class const_base_segment_info
  {
  public:
    const_base_segment_info(const const_base_segment_info&)=default;
    const_base_segment_info& operator=(const const_base_segment_info&)=default;
    
    const_local_base_iterator begin()const noexcept
      {return {it,it->second.begin()};}
    const_local_base_iterator end()const noexcept
      {return {it,it->second.end()};}
    const_local_base_iterator cbegin()const noexcept{return begin();}
    const_local_base_iterator cend()const noexcept{return end();}

    template<typename T>
    const_local_iterator<T> begin()const noexcept
      {return const_local_iterator<T>{begin()};}
    template<typename T>
    const_local_iterator<T> end()const noexcept
      {return const_local_iterator<T>{end()};}
    template<typename T>
    const_local_iterator<T> cbegin()const noexcept{return begin<T>();}
    template<typename T>
    const_local_iterator<T> cend()const noexcept{return end<T>();}

    const std::type_info& type_info()const{return *it->first;}

  protected:
    friend class poly_collection;

    const_base_segment_info(const_segment_map_iterator it)noexcept:it{it}{}

    const_segment_map_iterator it;
  };

  class base_segment_info:public const_base_segment_info
  {
  public:
    base_segment_info(const base_segment_info&)=default;
    base_segment_info& operator=(const base_segment_info&)=default;

    using const_base_segment_info::begin;
    using const_base_segment_info::end;

    local_base_iterator begin()noexcept
      {return {this->it,this->it->second.begin()};}
    local_base_iterator end()noexcept
      {return {this->it,this->it->second.end()};}

    template<typename T>
    local_iterator<T> begin()noexcept{return local_iterator<T>{begin()};}
    template<typename T>
    local_iterator<T> end()noexcept{return local_iterator<T>{end()};}

  private:
    friend class poly_collection;

    using const_base_segment_info::const_base_segment_info;
  };

  template<typename T>
  class const_segment_info
  {
  public:
    const_segment_info(const const_segment_info&)=default;
    const_segment_info& operator=(const const_segment_info&)=default;
    
    const_local_iterator<T> begin()const noexcept
      {return {it,it->second.begin()};}
    const_local_iterator<T> end()const noexcept
      {return {it,it->second.end()};}
    const_local_iterator<T> cbegin()const noexcept{return begin();}
    const_local_iterator<T> cend()const noexcept{return end();}

  protected:
    friend class poly_collection;

    const_segment_info(const_segment_map_iterator it)noexcept:it{it}{}

    const_segment_map_iterator it;
  };

  template<typename T>
  class segment_info:public const_segment_info<T>
  {
  public:
    segment_info(const segment_info&)=default;
    segment_info& operator=(const segment_info&)=default;

    using const_segment_info<T>::begin;
    using const_segment_info<T>::end;

    local_iterator<T> begin()noexcept
      {return {this->it,this->it->second.begin()};}
    local_iterator<T> end()noexcept
      {return {this->it,this->it->second.end()};}

  private:
    friend class poly_collection;

    using const_segment_info<T>::const_segment_info;
  };

private:
  template<typename SegmentInfo>
  class segment_info_iterator_impl:
    public boost::iterator_adaptor<
      segment_info_iterator_impl<SegmentInfo>,
      const_segment_map_iterator,
      SegmentInfo,
      std::input_iterator_tag,
      SegmentInfo
    >
  {
    segment_info_iterator_impl(const_segment_map_iterator it):
      segment_info_iterator_impl::iterator_adaptor_{it}{}

  public:
    segment_info_iterator_impl()=default;
    segment_info_iterator_impl(const segment_info_iterator_impl&)=default;
    segment_info_iterator_impl& operator=(
      const segment_info_iterator_impl&)=default;

    template<
      typename SegmentInfo2,
      typename std::enable_if<
        std::is_base_of<SegmentInfo,SegmentInfo2>::value
      >::type* =nullptr
    >
    segment_info_iterator_impl(
      const segment_info_iterator_impl<SegmentInfo2>& x):
      segment_info_iterator_impl::iterator_adaptor_{x.base()}{}
      
    template<
      typename SegmentInfo2,
      typename std::enable_if<
        std::is_base_of<SegmentInfo,SegmentInfo2>::value
      >::type* =nullptr
    >
    segment_info_iterator_impl& operator=(
      const segment_info_iterator_impl<SegmentInfo2>& x)
    {
      this->base_reference()=x.base();
      return *this;
    }

  private:
    template<typename>
    friend class segment_info_iterator_impl;
    friend class poly_collection;
    friend class boost::iterator_core_access;
    template<typename>
    friend struct detail::iterator_traits;

    SegmentInfo dereference()const noexcept{return this->base();}
  };

public:
  using base_segment_info_iterator=
    segment_info_iterator_impl<base_segment_info>; 
  using const_base_segment_info_iterator=
    segment_info_iterator_impl<const_base_segment_info>;
    
private:
  template<typename Iterator>
  static Iterator                   nonconst_hlp(Iterator);
  static iterator                   nonconst_hlp(const_iterator);
  static local_base_iterator        nonconst_hlp(const_local_base_iterator);
  template<typename T>
  static local_iterator<T>          nonconst_hlp(const_local_iterator<T>);
  static base_segment_info_iterator nonconst_hlp(
                                      const_base_segment_info_iterator);

  template<typename Iterator>
  using nonconst_version=decltype(nonconst_hlp(std::declval<Iterator>()));

public:
  class const_segment_traversal_info
  {
  public:
    const_segment_traversal_info(const const_segment_traversal_info&)=default;
    const_segment_traversal_info& operator=(
      const const_segment_traversal_info&)=default;
    
    const_base_segment_info_iterator begin()const noexcept
                                       {return pmap->cbegin();}
    const_base_segment_info_iterator end()const noexcept{return pmap->cend();}
    const_base_segment_info_iterator cbegin()const noexcept{return begin();}
    const_base_segment_info_iterator cend()const noexcept{return end();}

  protected:
    friend class poly_collection;

    const_segment_traversal_info(const segment_map& map)noexcept:
      pmap{const_cast<segment_map*>(&map)}{}

    segment_map* pmap;
  };

  class segment_traversal_info:public const_segment_traversal_info
  {
  public:
    segment_traversal_info(const segment_traversal_info&)=default;
    segment_traversal_info& operator=(const segment_traversal_info&)=default;

    using const_segment_traversal_info::begin;
    using const_segment_traversal_info::end;

    base_segment_info_iterator begin()noexcept{return this->pmap->cbegin();}
    base_segment_info_iterator end()noexcept{return this->pmap->cend();}

  private:
    friend class poly_collection;

    using const_segment_traversal_info::const_segment_traversal_info;
  };

  /* construct/destroy/copy */

  poly_collection()=default;
  poly_collection(const poly_collection&)=default;
  poly_collection(poly_collection&&)=default;
  explicit poly_collection(const allocator_type& al):
    map{segment_map_allocator_type{al}}{}
  poly_collection(const poly_collection& x,const allocator_type& al):
    map{x.map,segment_map_allocator_type{al}}{}
  poly_collection(poly_collection&& x,const allocator_type& al):
    map{std::move(x.map),segment_map_allocator_type{al}}{}

  template<typename InputIterator>
  poly_collection(
    InputIterator first,InputIterator last,
    const allocator_type& al=allocator_type{}):
    map{segment_map_allocator_type{al}}
  {
    this->insert(first,last);
  }

  // TODO: what to do with initializer_list?

  poly_collection& operator=(const poly_collection&)=default;
  poly_collection& operator=(poly_collection&&)=default;

  allocator_type get_allocator()const noexcept{return map.get_allocator();}

  /* type registration */

  template<
    typename... T,
    for_all<enable_if_acceptable<T>...> =nullptr
  >
  void register_types()
  {
    /* http://twitter.com/SeanParent/status/558765089294020609 */

    using seq=int[1+sizeof...(T)];
    (void)seq{
      0,
      (map.insert(
        typeid(T),segment_type::template make<T>(get_allocator())),0)...
    };
  }

  bool is_registered(const std::type_info& info)const
  {
    return map.find(info)!=map.end();
  }

  template<typename T,enable_if_acceptable<T> =nullptr>
  bool is_registered()const
  {
    return is_registered(typeid(T));
  }

  /* iterators */

  iterator       begin()noexcept{return {map.begin(),map.end()};}
  iterator       end()noexcept{return {map.end(),map.end()};}
  const_iterator begin()const noexcept{return {map.begin(),map.end()};}
  const_iterator end()const noexcept{return {map.end(),map.end()};}
  const_iterator cbegin()const noexcept{return begin();}
  const_iterator cend()const noexcept{return end();}

  local_base_iterator begin(const std::type_info& info)
  {
    auto it=get_map_iterator_for(info);
    return {it,segment(it).begin()};
  }

  local_base_iterator end(const std::type_info& info)
  {
    auto it=get_map_iterator_for(info);
    return {it,segment(it).end()};
  }

  const_local_base_iterator begin(const std::type_info& info)const
  {
    auto it=get_map_iterator_for(info);
    return {it,segment(it).begin()};
  }

  const_local_base_iterator end(const std::type_info& info)const
  {
    auto it=get_map_iterator_for(info);
    return {it,segment(it).end()};
  }

  const_local_base_iterator cbegin(const std::type_info& info)const
    {return begin(info);}
  const_local_base_iterator cend(const std::type_info& info)const
    {return end(info);}

  template<typename T,enable_if_acceptable<T> =nullptr>
  local_iterator<T> begin()
  {
    auto it=get_map_iterator_for(typeid(T));
    return {it,segment(it).template begin<T>()};
  }

  template<typename T,enable_if_acceptable<T> =nullptr>
  local_iterator<T> end()
  {
    auto it=get_map_iterator_for(typeid(T));
    return {it,segment(it).template end<T>()};
  }

  template<typename T,enable_if_acceptable<T> =nullptr>
  const_local_iterator<T> begin()const
  {
    auto it=get_map_iterator_for(typeid(T));
    return {it,segment(it).template begin<T>()};
  }

  template<typename T,enable_if_acceptable<T> =nullptr>
  const_local_iterator<T> end()const
  {
    auto it=get_map_iterator_for(typeid(T));
    return {it,segment(it).template end<T>()};
  }

  template<typename T,enable_if_acceptable<T> =nullptr>
  const_local_iterator<T> cbegin()const{return begin<T>();}

  template<typename T,enable_if_acceptable<T> =nullptr>
  const_local_iterator<T> cend()const{return end<T>();}

  base_segment_info segment(const std::type_info& info)
  {
    return get_map_iterator_for(info);
  }

  const_base_segment_info segment(const std::type_info& info)const
  {
    return get_map_iterator_for(info);
  }

  template<typename T,enable_if_acceptable<T> =nullptr>
  segment_info<T> segment(){return get_map_iterator_for(typeid(T));}

  template<typename T,enable_if_acceptable<T> =nullptr>
  const_segment_info<T> segment()const{return get_map_iterator_for(typeid(T));}

  segment_traversal_info       segment_traversal()noexcept{return map;}
  const_segment_traversal_info segment_traversal()const noexcept{return map;}

  /* capacity */

  bool empty()const noexcept
  {
    for(const auto& x:map)if(!x.second.empty())return false;
    return true;
  }

  bool empty(const std::type_info& info)const
  {
    return segment(get_map_iterator_for(info)).empty();
  }

  template<typename T,enable_if_acceptable<T> =nullptr>
  bool empty()const
  {
    return segment(get_map_iterator_for(typeid(T))).template empty<T>();
  }

  size_type size()const noexcept
  {
    size_type res=0;
    for(const auto& x:map)res+=x.second.size();
    return res;
  }

  size_type size(const std::type_info& info)const
  {
    return segment(get_map_iterator_for(info)).size();
  }

  template<typename T,enable_if_acceptable<T> =nullptr>
  size_type size()const
  {
    return segment(get_map_iterator_for(typeid(T))).template size<T>();
  }

  size_type max_size(const std::type_info& info)const
  {
    return segment(get_map_iterator_for(info)).max_size();
  }

  template<typename T,enable_if_acceptable<T> =nullptr>
  size_type max_size()const
  {
    return segment(get_map_iterator_for(typeid(T))).template max_size<T>();
  }

  size_type capacity(const std::type_info& info)const
  {
    return segment(get_map_iterator_for(info)).capacity();
  }

  template<typename T,enable_if_acceptable<T> =nullptr>
  size_type capacity()const
  {
    return segment(get_map_iterator_for(typeid(T))).template capacity<T>();
  }

  void reserve(size_type n)
  {
    for(auto& x:map)x.second.reserve(n);
  }

  void reserve(const std::type_info& info,size_type n)
  {
    segment(get_map_iterator_for(info)).reserve(n);
  }

  template<typename T,enable_if_acceptable<T> =nullptr>
  void reserve(size_type n)
  {
    /* note this creates the segment if it didn't previously exist */

    segment(get_map_iterator_for<T>()).template reserve<T>(n);
  }

  void shrink_to_fit()
  {
    for(auto& x:map)x.second.shrink_to_fit();
  }

  void shrink_to_fit(const std::type_info& info)
  {
    segment(get_map_iterator_for(info)).shrink_to_fit();
  }

  template<typename T,enable_if_acceptable<T> =nullptr>
  void shrink_to_fit()
  {
    segment(get_map_iterator_for(typeid(T))).template shrink_to_fit<T>();
  }

  /* modifiers */

  template<typename T,typename... Args,enable_if_acceptable<T> =nullptr>
  iterator emplace(Args&&... args)
  {
    auto it=get_map_iterator_for<T>();
    return {
      it,map.end(),
      segment(it).template emplace_back<T>(std::forward<Args>(args)...)
    };
  }

  template<typename T,typename... Args,enable_if_acceptable<T> =nullptr>
  iterator emplace_hint(const_iterator hint,Args&&... args)
  {
    auto  it=get_map_iterator_for<T>();
    return {
      it,map.end(),
      hint.mapit==it? /* hint in segment */
        segment(it).template emplace<T>(
          hint.segpos,std::forward<Args>(args)...):
        segment(it).template emplace_back<T>(std::forward<Args>(args)...)
    };
  }

  template<typename T,typename... Args,enable_if_acceptable<T> =nullptr>
  local_base_iterator
  emplace_pos(local_base_iterator pos,Args&&... args)
  {
    return emplace_pos<T>(
      const_local_base_iterator{pos},std::forward<Args>(args)...);
  }

  template<typename T,typename... Args,enable_if_acceptable<T> =nullptr>
  local_base_iterator
  emplace_pos(const_local_base_iterator pos,Args&&... args)
  {
    BOOST_ASSERT(pos.type_info()==typeid(T));
    return {
      pos.mapit,
      pos.segment().template emplace<T>(pos.base(),std::forward<Args>(args)...)
    };
  }

  template<typename T,typename... Args>
  local_iterator<T>
  emplace_pos(local_iterator<T> pos,Args&&... args)
  {
    return emplace_pos(
      const_local_iterator<T>{pos},std::forward<Args>(args)...);
  }

  template<typename T,typename... Args>
  local_iterator<T>
  emplace_pos(const_local_iterator<T> pos,Args&&... args)
  {
    return {
      pos.mapit,
      pos.segment().template emplace<T>(pos.base(),std::forward<Args>(args)...)
    };
  }

  template<typename T,enable_if_implementation<T> =nullptr>
  iterator insert(T&& x)
  {
    auto it=get_map_iterator_for(x);
    return {it,map.end(),push_back(segment(it),std::forward<T>(x))};
  }

  template<
    typename T,
    enable_if_not_same<const_iterator,T> =nullptr,
    enable_if_implementation<T> =nullptr
  >
  iterator insert(const_iterator hint,T&& x)
  {
    auto it=get_map_iterator_for(x);
    return {
      it,map.end(),
      hint.mapit==it? /* hint in segment */
        segment(it).insert(hint.segpos,std::forward<T>(x)):
        push_back(segment(it),std::forward<T>(x))
    };
  }

  template<
    typename BaseIterator,typename T,
    enable_if_not_same<local_iterator_impl<BaseIterator>,T> =nullptr,
    enable_if_implementation<T> =nullptr
  >
  nonconst_version<local_iterator_impl<BaseIterator>>
  insert(local_iterator_impl<BaseIterator> pos,T&& x)
  {
    BOOST_ASSERT(pos.type_info()==subtypeid(x));
    return {
      pos.mapit,
      pos.segment().insert(pos.base(),std::forward<T>(x))
    };
  }

  template<
    typename InputIterator,
    enable_if_derefs_to_implementation<InputIterator> =nullptr,
    enable_if_derefs_to_not_terminal<InputIterator> =nullptr
  >
  void insert(InputIterator first,InputIterator last)
  {
    for(;first!=last;++first)insert(*first);
  }

  template<
    typename InputIterator,
    enable_if_derefs_to_implementation<InputIterator> =nullptr,
    enable_if_derefs_to_terminal<InputIterator> =nullptr
  >
  void insert(InputIterator first,InputIterator last) 
  {
    if(first==last)return;

    /* same segment for all (type is terminal) */

    auto& seg=segment(get_map_iterator_for(*first)); 
    seg.insert(first,last);
  }

  template<bool Const>
  void insert(iterator_impl<Const> first,iterator_impl<Const> last)
  {
    for(;first!=last;++first){
      auto& seg=segment(get_map_iterator_for(*first,first.segment()));
      push_back(seg,*first);
    }
  }

  template<typename BaseIterator>
  void insert(
    local_iterator_impl<BaseIterator> first,
    local_iterator_impl<BaseIterator> last)
  {
    if(first==last)return;

    /* same segment for all (iterator is local) */

    auto& seg=segment(get_map_iterator_for(*first,first.segment()));
    do seg.push_back(*first); while(++first!=last);
  }

  template<
    typename InputIterator,
    enable_if_derefs_to_implementation<InputIterator> =nullptr,
    enable_if_derefs_to_not_terminal<InputIterator> =nullptr
  >
  void insert(const_iterator hint,InputIterator first,InputIterator last)
  {
    for(;first!=last;++first){
      auto it=get_map_iterator_for(*first);
      if(hint.mapit==it){ /* hint in segment */
        hint={it,map.end(),segment(it).insert(hint.segpos,*first)};
        ++hint;
      }
      else push_back(segment(it),*first);
    }
  }

  template<
    typename InputIterator,
    enable_if_derefs_to_implementation<InputIterator> =nullptr,
    enable_if_derefs_to_terminal<InputIterator> =nullptr
  >
  void insert(const_iterator hint,InputIterator first,InputIterator last) 
  {
    if(first==last)return;

    /* same segment for all (type is terminal) */

    auto it=get_map_iterator_for(*first);
    auto& seg=segment(it); 
    if(hint.mapit==it)seg.insert(hint.segpos,first,last); /* hint in segment */
    else seg.insert(first,last);
  }

  template<bool Const>
  void insert(
    const_iterator hint,iterator_impl<Const> first,iterator_impl<Const> last)
  {
    for(;first!=last;++first){
      auto it=get_map_iterator_for(*first,first.segment());
      if(hint.mapit==it){ /* hint in segment */
        hint={it,map.end(),segment(it).insert(hint.segpos,*first)};
        ++hint;
      }
      else push_back(segment(it),*first);
    }
  }

  template<typename BaseIterator>
  void insert(
    const_iterator hint,
    local_iterator_impl<BaseIterator> first,
    local_iterator_impl<BaseIterator> last)
  {
    if(first==last)return;

    /* same segment for all (iterator is local) */

    auto it=get_map_iterator_for(*first,first.segment());
    auto& seg=segment(it); 
    if(hint.mapit==it){ /* hint in segment */
      do{
        hint={it,map.end(),seg.insert(hint.segpos,*first)};
        ++hint;
      }while(++first!=last);
    }
    else{
      do push_back(seg,*first); while(++first!=last);
    }
  }

  template<
    typename InputIterator,
    enable_if_derefs_to_implementation<InputIterator> =nullptr
  >
  local_base_iterator insert(
    const_local_base_iterator pos,InputIterator first,InputIterator last)
  {
    auto&     seg=pos.segment();
    auto      it=Model::nonconst_iterator(pos.base());
    size_type n=0;

    for(;first!=last;++first){
      BOOST_ASSERT(pos.type_info()==subtypeid(*first));
      it=std::next(seg.insert(it,*first));
      ++n;
    }
    return {pos.mapit,it-n};
  }

  template<typename T,typename InputIterator>
  local_iterator<T> insert(
    const_local_iterator<T> pos,InputIterator first,InputIterator last)
  {
    auto&               seg=pos.segment();
    segment_iterator<T> it=Model::nonconst_iterator(pos.base());
    size_type           n=0;

    for(;first!=last;++first){
      it=std::next(
        static_cast<segment_iterator<T>>(local_insert<T>(seg,it,*first)));
      ++n;
    }
    return {pos.mapit,it-n};
  }

  template<typename T,typename InputIterator>
  local_iterator<T> insert(
    local_iterator<T> pos,InputIterator first,InputIterator last)
  {
    return insert(const_local_iterator<T>{pos},first,last);
  }

  iterator erase(const_iterator pos)
  {
    return {pos.mapit,pos.mapend,pos.segment().erase(pos.segpos)};
  }

  template<typename BaseIterator>
  nonconst_version<local_iterator_impl<BaseIterator>>
  erase(local_iterator_impl<BaseIterator> pos)
  {
    return {pos.mapit,pos.segment().erase(pos.base())};
  }

  iterator erase(const_iterator first, const_iterator last)
  {
    const_segment_map_iterator fseg=first.mapit,
                               lseg=last.mapit,
                               end=first.mapend;

    if(fseg!=lseg){ /* [first,last] spans over more than one segment */
      /* from 1st elem to end of 1st segment */

      segment(fseg).erase_till_end(first.segpos);

      /* entire segments till last one */

      while(++fseg!=lseg)segment(fseg).clear(); 

      /* remaining elements of last segment */

      if(fseg==end){                /* except if at end of container */
        return {end,end};
      }
      else{
        return {fseg,end,segment(fseg).erase_from_begin(last.segpos)};
      }
    }
    else{                   /* range is included in one segment only */
      if(first==last){      /* to avoid segment(fseg) when fseg==end */
        return {fseg,end,first.segpos};
      }
      else{
        return {fseg,end,segment(fseg).erase(first.segpos,last.segpos)};
      }
    }
  }

  template<typename BaseIterator>
  nonconst_version<local_iterator_impl<BaseIterator>>
  erase(
    local_iterator_impl<BaseIterator> first,
    local_iterator_impl<BaseIterator> last)
  {
    BOOST_ASSERT(first.mapit==last.mapit);
    return{
      first.mapit,
      first.segment().erase(first.base(),last.base())
    };
  }

  void clear()noexcept
  {
    for(auto& x:map)x.second.clear();
  }

  void clear(const std::type_info& info)
  {
    segment(get_map_iterator_for(info)).clear();
  }

  template<typename T,enable_if_acceptable<T> =nullptr>
  void clear()
  {
    segment(get_map_iterator_for(typeid(T))).template clear<T>();
  }

  void swap(poly_collection& x){map.swap(x.map);}

private:
  template<typename M,typename A>
  friend bool operator==(
    const poly_collection<M,A>&,const poly_collection<M,A>&);

  template<
    typename T,
    enable_if_acceptable<T> =nullptr,
    enable_if_not_terminal<T> =nullptr
  >
  const_segment_map_iterator get_map_iterator_for(const T& x)
  {
    const auto& id=subtypeid(x);
    auto        it=map.find(id);
    if(it!=map.end())return it;
    else if(id!=typeid(T))throw unregistered_type{id};
    else return map.insert(
      typeid(T),segment_type::template make<T>(get_allocator())).first;
  }

  template<
    typename T,
    enable_if_acceptable<T> =nullptr,
    enable_if_terminal<T> =nullptr
  >
  const_segment_map_iterator get_map_iterator_for(const T&)
  {
    auto it=map.find(typeid(T));
    if(it!=map.end())return it;
    else return map.insert(
      typeid(T),segment_type::template make<T>(get_allocator())).first;
  }

  template<
    typename T,
    enable_if_not_acceptable<T> =nullptr,
    enable_if_not_terminal<T> =nullptr
  >
  const_segment_map_iterator get_map_iterator_for(const T& x)const
  {
    const auto& id=subtypeid(x);
    auto it=map.find(id);
    if(it!=map.end())return it;
    else throw unregistered_type{id};
  }

  template<
    typename T,
    enable_if_not_acceptable<T> =nullptr,
    enable_if_terminal<T> =nullptr
  >
  const_segment_map_iterator get_map_iterator_for(const T&)const
  {
    static_assert(
      is_acceptable<T>::value,
      "type must be move constructible and move assignable");
    return {}; /* never executed */
  }

  template<typename T>
  const_segment_map_iterator get_map_iterator_for(
    const T& x,const segment_type& seg)
  {
    const auto& id=subtypeid(x);
    auto        it=map.find(id);
    if(it!=map.end())return it;
    else return map.insert(
      id,segment_type::make_from_prototype(seg,get_allocator())).first;
  }

  template<typename T>
  const_segment_map_iterator get_map_iterator_for()
  {
    auto it=map.find(typeid(T));
    if(it!=map.end())return it;
    else return map.insert(
      typeid(T),segment_type::template make<T>(get_allocator())).first;
  }

  const_segment_map_iterator get_map_iterator_for(const std::type_info& info)
  {
    return const_cast<const poly_collection*>(this)->
      get_map_iterator_for(info);
  }

  const_segment_map_iterator get_map_iterator_for(
    const std::type_info& info)const
  {
    auto it=map.find(info);
    if(it!=map.end())return it;
    else throw unregistered_type{info};
  }

  static segment_type& segment(const_segment_map_iterator pos)
  {
    return const_cast<segment_type&>(pos->second);
  }

  template<
    typename T,
    enable_if_not_acceptable<T> =nullptr
  >
  segment_base_iterator push_back(segment_type& seg,T&& x)
  {
    return seg.push_back(std::forward<T>(x));
  }

  template<
    typename T,
    enable_if_acceptable<T> =nullptr,
    enable_if_not_terminal<T> =nullptr
  >
  segment_base_iterator push_back(segment_type& seg,T&& x)
  {
    return subtypeid(x)==typeid(T)?
      seg.push_back_terminal(std::forward<T>(x)):
      seg.push_back(std::forward<T>(x));
  }

  template<
    typename T,
    enable_if_acceptable<T> =nullptr,
    enable_if_terminal<T> =nullptr
  >
  segment_base_iterator push_back(segment_type& seg,T&& x)
  {
    return seg.push_back_terminal(std::forward<T>(x));
  }

  template<
    typename T,typename BaseIterator,typename U,
    enable_if_implementation<U> =nullptr,
    enable_if_not_constructible<T,U&&> =nullptr
  >
  static segment_base_iterator local_insert(
    segment_type& seg,BaseIterator pos,U&& x)
  {
    BOOST_ASSERT(subtypeid(x)==typeid(T));
    return seg.insert(pos,std::forward<U>(x));
  }

  template<
    typename T,typename BaseIterator,typename U,
    enable_if_implementation<U> =nullptr,
    enable_if_constructible<T,U&&> =nullptr
  >
  static segment_base_iterator local_insert(
    segment_type& seg,BaseIterator pos,U&& x)
  {
    if(subtypeid(x)==typeid(T))return seg.insert(pos,std::forward<U>(x));
    else return seg.template emplace<T>(pos,std::forward<U>(x));
  }

  template<
    typename T,typename BaseIterator,typename U,
    enable_if_not_implementation<U> =nullptr,
    enable_if_constructible<T,U&&> =nullptr
  >
  static segment_base_iterator local_insert(
    segment_type& seg,BaseIterator pos,U&& x)
  {
    return seg.template emplace<T>(pos,std::forward<U>(x));
  }

  template<
    typename T,typename BaseIterator,typename U,
    enable_if_not_implementation<U> =nullptr,
    enable_if_not_constructible<T,U&&> =nullptr
  >
  static segment_base_iterator local_insert(
    segment_type&,BaseIterator,U&&)
  {
    static_assert(
      is_constructible<T,U&&>::value,
      "element must be constructible from type");
    return {}; /* never executed */
  }

  segment_map map;
};

template<typename Model,typename Allocator>
bool operator==(
  const poly_collection<Model,Allocator>& x,
  const poly_collection<Model,Allocator>& y)
{
  typename poly_collection<Model,Allocator>::size_type s=0;
  const auto &mapx=x.map,&mapy=y.map;
  for(const auto& p:mapx){
    auto ss=p.second.size();
    auto it=mapy.find(*p.first);
    if(it==mapy.end()?ss!=0:p.second!=it->second)return false;
    s+=ss;
  }
  return s==y.size(); 
}

template<typename Model,typename Allocator>
bool operator!=(
  const poly_collection<Model,Allocator>& x,
  const poly_collection<Model,Allocator>& y)
{
  return !(x==y);
}

template<typename Model,typename Allocator>
void swap(
  poly_collection<Model,Allocator>& x,poly_collection<Model,Allocator>& y)
{
  x.swap(y);
}

} /* namespace poly_collection::common_impl */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* poly_collection.hpp
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
*/