/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_FUSED_HPP_INCLUDED)
#define BOOST_FUSION_FUNCTIONAL_ADAPTER_FUSED_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/config.hpp>

#include <boost/fusion/functional/adapter/detail/access.hpp>
#include <boost/fusion/functional/invocation/invoke.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    template <typename Function> class fused;

    //----- ---- --- -- - -  -   -

    template <typename Function>
    class fused
    {
        Function fnc_transformed;

        typedef typename detail::qf_c<Function>::type & func_const_fwd_t;
        typedef typename detail::qf<Function>::type & func_fwd_t;

    public:

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline explicit fused(func_const_fwd_t f = Function())
            : fnc_transformed(f)
        { }

        template <class Seq> 
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke<func_const_fwd_t,Seq const>::type 
        operator()(Seq const & s) const
        {
            return fusion::invoke<func_const_fwd_t>(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke<func_fwd_t,Seq const>::type 
        operator()(Seq const & s) 
        {
            return fusion::invoke<func_fwd_t>(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke<func_const_fwd_t,Seq>::type 
        operator()(Seq & s) const
        {
            return fusion::invoke<func_const_fwd_t>(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke<func_fwd_t,Seq>::type 
        operator()(Seq & s) 
        {
            return fusion::invoke<func_fwd_t>(this->fnc_transformed,s);
        }

        template <typename Sig>
        struct result;

        template <class Self, class Seq>
        struct result< Self const (Seq) >
            : result_of::invoke<func_const_fwd_t,
                typename boost::remove_reference<Seq>::type >
        { };

        template <class Self, class Seq>
        struct result< Self(Seq) >
            : result_of::invoke<func_fwd_t,
                typename boost::remove_reference<Seq>::type >
        { };

    };

}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif


/* fused.hpp
jcvEWZw3kaxjPo7i0JCYKIP0D85cJyI6a7+8cOPx1d50zNUC3fdhhuq8D9NX+74/i7GSophpeV4GSVoSR9N+BIHmXGwhz0i8R5zL43T8nGPFv6P5sRIeNdgvMiomQj3/s93PT5MvBot8MVjkiyl+mv3LK+MCTsjJ/uFI3Kbsn7fl/sWEBMXHxIYNClH3b85T9i/ZYv9WWuzfOtP+yfigWY+TVLRynGj6URaX5xQG5SAOOBC/JA5pPmZxkPTN3js7Nf1F5Vpv2n/ttT0yAOT3QRunaNMygWDZp9XY/zc/eVCYOCj10Q99tP1/5Til86jlcwFh6jzSQfPczz0ZQ88/P2khblf69nY3Twv12m/KUEmTvNm4TtUINl2nBvcyXi+M16RNPY3zjNekuz2M84zXpKamecbxvwpbXGtKWVxrnCyuNc522uuGi/FzHJki/TjN5gWi9poVJ/n0xGuG/PZqf9tDTed8pPF6ZOUaIstFgcWxFW35HmC2r3ud0fYblv77TvL7jmoeR/czz2Pt+brH8PS8/Sd7dwJfw7UHcPxaYsmzxK4kREVriUhiaWwVe8QWBFFLcrMRslxZxC40diX29aFEi9r7KN2k1WqUtqGtaqutlhZFq2hLqfd+M/nn3js3E25K+17f586np1/GnTnLnNnOnDkTO9qybeeOMm8fqqWclyzzzOelT0fmrwPHRuavA4+PzF8Haljmmc9Lk2LM87zzyivHZl88ZXMsOWOz313QKc+rlusOc924aZlnrhuGe52bZNulWM5NevVHtp+mLhZYZyIxxY46E2JTZ3oYNPVab0xizXE+QPr8V2YddbA8KteE7sl5dSYpJdzqmvBBjpPW14RhNteEI3SuCU0614T1ba4Jva2uCdVxW9kHlOfLh4pxDTjGcj3nfo/ruSHJmus56b9dUP/ehzdW28Pqh6zf37vgfub6/ZML7geu34+64P7M+v3GC+7nrN8vvaD+8IXvN17Y/vP6/cwL6s9fcH/402nq9tqUunXQsaIDa4ypcPHYRi92EHWsqKJyjyv3vv5F0aD251Sntkp/FHwSG2Bn9MUu2Ap7YjfshSEYhNHYB1OwL07BYFyAA3ANDsQsDMHPcBB+hU/h1zgYf8BheBeN6ESaRmEZjEV3jMN6GI8+mIDBaMJBmIIJOAan4wSchxPxnzgZM3EK7sWpeBynYRHK4mmsgOlYF6djI5yB3jgTA3AWhuFsjMI5OAnn4jSch5/gfDyNGXgdF+JNXITlqX+LsTIuwRhchim4HFPxEM7Bt3ABvo2r8TAexaN4CY/hz/ge1lT6R6Ib5mA9/BB98SNsgR9Lv7cLxeQ+XO7P/dVxBqlDcs++VvoXPItdcQOOxkycgJtwOj6Pz+JmfA234Kf4Ap7HbXgNt+Nd3IF15buO3XEXRuFunIJ7MB3/hVtwLx7HfXgJX0In0rofnfFlbIKv4EB8FUfjazgXX8cMzMK9+AZ+gW/ir3gIKyjljJXwMNbCd9AXs7ELHsHu+C4OwqM4Eo/hanwf38YP8CvMwXN4Assp2wHr40fYEE9iMH6CkfgZjsXPcR5+iavwDL6FX+OX+A2exbNY1on2I3wcv0VP/A4H4Hk04QVMxIu4Br/HfXgJ9+MVPIY/4Bn8Eb/Fn/B7vIY/43UswrH/BrrjzxiAv2A4/ooT8SZOxd9wPd7GbLyD3+DveAfvYhHlnq8I68MiGIBFMRyL4UQsjlOxBK7HkpiNpfAbLI130BnvYhksXYpzJrphOfTB8tgCXbATVsD+WBFnYGXchVXwXayKH2B1vIWPYCXOzzWwCrpiO3TD3uiOEVgHU9EDp+NjuBMfxyNYH9/HBngTG2JF9r9GWA0=
*/