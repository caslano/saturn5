// Copyright 2008-2010 Gordon Woodhull
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_MPL_GRAPH_DEPTH_FIRST_SEARCH_HPP_INCLUDED
#define BOOST_MSM_MPL_GRAPH_DEPTH_FIRST_SEARCH_HPP_INCLUDED

#include <boost/msm/mpl_graph/mpl_graph.hpp>

#include <boost/mpl/has_key.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/has_key.hpp>

#include "search_colors.hpp"

namespace boost {
namespace msm {
namespace mpl_graph {

// dfs takes a visitor which has all the bgl-like metafunctions encapsulated in an 
// "operations" member class, and also a state.  the operations are expected to return a new state
// in addition, the visitor operations are expected to update the colors of vertices
// and need to support a new metafunction get_color<Vertex, State>

struct dfs_default_visitor_operations {
    template<typename Vertex, typename Graph, typename State>
    struct initialize_vertex {
        typedef State type;       
    };
    
    template<typename Vertex, typename Graph, typename State>
    struct discover_vertex {
        typedef State type;       
    };
    
    template<typename Vertex, typename Graph, typename State>
    struct finish_vertex {
        typedef State type;       
    };
        
    template<typename Edge, typename Graph, typename State>
    struct tree_edge {
        typedef State type;
    };
    
    template<typename Edge, typename Graph, typename State>
    struct back_edge {
        typedef State type;
    };
    
    template<typename Edge, typename Graph, typename State>
    struct forward_or_cross_edge {
        typedef State type;
    };  
};

// requires IncidenceGraph
// returns pair<VisitorState, ColorState>
template<typename Graph, typename VisitorOps, typename VisitorState,
         typename Vertex, 
         typename ColorState = create_search_color_map::type >
struct depth_first_search {
    // enter vertex
    typedef typename VisitorOps::template 
        discover_vertex<Vertex, Graph, VisitorState>::type 
            discovered_state;
    typedef typename search_color_map_ops::template 
        set_color<Vertex, search_colors::Gray, ColorState>::type 
            discovered_colors;
            
    // loop over out edges
    typedef typename 
        mpl::fold<typename mpl_graph::out_edges<Vertex, Graph>::type, 
                  mpl::pair<discovered_state, discovered_colors>,
                  mpl::if_<boost::is_same<search_color_map_ops::get_color<mpl_graph::target<mpl::_2, Graph>, mpl::second<mpl::_1> >, 
                                          search_colors::White>,
                           // unseen target: recurse
                           depth_first_search<Graph, 
                                              VisitorOps, typename VisitorOps::template tree_edge<mpl::_2, Graph, mpl::first<mpl::_1> >, 
                                              mpl_graph::target<mpl::_2, Graph>, 
                                              mpl::second<mpl::_1> >,
                           // seen: back or forward edge
                           mpl::pair<mpl::if_<boost::is_same<typename search_color_map_ops::template 
                                                 get_color<mpl_graph::target<mpl::_2, Graph>, mpl::second<mpl::_1 > >, 
                                                 search_colors::Gray>,
                                              typename VisitorOps::template back_edge<mpl::_2, Graph, mpl::first<mpl::_1> >,
                                              typename VisitorOps::template forward_or_cross_edge<mpl::_2, Graph, mpl::first<mpl::_1> > >,  // Black
                                     mpl::second<mpl::_1> > > 
                 >::type after_outedges;
                 
    // leave vertex, and done!
    typedef mpl::pair<typename VisitorOps::template finish_vertex<Vertex, Graph, typename mpl::first<after_outedges>::type >::type,
                      typename search_color_map_ops::template set_color<Vertex, search_colors::Black, typename mpl::second<after_outedges>::type>::type> type;
};

// requires IncidenceGraph, VertexListGraph
template<typename Graph, typename VisitorOps, typename VisitorState,
         typename FirstVertex = typename mpl::front<typename mpl_graph::vertices<Graph>::type>::type,
         typename ColorState = create_search_color_map::type>
struct depth_first_search_all : // visit first then rest
    mpl::fold<typename mpl_graph::vertices<Graph>::type,
              typename depth_first_search<Graph, 
                                          VisitorOps, VisitorState, 
                                          FirstVertex, 
                                          ColorState>::type, 
              mpl::if_<boost::is_same<search_color_map_ops::get_color<mpl::_2, mpl::second<mpl::_1> >,
                                      search_colors::White>, // visit any yet unvisited
                       depth_first_search<Graph,
                                 VisitorOps, mpl::first<mpl::_1>,
                                 mpl::_2,
                                 mpl::second<mpl::_1> >,
                       mpl::_1> >   
{};

} // namespace mpl_graph
} // namespace msm
} // namespace boost


#endif // BOOST_MSM_MPL_GRAPH_DEPTH_FIRST_SEARCH_HPP_INCLUDED

/* depth_first_search.hpp
4cePSeg7Hs73Qc2jurx8H4wNu1P4EcvKKLdj0qNEtb/4YGCbEDOorTwGOr0qiMb2iitoPF/6Y8YojlInrgHaF3lPI4uGRQCuV9CbF7y7xTWG78SEgXN4QJRMZNSaT/5f+DwVs0uEpMgizdK9VIOgpEWcsRJdXpxFbsVM5YO5HxdPKf2vZs3ZOSj6ZSJPW6th4qmwhzbDx45kvstdK9FP0PWSyk/yy+5KT4ChZcmQr0r3hjd0aZEy3/Cysozh3uVPU2SHbFxd8kNDTupFBgU5Lud/2E7vMnAQAOSxHPEg49Iw9qwGiw7yBh3Rb7igCPog+/nr53dARsImx/Cjo0PrByFz7Sj3EdISUyYPbveT2kJtr8mvJ6Nki/dw3njgRLw1wLMwRhjtHbJYtxVuK6GH1qDSPCJ9FOJTNZ2J6mMNhCU6tOutoo5oNMPj3+qv9lHWn3bwb53pnuzaZY5rhr9Gi3zdb8EAmJ/e6XzdGsOSECtl0P3V+cw+nl4sN3o/AA6eYGSyC+bwERWJiPA1DD1oQ10wAFTEdPfv1NK1Gi+w9naQsXeYkBXv4mIJS6WJ6jxG5I6ujwEWxa6IRdYe9Zy3hs4BgJGY7hNzbOvL9HX0dOa26lRLrgmkVg9h6prsXrsxab4ZhYnmI4FRa07ekMlLMy5N4Y8yggfXEfaYmUooOKK7+PrISmuLavHdCEk4Jx3Rvmb9D1uFFoUS8QPhQ4ouHMV5uhdkHXl8DutdJWrdo/nXjwZdUA+yNQkSKR25obpGenWSLC4q8iGHFETGMD0RMZk0yUgr+0QhWBdgPRhMyOK1bSH6R5suqEe0LkHET9xCc03deckiOteoj227FIhDvnJ4e0UHlxljA1Vdhdzvcx/RJdTJrjKDd4tQKOGycQ8ERuRStOUX7exPcu/DjEufVfYnKPWgpMn4yFVjTLZkVtn0r8zsv9FJv986ZjE1+UXi4nowv9N45bA3qTIF+XXdM0ST8rFWn3/8XAZKMG/UTIw844uN+HjoyzPcGtQNDqVahCIAccb2fVxOc8TIsScmXt+tSQGgCKrIZuj+XcRax3vurv021IyxYjlSrivF96rDzgTC7DKQMh7vLQ8se+yf882AtNKIxPOexH1V2G+cDMLKkbda7pI6EA3gdhLKKmbGyohyxqyx1vj0oRqmOequy3+oQE58FN1f6zRvbp1MfXAeBxczXDmlrN0/uYyfFvrl7ifM0XubsefYIV7MFuZAYK68O7i0SxROnvYbQKYAuyYm+cZra5x/mNd6jpe9EmD9flLJqJJ4bjkheSZfGjOOS5MXJuEUrQS+GPsYwmpoYarSjZfq/OuR9phlsvNSFl70wQCKAzgAPxOpkU3GHxnHm+gj1YfBHP7BwR+e/vuy1qo1X8L+XdYanLG3pxaEaitBQTpincS+5HD49KO0pItMPV/kdzW5S/hnp08EyR0iaGDlo1wwQbMQhoSY5iwoxyLtCMjBk0VHFfBhbKiK5t4HYxpFQ6fU1X7eE17CbyOD78si92ibulWKmQAGLPnTxGcazW/y52QJc90HFuvnZUf0TErT+ULlecrehBmbOAxaQk2lRsVmn44WfBqZTzNRaq8ttCKPMPhTkqyZoS82QU7YhOQsKA7NBq9p7cCTQWGoAnIcJ+VUVaEgQG0VasPcYxvqo5eOqrGxi+Oa0zO2fQwdtuGAvG3/LAlCkyb1BPnoDCKvFUXZ0nEJJXppIWtMDPCSOUari5B/lHB1uZYih15wghq9DULi1FsJkGcLC9xIt5+77D3VU8Ohw/hkeXQTLqfiggeFCvWRiM8n/H3zUNPZBu8nfLsAMx5dJrKIjYAtS8svcMuOF8JWFYd6LtaWJQ81raWynPITMcxfLoqx061q+ipNVe6Exaztfp6nzy2piFtsYmls55YmhNnRjYJweKNalOJZK8pD1NkTVN2OVQgBBxHkzroJgb1OU76qHCB/jeaaFl7JTqN5iAe40uekLpiHlZrY/ZONHzIoxQ7QFLmxvOqJb8/fXFibvVMwmcgAC8whFqzBJZnTmAt+tX8xed74hsgokcwDzWr++YoEV6GMPDPHjavHUjcg4lD+ql2TCRE2OZm9UslTZdf9Q/Yh7PAn+h+2E5dDggLdOytsK1QGTaucWrNiQYx1F2Efw5Ehbe/XFNEjqdZksDE/ex9rN7FohL1rV1xI7YIwNMQZETKWHEKhl/zIxmTYx9fOGu0OkTfRPunsFhtIG64451dExnXvdnlo7TExhTKhAWTwxXm44A1auS9dGDQONvOSweQPm+rd8BchVQ/jwwWp5nWSpe/ZxoUv494tJqQRYn8umWAw+zCvBgLZDhMT49opZGZkE5ftow1m0kdNQ7OsxpbXFECngQqKCVa1Yqm08twyrBc0gSeiyYXc4U9Xp4YuCni+rwkKN1j7qyU2mgyp06Qb9kiSsGSb+dlad+BpbZ9vMjHuTC+fC3XGky/nNvczpDqepO3QBF7qtSQAVYXm0xzBSTHMQMyYxUrxPH/sJnfBfRGFlrGjtKTwOGfjTU+EgTsOTAZXjZ0GbI1eR68jjHhlyVdGhwqhF/SIXtR2S+P19EdX+EKEdhxUYY0stwGuNbORfrTGcoaFcUivn6oYIi9HdI4iMHozJWZYwpTnTV9MqJjPH4Xpit4LAZivWLCfyJ14nVLvYrDw/U5w8cdZwz0OENOaHNZebOBJA4q+ARsFE95XWBo2ZkzYp84RGCCa3ekxztuF0WHMK9jjIRCtu29eJ30ZkbY2TiJRr3/9dmGMWfCDKZ67ojz6B0XUOZesWmAMhVGBnS9QhnZkCG+P1zizAkdOcOgO4nDtEkpIAEblNnhQtj+aqwrHTt6/XnZlfC8DO0rY3/m7U9ATIfyIYm0WLQx2ASkjXbtGNe1CrNkhxpRfGxpRZvyd9nFnK2w/AkeDRcru+PuQm5TYIOID6vmO0APqJedxmSTh6BBVIglX/hBhZQGVvnsx9caDB57GX2kX0EcvNT/1u2Gh7bF14SV1yRf8NbTj0j/huWpw6GG84fGkEtK4RPLjDWzx35Lh2luhrm0BHFcNoJfxYy9dRgcVEK0Ml2cpa0oiAz7b1NqbhHY+MOcuQ67gbKSYSHuf4+7fTXEIUviGH2zSqCtfdKXiBq1Qh3BRua6mneAXRBJJHFDoSHFpJvui5feLor7ll1iXIJVldDgXtkOKDBk+lDtKn0jpO2ur3oLFxxgrRyT2NGgl9hGeSnbFE4+eaaPL4O0cV34hseuHl27DP2j6IZ7mmwR/ZJ3OKaqL0h/9fNVnwfVyvibz8Pa5zoDpRb6FHLn12SNg90n2s/3CdU2f0xPA7EtM7S0R2zLEZ/v1n/PB9yDT0+GrccTp2YAHdJiPh6K/lmu7XtDQM6WrDYuSJc8kdtENJC+xrd2zolFySki7syXfWpSPSchX/urwQXGTyrenJq75bq60a6m+UvDhTF61w7E5XPoc3lrfUKNSYPWKwMimOjaGQuUXoJNvoaCNEanpW6hXqm3Xo+d6r109gFcPdKtAsqcu4CHuHG8mGojidYkStkPS684KVaHYbU6rgNHEXNsQsnLH0Nt1M2+xvJm8ndB8HohJskgaSLyg13ZLvzI9o1ow49J5emwktDVE3niTga32Bc+luMy2pp32yMO4TtdP56oNPbjcVytjMrO3MibLU4XlvUc9BeRcnOEqNqvsvdC5RJW3yRFp5jfXjjTeEG+8qsT4QzoP1PdjfpBcsk54lljYla78G5lhiw/uXtB+t/a17aISukZSLXfv5QRzqvKf9J0hrrI79CGW4WpPX8h7Y95u0LrI7oUFazbWF2A1w8lWcRFq/xy95InzhYswEB7jAo1/b/r0PHaPVIKIvH926qVyksljD1npncRDwGuHQgU8XcBkpH9/iRYnOHtkW4Di7qQRexAecBg1NaY5G+tq9cUdKQVsQRMz89nR8vLLAzBs4mnpfrTHXZkzkEO9OSlgIaELsf0Bp/eQo/eyRiqB3QQCJIz9dFPd3YbD90jmlEnQDTcf9JNyfcp9z10lN+qB31MC6hjuBXnjfiL2131nftUt8vg07vo3CRhO7A2NAGbj7h+p1bGI44zccKB9vXtLwzX6wmDvnsLyepbN7xzv88lo9Y9PMN+MfG1iOBVxjDWb1mJDqp77MPVzkbMUOD0ZjVGFLckZEV9gsX4F4ON7PLO8NZQlr47kHT3v22cn6YisdcffmBoM6pc2/QyohJgjBBiErdA+GBZIlAosHMSJkNcE91st3H55d3b/Fq40/YJXOR0USBDp5Yt+Gmwx6q3uhnxK3ew70Zpe5Umf8FIC9Cgqd1nsPtqaxEGVFmmCLYBRcdpw5LPWqshS7YUlZvR8sxQ24+WopCU8LMs61c07wchW10KEjEGPhdRNoJg9Fa7xE2QUWmU0zYUB0qsK6mepbQ59WXsh+hHaeQ1a/45ieksfhmv8U7KMOpHEA0R+bAxxUx0vBPLeaKgVFIVMp661DaoNXvmF01vyEvf2QJPgZ9YOSW0DAb58PIsQEIMmhQErQ9JCu36mYz70UPhjqw7npw/u5tiKvOk2fJ4NexLkg47H6fm0eOb2R22GbzZDcdiFe98lD9zHfb473FSOESHpgg2xMoOr1vMu1Qkx71z1LhJ1EbczvSQhf7x5C/G4iltmx/Kp2Re408A4tr1OcvxrPuhJsPskqXsnQVZi2wGmETiZDQmKq3WHWQiAjEDcOHP5oRYfhO5lGolmEbJ6DPGmBkJwApAquhnmYZbvBbX5JoVd55r0ea/27d1tjLcRUt2xfMsTaCjYIbYDB4wWt31aXk6LRVQyB3AmMQqt7BiiF6f9uVkwPjNmzRnStkA957liECiJ7lvb6zg8dtuiTz0LTTks1N58hf+MSrvfIz5fXn4r9nR/VDx/qbCXLvyN9C3MwnKMccM+xdXdPkns8tuD78oLyyYwqCeQuNWQpAFAXaN3JJRSRmwz3L2r092rSZ0dieqiv878DoSPvxBdu0OY8icAbzLWpLx3scSECZ0T16kkpA+osGGkH5Lmg7KyMHKiOiXa5o9bOyWI9wiNWwqzAjs+ciVv9ZLiojZlzFSkFulH3uSyfR2xb1zHTM/7NGbdjwa+y+vHOUG68eYiSvVF8IhiWCyd+AEFMUDQaZEnmJKG79zoavPpEG7rDt4WdXznKJvx2QFAYhRp9ELjcoG+EIDovdm/z57uA13AQ+vKfmokrmsUP3TeE1xRAROZRKit2nfyBF+6J5YGkdbz5UE6TPXpwkWlgORHCJY/CQEyEXH8/vGSXeJJ1mGe6wboEr5mWtXePHvzXWTxecTZob2xaHu90MJRWZBUXlyRbZBxYYQG+H3R7q1lU/PyXGdZZgOduvoGv8qZcHn0/OrI3kiK9lOmHTU7IDHpKgv4mhzoIpcVqBeFHJRKJ9wLnaR91QEoG1dsu+iqAVTaOzaXeJiexJNM6CzGENqq2NhJEvjh7zmac5tDgzgXeuC+b3Fzn/VwLwwZhTGy7iZlkJ3ihKAo6SEAjide0DcWJ65u6T8o8yvNdQR/p0QxA95fpPVkjwcjino3AlVfdMh3PJSsILxlkhHqfI3jcDYaYaYY5+g2TbXNN/Vj1Y8/bc0mO5feNSLS+j0yfpaL+tJNJWjtYYc8ojTTAZEQT/HB3XuStRCvHQ5Y1Jv7ZEHagdJ+7hj2EyyVzRIghHNbzl/7M3/QdhfeTxViRFEMaX09V8h6ohxFYqre9KkYv5caCj1d2NQdS/d2dLmfej3yBdL2Bj3dKtmzKJMe/YgfLyrXmkDnrTJtZO0WZbMRfzhjemID740EHXfHaOem3aNW3YTFEcNOdsXl0khhUQS266h1A4YPqOJk+SePLzqNv88HoXT4N9ZsJTGJQ2bGFwXslof439EVDajdmezx6uIX81EM68j1UPe6Iw8u9XisbYB9eStGsVTiYXuWzW/h/W49w7xiXDYQa93588WumbhbAJfA3vASykFwWEqqfAAgyAvF70yk9kXEpR7Nf3fe3OirOiMCawdi+3Uonh2ztdhs7+oLTe9eYEB9pXMPomu7uuC5G66ZDbc5naW9QqzuT8RMSCdsoGN6caKHxpesaknrI47KU72Aqlr7BLgaVdY3cxziH0myFFpAu9TQsaZ6XmVLkaMfe7GcphFpLy08nCQ3q+32CExq7aBwm/DqKBwcOUb9PMIORe9Yvwcc3BZ/okBbC+28nE1TOxVCODaC3RVkJ+Wzh1gGNAB7V4GmX5AyIRaI7vwHquP0W0WfsRZ6iE0DsIW7HfBrbiteCHsZu0i+12BE8pJx4ZrC3VIAi5YgSFaDjB5QezVZldX7aRQohX/dnr7o1L59FH1vRiSZm13/7ibjaJ2wZi8EQzEBdvM62UVjQuwDbfDwqiIMpLC4QHidO4LYJWwVD2M4X5hTfc285o9dPDXGTGTc8pbaCLCYmFHqkKAfcZGwn7mnA0IrYmbZRAXwuOLtjB+64zqnqTtix+0LmWEgDerip9MrEsq5aLY18RZvYNqpnLkq0vkcYe1tF5z/4x5GdSBD4ElBDWQzG9XlNXItzsY++fFPVsqOi9RgWlEeIvYdqfacd1zJXihMOHXDgbco64upQf3jQYF5hT1wJdukpudLOoxl2al9yck01WbVN56MtX0UKA7QwqaR+DjZOorkTb4CMOl8DvMklGMGHseGW/JTlxI24q1Uh8XZZEnTv1S4f1KySK2WdlHQ99mv5hLOHel851HSqefy3EXwUQZp1HMLiUAfQk19SVka+A5l6oqfJorvo2FjACA0/Rxa+waYxlqAq0eqkm/k9dQOn6G5DmcSEWAX43JA2b1JH1ZiHEy8CscWM6bNA2WNG2yF9HCCG7wniib0sOj/lpOgyR/Ta2+spayNoFSn9jQAYWOn64N7el5A+EUm2aKf79Odi6UWHgOIhET10Fyct6qg8LrgytMa4Nf6LXkUK2bR55IOP23Dcydu0FRyQqah+mjBrcLOx8dFJSeIGikfM8EwSgXHf/mjfGqvs9FSFY4MpCvlRS4Uokt1wRVGMScVft56LKqm58Dx9UfGhThnMv9fOogXZuUVpm9giNai97GB0H0NNVfJJT3ml94Nj3htzL3+CELXkC5eyIYvAg63kC4HemErqeg3qbUFkQFWwgBdSEHB7nEWlxdlgP160lt22ls9/7ZnquMN5VxjiEsC7zuS43WjMBtRzkxNOc8EepaPPauPuN0NrKrj2t8T03JEI1v132iQ24VbeWJnyAqq+2LMWwjJk/60nsGU+DXWWJxCnV2Aj+LeGDPZlzUbBz6PeDnqcV51tpsFmYkqr3emw+8J4o9LVn7zEx5dMgkp6MuOaTKBl+N0AXplR/xcizqzs+k+D1j4LtLLWTNAsvCDdPnax/s4AwVwfOZ0JaQNdc2Rr7r2FPDaSRAdbhkkOmNMH2oLBtlL5IWbZhEXOhF/dML6ebDOCZXDkmt1QiphYTRMDz5V9iB1C669I7H9ooOJ2bpXgT5c7csy9/1ddcE3Gk5wSjC7DJ9jYWsFW8XccqP5uL2M3oJx/bh6YjkXh7Q84x7BwPX07CFknpzgp0giHGVuja+XsPnbYZ3NX1KwTb3b9me4yiwTLiPkasu7O1bDwRf9jeD+0U+N
*/