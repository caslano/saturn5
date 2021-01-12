/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REMOVE_07162005_0818)
#define FUSION_REMOVE_07162005_0818

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct remove
        {
            typedef filter_view<Sequence, mpl::not_<is_same<mpl::_, T> > > type;
        };
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::remove<Sequence const, T>::type
    remove(Sequence const& seq)
    {
        typedef typename result_of::remove<Sequence const, T>::type result_type;
        return result_type(seq);
    }
}}

#endif


/* remove.hpp
Pil/pM1Uti0H5c/7XhyicSSWwdFYAcdiFfwA38aJ+A5OwjhJ7yrp3aU7Tb7PwlNGm51cj8h48xP7ZbyFLM/268JoxWD0wRAshg2wOIZiGSyH9bACNsNw7IDVMBarYxJGYDf5Pl2+7yvfZ2I9HCbDH45v4CisjeOxDk6TfLMk32yMQnVeaJa2JaV9zWXYluA8Rf019uR8Ct+UcrUlFsdoLImtMAzbYGVsL+VpN2yF6RiPfaT8
*/