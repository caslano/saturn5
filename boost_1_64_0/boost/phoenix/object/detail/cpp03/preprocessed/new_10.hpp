/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
    template <typename T, typename A0>
    inline
    typename expression::new_<detail::target<T>, A0>::type const
    new_(A0 const& a0)
    {
        return
            expression::
                new_<detail::target<T>, A0>::
                    make(detail::target<T>(), a0);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1>
    inline
    typename expression::new_<detail::target<T>, A0 , A1>::type const
    new_(A0 const& a0 , A1 const& a1)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1>::
                    make(detail::target<T>(), a0 , a1);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2>::
                    make(detail::target<T>(), a0 , a1 , a2);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
    }

/* new_10.hpp
2eSLxMxzuI9ecSXTYgzCOm+iTvuD6w/rSCrnzO1SThZK8kq5i77P65CetJ5rhvUcNXEaXeH9nkgKa0r36oTp+Rd5pWn9HlBGqbUKeiOmqcFYU7phO3eHrEjj6g/gzHubTH9eBljuANjiUViqCQtf/qE/25rzAuXpWFsOexVD+FKwWu6LKSFgmuOhQus1po/XmJzlakgpV6FZnCXdklovTHW5pCyjCUMLq84OgE8v/EOV+K+EjKQQ/LeA/zueGmsENXMgu+AEugwZzJ9EAEVbuR2pLPOIrHwARDQ3OzRhtvgLQxMKqctef4kTUOr4XY7UQyiGdw4vvswRVJONmwmtFLKJFt74LxXuNgVKRXt9O4FSG6W6uY3i0AOjozWxr31rfJShVlM+UE+hbt+hvn71ytDaHyCaIdhPIb3oijlTrQWz/Rk5Pn6iuYWGXr+Igz3kSLkJV2YDAYhwFgfElC2HsGk9yjEldHoKZZEMxSEeTwGpNKrSgk1Uv7Cf2qI3f6m2yEkLZaeJf24oe6600dCe2Eb4r4SkUQj+q8Z5QEd76KeJO3xEqquJVIcTL6E/2wK1LOpin3qyMbQMw5XBjnfUgFS1htNRRuAHgh4v6RqoAA2hMgiXO/1fyOw1FNqH340ygeM32C7ltKL52wjPVco6F2G8thCnjQuQSt/fcqIxmc3zJvGTuqYcOJNU7+AtVDFs3dSH1YDq+N9DIqaI3gSQnkgA4W7hh/DKvTfR5bEv/P9e/bD+9Hy64qV25U8fjpQ/vd3N9u97tSt/Gt7YjvzpmxsPUf7UFpdCrAvH0BRHGhpGlecPhdEiFQgjBXgjGfxB8GvBXX2YAMb/RuJMmtppnlredcU2Le8aJ2P56J5Oede4NJIqGZnglHh929ASr7s9Eef5f/bHkHjlc9+3mIy1GKvV5xQ5i1PiLth6MCKeRIB+GkeP3gCFtKVaz2AcMh6O5U8ay6dnW9+DAsgMtpoY/qrJlIW2RJdjncchxOhqJqWM1m5UGelrkHuZwyj21JMgVcTcOPk5ijXrPU7RiBk0VBzooW8DFm2iJqzYxNANAs1vfmgh8GuGNj+MwLSaMN2l4vpermRwywhdGlXCZ1ZBMGEqJUzLfkzBlH42pe/JDWR+onAzkkJCkqFw/yOiTEsJ05EqrtnTVvDDo+K0XPBQQuedHCUXnEyY5nGwOnIujDinDEafU17PjcqbYMos73kK4cOZnpjPpwlcJZ/XWewtlJnZ3Zb5rab0x0KTSPrRlH6Gn9MnOtIDXPd/Lyngr++P7/fY+h2f1IjSEhNPDCsnQxeHEpXyhJ7aXl1YwwTg2IlgYsqTCksDgFP/xQsR+08yhkIqtD7nPgHhNT/N0ymQoRrvpogV4HF0zYZ2GmlVQoptAqC8jXZpcJrVm4L9pBm/2XFJGCCbfWyy8fA60z7/3Ryj/CfHLv81Uv6LWA+P2DL2LwmUJVINpOD5gSUT3GUGa4khzIAsuOR0o8xHRh97S9Lk8mxvCNKmONKmlE8AvXqYasJh1jKaPjQThQJtSQGV78GpwXZ+SRZyd76/BPm1YobS8uXFdCbwQ7YTf7xqwWI+bUsfJd+885t+gvqeZ4ST6ZYFU7vlShXHtrDRFeEwzl/OEBb3jCHPQuNFx/LsC5LdFBNbn0Pm81qemipx3K8OtuoFI+/h7lebX2vOZorTq0ZtaY9Uu9dP0KvGK1BdJC0lgxPVqrHRdENToMUKQlX4omy1xtJe0WfdA8mdMkGwcm7kbdnTE2T3xSZ5sukbYXxk9vwrbo0j2iuo2iv2+5+N6jwDx/VQll3eoBx0Uhn9PWKPzE76qna8lwB/7PcSev23IUb+KVELLW67JTRDBDs=
*/