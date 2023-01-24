
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F

    , typename has_apply_ = typename aux::has_apply<F>::type

    >
struct apply_wrap0

{
    typedef typename F::template apply<
        
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap0<int>
{
    typedef int type;
};

template<
      typename F, typename T1

    >
struct apply_wrap1

{
    typedef typename F::template apply<
         T1
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap1< int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2

    >
struct apply_wrap2

{
    typedef typename F::template apply<
         T1, T2
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap2< int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3

    >
struct apply_wrap3

{
    typedef typename F::template apply<
         T1, T2, T3
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap3< int,int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4

    >
struct apply_wrap4

{
    typedef typename F::template apply<
         T1, T2, T3, T4
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap4< int,int,int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5

    >
struct apply_wrap5

{
    typedef typename F::template apply<
         T1, T2, T3, T4, T5
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap5< int,int,int,int,int,int >
{
    typedef int type;
};

}}


/* apply_wrap.hpp
MR1nP03rLq2nPeH1ZjTufj8+bsOkhV+8Jx7v2wlqpC+SJrqVUlulO8luLumqFQo43SPimqWEaZb6Q9pv1YFbFzJUCN57mQPVxz6CUwnNoYC8flNNoai7HB/VdagVv1t6cl9/YFxqlP9zWSofcf4npzIQVVaYGyaEGDUl6MZ4JUXlIxeZ0UztFxrVlnwFmZvNDvJPgo7NsfBl58AEtcBTzaOn8sun2h2vYYG3HZNKZXzbrrTq9yGCZQbZRcu+3pHzEyoicRp/Mn7kNo+H0F/cu0n5x+iBR/fLd/T/UHpUSKuuxjWvFvlj6CzbSlhWx9nt9lOR92icJbEU0BY8aHh0fStljB6Ui28aZZ78VZc7Zm54yq7j5e449DElY0d1kNBsAQX2r7jO/QGIDwnseSsjd0YtFq5gQ5EVGrJKC87I/IHbmI5D+ma9MChIq6Bp9YHBqaNIOg/huEWL46Ps0EyzXncDVqobrY7XO1qbPoSX0idmIpS+aI7rpeBODcnRKYgyEnnPLpvPuA85jr+UDKsi0GpPvasqC5psNk1XvYvbME7ihhv4SlzfK42M3W+e32ZapmdR5LcuupWjX3elil2rzZHe2+weIpdHimrBcFsG2eqtNaElgM0cExD088Edj4ZgnaNI6sbE4LZqBnkelQOVg+xA8lfxHqpbM9qGl/pL7j+rN7QdCGNI40IpBnEtH6zaEHb8dfQWDN0sJCP/
*/