
#ifndef BOOST_MPL_GET_TAG_HPP_INCLUDED
#define BOOST_MPL_GET_TAG_HPP_INCLUDED

// Copyright Sergey Krivonos 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$


#define BOOST_MPL_GET_TAG_DEF(TAG) \
    namespace boost { namespace mpl { \
        template<typename T> \
        struct get_##TAG { \
            typedef typename T::TAG type; \
        }; \
    }}

#endif

/* get_tag.hpp
fHiJ8BJxj46jj7AqNYgBRAwg4j5XHEUGMZCIgUTs0MQMdxyDiBhExM4WicFEDCbiMU3IfAw1iCFEDCHiSUFA2d/T4RV+NiKgiXwi8ok44ErVKCOOAiIKiHheEMbvvJdBFBJRSMSrrnxkG8RoIkYT8ZYg8G6/SVhhv6P6jCFiDBEHPXTNZapCRhwRIiJEHHblvMIgxhIxloiPXESpQYwjYhwRnwkCCtNUpwe3wv5d9RlPxHgiTkvCYam/kX59mig=
*/