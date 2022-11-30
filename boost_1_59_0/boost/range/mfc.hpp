#ifndef BOOST_RANGE_MFC_HPP
#define BOOST_RANGE_MFC_HPP




// Boost.Range MFC Extension
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)




// config
//


#include <afx.h> // _MFC_VER


#if !defined(BOOST_RANGE_MFC_NO_CPAIR)
    #if (_MFC_VER < 0x0700) // dubious
        #define BOOST_RANGE_MFC_NO_CPAIR
    #endif
#endif


#if !defined(BOOST_RANGE_MFC_HAS_LEGACY_STRING)
    #if (_MFC_VER < 0x0700) // dubious
        #define BOOST_RANGE_MFC_HAS_LEGACY_STRING
    #endif
#endif


// A const collection of old MFC doesn't return const reference.
//
#if !defined(BOOST_RANGE_MFC_CONST_COL_RETURNS_NON_REF)
    #if (_MFC_VER < 0x0700) // dubious
        #define BOOST_RANGE_MFC_CONST_COL_RETURNS_NON_REF
    #endif
#endif




// forward declarations
//


template< class Type, class ArgType >
class CArray;

template< class Type, class ArgType >
class CList;

template< class Key, class ArgKey, class Mapped, class ArgMapped >
class CMap;

template< class BaseClass, class PtrType >
class CTypedPtrArray;

template< class BaseClass, class PtrType >
class CTypedPtrList;

template< class BaseClass, class KeyPtrType, class MappedPtrType >
class CTypedPtrMap;




// extended customizations
//


#include <cstddef> // ptrdiff_t
#include <utility> // pair
#include <boost/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/range/atl.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/detail/microsoft.hpp>
#include <boost/range/end.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/utility/addressof.hpp>
#include <afx.h> // legacy CString
#include <afxcoll.h> // CXXXArray, CXXXList, CMapXXXToXXX
#include <tchar.h>


namespace boost { namespace range_detail_microsoft {


    // mfc_ptr_array_iterator
    //
    // 'void **' is not convertible to 'void const **',
    // so we define...
    //

    template< class ArrayT, class PtrType >
    struct mfc_ptr_array_iterator;

    template< class ArrayT, class PtrType >
    struct mfc_ptr_array_iterator_super
    {
        typedef iterator_adaptor<
            mfc_ptr_array_iterator<ArrayT, PtrType>,
            std::ptrdiff_t, // Base!
            PtrType,        // Value
            random_access_traversal_tag,
            use_default,
            std::ptrdiff_t  // Difference
        > type;
    };

    template< class ArrayT, class PtrType >
    struct mfc_ptr_array_iterator :
        mfc_ptr_array_iterator_super<ArrayT, PtrType>::type
    {
    private:
        typedef mfc_ptr_array_iterator self_t;
        typedef typename mfc_ptr_array_iterator_super<ArrayT, PtrType>::type super_t;
        typedef typename super_t::reference ref_t;

    public:
        explicit mfc_ptr_array_iterator()
        { }

        explicit mfc_ptr_array_iterator(ArrayT& arr, INT_PTR index) :
            super_t(index), m_parr(boost::addressof(arr))
        { }

    template< class, class > friend struct mfc_ptr_array_iterator;
        template< class ArrayT_, class PtrType_ >
        mfc_ptr_array_iterator(mfc_ptr_array_iterator<ArrayT_, PtrType_> const& other) :
            super_t(other.base()), m_parr(other.m_parr)
        { }

    private:
        ArrayT *m_parr;

    friend class iterator_core_access;
        ref_t dereference() const
        {
            BOOST_ASSERT(0 <= this->base() && this->base() < m_parr->GetSize() && "out of range");
            return *( m_parr->GetData() + this->base() );
        }

        bool equal(self_t const& other) const
        {
            BOOST_ASSERT(m_parr == other.m_parr && "iterators incompatible");
            return this->base() == other.base();
        }
    };

    struct mfc_ptr_array_functions
    {
        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return Iterator(x, 0);
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return Iterator(x, x.GetSize());
        }
    };


    // arrays
    //

    template< >
    struct customization< ::CByteArray > :
        array_functions
    {
        template< class X >
        struct meta
        {
            typedef BYTE val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *const_iterator;
        };
    };


    template< >
    struct customization< ::CDWordArray > :
        array_functions
    {
        template< class X >
        struct meta
        {
            typedef DWORD val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *const_iterator;
        };
    };


    template< >
    struct customization< ::CObArray > :
        mfc_ptr_array_functions
    {
        template< class X >
        struct meta
        {
            typedef mfc_ptr_array_iterator<X, CObject *> mutable_iterator;
            typedef mfc_ptr_array_iterator<X const, CObject const *> const_iterator;
        };
    };


    template< >
    struct customization< ::CPtrArray > :
        mfc_ptr_array_functions
    {
        template< class X >
        struct meta
        {
            typedef mfc_ptr_array_iterator<X, void *> mutable_iterator;
            typedef mfc_ptr_array_iterator<X const, void const *> const_iterator;
        };
    };


    template< >
    struct customization< ::CStringArray > :
        array_functions
    {
        template< class X >
        struct meta
        {
            typedef ::CString val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *const_iterator;
        };
    };


    template< >
    struct customization< ::CUIntArray > :
        array_functions
    {
        template< class X >
        struct meta
        {
            typedef UINT val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *const_iterator;
        };
    };


    template< >
    struct customization< ::CWordArray > :
        array_functions
    {
        template< class X >
        struct meta
        {
            typedef WORD val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *const_iterator;
        };
    };


    // lists
    //

    template< >
    struct customization< ::CObList > :
        list_functions
    {
        template< class X >
        struct meta
        {
            typedef list_iterator<X, ::CObject *> mutable_iterator;
    #if !defined(BOOST_RANGE_MFC_CONST_COL_RETURNS_NON_REF)
            typedef list_iterator<X const, ::CObject const *> const_iterator;
    #else
            typedef list_iterator<X const, ::CObject const * const, ::CObject const * const> const_iterator;
    #endif
        };
    };


    template< >
    struct customization< ::CPtrList > :
        list_functions
    {
        template< class X >
        struct meta
        {
            typedef list_iterator<X, void *> mutable_iterator;
    #if !defined(BOOST_RANGE_MFC_CONST_COL_RETURNS_NON_REF)
            typedef list_iterator<X const, void const *> const_iterator;
    #else
            typedef list_iterator<X const, void const * const, void const * const> const_iterator;
    #endif
        };
    };


    template< >
    struct customization< ::CStringList > :
        list_functions
    {
        template< class X >
        struct meta
        {
            typedef ::CString val_t;

            typedef list_iterator<X, val_t> mutable_iterator;
    #if !defined(BOOST_RANGE_MFC_CONST_COL_RETURNS_NON_REF)
            typedef list_iterator<X const, val_t const> const_iterator;
    #else
            typedef list_iterator<X const, val_t const, val_t const> const_iterator;
    #endif
        };
    };


    // mfc_map_iterator
    //

    template< class MapT, class KeyT, class MappedT >
    struct mfc_map_iterator;

    template< class MapT, class KeyT, class MappedT >
    struct mfc_map_iterator_super
    {
        typedef iterator_facade<
            mfc_map_iterator<MapT, KeyT, MappedT>,
            std::pair<KeyT, MappedT>,
            forward_traversal_tag,
            std::pair<KeyT, MappedT> const
        > type;
    };

    template< class MapT, class KeyT, class MappedT >
    struct mfc_map_iterator :
        mfc_map_iterator_super<MapT, KeyT, MappedT>::type
    {
    private:
        typedef mfc_map_iterator self_t;
        typedef typename mfc_map_iterator_super<MapT, KeyT, MappedT>::type super_t;
        typedef typename super_t::reference ref_t;

    public:
        explicit mfc_map_iterator()
        { }

        explicit mfc_map_iterator(MapT const& map, POSITION pos) :
            m_pmap(boost::addressof(map)), m_posNext(pos)
        {
            increment();
        }

        explicit mfc_map_iterator(MapT const& map) :
            m_pmap(&map), m_pos(0) // end iterator
        { }

    template< class, class, class > friend struct mfc_map_iterator;
        template< class MapT_, class KeyT_, class MappedT_>
        mfc_map_iterator(mfc_map_iterator<MapT_, KeyT_, MappedT_> const& other) :
            m_pmap(other.m_pmap),
            m_pos(other.m_pos), m_posNext(other.m_posNext),
            m_key(other.m_key), m_mapped(other.m_mapped)
        { }

    private:
        MapT const *m_pmap;
        POSITION m_pos, m_posNext;
        KeyT m_key; MappedT m_mapped;

    friend class iterator_core_access;
        ref_t dereference() const
        {
            BOOST_ASSERT(m_pos != 0 && "out of range");
            return std::make_pair(m_key, m_mapped);
        }

        void increment()
        {
            BOOST_ASSERT(m_pos != 0 && "out of range");

            if (m_posNext == 0) {
                m_pos = 0;
                return;
            }

            m_pos = m_posNext;
            m_pmap->GetNextAssoc(m_posNext, m_key, m_mapped);
        }

        bool equal(self_t const& other) const
        {
            BOOST_ASSERT(m_pmap == other.m_pmap && "iterators incompatible");
            return m_pos == other.m_pos;
        }
    };

    struct mfc_map_functions
    {
        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return Iterator(x, x.GetStartPosition());
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return Iterator(x);
        }
    };


#if !defined(BOOST_RANGE_MFC_NO_CPAIR)


    // mfc_cpair_map_iterator
    //
    // used by ::CMap and ::CMapStringToString
    //

    template< class MapT, class PairT >
    struct mfc_cpair_map_iterator;

    template< class MapT, class PairT >
    struct mfc_pget_map_iterator_super
    {
        typedef iterator_facade<
            mfc_cpair_map_iterator<MapT, PairT>,
            PairT,
            forward_traversal_tag
        > type;
    };

    template< class MapT, class PairT >
    struct mfc_cpair_map_iterator :
        mfc_pget_map_iterator_super<MapT, PairT>::type
    {
    private:
        typedef mfc_cpair_map_iterator self_t;
        typedef typename mfc_pget_map_iterator_super<MapT, PairT>::type super_t;
        typedef typename super_t::reference ref_t;

    public:
        explicit mfc_cpair_map_iterator()
        { }

        explicit mfc_cpair_map_iterator(MapT& map, PairT *pp) :
            m_pmap(boost::addressof(map)), m_pp(pp)
        { }

    template< class, class > friend struct mfc_cpair_map_iterator;
        template< class MapT_, class PairT_>
        mfc_cpair_map_iterator(mfc_cpair_map_iterator<MapT_, PairT_> const& other) :
            m_pmap(other.m_pmap), m_pp(other.m_pp)
        { }

    private:
        MapT  *m_pmap;
        PairT *m_pp;

    friend class iterator_core_access;
        ref_t dereference() const
        {
            BOOST_ASSERT(m_pp != 0 && "out of range");
            return *m_pp;
        }

        void increment()
        {
            BOOST_ASSERT(m_pp != 0 && "out of range");
            m_pp = m_pmap->PGetNextAssoc(m_pp);
        }

        bool equal(self_t const& other) const
        {
            BOOST_ASSERT(m_pmap == other.m_pmap && "iterators incompatible");
            return m_pp == other.m_pp;
        }
    };

    struct mfc_cpair_map_functions
    {
        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            // Workaround:
            // Assertion fails if empty.
            // MFC document is wrong.
    #if !defined(NDEBUG)
            if (x.GetCount() == 0) 
                return Iterator(x, 0);
    #endif

            return Iterator(x, x.PGetFirstAssoc());
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return Iterator(x, 0);
        }
    };


#endif // !defined(BOOST_RANGE_MFC_NO_CPAIR)


    // maps
    //

    template< >
    struct customization< ::CMapPtrToWord > :
        mfc_map_functions
    {
        template< class X >
        struct meta
        {
            typedef void *key_t;
            typedef WORD mapped_t;

            typedef mfc_map_iterator<X, key_t, mapped_t> mutable_iterator;
            typedef mutable_iterator const_iterator;
        };
    };


    template< >
    struct customization< ::CMapPtrToPtr > :
        mfc_map_functions
    {
        template< class X >
        struct meta
        {
            typedef void *key_t;
            typedef void *mapped_t;

            typedef mfc_map_iterator<X, key_t, mapped_t> mutable_iterator;
            typedef mutable_iterator const_iterator;
        };
    };


    template< >
    struct customization< ::CMapStringToOb > :
        mfc_map_functions
    {
        template< class X >
        struct meta
        {
            typedef ::CString key_t;
            typedef ::CObject *mapped_t;

            typedef mfc_map_iterator<X, key_t, mapped_t> mutable_iterator;
            typedef mutable_iterator const_iterator;
        };
    };


    template< >
    struct customization< ::CMapStringToPtr > :
        mfc_map_functions
    {
        template< class X >
        struct meta
        {
            typedef ::CString key_t;
            typedef void *mapped_t;

            typedef mfc_map_iterator<X, key_t, mapped_t> mutable_iterator;
            typedef mutable_iterator const_iterator;
        };
    };


    template< >
    struct customization< ::CMapStringToString > :
    #if !defined(BOOST_RANGE_MFC_NO_CPAIR)
        mfc_cpair_map_functions
    #else
        mfc_map_functions
    #endif
    {
        template< class X >
        struct meta
        {
    #if !defined(BOOST_RANGE_MFC_NO_CPAIR)
            typedef typename X::CPair pair_t;

            typedef mfc_cpair_map_iterator<X, pair_t> mutable_iterator;
            typedef mfc_cpair_map_iterator<X const, pair_t const> const_iterator;
    #else
            typedef ::CString key_t;
            typedef ::CString mapped_t;

            typedef mfc_map_iterator<X, key_t, mapped_t> mutable_iterator;
            typedef mutable_iterator const_iterator;
    #endif
        };
    };


    template< >
    struct customization< ::CMapWordToOb > :
        mfc_map_functions
    {
        template< class X >
        struct meta
        {
            typedef WORD key_t;
            typedef ::CObject *mapped_t;

            typedef mfc_map_iterator<X, key_t, mapped_t> mutable_iterator;
            typedef mutable_iterator const_iterator;
        };
    };


    template< >
    struct customization< ::CMapWordToPtr > :
        mfc_map_functions
    {
        template< class X >
        struct meta
        {
            typedef WORD key_t;
            typedef void *mapped_t;

            typedef mfc_map_iterator<X, key_t, mapped_t> mutable_iterator;
            typedef mutable_iterator const_iterator;
        };
    };


    // templates
    //

    template< class Type, class ArgType >
    struct customization< ::CArray<Type, ArgType> > :
        array_functions
    {
        template< class X >
        struct meta
        {
            typedef Type val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *const_iterator;
        };
    };


    template< class Type, class ArgType >
    struct customization< ::CList<Type, ArgType> > :
        list_functions
    {
        template< class X >
        struct meta
        {
            typedef Type val_t;

            typedef list_iterator<X, val_t> mutable_iterator;
    #if !defined(BOOST_RANGE_MFC_CONST_COL_RETURNS_NON_REF)
            typedef list_iterator<X const, val_t const> const_iterator;
    #else
            typedef list_iterator<X const, val_t const, val_t const> const_iterator;
    #endif
        };
    };


    template< class Key, class ArgKey, class Mapped, class ArgMapped >
    struct customization< ::CMap<Key, ArgKey, Mapped, ArgMapped> > :
    #if !defined(BOOST_RANGE_MFC_NO_CPAIR)
        mfc_cpair_map_functions
    #else
        mfc_map_functions
    #endif
    {
        template< class X >
        struct meta
        {
    #if !defined(BOOST_RANGE_MFC_NO_CPAIR)
            typedef typename X::CPair pair_t;

            typedef mfc_cpair_map_iterator<X, pair_t> mutable_iterator;
            typedef mfc_cpair_map_iterator<X const, pair_t const> const_iterator;
    #else
            typedef Key key_t;
            typedef Mapped mapped_t;

            typedef mfc_map_iterator<X, key_t, mapped_t> mutable_iterator;
            typedef mutable_iterator const_iterator;
    #endif            
        };
    };


    template< class BaseClass, class PtrType >
    struct customization< ::CTypedPtrArray<BaseClass, PtrType> >
    {
        template< class X >
        struct fun
        {
            typedef typename remove_pointer<PtrType>::type val_t;

            typedef typename mpl::if_< is_const<X>,
                val_t const,
                val_t
            >::type val_t_;

            typedef val_t_ * const result_type;

            template< class PtrType_ >
            result_type operator()(PtrType_ p) const
            {
                return static_cast<result_type>(p);
            }
        };

        template< class X >
        struct meta
        {
            typedef typename compatible_mutable_iterator<BaseClass>::type miter_t;
            typedef typename range_const_iterator<BaseClass>::type citer_t;

            typedef transform_iterator<fun<X>, miter_t> mutable_iterator;
            typedef transform_iterator<fun<X const>, citer_t> const_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return Iterator(boost::begin<BaseClass>(x), fun<X>());
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return Iterator(boost::end<BaseClass>(x), fun<X>());
        }
    };


    template< class BaseClass, class PtrType >
    struct customization< ::CTypedPtrList<BaseClass, PtrType> > :
        list_functions
    {
        template< class X >
        struct meta
        {
            typedef typename remove_pointer<PtrType>::type val_t;

            // not l-value
            typedef list_iterator<X, val_t * const, val_t * const> mutable_iterator;
            typedef list_iterator<X const, val_t const * const, val_t const * const> const_iterator;
        };
    };


    template< class BaseClass, class KeyPtrType, class MappedPtrType >
    struct customization< ::CTypedPtrMap<BaseClass, KeyPtrType, MappedPtrType> > :
        mfc_map_functions
    {
        template< class X >
        struct meta
        {
            typedef mfc_map_iterator<X, KeyPtrType, MappedPtrType> mutable_iterator;
            typedef mutable_iterator const_iterator;
        };
    };


    // strings
    //

#if defined(BOOST_RANGE_MFC_HAS_LEGACY_STRING)

    template< >
    struct customization< ::CString >
    {
        template< class X >
        struct meta
        {
            // LPTSTR/LPCTSTR is not always defined in <tchar.h>.
            typedef TCHAR *mutable_iterator;
            typedef TCHAR const *const_iterator;
        };

        template< class Iterator, class X >
        typename mutable_<Iterator, X>::type begin(X& x)
        {
            return x.GetBuffer(0);
        }

        template< class Iterator, class X >
        Iterator begin(X const& x)
        {
            return x;
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return begin<Iterator>(x) + x.GetLength();
        }
    };

#endif // defined(BOOST_RANGE_MFC_HAS_LEGACY_STRING)


} } // namespace boost::range_detail_microsoft




// range customizations
//


// arrays
//
BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CByteArray
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CDWordArray
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CStringArray
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CUIntArray
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CWordArray
)


// lists
//
BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CObList
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CPtrList
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CStringList
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CObArray
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CPtrArray
)


// maps
//
BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CMapPtrToWord
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CMapPtrToPtr
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CMapStringToOb
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CMapStringToPtr
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CMapStringToString
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CMapWordToOb
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CMapWordToPtr
)


// templates
//
BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CArray, 2
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CList, 2
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CMap, 4
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CTypedPtrArray, 2
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CTypedPtrList, 2
)

BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TEMPLATE(
    boost::range_detail_microsoft::using_type_as_tag,
    BOOST_PP_NIL, CTypedPtrMap, 3
)


// strings
//
#if defined(BOOST_RANGE_MFC_HAS_LEGACY_STRING)

    BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
        boost::range_detail_microsoft::using_type_as_tag,
        BOOST_PP_NIL, CString
    )

#endif




#endif

/* mfc.hpp
/OLQoryF8cPiqj8Y0f2Tx3X+2jQexdYZLySuTY6EtWmZK+HOyJzg5HxgSB/8ARmS5KgvDjh2ojTyj7kYfxqRKc9ExAYcDSRhXDUbBBFSUNKW7x5vBY7UwDyOAUVyt7+FIQokd5sLOHANniMpaSt5kTZ2sZMssmZ4YHF+BPfWd72E7mDaEBJ8wnYexldexXMOFGJ2kkn5ZmgGiNG/hebtV8R2RWxivwJQyrStCyda/UujsHZ16SQhxK1gmtDNrI8paXVo++yo5+H8GpysGA+mhBDdh+NW43kGLM9sAIxNw+UOjQfq60iJMXmU0p4SukbUxFPSIYW3e+BFKJvWAMk9M9HvFPRtxe2w5HkAIaE6vD4ijo0XPhgvnNDVve8Od3X3nOGuvujArub1WPBOtuIBqR1BPAwggsfb4/qAz6RD783X8DXfxl57hSgmQ31dNqNf9WOVrvlKKUjni2NFEyhDwbtwtHc/R7JVgY0cBa3K0xzpTEGlpaOYdgcCAXxDUngG5Gm0VySPY8UVS0omqJmsUsvZRjmGJu0ztkTL+Q1uUqgVpUJFgXVQ0d7JUKY4QBEGnBW401rsKqZbkWnr/koIv4q33ha4vQ+Updo8PHxAwLigvpRHwsS90In9Kgw25ne4xqhvahseubEf/SHgSnMvfEIh+Srq0H1d9VTIdxYrb2A5Ja2KBtlrkt/A9NiTat1yX+wRjy7YmY7xj35PGPOZ0Pl7oMAgv+f0LmAf+IBFjFpPC7aJHbxB8+9OvtWD6H3FbUIHEfloT11AqS/5UBow4+PT8Og/YEWfw5NDA+SyoRHW/NgUtnw9FrJhoV/RI31auj7+6W3r8Yoz7uB8/Q4QsPP33Bc759dzXPLM7TDxGlNspym4gd6pHJMLnPGn+eoTeTz/xf+oujmsnoXesYVeo5w/J2aS850wS/KhqJji7rmqkexe68i4ZoRdUGWezjsO6lRjKNSRpaCJhEcnxn3Yc0BREhx+/7GJrqIV3CIVFEoFc6QCKDSfN7SxIE/dMx9mW1cnsK1d8xLWp5WntZ0qkB39D83Ric5SVrYOhmP+OloT5GntaN5qRG/MyofS7DnMjrnX89yKCVo6LP6Y/mM1vepGNX3+IvKi0DibYsuyp6Eb5dTxJLnIZN9XaZTGS/mAJYNcZIbXFKnIIOWbv9fCz0y3mUSTJDSBSJUspcsT7e9XLs9dZPDe5fKMzgmVBXxtJ1+VCwzORqF1Ep5ElKBpI9M3Yry7cZZdTTkhT2beMkmILiguhp8TaPVYjHZrxZKjm+JUtyhp22uR6bWUg6w3HioaK5c02d/3pkij+WEJj8D0gJxg4yiHyU991Wn0U2/gl8qq4pgtQn/Dlj37LbsEc6lnybNlA6f/hlE5YHG3hx/SY9/2hxmUCGEJKLBo4KzkMPE8UzhmVb/1LFn07MDZRQvt4cpkOWzZ48BPwl2mMfh8hh7iLeoQTFGHudMYGhpvjYYjzeyDLUYKWSI3iZdHWLTE/FFXf4PxAVt0hTk6tglKnQiz3VBGbooZOts724PYQnuTD2pyD3tkMHUKGaVFYWYtgqo7M0DhfxRtt/f0dQo2yIUck5YT/tTE7qPMUKdgHtNn2QP5RZBKn7l4zhgkw4y4Twe5xASw+V0R7NvnVs8Sy56jZZZdH2YftuwK6/c961lSTkc+4c+h90chw7NkYbFlzyB8reEQiw0MhT/DtzGDUK8Z0ghduw7rw4h+Na9R3Ymg6iNfdArp7Uc+6uqMRBiiJjkaxlf+2BMJdxpr35tgjTZHmtuP8+TxnZFOwRpdajpx8ERzVDDF5kT2dRqDWqkOgHUcy40BhEbgf5Afr47si441fTbeijA6I5hr5TBgrODDE5/E/oro7xRMcTEzYqwFWooIVt66/oZ8cUz0yp2Y5rbG0iJftEewPfmiKWrE1BjrbIfSncZt8MK7kC9aIoK5nVp6uh1aOjFifAZzj/NcM9YJJSJuU+yKTuMWzDrKs8bxDyPNJz45cTAWpo5AUROnGvb6o0ZdHIeAQX+vNRKKfHG8B7++5YGJ1G38zz1If/t6dgNhccLsTOjSA+ZIc9T4zF7ATHMsE0AwDcQoqLLEGrNEQu37IuETh058HGnudFujIX9venQpgEwHZEWNQWhz5x1ZVNcdWUCo6UBo7DJYMaBSKAqFzs9OpuxBnh298vthdMJa2GnE3pbiuLJQwKjrFICw+tqbkcpr4R3IKeroG9OH79v4+xi8/6wOYRGAKk7ESwbhRcXhvfwDuUlu72k6HzuREOIn5cTBaDiWMQIvkRLbSLxE3DbECwyYLeLOILyEiE7ORIQzEehSRLDBjyEiZESgZ89jzwQTfAAloAVQSG4/v9iaeLHolQgOSgLTirjNSDHnlS6E0o84EBz916xyqEP0uzCOEjTuFWAaNqHf9KZwj6kD35o5oqOngQ9IxOBgsEsGIQ9YYfvX8HviZORgZ0kfJ0/jA4bIvlgyoOC49hqOWc7JixzS5rEhEoKEMM5MJG1DZyQ2vvO4NkWA70HhZhl6E27fHwmp3BOGvNMaeSfyjob4S2Qgj0hnR+dx+Bcnwxed0BVzZ3rP8zB4J2AyciYANUJJIOyGE92R/Se+jjTHJsCY7W//BOD/C9JCJ05FDnUC6Q1GGjTgYwHicZgKS/tOfAXcItzZC+A6MGcckkxfdOngia9OQCehbmHwxMcnTkeNk47jgmXuvLAzKToNmVTn+GGmMJrPqs4LY8md7fFba3ja1jsDzS1+il6DB/U+vUe/AKWu0oBXl4S7YeiYgofXYL8exAuBvVh8gO6bnNFZqv5N4qZ81rLrbE6zx/RLuZF21SSfiW+spf+iX+lANrSudoIVVKvoafkAKKty35Gz8okB0JEGJYcVp3L3cZ9Ncts63W2dQlt0aXenO4rL19jprdATdwsPMQsr4H4JA9nYOC10uhvsByyPNWMeEM4uoMhTHcKpqNCAjLyF00OSpRo9UHW2F0XFliKYbTi/3bBY9eG8nnDcqIs6omVlUaE76u7m6PoRZBYVYfbJyHB2TN+JZdp4GSO0MzYzXvBg5D/CeTURziiAAwMRweMdwWrqTFcEU65osjx6AyyIs+wnLI9OoBs6Ztk9uExufaRpGSx0MBdCPcmhz5NDLLlaqfyVLMLsaqbpcRCxQfOEo6UAfjr17YfYxZJRt6kgCZ4PMgs8R0KbUqJjmIGSlU69ynpObcL3ZP9+k/+A4XaxgVO03zeoK1/oTVXEQbahEMVFoZe2PhLoJ72ULqj2g3S70iALmfR2FN6cBpTmHBn+ZkORItq0g16TB919zwPZdtIbeGsfln1Qml9ANSrpMVSa0YE9noiuoOsVOyn2nonH3gOh+NNcd733n7JQKztq5D5J6OaO2buckrtPcnSxQ98oSimeWU7cC8KeJDA8HqiiOJVCDUhPbJnf93cMNCn+KNyVDDprvSL2sX8coss3Pf1ozuIIscdvAOFiJirkxaCxKcecmPj+TDyGMcnT6nfj1d4GEGsFEzrcrqOvWtnCG7gun0QftLKX6INeRWxTPqzI1LXoiovhM3mQ3CPU4EubkjYDgNmHvHia1YYxK0wEGY8vhT7015aGMVsOrSnciKFhQa803Cqeiv1cPkKCz1cg+8BSM+ZDWewO91iRy35sGnPEfnJNumyyH/SO3ogTQ5FMMRCT4du5IoOGoQb3MLSNe48IsQdnDtCRbtmjw3bXqCXQjgzKr6gubChI2OWYFNyHA+YMYPQQyR1Fy4sCczbocZWm7BvJbY3AB8fEB8fXi1Esrz2F/KMb+ccRbv6gGocFHC3skuuhFbMMaqg1vqOg7Ym0sNIZiMtujDKahvhHb3ITYXjhC7X0W4Thonl4Yxw0NsQrd9/aCjqao8+yy9GLMmC4K726uXIciI6pyf59hlulEpP4NUK7XhaiAKZY+0jsg7ErKlVWGpRjfh/Tec00bmr95N8CtUKOxBZ2PTSQ/SgwjEGYGtlCpuywZQvWbIdZL0zSOyb5fVN0xaXe1DxQQrIdGbEU+NU7MkjFywpM3aRcz1oxTKJ7spSClzcqLXvG3dOsR8UAl1sQW/0f6/X7SG8IDyZLjgyuHmRY9pQm3XNUr2kQIPpSQSoziZeZZNlTkHxPSG/Z835CdlyLmJSgRWTQg5SCcvFkVXQhkrTBtC6WLyyVp7jk+w3AreUFZjnPlH2gUTgDhJakiGeyjxc75XzzvFKY8dmN8GjKFjB+Fx6r2Bi7/qyiXS0oDP4bqWi0jCpJ+hL5tOSrtVTtR5NiAbBmzumQ0Ku55dFaTAJooPOJNfaTlkdfQOfXM2vumGg1PTQeiUxZa2Bb7GeVnmrM8WUp3rEIshIZCd7GRTKvR8u32QY6AEjYtdJoLMS+zqVNtXHavLjz5wNK7G1QBxuFKA8oyuB7pAi+t6LuxkVZYAZ9mBYgp/E6tTi74q1+JfZXReyCKc2+nYGelaA3T4Yloc5+SDSyLx10jCgJ9ZyJBWGdDbLUr3CS1IPGWZvr7vO+6kSGwGl+tiGh5cRROEvFAK6lxFw4P5GFDHSI8WOSpyx7WjlfABIacxAH+Z+mMSBtAdExy64DiN9vkD3ONNSh06K2txWampkUMCC9sgzJATTP7LCT7XsTeKpdyPTNB75OpEbwUbrD7Je17GlqtpV4kpZdpWZbNq9Ed6bWnJDdnWHZGsLb04tInABOv8qyZ+yPF05EXTdgyPfoUU2TxF77AaRgmMBjL4FMjcrjJeTDUCBZbrLsScuAfK4rBww3Q+7CgSH7ASDxA1B+rI7UTU0UdfT2RHWcXMSrOlBnSY+OLURpY34W/o8qajGNB1pFKj3I5+VD1OVmgC852qmiQxjmwZFFfY14lihienZ7MYYyPqbH+FmVRklsjY2jjGJKo2uBWdSF9mx3+3BOOy/dnVi6HSBZ9rizst29w4mAj0qDfCA2JiEJ+tOt9VHrYCs9APeTkvxCn0FxtFmqURWSfbWyWJPTARQ1vDAhEXF6Qp6nElId0KFeXmDAAuz6nyMTrueM7xxivz7YH19Qrr6Btl6ZCaSKfZk6z/Jg+s1Q5JGHYbkII0d0mCVhZ3Wz5dHHKfom8EcTvvnxrdCQ0xEo6aJdmG5+8i8nzVOcTm0xoZBv7lbJ3Sa522HxUdKcb+DtR56jpG0hXwSWqmnJxDVknw0YR7bPHHBsZUEM+CvshOnzQ2xgK4tNU++foN2qu7ZRqMEO8q9c583+GvbYdF7+T3jVRaxVxGfY2NyEyb6JJnvyL/BsOght3AzTfLPk28Iu/TfO9C0oQtwD3+a6g5aq/5uEG2biM+qMp0p/YNK7aMo/w0cq153O40Lbhyybo7TvB0K2JLQc8bXIjTDPJbFhwN0QuD1JEmDyhyR3Xa67Zf2tgbmK5NgulzTJjjr9QclRb2/y/URfst3e6rtUdtfLjmDA/Kx8oQSP7mDA9oR8kXSh7KiXRud0KEIdfKQ4ttsdLZV7ZUdDkqNJcYTE7bFyuZGOo9aVwveSoylwuwLVW3YdhhbkSQJU3mI/WflTrDUZwNLF6xZ9WBFaAga/nC5dBDXD2iyl54ot66M5HXpHg3wAxLUkgSoIcbTEKfcZ1/l0u2nE4MKQPHAD0u4WjXZrMDINH1n24Bsa6W5l906FZXxJNY9WOj/oQLq9uwroFqgIzVkxeKCvtlqBRSmZHDVmu01Ap9UdsCgln7sorTGwoam4KCVzEefn1wxgaKIfEHFW59AqcoEmUXTn4CzquQ3BLu2FicaIDgsMruJziZCx0ddrSxDjs5IKs211sAT9hYTQVrb2+rhzP1iC0EMz0KUHj9Np+WmAWdWAjnYe/hzpEqOL7fb7+nS0BGliV4Embo2gxGL5kkR56/3/bgGCRQa+fhE5tgSSElApyYaPfoebokKUFiJchHR2kG+qjpGcuLMo4AgWoQNgJ6v/UlEiX+CmDe3V7OR7NdtQ2RJhauF6IjeJD4JSwqUny57T2Zww9Y2SWM/XlHo5TJx4kIrhqpJQpouX6QLBMZPL1+pBqz6sLSqOLmCm5/LdenqIXf4Di0oRq/tcXVQSeHPUUj0OlT6g7wKOXhWfLhJ8NQIH5NbFqQdG9cWpSNhNGmGPGP4X/6pRdgt78jrOlFf/DxB3xvc6QkjH8w5HBkbSFLokR5s9LE5xkuvTaVgHg3ZhRDyaZngkCFmNQnd6N9R0A9TUgyE6YTXVFbvewsTKe1GMCIgmftvcs2SH9yIu2S2Coc56duBskR6d7AxKgjkGOdZswVTGc0Dx6dKjJnsKdCxswS/UFgjt0O+Ao3dEI2ACsj270fnBJF3lqnMrXeTNgDVHDkO9ABXgT4Kas/GIV3LYoF6HFfNAAG9LyOuVHAiZHZ36v9R7424U4rJAvPcPLrE8ZidNswujOi9thXnbBpTcEl7RYsVjhmXhFSeQwoAlhlc0QZIjCklR6GZowM33yFKABTcKXXk0BRqA7pqgUTB/HC2gwAAdlkQtu0pa9UhkJzBFfzA8mBI+nZKwxwacWO9og0dKbh4TpiFMhY6MwMwOWWz1ZiNmjmSXmGFd/tay62xYScluLMDNnG/x8T0YnOwwhvULxa7k6zToCrsOQJ0wOgXA0aEOvQM6APg6ld0EmtXE/4gtK4V+CyUJDbJQrzi6koQ2v69LBxKS5TE8qC1fqPpEunwVnqtk6TwLghuQB/+rksJpgWggmnIv2Y7e8y9XxEmgNSkiGmuAGERuArBjLPM7Rel5iRw+1MA7cPsd7Il/4dQKZou1sq8u21eDRO5rs1Q9iNdoT1qqVmNxRz176ipShv+DhFDPmq/hK34OSQiaesC/KnWdrx+smMLLf0U3/UEdCLHYlAQJgZGE0JWvceI2J9P/i1RllA3eQuNzd5+l6q86kg1CnBUHBCCUFjprEkBbnSRjIPIsSdiO0fKEdsAJxoAV0yX3c4AZyb0NfSg8R+howbPzHfzuvdAOBNZm3185AVjRxlTaZAgbCmHMxS94j+LrbIgsBtpIxqlJWGvZyLU2xMZN4cq6JifSWsvFRMtfNI5Uz/SARtbtA3aUpZocv45DfacPHaqkyyUZckR6Hh0MoTq0j1jRJpZ/HcLeLC800BK7Ok5fmxqFTcSKal4DVnQluWDKzFGy37NU6eDF88tF2YctVV8Ci8Lfj9Xfo+pvJy3RW9jTV9IuhOQ7o944Gzn2W9i72bTQjued2MJunDyg9LwJX79N5hq+nZK4nTM5db4UG5xFyqqRJLGd/fJaDgZKwysZLJyqgbV6J7kI3coOXTugXW2ThM3294A+Qjf1Kx4T1tkMmdyxEixaxjrOKzpwTmG9RdGx64AqiiAtOq0VtzphQdz7jlF33NHAPvAaValF7iuVyGMTi71i1OXg/Ul9u32gMlU+MAD8vy6ml3wg4NXDOFj2hIFXtQCvajEtk0oOw8Nhk+SoCa+osUolteEVtUCD2wbc23KacUMKmJgPxL566cl15B0qFOdmJYeBewWJeyE/C+lBHCipxTTgI5schyC9Jp5+iPMvkBaA3QwLDhQDx45yfGPAfClxojriQnVI1bBkpfGwSEmNwgaih+deBbzehawYDVz0fah+fZjdypGlP4IW50JvQNgA+hyOsAS6h8jYH1FW6/MYSKcQt4JaAUNX
*/