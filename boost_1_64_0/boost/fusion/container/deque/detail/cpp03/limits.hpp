/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_LIMITS_26112006_1737)
#define BOOST_FUSION_DEQUE_LIMITS_26112006_1737

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/fusion/container/vector/detail/cpp03/limits.hpp>

#if !defined(FUSION_MAX_DEQUE_SIZE)
# define FUSION_MAX_DEQUE_SIZE FUSION_MAX_VECTOR_SIZE
#else
# if FUSION_MAX_DEQUE_SIZE < 3
#   undef FUSION_MAX_DEQUE_SIZE
#   if (FUSION_MAX_VECTOR_SIZE > 10)
#       define FUSION_MAX_DEQUE_SIZE 10
#   else
#       define FUSION_MAX_DEQUE_SIZE FUSION_MAX_VECTOR_SIZE
#   endif
# endif
#endif

#define FUSION_MAX_DEQUE_SIZE_STR BOOST_PP_STRINGIZE(BOOST_FUSION_PP_ROUND_UP(FUSION_MAX_DEQUE_SIZE))

#endif

/* limits.hpp
pYwdPXnymNFjJ6WMT5w1YdqURIuc8784yqKflTCnkezdhrSVvYVSY5DbbO8lY6ddkTRjSsqMhGnjR4/jBKrMtHy2L7Ytsfd9LrVHM33vf9tZYIvtaVvSYpzX19SKLsOQ9vION5cwlaa6UGIqlYNkbHp0cq+Hft5ID4T5SNvfUfrfc53OjkgWX/tO4ifQDumg+UCb6aCdnMjBa4WZ+cXo4bU+tLL/LGW/rItL2SXfSGmHcCSdsgeXm+d7pm3Q256u5YsIZz3KxBd/JNJR2iITPeLN9MjJzxFFGqSHY8/0Lrb5fjEu0W92uXk9NZfHrrFST6OQUOJXmOmHagt89C8S/WT+XIto1+Nx0SPbxVYrRI98sZMcpJh/qXOrB24lPq4BiDDRY+Dtdj0WuOjRSXzjL0Taik3nd9Ym1kz00EYamzINr4+7bjevj1rRY6PYzXokjzBVpnqU5KcU5Kf7chaYfa0DtOlBJOV8yBUR2m+aEdbrWxCj6+tyJh3rGDiFzCL2dc5q9JI01HIsET/8EVKOocg1pFm22qQcRWfWD2WNjdQxSztEtwdEt/PaqWtuuM4xb+saM91K8rVK8Fkv13b+fLV5O69yo4NljYkOiwpzijNTzkiPjmt0PZx9t5vX37faybe/ohjopEdacQFHYGonGvji86fp0BwWN3M+VypYX5OTlldQkq+vt+mkh+VsGtO+K2tc5JviHd21NRONPu1W9NJTazoWnFjz7sDp76a42xP9118j4u8aGvM98t2tKfF/b3jzvd7d73n/0mDbmqEeyT2HdGpzdNTioykP5b70hvuzC/qO037v3OnLxrde/tbx3A5bDj10qmSR+73zv7V9s5dnIbG1Mv6jKYxV5l7awkLYExbBC2EJ7AcXqt+0JZ1hko76bXopP7WHy2A0LFPi1Um8Tq7x5Bt2K3gtbAev0+PJswOMNImXIXpnwnCYJfESkHiJN1LiNYMjJd5V8g19DoyEV8MB8DeidyocBtP09OTeDMeapBcregyBoXAoDINxUo8XwVFwpKSXitRJevmS3rlwhqTXTuojBPaG7eFg2AEOgZ3hBBgKU2EXmAG7wRwYru+9KfdQeKHko+692UP07gm7wkjYQ5lrLUWqJP5Gid8S5kr8y6QeE2B3OAn2h5NhLJwCk2ASnA2nwqvgNJgFp8M8OBMWw9lwPUyGdruVexYcYWK3OZL/fMl3gdRTHhwK85V6qFntvh4GSD0MlHoYJPUwWI/PtcZ9/CiJ31vi95H4ffX4MqbDwSbxbxS7XwH7wpvgILgSriLsKg97oFYO55t3H/teqEeH89u+INv8RDJyAGGvUvYjNe49Wo3UICcR5gD0PUK3I4dJYy88hWjf9WcgGbJ35xFE25uzH+LYe/MU4R17b25FikeQPjyNdHqB76eyL6bsgem092Us/z4SJiPFiGOfysNISAx5IEvk23U1ErHduH/k3hHkA3ORCsTxbTmJtI/DYNnHMZe/rbBME/57B3IYseznez+ShJQilcgBpA7p9CL6IRkv/m9/Kw1C8n/t93+r/T/OxjcA7R2/mI51UvbwN78///c9X3BP0ftfgrGP6X2KfqT3l2qEPiH9ACr2jl07zZUErsAVuAJX4ApcgStwBa7AFbgCV+AKXBbLf3j+P78gP1N7+T8L7/6FgXf/wLt/4ApcgStwBa7AFbgCV+AKXIErcAUuv69f9f2f7bDSF9j//2zN/V8RRRqOs8hkTf0LsBt8Bg7X9nFdYltTMyVpfOL06Ry5t4CjkjKtrKq3LvZpTW4qjLOttS1aYJF1ktkw2r6Wm2RSskry022/W/U13tpabPvvbWUN/tAYWT9Zv05f1lrm2NZ/vn4=
*/