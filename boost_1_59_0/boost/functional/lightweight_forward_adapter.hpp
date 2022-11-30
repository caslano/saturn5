/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#ifndef BOOST_FUNCTIONAL_LIGHTWEIGHT_FORWARD_ADAPTER_HPP_INCLUDED
#   ifndef BOOST_PP_IS_ITERATING

#   include <boost/config.hpp>
#   include <boost/config/workaround.hpp>

#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/iteration/iterate.hpp>
#   include <boost/preprocessor/repetition/enum.hpp>
#   include <boost/preprocessor/repetition/enum_params.hpp>
#   include <boost/preprocessor/repetition/enum_binary_params.hpp>
#   include <boost/preprocessor/facilities/intercept.hpp>

#   include <boost/utility/result_of.hpp>
#   include <boost/ref.hpp>

#   ifndef BOOST_FUNCTIONAL_LIGHTWEIGHT_FORWARD_ADAPTER_MAX_ARITY
#     define BOOST_FUNCTIONAL_LIGHTWEIGHT_FORWARD_ADAPTER_MAX_ARITY 10
#   elif BOOST_FUNCTIONAL_FORDWARD_ADAPTER_MAX_ARITY < 3
#     undef  BOOST_FUNCTIONAL_LIGHTWEIGHT_FORWARD_ADAPTER_MAX_ARITY
#     define BOOST_FUNCTIONAL_LIGHTWEIGHT_FORWARD_ADAPTER_MAX_ARITY 3
#   endif

namespace boost 
{
    template< typename Function, int Arity_Or_MinArity = -1, int MaxArity = -1 >
    class lightweight_forward_adapter;

    //----- ---- --- -- - -  -   -

    namespace detail
    {
        template< class MostDerived, typename Function, typename FunctionConst, 
            int Arity, int MinArity >
        struct lightweight_forward_adapter_impl;

        struct lightweight_forward_adapter_result
        {
            template< typename Sig > struct apply;

            // Utility metafunction for argument transform
            template< typename T > struct x  { typedef T const& t; };
            template< typename T > struct x< boost::reference_wrapper<T> >
            { typedef T& t; };
            template< typename T > struct x<T&>       : x<T> { };
            template< typename T > struct x<T const&> : x<T> { };
            template< typename T > struct x<T const>  : x<T> { };

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
        boost::detail::lightweight_forward_adapter_impl< \
            lightweight_forward_adapter<f,Arity_Or_MinArity,MaxArity>, fn, fc, \
            (MaxArity!=-1? MaxArity :Arity_Or_MinArity!=-1? Arity_Or_MinArity \
                :BOOST_FUNCTIONAL_LIGHTWEIGHT_FORWARD_ADAPTER_MAX_ARITY), \
            (Arity_Or_MinArity!=-1? Arity_Or_MinArity : 0) >

    template< typename Function, int Arity_Or_MinArity, int MaxArity >
    class lightweight_forward_adapter
        : public BOOST_TMP_MACRO(Function,Function,Function const)
        , private Function
    {
      public:
        lightweight_forward_adapter(Function const& f = Function()) 
          : Function(f) 
        { }

        typedef Function        target_function_t;
        typedef Function const  target_function_const_t;

        Function       & target_function()       { return *this; }
        Function const & target_function() const { return *this; }

        template< typename Sig > struct result
            : detail::lightweight_forward_adapter_result::template apply<Sig>
        { };

        using BOOST_TMP_MACRO(Function,Function, Function const)::operator();
    };
    template< typename Function, int Arity_Or_MinArity, int MaxArity >
    class lightweight_forward_adapter< Function const, Arity_Or_MinArity, 
        MaxArity >
        : public BOOST_TMP_MACRO(Function const, Function const, Function const)
        , private Function
    {
      public:
        lightweight_forward_adapter(Function const& f = Function())
          : Function(f) 
        { }

        typedef Function const target_function_t;
        typedef Function const target_function_const_t;

        Function const & target_function() const { return *this; }

        template< typename Sig > struct result
            : detail::lightweight_forward_adapter_result::template apply<Sig>
        { };

        using BOOST_TMP_MACRO(Function const,Function const, Function const)
            ::operator();
    };
    template< typename Function, int Arity_Or_MinArity, int MaxArity >
    class lightweight_forward_adapter< Function &, Arity_Or_MinArity, MaxArity >
        : public BOOST_TMP_MACRO(Function&, Function, Function)
    {
        Function& ref_function;
      public:
        lightweight_forward_adapter(Function& f)
          : ref_function(f) 
        { }

        typedef Function target_function_t;
        typedef Function target_function_const_t;

        Function & target_function() const { return this->ref_function; }

        template< typename Sig > struct result
            : detail::lightweight_forward_adapter_result::template apply<Sig>
        { };

        using BOOST_TMP_MACRO(Function&, Function, Function)::operator();
    }; 

    #undef BOOST_TMP_MACRO

    namespace detail
    {
        template< class Self >
        struct lightweight_forward_adapter_result::apply< Self() >
            : boost::result_of< BOOST_DEDUCED_TYPENAME c<Self>::t() >
        { };

        // When operator() doesn't have any parameters, it can't
        // be templatized and can't use SFINAE, so intead use class
        // template parameter SFINAE to decide whether to instantiate it.

        template <typename T, typename R = void>
        struct lightweight_forward_adapter_sfinae
        {
            typedef T type;
        };

        // This is the fallback for when there isn't an operator()(),
        // need to create an operator() that will never instantiate
        // so that using parent::operator() will work okay.
        template< class MD, class F, class FC, class Enable = void>
        struct lightweight_forward_adapter_impl_zero
            : lightweight_forward_adapter_result
        {
            template <typename T> struct never_instantiate {};
            template <typename T>
            typename never_instantiate<T>::type operator()(T) const {}
        };

        template< class MD, class F, class FC>
        struct lightweight_forward_adapter_impl_zero<MD, F, FC,
            typename lightweight_forward_adapter_sfinae<typename boost::result_of< FC() >::type>::type>
            : lightweight_forward_adapter_result
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
        struct lightweight_forward_adapter_impl<MD,F,FC,0,0>
            : lightweight_forward_adapter_impl_zero<MD,F,FC>
        {
        };

#       define  BOOST_PP_FILENAME_1 \
            <boost/functional/lightweight_forward_adapter.hpp>
#       define  BOOST_PP_ITERATION_LIMITS                                     \
            (1,BOOST_FUNCTIONAL_LIGHTWEIGHT_FORWARD_ADAPTER_MAX_ARITY) 
#       include BOOST_PP_ITERATE()

    } // namespace detail

    template<class F, int A0, int A1>
    struct result_of<boost::lightweight_forward_adapter<F,A0,A1> const ()>
        : boost::detail::lightweight_forward_adapter_result::template apply<
            boost::lightweight_forward_adapter<F,A0,A1> const () >
    { };
    template<class F, int A0, int A1>
    struct result_of<boost::lightweight_forward_adapter<F,A0,A1>()>
        : boost::detail::lightweight_forward_adapter_result::template apply<
            boost::lightweight_forward_adapter<F,A0,A1>() >
    { };
    template<class F, int A0, int A1>
    struct result_of<boost::lightweight_forward_adapter<F,A0,A1> const& ()>
        : boost::detail::lightweight_forward_adapter_result::template apply<
            boost::lightweight_forward_adapter<F,A0,A1> const () >
    { };
    template<class F, int A0, int A1>
    struct result_of<boost::lightweight_forward_adapter<F,A0,A1>& ()>
        : boost::detail::lightweight_forward_adapter_result::template apply<
            boost::lightweight_forward_adapter<F,A0,A1>() >
    { };
}

#     define BOOST_FUNCTIONAL_LIGHTWEIGHT_FORWARD_ADAPTER_HPP_INCLUDED

#   else // defined(BOOST_PP_IS_ITERATING)
#     define N BOOST_PP_ITERATION() 

        template< class Self, BOOST_PP_ENUM_PARAMS(N,typename T) >
        struct lightweight_forward_adapter_result::apply<
            Self (BOOST_PP_ENUM_PARAMS(N,T)) >
            : boost::result_of<
                BOOST_DEDUCED_TYPENAME c<Self>::t (BOOST_PP_ENUM_BINARY_PARAMS(N,
                    typename x<T,>::t BOOST_PP_INTERCEPT)) >
        { };

        template< class MD, class F, class FC >
        struct lightweight_forward_adapter_impl<MD,F,FC,BOOST_PP_DEC(N),N>
            : lightweight_forward_adapter_result
        {
            template< BOOST_PP_ENUM_PARAMS(N,typename T) >
            inline typename boost::result_of< F(BOOST_PP_ENUM_BINARY_PARAMS(N,
                T,const& BOOST_PP_INTERCEPT)) >::type
            operator()(BOOST_PP_ENUM_BINARY_PARAMS(N,T,& BOOST_PP_INTERCEPT));
        };

        template< class MD, class F, class FC, int MinArity >
        struct lightweight_forward_adapter_impl<MD,F,FC,N,MinArity>
            : lightweight_forward_adapter_impl<MD,F,FC,BOOST_PP_DEC(N),MinArity>
        {
            using lightweight_forward_adapter_impl<MD,F,FC,BOOST_PP_DEC(N),
                MinArity>::operator();

#     define M(z,i,d) \
          static_cast<typename d::template x<T##i>::t>(a##i)

            template< BOOST_PP_ENUM_PARAMS(N,typename T) >
            inline typename lightweight_forward_adapter_result::template apply<
                MD const (BOOST_PP_ENUM_BINARY_PARAMS(N,
                    T,const& BOOST_PP_INTERCEPT)) >::type
            operator()(BOOST_PP_ENUM_BINARY_PARAMS(N,T,const& a)) const
            {
                typedef lightweight_forward_adapter_result _;
                return static_cast<MD const*>(this)->target_function()(
                    BOOST_PP_ENUM(N,M,_));
            }
            template< BOOST_PP_ENUM_PARAMS(N,typename T) >
            inline typename lightweight_forward_adapter_result::template apply<
                MD (BOOST_PP_ENUM_BINARY_PARAMS(N,
                    T,const& BOOST_PP_INTERCEPT)) >::type
            operator()(BOOST_PP_ENUM_BINARY_PARAMS(N,T,const& a))
            {
                typedef lightweight_forward_adapter_result _;
                return static_cast<MD*>(this)->target_function()(
                    BOOST_PP_ENUM(N,M,_));
            }
#     undef M
      };

#     undef N
#   endif // defined(BOOST_PP_IS_ITERATING)

#endif // include guard


/* lightweight_forward_adapter.hpp
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
*/