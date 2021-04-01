/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FRONT_09162005_0343)
#define FUSION_FRONT_09162005_0343

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;

    namespace result_of
    {
        template <typename Sequence>
        struct front
            : result_of::deref<typename result_of::begin<Sequence>::type>
        {};
    }
    
    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::front<Sequence>::type
    front(Sequence& seq)
    {
        return *fusion::begin(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::front<Sequence const>::type
    front(Sequence const& seq)
    {
        return *fusion::begin(seq);
    }
}}

#endif

/* front.hpp
K/dpw6HiiFij2axQJUZeXeeR06DgjZ7fy39hxcQ0neEDkcel57/3zVunFT8Z6k6H3C1sBMmYsS9UOSDvZ6jext4+IvUiywIHor4cp1B+w3eJBUIdvbrskdZJeLHjB1f+bXVrMJW/Xuwb9LrWtjBLdvEsz5elOTaCz7kJVnklOYcSzy2vAGVkHU2Pvbta3oo94HEQIVOSpMdOw3vOIQiOAZHF9hgjwdM7syuhjUl8Gu/kg1zmDSyAMvJAPqDkUzZKwWEmXaPoapEynOXhl5QMNABrMDyBmbGAHtuwqEhu8B7gPzsYSafgjlf7sHZMj4cIaMoscshrei1MQ7U/DYz79ZgIWUxO7BfINhabwUx6n80SSN5QCGRUsNI5hRlndqRtAj2IIfDGFwEPoLRoyxhucpMs/AuJnSkWx/ckRBviOTmb0R6K5nmmfybkKesb9Yto4XbJnWe6tr0dmJeVInewNWE3sRL4eg9WzNSUMIflHy8+yZxHEEJTfGKsIXETUnaXxF76F3aEpNR7XFxAKz7CV84quYC0sYSqSu9mPGl2zGu0xq7Td1REPaWDlA==
*/