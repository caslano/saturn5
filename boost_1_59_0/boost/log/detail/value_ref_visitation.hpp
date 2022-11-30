/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   value_ref_visitation.hpp
 * \author Andrey Semashev
 * \date   28.07.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html. In this file
 *         internal configuration macros are defined.
 */

#ifndef BOOST_LOG_DETAIL_VALUE_REF_VISITATION_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_VALUE_REF_VISITATION_HPP_INCLUDED_

#include <boost/mpl/at.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/size.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifndef BOOST_LOG_VALUE_REF_VISITATION_UNROLL_COUNT
#define BOOST_LOG_VALUE_REF_VISITATION_UNROLL_COUNT 8
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

template< typename SequenceT, typename VisitorT, unsigned int SizeV = mpl::size< SequenceT >::value >
struct apply_visitor_dispatch
{
    typedef typename VisitorT::result_type result_type;

    static BOOST_FORCEINLINE result_type call(const void* p, unsigned int type_index, VisitorT& visitor)
    {
        typedef typename mpl::begin< SequenceT >::type begin_type;
        typedef typename mpl::advance_c< begin_type, SizeV / 2u >::type middle_type;
        if (type_index < (SizeV / 2u))
        {
            typedef typename mpl::erase< SequenceT, middle_type, typename mpl::end< SequenceT >::type >::type new_sequence;
            typedef apply_visitor_dispatch< new_sequence, VisitorT > new_dispatch;
            return new_dispatch::call(p, type_index, visitor);
        }
        else
        {
            typedef typename mpl::erase< SequenceT, begin_type, middle_type >::type new_sequence;
            typedef apply_visitor_dispatch< new_sequence, VisitorT > new_dispatch;
            return new_dispatch::call(p, type_index - (SizeV / 2u), visitor);
        }
    }
};

#define BOOST_LOG_AUX_CASE_ENTRY(z, i, data)\
    case i: return visitor(*static_cast< typename mpl::at_c< SequenceT, i >::type const* >(p));

#define BOOST_PP_FILENAME_1 <boost/log/detail/value_ref_visitation.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, BOOST_PP_INC(BOOST_LOG_VALUE_REF_VISITATION_VTABLE_SIZE))
#include BOOST_PP_ITERATE()

#undef BOOST_LOG_AUX_CASE_ENTRY

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_VALUE_REF_VISITATION_HPP_INCLUDED_

#ifdef BOOST_PP_IS_ITERATING

#define BOOST_LOG_AUX_SWITCH_SIZE BOOST_PP_ITERATION()

template< typename SequenceT, typename VisitorT >
struct apply_visitor_dispatch< SequenceT, VisitorT, BOOST_LOG_AUX_SWITCH_SIZE >
{
    typedef typename VisitorT::result_type result_type;

    static BOOST_FORCEINLINE result_type call(const void* p, unsigned int type_index, VisitorT& visitor)
    {
        switch (type_index)
        {
        BOOST_PP_REPEAT_FROM_TO(1, BOOST_LOG_AUX_SWITCH_SIZE, BOOST_LOG_AUX_CASE_ENTRY, ~)
        default:
            return visitor(*static_cast< typename mpl::at_c< SequenceT, 0 >::type const* >(p));
        }
    }
};

#undef BOOST_LOG_AUX_SWITCH_SIZE

#endif // BOOST_PP_IS_ITERATING

/* value_ref_visitation.hpp
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
*/