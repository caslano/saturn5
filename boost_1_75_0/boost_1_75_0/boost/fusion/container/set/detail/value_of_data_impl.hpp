/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<set_iterator_tag>
      : value_of_impl<set_iterator_tag>
    {};
}}}

#endif

/* value_of_data_impl.hpp
NHEm1cWS8fnvc0Dpfp5HTcO3VxEhPkN2pgTn3aKT3/axiCdPmSCfxAEPynbpeX9sgGHZcvvSLVvuFMraYWXsyLlHx2OcWwkTf20/JHz3uSoCvidWGOUY9/HKQH3ySQmJEF/jKhixW81B85WHA8vXHCOjjWAOdQ0UZoyXsPzgeAuWbePOPfS4x14ZddxXwLjH+JdehwTyNvP2RyFAk7a39D+skS84uqOR76iQI99cgXtL+UTb3mL7hsnbwvHRnv9kdIehXSaJbxkaqOqPdPy40Ycz5t/6djTm/hUdzPFXWw85xzGjDznH1/McJ84Mm+N3Rx3OeHM6HO9dd8s5vuVunOPO93U8x723HnKOzxl1yDn28xR7D2vI09M6GvLqu5R9G9Hu6OqsvG4qPu2ied3sD/nGFKnQ+bdcohkX9nYhwV57HRLs8d8gwb5lrTQubB6pjAt9Rcq4cM8QFyZxDhjK42bYFfqOGcAdc1JAbJdITVGEIdwV8+ovL2R3FyDLu28gshxMDwfthM/JkvNBdOT3/xJ0JMVsGSWz2Tukp834r4mQBD1zqrI+7KPaASWZQhOIPeN9P4dpifdznJZYwcygn8xiFjWJrmLfGihDwmWRnnMuVXqrzwSfA2VdNgCvlBcN7fxSFdtJedsc9a8ODB/L7KmTwjbhhj5hqZMKpFUaw8HbZawUvOoe5n0nKF8stD0moC352AJasjqmyc6A
*/