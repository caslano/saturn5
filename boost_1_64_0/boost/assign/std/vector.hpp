// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_STD_VECTOR_HPP
#define BOOST_ASSIGN_STD_VECTOR_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <vector>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::vector<V,A> >, V > 
    operator+=( std::vector<V,A>& c, V2 v )
    {
        return push_back( c )( v );
    }

#else

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::vector<V, A> >, V >
    operator+=( std::vector<V, A>& c, V2&& v )
    {
        return push_back( c )( std::forward<V2>(v) );
    }

#endif
}
}

#endif

/* vector.hpp
P6G6qHis4dcbXY+WROd+SQyrh9zPutdDdHqwHugXU0P3Cekn3ifJtj5R5drq0ZgUXo8PzetmaD30PbB7PdDRx9ctKj2gYblmnkRdAscXZbNNyg45vnzJ4fX5E/lzHOojp5xrfXIs9Vmt0gMaFr/sTqjParVNl227tk1OCa/PR+TPC6+PvveOdKzlWep0nUrXWrpOeZ1QJ8pmmy7bVqeMVOc6eV3qxM1oxDp5neuEluX70p1bJ8q2H3fvu9SpyKFOcs/vWp+i8PqIRrA+RZ1XHyk75Bmmt3N9fM71oUHc6+MLr49oWPzmO7U+lB1Sn/q08PocG812h/rIs4Zrfeot1+sbVbrSkLqQfhJ1CVyvb1TbVLm2enjTw+vxZ/I2ONRDnk/c3+1Y+mWtShcN3S/kOYm6BPplrdqmy9b+NuUeN3+bjvtpuPnb/Ej5q2R/6afHPxz5XuMi36XL/7zi431u/idu/htufjud56/SWbHUXPyFlP+Jz5B3+TIeUCSx/UqlIz8lp8lImA2z4Sh4FsyFn4bXwhy4Co6CN8Ax8FZ4DnwAngtfkO3yDWN5p87vmexXvmGs/U5MDoIpsp4GB4s/yhA4AQ7T/tvyrhvGS3lW/+25Ut4XYRycp/XIK3pxDnrnid75MBaOt+j5Iuzv+6K3Xfa3Q+vxRwS9vaL3U9HbZ9FriGDnDNHzip0FFr3GCPt7QfRelP29ZNFrctOTmG8mu8I42A0G9Joj6D0g+9si+3vQsr+WCHp3it5dorfeGsMpgt4NordG9G60zhOIoHel6NWJ3lUWPeMtd72FolcuehXW+QUR9A6J3rui9541ZlQEvY9F75joHRe9clNX9LaJXg913Ov4rvWZMBGeA5PhGNgbzoRpcA5Mh1+EA+Ai2AfWw35wk2yXeQTy7oP9yP6s8wgKxc4isbMYdofzrfaK/s0O9uaRrw+cKNefSfBcOBleDqeIvdNhCcyHdfBieA2cButD5l0cjGDvTrH3WbF3l9j7nHXeRAT9t0T/56J/QPTf1vryLAq6O+jPEv3Py/l8OewGZ1v0Ew+47/8V0X9V9t8i+3/N2l8R9E+T8/t0Ob97we4wEep5KxH0H5X9Pyb7b5L9P27Zf14E/XtFv1H0vy36myz63gj6t4h+g+h/U/Rv1froRNC/VvTrRX+F6F9nnXcTQb9a9H2iv0T0a7Q+f0TQ/4PofyD6fxT9Vot+QwT9f4q+ofoPSP/FQL5NyzyOjs3JsfpeHkbE31L8K8N9K2eJT+VxaPWd3II0BXwl+btuYqhPpJ4jo/0hS8Xv8SiifRy1f2OYb6P2Z/Qi2n/R2W9R+ylOd/VNFB9E/A43ItuRg0jcB3yvFPEitcg6ZDtyADGDVw5B8pFKZC3ShOxBjiIZrXFGHlKKrEG2IHuQViT1wzhjDDIPqUcaP4z6O0aX6BJdokt0iS7RJbpEl+gSXaLLf3I5Rf7/lRXzlfv/Sfn/DzASlC9a1i8MI9YoLVtQvKyytjAwLGSo+QGGigEovp0OsfZeMH1gX9XjSSUYXRNwxugRjH8k40iS192PTNJj2hxDOt0ef8/VB+Nssb0pRsbAsCFd6MnhnbS2Xbn+W23WPv9vqTwfSB0COpna5393i7nusX5nUX9r+4jKu8+YasxV9v2dSt6XbBheXqj+g79TUiNLUZop7Z9HYLZLjqVdZF3axbRrbNJpyl7e7Y+2jxfuF1/+ocHvo6gPoyS+pttIufGX1NQWqq+ySR8XZtj6WPIPVX28d7CZVrrYN0rGCV3Sl0i61zG9Yslin8TPCqa3+xjBPtsxQpmsK5vUtgzLtiWyLUtvU/u2zSUpcvDjf8n0swhpp7KqhRVVZY5tRN4=
*/