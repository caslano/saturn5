//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_HPP
#define BOOST_BEAST_HTTP_HPP

#include <boost/beast/core/detail/config.hpp>

#include <boost/beast/http/basic_dynamic_body.hpp>
#include <boost/beast/http/basic_file_body.hpp>
#include <boost/beast/http/basic_parser.hpp>
#include <boost/beast/http/buffer_body.hpp>
#include <boost/beast/http/chunk_encode.hpp>
#include <boost/beast/http/dynamic_body.hpp>
#include <boost/beast/http/empty_body.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/field.hpp>
#include <boost/beast/http/fields.hpp>
#include <boost/beast/http/file_body.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/parser.hpp>
#include <boost/beast/http/read.hpp>
#include <boost/beast/http/rfc7230.hpp>
#include <boost/beast/http/serializer.hpp>
#include <boost/beast/http/span_body.hpp>
#include <boost/beast/http/status.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/type_traits.hpp>
#include <boost/beast/http/vector_body.hpp>
#include <boost/beast/http/verb.hpp>
#include <boost/beast/http/write.hpp>

#endif

/* http.hpp
YboLHRPIxLUF0ju0Zkqg3f73cM1D/O3pTntK4rXHLJsC24VsXHsgvf17Ysm1HVo3JdD29tdNjk72DPXrJAudlLWrE5ZOwTpBNv7aqSwBnZRd2/m104ZOPmPS93BcK9hOou3qxCyfgvSCfPz1UzQBvUSv7fz6aUMnnzM5ttJU7NULiF7Wx9eLLqECdYJs59dQGwKeNZ07vDXjtepj5FOEXtSx2VXHpZWV1dFG4zqiQZyNcLTtWVZfW9XQ5v/ohyJba+pMWeZb/j/Jb8qGi/jH+FR5XtKXS3t7SK3qjY+D9yUt2+wrtk/iJ6LPAZKf+zXHauMz52lJr/fu6Wn8Brwp6Zm6x2dsebbvkLX02fZhrP3Ra1bXI4ye/5ij/kU0z8vk+Yedp1fU5DnLk8dCt/+082SeavIs1DyO/5KJugeolaBfkcLrfH5FdI8w6YOY+1GNGsUy7dsFhHx7XF7n6tuVlTW1l1QvrlzVWL9smfSsy0cFXDjjk8GRG2B0/QWJz/T2g/TpFyVttmsfywvojjYbuV7Sjzb+aDeig6+qHr6UgG8wWxff9utCfTZQb++7spGtwv11LGYT+qGL/S5dVCxtqK1s/ZlQV19XWS31Ne/DbfM3ulC5bEkvdH4LmDlb07ma2KHHf0pNW7qxi9Ti9sdxbsw7damPmZsKnfW8b93KdT0+wp4aZcnxiO65eg9h4Dh0stG152pNdeVFqoYgn17oQPMPNX1+tMTP0XjE2iHxPJcOKxrMut7IFxp7KpH4TbH+Sxe3rffywXLJEyWP2pz0i6yjzJxxneTp6s5DOZLF1PVqyTPaV1e9tpYrFze+xc6RPLM07sikW/mM99XY14Gj+L7SHu8Zq7LSu1nutZmMeSffQPT/lswLF2al5oTnm0G+F+18PSZldenVlu9nnnzLyfe2nS93aFbKYF8+M9fsKLBDu3ttumzN7YtIbc3YH33psavGMZYc9eqnaxFh0DiLwe6yq/ropWpWYWNL8/c3vqb6S/xMpoaI1xaN36h8yTMHa8xQ+3LKyQ+0J5n/wVGSZzDfCmcG24va1FzJly193YK+9/Fh8k9snWfPzerax3L99lSda760MU5fT/X2s8kzYozTf/19fZdoP7XNCe37CGS9KsdLhKGE7xAKObfe3U8rl8+ZIbeD0L1RNf9oswfoTonfJ/eDXJkT67QvnLwjzVh/WOL3Bt5r5pP+LUm/W+JlRn5Y4L3mu5K2ScoaNdbsxW3uNY9L+lXWUei2G+ej6HYbBvpR2vQ04WGC+/5TV9T++LDvPzNv8N1/3Ht9mv1p0QXn6nReDr9H9SvxrxeH2GuxG9r6hd5cVd3Q6L5Lhc3PKpcTdo/S9ILQe5Smd+oe1WZ7HbtHOe8etkzQvY1t36aKReiixaULtLy44ZJKfriKocr43RWwZze6ULnhxqflnyV+VKRvpJe0/6Q+at8Nqh8jU2T84h2Q+JjI4Ej3QDt89Uuk23viq7/Kv7ReM/I6594Wf/26D67kO4I4+Uy8ROqxX94/Lq1y7wv+DylnaOQPQWUgM1dsvgE9IKNjMUPSB0T6RFLMGqyrVbt0ksuH39+03NfUh/6pptyjyTM9p5927OAbxaemnovIOZOPOWwgHf7GeL61xz6y0pf61sz5miePPu0uPjKbXszq1tu3Jnb27/0C4y/Tzkf4wB6fznjV8fkN/u4Bfi7BcUpdnXFqfrftit3L3DzbwQ44L3YQ4+ftKt2AMo2CjgDfJhTYz5pFN03yuYl3TP5QxiT3kQZjh5p/qJnnbpP4C2FjlPyxa6TNEn8lbMxq/kmB+3HngXdI+o8l/d1s2ybkZ6v0Lb+viNMfN8l3DfIMusRO07oxWlc=
*/