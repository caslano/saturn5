//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_VALUE_INIT_HPP
#define BOOST_CONTAINER_DETAIL_VALUE_INIT_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

namespace boost {
namespace container {
namespace dtl {

template<class T>
struct value_init
{
   value_init()
      : m_t()
   {}

   operator T &() { return m_t; }

   T &get() { return m_t; }

   T m_t;
};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DETAIL_VALUE_INIT_HPP

/* value_init.hpp
yxR2eO/selieqDdmavA1WDEzOfYK0cvbhyx4DtZA5rQ825Sc3czWkJnrI5jrb5STmTmGw3xkPG7+hrpkWLyIG37Et2NgyWR+Zk9vnjwBFhY5D+/fWgTLE2beRQMrFvb4Vx8nwipEL09+sX0irE5YeNmHcbAWkfPI78+eBusUNnzyA2fA+oQtP37RozDvY7RtMvvbsvrDYXFkvJfxae/EwpKE3TM3PQBLJ+P1Xpjx2ARYlrDVn4y6A1YgehlqRdJg5SLOvJ8PViPs2aLcblijyOk5YvQ9sA4xhiHP/GM8rE9Y/hWHbYBZVdH1zrzz1yxYrLCUE4edBAuR8V7WbPz6bVhalfP6iwi7ubu4HZYvcg6anzEZVkZmMxv4aNc2WI2w3Uft3gFrEvWe+fS4RFi7sL/MvHIQrEf0UtZfdBzM+3h03Gir9itYgJkcXwKZ0/hSyWxmR1ePqIVFhE34dlYurEDUOya0YTWsVNhR00uOgVWROY2vURlfm4gzzwbCesmc9nWeJ+iciJk5T4ZZZH5mb20cXgcLktnMzN+IYCkirnTIsBAsQoY+i8nM83+wQjKbmbn+g5WTeZmZc31YtYj74KeNr8EahdUtef45WDuZxYyfv/SQ+Zm9fdp3x8OsJ+n8jFn9lq4/YQmKpZPxXsx1IyybzIKJdVRI5mFm/p4DKybzMSsKZJwLqyJzWmZ1IucXfzvqZliDyOm+pb0A1v6kssxEPfN9UZirOnq5JFz4XgQWS8ZzVi18bRgsRIZltpasMeba+2GpZD5mh56ycDcsi8xiturmyXfvtzkLCljcOvrW4nGbX7wWVk4WYOZ68OU9sAYyi9mmg0rPh7WS2cwOTVudAusm8zO789HrZsO8W6Nt4b6958HiyXjOGZHkq2DJZLyX2smjv4ali7jvQ/cfB8tW4grJfMzOOmdMEFZBFmC24P4d38EaRU58i4Is3MZyrjfvDrvhk/r9Fh7RS4Z7MyX0PGXBMa4rYIGnaH7CxLOWcczu5t8iNN/VI8O9kg307byjH6tv3m+zZ6WTYX6W8mdCySLCrGHDpsLyyPzMPvw86wJYmbDQ2bM2wepETvPuDVgTmc3Mv+q+3bAOYTX/nPgYrI/MYmbuWcG8T0fbwaWvhmABYY2LnhwDSyDzwMT36hKZ3Su+R5TMTXz7aZKw8Wd9kAVLI7OYmW9TwyLCnpsYvwSW72jhESWs3n3imd4yMi+zvz9deC+siiyW2airS1+EtQj76rEfz4L1kVnMYvKH9sC8NbT+mK19pehWWKywwXdfOxqWSMZzpq/6IwmWKuIqDrnq77CIMO/0wh9gBWQeZubvXLAiEff4rq11sAphBz+ztB9WJ3Ka9Q5rEHG7Chq2wtqETW457htYjxj7wHe+uQ4W84zzGLxkPO6EItcYWICM11t3z/xsWEjEbcovehA2icxpLqUplqFYWLEsxXIVy1esULFixUoVK1esUrFqxWoVq1eskZmcg81kXph4hr9dydmpWLcw88wBrNcxzuXqZ3Y/Hau6Fow4DxbzrLN5FbOF7Xh4RRHMT2YzO3SmdQwsgSye2cNT1hfDwmQWM/6usjxRz+zLYQWi3ulf+MtgZWQ+Zu++NvYRWC2Zn1lu+MG/wlpF3OpmTyasR9gbC9xlMO9z0Xbu7GfvgMWRWcxO+uOhSbBEYS1/OScCSyULMPsy+fYkWK4SV0TmhYnnvMvIPMz29FWsgVWQ2cyOOefeAKxOjK866ywvrFXEjT/oyoth3SKuq8p/N8xT69yLVevcS1ytcy/Jtc69ZNQ695LHexHfmC4g8zN7bNHZybAKUe/Pj57vhNUJ+/WK86fAWsgsZu78U6+CdYo4/h2AfrI=
*/