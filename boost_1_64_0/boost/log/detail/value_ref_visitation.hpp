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
S2//NCNj7U/n1Zbd9L1Doe0ZvxX/4z4acHr+h2uu2z7l/NRD7ddfGcoOcfLsK2/Ee9zvXfilgkPRN2+9YluXN/d87ytPO86HMv5LDurNRo5BXvb7+wgy2vsNqt/Y9Vqeh2jYXtrXfgrsCXvDNNjHr68+TcN3lfCh++qTYRcNV2S+V3g/NVwsku8toPiLgJNgCpwMT4PnwuFwCsyCuXAMnA7Hwmlwgp4fgQO8v+Wwnd4nAukVbPsQ/8u9v2dwnvrvgCxW//3wFwn7wzh4murjdDgCDoRnqPu5cBjMg8PhLDgIztXzIzDN1O++utiVb23znIy/za3wV4TUNaPXTNVrlur1TNXraNXrGNXrWarX8arXcXCCnu+MpHxsj3XykW0fRzijZ9D/j2xE6nDb7jlfi60Aemwth2E55/VIwkyv7QVeFeGkInX8PQ6Onkk4pA7ZhBThthPuR44i8bOwReC2BdmDDOH8GIy/OsLJ5e80eJi4Kvk7h7/rYS0sGUc8/P0mchvnO5B9yFFk9DrsHEj6bMIg1+N3OVyH26ZxhOfv7fx9cBzn/N2AJF9DepEiZC/n2ya1cw7DWs43IqlzcIMbxqMDmMH5rvHcF83P5u+DuNVNiHFq5+AfSb2We8CnkeQJxMv5OFgL65FtyEGuPQtvI1zMXMJch20KZiOj+bsAKZlLvHATsgtJOxv9wFrcb0NyON8Ni2DUPPSHjL6eNCF1HnJeiWy6nvvCHch+ZC/nh5CjHjfuH3UD90aisgkDU/OJC5mNrMNtOdwCN3JtH3II2cV5XT5uSPKNxMt5HtzBeZHnHNbDYzDtPNKKFCHXI9uQZ5E3kWPIbvwlz0dHyGKkDrn+KWxO8ADXNk3Ez3ziRHapbStjfaN9y1nAfdcTBtmCpHK+C2bCN2EBrEVuQ3YiJYTZQ573L2i0gR2CMRvI/wZYQJ5hOqyBG5A8/i5HGjzncB/0t5Vtxi31pkZ7WQZ8lvN8WIscKOAesAHZjzgLya/Hnfun3cw9Oc+BubAIqeHvOngbsp2/nbNjnA2edxJ5GjmIRH0/1hmA5CBF3w/b38JH+Agf4SN8hI/wET7CR/gIH+Hj//n4TOz/lyy9VIz/zomv//ea31j/PLX/17v0Kypv9NjBLpI+fE+3/aT8As84+rKll6o95XqvTb+W/j2vDUv8L3En8W+Oa1+zjzhNv/yx4RoH7j28tjS5foNbQEoWupFOLRLcvx8YzwWpDockxayL1W2JrOEVYP+CZi78QAl/nbvAoZ/AjXC+iAyjf78D115HN3UJpIWbjcfzQSL8DW5vqPsQ3KHp+w89t7xdYrWkg8WWSnz2leu9YwdqffYVdNHopn3/Z6h9pV5t5t9wyTO8Et7keTYl8mwIUEg8hasrS4prMJKpPnw2WjMPX/xXud2w+M13O9ufjfhxbc9Xnk2OXF/qxlLWct0u9udSYn++Kfpczpbr5W5nQs10k6z2GOIw9tKbxR5Ts7LyotVLvbaeQwH775RQon17rR2UsD922vGkv+N0NWs43ljqi3O1o+HKSwPWr3xXwk5D/6cQDjcTroPZv6uTnN/Nsz9f9n0a1NUqUjZSW7n3i7dc8NwCbNcxlrIS36SspOjeFTeLP6MnYz866oaa/9B2e43dLhPajnOz2Iny7rly3KwPVuZ/sOamT1LmXZMdah7If599p612N/s8ltB2N7t9LbT9zj4Pp/l5Kfu9daXW67UwFdmjhbFYbS1LYTZcAXNgOVwMV8JiuAFeBFfBF2ENfBuuhu/BS+BheCn8CH4JfgIvh8m6p0N/uA5mwmvhaHgdnAdvhIvhengR3ACXwIvhZbAKrlX3q+By754Xpr6gjtT8dUc=
*/