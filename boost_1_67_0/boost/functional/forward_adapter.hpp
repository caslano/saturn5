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