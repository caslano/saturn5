/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion
{
    struct fusion_sequence_tag;
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    struct set : sequence_base<set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9> >
    {
        struct category : forward_traversal_tag, associative_tag {};
        typedef set_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef vector<
            T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9>
        storage_type;
        typedef typename storage_type::size size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set()
            : data() {}
        template <typename Sequence>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set(Sequence const& rhs
            , typename enable_if<traits::is_sequence<Sequence>, detail::enabler_>::type = detail::enabler)
            : data(rhs) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    explicit
    set(typename detail::call_param<T0 >::type arg0)
        : data(arg0) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1)
        : data(arg0 , arg1) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2)
        : data(arg0 , arg1 , arg2) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3)
        : data(arg0 , arg1 , arg2 , arg3) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4)
        : data(arg0 , arg1 , arg2 , arg3 , arg4) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9) {}
        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set&
        operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type& get_data() { return data; }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type const& get_data() const { return data; }
    private:
        storage_type data;
    };
}}

/* set10.hpp
12APrMCe+Br2wo+wDx7DvqilUz+sj7ehP/bHaByA/XEQjsfBmIqxeC8OwVIchutwOG7BEXgIR+JRHI2ncQxyLC1j8WYchzE4HsdiPBZjAi7ERFyOSfgIJuMaTMEPMRWPYhr+jOl4ATNRGxtlAgbhRMzAHLRiLpbhJNyDefgd5uNZLEDGcbIU4vU4GevjFGyBRRiDU3Em3on34AzchHfhUZyJXhzfYrweZ+GNOBvb4Bxsh3NxBN6NE3AeFuE9OANLpBw8aZHfObhRygWtPD0i5UK8lPMJ2AqTMAxTsCumYiKmYRpm4GTMxLtwAj6BE3EbZuFOzMHDmIvH0Yo12fYkrI352BgLMBgLcQROxjicimk4DbNxBs7Fu3AFzsTVWMy/F3AWVuBsKV8Y819+C3GMpS9AEP9fitq0QMa0uR9b40LsiIswAhdjP3wAJ+ISzMNlOA0fxMfxIXwGl+P7+DB+givwOK7Ek7gKG7LtR7EZPoa9sEzOlydwFK7G8fgkFuJTOAPX4OP4NJbjM7gDn8V38Tn8EddiVfLz81gTX8KWuA5DcD32wg04HDdiKm7CSbgZ5+BfcAluwWX4Cu7GrfgFvop/x214DrfL+fM6Nsad2Anfwr74No7DXZiE70j+LLHI7zfsIfmztq0PpX16T8q1vXKcPsS5+AnOx79iBX6GH+EBPICf40U8iN6s8xBWxy+xOf4NI/Ar7IIyVgf1cvktJb+xtPhQ36HclvhIH9P3sTV+gJ3wI4zAj3EM7sMkPIB34ec4Dw/is/gFvoSH8S/4Nd7Ato5gUzyK7fAYhuE32BO/xzj8ARfij7gMT+Bf8Gfci6dxH57Bo/gLXsCzqOWPc9gEf8W2+Bt2wosYjr/j7UhC0JccMBu9sRir4D3og4uwKq7Ea/BZvBZ3YDV8D6vjHqyBn+N1+BvWxKpVOOZYA32xDtbBAKyLHbEe9sL62B9vwCHYAOOxIU7EG3E+3oT3Y2NcgU1wPfrhRmyBO7ANfoD+eAAD8Bi2xZ+wHV7E9lhd66OODbAjNsdO2BGDMASDUfpaOX5TEvc/9rW6W8rde/AmLMFueC/2wfkYhwswCe/HQlyIM3ARPo6l+BQ+gJtwCX6OD+GPuBxP4QrU8v9KrI2rkDxt648T2P/S/XjOErR+OrEst9Vq769TQMjg8y7cTzhN8O3g6qMTQzD0zZE+Ofr+ONFKnxzpj2PaF8efsIDtDUOzPjjnCa068/37q9n64rQnDONzCsHRF2ct3zf2x/mE8APhPGEnf1f74KQo/XDW2vviVKofzlzCftal9rn5hGAJ4bvMV/vaJBDuJCxQ+tv4lbPfLGfW16YLYaCzr82l+9hEO/vZuPrXNBpQ3dKFMIxgJZQS1hJ2EY4QLAPpd0OIJIwlFBGWEioInxBOD7y6bdv/I8//J2fn25/+/3vP/7Xn+0Mb28pai7/nfs7/7f2cK71vU8F6KHcrVeZKWftvl7OVLWMvUb5KueosTy9Vlv5p5ahJGXrZ8vNqlJueyTN5Js/kmTyTZ/JMnskzeaY/f/Ih5Fzt3///ZO9u4Ksa4wCO32mp0ct6kfTCssXUqpW11ou12ppVK6tGay3b2nvt5dpLLcIkDGGRhDDvYRiKEEIIYd7DsEhCGIW8+517//fec8/OXdua8vI8H49vne5znuc855x7z3me8zxHPt5abQDTVBuAagNQbQCqDUAFFVRQQQUVVFBBBRVUaFY4IP3/uTlzW+PeXxv/P5sxHTEP28b/Z2Smau8sZhi/bR4A+/j/cO71QmVM72IveaZdxjVvI6b4k3eOY/y/a3RsU97l35LxsUv9XONFtbEpxfPszyil+stYKylrhNzuzPSirDg=
*/