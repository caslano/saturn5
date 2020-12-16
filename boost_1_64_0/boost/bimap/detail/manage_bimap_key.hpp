// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/manage_bimap_key.hpp
/// \brief Utility class to manage the set types of a bimap.

#ifndef BOOST_BIMAP_DETAIL_MANAGE_BIMAP_KEY_HPP
#define BOOST_BIMAP_DETAIL_MANAGE_BIMAP_KEY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/bimap/detail/is_set_type_of.hpp>

#include <boost/bimap/set_of.hpp>

namespace boost {
namespace bimaps {
namespace detail {

/** \struct boost::bimaps::detail::manage_bimap_key
\brief Metafunction to manage the set types of a bimap.

\code
template< class Type >
struct manage_bimap_key
{
    typedef -SetType- type;
}
\endcode

See also bimap, bimap_core.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class Type >
struct manage_bimap_key
{

typedef BOOST_DEDUCED_TYPENAME

    mpl::eval_if< BOOST_DEDUCED_TYPENAME is_set_type_of< Type >::type,
    // {
            mpl::identity< Type >,
    // }
    // else
    // {
            // Default it to a set
            mpl::identity< set_of< Type > >
    // }

    >::type set_type;

    // Returns set_type and evaluate the concept_checked_type

    typedef BOOST_DEDUCED_TYPENAME mpl::if_c< true, set_type, 
        BOOST_DEDUCED_TYPENAME set_type::lazy_concept_checked::type
    >::type type;
};



#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

} // namespace detail
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_DETAIL_MANAGE_BIMAP_KEY_HPP



/* manage_bimap_key.hpp
iOvrFG5S2A8l8DVnYSCuj1DcJ98S9DPN6l8UTu9tpl8foXXqt4zf7imbeIbbz1hx5PBOdLPS8rpzYiA3pZ2Js4D8tnOqibSoanZdRD7qc7dIvxfNujwgHZDm3rm6F7q5xNzLMHG9Y1ZEFZX6g416z7ON72DpYJfus2GmvmoJi52/vmXsQxmLUkx8s7LUhxSV1C2pLjPxNXGng9u/VLvtY71Jx5DAhc4u6bMLxzcyGB+xpiqNitNKY4PSuMAkssTtJ5hn9epjXJmkleaZVYELA515xvlZndtSxu3oaXoEzyW9Zn1GaruM1PS09IzUjh3ndjy545i0DhmpGZH1/EWkJdLH1ZXMVXrGwij9J1o7XWfy09+VofqDsac4Gje5Fkq+wE53/ezKktpaR3FPDLmpPsgqeQq71cOgPr8Rystj7d28TCQvwYykd5yTltImq+PYtLSM1M7BDLZph07A9PSMNh2bzdcZPvkabfKRlzBf4Xf+c8Yt28RXmCCfBQnyOUb5HK58ruvg5rON8pkWymdaakbndmnUYh75zEhJb77uTo3JY7byeMi0lUOsD2yPzpe+m/qZfE3R+OSfr5EJ8lWnfA1Qvuo6ki+jt/HbZKaXlZkUMpOWIC/Y1Wd81aT7vIBHvcltnFtvb8fXm7vu/nPjt2ug0Nll0jotQR6HJshjtfIY1gM4ohv9Z25oXN7teF7uWvoBuNSMlRpbuHcocs+MEzncczzGVO9xWvqQPMbabrFjre5vhO8Yv+ondb8JzjLPjPR32cjrlvfk+3wEdehwX34b3DjUjykdOyF9GPdNHxYlb/LucTovRrKmazA/IIGNXzRjce28iuqiktoFw7htj53VlryJ/I5y5U1+ZuyznUnSKZqdZsKQ28i4/bLxc5lzgWRHJ7jxDA/XP38jFGaaXURO71njp8r5rORAyt1wg+LbqtrjAeOe6/522GfsF3v1OXJr57bdkzYaeVTPPsfBDR96/zzard6X8sgzfdvvUOi+d4llQMaH222h20apD90z70+aued+Cxa7cnsqz0h43edmRC+j2uxCE7bc9RPJE/f1Lpqwbj5snVkTxgdlBsaNefTcok++v6rLliFX/LbuU4v8ZBWOng6soyXT8kzb4P1dL0976/7KHvs+WN845rX8R97mTGVzv+k3l/a5rfiBDis6vhDIOXjf462XFfGWyWm9bMwMI3OS9kTt+rRHXn+1T9rvZswse62zv2yMt64of1kUb5kTf5kWb1kdfxkbb1kUf1kdb9kYf1kXb51f/jItts4sxkiz7p8nnVn7wr+bNTeCm9Ghskf+50hHVblkNubB6XA+nA0XwBpYBa+A1fBaWANvhbXwaVgHn4NLpMPnangmXAYvhsvhNLgCTodL4Gy4Ei7S/cVaq1+hNfpb4Fqt1a+D2+B6+BT8Avwh3ABfg7eEda64vw3MbzWTX5qhzn/gnnR0fRqeCc+Vrh1Mw6XwPOk4Gqf8TZSOowvho7AQPgUvgt+GU2Ab6SZKh0F7R9mPlz1L9i6yd5V9IpwGC2WfIvs02WfIXiR7iezr4XR4q+ybZL9L9i/Jfo/s22Vvkv0R2V+BM+Gb0qG0HxbB4yi3YpgLL4W94VTYF14MB8Az4SD5o9yhxjR4p2RX2kPya66ekm3qBXvAPDgW9oETYb5kSwbA+XAgrJVs05VwMHw21chiNCuHMbFKumEsvTAHqmzdMJhq5BFi9MNsxN6ECctq9PtVqvMK9on4idUVc6jaT18MZiHyAZhSTFh3zAb+3oqZyd+PQT/Zjj0LI/IdmTXR+mROxT4RU4lZF3TD7MeEdcxMIb3v4r8eLsXeszZa38wY7Ntwi9Y7A7m/Cvsr8BA=
*/