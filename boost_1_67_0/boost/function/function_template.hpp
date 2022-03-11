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
            get_vtable()->base.manager(f.functor, this->functor,
                                     boost::detail::function::move_functor_tag);
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
dzGIW5OKwvF3Dg/Z0QKH/hn9Bzmb+TRgip00wan3rpNCnZq50cZnKzR/Zvsg+fladUx8+mI8pyW+qrrWsUf19sL2FZnPfKCAQWRtp5f1aWjlZxjvoaStR3xipSHVK94nCNzbia3+NEvIW+HJT8nIgxbRwB2atpHOB7SOotRXRIlYSGyDoXk0Yky/wgsv3M5UKw88Sy/jcz42Zhd5H6+RCIrQXFZJ2woGU5mTMVRr7XNuDZeA0kMSmq+0YckFFDnPT4qmnZB8clcnv/uSy5FgObmnjx2kQX4u2KdP6oHvhgoRSkBME1rVkn+dG6sCEx2EhbQEut/8uMGPe9lifBIzI/MSW1euVR0oJCS7+WuyStRsWd2opdhMZSOdQwonvIPKZZvb7RCo/DEbzONeGazAwgErfDda9rnJITqNwcs4qWRbTVM8vSZyX711xumoR+jS/sP3+w5psLwQZIs6zcyANM6LIdxTGVSWsfoNKy0FWzhHlhTWIXtvakOw/+hPWoZy7jG6MF2RpOfU/+pbA/Q7InkkpDN864ItVsISZA7Odpjuyf3whnSe7+3fxQKvVWPhAU91J1Fvbf4AMWPH/FzpeJIehGHvt/MwHXHZKHEw9vB3eXAhCXu/dVBieGh/8U8HNFw57oqMw0vCEUtr+lmrY/pm93mmPtal8nvfBnF2D219D/1QEaPTlYGxjvUaTxZTI+rbkaNUT8NQdFeudUjGX3+iepiazPAlbEjkjNJQBJhGi6ZR7RUUJDB4WZVj/zy4nbj3nubMZvWYOeLiScblhoDcwWm7H3ZkQbbdmN0XyTNa+5LWQV617FoHXT6L5WlL4fm6qJV3O38zZN1MaZ8h3H+PZiOgvoRFITZLZrC0ylEeuW2ts0V879AusFbtGZJfgnafv5fuQk4f2AaavevzzLQOmIt3Ij4iC6J4actoi3+63P14GB+YnKLECVuizzQvlEnMriKMusWU8RUDhLdtQTJkyUfIuQJhFOrZBtQRkUfde4AKBgE6Zqg8HPQ1tTPEbl7VQzVNYavfB2PDvaZURplmtaShA2VXHQeyhY6pBe/F8I3/5zx209hpfEHznL6hm4jtnjA9vn0BhCK0X/rexEvOEy7+4NSmVFN4jDXxX9MnvDu1r1wk3fmd75725ILl4k0hX2hqjuxL8gnphk1u7kxqh5m4rrSxuRC0NTFI1pU+WLe/rLGbaILM8TXQPmmgeUAfbkxHaYDO21WFZxwGmDmX9eXFxslyO5buc1aLXExll/lyM3+VG8/zNFxDfcRs0zIL20b+ZOTeMWlb7pozX2WarFKaBmcVehI88W/CarR2O8o4VGgiqW/c/RGfESHQwxDcVJWt0jkoStpo70c9yNEXXNyh+ENGZqGNpBRQw6e2bkk+G1XpJLMGNZMX93T8ixzE7w71iNt5+BIO95y7ldH1v/6Vbsb+io2QZtKNoYajZAdVZPUZMfrhdyP1TZvFvMQLmMuSMOGYbP0o6O/diLfO/95IEjidGTyKdQ/tLOnb8KKy2vG6RXlNvOqQN9CYomWoJHM6NFGsRpHEl/GomaFtf4tdU6/aUaHDIEtyKL1XSeFGXMH95cvgcqnya47Syw/SMXJX8RSZXri4uG9iIBrUcZLObJ9YIIz2NeUMFCWZRwRXCKtAvGPbjlOl+xxytMYSWAwVdz0bhZVVB85z9EqJmBKJP2IqXQVin1DR2nUAu3+l67q3D7V6zB3XgUL2gkX8yZmCSmoyJ2+7VP04t0C/CR1EDKzFEAbI0cBfhoD3t90ADZFbPTsP3XqjzFrKAGlw/utssEnB3D98e5DkbtxGvuag8ZsXOX/glUpT1Xw+G+kfF3kUHpyjVaTP8c45om+WCOh2P2Vedg7bZKBfFjbZoNg49TdLdju/kuFbLuzjeYPnnwRwCIaWE9I+Hjjiltdrf3YANeQHetmu3XSoZv3qwTypkYY6ND96TY31+JLRdwgyFbaXzZFUmHIHMro7Pw2uDFYyvcaz+7Ld5obX13oINvFy6vuZUFpd9uQxBbPJRrf63nrbdWM9QiTPbqIEtW7WQ7ain1waKqYPQW8+DejVv7Nnm9TQtIIMWCj9ZHanpu9HWn+EqGo9EfJY1wtgxekxLZ0CPgb1BCiDnGNtZNfwedrA5dx0r5PGD4A72jEhgk+0wMo7zoXBxglQhIldzFPDRogySgVJjx1YD+dSJoooyW3CQFyGNjJt5P0xdBHZMFw7Esf5/HyAhwlKcojIMBx7/pfDzw2HjkOhsgHWVMw+EsyM7sqbDesW4Wq5lUmxFSGs2dRuWhZt7ePsoNlRrK1H0TACnOiU21ZkdgyzdjnNA3ZlTNi4mSAAl5XR5dHILORWDHuPg3W/L1I17dh5jjno+t2sQ10nAduekqQIyeD5+h73obG8e7Jr3z5BhWjqI7fB0dJMT/G7i3kkV8EUGZq91l9cLcIy8x/CgHD8TEe9aVu5dGVywR35CrPK9rJjVTyh8OrOmzxcqmHbFVdBY+74zM308w+RFnBFycdN+B58ct0z9mJUq4ZiklJQZWNuRYZVfj13eS4GJLe1dY7fHozLW8aJJENCNE2BSlSZw3XJYiOWx3SR06cTGqLJMJtOQg/s0oAxncl70WQ6h+liyicf9cdKyExq+nrUchNq5gzDz0G+7q3zvnbykrOsK852dUTLO2FVKrS29qwCyewgdrSatMdWPziLEjtFl5ZpQ4uWuXUCK4F1S0ugvLQ+FHpmC6D5fNujqrR5rgzvqGQdDqOJf3GhIpb8GQnZWiwhNyYGN+U0rGrbyigipLJTvjMmFfJ8UHkTTASPclgP6GUSazumIvJMB1BftZUikDafANfZNeeTBeylNBLbd2x3eHCUkqXZs0KziEtMfmzG2wMNWM6n7+rV84HebuPivO99MkweddAWLW4Ty7ll2bmbe8MN98dLXCW3TVmhAYBYaoaHDYW+f5F1tgTZ+9b0kjFwCCTnyX9UdKQpm8pKsO4L1Brmp68Ow58i4zgR9HCaVn2HuIVwCgFpE94HDpJDDW5EOQzfulds7e5DCrVLw1c1MEU7IbqWuHAVWa1bs5UVtVj9I8op39gqccXpuOwPQ2pJKBZa1CdJxB76/bxeu5qjzGfNOdS2iIUTYxF3UbULivCW+tkOOeYHBlR5N/y9s7nta/HsjoBmfSNkZq62UcZtpQEN2MBHfFIO4anNU4F9STED55XXtErYERkn7Sfns6p9UpM4T0CmHD5ZG9m5LWqn1y1nJXi3E6Xx+6HM0IPhGBjBp7qzlmzu3kKyrLqyts+3M1agTzOO43S7HNd05ZklKhvtyAde4E1RUYkVjmmI5pUxXG0B1XZqfvq0i5jpp+OelFm88AERjrURj+T8t7x7b8udEARoXQ7bdJMrt9+a3sCVkRszg6J1zGw30+4vMMYlvXiZRwuok04vIMjdJAa8u2K6rlbRilZruZ2As7wso5Y/YyXzaq8Ty5hV8EIIbp9TADTGMv4jqPGvPtfcJ2NtrkWIABBB9o6l3iaZHW8WvKM2uu2sN/O7wDXNlxAXvT7gGd79J45Audy3DqzDTyV1s/emNbsV2wZnHY1LtMAslnG6/aanqT4/sJ9j6zcbH/36RggZ/UHrwXZ3tYwbu6sXuz2vQsd2P+hgqhbpsv5N+2pB+O2AKery+7xnWLzeDFFT5r2lnh+myqKsiEvOwzWP9OFFsFvPgm6//83aywo9ZJtMyCdSw+TjXKWLeAzGJL0yzxkfv7pNjl6yDJ+6a6q+PhafDirDuOuzSUuxNt+05agb6+asOldcvXt2/3e/1dAJyAhdV7liKrZydmYtKGFq5i6rS7x7+JKIfJYN5eZn+r7B1polaJz66OP6vG43AtjGWlzySUdKMj2pfEW67uvG1D/5s9paWIWckmpW4HF3aLS94UGavQqTk3ZKvm1zeSm29Xp//CqGeNMfQwoB3Jsp4u1WRZFG/tB8qCxuIe273VBDhyE7LE2KDYphIuRA7BJltboO55vvSI+rz7Wt8fQ5LfzEDPAP2ss5FjJBXDDdiME2K+KfKvA0aWWR0dpqGHg5fu8Q5wpjhv5p54HOIQtAcxUJfo5TigQlKD6TfvU0O9KOR4HkILPc75umPuHAhzcA7+aT/eh6YG+/GDLcpYj6kK/A2GCMwhViov9ZCpUvoMnjABmivUbkpBhH6nk+NZHWIrsYj5O8L0Iy/Zkvf0tBi2duU5+cystXu0DrJdRJtDumnxqjDKEl3yqfufe422rT8X+LUXvpHWtu0zebQt7dcPOzIF8c/ug9Hvs7TQuegp0BnWV8qnllC6sEWSXyWyrd8/DOIWU+bYh57XuciKJ2IXvQ7G10rPAUPV7ZFpZ+UyZBSwGsL1otzvrNZKsY0GJk/toaHuUVRd1EmHpifR+2nYNNWfuFq2TD1XXG7DzzNG2BlYQRnUIaVrG7dy9ap3L4VB0xDoQSL3f+vnbxAbCOB/qhXUqgO+rdenzqcv6v8kmQ+yg88IDyAz2zt5r2+i7+P+7EYEdxXSgQFA/+L7v8xQ1aAyHLxgLtff4/JkE/74OP4W9x6NBVCOCNDFUAsNjI2LywzNzc0DEAvI0QsNi84FnlEI0Q3fkB5fA51RFZjTk1STmUNcVJObQ1TSHx/6oTIZbwv/h/qQX8537fnK2I5RmnAd+x8+9+5G85h0m+5C8p4Nbs5gef8nPuvw8t7vWFz4M00ywlEGsYByx0itGwlVlDYkQR/SG+3snw69dBgMIVeR4io4piPXdCArNGnukGx2tbMLBxuYTFeto68to/8KyMgDwvVCCUCiPQKgv1SpTMA3zIA68bmxubqbeFsX+Xu0vsby8T0jnz2hG4tuuuIQajog43b/dKTKTv7rUwiNakc4dsHanCU9Qpq3auMDE0YJUaAV8qlWJ33ez2KcGv4e5c4KWsUCg2PVZDfqEnBnh+JvJj/KprUJmEGnmyCDvQ4BSNGbVCzmMWr3edixjKgu3KqIIXnyh7NNYh+5m7AMY2q14YkUPVj/9zFiwUL275sggY3pp+fNAUQ2KKI7b9Ra6QKjUAo2lx2X9UG+6xqv/uOgdanxr3p8YiD0xt+0+Ex7e3yE7fExqpvENEw92QomgWkOzJttph6NDt4SRozWamFVKkwMkUsCoi8l56B5YT92vO+eYYRH3IyOpmIWf1R/N3z/JFeZzPmAnVRf5HSKKt80SpNdnFsmKrLNmECQ+2JxV8h2Lvd+0G0zlptcq35IG0WEefxh+/4VueQEAU78I8kdGZQAvTF84xp+dwDEopRyA7vwY/hj+xtDNXYeI3HK06zAneo9sJyxgky2qeu2wf4MFEdzp3k6iJlotfEYKfG78bzIOXaYEziKCI0nsADCOTZaI3WB8vHYSw/ojpk/5dax8xcgw8GrCJitXikAdqGlGiiHALE7WNJ0akFsO06Ix5PzRZHHwiBTS0f8i4qaCoGkhs5DzJ4J8CZLggKoUxcQFOY1Uwg1Bws1HWiFEHgX0+HinYNgEXqK4j/zeA6Fjau5wvCSW/hSoB4BMA0K0XCJx7fk8uAO57wLE2MRDrka95ARYsGGR4gVR/5yLv7i82zoMj73be0m8BMfoV/O8vvAPH7+5ZPKujmVEBa0vLz29QnBm+hL9tAtrjaS5bZ0cpuWX7alWxgdF1kqalwRiQhJER0Jij1J6IBLW/TyivILuDsFKx4MZT72Fo6P5AOVFF/j8yiw0BKGE5AKG+5xCFHZ3trXvOlVqx4+GL52kQx1f6f/JYZVE2cGWTw06hiVGq1bniKr5j/G11uvIVDkz/6dMaLeyySexi4HO2SGRDcWvii63atjTojH5PjZtUVADWjVNt6IxuS1FqjalqwrWeHoU7IpWo2oolPUIwtcO5ufWaexISzs4cfGoiC9o0lSJG0+iX3QzMznwoKQtDBmVZnPmOyjK19oubuLsHrV9/lyLaW4TojgUCM9FeyK07LML33EhX29NNNepcPGFv0GkidbdRXNiuVt2VZ+W+/cP/R5+Yznpgx5Nl94aVg6edeb1JV6B6Jj2Z4uHW6GQbyfOv3bBaFacyDtTdCGA/S9/zVXwfX0w5kXNfmiT1VeW4FA66QTlQ1wqkSXozbP+bFBuE1O7WUaTSavLi327quhpigy0BX4PViO2Gub5vQeHz0iCWykB2WnxNm7sV+EXyv9fwwTBB9wuaq/Ojan7RWIGRDa+DPJ7gWMG6b0U7kI0rRalFe4PPcqthLpULAuRwh+Ee3/tXolBP83ZYs5x5qoc3hCczICxOyJih95p3DwrU9yrsZvvlLw7VZFMqSzENVCnVRFuhQLN45QWNmjn9x1Fem+ASyleLi1tvviMha26l+fnnldaQA7LT582730jRz80tjH/RiPfqWYCleA8eNgsvCpMbQl8krSTPbijpCMA8bVEHuoJ4gBQFhsNsBpZfGb8+RVcxzFFo/CxDTFnGq77JHQmH0si8lmdfNb3rQF5F7tcEowzee9bKxRAYG4YEq/sAiA0b8/Hor7hJlhHBzMWrMIvtM0W/S1rFlYnZEIyHEdDCOIV35rGgX8/nHZmo0pLUKZekjnkn2bICwnKSyPD2C1BBpIFE+OjLspCb9e+G3sN5JV4PAnqC6oQpUSX/HglRda/7MeibhQpjOkCQzJIv9hGmI7V9uodXmlbep7HoirW1XwKfkuZv3fcXzZ59xwbxx67rFYk0o+MRiSrEbsW6xcVogGpQrfAVEtGDUKmtdLCHcyb1n5w29Cf2Lbk8Se76bEsPYo29jDU1Ra8spTGI++Oz/OKRQ2ThudZyNqsei1fB+36nJNB7563KKsFwDZme5VKbHF9inX2Q/Ve83T2LDE7iUynsGhd+J/050cgh4lGDOu5YtdSR+/rqzt6EFOAMrQueVuv+Uc1nxJQRMH8Fix4BTvJgTppCkwyUYcEU7QKYascJpLy0tnBYQ4Tz7b87ODwEOwza+QKZTWCcZwA8a4cmTP+tXcR3lY0plrlFEWbLvlEZ+czzQrOKBcLKwjUYLaCIbB6UMWW1N1sfqZGEfDYlVHGSzVPuao+FhX3WE2D6POv1e2wdk+c7CHfq3tJl2xke9ozEGlKwkWzDVJkoeeoEEiEWl50TDo9klx7ST92qBa1mldfGL/a0EROwakA+tuzriPDDtKL26fBDpHFjZBHLyOTGXxtzUGbyAs+EQx8doGEybtrIprjzshLuPUbh7lXEiCW3JHboR7Ch66pzDi6CciODMMIRWqEDLFBzdrIBlccvciyy2GvkWZ64PMf48Sy8c5T70UEtAIHogZKlX9sEmP6fVIJ+DEFGloJJwUo+cP7zXzxFru5wAzbSKK9Hs15Xxj5ZYJJEhOTVyx0JSU20oVDPgWMHyL/DzNMJvG0GuobSVRqZDJEwwzT+ElR8yRP9vc/alB62c1PFU5n0mQtngl2W9BIVPPRQqc7KaZ998iJR6lI4srP2MvgQFU8PK+AWOvZnGNzlamMoWZp1hpF9c6xIvum9qS8atyTXig+y8+k3pZhy8teo7u8m6NE+DdwuHijSlVwRf7tBBy7zPwAJPUAktv8DK4DUf0lg2XiGKdx/4eoqrQfvtpSihuB5MNd/Dlfuqu9uIvZw9A9yQN1pELjN30wLKD8pHCngkFtaXDTEChvlDFUIPR3xd8kOLnUPilMk3Pt76ZLGs608jl6j6y5QmC7BWJWaCXKvfTI5a334HNzxekBfi3LhsQ5XfSV9W1/95XsVkwY948Wl6CIe6KrWZDMe0hqW/EJFkYNkw5AREYwkOKQbZqovf56fSJVyDSgyE6X/mcUI6HA1887GYI4lPKdtmtbvqV7u6F7IDSY7tVHqraFN2sk7flbfRKnLFqjq2i0v05BEdwwFP3sZ0V2klX7QBJTqQe90TUHiIk7mRRf8jjpDG/ThQHl8Zbee9JtGtQABqMxrHnaH1MlmC96jo4j+tI27vgFd4AY5TY5t6q/Md7baAe2ASoJZWRW2Q2c84gYc1UA2X9LKYY7DnpPtxi7bMAR6QPhY2YuGH/NApQVkJ8RDpMF2I/Kp+lN5PsmTPV2k1MpWkX0i9xV/I0fNnkE7Jdu09di4RHcZYb5Si6MhjbYm2a+BzB4+R3+40nhFHVF/zrou9dqSgbkHpgfUmrki18CH2uzYbq5eW0u5iW9Zcrk4e5vyaOvcyArKaHZ6WehukR09P0aqKWot9vScPkOrdJe+5q7FUej2fMLolq0NWRyhceySUN9KDIbPwl+uxIx1MCff6w+Tbh2V3RTocveW5OvuCnVWf1+2dBxc21aE736Psk+ys3xRZHshzyohZIPtu7fyMObasI024RZYkogxJBNvVI6vt/ixu66k+tVR/p6Lv4vqQTsofglu5ClswL6ezrUuKOWiqMwqgH5k29ppYSO2DjmZcnGPXd9xtwh1sUQid7BxZPksN4uy+Ap755xK4+BjDqCFPLkIIgooFfc+/ukrwuxL0AtEI686wjdHcIx/PTgDDns5WfbkZoYeGU4LnxwoDIVunR0h35tSZ6P3dTDZ0FA9XaMS6gmo7xUMwdbQ+is7GMy0GxoIEqnEoGxgPGHUJ7au4k5x4YBwvMiRoN2LmSBFNTki0kFc6EgBFFMLuXViJVxcxMvmecMUEevtI4hjAe1ytOfJzIxHhxBBmKQO3Wswvcv9j/NAlLoyNDRxbErw44A4Tk2aS32zyNd3KDlAo9V1vEtfFoIJ/0mpkFlzsNUvhTPTLyO+Bq8/GKpUJ4wsyK6Q2wxIA6ZnmrzWvNVW9IFm8DO18fXuy4bkeZLWvRPKKdz4DpNqbqkragJhPlhdKBJatjjwXX1PjkIU1WoU/SSe3RSnE57FyV9z5x2NwIfhwLmQg59m143QHcByr/+GxoPAbcGkMQ4gyuqQhSqjOPHBs03Q/bshVwExmxQRUoynjyg5/lkwelYRNtDDdlgmQgCioz6ib9NY1dNvlETwUWq5cNl7GC9zniWOylfYHWb/jiut+RXDF1o2sPrV/onkXs6/VcxmkEj3NzBASq+QIguxCP0L+eXdNewhO3/ORdIB8RTunpqm2RpJfnjiynG3mCDGKWm41iitTPWwDeu57gs7hFe4tXBh3mvoR7pqDIQzjdKPNhPv1HOp8rEN0yiA+Stm1F9/1s90LUmreZYddfoJSzlHQueDjAbruoa5NiZ0gWWKNuQ=
*/