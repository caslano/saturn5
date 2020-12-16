/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_UNFUSED_HPP_INCLUDED)
#if !defined(BOOST_PP_IS_ITERATING)

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>

#include <boost/utility/result_of.hpp>

#include <boost/config.hpp>

#include <boost/fusion/container/vector/vector.hpp>

#include <boost/fusion/functional/adapter/limits.hpp>
#include <boost/fusion/functional/adapter/detail/access.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    template <class Function, bool AllowNullary = true>
    class unfused;

    //----- ---- --- -- - -  -   -

    template <class Function> 
    class unfused<Function,true>
      : public unfused<Function,false>
    {
        typedef typename detail::qf_c<Function>::type function_c;
        typedef typename detail::qf<Function>::type function;
        typedef typename detail::call_param<Function>::type func_const_fwd_t;
      public:

        using unfused<Function,false>::operator();

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline explicit unfused(func_const_fwd_t f = function())
            : unfused<Function,false>(f)
        { }

        typedef typename boost::result_of<
            function_c(fusion::vector0<> &) >::type call_const_0_result;

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline call_const_0_result operator()() const
        {
            fusion::vector0<> arg;
            return this->fnc_transformed(arg);
        }

        typedef typename boost::result_of< 
            function(fusion::vector0<> &) >::type call_0_result;

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline call_0_result operator()()
        {
            fusion::vector0<> arg;
            return this->fnc_transformed(arg);
        }
    };

    template <class Function> class unfused<Function,false>
    {
      protected:
        Function fnc_transformed;
        typedef typename detail::qf_c<Function>::type function_c;
        typedef typename detail::qf<Function>::type function;
        typedef typename detail::call_param<Function>::type func_const_fwd_t;
      public:

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline explicit unfused(func_const_fwd_t f = function())
            : fnc_transformed(f)
        { }

        template <typename Sig>
        struct result;

        #define  BOOST_PP_FILENAME_1 \
            <boost/fusion/functional/adapter/unfused.hpp>
        #define  BOOST_PP_ITERATION_LIMITS \
            (1,BOOST_FUSION_UNFUSED_MAX_ARITY)
        #include BOOST_PP_ITERATE()
    };
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

namespace boost 
{
#if !defined(BOOST_RESULT_OF_USE_DECLTYPE) || defined(BOOST_NO_CXX11_DECLTYPE)
    template<class F>
    struct result_of< boost::fusion::unfused<F> const () >
    {
        typedef typename boost::fusion::unfused<F>::call_const_0_result type;
    };
    template<class F>
    struct result_of< boost::fusion::unfused<F>() >
    {
        typedef typename boost::fusion::unfused<F>::call_0_result type;
    };
#endif
    template<class F>
    struct tr1_result_of< boost::fusion::unfused<F> const () >
    {
        typedef typename boost::fusion::unfused<F>::call_const_0_result type;
    };
    template<class F>
    struct tr1_result_of< boost::fusion::unfused<F>() >
    {
        typedef typename boost::fusion::unfused<F>::call_0_result type;
    };
}

#define BOOST_FUSION_FUNCTIONAL_ADAPTER_UNFUSED_HPP_INCLUDED
#else // defined(BOOST_PP_IS_ITERATING)
////////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
////////////////////////////////////////////////////////////////////////////////
#define N BOOST_PP_ITERATION()

        template <class Self, BOOST_PP_ENUM_PARAMS(N,typename T)>
        struct result< Self const (BOOST_PP_ENUM_PARAMS(N,T)) >
            : boost::result_of< function_c(
                BOOST_PP_CAT(fusion::vector,N)< BOOST_PP_ENUM_BINARY_PARAMS(N,
                    typename detail::mref<T,>::type BOOST_PP_INTERCEPT) > & )>
        { };

        template <class Self, BOOST_PP_ENUM_PARAMS(N,typename T)>
        struct result< Self(BOOST_PP_ENUM_PARAMS(N,T)) >
            : boost::result_of< function(
                BOOST_PP_CAT(fusion::vector,N)< BOOST_PP_ENUM_BINARY_PARAMS(N,
                    typename detail::mref<T,>::type BOOST_PP_INTERCEPT) > & )>
        { };

        template <BOOST_PP_ENUM_PARAMS(N,typename T)>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename boost::result_of<function_c(BOOST_PP_CAT(fusion::vector,N)
            <BOOST_PP_ENUM_BINARY_PARAMS(N,T,& BOOST_PP_INTERCEPT)> & )>::type
        operator()(BOOST_PP_ENUM_BINARY_PARAMS(N,T,& a)) const
        {
            BOOST_PP_CAT(fusion::vector,N)<
                  BOOST_PP_ENUM_BINARY_PARAMS(N,T,& BOOST_PP_INTERCEPT) >
                arg(BOOST_PP_ENUM_PARAMS(N,a));
            return this->fnc_transformed(arg);
        }

        template <BOOST_PP_ENUM_PARAMS(N,typename T)>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename boost::result_of<function(BOOST_PP_CAT(fusion::vector,N)
            <BOOST_PP_ENUM_BINARY_PARAMS(N,T,& BOOST_PP_INTERCEPT)> & )>::type
        operator()(BOOST_PP_ENUM_BINARY_PARAMS(N,T,& a)) 
        {
            BOOST_PP_CAT(fusion::vector,N)<
                  BOOST_PP_ENUM_BINARY_PARAMS(N,T,& BOOST_PP_INTERCEPT) >
                arg(BOOST_PP_ENUM_PARAMS(N,a));
            return this->fnc_transformed(arg);
        }
#undef N
#endif // defined(BOOST_PP_IS_ITERATING)
#endif


/* unfused.hpp
sp6OGICdcBh2xgjsYl6vnC9xhc56y8l6K2NnrILdsCoGYzUcjI9IOddwPMf9S57j2vMMt7DPb0tlOBs8CJ0IYYQ0QiYhm3COYFjI99MJbRY6nuM6JsfkmByTY3JMjskxOSbH5Jgck2P6/5n+guf/sTHhD/78v4ahjPod7wAa84oZlLXyk+RQZVA9878l19L8mzpQXy35tx75l1O+Qm3+97H5llX/2fCo/HtQ/uXli+yWOCbmW4f6E/M6gnXWobyNab2OtHzrUH+i9n9obDX+gas8t/eTsQCaEsa60mb8SWl5LtS1c6+OHdSBB+z5Bnjeu7n1XNXnPeG23wieJ/GVJzgRyhHG8dszNvEN56VzY+JwNT7DfeIrpY1P+/xQ4ouQsQeGEcbzW8MpbXwMPHDfZ1/avPFc1SaubfIsvpc8i+9GmMgf0mzi4oV6Na7q94nL3RzX8Kh4slZVnuHWz82rMTY23MhjRHmOLe/XUwZqwcnzbWAd8s5tqLoezfaILJ4/zZP5w9X8aQ5NiI18oHTXfYjpPiPpjiFUI0QS0vh92Kd56Vb6csQkyevx9023vHNuebYqaZ6kPrdM1Wznt6Q/wL9kvM2dOE0pM3Pc4THxVuNthtwn3jDzeJtJmm8RyziZ0pcl/7v77phi1efBQ/6e/535WJsxDXLTJnmUZeI0efSX5+4+Ur6ehHTy6H7anEeyGBNvzzFBnmNrxk7wk3FRZYwUTdw5EndHqZNPEmYo29YmbpMx8qHErfnWOfModU1dSy8p7ftE7oqlUUlPlnV6YqPUFNkzRoY8t9ekKUAnTUHaNOmOi1Dfso01z/svSJoHynG9LyFB2X5f5qU5IjbKmGh3+Un/KM12SpM+BfsIVQm7CTOVc4c2DuUEZXeZSDz83fpb5Tp514xBMVKzve5IurZI3jMl72lfadKlntPsGzdBkzbbtGjKPad07oJDZTyhEJyt1N0z5rjjTH9gn5H9WdPXw2BJg1pfquuMQVHc/JvhIOdLy/HFPM9FM1aFto/Zin8Y1CmMBeuIc5W69I05TwnxSclcbEWFJqUaTfaVaRmgfL4vbf62//aLpeUb+829DTKvlHles5Z58yIumOf55c17/bx53hN58x6xzGuRNy/5O/O85nnzPvjWPK9Z3ryGlnlN8+ZNP2ee55s378xZ8zyfvHOXv7ksKZfImOSYhHipz5Y6pO1HwzlSO86yfOte/5vz2v2gZQUj20G+H6/+fanl75q6SZ8VdXIvSt3EmvgM23H9Zct2NI3L3XYj7lM3TTZ5GWtdNzVjurTX3Xe9zd/f76D2z1vzD/ZT0ref+V2vSJ3QnMOM3tbHaplnrucBlnm+1sdPmddU6rSmPFzLWsYOqihjB82nPIJ+zCuPyBSTXXVZczyX/Jr72mniTJM4Z0icU+XYZLgqcapHJfuPD3rH5ZsSR3VCaTl/ZxDHLnMcytV1dKxxeNJ9r6+VeErZbFsX87bUnidHlJN+CXI/GEgoX4ljoiZekzHRGKfU7fvGrT1WpY6IiRihvU6Q+PzlXqIdYSH59P7JOj5lV7p/XNp8GrV9gMvn/nCanOcmSXmmmePhOpOTnHph/wDXmtbnOoPN/lK8gHPdKUlbc6lP3oQ4V7xmlTaGZDcmx4yJ+gNp01wTSgn2k7h6SVxp1nElREb+kTKwjmezxNNd4uki8VzVxBNfqHO3Xjzu/F+ZQmQf6Sf3EEHXJR65f/gj13RyvNe9f5hVQX+bZVnHOz4qMeEByzGWecr0odynvC/3KS438uKJjcq9U/n73qcUr2Rg4veyb34s16Bhv+TlMc6YNEptI7F7G9p3DZpqcw0arjnOx0q6EqTdYSRhEeky/So=
*/