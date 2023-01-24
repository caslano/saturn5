
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_PUSH_COROUTINE_SYNTHESIZED_H
#define BOOST_COROUTINES_DETAIL_PUSH_COROUTINE_SYNTHESIZED_H

#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/coroutine_context.hpp>
#include <boost/coroutine/detail/push_coroutine_impl.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename R >
class push_coroutine_synthesized : public push_coroutine_impl< R >
{
private:
    typedef push_coroutine_impl< R >                                    impl_t;

public:
    push_coroutine_synthesized( coroutine_context * caller,
                                coroutine_context * callee,
                                bool unwind) :
        impl_t( caller, callee, unwind)
    {}

    void destroy() {}
};

template< typename R >
class push_coroutine_synthesized< R & > : public push_coroutine_impl< R & >
{
private:
    typedef push_coroutine_impl< R & >                                    impl_t;

public:
    push_coroutine_synthesized( coroutine_context * caller,
                                coroutine_context * callee,
                                bool unwind) :
        impl_t( caller, callee, unwind)
    {}

    void destroy() {}
};

template<>
class push_coroutine_synthesized< void > : public push_coroutine_impl< void >
{
private:
    typedef push_coroutine_impl< void >                                    impl_t;

public:
    push_coroutine_synthesized( coroutine_context * caller,
                                coroutine_context * callee,
                                bool unwind) :
        impl_t( caller, callee, unwind)
    {}

    inline void destroy() {}
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_PUSH_COROUTINE_SYNTHESIZED_H

/* push_coroutine_synthesized.hpp
6ynEEuJ+sxIFz3R5gJ/tefwYdO93J6U/ddUAzAj5DAfUb4jti0HFQD964Y3OJvhE+vyOHJGEdRsb2GMCwtmIE70vRK5ACA22CA3VawA2TlCVbDBOOX2lYT8cI1R2/RS2MeQnfHkzGZnfMKUwRUrnw+ONUhfjHfXA1mLTdCkje1+SBPqbN+Njuuo1AZYE1w6wzZVnkIZh2GdmZ8yvrfC8G2RdIe4bcQkSE6DuokyPwaWsNOQFPD68pxkSKde7A+DtPq8J4nkJX4Ye7Kden8YzgywRQrhZ16RDEDMp3mCba9+Lp+haMYhMRbJf1E4Lzd2lWJeV+wFg5BY9yg8Bhj/fk+/EIsXu7ED4Wxm976p1Co0rrdd2RwCT0+6guUaBz5f6NIx+EgdNByAZ45qLDmb2RtY/z6FyvpkuVZ+rLmtcb0GDCON/qMwP78q88XBfRCTbq/+jMun+h8pUdXawcrYAAv8tMP289XVcxeC6lzX84Ymt1gm84QmN47H9McX8MRoD4axDGYrbs9ESeiSC+32+dcbxDLArogFWJA+G2vrv7wz/+GsR2uIEqkWXVPbwLlsE2tnaBj59iELS/1lr3PNFX5QiSv3Uy6/TSrfJcGQb0A6Ae497wQfa4I+t+2teZ8miiDatiW7EcEiNmpygJPGVen4IU+RR2uf4I0yi+kf1fFXHX1hiSjW/rujyQjz0C/emIvlyYUxfeWrRv2AZ
*/