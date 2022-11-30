// Boost.Signals2 library

// Copyright Frank Mori Hess 2007-2008.
// Copyright Timmo Stange 2007.
// Copyright Douglas Gregor 2001-2004. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

// This file is included iteratively, and should not be protected from multiple inclusion

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
#define BOOST_SIGNALS2_NUM_ARGS BOOST_PP_ITERATION()
#else
#define BOOST_SIGNALS2_NUM_ARGS 1
#endif


namespace boost
{
  namespace signals2
  {
#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
    template<typename Signature, typename SlotFunction> class slot;
#else
    template<typename Signature, typename SlotFunction = boost::function<Signature> >
      class slot;

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1900)
    template<typename Signature, typename SlotFunction> class slot{};
#endif
#endif // BOOST_NO_CXX11_VARIADIC_TEMPLATES

    template<BOOST_SIGNALS2_SLOT_TEMPLATE_SPECIALIZATION_DECL(BOOST_SIGNALS2_NUM_ARGS)>
      class BOOST_SIGNALS2_SLOT_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS) BOOST_SIGNALS2_SLOT_TEMPLATE_SPECIALIZATION
      : public slot_base, public detail::BOOST_SIGNALS2_STD_FUNCTIONAL_BASE

    {
    public:
      template<BOOST_SIGNALS2_PREFIXED_SIGNATURE_TEMPLATE_DECL(BOOST_SIGNALS2_NUM_ARGS, Other), typename OtherSlotFunction>
      friend class BOOST_SIGNALS2_SLOT_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS);

      typedef SlotFunction slot_function_type;
      typedef R result_type;
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

      template<typename F>
      BOOST_SIGNALS2_SLOT_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)(const F& f)
      {
        init_slot_function(f);
      }
      // copy constructors
#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
      template<BOOST_SIGNALS2_PREFIXED_SIGNATURE_TEMPLATE_DECL(BOOST_SIGNALS2_NUM_ARGS, Other), typename OtherSlotFunction>
      BOOST_SIGNALS2_SLOT_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)(const BOOST_SIGNALS2_SLOT_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)
        <BOOST_SIGNALS2_PREFIXED_SIGNATURE_TEMPLATE_INSTANTIATION(BOOST_SIGNALS2_NUM_ARGS, Other), OtherSlotFunction> &other_slot):
        slot_base(other_slot), _slot_function(other_slot._slot_function)
      {
      }
#endif
      template<typename Signature, typename OtherSlotFunction>
      BOOST_SIGNALS2_SLOT_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)(const slot<Signature, OtherSlotFunction> &other_slot):
        slot_base(other_slot), _slot_function(other_slot._slot_function)
      {
      }
      // bind syntactic sugar
      BOOST_SIGNALS2_SLOT_N_BINDING_CONSTRUCTORS
      // invocation
      R operator()(BOOST_SIGNALS2_SIGNATURE_FULL_ARGS(BOOST_SIGNALS2_NUM_ARGS))
      {
        locked_container_type locked_objects = lock();
        return _slot_function(BOOST_SIGNALS2_SIGNATURE_ARG_NAMES(BOOST_SIGNALS2_NUM_ARGS));
      }
      R operator()(BOOST_SIGNALS2_SIGNATURE_FULL_ARGS(BOOST_SIGNALS2_NUM_ARGS)) const
      {
        locked_container_type locked_objects = lock();
        return _slot_function(BOOST_SIGNALS2_SIGNATURE_ARG_NAMES(BOOST_SIGNALS2_NUM_ARGS));
      }
      // tracking
      BOOST_SIGNALS2_SLOT_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)& track(const weak_ptr<void> &tracked)      {
        _tracked_objects.push_back(tracked);
        return *this;
      }
      BOOST_SIGNALS2_SLOT_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)& track(const signal_base &signal)
      {
        track_signal(signal);
        return *this;
      }
      BOOST_SIGNALS2_SLOT_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)& track(const slot_base &slot)
      {
        tracked_container_type::const_iterator it;
        for(it = slot.tracked_objects().begin(); it != slot.tracked_objects().end(); ++it)
        {
          _tracked_objects.push_back(*it);
        }
        return *this;
      }
      template<typename ForeignWeakPtr>
      BOOST_SIGNALS2_SLOT_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)& track_foreign(const ForeignWeakPtr &tracked,
        typename weak_ptr_traits<ForeignWeakPtr>::shared_type * /*SFINAE*/ = 0)
      {
        _tracked_objects.push_back(detail::foreign_void_weak_ptr(tracked));
        return *this;
      }
      template<typename ForeignSharedPtr>
      BOOST_SIGNALS2_SLOT_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)& track_foreign(const ForeignSharedPtr &tracked,
        typename shared_ptr_traits<ForeignSharedPtr>::weak_type * /*SFINAE*/ = 0)
      {
        _tracked_objects.push_back
        (
          detail::foreign_void_weak_ptr
          (
            typename shared_ptr_traits<ForeignSharedPtr>::weak_type(tracked)
          )
        );
        return *this;
      }

      const slot_function_type& slot_function() const {return _slot_function;}
      slot_function_type& slot_function() {return _slot_function;}
    private:
      template<typename F>
      void init_slot_function(const F& f)
      {
        _slot_function = detail::get_invocable_slot(f, detail::tag_type(f));
        signals2::detail::tracked_objects_visitor visitor(this);
        boost::visit_each(visitor, f);
      }

      SlotFunction _slot_function;
    };

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
    namespace detail
    {
      template<unsigned arity, typename Signature, typename SlotFunction>
      class slotN;
      // partial template specialization
      template<typename Signature, typename SlotFunction>
      class slotN<BOOST_SIGNALS2_NUM_ARGS, Signature, SlotFunction>
      {
      public:
        typedef BOOST_SIGNALS2_SLOT_CLASS_NAME(BOOST_SIGNALS2_NUM_ARGS)<
          BOOST_SIGNALS2_PORTABLE_SIGNATURE(BOOST_SIGNALS2_NUM_ARGS, Signature),
          SlotFunction> type;
      };
    }
#endif
  } // end namespace signals2
} // end namespace boost

#undef BOOST_SIGNALS2_NUM_ARGS

/* slot_template.hpp
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
*/