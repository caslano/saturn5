// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_NAME_HPP
#define BOOST_PARAMETER_AUX_NAME_HPP

namespace boost { namespace parameter { namespace aux {

    struct name_tag_base
    {
    };

    template <typename Tag>
    struct name_tag
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/bool.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_name_tag : ::boost::mpl::false_
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/value_type.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if !defined(BOOST_NO_SFINAE) && \
    !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x592))
#include <boost/parameter/aux_/lambda_tag.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace mpl {

    template <typename T>
    struct lambda<
        T
      , typename ::boost::enable_if<
            ::boost::parameter::aux::is_name_tag<T>
          , ::boost::parameter::aux::lambda_tag
        >::type
    >
    {
        typedef ::boost::mpl::true_ is_le;
        typedef ::boost::mpl::bind3<
            ::boost::mpl::quote3< ::boost::parameter::value_type>
          , ::boost::mpl::arg<2>
          , T
          , void
        > result_;
        typedef result_ type;
    };
}} // namespace boost::mpl

#endif  // SFINAE enabled, not Borland.

#include <boost/parameter/aux_/void.hpp>

#define BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(tag)                            \
    ::boost::parameter::value_type<                                          \
        ::boost::mpl::_2,tag,::boost::parameter::void_                       \
    >
/**/

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_TAG_MP11_PLACEHOLDER_VALUE(name, tag)                \
    template <typename ArgumentPack>                                         \
    using name = typename ::boost::parameter                                 \
    ::value_type<ArgumentPack,tag,::boost::parameter::void_>::type
/**/

#include <boost/parameter/binding.hpp>

#define BOOST_PARAMETER_TAG_MP11_PLACEHOLDER_BINDING(name, tag)              \
    template <typename ArgumentPack>                                         \
    using name = typename ::boost::parameter                                 \
    ::binding<ArgumentPack,tag,::boost::parameter::void_>::type
/**/

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* name.hpp
Zz6n5IDyv9B3bNbfD4gdYlxPV+NxEXqKIB0N1FgbrvM3TMZjj5t03MQZbupM1m4aSh8eI27GNJQxO3icK5B1Bd9x2/OtgHgZt6Nl7I41zDX4VoDqr0R38bIoECYOaiGPoLuKIRfUnfsBiM2bvkY16D/NZ5qUyvcHCiXe8cgDVLAV7rgn6PNMcks8T5tMZ0cqGzUEWNUzwtD9xeOR8o3bgikTpF6q5w1ybhB/ErpcO8c1o8w7Kd3kGhVD96nPq3CjxMzTiiGy7i7rz43RQRNkT5Ref/Z7vlmM+TwQU36wV+kj3dhLusW9kTY1P5I0+34Lb5t8I2CgRDQA6WmMn0OVTktKsnNLCS8/u4j5urTZ7uo+Tlno+7ho5b6fpW4JS89Zo5TfvBnTp3vPTotV13tb9uNmv93l/rG4xNummqrrLst+W/zW+Hx1wkdPKl8yj4TKTqVX1k7FnaTDrMuQBGtdlvrqUnm10KXkaYHkyfKe+wK6nFmNLkv96VLKsFzK0EqXpf8lXXr66Lmiy0YSeLynjxZd+u2g+TPNdS94ZqC5f0ltWvWMyO+NAskkTnVGpPmRK6cBShm+FlPd+ZDi3zSGPRhZ8/MeCVuf92hO6z6LtJ4nrREWaTWPtzMiqk9rhE9aH7qItBK2Tqt5PpiRWDWt/6yPb6u06sM+L/6sT49u0ppVjc8ei71VfKUzyopqqBv86/ZTVv3zCu1Wj8U1yIOFHnXbKTM9uzC3k9ZJVfPaKx6xymuZcdPIXbdxTGgN80w4ely8P8Jzz8RuGz/57uWT74ToX5Zvzzo9cWIncfqU8/4k6zaQaZn3qdPLa5jnTJ88NPyFeTCPDduTq6Y12VgbNqVVbvXUAzS5p6s2nfg1rwX5r48mt951n5rniXRUqY/Ep+ujOZ+lKVXz2T4e+6r5pKW796qMqOtTr6zGPZ/0D6tB+j3zJcL3rUM6vbHNfdOLxDKftUjvjMnu+uOMrb5cKnzS+spFtH3CtuzvXalV05mBXldUSac+vrhGdWiFqX1PjLrw2cWG+196dvEjFmcXE6fv2cW6bE6nWreZDRZ5phevUX43XESb2fBv9OEX02bublE1nx3I55Yq+VS9WI3yueXf6MMI27IOLm1ZNZ3B1NftVdMpp1TWrL1sl7Sa19ln+imT7T752nkRZWJqW5XPUZT4zOsYma3kWZFpL9BwY/6p86rWrxlN3c8wslQflmuVP/FjN7kbb5U33NVsTdTzrIOwSHuurPOImbDNa7cBct58BhKE9EV+Qg8nJR9lJR1UTmTbhm/d0msbP2f6P9/6pCl/cq6uPjv6jLrWk/121s8zxK95zaQcner75/gr3fdCUXL/XE+Z42zB2El8/BXre6dIuW76JqM+/z8GutT1BLVOnkUZr23NuS+R2AdFu5wkyNxnq3UYcbcNd6cMd7WSzXXvos6xNrerOpXq35RK8+VYObP6ege/4SzY31g/VWmvMG265X6yZFa2sZCn6rQ+R1cuF+dblZeEYze51/se9T7PE8pNsEWZWfuXvYPaf8Aw8W9xL2nlX/Y+av/x4t/iTF5/6c81+08X/xbnMpv9S301PodRXlJm8p9p8h9r8h9r8h9jjn+qsZTKwgtKiJO6u8XtztGMULeS8jc5kcIIL94UXrwOz9z/uUs0RdKSra5PdNxCeh5EXkTeR75BxjkCVBoTTGEmmNOow/QkT2140e3rPdwRswojyRQGv016Mq9TZJeq8Vv8z1duhjjakc8uDvc+3lRTOKlW4aj7fRWOTsczV6keRJ/Nu0j5yXC0sUWqfcqtTWG2ljBN6yD8yTqI+H9SXQ91uM12KQuHyb2RF+86/A3q+ruUTxN7ur2ZLQ8=
*/