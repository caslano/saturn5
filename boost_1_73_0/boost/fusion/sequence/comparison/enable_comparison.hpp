/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ENABLE_COMPARISON_09232005_1958)
#define FUSION_ENABLE_COMPARISON_09232005_1958

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion { namespace traits
{
    template <typename Seq1, typename Seq2, typename Enable = void>
    struct enable_equality
        : mpl::and_<traits::is_sequence<Seq1>, traits::is_sequence<Seq2> >
    {};

    template <typename Seq1, typename Seq2, typename Enable = void>
    struct enable_comparison
        : mpl::and_<
            traits::is_sequence<Seq1>, traits::is_sequence<Seq2>
          , mpl::equal_to<result_of::size<Seq1>, result_of::size<Seq2> >
        >
    {};
}}}

#endif

/* enable_comparison.hpp
Uc7X/3vWGST+/TxGHd/L5HvJR4hpZCOWuZrNtYpQRv/Wow0ZvL/hr8yFGN6PLtpc8WvavZ84Qysa6YNOdHPe+h9EBRr2kEPRhiCvMy/lyHn7OFcj/V/bwnhxrmJkHa+TXmauH5+DvK+FYyptCdC//Sfznjs412qudRvnRwsGyLmB4/MonVyUSNu5btls+oyvBznWcGzn2Moxl2Mc6pH2WXAsJ8c0c+0ODCDoZ7zSEUbPqax3
*/