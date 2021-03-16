/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONTINUOUS_HPP_JOFA_080910
#define BOOST_ICL_TYPE_TRAITS_IS_CONTINUOUS_HPP_JOFA_080910

#include <string>
#include <boost/mpl/not.hpp>
#include <boost/icl/type_traits/is_discrete.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_continuous
    {
        typedef is_continuous type;
        BOOST_STATIC_CONSTANT(bool, 
            value = mpl::not_<is_discrete<Type> >::value);
    };

}} // namespace boost icl

#endif



/* is_continuous.hpp
gCeQfiAm+PHLgCeSfuApwGuApwJvBI4BPgI8A/gMEG1ifCPwbCCNi8cmi70L2X2LvQuFMhS5gbmcaTN1KEPFEapj2gIdymDHgjQ/zVRH6VAGW7iIvr2iRt9YSyu1tK8tbYulkf2g0NrFDO0oSzvW0q63tJss7U9L+8fSMpIMrXWSofWytH6W5tix01iHRtTGGkdcVLFrD78XuLZ6t2Jwb5p5L2ys7EpbOvnWSZmskPBeDhkVEqfeseTdgTp7/to=
*/