
#ifndef BOOST_MPL_SET_SET0_HPP_INCLUDED
#define BOOST_MPL_SET_SET0_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/set/aux_/at_impl.hpp>
#include <boost/mpl/set/aux_/clear_impl.hpp>
//#include <boost/mpl/set/aux_/O1_size.hpp>
#include <boost/mpl/set/aux_/size_impl.hpp>
#include <boost/mpl/set/aux_/empty_impl.hpp>
#include <boost/mpl/set/aux_/insert_impl.hpp>
#include <boost/mpl/set/aux_/insert_range_impl.hpp>
#include <boost/mpl/set/aux_/erase_impl.hpp>
#include <boost/mpl/set/aux_/erase_key_impl.hpp>
#include <boost/mpl/set/aux_/has_key_impl.hpp>
#include <boost/mpl/set/aux_/key_type_impl.hpp>
#include <boost/mpl/set/aux_/value_type_impl.hpp>
#include <boost/mpl/set/aux_/begin_end_impl.hpp>
#include <boost/mpl/set/aux_/iterator.hpp>
#include <boost/mpl/set/aux_/item.hpp>
#include <boost/mpl/set/aux_/set0.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

#endif // BOOST_MPL_SET_SET0_HPP_INCLUDED

/* set0.hpp
k+M6VrfS3mulvZ/HapiuWn85T/ZLlP3UY+HnSXs/Le29EOvgImyIi7EdPoOdcQkOwqU4DJ/FUFyOUbgCY3AlxuEqKcdqOznuynFYKUd/5XnkO6uL6loZV3TH6lgd62ENbIb3Y2ushx2wPvpgAxyOHpiGDXExNsLl2BjTsQluwma4D5vje9gCP8GW+C164gX0wnKUtTU6YBusiw9ga2yL7bE9DsYOOAI7YjB2wsexM85GH5yDXXAZPoQrsBtuxO74Avriq9gTt6Ef7kZ/3IN98CD2xUPYH4/iQMzFoXgGh+F1HI63cATa0eaPYn0MxJYYhO1wFHpjKPrjaByKYTgew3EdRuDLOAZ3YSTuxij8FKPxGsbgzxiL9/IGjcNK+Bg2x3j0wgT0xUQcjWMxEpPwMUzGZByH0/FxnI3jcSGm4AqciGtwEr6Nk3EfTpE5/6fhMUzFH/EJvIoz5e+4sJh03M1yErsu2jjFvytWzRjFvz1erY1PtE3M+mIlxiY6M381OY68lJzlrMWutaQlLWlJS1rSkpa0pCUtaUlLf08qifn/mT/cJvP/33QlPmeYI0/iwi/K+cUN5HLexL8vmc4v8rxFHj9uOd7di8AhE+0VOH48TjUX4EXDfHWe1sf9XzEb5y/rfavG+eddMh/n3/yy+W1fuU2ZzMabR0mMdL60QZoibbCa+5uNN1caQlf0c6pm483VdZe6ctts7LyTeV1pC8u6auPP/6vjz8/pz7Flrz6wsNm8G/cNHPbjrx18H8gp/rnDPzP+fL5O/t7xRRmXfB+mGuZZUo3broRuWBWrYkOshl3QHX2xOo7AGhiENTEMa+E4rI2TsA4uwLqYjvVwA9Y3nluRv0EpY5bFuRVPKVcrdMa2Uq52WAM7YGvsiB2wEw5AbxyEPlLOBzEJu+BsfAjTsCt2/R+Npw4pa6+NqbZxfLqrS3ndcBctHq0lLWlJS1rS0n8xlcT4/5CIsNCERNtc//+zcv2/RQzgTXIF8i7yfcoc3xdVMQDluYux9p/EAYzzsA+icyBLSBjnxI8rbT5W31nmBYgO4baM8x9b2nztBn6vjEsuQnygnWOri+b9/2nG22b9fwbsyJg6qf8TZEfq73DJvP8vjVDs682ttIFZPISX9y/X3xATmGXDcbrdyyvbO173aBBwLWVmRo+hbufvnjP5zhu/+4K+PKkbln/89YEWLaYeGDAuYu7687Yb11vcPnhxYxG2itUUFIuo+ryyPaf+vm5dPl3h+HLDlKFnPb2SCo4VfKFvz8Sqs69O7b9s6IxGg1Y5eJU9/efG9U7RyeeIfL442Jn34d2lD18T3bEWtsXa2A/rYADWw6FYH8PRA5/EhrgSG+EabIJbsSnuwmYoc4nL3zN/51IO9VziXlKONqpYQmNshy2xvSqWMAg74Rj0xhj0wan4ID6BXbCFfaHj3Yxxhaje9IfJljGEun3oP5KtxRLS/iCe0AR9yFf4eWTfosUWzvOzcz/KRB4ncYYVmIkZaBlvOC0xh9LEEgKwLhpiD/79C44/ZFjEIPLwBtnaWLmOEosYjonkgmISGWzLJg/n5ytoPT6BEqM4Sy4fYIpVNAkoPF7hH8Bj4UhMJefHLjDAFL/YGkD5yOo4xtkA81hGABYWz3B+xBTT8EVDXGM+biXnkNUxjvKDihfnSGNbBjmbfJ5cUNyj5mBT7GMweYrEQPZYxEFyBptiIbf42W3I7TERL7bl4nBMIS+S+MhWzCbf4OcsF6451+IkWtKSlrSkpX9ZKpH+v2eEzeb/+0XV/8+Q/n+Y9H+DyZW8+e+cqv/PczOVXBHOfZdxDDhnujbWybDGZCXOfceEJvNjgWMDovkvIsYUC/g=
*/