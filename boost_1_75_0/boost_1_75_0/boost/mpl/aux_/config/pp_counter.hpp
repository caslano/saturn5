
#ifndef BOOST_MPL_AUX_CONFIG_PP_COUNTER_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_PP_COUNTER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_AUX_PP_COUNTER)
#   include <boost/mpl/aux_/config/msvc.hpp>
#   if BOOST_WORKAROUND(BOOST_MSVC, >= 1300)
#       define BOOST_MPL_AUX_PP_COUNTER() __COUNTER__
#   else
#       define BOOST_MPL_AUX_PP_COUNTER() __LINE__
#   endif
#endif

#endif // BOOST_MPL_AUX_CONFIG_PP_COUNTER_HPP_INCLUDED

/* pp_counter.hpp
kifZnAdzDWkF/0eXYi7fG4/s+nJ049UuJFFE4ntBQeP7u6KCiReAX7Yq3duuaeOEU9MXt8U29iTi27ecHMNM3ckZ+VhRkkwqpbSRkUfC2Asn3j/eip2UchZ9Z792l6un2sun2ktgIqZmHzx65IfxHyXOVfwFCNvIW+FG1X+Fy3px5G8V8Y2XnrMcvTxJ8uSyXM6rrUwut8MmIhqSlvZNiimcnOy/u1sXGmpvst7asoERTyAiXt+A39iAs3WOR6C2YhX+nUDqaUFiDnUmiTK4gMa2efrrkvIhtzWVuedoJO94ec3P/1Wgg4UxMF4d/WGb0Z6x2nGyqmasrrKSnrl6clx97KANLfxPurrTd3B+jqH561wtD4tzBs1ztJ+YfzcuZ88C+RUD+jpT9o/lDY8/p4cyWfbjrZNEgfSIpLVpG82OXUZGww9eRhrJrbW1NY2NXaWlwKK9s94QINGPP77Fds0EXBo5CrT3UUAriO6OxnqMFmVA/C1xjWIasXNhG9Z/dF3w0WTfmUqDRyBpWRBL1DMHSV2B2lMC0nlHxPufWKZDy0KArLPHvgwfDh2J71zcmy5tr8igWEDcwrbpAyuiV+2/sUyJbdOJGIv0qZU0Zv/kBPFyzG2Y82L+jWUiuaTnO6D/Qm6wGkWw/uevXM+Y6q7kVEK/k25Ph5Pc+lZ+QSA7J3YXiTjGYKzizQPb99jwPHxagR9JmX+sldzw
*/