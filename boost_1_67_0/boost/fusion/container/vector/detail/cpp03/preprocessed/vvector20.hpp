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
Z9We14GmqT2Tao8BPV/6nLHRZ73py1LPLrPg61MLTgGdus9ZYHYOwMwCnn8jt7ZRm+MgivemfsSncfgBLEf657LFtxAVvI2oICBUKkZ0MAyHUKFFAOFXFkFrOwdkcNjvspmg4zsbyA88mhp/epLJaos20ucZiN9IhEz77cT0Xf3MEO3qOQAivnHtD+US/fUPZe3yqocuR/Fz7UFnynKTk2ZpvyqzVBzOdNE4yDaeM12SGhO1ooQV3bePbssLGN1XUGsFeA/svBpzam/GzcijNQzlM7+MZWRMEg0MdypSFlL9pf2xFWpzDQ8zS6abymwrYiWyosBckHIaWQRt7qdNYwGqDdHCT8YCYRcJCHKI+GRgg7U3t5kFgdlGV4AKKnimO9uqAPNfdMPV2SfHyTApMLtlmByMr8aU07XInMxlMjvGVkk837QwQ77pdIeRb1pE8dUG52xiINVcFjSSRzfLPPu0TNmnnTz7tMyzTx/ssLJPy4m3WUQOabs60N4v8DoC1MlYofEEL0F6CDVDmZoC5q0GhvRe49E0u2eYWM9oKlYWNnORy5iLHD0rMBm5rL3/a/RSd04/6+rXURZy55Qs5JwFzbK/XTGf+j/el5NPHS1RyEgWMRtxl6EgHvUewJHYtHTyZN8rv5Rl32u5b6p9r+GGHGf3XH1vlbHnu931qUCZgv4wfB08bwFcb3O7tXnbDbuX94884JF6FykgdgjIt7qSaRmK1XhPxwPoP8ZWo5dXvbfe3RCvROcu+AFghkCqfeecrvNl/Bkso+Pz/8jxCBbPB02UAbuw1Ht94kcgdOJ6OXC9Any9iuMuk165FG37Vj7FISj9e8CBUu/7cVTJ1bOiIEg9L2mPXCI51xkyjDBFMOQdgnc4fs0hXO87tprrfSnx+4h209aMNbkqV+lagTG0aLOja+zkDIV4WQGjLdU+e38GLysQLysJ3bYlcox4bDbp5vuOx6+JsNs9p0IhzwCwbn4QYE+ib0nWe+RqeBm8NobvYQeTo40ZC0oDAuuGdBFPSs+dMqz6pXg/u5KEdTEUJPkb4UhW56sRBPxGdOiJfgrn2pihibntkzfIDeS8vAFFGFZXCQ0JbqjeALWX8NpD/KdnQBONB1nyTYRqAtSjDzT37TOconMdNU34peESvPMqcqY4lk6OOnHSpdEuG7to3p8vQEnZ8eR8NrgS09XuuS1+d1IrSE64d653/GDvE8+TzucQ/KEYbSPXP0X3xFxPUfazBbctgDrxWUmtOFH2FC4iNCsD750cFg2ZmaWRODhx+S+KiWWAwLCCfjLBsmZJxUVFo0Gj2zVyXfLivPgDyYuz43/ZJYLQTTYD7lJkmHJEwy1XhtPycXS/HyhAlcmIiKTcxrsXaRVoucrN+Te6y2BXS3BwLCSn4m50y8YjAMVBa4DfP26TX4LPD+Hzbfj8/jjqI+0FBQWCYEcVhVBYaIOfdruQ889u7pdnYAWamB2HB4yNMzaNXGZhQ6Zs3rT9Esy7uny/8u+nlLWfIkrAu92uKHvHYB+KaNG6Cjxn8Ivhf1GWuQcPRNvx5GCH6sBXuTtesjPs+MGhvSdwxw9vO3HlHXfzHS8KB5Np3NAyJkdh06EbNNi3ch/QDtzPeAdu7WegKF8R0pSaYwKmPIg6ADjq1yQHLilweBzB+zsBEZ6UoEsUAM2CMDUdRPtD/GZYjRXhLnvyeT30FN5WCrL1TkV/OatbtV3M+sX0//WCTR6Ez7fhcwQ+v35hpr3N9lcQjS3IYKBkGiF3uwXUUcggO7Hh/jn5PF7hvOi+cdrlAToqpCz2QORECPW2SsTya9izidKfE1cjWVwNukZZvezFMVC0MnwZnxtBL0m9ZAXGIbScvnL8L8Qou4jRM6qRDjjxvsXHuAfxi9ov0Un9Re2x94ncc9XLXWw+ypEhthgmXYp3s2OALdZM8fLXDTn+LrnnYYUxyde0N7HVMfSYeB6v39nJW2AlbBwasUphzitozq06KSRdnGPQS2ruIOUonj0KKj4nkAwA6jfiD5AScLEMj4Qy+Lj7gVnD47FsGFq0a9+6j5qrQRRxt2CoOCv2Hm+0Ab4aURNBJpod1ba2mYpPN2eMw9YDNJ1XTbUVMyTfFbnnnNtaeKDfcAyRn/czeLCYngF6ST0Fd+xeYpwrAl7yukbGOw8ltThndGcScjrKR/Bh/Z+6Ev95ETqVDK+OMvQT0YbRkawYenUzMQLbew06uwJhwlPXxt083OT3ejLXL494vBwV2Z/Xv39K/zACwqk/q/8LN2RZWrfmeD9vgV85ALnf3S1aVqDvufvRmf+H7oP45zzzoS0IWDTvUGIOcQHnH4VBoFMVHSiloXA4DKOsUB93f1nEwSEXFuRvTBNsNMJNsEAbyulc4rESye8aij/kGQgHO2BkdI1szycM18qVElb5seS5EIF/0KI7BEPtp/ikT9PVAhhFlf7qykIYUDzMbpOhPNdXADZ4TqFFr0PdUB+HJXUFQ379Z/ilywjhiA466IqgpA5Sm8FIKKu5xA/ZNnIXKzX4lMpQl92iyvexOxE1EMS5hzf7idb/IRkGiXdzoTFERFvHHz4gTKvAG2TougZzFPlJne2Ll6+T+NcQ4YOWZaM0zetONeOjVw4aH8Rs40MbWR9Esj4c34ju1Q9ku8Qjv35jFn2qnEKf6k0YVXe7y7SPX0Aa5TmDJjC0LROVcpluddoXMA33ZndjPiMhseRAcxS7tuKT3EQI67qBeFykcO5gONTCzXoAG6WFHC6sZdRW/5Hz2GSLDRl0r969wSR1E0h7jE5XoIAMndZip+jyqBRoQ1vIjusKIqWrJRAKR40OjXaQ1JHZEmFO+8NFDHqKFG/7RpPA1XBTzyeNB7AkBmlEexN/59s4xS5UZT1A7qwxr6dgfS55rMmQsT/tfIyQ+z6iDt2nmnYuDmF7gzdm0YPyHHrgnk4ParLpQSMSgm+5FfxzEYjBbneVen0U8L0BnmiV7+NVbnclbVjG66Ilg/KVdsf+SruJ7vXuj3tOhRV0ZKrXvhSh3S4DLA9jLFyDdDSGwornLTr9BDwVkBAQWjr2v84t+y7PcV+H2rgBPVvKDABAV4Fy9GpNGX5FbkC3BkLDp2Nk33PTGYgK4U+8bwhvdCjyYgUaxuwhVMMFhZ7hRT3Wz3Yr7X+cnpn9et+Nz4tovghXm3EXUwSKeYpWaT0sx65ogqg0QdeDYAu6fjfas+dGF3qNg5yQPg1IXDMdr90cr9/ZgHhdxfFav7kMAFK/uZT+d9H/Tvpfpv8l+l+E/0ke6hx/AdoH1nhDZT6WiF7rJZvJrz9x7dfGXiBPiwUwsI14A28WPsgKmIj3J5ukvuOGwY0cG3wiiNqGHzu6AWafTxgvMHcIqInFuwMgqZse/1Z0QyO+YAItlHO4hRLvoWL4Ya2xQFa0T/sNj7m4E7stynRLBTmWHC0wK5rtiSiLGf0XxZIT9p2zyJw3PaAdlo+yHjG1EysYy1KiF3FjjZ29pJ9qp84EW6aZLJ/FPP1BuR3F0C2W4aF3s7rN29+d0F9gkjVIqZ2TXTb07V7EVpVSNGA4Ly7E56H8uEpKNQuoLbuK8Uid34Dli2gf85nLV0I3MUUlOTgZ1D5ySdf5QlNoyVBE0eLmo+n34/H+7IQ9cRuFeI4vS66wxV2ou17AQivSdeV06cVGkSclmwEkko2cPptEta4c3cpqjLdotM7thLdPFm0LvprECHvQSSBBVm56iJrBKOuWWC2IybdejN76nBIE7rzkGKrMaEVMew3uB2t2Asxm18dJzIovxFu+89E2ym3a+Aq57kkKkOJEthUw4RzdkKaXZnt+J4bMMNsTbNGuUSg4Rgo/5826fklXukajhg5SLxknuZQp9exFtdeJF2kR9SdwrEYZYxP5/CMwopvRSrZLtsWzRq3WyTkQD/PAseA+/NxyhvfLVnvWeJO95bbs4SZ7oeExjAScKDZ6xuE1oLkQmHIzONP0gM/G+EAaBOAJAgRq107ym71NsESoofY7Vb8Lk9X5y9VImdrsJvSWM/FZw6xNwjFh+PV9H6DlKbEs2oXgP05BLBJSe4wb27GautNF78a4C9g5vJ8ts1BjNBiOsGOAjbHWLHOeEU8eW+H0ox1fmisQL0r2OkFIjBkB5dHE7pMcT8IYSyaBRkU6x35ukxVkP0ZR+qZNhtLzKTA9loY1qsU1wlsX7qiBmWVddhQLqYSx3taQk93Q4bUUj1lOTuxOLEpeHAVM8Dn3NcCpY+fbBA23OENBBepoUCdruXi8c7EgO9454jOSDECIxe2cSPIw3883W2G+A2VKKjWJkcq0363F8OQTH1LAcHykaNG1yJd2B1gKH+Nlgy4gnbjjarNgwI8Blmk/8Rtp2wY7/pAwiweLummhQtozaxHQMHC75ycxbW3z9IDieek5BlYmgh7lBFv7Sq3pCL2scwKfa/utJ3PbM/Q8h+a3G0R/GnyiHU3EwOP545Ui3OXCB0CkjKuaLibd2oV4GY0urF261xzF/Jha3EoDMcAGbc6pJmcw7eNu9IqIl1NAvk+UqMWwv7C+a2OtGdBJ9jgBfHqW8GMEQcjnjLXyHnmTDQKHp4JoGMBJ9Tnx0gu1iiXbOVCg/1+PZItL+iznT5Aq4XLr8zLf88zXo1ev3PvdArn3ZpioGHlG+S4SI7SHsuaJYFg/GUgOO71UZPdvsacs/WtyJTZt2yMlV+IpbksUegaGCDuHss8DzRZvaUhsRtAHIO6EY6zTdgLZhwkjW0Z6Fv7G9IN6yVY65eJzvibDo/+JJbrs6p2IgFoTXXYRYsbpLKEFv5o/sx5Np0e0ebRlEX47W/N93Ny4UgKoiOaxnszJwFOYLcNZey5E+8703vBs/XfJNsyiQjCkFVgVnP5k2ul9d/e59tajC+wCr9olaas3ZW7wwOmMxDB1AXMtCmuBePSa7A3PcSmrlQAbUjsHCQ7N89EXCgC5NQPJxnmdvGRPzNL+7j4KOo6kNhLUvpjvSDboDeKwxT4shvEswNFcD6OJaF9aZ9gjYvnxAZpHlEj5nAqtYQAJLPbTlz3Yub8BU6Hws6uCK2o2ARgC5b0mgnG1O/9zDY8aAQC/ayG+yShpODTzINVmhGrSu5JHhFkOMORC93EVT5/2XHpHm1m1Bjett8bkVz7KMPx3/BokowNSUNE++0eTZ8GDBx58ynzQ6aa6q6bXbcG6IUW7+48ZfgfNJ9pyq+4xApYis26ivzNOrY17zdaW8NZ+TK3JUPn8uNmatVV3me2Z8WFuvFz8FJ79xl+jGG4y2q/WUHgdHq3ZkTnYiRRjwk8zv/Z4TjzHWP54Rnn4KRYsRXt6GdnT3WRPL1cbpDwUhONXVn2J1xdVojdS/njQDcut+eYNhgVMS29FFKNdcxtpmxUw5gyIX4Vo/gRS6JeytR9RNSYZN6QG8rpaZPVfftPl+29Dl8ElNKN8TVnjk/j4MKWCMcD4XPRjMC/t+qWoWnjZQRnxsW/KUsGIMy2Jv0JRfWOGuVSn2F1iop75x5niSjWPQ3+n1bZRoFS30bPSKD0kHrzbZQP4Jgu6EzDtdN+Z7jtY22jA+8Hun2LTLWMhoEb8Kv9MowUWsGksaJg4h2bwe+Dz6b/yfHpEtrMioibMLSYOSA041fWu5B7RXM7ErXhdyRnlY961LDJz95IN6hXEP8Gi42yVK7V+XD/puaD6RgF3+gZ6a017Lr4tjdBrWJlbaGWuNZjG0iDIrkHkGpFudXtYYswP1b2J0d1pPLnSAeS0LrNExIEoxhjzZlgi/uJico8L2e2FBQIe/rCwARf5XtL5SNdCuucBj3ZLEVvvXtIscBpI68vqGnJQ+Pzfr7bZTlwNPyWsQb6p8W6Tcl3POSztHuvJPLUol5cCOa9iTNfbs04VHq8/OYDiCYqveeL5E++eIgFmM2nmgJlaQFIpSanI3JDFk6pa8peEch9IPuiPAUMvEAw5zC9ghIQm6daT3ud3zDHlY9FWOKj6hYwcN6X/THtoQPXL+MOln0o1g+QhGqZszVZniVVXsX5OWj/prqnr9/6dl1u/0bfzr598xfWTr3b9AN+OZuPb5pmC0fXIuDJtTjXxmNpzRG173OJyz58xIlvwK11ev2TswfnniOgCQUQh5XHOPaV9T3Ba7NiPkb1GSpIf2Hf8jgTk83SBNfEY6zmSavqG1vsRPKiEVIMdBAdsf0Eq8Q00eldlBQJO3NvVoJeUAxehFhsnF2Dm7UnfEUH3PcEmnroGCr77dc8FaFFNjJJb5Ll12pvLbTbvLxJ/PeIwKmGHP1mOHNHjeKWVNT2hip4BGOXhgXwh235YZ+aQmn4+adnr2ZhZz9zllGA5YQkBCkdCuYtXTIs3UmPvFXBUO5ebq1tblWr5BgZrWRuyVuC900txau/9wjy2RSyeSz34kGfXTROgLHg3odoYheqX8jJ0fH43ua+C33AqRvhF7cE64hBTzVUUSLrz5hwu47WRy3AZJr823oBc0ot3zMivDY1M4df+zXzQ+T3isP76jrz8GnJYj4xM4dd2jExjuaz28/A/IKuV85sHMJbcnCi578V870loIvO3Uo6pMNgECE/6LpkpFSTHpUkFgXyVxJQyuqhOON2sxlwWL7MID8CQWzHfgvDdIrG5oZRfQsMjCGH09HakAZVhIgHwe9cqTMHhhE5HFu+S9+lolIuL+3RExcSsZz8KQIjD4uPwu/Jwi9bosvPrSCjwskI4qFgDNP6y57h30HGw2043WkNSBCBFUZsm1aZxtWki1TQZ7LKH+V3GuylC3mTfccf+eykjErJo8xXtZzfwKLAfpfciakvLWdtkEPWlwPcXs5dATpgDI9VP0T0lWKiwIS4HUajn5yPxVFDVHeb14IxeS5rFcCogoSsNuiHh0yrgGtpEWqmX+KNd9+Ws1CVjpS7xlXqGVqoYVwobDuSuVMDFxf5dNyR7Jmy7lxq1F/La8bn7LmH1eKGamMB1801C7XmK9s6NVlBxoN73wFbXSqmm8WCqZTKEC4a30fa/RM70Ezb0sJ0oxlH4JmLtBrPwDD4Y+TYe/2bERb4/XMVzMdP69exF7fYyXOOEkw4e9pL2yQ/x6DGjJoYpmuQ4tqj6JkbmmPxQQnL8YP1y72BiPuzt2sqUb1KBHR+RWRTgsRLWFfeXsyTVMDUlAkuqvYIWzjHMd2asESyOZ+ZlGYdJ1UKvyYmC3Y8y33irOaxW1NHkUDSOb0pysEqzw/p5jsMi/e3gmpsGM/wlzi/VgjcUyTvGDRvcBITe21waA1LfcLMIvWbrt69C3rgsvw+MZY9si/+KWFZnhmVN7slw/WUGY3pUwC3MxxcGSknVt3zvniW2hFXcPVNxZFPLw8Sm4vfT8A343/lsVQVNN3j+2zYu+4fKECmAOY4vZ4FxvEeyHpn+MwDkHxhA/gEB+e6ncTtGEnjjIpARUYDzxWruINUjyeBOpFT4sDLrYVmGs52B8+WNkvBuDiQdIL8GFOcttnhohkiil7MfYSgqdBWcn2tGOjqbtnqKPvG/QL4zd1qavtMfSaaBymvjy2y2yOUkO/aCtrfUKkMjzVdsJvlbVmfU1+UtP54cHAcKWEaZFUzjFdQmTXZWM6yuMkd+yEpdZvyezk9HaT3QC8iQ1CJqoNRwPp7KgXP8fMNXijDUIqsNcdbkVJVu1uJSG3arh9Cv443H9pMBou25UmRXalekvojpdUPsixidOqSfzOJaTP4GTjE3XmQD0CeNp+gNlKLqV+SCgoDKsgX70thAtHMrMgwAJJx4tMcy5IP8oymZL0CTG6HJxWnbXfypRfPpF8HKw4/z0tdk3j1uvMuKG5s7f6VzwxpUlHXZOn/cgPZT1JGZ/Hpy1JVR1oeRlHsGaIlfSzWNcoU3iq2+MdU3DkQTjyVnMKq2afqpZM84nRTjdu7H2SBFovrLMPx7GJLvUE3KN6oEebSJ7uXwrBivVNjw/hg8KCFXcW4LeOYuyxZQZCIWTY772RUypSGC7RDu040xysbUMhpii0KGBmEhMCMOYE66bCFTQP8feVtrmsRwO5i4NXDXFA4W1+MpWmu8nOFk+/guhAB2SDXIWojIl2IGO5lbbnNYdqpP+wEYMdug/GwfPsH7hlTZhZUNkEruwttKVHII3lBIWwpEZ+qz+WCgyBwqss+ECicvNVzntjGVAOi4VcgeZA0u/WVshONbBn7z9FeT09/097XZ73F+WMScnMv2hs+FC4VleXzrqWtVj9N15ei7Wq+C3yeozsRlzgPuhkiAKhAtdmeWSGDXWpbkiATDv5xJJDDlAUJR7ZnlBk8POBO/haz2TfIsXF0QAL77yykSwZFfZth8tEEfeXc6S39V5z1aSK6k3uvPqB8xmeDHLY3Uikg+5ObqqejMZxwiGtBE1c7uQh5eiOgno1dWV17leUYZuWfmX5C4BPoV1WecZ2idFFi7EDFl0JfVnQKpVheyVSLKGi3SgSY51L9evNyJb9HTx6fT02v50yvSzEx+b8veJtrCRPIfpiQ6yorUo/iFyxdVdu4+n2qSgp31qJGh3v4bSk9iKiKHuioBAzCz3wQ9MrhT3aFi/zDwdDtnh9N+uZKugzhVf6XqdyExrSFamhCSzS4B1Y7uKKkn8HcBELpgKXVGv+1QvtaZai4P4i0rKtddvK/ZhbYspIlVqUhVKFNdpMAGqQhFNcCmKvBGr78Ue4UpvKz6ay74XWJ8CfsKTdpfhXxdZuKJ2bFWTFmOUPRoHEsEV6Qexi/KsP8g5t3wH2K19eiYw4Nx2zqR2esqxFhNNjwiW9s5UBn2QYt9IOO3E03iFLFV770BBQU4OUD6lA7gOeAKhtfTGIp0eL/nHAXkknPkRTLlNBzCIBsYz08/6Tnj0eEAw4j+/TYu8a2h16W0JvEd6LvygATMe6plHH2mYfnuh8PNnghhqisXikj86SoSMlItEyEiGQqzr+aWoizRo/tuzJ8MP4kVHjN+4Ds0k10b8PaMgfSKqXq4NsjSV7ebKWtz+Y2owf9xZIkMP4Jh+e3ZDM80/iTKep1GPLc7BqL9D2ONfr9reh3Ov2Gsgps/fFbfM4vvQlmGP6Ojy3OqP+j2PmceMP1f/JqBS67ss8FoDx0d3kn2Vtii8SbmL0fdV0qRRgo8p3Ddl7AdFezjwHOwH0+5ibtJUjdKbJPM1jhDIO2pG+WI2uA=
*/