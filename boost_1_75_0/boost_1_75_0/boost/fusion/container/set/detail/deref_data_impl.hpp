/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/deref_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<set_iterator_tag>
      : deref_impl<set_iterator_tag>
    {};
}}}

#endif

/* deref_data_impl.hpp
4BO81YPFr6WjkR6ILU8U926O8Vanw01D0twwOpmOMYssQiEGUCxLwZD2jnNQOLNCp0rLLAjWNwARwR0uVgrftj1FXqnF4GTZA+scsu5tUQdSr+JW3Ox8odvIXZXeHvLtFtc5web6I9zo/3mnFX1nq+6mCoF3ep7vNnIFN+igqDvnyBeZjvPZqfKmcR5MwV6cH7wuvUImvAM+A+KQZXIZILuwN6aRXRgwKG/BZMEuhREy+ZPN0N0uI0i+hLyHi3FNe9pNXlgU7NAlrYEttccxCdSg2aLYm5liV0o0NxonY97SInPYz3vB1IpsjMCAtrNMcuhBBwFx93VHrdgT/cG/gEUcwrmw65e5OGoWbGqbFE8FszdavGBIANK1B8Tulu0BR+ndWDMUX52dFqg/ogn9cQBGb5ntxJ7QqpKdf/Kk0LMq2SnWqEnt4kH6YvC/ZON8My6d3MLOiCesQtJ+MOXCKzsVPU9/KkVNIHxfPA6kSzztjAYCwsulJLKFqwdBijP4lvQib/WQOBoQYFK1APLjmW2XiiPTIEtlsrX+hJRSNXFo2oYO3SUSLZUxfX6pTH9xA/TMmfzg6yiNpu9aJxIBym5YJv7rpzVXdsMeZmlLZCWbDXuk1bBYNDAaPp74xbLLtawulkqGzJxGU45vaXfWCcPjqYOHXf7oxnoLlmBHa3Xm1N5C0exSLGkj3bQmwpq27TxtzWraqtoFIX8V
*/