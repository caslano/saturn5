#ifndef BOOST_ARCHIVE_POLYMORPHIC_TEXT_OARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_TEXT_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_text_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_text_oarchive :
    public detail::polymorphic_oarchive_route<text_oarchive>
{
public:
    polymorphic_text_oarchive(std::ostream & os, unsigned int flags = 0) :
        detail::polymorphic_oarchive_route<text_oarchive>(os, flags)
    {}
    ~polymorphic_text_oarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_text_oarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_TEXT_OARCHIVE_HPP


/* polymorphic_text_oarchive.hpp
9Ib3ZfJv91CcTUpan8CQtTCS9hiJb/1B/TMcBKkVuignAbD/enYIde/nlItD3M+exg4cHSr3s32T4P28YQql+XaYN8itLQ/+OF5/31/UEDzQVH9/dgT7a4P+anwVDALiNN8msyusU+OvrtH/3FD99zD6j1X9p1j6/z2gv8b9K4izvOK4s7XAvwbne49Lwb9oC/y71JhvGM339X9tvr4JDfV/hup/sKX/Jycb/dup/7J/rf/wBvu/J0vNP8oyf/R/0GcCOAxh3UkMYXmJ0YKULbmZWqmqQ39OHS/+w57oLVTyVecdID8DbF3K1KeQpOQ/UELm/nx1tHL9RfYL8PsVo3fqRpr1RCjdXqlVNpZhpt1M48vR1ruE97Nc3rihNethyudcu17euCptveV5i+LnjXlYUfy0VdWsd3icwg+JRlokpTXOiPMX+s9D/2CarE/wDGEcqzEDSNRKtjK7JRq2gJH8LcIbdpxhaPbksKoGfiv551jhDy03+WnLhTd0Bp7E9vpfIa3HWOKJL9RbsYW83RWlAgZba225Yg7FO9dWVOpRmGsjeDOhPhJvR850LxkVgraWFp7DgrxqvdVgeeJLinV2BKz7zhSu+17D0JCkBekWf4OlVBAa5zumW81zPMmIgLg0hgz/nWsdJSNa+zLsS+Plp9teuc/RZETr5VNaLysCJRy9MQtfqC12zzPOl273XsDKIgE9grtf2sfsD8lk/zpdkMdm9Bvc+o+6sER/n7+JEpx6Wddt2jQaUyxF9TkfHBE1WPjG+FMXcfYzSMly0g0pmQjIfj0pDovV1Po/MzoYn+BbmJfyuvWkdYujhYKpIEwLsxteuWzryl1GKzeRloTlc1i+DZ15+dKm1Vm/zpfXXr/7OodYv21616nm+jUfeMAi9TrpRVL2fxda7P86h7D/s+Q/NyKE/Z8lf+y0EPZ/lvz1nULY/1nyW4eon2jJvy5E/R8vsOj/hrA/3GXJf/usEPaPlvzLOoaYvyU/LET/Xkv+zcNDzN+SP75viPlb8ltj/Nb3TjQrWlxQ/71zFlcAWLJMkM+X3nEUE2P5pb4ElAAcoTfwjYsU7jNSfFj6mAbKQi5ADDN3zxujPzuANJmU/HrcgO4eVSxB6Y15eixfGBGGRj3NkNlU33I+HjR+w/1tl3PJImLdPcUpMRs5J4APO0PCUy2t2aXT8jvDbCLhQ6+qz5mCGiR4uwd5zqP1CubVLTwtmDZGf5rTFsQY3bLZAoaIUfXjUa1TY1hnGUNHIGCooJ5u69xH6S+mCwlLyrUDui89G1Omu27PKWEkCXd4aVvcQuO6u2I3lWiU4Y8qeYoLcLthRJtlYm/ROAfwRg8lT9GrIv0s1fPTg6aP+816EYDu2MFC/ckOwAfzuxRmbnKWigO/fh0ikfQ2jT98iiASXSBHG0SM1WXjPCN7Luf4RDHzZ7vv0lZfv+lnCm6zLbDPp1G3dv94+RLmP0++RPjd8sXhHyJfEvz95UuWv6d8SfJ3GXQW7XOLQTfiUfa2XI5kao3WFN/VkgdyuhTSuH5sbw569flYa6AyD3YX6qoE/AfrQp+jj/idKBN2xyo7scpY0WYlt25VS7nVXBIHzfSbPrWrn6/H/U4tLtMIZsZ4/fv+fMKRQVStbgfFrMJut5korycgbO8r+Pj/zq3dSqVQQDpL0pfKxWgnyPjjFs5AjLNcb1rCydahXKgv728M5RtmDGE1yn+vDvVU5CHjEDLYKs0H5/QBj3lcpVDkoYCaXXknuyT1NNukxaacziqnhTk/B1L4sORfLuvO8m86MQ/JiWl6MIATw6TVQNPJWeducnj+gZszaBztqowG+49KpCjQk5kHg+h7TVcpXD4=
*/