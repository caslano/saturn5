// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//  
 

#ifndef BOOST_ASSIGN_ASSIGNMENT_EXCEPTION_HPP
#define BOOST_ASSIGN_ASSIGNMENT_EXCEPTION_HPP

#include <boost/config.hpp>
#include <exception>

#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

namespace boost
{    
    namespace assign
    {
        class assignment_exception : public std::exception
        {
        public:
            assignment_exception( const char* _what ) 
            : what_( _what )
            { }

            virtual const char* what() const BOOST_NOEXCEPT_OR_NOTHROW
            {
                return what_;
            }

        private:
                const char* what_;
        };
    }
}

#endif

/* assignment_exception.hpp
VY9lT544xe6fwXEuUF2TkzfRVkRll9di1dSFmHXG/nEudSg/Jy43DTvxmH/+/qyn67bIvqsfuL8qvrGdA2tez1j3kJBV4OwQXsuV89MauccKvy8OW+Yh35a75dsK13wr6x/fSM6ffI5UcBydVz5P2R+GZwl/epYy31+gczifY6jrGgWITflZjvsbFijIDDIiDJgANlTn/NFzLM0rKM5Cobh2fYXw9vl9vO7Fu+SubfRQf3HYFNmn/wm5nzccRpmINuBt8PymP3VW/eMNdcQuxS1vynFNByjubkOQ0kRsVWqIZ3mOVa48TxzP7ccsoyQeGyfbB9Pyhea7dpzChxm5XHD8zpQ/G1H4wml0dpc6ksNx2UA+8VjvynrRNTzlIUrfvQ7meSGXKWwftAosMo1EtzTKPNXLPEZxD4XbK+Mmu8Utr9weketCfEzPfyOe7GxRIS7I5/gwPcce3K6wl01P7Y+VFN8o2zcPkNtkIDd+PUTp9Kd0uIxzOvTQZP2YQvHuN3hrx4TznL8KCpdkaCBmKKcVM/lPhv9ndL8W4zhDe/GEIVDbxuHzcnqa+TNnKY7BSPUaP6OTVHfl52jn7Zzqooarx27OszhzZ9Q3gcLZJsrieudiMyJZqIDEg7B31qH2E9pM199uwjtwaTcVeqhzStzqnFIPdc5SWTfYy0I413WNyI/zu6zvPH9Xy9TwHr6r5S7f1arbU+Eu7S8+punTL9P79P/tffrzqU//pdjuV1/uU/BCwcd1g3MWHhyEflRKP+n7mGbDLs1e8nSfURHnLPfNu/V9/U/ScyiOXPbd/CGPjrqnxYgngtv5nvGuAyim8Is2r/3ws91xcfN3p5fkrdh07ubqBnY65D2WpUthb8PvbbCCx6hFgQPAXtxXPp7HpOVyn3gBjzlbDo7keVGjwTXcF/4o94WraY4Fd4Hjef5NDniBxxR+x2MCA9Wx6mAIOBmsDeaD0WAhz8eZCnYHp4G8Fzy330mOwX247gX/La/FfoHnE10GG4EXeYzi96zruMzprZFtSNRv/FzUJt9yTq8Bj3lsymu5N2fdSQt+Ti15DGIsWMRjC2ey7mORmjaP1YsHy8EO4MtgEp+/K/gj6zIMPE/MF+zJxw/I7z21hej6VN3HLtaNzOOxkQvBMeAicC54D48pXAb+AbwX3AzeB+4Gl/PYwfvBb3ne1Q/gatCooOzzmMG1YCz4GNgWXAd2AMvATuDfwfHgejAX3ADeC24E7wfLwXLwSbAC3AK+AP4R3MfzsQ6A28DD4AvgSU73K/BF8AK4HVSQv18CfcBXwLrgq2ATcAfYAtwNtgH3qPkG3Av2At8B08B94HDwPTALfB+cCB7geXQHwZngIbAUPAo+Ap4Ad4B/Bd8EPwEPgp+CJ0H1ej8FT4Lfg1+ANfC+vgTbgud4vtw/wMeM16fLMWE+VuIm6C/K0e8Pfc5kWHf9jqmrfY5aYzAD7txNnueqTb6G3iegGwir6n+SQa0OaPamqvVA+1U9EGwiHngG7EU1DqjqhZaD7rqhXawfOgOWg6Zkp54oNtm7rmi5B33RTvw+ButRb9TDrjtKAofBPr0J4WE96ZKOqfcILod/BayqVzoManVLPAdP6pcWsY5pD+w51jXFbVb1TbA9q9Y5xeL4uR1GqXtKhjsHVquDmt3TqYdajd/lsKo+aizOUQzu6emql2rnMu8P3OzUTy3f7KqjuqjRU8WADl1VIbgadhusVm9Vthlh4XfOu/6K5w/CrjV61GNNht9y2ArY/bCe9Fqij1O3lQg7lnVcZW56rm1wXwZPqoR113ldxLXUTHXqvpLwOxO2mHVgq8EK2FVqvBMmkQg7DLbwhK4T041udKM=
*/