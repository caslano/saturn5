/*=============================================================================
    Copyright (c) 2012 Nathan Ridge

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEFINE_STRUCT_INLINE_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEFINE_STRUCT_INLINE_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/sequence/sequence_facade.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/fusion/algorithm/auxiliary/copy.hpp>
#include <boost/fusion/adapted/struct/detail/define_struct.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// MSVC and GCC <= 4.4 have a bug that affects partial specializations of
// nested templates under some circumstances. This affects the implementation
// of BOOST_FUSION_DEFINE_STRUCT_INLINE, which uses such specializations for
// the iterator class's 'deref' and 'value_of' metafunctions. On these compilers
// an alternate implementation for these metafunctions is used that does not 
// require such specializations. The alternate implementation takes longer
// to compile so its use is restricted to the offending compilers.
// For MSVC, the bug was reported at https://connect.microsoft.com/VisualStudio/feedback/details/757891/c-compiler-error-involving-partial-specializations-of-nested-templates
// For GCC, 4.4 and earlier are no longer maintained so there is no need
// to report a bug.
#if defined(BOOST_MSVC) || (defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 4)))
    #define BOOST_FUSION_NEED_NESTED_TEMPLATE_PARTIAL_SPEC_WKND 
#endif

#ifdef BOOST_FUSION_NEED_NESTED_TEMPLATE_PARTIAL_SPEC_WKND
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/if.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/container/vector.hpp>
#endif


#define BOOST_FUSION_MAKE_DEFAULT_INIT_LIST_ENTRY(R, DATA, N, ATTRIBUTE)        \
    BOOST_PP_COMMA_IF(N) BOOST_PP_TUPLE_ELEM(2, 1, ATTRIBUTE)()

#define BOOST_FUSION_MAKE_DEFAULT_INIT_LIST(ATTRIBUTES_SEQ)                     \
            : BOOST_PP_SEQ_FOR_EACH_I(                                          \
              BOOST_FUSION_MAKE_DEFAULT_INIT_LIST_ENTRY,                        \
              ~,                                                                \
              ATTRIBUTES_SEQ)                                                   \

#define BOOST_FUSION_IGNORE_2(ARG1, ARG2)

#define BOOST_FUSION_MAKE_COPY_CONSTRUCTOR(NAME, ATTRIBUTES_SEQ)                \
    BOOST_FUSION_GPU_ENABLED                                                    \
    NAME(BOOST_PP_SEQ_FOR_EACH_I(                                               \
            BOOST_FUSION_MAKE_CONST_REF_PARAM,                                  \
            ~,                                                                  \
            ATTRIBUTES_SEQ))                                                    \
        : BOOST_PP_SEQ_FOR_EACH_I(                                              \
              BOOST_FUSION_MAKE_INIT_LIST_ENTRY,                                \
              ~,                                                                \
              ATTRIBUTES_SEQ)                                                   \
    {                                                                           \
    }                                                                           \

#define BOOST_FUSION_MAKE_CONST_REF_PARAM(R, DATA, N, ATTRIBUTE)                \
    BOOST_PP_COMMA_IF(N)                                                        \
    BOOST_PP_TUPLE_ELEM(2, 0, ATTRIBUTE) const&                                 \
    BOOST_PP_TUPLE_ELEM(2, 1, ATTRIBUTE)

#define BOOST_FUSION_MAKE_INIT_LIST_ENTRY_I(NAME) NAME(NAME)

#define BOOST_FUSION_MAKE_INIT_LIST_ENTRY(R, DATA, N, ATTRIBUTE)                \
    BOOST_PP_COMMA_IF(N)                                                        \
    BOOST_FUSION_MAKE_INIT_LIST_ENTRY_I(BOOST_PP_TUPLE_ELEM(2, 1, ATTRIBUTE))

#define BOOST_FUSION_ITERATOR_NAME(NAME)                                        \
    BOOST_PP_CAT(boost_fusion_detail_, BOOST_PP_CAT(NAME, _iterator))

// Note: all template parameter names need to be uglified, otherwise they might
//       shadow a template parameter of the struct when used with
//       BOOST_FUSION_DEFINE_TPL_STRUCT_INLINE

#define BOOST_FUSION_MAKE_ITERATOR_VALUE_OF_SPECS(Z, N, NAME)                   \
    template <typename boost_fusion_detail_Sq>                                  \
    struct value_of<                                                            \
               BOOST_FUSION_ITERATOR_NAME(NAME)<boost_fusion_detail_Sq, N>      \
           >                                                                    \
        : boost::mpl::identity<                                                 \
              typename boost_fusion_detail_Sq::t##N##_type                      \
          >                                                                     \
    {                                                                           \
    };

#define BOOST_FUSION_MAKE_ITERATOR_DEREF_SPEC(                                  \
    SPEC_TYPE, CALL_ARG_TYPE, TYPE_QUAL, ATTRIBUTE, N)                          \
                                                                                \
    template <typename boost_fusion_detail_Sq>                                  \
    struct deref<SPEC_TYPE, N> >                                                \
    {                                                                           \
        typedef typename boost_fusion_detail_Sq::t##N##_type TYPE_QUAL& type;   \
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                                \
        static type call(CALL_ARG_TYPE, N> const& iter)                         \
        {                                                                       \
            return iter.seq_.BOOST_PP_TUPLE_ELEM(2, 1, ATTRIBUTE);              \
        }                                                                       \
    };

#define BOOST_FUSION_MAKE_ITERATOR_DEREF_SPECS(R, NAME, N, ATTRIBUTE)           \
    BOOST_FUSION_MAKE_ITERATOR_DEREF_SPEC(                                      \
        BOOST_FUSION_ITERATOR_NAME(NAME)<boost_fusion_detail_Sq,                \
        BOOST_FUSION_ITERATOR_NAME(NAME)<boost_fusion_detail_Sq,                \
        ,                                                                       \
        ATTRIBUTE,                                                              \
        N)                                                                      \
    BOOST_FUSION_MAKE_ITERATOR_DEREF_SPEC(                                      \
        BOOST_FUSION_ITERATOR_NAME(NAME)<const boost_fusion_detail_Sq,          \
        BOOST_FUSION_ITERATOR_NAME(NAME)<const boost_fusion_detail_Sq,          \
        const,                                                                  \
        ATTRIBUTE,                                                              \
        N)                                                                      \
    BOOST_FUSION_MAKE_ITERATOR_DEREF_SPEC(                                      \
        const BOOST_FUSION_ITERATOR_NAME(NAME)<boost_fusion_detail_Sq,          \
        BOOST_FUSION_ITERATOR_NAME(NAME)<boost_fusion_detail_Sq,                \
        ,                                                                       \
        ATTRIBUTE,                                                              \
        N)                                                                      \
    BOOST_FUSION_MAKE_ITERATOR_DEREF_SPEC(                                      \
        const BOOST_FUSION_ITERATOR_NAME(NAME)<const boost_fusion_detail_Sq,    \
        BOOST_FUSION_ITERATOR_NAME(NAME)<const boost_fusion_detail_Sq,          \
        const,                                                                  \
        ATTRIBUTE,                                                              \
        N)                                                                      \

#define BOOST_FUSION_MAKE_VALUE_AT_SPECS(Z, N, DATA)                            \
    template <typename boost_fusion_detail_Sq>                                  \
    struct value_at<boost_fusion_detail_Sq, boost::mpl::int_<N> >               \
    {                                                                           \
        typedef typename boost_fusion_detail_Sq::t##N##_type type;              \
    };

#define BOOST_FUSION_MAKE_AT_SPECS(R, DATA, N, ATTRIBUTE)                       \
    template <typename boost_fusion_detail_Sq>                                  \
    struct at<boost_fusion_detail_Sq, boost::mpl::int_<N> >                     \
    {                                                                           \
        typedef typename boost::mpl::if_<                                       \
            boost::is_const<boost_fusion_detail_Sq>,                            \
            typename boost_fusion_detail_Sq::t##N##_type const&,                \
            typename boost_fusion_detail_Sq::t##N##_type&                       \
        >::type type;                                                           \
                                                                                \
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                                \
        static type call(boost_fusion_detail_Sq& sq)                            \
        {                                                                       \
            return sq. BOOST_PP_TUPLE_ELEM(2, 1, ATTRIBUTE);                    \
        }                                                                       \
    };

#define BOOST_FUSION_MAKE_TYPEDEF(R, DATA, N, ATTRIBUTE)                        \
    typedef BOOST_PP_TUPLE_ELEM(2, 0, ATTRIBUTE) t##N##_type;

#define BOOST_FUSION_MAKE_DATA_MEMBER(R, DATA, N, ATTRIBUTE)                    \
    BOOST_PP_TUPLE_ELEM(2, 0, ATTRIBUTE) BOOST_PP_TUPLE_ELEM(2, 1, ATTRIBUTE);

#ifdef BOOST_FUSION_NEED_NESTED_TEMPLATE_PARTIAL_SPEC_WKND

#define BOOST_FUSION_DEFINE_ITERATOR_VALUE_OF(NAME, ATTRIBUTE_SEQ_SIZE)         \
        template <typename boost_fusion_detail_Iterator>                        \
        struct value_of : boost::fusion::result_of::at_c<                       \
                              ref_vec_t,                                        \
                              boost_fusion_detail_Iterator::index::value        \
                          >                                                     \
        {                                                                       \
        };

#define BOOST_FUSION_DEFINE_ITERATOR_DEREF(NAME, ATTRIBUTES_SEQ)                \
        template <typename boost_fusion_detail_Iterator>                        \
        struct deref                                                            \
        {                                                                       \
            typedef typename boost::remove_const<                               \
                boost_fusion_detail_Iterator                                    \
            >::type iterator_raw_type;                                          \
                                                                                \
            static const int index = iterator_raw_type::index::value;           \
                                                                                \
            typedef typename boost::fusion::result_of::at_c<                    \
                ref_vec_t,                                                      \
                index                                                           \
            >::type result_raw_type;                                            \
                                                                                \
            typedef typename boost::mpl::if_<                                   \
                boost::is_const<typename iterator_raw_type::sequence_type>,     \
                typename boost::add_const<result_raw_type>::type,               \
                result_raw_type                                                 \
            >::type type;                                                       \
                                                                                \
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                            \
            static type call(iterator_raw_type const& iter)                     \
            {                                                                   \
                return boost::fusion::at_c<index>(iter.ref_vec);                \
            }                                                                   \
        };

#define BOOST_FUSION_MAKE_ITERATOR_WKND_FIELD_NAME(R, DATA, N, ATTRIBUTE)       \
        BOOST_PP_COMMA_IF(N) seq.BOOST_PP_TUPLE_ELEM(2, 1, ATTRIBUTE)

#define BOOST_FUSION_DEFINE_ITERATOR_WKND_INIT_LIST_ENTRIES(ATTRIBUTES_SEQ)     \
        , ref_vec(BOOST_PP_SEQ_FOR_EACH_I(                                      \
                          BOOST_FUSION_MAKE_ITERATOR_WKND_FIELD_NAME,           \
                          ~,                                                    \
                          BOOST_PP_SEQ_TAIL(ATTRIBUTES_SEQ)))

#define BOOST_FUSION_MAKE_ITERATOR_WKND_REF(Z, N, DATA)                         \
        BOOST_PP_COMMA_IF(N)                                                    \
        typename boost::mpl::if_<                                               \
                boost::is_const<boost_fusion_detail_Seq>,                       \
                typename boost::add_const<                                      \
                        typename boost_fusion_detail_Seq::t##N##_type           \
                >::type,                                                        \
                typename boost_fusion_detail_Seq::t##N##_type                   \
        >::type&

#define BOOST_FUSION_DEFINE_ITERATOR_WKND_MEMBERS(ATTRIBUTES_SEQ_SIZE)          \
        typedef boost::fusion::vector<                                          \
            BOOST_PP_REPEAT(                                                    \
                    ATTRIBUTES_SEQ_SIZE,                                        \
                    BOOST_FUSION_MAKE_ITERATOR_WKND_REF,                        \
                    ~)                                                          \
        > ref_vec_t;                                                            \
                                                                                \
        ref_vec_t ref_vec;

#else

#define BOOST_FUSION_DEFINE_ITERATOR_VALUE_OF(NAME, ATTRIBUTES_SEQ_SIZE)        \
        template <typename boost_fusion_detail_T> struct value_of;              \
        BOOST_PP_REPEAT(                                                        \
            ATTRIBUTES_SEQ_SIZE,                                                \
            BOOST_FUSION_MAKE_ITERATOR_VALUE_OF_SPECS,                          \
            NAME)

#define BOOST_FUSION_DEFINE_ITERATOR_DEREF(NAME, ATTRIBUTES_SEQ)                \
        template <typename boost_fusion_detail_T> struct deref;                 \
        BOOST_PP_SEQ_FOR_EACH_I(                                                \
            BOOST_FUSION_MAKE_ITERATOR_DEREF_SPECS,                             \
            NAME,                                                               \
            ATTRIBUTES_SEQ)

#define BOOST_FUSION_DEFINE_ITERATOR_WKND_INIT_LIST_ENTRIES(ATTRIBUTES_SEQ)

#define BOOST_FUSION_DEFINE_ITERATOR_WKND_MEMBERS(ATTRIBUTES_SEQ_SIZE)

#endif  // BOOST_FUSION_NEED_NESTED_TEMPLATE_PARTIAL_SPEC_WKND

// Note: We can't nest the iterator inside the struct because we run into
//       a MSVC10 bug involving partial specializations of nested templates.

#define BOOST_FUSION_DEFINE_STRUCT_INLINE_IMPL(NAME, ATTRIBUTES)                \
    BOOST_FUSION_DEFINE_STRUCT_INLINE_ITERATOR(NAME, ATTRIBUTES)                \
    struct NAME : boost::fusion::sequence_facade<                               \
                      NAME,                                                     \
                      boost::fusion::random_access_traversal_tag                \
                  >                                                             \
    {                                                                           \
        BOOST_FUSION_DEFINE_STRUCT_INLINE_MEMBERS(NAME, ATTRIBUTES)             \
    };

#define BOOST_FUSION_DEFINE_TPL_STRUCT_INLINE_IMPL(                             \
    TEMPLATE_PARAMS_SEQ, NAME, ATTRIBUTES)                                      \
                                                                                \
    BOOST_FUSION_DEFINE_STRUCT_INLINE_ITERATOR(NAME, ATTRIBUTES)                \
                                                                                \
    template <                                                                  \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS_IMPL(                  \
            (0)TEMPLATE_PARAMS_SEQ)                                             \
    >                                                                           \
    struct NAME : boost::fusion::sequence_facade<                               \
                      NAME<                                                     \
                          BOOST_PP_SEQ_ENUM(TEMPLATE_PARAMS_SEQ)                \
                      >,                                                        \
                      boost::fusion::random_access_traversal_tag                \
                  >                                                             \
    {                                                                           \
        BOOST_FUSION_DEFINE_STRUCT_INLINE_MEMBERS(NAME, ATTRIBUTES)             \
    };

#define BOOST_FUSION_DEFINE_STRUCT_INLINE_MEMBERS(NAME, ATTRIBUTES)             \
    BOOST_FUSION_DEFINE_STRUCT_MEMBERS_IMPL(                                    \
        NAME,                                                                   \
        BOOST_PP_CAT(BOOST_FUSION_DEFINE_STRUCT_FILLER_0 ATTRIBUTES,_END))

// Note: can't compute BOOST_PP_SEQ_SIZE(ATTRIBUTES_SEQ) directly because
//       ATTRIBUTES_SEQ may be empty and calling BOOST_PP_SEQ_SIZE on an empty
//       sequence produces warnings on MSVC.
#define BOOST_FUSION_DEFINE_STRUCT_MEMBERS_IMPL(NAME, ATTRIBUTES_SEQ)           \
    BOOST_FUSION_DEFINE_STRUCT_INLINE_MEMBERS_IMPL_IMPL(                        \
        NAME,                                                                   \
        ATTRIBUTES_SEQ,                                                         \
        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE((0)ATTRIBUTES_SEQ)))

#define BOOST_FUSION_DEFINE_STRUCT_INLINE_ITERATOR(NAME, ATTRIBUTES)            \
    BOOST_FUSION_DEFINE_STRUCT_ITERATOR_IMPL(                                   \
        NAME,                                                                   \
        BOOST_PP_CAT(BOOST_FUSION_DEFINE_STRUCT_FILLER_0 ATTRIBUTES,_END))

#define BOOST_FUSION_DEFINE_STRUCT_ITERATOR_IMPL(NAME, ATTRIBUTES_SEQ)          \
    BOOST_FUSION_DEFINE_STRUCT_INLINE_ITERATOR_IMPL_IMPL(                       \
        NAME,                                                                   \
        ATTRIBUTES_SEQ,                                                         \
        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE((0)ATTRIBUTES_SEQ)))

#define BOOST_FUSION_DEFINE_STRUCT_INLINE_ITERATOR_IMPL_IMPL(                   \
    NAME, ATTRIBUTES_SEQ, ATTRIBUTES_SEQ_SIZE)                                  \
                                                                                \
    template <typename boost_fusion_detail_Seq, int N>                          \
    struct BOOST_FUSION_ITERATOR_NAME(NAME)                                     \
        : boost::fusion::iterator_facade<                                       \
              BOOST_FUSION_ITERATOR_NAME(NAME)<boost_fusion_detail_Seq, N>,     \
              boost::fusion::random_access_traversal_tag                        \
          >                                                                     \
    {                                                                           \
        typedef boost::mpl::int_<N> index;                                      \
        typedef boost_fusion_detail_Seq sequence_type;                          \
                                                                                \
        BOOST_FUSION_GPU_ENABLED                                                \
        BOOST_FUSION_ITERATOR_NAME(NAME)(boost_fusion_detail_Seq& seq)          \
            : seq_(seq)                                                         \
              BOOST_FUSION_DEFINE_ITERATOR_WKND_INIT_LIST_ENTRIES(              \
                      (0)ATTRIBUTES_SEQ)                                        \
        {}                                                                      \
                                                                                \
        boost_fusion_detail_Seq& seq_;                                          \
                                                                                \
        BOOST_FUSION_DEFINE_ITERATOR_WKND_MEMBERS(ATTRIBUTES_SEQ_SIZE)          \
                                                                                \
        BOOST_FUSION_DEFINE_ITERATOR_VALUE_OF(NAME, ATTRIBUTES_SEQ_SIZE)        \
                                                                                \
        BOOST_FUSION_DEFINE_ITERATOR_DEREF(NAME, ATTRIBUTES_SEQ)                \
                                                                                \
        template <typename boost_fusion_detail_It>                              \
        struct next                                                             \
        {                                                                       \
            typedef BOOST_FUSION_ITERATOR_NAME(NAME)<                           \
                typename boost_fusion_detail_It::sequence_type,                 \
                boost_fusion_detail_It::index::value + 1                        \
            > type;                                                             \
                                                                                \
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                            \
            static type call(boost_fusion_detail_It const& it)                  \
            {                                                                   \
                return type(it.seq_);                                           \
            }                                                                   \
        };                                                                      \
                                                                                \
        template <typename boost_fusion_detail_It>                              \
        struct prior                                                            \
        {                                                                       \
            typedef BOOST_FUSION_ITERATOR_NAME(NAME)<                           \
                typename boost_fusion_detail_It::sequence_type,                 \
                boost_fusion_detail_It::index::value - 1                        \
            > type;                                                             \
                                                                                \
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                            \
            static type call(boost_fusion_detail_It const& it)                  \
            {                                                                   \
                return type(it.seq_);                                           \
            }                                                                   \
        };                                                                      \
                                                                                \
        template <                                                              \
            typename boost_fusion_detail_It1,                                   \
            typename boost_fusion_detail_It2                                    \
        >                                                                       \
        struct distance                                                         \
        {                                                                       \
            typedef typename boost::mpl::minus<                                 \
                typename boost_fusion_detail_It2::index,                        \
                typename boost_fusion_detail_It1::index                         \
            >::type type;                                                       \
                                                                                \
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                            \
            static type call(boost_fusion_detail_It1 const& /* it1 */,          \
                             boost_fusion_detail_It2 const& /* it2 */)          \
            {                                                                   \
                return type();                                                  \
            }                                                                   \
        };                                                                      \
                                                                                \
        template <                                                              \
            typename boost_fusion_detail_It,                                    \
            typename boost_fusion_detail_M                                      \
        >                                                                       \
        struct advance                                                          \
        {                                                                       \
            typedef BOOST_FUSION_ITERATOR_NAME(NAME)<                           \
                typename boost_fusion_detail_It::sequence_type,                 \
                boost_fusion_detail_It::index::value                            \
                    + boost_fusion_detail_M::value                              \
            > type;                                                             \
                                                                                \
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                            \
            static type call(boost_fusion_detail_It const& it)                  \
            {                                                                   \
                return type(it.seq_);                                           \
            }                                                                   \
        };                                                                      \
    };


#define BOOST_FUSION_DEFINE_STRUCT_INLINE_MEMBERS_IMPL_IMPL(                    \
    NAME, ATTRIBUTES_SEQ, ATTRIBUTES_SEQ_SIZE)                                  \
                                                                                \
    NAME()                                                                      \
        BOOST_PP_IF(ATTRIBUTES_SEQ_SIZE,                                        \
            BOOST_FUSION_MAKE_DEFAULT_INIT_LIST,                                \
            BOOST_PP_EMPTY)(ATTRIBUTES_SEQ)                                     \
    {                                                                           \
    }                                                                           \
                                                                                \
    BOOST_PP_IF(                                                                \
        ATTRIBUTES_SEQ_SIZE,                                                    \
        BOOST_FUSION_MAKE_COPY_CONSTRUCTOR,                                     \
        BOOST_FUSION_IGNORE_2)                                                  \
            (NAME, ATTRIBUTES_SEQ)                                              \
                                                                                \
    template <typename boost_fusion_detail_Seq>                                 \
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED                              \
    NAME(const boost_fusion_detail_Seq& rhs)                                    \
    {                                                                           \
        boost::fusion::copy(rhs, *this);                                        \
    }                                                                           \
                                                                                \
    template <typename boost_fusion_detail_Seq>                                 \
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED                              \
    NAME& operator=(const boost_fusion_detail_Seq& rhs)                         \
    {                                                                           \
        boost::fusion::copy(rhs, *this);                                        \
        return *this;                                                           \
    }                                                                           \
                                                                                \
    template <typename boost_fusion_detail_Sq>                                  \
    struct begin                                                                \
    {                                                                           \
        typedef BOOST_FUSION_ITERATOR_NAME(NAME)<boost_fusion_detail_Sq, 0>     \
             type;                                                              \
                                                                                \
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                                \
        static type call(boost_fusion_detail_Sq& sq)                            \
        {                                                                       \
            return type(sq);                                                    \
        }                                                                       \
    };                                                                          \
                                                                                \
    template <typename boost_fusion_detail_Sq>                                  \
    struct end                                                                  \
    {                                                                           \
        typedef BOOST_FUSION_ITERATOR_NAME(NAME)<                               \
            boost_fusion_detail_Sq,                                             \
            ATTRIBUTES_SEQ_SIZE                                                 \
        > type;                                                                 \
                                                                                \
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                                \
        static type call(boost_fusion_detail_Sq& sq)                            \
        {                                                                       \
            return type(sq);                                                    \
        }                                                                       \
    };                                                                          \
                                                                                \
    template <typename boost_fusion_detail_Sq>                                  \
    struct size : boost::mpl::int_<ATTRIBUTES_SEQ_SIZE>                         \
    {                                                                           \
    };                                                                          \
                                                                                \
    template <typename boost_fusion_detail_Sq>                                  \
    struct empty : boost::mpl::bool_<ATTRIBUTES_SEQ_SIZE == 0>                  \
    {                                                                           \
    };                                                                          \
                                                                                \
    template <                                                                  \
        typename boost_fusion_detail_Sq,                                        \
        typename boost_fusion_detail_N                                          \
    >                                                                           \
    struct value_at : value_at<                                                 \
                          boost_fusion_detail_Sq,                               \
                          boost::mpl::int_<boost_fusion_detail_N::value>        \
                      >                                                         \
    {                                                                           \
    };                                                                          \
                                                                                \
    BOOST_PP_REPEAT(                                                            \
        ATTRIBUTES_SEQ_SIZE,                                                    \
        BOOST_FUSION_MAKE_VALUE_AT_SPECS,                                       \
        ~)                                                                      \
                                                                                \
    template <                                                                  \
        typename boost_fusion_detail_Sq,                                        \
        typename boost_fusion_detail_N                                          \
    >                                                                           \
    struct at : at<                                                             \
                    boost_fusion_detail_Sq,                                     \
                    boost::mpl::int_<boost_fusion_detail_N::value>              \
                >                                                               \
    {                                                                           \
    };                                                                          \
                                                                                \
    BOOST_PP_SEQ_FOR_EACH_I(BOOST_FUSION_MAKE_AT_SPECS, ~, ATTRIBUTES_SEQ)      \
                                                                                \
    BOOST_PP_SEQ_FOR_EACH_I(BOOST_FUSION_MAKE_TYPEDEF, ~, ATTRIBUTES_SEQ)       \
                                                                                \
    BOOST_PP_SEQ_FOR_EACH_I(                                                    \
        BOOST_FUSION_MAKE_DATA_MEMBER,                                          \
        ~,                                                                      \
        ATTRIBUTES_SEQ)

#endif

/* define_struct_inline.hpp
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
*/