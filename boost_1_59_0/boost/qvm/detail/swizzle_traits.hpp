#ifndef BOOST_QVM_DETAIL_SWIZZLE_TRAITS_HPP_INCLUDED
#define BOOST_QVM_DETAIL_SWIZZLE_TRAITS_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/inline.hpp>
#include <boost/qvm/deduce_vec.hpp>
#include <boost/qvm/enable_if.hpp>
#include <boost/qvm/assert.hpp>

namespace boost { namespace qvm {

namespace
qvm_detail
    {
    BOOST_QVM_INLINE_CRITICAL
    void const *
    get_null()
        {
        static int const obj=0;
        return &obj;
        }

    template <int A,class Next=void> struct swizzle_idx { static int const value=A; typedef Next next; };

    template <class V,int Idx>
    struct
    const_value
        {
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        typename vec_traits<V>::scalar_type
        value()
            {
            BOOST_QVM_ASSERT(0);
            return typename vec_traits<V>::scalar_type();
            }
        };

    template <class V>
    struct
    const_value<V,-1>
        {
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        typename vec_traits<V>::scalar_type
        value()
            {
            return scalar_traits<typename vec_traits<V>::scalar_type>::value(0);
            }
        };

    template <class V>
    struct
    const_value<V,-2>
        {
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        typename vec_traits<V>::scalar_type
        value()
            {
            return scalar_traits<typename vec_traits<V>::scalar_type>::value(1);
            }
        };

    template <int Index,bool Neg=(Index<0)>
    struct neg_zero;

    template <int Index>
    struct
    neg_zero<Index,true>
        {
        static int const value=0;
        };

    template <int Index>
    struct
    neg_zero<Index,false>
        {
        static int const value=Index;
        };

    template <class SwizzleList,int Index,int C=0>
    struct
    swizzle
        {
        static int const value=swizzle<typename SwizzleList::next,Index,C+1>::value;
        };

    template <class SwizzleList,int Match>
    struct
    swizzle<SwizzleList,Match,Match>
        {
        static int const value=SwizzleList::value;
        };

    template <int Index,int C>
    struct swizzle<void,Index,C>;

    template <class SwizzleList,int C=0>
    struct
    swizzle_list_length
        {
        static int const value=swizzle_list_length<typename SwizzleList::next,C+1>::value;
        };

    template <int C>
    struct
    swizzle_list_length<void,C>
        {
        static int const value=C;
        };

    template <class SwizzleList,int D>
    struct
    validate_swizzle_list
        {
        static bool const value =
            ((SwizzleList::value)<D) && //don't touch extra (), MSVC parsing bug.
            validate_swizzle_list<typename SwizzleList::next,D>::value;
        };

    template <int D>
    struct
    validate_swizzle_list<void,D>
        {
        static bool const value=true;
        };

    template <class OriginalType,class SwizzleList>
    class
    sw_
        {
        sw_( sw_ const & );
        sw_ & operator=( sw_ const & );
        ~sw_();

        BOOST_QVM_STATIC_ASSERT((validate_swizzle_list<SwizzleList,vec_traits<OriginalType>::dim>::value));

        public:

        template <class T>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        sw_ &
        operator=( T const & x )
            {
            assign(*this,x);
            return *this;
            }

        template <class R>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        operator R() const
            {
            R r;
            assign(r,*this);
            return r;
            }
        };

    template <class SwizzleList>
    class
    sw01_
        {
        sw01_( sw01_ const & );
        sw01_ & operator=( sw01_ const & );
        ~sw01_();

        public:

        template <class R>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        operator R() const
            {
            R r;
            assign(r,*this);
            return r;
            }
        };

    template <class OriginalType,class SwizzleList>
    class
    sws_
        {
        sws_( sws_ const & );
        sws_ & operator=( sws_ const & );
        ~sws_();

        BOOST_QVM_STATIC_ASSERT((validate_swizzle_list<SwizzleList,1>::value));

        public:

        template <class R>
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        operator R() const
            {
            R r;
            assign(r,*this);
            return r;
            }
        };
    }

template <class OriginalVector,class SwizzleList>
struct
vec_traits<qvm_detail::sw_<OriginalVector,SwizzleList> >
    {
    typedef qvm_detail::sw_<OriginalVector,SwizzleList> this_vector;
    typedef typename vec_traits<OriginalVector>::scalar_type scalar_type;
    static int const dim=qvm_detail::swizzle_list_length<SwizzleList>::value;

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_vector const & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        int const idx=qvm_detail::swizzle<SwizzleList,I>::value;
        BOOST_QVM_STATIC_ASSERT(idx<vec_traits<OriginalVector>::dim);
        return idx>=0?
            vec_traits<OriginalVector>::template read_element<qvm_detail::neg_zero<idx>::value>(reinterpret_cast<OriginalVector const &>(x)) :
            qvm_detail::const_value<this_vector,idx>::value();
        }

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element( this_vector & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        int const idx=qvm_detail::swizzle<SwizzleList,I>::value;
        BOOST_QVM_STATIC_ASSERT(idx>=0);
        BOOST_QVM_STATIC_ASSERT(idx<vec_traits<OriginalVector>::dim);
        return vec_traits<OriginalVector>::template write_element<idx>(reinterpret_cast<OriginalVector &>(x));
        }
    };

template <class SwizzleList>
struct
vec_traits<qvm_detail::sw01_<SwizzleList> >
    {
    typedef qvm_detail::sw01_<SwizzleList> this_vector;
    typedef int scalar_type;
    static int const dim=qvm_detail::swizzle_list_length<SwizzleList>::value;

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_vector const & )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        int const idx=qvm_detail::swizzle<SwizzleList,I>::value;
        BOOST_QVM_STATIC_ASSERT(idx<0);
        return qvm_detail::const_value<this_vector,idx>::value();
        }
    };

template <class OriginalScalar,class SwizzleList>
struct
vec_traits<qvm_detail::sws_<OriginalScalar,SwizzleList> >
    {
    typedef qvm_detail::sws_<OriginalScalar,SwizzleList> this_vector;
    typedef OriginalScalar scalar_type;
    static int const dim=qvm_detail::swizzle_list_length<SwizzleList>::value;

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_vector const & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        int const idx=qvm_detail::swizzle<SwizzleList,I>::value;
        BOOST_QVM_STATIC_ASSERT(idx<1);
        return idx==0?
            reinterpret_cast<OriginalScalar const &>(x) :
            qvm_detail::const_value<this_vector,idx>::value();
        }

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element( this_vector & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        int const idx=qvm_detail::swizzle<SwizzleList,I>::value;
        BOOST_QVM_STATIC_ASSERT(idx==0);
        return reinterpret_cast<OriginalScalar &>(x);
        }
    };

template <class OriginalVector,class SwizzleList,int D>
struct
deduce_vec<qvm_detail::sw_<OriginalVector,SwizzleList>,D>
    {
    typedef vec<typename vec_traits<OriginalVector>::scalar_type,D> type;
    };

template <class OriginalVector,class SwizzleList,int D>
struct
deduce_vec2<qvm_detail::sw_<OriginalVector,SwizzleList>,qvm_detail::sw_<OriginalVector,SwizzleList>,D>
    {
    typedef vec<typename vec_traits<OriginalVector>::scalar_type,D> type;
    };

template <class Scalar,class SwizzleList,int D>
struct
deduce_vec<qvm_detail::sws_<Scalar,SwizzleList>,D>
    {
    typedef vec<Scalar,D> type;
    };

template <class Scalar,class SwizzleList,int D>
struct
deduce_vec2<qvm_detail::sws_<Scalar,SwizzleList>,qvm_detail::sws_<Scalar,SwizzleList>,D>
    {
    typedef vec<Scalar,D> type;
    };

} }

#endif

/* swizzle_traits.hpp
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
*/