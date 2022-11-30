// Copyright (C) 2004-2008 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Nick Edmonds
//           Andrew Lumsdaine

// The placement of this #include probably looks very odd relative to
// the #ifndef/#define pair below. However, this placement is
// extremely important to allow the various property map headers to be
// included in any order.
#include <boost/property_map/property_map.hpp>

#ifndef BOOST_PARALLEL_DISTRIBUTED_PROPERTY_MAP_HPP
#define BOOST_PARALLEL_DISTRIBUTED_PROPERTY_MAP_HPP

#include <boost/assert.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/optional.hpp>
#include <boost/property_map/parallel/process_group.hpp>
#include <boost/function/function1.hpp>
#include <vector>
#include <set>
#include <boost/property_map/parallel/basic_reduce.hpp>
#include <boost/property_map/parallel/detail/untracked_pair.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/property_map/parallel/local_property_map.hpp>
#include <map>
#include <boost/version.hpp>
#include <boost/property_map/parallel/unsafe_serialize.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/sequenced_index.hpp>

// Serialization functions for constructs we use
#include <boost/serialization/utility.hpp>

namespace boost { namespace parallel {

namespace detail {
  /**************************************************************************
   * Metafunction that degrades an Lvalue Property Map category tag to
   * a Read Write Property Map category tag.
   **************************************************************************/
  template<bool IsLvaluePropertyMap>
  struct make_nonlvalue_property_map
  {
    template<typename T> struct apply { typedef T type; };
  };

  template<>
  struct make_nonlvalue_property_map<true>
  {
    template<typename>
    struct apply
    {
      typedef read_write_property_map_tag type;
    };
  };

  /**************************************************************************
   * Performs a "put" on a property map so long as the property map is
   * a Writable Property Map or a mutable Lvalue Property Map. This
   * is required because the distributed property map's message
   * handler handles "put" messages even for a const property map,
   * although receipt of a "put" message is ill-formed.
   **************************************************************************/
  template<bool IsLvaluePropertyMap>
  struct maybe_put_in_lvalue_pm
  {
    template<typename PropertyMap, typename Key, typename Value>
    static inline void
    do_put(PropertyMap, const Key&, const Value&)
    { BOOST_ASSERT(false); }
  };

  template<>
  struct maybe_put_in_lvalue_pm<true>
  {
    template<typename PropertyMap, typename Key, typename Value>
    static inline void
    do_put(PropertyMap pm, const Key& key, const Value& value)
    {
      using boost::put;

      put(pm, key, value);
    }
  };

  template<typename PropertyMap, typename Key, typename Value>
  inline void
  maybe_put_impl(PropertyMap pm, const Key& key, const Value& value,
                 writable_property_map_tag)
  {
    using boost::put;

    put(pm, key, value);
  }

  template<typename PropertyMap, typename Key, typename Value>
  inline void
  maybe_put_impl(PropertyMap pm, const Key& key, const Value& value,
                 lvalue_property_map_tag)
  {
    typedef typename property_traits<PropertyMap>::value_type value_type;
    typedef typename property_traits<PropertyMap>::reference reference;
    // DPG TBD: Some property maps are improperly characterized as
    // lvalue_property_maps, when in fact they do not provide true
    // references. The most typical example is those property maps
    // built from vector<bool> and its iterators, which deal with
    // proxies. We don't want to mischaracterize these as not having a
    // "put" operation, so we only consider an lvalue_property_map as
    // constant if its reference is const value_type&. In fact, this
    // isn't even quite correct (think of a
    // vector<bool>::const_iterator), but at present C++ doesn't
    // provide us with any alternatives.
    typedef is_same<const value_type&, reference> is_constant;

    maybe_put_in_lvalue_pm<(!is_constant::value)>::do_put(pm, key, value);
  }

  template<typename PropertyMap, typename Key, typename Value>
  inline void
  maybe_put_impl(PropertyMap, const Key&, const Value&, ...)
  { BOOST_ASSERT(false); }

  template<typename PropertyMap, typename Key, typename Value>
  inline void
  maybe_put(PropertyMap pm, const Key& key, const Value& value)
  {
    maybe_put_impl(pm, key, value,
                   typename property_traits<PropertyMap>::category());
  }
} // end namespace detail

/** The consistency model used by the distributed property map. */
enum consistency_model {
  cm_forward = 1 << 0,
  cm_backward = 1 << 1,
  cm_bidirectional = cm_forward | cm_backward,
  cm_flush = 1 << 2,
  cm_reset = 1 << 3,
  cm_clear = 1 << 4
};

/** Distributed property map adaptor.
 *
 *  The distributed property map adaptor is a property map whose
 *  stored values are distributed across multiple non-overlapping
 *  memory spaces on different processes. Values local to the current
 *  process are stored within a local property map and may be
 *  immediately accessed via @c get and @c put. Values stored on
 *  remote processes may also be access via @c get and @c put, but the
 *  behavior differs slightly:
 *
 *  - @c put operations update a local ghost cell and send a "put"
 *    message to the process that owns the value. The owner is free to
 *    update its own "official" value or may ignore the put request.
 *
 *  - @c get operations returns the contents of the local ghost
 *    cell. If no ghost cell is available, one is created using the
 *    default value provided by the "reduce" operation. See, e.g.,
 *    @ref basic_reduce and @ref property_reduce.
 *
 * Using distributed property maps requires a bit more care than using
 * local, sequential property maps. While the syntax and semantics are
 * similar, distributed property maps may contain out-of-date
 * information that can only be guaranteed to be synchronized by
 * calling the @ref synchronize function in all processes.
 *
 * To address the issue of out-of-date values, distributed property
 * maps are supplied with a reduction operation. The reduction
 * operation has two roles:
 *
 *   -# When a value is needed for a remote key but no value is
 *      immediately available, the reduction operation provides a
 *      suitable default. For instance, a distributed property map
 *      storing distances may have a reduction operation that returns
 *      an infinite value as the default, whereas a distributed
 *      property map for vertex colors may return white as the
 *      default.
 *
 *   -# When a value is received from a remote process, the process
 *      owning the key associated with that value must determine which
 *      value---the locally stored value, the value received from a
 *      remote process, or some combination of the two---will be
 *      stored as the "official" value in the property map. The
 *      reduction operation transforms the local and remote values
 *      into the "official" value to be stored.
 *
 * @tparam ProcessGroup the type of the process group over which the
 * property map is distributed and is also the medium for
 * communication.
 *
 * @tparam StorageMap the type of the property map that will
 * store values for keys local to this processor. The @c value_type of
 * this property map will become the @c value_type of the distributed
 * property map. The distributed property map models the same property
 * map concepts as the @c LocalPropertyMap, with one exception: a
 * distributed property map cannot be an LvaluePropertyMap (because
 * remote values are not addressable), and is therefore limited to
 * ReadWritePropertyMap.
 */
template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
class distributed_property_map
{
 public:
  /// The key type of the property map.
  typedef typename property_traits<GlobalMap>::key_type key_type;

  /// The value type of the property map.
  typedef typename property_traits<StorageMap>::value_type value_type;
  typedef typename property_traits<StorageMap>::reference  reference;
  typedef ProcessGroup                        process_group_type;

 private:
  typedef distributed_property_map            self_type;
  typedef typename property_traits<StorageMap>::category local_category;
  typedef typename property_traits<StorageMap>::key_type local_key_type;
  typedef typename property_traits<GlobalMap>::value_type owner_local_pair;
  typedef typename ProcessGroup::process_id_type process_id_type;

  enum property_map_messages {
    /** A request to store a value in a property map. The message
     * contains a std::pair<key, data>.
     */
    property_map_put,

    /** A request to retrieve a particular value in a property
     *  map. The message contains a key. The owner of that key will
     *  reply with a value.
     */
    property_map_get,

    /** A request to update values stored on a remote processor. The
     * message contains a vector of keys for which the source
     * requests updated values. This message will only be transmitted
     * during synchronization.
     */
    property_map_multiget,

    /** A request to store values in a ghost cell. This message
     * contains a vector of key/value pairs corresponding to the
     * sequence of keys sent to the source processor.
     */
    property_map_multiget_reply,

    /** The payload containing a vector of local key-value pairs to be
     * put into the remote property map. A key-value std::pair will be
     * used to store each local key-value pair.
     */
    property_map_multiput
  };

  // Code from Joaquín M López Muñoz to work around unusual implementation of
  // std::pair in VC++ 10:
  template<typename First,typename Second>
  class pair_first_extractor {
    typedef std::pair<First,Second> value_type;

    public:
    typedef First result_type;
    const result_type& operator()(const value_type& x) const {
      return x.first;
    }

    result_type& operator()(value_type& x) const {
      return x.first;
    }
  };

 public:
  /// The type of the ghost cells
  typedef multi_index::multi_index_container<
            std::pair<key_type, value_type>,
            multi_index::indexed_by<
              multi_index::sequenced<>,
              multi_index::hashed_unique<
                pair_first_extractor<key_type, value_type>
              >
            >
          > ghost_cells_type;

  /// Iterator into the ghost cells
  typedef typename ghost_cells_type::iterator iterator;

  /// Key-based index into the ghost cells
  typedef typename ghost_cells_type::template nth_index<1>::type
    ghost_cells_key_index_type;

  /// Iterator into the ghost cells (by key)
  typedef typename ghost_cells_key_index_type::iterator key_iterator;

  /** The property map category.  A distributed property map cannot be
   * an Lvalue Property Map, because values on remote processes cannot
   * be addresses.
   */
  typedef typename detail::make_nonlvalue_property_map<
    (is_base_and_derived<lvalue_property_map_tag, local_category>::value
     || is_same<lvalue_property_map_tag, local_category>::value)>
    ::template apply<local_category>::type category;

  /** Default-construct a distributed property map.  This function
   * creates an initialized property map that must be assigned to a
   * valid value before being used. It is only provided here because
   * property maps must be Default Constructible.
   */
  distributed_property_map() {}

  /** Construct a distributed property map.  Builds a distributed
   * property map communicating over the given process group and using
   * the given local property map for storage. Since no reduction
   * operation is provided, the default reduction operation @c
   * basic_reduce<value_type> is used.
   */
  distributed_property_map(const ProcessGroup& pg, const GlobalMap& global,
                           const StorageMap& pm)
    : data(new data_t(pg, global, pm, basic_reduce<value_type>(), false))
  {
    typedef handle_message<basic_reduce<value_type> > Handler;

    data->ghost_cells.reset(new ghost_cells_type());
    Handler handler(data);
    data->process_group.replace_handler(handler, true);
    data->process_group.template get_receiver<Handler>()
      ->setup_triggers(data->process_group);
  }

  /** Construct a distributed property map.  Builds a distributed
   * property map communicating over the given process group and using
   * the given local property map for storage. The given @p reduce
   * parameter is used as the reduction operation.
   */
  template<typename Reduce>
  distributed_property_map(const ProcessGroup& pg, const GlobalMap& global,
                           const StorageMap& pm,
                           const Reduce& reduce);

  ~distributed_property_map();

  /// Set the reduce operation of the distributed property map.
  template<typename Reduce>
  void set_reduce(const Reduce& reduce);

  // Set the consistency model for the distributed property map
  void set_consistency_model(int model);

  // Get the consistency model
  int get_consistency_model() const { return data->model; }

  // Set the maximum number of ghost cells that we are allowed to
  // maintain. If 0, all ghost cells will be retained.
  void set_max_ghost_cells(std::size_t max_ghost_cells);

  // Clear out all ghost cells
  void clear();

  // Reset the values in all ghost cells to the default value
  void reset();

  // Flush all values destined for remote processors
  void flush();

  reference operator[](const key_type& key) const
  {
    owner_local_pair p = get(data->global, key);

    if (p.first == process_id(data->process_group)) {
      return data->storage[p.second];
    } else {
      return cell(key);
    }
  }

  process_group_type process_group() const
  {
    return data->process_group.base();
  }

  StorageMap&       base()       { return data->storage; }
  const StorageMap& base() const { return data->storage; }

  /** Sends a "put" request.
   * \internal
   *
   */
  void
  request_put(process_id_type p, const key_type& k, const value_type& v) const
  {
    send(data->process_group, p, property_map_put,
         boost::parallel::detail::make_untracked_pair(k, v));
  }

  /** Access the ghost cell for the given key.
   * \internal
   */
  value_type& cell(const key_type& k, bool request_if_missing = true) const;

  /** Perform synchronization
   * \internal
   */
  void do_synchronize();

  const GlobalMap& global() const { return data->global; }
  GlobalMap&       global()       { return data->global; }

  struct data_t
  {
    data_t(const ProcessGroup& pg, const GlobalMap& global,
           const StorageMap& pm, const function1<value_type, key_type>& dv,
           bool has_default_resolver)
      : process_group(pg), global(global), storage(pm),
        ghost_cells(), max_ghost_cells(1000000), get_default_value(dv),
        has_default_resolver(has_default_resolver), model(cm_forward) { }

    /// The process group
    ProcessGroup process_group;

    /// A mapping from the keys of this property map to the global
    /// descriptor.
    GlobalMap global;

    /// Local property map
    StorageMap storage;

    /// The ghost cells
    shared_ptr<ghost_cells_type> ghost_cells;

    /// The maximum number of ghost cells we are permitted to hold. If
    /// zero, we are permitted to have an infinite number of ghost
    /// cells.
    std::size_t max_ghost_cells;

    /// Default value for remote ghost cells, as defined by the
    /// reduction operation.
    function1<value_type, key_type> get_default_value;

    /// True if this resolver is the "default" resolver, meaning that
    /// we should not be able to get() a default value; it needs to be
    /// request()ed first.
    bool has_default_resolver;

    // Current consistency model
    int model;

    // Function that resets all of the ghost cells to their default
    // values. It knows the type of the resolver, so we can eliminate
    // a large number of calls through function pointers.
    void (data_t::*reset)();

    // Clear out all ghost cells
    void clear();

    // Flush all values destined for remote processors
    void flush();

    // Send out requests to "refresh" the values of ghost cells that
    // we're holding.
    void refresh_ghost_cells();

  private:
    template<typename Resolver> void do_reset();

    friend class distributed_property_map;
  };
  friend struct data_t;

  shared_ptr<data_t> data;

 private:
  // Prunes the least recently used ghost cells until we have @c
  // max_ghost_cells or fewer ghost cells.
  void prune_ghost_cells() const;

  /** Handles incoming messages.
   *
   * This function object is responsible for handling all incoming
   * messages for the distributed property map.
   */
  template<typename Reduce>
  struct handle_message
  {
    explicit handle_message(const shared_ptr<data_t>& data,
                            const Reduce& reduce = Reduce())
      : data_ptr(data), reduce(reduce) { }

    void operator()(process_id_type source, int tag);

    /// Individual message handlers
    void
    handle_put(int source, int tag,
               const boost::parallel::detail::untracked_pair<key_type, value_type>& data,
               trigger_receive_context);

    value_type
    handle_get(int source, int tag, const key_type& data,
               trigger_receive_context);

    void
    handle_multiget(int source, int tag,
                    const std::vector<key_type>& data,
                    trigger_receive_context);

    void
    handle_multiget_reply
      (int source, int tag,
       const std::vector<boost::parallel::detail::untracked_pair<key_type, value_type> >& msg,
       trigger_receive_context);

    void
    handle_multiput
      (int source, int tag,
       const std::vector<unsafe_pair<local_key_type, value_type> >& data,
       trigger_receive_context);

    void setup_triggers(process_group_type& pg);

  private:
    weak_ptr<data_t> data_ptr;
    Reduce reduce;
  };

  /* Sets up the next stage in a multi-stage synchronization, for
     bidirectional consistency. */
  struct on_synchronize
  {
    explicit on_synchronize(const shared_ptr<data_t>& data) : data_ptr(data) { }

    void operator()();

  private:
    weak_ptr<data_t> data_ptr;
  };
};

/* An implementation helper macro for the common case of naming
   distributed property maps with all of the normal template
   parameters. */
#define PBGL_DISTRIB_PMAP                                       \
  distributed_property_map<ProcessGroup, GlobalMap, StorageMap>

/* Request that the value for the given remote key be retrieved in
   the next synchronization round. */
template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline void
request(const PBGL_DISTRIB_PMAP& pm,
        typename PBGL_DISTRIB_PMAP::key_type const& key)
{
  if (get(pm.data->global, key).first != process_id(pm.data->process_group))
    pm.cell(key, false);
}

/** Get the value associated with a particular key.  Retrieves the
 * value associated with the given key. If the key denotes a
 * locally-owned object, it returns the value from the local property
 * map; if the key denotes a remotely-owned object, retrieves the
 * value of the ghost cell for that key, which may be the default
 * value provided by the reduce operation.
 *
 * Complexity: For a local key, O(1) get operations on the underlying
 * property map. For a non-local key, O(1) accesses to the ghost cells.
 */
template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline
typename PBGL_DISTRIB_PMAP::value_type
get(const PBGL_DISTRIB_PMAP& pm,
    typename PBGL_DISTRIB_PMAP::key_type const& key)
{
  using boost::get;

  typename property_traits<GlobalMap>::value_type p =
    get(pm.data->global, key);

  if (p.first == process_id(pm.data->process_group)) {
    return get(pm.data->storage, p.second);
  } else {
    return pm.cell(key);
  }
}

/** Put a value associated with the given key into the property map.
 * When the key denotes a locally-owned object, this operation updates
 * the underlying local property map. Otherwise, the local ghost cell
 * is updated and a "put" message is sent to the processor owning this
 * key.
 *
 * Complexity: For a local key, O(1) put operations on the underlying
 * property map. For a nonlocal key, O(1) accesses to the ghost cells
 * and will send O(1) messages of size O(sizeof(key) + sizeof(value)).
 */
template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
void
put(const PBGL_DISTRIB_PMAP& pm,
    typename PBGL_DISTRIB_PMAP::key_type const & key,
    typename PBGL_DISTRIB_PMAP::value_type const & value)
{
  using boost::put;

  typename property_traits<GlobalMap>::value_type p =
    get(pm.data->global, key);

  if (p.first == process_id(pm.data->process_group)) {
    put(pm.data->storage, p.second, value);
  } else {
    if (pm.data->model & cm_forward)
      pm.request_put(p.first, key, value);

    pm.cell(key, false) = value;
  }
}

/** Put a value associated with a given key into the local view of the
 * property map. This operation is equivalent to @c put, but with one
 * exception: no message will be sent to the owning processor in the
 * case of a remote update. The effect is that any value written via
 * @c local_put for a remote key may be overwritten in the next
 * synchronization round.
 */
template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
void
local_put(const PBGL_DISTRIB_PMAP& pm,
          typename PBGL_DISTRIB_PMAP::key_type const & key,
          typename PBGL_DISTRIB_PMAP::value_type const & value)
{
  using boost::put;

  typename property_traits<GlobalMap>::value_type p =
    get(pm.data->global, key);

  if (p.first == process_id(pm.data->process_group))
    put(pm.data->storage, p.second, value);
  else pm.cell(key, false) = value;
}

/** Cache the value associated with the given remote key. If the key
 *  is local, ignore the operation. */
template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline void
cache(const PBGL_DISTRIB_PMAP& pm,
      typename PBGL_DISTRIB_PMAP::key_type const & key,
      typename PBGL_DISTRIB_PMAP::value_type const & value)
{
  typename ProcessGroup::process_id_type id = get(pm.data->global, key).first;

  if (id != process_id(pm.data->process_group)) pm.cell(key, false) = value;
}

/// Synchronize the property map.
template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
void
synchronize(PBGL_DISTRIB_PMAP& pm)
{
  pm.do_synchronize();
}

/// Create a distributed property map.
template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline distributed_property_map<ProcessGroup, GlobalMap, StorageMap>
make_distributed_property_map(const ProcessGroup& pg, GlobalMap global,
                              StorageMap storage)
{
  typedef distributed_property_map<ProcessGroup, GlobalMap, StorageMap>
    result_type;
  return result_type(pg, global, storage);
}

/**
 * \overload
 */
template<typename ProcessGroup, typename GlobalMap, typename StorageMap,
         typename Reduce>
inline distributed_property_map<ProcessGroup, GlobalMap, StorageMap>
make_distributed_property_map(const ProcessGroup& pg, GlobalMap global,
                              StorageMap storage, Reduce reduce)
{
  typedef distributed_property_map<ProcessGroup, GlobalMap, StorageMap>
    result_type;
  return result_type(pg, global, storage, reduce);
}

} } // end namespace boost::parallel

#include <boost/property_map/parallel/impl/distributed_property_map.ipp>

#undef PBGL_DISTRIB_PMAP

#endif // BOOST_PARALLEL_DISTRIBUTED_PROPERTY_MAP_HPP

/* distributed_property_map.hpp
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
*/