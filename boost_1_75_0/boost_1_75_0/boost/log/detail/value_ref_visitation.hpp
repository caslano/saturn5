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
yDyTld+L5XdBfuOOAZd/Ie7nkBLh4SwOBlpH+w6y/R592uTvEP7i9kAmg/zjg1+XKc2UB1+aq4eAq/MGvIoE7nyoT6MH3uVwR+qVCC7vwUcy8J53Rr43UqjmkfQ6vIpUiU/fJn+vebjPAdpSn7YetIlSnzYnf2tLFN8U5UTTNlDKFYkyP29DOm8lKm/QwwfkO03J3ojwaPESPo9Gr4d4JBiPzznhMSnxaKrzrvvx5vnxmjjePD/exUA8XT6V5/l+vGbO83w/z1c83G9aPNRWavLcWxrm0ekt8Hm0eMPEYwGVQn3uRvC4WGrKPVVq2udGqS5Luc+vlWq5IlHulwXzpF2WdoLhhI5X4cdrQx2kKvx4daVu/dtt3IKbyxIvxXW30I/XEojHde6nt8iP187xFvnx0oF4KCt0C4STysF1TD8xHXPZK7iecNdG5QkjZKnEayUYR9nRRsTsPMEdgipiNkzQQ/k5RzBBcFcqHuOkIH1mxlN9FGuVMwQ3SlR9II+nCLBWw/rOjCvUneeXpV3qvKFMlSWJspfpurPHUp7Hko43XIK+SPktwz0x1VYmnj2ukF6pHw95xHr0ZJmpOx2v0RljHV51qsxvzwsoI/qRT6vGUht/TxNtwqfF+ghMoMcq2nk+bRPTzvNpp+lLL/IptPgkpA3Lpb3uknyqJcRpgksEVwlaiKhK2qNF2uMC+AEhdV6s3gcC9VBr1QM+
*/