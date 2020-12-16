/*!
@file
Defines `boost::hana::Constant`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_CONSTANT_HPP
#define BOOST_HANA_CONCEPT_CONSTANT_HPP

#include <boost/hana/fwd/concept/constant.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/value.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename C>
    struct Constant
        : hana::integral_constant<bool,
            !is_default<value_impl<typename tag_of<C>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_CONSTANT_HPP

/* constant.hpp
eV9N6qoNK8ysahV1nSKKql9X2WbmVRfX9d6arFct2aF5Fa2yrpNFSfXrqiQlNK/KuL731KQfGAmAzatqFXXNqcm6dSed/M/qO6km69ZIDvmf9YOJNamrnPL/r+p6d032B+buuKqs64SarFf9NNrM2uK6hogAGkvyy8TrwDzSVyRNcJhbOI+j9WdS2OR53Ght9ie+XamhY8R6GXuuiXMJ413PoPDJGU9V7TlYlPjhGg7tIc0++ppMb6OZW1zfV4QnJAv1dbWYdYP3/nldmnbS1cOfl7/p9V29113fFI/6XiPCtluqUV+/Xgan1zn7sLvOYz3qfC0947PKdWza5XD6vTUV7rqN86hLiggOrrJupp4+WbRPVeqX6lG/cZTjvsr6mXEKVcV+4C6RUHWb+vsQX0Wds0V8jets7qFea/v9SttneNRvvEi01bS+pg+njetDfnXX2eFR5yyRf07N62zyKbZe52Slznd61NkpTtStaZ1NP33V69xUqXOmR50zxf4a92Vzpwe0+g5R6uv0qN+dIq/G9TV96KrXOV6pc5ZHHR0i11LTOps7VYD3bxmipMbr2C+ntFXUO10k1rjefpnmqKLeaSKrxv3D9FPyKup8v5hb6+/r/IqW2S68f0o6jVDC6Y7Mjqsjf3KFd0re16S9X/RK+S5925H/marYhSNjj7pM23YWKtb1ieIbdKN/YulTS+R9Q9pTMfLmXDvdZaEB9FOxx58So6Xp94+FCbc1bPzKGi6TrK7Vbdf8MOVel8XRRX8/KssdHtJ9Oy8XRGUqn7foy/P2uyyBjmXvKsvNvf3XRK4L5Yl6XLGTrW542GXFdbRZMKXMTcvC+PPoWHO3Ym88E3olL0dWoljObaPedVluMJ1vKfXs2yrqbpfl19MyA7htSaNLR3OZZHcqy32z9V0L1+Vcuq9aWWfvXhQW5DJHfboHXSnzszM7C9joi6PnlTJF5LoV3H4N6RtMt9G1ypatvD7Pp7vhlDJfvX3kGS6T7BvFbq39eJHLtISbrRVrWbtfOq8XsmGKbfuy1UqXlZNFKrYnK7oZtx8lsvxUsdfbrOnJy5Fdqlib9rY3ebkwzzJ7fb3lfu5nYZ7LWSO/estlU8guUuzB9wYnuUzrHT0Ue2Bax0NcF7JNin1ke5b7Z3ETfbtlu+H4Zdfx+qQ8MJ8r9nbU1WlczwtobKHY9kONZ/ByZO0V27H90Q7cz8iC1c+b83gMx0DWV7HCm29u7zIticnFinUdfsfPLrOTXaj0wYmHnt/G9WxB13cpfanu9r4cQ2w4PT9VKXPv2uSuvK7JvlTK7N6loj73JWqEyUqZxzdH73JZGXWySUqZj74xrQ4v18bz8yZdfservF7IHlHKPKeozfMcHwV+VKnL7vJfFrpM288+pNblqrHjeH1eQm2rLJcX0fwjrgt1wAHKcmubHZzKy1EHnKvUs/GD30Xz+rTTtqIs9375pom8XBTlDlKWu+Rn+0+8HJVQX6nLiz8XcRs56MaYOcpy9Yti3uN9QRf6/8pyN9/2cyGvF2qtR5XlBs8JPcL9muwBxfovKC3hunQTYq1QYv9kagivz+50/ZJiY+4axf0stId+HGNLfPKZz9no5qvtikWe8+1XvP2R5Sk2b8onXGYu7TFuUfcvJf2+5uUqWb19jcs4hstpk1CPR5cUBfL6JGtkc5u99bg7+fNiaZ+stN/9n3Q9wEY3IHyo2MG27z3K/aU3tZFidw/4LJu3zT50X7Jisf0Gj+dt7FrPfUiT26638bqmjT1fse6NV5Vy+5HdoZR5Ub2wnrwcXfTyjGKd9o/ry8vRBZ0ZSpnZRRbe99j70xhCWe6ZHXN/5XU2gDJgqf2lTl0=
*/