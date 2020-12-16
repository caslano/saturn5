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
0lNnG0t7rdgI2g+ZtNr7iH20K7atu7d7x6b1C8GRYfGR3kGzY6Pm6+cVB3h6bj5pVyxppHjrukuvkSjSvqtm0xlRVn2IeezKQVPdsYVD2Yd0xV8JyBFKahaHmv7iKT7q0catGy09nxz1+RXDE++e08/bXPHIcM+bV27rvx+QGvri4X50oXdOTtHlLENxShvHtxotBp9tueMrxUc5uvdLXJ9oi756Ucjt3ati3KLxxPWRzhTV28wVQgK91TOEH+ZET+EN5dVFXblcJZKG4xIhU/Fq/OIgWG3BlZnIuaWk81zHCNdltkje+drMe0z+8J1V9bk+J57c4Owa5sI7Suy9a4dDsj1UJPgTpUdlphe7yN8cUeS65u//s99GRdHAiNz7Bh37p0QnerGh9e4NzQeB+exMAg4pyXcDFUZjahzkdZ6Rs4h/vdvUwsIwyPcE92RqjDRfurgy7IN34LT1KVmldnyPpq2M++spMsnUXjLKK603EUX0t7rb/gaPj7Ew62cfXvbpHLf2k5UU9+w0PfBkaVp6nByqrUG85+SxnF0g4sSo+tHsZl/VecLhZcHfPH1MQm58f+gr7dry53QvgbI0ovMzNx4XUS2RfcHNPkByX2/IPV4uaQ+s2u1oHPWXHvxUfJpM4t1qwrZX51Tm0BEZPP3l6QlpXDon8U+/Mb9jv2H2XEqiyW327HkpqHfgGzGcqCo5424dG+vhlbrDod9CORaIfvOKU0S939h0bktL6OQts6vaR1iPWxneaLRoce40u1R/7vvHEJ+BXlY+SwN/U2YS31tb4kGCTOcldOcnXpoLmCR3XPgsolBNz0/gn0K+gcdd6hn01GNkPC1yza7qsWDQMaNcUc4DR8d1Zglcus1uJItLpHw0d8bol3MX3qtaq4XujcyoXA5FR5ejzG+IRIrJh1vI+jHuJzE6vQ16kClsxjlzIkA1KNEv6kSpZM/B2CGej5lJY9zXG7L6arQSJr5pf24yv2Mxr3I4yB0vpzw9l2so6KRl2WiF7AqriV7XZJDgipbTuiOxZvqpF9qKXwfrDG+VTdHrWD22/RAo0e3AP4TXuVDV1ZNlcMmvnCzbvfDai1Lhzy1e4vF8340INY8amzou+pvLTrPcozQqTTKjHWZLZwj9xGVZOZOt7Oc1WMHGya9tJNrtdJ0hvtvjWtiRZvzSSCX9g5f0tqlFLzupchiIBMkzzEbuhrYJDFfOtjaTa+KWDtPIs46L8GiVXuQ1S+Wdll7y5md0eHCdUH0t2IKpGe/cWvyZDEF10mwhSoo4E5qgbecbiVzpcgbmC7nuLdezhHEd0jR8aRlfqrwdCfxYSZO/qJsqSbbd7rdtyN98Ye7Gdc7Pyyibc+/T1MTUsfcsfuUrHRIqQTQqP5eEJjhIfeaV2878KmETFHpvK3rTxHDJWWfLc8jgm8A7Iep0WcdNQa2FnZKdfl+qdo/gZb3h65+M9gWG6D6ejfbcthH8eXkFv++Z0FOKHZmGovnxbGLlh83k7INveAQD/FrWhr/eLTbuaaEPJzVpqq+daX1hqrKRU72zLPD+6S8BbKV3mgLCVL8MVJ9jiJiiZhL0mJXgzprDFTW/+WJqrfQaSX7EVUjwfCW9uTkom5gwtiVQQef2MokhOk30wdfinmzqirjG1HkHyuzLzdXNMqIap6p5rJY/3ya4nu9uw391kVuEups54BcHA7LdH7FDbbxzRhuxeid91fRivKwDtdpzLLmUTOiC515djew1EQvcHmU/Eu4jZqfcPXWI3CToNaOzyIBic/HXOZ1rr0r8ay4X5R9lD6kWM98pLlspyTCKllGg3fO0JThUE1akFpb53NxIWv4FeyCBQaWE4WWn+H4=
*/