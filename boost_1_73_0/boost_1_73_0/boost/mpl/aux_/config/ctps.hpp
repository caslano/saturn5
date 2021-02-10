
#ifndef BOOST_MPL_AUX_CONFIG_CTPS_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_CTPS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/config.hpp>

#if    !defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, < 0x582)

#   define BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC

#endif

// BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION is defined in <boost/config.hpp>

#endif // BOOST_MPL_AUX_CONFIG_CTPS_HPP_INCLUDED

/* ctps.hpp
TyS1r8fssqVnS9s8Z3yrIJCyqqoe7lReZNjju6BbF2wWzWM57H8ZwrEVcBbIVrSIH2bgV+B1f5pNvjwocL++G48pDNfrA5N/lopBB1efxQfvzB8Af6n6j0q43sfs2Ty0pGnWC5bpeg/NAKk1YQmUINRDDIly8APRgOcSy8UMtw2WKYrSktU2GwmeY2gjv49bR9w3bTsrtCOeufn+zSuLCEBvykx2XybzxUM07YgbrbHg40t52RGdf00fylMmPKG04jn6Lw9n0C78DA4x2TxWV55+Ib8BUEsDBAoAAAAIAC1nSlKD+NPVsgEAABoDAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjA1M1VUBQABtkgkYJVTXWvbMBR9F/g/XFr6UubKTjtohQiULDRhXWwSty9jFE2+rs0cyVhq2vz7XdtpQmgZDIP1dc655x7L0qPzWjkcM1mZwtLwB7evts3dmM2yLO1fcDfN2ORheZ+k2dMkWSymk+wpS5jkB7DkA5+dslNYYbvBNnRVjky22NRbAuTKq0GUxxcxjKIIku/sm/IoIHvBLxDdwMJu6CCOIL4SVzeCIHc/qLQ1Ho0P79E8+1LA5X4n2zbE9vjmeVOryjBGkpIPpSTfle49TeqqYwyedL8g
*/