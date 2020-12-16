///////////////////////////////////////////////////////////////////////////////
// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
// Copyright 2015 John Fletcher
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_find.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_FIND_EN_14_12_2004
#define BOOST_PHOENIX_HAS_FIND_EN_14_12_2004

#include <boost/mpl/or.hpp>
#include "./is_std_map.hpp"
#include "./is_std_set.hpp"
#include "./is_std_hash_map.hpp"
#include "./is_std_hash_set.hpp"
#include "./is_unordered_set_or_map.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_find
        : boost::mpl::or_<
            boost::mpl::or_<
                is_std_map<T>
              , is_std_multimap<T>
              , is_std_set<T>
              , is_std_multiset<T>
            >
          , boost::mpl::or_<
                is_std_hash_map<T>
              , is_std_hash_multimap<T>
              , is_std_hash_set<T>
              , is_std_hash_multiset<T>
          >
          , boost::mpl::or_<
                is_std_unordered_map<T>
              , is_std_unordered_multimap<T>
              , is_std_unordered_set<T>
              , is_std_unordered_multiset<T>
            >
        >
    {
    };
}

#endif

/* has_find.hpp
FLmkpdiOkZVkOT+WGHjwKS/ylRiCSWHE4HtON4YMfiqJjxswpM+we+PiY3uM6DHkJuKpSz7J6dbtGRqi2h8kvit1tb/lhPO+SN34OGQR44x0ugklJLkcl3rb5NbTbpuG5Burly8/I2XxC9/NbBuOXWwbmxhYRL99GHVjMLWwVMN0Q/ljkPZhU/8LdWJoTAz5ujFk3VT9W+IIJyWl2Z7v969vXvIn2a9/JDUljgJzHLbXWcieXwSc/v3K4TVB1XEwjRXKNUI+U9mflfNl9TXDjn6LfyQe+f1aHX9hfW07vpv6Lub9xJ81pbQeew2I7d9nRHxSjtGVtjQniGPSFNv8moZr82sezJ/zOvmZfu1zIb8c3kV+NvcbbAjXtpP2wSyp5De6bWTHeGOGsTQ3p/PqIHlZPqvcAjlmsILknHQ2ke15ZVgD8xoSJYYE0jmWjzHHwGGb3+MNCZnxExOUK8fl+TxSn0eWSJ7Pctz3waewFf+nSMlTuQwmOd74PDKIX5MbXGR5sjP/BsVOlW5weN6TTZKVa77DmaYvMf27r/Wz84p8JmVPNZa22aE/kRfTvMd2zMnG8v3yDpLYjH/kXbIpGz+UTbc5Tw1z070OP5ey8RtQp9L4gsjJ0kdz3lXWJ33uoi/zb1WfutZMq/vUhSvTbc3vNy/L2JAOzhvknhXOPszf12Ra/dlvel8lqTPLtf+T12W/lno+J9PJnCNxaKKc1KPM45PdUn6uJSSmsC+VjvVZqSHHz0b0L2N6hjnu0hiKr5vrn6NUQprpVEHyqEoMM4khiTykbSvrKWQ925k35xfWI+8/I/mb7mqyf39Vtl0ob/zuV95vuVeA94eb8rUcu5g2nb9wsFHaSXO278ScZNO6SttGd4l7fQDvYXqn5M+1Sptz/IPSVs6y4/ngKWzBusJKLG1FqSKObs6cb7n7ffWH/baVc/zMRJu2Lz8oqb7zyD1aUifN5BgV08Scgb8cH3xJbwajeYwYvmfe+Lhk6cu/neXi40xLmOslWPq07WS++n6v/ZLnQslzAakO9RKp5Ml3WxevUdp8v5XzJqPE8QrrVX/+0MeKjB334dPvy+ioj+mt65uo32fUcZ9U/b6Mro99eqv6pOr3qXXUZ9T1vqf6fUMd9bl03Dd3rK9p/kubVuz+5MC0Kw/6FwY29/h1iOt9VR31wW3ub5ofeHTu5KgOz7lHH/hw0i+huzY57kuq3zfU9b68+n2mHfddpm8YY4vK/aA4WJ6T7YH8m5e5j2EVTMBAnIh1MBHrowEjMBn74CQciClofl633MeJ1UgFds/rpm8Y6+c96IE90LJcrCznpbNcc1kuAj2xBV7EMNIEWa4JaTR14obELuck1vflO/m+Innf3WW+j9fnN37fBVKMvI97+Xif+TrYSXnfdJ67XR1nYA18GOvjPIzG+TgAF+MofBIn4VOYhc9hLi7F5bgKV+HL+Aquwa34Ku7ADbgP/4KHcCMexs14DLfij7gNg4l3O0ZiIbbBt7AX7sA++DaOwr/hGCxCys1vinIvIDwv9eOD2ST5jMzzwfMYgP/E2ngBw/EnbIgXsRn+jF3wEg7FyxiPv2A2/oqP4hVcjr+htCvu91PaFXHYtqupbKcqmI6emIGW5Yplueo6yyXIchPRGxOR5WjXcr8d1JDl3LGNLLdEnoP/J/TE59AHl2IALlPFHSbrCdbJ/x157v1erIHvorL/nXBc3pES9ygp72hU9r8ylusiy3WV5bqplptQxnL9ZLn+stwA1XLGE47rd5gsF4veOFy1XH4Zy3WQ5TqiN3ZSLVdQxnI9Zble6I29UWk/ZSyXIsulojdOxotoJF2Q5ebKcl6YJMtlyXLZGIA=
*/