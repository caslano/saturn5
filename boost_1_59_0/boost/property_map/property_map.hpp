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
#include <iterator>
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
    typename std::iterator_traits<RAIter>::value_type,
    typename std::iterator_traits<RAIter>::reference>
  make_safe_iterator_property_map(RAIter iter, std::size_t n, ID id) {
    BOOST_CONCEPT_ASSERT((RandomAccessIteratorConcept<RAIter>));
    typedef safe_iterator_property_map<
      RAIter, ID,
      typename std::iterator_traits<RAIter>::value_type,
      typename std::iterator_traits<RAIter>::reference> PA;
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
// Hide include from dependency trackers; the right fix
// is not to have it at all, but who knows what'll break
#define BOOST_PMAP_HEADER_NAME <boost/property_map/parallel/parallel_property_maps.hpp>
#include BOOST_PMAP_HEADER_NAME
#undef BOOST_PMAP_HEADER_NAME
#endif

#include <boost/property_map/vector_property_map.hpp>

#endif /* BOOST_PROPERTY_MAP_HPP */


/* property_map.hpp
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
*/