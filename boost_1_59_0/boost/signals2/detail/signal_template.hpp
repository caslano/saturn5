/*
  Template for Signa1, Signal2, ... classes that support signals
  with 1, 2, ... parameters

  Begin: 2007-01-23
*/
// Copyright Frank Mori Hess 2007-2008
//
// Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is included iteratively, and should not be protected from multiple inclusion

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
#define BOOST_SIGNALS2_NUM_ARGS BOOST_PP_ITERATION()
#else
#define BOOST_SIGNALS2_NUM_ARGS 1
#endif

// R, T1, T2, ..., TN, Combiner, Group, GroupCompare, SlotFunction, ExtendedSlotFunction, Mutex
#define BOOST_SIGNALS2_SIGNAL_TEMPLATE_INSTANTIATION \
  BOOST_SIGNALS2_SIGNATURE_TEMPLATE_INSTANTIATION(BOOST_SIGNALS2_NUM_ARGS), \
  Combiner, Group, GroupCompare, SlotFunction, ExtendedSlotFunction, Mutex

namespace boost
{
  namespace signals2
  {
    namespace detail
    {
      // helper for bound_extended_slot_function that handles specialization for void return
      template<typename R>
        class BOOST_SIGNALS2_BOUND_EXTENDED_SLOT_FUNCTION_INVOKER_N(BOOST_SIGNALS2_NUM_ARGS)
      {
      public:
        typedef R result_type;
        template<typename ExtendedSlotFunction BOOST_SIGNALS2_PP_COMMA_IF(BOOST_SIGNALS2_NUM_ARGS)
          BOOST_SIGNALS2_ARGS_TEMPLATE_DECL(BOOST_SIGNALS2_NUM_ARGS)>
          result_type operator()(ExtendedSlotFunction &func, const connection &conn
            BOOST_SIGNALS2_PP_COMMA_IF(BOOST_SIGNALS2_NUM_ARGS)
            BOOST_SIGNALS2_FULL_FORWARD_ARGS(BOOST_SIGNALS2_NUM_ARGS)) const
        {
          return func(conn BOOST_SIGNALS2_PP_COMMA_IF(BOOST_SIGNALS2_NUM_ARGS)
            BOOST_SIGNALS2_FORWARDED_ARGS(BOOST_SIGNALS2_NUM_ARGS));
        }
      };
#ifdef BOOST_NO_VOID_RETURNS
      template<>
        class BOOST_SIGNALS2_BOUND_EXTENDED_SLOT_FUNCTION_INVOKER_N(BOOST_SIGNALS2_NUM_ARGS)<void>
      {
      public:
        typedef result_type_wrapper<void>::type result_type;
        template<typename ExtendedSlotFunction BOOST_SIGNALS2_PP_COMMA_IF(BOOST_SIGNALS2_NUM_ARGS)
          BOOST_SIGNALS2_ARGS_TEMPLATE_DECL(BOOST_SIGNALS2_NUM_ARGS)>
          result_type operator()(ExtendedSlotFunction &func, const connection &conn
            BOOST_SIGNALS2_PP_COMMA_IF(BOOST_SIGNALS2_NUM_ARGS)
            BOOST_SIGNALS2_FULL_FORWARD_ARGS(BOOST_SIGNALS2_NUM_ARGS)) const
        {
          func(conn BOOST_SIGNALS2_PP_COMMA_IF(BOOST_SIGNALS2_NUM_ARGS)
            BOOST_SIGNALS2_FORWARDED_ARGS(BOOST_SIGNALS2_NUM_ARGS));
          return result_type();
        }
      };
#endif
// wrapper around an signalN::extended_slot_function which binds the
// connection argument so it looks like a normal
// signalN::slot_function

      template<typename ExtendedSlotFunction>
        class BOOST_SIGNALS2_BOUND_EXTENDED_SLOT_FUNCTION_N(BOOST_SIGNALS2_NUM_ARGS)
      {
      public:
        typedef typename result_type_wrapper<typename ExtendedSlotFunction::result_type>::type result_type;
        BOOST_SIGNALS2_BOUND_EXTENDED_SLOT_FUNCTION_N(BOOST_SIGNALS2_NUM_ARGS)(const ExtendedSlotFunction &fun):
          _fun(fun), _connection(new connection)
        {}
        void set_connection(const connection &conn)
        {
          *_connection = conn;
        }

#if BOOST_SIGNALS2_NUM_ARGS > 0
        template<BOOST_SIGNALS2_ARGS_TEMPLATE_DECL(BOOST_SIGNALS2_NUM_ARGS)>
#endif // BOOST_SIGNALS2_NUM_ARGS > 0
          result_type operator()(BOOST_SIGNALS2_FULL_FORWARD_ARGS(BOOST_SIGNALS2_NUM_ARGS))
        {
          return BOOST_SIGNALS2_BOUND_EXTENDED_SLOT_FUNCTION_INVOKER_N(BOOST_SIGNALS2_NUM_ARGS)
            <typename ExtendedSlotFunction::result_type>()
            (_fun, *_connection BOOST_SIGNALS2_PP_COMMA_IF(BOOST_SIGNALS2_NUM_ARGS)
              BOOST_SIGNALS2_FORWARDED_ARGS(BOOST_SIGNALS2_NUM_ARGS));
        }
        // const overload
#if BOOST_SIGNALS2_NUM_ARGS > 0
        template<BOOST_SIGNALS2_ARGS_TEMPLATE_DECL(BOOST_SIGNALS2_NUM_ARGS)>
#endif // BOOST_SIGNALS2_NUM_ARGS > 0
          result_type operator()(BOOST_SIGNALS2_FULL_FORWARD_ARGS(BOOST_SIGNALS2_NUM_ARGS)) const
        {
          return BOOST_SIGNALS2_BOUND_EXTENDED_SLOT_FUNCTION_INVOKER_N(BOOST_SIGNALS2_NUM_ARGS)
            <typename ExtendedSlotFunction::result_type>()
            (_fun, *_connection BOOST_SIGNALS2_PP_COMMA_IF(BOOST_SIGNALS2_NUM_ARGS)
              BOOST_SIGNALS2_FORWARDED_ARGS(BOOST_SIGNALS2_NUM_ARGS));
        }
        template<typename T>
          bool operator==(const T &other) const
        {
          return _fun == other;
        }
      private:
        BOOST_SIGNALS2_BOUND_EXTENDED_SLOT_FUNCTION_N(BOOST_SIGNALS2_NUM_ARGS)()
        {}

        ExtendedSlotFunction _fun;
        boost::shared_ptr<connection> _connection;
      };

      template<BOOST_SIGNALS2_SIGNAL_TEMPLATE_DECL(BOOST_SIGNALS2_NUM_ARGS)>
        class BOOST_SIGNALS2_SIGNAL_IMPL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS);

      template<BOOST_SIGNALS2_SIGNAL_TEMPLATE_SPECIALIZATION_DECL(BOOST_SIGNALS2_NUM_ARGS)>
      class BOOST_SIGNALS2_SIGNAL_IMPL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS) BOOST_SIGNALS2_SIGNAL_TEMPLATE_SPECIALIZATION
      {
      public:
        typedef SlotFunction slot_function_type;
        // typedef slotN<Signature, SlotFunction> slot_type;
        typedef BOOST_SIGNALS2_SLOT_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)
          <BOOST_SIGNALS2_SIGNATURE_TEMPLATE_INSTANTIATION(BOOST_SIGNALS2_NUM_ARGS),
          slot_function_type> slot_type;
        typedef ExtendedSlotFunction extended_slot_function_type;
        // typedef slotN+1<R, const connection &, T1, T2, ..., TN, extended_slot_function_type> extended_slot_type;
        typedef BOOST_SIGNALS2_EXTENDED_SLOT_TYPE(BOOST_SIGNALS2_NUM_ARGS) extended_slot_type;
        typedef typename nonvoid<typename slot_function_type::result_type>::type nonvoid_slot_result_type;
      private:
#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
        class slot_invoker;
#else // BOOST_NO_CXX11_VARIADIC_TEMPLATES
        typedef variadic_slot_invoker<nonvoid_slot_result_type, Args...> slot_invoker;
#endif // BOOST_NO_CXX11_VARIADIC_TEMPLATES
        typedef slot_call_iterator_cache<nonvoid_slot_result_type, slot_invoker> slot_call_iterator_cache_type;
        typedef typename group_key<Group>::type group_key_type;
        typedef shared_ptr<connection_body<group_key_type, slot_type, Mutex> > connection_body_type;
        typedef grouped_list<Group, GroupCompare, connection_body_type> connection_list_type;
        typedef BOOST_SIGNALS2_BOUND_EXTENDED_SLOT_FUNCTION_N(BOOST_SIGNALS2_NUM_ARGS)<extended_slot_function_type>
          bound_extended_slot_function_type;
      public:
        typedef Combiner combiner_type;
        typedef typename result_type_wrapper<typename combiner_type::result_type>::type result_type;
        typedef Group group_type;
        typedef GroupCompare group_compare_type;
        typedef typename detail::slot_call_iterator_t<slot_invoker,
          typename connection_list_type::iterator, connection_body<group_key_type, slot_type, Mutex> > slot_call_iterator;

        BOOST_SIGNALS2_SIGNAL_IMPL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)(const combiner_type &combiner_arg,
          const group_compare_type &group_compare):
          _shared_state(new invocation_state(connection_list_type(group_compare), combiner_arg)),
          _garbage_collector_it(_shared_state->connection_bodies().end()),
          _mutex(new mutex_type())
        {}
        // connect slot
        connection connect(const slot_type &slot, connect_position position = at_back)
        {
          garbage_collecting_lock<mutex_type> lock(*_mutex);
          return nolock_connect(lock, slot, position);
        }
        connection connect(const group_type &group,
          const slot_type &slot, connect_position position = at_back)
        {
          garbage_collecting_lock<mutex_type> lock(*_mutex);
          return nolock_connect(lock, group, slot, position);
        }
        // connect extended slot
        connection connect_extended(const extended_slot_type &ext_slot, connect_position position = at_back)
        {
          garbage_collecting_lock<mutex_type> lock(*_mutex);
          bound_extended_slot_function_type bound_slot(ext_slot.slot_function());
          slot_type slot = replace_slot_function<slot_type>(ext_slot, bound_slot);
          connection conn = nolock_connect(lock, slot, position);
          bound_slot.set_connection(conn);
          return conn;
        }
        connection connect_extended(const group_type &group,
          const extended_slot_type &ext_slot, connect_position position = at_back)
        {
          garbage_collecting_lock<Mutex> lock(*_mutex);
          bound_extended_slot_function_type bound_slot(ext_slot.slot_function());
          slot_type slot = replace_slot_function<slot_type>(ext_slot, bound_slot);
          connection conn = nolock_connect(lock, group, slot, position);
          bound_slot.set_connection(conn);
          return conn;
        }
        // disconnect slot(s)
        void disconnect_all_slots()
        {
          shared_ptr<invocation_state> local_state =
            get_readable_state();
          typename connection_list_type::iterator it;
          for(it = local_state->connection_bodies().begin();
            it != local_state->connection_bodies().end(); ++it)
          {
            (*it)->disconnect();
          }
        }
        void disconnect(const group_type &group)
        {
          shared_ptr<invocation_state> local_state =
            get_readable_state();
          group_key_type group_key(grouped_slots, group);
          typename connection_list_type::iterator it;
          typename connection_list_type::iterator end_it =
            local_state->connection_bodies().upper_bound(group_key);
          for(it = local_state->connection_bodies().lower_bound(group_key);
            it != end_it; ++it)
          {
            (*it)->disconnect();
          }
        }
        template <typename T>
        void disconnect(const T &slot)
        {
          typedef mpl::bool_<(is_convertible<T, group_type>::value)> is_group;
          do_disconnect(slot, is_group());
        }
        // emit signal
        result_type operator ()(BOOST_SIGNALS2_SIGNATURE_FULL_ARGS(BOOST_SIGNALS2_NUM_ARGS))
        {
          shared_ptr<invocation_state> local_state;
          typename connection_list_type::iterator it;
          {
            garbage_collecting_lock<mutex_type> list_lock(*_mutex);
            // only clean up if it is safe to do so
            if(_shared_state.unique())
              nolock_cleanup_connections(list_lock, false, 1);
            /* Make a local copy of _shared_state while holding mutex, so we are
            thread safe against the combiner or connection list getting modified
            during invocation. */
            local_state = _shared_state;
          }
          slot_invoker invoker = slot_invoker(BOOST_SIGNALS2_SIGNATURE_ARG_NAMES(BOOST_SIGNALS2_NUM_ARGS));
          slot_call_iterator_cache_type cache(invoker);
          invocation_janitor janitor(cache, *this, &local_state->connection_bodies());
          return detail::combiner_invoker<typename combiner_type::result_type>()
            (
              local_state->combiner(),
              slot_call_iterator(local_state->connection_bodies().begin(), local_state->connection_bodies().end(), cache),
              slot_call_iterator(local_state->connection_bodies().end(), local_state->connection_bodies().end(), cache)
            );
        }
        result_type operator ()(BOOST_SIGNALS2_SIGNATURE_FULL_ARGS(BOOST_SIGNALS2_NUM_ARGS)) const
        {
          shared_ptr<invocation_state> local_state;
          typename connection_list_type::iterator it;
          {
            garbage_collecting_lock<mutex_type> list_lock(*_mutex);
            // only clean up if it is safe to do so
            if(_shared_state.unique())
              nolock_cleanup_connections(list_lock, false, 1);
            /* Make a local copy of _shared_state while holding mutex, so we are
            thread safe against the combiner or connection list getting modified
            during invocation. */
            local_state = _shared_state;
          }
          slot_invoker invoker = slot_invoker(BOOST_SIGNALS2_SIGNATURE_ARG_NAMES(BOOST_SIGNALS2_NUM_ARGS));
          slot_call_iterator_cache_type cache(invoker);
          invocation_janitor janitor(cache, *this, &local_state->connection_bodies());
          return detail::combiner_invoker<typename combiner_type::result_type>()
            (
              local_state->combiner(),
              slot_call_iterator(local_state->connection_bodies().begin(), local_state->connection_bodies().end(), cache),
              slot_call_iterator(local_state->connection_bodies().end(), local_state->connection_bodies().end(), cache)
            );
        }
        std::size_t num_slots() const
        {
          shared_ptr<invocation_state> local_state =
            get_readable_state();
          typename connection_list_type::iterator it;
          std::size_t count = 0;
          for(it = local_state->connection_bodies().begin();
            it != local_state->connection_bodies().end(); ++it)
          {
            if((*it)->connected()) ++count;
          }
          return count;
        }
        bool empty() const
        {
          shared_ptr<invocation_state> local_state =
            get_readable_state();
          typename connection_list_type::iterator it;
          for(it = local_state->connection_bodies().begin();
            it != local_state->connection_bodies().end(); ++it)
          {
            if((*it)->connected()) return false;
          }
          return true;
        }
        combiner_type combiner() const
        {
          unique_lock<mutex_type> lock(*_mutex);
          return _shared_state->combiner();
        }
        void set_combiner(const combiner_type &combiner_arg)
        {
          unique_lock<mutex_type> lock(*_mutex);
          if(_shared_state.unique())
            _shared_state->combiner() = combiner_arg;
          else
            _shared_state.reset(new invocation_state(*_shared_state, combiner_arg));
        }
      private:
        typedef Mutex mutex_type;

        // slot_invoker is passed to slot_call_iterator_t to run slots
#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
        class slot_invoker
        {
        public:
          typedef nonvoid_slot_result_type result_type;
// typename add_reference<Tn>::type
#define BOOST_SIGNALS2_ADD_REF_TYPE(z, n, data) \
  typename add_reference<BOOST_PP_CAT(T, BOOST_PP_INC(n))>::type
// typename add_reference<Tn>::type argn
#define BOOST_SIGNALS2_ADD_REF_ARG(z, n, data) \
  BOOST_SIGNALS2_ADD_REF_TYPE(~, n, ~) \
  BOOST_SIGNALS2_SIGNATURE_ARG_NAME(~, n, ~)
// typename add_reference<T1>::type arg1, typename add_reference<T2>::type arg2, ..., typename add_reference<Tn>::type argn
#define BOOST_SIGNALS2_ADD_REF_ARGS(arity) \
  BOOST_PP_ENUM(arity, BOOST_SIGNALS2_ADD_REF_ARG, ~)
          slot_invoker(BOOST_SIGNALS2_ADD_REF_ARGS(BOOST_SIGNALS2_NUM_ARGS)) BOOST_PP_EXPR_IF(BOOST_SIGNALS2_NUM_ARGS, :)
#undef BOOST_SIGNALS2_ADD_REF_ARGS

// m_argn
#define BOOST_SIGNALS2_M_ARG_NAME(z, n, data) BOOST_PP_CAT(m_arg, BOOST_PP_INC(n))
// m_argn ( argn )
#define BOOST_SIGNALS2_MISC_STATEMENT(z, n, data) \
  BOOST_SIGNALS2_M_ARG_NAME(~, n, ~) ( BOOST_SIGNALS2_SIGNATURE_ARG_NAME(~, n, ~) )
// m_arg1(arg1), m_arg2(arg2), ..., m_argn(argn)
            BOOST_PP_ENUM(BOOST_SIGNALS2_NUM_ARGS, BOOST_SIGNALS2_MISC_STATEMENT, ~)
#undef BOOST_SIGNALS2_MISC_STATEMENT
          {}
          result_type operator ()(const connection_body_type &connectionBody) const
          {
            return m_invoke<typename slot_type::result_type>(connectionBody);
          }
        private:
          // declare assignment operator private since this class might have reference or const members
          slot_invoker & operator=(const slot_invoker &);

#define BOOST_SIGNALS2_ADD_REF_M_ARG_STATEMENT(z, n, data) \
  BOOST_SIGNALS2_ADD_REF_TYPE(~, n, ~) BOOST_SIGNALS2_M_ARG_NAME(~, n, ~) ;
          BOOST_PP_REPEAT(BOOST_SIGNALS2_NUM_ARGS, BOOST_SIGNALS2_ADD_REF_M_ARG_STATEMENT, ~)
#undef BOOST_SIGNALS2_ADD_REF_M_ARG_STATEMENT
#undef BOOST_SIGNALS2_ADD_REF_ARG
#undef BOOST_SIGNALS2_ADD_REF_TYPE

// m_arg1, m_arg2, ..., m_argn
#define BOOST_SIGNALS2_M_ARG_NAMES(arity) BOOST_PP_ENUM(arity, BOOST_SIGNALS2_M_ARG_NAME, ~)
          template<typename SlotResultType>
          result_type m_invoke(const connection_body_type &connectionBody,
            typename boost::enable_if<boost::is_void<SlotResultType> >::type * = 0) const
          {
            connectionBody->slot().slot_function()(BOOST_SIGNALS2_M_ARG_NAMES(BOOST_SIGNALS2_NUM_ARGS));
            return void_type();
          }
          template<typename SlotResultType>
          result_type m_invoke(const connection_body_type &connectionBody, 
            typename boost::disable_if<boost::is_void<SlotResultType> >::type * = 0) const
          {
            return connectionBody->slot().slot_function()(BOOST_SIGNALS2_M_ARG_NAMES(BOOST_SIGNALS2_NUM_ARGS));
          }
        };
#undef BOOST_SIGNALS2_M_ARG_NAMES
#undef BOOST_SIGNALS2_M_ARG_NAME

#endif // BOOST_NO_CXX11_VARIADIC_TEMPLATES
        // a struct used to optimize (minimize) the number of shared_ptrs that need to be created
        // inside operator()
        class invocation_state
        {
        public:
          invocation_state(const connection_list_type &connections_in,
            const combiner_type &combiner_in): _connection_bodies(new connection_list_type(connections_in)),
            _combiner(new combiner_type(combiner_in))
          {}
          invocation_state(const invocation_state &other, const connection_list_type &connections_in):
            _connection_bodies(new connection_list_type(connections_in)),
            _combiner(other._combiner)
          {}
          invocation_state(const invocation_state &other, const combiner_type &combiner_in):
            _connection_bodies(other._connection_bodies),
            _combiner(new combiner_type(combiner_in))
          {}
          connection_list_type & connection_bodies() { return *_connection_bodies; }
          const connection_list_type & connection_bodies() const { return *_connection_bodies; }
          combiner_type & combiner() { return *_combiner; }
          const combiner_type & combiner() const { return *_combiner; }
        private:
          invocation_state(const invocation_state &);

          shared_ptr<connection_list_type> _connection_bodies;
          shared_ptr<combiner_type> _combiner;
        };
        // Destructor of invocation_janitor does some cleanup when a signal invocation completes.
        // Code can't be put directly in signal's operator() due to complications from void return types.
        class invocation_janitor: noncopyable
        {
        public:
          typedef BOOST_SIGNALS2_SIGNAL_IMPL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS) signal_type;
          invocation_janitor
          (
            const slot_call_iterator_cache_type &cache,
            const signal_type &sig,
            const connection_list_type *connection_bodies
          ):_cache(cache), _sig(sig), _connection_bodies(connection_bodies)
          {}
          ~invocation_janitor()
          {
            // force a full cleanup of disconnected slots if there are too many
            if(_cache.disconnected_slot_count > _cache.connected_slot_count)
            {
              _sig.force_cleanup_connections(_connection_bodies);
            }
          }
        private:
          const slot_call_iterator_cache_type &_cache;
          const signal_type &_sig;
          const connection_list_type *_connection_bodies;
        };

        // clean up disconnected connections
        void nolock_cleanup_connections_from(garbage_collecting_lock<mutex_type> &lock,
          bool grab_tracked,
          const typename connection_list_type::iterator &begin, unsigned count = 0) const
        {
          BOOST_ASSERT(_shared_state.unique());
          typename connection_list_type::iterator it;
          unsigned i;
          for(it = begin, i = 0;
            it != _shared_state->connection_bodies().end() && (count == 0 || i < count);
            ++i)
          {
            bool connected;
            if(grab_tracked)
              (*it)->disconnect_expired_slot(lock);
            connected = (*it)->nolock_nograb_connected();
            if(connected == false)
            {
              it = _shared_state->connection_bodies().erase((*it)->group_key(), it);
            }else
            {
              ++it;
            }
          }
          _garbage_collector_it = it;
        }
        // clean up a few connections in constant time
        void nolock_cleanup_connections(garbage_collecting_lock<mutex_type> &lock,
          bool grab_tracked, unsigned count) const
        {
          BOOST_ASSERT(_shared_state.unique());
          typename connection_list_type::iterator begin;
          if(_garbage_collector_it == _shared_state->connection_bodies().end())
          {
            begin = _shared_state->connection_bodies().begin();
          }else
          {
            begin = _garbage_collector_it;
          }
          nolock_cleanup_connections_from(lock, grab_tracked, begin, count);
        }
        /* Make a new copy of the slot list if it is currently being read somewhere else
        */
        void nolock_force_unique_connection_list(garbage_collecting_lock<mutex_type> &lock)
        {
          if(_shared_state.unique() == false)
          {
            _shared_state.reset(new invocation_state(*_shared_state, _shared_state->connection_bodies()));
            nolock_cleanup_connections_from(lock, true, _shared_state->connection_bodies().begin());
          }else
          {
            /* We need to try and check more than just 1 connection here to avoid corner
            cases where certain repeated connect/disconnect patterns cause the slot
            list to grow without limit. */
            nolock_cleanup_connections(lock, true, 2);
          }
        }
        // force a full cleanup of the connection list
        void force_cleanup_connections(const connection_list_type *connection_bodies) const
        {
          garbage_collecting_lock<mutex_type> list_lock(*_mutex);
          // if the connection list passed in as a parameter is no longer in use,
          // we don't need to do any cleanup.
          if(&_shared_state->connection_bodies() != connection_bodies)
          {
            return;
          }
          if(_shared_state.unique() == false)
          {
            _shared_state.reset(new invocation_state(*_shared_state, _shared_state->connection_bodies()));
          }
          nolock_cleanup_connections_from(list_lock, false, _shared_state->connection_bodies().begin());
        }
        shared_ptr<invocation_state> get_readable_state() const
        {
          unique_lock<mutex_type> list_lock(*_mutex);
          return _shared_state;
        }
        connection_body_type create_new_connection(garbage_collecting_lock<mutex_type> &lock,
          const slot_type &slot)
        {
          nolock_force_unique_connection_list(lock);
          return connection_body_type(new connection_body<group_key_type, slot_type, Mutex>(slot, _mutex));
        }
        void do_disconnect(const group_type &group, mpl::bool_<true> /* is_group */)
        {
          disconnect(group);
        }
        template<typename T>
        void do_disconnect(const T &slot, mpl::bool_<false> /* is_group */)
        {
          shared_ptr<invocation_state> local_state =
            get_readable_state();
          typename connection_list_type::iterator it;
          for(it = local_state->connection_bodies().begin();
            it != local_state->connection_bodies().end(); ++it)
          {
            garbage_collecting_lock<connection_body_base> lock(**it);
            if((*it)->nolock_nograb_connected() == false) continue;
            if((*it)->slot().slot_function() == slot)
            {
              (*it)->nolock_disconnect(lock);
            }else
            {
              // check for wrapped extended slot
              bound_extended_slot_function_type *fp;
              fp = (*it)->slot().slot_function().template target<bound_extended_slot_function_type>();
              if(fp && *fp == slot)
              {
                (*it)->nolock_disconnect(lock);
              }
            }
          }
        }
        // connect slot
        connection nolock_connect(garbage_collecting_lock<mutex_type> &lock,
          const slot_type &slot, connect_position position)
        {
          connection_body_type newConnectionBody =
            create_new_connection(lock, slot);
          group_key_type group_key;
          if(position == at_back)
          {
            group_key.first = back_ungrouped_slots;
            _shared_state->connection_bodies().push_back(group_key, newConnectionBody);
          }else
          {
            group_key.first = front_ungrouped_slots;
            _shared_state->connection_bodies().push_front(group_key, newConnectionBody);
          }
          newConnectionBody->set_group_key(group_key);
          return connection(newConnectionBody);
        }
        connection nolock_connect(garbage_collecting_lock<mutex_type> &lock,
          const group_type &group,
          const slot_type &slot, connect_position position)
        {
          connection_body_type newConnectionBody =
            create_new_connection(lock, slot);
          // update map to first connection body in group if needed
          group_key_type group_key(grouped_slots, group);
          newConnectionBody->set_group_key(group_key);
          if(position == at_back)
          {
            _shared_state->connection_bodies().push_back(group_key, newConnectionBody);
          }else  // at_front
          {
            _shared_state->connection_bodies().push_front(group_key, newConnectionBody);
          }
          return connection(newConnectionBody);
        }

        // _shared_state is mutable so we can do force_cleanup_connections during a const invocation
        mutable shared_ptr<invocation_state> _shared_state;
        mutable typename connection_list_type::iterator _garbage_collector_it;
        // connection list mutex must never be locked when attempting a blocking lock on a slot,
        // or you could deadlock.
        const boost::shared_ptr<mutex_type> _mutex;
      };

      template<BOOST_SIGNALS2_SIGNAL_TEMPLATE_DECL(BOOST_SIGNALS2_NUM_ARGS)>
        class BOOST_SIGNALS2_WEAK_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS);
    }

    template<BOOST_SIGNALS2_SIGNAL_TEMPLATE_DEFAULTED_DECL(BOOST_SIGNALS2_NUM_ARGS)>
      class BOOST_SIGNALS2_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS);

    template<BOOST_SIGNALS2_SIGNAL_TEMPLATE_SPECIALIZATION_DECL(BOOST_SIGNALS2_NUM_ARGS)>
    class BOOST_SIGNALS2_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)
      BOOST_SIGNALS2_SIGNAL_TEMPLATE_SPECIALIZATION: public signal_base,
      public detail::BOOST_SIGNALS2_STD_FUNCTIONAL_BASE
    {
      typedef detail::BOOST_SIGNALS2_SIGNAL_IMPL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)
        <BOOST_SIGNALS2_SIGNAL_TEMPLATE_INSTANTIATION> impl_class;
    public:
      typedef detail::BOOST_SIGNALS2_WEAK_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)
        <BOOST_SIGNALS2_SIGNAL_TEMPLATE_INSTANTIATION> weak_signal_type;
      friend class detail::BOOST_SIGNALS2_WEAK_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)
        <BOOST_SIGNALS2_SIGNAL_TEMPLATE_INSTANTIATION>;

      typedef SlotFunction slot_function_type;
      // typedef slotN<Signature, SlotFunction> slot_type;
      typedef typename impl_class::slot_type slot_type;
      typedef typename impl_class::extended_slot_function_type extended_slot_function_type;
      typedef typename impl_class::extended_slot_type extended_slot_type;
      typedef typename slot_function_type::result_type slot_result_type;
      typedef Combiner combiner_type;
      typedef typename impl_class::result_type result_type;
      typedef Group group_type;
      typedef GroupCompare group_compare_type;
      typedef typename impl_class::slot_call_iterator
        slot_call_iterator;
      typedef typename mpl::identity<BOOST_SIGNALS2_SIGNATURE_FUNCTION_TYPE(BOOST_SIGNALS2_NUM_ARGS)>::type signature_type;

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES

// typedef Tn argn_type;
#define BOOST_SIGNALS2_MISC_STATEMENT(z, n, data) \
  typedef BOOST_PP_CAT(T, BOOST_PP_INC(n)) BOOST_PP_CAT(BOOST_PP_CAT(arg, BOOST_PP_INC(n)), _type);
      BOOST_PP_REPEAT(BOOST_SIGNALS2_NUM_ARGS, BOOST_SIGNALS2_MISC_STATEMENT, ~)
#undef BOOST_SIGNALS2_MISC_STATEMENT
#if BOOST_SIGNALS2_NUM_ARGS == 1
      typedef arg1_type argument_type;
#elif BOOST_SIGNALS2_NUM_ARGS == 2
      typedef arg1_type first_argument_type;
      typedef arg2_type second_argument_type;
#endif

      template<unsigned n> class arg : public
        detail::BOOST_SIGNALS2_PREPROCESSED_ARG_N_TYPE_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)
        <n BOOST_SIGNALS2_PP_COMMA_IF(BOOST_SIGNALS2_NUM_ARGS)
        BOOST_SIGNALS2_ARGS_TEMPLATE_INSTANTIATION(BOOST_SIGNALS2_NUM_ARGS)>
      {};

      BOOST_STATIC_CONSTANT(int, arity = BOOST_SIGNALS2_NUM_ARGS);

#else // BOOST_NO_CXX11_VARIADIC_TEMPLATES

      template<unsigned n> class arg
      {
      public:
        typedef typename detail::variadic_arg_type<n, Args...>::type type;
      };
      BOOST_STATIC_CONSTANT(int, arity = sizeof...(Args));

#endif // BOOST_NO_CXX11_VARIADIC_TEMPLATES

      BOOST_SIGNALS2_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)(const combiner_type &combiner_arg = combiner_type(),
        const group_compare_type &group_compare = group_compare_type()):
        _pimpl(new impl_class(combiner_arg, group_compare))
      {}
      virtual ~BOOST_SIGNALS2_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)()
      {
      }
      
      //move support
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
      BOOST_SIGNALS2_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)(
        BOOST_SIGNALS2_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS) && other) BOOST_NOEXCEPT
      {
        using std::swap;
        swap(_pimpl, other._pimpl);
      }
      
      BOOST_SIGNALS2_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS) & 
        operator=(BOOST_SIGNALS2_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS) && rhs) BOOST_NOEXCEPT
      {
        if(this == &rhs)
        {
          return *this;
        }
        _pimpl.reset();
        using std::swap;
        swap(_pimpl, rhs._pimpl);
        return *this;
      }
#endif // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
      
      connection connect(const slot_type &slot, connect_position position = at_back)
      {
        return (*_pimpl).connect(slot, position);
      }
      connection connect(const group_type &group,
        const slot_type &slot, connect_position position = at_back)
      {
        return (*_pimpl).connect(group, slot, position);
      }
      connection connect_extended(const extended_slot_type &slot, connect_position position = at_back)
      {
        return (*_pimpl).connect_extended(slot, position);
      }
      connection connect_extended(const group_type &group,
        const extended_slot_type &slot, connect_position position = at_back)
      {
        return (*_pimpl).connect_extended(group, slot, position);
      }
      void disconnect_all_slots()
      {
        (*_pimpl).disconnect_all_slots();
      }
      void disconnect(const group_type &group)
      {
        (*_pimpl).disconnect(group);
      }
      template <typename T>
      void disconnect(const T &slot)
      {
        (*_pimpl).disconnect(slot);
      }
      result_type operator ()(BOOST_SIGNALS2_SIGNATURE_FULL_ARGS(BOOST_SIGNALS2_NUM_ARGS))
      {
        return (*_pimpl)(BOOST_SIGNALS2_SIGNATURE_ARG_NAMES(BOOST_SIGNALS2_NUM_ARGS));
      }
      result_type operator ()(BOOST_SIGNALS2_SIGNATURE_FULL_ARGS(BOOST_SIGNALS2_NUM_ARGS)) const
      {
        return (*_pimpl)(BOOST_SIGNALS2_SIGNATURE_ARG_NAMES(BOOST_SIGNALS2_NUM_ARGS));
      }
      std::size_t num_slots() const
      {
        return (*_pimpl).num_slots();
      }
      bool empty() const
      {
        return (*_pimpl).empty();
      }
      combiner_type combiner() const
      {
        return (*_pimpl).combiner();
      }
      void set_combiner(const combiner_type &combiner_arg)
      {
        return (*_pimpl).set_combiner(combiner_arg);
      }
      void swap(BOOST_SIGNALS2_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS) & other) BOOST_NOEXCEPT
      {
        using std::swap;
        swap(_pimpl, other._pimpl);
      }
    protected:
      virtual shared_ptr<void> lock_pimpl() const
      {
        return _pimpl;
      }
    private:
      shared_ptr<impl_class>
        _pimpl;
    };

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
    // free swap function for signalN classes, findable by ADL
    template<BOOST_SIGNALS2_SIGNAL_TEMPLATE_DECL(BOOST_SIGNALS2_NUM_ARGS)>
      void swap(
        BOOST_SIGNALS2_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS) <BOOST_SIGNALS2_SIGNAL_TEMPLATE_INSTANTIATION> &sig1,
        BOOST_SIGNALS2_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS) <BOOST_SIGNALS2_SIGNAL_TEMPLATE_INSTANTIATION> &sig2 ) BOOST_NOEXCEPT
    {
      sig1.swap(sig2);
    }
#endif

    namespace detail
    {
      // wrapper class for storing other signals as slots with automatic lifetime tracking
      template<BOOST_SIGNALS2_SIGNAL_TEMPLATE_DECL(BOOST_SIGNALS2_NUM_ARGS)>
        class BOOST_SIGNALS2_WEAK_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS);

      template<BOOST_SIGNALS2_SIGNAL_TEMPLATE_SPECIALIZATION_DECL(BOOST_SIGNALS2_NUM_ARGS)>
        class BOOST_SIGNALS2_WEAK_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)
        BOOST_SIGNALS2_SIGNAL_TEMPLATE_SPECIALIZATION
      {
      public:
        typedef typename BOOST_SIGNALS2_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)
          <BOOST_SIGNALS2_SIGNAL_TEMPLATE_INSTANTIATION>::result_type
          result_type;

        BOOST_SIGNALS2_WEAK_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)
          (const BOOST_SIGNALS2_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)
          <BOOST_SIGNALS2_SIGNAL_TEMPLATE_INSTANTIATION>
          &signal):
          _weak_pimpl(signal._pimpl)
        {}
        result_type operator ()(BOOST_SIGNALS2_SIGNATURE_FULL_ARGS(BOOST_SIGNALS2_NUM_ARGS))
        {
          shared_ptr<detail::BOOST_SIGNALS2_SIGNAL_IMPL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)
            <BOOST_SIGNALS2_SIGNAL_TEMPLATE_INSTANTIATION> >
            shared_pimpl(_weak_pimpl.lock());
          return (*shared_pimpl)(BOOST_SIGNALS2_SIGNATURE_ARG_NAMES(BOOST_SIGNALS2_NUM_ARGS));
        }
        result_type operator ()(BOOST_SIGNALS2_SIGNATURE_FULL_ARGS(BOOST_SIGNALS2_NUM_ARGS)) const
        {
          shared_ptr<detail::BOOST_SIGNALS2_SIGNAL_IMPL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)
            <BOOST_SIGNALS2_SIGNAL_TEMPLATE_INSTANTIATION> >
            shared_pimpl(_weak_pimpl.lock());
          return (*shared_pimpl)(BOOST_SIGNALS2_SIGNATURE_ARG_NAMES(BOOST_SIGNALS2_NUM_ARGS));
        }
      private:
        boost::weak_ptr<detail::BOOST_SIGNALS2_SIGNAL_IMPL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)
          <BOOST_SIGNALS2_SIGNAL_TEMPLATE_INSTANTIATION> > _weak_pimpl;
      };

#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
      template<int arity, typename Signature>
        class extended_signature: public variadic_extended_signature<Signature>
      {};
#else // BOOST_NO_CXX11_VARIADIC_TEMPLATES
      template<int arity, typename Signature>
        class extended_signature;
      // partial template specialization
      template<typename Signature>
        class extended_signature<BOOST_SIGNALS2_NUM_ARGS, Signature>
      {
      public:
// typename function_traits<Signature>::result_type (
// const boost::signals2::connection &,
// typename function_traits<Signature>::arg1_type,
// typename function_traits<Signature>::arg2_type,
// ...,
// typename function_traits<Signature>::argn_type)
#define BOOST_SIGNALS2_EXT_SIGNATURE(arity, Signature) \
  typename function_traits<Signature>::result_type ( \
  const boost::signals2::connection & BOOST_SIGNALS2_PP_COMMA_IF(BOOST_SIGNALS2_NUM_ARGS) \
  BOOST_PP_ENUM(arity, BOOST_SIGNALS2_SIGNATURE_TO_ARGN_TYPE, Signature) )
        typedef function<BOOST_SIGNALS2_EXT_SIGNATURE(BOOST_SIGNALS2_NUM_ARGS, Signature)> function_type;
#undef BOOST_SIGNALS2_EXT_SIGNATURE
      };

      template<unsigned arity, typename Signature, typename Combiner,
        typename Group, typename GroupCompare, typename SlotFunction,
        typename ExtendedSlotFunction, typename Mutex>
      class signalN;
      // partial template specialization
      template<typename Signature, typename Combiner, typename Group,
        typename GroupCompare, typename SlotFunction,
        typename ExtendedSlotFunction, typename Mutex>
      class signalN<BOOST_SIGNALS2_NUM_ARGS, Signature, Combiner, Group,
        GroupCompare, SlotFunction, ExtendedSlotFunction, Mutex>
      {
      public:
        typedef BOOST_SIGNALS2_SIGNAL_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)<
          BOOST_SIGNALS2_PORTABLE_SIGNATURE(BOOST_SIGNALS2_NUM_ARGS, Signature),
          Combiner, Group,
          GroupCompare, SlotFunction, ExtendedSlotFunction, Mutex> type;
      };

#endif // BOOST_NO_CXX11_VARIADIC_TEMPLATES

    } // namespace detail
  } // namespace signals2
} // namespace boost

#undef BOOST_SIGNALS2_NUM_ARGS
#undef BOOST_SIGNALS2_SIGNAL_TEMPLATE_INSTANTIATION

/* signal_template.hpp
ZeUqAsJ7BOn5fKVtImL/tWlfGL4FGWshpo2ugTVIVVXVMiKlTlu5CK6qConACkfgSfqnzhHYiG/lXSfPGMkKwNsMGqdvBY+yhIBQxRwwB/fpUAyOKKhx/tBMyWiD3FqQHuG7VLxoLyB5BtWs9WdIdtiixaJk9IsM09l43u9F6AGj/eUnU04ZEXuyn2zDRVbqRANtVGCE0KtgrnEykuep45ipJWN987s9da/xWuRHsyNZc5NuqyVH0alSvqa9PW1+1Bt/rdVNBaOXv7D5ojxvMkcsw6ECsR3aZdarfi9IvBoiw1M4A3AF1oNPiYOb2J9uXPzxxTbi66O5eGKPDElUts80FnRXGKEawtFJb4V8+yTRyfleXVvFRZqco72EPrjcwm4zeXoVFQfb9MsTxDbdvp5IW4HCP/HOceefE2leKKZyAPWlTk5PQpKxWxyhveqphzBdM/FVkN1WueIGEhYCakcTm3bk6yC0rcIGShqQ0keNicGFQQn01Qm2P0j9gUWrzVeSR5xTyVgxgvcRvO0ydJrdosopbhFnCmOdiSlZA7B3DvhPL84SB0VFNL7T6T+0xCXe5SfvFTX6z3mea9RLFndwprwZTrMtjiOAdm6ndoxA95c1Rb1MlIy1+n8x91/6y5wxhM8uDHT5S51LdogcDizQLRY6E/cAIfQUBrvEOf9xav4M7FKbarMR/X2Arh2jhw49eKypRJEImsfgMaJ65hmB7p0jd87HKYHX1jBuZ65FaC66/AuD0PhO1i/tarLjquPwqC9U4vk+eVSwRCpr4Ek+uIsYG2gQEQP8FDW8wUSsp7BVqeAxQ5O0VX8/lbbql8Kr/HAyA551HKZO9Bj2YZNoFe0vX5nM22VQPJZvi14mfzW5z6YxjwFlatOkTkXe/h7Ga0IbkSZuLnLTXGTQaUaWoKc7obtsBiEch9jRyJqjSKOduW0jVJBJHp9dR+QR56Py7rsvJI+IhCmnvdCXPNJsyuX5afIYujtNHq1ixsKHapp3E3V2OlWWVJYgAqwwGRaf5HxjBBIpRbKginzxv88ZyaszThycy1N2ZX9ymElWd1DBt++Hc3mxyh2d27AQdPjd56HvR47zAUWNct065jLlg0Y3hC+3fLm/0hJFxsx6UA/8A9xsIti+JyD7y6orPqdldqt74vx/PfpzQ16nPuySi/uD2wcLXPOz20jiZCH2Vw9DF9slSruLI/aQnFjrsMV35+pTR9P4xgAfPPspifmnVI02OfAKGL9wcPLYp+CCO+bgSAfHhOOHeuPfctvwzTf4m9Lk3gbYp9BEVyifX7CqK48Bf8dXYoGMcFEjotSyDk3nFKrEFBv6cshGieW76W9I3w6TCX07gl83LUced+ybpuWdNmBsvIGgpLx99e3syreyEXW/k1h+2Maev/GVMKwz9O1eLjmO/+byX7a/2t7L39r4ejT/HcN/x/Lf8fx3Av/t4pL5fI2z/Xlz5/Rh8U52GiAxK/Fl9CsEdWpoKj2GyhHL7oZflrz9h4jNlKmfnisOyIUfcUioCppBHBSFE9sxK2HjnfpUCq10irBCZI/EFBEhK12k5dOf6KDUNMB8M238M2/O3DQrrpIn1Ea1/jKbG6Sd31jsq12kfQtnpr7ah6JzfXwek9iO2sLR0amDq8D5vRgP9d2HhpEccX6yr3QZL0adgzk7oIyCMrSMiCqPo0tzFhaK0jKcqj1M1xGxHCtWIZ7D8oVRySTUSBWB21cQY7xHz/XlKEHPreG/5+dv5ulcwxwt2xfoJQKTPmafATOZ/myjB3fzvhHq//UBz8qlfdZniFW3NczLVCUYrUDWL6pqOlWV7A8HJvnHdsNIj5JTCwKrjFNGXL+jbWrmfL8I32NMOHKd3wG49D0HGPXUCfrrq3ZrzkgBCWHevgndZymiRhtclDnDYoIeQ97BL8vuPiH98P1gj5nYfceRvXLR04R7VF7395G//cje94O9H+6Q9+F5s5nRnfDwBMLD85IPoSsu8Sz2MjEvz2Jr+9+JDUhJ4tPEjPH+fdGLfD/DytQOAJhnE2eWvEHMGEsv3lUVLHNlcwXLeh2Ivxd7k+C42u1ZDT7SJYfl8yGLSlFjrUhY1C6qN6LeDEBxxh9cZJPj/Eyt1Ow9PY5QhF67qO9Z8r/9tvurmd9OuODbeOfYTDrrVrm3QgSuwxOBYyEdyX2BLWjfO/QSp17i0kvcvsAxrb8vID11V1OFsMrQY+1pA5uLYElKTKk3OkQEjoGxbhGlBYc+L9yZzBb94o0DdCRExPOq0Yd6CluYjFc49WBnKrmkKSQzaPIBSKCNhvQNAjlEXSO4DCO1PKGE+7WgaXxhZxul24XWFt/z0IVp1GLtQmulApeAPwndVxgilqsHmWTeUjY5xOA069OcmZVFR8Rra5BPvfZ+mzZQlI6mCehgHRYX2qQKXSqmuh1Tnab8IH+m5D6urAPhDIHAgJ899f8FSC+934zEfkB+933egd5UBYd6Ov7HBku8GqRWn+py9DNrPcYvD52hWgdmlKb+KBuizBA+xMQ5aLvMyDfDXsU0X+noWk9GLw+dSTrpebXZW9XX5Axf6T3Rsb6AV7tYDCfu8DBnDp8vPIXBY8KWmGJ30rKVji4MyLgkOHAmR6Fs3r/tpgO5XEtcosTpCEgCGmaOxC6wR1seVMkrTQjMMynNBHtW36n1NPHMgTp2VAJJFh3Vn8MT39waT/0dfEHT6eMlCVckgj2mLyR7YiaCUt365t6rwrL75t7nqf+NWhMT+0D0EpMyUU6kYDaBof/shSimJP3wg+ylhOHa9pp4ZueRt6R3pcOGWCVU5oOjSdcH7x/Ze+Qt+u398C3CNicSGdiGY7IgFdJgFZXF37yEVbdEoKjjvuoeQuXVvdHR/l3JPHPA1jOvr1pqA33VnVqOIvs+fh91NwW6srFRYt3JUZHsWeFQYiVYDvlAByd3GhFxmLgUXlpdmJhVrXammSnzHfkakbimnCdpZCkyvzyDzHOYN8XJ6Msb+e9u/tvMf/fz3xb+e5j/tvJfjgWxvN0GFgdSNwcfWA47an35dP5bxn/hEYJIPshZxJbzy+/h5/fx33v5L2K+yiWI50wyQw2+aFgLBvPDZ0xFj7FgnApMrEhQ4RkiQadmz9br2+Gnuif6XVG2SE9wFONpi/SyRYi2eDzxxmYrSOkZPgBLB98g5lLzGi/vV+/1RCu+hN3cYvEGX6uIyAlUn3jZrEafvGhDB1snCECZ/4Cn7h0sleamzR5npow/8++hVeTO0KsUAewDjbP0+jYO88gN8LVwIUOYitpdjz74z10Iq6Xph+9z0QyK+KAgSOVg3yiUooo8NgLVqfwaNwpcfQsWKdV+InEMksaHPWegesno8ixjSwEPCt0zXuY43Rd2GI6iqgoVtFIuO3fGqDJebuWCjfwpOqXKhOSlzWcMS7USsVcRkshVrwxrReSpj8+Yn4bMzl3/khltSd3+8r0zRgfHknVEHPNwBoHDc4KDISSpbH+923jRZismoTAydJ5gsKElUacoxc5wldk51S01Lhgral5CuZsI5SaXiGnj/Qeihb6XmBm4wtgCfkHYKxTwcCcJfthcnIlKMiimjaUvSkUgrzDgjd4mAvmFgdzoLZhNl4ibbAfn6qlCkm1im4YQ10CVhDIr5RpnjpXf/gmJUnk2MRmHuw5Y2S7FVi2LZEUvLptFKGPyRK1D3DkRcmL8jEPLJhSza9YuS668jXigGjgQydPFF8qVfz9LM3jyaUuuJESt7COPEmP9HHZi7TX+s4vv8W/HdWy64P2KrGQLx7LVsI2zkuHl4vcYY39uYWxEeVbG9/fVN4ocbZgVPMUI3dvxMfrzdlO3cSFC77JuM4jEUKbjLt2FYINlzo4NjEZkBwCvssf/jqju1QM0ufVHVVLHeO09RIs5qXOOIhFNAalQZ6fCiX14AC+qV9Ibm9iaN/Q04Z4sGDHGG7PFGcLhWaKnz6eOeFNWnI26bLjOQc6oZ4FDE5Pt/hYq3uKIuZn1TEwfYO+4naALnYteUv+25qw/Gh2euCMrMS3L1CExxs3mprvMDk2cLFayG8Te2lxHs+OM+Z2La8ly9Jx/r/L3+YLdtQ6odrhGR2M81m1L5Lu0LEdrX1sidYcgZo6e+HYIYXByUKLLUJDnOAe1stXmOLZDdrXG2p/ZJozYGh8Y50z5KDSLHpsZGk3YGv1lsBUyYavsP8KWyInYOXTVBbAxTAQ7Tdjo4mN5+YM/dZsSKcYFfRmfymt+gkvtFiKSBHPqoEXkpIgkgdPPe2GX3et7DkNUZr3xQG9OB0jfEekbBZwddSmcTUi30cLDQ5sCx0gCsBGMQbQnnjrpZlKMuKoJYkWRY894Gq2AqC/2VXdpjyoSYLIj3tliB7R7zJPkHGk8IpM5RyT9u/dI4wf/+Kj9gyNo53bmTXag6bZB67blejPw/cJ6cCadzJkcIZxOnMnRQBezJXP4VRc9bP2AV7/ISK3/5QrKmKfzPccyeH8Cm8Ril51QVKy7sOducy9UdiXcUx081Q7ahC7B6oqE+655c2lHZq6y9/xVvtF/1vMkOAS1mJ4E+If/tNoHGZPAgIExCaxJeNW6LO4mvWqZwOxOLzpM9wAwJm4h8kVyc8yBJWduh+6QerLXHMXEMvXpYQYE0SKf+hwpq8wt6LzDwYySI9Bjgn9iep6dtvuOHAY8fZEzOUw6d3Ub/wn8K0wO+H//bJDEbE7NdGRFDfr5JhYw52TiGswJp1PErMQndfvyvHCU4EBn99VbqaJLdDYWU18vfsXKfvz4zm4rFWQYTZ6RS/9s8Akes0u9/4I9+uzZhDSC4gl86ovjr3Z7VdGp+sbaW+tPLfqq/1Xu0U3iCbVKm/1b+MFl4id4YIz/A9YM61iqii7eO3eear53h9U853nMCYszxqNjMbt9B2ORBnMw8ZjbUGZviafAHWoD2az4oTvOGMmBxBrQ1Mp+7t6UXZeVOVPhEZXvmrt4Qwqy2IeGk+44U3gkYiRWovqITco/ZNmQjXNausMppdbSDw1lU1YaZ0WaTZsUTrV2I7VWZLZWKFaq1l6LP1Zmiw7i9pA4HdxxCp5Vp+XHjdxSn65fpZKHcmVXpLrOcTkyanh/njgwt2PCfiLWa1UlaeXd6bdYWvanO4gU3TeadV6T3mgqkShY03qVk5SrTqXolnecX/PW/7eanf+2ZvlmCiRTeb/1uWPMSpH6+1qz0sszpqDCWLU6Yw6OWAD+81RtVeHUig0+xKHfVY3I9H29WeNVqsYvy/TN1R42F2fKBX00M4t33H4mXfN/6KuZprxvXz/d3s1R8Ia9R6zYlhUpA24IYOYRlrzhCwI21gfbiGddjnUnbNaPGFDvLUO9cdbb2sSouluHeqMEIr3qvQMqYvWOwG65WlZ+qiCcVemP9EeyzInq1iYfpVtwzkTsfkXzJT9fYTF+FVVhteb//F+ogiOwD1DqX1b8JrajDgSOzFB6y1/+PsuWmOuM2JKDqpS58Ru3nTFKqyIFNG3j7z5piK76U48dM+cicl/Dfshxw1eYchwO6ksWsWXQNxfZLPtuPbBaGXxvAAJfg1Mg4UCQixAOjrU1xPBqa6PUiBnAVbkScNj54FozqvtjhFDsOJg+RuQIZ9KdwoHTHDYft/Mp7wYjtDh5jW8LG6ZfJjdffYrEY2+VdV60SRVO26A7uH+wFGBbb8scitMngL8voPeOgJW/ARGttEbzWB1pcxEnPbDZtAHwxcZEL40MNoY56Wbi0oVDRfOODtfSM0sX9t8h8SCr6BQxHJPOZzg+PNIU2Ah3Y/Adk6P96A7Lj0C0Yo+yVXGEuBltox5bR6PQY+vlP5f0GKc/HHkKxeJ/+yK+x1GlzrozyuylMkiwEGjl+ALwzGgJw8TesmjgY1vTxL7lfBP71aaJ/WX/e8KQf1zex8TezD0P6LaA278rBdxiEqDa9xzAGMxIr3pNUPye+dAEbfMhAa4dgWxg0HxAht+GQTPkKH05C2VPSL5ml+Mn+ACGG9S5efEEEJS+3MnXLr528bXSdjCb80QjXzfyNR+wcJ/EEyzRc1d07ph4gsXh5QV8zccvy0fzNR+/LB/L13wIs3w8X0/g6wl8zQcyy/HX9zzjlUoSXVbAcNPP9yqBmkV91yAiuYsjkv/m7+AyXLDJI2bGeBq8qaH1qi0Pgun3I+o5V7L4N+IJHCGpZPATuXncy09/k2UjFuR56FZqbyAO5CY/X8euFU+w7/v4Naq88Qoey79/levE9eJDZlhzmftHC1/SlolPihYSWWfMKTR3mNhZrcdT90MMongM4aWr2YXvsoyzxY3f7lZZmTeSlL0dYXrACwhttBw9mvYijkhpT6UCv24QMebY+ymPjG7RHZIvvXOCBNpgL1wychgH70a8DVjLEQK64g5CQMXO5FfjBw1fbDSCtY5WVtLjIMRR9aKsWwylNqrKOchNjeiKG0bUZWbWHSf28FgLUhp4mAPD3hrea+B9wmlnRXikIRK2Sw7daxgdiGdRIQt2GexEksGjfoez2vc3PTu0exUbVExDjxFDBu/QpLfXlF5MV24XjmYvW26dsjFgsB/vRRf6u0MRDYj3PNOYpIWNXkwV3hkzvd72ydti7PX2yiaa+kedNJxbUSMOsooai+coYm0Rq5wfmsRKLn+LQ6Qxzfr/h8qQlvX/rDX8P+sMOWBplgxwxnCX6XJexh54hNBMDBHINdFDIM/co3tk9zLCWLm2Ghy0NczD2Bcs4+jVvEGJJZ4b39B5jgG0tkIwgb/bswLrYAk07K3B3UL0Gyxaf+FFUAFjphMG1Lw75am5dptRj5oE//Vz/Yt/G/8l/oUE+q9G5XB4BVsOyKceT3l8lh7rNiwVJ0rYUWLUPbTkkWxjM06IiRtQvRQ9HZgUueCVbiP+Bh719yRm2mHsPf5BVFi8kyr87K/dyhzAHckKG+/QR5dhNtjWV4V/iP5NfW3TypQr0KvXw3+pHko304VpIAdOWL/PMCy3o4hBsm7TUkyIHd+cPGkYTTxO3DKwJjiRSYg2zlaiAHLKRzjoT0io8lZ1nDDM12qKikOJerypWdM/1xuyHEcunnHSUCqt0dQlHPxzp7D81KmvsGWVYbyMD0VzDZxr5VVfqD7qiwAALP/TpqR7J2aMiRh62ZgQg45dllJn1Wxwdwzut2m1K3rkHQfgooFuIQgr4k6KN7Ae8TcVFzbfnO1o//ibY/nJXNXL2uuU4o31lTQIKAtIOPmKeAIgp7obMl5FLTLWm57ML+2pXHfC6pqcsQR24tMbfgag3V7LduIORiee+isQ9clhqUOLThG3BQNxN1wE5hd46hx4v08uJtQrevznPHUnEJXoUXrTkcVvooiJc1Au/mW3UXUlVKhViMy/KtJt6IGNPpYHPStb7XCKB1Fj5NVAva+xXUpd+9FYU9m4Tdd6/Qeiw6oSceyCUFj6d5yjJvXY5mS2rm0W5zDUCmop3v9zo+mJ0ZeYQ1YpN+w4Z0yO8wtmuccioSiAUd17EjD+VzKpyP2R7w8YqkazN9m/R9uvPzGG6vItGBctFNPGge83MWp+xi1D/Ewc7ufor6I8cTqJBZnp3OReJ9IygG3gyI0uEWzxxRqiDhFs1YNbRbCNBul7HUQ+Osrf
*/