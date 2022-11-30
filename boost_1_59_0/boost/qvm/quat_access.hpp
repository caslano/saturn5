#ifndef BOOST_QVM_QUAT_ACCESS_HPP_INCLUDED
#define BOOST_QVM_QUAT_ACCESS_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/inline.hpp>
#include <boost/qvm/quat_traits.hpp>
#include <boost/qvm/deduce_vec.hpp>
#include <boost/qvm/static_assert.hpp>
#include <boost/qvm/enable_if.hpp>

namespace boost { namespace qvm {

namespace
qvm_detail
    {
    template <class Q>
    struct
    quat_v_
        {
        template <class R>
        operator R() const
            {
            R r;
            assign(r,*this);
            return r;
            }

        private:

        quat_v_( quat_v_ const & );
        quat_v_ const & operator=( quat_v_ const & );
        ~quat_v_();
        };
    }

template <class V>
struct vec_traits;

template <class Q>
struct
vec_traits< qvm_detail::quat_v_<Q> >
    {
    typedef qvm_detail::quat_v_<Q> this_vector;
    typedef typename quat_traits<Q>::scalar_type scalar_type;
    static int const dim=3;

    template <int I>
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    static
    scalar_type
    read_element( this_vector const & q )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        return quat_traits<Q>::template read_element<I+1>( reinterpret_cast<Q const &>(q) );
        }

    template <int I>
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    static
    scalar_type &
    write_element( this_vector & q )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        return quat_traits<Q>::template write_element<I+1>( reinterpret_cast<Q &>(q) );
        }
    };

template <class Q,int D>
struct
deduce_vec<qvm_detail::quat_v_<Q>,D>
    {
    typedef vec<typename quat_traits<Q>::scalar_type,D> type;
    };

template <class Q,int D>
struct
deduce_vec2<qvm_detail::quat_v_<Q>,qvm_detail::quat_v_<Q>,D>
    {
    typedef vec<typename quat_traits<Q>::scalar_type,D> type;
    };

template <class Q>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
typename enable_if_c<
    is_quat<Q>::value,
    qvm_detail::quat_v_<Q> const &>::type
V( Q const & a )
    {
    return reinterpret_cast<qvm_detail::quat_v_<Q> const &>(a);
    }

template <class Q>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
typename enable_if_c<
    is_quat<Q>::value,
    qvm_detail::quat_v_<Q> &>::type
V( Q & a )
    {
    return reinterpret_cast<qvm_detail::quat_v_<Q> &>(a);
    }

template <class Q> BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL typename enable_if_c<is_quat<Q>::value,typename quat_traits<Q>::scalar_type>::type S( Q const & a ) { return quat_traits<Q>::template read_element<0>(a); }
template <class Q> BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL typename enable_if_c<is_quat<Q>::value,typename quat_traits<Q>::scalar_type>::type X( Q const & a ) { return quat_traits<Q>::template read_element<1>(a); }
template <class Q> BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL typename enable_if_c<is_quat<Q>::value,typename quat_traits<Q>::scalar_type>::type Y( Q const & a ) { return quat_traits<Q>::template read_element<2>(a); }
template <class Q> BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL typename enable_if_c<is_quat<Q>::value,typename quat_traits<Q>::scalar_type>::type Z( Q const & a ) { return quat_traits<Q>::template read_element<3>(a); }

template <class Q> BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL typename enable_if_c<is_quat<Q>::value,typename quat_traits<Q>::scalar_type &>::type S( Q & a ) { return quat_traits<Q>::template write_element<0>(a); }
template <class Q> BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL typename enable_if_c<is_quat<Q>::value,typename quat_traits<Q>::scalar_type &>::type X( Q & a ) { return quat_traits<Q>::template write_element<1>(a); }
template <class Q> BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL typename enable_if_c<is_quat<Q>::value,typename quat_traits<Q>::scalar_type &>::type Y( Q & a ) { return quat_traits<Q>::template write_element<2>(a); }
template <class Q> BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL typename enable_if_c<is_quat<Q>::value,typename quat_traits<Q>::scalar_type &>::type Z( Q & a ) { return quat_traits<Q>::template write_element<3>(a); }

} }

#endif

/* quat_access.hpp
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
*/