// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/generate_index_binder.hpp
/// \brief Define macros to help building the set type of definitions


#ifndef BOOST_BIMAP_DETAIL_GENERATE_INDEX_BINDER_HPP
#define BOOST_BIMAP_DETAIL_GENERATE_INDEX_BINDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/multi_index/tag.hpp>


/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_INDEX_BINDER_0CP(                                \
                                                                              \
    MULTI_INDEX_TYPE                                                          \
                                                                              \
)                                                                             \
                                                                              \
template< class KeyExtractor, class Tag >                                     \
struct index_bind                                                             \
{                                                                             \
    typedef MULTI_INDEX_TYPE                                                  \
    <                                                                         \
        multi_index::tag< Tag >,                                              \
        KeyExtractor                                                          \
                                                                              \
    > type;                                                                   \
};
/*===========================================================================*/



/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_INDEX_BINDER_1CP(                                \
                                                                              \
    MULTI_INDEX_TYPE,                                                         \
    CONFIG_PARAMETER                                                          \
                                                                              \
)                                                                             \
                                                                              \
template< class KeyExtractor, class Tag >                                     \
struct index_bind                                                             \
{                                                                             \
    typedef MULTI_INDEX_TYPE                                                  \
    <                                                                         \
        multi_index::tag< Tag >,                                              \
        KeyExtractor,                                                         \
        CONFIG_PARAMETER                                                      \
                                                                              \
    > type;                                                                   \
};
/*===========================================================================*/




/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_INDEX_BINDER_2CP(                                \
                                                                              \
    MULTI_INDEX_TYPE,                                                         \
    CONFIG_PARAMETER_1,                                                       \
    CONFIG_PARAMETER_2                                                        \
)                                                                             \
                                                                              \
template< class KeyExtractor, class Tag >                                     \
struct index_bind                                                             \
{                                                                             \
    typedef MULTI_INDEX_TYPE                                                  \
    <                                                                         \
        multi_index::tag< Tag >,                                              \
        KeyExtractor,                                                         \
        CONFIG_PARAMETER_1,                                                   \
        CONFIG_PARAMETER_2                                                    \
                                                                              \
    > type;                                                                   \
                                                                              \
};
/*===========================================================================*/


// This is a special registration to allow sequenced and random access indices
// to play along smoothly with the other index types.

/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_INDEX_BINDER_0CP_NO_EXTRACTOR(                   \
                                                                              \
    MULTI_INDEX_TYPE                                                          \
                                                                              \
)                                                                             \
                                                                              \
template< class KeyExtractor, class Tag >                                     \
struct index_bind                                                             \
{                                                                             \
    typedef MULTI_INDEX_TYPE< multi_index::tag< Tag > > type;                 \
};
/*===========================================================================*/


// This is yet another special registration to allow unconstrained sets
// to play along smoothly with the other index types.

/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_INDEX_BINDER_FAKE                                \
                                                                              \
template< class KeyExtractor, class Tag >                                     \
struct index_bind                                                             \
{                                                                             \
    typedef void type;                                                        \
};                                                                            \
/*===========================================================================*/

#endif // BOOST_BIMAP_DETAIL_GENERATE_INDEX_BINDER_HPP

/* generate_index_binder.hpp
8mhGHFGbHEMqoR9zkGc9G9Z6zb0jNz1NV37ASHbvL5VLmetukwqbbtKhZHJcpnIFhI6FEkjw0/MxDBaoPw64S/PLG/yMHDL1fQIOOTtiXLs8cXDzJcpOkxEXOs/vYcz6kARiEQNf7e8GgsaZ26itK3Sagwd1/bwSANiVXgKsMnGMfWknhludW0QlddUVybTu3gzBsjHkD087eBwXZrT9o/Iw2nbzlzElgivhdtueujQvDwmn2rA/u3v9srEc3Duxt0XMpjH5t6q4DyMTC7vgcAzTybSa7zrvV+yT9e4bCBHwfGqew299vTL34AZ+/b6CRL02q5mdEk2pIaGxMH7gWgdvPIGiapmhMM/JMjlyrzO9WcXlS5N67JrYLAzpwPia7GIeoLriRlkWta4zDHkbvGZesJf2bzk+86sLM0sRq74Wyo/ckehDJwGBXCoHb/wemYUyh47N5CSprkvVSy16PUNofjuJvUAg7zjsXgUSrTQQj1w5rqyqOsYy2qFsYpN67sGDz+nu1m/7+vCFu5xrx8OdkQ4ATr+e4iIEyVvUJFXxWZDrp/WHKsInFw==
*/