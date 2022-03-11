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