/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion
{
    struct nil_;
    struct void_;
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    struct list
        : detail::list_to_cons<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9>::type
    {
    private:
        typedef
            detail::list_to_cons<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9>
        list_to_cons;
        typedef typename list_to_cons::type inherited_type;
    public:
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list()
            : inherited_type() {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list(list<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& rhs)
            : inherited_type(rhs) {}
        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        list(Sequence const& rhs
            , typename enable_if<traits::is_sequence<Sequence>, detail::enabler_>::type = detail::enabler)
            : inherited_type(rhs) {}
        
        
        
        
        
        
        
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    explicit
    list(typename detail::call_param<T0 >::type arg0)
        : inherited_type(list_to_cons::call(arg0))
    {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    list(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1)
        : inherited_type(list_to_cons::call(arg0 , arg1))
    {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    list(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2)
        : inherited_type(list_to_cons::call(arg0 , arg1 , arg2))
    {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    list(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3)
        : inherited_type(list_to_cons::call(arg0 , arg1 , arg2 , arg3))
    {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    list(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4)
        : inherited_type(list_to_cons::call(arg0 , arg1 , arg2 , arg3 , arg4))
    {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    list(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5)
        : inherited_type(list_to_cons::call(arg0 , arg1 , arg2 , arg3 , arg4 , arg5))
    {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    list(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6)
        : inherited_type(list_to_cons::call(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6))
    {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    list(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7)
        : inherited_type(list_to_cons::call(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7))
    {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    list(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8)
        : inherited_type(list_to_cons::call(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8))
    {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    list(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9)
        : inherited_type(list_to_cons::call(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9))
    {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list&
        operator=(list<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::enable_if<traits::is_sequence<Sequence>, list&>::type
        operator=(Sequence const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }
    };
}}

/* list10.hpp
OB8BPWyP3cEZrM+vjB/6HewH/sF6/QkeDf4FjgX/BieDKMg7QwI4G2wLloPQKeuzWTinAMdSXxuwC/Vdqnxjis/4fPa3t1F9Y4rt1pnttg/bbRDbbQz4HjgefF+Jd+IzOzhI8C2zb1jetxyv36nsqKPcRMG3rs5nnNwF4EHghWA6eBF4GLgIHAcuBll/PjvjmTpM/e08b7pA7+XUewX1XcnxdRV4JHgNOAVcotLbyPIGIDciq/WOVNvHuM3eoc/D81xk5bkjPK+B5/U3OG8l488aEKOy/qHksHFoRrFn8z1JQfvgfYryAnFnzSuT4449M4o7s65KDhV7FnYvvHpPUlwxZ7p4M02s2TqUjXizhO+DZxBXpsSTpa9KTnhMmWAPvIj3v/PVJEUUPybaA2/GquRW3Qcv3pixSOPFtuJ6SH0Y3wdDzkX2Ii9FXou8CbkZ2foI+g3ZjlyEvAi5AXkT8rZHzDgyM5nJTGYyk5l2mP+/pDgvEf5/yZd/kc3S8k4x3/+X/khCtiLfjgf33CmKb2vUOHv2mElYy8xx5OGl1TmOyuK5mOKG3/9fWr9sD57VX7NnvqJ7BXXvSd2dkJfjXK9Yd9UsR1l5fnlZpScK3YqvX/eOqK0tfcbU3RF5BXTXC3X7/beJqHMD9fZD3o2+vTtwbqNYbwlcdY5ZJc7Cyih06+MbIMQ1ZLkk7Tvl7XTtwP5vFtrjKpNHJUZUItpiRbvg/r8T51qninTLb+u63Q7p+wex6z6WutN2EetON9LNMSCrj6Puh1P/UoH+u3CuXai/+PR42jsw5rskia91t4FOB9yohZ6imPUq+0kkia/zOiO9vMyjqTPGvFB3h13F47tBqBv+bVY6Gt1Gfeylbit170ndPqFuuPwToHOLQX2bhTrhp49DZ6CN3cnisWydJtJZXlFcKH3tBR2dAN2Bj9Tsg7w7cgryKpybLtRdGdM9RHQ/bber8i0WzX3lUdpzBH2UhyLfDXvsYnt095XwPm3GA2hs6oFjaYpN+vLg41b+rbykQK1Pd3/Ipt/dxt+mXvxtqje0Xf49iasddb9Lii0baEs32tKVtviMbIlyLBvbgnJ0Y6yA/vcU2tIduUG6poS2YOcTNkys95BwbWOlH/xd2rIR+Ym9cTxHb4+zsmyww1PukOMfw8ZydGIsB9tGieNADKVmn5d+FlXMBPc0ypZ1w4/TX7dfyB7B96P7cE76yTpbo3y2hK1ot0DcoUsTC7dVoPN+6LTrdUY4frtRlzbGUVvPesYEfMA+eZt94tbr9D/HoF9w/4tgrympnnZdn+To+qSTpk+KGfeixEJpnwE6ivujbrrezuJSd4kDA1LukrBtJOoPJV7YQGeDXmcUzxyR9En7TmK9Pr3eKH/3DXRrxuB86u5I3R2ou1mvO8Lf/Ujqm4YfYPkYFHQH/+QYtJyi1ynfD3BjkAdiq94XMk8R3xd8tPVyXi+Laat9ht7WypbrJYJ9rCKxNfT1MlvTj6nyf+H3bYs6klI/Wmfq7ZTKjsS+Dv571KmQV/3dpPt7hO7vNOlv7j33uV93v/ETB6dbGKv8oXJsuPz3JuXvTPnv15S/D5P/fkH5+1D576eVv4fJfz+q/J2hxPhh7Gl+o9KUGP1yRM3qxwDGtT6OmG15In2S45FXS88XuS1tKQ/sCPqZNgX9jmcr3wEsr/LwmF3Zl6y4zMJjOYH+xrESjtUvZTvge9WN1dzOwXP2NdIYcCp2Txgdx3x9QgTPRYHx6KMtPZCT+Nz7EGzJCrKltCCSe1nAhnP2Fs8nRuO4/tn+YejLFeiLdm5spHOtQOcj0OkN0umWbtwoIH6dWV10z77s43q1zhifeyPpX+W+2CU=
*/