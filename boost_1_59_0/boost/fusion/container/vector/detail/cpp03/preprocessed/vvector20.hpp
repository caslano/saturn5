/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion
{
    struct void_;
    struct fusion_sequence_tag;
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
    struct vector
        : sequence_base<vector<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19> >
    {
    private:
        typedef typename detail::vector_n_chooser<
            T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19>::type
        vector_n;
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
        friend struct vector;
    public:
        typedef typename vector_n::types types;
        typedef typename vector_n::fusion_tag fusion_tag;
        typedef typename vector_n::tag tag;
        typedef typename vector_n::size size;
        typedef typename vector_n::category category;
        typedef typename vector_n::is_view is_view;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector()
            : vec() {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector(vector<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19> const& rhs)
            : vec(rhs.vec) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector(vector const& rhs)
            : vec(rhs.vec) {}
        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        vector(Sequence const& rhs,
            typename enable_if<traits::is_sequence<Sequence>, detail::enabler_>::type = detail::enabler)
            : vec(BOOST_FUSION_VECTOR_COPY_INIT()) {}
        
        
        
        
        
        
        
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    explicit
    vector(typename detail::call_param<T0 >::type arg0)
        : vec(arg0) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    explicit
    vector(U0 && arg0
        , typename boost::disable_if_c<boost::is_same<vector, typename boost::remove_cv_ref<U0>::type>::value, detail::enabler_>::type = detail::enabler
        )
        : vec(std::forward<U0>( arg0)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1)
        : vec(arg0 , arg1) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2)
        : vec(arg0 , arg1 , arg2) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1 , typename U2>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1 , U2 && arg2
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3)
        : vec(arg0 , arg1 , arg2 , arg3) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1 , typename U2 , typename U3>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4)
        : vec(arg0 , arg1 , arg2 , arg3 , arg4) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5)
        : vec(arg0 , arg1 , arg2 , arg3 , arg4 , arg5) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6)
        : vec(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7)
        : vec(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8)
        : vec(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9)
        : vec(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10)
        : vec(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11)
        : vec(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10) , std::forward<U11>( arg11)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12)
        : vec(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10) , std::forward<U11>( arg11) , std::forward<U12>( arg12)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13)
        : vec(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10) , std::forward<U11>( arg11) , std::forward<U12>( arg12) , std::forward<U13>( arg13)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14)
        : vec(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13 , U14 && arg14
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10) , std::forward<U11>( arg11) , std::forward<U12>( arg12) , std::forward<U13>( arg13) , std::forward<U14>( arg14)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15)
        : vec(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13 , U14 && arg14 , U15 && arg15
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10) , std::forward<U11>( arg11) , std::forward<U12>( arg12) , std::forward<U13>( arg13) , std::forward<U14>( arg14) , std::forward<U15>( arg15)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16)
        : vec(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13 , U14 && arg14 , U15 && arg15 , U16 && arg16
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10) , std::forward<U11>( arg11) , std::forward<U12>( arg12) , std::forward<U13>( arg13) , std::forward<U14>( arg14) , std::forward<U15>( arg15) , std::forward<U16>( arg16)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17)
        : vec(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13 , U14 && arg14 , U15 && arg15 , U16 && arg16 , U17 && arg17
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10) , std::forward<U11>( arg11) , std::forward<U12>( arg12) , std::forward<U13>( arg13) , std::forward<U14>( arg14) , std::forward<U15>( arg15) , std::forward<U16>( arg16) , std::forward<U17>( arg17)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18)
        : vec(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13 , U14 && arg14 , U15 && arg15 , U16 && arg16 , U17 && arg17 , U18 && arg18
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10) , std::forward<U11>( arg11) , std::forward<U12>( arg12) , std::forward<U13>( arg13) , std::forward<U14>( arg14) , std::forward<U15>( arg15) , std::forward<U16>( arg16) , std::forward<U17>( arg17) , std::forward<U18>( arg18)) {}
# endif
    
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18 , typename detail::call_param<T19 >::type arg19)
        : vec(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
    
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    vector(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13 , U14 && arg14 , U15 && arg15 , U16 && arg16 , U17 && arg17 , U18 && arg18 , U19 && arg19
        )
        : vec(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10) , std::forward<U11>( arg11) , std::forward<U12>( arg12) , std::forward<U13>( arg13) , std::forward<U14>( arg14) , std::forward<U15>( arg15) , std::forward<U16>( arg16) , std::forward<U17>( arg17) , std::forward<U18>( arg18) , std::forward<U19>( arg19)) {}
# endif
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector&
        operator=(vector<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19> const& rhs)
        {
            vec = rhs.vec;
            return *this;
        }
        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector&
        operator=(T const& rhs)
        {
            vec = rhs;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector&
        operator=(vector const& rhs)
        {
            vec = rhs.vec;
            return *this;
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector(vector&& rhs)
            : vec(std::forward<vector_n>(rhs.vec)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector&
        operator=(vector&& rhs)
        {
            vec = std::forward<vector_n>(rhs.vec);
            return *this;
        }
        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if_c<
            boost::is_same<vector, typename boost::remove_cv_ref<T>::type>::value
          , vector&
        >::type
        operator=(T&& rhs)
        {
            vec = std::forward<T>( rhs);
            return *this;
        }
# endif
        template <int N>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<
            typename mpl::at_c<types, N>::type
        >::type
        at_impl(mpl::int_<N> index)
        {
            return vec.at_impl(index);
        }
        template <int N>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<
            typename add_const<
                typename mpl::at_c<types, N>::type
            >::type
        >::type
        at_impl(mpl::int_<N> index) const
        {
            return vec.at_impl(index);
        }
        template <typename I>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<
            typename mpl::at<types, I>::type
        >::type
        at_impl(I )
        {
            return vec.at_impl(mpl::int_<I::value>());
        }
        template<typename I>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<
            typename add_const<
                typename mpl::at<types, I>::type
            >::type
        >::type
        at_impl(I ) const
        {
            return vec.at_impl(mpl::int_<I::value>());
        }
    private:
        BOOST_FUSION_VECTOR_CTOR_HELPER()
        vector_n vec;
    };
}}

/* vvector20.hpp
kPZr46sEIigeZesI3IDjifb764XdTe0h4lSwTMUAA5RuVaD+MBJCOLD0AAZgBzOHlXhGDqy9/k3B6RHkdLIi6ZAqh7eKkWbYF0HgTChMUNNm8KRXWIRmJI8wHsIvcvP11fCKJLfnNtHX5mNHWIYVDUqTTwiL25EPq3Mi9AKh2lfWTQBw/EDAz5rh95sSPXEg5ceeuqdKA7BP7Q4FHqFbDIFHMKhsLzB5RQAhhGYthCjQVpzDLK4zwyjBDH9eRLv4EJisH5xTUrDJleeLuDSUk+aWODuwQmNanzSM3mst6n8pj4XM6ycYRnTGDYbuu0mHRNl0mFTiG92IJzRnEA/9S+R+HnFg3ohu3X9xD3tFdWhfOq34OIu7NJfz5pP7zHFsjheqcfaG9vCOjkjhDXEYlxpQaqnegDfo+IR+Jp3tWBTgce1zZeVzB2NfdDKzR40WGp3fo+cXVP7JKAAYwXQsF9tMnqBJe9FzQva086iPetFj+XTMt7+/oPajLfnU4Lz15tfO+u/jtbfdVHFrWIPHZeHRvOWcRVQxWnfxnIEmBXs9FpsIF2ZVza+nfyLJouGgNjVhfWU1ctB5VU138hN9qOkJdHTZDAjZIRhCjQBNuMXRItH/p14IDVg3NOnYpU0LcD+NIXf+Kmmyf3iMOsVq8FvTe7+gzWv6aIA2bqI+cuiAaC7EggOs/MjMoXlha7CGXg1vzcwHAa9aE5z0iWLWoKUaMFq+mSWWnJ8di5w8MNLpjKExHPHgmBhpuWxuDBE6tdUhhvlh7n2wn+M9zxQ+xaAZBnlUMOqLZOwBSa9PK8Az5CjZSKce2y045uZhzDjQckfGHj5a8BMI+AIDc6rGgleo6JGlDPekE2wayXGnWAPNEgk6wxh4qFMsCODzwmIBYCuwQwjP65s3EGs/fcb58pynANxw1i5+NXDH8BhIGqIB2OYu89Hk+oBa4VA0gPfRzUbfxGGSTWYb8Xyej+BHXmgFQoW3BG4P3fB0dw9R4l/TbtX75gO2izMlscNY+dRza2urNMEdyUqa01tyG7i29kY3yZmw79CQ9gvV48I+guxnAvMpu0HUDAnvK0ndT0qacSD4i4o9GmplCRj6UU8phNDGCCPDCax5btJk7akjgUUHZf5GWroTsxq+yaa/qhw6HlTkMVqRya06RyDatgAl3Gn9nJfuLcnmX1d8AMcfwN0D+ZpoJq6R/OToqmtS5IqDgQMhhTdjil5wBTSu03T+W+sfEcR4Aj7ve3yWoAZBAuyawuX+qajwU7rXgop3p1TYUjeWJeFbQR60JDjgv+7tmyVF6bm855ZSnAmsTAlBFSGqjJMMBnGFJhTSEkghhUhsvRujF14xxPaODSHm4I4Jrz6ptPJRhIWk4Xn36I2Pmqg9jn980XGuTyr9+uPtbdnb2yzNpVhT2b3EMJNpTeLzZzHrAT0Y/o5eaYr79/IRtyLqr8Mcf7JGFFALiR/vD5ZNTJ/I2t18vVVnUpSiYJPeRT6tI+rStsDNOuNohBiXXJEdHXIqmiVn521G2wd32UDAfxf32Y8zfo0EHhJG9NhXPB1sOCQN1cF8agpMkOxCwCBkeuRNQNuv9VDEG5bHo4pjgNbRUjFMZ5LQlT0YsKFTXNgnTqnLMOhHmAef7EOKOXLFurWRikicrshJDevAMDu5p+pATmrhbv9Qamahi0JtYalk9YFlrC0xae/HNLJOGp2md1N7tzYlIga9vIg+zzQP2GSv//sYOdF0CNt8JTt0Y+DXxccwqVFTq5CdNtUfOUSZ3v7GUL4MLKmrxSK3DY6+V3mM7DIV40jqvymXj1IOI6TApE9ePPoHY8kwqpWtbe0GWDi7dDSldJP/x8l5LZ9pMCGXDEb8KcULlZOJm9CHy7ys0kKoKhw2VZz27vgKPVc20+yieNcxvltQaaV4Z17kHSB22lUwvRGDGGb4qyBCzBe1UWcXLH9ecQpT4TBo31QfdjmzMqmVhBqppZdLqitJV5/u8CB6cuSjEaI23QynlU6F1eB4BA9ISrL/Wfw1GtNbUra0EaMYnKcw0wOOsW/a+pxHdu8OdD9REztdGiB7GAGZYa91rC4ZSOcRBWymFyG6FwFmCEG9QDOQPcXqjJzadeyIdJsEpuEoxFL8aL8W6xrUBAd0y3hUo/0WvzyIRuATkbeEnxO95u/X0kP5g1e9CN8I1ey467HV+uNDlpx89HUiA7keg5R8IdeuKt1tKPeZLPqjQHYmL/lBOTgLMliygHvGdVVS3Lqc5JFgdT5is2LdHSsseoAfbXZEBemDjq9CV23lfA5dTms0zTBMfm4944GKRiG5IqhvkfXEyCDvgcFBdeSMXhKPDBucpumTbI5Basc5pcfHfuV3/PEl2HgcPF6ihUdrM1bQ5yUM6aR0vEBqc+t6eKvTUgmztLNl4oNWi61ISbIyLnjT2DNzVSjdCmgFSvf4sxkvFjhAltWdXl7PSoyBWYlEB1t9HTIRYbNlepGqOgwAp4dEgMvFp+WB+n1rB14K7AzeKP/p6Q+yV3E1k27g7a5xogxAT9oQN41Sbkf0SFfucNezqfnd5+VXwMkaDLnturjACX5HkkIP60wUAf+JelE82zXTWoPfIZ2aik3PHzza4NCbg4Gh27hYuNSBQGAh638I7uh5oPYMJEt3+tSHCRtF4ty4RdPuJtzIAUSNdylh9JwdS2Y4Id5bJ6soW5x8wqwsRxpDEg0q3YjEfclg9bk34z9aZ04+HLJTvpraqmVZ/KwVE+icgs8qNKQn022aBR/0QQ63H0ZaLH2Xl7AwC6xEkuC72n/cBl2IcjGydYMrx+4lW7nQ77iQ/duh3SScs6eCmlM1RC6x0sgNgXwOEcUV7SDrXFKwpYOMdxWKse6CD3Qt9H7ercxi3Ji4rbA78gon7DpuvhBzqns3Bs/Tl2B77E5pkvUkXTOzXYnWAaPd+kluqMbZb3DBNs6+0yvjRAqYQmIIHJd1966YJwxR5AMbCC1KPESIlkaZ5g/G3FvcdViDkRRXjCXkMVK8h7yK4zlzuDB1dRh3jY9/AGFhzo3e+f47lqLKG0IvUbnZLoHOWhHzFUi4UqF2Pi9Y5Wr2HFjRiEqu2KC9mDyTKdC7iXFcr7+gmNo86ZEIVtb74N7JyedkquBgAKNOBDybdjZlX0FvsfmUvHWLFRnyr2bzMd/J5geJrgK66fcLF9K790vHy6bnNM/L5hW1WfptWboNBvX3pb7Lx4CqQTdW4T2G17Ndjpg09mqSJBDT3KCqgP10vGF+3X2Kp92DlmltxR9rATaEv+RFNYlTh24dVbUWaMzrDsivaoY1eopXKHKvXJA3NQMsMse8hxbgFPsUE1HPxseInAGjhUR/NkdlaYN9bYJ2ql7tsD5LdgdobjOj4R5mieFi341mlKY33MqSRtw74N08zyDnSCriW1LLO3li3TqyNZNNDCr7vMtUiPlCeLmaLtaST7FPaYAuW6YV7rcZKXHMr95JeoWeeq9oHKoAXX5gQuhb2DAuyVTZCpkobfHGqvAIYkbvrq5B9i+7FeaBSVN0g6h3znAxvuNEuHv+2JIIqBGtoBGsrGjgeGioAa+soB7BFnzRnSEnqkI8X8uC5iyZZS3AFhH/szo7TpERBzi3qAsFiqFDQb1p/k58TRNqOeh9eLMKgQR/mZQontOhcMOdaUDJMDnrBLfljrxTuOiXFfaP18hpGYuNv0im70B7a7iO4+Hi6KATcMGDcludP9JIhjha5+QWgrD/dPvMYXn0rNTz4A5lem2Q7n1UNVy+zFePvxFa87uBMJo+4s8Y9QwZfwfj+sPhPiF4+BhC/7BxSLNif+xqNz7zJp72BlrX7IU99qmIVfjFUTNaKRQ7/exiCkHJ98F+KRzHJ75KcLC7h/m6JliA4zP26kDDXdRLx0K8T7QSfyz5bsequxzaoF5KXfu0Avd0YLX8tDSQ4WBPHXzfADeqDOu22dkXpVj2+Zqlxk1AUBgtuOxuS660/8Gw+Zc9F6c19Ua3zUcWNtGX+mz8XO/4AWsH31lwVSKfE69CHTUCxPbeC/3SgyJkWUgS4LbR07yvNWg8mYe8gMEtn/9Yf32A7J6QyvCVtt1LQh+w4k/LMescpgLLpGlPAN2ClhFhOFnP6bxbMBxOed6fMaRqeIfdltGWIJUMWM4gGob3a8aP48xNVyrXDO4L/7hydjcR+ukARB99iX+hsC4sQ2B/lTw6/kU1diOdACx/Itbf9QcvU8JLIYEteknS72g1dBZOb5+zTSPbVOmPPgXJIlCfU5Ih+KvdjY40cAeZQMCF6wGiau8lMFSSpZeMbcfKt4MywfX3F4elrCmal0cPnNdh8iIjoTwoSswpiq6nuJY4v0a3KXQ5rW+/2zms+185SFcLcEL9nOvrpxOspO3OKMlmB82JdfdrY8lciyB7MFg+5XZ6Vx/1c9oGewoeCxS39cSWrNy5BdPmzNU6WPji1XM+AcqtLsA3trQrsoCSmkFqYVHGSbGWrfXG1lJKrbRdE5znuUpSsWBpQsFM9j2Ps7SiTi85cr05kZS+AylM2+bAOOZCoMHAerWWjczucpREAo0Qqn28t8o3rPV9e6uHDZfC9GvBG5ZVFnV9pBzRT3aFahvpxlKhWtBihh1FnISTEw4y5QhxDDLpJKKFmzIX6ApXZCtxshAwdFqal+2LuQ1R1WoUZ1M+S82/UuGTEtO9tYrb7xapotJG/9NKBy8Np03A+5Cj89h6RU5mmlHw0M+99Bgn99RBblHzOUC/R/S3f5CIgkPbN9DP0mKCir1NdnFSyVhLXw4vP0guQlvRRjJE2FeSuN/H8hGH1OUKV1qVn9QKDJzaz7Q9rJ2qyE57WZfsz7FTXx1LDeGJIjxYPPN+sJ80Xq3xavX7bNRBfHdODbbpYHZahJwC0PePk5SqkKS/KJIMyPFSny1PBcv2QxzVRa54SU5bfO3CdeoVaSFI2GrCOc4Hv+tl5149pGm5VbtEpbXe0aZu3/Qmm/yW9BMyf/+5NKBXKxBNt5OW92Ou7zIW2mx8E1Xt7BqyDgmFsb/hCaJtMtzWBPVdTEMn4YYNMZ3dxR27hhY4SRe2ClYDv2gVQ4LwL3psKnJxcov/V1ldUirncUAYzefq+PvZb6Dl5iPloOgt/RPdBc2XuYiEiIuhWTT3NkrOicfwQOWRUx1ye4jQIEL41zCjTi/zhT5CN60Jh95BCjRJQsL3hWb/fdCJfjlOpWe7bHGBxZ1Qwt1SQ1Oge2DsmWYf/PSI817BgLSrfywoo4zSorulf1L+lHqvKbKM0IYpGDtkCMMdVCVjPsM/kZFLnwJi5sk828t8W41BhaK5yDvMUzcNbTLUvktu8AesOqDKcl1PA3bIfTfX4XWnJ9eYja5Er0Vro8qHX4Gvzn3WPBdGN3iv+1pq8YKvg2POWjhVzOQUdjFAbdO82Zt14vFtq0ROr77257jfoD7mL90HZlcUmslzshEu7cgoOQY6MOSVqZxzjvfZ4INKT3xSIs60wY6EJuUHJOJVYHLk10Sg10+S+yyf7exPmJGt6rMqehLqTTfM8KQ3YOJ7TN1eMWEP7JSMzOnWFTIcFuXO03pFTfe67yN/S80pDU710juVy34ycga2ECjbXL8jH7SGE1n6q2eXZxSObO3BqCM/fgi358EcBe4cqyp2Ld6IITCyRHd89R52A8uQVVQiE8Msm+EbSSdT4o8zOogvFQIpoVrtZY3T85K6FCkhYVVM9UxGxBhUx9+K0rJ7X9rld8MdL2o0WZ0zIEsEHT2K5HDuF/kiFdm2fOhALgPie9I0k1sCOB+qPdUQVzWCHm8+WlFju85JY82q2oe3zWxhqqCuVR3N8DD8Dqe7Yx41fSJo/C5LmzfydXYOda9wObP+CLMDPQEuS1bskW8daY76ZxP1NO/eBavBhT9HApH3dZ0HittW7UrUYuxnl4EFcRgDaphsAEldgQ40BTSdeQhPpnp1L1byZs7ssET5Cyjhwe4hyETIJn0y1aXzMaR355+jTxDe4h12RSjHDaAyMDbXY4hSIU4HGUr28G2RIOMOskeU2VTAwWEQQaNP49yWux6LJaUIkVW9rCB0ovKGqeG56rSUfkfrXW/j/ck++ael7BP3UNgAw305QEFJaFan70JrkvmO93pcGSrGjntglGFmr5TkzZIplyJ4Ks9Iya3BUsUfx4TOc+qXj8U9U5xQoM4JVIrEcYRaSIzl+4qyxu3T3j1/oHGuaXH1gdV21w0MrhbpJzhXn4K1tFkn69+snAjGhDTTjKHUav12RswB6aRIhs68lKT/0SzKqT1f7400qOfQHWgVkhMqaEyULO/2FWreQXKXQBiGjbJwNBtkEeoLxJlO1NTUGov7HJD6xgyElYsoAH9T3GZ6f3d6STj8rXqS+neTYFOFp7kSe1FgNWOjCYqzfN1cFdBjI+bLlBPW7kBhlY1H5BQXtQN9RTegOFj/Yl72ni/22nMEIVOCjDB8qJuw2XsUZ1nKTS58C+2wJPbJz8GTW+ABP4kFSYvRvnJmtGJnURyaxXHIpA0o8iA94k4WOcPF8xZvzalJHu6bHIw6ZF7yN3YTsdOPSsN5r8Ud1Tj/GGvtAiT7Enjb8owgdQC2GYbylH06cL6ftFTrZMdkQ0S7E757Vr8iDEfS36zCaiYEeHL4QUwpevCVEmfEv2pntzTnDKCSemdkSSocWy6J22C6EKrXBNYMMtSPso7Rd7MKrBrFTvrxNSRMO9LfxrkTZ5X4OV9ofo60+vIIpGuIrrIn6zJY9KuY84IEPFtup8IRJhDiZnuG0soYEDqBOzG0zsgxnnfD6hRkovTmnCGumWbb9yPasMsZ5e5by9sk2+Hu0VLC0NfTZHa79Y5s/LsxBVg7x4NHGytoOjTilDXQySvYxAKFgeB6KYGBZKKPB58itxaDUceNJJ8qiUUUt+dMO7sU40CK+GyLa8xVL5/PtpIX7wpr/mxbsW+jFPCscz5rOSwjRwDhhaJu/m5m6aqH6s+Sbz+mqJ2pxLyPGZCSV1/OwUqVOH7pFAw6CBGCXQucFb6y/t4PgewpjC1Rbf4pvzr++KfrGcQlsLxetEatBwgUTtxqW2IR1gW5HBqu1xRBeyFpbuV4GRf0eD/0apfH9HAVDsnKaw5OYQuI9ffVLTgYh2ib9HhlYCyWAbfpjM2hT02SJhu46vCZE5Z0ZqAscBfrrVHnPrAApWfoxZhZrFHg5dAD1PYUUdxyQS4BUfBBiP3Gtzp8yGyvoEVi5E5f9b5qCtUYYU0tvxd/wIFunlhd4qeh4Stf+3KjvCzJhPJS0dVx1YGH7bYeCbdqWmcfDFKnc/JBqWJHTVbMVHWtcL78bdZ8wlrGcvsbNamqjHyGucjoxCa1QmJjefJhoP82D7A9lmiE7fM7jMmR0E4jv5VjZWsx2kLvkuvdR8kts1xvws2h5Pst867eMZc7QOktc9wM2H2IFPBGrPpTis5rH3kJu8n5O9uA56p6wblNK9JgOEolLdaQvXIAe3V/0TeH11UO/nQhvfSannIGWcF25HyN1+GbyraXcOkFygQEJD/k/pLxHbSaFsQ+LkRk3z/oaJitEbeBG8EmgIQUUVYiWanscAeUnOBb7OC0A2ucI/TS47+pFXKi1j6LlZFzZ5Sotj6L
*/