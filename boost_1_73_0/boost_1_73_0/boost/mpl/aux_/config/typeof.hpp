
#ifndef BOOST_MPL_AUX_CONFIG_TYPEOF_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_TYPEOF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/gcc.hpp>

#if !defined(BOOST_MPL_CFG_HAS_TYPEOF) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   defined(BOOST_MPL_CFG_GCC) && BOOST_MPL_CFG_GCC >= 0x0302 \
        || defined(__MWERKS__) && __MWERKS__ >= 0x3000 \
        )

#   define BOOST_MPL_CFG_HAS_TYPEOF

#endif


#if !defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && defined(BOOST_MPL_CFG_HAS_TYPEOF)

#   define BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif

#endif // BOOST_MPL_AUX_CONFIG_TYPEOF_HPP_INCLUDED

/* typeof.hpp
OFXxAk46ByyPoKTyCVPJKGaZQipgNRUg5GKzIUTDc2hZZ9PbxfJmNjyris9u50vLtQMfzBIq41R5htXCrWqBaUY1IWL/lIeWewlImjuUabyDSjlgsaZZUIlbJQCiQ0ODBkVbJUK3jfCxxlKCQgotuMjGBo1vaOofnEMeEkoP4SeaLeMzcTMnayo9BF7KzDq7u54vbm4/tYwJ51jQ43PrvGr2i9L+emZVQlQSNvep2tHV+cMbVsp01K7r1zGqELkijM/82LVXNga2wzCKeBAPAs91udvtupE3iGOv63BvwFaO1135cb8bYNwLcMB4rx/7+OzunhjgJcqE1lH80HrqiHX8t/0OUEsDBAoAAAAIAC1nSlLLu/T2FQMAAN0HAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjA2NlVUBQABtkgkYOVVXW/bOBB8F+D/sPUhwLWoIpHWh+3KAYy0dwlQNEbsNs8MtbSEyqKOpJrz/fpbSU6ctEXRok9FAcMmpdnd4cxynTm0TgqLZ15W1krTz0fc32mT2zPvYrNZ9V/w95vNsHhdbikAROsKLwuO0CwYov+ANZpPaHxb5uhlBptqT29z4cSQL2CnDKKQwZJSaFP+J1ypa7jGf9rSYD7yhvg5LBsh
*/