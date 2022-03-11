//  (C) Copyright Jeremy Siek 1999-2001.
//  Copyright (C) 2006 Trustees of Indiana University
//  Authors: Douglas Gregor and Jeremy Siek

// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/property_map for documentation.

#ifndef BOOST_PROPERTY_MAP_HPP
#define BOOST_PROPERTY_MAP_HPP

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/static_assert.hpp>
#include <cstddef>
#include <boost/detail/iterator.hpp>
#include <boost/concept/assert.hpp>
#include <boost/concept_check.hpp>
#include <boost/concept_archetype.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {

  //=========================================================================
  // property_traits class

  BOOST_MPL_HAS_XXX_TRAIT_DEF(key_type)
  BOOST_MPL_HAS_XXX_TRAIT_DEF(value_type)
  BOOST_MPL_HAS_XXX_TRAIT_DEF(reference)
  BOOST_MPL_HAS_XXX_TRAIT_DEF(category)
 
  template<class PA>
  struct is_property_map :
    boost::mpl::and_<
      has_key_type<PA>,
      has_value_type<PA>,
      has_reference<PA>,
      has_category<PA>
    >
  {};
 
  template <typename PA>
  struct default_property_traits {
    typedef typename PA::key_type key_type;
    typedef typename PA::value_type value_type;
    typedef typename PA::reference reference;
    typedef typename PA::category   category;
  };
 
  struct null_property_traits {};
 
  template <typename PA>
  struct property_traits :
    boost::mpl::if_<is_property_map<PA>,
      default_property_traits<PA>,
      null_property_traits>::type
  {};

#if 0
  template <typename PA>
  struct property_traits {
    typedef typename PA::key_type key_type;
    typedef typename PA::value_type value_type; 
    typedef typename PA::reference reference;
    typedef typename PA::category   category;
  };
#endif

  //=========================================================================
  // property_traits category tags

  namespace detail {
    enum ePropertyMapID { READABLE_PA, WRITABLE_PA, 
                          READ_WRITE_PA, LVALUE_PA, OP_BRACKET_PA, 
                          RAND_ACCESS_ITER_PA, LAST_PA };
  }
  struct readable_property_map_tag { enum { id = detail::READABLE_PA }; };
  struct writable_property_map_tag { enum { id = detail::WRITABLE_PA }; };
  struct read_write_property_map_tag :
    public readable_property_map_tag,
    public writable_property_map_tag
  { enum { id = detail::READ_WRITE_PA }; };

  struct lvalue_property_map_tag : public read_write_property_map_tag
  { enum { id = detail::LVALUE_PA }; };

  //=========================================================================
  // property_traits specialization for pointers

  template <class T>
  struct property_traits<T*> {
    // BOOST_STATIC_ASSERT(boost::is_same<T, T*>::value && !"Using pointers as property maps is deprecated");
    typedef T value_type;
    typedef value_type& reference;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_property_map_tag category;
  };
  template <class T>
  struct property_traits<const T*> {
    // BOOST_STATIC_ASSERT(boost::is_same<T, T*>::value && !"Using pointers as property maps is deprecated");
    typedef T value_type;
    typedef const value_type& reference;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_property_map_tag category;
  };

#if !defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
  // MSVC doesn't have Koenig lookup, so the user has to
  // do boost::get() anyways, and the using clause
  // doesn't really work for MSVC.
} // namespace boost
#endif

  // These need to go in global namespace because Koenig
  // lookup does not apply to T*.

  // V must be convertible to T
  template <class T, class V>
  inline void put(T* pa, std::ptrdiff_t k, const V& val) { pa[k] = val;  }

  template <class T>
  inline const T& get(const T* pa, std::ptrdiff_t k) { return pa[k]; }

#if !defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
namespace boost {
  using ::put;
  using ::get;
#endif

  //=========================================================================
  // concept checks for property maps

  template <class PMap, class Key>
  struct ReadablePropertyMapConcept
  {
    typedef typename property_traits<PMap>::key_type key_type;
    typedef typename property_traits<PMap>::reference reference;
    typedef typename property_traits<PMap>::category Category;
    typedef boost::readable_property_map_tag ReadableTag;
    void constraints() {
      BOOST_CONCEPT_ASSERT((ConvertibleConcept<Category, ReadableTag>));

      val = get(pmap, k);
    }
    PMap pmap;
    Key k;
    typename property_traits<PMap>::value_type val;
  };
  template <typename KeyArchetype, typename ValueArchetype>
  struct readable_property_map_archetype {
    typedef KeyArchetype key_type;
    typedef ValueArchetype value_type;
    typedef convertible_to_archetype<ValueArchetype> reference;
    typedef readable_property_map_tag category;
  };
  template <typename K, typename V>
  const typename readable_property_map_archetype<K,V>::reference&
  get(const readable_property_map_archetype<K,V>&, 
      const typename readable_property_map_archetype<K,V>::key_type&)
  {
    typedef typename readable_property_map_archetype<K,V>::reference R;
    return static_object<R>::get();
  }


  template <class PMap, class Key>
  struct WritablePropertyMapConcept
  {
    typedef typename property_traits<PMap>::key_type key_type;
    typedef typename property_traits<PMap>::category Category;
    typedef boost::writable_property_map_tag WritableTag;
    void constraints() {
      BOOST_CONCEPT_ASSERT((ConvertibleConcept<Category, WritableTag>));
      put(pmap, k, val);
    }
    PMap pmap;
    Key k;
    typename property_traits<PMap>::value_type val;
  };
  template <typename KeyArchetype, typename ValueArchetype>
  struct writable_property_map_archetype {
    typedef KeyArchetype key_type;
    typedef ValueArchetype value_type;
    typedef void reference;
    typedef writable_property_map_tag category;
  };
  template <typename K, typename V>
  void put(const writable_property_map_archetype<K,V>&, 
           const typename writable_property_map_archetype<K,V>::key_type&, 
           const typename writable_property_map_archetype<K,V>::value_type&) { }


  template <class PMap, class Key>
  struct ReadWritePropertyMapConcept
  {
    typedef typename property_traits<PMap>::category Category;
    typedef boost::read_write_property_map_tag ReadWriteTag;
    void constraints() {
      BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept<PMap, Key>));
      BOOST_CONCEPT_ASSERT((WritablePropertyMapConcept<PMap, Key>));
      BOOST_CONCEPT_ASSERT((ConvertibleConcept<Category, ReadWriteTag>));
    }
  };
  template <typename KeyArchetype, typename ValueArchetype>
  struct read_write_property_map_archetype
    : public readable_property_map_archetype<KeyArchetype, ValueArchetype>,
      public writable_property_map_archetype<KeyArchetype, ValueArchetype>
  {
    typedef KeyArchetype key_type;
    typedef ValueArchetype value_type;
    typedef convertible_to_archetype<ValueArchetype> reference;
    typedef read_write_property_map_tag category;
  };


  template <class PMap, class Key>
  struct LvaluePropertyMapConcept
  {
    typedef typename property_traits<PMap>::category Category;
    typedef boost::lvalue_property_map_tag LvalueTag;
    typedef typename property_traits<PMap>::reference reference;

    void constraints() {
      BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept<PMap, Key>));
      BOOST_CONCEPT_ASSERT((ConvertibleConcept<Category, LvalueTag>));

      typedef typename property_traits<PMap>::value_type value_type;
      BOOST_MPL_ASSERT((boost::mpl::or_<
                          boost::is_same<const value_type&, reference>,
                          boost::is_same<value_type&, reference> >));

      reference ref = pmap[k];
      ignore_unused_variable_warning(ref);
    }
    PMap pmap;
    Key k;
  };
  template <typename KeyArchetype, typename ValueArchetype>
  struct lvalue_property_map_archetype
    : public readable_property_map_archetype<KeyArchetype, ValueArchetype>
  {
    typedef KeyArchetype key_type;
    typedef ValueArchetype value_type;
    typedef const ValueArchetype& reference;
    typedef lvalue_property_map_tag category;
    const value_type& operator[](const key_type&) const {
      return static_object<value_type>::get();
    }
  };

  template <class PMap, class Key>
  struct Mutable_LvaluePropertyMapConcept
  {
    typedef typename property_traits<PMap>::category Category;
    typedef boost::lvalue_property_map_tag LvalueTag;
    typedef typename property_traits<PMap>::reference reference;
    void constraints() {
      BOOST_CONCEPT_ASSERT((ReadWritePropertyMapConcept<PMap, Key>));
      BOOST_CONCEPT_ASSERT((ConvertibleConcept<Category, LvalueTag>));

      typedef typename property_traits<PMap>::value_type value_type;
      BOOST_MPL_ASSERT((boost::is_same<value_type&, reference>));

      reference ref = pmap[k];
      ignore_unused_variable_warning(ref);
    }
    PMap pmap;
    Key k;
  };
  template <typename KeyArchetype, typename ValueArchetype>
  struct mutable_lvalue_property_map_archetype
    : public readable_property_map_archetype<KeyArchetype, ValueArchetype>,
      public writable_property_map_archetype<KeyArchetype, ValueArchetype>
  {
    typedef KeyArchetype key_type;
    typedef ValueArchetype value_type;
    typedef ValueArchetype& reference;
    typedef lvalue_property_map_tag category;
    value_type& operator[](const key_type&) const { 
      return static_object<value_type>::get();
    }
  };

  template <typename T>
  struct typed_identity_property_map;

  // A helper class for constructing a property map
  // from a class that implements operator[]

  template <class Reference, class LvaluePropertyMap>
  struct put_get_helper { };

  template <class PropertyMap, class Reference, class K>
  inline Reference
  get(const put_get_helper<Reference, PropertyMap>& pa, const K& k)
  {
    Reference v = static_cast<const PropertyMap&>(pa)[k];
    return v;
  }
  template <class PropertyMap, class Reference, class K, class V>
  inline void
  put(const put_get_helper<Reference, PropertyMap>& pa, K k, const V& v)
  {
    static_cast<const PropertyMap&>(pa)[k] = v;
  }

  //=========================================================================
  // Adapter to turn a RandomAccessIterator into a property map

  template <class RandomAccessIterator, 
    class IndexMap
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
    , class T, class R
#else
    , class T = typename std::iterator_traits<RandomAccessIterator>::value_type
    , class R = typename std::iterator_traits<RandomAccessIterator>::reference
#endif
     >
  class iterator_property_map
    : public boost::put_get_helper< R, 
        iterator_property_map<RandomAccessIterator, IndexMap,
        T, R> >
  {
  public:
    typedef typename property_traits<IndexMap>::key_type key_type;
    typedef T value_type;
    typedef R reference;
    typedef boost::lvalue_property_map_tag category;

    inline iterator_property_map(
      RandomAccessIterator cc = RandomAccessIterator(), 
      const IndexMap& _id = IndexMap() ) 
      : iter(cc), index(_id) { }
    inline R operator[](key_type v) const { return *(iter + get(index, v)) ; }
  protected:
    RandomAccessIterator iter;
    IndexMap index;
  };

#if !defined BOOST_NO_STD_ITERATOR_TRAITS
  template <class RAIter, class ID>
  inline iterator_property_map<
    RAIter, ID,
    typename std::iterator_traits<RAIter>::value_type,
    typename std::iterator_traits<RAIter>::reference>
  make_iterator_property_map(RAIter iter, ID id) {
    BOOST_CONCEPT_ASSERT((RandomAccessIteratorConcept<RAIter>));
    typedef iterator_property_map<
      RAIter, ID,
      typename std::iterator_traits<RAIter>::value_type,
      typename std::iterator_traits<RAIter>::reference> PA;
    return PA(iter, id);
  }
#endif
  template <class RAIter, class Value, class ID>
  inline iterator_property_map<RAIter, ID, Value, Value&>
  make_iterator_property_map(RAIter iter, ID id, Value) {
    BOOST_CONCEPT_ASSERT((RandomAccessIteratorConcept<RAIter>));
    typedef iterator_property_map<RAIter, ID, Value, Value&> PMap;
    return PMap(iter, id);
  }

  template <class RandomAccessIterator, 
    class IndexMap
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
    , class T, class R
#else
    , class T = typename std::iterator_traits<RandomAccessIterator>::value_type
    , class R = typename std::iterator_traits<RandomAccessIterator>::reference
#endif
     >
  class safe_iterator_property_map
    : public boost::put_get_helper< R, 
        safe_iterator_property_map<RandomAccessIterator, IndexMap,
        T, R> >
  {
  public:
    typedef typename property_traits<IndexMap>::key_type key_type; 
    typedef T value_type;
    typedef R reference;
    typedef boost::lvalue_property_map_tag category;

    inline safe_iterator_property_map(
      RandomAccessIterator first, 
      std::size_t n_ = 0, 
      const IndexMap& _id = IndexMap() ) 
      : iter(first), n(n_), index(_id) { }
    inline safe_iterator_property_map() { }
    inline R operator[](key_type v) const {
      BOOST_ASSERT(get(index, v) < n);
      return *(iter + get(index, v)) ;
    }
    typename property_traits<IndexMap>::value_type size() const { return n; }
  protected:
    RandomAccessIterator iter;
    typename property_traits<IndexMap>::value_type n;
    IndexMap index;
  };

  template <class RAIter, class ID>
  inline safe_iterator_property_map<
    RAIter, ID,
    typename boost::detail::iterator_traits<RAIter>::value_type,
    typename boost::detail::iterator_traits<RAIter>::reference>
  make_safe_iterator_property_map(RAIter iter, std::size_t n, ID id) {
    BOOST_CONCEPT_ASSERT((RandomAccessIteratorConcept<RAIter>));
    typedef safe_iterator_property_map<
      RAIter, ID,
      typename boost::detail::iterator_traits<RAIter>::value_type,
      typename boost::detail::iterator_traits<RAIter>::reference> PA;
    return PA(iter, n, id);
  }
  template <class RAIter, class Value, class ID>
  inline safe_iterator_property_map<RAIter, ID, Value, Value&>
  make_safe_iterator_property_map(RAIter iter, std::size_t n, ID id, Value) {
    BOOST_CONCEPT_ASSERT((RandomAccessIteratorConcept<RAIter>));
    typedef safe_iterator_property_map<RAIter, ID, Value, Value&> PMap;
    return PMap(iter, n, id);
  }

  //=========================================================================
  // An adaptor to turn a Unique Pair Associative Container like std::map or
  // std::hash_map into an Lvalue Property Map.

  template <typename UniquePairAssociativeContainer>
  class associative_property_map
    : public boost::put_get_helper<
       typename UniquePairAssociativeContainer::value_type::second_type&,
       associative_property_map<UniquePairAssociativeContainer> >
  {
    typedef UniquePairAssociativeContainer C;
  public:
    typedef typename C::key_type key_type;
    typedef typename C::value_type::second_type value_type;
    typedef value_type& reference;
    typedef lvalue_property_map_tag category;
    associative_property_map() : m_c(0) { }
    associative_property_map(C& c) : m_c(&c) { }
    reference operator[](const key_type& k) const {
      return (*m_c)[k];
    }
  private:
    C* m_c;
  };

  template <class UniquePairAssociativeContainer>
  associative_property_map<UniquePairAssociativeContainer>
  make_assoc_property_map(UniquePairAssociativeContainer& c)
  {
    return associative_property_map<UniquePairAssociativeContainer>(c);
  }

  template <typename UniquePairAssociativeContainer>
  class const_associative_property_map
    : public boost::put_get_helper<
       const typename UniquePairAssociativeContainer::value_type::second_type&,
       const_associative_property_map<UniquePairAssociativeContainer> >
  {
    typedef UniquePairAssociativeContainer C;
  public:
    typedef typename C::key_type key_type;
    typedef typename C::value_type::second_type value_type;
    typedef const value_type& reference;
    typedef lvalue_property_map_tag category;
    const_associative_property_map() : m_c(0) { }
    const_associative_property_map(const C& c) : m_c(&c) { }
    reference operator[](const key_type& k) const {
      return m_c->find(k)->second;
    }
  private:
    C const* m_c;
  };
  
  template <class UniquePairAssociativeContainer>
  const_associative_property_map<UniquePairAssociativeContainer>
  make_assoc_property_map(const UniquePairAssociativeContainer& c)
  {
    return const_associative_property_map<UniquePairAssociativeContainer>(c);
  }

  //=========================================================================
  // A property map that always returns the same object by value.
  //
  template <typename ValueType, typename KeyType = void>
  class static_property_map :
      public
  boost::put_get_helper<ValueType,static_property_map<ValueType> >
  { 
    ValueType value;
  public:
    typedef KeyType key_type;
    typedef ValueType value_type;
    typedef ValueType reference;
    typedef readable_property_map_tag category;
    static_property_map(ValueType v) : value(v) {}
    
    template<typename T>
    inline reference operator[](T) const { return value; }
  };

  template <typename KeyType, typename ValueType>
  static_property_map<ValueType, KeyType>
  make_static_property_map(const ValueType& v) {
    return static_property_map<ValueType, KeyType>(v);
  }

  //=========================================================================
  // A property map that always returns a reference to the same object.
  //
  template <typename KeyType, typename ValueType>
  class ref_property_map :
    public
      boost::put_get_helper<ValueType&,ref_property_map<KeyType,ValueType> >
  { 
    ValueType* value;
  public:
    typedef KeyType key_type;
    typedef ValueType value_type;
    typedef ValueType& reference;
    typedef lvalue_property_map_tag category;
    ref_property_map(ValueType& v) : value(&v) {}
    ValueType& operator[](key_type const&) const { return *value; }
  };

  //=========================================================================
  // A generalized identity property map
  template <typename T>
  struct typed_identity_property_map
    : public boost::put_get_helper<T, typed_identity_property_map<T> >
  {
    typedef T key_type;
    typedef T value_type;
    typedef T reference;
    typedef boost::readable_property_map_tag category;

    inline value_type operator[](const key_type& v) const { return v; }
  };

//=========================================================================
  // A property map that applies the identity function to integers
  typedef typed_identity_property_map<std::size_t> identity_property_map;

  //=========================================================================
  // A property map that does not do anything, for
  // when you have to supply a property map, but don't need it.
  namespace detail {
    struct dummy_pmap_reference {
      template <class T>
      dummy_pmap_reference& operator=(const T&) { return *this; }
      operator int() { return 0; }
    };
  }
  class dummy_property_map 
    : public boost::put_get_helper<detail::dummy_pmap_reference,
        dummy_property_map  > 
  {
  public:
    typedef void key_type; 
    typedef int value_type;
    typedef detail::dummy_pmap_reference reference;
    typedef boost::read_write_property_map_tag category;
    inline dummy_property_map() : c(0) { }
    inline dummy_property_map(value_type cc) : c(cc) { }
    inline dummy_property_map(const dummy_property_map& x)
      : c(x.c) { }
    template <class Vertex>
    inline reference operator[](Vertex) const { return reference(); }
   protected:
    value_type c;
  };

  // Convert a Readable property map into a function object
  template <typename PropMap>
  class property_map_function {
    PropMap pm;
    typedef typename property_traits<PropMap>::key_type param_type;
    public:
    explicit property_map_function(const PropMap& pm): pm(pm) {}
    typedef typename property_traits<PropMap>::value_type result_type;
    result_type operator()(const param_type& k) const {return get(pm, k);}
  };

  template <typename PropMap>
  property_map_function<PropMap>
  make_property_map_function(const PropMap& pm) {
    return property_map_function<PropMap>(pm);
  }

} // namespace boost

#ifdef BOOST_GRAPH_USE_MPI
#include <boost/property_map/parallel/parallel_property_maps.hpp>
#endif

#include <boost/property_map/vector_property_map.hpp>

#endif /* BOOST_PROPERTY_MAP_HPP */


/* property_map.hpp
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
*/