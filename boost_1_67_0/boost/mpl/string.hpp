
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
    template<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, int C), int J>                         \
    struct string_iterator<mpl::string<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, C)>, n, J>   \
    {                                                                                                 \
        enum { eomc_ = (BOOST_MPL_MULTICHAR_LENGTH(BOOST_PP_CAT(C, n)) == J + 1) };                   \
        typedef mpl::string<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, C)> string;             \
        typedef std::bidirectional_iterator_tag category;                                             \
        typedef                                                                                       \
            mpl::string_iterator<string, n + eomc_, eomc_ ? 0 : J + 1>                                \
        next;                                                                                         \
        typedef                                                                                       \
            mpl::string_iterator<string, n, J - 1>                                                    \
        prior;                                                                                        \
        typedef mpl::char_<BOOST_MPL_MULTICHAR_AT(BOOST_PP_CAT(C, n), J)> type;                       \
    };                                                                                                \
    template<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, int C)>                                \
    struct string_iterator<mpl::string<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, C)>, n, 0>   \
    {                                                                                                 \
        enum { eomc_ = (BOOST_MPL_MULTICHAR_LENGTH(BOOST_PP_CAT(C, n)) == 1) };                       \
        typedef mpl::string<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, C)> string;             \
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