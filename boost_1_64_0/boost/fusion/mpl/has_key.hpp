/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_HAS_KEY_10022005_1617)
#define FUSION_HAS_KEY_10022005_1617

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct has_key_impl;

    template <>
    struct has_key_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Key>
        struct apply : fusion::result_of::has_key<Sequence, Key> {};
    };
}}

#endif


/* has_key.hpp
kBYT+eKWSmBwgbTHOK2wXh19DgRfVtkHHtI5/fv/RFHuQx5yV+VncaXvQIhNG09IGws793nGE94WNoXMQ7rsH99fZYOeFa/agaVwp+ML9Z1HA91BJ9uPrm5b3ckHbpmoVVR5Yyj6lH4E/CMhJbX9BFE+7B2BPvzwsdYbOXVBqflVSWTmFjec1g6eRNO2EWp17BB87eo8qYv9jDYfbp5CzwAVKQyq0zlaS0N2mRq6DlrKW+N+sz7GEK3vIPtNgoFX7bJQ434EM4qDJ8y2nIaQTo6JlR5pMlhDkAIie8hFspKIud3LWUxF/pl05zCExPZxQcy175w61mN9H9p4pfVpN1KU+LRRF24fWg5x8B4VH/GjfrZzl0UCRbSPlVtLIioqGV26yPgQFzYp5o/lqgMJFHg2ug7CYvv5yEg9pGzHE9NBSi3gCuypCkLNebV6Jvwe35FMjV51E4/RuV14WrWrQVBjcwz9nkNXjBg7lGLcQcqanDTv8Wh4M+6J6ePtselk7k3MuON1ZkNZXbnN6QlwADHDDW5hpijHo9W5lcZhZhVmNbZFxx8tekjLig==
*/