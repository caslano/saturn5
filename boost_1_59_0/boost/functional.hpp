// ------------------------------------------------------------------------------
// Copyright (c) 2000 Cadenza New Zealand Ltd
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------
// Boost functional.hpp header file
// See http://www.boost.org/libs/functional for documentation.
// ------------------------------------------------------------------------------
// $Id$
// ------------------------------------------------------------------------------

#ifndef BOOST_FUNCTIONAL_HPP
#define BOOST_FUNCTIONAL_HPP

#include <boost/config.hpp>
#include <boost/call_traits.hpp>
#include <functional>

namespace boost
{
    namespace functional
    {
        namespace detail {
#if defined(_HAS_AUTO_PTR_ETC) && !_HAS_AUTO_PTR_ETC
            // std::unary_function and std::binary_function were both removed
            // in C++17.

            template <typename Arg1, typename Result>
            struct unary_function
            {
                typedef Arg1 argument_type;
                typedef Result result_type;
            };

            template <typename Arg1, typename Arg2, typename Result>
            struct binary_function
            {
                typedef Arg1 first_argument_type;
                typedef Arg2 second_argument_type;
                typedef Result result_type;
            };
#else
            // Use the standard objects when we have them.

            using std::unary_function;
            using std::binary_function;
#endif
        }
    }

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    // --------------------------------------------------------------------------
    // The following traits classes allow us to avoid the need for ptr_fun
    // because the types of arguments and the result of a function can be 
    // deduced.
    //
    // In addition to the standard types defined in unary_function and 
    // binary_function, we add
    //
    // - function_type, the type of the function or function object itself.
    //
    // - param_type, the type that should be used for passing the function or
    //   function object as an argument.
    // --------------------------------------------------------------------------
    namespace detail
    {
        template <class Operation>
        struct unary_traits_imp;
        
        template <class Operation>
        struct unary_traits_imp<Operation*>
        {
            typedef Operation                         function_type;
            typedef const function_type &             param_type;
            typedef typename Operation::result_type   result_type;
            typedef typename Operation::argument_type argument_type;
        };

        template <class R, class A>
        struct unary_traits_imp<R(*)(A)>
        {
            typedef R (*function_type)(A);
            typedef R (*param_type)(A);
            typedef R result_type;
            typedef A argument_type;
        };

        template <class Operation>
        struct binary_traits_imp;

        template <class Operation>
        struct binary_traits_imp<Operation*>
        {
            typedef Operation                                function_type;
            typedef const function_type &                    param_type;
            typedef typename Operation::result_type          result_type;
            typedef typename Operation::first_argument_type  first_argument_type;
            typedef typename Operation::second_argument_type second_argument_type;
        };
        
        template <class R, class A1, class A2>
        struct binary_traits_imp<R(*)(A1,A2)>
        {
            typedef R (*function_type)(A1,A2);
            typedef R (*param_type)(A1,A2);
            typedef R result_type;
            typedef A1 first_argument_type;
            typedef A2 second_argument_type;
        };
    } // namespace detail
    
    template <class Operation>
    struct unary_traits
    {
        typedef typename detail::unary_traits_imp<Operation*>::function_type function_type;
        typedef typename detail::unary_traits_imp<Operation*>::param_type    param_type;
        typedef typename detail::unary_traits_imp<Operation*>::result_type   result_type;
        typedef typename detail::unary_traits_imp<Operation*>::argument_type argument_type;
    }; 

    template <class R, class A>
    struct unary_traits<R(*)(A)>
    {
        typedef R (*function_type)(A);
        typedef R (*param_type)(A);
        typedef R result_type;
        typedef A argument_type;
    };

    template <class Operation>
    struct binary_traits
    {
        typedef typename detail::binary_traits_imp<Operation*>::function_type        function_type;
        typedef typename detail::binary_traits_imp<Operation*>::param_type           param_type;
        typedef typename detail::binary_traits_imp<Operation*>::result_type          result_type;
        typedef typename detail::binary_traits_imp<Operation*>::first_argument_type  first_argument_type;
        typedef typename detail::binary_traits_imp<Operation*>::second_argument_type second_argument_type;
    };
    
    template <class R, class A1, class A2>
    struct binary_traits<R(*)(A1,A2)>
    {
        typedef R (*function_type)(A1,A2);
        typedef R (*param_type)(A1,A2);
        typedef R result_type;
        typedef A1 first_argument_type;
        typedef A2 second_argument_type;
    };
#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    // --------------------------------------------------------------------------
    // If we have no partial specialisation available, decay to a situation
    // that is no worse than in the Standard, i.e., ptr_fun will be required.
    // --------------------------------------------------------------------------

    template <class Operation>
    struct unary_traits
    {
        typedef Operation                         function_type;
        typedef const Operation&                  param_type;
        typedef typename Operation::result_type   result_type;
        typedef typename Operation::argument_type argument_type;
    }; 
    
    template <class Operation>
    struct binary_traits
    {
        typedef Operation                                function_type;
        typedef const Operation &                        param_type;
        typedef typename Operation::result_type          result_type;
        typedef typename Operation::first_argument_type  first_argument_type;
        typedef typename Operation::second_argument_type second_argument_type;
    };    
#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    
    // --------------------------------------------------------------------------
    // unary_negate, not1
    // --------------------------------------------------------------------------
    template <class Predicate>
    class unary_negate
        : public boost::functional::detail::unary_function<typename unary_traits<Predicate>::argument_type,bool>
    {
      public:
        explicit unary_negate(typename unary_traits<Predicate>::param_type x)
            :
            pred(x)
        {}
        bool operator()(typename call_traits<typename unary_traits<Predicate>::argument_type>::param_type x) const
        {
            return !pred(x);
        }
      private:
        typename unary_traits<Predicate>::function_type pred;
    };

    template <class Predicate>
    unary_negate<Predicate> not1(const Predicate &pred)
    {
        // The cast is to placate Borland C++Builder in certain circumstances.
        // I don't think it should be necessary.
        return unary_negate<Predicate>((typename unary_traits<Predicate>::param_type)pred);
    }

    template <class Predicate>
    unary_negate<Predicate> not1(Predicate &pred)
    {
        return unary_negate<Predicate>(pred);
    }

    // --------------------------------------------------------------------------
    // binary_negate, not2
    // --------------------------------------------------------------------------
    template <class Predicate>
    class binary_negate
        : public boost::functional::detail::binary_function<
                                      typename binary_traits<Predicate>::first_argument_type,
                                      typename binary_traits<Predicate>::second_argument_type,
                                      bool>
    {
      public:
        explicit binary_negate(typename binary_traits<Predicate>::param_type x)
            :
            pred(x)
        {}
        bool operator()(typename call_traits<typename binary_traits<Predicate>::first_argument_type>::param_type x,
                        typename call_traits<typename binary_traits<Predicate>::second_argument_type>::param_type y) const
        {
            return !pred(x,y);
        }
      private:
        typename binary_traits<Predicate>::function_type pred;
    };

    template <class Predicate>
    binary_negate<Predicate> not2(const Predicate &pred)
    {
        // The cast is to placate Borland C++Builder in certain circumstances.
        // I don't think it should be necessary.
        return binary_negate<Predicate>((typename binary_traits<Predicate>::param_type)pred);
    }

    template <class Predicate>
    binary_negate<Predicate> not2(Predicate &pred)
    {
        return binary_negate<Predicate>(pred);
    }
        
    // --------------------------------------------------------------------------
    // binder1st, bind1st
    // --------------------------------------------------------------------------
    template <class Operation>
    class binder1st
        : public boost::functional::detail::unary_function<
                                     typename binary_traits<Operation>::second_argument_type,
                                     typename binary_traits<Operation>::result_type>
    {       
      public:
        binder1st(typename binary_traits<Operation>::param_type x,
                  typename call_traits<typename binary_traits<Operation>::first_argument_type>::param_type y)
            :
            op(x), value(y)
        {}
        
        typename binary_traits<Operation>::result_type
        operator()(typename call_traits<typename binary_traits<Operation>::second_argument_type>::param_type x) const
        {
            return op(value, x);
        }
        
      protected:
        typename binary_traits<Operation>::function_type op;
        typename binary_traits<Operation>::first_argument_type value;
    };

    template <class Operation>
    inline binder1st<Operation> bind1st(const Operation &op,
                                        typename call_traits<
                                                    typename binary_traits<Operation>::first_argument_type
                                        >::param_type x)
    {
        // The cast is to placate Borland C++Builder in certain circumstances.
        // I don't think it should be necessary.
        return binder1st<Operation>((typename binary_traits<Operation>::param_type)op, x);
    }

    template <class Operation>
    inline binder1st<Operation> bind1st(Operation &op,
                                        typename call_traits<
                                                    typename binary_traits<Operation>::first_argument_type
                                        >::param_type x)
    {
        return binder1st<Operation>(op, x);
    }

    // --------------------------------------------------------------------------
    // binder2nd, bind2nd
    // --------------------------------------------------------------------------
    template <class Operation>
    class binder2nd
        : public boost::functional::detail::unary_function<
                                     typename binary_traits<Operation>::first_argument_type,
                                     typename binary_traits<Operation>::result_type>
    {
      public:
        binder2nd(typename binary_traits<Operation>::param_type x,
                  typename call_traits<typename binary_traits<Operation>::second_argument_type>::param_type y)
            :
            op(x), value(y)
        {}
        
        typename binary_traits<Operation>::result_type
        operator()(typename call_traits<typename binary_traits<Operation>::first_argument_type>::param_type x) const
        {
            return op(x, value);
        }               
        
      protected:
        typename binary_traits<Operation>::function_type op;
        typename binary_traits<Operation>::second_argument_type value;
    };

    template <class Operation>
    inline binder2nd<Operation> bind2nd(const Operation &op,
                                        typename call_traits<
                                                    typename binary_traits<Operation>::second_argument_type
                                        >::param_type x)
    {
        // The cast is to placate Borland C++Builder in certain circumstances.
        // I don't think it should be necessary.
        return binder2nd<Operation>((typename binary_traits<Operation>::param_type)op, x);
    }

    template <class Operation>
    inline binder2nd<Operation> bind2nd(Operation &op,
                                        typename call_traits<
                                                    typename binary_traits<Operation>::second_argument_type
                                        >::param_type x)
    {
        return binder2nd<Operation>(op, x);
    }

    // --------------------------------------------------------------------------
    // mem_fun, etc
    // --------------------------------------------------------------------------
    template <class S, class T>
    class mem_fun_t : public boost::functional::detail::unary_function<T*, S>
    {
      public:
        explicit mem_fun_t(S (T::*p)())
            :
            ptr(p)
        {}
        S operator()(T* p) const
        {
            return (p->*ptr)();
        }
      private:
        S (T::*ptr)();
    };

    template <class S, class T, class A>
    class mem_fun1_t : public boost::functional::detail::binary_function<T*, A, S>
    {
      public:   
        explicit mem_fun1_t(S (T::*p)(A))
            :
            ptr(p)
        {}
        S operator()(T* p, typename call_traits<A>::param_type x) const
        {
            return (p->*ptr)(x);
        }
      private:
        S (T::*ptr)(A);
    };

    template <class S, class T>
    class const_mem_fun_t : public boost::functional::detail::unary_function<const T*, S>
    {
      public:
        explicit const_mem_fun_t(S (T::*p)() const)
            :
            ptr(p)
        {}
        S operator()(const T* p) const
        {
            return (p->*ptr)();
        }
      private:
        S (T::*ptr)() const;        
    };

    template <class S, class T, class A>
    class const_mem_fun1_t : public boost::functional::detail::binary_function<const T*, A, S>
    {
      public:
        explicit const_mem_fun1_t(S (T::*p)(A) const)
            :
            ptr(p)
        {}
        S operator()(const T* p, typename call_traits<A>::param_type x) const
        {
            return (p->*ptr)(x);
        }
      private:
        S (T::*ptr)(A) const;
    };
    
    template<class S, class T>
    inline mem_fun_t<S,T> mem_fun(S (T::*f)())
    {
        return mem_fun_t<S,T>(f);
    }
    
    template<class S, class T, class A>
    inline mem_fun1_t<S,T,A> mem_fun(S (T::*f)(A))
    {
        return mem_fun1_t<S,T,A>(f);
    }

#ifndef BOOST_NO_POINTER_TO_MEMBER_CONST
    template<class S, class T>
    inline const_mem_fun_t<S,T> mem_fun(S (T::*f)() const)
    {
        return const_mem_fun_t<S,T>(f);
    }
    
    template<class S, class T, class A>
    inline const_mem_fun1_t<S,T,A> mem_fun(S (T::*f)(A) const)
    {
        return const_mem_fun1_t<S,T,A>(f);
    }
#endif // BOOST_NO_POINTER_TO_MEMBER_CONST

    // --------------------------------------------------------------------------
    // mem_fun_ref, etc
    // --------------------------------------------------------------------------
    template <class S, class T>
    class mem_fun_ref_t : public boost::functional::detail::unary_function<T&, S>
    {
      public:
        explicit mem_fun_ref_t(S (T::*p)())
            :
            ptr(p)
        {}
        S operator()(T& p) const
        {
            return (p.*ptr)();
        }
      private:
        S (T::*ptr)();
    };

    template <class S, class T, class A>
    class mem_fun1_ref_t : public boost::functional::detail::binary_function<T&, A, S>
    {
      public:
        explicit mem_fun1_ref_t(S (T::*p)(A))
            :
            ptr(p)
        {}
        S operator()(T& p, typename call_traits<A>::param_type x) const
        {
            return (p.*ptr)(x);
        }
      private:
        S (T::*ptr)(A);
    };
    
    template <class S, class T>
    class const_mem_fun_ref_t : public boost::functional::detail::unary_function<const T&, S>
    {
      public:
        explicit const_mem_fun_ref_t(S (T::*p)() const)
            :
            ptr(p)
        {}
        
        S operator()(const T &p) const
        {
            return (p.*ptr)();
        }
      private:
        S (T::*ptr)() const;
    };

    template <class S, class T, class A>
    class const_mem_fun1_ref_t : public boost::functional::detail::binary_function<const T&, A, S>
    {
      public:
        explicit const_mem_fun1_ref_t(S (T::*p)(A) const)
            :
            ptr(p)
        {}

        S operator()(const T& p, typename call_traits<A>::param_type x) const
        {
            return (p.*ptr)(x);
        }
      private:
        S (T::*ptr)(A) const;
    };
    
    template<class S, class T>
    inline mem_fun_ref_t<S,T> mem_fun_ref(S (T::*f)())
    {
        return mem_fun_ref_t<S,T>(f);
    }

    template<class S, class T, class A>
    inline mem_fun1_ref_t<S,T,A> mem_fun_ref(S (T::*f)(A))
    {
        return mem_fun1_ref_t<S,T,A>(f);
    }

#ifndef BOOST_NO_POINTER_TO_MEMBER_CONST
    template<class S, class T>
    inline const_mem_fun_ref_t<S,T> mem_fun_ref(S (T::*f)() const)
    {
        return const_mem_fun_ref_t<S,T>(f);
    }

    template<class S, class T, class A>
    inline const_mem_fun1_ref_t<S,T,A> mem_fun_ref(S (T::*f)(A) const)
    {
        return const_mem_fun1_ref_t<S,T,A>(f);
    }   
#endif // BOOST_NO_POINTER_TO_MEMBER_CONST

    // --------------------------------------------------------------------------
    // ptr_fun
    // --------------------------------------------------------------------------
    template <class Arg, class Result>
    class pointer_to_unary_function : public boost::functional::detail::unary_function<Arg,Result>
    {
      public:
        explicit pointer_to_unary_function(Result (*f)(Arg))
            :
            func(f)
        {}

        Result operator()(typename call_traits<Arg>::param_type x) const
        {
            return func(x);
        }
        
      private:
        Result (*func)(Arg);
    };

    template <class Arg, class Result>
    inline pointer_to_unary_function<Arg,Result> ptr_fun(Result (*f)(Arg))
    {
        return pointer_to_unary_function<Arg,Result>(f);
    }

    template <class Arg1, class Arg2, class Result>
    class pointer_to_binary_function : public boost::functional::detail::binary_function<Arg1,Arg2,Result>
    {
      public:
        explicit pointer_to_binary_function(Result (*f)(Arg1, Arg2))
            :
            func(f)
        {}
        
        Result operator()(typename call_traits<Arg1>::param_type x, typename call_traits<Arg2>::param_type y) const
        {
            return func(x,y);
        }
        
      private:
        Result (*func)(Arg1, Arg2);
    };

    template <class Arg1, class Arg2, class Result>
    inline pointer_to_binary_function<Arg1,Arg2,Result> ptr_fun(Result (*f)(Arg1, Arg2))
    {
        return pointer_to_binary_function<Arg1,Arg2,Result>(f);
    }
} // namespace boost

#endif

/* functional.hpp
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
*/