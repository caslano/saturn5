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