#ifndef BOOST_RANGE_DETAIL_MICROSOFT_HPP
#define BOOST_RANGE_DETAIL_MICROSOFT_HPP

// Boost.Range MFC/ATL Extension
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)




// config
//


#include <boost/range/iterator.hpp>


#define BOOST_RANGE_DETAIL_MICROSOFT_RANGE_VERSION_1 1


#if !defined(BOOST_RANGE_DETAIL_MICROSOFT_RANGE_VERSION_1)
    #define BOOST_RANGE_DETAIL_MICROSOFT_range_mutable_iterator range_mutable_iterator
    #define BOOST_RANGE_DETAIL_MICROSOFT_range_begin            range_begin
    #define BOOST_RANGE_DETAIL_MICROSOFT_range_end              range_end
#else
    #define BOOST_RANGE_DETAIL_MICROSOFT_range_mutable_iterator range_mutable_iterator
    #define BOOST_RANGE_DETAIL_MICROSOFT_range_begin            range_begin
    #define BOOST_RANGE_DETAIL_MICROSOFT_range_end              range_end
#endif




// yet another customization way
//


#include <boost/iterator/iterator_traits.hpp> // iterator_difference
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/detail/is_unary.hpp>
#include <boost/preprocessor/list/for_each.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/size_type.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/enable_if.hpp> // disable_if
#include <boost/next_prior.hpp>

#if !defined(BOOST_RANGE_DETAIL_MICROSOFT_RANGE_VERSION_1)
    #include <boost/range/mutable_iterator.hpp>
#else
    #include <iterator> // distance
    #include <boost/range/begin.hpp>
    #include <boost/range/end.hpp>
    #include <boost/range/iterator.hpp>
#endif


namespace boost { namespace range_detail_microsoft {


    // customization point
    //

    template< class Tag >
    struct customization;


    template< class T >
    struct customization_tag;


    struct using_type_as_tag
    { };


    // Topic:
    // In fact, it is unnecessary for VC++.
    // VC++'s behavior seems conforming, while GCC fails without this.
    template< class Iterator, class T >
    struct mutable_ :
        disable_if< is_const<T>, Iterator >
    { };


    // helpers
    //

    template< class Tag, class T >
    struct customization_tag_of
    {
        typedef typename mpl::if_< is_same<using_type_as_tag, Tag>,
            T,
            Tag
        >::type type;
    };


    template< class T >
    struct customization_of
    {
        typedef typename remove_cv<T>::type bare_t;
        typedef typename customization_tag<bare_t>::type tag_t;
        typedef customization<tag_t> type;
    };


    template< class T >
    struct mutable_iterator_of
    {
        typedef typename remove_cv<T>::type bare_t;
        typedef typename customization_of<bare_t>::type cust_t;
        typedef typename cust_t::template meta<bare_t>::mutable_iterator type;
    };


    template< class T >
    struct const_iterator_of
    {
        typedef typename remove_cv<T>::type bare_t;
        typedef typename customization_of<bare_t>::type cust_t;
        typedef typename cust_t::template meta<bare_t>::const_iterator type;
    };


    template< class T >
    struct size_type_of
    {
        typedef typename range_detail_microsoft::mutable_iterator_of<T>::type miter_t;
        typedef typename iterator_difference<miter_t>::type type;
    };


    template< class T > inline
    typename mutable_iterator_of<T>::type
    begin_of(T& x)
    {
        typedef typename customization_of<T>::type cust_t;
        return cust_t().template begin<typename mutable_iterator_of<T>::type>(x);
    }


    template< class T > inline
    typename const_iterator_of<T>::type
    begin_of(T const& x)
    {
        typedef typename customization_of<T>::type cust_t;
        return cust_t().template begin<typename const_iterator_of<T>::type>(x);
    }


    template< class T > inline
    typename mutable_iterator_of<T>::type
    end_of(T& x)
    {
        typedef typename customization_of<T>::type cust_t;
        return cust_t().template end<typename mutable_iterator_of<T>::type>(x);
    }


    template< class T > inline
    typename const_iterator_of<T>::type
    end_of(T const& x)
    {
        typedef typename customization_of<T>::type cust_t;
        return cust_t().template end<typename const_iterator_of<T>::type>(x);
    }


#if defined(BOOST_RANGE_DETAIL_MICROSOFT_RANGE_VERSION_1)

    template< class T > inline
    typename size_type_of<T>::type
    size_of(T const& x)
    {
        return std::distance(boost::begin(x), boost::end(x));
    }

#endif


    template< class Range >
    struct compatible_mutable_iterator : 
        BOOST_RANGE_DETAIL_MICROSOFT_range_mutable_iterator<Range>
    { };


} } // namespace boost::range_detail_microsoft


#define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_namespace_open(NamespaceList) \
    BOOST_PP_LIST_FOR_EACH(BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_namespace_open_op, ~, NamespaceList) \
/**/

    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_namespace_open_op(r, data, elem) \
        namespace elem { \
    /**/


#define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_namespace_close(NamespaceList) \
    BOOST_PP_LIST_FOR_EACH(BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_namespace_close_op, ~, NamespaceList) \
/**/

    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_namespace_close_op(r, data, elem) \
        } \
    /**/


#define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_namespace_expand_op(r, data, elem) \
    :: elem \
/**/


#define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(Tag, NamespaceList, Name) \
    namespace boost { namespace range_detail_microsoft { \
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_tag(Tag, BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_fullname(NamespaceList, Name)) \
    } } \
    \
    namespace boost { \
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_mutable_iterator(BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_fullname(NamespaceList, Name)) \
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_const_iterator(BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_fullname(NamespaceList, Name)) \
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_size_type(BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_fullname(NamespaceList, Name)) \
    } \
    \
    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_namespace_open(NamespaceList) \
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_begin(BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_fullname(NamespaceList, Name)) \
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_begin_const(BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_fullname(NamespaceList, Name)) \
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_end(BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_fullname(NamespaceList, Name)) \
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_end_const(BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_fullname(NamespaceList, Name)) \
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_size(BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_fullname(NamespaceList, Name)) \
    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_namespace_close(NamespaceList) \
/**/


    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_fullname(NamespaceList, Name) \
        BOOST_PP_LIST_FOR_EACH(BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_namespace_expand_op, ~, NamespaceList) :: Name \
    /**/


    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_tag(Tag, Fullname) \
        template< > \
        struct customization_tag< Fullname > : \
            customization_tag_of< Tag, Fullname > \
        { }; \
    /**/


    // metafunctions
    //

    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_mutable_iterator(Fullname) \
        template< > \
        struct BOOST_RANGE_DETAIL_MICROSOFT_range_mutable_iterator< Fullname > : \
            range_detail_microsoft::mutable_iterator_of< Fullname > \
        { }; \
    /**/


    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_const_iterator(Fullname) \
        template< > \
        struct range_const_iterator< Fullname > : \
            range_detail_microsoft::const_iterator_of< Fullname > \
        { }; \
    /**/


    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_size_type(Fullname) \
        template< > \
        struct range_size< Fullname > : \
            range_detail_microsoft::size_type_of< Fullname > \
        { }; \
    /**/


    // functions
    //

    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_begin(Fullname) \
        inline \
        boost::range_detail_microsoft::mutable_iterator_of< Fullname >::type \
        BOOST_RANGE_DETAIL_MICROSOFT_range_begin(Fullname& x) \
        { \
            return boost::range_detail_microsoft::begin_of(x); \
        } \
    /**/


    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_begin_const(Fullname) \
        inline \
        boost::range_detail_microsoft::const_iterator_of< Fullname >::type \
        BOOST_RANGE_DETAIL_MICROSOFT_range_begin(Fullname const& x) \
        { \
            return boost::range_detail_microsoft::begin_of(x); \
        } \
    /**/


    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_end(Fullname) \
        inline \
        boost::range_detail_microsoft::mutable_iterator_of< Fullname >::type \
        BOOST_RANGE_DETAIL_MICROSOFT_range_end(Fullname& x) \
        { \
            return boost::range_detail_microsoft::end_of(x); \
        } \
    /**/


    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_end_const(Fullname) \
        inline \
        boost::range_detail_microsoft::const_iterator_of< Fullname >::type \
        BOOST_RANGE_DETAIL_MICROSOFT_range_end(Fullname const& x) \
        { \
            return boost::range_detail_microsoft::end_of(x); \
        } \
    /**/


    #if !defined(BOOST_RANGE_DETAIL_MICROSOFT_RANGE_VERSION_1)

        #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_size(Fullname) \
        /**/

    #else

        #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE_size(Fullname) \
            inline \
            boost::range_detail_microsoft::size_type_of< Fullname >::type \
            boost_range_size(Fullname const& x) \
            { \
                return boost::range_detail_microsoft::size_of(x); \
            } \
        /**/

    #endif


#define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(Tag, NamespaceList, Name, ParamSeqOrCount) \
    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_impl( \
        Tag, NamespaceList, Name, \
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_to_param_seq(ParamSeqOrCount) \
    ) \
/**/

    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_to_param_seq(ParamSeqOrCount) \
        BOOST_PP_IIF(BOOST_PP_IS_UNARY(ParamSeqOrCount), \
            ParamSeqOrCount BOOST_PP_TUPLE_EAT(3), \
            BOOST_PP_REPEAT \
        )(ParamSeqOrCount, BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_to_param_seq_op, ~) \
    /**/

        #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_to_param_seq_op(z, n, _) \
            (class) \
        /**/


#define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_impl(Tag, NamespaceList, Name, ParamSeq) \
    namespace boost { namespace range_detail_microsoft { \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_tag( \
            Tag, \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_params(ParamSeq), \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
    } } \
    \
    namespace boost { \
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_mutable_iterator( \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_params(ParamSeq), \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_const_iterator( \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_params(ParamSeq), \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
        \
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_size_type( \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_params(ParamSeq), \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
    } \
    \
    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_namespace_open(NamespaceList) \
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_begin( \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_params(ParamSeq), \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_begin_const( \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_params(ParamSeq), \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_end( \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_params(ParamSeq), \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_end_const( \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_params(ParamSeq), \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_size( \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_params(ParamSeq), \
            BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_namespace_close(NamespaceList) \
/**/


    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_params(ParamSeq) \
        BOOST_PP_SEQ_FOR_EACH_I(BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_params_op, ~, ParamSeq) \
    /**/

        #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_params_op(r, data, i, elem) \
            BOOST_PP_COMMA_IF(i) elem BOOST_PP_CAT(T, i) \
        /**/


    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        BOOST_PP_LIST_FOR_EACH(BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_namespace_expand_op, ~, NamespaceList) \
        :: Name < BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(ParamSeq), T) > \
    /**/


    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_tag(Tag, Params, Fullname) \
        template< Params > \
        struct customization_tag< Fullname > : \
            customization_tag_of< Tag, Fullname > \
        { }; \
    /**/


    // metafunctions
    //

    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_mutable_iterator(Params, Fullname) \
        template< Params > \
        struct BOOST_RANGE_DETAIL_MICROSOFT_range_mutable_iterator< Fullname > : \
            range_detail_microsoft::mutable_iterator_of< Fullname > \
        { }; \
    /**/


    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_const_iterator(Params, Fullname) \
        template< Params > \
        struct range_const_iterator< Fullname > : \
            range_detail_microsoft::const_iterator_of< Fullname > \
        { }; \
    /**/


    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_size_type(Params, Fullname) \
        template< Params > \
        struct range_size< Fullname > : \
            range_detail_microsoft::size_type_of< Fullname > \
        { }; \
    /**/


    // functions
    //

    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_begin(Params, Fullname) \
        template< Params > inline \
        typename boost::range_detail_microsoft::mutable_iterator_of< Fullname >::type \
        BOOST_RANGE_DETAIL_MICROSOFT_range_begin(Fullname& x) \
        { \
            return boost::range_detail_microsoft::begin_of(x); \
        } \
    /**/


    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_begin_const(Params, Fullname) \
        template< Params > inline \
        typename boost::range_detail_microsoft::const_iterator_of< Fullname >::type \
        BOOST_RANGE_DETAIL_MICROSOFT_range_begin(Fullname const& x) \
        { \
            return boost::range_detail_microsoft::begin_of(x); \
        } \
    /**/


    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_end(Params, Fullname) \
        template< Params > inline \
        typename boost::range_detail_microsoft::mutable_iterator_of< Fullname >::type \
        BOOST_RANGE_DETAIL_MICROSOFT_range_end(Fullname& x) \
        { \
            return boost::range_detail_microsoft::end_of(x); \
        } \
    /**/


    #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_end_const(Params, Fullname) \
        template< Params > inline \
        typename boost::range_detail_microsoft::const_iterator_of< Fullname >::type \
        BOOST_RANGE_DETAIL_MICROSOFT_range_end(Fullname const& x) \
        { \
            return boost::range_detail_microsoft::end_of(x); \
        } \
    /**/


    #if !defined(BOOST_RANGE_DETAIL_MICROSOFT_RANGE_VERSION_1)

        #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_size(Params, Fullname) \
        /**/

    #else

        #define BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE_size(Params, Fullname) \
            template< Params > inline \
            typename boost::range_detail_microsoft::size_type_of< Fullname >::type \
            boost_range_size(Fullname const& x) \
            { \
                return boost::range_detail_microsoft::size_of(x); \
            } \
        /**/

    #endif




// list_iterator and helpers
//


#include <boost/assert.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>


// POSITION's header is undocumented, so is NULL.
//
struct __POSITION; // incomplete, but used as just a pointer.
typedef __POSITION *POSITION;


namespace boost { namespace range_detail_microsoft {


    template<
        class ListT,
        class Value,
        class Reference,
        class Traversal
    >
    struct list_iterator;


    template<
        class ListT,
        class Value,
        class Reference,
        class Traversal
    >
    struct list_iterator_super
    {
        typedef typename mpl::if_< is_same<use_default, Reference>,
            Value&,
            Reference
        >::type ref_t;

        typedef typename mpl::if_< is_same<use_default, Traversal>,
            bidirectional_traversal_tag,
            Traversal
        >::type trv_t;

        typedef iterator_facade<
            list_iterator<ListT, Value, Reference, Traversal>,
            Value,
            trv_t,
            ref_t
        > type;
    };


    template<
        class ListT,
        class Value,
        class Reference = use_default,
        class Traversal = use_default
    >
    struct list_iterator :
        list_iterator_super<ListT, Value, Reference, Traversal>::type
    {
    private:
        typedef list_iterator self_t;
        typedef typename list_iterator_super<ListT, Value, Reference, Traversal>::type super_t;
        typedef typename super_t::reference ref_t;

    public:
        explicit list_iterator()
        { }

        explicit list_iterator(ListT& lst, POSITION pos) :
            m_plst(boost::addressof(lst)), m_pos(pos)
        { }

    template< class, class, class, class > friend struct list_iterator;
        template< class ListT_, class Value_, class Reference_, class Traversal_>
        list_iterator(list_iterator<ListT_, Value_, Reference_, Traversal_> const& other) :
            m_plst(other.m_plst), m_pos(other.m_pos)
        { }

    private:
        ListT *m_plst;
        POSITION m_pos;

    friend class iterator_core_access;
        ref_t dereference() const
        {
            BOOST_ASSERT(m_pos != 0 && "out of range");
            return m_plst->GetAt(m_pos);
        }

        // A    B    C    D    x
        // Head           Tail NULL(0)
        //
        void increment()
        {
            BOOST_ASSERT(m_pos != 0 && "out of range");
            m_plst->GetNext(m_pos);
        }

        void decrement()
        {
            if (m_pos == 0) {
                m_pos = m_plst->GetTailPosition();
                return;
            }

            m_plst->GetPrev(m_pos);
        }

        bool equal(self_t const& other) const
        {
            BOOST_ASSERT(m_plst == other.m_plst && "iterators incompatible");
            return m_pos == other.m_pos;
        }
    };


    // customization helpers
    //

    struct array_functions
    {
        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return x.GetData();
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return begin<Iterator>(x) + x.GetSize();
        }
    };


    struct list_functions
    {
        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return Iterator(x, x.GetHeadPosition());
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return Iterator(x, POSITION(0));
        }
    };


} } // namespace boost::range_detail_microsoft




// test
//


#if defined(BOOST_RANGE_DETAIL_MICROSOFT_TEST)


#include <algorithm>
#include <iterator>
#include <vector>
#include <boost/concept_check.hpp>
#include <boost/next_prior.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/distance.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/mutable_iterator.hpp>
#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>
#include <boost/range/value_type.hpp>
#include <boost/type_traits/is_same.hpp>


namespace boost { namespace range_detail_microsoft {


    template< class Range1, class Range2 >
    bool test_equals(Range1 const& rng1, Range2 const& rng2)
    {
        return
            boost::distance(rng1) == boost::distance(rng2) &&
            std::equal(boost::begin(rng1), boost::end(rng1), boost::begin(rng2))
        ;
    }


    template< class AssocContainer, class PairT >
    bool test_find_key_and_mapped(AssocContainer const& ac, PairT const& pa)
    {
        typedef typename boost::range_const_iterator<AssocContainer>::type iter_t;
        for (iter_t it = boost::const_begin(ac), last = boost::const_end(ac); it != last; ++it) {
            if (it->first == pa.first && it->second == pa.second)
                return true;
        }

        return false;
    }


    // test functions
    //

    template< class Range >
    bool test_emptiness(Range& )
    {
        bool result = true;

        Range emptyRng;
        result = result && boost::empty(emptyRng);

        return result;
    }


    template< class Range >
    bool test_trivial(Range& rng)
    {
        bool result = true;

        // convertibility check
        typedef typename range_const_iterator<Range>::type citer_t;
        citer_t cit = boost::begin(rng);
        (void)cit; // unused

        // mutability check
        typedef typename range_value<Range>::type val_t;
        val_t v = *boost::begin(rng);
        *boost::begin(rng) = v;
        result = result && *boost::begin(rng) == v;

        return result;
    }


    template< class Range >
    bool test_forward(Range& rng)
    {
        boost::function_requires< ForwardRangeConcept<Range> >();

        bool result = (test_trivial)(rng);

        typedef typename range_value<Range>::type val_t;

        std::vector<val_t> saved;
        std::copy(boost::begin(rng), boost::end(rng), std::back_inserter(saved));
        std::rotate(boost::begin(saved), boost::next(boost::begin(saved)), boost::end(saved));

        std::rotate(boost::begin(rng), boost::next(boost::begin(rng)), boost::end(rng));

        return result && (test_equals)(saved, rng);
    };


    template< class Range >
    bool test_bidirectional(Range& rng)
    {
        boost::function_requires< BidirectionalRangeConcept<Range> >();

        bool result = (test_forward)(rng);

        typedef typename range_value<Range>::type val_t;

        std::vector<val_t> saved;
        std::copy(boost::begin(rng), boost::end(rng), std::back_inserter(saved));

        result = result && (test_equals)(
            boost::make_iterator_range(boost::rbegin(saved), boost::rend(saved)),
            boost::make_iterator_range(boost::rbegin(rng), boost::rend(rng))
        );

        return result;
    }


    template< class Range >
    bool test_random_access(Range& rng)
    {
        boost::function_requires< RandomAccessRangeConcept<Range> >();

        bool result = (test_bidirectional)(rng);

        typedef typename range_value<Range>::type val_t;

        std::vector<val_t> saved;
        std::copy(boost::begin(rng), boost::end(rng), std::back_inserter(saved));
        std::sort(boost::begin(saved), boost::end(saved));

        std::random_shuffle(boost::begin(rng), boost::end(rng));
        std::sort(boost::begin(rng), boost::end(rng));
        result = result && (test_equals)(rng, saved);

        std::random_shuffle(boost::begin(rng), boost::end(rng));
        std::stable_sort(boost::begin(rng), boost::end(rng));
        result = result && (test_equals)(rng, saved);

        std::random_shuffle(boost::begin(rng), boost::end(rng));
        std::partial_sort(boost::begin(rng), boost::end(rng), boost::end(rng));
        result = result && (test_equals)(rng, saved);

        return result;
    }


    // initializer
    //

    template< class ArrayT, class SampleRange >
    bool test_init_array(ArrayT& arr, SampleRange const& sample)
    {
        typedef typename range_const_iterator<SampleRange>::type iter_t;
        typedef typename range_value<SampleRange>::type val_t;

        for (iter_t it = boost::const_begin(sample), last = boost::const_end(sample); it != last; ++it) {
            val_t v = *it; // works around ATL3 CSimpleArray
            arr.Add(v);
        }

        return (test_equals)(arr, sample);
    }


    template< class ListT, class SampleRange >
    bool test_init_list(ListT& lst, SampleRange const& sample)
    {
        typedef typename range_const_iterator<SampleRange>::type iter_t;

        for (iter_t it = boost::const_begin(sample), last = boost::const_end(sample); it != last; ++it) {
            lst.AddTail(*it);
        }

        return (test_equals)(lst, sample);
    }


    template< class StringT, class SampleRange >
    bool test_init_string(StringT& str, SampleRange const& sample)
    {
        typedef typename range_const_iterator<SampleRange>::type iter_t;
        typedef typename range_value<SampleRange>::type val_t;

        for (iter_t it = boost::const_begin(sample), last = boost::const_end(sample); it != last; ++it) {
            str += *it;
        }

        return (test_equals)(str, sample);
    }


    template< class MapT, class SampleMap >
    bool test_init_map(MapT& map, SampleMap const& sample)
    {
        typedef typename range_const_iterator<SampleMap>::type iter_t;

        for (iter_t it = boost::const_begin(sample), last = boost::const_end(sample); it != last; ++it) {
            map.SetAt(it->first, it->second);
        }

        return boost::distance(map) == boost::distance(sample);
    }


    // metafunction test
    //

    template< class Range, class Iter >
    struct test_mutable_iter :
        boost::is_same< typename boost::BOOST_RANGE_DETAIL_MICROSOFT_range_mutable_iterator<Range>::type, Iter >
    { };


    template< class Range, class Iter >
    struct test_const_iter :
        boost::is_same< typename boost::range_const_iterator<Range>::type, Iter >
    { };


} } // namespace boost::range_detail_microsoft


#endif // defined(BOOST_RANGE_DETAIL_MICROSOFT_TEST)



#endif

/* microsoft.hpp
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
*/