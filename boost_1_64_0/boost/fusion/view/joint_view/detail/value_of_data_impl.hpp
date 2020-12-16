/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<joint_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::value_of_data<typename It::first_type>
        {};
    };
}}}

#endif

/* value_of_data_impl.hpp
w/cpw46qkugufm6amjPctd/W6EjFp/oEdwyyj3Hvho+Rl/faB3dsdvZLsA8MddcHorb7gCJg2Ke7BNnt2AeO4Z5ez2++RqI7+S9iH8gEPMMND+LWlpsp5dM6o1uQYpjxuJvnnv/uANzF9je3RX2yJXyz3v4w/C8tq6y0NDWmlE9jwKAgxSLgMfwGDvNw/3JHv30m9oF0Z+2vrKu2ZJTXyjfW2iODdI6sBD5vbF/bW7awnb8BzxUWtHHWfoshOQwC5jh4dpB1wDGA86Jh0/hXJdrWH5eNukCmMx7Eo7YOymjlG2PAjCA7EvXC4/k8uO9dhwoQIiNlpqPtNc1p+y15uhkEzP25WUHWGv16RvP14yW34z5la391Ju7H5LriQVUpXE1j6XSMQcDsB/cG2VN49n4Mv1MlkHmERFv5Y5EHM7Mc+DZhFSPldXZ5QAQ0HjwZZPtgXziB8YsuKw6XaEu/APvCdGfzQVVpTXnY0l6MQcDkwbIgxXHkcbOLcl4+G60F/hLUixucjQdVFi1uBgFzPHghyL7FvnASfH/u/mUHSLQF2ZPyg654AGfZrC2OzPLJVvBqkOwmYw27yQ5+iUu7CdbPns3EIGCesV8JujGOBSfz9l41oRIDb/iLdsb1YWuHMmAt0oBBwPTvWx9kN6Ac8E3p2IMfvinRXL8kB+UgwyEPeJQQu0wgCjQWbAyyWciDUq4bPL6juDsBpN/fnI3jYZ4rHsTjcFmRLQ94g4JxJiSYRnE3xsHn696dXWQrs/1BuE5c72ydCDW0Oy8SAcN+uncaexx5UMbjF25cMEqiWX4R+igUuZQDuK/L0t5CIwo0JvZLYz8jD8r5iaD72XnKStKQj3LgTE+GGlaOry2z5LNjkEj13xqVxuYiHyo4HzK/OUyiGf56ZTdwNi5CJassBdvQyjf2205OY6ux/ZXcbvB86Tuyhen+PBwT87Nctj8cseTurFPYzj3qNJ/HgFd3i+/oigeRqCVHDYOAuVaoSWMDUUeq4tFsTy3sJtGgX4T6QVG2QzmoDlkeDQQBcyyYmsbaYF/gQQt7v94ZY1gG/Glp6OPsbK0Qj9teMCkKxngAC8JzkQcTuAdn6ccYb8b3Z6M/62xn6+Z43LYVTVEw/FkvSKM4nmEenrz8s0EoJX4iM7m/2tY6DyJlE0M98MPWkqExDRoTpqaz5cgHntr6htBtDIWhAPkwzjkf4g74EDfXDf0zyIeLnx0NDTukBGcNb66PcV1dxFnBOlaXupAIomKOD0VJXkQMXvz9n/LCrlQQFTMGOPDib+RFNb+DtuXiXWVr//I64XxR5CLmSnkN/IM9MVuqIxWf4ndwZAbFXKnhURV2e+dbif7pzZuCPr4t3bU/bktjoOJTzsC0zaI7B6PwWVGy/iyJ/uENxTNyq1zE/hYVBBEN11iVAEXAsK3tnsW6Iw9ivOUnrUtI9HfvnrRkjI1MNzyAda6to+QGAZMHe2SxS5AH/GKt2065/imJ/uZlZmJGd3JQkbDkvknFp44D+2dRvJ1a3tRfNm7Ck7LechV7yUWMQlnBypCtkEPJ8rdz/fiLp87R81iN7Ry135ZdVZVuzIEHZLG52fLdJ/h64ZcncQ742VNRzwvdzYGV4UlWG8+LN/v+YVm0v1Jn7K/85A13ur/CK2hxd4WKT/G7gvavRrsBD8j5TfaV6yS62Vuaj2ulti70QVnBeltuN1R8ytgXy2Knovzzu5dvOeLXGyX6ozcWx75id/IPFbTlcmGWTzrQ1CyKv8gvhDpjwZgbZAt/8JQvcmaus/aPr7CqAYniTfkHR4oe2H6u8n5eeMEvEv3ey90R7SXt3LW/qodVJZjKp7XxS1lsNxz/Tuc=
*/