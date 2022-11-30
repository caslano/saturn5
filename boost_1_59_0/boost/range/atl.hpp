#ifndef BOOST_RANGE_ATL_HPP
#define BOOST_RANGE_ATL_HPP




// Boost.Range ATL Extension
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)




// config
//


#include <atldef.h> // _ATL_VER


#if !defined(BOOST_RANGE_ATL_NO_COLLECTIONS)
    #if (_ATL_VER < 0x0700)
        #define BOOST_RANGE_ATL_NO_COLLECTIONS
    #endif
#endif


#if !defined(BOOST_RANGE_ATL_HAS_OLD_CSIMPLE_XXX)
    #if (_ATL_VER < 0x0700) // dubious
        #define BOOST_RANGE_ATL_HAS_OLD_CSIMPLE_XXX
    #endif
#endif


// forward declarations
//


#include <basetyps.h> // IID


namespace ATL {


#if !defined(BOOST_RANGE_ATL_NO_COLLECTIONS)


    // arrays
    //
    template< class E, class ETraits >
    class CAtlArray;

    template< class E >
    class CAutoPtrArray;

    template< class I, const IID *piid >
    class CInterfaceArray;


    // lists
    //
    template< class E, class ETraits >
    class CAtlList;

    template< class E >
    class CAutoPtrList;

    template< class E, class Allocator >
    class CHeapPtrList;

    template< class I, const IID *piid >
    class CInterfaceList;


    // maps
    //
    template< class K, class V, class KTraits, class VTraits >
    class CAtlMap;

    template< class K, class V, class KTraits, class VTraits >
    class CRBTree;

    template< class K, class V, class KTraits, class VTraits >
    class CRBMap;

    template< class K, class V, class KTraits, class VTraits >
    class CRBMultiMap;


    // strings
    //
#if !defined(BOOST_RANGE_ATL_HAS_OLD_CSIMPLESTRING)
    template< class BaseType, bool t_bMFCDLL >
    class CSimpleStringT;
#else
    template< class BaseType >
    class CSimpleStringT;
#endif

    template< class BaseType, class StringTraits >
    class CStringT;

    template< class StringType, int t_nChars >
    class CFixedStringT;

    template< class BaseType, const int t_nSize >
    class CStaticString;


#endif // !defined(BOOST_RANGE_ATL_NO_COLLECTIONS)


    // simples
    //
#if !defined(BOOST_RANGE_ATL_HAS_OLD_CSIMPLE_XXX)

    template< class T, class TEqual >
    class CSimpleArray;

    template< class TKey, class TVal, class TEqual >
    class CSimpleMap;

#else

    template< class T >
    class CSimpleArray;

    template< class T >
    class CSimpleValArray;

    template< class TKey, class TVal >
    class CSimpleMap;

#endif // !defined(BOOST_RANGE_ATL_HAS_OLD_CSIMPLE_XXX)


    // pointers
    //
    template< class E >
    class CAutoPtr;

    template< class T >
    class CComPtr;

    template< class T, const IID *piid >
    class CComQIPtr;

    template< class E, class Allocator >
    class CHeapPtr;

    template< class T >
    class CAdapt;


} // namespace ATL




// indirect_iterator customizations
//


#include <boost/mpl/identity.hpp>
#include <boost/pointee.hpp>


namespace boost {


    template< class E >
    struct pointee< ATL::CAutoPtr<E> > :
        mpl::identity<E>
    { };

    template< class T >
    struct pointee< ATL::CComPtr<T> > :
        mpl::identity<T>
    { };

    template< class T, const IID *piid >
    struct pointee< ATL::CComQIPtr<T, piid> > :
        mpl::identity<T>
    { };

    template< class E, class Allocator >
    struct pointee< ATL::CHeapPtr<E, Allocator> > :
        mpl::identity<E>
    { };

    template< class T >
    struct pointee< ATL::CAdapt<T> > :
        pointee<T>
    { };


} // namespace boost




// extended customizations
//


#include <boost/iterator/indirect_iterator.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/range/detail/microsoft.hpp>
#include <boost/tuple/tuple.hpp>
#include <atlbase.h> // CComBSTR


namespace boost { namespace range_detail_microsoft {


#if !defined(BOOST_RANGE_ATL_NO_COLLECTIONS)


    // arrays
    //

    struct atl_array_functions :
        array_functions
    {
        template< class Iterator, class X >
        Iterator end(X& x) // redefine
        {
            return x.GetData() + x.GetCount(); // no 'GetSize()'
        }
    };


    template< class E, class ETraits >
    struct customization< ATL::CAtlArray<E, ETraits> > :
        atl_array_functions
    {
        template< class X >
        struct meta
        {
            typedef E val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *const_iterator;
        };
    };


    template< class E >
    struct customization< ATL::CAutoPtrArray<E> > :
        atl_array_functions
    {
        template< class X >
        struct meta
        {
            // ATL::CAutoPtr/CHeapPtr is no assignable.
            typedef ATL::CAutoPtr<E> val_t;
            typedef val_t *miter_t;
            typedef val_t const *citer_t;

            typedef indirect_iterator<miter_t> mutable_iterator;
            typedef indirect_iterator<citer_t> const_iterator;
        };
    };


    template< class I, const IID *piid >
    struct customization< ATL::CInterfaceArray<I, piid> > :
        atl_array_functions
    {
        template< class X >
        struct meta
        {
            typedef ATL::CComQIPtr<I, piid> val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *const_iterator;
        };
    };


    template< class E, class ETraits >
    struct customization< ATL::CAtlList<E, ETraits> > :
        list_functions
    {
        template< class X >
        struct meta
        {
            typedef E val_t;

            typedef list_iterator<X, val_t> mutable_iterator;
            typedef list_iterator<X const, val_t const> const_iterator;
        };
    };


    struct indirected_list_functions
    {
        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            typedef typename Iterator::base_type base_t; // == list_iterator
            return Iterator(base_t(x, x.GetHeadPosition()));
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            typedef typename Iterator::base_type base_t;
            return Iterator(base_t(x, POSITION(0)));
        }
    };


    template< class E >
    struct customization< ATL::CAutoPtrList<E> > :
        indirected_list_functions
    {
        template< class X >
        struct meta
        {
            typedef ATL::CAutoPtr<E> val_t;
            typedef list_iterator<X, val_t> miter_t;
            typedef list_iterator<X const, val_t const> citer_t;

            typedef indirect_iterator<miter_t> mutable_iterator;
            typedef indirect_iterator<citer_t> const_iterator;
        };
    };


    template< class E, class Allocator >
    struct customization< ATL::CHeapPtrList<E, Allocator> > :
        indirected_list_functions
    {
        template< class X >
        struct meta
        {
            typedef ATL::CHeapPtr<E, Allocator> val_t;
            typedef list_iterator<X, val_t> miter_t;
            typedef list_iterator<X const, val_t const> citer_t;

            typedef indirect_iterator<miter_t> mutable_iterator;
            typedef indirect_iterator<citer_t> const_iterator;
        };
    };


    template< class I, const IID *piid >
    struct customization< ATL::CInterfaceList<I, piid> > :
        list_functions
    {
        template< class X >
        struct meta
        {
            typedef ATL::CComQIPtr<I, piid> val_t;

            typedef list_iterator<X, val_t> mutable_iterator;
            typedef list_iterator<X const, val_t const> const_iterator;
        };
    };


    // maps
    //

    struct atl_rb_tree_tag
    { };

    template< >
    struct customization< atl_rb_tree_tag > :
        indirected_list_functions
    {
        template< class X >
        struct meta
        {
            typedef typename X::CPair val_t;

            typedef list_iterator<X, val_t *, val_t *> miter_t;
            typedef list_iterator<X const, val_t const *, val_t const *> citer_t;
            
            typedef indirect_iterator<miter_t> mutable_iterator;
            typedef indirect_iterator<citer_t> const_iterator;
        };
    };


    template< class K, class V, class KTraits, class VTraits >
    struct customization< ATL::CAtlMap<K, V, KTraits, VTraits> > :
        customization< atl_rb_tree_tag >
    {
        template< class Iterator, class X >
        Iterator begin(X& x) // redefine
        {
            typedef typename Iterator::base_type base_t; // == list_iterator
            return Iterator(base_t(x, x.GetStartPosition())); // no 'GetHeadPosition'
        }
    };


    // strings
    //

    struct atl_string_tag
    { };

    template< >
    struct customization< atl_string_tag >
    {
        template< class X >
        struct meta
        {
            typedef typename X::PXSTR mutable_iterator;
            typedef typename X::PCXSTR const_iterator;
        };

        template< class Iterator, class X >
        typename mutable_<Iterator, X>::type begin(X& x)
        {
            return x.GetBuffer(0);
        }

        template< class Iterator, class X >
        Iterator begin(X const& x)
        {
            return x.GetString();
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return begin<Iterator>(x) + x.GetLength();
        }
    };


    template< class BaseType, const int t_nSize >
    struct customization< ATL::CStaticString<BaseType, t_nSize> >
    {
        template< class X >
        struct meta
        {
            typedef BaseType const *mutable_iterator;
            typedef mutable_iterator const_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X const& x)
        {
            return x;
        }

        template< class Iterator, class X >
        Iterator end(X const& x)
        {
            return begin<Iterator>(x) + X::GetLength();
        }
    };


#endif // !defined(BOOST_RANGE_ATL_NO_COLLECTIONS)


    template< >
    struct customization< ATL::CComBSTR >
    {
        template< class X >
        struct meta
        {
            typedef OLECHAR *mutable_iterator;
            typedef OLECHAR const *const_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return x.operator BSTR();
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return begin<Iterator>(x) + x.Length();
        }
    };


    // simples
    //

#if !defined(BOOST_RANGE_ATL_HAS_OLD_CSIMPLE_XXX)
    template< class T, class TEqual >
    struct customization< ATL::CSimpleArray<T, TEqual> > :
#else
    template< class T >
    struct customization< ATL::CSimpleArray<T> > :
#endif
        array_functions
    {
        template< class X >
        struct meta
        {
            typedef T val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *const_iterator;
        };
    };


#if defined(BOOST_RANGE_ATL_HAS_OLD_CSIMPLE_XXX)

    template< class T >
    struct customization< ATL::CSimpleValArray<T> > :
        array_functions
    {
        template< class X >
        struct meta
        {
            typedef T val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *const_iterator;
        };
    };

#endif // defined(BOOST_RANGE_ATL_HAS_OLD_CSIMPLE_XXX)


#if !defined(BOOST_RANGE_ATL_HAS_OLD_CSIMPLE_XXX)
    template< class TKey, class TVal, class TEqual >
    struct customization< ATL::CSimpleMap<TKey, TVal, TEqual> >
#else
    template< class TKey, class TVal >
    struct customization< ATL::CSimpleMap<TKey, TVal> >
#endif
    {
        template< class X >
        struct meta
        {
            typedef TKey k_val_t;
            typedef k_val_t *k_miter_t;
            typedef k_val_t const *k_citer_t;

            typedef TVal v_val_t;
            typedef v_val_t *v_miter_t;
            typedef v_val_t const *v_citer_t;

            // Topic:
            // 'std::pair' can't contain references
            // because of reference to reference problem.

            typedef zip_iterator< tuple<k_miter_t, v_miter_t> > mutable_iterator;
            typedef zip_iterator< tuple<k_citer_t, v_citer_t> > const_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return Iterator(boost::make_tuple(x.m_aKey, x.m_aVal));
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return Iterator(boost::make_tuple(x.m_aKey + x.GetSize(), x.m_aVal + x.GetSize()));
        }
    };


} } // namespace boost::range_detail_microsoft




// range customizations
//


#if !defined(BOOST_RANGE_ATL_NO_COLLECTIONS)


    // arrays
    //
    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::using_type_as_tag,
        (ATL, BOOST_PP_NIL), CAtlArray, 2
    )

    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::using_type_as_tag,
        (ATL, BOOST_PP_NIL), CAutoPtrArray, 1
    )

    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::using_type_as_tag,
        (ATL, BOOST_PP_NIL), CInterfaceArray, (class)(const IID *)
    )


    // lists
    //
    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::using_type_as_tag,
        (ATL, BOOST_PP_NIL), CAtlList, 2
    )

    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::using_type_as_tag,
        (ATL, BOOST_PP_NIL), CAutoPtrList, 1
    )

    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::using_type_as_tag,
        (ATL, BOOST_PP_NIL), CHeapPtrList, 2
    )

    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::using_type_as_tag,
        (ATL, BOOST_PP_NIL), CInterfaceList, (class)(const IID *)
    )


    //maps
    //
    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::using_type_as_tag,
        (ATL, BOOST_PP_NIL), CAtlMap, 4
    )

    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::atl_rb_tree_tag,
        (ATL, BOOST_PP_NIL), CRBTree, 4
    )

    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::atl_rb_tree_tag,
        (ATL, BOOST_PP_NIL), CRBMap, 4
    )

    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::atl_rb_tree_tag,
        (ATL, BOOST_PP_NIL), CRBMultiMap, 4
    )


    // strings
    //
    #if !defined(BOOST_RANGE_ATL_HAS_OLD_CSIMPLESTRING)
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
            boost::range_detail_microsoft::atl_string_tag,
            (ATL, BOOST_PP_NIL), CSimpleStringT, (class)(bool)
        )
    #else
        BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
            boost::range_detail_microsoft::atl_string_tag,
            (ATL, BOOST_PP_NIL), CSimpleStringT, 1
        )
    #endif

    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::atl_string_tag,
        (ATL, BOOST_PP_NIL), CStringT, 2
    )

    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::atl_string_tag,
        (ATL, BOOST_PP_NIL), CFixedStringT, (class)(int)
    )

    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::using_type_as_tag,
        (ATL, BOOST_PP_NIL), CStaticString, (class)(const int)
    )


#endif // !defined(BOOST_RANGE_ATL_NO_COLLECTIONS)


BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    (ATL, BOOST_PP_NIL), CComBSTR
)


// simples
//
#if !defined(BOOST_RANGE_ATL_HAS_OLD_CSIMPLE_XXX)

    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::using_type_as_tag,
        (ATL, BOOST_PP_NIL), CSimpleArray, 2
    )

    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::using_type_as_tag,
        (ATL, BOOST_PP_NIL), CSimpleMap, 3
    )

#else

    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::using_type_as_tag,
        (ATL, BOOST_PP_NIL), CSimpleArray, 1
    )

    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::using_type_as_tag,
        (ATL, BOOST_PP_NIL), CSimpleMap, 2
    )

    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
        boost::range_detail_microsoft::using_type_as_tag,
        (ATL, BOOST_PP_NIL), CSimpleValArray, 1
    )

#endif // !defined(BOOST_RANGE_ATL_HAS_OLD_CSIMPLE_XXX)




#endif

/* atl.hpp
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
*/