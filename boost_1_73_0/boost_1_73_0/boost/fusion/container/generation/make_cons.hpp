/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAKE_CONS_07172005_0918)
#define FUSION_MAKE_CONS_07172005_0918

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    namespace result_of
    {
        template <typename Car, typename Cdr = nil_>
        struct make_cons
        {
            typedef cons<typename detail::as_fusion_element<Car>::type, Cdr> type;
        };
    }

    template <typename Car>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline cons<typename detail::as_fusion_element<Car>::type>
    make_cons(Car const& car)
    {
        return cons<typename detail::as_fusion_element<Car>::type>(car);
    }

    template <typename Car, typename Cdr>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline cons<typename detail::as_fusion_element<Car>::type, Cdr>
    make_cons(Car const& car, Cdr const& cdr)
    {
        return cons<typename detail::as_fusion_element<Car>::type, Cdr>(car, cdr);
    }
}}

#endif


/* make_cons.hpp
TTjvdq11L7RJdMpCnRm3D5O+oW2Pa1DTgGDFXq4CMgdgSM4/ChXQGw3vcbR4qBngB2/MUlUUTCEBEg4BymJJIN0Zl29NdaWyNX9bNUK5teWz8hbZajlfuekTKpQmd8Uqvr4b3pgXXaPb0NzaYAQ9AebLVUAL5sLO766U2SuYixjedo3etarE4rkI1kab0x/ObeBZYo3xB3is9asBFs+VDLTuvRqgGA9PFmuwfuPTrprhLzpfqqn6qFC3hXh4Dk+jePwsNFXI4r6e9qlBPH5mVFP1UaFtFOJlTjmURRbn2pMu9D+VHYxqroPHkmQiE9s8dhhtbjps5wel3cNp5OOSMCghN5d9bXChNs1bELPHnypgqioxZ21p2XKt5AEqaqu1CtJGwxifvHrVHfS7ukJ+LA4hgMfDXDO1waZjJ71xU90prNm/342MpoYvxjg+qgxXMlytrkAhXhXmivBCl9VYd8/QBpBkN7ccADLuodYDXLUlecnWm7ceN1rfi/8oLcfNdQUFS4XZun25dZtsnzk/PKZMtBaqB2dscaQcV1H+TMInccUpf8eXm7JCgxEUgV9SyualvnsfFwuHUQt8XsmuAYkFvKVCpsVjnBcLdzG6Ox9UYzrcgFDMdvLoFTHjabY5TyWM6zj+yPkuZ7Vq
*/