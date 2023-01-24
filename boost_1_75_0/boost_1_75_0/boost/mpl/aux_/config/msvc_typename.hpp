
#ifndef BOOST_MPL_AUX_CONFIG_MSVC_TYPENAME_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_MSVC_TYPENAME_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
#   define BOOST_MSVC_TYPENAME
#else
#   define BOOST_MSVC_TYPENAME typename
#endif

#endif // BOOST_MPL_AUX_CONFIG_MSVC_TYPENAME_HPP_INCLUDED

/* msvc_typename.hpp
barWorw6SPKuC/6RA/hrt6BvcsDE6iCqOLuQ4zVSPZtvgBmn5bptyHbuJqarZSnbwwheZSVXSAsDswwlvg411h4lemU8mqXLCjg0X7VyqkVDM7cB+Nk3RPinV9sZdbw5hfLiunD5V/U0xl8MFFUmOZapFl5IsON31O2gL+1usrIju50/QBo3ydeRXy9H9uzmOdc3uLu2trYcHR0r9bUca+Rzh8dioj29Nf4Gb4U1lDCcXoUOf+PzdP9iecrezqO4npyzRTfGIc9hLyUUSd5Y/EtMQ6Otk0tEDS+dPmrNX8JO2tfSX9YfqF/DysQ0obEvx1nSYmk5J9jqubgCBIr/WT1ecobExBUcjjiYdDd+raH5pN+jhUnCN42O/SeBx1OJnXGaQbB0LJw0HEy3Yr7Sut8oeZRdGMXx0qnTrXQql1C5l5aGpIf4G3OYE/lMyMt3b1MoMXn3M4CCEH8CSkaSIfmAhi79xmeJMpGRqkiN0XEyidvSmleh5GRyUr6gnppFKTeDPjYaW0amhER0mt9L0c/FRNbTU1JP7+B4M2kh5y1Mkn9ogyMF6HOyd9wyZqgnn6VpWK65nJaCN7rPMGbW/bmnuBiq9BQpklKQSYEVR+tHhF1Bvhz9LB6OlOOaw/GFlzfv31gRVanzVdPqOl4A4BEA2OD6lC1jv2IHD+wgz3GF8yOj3LXpkdFgwkqhHd7w6OiuZdXwly3rKGjo
*/