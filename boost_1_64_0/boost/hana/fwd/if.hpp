/*!
@file
Forward declares `boost::hana::if_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_IF_HPP
#define BOOST_HANA_FWD_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Conditionally return one of two values based on a condition.
    //! @ingroup group-Logical
    //!
    //! Specifically, `then` is returned iff `cond` is true-valued, and
    //! `else_` is returned otherwise. Note that some `Logical` models may
    //! allow `then` and `else_` to have different types, while others may
    //! require both values to have the same type.
    //!
    //!
    //! @param cond
    //! The condition determining which of the two values is returned.
    //!
    //! @param then
    //! The value returned when `cond` is true-valued.
    //!
    //! @param else_
    //! The value returned when `cond` is false-valued.
    //!
    //!
    //! Example
    //! -------
    //! @include example/if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto if_ = [](auto&& cond, auto&& then, auto&& else_) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct if_impl : if_impl<L, when<true>> { };

    struct if_t {
        template <typename Cond, typename Then, typename Else>
        constexpr decltype(auto) operator()(Cond&& cond, Then&& then, Else&& else_) const;
    };

    constexpr if_t if_{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_IF_HPP

/* if.hpp
BVnXBWumBSPlQq6f69zAi+a+wVjUlyzOMguNXseCu5Fy75rv/TgeR84POHmNYdpm+Z9/GIivevAHTtubN4weo8foMXqMHqPH6DF6jB6jx+gxeoweo8foMXqMHqPH6DF6jB7/MwfvD8n7/zVig/mPnxzPW2jnubdvPttVrdz+1BWNXdXush91r8YmkWt+fvsfu6rVSf0bXsBekR87++Hyrmr/6etevbiruvBt5+b9EHvu0iZsXdUB2oKtq7qYdlvrqi6hrdi6qktp17Wu6im0yVpX9TTaXq2rupx2ZrO92aBJb1ifGY+Tv5A25xdjxGxlct5k7L07wy1meyZXuyfP9YgZqpjtm1ytTp7rEzP8Ynbh5Gr/ZOwkOqNIzA5Mri6aPDcgZhSL2SWTq4snzy0RM0rF7CmTq0snz50iZkwTs8snV0+bPLe8oTP3fo5dFbwZY1cFb8WY+gLtVCqc2Dq4M5H+9xW0oyD2JQUH2Pxcf+LbA3Gk84lDeOoRJ4gxfe6XBuL5D+fTRuO5yse7bs3dmSivCr+dlBe2Iu7MuJ8kUzCrCVtJlnbNKuatJGc10SaSLc+Md8TvasJ97Ib4bXMHyT7sifgHN71zSnjy2ioU2jnyhLP5TGO0Vr/2Dt42knc3zLlx5KYAUulecJzYL7IIZRS3eQLz5WaRShE2iwzhgnclxVml8zK5d+RW7Crp8E6oCrwCV6936CUBawP24E4mQT/1XaInYE+o5H6RFYP2i5zVxJtFLsRmkSXYLLKUd3Nc9PR4R2OFrJuYsVPkrCa5TaRs1HOxFyrkHpE3puwRuSh5j0hkHjazHIMsnXc1jXB3SNTnNmL5L99M1OdqGba4mj17XvVNpd0F6oJF2ALyj0Th9PvkZ7XF3hnyKrExJPnbOB6lxh8WTSpH/dQU1ooWhf2L69ifj+zXJfbH0+D4g3uyfBk2A4YPiwu8wqvOV73qu4u86ntLnXXwwhV5izvKDizz3nFIEXUlE7evOkP6oe/wqrPU+501AWwtKTdfFC0Bcg2u6iOVQdsoeifcz15u3I26druO416HOKeRZ/YMrp/p2K0iczxtdT1LBbjFwzgd9sDvV97R7XF1O6lf4Q/uzO1u13FeN3YX3i8JdsORt0m65QId28fhST3ljnO5C6y79lH54oyGx8E+AUZRlutZ3hbmYXIpc/auC2IPVUIi+ynieWRfGryI1/d17BlHPlxv8Ra0O3kgN0telqKEhSiBqoT3jvRz5szdw0iN/BcifwptYRb8wSglcRtMUjpvcSfKKQ6ytjBCAlzkmt2nUVEb2X+PcPMdquushiTiIF7toYqZg5yRgyy9Y9c4Yx06LkiFr1bt2OHGO9hMUhxFusNwYEZ5QWpIB+0Z5trXsWMcBxLhFvKb1tGturo13MDSe33MA3pQx24iP4JG4ypCym5y8qKacLvCtY9qVCD6AyzsBi8CRaAVjDXTk7h8ENdHPEyrRs2yy3WBiBKPUPAClXyGpJN3vjmHMl274VKdgjIR1sANwyEnHXvc5CVHGvqIq0Q2dw3y+RvOTa4d3NgdWB+P0u5SUarrHIvKQaaEfdt+2eCHg70afuBGfccuN5KhOPGshlw5kOMEMtpClYoWbPMUuCjqohAOaTzD89KO7aoLSgG3jnbsIK4e9RhU1Lt2UP1zcpxRT2ZCDe+hxpEbtYGLP8Xhqn8EdVhCVXBR9AUpntPHFYB1dmRERDdulbJ4I7MLFNnCLVFCwjqOQyNJEmWNc7ZLWNgRCECNQxn3iLNBGbTJOZvSzk3pp1wPk8Rz7Oi/XKjR4AsQPxRKXAiKfegGwxyxhEU90BmQd41Gz8AvVyepw0QdGXniZoWRqg7xY5Q=
*/