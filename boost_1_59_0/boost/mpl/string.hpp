
#ifndef BOOST_MPL_STRING_HPP_INCLUDED
#define BOOST_MPL_STRING_HPP_INCLUDED

// Copyright Eric Niebler 2009
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: string.hpp 49239 2009-04-01 09:10:26Z eric_niebler $
// $Date: 2009-04-01 02:10:26 -0700 (Wed, 1 Apr 2009) $
// $Revision: 49239 $
//
// Thanks to:
//   Dmitry Goncharov for porting this to the Sun compiler

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/predef/other/endian.h>
#include <boost/mpl/limits/string.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/char.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/front_inserter.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/arithmetic/div.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

#include <iterator> // for bidirectional_iterator_tag
#include <climits>

namespace boost { namespace mpl
{
    #define BOOST_MPL_STRING_MAX_PARAMS                                                             \
      BOOST_PP_DIV(BOOST_PP_ADD(BOOST_MPL_LIMIT_STRING_SIZE, 3), 4)

    // Low-level bit-twiddling is done by macros. Any implementation-defined behavior of
    // multi-character literals should be localized to these macros.

    #define BOOST_MPL_MULTICHAR_LENGTH(c)                                                           \
      (std::size_t)((c<CHAR_MIN) ? 4 : ((c>0xffffff)+(c>0xffff)+(c>0xff)+1))

    #if BOOST_ENDIAN_LITTLE_BYTE && defined(__SUNPRO_CC)

        #define BOOST_MPL_MULTICHAR_AT(c,i)                                                         \
          (char)(0xff&((unsigned)(c)>>(8*(std::size_t)(i))))

        #define BOOST_MPL_MULTICHAR_PUSH_BACK(c,i)                                                  \
          ((((unsigned char)(i))<<(BOOST_MPL_MULTICHAR_LENGTH(c)*8))|(unsigned)(c))

        #define BOOST_MPL_MULTICHAR_PUSH_FRONT(c,i)                                                 \
          (((unsigned)(c)<<8)|(unsigned char)(i))

        #define BOOST_MPL_MULTICHAR_POP_BACK(c)                                                     \
          (((1<<((BOOST_MPL_MULTICHAR_LENGTH(c)-1)*8))-1)&(unsigned)(c))

        #define BOOST_MPL_MULTICHAR_POP_FRONT(c)                                                    \
          ((unsigned)(c)>>8)

    #else

        #define BOOST_MPL_MULTICHAR_AT(c,i)                                                         \
          (char)(0xff&((unsigned)(c)>>(8*(BOOST_MPL_MULTICHAR_LENGTH(c)-(std::size_t)(i)-1))))

        #define BOOST_MPL_MULTICHAR_PUSH_BACK(c,i)                                                  \
          (((unsigned)(c)<<8)|(unsigned char)(i))

        #define BOOST_MPL_MULTICHAR_PUSH_FRONT(c,i)                                                 \
          ((((unsigned char)(i))<<(BOOST_MPL_MULTICHAR_LENGTH(c)*8))|(unsigned)(c))

        #define BOOST_MPL_MULTICHAR_POP_BACK(c)                                                     \
          ((unsigned)(c)>>8)

        #define BOOST_MPL_MULTICHAR_POP_FRONT(c)                                                    \
          (((1<<((BOOST_MPL_MULTICHAR_LENGTH(c)-1)*8))-1)&(unsigned)(c))

    #endif

    struct string_tag;
    struct string_iterator_tag;

    template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_MPL_STRING_MAX_PARAMS, int C, 0)>
    struct string;

    template<typename Sequence, int I, int J>
    struct string_iterator;

    template<typename Sequence>
    struct sequence_tag;

    template<typename Tag>
    struct size_impl;

    template<>
    struct size_impl<mpl::string_tag>
    {
        template<typename Sequence>
        struct apply;

        #define M0(z, n, data)                                                                      \
        + BOOST_MPL_MULTICHAR_LENGTH(BOOST_PP_CAT(C,n))

        #define M1(z, n, data)                                                                      \
        template<BOOST_PP_ENUM_PARAMS_Z(z, n, int C)>                                               \
        struct apply<mpl::string<BOOST_PP_ENUM_PARAMS_Z(z, n, C)> >                                 \
          : mpl::size_t<(0 BOOST_PP_REPEAT_ ## z(n, M0, ~))>                                        \
        {};

        BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(BOOST_MPL_STRING_MAX_PARAMS), M1, ~)
        #undef M0
        #undef M1
    };

    template<>
    struct size_impl<mpl::string_tag>::apply<mpl::string<> >
      : mpl::size_t<0>
    {};

    template<typename Tag>
    struct begin_impl;

    template<>
    struct begin_impl<mpl::string_tag>
    {
        template<typename Sequence>
        struct apply
        {
            typedef mpl::string_iterator<Sequence, 0, 0> type;
        };
    };

    template<typename Tag>
    struct end_impl;

    template<>
    struct end_impl<mpl::string_tag>
    {
        template<typename Sequence>
        struct apply;

        #define M0(z,n,data)                                                                        \
        template<BOOST_PP_ENUM_PARAMS_Z(z, n, int C)>                                               \
        struct apply<mpl::string<BOOST_PP_ENUM_PARAMS_Z(z, n, C)> >                                 \
        {                                                                                           \
            typedef mpl::string_iterator<mpl::string<BOOST_PP_ENUM_PARAMS_Z(z, n, C)>, n, 0> type;  \
        };

        BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(BOOST_MPL_STRING_MAX_PARAMS), M0, ~)
        #undef M0
    };

    template<>
    struct end_impl<mpl::string_tag>::apply<mpl::string<> >
    {
        typedef mpl::string_iterator<mpl::string<>, 0, 0> type;
    };

    template<typename Tag>
    struct push_back_impl;

    template<>
    struct push_back_impl<mpl::string_tag>
    {
        template<typename Sequence, typename Value, bool B = (4==BOOST_MPL_MULTICHAR_LENGTH(Sequence::back_))>
        struct apply
        {
            BOOST_MPL_ASSERT_MSG(
                (BOOST_MPL_LIMIT_STRING_SIZE != mpl::size<Sequence>::type::value)
              , PUSH_BACK_FAILED_MPL_STRING_IS_FULL
              , (Sequence)
            );
            // If the above assertion didn't fire, then the string is sparse.
            // Repack the string and retry the push_back
            typedef
                typename mpl::push_back<
                    typename mpl::copy<
                        Sequence
                      , mpl::back_inserter<mpl::string<> >
                    >::type
                  , Value
                >::type
            type;
        };

        template<typename Value>
        struct apply<mpl::string<>, Value, false>
        {
            typedef mpl::string<(char)Value::value> type;
        };

        #define M0(z,n,data)                                                                        \
        template<BOOST_PP_ENUM_PARAMS_Z(z, n, int C), typename Value>                               \
        struct apply<mpl::string<BOOST_PP_ENUM_PARAMS_Z(z, n, C)>, Value, false>                    \
        {                                                                                           \
            typedef                                                                                 \
                mpl::string<                                                                        \
                    BOOST_PP_ENUM_PARAMS_Z(z, BOOST_PP_DEC(n), C)                                   \
                    BOOST_PP_COMMA_IF(BOOST_PP_DEC(n))                                              \
                    ((unsigned)BOOST_PP_CAT(C,BOOST_PP_DEC(n))>0xffffff)                            \
                    ?BOOST_PP_CAT(C,BOOST_PP_DEC(n))                                                \
                    :BOOST_MPL_MULTICHAR_PUSH_BACK(BOOST_PP_CAT(C,BOOST_PP_DEC(n)), Value::value)   \
                  , ((unsigned)BOOST_PP_CAT(C,BOOST_PP_DEC(n))>0xffffff)                            \
                    ?(char)Value::value                                                             \
                    :0                                                                              \
                >                                                                                   \
            type;                                                                                   \
        };

        BOOST_PP_REPEAT_FROM_TO(1, BOOST_MPL_STRING_MAX_PARAMS, M0, ~)
        #undef M0

        template<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, int C), typename Value>
        struct apply<mpl::string<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, C)>, Value, false>
        {
            typedef
                mpl::string<
                    BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(BOOST_MPL_STRING_MAX_PARAMS), C)
                  , BOOST_MPL_MULTICHAR_PUSH_BACK(BOOST_PP_CAT(C,BOOST_PP_DEC(BOOST_MPL_STRING_MAX_PARAMS)), Value::value)
                >
            type;
        };
    };

    template<typename Tag>
    struct has_push_back_impl;

    template<>
    struct has_push_back_impl<mpl::string_tag>
    {
        template<typename Sequence>
        struct apply
          : mpl::true_
        {};
    };

    template<typename Tag>
    struct pop_back_impl;

    template<>
    struct pop_back_impl<mpl::string_tag>
    {
        template<typename Sequence>
        struct apply;

        #define M0(z,n,data)                                                                        \
        template<BOOST_PP_ENUM_PARAMS_Z(z, n, int C)>                                               \
        struct apply<mpl::string<BOOST_PP_ENUM_PARAMS_Z(z, n, C)> >                                 \
        {                                                                                           \
            BOOST_MPL_ASSERT_MSG((C0 != 0), POP_BACK_FAILED_MPL_STRING_IS_EMPTY, (mpl::string<>));  \
            typedef                                                                                 \
                mpl::string<                                                                        \
                    BOOST_PP_ENUM_PARAMS_Z(z, BOOST_PP_DEC(n), C)                                   \
                    BOOST_PP_COMMA_IF(BOOST_PP_DEC(n))                                              \
                    BOOST_MPL_MULTICHAR_POP_BACK(BOOST_PP_CAT(C,BOOST_PP_DEC(n)))                   \
                >                                                                                   \
            type;                                                                                   \
        };

        BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(BOOST_MPL_STRING_MAX_PARAMS), M0, ~)
        #undef M0
    };

    template<typename Tag>
    struct has_pop_back_impl;

    template<>
    struct has_pop_back_impl<mpl::string_tag>
    {
        template<typename Sequence>
        struct apply
          : mpl::true_
        {};
    };

    template<typename Tag>
    struct push_front_impl;

    template<>
    struct push_front_impl<mpl::string_tag>
    {
        template<typename Sequence, typename Value, bool B = (4==BOOST_MPL_MULTICHAR_LENGTH(Sequence::front_))>
        struct apply
        {
            BOOST_MPL_ASSERT_MSG(
                (BOOST_MPL_LIMIT_STRING_SIZE != mpl::size<Sequence>::type::value)
              , PUSH_FRONT_FAILED_MPL_STRING_IS_FULL
              , (Sequence)
            );
            // If the above assertion didn't fire, then the string is sparse.
            // Repack the string and retry the push_front.
            typedef
                typename mpl::push_front<
                    typename mpl::reverse_copy<
                        Sequence
                      , mpl::front_inserter<string<> >
                    >::type
                  , Value
                >::type
            type;
        };

        #if !BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x590))
        template<typename Value>
        struct apply<mpl::string<>, Value, false>
        {
            typedef mpl::string<(char)Value::value> type;
        };
        #endif

        #define M0(z,n,data)                                                                        \
        template<BOOST_PP_ENUM_PARAMS_Z(z, n, int C), typename Value>                               \
        struct apply<mpl::string<BOOST_PP_ENUM_PARAMS_Z(z, n, C)>, Value, true>                     \
        {                                                                                           \
            typedef                                                                                 \
                mpl::string<                                                                        \
                    (char)Value::value                                                              \
                    BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, C)                                        \
                >                                                                                   \
            type;                                                                                   \
        };

        BOOST_PP_REPEAT_FROM_TO(1, BOOST_MPL_STRING_MAX_PARAMS, M0, ~)
        #undef M0

        template<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, int C), typename Value>
        struct apply<mpl::string<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, C)>, Value, false>
        {
            typedef
                mpl::string<
                    BOOST_MPL_MULTICHAR_PUSH_FRONT(C0, Value::value)
                  , BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, C)
                >
            type0;

            #if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x590))
            typedef
                typename mpl::if_<
                    mpl::empty<mpl::string<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, C)> >
                  , mpl::string<(char)Value::value>
                  , type0
                >::type
            type;
            #else
            typedef type0 type;
            #endif
        };
    };

    template<typename Tag>
    struct has_push_front_impl;

    template<>
    struct has_push_front_impl<mpl::string_tag>
    {
        template<typename Sequence>
        struct apply
          : mpl::true_
        {};
    };

    template<typename Tag>
    struct pop_front_impl;

    template<>
    struct pop_front_impl<mpl::string_tag>
    {
        template<typename Sequence, bool B = (1==BOOST_MPL_MULTICHAR_LENGTH(Sequence::front_))>
        struct apply;

        #define M0(z,n,data)                                                                        \
        template<BOOST_PP_ENUM_PARAMS_Z(z, n, int C)>                                               \
        struct apply<mpl::string<BOOST_PP_ENUM_PARAMS_Z(z, n, C)>, true>                            \
        {                                                                                           \
            BOOST_MPL_ASSERT_MSG((C0 != 0), POP_FRONT_FAILED_MPL_STRING_IS_EMPTY, (mpl::string<>)); \
            typedef                                                                                 \
                mpl::string<BOOST_PP_ENUM_SHIFTED_PARAMS_Z(z, n, C)>                                \
            type;                                                                                   \
        };

        BOOST_PP_REPEAT_FROM_TO(1, BOOST_MPL_STRING_MAX_PARAMS, M0, ~)
        #undef M0

        template<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, int C)>
        struct apply<mpl::string<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, C)>, false>
        {
            typedef
                mpl::string<
                    BOOST_MPL_MULTICHAR_POP_FRONT(C0)
                  , BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, C)
                >
            type;
        };
    };

    template<typename Tag>
    struct has_pop_front_impl;

    template<>
    struct has_pop_front_impl<mpl::string_tag>
    {
        template<typename Sequence>
        struct apply
          : mpl::true_
        {};
    };

    template<typename Tag>
    struct insert_range_impl;

    template<>
    struct insert_range_impl<mpl::string_tag>
    {
        template<typename Sequence, typename Pos, typename Range>
        struct apply
          : mpl::copy<
                mpl::joint_view<
                    mpl::iterator_range<
                        mpl::string_iterator<Sequence, 0, 0>
                      , Pos
                    >
                  , mpl::joint_view<
                        Range
                      , mpl::iterator_range<
                            Pos
                          , typename mpl::end<Sequence>::type
                        >
                    >
                >
              , mpl::back_inserter<mpl::string<> >
            >
        {};
    };

    template<typename Tag>
    struct insert_impl;

    template<>
    struct insert_impl<mpl::string_tag>
    {
        template<typename Sequence, typename Pos, typename Value>
        struct apply
          : mpl::insert_range<Sequence, Pos, mpl::string<(char)Value::value> >
        {};
    };

    template<typename Tag>
    struct erase_impl;

    template<>
    struct erase_impl<mpl::string_tag>
    {
        template<typename Sequence, typename First, typename Last>
        struct apply
          : mpl::copy<
                mpl::joint_view<
                    mpl::iterator_range<
                        mpl::string_iterator<Sequence, 0, 0>
                      , First
                    >
                  , mpl::iterator_range<
                        typename mpl::if_na<Last, typename mpl::next<First>::type>::type
                      , typename mpl::end<Sequence>::type
                    >
                >
              , mpl::back_inserter<mpl::string<> >
            >
        {};
    };

    template<typename Tag>
    struct clear_impl;

    template<>
    struct clear_impl<mpl::string_tag>
    {
        template<typename>
        struct apply
        {
            typedef mpl::string<> type;
        };
    };

    #define M0(z, n, data)                                                                            \
    template<BOOST_PP_ENUM_PARAMS_Z(z, BOOST_MPL_STRING_MAX_PARAMS, int C), int J>                    \
    struct string_iterator<mpl::string<BOOST_PP_ENUM_PARAMS_Z(z, BOOST_MPL_STRING_MAX_PARAMS, C)>, n, J> \
    {                                                                                                 \
        enum { eomc_ = (BOOST_MPL_MULTICHAR_LENGTH(BOOST_PP_CAT(C, n)) == J + 1) };                   \
        typedef mpl::string<BOOST_PP_ENUM_PARAMS_Z(z, BOOST_MPL_STRING_MAX_PARAMS, C)> string;        \
        typedef std::bidirectional_iterator_tag category;                                             \
        typedef                                                                                       \
            mpl::string_iterator<string, n + eomc_, eomc_ ? 0 : J + 1>                                \
        next;                                                                                         \
        typedef                                                                                       \
            mpl::string_iterator<string, n, J - 1>                                                    \
        prior;                                                                                        \
        typedef mpl::char_<BOOST_MPL_MULTICHAR_AT(BOOST_PP_CAT(C, n), J)> type;                       \
    };                                                                                                \
    template<BOOST_PP_ENUM_PARAMS_Z(z, BOOST_MPL_STRING_MAX_PARAMS, int C)>                           \
    struct string_iterator<mpl::string<BOOST_PP_ENUM_PARAMS_Z(z, BOOST_MPL_STRING_MAX_PARAMS, C)>, n, 0> \
    {                                                                                                 \
        enum { eomc_ = (BOOST_MPL_MULTICHAR_LENGTH(BOOST_PP_CAT(C, n)) == 1) };                       \
        typedef mpl::string<BOOST_PP_ENUM_PARAMS_Z(z, BOOST_MPL_STRING_MAX_PARAMS, C)> string;        \
        typedef std::bidirectional_iterator_tag category;                                             \
        typedef                                                                                       \
            mpl::string_iterator<string, n + eomc_, !eomc_>                                           \
        next;                                                                                         \
        typedef                                                                                       \
            mpl::string_iterator<                                                                     \
                string                                                                                \
              , n - 1                                                                                 \
              , BOOST_MPL_MULTICHAR_LENGTH(BOOST_PP_CAT(C, BOOST_PP_DEC(n))) - 1                      \
            >                                                                                         \
        prior;                                                                                        \
        typedef mpl::char_<BOOST_MPL_MULTICHAR_AT(BOOST_PP_CAT(C, n), 0)> type;                       \
    };

    BOOST_PP_REPEAT(BOOST_MPL_STRING_MAX_PARAMS, M0, ~)
    #undef M0

    template<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, int C)>
    struct string
    {
        /// INTERNAL ONLY
        enum
        {
            front_  = C0
          , back_   = BOOST_PP_CAT(C, BOOST_PP_DEC(BOOST_MPL_STRING_MAX_PARAMS))
        };

        typedef char        value_type;
        typedef string      type;
        typedef string_tag  tag;
    };

    namespace aux_
    {
        template<typename It, typename End>
        struct next_unless
          : mpl::next<It>
        {};

        template<typename End>
        struct next_unless<End, End>
        {
            typedef End type;
        };

        template<typename It, typename End>
        struct deref_unless
          : mpl::deref<It>
        {};

        template<typename End>
        struct deref_unless<End, End>
        {
            typedef mpl::char_<'\0'> type;
        };
    }

    template<typename Sequence>
    struct c_str
    {
        typedef typename mpl::end<Sequence>::type iend;
        typedef typename mpl::begin<Sequence>::type i0;
        #define M0(z, n, data)                                                                      \
        typedef                                                                                     \
            typename mpl::aux_::next_unless<BOOST_PP_CAT(i, n), iend>::type                         \
        BOOST_PP_CAT(i, BOOST_PP_INC(n));
        BOOST_PP_REPEAT(BOOST_MPL_LIMIT_STRING_SIZE, M0, ~)
        #undef M0

        typedef c_str type;
        static typename Sequence::value_type const value[BOOST_MPL_LIMIT_STRING_SIZE+1];
    };

    template<typename Sequence>
    typename Sequence::value_type const c_str<Sequence>::value[BOOST_MPL_LIMIT_STRING_SIZE+1] =
    {
        #define M0(z, n, data)                                                                      \
        mpl::aux_::deref_unless<BOOST_PP_CAT(i, n), iend>::type::value,
        BOOST_PP_REPEAT(BOOST_MPL_LIMIT_STRING_SIZE, M0, ~)
        #undef M0
        '\0'
    };

}} // namespace boost

#endif // BOOST_MPL_STRING_HPP_INCLUDED

/* string.hpp
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
*/