/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FIND_FWD_HPP_INCLUDED)
#define BOOST_FUSION_FIND_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct find;
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::find<Sequence, T>
        >::type const
    find(Sequence& seq);

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::find<Sequence const, T>::type const
    find(Sequence const& seq);
}}

#endif

/* find_fwd.hpp
LHlP7ftq30aZ973D6SDuanlZq+DQ1/gHSjf1T62wTx5o5ZnZMdA1gN03i6EPGomcC8O1jqZiE9aoQGm4mP3gERxdqlPkyuEHKb5KjGnhCfgk0NJSPZnsMiM/tpGycO70jclnrzeawgsPZqNPdGLxNcu4Cz7wxugKaEk0nyeKPc9nclg5Ohu/5M1X9UnVQ2be6UXmsDXAWw+hKHAZihY9u6WBaiPUyXGTxVV7kD5SZ7ohGB5BSVhhk38nhyfJb2m2inoNuKaXfhjUG6jqRBd4poY3a0kiOK6i+grtRq5L0A+HiVd2Pc/SOJPDgpWykR5PuZ3NGspHcycF88nSlp4C6WjYaNKgrP+xOWFfvkAGdsZBTGNruPT1rHyGHGlOxjHZNhGqVE8FM8UOYcDCmpWqE7R1TmO3NSEeHIsgcpUJS8RUrvcU7EoXKW9Q8vdyKV8O8+1aUCJKpmLgR/YocAVvBsIEkijc5s639LLGIYXUON5uDNQ84QEIhnzCHN3HDmhFvD2yGG5pWh7de/FCJsHHY6wDmvWJycGTgMshhCA+iB89D4osQmOJq1j69g==
*/