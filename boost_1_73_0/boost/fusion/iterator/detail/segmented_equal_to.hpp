/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_ITERATOR_EQUAL_TO_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_ITERATOR_EQUAL_TO_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    namespace detail
    {
        template <typename Stack1, typename Stack2>
        struct segmented_equal_to
          : mpl::and_<
                segmented_equal_to<
                    typename Stack1::cdr_type,
                    typename Stack2::cdr_type
                >
              , result_of::equal_to<
                    typename Stack1::car_type::begin_type,
                    typename Stack2::car_type::begin_type
                >
            >
        {};

        template <>
        struct segmented_equal_to<fusion::nil_, fusion::nil_>
          : mpl::true_
        {};
    }
}}

#endif

/* segmented_equal_to.hpp
7/sq17e7XAevdn2Y7d8r082vw85v43BfgXXuI+ZL42V9yOfN5xr31kur/b2Ncd6v/fzOK84fn+fMucl5tdZ+nGHdWe28eNj1Ita4e9L5/VPjy/3KAdfJyUeMrxzrnxvd5/7QcTzXfPB566py17k+v+++Z47XW7fBde8U56F5fYr5ckGm/bTS8we8X+vBgwXue7/v+rbQ/Nzq8XL7r9V9YKL7d+ucAvPlhfNdX67xvmvN14PG
*/