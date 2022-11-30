// Copyright 2002 The Trustees of Indiana University.

// Copyright 2018 Glen Joseph Fernandes
// (glenjofe@gmail.com)

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_HPP
#define BOOST_MULTI_ARRAY_HPP

//
// multi_array.hpp - contains the multi_array class template
// declaration and definition
//

#if defined(__GNUC__) && ((__GNUC__*100 + __GNUC_MINOR__) >= 406)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wshadow"
#endif

#include "boost/multi_array/base.hpp"
#include "boost/multi_array/collection_concept.hpp"
#include "boost/multi_array/copy_array.hpp"
#include "boost/multi_array/iterator.hpp"
#include "boost/multi_array/subarray.hpp"
#include "boost/multi_array/multi_array_ref.hpp"
#include "boost/multi_array/algorithm.hpp"
#include "boost/core/alloc_construct.hpp"
#include "boost/core/empty_value.hpp"
#include "boost/array.hpp"
#include "boost/mpl/if.hpp"
#include "boost/type_traits.hpp"
#include <algorithm>
#include <cstddef>
#include <functional>
#include <numeric>
#include <vector>



namespace boost {
  namespace detail {
    namespace multi_array {

      struct populate_index_ranges {
        multi_array_types::index_range
        // RG: underscore on extent_ to stifle strange MSVC warning.
        operator()(multi_array_types::index base,
                   multi_array_types::size_type extent_) {
          return multi_array_types::index_range(base,base+extent_);
        }
      };

#ifdef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
//
// Compilers that don't support partial ordering may need help to
// disambiguate multi_array's templated constructors.  Even vc6/7 are
// capable of some limited SFINAE, so we take the most-general version
// out of the overload set with disable_multi_array_impl.
//
template <typename T, std::size_t NumDims, typename TPtr>
char is_multi_array_impl_help(const_multi_array_view<T,NumDims,TPtr>&);
template <typename T, std::size_t NumDims, typename TPtr>
char is_multi_array_impl_help(const_sub_array<T,NumDims,TPtr>&);
template <typename T, std::size_t NumDims, typename TPtr>
char is_multi_array_impl_help(const_multi_array_ref<T,NumDims,TPtr>&);

char ( &is_multi_array_impl_help(...) )[2];

template <class T>
struct is_multi_array_impl
{
    static T x;
    BOOST_STATIC_CONSTANT(bool, value = sizeof((is_multi_array_impl_help)(x)) == 1);

  typedef mpl::bool_<value> type;
};

template <bool multi_array = false>
struct disable_multi_array_impl_impl
{
    typedef int type;
};

template <>
struct disable_multi_array_impl_impl<true>
{
    // forming a pointer to a reference triggers SFINAE
    typedef int& type; 
};


template <class T>
struct disable_multi_array_impl :
  disable_multi_array_impl_impl<is_multi_array_impl<T>::value>
{ };


template <>
struct disable_multi_array_impl<int>
{
  typedef int type;
};


#endif

    } //namespace multi_array
  } // namespace detail

template<typename T, std::size_t NumDims,
  typename Allocator>
class multi_array :
  public multi_array_ref<T,NumDims>,
  private boost::empty_value<Allocator>
{
  typedef boost::empty_value<Allocator> alloc_base;
  typedef multi_array_ref<T,NumDims> super_type;
public:
  typedef typename super_type::value_type value_type;
  typedef typename super_type::reference reference;
  typedef typename super_type::const_reference const_reference;
  typedef typename super_type::iterator iterator;
  typedef typename super_type::const_iterator const_iterator;
  typedef typename super_type::reverse_iterator reverse_iterator;
  typedef typename super_type::const_reverse_iterator const_reverse_iterator;
  typedef typename super_type::element element;
  typedef typename super_type::size_type size_type;
  typedef typename super_type::difference_type difference_type;
  typedef typename super_type::index index;
  typedef typename super_type::extent_range extent_range;


  template <std::size_t NDims>
  struct const_array_view {
    typedef boost::detail::multi_array::const_multi_array_view<T,NDims> type;
  };

  template <std::size_t NDims>
  struct array_view {
    typedef boost::detail::multi_array::multi_array_view<T,NDims> type;
  };

  explicit multi_array(const Allocator& alloc = Allocator()) :
    super_type((T*)initial_base_,c_storage_order(),
               /*index_bases=*/0, /*extents=*/0),
    alloc_base(boost::empty_init_t(),alloc) {
    allocate_space(); 
  }

  template <class ExtentList>
  explicit multi_array(
      ExtentList const& extents,
      const Allocator& alloc = Allocator()
#ifdef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
      , typename mpl::if_<
      detail::multi_array::is_multi_array_impl<ExtentList>,
      int&,int>::type* = 0
#endif
      ) :
    super_type((T*)initial_base_,extents),
    alloc_base(boost::empty_init_t(),alloc) {
    boost::function_requires<
      detail::multi_array::CollectionConcept<ExtentList> >();
    allocate_space();
  }

    
  template <class ExtentList>
  explicit multi_array(ExtentList const& extents,
                       const general_storage_order<NumDims>& so) :
    super_type((T*)initial_base_,extents,so),
    alloc_base(boost::empty_init_t()) {
    boost::function_requires<
      detail::multi_array::CollectionConcept<ExtentList> >();
    allocate_space();
  }

  template <class ExtentList>
  explicit multi_array(ExtentList const& extents,
                       const general_storage_order<NumDims>& so,
                       Allocator const& alloc) :
    super_type((T*)initial_base_,extents,so),
    alloc_base(boost::empty_init_t(),alloc) {
    boost::function_requires<
      detail::multi_array::CollectionConcept<ExtentList> >();
    allocate_space();
  }


  explicit multi_array(const detail::multi_array
                       ::extent_gen<NumDims>& ranges,
                       const Allocator& alloc = Allocator()) :
    super_type((T*)initial_base_,ranges),
    alloc_base(boost::empty_init_t(),alloc) {

    allocate_space();
  }


  explicit multi_array(const detail::multi_array
                       ::extent_gen<NumDims>& ranges,
                       const general_storage_order<NumDims>& so) :
    super_type((T*)initial_base_,ranges,so),
    alloc_base(boost::empty_init_t()) {

    allocate_space();
  }


  explicit multi_array(const detail::multi_array
                       ::extent_gen<NumDims>& ranges,
                       const general_storage_order<NumDims>& so,
                       Allocator const& alloc) :
    super_type((T*)initial_base_,ranges,so),
    alloc_base(boost::empty_init_t(),alloc) {

    allocate_space();
  }

  multi_array(const multi_array& rhs) :
  super_type(rhs),
  alloc_base(static_cast<const alloc_base&>(rhs)) {
    allocate_space();
    boost::detail::multi_array::copy_n(rhs.base_,rhs.num_elements(),base_);
  }


  //
  // A multi_array is constructible from any multi_array_ref, subarray, or
  // array_view object.  The following constructors ensure that.
  //

  // Due to limited support for partial template ordering, 
  // MSVC 6&7 confuse the following with the most basic ExtentList 
  // constructor.
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
  template <typename OPtr>
  multi_array(const const_multi_array_ref<T,NumDims,OPtr>& rhs,
              const general_storage_order<NumDims>& so = c_storage_order(),
              const Allocator& alloc = Allocator())
    : super_type(0,so,rhs.index_bases(),rhs.shape()),
      alloc_base(boost::empty_init_t(),alloc)
  {
    allocate_space();
    // Warning! storage order may change, hence the following copy technique.
    std::copy(rhs.begin(),rhs.end(),this->begin());
  }

  template <typename OPtr>
  multi_array(const detail::multi_array::
              const_sub_array<T,NumDims,OPtr>& rhs,
              const general_storage_order<NumDims>& so = c_storage_order(),
              const Allocator& alloc = Allocator())
    : super_type(0,so,rhs.index_bases(),rhs.shape()),
      alloc_base(boost::empty_init_t(),alloc)
  {
    allocate_space();
    std::copy(rhs.begin(),rhs.end(),this->begin());
  }


  template <typename OPtr>
  multi_array(const detail::multi_array::
              const_multi_array_view<T,NumDims,OPtr>& rhs,
              const general_storage_order<NumDims>& so = c_storage_order(),
              const Allocator& alloc = Allocator())
    : super_type(0,so,rhs.index_bases(),rhs.shape()),
      alloc_base(boost::empty_init_t(),alloc)
  {
    allocate_space();
    std::copy(rhs.begin(),rhs.end(),this->begin());
  }

#else // BOOST_NO_FUNCTION_TEMPLATE_ORDERING
  // More limited support for MSVC


  multi_array(const const_multi_array_ref<T,NumDims>& rhs,
              const Allocator& alloc = Allocator())
    : super_type(0,c_storage_order(),rhs.index_bases(),rhs.shape()),
      alloc_base(boost::empty_init_t(),alloc)
  {
    allocate_space();
    // Warning! storage order may change, hence the following copy technique.
    std::copy(rhs.begin(),rhs.end(),this->begin());
  }

  multi_array(const const_multi_array_ref<T,NumDims>& rhs,
              const general_storage_order<NumDims>& so,
              const Allocator& alloc = Allocator())
    : super_type(0,so,rhs.index_bases(),rhs.shape()),
      alloc_base(boost::empty_init_t(),alloc)
  {
    allocate_space();
    // Warning! storage order may change, hence the following copy technique.
    std::copy(rhs.begin(),rhs.end(),this->begin());
  }

  multi_array(const detail::multi_array::
              const_sub_array<T,NumDims>& rhs,
              const Allocator& alloc = Allocator())
    : super_type(0,c_storage_order(),rhs.index_bases(),rhs.shape()),
      alloc_base(boost::empty_init_t(),alloc)
  {
    allocate_space();
    std::copy(rhs.begin(),rhs.end(),this->begin());
  }

  multi_array(const detail::multi_array::
              const_sub_array<T,NumDims>& rhs,
              const general_storage_order<NumDims>& so,
              const Allocator& alloc = Allocator())
    : super_type(0,so,rhs.index_bases(),rhs.shape()),
      alloc_base(boost::empty_init_t(),alloc)
  {
    allocate_space();
    std::copy(rhs.begin(),rhs.end(),this->begin());
  }


  multi_array(const detail::multi_array::
              const_multi_array_view<T,NumDims>& rhs,
              const Allocator& alloc = Allocator())
    : super_type(0,c_storage_order(),rhs.index_bases(),rhs.shape()),
      alloc_base(boost::empty_init_t(),alloc)
  {
    allocate_space();
    std::copy(rhs.begin(),rhs.end(),this->begin());
  }

  multi_array(const detail::multi_array::
              const_multi_array_view<T,NumDims>& rhs,
              const general_storage_order<NumDims>& so,
              const Allocator& alloc = Allocator())
    : super_type(0,so,rhs.index_bases(),rhs.shape()),
      alloc_base(boost::empty_init_t(),alloc)
  {
    allocate_space();
    std::copy(rhs.begin(),rhs.end(),this->begin());
  }

#endif // !BOOST_NO_FUNCTION_TEMPLATE_ORDERING

  // Thes constructors are necessary because of more exact template matches.
  multi_array(const multi_array_ref<T,NumDims>& rhs,
              const Allocator& alloc = Allocator())
    : super_type(0,c_storage_order(),rhs.index_bases(),rhs.shape()),
      alloc_base(boost::empty_init_t(),alloc)
  {
    allocate_space();
    // Warning! storage order may change, hence the following copy technique.
    std::copy(rhs.begin(),rhs.end(),this->begin());
  }

  multi_array(const multi_array_ref<T,NumDims>& rhs,
              const general_storage_order<NumDims>& so,
              const Allocator& alloc = Allocator())
    : super_type(0,so,rhs.index_bases(),rhs.shape()),
      alloc_base(boost::empty_init_t(),alloc)
  {
    allocate_space();
    // Warning! storage order may change, hence the following copy technique.
    std::copy(rhs.begin(),rhs.end(),this->begin());
  }


  multi_array(const detail::multi_array::
              sub_array<T,NumDims>& rhs,
              const Allocator& alloc = Allocator())
    : super_type(0,c_storage_order(),rhs.index_bases(),rhs.shape()),
      alloc_base(boost::empty_init_t(),alloc)
  {
    allocate_space();
    std::copy(rhs.begin(),rhs.end(),this->begin());
  }

  multi_array(const detail::multi_array::
              sub_array<T,NumDims>& rhs,
              const general_storage_order<NumDims>& so,
              const Allocator& alloc = Allocator())
    : super_type(0,so,rhs.index_bases(),rhs.shape()),
      alloc_base(boost::empty_init_t(),alloc)
  {
    allocate_space();
    std::copy(rhs.begin(),rhs.end(),this->begin());
  }


  multi_array(const detail::multi_array::
              multi_array_view<T,NumDims>& rhs,
              const Allocator& alloc = Allocator())
    : super_type(0,c_storage_order(),rhs.index_bases(),rhs.shape()),
      alloc_base(boost::empty_init_t(),alloc)
  {
    allocate_space();
    std::copy(rhs.begin(),rhs.end(),this->begin());
  }
    
  multi_array(const detail::multi_array::
              multi_array_view<T,NumDims>& rhs,
              const general_storage_order<NumDims>& so,
              const Allocator& alloc = Allocator())
    : super_type(0,so,rhs.index_bases(),rhs.shape()),
      alloc_base(boost::empty_init_t(),alloc)
  {
    allocate_space();
    std::copy(rhs.begin(),rhs.end(),this->begin());
  }
    
  // Since assignment is a deep copy, multi_array_ref
  // contains all the necessary code.
  template <typename ConstMultiArray>
  multi_array& operator=(const ConstMultiArray& other) {
    super_type::operator=(other);
    return *this;
  }

  multi_array& operator=(const multi_array& other) {
    if (&other != this) {
      super_type::operator=(other);
    }
    return *this;
  }


  template <typename ExtentList>
  multi_array& resize(const ExtentList& extents) {
    boost::function_requires<
      detail::multi_array::CollectionConcept<ExtentList> >();

    typedef detail::multi_array::extent_gen<NumDims> gen_type;
    gen_type ranges;

    for (int i=0; i != NumDims; ++i) {
      typedef typename gen_type::range range_type;
      ranges.ranges_[i] = range_type(0,extents[i]);
    }
    
    return this->resize(ranges);
  }



  multi_array& resize(const detail::multi_array
                      ::extent_gen<NumDims>& ranges) {


    // build a multi_array with the specs given
    multi_array new_array(ranges,this->storage_order(),allocator());


    // build a view of tmp with the minimum extents

    // Get the minimum extents of the arrays.
    boost::array<size_type,NumDims> min_extents;

    const size_type& (*min)(const size_type&, const size_type&) =
      std::min;
    std::transform(new_array.extent_list_.begin(),new_array.extent_list_.end(),
                   this->extent_list_.begin(),
                   min_extents.begin(),
                   min);


    // typedef boost::array<index,NumDims> index_list;
    // Build index_gen objects to create views with the same shape

    // these need to be separate to handle non-zero index bases
    typedef detail::multi_array::index_gen<NumDims,NumDims> index_gen;
    index_gen old_idxes;
    index_gen new_idxes;

    std::transform(new_array.index_base_list_.begin(),
                   new_array.index_base_list_.end(),
                   min_extents.begin(),new_idxes.ranges_.begin(),
                   detail::multi_array::populate_index_ranges());

    std::transform(this->index_base_list_.begin(),
                   this->index_base_list_.end(),
                   min_extents.begin(),old_idxes.ranges_.begin(),
                   detail::multi_array::populate_index_ranges());

    // Build same-shape views of the two arrays
    typename
      multi_array::BOOST_NESTED_TEMPLATE array_view<NumDims>::type view_old = (*this)[old_idxes];
    typename
      multi_array::BOOST_NESTED_TEMPLATE array_view<NumDims>::type view_new = new_array[new_idxes];

    // Set the right portion of the new array
    view_new = view_old;

    using std::swap;
    // Swap the internals of these arrays.
    swap(this->super_type::base_,new_array.super_type::base_);
    swap(this->allocator(),new_array.allocator());
    swap(this->storage_,new_array.storage_);
    swap(this->extent_list_,new_array.extent_list_);
    swap(this->stride_list_,new_array.stride_list_);
    swap(this->index_base_list_,new_array.index_base_list_);
    swap(this->origin_offset_,new_array.origin_offset_);
    swap(this->directional_offset_,new_array.directional_offset_);
    swap(this->num_elements_,new_array.num_elements_);
    swap(this->base_,new_array.base_);
    swap(this->allocated_elements_,new_array.allocated_elements_);

    return *this;
  }


  ~multi_array() {
    deallocate_space();
  }

private:
  friend inline bool operator==(const multi_array& a, const multi_array& b) {
    return a.base() == b.base();
  }

  friend inline bool operator!=(const multi_array& a, const multi_array& b) {
    return !(a == b);
  }

  const super_type& base() const {
    return *this;
  }

  const Allocator& allocator() const {
    return alloc_base::get();
  }

  Allocator& allocator() {
    return alloc_base::get();
  }

  void allocate_space() {
    base_ = allocator().allocate(this->num_elements());
    this->set_base_ptr(base_);
    allocated_elements_ = this->num_elements();
    boost::alloc_construct_n(allocator(),base_,allocated_elements_);
  }

  void deallocate_space() {
    if(base_) {
      boost::alloc_destroy_n(allocator(),base_,allocated_elements_);
      allocator().deallocate(base_,allocated_elements_);
    }
  }

  typedef boost::array<size_type,NumDims> size_list;
  typedef boost::array<index,NumDims> index_list;

  T* base_;
  size_type allocated_elements_;
  enum {initial_base_ = 0};
};

} // namespace boost

#if defined(__GNUC__) && ((__GNUC__*100 + __GNUC_MINOR__) >= 406)
#  pragma GCC diagnostic pop
#endif

#endif

/* multi_array.hpp
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
*/