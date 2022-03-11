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