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