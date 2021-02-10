// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_TEMPLATE_KEYWORD_ARG_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_TEMPLATE_KEYWORD_ARG_HPP

#include <boost/parameter/template_keyword.hpp>
#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux {

    struct tag_template_keyword_arg
    {
        template <typename K, typename T>
        struct apply
        {
            typedef ::boost::parameter::template_keyword<K,T> type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename K, typename T>
        using fn = ::boost::parameter::template_keyword<K,T>;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* tag_template_keyword_arg.hpp
zfDAGZNKrrE75ETIa6DSwNTL2lff82b30KM60UpZ2IHe/unHPy/Xr7Y8T/DgXXc0x6bsVuwb+GvXfhjCd496r9RCWvA/G7Q6rKNZo8D6ZYH9hFrg1DKhd+GyDpYSaK7G0t9yFhCh3fIePM8zueAW9gjIlsO3xxHYwvoXxF/i1FRTCoWSxNB7jQTPgx7uhqQzqW1jJLRVfqfnQ4uZhmYWSw8GtdxDjaQwqLCmwX+MNyZFHznwuuvmqUAhpkTtvxfE1jO19CKeBZg7DaiXYDZ76440osJdNgsk8EUKVMlkcBiBv93j6HEBYCYY+FI59SYXVBOFkAz1G5d4dRUs2D7cXQSbYjOXHUinRSU06fZqPdr+G0w8HvOgHwaXX+FqNawXcbxo8RF7SVdID9sYn6UyNtwJegOcb+B/M9x6okDZJRlAwP6J/6O9hfJkWis9hB4fuvCGMBPGUFcglhNIOF40zuljUS6OntM2798/PXp4hgUNULhxEDS5ntOjDTscB5vjMBbLYBKD1Js7WDCD/uYSENSTXcnXhb7M0mtBu9tBU9g/Xg7tveBQLCXhFSKek9ESgmhdbkZLc/MaVPwwUW5GMGVcoZUXk/OfcHWrbkY4izptlK22RilXS5L1El5is718idDe4BnaJSiXofg6
*/