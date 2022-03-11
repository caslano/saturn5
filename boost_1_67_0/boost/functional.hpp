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
VQYs33KRqW0ZvRH+bVzjgc/eVFDPQ4n6NXmEuh8Eee+3pLba7EybsfI/saoUqR5CooRjpUZQsJSKSilCJZMyFYT90Aqc2wEBJ2IRYUaqIIm62/lKgRqCTvONFW5bWvkPWACUqsvFaif6VCrnmJkB9ghjWUii2Ffj3uC7D+L4nVAGM05WO57l0LyFSjtMU9rAA7AXtz9y+E4g0E2EdYldkpYwAZQHsTHMbjKi800Zu8A4589fuMsacepanRYyFKY6bY+3QlkgiGnEeD+VCaushqb3jLUH793N+igdUo9/1Kf1ZBTURz9KrRgQ3nJqDDx75bdLQS9/ekmt1cu9bIrdGWrb6loTlZQ5HFVa5cWYQ4yu6sw9Ih//T5H6ZU0G6+sK7YpkckFFGRU/69TTIbMWkGOxVenaqAEClxm2LmRWrc33bKCJb78TIk+pr6y5THy7E8JlVOXqvHct0CSOw1bg+Msj3ri1ylwP3kv7C8kbN5EY2uG08HmHq0miXwW9w+K/igsnNFUWyvAJEGxqHDm32th6GBl1buu2Q5L4weQOfbfBogjYQqSYHg74bSqJaf3BXlY9tNaxOdOanIt6coFarzeRIR+lh8Q5Lbks7a8znFvJv5OXRG7Dne8ZbGcKjrTx0XuNasNi+MrIpkcAJjarVuncwFj8pjg1cImXK/8hYIHZZtWNe87STfff8afSoMWTcYlHhqHbasmyYPtjCvLmEOdh75ZEQg+qt/CVHHXJxyZOJhLbGRVAePoi1bM8FspJ3ygMOS4ZnHtXAdioOk/9kEXea8noDmBGJHF3KdxTv4c+Tdn2KFoZdfrkXztinCSoVL/u5KbWYq5/+dzagrj5cb6LJBpLebFaee67fU84RnLS0YuupdrwDzMjIuATuzLahv4feTcO+Wt+JVPkeeFHh6cPKFZc2HpVLslXaSnRpHkQoMk4mh0Ji+NBJGFTwY9S1zT7K9UKOi/wvyPE51hTiAktuTIKVocZsOHHlo/Lm770qiRgdqW5ukob7wqXp2dt6yA3kqAAgBQN7SRGMV8jIKFyP65vhpzzM2qeRzeFkgIXI8hnIqDy/m9p2egO+Tq9oafT0GujzQJUaZ+HAiX37AB2lV6oPqBJN8LSxLWrOiGybiOgwsKErBWrCUGYF1spxDxhjNYEAcT9V33rmnkgSBD+QMl0oOpkvqI7nSMJL+9fxMOTapPIUGATSkGpkindXk3oFzpjkFqPey2rNWy79yervHpPjtkWHXrsGAO3fSZFVrv2rKcGFIEnjeIVP8K/vcdJPtUYyJWF7adJSuA6pyi6hHycIQNieezwNqps/wXnBZLBowjQDbMvEyZ+hHFZKd28L4mdqe7kEHPhzkJbIJyoejnZG49HqvAEXVspRvdLNcrpUJV32rEKAuxKbqNMsYqnSm3UeVYtkAZdQnA3j8VFojbguq7WJYCDsYo4N5JQr6EA9Rc2p5TG7wmQP1cihVjbzL7NrIrODgOU20qUu4R/cbrvK+N3RqROyNG9L2iizm3amBMr7cFCmsaBM8EF8Jf/yoE3e/va99S54usYokN9WLHrbaiTWJFCjTs0ydiY4yTrm86l3hfgk82wcdc4jONyBkBk1wDgBs7nvdEdDLzGCENMGjQnjEtcYPWCtKiIZqmn7DG/QU2KjIEyaOTyNXtXrHocn3tOXJ9CJ6j5Zfyuw7ksLiyXTNf0wYi5uwXMGkDbw0/W/MDFVCmX1yUKGUzeGBrH1nWYIO49v9AgETI0DUCJFDEhrHY3WIG9MPuhR/hr13rHPX+5WU0nlcMnffQCe3EmB6Xmht5JMb/Y9il7/6vzCO0iDHo4E3O+ggtszoT+rJ4j5N3wZqeB8UbbCYRddE9q5uzRBRpU/GAJShB0J9RCfbBuc7s3NVLXTxMUm9sir1tG2iS9mq6S7y6ZZIrWLIzVuVRY1ncnCWjW7Ve5ycGF7ubgCXOpnalqr+ciW7uUC1BXiwxCaAxi4BumLFVHHC+9tEg3H8epsYbpYgkXyRmVlhMSORlbeiYVNxe8Y2QhsfKqObf9PcmxtNmwRqrf9eeJlMMPDR04QXJBnKzwWQW351/qcsR/PDyKurkXM9qTSiHVRgcR/7QrlfF9fWV8s6NAP/SmMekVcCwfQVxxXsAwL2kvduo4P26BTdyUbda0xFTWOBO3V2/1RdnEKJOhF4nE0NojET9PbBRg0zPeg8Bw0tQwf1I34m+aZJgh3GEC0skaMkJYr+y/yBHK4ZqrOljzDbohHMeDWJRwDIbRIEbiW89wB8ulZ4T8qQgnL2CYikq3wsQ13slfDf1jjQc56IAnRJYX6z4HdR3O0fd3duWiI4zKpr66jQw8Vlaj3J+U3+hQIO+UO8JZWyz/t5y0pbk/9C27TTjnxpUBJp+H3mhgUywlCHjJRvu1FOkG4T5fNg97Ec5yz8OgHOuqdZyUmY9olmyUQbSHAE81Uc+KFirjO00xT0yQK38p6xcnC/m6QQA29mWGQC2topKvAObH386Kx51K6V4Txmt8cZM0nTgbBLM/m0AJtssCNK0ZaE2yX4Mva7kvWy+X/qlaMX4DVsd/OAeEtl3f32F4U3vqbgZlO9zf2yzQrbbHW29uFNa7RNsZ+fS0ebR2ENQlMjv27wjtoCI5PrXxHCceWKg6NMOyetN87EAu6y7X1mctKYOBg0e60meCteqg61H48z4X60ZLM1ohzVMgAZ2pOjmMPQ0km/p6wTbpQe1ncmjNffEzIhdm/lKKXE+B1/+lYR6BIDSXuzCPY+hB6kD0/fQwiQbvDAFLxUDaDqNlJ0/um7PJHu4ugiUbNShrO1Ru0pQ9tWUFltiFBZufejGYOyRpHpcGDh8zD7iMohfhWt3mVcSv3s2TloveIWrXiCYLs3xm+flq+n51sPApgmxwZTB7U0j2U8ljboRxSYefSBiNcoCYLtdimh6hnhvRwVhJDteKs/3yWlCsoSkvfiCyreGHDrUasbekpDs0hHxmKWyNqmToJr6Xm4NHz7Dp9xoz2F4qiMTDmkHZ2szooJZ977aQIri9QmMVLZsf2KWS7qLjHzx/YNhvBuzMxwIeIJc2NWMS0ItHkRZMmQnEU9QpuX46DOp3JraW3oTvApohDXXIxz7+wfGyJB6elf7bEnuVQdU8sy/pAMETd/3XTptCMaSIDTdb2ooGqxNKIKwez0haWKBS+m3z50FCdPV6TkXXIUThn5nyr3mOaLwfjbWN4VJN9ohjteKuZfC5MEz0XBChKOIv6zrtbAoKBUZhM4a2EEHmYkyvLguqNgC1olTZWvUa7evUzxf/JlO0/WPfcs4bFr0kOmGZy5/Y0uPbOlbYlTaOEusNgUfSt0SRV0I3G2bgnq4vkhYiz0Y+j93x8Z6JdkEgFjGrxfAcl545Jyrsw1CUEtZYsTz6qo60HH+GS5O54bAktpTe44eL87pCLyG6bpXXoe3EEj1bj/cq+KjzITVjRu/Al1+cmWmKaed4+yMPrGDuSe5OP9t80kehT+9O9qLes8T7tJYN27iDwamzbwG4vwb8nh/dSoHcUJbldjolbqzCClvT0SJiHHbcU5RnZx8ciIwqLErk3K2sYhiFUlFJa4SxPCSHlOf8/lU1KVf7gQwfYaYXulviuok9gLPUAj1B9uvsRxWO0FawTXoINf5GX0FpPltD2+lP0Gn7DrOtt0XyBkyn31N3SWruvRMe420MSo6EjFqnR7BZTsANO2W+SU5dpyUEzflzyVfZsdelb1ggHyrfOpBhvgHnxALCFso0HeBUkmVgN3OCeGvnfQEWIy0FM/ea5uk5d9nlOpQ+A+atdPrHYSUjZJZJaVowuC2k65KotojaxsOGpRLyJsh2cNSVLX9VYg05rPQcv7qwF6l3rSigCLYiLWDYop3/p6gq0Ja/jXpzaqpu1raWzm4lB52H1h7GuExP+Cn8cN7cTK8eb+2drRW+bzR+QnVVK3vnXWZI9oSEX903EgY+ASh8vsOIrzIbXv7UaIqHRg9PKejRKehKt7RdCBEueBuiQGUQkxkVuF+VaBO9ZgCxTS5f4gFFqwVumi5LQjdEPMCrohneitUFfxqsLbCVbivipxrawqEsC+gPVwi5DUZteNaVOvgkmx9ihTo4TeOHioaXhxGYcE3KQSFqgWqY7jJz+vfEz4mdW2LAhJogf/K3RXVs6YpZs467wqSonVFtR7uuALNA/m8dhvGhKKJkkQFgmm8qPQG/7XVfq4/ziWGIvJ5iOdU9FvrsNm4NHxPqx+0HiVyPKq2HyM3shE5pskR+vCcKXTUGo1+jUAc0dCoSRgiMk1nUvZPPT/9YzYFL0uMD3pDZ9CbqFSo3PzXnRuBS2eZq6jNWMeR45wraZ/CvynLOy8y2EAlFSXQT9u6UiOlER3yO4y2TbP8chMw2LTIjFCwDmbRU0eo7QrSvnfczW9CVFd8NqKCz2Qa4wc/rkuhm1AUkAQZ6SNLSxdujGa/BbinYb8CKgv8mDkKQFzqdbJdFTc3qiGqQQU3BRxEOGsKa/2jUEhrZGekfsZfzDrxODwB3Aw9F8XZTDZA8MiIJskRV5oqX0rrWK5Iu5Ndi6ukJBRAaWKbPjET69Y0BSkmRvSlibQLvo23r4awB63TpL78nVrQPVFvmFWH3EegjXJ3/J208boMIQIxOI05gimtMSx2iep+IGCYTwt5TXnco6cMVTdggzWywmTaXGMy9ImR8GUqeIXnSp0xnbd3xFPnET9rNIyBWcBArgU1w/0qNvslRJJ3RFV+tuimNwDuQ8eS7Jr3x66S7WiDygSsDKPy2nAEV2oRWqmKkh5C6bx3L6K42d1CqsN5JtPuldEsUsRjhJnDFFbgwxD0kTUO5vblIPTYFRSyjthulXNEOVuyi7rfuaGqKKksZv7tj0YxhT9aPRM8rMzCKufB7pkWGDYkNHjcQn3sOJUkOEv42fennmZDSY0p55pqFHS4D3LSjzcWk7W0IfntjUOZTzH2NVRa6bDTW13FciksDVBRijyUPNyldJOI3PCTFtI4Uvk7A04AWl7wYuKqvsByznOlAqhYhZQsku56OFb37/s7jJGgQkwWGawUsZpOx3wE1f1XTf8X5F9PyZ+PsCTP4inToHn+zxRODZwBxHFqtNgoQ0+q4xQUn0NKJD9F927ESmDJOdiq16tgBiLGBJbgHbUgSJmdmoxwvM2UKQ5f8Lo7evlq0exZGwbyRGXxselL3nE5h15GTyqkYaelAMlW3XZ3D3aNNV5dMdDF8anfjSYMqaE3BT6hDt6jwiO4zcx0sboj5RMsq1RPwNXyimTpk1n8OcbRas3AN0P5AHTLOKMDW8O2k4WCSuSUNKLci8VwLLe6r+MeVGLBFWNKvk4N16S6zmnYz0q7kcqSrCrx0yy3xac6l1Ij0LMau9BF2FnJrYcRafb6+oRtmKrSHcjslFnE3+WIVIJHi4HvsOtD6g5ah3L41mpT7Q6Si6DX63I2LVO+PNJgbAZpQC1zK1UYiQDlIDsRcb8BdjCgd0t1ZQfHkEYkPeuI7iHSnKLUjfORF9hc+Hv//lV7rRXI7JTI3GQsoKfDut+o82PuMEll8fbyJvZJSHDe+8eZh6qUx7QTHCrAens3mMY/dYPfk2i8PZSXWjOpZngL96znjA6LwZ5P8GR53X3lfZLxBEIGKmcFXRCLRwvJT2RBgepk5voWKu7/GU8CRyVxNKtAbTNE5zyBwub+FdOwvByFcedg10CggjEeCvkWffVljyBMu8A7OI1Hl0ljqjYCJxmSAy3PXuV1h9ZYI+6WylZsVyue1NYB5LLrzjkY1qBK6tPuTqo/pbfNYIdqf5ygVTQXZEHFvTYFjOzaoiitWr5RP19PrU5XMqyrhf9Mtis+TL7OsWuCvB31DO4lP24w+ssww6zyLhQ/mzcggti6/bkCZqW5+yDGT59mqw3PqBCVu8S7y/tooKdy+iWEUJajN0RkwMm50NCfH2Enx0UTseGqoH3t/lR6yiZUSGHxAmz/GWErND2cKQAToi76r01yPl7oGt1hnqA9Rat1vOZ9xPFMWRhlUGlD6pltISAuvAGUsI6Y/pcGQ/+0xmF1mjD5Xdik0KZROQ6gcrirllz9t4QRmFJTA83tRpJZsKBjwMJNWfrqHNPJzZ5b4IDp3neciWuLWQ+VhVPqFrKTnIvXIK8XkOIZs6uCz1iUGlP9GFz8Q1WKWJtzoh2UTOsbYfSJOJFgNibwatbdFP6B/9QiRi0ZjomqzLTfcZS60psZbHXSJ+MRpmCDorgU5fq2Z1L5Qed/+ULGfM0cJJSPYIah0wQqPKdYVP1vTpNUvsSeAUDjyTFsqpQ/7cQ1X87qChbFX3cD0t1GI3WmBbQ9P5kHBuncC7Ds9NDz+hv9FXtsvoJjKzpzeSQuv0E20RfGx9NgTz+2WsrbVu40WudQmZtG8iwyAkRrIGZRQ2N3Vdg2T3H8QijzoNDzP5tJbAUoREGSSBv0C8rk8TLA5Gu7TyRoYR5v6FqiW76lCcVNa+VTc5BhKbMvNntjGssz10FDp/vIjT78/ShjhrjicRFKsT0OziVBu76YPtRZTkBoNaf49PwaPQhzGTqHh29w3HXuTOH4Gla3QleaY+MYxcEkRP0DTpxqauLqrUmPtgcl3YtBZT9OHuL4r476r1wkT5fxVDMJobVrxlSgdK+ygidRMDzEkRd1ooYBITTYW2LJuLR2pc3SbjK+tdf6vFdv3nZiMpMYqbbFhJeCbTDnqahqx1zd7fOyXf4+FYVLbBbIclzZ85m9v1f76iMmhuVp+sVPjITGH7tJYLwsrcZ7FNikV0T4pC0cVmijv8F69FPAA7BixFFKLLDzxDtEGrjef+5JtwmdX03dfG4vExgYPjkJ5SFtxjsF6glMjCktQmX68xAYq3c20YwxTxlTETKvoS3EFnX8hYww/QvntsW/XrQZ2WyJwRuyGCTnE9sFlV2w+3ME6oS/6/hgG6PcvsTtmYSUrJPaHjIj9nxZ6FNQNDPz+CEsbKbIx5jOGtzUNeLXcvhoyM/bjvYGKgxPAC24wcTdfDfFSucqXcjNbqfm99tb4wNr8wgNtD2NcSOJwAO2z+2sLCbF0vsarDgHE0ZN6mwBI7BKKmUdpKEHAR89apiW4fgBQUyvlLlWWgEOwAaIaGoJqPByvsJRbWNFgPiFYhZHstuHHT16gmqHjEvac6XuSQi9xeKwMJqDt2Z3mvi+yMzgQo0jvRlUJcHlM39RSIHvNXjQuIB8Qd0OnzD2dolNgsWqgMH1K5swQtGMzDLWllMWGLwvZ42tb1JWx4sOTeCj+oI4bwAlDAAYiJx/e5cr+TPYZwZKl57mmzRgQMpHltYDdR6oj5tpV9lMH+kC40YvzS7a9sxWh7JDFDzMgUJifKW1udRObrmOyw3OwGZDfOHF4BQcAACz/0xwqNeZzq+AOGfssI3mEh14N4Wo5Mq7dco6UOnIAkSv80TmGrpNbtPafQZxERgHMvvu23JBEnI8bTDm+3zTx79pp23l2EgjuboiUJnKgy/WRNtDqC0HrwE5tPVBiFa5PMZcT7gKdb/tOsCeiexvL/Y5qWjxX2f4a4feHzbOUzBUny4IWu7sldpjYX30QpwVaLk1vlSvCvpivyMz82ie5ELKUwaxAPbfqQ/lz2W1ep7Sd+k6IMHvSWKfItgy1XptQDjdm0Lr3ePO1gSn3xzigOMDzQlZrtf8TE7+5pLMZX1cyNuOIcryEsc/AvokziLQrsRf4jl4F7w43+qjbgUfhBl+k0q4sttm/bWxI2KlkAf8fiVEI+p/4wejH01MScBwHI46DjJudIiZ7HjjGTtzfZ7xT3YSbAsVJkSlL0ZVHhGGHlXPqb2/jnBeV7d83zGea6l/7L8PaMcQ5ehd7KpvdEqglrGZPIJyvTBbpA7Yp6TtRT17cIOMcCfi68K62CaA8eXRR1wVXnqR1joAv0HMq5USNxHn4yqAHuGn0X1lEmQcitnIIgPSi1eCbRv3Ibsn+sBXPGAHeyN8gcXKsFKKUgG9g6COC5ggYvoF6BxmijBGEtADdv8bfHuEj7jp/Ai/RnB079grg9ozK175BWGLiQCSHQQbwEfbDcaIhLR8jilJhQ02rhullTPkDE6ig5gfrGb43RqUliwbDDK8jRZzQKXmbjILv3kg1xnEGVhQgB8WtsMNomhzIAma2oTaAzfZiTgBrXq7S/2p+/W/WMxA8bOk6BWKayXkwt4GLu1hG/hz624TTEysTidcbJET7jifobImtY7SmqccMJiIZoUP6idRCPmef73WWmx0LlimayzAwQLl7hdnLaHlbia43fR2MbcVm6xxeUZXUVyuhJDEUMltetcAbOqVwCLE0qOxD2Gl2q6pvJt8pRKOhJ/zqXTRtX3mIdfilbDNu4Oxhh7c8IrMJ417e8+b4Sjibti+QSzzjV+gbcSkU5zQf1fg8E4CHxnzBjnOT1f3jDcI6ROTyBGq5vlE+2rd1o2Dkj+4ISNhFVj5h3kBgkeYHBUSpZl3kyYMRqBLm9rr1to/V3O3EY7Ko+NGo1fQdjc5so0qfM4RVUBbv+goD8Chjs7woy2hrIxZ/F37zX5gLVZ7TGVYoC+M1ktZGtKgruSijufJ58VRvRj9sHS6mVyjMSVH9fjWVO/MoUdzDqxx8Rj5eifsdcEQC2SuahEy9j7wEvqdirZMnEbxm79GsBkVOnzXNxmbatFV9bJGpHX9W3panEDTXDXNXXiC6pqGKpGdZl9uyKoeNreGBy0nmtr4ZqGYfLbwFlkNT25hYMIt8s2gMoMJAqN0zaB4Ca7zgkztnhCKowztl9nKN10XWXQ42SfYAQHcTkwx2tn5MD+sUj/rBvoBDRrLPxO/cFrq/hnUpaqpbETlxMjfWb18xuiEOnFRqnReH4MwG5neeXieN7kcUyFTdnQ3rKknVb8USR7kLGZ+I3B49d6gMZPt1AxQHnSsDIeudPzXJ0qoLzQEtNsPQ/jluXZlBeGm3EjJPZ0FH3EYm7WHjciVUASWmEi4dU10EHOjRk3QpOL0bgyPG9YYO4eYRleHSdEsgOKsQoAydh1vjhoLlbDpNzxDyzhsSYMzleDkhQZ8B0dCp80Jly1Sx45v0DzibHB8Fb1iEzQ0DvPvMkGHToB6qihmKtI8rsyDSjZKBZSavWHqq1pC/DjvG0tBMbV5dTR2de22oeGE=
*/