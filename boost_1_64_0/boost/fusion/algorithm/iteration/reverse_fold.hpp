/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_FOLD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_FOLD_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/reverse_fold_fwd.hpp>
#include <boost/config.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/add_reference.hpp>

#define BOOST_FUSION_REVERSE_FOLD

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/algorithm/iteration/detail/preprocessed/reverse_fold.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/preprocessed/reverse_fold.hpp")
#endif

/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#include <boost/fusion/algorithm/iteration/detail/fold.hpp>

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#undef BOOST_FUSION_REVERSE_FOLD

#endif

/* reverse_fold.hpp
pzBjV39d4QFjMLnXQTGmwSy0a2Er4FAiCMf56cb8CVN5/KkEzlMY6kuUeqQeeuBpVvMmv+jcY8/io7areVjOxdpKrPrRQkgzPEyYJuQPx+q4xoqbuRt0SogC8cEHObsJ1CTkHY4j9dpjpffac8DlsPtNLP0bg3PBnRoUQ+EF/lt/LLG25QbSEZeHqIrY6IEVrzP04IrN8CS/R2AbmjaN+wolsvQEVfbiTPNlHx6K08R84xA9qRe05p6k/oQCwhLiXfpb8O7LgY5ROA/UDxWKVgi+Q7Kgx8IByGd7LwipEVNXforG/kBDn7nVNybxUeYzmADO9TXskydfgNelP5tj8G2241JEwzCuGQ17AD8sw/nyrbO75X2+C9OEAQjGsICCh13a3Al2f3MTOaaq2xbon9KVRO1VvyWJr6zGMjhWU5R5yWpVKROQ6UognZQVjCrSTeVrxmBXKRR8TR45SKCzzL+qfEDOBU2uihnYmfqp7ZW3b5Fzg8UTwQ5HmBVNmD98ODY0KvviohCv38NwCvmnLOELUyV9mibCDcwNP7MseI4BNJ5j9JOG+6yezg==
*/