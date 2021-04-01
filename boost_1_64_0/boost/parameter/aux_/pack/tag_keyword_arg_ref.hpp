// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_KEYWORD_ARG_REF_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_KEYWORD_ARG_REF_HPP

#include <boost/parameter/aux_/unwrap_cv_reference.hpp>
#include <boost/parameter/aux_/tagged_argument.hpp>
#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux { 

    template <
        typename Keyword
      , typename ActualArg
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
      , typename = typename ::boost::parameter::aux
        ::is_cv_reference_wrapper<ActualArg>::type
#endif
    >
    struct tag_ref
    {
        typedef ::boost::parameter::aux::tagged_argument<
            Keyword
          , typename ::boost::parameter::aux
            ::unwrap_cv_reference<ActualArg>::type
        > type;
    };
}}} // namespace boost::parameter::aux_

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))

#include <boost/mpl/bool.hpp>

namespace boost { namespace parameter { namespace aux { 

    template <typename Keyword, typename ActualArg>
    struct tag_ref<Keyword,ActualArg,::boost::mpl::false_>
    {
        typedef ::boost::parameter::aux
        ::tagged_argument<Keyword,ActualArg> type;
    };
}}} // namespace boost::parameter::aux_

#endif  // Borland workarounds needed.

namespace boost { namespace parameter { namespace aux {

    struct tag_keyword_arg_ref
    {
        template <typename K, typename T>
        struct apply
        {
            typedef typename ::boost::parameter::aux::tag_ref<K,T>::type type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename K, typename T>
        using fn = typename ::boost::parameter::aux::tag_ref<K,T>::type;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* tag_keyword_arg_ref.hpp
te5V1K1bBBpiwoFHbj/K3rcmSeC7T3tGrN0C7IfCasob7i9FH1QHBsZpaEzhzkdqu7llNAH78ueL9jIEJqg63FJBxcI0qTreD2rEjZGxa2EQlMP43wlZcc5qu3mbUnnD3MtOZSnDQMRvAJ66CiFlEeVkD7QaV2MoDf+WWS3O270Q2zPfuBtWq595fJksKhO7WP4Oc3QgK64EooXmi/7dj+mq243/KfLkPufi2d8YNqqFbM162M5HdPCJrfkFc1JxYVmsr7Xjs4V8ofr2Jw7SsiLrYkSoLjCi2aTz/a48l9EyHBfTl7u9ocYKMY9KS3q4yHwT0i2tUyykjIOLMbHtno5Lc+SPe99LR+5pPEr5G14Q+FkgiKlrDSU74N4tHX4dZqUIE2sEKbxAGnL5kWX3LrMWtVp8KtRwghzvnMlzBP7VAOtgyNJidXh2hgQUH1qEEVwESv2jgN16m2DQLOlJtntHQ9jX1J6DT9LCULiRW9qcTwWmWUhlq15cUT+WyXvQ9KS1l9Um0y+o+0yeisttreAefhdvX07ssjBmX3Y8Bf1ey6YLmuyd7lN4qA==
*/