// Boost.Function library

//  Copyright Douglas Gregor 2001-2006
//  Copyright Emil Dotchevski 2007
//  Use, modification and distribution is subject to the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_FUNCTION_BASE_HEADER
#define BOOST_FUNCTION_BASE_HEADER

#include <stdexcept>
#include <string>
#include <memory>
#include <new>
#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/integer.hpp>
#include <boost/type_index.hpp>
#include <boost/type_traits/has_trivial_copy.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/type_traits/composite_traits.hpp>
#include <boost/ref.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/config/workaround.hpp>
#include <boost/type_traits/alignment_of.hpp>
#ifndef BOOST_NO_SFINAE
#include <boost/type_traits/enable_if.hpp>
#else
#include <boost/type_traits/integral_constant.hpp>
#endif
#include <boost/function_equal.hpp>
#include <boost/function/function_fwd.hpp>

#if defined(BOOST_MSVC)
#   pragma warning( push )
#   pragma warning( disable : 4793 ) // complaint about native code generation
#   pragma warning( disable : 4127 ) // "conditional expression is constant"
#endif

#if defined(__ICL) && __ICL <= 600 || defined(__MWERKS__) && __MWERKS__ < 0x2406 && !defined(BOOST_STRICT_CONFIG)
#  define BOOST_FUNCTION_TARGET_FIX(x) x
#else
#  define BOOST_FUNCTION_TARGET_FIX(x)
#endif // __ICL etc

#  define BOOST_FUNCTION_ENABLE_IF_NOT_INTEGRAL(Functor,Type)              \
      typename ::boost::enable_if_<          \
                           !(::boost::is_integral<Functor>::value), \
                           Type>::type

namespace boost {
  namespace detail {
    namespace function {
      class X;

      /**
       * A buffer used to store small function objects in
       * boost::function. It is a union containing function pointers,
       * object pointers, and a structure that resembles a bound
       * member function pointer.
       */
      union function_buffer_members
      {
        // For pointers to function objects
        typedef void* obj_ptr_t;
        mutable obj_ptr_t obj_ptr;

        // For pointers to std::type_info objects
        struct type_t {
          // (get_functor_type_tag, check_functor_type_tag).
          const boost::typeindex::type_info* type;

          // Whether the type is const-qualified.
          bool const_qualified;
          // Whether the type is volatile-qualified.
          bool volatile_qualified;
        } type;

        // For function pointers of all kinds
        typedef void (*func_ptr_t)();
        mutable func_ptr_t func_ptr;

        // For bound member pointers
        struct bound_memfunc_ptr_t {
          void (X::*memfunc_ptr)(int);
          void* obj_ptr;
        } bound_memfunc_ptr;

        // For references to function objects. We explicitly keep
        // track of the cv-qualifiers on the object referenced.
        struct obj_ref_t {
          mutable void* obj_ptr;
          bool is_const_qualified;
          bool is_volatile_qualified;
        } obj_ref;
      };

      union BOOST_SYMBOL_VISIBLE function_buffer
      {
        // Type-specific union members
        mutable function_buffer_members members;

        // To relax aliasing constraints
        mutable char data[sizeof(function_buffer_members)];
      };

      /**
       * The unusable class is a placeholder for unused function arguments
       * It is also completely unusable except that it constructable from
       * anything. This helps compilers without partial specialization to
       * handle Boost.Function objects returning void.
       */
      struct unusable
      {
        unusable() {}
        template<typename T> unusable(const T&) {}
      };

      /* Determine the return type. This supports compilers that do not support
       * void returns or partial specialization by silently changing the return
       * type to "unusable".
       */
      template<typename T> struct function_return_type { typedef T type; };

      template<>
      struct function_return_type<void>
      {
        typedef unusable type;
      };

      // The operation type to perform on the given functor/function pointer
      enum functor_manager_operation_type {
        clone_functor_tag,
        move_functor_tag,
        destroy_functor_tag,
        check_functor_type_tag,
        get_functor_type_tag
      };

      // Tags used to decide between different types of functions
      struct function_ptr_tag {};
      struct function_obj_tag {};
      struct member_ptr_tag {};
      struct function_obj_ref_tag {};

      template<typename F>
      class get_function_tag
      {
        typedef typename conditional<(is_pointer<F>::value),
                                   function_ptr_tag,
                                   function_obj_tag>::type ptr_or_obj_tag;

        typedef typename conditional<(is_member_pointer<F>::value),
                                   member_ptr_tag,
                                   ptr_or_obj_tag>::type ptr_or_obj_or_mem_tag;

        typedef typename conditional<(is_reference_wrapper<F>::value),
                                   function_obj_ref_tag,
                                   ptr_or_obj_or_mem_tag>::type or_ref_tag;

      public:
        typedef or_ref_tag type;
      };

      // The trivial manager does nothing but return the same pointer (if we
      // are cloning) or return the null pointer (if we are deleting).
      template<typename F>
      struct reference_manager
      {
        static inline void
        manage(const function_buffer& in_buffer, function_buffer& out_buffer,
               functor_manager_operation_type op)
        {
          switch (op) {
          case clone_functor_tag:
            out_buffer.members.obj_ref = in_buffer.members.obj_ref;
            return;

          case move_functor_tag:
            out_buffer.members.obj_ref = in_buffer.members.obj_ref;
            in_buffer.members.obj_ref.obj_ptr = 0;
            return;

          case destroy_functor_tag:
            out_buffer.members.obj_ref.obj_ptr = 0;
            return;

          case check_functor_type_tag:
            {
              // Check whether we have the same type. We can add
              // cv-qualifiers, but we can't take them away.
              if (*out_buffer.members.type.type == boost::typeindex::type_id<F>()
                  && (!in_buffer.members.obj_ref.is_const_qualified
                      || out_buffer.members.type.const_qualified)
                  && (!in_buffer.members.obj_ref.is_volatile_qualified
                      || out_buffer.members.type.volatile_qualified))
                out_buffer.members.obj_ptr = in_buffer.members.obj_ref.obj_ptr;
              else
                out_buffer.members.obj_ptr = 0;
            }
            return;

          case get_functor_type_tag:
            out_buffer.members.type.type = &boost::typeindex::type_id<F>().type_info();
            out_buffer.members.type.const_qualified = in_buffer.members.obj_ref.is_const_qualified;
            out_buffer.members.type.volatile_qualified = in_buffer.members.obj_ref.is_volatile_qualified;
            return;
          }
        }
      };

      /**
       * Determine if boost::function can use the small-object
       * optimization with the function object type F.
       */
      template<typename F>
      struct function_allows_small_object_optimization
      {
        BOOST_STATIC_CONSTANT
          (bool,
           value = ((sizeof(F) <= sizeof(function_buffer) &&
                     (alignment_of<function_buffer>::value
                      % alignment_of<F>::value == 0))));
      };

      template <typename F,typename A>
      struct functor_wrapper: public F, public A
      {
        functor_wrapper( F f, A a ):
          F(f),
          A(a)
        {
        }

        functor_wrapper(const functor_wrapper& f) :
          F(static_cast<const F&>(f)),
          A(static_cast<const A&>(f))
        {
        }
      };

      /**
       * The functor_manager class contains a static function "manage" which
       * can clone or destroy the given function/function object pointer.
       */
      template<typename Functor>
      struct functor_manager_common
      {
        typedef Functor functor_type;

        // Function pointers
        static inline void
        manage_ptr(const function_buffer& in_buffer, function_buffer& out_buffer,
                functor_manager_operation_type op)
        {
          if (op == clone_functor_tag)
            out_buffer.members.func_ptr = in_buffer.members.func_ptr;
          else if (op == move_functor_tag) {
            out_buffer.members.func_ptr = in_buffer.members.func_ptr;
            in_buffer.members.func_ptr = 0;
          } else if (op == destroy_functor_tag)
            out_buffer.members.func_ptr = 0;
          else if (op == check_functor_type_tag) {
            if (*out_buffer.members.type.type == boost::typeindex::type_id<Functor>())
              out_buffer.members.obj_ptr = &in_buffer.members.func_ptr;
            else
              out_buffer.members.obj_ptr = 0;
          } else /* op == get_functor_type_tag */ {
            out_buffer.members.type.type = &boost::typeindex::type_id<Functor>().type_info();
            out_buffer.members.type.const_qualified = false;
            out_buffer.members.type.volatile_qualified = false;
          }
        }

        // Function objects that fit in the small-object buffer.
        static inline void
        manage_small(const function_buffer& in_buffer, function_buffer& out_buffer,
                functor_manager_operation_type op)
        {
          if (op == clone_functor_tag || op == move_functor_tag) {
            const functor_type* in_functor =
              reinterpret_cast<const functor_type*>(in_buffer.data);
            new (reinterpret_cast<void*>(out_buffer.data)) functor_type(*in_functor);

            if (op == move_functor_tag) {
              functor_type* f = reinterpret_cast<functor_type*>(in_buffer.data);
              (void)f; // suppress warning about the value of f not being used (MSVC)
              f->~Functor();
            }
          } else if (op == destroy_functor_tag) {
            // Some compilers (Borland, vc6, ...) are unhappy with ~functor_type.
             functor_type* f = reinterpret_cast<functor_type*>(out_buffer.data);
             (void)f; // suppress warning about the value of f not being used (MSVC)
             f->~Functor();
          } else if (op == check_functor_type_tag) {
             if (*out_buffer.members.type.type == boost::typeindex::type_id<Functor>())
              out_buffer.members.obj_ptr = in_buffer.data;
            else
              out_buffer.members.obj_ptr = 0;
          } else /* op == get_functor_type_tag */ {
            out_buffer.members.type.type = &boost::typeindex::type_id<Functor>().type_info();
            out_buffer.members.type.const_qualified = false;
            out_buffer.members.type.volatile_qualified = false;
          }
        }
      };

      template<typename Functor>
      struct functor_manager
      {
      private:
        typedef Functor functor_type;

        // Function pointers
        static inline void
        manager(const function_buffer& in_buffer, function_buffer& out_buffer,
                functor_manager_operation_type op, function_ptr_tag)
        {
          functor_manager_common<Functor>::manage_ptr(in_buffer,out_buffer,op);
        }

        // Function objects that fit in the small-object buffer.
        static inline void
        manager(const function_buffer& in_buffer, function_buffer& out_buffer,
                functor_manager_operation_type op, true_type)
        {
          functor_manager_common<Functor>::manage_small(in_buffer,out_buffer,op);
        }

        // Function objects that require heap allocation
        static inline void
        manager(const function_buffer& in_buffer, function_buffer& out_buffer,
                functor_manager_operation_type op, false_type)
        {
          if (op == clone_functor_tag) {
            // Clone the functor
            // GCC 2.95.3 gets the CV qualifiers wrong here, so we
            // can't do the static_cast that we should do.
            // jewillco: Changing this to static_cast because GCC 2.95.3 is
            // obsolete.
            const functor_type* f =
              static_cast<const functor_type*>(in_buffer.members.obj_ptr);
            functor_type* new_f = new functor_type(*f);
            out_buffer.members.obj_ptr = new_f;
          } else if (op == move_functor_tag) {
            out_buffer.members.obj_ptr = in_buffer.members.obj_ptr;
            in_buffer.members.obj_ptr = 0;
          } else if (op == destroy_functor_tag) {
            /* Cast from the void pointer to the functor pointer type */
            functor_type* f =
              static_cast<functor_type*>(out_buffer.members.obj_ptr);
            delete f;
            out_buffer.members.obj_ptr = 0;
          } else if (op == check_functor_type_tag) {
            if (*out_buffer.members.type.type == boost::typeindex::type_id<Functor>())
              out_buffer.members.obj_ptr = in_buffer.members.obj_ptr;
            else
              out_buffer.members.obj_ptr = 0;
          } else /* op == get_functor_type_tag */ {
            out_buffer.members.type.type = &boost::typeindex::type_id<Functor>().type_info();
            out_buffer.members.type.const_qualified = false;
            out_buffer.members.type.volatile_qualified = false;
          }
        }

        // For function objects, we determine whether the function
        // object can use the small-object optimization buffer or
        // whether we need to allocate it on the heap.
        static inline void
        manager(const function_buffer& in_buffer, function_buffer& out_buffer,
                functor_manager_operation_type op, function_obj_tag)
        {
          manager(in_buffer, out_buffer, op,
                  integral_constant<bool, (function_allows_small_object_optimization<functor_type>::value)>());
        }

        // For member pointers, we use the small-object optimization buffer.
        static inline void
        manager(const function_buffer& in_buffer, function_buffer& out_buffer,
                functor_manager_operation_type op, member_ptr_tag)
        {
          manager(in_buffer, out_buffer, op, true_type());
        }

      public:
        /* Dispatch to an appropriate manager based on whether we have a
           function pointer or a function object pointer. */
        static inline void
        manage(const function_buffer& in_buffer, function_buffer& out_buffer,
               functor_manager_operation_type op)
        {
          typedef typename get_function_tag<functor_type>::type tag_type;
          if (op == get_functor_type_tag) {
            out_buffer.members.type.type = &boost::typeindex::type_id<functor_type>().type_info();
            out_buffer.members.type.const_qualified = false;
            out_buffer.members.type.volatile_qualified = false;
          } else {
            manager(in_buffer, out_buffer, op, tag_type());
          }
        }
      };

      template<typename Functor, typename Allocator>
      struct functor_manager_a
      {
      private:
        typedef Functor functor_type;

        // Function pointers
        static inline void
        manager(const function_buffer& in_buffer, function_buffer& out_buffer,
                functor_manager_operation_type op, function_ptr_tag)
        {
          functor_manager_common<Functor>::manage_ptr(in_buffer,out_buffer,op);
        }

        // Function objects that fit in the small-object buffer.
        static inline void
        manager(const function_buffer& in_buffer, function_buffer& out_buffer,
                functor_manager_operation_type op, true_type)
        {
          functor_manager_common<Functor>::manage_small(in_buffer,out_buffer,op);
        }

        // Function objects that require heap allocation
        static inline void
        manager(const function_buffer& in_buffer, function_buffer& out_buffer,
                functor_manager_operation_type op, false_type)
        {
          typedef functor_wrapper<Functor,Allocator> functor_wrapper_type;
#if defined(BOOST_NO_CXX11_ALLOCATOR)
          typedef typename Allocator::template rebind<functor_wrapper_type>::other
            wrapper_allocator_type;
          typedef typename wrapper_allocator_type::pointer wrapper_allocator_pointer_type;
#else
          using wrapper_allocator_type = typename std::allocator_traits<Allocator>::template rebind_alloc<functor_wrapper_type>;
          using wrapper_allocator_pointer_type = typename std::allocator_traits<wrapper_allocator_type>::pointer;
#endif

          if (op == clone_functor_tag) {
            // Clone the functor
            // GCC 2.95.3 gets the CV qualifiers wrong here, so we
            // can't do the static_cast that we should do.
            const functor_wrapper_type* f =
              static_cast<const functor_wrapper_type*>(in_buffer.members.obj_ptr);
            wrapper_allocator_type wrapper_allocator(static_cast<Allocator const &>(*f));
            wrapper_allocator_pointer_type copy = wrapper_allocator.allocate(1);
#if defined(BOOST_NO_CXX11_ALLOCATOR)
            wrapper_allocator.construct(copy, *f);
#else
            std::allocator_traits<wrapper_allocator_type>::construct(wrapper_allocator, copy, *f);
#endif

            // Get back to the original pointer type
            functor_wrapper_type* new_f = static_cast<functor_wrapper_type*>(copy);
            out_buffer.members.obj_ptr = new_f;
          } else if (op == move_functor_tag) {
            out_buffer.members.obj_ptr = in_buffer.members.obj_ptr;
            in_buffer.members.obj_ptr = 0;
          } else if (op == destroy_functor_tag) {
            /* Cast from the void pointer to the functor_wrapper_type */
            functor_wrapper_type* victim =
              static_cast<functor_wrapper_type*>(in_buffer.members.obj_ptr);
            wrapper_allocator_type wrapper_allocator(static_cast<Allocator const &>(*victim));
#if defined(BOOST_NO_CXX11_ALLOCATOR)
            wrapper_allocator.destroy(victim);
#else
            std::allocator_traits<wrapper_allocator_type>::destroy(wrapper_allocator, victim);
#endif
            wrapper_allocator.deallocate(victim,1);
            out_buffer.members.obj_ptr = 0;
          } else if (op == check_functor_type_tag) {
            if (*out_buffer.members.type.type == boost::typeindex::type_id<Functor>())
              out_buffer.members.obj_ptr = in_buffer.members.obj_ptr;
            else
              out_buffer.members.obj_ptr = 0;
          } else /* op == get_functor_type_tag */ {
            out_buffer.members.type.type = &boost::typeindex::type_id<Functor>().type_info();
            out_buffer.members.type.const_qualified = false;
            out_buffer.members.type.volatile_qualified = false;
          }
        }

        // For function objects, we determine whether the function
        // object can use the small-object optimization buffer or
        // whether we need to allocate it on the heap.
        static inline void
        manager(const function_buffer& in_buffer, function_buffer& out_buffer,
                functor_manager_operation_type op, function_obj_tag)
        {
          manager(in_buffer, out_buffer, op,
                  integral_constant<bool, (function_allows_small_object_optimization<functor_type>::value)>());
        }

      public:
        /* Dispatch to an appropriate manager based on whether we have a
           function pointer or a function object pointer. */
        static inline void
        manage(const function_buffer& in_buffer, function_buffer& out_buffer,
               functor_manager_operation_type op)
        {
          typedef typename get_function_tag<functor_type>::type tag_type;
          if (op == get_functor_type_tag) {
            out_buffer.members.type.type = &boost::typeindex::type_id<functor_type>().type_info();
            out_buffer.members.type.const_qualified = false;
            out_buffer.members.type.volatile_qualified = false;
          } else {
            manager(in_buffer, out_buffer, op, tag_type());
          }
        }
      };

      // A type that is only used for comparisons against zero
      struct useless_clear_type {};

#ifdef BOOST_NO_SFINAE
      // These routines perform comparisons between a Boost.Function
      // object and an arbitrary function object (when the last
      // parameter is false_type) or against zero (when the
      // last parameter is true_type). They are only necessary
      // for compilers that don't support SFINAE.
      template<typename Function, typename Functor>
        bool
        compare_equal(const Function& f, const Functor&, int, true_type)
        { return f.empty(); }

      template<typename Function, typename Functor>
        bool
        compare_not_equal(const Function& f, const Functor&, int,
                          true_type)
        { return !f.empty(); }

      template<typename Function, typename Functor>
        bool
        compare_equal(const Function& f, const Functor& g, long,
                      false_type)
        {
          if (const Functor* fp = f.template target<Functor>())
            return function_equal(*fp, g);
          else return false;
        }

      template<typename Function, typename Functor>
        bool
        compare_equal(const Function& f, const reference_wrapper<Functor>& g,
                      int, false_type)
        {
          if (const Functor* fp = f.template target<Functor>())
            return fp == g.get_pointer();
          else return false;
        }

      template<typename Function, typename Functor>
        bool
        compare_not_equal(const Function& f, const Functor& g, long,
                          false_type)
        {
          if (const Functor* fp = f.template target<Functor>())
            return !function_equal(*fp, g);
          else return true;
        }

      template<typename Function, typename Functor>
        bool
        compare_not_equal(const Function& f,
                          const reference_wrapper<Functor>& g, int,
                          false_type)
        {
          if (const Functor* fp = f.template target<Functor>())
            return fp != g.get_pointer();
          else return true;
        }
#endif // BOOST_NO_SFINAE

      /**
       * Stores the "manager" portion of the vtable for a
       * boost::function object.
       */
      struct vtable_base
      {
        void (*manager)(const function_buffer& in_buffer,
                        function_buffer& out_buffer,
                        functor_manager_operation_type op);
      };
    } // end namespace function
  } // end namespace detail

/**
 * The function_base class contains the basic elements needed for the
 * function1, function2, function3, etc. classes. It is common to all
 * functions (and as such can be used to tell if we have one of the
 * functionN objects).
 */
class function_base
{
public:
  function_base() : vtable(0) { }

  /** Determine if the function is empty (i.e., has no target). */
  bool empty() const { return !vtable; }

  /** Retrieve the type of the stored function object, or type_id<void>()
      if this is empty. */
  const boost::typeindex::type_info& target_type() const
  {
    if (!vtable) return boost::typeindex::type_id<void>().type_info();

    detail::function::function_buffer type;
    get_vtable()->manager(functor, type, detail::function::get_functor_type_tag);
    return *type.members.type.type;
  }

  template<typename Functor>
    Functor* target()
    {
      if (!vtable) return 0;

      detail::function::function_buffer type_result;
      type_result.members.type.type = &boost::typeindex::type_id<Functor>().type_info();
      type_result.members.type.const_qualified = is_const<Functor>::value;
      type_result.members.type.volatile_qualified = is_volatile<Functor>::value;
      get_vtable()->manager(functor, type_result,
                      detail::function::check_functor_type_tag);
      return static_cast<Functor*>(type_result.members.obj_ptr);
    }

  template<typename Functor>
    const Functor* target() const
    {
      if (!vtable) return 0;

      detail::function::function_buffer type_result;
      type_result.members.type.type = &boost::typeindex::type_id<Functor>().type_info();
      type_result.members.type.const_qualified = true;
      type_result.members.type.volatile_qualified = is_volatile<Functor>::value;
      get_vtable()->manager(functor, type_result,
                      detail::function::check_functor_type_tag);
      // GCC 2.95.3 gets the CV qualifiers wrong here, so we
      // can't do the static_cast that we should do.
      return static_cast<const Functor*>(type_result.members.obj_ptr);
    }

  template<typename F>
    bool contains(const F& f) const
    {
      if (const F* fp = this->template target<F>())
      {
        return function_equal(*fp, f);
      } else {
        return false;
      }
    }

#if defined(__GNUC__) && __GNUC__ == 3 && __GNUC_MINOR__ <= 3
  // GCC 3.3 and newer cannot copy with the global operator==, due to
  // problems with instantiation of function return types before it
  // has been verified that the argument types match up.
  template<typename Functor>
    BOOST_FUNCTION_ENABLE_IF_NOT_INTEGRAL(Functor, bool)
    operator==(Functor g) const
    {
      if (const Functor* fp = target<Functor>())
        return function_equal(*fp, g);
      else return false;
    }

  template<typename Functor>
    BOOST_FUNCTION_ENABLE_IF_NOT_INTEGRAL(Functor, bool)
    operator!=(Functor g) const
    {
      if (const Functor* fp = target<Functor>())
        return !function_equal(*fp, g);
      else return true;
    }
#endif

public: // should be protected, but GCC 2.95.3 will fail to allow access
  detail::function::vtable_base* get_vtable() const {
    return reinterpret_cast<detail::function::vtable_base*>(
             reinterpret_cast<std::size_t>(vtable) & ~static_cast<std::size_t>(0x01));
  }

  bool has_trivial_copy_and_destroy() const {
    return reinterpret_cast<std::size_t>(vtable) & 0x01;
  }

  detail::function::vtable_base* vtable;
  mutable detail::function::function_buffer functor;
};

#if defined(BOOST_CLANG)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
#endif
/**
 * The bad_function_call exception class is thrown when a boost::function
 * object is invoked
 */
class BOOST_SYMBOL_VISIBLE bad_function_call : public std::runtime_error
{
public:
  bad_function_call() : std::runtime_error("call to empty boost::function") {}
};
#if defined(BOOST_CLANG)
#   pragma clang diagnostic pop
#endif

#ifndef BOOST_NO_SFINAE
inline bool operator==(const function_base& f,
                       detail::function::useless_clear_type*)
{
  return f.empty();
}

inline bool operator!=(const function_base& f,
                       detail::function::useless_clear_type*)
{
  return !f.empty();
}

inline bool operator==(detail::function::useless_clear_type*,
                       const function_base& f)
{
  return f.empty();
}

inline bool operator!=(detail::function::useless_clear_type*,
                       const function_base& f)
{
  return !f.empty();
}
#endif

#ifdef BOOST_NO_SFINAE
// Comparisons between boost::function objects and arbitrary function objects
template<typename Functor>
  inline bool operator==(const function_base& f, Functor g)
  {
    typedef integral_constant<bool, (is_integral<Functor>::value)> integral;
    return detail::function::compare_equal(f, g, 0, integral());
  }

template<typename Functor>
  inline bool operator==(Functor g, const function_base& f)
  {
    typedef integral_constant<bool, (is_integral<Functor>::value)> integral;
    return detail::function::compare_equal(f, g, 0, integral());
  }

template<typename Functor>
  inline bool operator!=(const function_base& f, Functor g)
  {
    typedef integral_constant<bool, (is_integral<Functor>::value)> integral;
    return detail::function::compare_not_equal(f, g, 0, integral());
  }

template<typename Functor>
  inline bool operator!=(Functor g, const function_base& f)
  {
    typedef integral_constant<bool, (is_integral<Functor>::value)> integral;
    return detail::function::compare_not_equal(f, g, 0, integral());
  }
#else

#  if !(defined(__GNUC__) && __GNUC__ == 3 && __GNUC_MINOR__ <= 3)
// Comparisons between boost::function objects and arbitrary function
// objects. GCC 3.3 and before has an obnoxious bug that prevents this
// from working.
template<typename Functor>
  BOOST_FUNCTION_ENABLE_IF_NOT_INTEGRAL(Functor, bool)
  operator==(const function_base& f, Functor g)
  {
    if (const Functor* fp = f.template target<Functor>())
      return function_equal(*fp, g);
    else return false;
  }

template<typename Functor>
  BOOST_FUNCTION_ENABLE_IF_NOT_INTEGRAL(Functor, bool)
  operator==(Functor g, const function_base& f)
  {
    if (const Functor* fp = f.template target<Functor>())
      return function_equal(g, *fp);
    else return false;
  }

template<typename Functor>
  BOOST_FUNCTION_ENABLE_IF_NOT_INTEGRAL(Functor, bool)
  operator!=(const function_base& f, Functor g)
  {
    if (const Functor* fp = f.template target<Functor>())
      return !function_equal(*fp, g);
    else return true;
  }

template<typename Functor>
  BOOST_FUNCTION_ENABLE_IF_NOT_INTEGRAL(Functor, bool)
  operator!=(Functor g, const function_base& f)
  {
    if (const Functor* fp = f.template target<Functor>())
      return !function_equal(g, *fp);
    else return true;
  }
#  endif

template<typename Functor>
  BOOST_FUNCTION_ENABLE_IF_NOT_INTEGRAL(Functor, bool)
  operator==(const function_base& f, reference_wrapper<Functor> g)
  {
    if (const Functor* fp = f.template target<Functor>())
      return fp == g.get_pointer();
    else return false;
  }

template<typename Functor>
  BOOST_FUNCTION_ENABLE_IF_NOT_INTEGRAL(Functor, bool)
  operator==(reference_wrapper<Functor> g, const function_base& f)
  {
    if (const Functor* fp = f.template target<Functor>())
      return g.get_pointer() == fp;
    else return false;
  }

template<typename Functor>
  BOOST_FUNCTION_ENABLE_IF_NOT_INTEGRAL(Functor, bool)
  operator!=(const function_base& f, reference_wrapper<Functor> g)
  {
    if (const Functor* fp = f.template target<Functor>())
      return fp != g.get_pointer();
    else return true;
  }

template<typename Functor>
  BOOST_FUNCTION_ENABLE_IF_NOT_INTEGRAL(Functor, bool)
  operator!=(reference_wrapper<Functor> g, const function_base& f)
  {
    if (const Functor* fp = f.template target<Functor>())
      return g.get_pointer() != fp;
    else return true;
  }

#endif // Compiler supporting SFINAE

namespace detail {
  namespace function {
    inline bool has_empty_target(const function_base* f)
    {
      return f->empty();
    }

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1310)
    inline bool has_empty_target(const void*)
    {
      return false;
    }
#else
    inline bool has_empty_target(...)
    {
      return false;
    }
#endif
  } // end namespace function
} // end namespace detail
} // end namespace boost

#undef BOOST_FUNCTION_ENABLE_IF_NOT_INTEGRAL

#if defined(BOOST_MSVC)
#   pragma warning( pop )
#endif

#endif // BOOST_FUNCTION_BASE_HEADER

/* function_base.hpp
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
*/