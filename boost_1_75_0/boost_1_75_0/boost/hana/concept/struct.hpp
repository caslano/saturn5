/*!
@file
Defines `boost::hana::Struct`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_STRUCT_HPP
#define BOOST_HANA_CONCEPT_STRUCT_HPP

#include <boost/hana/fwd/concept/struct.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename S>
    struct Struct
        : hana::integral_constant<bool,
            !is_default<accessors_impl<typename tag_of<S>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_STRUCT_HPP

/* struct.hpp
7UU5osgSXp8SnuVkm77hZ/MGpPFozS/ozZcbzJRawWhm3ZWHg8ZXBBShHEzeiwIVRvl7YXXZ1kZk5AcO6o6DNn2dnnzHkRHBM7QWX9k0B3Ko3lmrBZo9xOwqjCwZQboiAmdT7xhgT5txIg23rS5TPyqFd0VqsPo0StFS3C70VClk90GK0pJVrbxgWtBacNvLgs138Rp1ZLK26FS1D7sg17I+LivXvDHOO7Lk3Ut5VXD++UEaGo4S1evTkotWOAsLPRl/i/iocf/WfcriNMsaZSrZ6BanZagrLZB6hn28us4qDw6KNXn44Qdpc+RvBn2WrJPig5jZP2ej/8ZXbOoIJd8qQz3F2gA6ZJA6uMjCDsEssIsW5+Ch04TBS+HzmkeQtNHnnxznoBhzf64ZyNlQj2l9dhWNe/kWewurfD8cLlI9yeF1tBS0LpFdHuYe/JQGmqUY69H2FYP0InexS/3cHrAftb9n77OHw4coQn7Ufvi5ekJtAF3bbsI1KEjWCgnD4U+j/QUo8xpWeP4GSCrkS3M0f+jfb0+zrCgM+9IS2TP6fgIL9OGbHlBq7X1eg+cZEeWoabq86ksKx1XBN7kpWW5OlgeT1x/dLgS56j07sLqs0a3Oxe8w2aWubUou9tc7F+JJOUk5aEcYSVm/Spa/FKTgatw2QCts5CISvEtN8IPsBClUO2RPgIEvbQy6VXPtmgLcdGOhA3fJmfUp
*/