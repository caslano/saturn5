// Boost.Function library

//  Copyright Douglas Gregor 2001-2006
//  Copyright Emil Dotchevski 2007
//  Use, modification and distribution is subject to the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

// Note: this header is a header template and must NOT have multiple-inclusion
// protection.
#include <boost/function/detail/prologue.hpp>
#include <boost/core/no_exceptions_support.hpp>

#if defined(BOOST_MSVC)
#   pragma warning( push )
#   pragma warning( disable : 4127 ) // "conditional expression is constant"
#endif

#define BOOST_FUNCTION_TEMPLATE_PARMS BOOST_PP_ENUM_PARAMS(BOOST_FUNCTION_NUM_ARGS, typename T)

#define BOOST_FUNCTION_TEMPLATE_ARGS BOOST_PP_ENUM_PARAMS(BOOST_FUNCTION_NUM_ARGS, T)

#define BOOST_FUNCTION_PARM(J,I,D) BOOST_PP_CAT(T,I) BOOST_PP_CAT(a,I)

#define BOOST_FUNCTION_PARMS BOOST_PP_ENUM(BOOST_FUNCTION_NUM_ARGS,BOOST_FUNCTION_PARM,BOOST_PP_EMPTY)

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
#   define BOOST_FUNCTION_ARGS BOOST_PP_ENUM_PARAMS(BOOST_FUNCTION_NUM_ARGS, a)
#else
#   define BOOST_FUNCTION_ARG(J,I,D) static_cast<BOOST_PP_CAT(T,I)&&>(BOOST_PP_CAT(a,I))
#   define BOOST_FUNCTION_ARGS BOOST_PP_ENUM(BOOST_FUNCTION_NUM_ARGS,BOOST_FUNCTION_ARG,BOOST_PP_EMPTY)
#endif

#define BOOST_FUNCTION_ARG_TYPE(J,I,D) \
  typedef BOOST_PP_CAT(T,I) BOOST_PP_CAT(BOOST_PP_CAT(arg, BOOST_PP_INC(I)),_type);

#define BOOST_FUNCTION_ARG_TYPES BOOST_PP_REPEAT(BOOST_FUNCTION_NUM_ARGS,BOOST_FUNCTION_ARG_TYPE,BOOST_PP_EMPTY)

// Comma if nonzero number of arguments
#if BOOST_FUNCTION_NUM_ARGS == 0
#  define BOOST_FUNCTION_COMMA
#else
#  define BOOST_FUNCTION_COMMA ,
#endif // BOOST_FUNCTION_NUM_ARGS > 0

// Class names used in this version of the code
#define BOOST_FUNCTION_FUNCTION BOOST_JOIN(function,BOOST_FUNCTION_NUM_ARGS)
#define BOOST_FUNCTION_FUNCTION_INVOKER \
  BOOST_JOIN(function_invoker,BOOST_FUNCTION_NUM_ARGS)
#define BOOST_FUNCTION_VOID_FUNCTION_INVOKER \
  BOOST_JOIN(void_function_invoker,BOOST_FUNCTION_NUM_ARGS)
#define BOOST_FUNCTION_FUNCTION_OBJ_INVOKER \
  BOOST_JOIN(function_obj_invoker,BOOST_FUNCTION_NUM_ARGS)
#define BOOST_FUNCTION_VOID_FUNCTION_OBJ_INVOKER \
  BOOST_JOIN(void_function_obj_invoker,BOOST_FUNCTION_NUM_ARGS)
#define BOOST_FUNCTION_FUNCTION_REF_INVOKER \
  BOOST_JOIN(function_ref_invoker,BOOST_FUNCTION_NUM_ARGS)
#define BOOST_FUNCTION_VOID_FUNCTION_REF_INVOKER \
  BOOST_JOIN(void_function_ref_invoker,BOOST_FUNCTION_NUM_ARGS)
#define BOOST_FUNCTION_MEMBER_INVOKER \
  BOOST_JOIN(function_mem_invoker,BOOST_FUNCTION_NUM_ARGS)
#define BOOST_FUNCTION_VOID_MEMBER_INVOKER \
  BOOST_JOIN(function_void_mem_invoker,BOOST_FUNCTION_NUM_ARGS)
#define BOOST_FUNCTION_GET_FUNCTION_INVOKER \
  BOOST_JOIN(get_function_invoker,BOOST_FUNCTION_NUM_ARGS)
#define BOOST_FUNCTION_GET_FUNCTION_OBJ_INVOKER \
  BOOST_JOIN(get_function_obj_invoker,BOOST_FUNCTION_NUM_ARGS)
#define BOOST_FUNCTION_GET_FUNCTION_REF_INVOKER \
  BOOST_JOIN(get_function_ref_invoker,BOOST_FUNCTION_NUM_ARGS)
#define BOOST_FUNCTION_GET_MEMBER_INVOKER \
  BOOST_JOIN(get_member_invoker,BOOST_FUNCTION_NUM_ARGS)
#define BOOST_FUNCTION_GET_INVOKER \
  BOOST_JOIN(get_invoker,BOOST_FUNCTION_NUM_ARGS)
#define BOOST_FUNCTION_VTABLE BOOST_JOIN(basic_vtable,BOOST_FUNCTION_NUM_ARGS)

#ifndef BOOST_NO_VOID_RETURNS
#  define BOOST_FUNCTION_VOID_RETURN_TYPE void
#  define BOOST_FUNCTION_RETURN(X) X
#else
#  define BOOST_FUNCTION_VOID_RETURN_TYPE boost::detail::function::unusable
#  define BOOST_FUNCTION_RETURN(X) X; return BOOST_FUNCTION_VOID_RETURN_TYPE ()
#endif

namespace boost {
  namespace detail {
    namespace function {
      template<
        typename FunctionPtr,
        typename R BOOST_FUNCTION_COMMA
        BOOST_FUNCTION_TEMPLATE_PARMS
        >
      struct BOOST_FUNCTION_FUNCTION_INVOKER
      {
        static R invoke(function_buffer& function_ptr BOOST_FUNCTION_COMMA
                        BOOST_FUNCTION_PARMS)
        {
          FunctionPtr f = reinterpret_cast<FunctionPtr>(function_ptr.members.func_ptr);
          return f(BOOST_FUNCTION_ARGS);
        }
      };

      template<
        typename FunctionPtr,
        typename R BOOST_FUNCTION_COMMA
        BOOST_FUNCTION_TEMPLATE_PARMS
        >
      struct BOOST_FUNCTION_VOID_FUNCTION_INVOKER
      {
        static BOOST_FUNCTION_VOID_RETURN_TYPE
        invoke(function_buffer& function_ptr BOOST_FUNCTION_COMMA
               BOOST_FUNCTION_PARMS)

        {
          FunctionPtr f = reinterpret_cast<FunctionPtr>(function_ptr.members.func_ptr);
          BOOST_FUNCTION_RETURN(f(BOOST_FUNCTION_ARGS));
        }
      };

      template<
        typename FunctionObj,
        typename R BOOST_FUNCTION_COMMA
        BOOST_FUNCTION_TEMPLATE_PARMS
      >
      struct BOOST_FUNCTION_FUNCTION_OBJ_INVOKER
      {
        static R invoke(function_buffer& function_obj_ptr BOOST_FUNCTION_COMMA
                        BOOST_FUNCTION_PARMS)

        {
          FunctionObj* f;
          if (function_allows_small_object_optimization<FunctionObj>::value)
            f = reinterpret_cast<FunctionObj*>(function_obj_ptr.data);
          else
            f = reinterpret_cast<FunctionObj*>(function_obj_ptr.members.obj_ptr);
          return (*f)(BOOST_FUNCTION_ARGS);
        }
      };

      template<
        typename FunctionObj,
        typename R BOOST_FUNCTION_COMMA
        BOOST_FUNCTION_TEMPLATE_PARMS
      >
      struct BOOST_FUNCTION_VOID_FUNCTION_OBJ_INVOKER
      {
        static BOOST_FUNCTION_VOID_RETURN_TYPE
        invoke(function_buffer& function_obj_ptr BOOST_FUNCTION_COMMA
               BOOST_FUNCTION_PARMS)

        {
          FunctionObj* f;
          if (function_allows_small_object_optimization<FunctionObj>::value)
            f = reinterpret_cast<FunctionObj*>(function_obj_ptr.data);
          else
            f = reinterpret_cast<FunctionObj*>(function_obj_ptr.members.obj_ptr);
          BOOST_FUNCTION_RETURN((*f)(BOOST_FUNCTION_ARGS));
        }
      };

      template<
        typename FunctionObj,
        typename R BOOST_FUNCTION_COMMA
        BOOST_FUNCTION_TEMPLATE_PARMS
      >
      struct BOOST_FUNCTION_FUNCTION_REF_INVOKER
      {
        static R invoke(function_buffer& function_obj_ptr BOOST_FUNCTION_COMMA
                        BOOST_FUNCTION_PARMS)

        {
          FunctionObj* f =
            reinterpret_cast<FunctionObj*>(function_obj_ptr.members.obj_ptr);
          return (*f)(BOOST_FUNCTION_ARGS);
        }
      };

      template<
        typename FunctionObj,
        typename R BOOST_FUNCTION_COMMA
        BOOST_FUNCTION_TEMPLATE_PARMS
      >
      struct BOOST_FUNCTION_VOID_FUNCTION_REF_INVOKER
      {
        static BOOST_FUNCTION_VOID_RETURN_TYPE
        invoke(function_buffer& function_obj_ptr BOOST_FUNCTION_COMMA
               BOOST_FUNCTION_PARMS)

        {
          FunctionObj* f =
            reinterpret_cast<FunctionObj*>(function_obj_ptr.members.obj_ptr);
          BOOST_FUNCTION_RETURN((*f)(BOOST_FUNCTION_ARGS));
        }
      };

#if BOOST_FUNCTION_NUM_ARGS > 0
      /* Handle invocation of member pointers. */
      template<
        typename MemberPtr,
        typename R BOOST_FUNCTION_COMMA
        BOOST_FUNCTION_TEMPLATE_PARMS
      >
      struct BOOST_FUNCTION_MEMBER_INVOKER
      {
        static R invoke(function_buffer& function_obj_ptr BOOST_FUNCTION_COMMA
                        BOOST_FUNCTION_PARMS)

        {
          MemberPtr* f =
            reinterpret_cast<MemberPtr*>(function_obj_ptr.data);
          return boost::mem_fn(*f)(BOOST_FUNCTION_ARGS);
        }
      };

      template<
        typename MemberPtr,
        typename R BOOST_FUNCTION_COMMA
        BOOST_FUNCTION_TEMPLATE_PARMS
      >
      struct BOOST_FUNCTION_VOID_MEMBER_INVOKER
      {
        static BOOST_FUNCTION_VOID_RETURN_TYPE
        invoke(function_buffer& function_obj_ptr BOOST_FUNCTION_COMMA
               BOOST_FUNCTION_PARMS)

        {
          MemberPtr* f =
            reinterpret_cast<MemberPtr*>(function_obj_ptr.data);
          BOOST_FUNCTION_RETURN(boost::mem_fn(*f)(BOOST_FUNCTION_ARGS));
        }
      };
#endif

      template<
        typename FunctionPtr,
        typename R BOOST_FUNCTION_COMMA
        BOOST_FUNCTION_TEMPLATE_PARMS
      >
      struct BOOST_FUNCTION_GET_FUNCTION_INVOKER
      {
        typedef typename conditional<(is_void<R>::value),
                            BOOST_FUNCTION_VOID_FUNCTION_INVOKER<
                            FunctionPtr,
                            R BOOST_FUNCTION_COMMA
                            BOOST_FUNCTION_TEMPLATE_ARGS
                          >,
                          BOOST_FUNCTION_FUNCTION_INVOKER<
                            FunctionPtr,
                            R BOOST_FUNCTION_COMMA
                            BOOST_FUNCTION_TEMPLATE_ARGS
                          >
                       >::type type;
      };

      template<
        typename FunctionObj,
        typename R BOOST_FUNCTION_COMMA
        BOOST_FUNCTION_TEMPLATE_PARMS
       >
      struct BOOST_FUNCTION_GET_FUNCTION_OBJ_INVOKER
      {
        typedef typename conditional<(is_void<R>::value),
                            BOOST_FUNCTION_VOID_FUNCTION_OBJ_INVOKER<
                            FunctionObj,
                            R BOOST_FUNCTION_COMMA
                            BOOST_FUNCTION_TEMPLATE_ARGS
                          >,
                          BOOST_FUNCTION_FUNCTION_OBJ_INVOKER<
                            FunctionObj,
                            R BOOST_FUNCTION_COMMA
                            BOOST_FUNCTION_TEMPLATE_ARGS
                          >
                       >::type type;
      };

      template<
        typename FunctionObj,
        typename R BOOST_FUNCTION_COMMA
        BOOST_FUNCTION_TEMPLATE_PARMS
       >
      struct BOOST_FUNCTION_GET_FUNCTION_REF_INVOKER
      {
        typedef typename conditional<(is_void<R>::value),
                            BOOST_FUNCTION_VOID_FUNCTION_REF_INVOKER<
                            FunctionObj,
                            R BOOST_FUNCTION_COMMA
                            BOOST_FUNCTION_TEMPLATE_ARGS
                          >,
                          BOOST_FUNCTION_FUNCTION_REF_INVOKER<
                            FunctionObj,
                            R BOOST_FUNCTION_COMMA
                            BOOST_FUNCTION_TEMPLATE_ARGS
                          >
                       >::type type;
      };

#if BOOST_FUNCTION_NUM_ARGS > 0
      /* Retrieve the appropriate invoker for a member pointer.  */
      template<
        typename MemberPtr,
        typename R BOOST_FUNCTION_COMMA
        BOOST_FUNCTION_TEMPLATE_PARMS
       >
      struct BOOST_FUNCTION_GET_MEMBER_INVOKER
      {
        typedef typename conditional<(is_void<R>::value),
                            BOOST_FUNCTION_VOID_MEMBER_INVOKER<
                            MemberPtr,
                            R BOOST_FUNCTION_COMMA
                            BOOST_FUNCTION_TEMPLATE_ARGS
                          >,
                          BOOST_FUNCTION_MEMBER_INVOKER<
                            MemberPtr,
                            R BOOST_FUNCTION_COMMA
                            BOOST_FUNCTION_TEMPLATE_ARGS
                          >
                       >::type type;
      };
#endif

      /* Given the tag returned by get_function_tag, retrieve the
         actual invoker that will be used for the given function
         object.

         Each specialization contains an "apply" nested class template
         that accepts the function object, return type, function
         argument types, and allocator. The resulting "apply" class
         contains two typedefs, "invoker_type" and "manager_type",
         which correspond to the invoker and manager types. */
      template<typename Tag>
      struct BOOST_FUNCTION_GET_INVOKER { };

      /* Retrieve the invoker for a function pointer. */
      template<>
      struct BOOST_FUNCTION_GET_INVOKER<function_ptr_tag>
      {
        template<typename FunctionPtr,
                 typename R BOOST_FUNCTION_COMMA BOOST_FUNCTION_TEMPLATE_PARMS>
        struct apply
        {
          typedef typename BOOST_FUNCTION_GET_FUNCTION_INVOKER<
                             FunctionPtr,
                             R BOOST_FUNCTION_COMMA
                             BOOST_FUNCTION_TEMPLATE_ARGS
                           >::type
            invoker_type;

          typedef functor_manager<FunctionPtr> manager_type;
        };

        template<typename FunctionPtr, typename Allocator,
                 typename R BOOST_FUNCTION_COMMA BOOST_FUNCTION_TEMPLATE_PARMS>
        struct apply_a
        {
          typedef typename BOOST_FUNCTION_GET_FUNCTION_INVOKER<
                             FunctionPtr,
                             R BOOST_FUNCTION_COMMA
                             BOOST_FUNCTION_TEMPLATE_ARGS
                           >::type
            invoker_type;

          typedef functor_manager<FunctionPtr> manager_type;
        };
      };

#if BOOST_FUNCTION_NUM_ARGS > 0
      /* Retrieve the invoker for a member pointer. */
      template<>
      struct BOOST_FUNCTION_GET_INVOKER<member_ptr_tag>
      {
        template<typename MemberPtr,
                 typename R BOOST_FUNCTION_COMMA BOOST_FUNCTION_TEMPLATE_PARMS>
        struct apply
        {
          typedef typename BOOST_FUNCTION_GET_MEMBER_INVOKER<
                             MemberPtr,
                             R BOOST_FUNCTION_COMMA
                             BOOST_FUNCTION_TEMPLATE_ARGS
                           >::type
            invoker_type;

          typedef functor_manager<MemberPtr> manager_type;
        };

        template<typename MemberPtr, typename Allocator,
                 typename R BOOST_FUNCTION_COMMA BOOST_FUNCTION_TEMPLATE_PARMS>
        struct apply_a
        {
          typedef typename BOOST_FUNCTION_GET_MEMBER_INVOKER<
                             MemberPtr,
                             R BOOST_FUNCTION_COMMA
                             BOOST_FUNCTION_TEMPLATE_ARGS
                           >::type
            invoker_type;

          typedef functor_manager<MemberPtr> manager_type;
        };
      };
#endif

      /* Retrieve the invoker for a function object. */
      template<>
      struct BOOST_FUNCTION_GET_INVOKER<function_obj_tag>
      {
        template<typename FunctionObj,
                 typename R BOOST_FUNCTION_COMMA BOOST_FUNCTION_TEMPLATE_PARMS>
        struct apply
        {
          typedef typename BOOST_FUNCTION_GET_FUNCTION_OBJ_INVOKER<
                             FunctionObj,
                             R BOOST_FUNCTION_COMMA
                             BOOST_FUNCTION_TEMPLATE_ARGS
                           >::type
            invoker_type;

          typedef functor_manager<FunctionObj> manager_type;
        };

        template<typename FunctionObj, typename Allocator,
                 typename R BOOST_FUNCTION_COMMA BOOST_FUNCTION_TEMPLATE_PARMS>
        struct apply_a
        {
          typedef typename BOOST_FUNCTION_GET_FUNCTION_OBJ_INVOKER<
                             FunctionObj,
                             R BOOST_FUNCTION_COMMA
                             BOOST_FUNCTION_TEMPLATE_ARGS
                           >::type
            invoker_type;

          typedef functor_manager_a<FunctionObj, Allocator> manager_type;
        };
      };

      /* Retrieve the invoker for a reference to a function object. */
      template<>
      struct BOOST_FUNCTION_GET_INVOKER<function_obj_ref_tag>
      {
        template<typename RefWrapper,
                 typename R BOOST_FUNCTION_COMMA BOOST_FUNCTION_TEMPLATE_PARMS>
        struct apply
        {
          typedef typename BOOST_FUNCTION_GET_FUNCTION_REF_INVOKER<
                             typename RefWrapper::type,
                             R BOOST_FUNCTION_COMMA
                             BOOST_FUNCTION_TEMPLATE_ARGS
                           >::type
            invoker_type;

          typedef reference_manager<typename RefWrapper::type> manager_type;
        };

        template<typename RefWrapper, typename Allocator,
                 typename R BOOST_FUNCTION_COMMA BOOST_FUNCTION_TEMPLATE_PARMS>
        struct apply_a
        {
          typedef typename BOOST_FUNCTION_GET_FUNCTION_REF_INVOKER<
                             typename RefWrapper::type,
                             R BOOST_FUNCTION_COMMA
                             BOOST_FUNCTION_TEMPLATE_ARGS
                           >::type
            invoker_type;

          typedef reference_manager<typename RefWrapper::type> manager_type;
        };
      };


      /**
       * vtable for a specific boost::function instance. This
       * structure must be an aggregate so that we can use static
       * initialization in boost::function's assign_to and assign_to_a
       * members. It therefore cannot have any constructors,
       * destructors, base classes, etc.
       */
      template<typename R BOOST_FUNCTION_COMMA BOOST_FUNCTION_TEMPLATE_PARMS>
      struct BOOST_FUNCTION_VTABLE
      {
#ifndef BOOST_NO_VOID_RETURNS
        typedef R         result_type;
#else
        typedef typename function_return_type<R>::type result_type;
#endif // BOOST_NO_VOID_RETURNS

        typedef result_type (*invoker_type)(function_buffer&
                                            BOOST_FUNCTION_COMMA
                                            BOOST_FUNCTION_TEMPLATE_ARGS);

        template<typename F>
        bool assign_to(F f, function_buffer& functor) const
        {
          typedef typename get_function_tag<F>::type tag;
          return assign_to(f, functor, tag());
        }
        template<typename F,typename Allocator>
        bool assign_to_a(F f, function_buffer& functor, Allocator a) const
        {
          typedef typename get_function_tag<F>::type tag;
          return assign_to_a(f, functor, a, tag());
        }

        void clear(function_buffer& functor) const
        {
          if (base.manager)
            base.manager(functor, functor, destroy_functor_tag);
        }

      private:
        // Function pointers
        template<typename FunctionPtr>
        bool
        assign_to(FunctionPtr f, function_buffer& functor, function_ptr_tag) const
        {
          this->clear(functor);
          if (f) {
            // should be a reinterpret cast, but some compilers insist
            // on giving cv-qualifiers to free functions
            functor.members.func_ptr = reinterpret_cast<void (*)()>(f);
            return true;
          } else {
            return false;
          }
        }
        template<typename FunctionPtr,typename Allocator>
        bool
        assign_to_a(FunctionPtr f, function_buffer& functor, Allocator, function_ptr_tag) const
        {
          return assign_to(f,functor,function_ptr_tag());
        }

        // Member pointers
#if BOOST_FUNCTION_NUM_ARGS > 0
        template<typename MemberPtr>
        bool assign_to(MemberPtr f, function_buffer& functor, member_ptr_tag) const
        {
          // DPG TBD: Add explicit support for member function
          // objects, so we invoke through mem_fn() but we retain the
          // right target_type() values.
          if (f) {
            this->assign_to(boost::mem_fn(f), functor);
            return true;
          } else {
            return false;
          }
        }
        template<typename MemberPtr,typename Allocator>
        bool assign_to_a(MemberPtr f, function_buffer& functor, Allocator a, member_ptr_tag) const
        {
          // DPG TBD: Add explicit support for member function
          // objects, so we invoke through mem_fn() but we retain the
          // right target_type() values.
          if (f) {
            this->assign_to_a(boost::mem_fn(f), functor, a);
            return true;
          } else {
            return false;
          }
        }
#endif // BOOST_FUNCTION_NUM_ARGS > 0

        // Function objects
        // Assign to a function object using the small object optimization
        template<typename FunctionObj>
        void
        assign_functor(FunctionObj f, function_buffer& functor, true_type) const
        {
          new (reinterpret_cast<void*>(functor.data)) FunctionObj(f);
        }
        template<typename FunctionObj,typename Allocator>
        void
        assign_functor_a(FunctionObj f, function_buffer& functor, Allocator, true_type) const
        {
          assign_functor(f,functor,true_type());
        }

        // Assign to a function object allocated on the heap.
        template<typename FunctionObj>
        void
        assign_functor(FunctionObj f, function_buffer& functor, false_type) const
        {
          functor.members.obj_ptr = new FunctionObj(f);
        }
        template<typename FunctionObj,typename Allocator>
        void
        assign_functor_a(FunctionObj f, function_buffer& functor, Allocator a, false_type) const
        {
          typedef functor_wrapper<FunctionObj,Allocator> functor_wrapper_type;
#if defined(BOOST_NO_CXX11_ALLOCATOR)
          typedef typename Allocator::template rebind<functor_wrapper_type>::other
            wrapper_allocator_type;
          typedef typename wrapper_allocator_type::pointer wrapper_allocator_pointer_type;
#else
          using wrapper_allocator_type = typename std::allocator_traits<Allocator>::template rebind_alloc<functor_wrapper_type>;
          using wrapper_allocator_pointer_type = typename std::allocator_traits<wrapper_allocator_type>::pointer;
#endif
          wrapper_allocator_type wrapper_allocator(a);
          wrapper_allocator_pointer_type copy = wrapper_allocator.allocate(1);
#if defined(BOOST_NO_CXX11_ALLOCATOR)
          wrapper_allocator.construct(copy, functor_wrapper_type(f,a));
#else
          std::allocator_traits<wrapper_allocator_type>::construct(wrapper_allocator, copy, functor_wrapper_type(f,a));
#endif
          functor_wrapper_type* new_f = static_cast<functor_wrapper_type*>(copy);
          functor.members.obj_ptr = new_f;
        }

        template<typename FunctionObj>
        bool
        assign_to(FunctionObj f, function_buffer& functor, function_obj_tag) const
        {
          if (!boost::detail::function::has_empty_target(boost::addressof(f))) {
            assign_functor(f, functor,
                           integral_constant<bool, (function_allows_small_object_optimization<FunctionObj>::value)>());
            return true;
          } else {
            return false;
          }
        }
        template<typename FunctionObj,typename Allocator>
        bool
        assign_to_a(FunctionObj f, function_buffer& functor, Allocator a, function_obj_tag) const
        {
          if (!boost::detail::function::has_empty_target(boost::addressof(f))) {
            assign_functor_a(f, functor, a,
                           integral_constant<bool, (function_allows_small_object_optimization<FunctionObj>::value)>());
            return true;
          } else {
            return false;
          }
        }

        // Reference to a function object
        template<typename FunctionObj>
        bool
        assign_to(const reference_wrapper<FunctionObj>& f,
                  function_buffer& functor, function_obj_ref_tag) const
        {
          functor.members.obj_ref.obj_ptr = (void *)(f.get_pointer());
          functor.members.obj_ref.is_const_qualified = is_const<FunctionObj>::value;
          functor.members.obj_ref.is_volatile_qualified = is_volatile<FunctionObj>::value;
          return true;
        }
        template<typename FunctionObj,typename Allocator>
        bool
        assign_to_a(const reference_wrapper<FunctionObj>& f,
                  function_buffer& functor, Allocator, function_obj_ref_tag) const
        {
          return assign_to(f,functor,function_obj_ref_tag());
        }

      public:
        vtable_base base;
        invoker_type invoker;
      };
    } // end namespace function
  } // end namespace detail

  template<
    typename R BOOST_FUNCTION_COMMA
    BOOST_FUNCTION_TEMPLATE_PARMS
  >
  class BOOST_FUNCTION_FUNCTION : public function_base
  {
  public:
#ifndef BOOST_NO_VOID_RETURNS
    typedef R         result_type;
#else
    typedef  typename boost::detail::function::function_return_type<R>::type
      result_type;
#endif // BOOST_NO_VOID_RETURNS

  private:
    typedef boost::detail::function::BOOST_FUNCTION_VTABLE<
              R BOOST_FUNCTION_COMMA BOOST_FUNCTION_TEMPLATE_ARGS>
      vtable_type;

    vtable_type* get_vtable() const {
      return reinterpret_cast<vtable_type*>(
               reinterpret_cast<std::size_t>(vtable) & ~static_cast<std::size_t>(0x01));
    }

    struct clear_type {};

  public:
    BOOST_STATIC_CONSTANT(int, args = BOOST_FUNCTION_NUM_ARGS);

    // add signature for boost::lambda
    template<typename Args>
    struct sig
    {
      typedef result_type type;
    };

#if BOOST_FUNCTION_NUM_ARGS == 1
    typedef T0 argument_type;
#elif BOOST_FUNCTION_NUM_ARGS == 2
    typedef T0 first_argument_type;
    typedef T1 second_argument_type;
#endif

    BOOST_STATIC_CONSTANT(int, arity = BOOST_FUNCTION_NUM_ARGS);
    BOOST_FUNCTION_ARG_TYPES

    typedef BOOST_FUNCTION_FUNCTION self_type;

    BOOST_DEFAULTED_FUNCTION(BOOST_FUNCTION_FUNCTION(), : function_base() {})

    // MSVC chokes if the following two constructors are collapsed into
    // one with a default parameter.
    template<typename Functor>
    BOOST_FUNCTION_FUNCTION(Functor BOOST_FUNCTION_TARGET_FIX(const &) f
#ifndef BOOST_NO_SFINAE
                            ,typename boost::enable_if_<
                             !(is_integral<Functor>::value),
                                        int>::type = 0
#endif // BOOST_NO_SFINAE
                            ) :
      function_base()
    {
      this->assign_to(f);
    }
    template<typename Functor,typename Allocator>
    BOOST_FUNCTION_FUNCTION(Functor BOOST_FUNCTION_TARGET_FIX(const &) f, Allocator a
#ifndef BOOST_NO_SFINAE
                            ,typename boost::enable_if_<
                              !(is_integral<Functor>::value),
                                        int>::type = 0
#endif // BOOST_NO_SFINAE
                            ) :
      function_base()
    {
      this->assign_to_a(f,a);
    }

#ifndef BOOST_NO_SFINAE
    BOOST_FUNCTION_FUNCTION(clear_type*) : function_base() { }
#else
    BOOST_FUNCTION_FUNCTION(int zero) : function_base()
    {
      BOOST_ASSERT(zero == 0);
    }
#endif

    BOOST_FUNCTION_FUNCTION(const BOOST_FUNCTION_FUNCTION& f) : function_base()
    {
      this->assign_to_own(f);
    }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    BOOST_FUNCTION_FUNCTION(BOOST_FUNCTION_FUNCTION&& f) : function_base()
    {
      this->move_assign(f);
    }
#endif

    ~BOOST_FUNCTION_FUNCTION() { clear(); }

    result_type operator()(BOOST_FUNCTION_PARMS) const
    {
      if (this->empty())
        boost::throw_exception(bad_function_call());

      return get_vtable()->invoker
               (this->functor BOOST_FUNCTION_COMMA BOOST_FUNCTION_ARGS);
    }

    // The distinction between when to use BOOST_FUNCTION_FUNCTION and
    // when to use self_type is obnoxious. MSVC cannot handle self_type as
    // the return type of these assignment operators, but Borland C++ cannot
    // handle BOOST_FUNCTION_FUNCTION as the type of the temporary to
    // construct.
    template<typename Functor>
#ifndef BOOST_NO_SFINAE
    typename boost::enable_if_<
                  !(is_integral<Functor>::value),
               BOOST_FUNCTION_FUNCTION&>::type
#else
    BOOST_FUNCTION_FUNCTION&
#endif
    operator=(Functor BOOST_FUNCTION_TARGET_FIX(const &) f)
    {
      this->clear();
      BOOST_TRY  {
        this->assign_to(f);
      } BOOST_CATCH (...) {
        vtable = 0;
        BOOST_RETHROW;
      }
      BOOST_CATCH_END
      return *this;
    }
    template<typename Functor,typename Allocator>
    void assign(Functor BOOST_FUNCTION_TARGET_FIX(const &) f, Allocator a)
    {
      this->clear();
      BOOST_TRY{
        this->assign_to_a(f,a);
      } BOOST_CATCH (...) {
        vtable = 0;
        BOOST_RETHROW;
      }
      BOOST_CATCH_END
    }

#ifndef BOOST_NO_SFINAE
    BOOST_FUNCTION_FUNCTION& operator=(clear_type*)
    {
      this->clear();
      return *this;
    }
#else
    BOOST_FUNCTION_FUNCTION& operator=(int zero)
    {
      BOOST_ASSERT(zero == 0);
      this->clear();
      return *this;
    }
#endif

    // Assignment from another BOOST_FUNCTION_FUNCTION
    BOOST_FUNCTION_FUNCTION& operator=(const BOOST_FUNCTION_FUNCTION& f)
    {
      if (&f == this)
        return *this;

      this->clear();
      BOOST_TRY {
        this->assign_to_own(f);
      } BOOST_CATCH (...) {
        vtable = 0;
        BOOST_RETHROW;
      }
      BOOST_CATCH_END
      return *this;
    }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    // Move assignment from another BOOST_FUNCTION_FUNCTION
    BOOST_FUNCTION_FUNCTION& operator=(BOOST_FUNCTION_FUNCTION&& f)
    {
      if (&f == this)
        return *this;

      this->clear();
      BOOST_TRY {
        this->move_assign(f);
      } BOOST_CATCH (...) {
        vtable = 0;
        BOOST_RETHROW;
      }
      BOOST_CATCH_END
      return *this;
    }
#endif

    void swap(BOOST_FUNCTION_FUNCTION& other)
    {
      if (&other == this)
        return;

      BOOST_FUNCTION_FUNCTION tmp;
      tmp.move_assign(*this);
      this->move_assign(other);
      other.move_assign(tmp);
    }

    // Clear out a target, if there is one
    void clear()
    {
      if (vtable) {
        if (!this->has_trivial_copy_and_destroy())
          get_vtable()->clear(this->functor);
        vtable = 0;
      }
    }

#if (defined __SUNPRO_CC) && (__SUNPRO_CC <= 0x530) && !(defined BOOST_NO_COMPILER_CONFIG)
    // Sun C++ 5.3 can't handle the safe_bool idiom, so don't use it
    operator bool () const { return !this->empty(); }
#else
  private:
    struct dummy {
      void nonnull() {}
    };

    typedef void (dummy::*safe_bool)();

  public:
    operator safe_bool () const
      { return (this->empty())? 0 : &dummy::nonnull; }

    bool operator!() const
      { return this->empty(); }
#endif

  private:
    void assign_to_own(const BOOST_FUNCTION_FUNCTION& f)
    {
      if (!f.empty()) {
        this->vtable = f.vtable;
        if (this->has_trivial_copy_and_destroy()) {
          // Don't operate on storage directly since union type doesn't relax
          // strict aliasing rules, despite of having member char type.
#         if defined(BOOST_GCC) && (BOOST_GCC >= 40700)
#           pragma GCC diagnostic push
            // This warning is technically correct, but we don't want to pay the price for initializing
            // just to silence a warning: https://github.com/boostorg/function/issues/27
#           pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#         endif
          std::memcpy(this->functor.data, f.functor.data, sizeof(boost::detail::function::function_buffer));
#         if defined(BOOST_GCC) && (BOOST_GCC >= 40700)
#           pragma GCC diagnostic pop
#         endif
        } else
          get_vtable()->base.manager(f.functor, this->functor,
                                     boost::detail::function::clone_functor_tag);
      }
    }

    template<typename Functor>
    void assign_to(Functor f)
    {
      using boost::detail::function::vtable_base;

      typedef typename boost::detail::function::get_function_tag<Functor>::type tag;
      typedef boost::detail::function::BOOST_FUNCTION_GET_INVOKER<tag> get_invoker;
      typedef typename get_invoker::
                         template apply<Functor, R BOOST_FUNCTION_COMMA
                        BOOST_FUNCTION_TEMPLATE_ARGS>
        handler_type;

      typedef typename handler_type::invoker_type invoker_type;
      typedef typename handler_type::manager_type manager_type;

      // Note: it is extremely important that this initialization use
      // static initialization. Otherwise, we will have a race
      // condition here in multi-threaded code. See
      // http://thread.gmane.org/gmane.comp.lib.boost.devel/164902/.
      static const vtable_type stored_vtable =
        { { &manager_type::manage }, &invoker_type::invoke };

      if (stored_vtable.assign_to(f, functor)) {
        std::size_t value = reinterpret_cast<std::size_t>(&stored_vtable.base);
        // coverity[pointless_expression]: suppress coverity warnings on apparant if(const).
        if (boost::has_trivial_copy_constructor<Functor>::value &&
            boost::has_trivial_destructor<Functor>::value &&
            boost::detail::function::function_allows_small_object_optimization<Functor>::value)
          value |= static_cast<std::size_t>(0x01);
        vtable = reinterpret_cast<boost::detail::function::vtable_base *>(value);
      } else
        vtable = 0;
    }

    template<typename Functor,typename Allocator>
    void assign_to_a(Functor f,Allocator a)
    {
      using boost::detail::function::vtable_base;

      typedef typename boost::detail::function::get_function_tag<Functor>::type tag;
      typedef boost::detail::function::BOOST_FUNCTION_GET_INVOKER<tag> get_invoker;
      typedef typename get_invoker::
                         template apply_a<Functor, Allocator, R BOOST_FUNCTION_COMMA
                         BOOST_FUNCTION_TEMPLATE_ARGS>
        handler_type;

      typedef typename handler_type::invoker_type invoker_type;
      typedef typename handler_type::manager_type manager_type;

      // Note: it is extremely important that this initialization use
      // static initialization. Otherwise, we will have a race
      // condition here in multi-threaded code. See
      // http://thread.gmane.org/gmane.comp.lib.boost.devel/164902/.
      static const vtable_type stored_vtable =
        { { &manager_type::manage }, &invoker_type::invoke };

      if (stored_vtable.assign_to_a(f, functor, a)) {
        std::size_t value = reinterpret_cast<std::size_t>(&stored_vtable.base);
        // coverity[pointless_expression]: suppress coverity warnings on apparant if(const).
        if (boost::has_trivial_copy_constructor<Functor>::value &&
            boost::has_trivial_destructor<Functor>::value &&
            boost::detail::function::function_allows_small_object_optimization<Functor>::value)
          value |= static_cast<std::size_t>(0x01);
        vtable = reinterpret_cast<boost::detail::function::vtable_base *>(value);
      } else
        vtable = 0;
    }

    // Moves the value from the specified argument to *this. If the argument
    // has its function object allocated on the heap, move_assign will pass
    // its buffer to *this, and set the argument's buffer pointer to NULL.
    void move_assign(BOOST_FUNCTION_FUNCTION& f)
    {
      if (&f == this)
        return;

      BOOST_TRY {
        if (!f.empty()) {
          this->vtable = f.vtable;
          if (this->has_trivial_copy_and_destroy()) {
            // Don't operate on storage directly since union type doesn't relax
            // strict aliasing rules, despite of having member char type.
#           if defined(BOOST_GCC) && (BOOST_GCC >= 40700)
#             pragma GCC diagnostic push
              // This warning is technically correct, but we don't want to pay the price for initializing
              // just to silence a warning: https://github.com/boostorg/function/issues/27
#             pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#           endif
            std::memcpy(this->functor.data, f.functor.data, sizeof(this->functor.data));
#           if defined(BOOST_GCC) && (BOOST_GCC >= 40700)
#             pragma GCC diagnostic pop
#           endif
          } else
#if defined(BOOST_GCC) && (__GNUC__ == 11)
# pragma GCC diagnostic push
// False positive in GCC 11 for empty function objects (function_n_test.cpp:673)
# pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
            get_vtable()->base.manager(f.functor, this->functor,
                                     boost::detail::function::move_functor_tag);
#if defined(BOOST_GCC) && (__GNUC__ == 11)
# pragma GCC diagnostic pop
#endif
          f.vtable = 0;
        } else {
          clear();
        }
      } BOOST_CATCH (...) {
        vtable = 0;
        BOOST_RETHROW;
      }
      BOOST_CATCH_END
    }
  };

  template<typename R BOOST_FUNCTION_COMMA BOOST_FUNCTION_TEMPLATE_PARMS>
  inline void swap(BOOST_FUNCTION_FUNCTION<
                     R BOOST_FUNCTION_COMMA
                     BOOST_FUNCTION_TEMPLATE_ARGS
                   >& f1,
                   BOOST_FUNCTION_FUNCTION<
                     R BOOST_FUNCTION_COMMA
                     BOOST_FUNCTION_TEMPLATE_ARGS
                   >& f2)
  {
    f1.swap(f2);
  }

// Poison comparisons between boost::function objects of the same type.
template<typename R BOOST_FUNCTION_COMMA BOOST_FUNCTION_TEMPLATE_PARMS>
  void operator==(const BOOST_FUNCTION_FUNCTION<
                          R BOOST_FUNCTION_COMMA
                          BOOST_FUNCTION_TEMPLATE_ARGS>&,
                  const BOOST_FUNCTION_FUNCTION<
                          R BOOST_FUNCTION_COMMA
                          BOOST_FUNCTION_TEMPLATE_ARGS>&);
template<typename R BOOST_FUNCTION_COMMA BOOST_FUNCTION_TEMPLATE_PARMS>
  void operator!=(const BOOST_FUNCTION_FUNCTION<
                          R BOOST_FUNCTION_COMMA
                          BOOST_FUNCTION_TEMPLATE_ARGS>&,
                  const BOOST_FUNCTION_FUNCTION<
                          R BOOST_FUNCTION_COMMA
                          BOOST_FUNCTION_TEMPLATE_ARGS>& );

#if !defined(BOOST_FUNCTION_NO_FUNCTION_TYPE_SYNTAX)

#if BOOST_FUNCTION_NUM_ARGS == 0
#define BOOST_FUNCTION_PARTIAL_SPEC R (void)
#else
#define BOOST_FUNCTION_PARTIAL_SPEC R (BOOST_FUNCTION_TEMPLATE_ARGS)
#endif

template<typename R BOOST_FUNCTION_COMMA
         BOOST_FUNCTION_TEMPLATE_PARMS>
class function<BOOST_FUNCTION_PARTIAL_SPEC>
  : public BOOST_FUNCTION_FUNCTION<R BOOST_FUNCTION_COMMA BOOST_FUNCTION_TEMPLATE_ARGS>
{
  typedef BOOST_FUNCTION_FUNCTION<R BOOST_FUNCTION_COMMA BOOST_FUNCTION_TEMPLATE_ARGS> base_type;
  typedef function self_type;

  struct clear_type {};

public:

  BOOST_DEFAULTED_FUNCTION(function(), : base_type() {})

  template<typename Functor>
  function(Functor f
#ifndef BOOST_NO_SFINAE
           ,typename boost::enable_if_<
                          !(is_integral<Functor>::value),
                       int>::type = 0
#endif
           ) :
    base_type(f)
  {
  }
  template<typename Functor,typename Allocator>
  function(Functor f, Allocator a
#ifndef BOOST_NO_SFINAE
           ,typename boost::enable_if_<
                           !(is_integral<Functor>::value),
                       int>::type = 0
#endif
           ) :
    base_type(f,a)
  {
  }

#ifndef BOOST_NO_SFINAE
  function(clear_type*) : base_type() {}
#endif

  function(const self_type& f) : base_type(static_cast<const base_type&>(f)){}

  function(const base_type& f) : base_type(static_cast<const base_type&>(f)){}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
  // Move constructors
  function(self_type&& f): base_type(static_cast<base_type&&>(f)){}
  function(base_type&& f): base_type(static_cast<base_type&&>(f)){}
#endif

  self_type& operator=(const self_type& f)
  {
    self_type(f).swap(*this);
    return *this;
  }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
  self_type& operator=(self_type&& f)
  {
    self_type(static_cast<self_type&&>(f)).swap(*this);
    return *this;
  }
#endif

  template<typename Functor>
#ifndef BOOST_NO_SFINAE
  typename boost::enable_if_<
                         !(is_integral<Functor>::value),
                      self_type&>::type
#else
  self_type&
#endif
  operator=(Functor f)
  {
    self_type(f).swap(*this);
    return *this;
  }

#ifndef BOOST_NO_SFINAE
  self_type& operator=(clear_type*)
  {
    this->clear();
    return *this;
  }
#endif

  self_type& operator=(const base_type& f)
  {
    self_type(f).swap(*this);
    return *this;
  }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
  self_type& operator=(base_type&& f)
  {
    self_type(static_cast<base_type&&>(f)).swap(*this);
    return *this;
  }
#endif
};

#undef BOOST_FUNCTION_PARTIAL_SPEC
#endif // have partial specialization

} // end namespace boost

// Cleanup after ourselves...
#undef BOOST_FUNCTION_VTABLE
#undef BOOST_FUNCTION_COMMA
#undef BOOST_FUNCTION_FUNCTION
#undef BOOST_FUNCTION_FUNCTION_INVOKER
#undef BOOST_FUNCTION_VOID_FUNCTION_INVOKER
#undef BOOST_FUNCTION_FUNCTION_OBJ_INVOKER
#undef BOOST_FUNCTION_VOID_FUNCTION_OBJ_INVOKER
#undef BOOST_FUNCTION_FUNCTION_REF_INVOKER
#undef BOOST_FUNCTION_VOID_FUNCTION_REF_INVOKER
#undef BOOST_FUNCTION_MEMBER_INVOKER
#undef BOOST_FUNCTION_VOID_MEMBER_INVOKER
#undef BOOST_FUNCTION_GET_FUNCTION_INVOKER
#undef BOOST_FUNCTION_GET_FUNCTION_OBJ_INVOKER
#undef BOOST_FUNCTION_GET_FUNCTION_REF_INVOKER
#undef BOOST_FUNCTION_GET_MEM_FUNCTION_INVOKER
#undef BOOST_FUNCTION_GET_INVOKER
#undef BOOST_FUNCTION_TEMPLATE_PARMS
#undef BOOST_FUNCTION_TEMPLATE_ARGS
#undef BOOST_FUNCTION_PARMS
#undef BOOST_FUNCTION_PARM
#ifdef BOOST_FUNCTION_ARG
#   undef BOOST_FUNCTION_ARG
#endif
#undef BOOST_FUNCTION_ARGS
#undef BOOST_FUNCTION_ARG_TYPE
#undef BOOST_FUNCTION_ARG_TYPES
#undef BOOST_FUNCTION_VOID_RETURN_TYPE
#undef BOOST_FUNCTION_RETURN

#if defined(BOOST_MSVC)
#   pragma warning( pop )
#endif

/* function_template.hpp
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
*/