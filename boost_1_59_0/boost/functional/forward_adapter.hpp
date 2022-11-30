/*=============================================================================
    Copyright (c) 2007-2008 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).  
==============================================================================*/

#ifndef BOOST_FUNCTIONAL_FORWARD_ADAPTER_HPP_INCLUDED
#   ifndef BOOST_PP_IS_ITERATING

#   include <boost/config.hpp>
#   include <boost/config/workaround.hpp>

#   include <boost/preprocessor/iteration/iterate.hpp>
#   include <boost/preprocessor/repetition/enum_params.hpp>
#   include <boost/preprocessor/repetition/enum_binary_params.hpp>
#   include <boost/preprocessor/facilities/intercept.hpp>
#   include <boost/preprocessor/arithmetic/dec.hpp>

#   include <boost/utility/result_of.hpp>

#   ifndef BOOST_FUNCTIONAL_FORWARD_ADAPTER_MAX_ARITY
#     define BOOST_FUNCTIONAL_FORWARD_ADAPTER_MAX_ARITY 6
#   elif BOOST_FUNCTIONAL_FORWARD_ADAPTER_MAX_ARITY < 3
#     undef  BOOST_FUNCTIONAL_FORWARD_ADAPTER_MAX_ARITY
#     define BOOST_FUNCTIONAL_FORWARD_ADAPTER_MAX_ARITY 3
#   endif


namespace boost 
{
    template< typename Function, int Arity_Or_MinArity = -1, int MaxArity = -1 >
    class forward_adapter;

    //----- ---- --- -- - -  -   -

    namespace detail
    {
        template< class MostDerived, typename Function, typename FunctionConst, 
            int Arity, int MinArity >
        struct forward_adapter_impl;

        struct forward_adapter_result
        {
            template< typename Sig > struct apply;

            // Utility metafunction for qualification adjustment on arguments
            template< typename T > struct q          { typedef T const t; };
            template< typename T > struct q<T const> { typedef T const t; };
            template< typename T > struct q<T &>     { typedef T       t; };

            // Utility metafunction to choose target function qualification
            template< typename T > struct c
            { typedef typename T::target_function_t t; };
            template< typename T > struct c<T&      >
            { typedef typename T::target_function_t t; };
            template< typename T > struct c<T const >
            { typedef typename T::target_function_const_t t; };
            template< typename T > struct c<T const&>
            { typedef typename T::target_function_const_t t; };
        };
    }

#   define BOOST_TMP_MACRO(f,fn,fc) \
        boost::detail::forward_adapter_impl< \
            forward_adapter<f,Arity_Or_MinArity,MaxArity>, fn, fc, \
            (MaxArity!=-1? MaxArity :Arity_Or_MinArity!=-1? Arity_Or_MinArity \
                :BOOST_FUNCTIONAL_FORWARD_ADAPTER_MAX_ARITY), \
            (Arity_Or_MinArity!=-1? Arity_Or_MinArity : 0) >

    template< typename Function, int Arity_Or_MinArity, int MaxArity >
    class forward_adapter
        : public BOOST_TMP_MACRO(Function,Function,Function const)
        , private Function
    {
      public:
        forward_adapter(Function const& f = Function()) 
          : Function(f) 
        { }

        typedef Function        target_function_t;
        typedef Function const  target_function_const_t;

        Function       & target_function()       { return *this; }
        Function const & target_function() const { return *this; }

        template< typename Sig > struct result
            : detail::forward_adapter_result::template apply<Sig>
        { };

        using BOOST_TMP_MACRO(Function,Function, Function const)::operator();
    };
    template< typename Function, int Arity_Or_MinArity, int MaxArity >
    class forward_adapter< Function const, Arity_Or_MinArity, MaxArity >
        : public BOOST_TMP_MACRO(Function const, Function const, Function const)
        , private Function
    {
      public:
        forward_adapter(Function const& f = Function())
          : Function(f) 
        { }

        typedef Function const target_function_t;
        typedef Function const target_function_const_t;

        Function const & target_function() const { return *this; }

        template< typename Sig > struct result
            : detail::forward_adapter_result::template apply<Sig>
        { };

        using BOOST_TMP_MACRO(Function const,Function const, Function const)
            ::operator();
    };
    template< typename Function, int Arity_Or_MinArity, int MaxArity >
    class forward_adapter< Function &, Arity_Or_MinArity, MaxArity >
        : public BOOST_TMP_MACRO(Function&, Function, Function)
    {
        Function& ref_function;
      public:
        forward_adapter(Function& f)
          : ref_function(f) 
        { }

        typedef Function target_function_t;
        typedef Function target_function_const_t;

        Function & target_function() const { return this->ref_function; }

        template< typename Sig > struct result
            : detail::forward_adapter_result::template apply<Sig>
        { };

        using BOOST_TMP_MACRO(Function&, Function, Function)::operator();
    }; 

    #undef BOOST_TMP_MACRO

    namespace detail
    {
        template< class Self >
        struct forward_adapter_result::apply< Self() >
            : boost::result_of< BOOST_DEDUCED_TYPENAME c<Self>::t() >
        { };

        // WHen operator()() doesn't have any parameters, it can't
        // be templatized and can't use SFINAE, so intead use class
        // template parameter SFINAE to decide whether to instantiate it.

        template <typename T, typename R = void>
        struct forward_adapter_sfinae
        {
            typedef T type;
        };

        // This is the fallback for when there isn't an operator()(),
        // need to create an operator() that will never instantiate
        // so that using parent::operator() will work okay.
        template< class MD, class F, class FC, class Enable = void>
        struct forward_adapter_impl_zero
        {
            template <typename T> struct never_instantiate {};
            template <typename T>
            typename never_instantiate<T>::type operator()(T) const {}
        };

        template< class MD, class F, class FC>
        struct forward_adapter_impl_zero<MD, F, FC,
            typename forward_adapter_sfinae<typename boost::result_of< FC() >::type>::type>
        {
            inline typename boost::result_of< FC() >::type
            operator()() const
            {
                return static_cast<MD const*>(this)->target_function()();
            }

            inline typename boost::result_of< F() >::type
            operator()()
            {
                return static_cast<MD*>(this)->target_function()();
            }
        };

        template< class MD, class F, class FC >
        struct forward_adapter_impl<MD,F,FC,0,0>
            : forward_adapter_impl_zero<MD,F,FC>
        {
            using forward_adapter_impl_zero<MD,F,FC>::operator();

        // closing brace gets generated by preprocessing code, below

#       define BOOST_TMP_MACRO(tpl_params,arg_types,params,args)              \
            template< tpl_params >                                             \
            inline typename boost::result_of< FC(arg_types) >::type            \
            operator()(params) const                                           \
            {                                                                  \
                return static_cast<MD const*>(this)->target_function()(args);  \
            }                                                                  \
            template< tpl_params >                                             \
            inline typename boost::result_of< F(arg_types)>::type              \
            operator()(params)                                                 \
            {                                                                  \
                return static_cast<MD*>(this)->target_function()(args);        \
            }

#       // This is the total number of iterations we need
#       define count ((1 << BOOST_FUNCTIONAL_FORWARD_ADAPTER_MAX_ARITY+1)-2)

#       // Chain file iteration to virtually one loop
#       if BOOST_FUNCTIONAL_FORWARD_ADAPTER_MAX_ARITY <= 7
#         define limit1 count
#         define limit2 0
#         define limit3 0
#       else
#         if BOOST_FUNCTIONAL_FORWARD_ADAPTER_MAX_ARITY <= 15
#           define limit1 (count >> 8)
#           define limit2 255
#           define limit3 0
#         else
#           define limit1 (count >> 16)
#           define limit2 255
#           define limit3 255
#         endif
#       endif

#       define N 0

#       define  BOOST_PP_FILENAME_1 <boost/functional/forward_adapter.hpp>
#       define  BOOST_PP_ITERATION_LIMITS (0,limit1)
#       include BOOST_PP_ITERATE()

#       undef N
#       undef limit3
#       undef limit2
#       undef limit1
#       undef count
#       undef BOOST_TMP_MACRO

        };

    } // namespace detail

    template<class F, int A0, int A1>
    struct result_of<boost::forward_adapter<F,A0,A1> const ()>
        : boost::detail::forward_adapter_result::template apply<
            boost::forward_adapter<F,A0,A1> const () >
    { };
    template<class F, int A0, int A1>
    struct result_of<boost::forward_adapter<F,A0,A1>()>
        : boost::detail::forward_adapter_result::template apply<
            boost::forward_adapter<F,A0,A1>() >
    { };
    template<class F, int A0, int A1>
    struct result_of<boost::forward_adapter<F,A0,A1> const& ()>
        : boost::detail::forward_adapter_result::template apply<
            boost::forward_adapter<F,A0,A1> const () >
    { };
    template<class F, int A0, int A1>
    struct result_of<boost::forward_adapter<F,A0,A1>& ()>
        : boost::detail::forward_adapter_result::template apply<
            boost::forward_adapter<F,A0,A1>() >
    { };
}

#       define BOOST_FUNCTIONAL_FORWARD_ADAPTER_HPP_INCLUDED

#   elif BOOST_PP_ITERATION_DEPTH() == 1 && limit2
#     define  BOOST_PP_FILENAME_2 <boost/functional/forward_adapter.hpp>
#     define  BOOST_PP_ITERATION_LIMITS (0,limit2)
#     include BOOST_PP_ITERATE()
#   elif BOOST_PP_ITERATION_DEPTH() == 2 && limit3
#     define  BOOST_PP_FILENAME_3 <boost/functional/forward_adapter.hpp>
#     define  BOOST_PP_ITERATION_LIMITS (0,limit3)
#     include BOOST_PP_ITERATE()

#   else

#     // I is the loop counter
#     if limit2 && limit3
#       define I (BOOST_PP_ITERATION_1 << 16 | BOOST_PP_ITERATION_2 << 8 | \
            BOOST_PP_ITERATION_3)
#     elif limit2
#       define I (BOOST_PP_ITERATION_1 << 8 | BOOST_PP_ITERATION_2)
#     else
#       define I BOOST_PP_ITERATION_1
#     endif

#     if I < count

#       // Done for this arity? Increment N
#       if (I+2 >> N+1) 
#         if N == 0
#           undef N
#           define N 1
#         elif N == 1
#           undef N
#           define N 2
#         elif N == 2
#           undef N
#           define N 3
#         elif N == 3
#           undef N
#           define N 4
#         elif N == 4
#           undef N
#           define N 5
#         elif N == 5
#           undef N
#           define N 6
#         elif N == 6
#           undef N
#           define N 7
#         elif N == 7
#           undef N
#           define N 8
#         elif N == 8
#           undef N
#           define N 9
#         elif N == 9
#           undef N
#           define N 10
#         elif N == 10
#           undef N
#           define N 11
#         elif N == 11
#           undef N
#           define N 12
#         elif N == 12
#           undef N
#           define N 13
#         elif N == 13
#           undef N
#           define N 14
#         elif N == 14
#           undef N
#           define N 15
#         elif N == 15
#           undef N
#           define N 16
#         endif

        };

        template< class Self, BOOST_PP_ENUM_PARAMS(N,typename T) >
        struct forward_adapter_result::apply< Self(BOOST_PP_ENUM_PARAMS(N,T)) >
            : boost::result_of< 
                BOOST_DEDUCED_TYPENAME c<Self>::t(BOOST_PP_ENUM_BINARY_PARAMS(N, 
                      typename q<T,>::t& BOOST_PP_INTERCEPT)) >
        { };

        template< class MD, class F, class FC >
        struct forward_adapter_impl<MD,F,FC,BOOST_PP_DEC(N),N>
        {
            template< BOOST_PP_ENUM_PARAMS(N,typename T) >
            inline typename boost::result_of< F(
                BOOST_PP_ENUM_BINARY_PARAMS(N,T,& BOOST_PP_INTERCEPT)) >::type
            operator()(BOOST_PP_ENUM_BINARY_PARAMS(N,T,& BOOST_PP_INTERCEPT));
        };

        template< class MD, class F, class FC, int MinArity >
        struct forward_adapter_impl<MD,F,FC,N,MinArity>
            : forward_adapter_impl<MD,F,FC,BOOST_PP_DEC(N),MinArity>
        {
            using forward_adapter_impl<MD,F,FC,BOOST_PP_DEC(N),MinArity>::operator();

#       endif

#       // Zero based count for each arity would be I-(1<<N)+2, but we don't
#       // need it, unless we need a nicer order.

#       // Macros for the parameter's type modifiers.
#       if I & 0x000001
#         define PT0 T0 &
#       else
#         define PT0 T0 const &
#       endif
#       if I & 0x000002
#         define PT1 T1 &
#       else
#         define PT1 T1 const &
#       endif
#       if I & 0x000004
#         define PT2 T2 &
#       else
#         define PT2 T2 const &
#       endif
#       if I & 0x000008
#         define PT3 T3 &
#       else
#         define PT3 T3 const &
#       endif
#       if I & 0x000010
#         define PT4 T4 &
#       else
#         define PT4 T4 const &
#       endif
#       if I & 0x000020
#         define PT5 T5 &
#       else
#         define PT5 T5 const &
#       endif
#       if I & 0x000040
#         define PT6 T6 &
#       else
#         define PT6 T6 const &
#       endif
#       if I & 0x000080
#         define PT7 T7 &
#       else
#         define PT7 T7 const &
#       endif
#       if I & 0x000100
#         define PT8 T8 &
#       else
#         define PT8 T8 const &
#       endif
#       if I & 0x000200
#         define PT9 T9 &
#       else
#         define PT9 T9 const &
#       endif
#       if I & 0x000400
#         define PT10 T10 &
#       else
#         define PT10 T10 const &
#       endif
#       if I & 0x000800
#         define PT11 T11 &
#       else
#         define PT11 T11 const &
#       endif
#       if I & 0x001000
#         define PT12 T12 &
#       else
#         define PT12 T12 const &
#       endif
#       if I & 0x002000
#         define PT13 T13 &
#       else
#         define PT13 T13 const &
#       endif
#       if I & 0x004000
#         define PT14 T14 &
#       else
#         define PT14 T14 const &
#       endif
#       if I & 0x008000
#         define PT15 T15 &
#       else
#         define PT15 T15 const &
#       endif

#       if BOOST_WORKAROUND(BOOST_MSVC,BOOST_TESTED_AT(1400)) 
            template< BOOST_PP_ENUM_PARAMS(N,typename T) >
            inline typename boost::result_of<  FC(BOOST_PP_ENUM_PARAMS(N,PT)) 
                >::type
            operator()(BOOST_PP_ENUM_BINARY_PARAMS(N,PT,a)) const
            {
                return static_cast<MD const* const>(this)
                    ->target_function()(BOOST_PP_ENUM_PARAMS(N,a));
            }
            template< BOOST_PP_ENUM_PARAMS(N,typename T) >
            inline typename boost::result_of<  F(BOOST_PP_ENUM_PARAMS(N,PT))
                >::type
            operator()(BOOST_PP_ENUM_BINARY_PARAMS(N,PT,a))
            {
                return static_cast<MD* const>(this)
                    ->target_function()(BOOST_PP_ENUM_PARAMS(N,a));
            }
#       else
        BOOST_TMP_MACRO(BOOST_PP_ENUM_PARAMS(N,typename T),
            BOOST_PP_ENUM_PARAMS(N,PT), BOOST_PP_ENUM_BINARY_PARAMS(N,PT,a),
            BOOST_PP_ENUM_PARAMS(N,a) )
        // ...generates uglier code but is faster - it caches ENUM_*
#       endif

#       undef PT0
#       undef PT1
#       undef PT2
#       undef PT3
#       undef PT4
#       undef PT5
#       undef PT6
#       undef PT7
#       undef PT8
#       undef PT9
#       undef PT10
#       undef PT11
#       undef PT12
#       undef PT13
#       undef PT14
#       undef PT15

#     endif // I < count

#     undef I
#   endif // defined(BOOST_PP_IS_ITERATING)

#endif // include guard


/* forward_adapter.hpp
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
*/