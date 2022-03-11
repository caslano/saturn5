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