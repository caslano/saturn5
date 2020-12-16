/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_HAS_SET_SEMANTICS_HPP_JOFA_100829
#define BOOST_ICL_TYPE_TRAITS_HAS_SET_SEMANTICS_HPP_JOFA_100829

#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/icl/type_traits/is_set.hpp>
#include <boost/icl/type_traits/is_map.hpp>
#include <boost/icl/type_traits/codomain_type_of.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct has_set_semantics
    { 
        typedef has_set_semantics<Type> type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (mpl::or_< is_set<Type>
                             , mpl::and_< is_map<Type>
                                        , has_set_semantics
                                          <typename codomain_type_of<Type>::type > 
                                        > 
                             >::value)); 
    };

}} // namespace boost icl

#endif



/* has_set_semantics.hpp
ql1T16/AlxEto1oGWup6Foa1jGgZ1TLQUpfroMsV+TKipS5f5ctAy/RTUMQHfpFw6jI5Psj1QZ4P8n1Q4INCH3SwlywWr1MHD7Yf5X+U+E38kuT6iW+xQr5Ovsi4/oira1KvkHr6KOgYD+fwv5E6MPjV9N/Hr0tuCV4hT4yXVcTLRsbLEk+fYxJn4XByEUksIsmvomFfRrSMahlomaNlrpZ5iWXgL4e6JF5KTosG4dQg4oOoDwIfdPdBDx+U+KDUBwf5YJAPBvuAV4slidcDXPvEIpJcRAvYSNpOvrlSG9AH0dSG9EFh6luQRjmpS6Uvz3c1Sn83NzXKS683NeqUGnVOjbqkRl1To26pUXFq1D016pG6DeHUKJIaRVOjIDXKSY1S1y+cun7h/PQ2SY0KU6MOqVFRatQxNeqUGnVOjYpTo+6pUfo6l6RGpalRr9Sod2rUJzUqS436pkb9UqMBqdEBqdGBqdHA1Oig1GhQapR+wzEkNTo4NTokNapKjYamRsNSo0NTo+Gp0WGp0YjUaGRqNCoeDLHHdjhxljyPJMeiSDyojAdHTx80fVBo+qDw9EHR6YNypg/Kmz4oHwlRmCIUpYD4biiXuEjILlNAhdSBiqgjdaIYdaGu1I2KqTv1oBIqpZ7Ui3pTHyqjvtSPymk/2p/6UwUNoAPoQBpIB9EgGkyVNIQOpkOoiobSMDqUhtNhNIJG0ig6nI6gT9BoGkNH0lE0lo6mcXQMjadj6TiaQBPpeDqBTqRJdBKdTJ+kajqFTmWzhilKAeVQHuWzoUNsaStMEYpSQDmUS3mUTwVUSGzjaIjCFKEohQxCCUmcmSe+EQ3sLCfxZTjxdfI8kuBw4pxxfpj60v7UnwLKoW8s0HvbQj/i507XUbc4EvGRvXUuiAd6GtazbriTvgxpyRvUvhpGfG0dfFDkg44+6KQjbiTsg4gP/KDOq9HBVwXTB08f7M8rUV+mIOKD5LfYSlpGtHQPtMzRMlfLPC3ztSzQslDLDloWadlRy05adtYypmUXLbtq2U3LYm5KKNfO8uysj52V2VmBneXbWV8762dn5Xa2n50V2tn+dtbfzgI7y7GzHnZWYmdhO4vYWWc7K7WznnbWy85621nUzmJ21sXOKuxsgJ0dYGcHsoHZcTiL2llgZzl2lmtneXaWb2cFdlZoZx3srIgpmFC8bL942YhB1+Qvve3EMWEONulhNDVkxV8dmhNlrkrL7loepKV/v1TLSi2jWpZoOTheVhAv6xMvKxt0Ta+lt41PnvObkstAy9zkUq+pmMDTkn0iOeHT0QfaY4OYXlBlvC8uSA97+6uDHB/09MGQ5GuVSHIR1SKspbN7oLdZ/nYrX8sCLQu17JBcPSvyQWTgT3KjoZGDruXRb2cFiVE0cR7YuaQwcd4tcV6cOO+eOO+ROC9JnJ+bOJ+aOO8UTi5CiUVfLZLYL5Rc6KtIchFNLoLkIie5yE0u8hKL8lBykfyB8uQPlCd/oDz5A/uFk4tIcpG8SP9QchFOLiLJRfJ7FaHkIvm9Yi0iyUU0uUj8hoJwbji5zIlqKY/q66i+zk+9wIzEyzR3lM+hjsmkzvEgFg+6xoNu8aA4HnSPBz3iQUk8KI0HPeNBr3jQOx70iQdl8aBvPOgXD8rjwX7xYP940D8eVMSDAfHggHhwYDwYGA8OiQdV8WBoPBgWDw6NB8PjwWHxYERq34oW+J6U64M8H+T7oJcG6R2xjw8O9sEhPqhKPeyikfQwmh4GTF6G/DCc7wN/Bki++j4yOfcZ4bGTGkR8EPVB4IMcH+T6IM8H+T4o8EGhDzr4oMgHHX3Qya8NR8ec2OKJRyUOcOEOocR5OHGelKhfIGo=
*/