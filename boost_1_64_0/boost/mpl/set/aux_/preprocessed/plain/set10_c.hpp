
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/set/set10_c.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T
    , T C0
    >
struct set1_c
    : s_item<
          integral_c< T,C0 >
        , set0_c<T>
        >
{
    typedef set1_c type;
};

template<
      typename T
    , T C0, T C1
    >
struct set2_c
    : s_item<
          integral_c< T,C1 >
        , set1_c< T,C0 >
        >
{
    typedef set2_c type;
};

template<
      typename T
    , T C0, T C1, T C2
    >
struct set3_c
    : s_item<
          integral_c< T,C2 >
        , set2_c< T,C0,C1 >
        >
{
    typedef set3_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3
    >
struct set4_c
    : s_item<
          integral_c< T,C3 >
        , set3_c< T,C0,C1,C2 >
        >
{
    typedef set4_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4
    >
struct set5_c
    : s_item<
          integral_c< T,C4 >
        , set4_c< T,C0,C1,C2,C3 >
        >
{
    typedef set5_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5
    >
struct set6_c
    : s_item<
          integral_c< T,C5 >
        , set5_c< T,C0,C1,C2,C3,C4 >
        >
{
    typedef set6_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6
    >
struct set7_c
    : s_item<
          integral_c< T,C6 >
        , set6_c< T,C0,C1,C2,C3,C4,C5 >
        >
{
    typedef set7_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7
    >
struct set8_c
    : s_item<
          integral_c< T,C7 >
        , set7_c< T,C0,C1,C2,C3,C4,C5,C6 >
        >
{
    typedef set8_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8
    >
struct set9_c
    : s_item<
          integral_c< T,C8 >
        , set8_c< T,C0,C1,C2,C3,C4,C5,C6,C7 >
        >
{
    typedef set9_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9
    >
struct set10_c
    : s_item<
          integral_c< T,C9 >
        , set9_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8 >
        >
{
    typedef set10_c type;
};

}}

/* set10_c.hpp
BvqYd0GX37xPe+ADWWfsVmPRlTL/DybvEQegi3xLO9hYocypHGasYHkVx0ahi1wHx6DLyf68fIT2vizu2Hh0kTm4k9FFvs2YZixD3sM+gwzZQzWXuuV8ns4jD2R+xIv4VOouwY6RMv5H3Xk+X1Zhx80+T9+k7rcy/488uEH2/zWWnet12YLOJTz7ELlyn7gD1tOfM5/jgwd9ru0yltfNsz3UHeTZ39FvpKz/hx3ynuQAvrrLyz2MHbJP/1/Gcq6U8b/reQaT9f+MFcp5VN5Yrsg92Vj2QC+3mrGCq+T7X2MZfbxtp8O6e3aWsbyYzP8zltbNs4bG4tJHNDaW3ke+/zXWfLl8/4t+eyKOXW0sX+YAXYsPRJcb8cF6n/ftkSvPzp2NRe/yvupO3W3+/OiNvXN8ub7GYodk/I9yJ3lf3Y3vZd3Qe/GpjMGPxI4K/nwbTXvVZf6fsSzd/wO2Vr7/hRV4NhWfPijjf8RNZMzGV7JGxVxiKfv2LSAnZRxzMXJn+Zi/SrkxMv6HvbK/3xvIlXf0bxmLyPPWRuJ2vdf5Pfws+w9uRReZA/kx5QZ79hm6yN5JBcToXs92kxudfd0f8F++P4/+gQzZv+xXZCwr6djvxLcg4thR/CxjzSltTMZiWf/PWNYBX7ecseiuYo6dZKzgiKz/Zyye4/U7xViki2e1kStr8p5pLFfWOTmP9uZ6ndNp73UZ/4Pt8TIuQcb9nl1pLFvWImxBuTdl/M9Y/mdelxuMFcZ9/t2Efls964RfZJyhm7G8371Pe9GexON22qvvz/O7aG+o7P9LXXmnORSdP/fn/n3IlTnHMWQM9uXG4r/PfR48ZizzHe+rSeTGIzL/j7oNPJthLCbzlp7Fjjwv4znKne/rzsc2Wf9lkbH0trL/h7Gc971+K7D37/48Wk1dmT+5ljyQb4w3ULe+13kzdWUuSRy/yPeD29Gluy/3KXVlHtRXxKi7jP/BZF2DvfhAvtH5mXKv+X58P7GU9bMPcR7leRl/onMPz5JvMHvlu9kSxjJf9jEqa6xghWcVjaWP87ZVMZa7Ssb/KCf9QRrtyXXhDOrGfblz0e9sH8sGxnI6pjh2EUze9zQ1li3v2q5Alx8rOtbcWDzf+7SVsdjhiGNtjEXzfK61ww55vuyILr1l/h8+lbmhPSk3xbd3G2yH99+d1JXn82xjGVV8e/cYS5Pn6RHoJ2uKPUC5PK/fQ8by//JsHHIlvhORK+vkTyFuzb1PpxvLWivf/yIjV9b/gw2V8T9iJPsavUQ5WYPkZeLRUfb/wLbGMv5HfGX/t3xsk7rrjUWk33iX9qQ/+ABdZDx2GzK+8OV24gOx7UvimyL7/2KH+Pl7WA0Z/yMnZb7FL/hK7osPUvdR7+cj6DxAvv+9kTksvr3ixiJvelbGWEaK91/UWGG34o5VNpb5tsz/M5aW4fP0NGNxefdZl3Lybf05xgrmeFYf/eTe8UJj+aPk+19jWSM9uxx7f/bsKnSWuWrXGNP3odejSy0fj7aU2+Tr3mws+znPulKumoz/Gcut6lkffPA3fx7dYSwm+zIONBZd7dkQYnS97P9rLG+tt+N+2Ezfdz6I/yZ5nz6K/27ybAI6vy7jf/hP+pyniO9emf8HK5D5f/g0x8t4Htvk2Xkhde/0tuXhU8m1ZfhvvT+3XkPnLj7v1xAjsWMd5WTe1zv4PtvLeB+/zJHvf2nv5GTHPoHJftZfoJ98L/Q1tp3my31H3Z6y/h/xlTXJ91F3qffLb5TbIfP/jBXKvsiRTMsDmWNdLJM88LEsbSyzn2+vgrHoC7L+H+XE3urGsmWuwanI/TnJsTrIlb3yzjYWF5/Wo9zLvh+6wFjaM/4=
*/