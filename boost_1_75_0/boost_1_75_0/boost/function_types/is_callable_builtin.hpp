
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_CALLABLE_BUILTIN_HPP_INCLUDED
#define BOOST_FT_IS_CALLABLE_BUILTIN_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_callable_builtin
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag, detail::callable_builtin_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_callable_builtin,(T,Tag))
    };
  }
}

#endif


/* is_callable_builtin.hpp
4631Iu6fw505NikWaImyVmKOX9YYkmNpHnwrL/3KLJgPC4d5ormceK88DEDIQQeaynwnGDLgRSBnTOJISoPhybueBC7TXBKN2p0jQhuXxW/xVEYinjMSSZwOxyMdvvUxykxgLnmJ0zROxF0XI3a/wOn4Vh7M0Bypq0X8Q0oQ8Q/QoD64irnklEnHQeyBO7lrnaWHCjtnSlt0I9UOLHF+mMXgdUwEDbekgBPnQFWh/fZwlYNXNxahiBe3DNgtxFDnCuRzQOfSAkpzZi6pCtaOIzgUSrPxHAkTB1emCqFTTKBouAJNMg4Vxmh3nGJIwH0k8l5Q/F35JPcuoT7ffNRKd87ADUofk1K39JCwpJ/EilejsPSwmIS4ueLSUoUci13pDnIhL11qVJyD6CrkpZF0Fw4/ZivBJMdpFxdwgF/OoxCGNiw5oyiaQjhEFZRgp6BhRlg4gbxCq1AhKlB44DDtgtjb2SiX77VtXP4RKuAYB3gXKZWMhb/RzmTeStdYvRorTQ0QlqJX4SMX8AQXuCbHa4qEGbiiPwhHS3m+2WziPY/W9Qw35tBFYXfBnCm2PyZadaPXRshYtk28SHAIOjX60ol6NTrnUxtG/qsoXj5sgTfUUD1LXgmS1dWAZdFiQ03THFBbuS1RUe26iV4uUZ2MVZmADCGjNQL9zwTcD4cgLq7A5zL9dZ9ZdzsoynSc9UpvzpqzqACe+RMIPEQm
*/