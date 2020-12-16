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
5Px8Cfl9EEjOL7V+Hc38vhBJuiTn9/UN5vgUmv3t6b0n/LL/ObX9Zvp2HyxS6cfekma8Kq3yKkz4R3rtqbxLF6WU57PK85rpP/tZmvI6SnjaRTXxb+jcNPBbJ5nwyxYo+KPTwS+04C18/XxOuvZb8NZ8rk0HP9yCv8es/53p4I+z4HuZ8Jemg//6egUfH7/T0sEvt+DfeE7B29PBz7fgzzfzXzs73fy34HuZ/f9oOvjeqfW/IR18pgXvXajgtXTwb15n4Y8J3z4d/BMWvIXfW2algQ9b8B/8ScH/MR28z4L3mvg2Nx18x9T6DE0Hv/XalPYenQ5+4bUp+X8+Mx3+W/ALzPbWpoMfbsGfb8LfmQ7+OBM+M2Tijz8d/NfXmPBvPKvg89PBL7fgPzDx35iRDv8t+F5mfy5OBz/egn/crH9VOvjeFrzXhB+VDj7Tgv/K7M9u6eDfvNpq7zMKftf0dPhvwV9u5t+QDj5swXvN/r8vHbzv6pT6T0wH39GCP/+PCr5vOvitV1n4Y8K70sEvtODvMeuz/uZ0+G/Bf/UHBf/rdPDDLfjzTXybmg7+uNT6+NPBf31lSnvz08EvvzIlf2NaOvy34JeZ7V2cDn68BX+5CV+1e3gwkRX/Tgm/TpJJoWzgFIwuwbb7nLKlpWDjWs5jqFkiVIOFZs563KD2Ow+BphTt+uC3tBsFRlc1UQl1Zzb1FqAmuQ3HyuZMwz1R3DAS8pkyF+GOEBeeY42mfac3yaMp1mHb3Uv/RisB5yELs/2EecWe0JAYuPA13bSShhmfI6bATyM8UEg8WrheEDz1x6Wm3k5MZnj4X1V9zsPGpedbqjPJ7UBuruatrx6UP6l/svUK0YnQhwBXaWU/eNbolxXKVmolAVwSpz2S7Ts0lz30UXDc0NxyJ7TLyLUdN9oTcB4BvbchWr3Dzqy6UaMr6mQjTya9gyaZ7rCXNCWoBs0dRqOSkjctipFcXeszqOfwnvGQAHiwWdIqRqOObymozDEK+luq6Ay2Eu4TF2XPf2zoWImUjRMUi6cNAweYunxn7ih1OUJ9JBNy3KgC2OINFUpN+T6YrNISlnGnULSsL8u1S1vQUWCOjhR7lcegqFNVkSeYRXYRReb7x5WitNqQu2hlfanK2BX1kz+17/z7b8erVnGaUOMQgngPFSWhLa+J0gaL0gKybe+ESiPTc2GqjJLgw4Lj2Az0v9soW4a7qvy0Z1MAk4mpoYyFpXD8+V1Uc2AMe/O+peXa8gxZf+HH5iOhuEhjouwxvlMyarbjZtGOkDlGV8sxuvuPHKOfKSlUD8O4mRdgeQePPuQQSQ7skSdZSNwxQS2RYiFTXbNeqfeW1B0qFVii010YbhuXglcFuCn7/FFuL/3jzsvgHZAMR52FH10Vfhxu4schoqUuhR+tfFhRE9yZwNIsH+fPCDrhHdWuQRVst+evpmdb8w9O/CO+d3cf7plxiZ7r9A70LrdopDBleqwf5pC5trb3Fw9yhXMSLsRRrGP86uyW2D5dklP7v1nSWhwBAybJsABbxB72fwmPEe1sAvc4PhVY9WdWQIeOqZ2ToJCOQjns2fWOGP7q4IXSwVmSwwgamwhE0843tf9dZp5XHzDpp7On7of/1uEyPe7ow4GoVAVlZ1J0eR68iWDkhavSNsblZwGQa0tkussW2syFcWgxg4owXY+hWz6Ah93GXwlXX+YS6NkWqkyw6ZN1ZkssPmEP0ElrK/+nl4pa7+if6wJCLM5E2AvsRIjR4FLTGDRESNLGA0Owl0L1XVgjWxNHg6YsTfbRXvu396Xm+aCfSS/ccEM6+teCv8iE19LBv3mJSY/89fcm/TspHf1rwX9vwjcAPt0=
*/