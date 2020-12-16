
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
/rjjg/gBdyUYnwy3cXC50fL+pvR3tDJ975eMxOND/bfkxhaOD6UturaV4zO81Ki8rrnxef6xqPEZXma8t/InjQ+VsOyauOOD+BtXJhif4XSf7Daj5f1N6b/9TevSz99sJB4f6j9jcQvHh9I+4Is/PpC6EsfC7GlqcF6uOkeKHTgGksrMbXyTxq5l5eW0oLycVpSX3YLysltRXhaXNwgRJEXGShiv4Cwq2NKR8cv3855dVZJBCkjNAZwBgMNtJXeACprZ7znCI1U7eqkqKNyJPjIyi1KFRlOyd6BnQ0AqwK65vWX20Khc7pMBqmwn6URZy3ai7ITgmvP58/UkL+kCULwZxsonjGj7yqOrsX2uImFvOVVI43CstruS3PgWr+hdvdkoAvzJGyukQksrpBzx2ueKap+rte3rQO2TIzMJegBsod3uS6X/Sb4azlHGB1+klKLsdHVA05aFlZ4HqCa0jvWml7fkjA/4oLWimN9sIwoeS4QhYXpHS9JrLRqtHxlxbvssmbvHjEgw/nQl0LOUWwiLqytYHclU4LpFR4713C7lf/co9R+nMKhtS6wtYfL/VF8EnG/fF3O+DDTiq49dIJ1JjEOm/BPly53InzORnWWgjRCH7WZ79MGRdl9PSif6OpMUYxiWS7m6ukeVEbkGyw1spNifad7AFqoU2vz7IM4qTvOIvofEPFjSRaplYDQvFIdhI8hSNtXO1sUOAcsuutoiZDoUHhY+jsGihCVOkYK+QlvwD1URCY8K409bqIwe0b1g5Pkf6Xo3OW/6qnnzNG8Zw13UvDmPJ1Kr9lMKn2Ptn1L9UqNLJKAaisuMFNbeCpEghreIMAqJXnoJA6TMS6WH4DQo7zloTslUxaVGBz7YEGJoYAWOXsobWHvDzlYUVytFw86QCr5xJbJQYpedx93YyJ+gplM9rthtXHE/wyUvXHjtABmdMigCrkCWbgzkJSgYSmKGg46dCGFNDw1F9ZBh1ltOD+oLyo3AHEWGO2IYft9ZIuB+En1RlWwClrwh3SqBPMDi/7c4HbVriAnDD79GImR4+kEme13OtEFt2VjAOQiHu9XNImQzu3GbynawZaP88/3M80+6YGz86IImlTH0GYw7RJc5OFLqruxieB2strJKjXJvDGndFaYu1EoqhQcmQ6KH8SpHmx13/b2RmOgwMXEEus0lD2ACuWa33cIcImQSJ6pKQHRiR1078jBH/aBl1Dd0bHrU//yQHnVUk+1qYtTbLjZHvXsVj/qVQ2xsyfbV9HijvmsRkrZ4bT8SPz2+o2jqG1OfhoaxPO3EOpVKXF1drR1UghckHGgW3q1s7bDEv97NUiUj404MvDJA2hm9FJ6hpuLtWrVTc4Ugx7mNb/FOp9jbqOLh3YQg4ojjWedYjIUyjLsiZI73khkWtc58rsVtXM1ftf0UpyQo2ffIYawHkXNK1LoHWOtkA5yN6YteUFZHYTxF27xzSiQ5Pl2ZVU4PCdNOWO90YVfxQIM+Noh10RG+iuYC4obfpOxy1JMPjGfkAkQpzkSKeJ2Tx4ey6ANp7dTLqwj31il8bwIlpdRN5LMniZRX34AqWY3Rd5TU1y1bKr8a/z6ca81P4+eae831kgYco3j2GgAvN396QX/jTjmKDSrhtQv1sgT9VYf/qliPPkhMjOidTm0seyxGVH7f7FTm1EIl+y0DVE+ilxCQnvGGmE2yhUf2pskC931UpeK8izKgOVblQgiD6E6mMBlzBpInt2JZb/HPlP+QZN6oICGddQ9yPJY63X3UyPIVim4ztTrBA9BavOcw77/QDJMKG9KMMPU7MwV/F/FfPKFBwcd36SN4Xmm5gCAi8+GYxEVPyWFmRJ6GSYo=
*/