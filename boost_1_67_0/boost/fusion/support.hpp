/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SUPPORT_10022005_0545)
#define FUSION_SUPPORT_10022005_0545

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/is_iterator.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/pair.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/deduce.hpp>
#include <boost/fusion/support/deduce_sequence.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/fusion/support/as_const.hpp>

#endif

/* support.hpp
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
*/